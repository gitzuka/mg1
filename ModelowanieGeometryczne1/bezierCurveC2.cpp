#include "bezierCurveC2.h"
#include "utils.h"
#include "3dmath.h"

BezierCurveC2::BezierCurveC2(ObjectType type, QString name)
	: DrawableObject(type, name), m_showPolyline(false), m_bSplineBasis(false)
{
}

BezierCurveC2::~BezierCurveC2()
{
}

void BezierCurveC2::draw(std::vector<QVector4D>& vec) const
{
	draw(vec, m_color);
}

void BezierCurveC2::draw(std::vector<QVector4D>& vec, float3 color) const
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

void BezierCurveC2::setModelMatrix(const QMatrix4x4& matrix)
{
	m_modelMatrix = matrix;
}

QVector4D BezierCurveC2::getPosition() const
{
	return QVector4D(m_modelMatrix.row(0).w(), m_modelMatrix.row(1).w(), m_modelMatrix.row(2).w(), 1);
}

QList<int> BezierCurveC2::getDeBoorPointIds() const
{
	QList<int> pointIds;
	for (int i = 0; i < m_deBoorPoints.count(); ++i)
	{
		pointIds.append(m_deBoorPoints.at(i)->getId());
	}
	return pointIds;
}

const QList<std::shared_ptr<Point3D>>& BezierCurveC2::getDeBoorPoints() const
{
	return m_deBoorPoints;
}

std::vector<std::shared_ptr<Point3D>> BezierCurveC2::getControlPoints() const
{
	return m_controlPoints;
}

void BezierCurveC2::pointMoved(int id)
{
	for (int i = 0; i < m_controlPoints.size(); ++i)
	{
		if (m_controlPoints.at(i)->getId() == id)
		{
			translateDeBoors(m_controlPoints.at(i), i, getDeBoorToTranslate(m_controlPoints.at(i)));
		}
	}
}

const std::vector<int>& BezierCurveC2::getPrevControlPointsIds() const
{
	return m_prevControlPointsIds;
}

void BezierCurveC2::createVertices()
{
	m_vertices.clear();
	int points = m_controlPoints.size();
	if (points < 4)
	{
		return;
	}
	int cubic = floor((points - 1) / 3);
	for (int i = 0; i < cubic; ++i)
	{
		std::unique_ptr<CurveCubic> curveCubic = std::make_unique<CurveCubic>(CurveCubic(m_width, m_height, m_controlPoints.at(3 * i)->getPosition(),
			m_controlPoints.at(3 * i + 1)->getPosition(), m_controlPoints.at(3 * i + 2)->getPosition(), m_controlPoints.at(3 * i + 3)->getPosition()));
		curveCubic->generateCurve(m_vertices);
	}
	if (m_showPolyline)
	{
		for (int i = 0; i < m_deBoorPoints.count(); ++i)
		{
			m_vertices.push_back(m_deBoorPoints.at(i)->getPosition());
		}
	}
	/*if (m_showPolyline)
	{
		if (m_bSplineBasis)
		{
			for (int i = 0; i < m_deBoorPoints.count(); ++i)
			{
				m_vertices.push_back(m_deBoorPoints.at(i)->getPosition());
			}
		}
		else
		{
			for (int i = 0; i < m_controlPoints.size(); ++i)
			{
				m_vertices.push_back(m_controlPoints.at(i)->getPosition());
			}
		}
	}*/
}

void BezierCurveC2::generateIndices()
{
	m_indices.clear();
	m_indices.reserve(m_vertices.size() + 1);
	int verticesSize = m_vertices.size();
	m_showPolyline ? verticesSize -= m_deBoorPoints.count() : verticesSize;
	for (int i = 0; i < verticesSize; ++i)
	{
		m_indices.push_back(i);
	}
	if (m_showPolyline)
	{
		m_indices.push_back(-1);
		for (int i = 0; i < m_deBoorPoints.count(); ++i)
		{
			m_indices.push_back(verticesSize + i);
		}
	}
}

