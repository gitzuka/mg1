#include "bezierCurveC0.h"
#include <QtGui>
#include "curveQuadratic.h"
#include "utils.h"

BezierCurveC0::BezierCurveC0(ObjectType type, QString name) :
	DrawableObject(type, name), m_showPolyline(false)
{
}

BezierCurveC0::~BezierCurveC0()
{
}

void BezierCurveC0::draw(std::vector<QVector4D>& vec) const
{
	draw(vec, m_color);
}

void BezierCurveC0::draw(std::vector<QVector4D>& vec, float3 color) const
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

void BezierCurveC0::setModelMatrix(const QMatrix4x4 &matrix)
{
	QVector3D vec = matrix.column(3).toVector3D();
	for (int i = 0; i < m_controlPoints.count(); ++i)
	{
		//QVector3D a = vec * matrix;
		//QVector3D vec2 = m_controlPoints.at(i)->getModelMatrix().column(3).toVector3D();
		//m_controlPoints.at(i)->setModelMatrix(m_controlPoints.at(i)->getModelMatrix() * matrix);
		//m_controlPoints.at(i)->setPosition(matrix);
		m_controlPoints.at(i)->setModelMatrix(matrix);
		//m_controlPoints.at(i)->setPosition(m_controlPoints.at(i)->getCenter());
	}
	m_modelMatrix = matrix;
}

QVector4D BezierCurveC0::getPosition() const
{
	return QVector4D(m_modelMatrix.row(0).w(), m_modelMatrix.row(1).w(), m_modelMatrix.row(2).w(), 1);
}

void BezierCurveC0::createVertices()
{
	m_vertices.clear();
	int points = m_controlPoints.count();
	if (points < 1)
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
	switch (points % 3)
	{
	case 0:
	{
		std::unique_ptr<CurveQuadratic> curveQuadratic = std::make_unique<CurveQuadratic>(CurveQuadratic(m_width, m_height, m_controlPoints.at(3 * cubic)->getPosition(),
			m_controlPoints.at(3 * cubic + 1)->getPosition(), m_controlPoints.at(3 * cubic + 2)->getPosition()));
		curveQuadratic->generateCurve(m_vertices);
		break;
	}
	case 1: //only cubic curves
		break;
	case 2:
		m_vertices.push_back(m_controlPoints.at(3 * cubic)->getPosition());
		m_vertices.push_back(m_controlPoints.at(3 * cubic + 1)->getPosition());
		break;
	}
	if (m_showPolyline)
	{
		for (int i = 0; i < m_controlPoints.count(); ++i)
		{
			m_vertices.push_back(m_controlPoints.at(i)->getPosition());
		}
	}
}

void BezierCurveC0::generateIndices()
{
	m_indices.clear();
	m_indices.reserve(m_vertices.size() + 1);
	int verticesSize = m_vertices.size();
	m_showPolyline ? verticesSize -= m_controlPoints.size() : verticesSize;
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

//TODO: ui
bool BezierCurveC0::addControlPoint(const std::shared_ptr<DrawableObject> &point)
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

bool BezierCurveC0::assignControlPoints(const std::vector<std::shared_ptr<DrawableObject>>& points)
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
	createVertices();
	generateIndices();
	return true;
}

void BezierCurveC0::removeControlPoint(const std::shared_ptr<DrawableObject> &point)
{
	for (int i = 0; i < m_controlPoints.count(); ++i)
	{
		if (point->getId() == m_controlPoints.at(i)->getId())
		{
			m_controlPoints.removeAt(i);
		}
	}
	createVertices();
	generateIndices();
}

void BezierCurveC0::removeControlPoint(int pointId)
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

QList<int> BezierCurveC0::getControlPointIds() const
{
	QList<int> pointIds;
	for (int i = 0; i < m_controlPoints.count(); ++i)
	{
		pointIds.append(m_controlPoints.at(i)->getId());
	}
	return pointIds;
}

const QList<std::shared_ptr<Point3D>>& BezierCurveC0::getControlPoints() const
{
	return m_controlPoints;
}
