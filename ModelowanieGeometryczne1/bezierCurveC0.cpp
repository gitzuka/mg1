#include "bezierCurveC0.h"
#include <QtGui>
#include "camera.h"
#include "curveQuadratic.h"

BezierCurveC0::BezierCurveC0(ObjectType type, QString name) :
	DrawableObject(type, name), m_uiBCC0(*this)
{
}

BezierCurveC0::~BezierCurveC0()
{
	m_uiBCC0.deleteCurve();
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
		if (vec.at(*it).z() <= CAM_NEAR || vec.at(*(it + 1)).z() <= CAM_NEAR
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
		m_controlPoints.at(i)->setCenter(matrix);
		//m_controlPoints.at(i)->setModelMatrix(m_modelMatrix);
		//m_controlPoints.at(i)->setCenter(m_controlPoints.at(i)->getCenter());
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
		m_curveCubic = std::make_unique<CurveCubic>(CurveCubic(m_width, m_height, m_controlPoints.at(3 * i)->getPosition(), m_controlPoints.at(3 * i + 1)->getPosition(),
			m_controlPoints.at(3 * i + 2)->getPosition(), m_controlPoints.at(3 * i + 3)->getPosition()));
		m_curveCubic->generateCurve(m_vertices);
	}
	switch (points % 3)
	{
	case 0:
		m_curveQuadratic = std::make_unique<CurveQuadratic>(CurveQuadratic(m_width, m_height, m_controlPoints.at(3 * cubic)->getPosition(), m_controlPoints.at(3 * cubic + 1)->getPosition(),
			m_controlPoints.at(3 * cubic + 2)->getPosition()));
		m_curveQuadratic->generateCurve(m_vertices);
		break;
	case 1: //only cubic curves
		break;
	case 2:
		m_vertices.push_back(m_controlPoints.at(3 * cubic)->getPosition());
		m_vertices.push_back(m_controlPoints.at(3 * cubic + 1)->getPosition());
		break;
	}
	m_curveCubic = nullptr;
	m_curveQuadratic = nullptr;
}

void BezierCurveC0::generateIndices()
{
	m_indices.clear();
	for (int i = 0; i < m_vertices.size(); ++i)
	{
		m_indices.push_back(i);
	}
}

void BezierCurveC0::addControlPoint(const std::shared_ptr<DrawableObject> &point)
{
	m_controlPoints.push_back(std::static_pointer_cast<Point3D>(point));
	//m_uiBCC0.addPoint(point->getId());
	m_uiBCC0.getPointsIds(this->getId());
	createVertices();
	generateIndices();
}

void BezierCurveC0::removeControlPoint(const std::shared_ptr<DrawableObject> &point)
{
	for (int i = 0; i < m_controlPoints.count(); ++i)
	{
		if (point->getId() == m_controlPoints.at(i)->getId())
		{
			m_controlPoints.removeAt(i);
			//m_uiBCC0.removePoint(point->getId());
			m_uiBCC0.getPointsIds(this->getId());
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

void BezierCurveC0::connectToUI(ComboBoxBezierCurveC0 *comboBox, ListWidgetObjects *listWidget, Scene *scene, ListWidgetParameters *listWidgetParams) const
{
	m_uiBCC0.connectToUi(comboBox, listWidget, scene, listWidgetParams);
}
