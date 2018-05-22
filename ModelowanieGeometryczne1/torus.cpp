#include "torus.h"
#include <math.h>
#include <qmath.h>
#include "utils.h"

Torus::Torus(ObjectType type, QString name) :
	DrawableObject(type, name),
	//m_smallRadius(0.10), m_bigRadius(0.40), m_minorSegments(30), m_majorSegments(30), m_uiTorus(*this)
	m_smallRadius(0.10), m_bigRadius(0.40), m_minorSegments(30), m_majorSegments(30)
{
	Torus::createVertices();
	Torus::generateIndices();
}

Torus::Torus(float r, float R, int minorSegments, int majorSegments,
	ObjectType type, QString name) :
	DrawableObject(type, name),
	//m_smallRadius(r), m_bigRadius(R), m_minorSegments(minorSegments), m_majorSegments(majorSegments), m_uiTorus(*this)
	m_smallRadius(r), m_bigRadius(R), m_minorSegments(minorSegments), m_majorSegments(majorSegments)
{
}

void Torus::setSmallRadius(float r)
{
	m_smallRadius = r;
	createVertices();
}

void Torus::setBigRadius(float R)
{
	m_bigRadius = R;
	createVertices();
}

void Torus::setMinorSegments(int minorSegments)
{
	m_minorSegments = minorSegments;
	createVertices();
}

void Torus::setMajorSegments(int majorSegments)
{
	m_majorSegments = majorSegments;
	createVertices();
}

void Torus::createVertices()
{
	m_vertices.clear();
	m_vertices.reserve(m_majorSegments*m_minorSegments);
	double phiStep = 2 * M_PI / m_majorSegments;
	double thetaStep = 2 * M_PI / m_minorSegments;
	for (double phi = 0.; phi < 2 * M_PI; phi += phiStep)
	{
		for (double theta = 0.; theta < 2 * M_PI; theta += thetaStep)
		{
			QVector4D vertex2;
			vertex2.setX(cos(theta + thetaStep) * (m_bigRadius + m_smallRadius * cos(phi + phiStep)));
			vertex2.setY(sin(theta + thetaStep) * (m_bigRadius + m_smallRadius * cos(phi + phiStep)));
			vertex2.setZ(m_smallRadius * sin(phi + phiStep));
			vertex2.setW(1);
			m_vertices.push_back(vertex2);
		}
	}
	generateIndices();
}

void Torus::generateIndices()
{
	m_indices.clear();
	for (int i = 0; i < m_majorSegments; ++i)
	{
		for (int j = i * m_minorSegments; j < (i + 1)*m_minorSegments; ++j)
		{
			m_indices.push_back(j);
		}
		m_indices.push_back(i*m_minorSegments);
		m_indices.push_back(-1);
	}
	for (int i = 0; i < m_minorSegments; ++i)
	{
		for (int j = i; j < (m_minorSegments)*m_majorSegments; j += m_minorSegments)
		{
			m_indices.push_back(j);
		}
		m_indices.push_back(i);
		m_indices.push_back(-1);
	}
}

void Torus::draw(std::vector<QVector4D>& vec) const
{
	draw(vec, m_color);
}

void Torus::draw(std::vector<QVector4D> &vec, float3 color) const
{
	for (std::vector<int>::const_iterator it = m_indices.begin(); it != m_indices.end(); ++it)
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

void Torus::setModelMatrix(const QMatrix4x4 &matrix)
{
	m_modelMatrix = matrix;
}

QVector4D Torus::getPosition() const
{
	return QVector4D(m_modelMatrix.row(0).w(), m_modelMatrix.row(1).w(), m_modelMatrix.row(2).w(), 1);
}

//void Torus::connectToUI(ComboBoxTorus *comboBox, ListWidgetMain *listWidget) const
//{
//	m_uiTorus.connectToUi(comboBox, listWidget);
//}