void BezierCurveC2::generateControlPoints()
{
	int deBoorCount = m_deBoorPoints.count();
	if (deBoorCount < 4)
		return;
	assignPrevCPIds();
	m_controlPoints.clear();
	std::vector<QVector4D> betweenDeBoorPoints;
	betweenDeBoorPoints.reserve(2 * deBoorCount - 2);
	for (int i = 0; i < deBoorCount - 1; ++i)
	{
		betweenDeBoorPoints.push_back(math3d::getPointBetweenPoints(m_deBoorPoints.at(i)->getPosition(), m_deBoorPoints.at(i + 1)->getPosition(), 1.f / 3.f));
		betweenDeBoorPoints.push_back(math3d::getPointBetweenPoints(m_deBoorPoints.at(i)->getPosition(), m_deBoorPoints.at(i + 1)->getPosition(), 2.f / 3.f));
	}
	std::vector<QVector4D> skewPoints;
	skewPoints.reserve(deBoorCount - 2);
	for (int i = 0; i < deBoorCount - 2; ++i)
	{
		skewPoints.push_back(math3d::getPointBetweenPoints(betweenDeBoorPoints.at(2 * i + 1), betweenDeBoorPoints.at(2 * i + 2), 0.5f));
	}
	m_controlPoints.reserve((deBoorCount - 4) * 2 + deBoorCount);
	m_controlPoints.push_back(std::make_shared<Point3D>(Point3D(ObjectType::point3D, "Point3D", skewPoints.at(0), m_bSplineBasis)));
	//for (int i = 0; i < (m_deBoorPoints.count() / 4 + m_deBoorPoints.count() % 4); ++i)
	for (int i = 0; i < ((deBoorCount - 4) * 2 + deBoorCount - 1) / 3; ++i)
	{
		m_controlPoints.push_back(std::make_shared<Point3D>(Point3D(ObjectType::point3D, "Point3D", betweenDeBoorPoints.at(2 * i + 2), m_bSplineBasis)));
		m_controlPoints.push_back(std::make_shared<Point3D>(Point3D(ObjectType::point3D, "Point3D", betweenDeBoorPoints.at(2 * i + 3), m_bSplineBasis)));
		m_controlPoints.push_back(std::make_shared<Point3D>(Point3D(ObjectType::point3D, "Point3D", skewPoints.at(i + 1), m_bSplineBasis)));
	}
}

void BezierCurveC2::assignPrevCPIds()
{
	m_prevControlPointsIds.clear();
	m_prevControlPointsIds.reserve(m_controlPoints.size());
	for (std::vector<std::shared_ptr<Point3D>>::const_iterator it = m_controlPoints.begin(); it != m_controlPoints.end(); ++it)
	{
		m_prevControlPointsIds.push_back(it->get()->getId());
	}
}

bool BezierCurveC2::addDeBoorPoint(const std::shared_ptr<DrawableObject> &point)
{
	if (point->m_type != DrawableObject::ObjectType::point3D)
		return false;
	for (int i = 0; i < m_deBoorPoints.count(); ++i)
	{
		if (m_deBoorPoints.at(i)->getId() == point->getId())
			return false;
	}
	m_deBoorPoints.push_back(std::static_pointer_cast<Point3D>(point));
	m_deBoorPoints.last()->m_enabled = !m_bSplineBasis;
	generateControlPoints();
	createVertices();
	generateIndices();
	return true;
}

bool BezierCurveC2::assignDeBoorPoints(const std::vector<std::shared_ptr<DrawableObject>> &points)
{
	m_deBoorPoints.clear();
	m_deBoorPoints.reserve(points.size());
	for (int i = 0; i < points.size(); ++i)
	{
		if (points.at(i)->m_type != DrawableObject::ObjectType::point3D)
		{
			m_deBoorPoints.clear();
			return false;
		}
		m_deBoorPoints.push_back(std::static_pointer_cast<Point3D>(points.at(i)));
		m_deBoorPoints.at(i)->m_enabled = !m_bSplineBasis;
	}
	generateControlPoints();
	createVertices();
	generateIndices();
	return true;
}

void BezierCurveC2::removeDeBoorPoint(const std::shared_ptr<DrawableObject> &point)
{
	for (int i = 0; i < m_deBoorPoints.count(); ++i)
	{
		if (point->getId() == m_deBoorPoints.at(i)->getId())
		{
			m_deBoorPoints.removeAt(i);
		}
	}
	generateControlPoints();
	createVertices();
	generateIndices();
}

