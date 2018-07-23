#include "bezierC2Interpolated.h"
#include "3dmath.h"
#include "Point3D.h"
#include "utils.h"
#include "curveQuadratic.h"
#include "curveCubic.h"

BezierC2Interpolated::BezierC2Interpolated(ObjectType type, QString name)
	: DrawableObject(type, name), m_showPolyline(false)
{
}

BezierC2Interpolated::~BezierC2Interpolated()
{
}

void BezierC2Interpolated::draw(std::vector<QVector4D>& vec) const
{
	draw(vec, m_color);
}

void BezierC2Interpolated::draw(std::vector<QVector4D>& vec, float3 color) const
{
	if (m_vertices.size() < 2)
	{
		return;
	}
	for (std::vector<int>::const_iterator it = m_indices.begin(); it != m_indices.end() - 1; ++it)
	{
		if (*it == -1 || *(it + 1) == -1
			|| vec.at(*it).z() <= CAM_NEAR || vec.at(*(it + 1)).z() <= CAM_NEAR
			|| vec.at(*it).z() > 1 || vec.at(*(it + 1)).z() > 1)
		{
			continue;
		}
		drawLine(vec.at(*it), vec.at(*(it + 1)), color);
	}
}

void BezierC2Interpolated::setModelMatrix(const QMatrix4x4& matrix)
{
	m_modelMatrix = matrix;
}

QList<int> BezierC2Interpolated::getControlPointIds() const
{
	QList<int> pointIds;
	for (int i = 0; i < m_controlPoints.count(); ++i)
	{
		pointIds.append(m_controlPoints.at(i)->getId());
	}
	return pointIds;
}

const QList<std::shared_ptr<Point3D>>& BezierC2Interpolated::getControlPoints() const
{
	return m_controlPoints;
}

void BezierC2Interpolated::createVertices()
{
	m_vertices.clear();
	std::vector<float> upperDiag;
	std::vector<float> middleDiag;
	std::vector<float> lowerDiag;
	std::vector<QVector3D> rhsVec;
	const std::vector<float> distances = calculateDistances();
	initializeMatrixData(upperDiag, middleDiag, lowerDiag, rhsVec, distances);

	std::vector<QVector3D> cTemp = computeMatrix(upperDiag, middleDiag, lowerDiag, rhsVec);
	std::vector<QVector3D> c;
	c.reserve(cTemp.size() + 2);
	c.push_back(QVector3D(0, 0, 0));
	for (int i = 0; i < cTemp.size(); ++i)
	{
		c.push_back(cTemp.at(i));
	}
	c.push_back(QVector3D(0, 0, 0));

	std::vector<QVector3D> d = computeDCoeff(c, distances);
	std::vector<QVector3D> b = computeBCoeff(c, d, distances);

	std::vector<QVector4D> controlPoints;
	controlPoints.reserve(4);
	for (int i = 0; i < b.size(); ++i)
	{
		convertPowerToBernstein(m_controlPoints.at(i)->getPosition(), b.at(i) * distances.at(i), c.at(i) * pow(distances.at(i), 2), d.at(i) * pow(distances.at(i), 3), controlPoints);
		getCubicCurve(controlPoints);
		controlPoints.clear();
	}

	if (m_showPolyline)
	{
		for (int i = 0; i < m_controlPoints.count(); ++i)
		{
			m_vertices.push_back(m_controlPoints.at(i)->getPosition());
		}
	}
}

void BezierC2Interpolated::generateIndices()
{
	m_indices.clear();
	m_indices.reserve(m_vertices.size() + 1);
	int verticesSize = m_vertices.size();
	m_showPolyline ? verticesSize -= m_controlPoints.count() : verticesSize;
	for (int i = 0; i < verticesSize; ++i)
	{
		m_indices.push_back(i);
	}
	if (m_showPolyline)
	{
		m_indices.push_back(-1);
		for (int i = 0; i < m_controlPoints.count(); ++i)
		{
			m_indices.push_back(verticesSize + i);
		}
	}
}

std::vector<float> BezierC2Interpolated::calculateDistances() const
{
	std::vector<float> distances;
	distances.reserve(m_controlPoints.size() - 1);
	for (int i = 0; i < m_controlPoints.size() - 1; ++i)
	{
		distances.push_back(math3d::calculateDistance3D(m_controlPoints.at(i + 1), m_controlPoints.at(i)));
	}
	return distances;
}

std::vector<QVector3D> BezierC2Interpolated::computeDCoeff(const std::vector<QVector3D>& c, const std::vector<float>& distances) const
{
	std::vector<QVector3D> d;
	d.reserve(c.size() - 1);
	for (int i = 0; i < c.size() - 1; ++i)
	{
		d.push_back((c.at(i + 1) - c.at(i)) / (3 * distances.at(i)));
	}
	return d;
}

std::vector<QVector3D> BezierC2Interpolated::computeBCoeff(const std::vector<QVector3D>& c, const std::vector<QVector3D>& d, const std::vector<float>& distances) const
{
	std::vector<QVector3D> b;
	b.reserve(c.size() - 1);
	for (int i = 0; i < c.size() - 1; ++i)
	{
		b.push_back((m_controlPoints.at(i + 1)->getPosition() - m_controlPoints.at(i)->getPosition() - c.at(i) * powf(distances.at(i), 2) - d.at(i) * powf(distances.at(i), 3)) / distances.at(i));
	}
	return b;
}

