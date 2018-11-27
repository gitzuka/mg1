#include "trimmingCurve.h"
#include "utils.h"
#include "curveCubic.h"
#include "bezierC2Interpolated.h"
#include "3dmath.h"

TrimmingCurve::TrimmingCurve(ObjectType type, QString name) :
	DrawableObject(type, name)
{
	m_color = float3(128, 0, 128);
}

TrimmingCurve::TrimmingCurve(ObjectType type, QString name, std::vector<QVector4D> vertices) :
	DrawableObject(type, name)
{
	m_color = float3(128, 0, 128);
	m_vertices.swap(vertices);
}

TrimmingCurve::~TrimmingCurve()
{
}

void TrimmingCurve::draw(std::vector<QVector4D>& vec) const
{
	draw(vec, m_color);
}

void TrimmingCurve::draw(std::vector<QVector4D>& vec, float3 color) const
{
	if (m_vertices.size() < 2)
	{
		return;
	}
	int i = 0;
	for (std::vector<int>::const_iterator it = m_indices.begin(); it != m_indices.end() - 1; ++it)
	{
		if (*it == -1 || *(it + 1) == -1
			|| vec.at(*it).z() <= CAM_NEAR || vec.at(*(it + 1)).z() <= CAM_NEAR
			|| vec.at(*it).z() > 1 || vec.at(*(it + 1)).z() > 1)
		{
			continue;
		}
		drawLine(vec.at(*it), vec.at(*(it + 1)), color);
		//drawLine(vec.at(*it), vec.at(*(it + 1)), swapColors(i));
		++i;
	}
}

void TrimmingCurve::setModelMatrix(const QMatrix4x4& matrix)
{
	m_modelMatrix = matrix;
}

void TrimmingCurve::setVertices(std::vector<QVector4D>& vertices)
{
	m_vertices.swap(vertices);
	generateIndices();
}

void TrimmingCurve::setParametrization(std::vector<QVector4D>& parametrization)
{
	m_parametrization.swap(parametrization);
}

const std::vector<QVector4D>& TrimmingCurve::getParametrization() const
{
	return m_parametrization;
}

void TrimmingCurve::upgradeToInterpolating()
{
	BezierC2Interpolated curve(DrawableObject::ObjectType::bezierC2Interpolated, "interpolated");
	std::vector<QVector4D> controlPoints;
	controlPoints.swap(m_vertices);
	//m_vertices.clear();
	m_indices.clear();
	std::vector<float> upperDiag;
	std::vector<float> middleDiag;
	std::vector<float> lowerDiag;
	std::vector<QVector3D> rhsVec;
	const std::vector<float> distances = calculateDistances(controlPoints);
	initializeMatrixData(upperDiag, middleDiag, lowerDiag, rhsVec, distances, controlPoints);

	std::vector<QVector3D> cTemp = curve.computeMatrix(upperDiag, middleDiag, lowerDiag, rhsVec);
	std::vector<QVector3D> c;
	c.reserve(cTemp.size() + 2);
	c.push_back(QVector3D(0, 0, 0));
	for (int i = 0; i < cTemp.size(); ++i)
	{
		c.push_back(cTemp.at(i));
	}
	c.push_back(QVector3D(0, 0, 0));

	std::vector<QVector3D> d = curve.computeDCoeff(c, distances);
	std::vector<QVector3D> b = computeBCoeff(c, d, distances, controlPoints);

	std::vector<QVector4D> controlPoints2;
	controlPoints2.reserve(4);
	for (int i = 0; i < b.size(); ++i)
	{
		curve.convertPowerToBernstein(QVector3D(controlPoints.at(i)), b.at(i) * distances.at(i), c.at(i) * pow(distances.at(i), 2), d.at(i) * pow(distances.at(i), 3), controlPoints2);
		getCubicCurve(controlPoints2);
		controlPoints2.clear();
	}

	m_indices.reserve(m_vertices.size() + 1);
	for (int i = 0; i < m_vertices.size(); ++i)
	{
		m_indices.push_back(i);
	}
}

std::vector<float> TrimmingCurve::calculateDistances(const std::vector<QVector4D> &controlPoints) const
{
	std::vector<float> distances;
	distances.reserve(controlPoints.size() - 1);
	for (int i = 0; i < controlPoints.size() - 1; ++i)
	{
		distances.push_back(math3d::calculateDistance3D(controlPoints.at(i + 1), controlPoints.at(i)));
	}
	return distances;
}

std::vector<QVector3D> TrimmingCurve::computeBCoeff(const std::vector<QVector3D>& c, const std::vector<QVector3D>& d,
	const std::vector<float>& distances, const std::vector<QVector4D> &controlPoints) const
{
	std::vector<QVector3D> b;
	b.reserve(c.size() - 1);
	for (int i = 0; i < c.size() - 1; ++i)
	{
		b.push_back((QVector3D(controlPoints.at(i + 1)) - QVector3D(controlPoints.at(i)) - c.at(i) * powf(distances.at(i), 2) - d.at(i) * powf(distances.at(i), 3)) / distances.at(i));
	}
	return b;
}

void TrimmingCurve::initializeMatrixData(std::vector<float>& upperDiag, std::vector<float>& middleDiag,
	std::vector<float>& lowerDiag, std::vector<QVector3D>& rhsVec, const std::vector<float>& distances, const std::vector<QVector4D> &controlPoints) const
{
	int pointsCount = controlPoints.size();
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
		rhsVec.push_back(3 * ((QVector3D(controlPoints[i + 2]) - QVector3D(controlPoints[i + 1])) / distances.at(i + 1) - 
			(QVector3D(controlPoints[i + 1]) - QVector3D(controlPoints[i])) / distances.at(i))
			/ (distances.at(i) + distances.at(i + 1)));
	}
}

void TrimmingCurve::getCubicCurve(const std::vector<QVector4D>& points)
{
	int pointsCount = points.size();
	if (pointsCount < 1)
	{
		return;
	}
	int cubic = floor((pointsCount - 1) / 3);
	for (int i = 0; i < cubic; ++i)
	{
		std::unique_ptr<CurveCubic> curveCubic = std::make_unique<CurveCubic>(CurveCubic(800, 600, points.at(3 * i),
			points.at(3 * i + 1), points.at(3 * i + 2), points.at(3 * i + 3)));
		curveCubic->generateCurve(m_vertices);
	}
}

void TrimmingCurve::createVertices()
{
}

void TrimmingCurve::generateIndices()
{
	m_indices.clear();
	m_indices.reserve(m_vertices.size() + 1);
	for (int i = 0; i < m_vertices.size(); ++i)
	{
		m_indices.push_back(i);
	}
}

float3 TrimmingCurve::swapColors(int i) const
{
	float3 c;
	if (i%2)
		c = float3(0, 255, 0);
	else
		c = float3(255, 0, 0);
	return c;
}