void BezierCurveC2::removeDeBoorPoint(int pointId)
{
	for (int i = 0; i < m_deBoorPoints.count(); ++i)
	{
		if (pointId == m_deBoorPoints.at(i)->getId())
		{
			m_deBoorPoints.removeAt(i);
		}
	}
	generateControlPoints();
	createVertices();
	generateIndices();
}

void BezierCurveC2::translateDeBoors(const std::shared_ptr<DrawableObject> &point, int controlPointIndex, int deBoorIndex)
{
	switch (controlPointIndex % 3)
	{
	case 0:
	{
		m_deBoorPoints.at(deBoorIndex)->setPosition(3.f / 2.f * point->getPosition() - 1.f / 4.f * m_deBoorPoints.at(deBoorIndex - 1)->getPosition() - 1.f / 4.f * m_deBoorPoints.at(deBoorIndex + 1)->getPosition());
		break;
	}
	case 1:
	{
		m_deBoorPoints.at(deBoorIndex)->setPosition(3.f / 2.f * point->getPosition() - 1.f / 2.f * m_deBoorPoints.at(deBoorIndex + 1)->getPosition());
		break;
	}
	case 2:
	{
		m_deBoorPoints.at(deBoorIndex)->setPosition(3.f / 2.f * point->getPosition() - 1.f / 2.f * m_deBoorPoints.at(deBoorIndex - 1)->getPosition());
		break;
	}
	}
}

void BezierCurveC2::translateCotrolPoints()
{
	int deBoorCount = m_deBoorPoints.count();
	if (deBoorCount < 4)
		return;
	std::vector<QVector4D> betweenDeBoorPoints;
	betweenDeBoorPoints.reserve(2 * deBoorCount - 2);
	for (int i = 0; i < deBoorCount - 1; ++i)
	{
		betweenDeBoorPoints.push_back(math3d::getPointBetweenPoints(m_deBoorPoints.at(i)->getPosition(), m_deBoorPoints.at(i + 1)->getPosition(), 1.f / 3.f));
		betweenDeBoorPoints.push_back(math3d::getPointBetweenPoints(m_deBoorPoints.at(i)->getPosition(), m_deBoorPoints.at(i + 1)->getPosition(), 2.f / 3.f));
	}
	std::vector<QVector4D> skewPoints;
	skewPoints.reserve(deBoorCount - 2);
	for (int i = 0; i < deBoorCount - 2; ++i)
	{
		skewPoints.push_back(math3d::getPointBetweenPoints(betweenDeBoorPoints.at(2 * i + 1), betweenDeBoorPoints.at(2 * i + 2), 0.5f));
	}
	m_controlPoints.at(0)->setPosition(skewPoints.at(0));
	for (int i = 0; i < (m_deBoorPoints.count() / 4 + m_deBoorPoints.count() % 4); ++i)
	{
		m_controlPoints.at(3 * i + 1)->setPosition(betweenDeBoorPoints.at(2 * i + 2));
		m_controlPoints.at(3 * i + 2)->setPosition(betweenDeBoorPoints.at(2 * i + 3));
		m_controlPoints.at(3 * i + 3)->setPosition(skewPoints.at(i + 1));
	}
}

int BezierCurveC2::getDeBoorToTranslate(const std::shared_ptr<DrawableObject> &point)
{
	if (m_controlPoints.at(0)->getId() == point->getId() || m_controlPoints.at(1)->getId() == point->getId())
	{
		return 1;
	}
	int k = 0;
	for (int i = 2; i < m_controlPoints.size(); ++i)
	{
		if (m_controlPoints.at(i)->getId() == point->getId())
		{
			return floor(k / 3) + 2;
		}
		k++;
	}
	return -1;
}

void BezierCurveC2::changeBasis(bool deBoor)
{
	m_bSplineBasis = deBoor;
	for (int i = 0; i < m_controlPoints.size(); ++i)
	{
		m_controlPoints.at(i)->m_enabled = m_bSplineBasis;
	}
	for (int i = 0; i < m_deBoorPoints.count(); ++i)
	{
		m_deBoorPoints.at(i)->m_enabled = !m_bSplineBasis;
	}
}
