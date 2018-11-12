#include "axes.h"

Axes::Axes(ObjectType type) : DrawableObject(DrawableObject::ObjectType::axes, "Axes"), m_x(false), m_y(false), m_z(false)
{
	Axes::createVertices();
}

void Axes::draw(std::vector<QVector4D>& vec) const
{
	draw(vec, m_color);
}

void Axes::draw(std::vector<QVector4D>& vec, float3 color) const
{
	if (m_x)
		drawLine(vec.at(0), vec.at(1), float3(1, 0, 0));
	if (m_y)
		drawLine(vec.at(2), vec.at(3), float3(0, 1, 0));
	if (m_z)
		drawLine(vec.at(4), vec.at(5), float3(0, 0, 1));

	/*for (std::vector<int>::const_iterator it = m_indices.begin(); it != m_indices.end(); ++it)
	{
		if (*it == -1 || *(it + 1) == -1
			|| vec.at(*it).z() <= CAM_NEAR || vec.at(*(it + 1)).z() <= CAM_NEAR
			|| vec.at(*it).z() > 1 || vec.at(*(it + 1)).z() > 1)
		{
			continue;
		}
		drawLine(vec.at(*it), vec.at(*(it + 1)), color);
	}*/
}

void Axes::setModelMatrix(const QMatrix4x4& matrix)
{
	m_modelMatrix = matrix;
}

void Axes::createVertices()
{
	m_vertices.push_back(QVector4D(-10, 0.0, 0.0, 1));
	m_vertices.push_back(QVector4D(10, 0.0, 0.0, 1));
	m_vertices.push_back(QVector4D(0, -10, 0.0, 1));
	m_vertices.push_back(QVector4D(0, 10, 0.0, 1));
	m_vertices.push_back(QVector4D(0, 0, -10, 1));
	m_vertices.push_back(QVector4D(0, 0, 10, 1));
}

void Axes::generateIndices()
{
}
