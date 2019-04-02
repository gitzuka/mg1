#include "axes.h"
#include "utils.h"

Axes::Axes(ObjectType type) : DrawableObject(DrawableObject::ObjectType::axes, "Axes"), m_x(false), m_y(false), m_z(false), m_axeVertNum(25)
{
	Axes::createVertices();
	Axes::generateIndices();
}

void Axes::draw(std::vector<QVector4D>& vec) const
{
	draw(vec, m_color);
}

void Axes::draw(std::vector<QVector4D>& vec, float3 color) const
{
	if (m_x)
		drawX(vec);
	if (m_y)
		drawY(vec);
	if (m_z)
		drawZ(vec);
	/*if (m_x)
		drawLine(vec.at(0), vec.at(1), float3(1, 0, 0));
	if (m_y)
		drawLine(vec.at(2), vec.at(3), float3(0, 1, 0));
	if (m_z)
		drawLine(vec.at(4), vec.at(5), float3(0, 0, 1));*/
}

void Axes::setModelMatrix(const QMatrix4x4& matrix)
{
	m_modelMatrix = matrix;
}

void Axes::createVertices()
{
	float length = 10.0f;
	for (int i = 0; i < m_axeVertNum; ++i)
	{
		m_vertices.emplace_back(-length + (static_cast<float>(i) / m_axeVertNum) * length, 0.0, 0.0, 1);
	}
	for (int i = 0; i < m_axeVertNum; ++i)
	{
		m_vertices.emplace_back(static_cast<float>(i) / m_axeVertNum * length, 0.0, 0.0, 1);
	}

	for (int i = 0; i < m_axeVertNum; ++i)
	{
		m_vertices.emplace_back(0, -length + (static_cast<float>(i) / m_axeVertNum) * length, 0.0, 1);
	}
	for (int i = 0; i < m_axeVertNum; ++i)
	{
		m_vertices.emplace_back(0, static_cast<float>(i) / m_axeVertNum * length, 0.0, 1);
	}

	for (int i = 0; i < m_axeVertNum; ++i)
	{
		m_vertices.emplace_back(0, 0.0, -length + (static_cast<float>(i) / m_axeVertNum) * length, 1);
	}
	for (int i = 0; i < m_axeVertNum; ++i)
	{
		m_vertices.emplace_back(0, 0.0, static_cast<float>(i) / m_axeVertNum * length, 1);
	}
	/*
	m_vertices.push_back(QVector4D(10, 0.0, 0.0, 1));
	m_vertices.push_back(QVector4D(0, -10, 0.0, 1));
	m_vertices.push_back(QVector4D(0, 10, 0.0, 1));
	m_vertices.push_back(QVector4D(0, 0, -10, 1));
	m_vertices.push_back(QVector4D(0, 0, 10, 1));*/
}

void Axes::generateIndices()
{
	for (int j = 0; j < 3; ++j)
	{
		int prev = j * 2 * m_axeVertNum;
		for (int i = 0; i < 2 * m_axeVertNum; ++i)
		{
			m_indices.push_back(i + prev);
		}
		m_indices.push_back(-1);
	}
}

void Axes::drawLines(const std::vector<QVector4D>& vec, int index, float3 color) const
{
	if (m_indices[index] == -1 || m_indices[index + 1] == -1
		|| vec[m_indices[index]].z() <= CAM_NEAR || vec[m_indices[index + 1]].z() <= CAM_NEAR
		|| vec[m_indices[index]].z() > 1 || vec[m_indices[index + 1]].z() > 1)
	{
		return;
	}
	drawLine(vec[m_indices[index]], vec[m_indices[index + 1]], color);
}

void Axes::drawX(const std::vector<QVector4D>& vec) const
{
	for (int i = 0; i < 2 * m_axeVertNum; ++i)
	{
		drawLines(vec, i, float3(1, 0, 0));
	}
}

void Axes::drawY(const std::vector<QVector4D>& vec) const
{
	for (int i = 2 * m_axeVertNum; i < 4 * m_axeVertNum + 1; ++i)
	{
		drawLines(vec, i, float3(0, 1, 0));
	}
}

void Axes::drawZ(const std::vector<QVector4D>& vec) const
{
	for (int i = 4 * m_axeVertNum + 1; i < m_vertices.size(); ++i)
	{
		drawLines(vec, i, float3(0, 0, 1));
	}
}
