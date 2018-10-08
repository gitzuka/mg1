#include "trimmingCurve.h"
#include "utils.h"

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

void TrimmingCurve::setModelMatrix(const QMatrix4x4& matrix)
{
	m_modelMatrix = matrix;
}

void TrimmingCurve::setVertices(std::vector<QVector4D>& vertices)
{
	m_vertices.swap(vertices);
	generateIndices();
}

void TrimmingCurve::createVertices()
{
}

void TrimmingCurve::generateIndices()
{
	m_indices.clear();
	m_indices.reserve(m_vertices.size() + 1);
	int verticesSize = m_vertices.size();
	for (int i = 0; i < verticesSize; ++i)
	{
		m_indices.push_back(i);
	}
}
