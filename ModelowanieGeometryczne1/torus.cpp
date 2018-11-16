#include "torus.h"
#include <math.h>
#include <qmath.h>
#include "utils.h"

Torus::Torus(ObjectType type, QString name) :
	DrawableObject(type, name, true, true),
	m_smallRadius(0.10), m_bigRadius(0.30), m_minorSegments(30), m_majorSegments(30), m_isWrapped(true)
{
	Torus::createVertices();
	Torus::generateIndices();
	m_intersectable = true;
}

Torus::Torus(float r, float R, int minorSegments, int majorSegments,
	ObjectType type, QString name) :
	DrawableObject(type, name, true, true),
	m_smallRadius(r), m_bigRadius(R), m_minorSegments(minorSegments), m_majorSegments(majorSegments), m_isWrapped(true)
{
	Torus::createVertices();
	Torus::generateIndices();
	m_intersectable = true;
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

float Torus::getSmallRadius() const
{
	return m_smallRadius;
}

float Torus::getBigRadius() const
{
	return m_bigRadius;
}

float Torus::getMinorSegments() const
{
	return m_minorSegments;
}

float Torus::getMajorSegments() const
{
	return m_majorSegments;
}

void Torus::createVertices()
{
	m_vertices.clear();
	double phiStep = 2 * M_PI / m_majorSegments;
	double thetaStep = 2 * M_PI / m_minorSegments;
	m_vertices.reserve(m_majorSegments * m_minorSegments);
	for (int i = 0; i < m_majorSegments; ++i)
	{
		for (int j = 0; j < m_minorSegments; ++j)
		{
			double u = phiStep * i;
			double v = thetaStep * j;
			QVector4D vertex;
			vertex.setX(cos(v) * (m_smallRadius * cos(u) + m_bigRadius));
			vertex.setY(sin(v) * (m_smallRadius * cos(u) + m_bigRadius));
			vertex.setZ(m_smallRadius * sin(u));
			vertex.setW(1);
			m_vertices.push_back(vertex);
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

QVector2D Torus::approximatePointOnSurface(const QVector3D &pos) const
{
	float minDist = std::numeric_limits<float>::infinity();
	QVector2D uv;

	double phiStep = 2 * M_PI / m_majorSegments;
	double thetaStep = 2 * M_PI / m_minorSegments;
	for (int i = 0; i < m_majorSegments; ++i)
	{
		for (int j = 0; j < m_minorSegments; ++j)
		{
			double u = phiStep * i;
			double v = thetaStep * j;
			QVector4D surfacePoint = getPointByUV(u, v);
			double dist = (pos - surfacePoint).length();
			if (dist < minDist)
			{
				uv = QVector2D(u, v);
				minDist = dist;
			}
		}
	}
	return uv;
}

QVector3D Torus::getUDerivative(double u, double v) const
{
	QVector3D vertex;
	vertex.setX(-m_smallRadius * cos(v) * sin(u));
	vertex.setY(-m_smallRadius * sin(v) * sin(u));
	vertex.setZ(m_smallRadius * cos(u));
	return vertex + getPosition();
}

QVector3D Torus::getVDerivative(double u, double v) const
{
	QVector3D vertex;
	vertex.setX(-sin(v) * (m_smallRadius * cos(u) + m_bigRadius));
	vertex.setY(cos(v) * (m_smallRadius * cos(u) + m_bigRadius));
	vertex.setZ(0);
	return vertex + getPosition();
}

QVector3D Torus::getPointByUV(double u, double v) const
{
	QVector3D vertex;
	vertex.setX(cos(v) * (m_bigRadius + m_smallRadius * cos(u)));
	vertex.setY(sin(v) * (m_bigRadius + m_smallRadius * cos(u)));
	vertex.setZ(m_smallRadius * sin(u));
	return vertex + getPosition();
}

QVector4D Torus::getRangeUV(double u, double v) const
{
	return QVector4D(0, 2 * M_PI, 0, 2 * M_PI);
}

bool Torus::isWrapped() const
{
	return m_isWrapped;
}