std::vector<QVector3D> BezierC2Interpolated::computeMatrix(const std::vector<float>& upperDiag, const std::vector<float>& middleDiag, const std::vector<float>& lowerDiag, const std::vector<QVector3D>& rhsVec) const
{
	std::vector<float> c;
	std::vector<QVector3D> d;
	std::vector<QVector3D> cRet(rhsVec.size(), QVector3D(0, 0, 0));
	c.reserve(rhsVec.size() - 1);
	d.reserve(rhsVec.size());

	c.push_back(upperDiag.at(0) / middleDiag.at(0));
	for (int i = 1; i < rhsVec.size() - 1; ++i)
	{
		c.push_back(upperDiag.at(i) / (middleDiag.at(i) - lowerDiag.at(i - 1) * c.at(i - 1)));
	}

	d.push_back(rhsVec.at(0) / middleDiag.at(0));
	for (int i = 1; i < rhsVec.size(); ++i)
	{
		d.push_back((rhsVec.at(i) - lowerDiag.at(i - 1) * d.at(i - 1)) / (middleDiag.at(i) - lowerDiag.at(i - 1) * c.at(i - 1)));
	}

	cRet.at(cRet.size() - 1) = d.at(cRet.size() - 1);
	for (int i = cRet.size() - 2; i >= 0; --i)
	{
		cRet.at(i) = d.at(i) - (c.at(i) * cRet.at(i + 1));
	}
	return cRet;
}

void BezierC2Interpolated::initializeMatrixData(std::vector<float>& upperDiag, std::vector<float>& middleDiag, std::vector<float>& lowerDiag, std::vector<QVector3D>& rhsVec, const std::vector<float> &distances) const
{
	int pointsCount = m_controlPoints.count();
	upperDiag.reserve(pointsCount - 3);
	middleDiag.reserve(pointsCount - 2);
	lowerDiag.reserve(pointsCount - 3);
	rhsVec.reserve(pointsCount - 2);

	for (int i = 0; i < pointsCount - 3; ++i)
	{
		upperDiag.push_back(distances.at(i + 1) / (distances.at(i) + distances.at(i + 1)));
		lowerDiag.push_back(distances.at(i + 1) / (distances.at(i + 1) + distances.at(i + 2)));
	}

	for (int i = 0; i < pointsCount - 2; ++i)
	{
		middleDiag.push_back(2);
		rhsVec.push_back(3 * ((m_controlPoints[i + 2]->getPosition() - m_controlPoints[i + 1]->getPosition()) / distances.at(i + 1) - (m_controlPoints[i + 1]->getPosition() - m_controlPoints[i]->getPosition()) / distances.at(i)) / (distances.at(i) + distances.at(i + 1)));
	}
}

void BezierC2Interpolated::convertPowerToBernstein(QVector3D a, QVector3D b, QVector3D c, QVector3D d, std::vector<QVector4D> &vec)
{
	vec.push_back(QVector4D(a, 1.0f));
	vec.push_back(QVector4D(a + (1.0f / 3.0f) * b, 1.0f));
	vec.push_back(QVector4D(a + (2.0f / 3.0f) * b + (1.0f / 3.0f) * c, 1.0f));
	vec.push_back(QVector4D(a + b + c + d, 1.0f));
}

void BezierC2Interpolated::getCubicCurve(const std::vector<QVector4D>& controlPoints)
{
	int points = controlPoints.size();
	if (points < 1)
	{
		return;
	}
	int cubic = floor((points - 1) / 3);
	for (int i = 0; i < cubic; ++i)
	{
		std::unique_ptr<CurveCubic> curveCubic = std::make_unique<CurveCubic>(CurveCubic(m_width, m_height, controlPoints.at(3 * i),
			controlPoints.at(3 * i + 1), controlPoints.at(3 * i + 2), controlPoints.at(3 * i + 3)));
		curveCubic->generateCurve(m_vertices);
	}
}

bool BezierC2Interpolated::addControlPoint(const std::shared_ptr<DrawableObject>& point)
{
	if (point->m_type != ObjectType::point3D)
		return false;
	for (int i = 0; i < m_controlPoints.count(); ++i)
	{
		if (m_controlPoints.at(i)->getId() == point->getId())
			return false;
	}
	m_controlPoints.push_back(std::static_pointer_cast<Point3D>(point));
	createVertices();
	generateIndices();
	return true;
}

bool BezierC2Interpolated::assignControlPoints(const std::vector<std::shared_ptr<DrawableObject>>& points)
{
	m_controlPoints.clear();
	m_controlPoints.reserve(points.size());
	for (int i = 0; i < points.size(); ++i)
	{
		if (points.at(i)->m_type != ObjectType::point3D)
		{
			m_controlPoints.clear();
			return false;
		}
		m_controlPoints.push_back(std::static_pointer_cast<Point3D>(points.at(i)));
	}
	if (m_controlPoints.size() < 4)
		return true;
	createVertices();
	generateIndices();
	return true;
}

void BezierC2Interpolated::removeControlPoint(const std::shared_ptr<DrawableObject>& point)
{
	removeControlPoint(point->getId());
}

void BezierC2Interpolated::removeControlPoint(int pointId)
{
	for (int i = 0; i < m_controlPoints.count(); ++i)
	{
		if (pointId == m_controlPoints.at(i)->getId())
		{
			m_controlPoints.removeAt(i);
		}
	}
	createVertices();
	generateIndices();
}
