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
	int i = 0;
	for (std::vector<int>::const_iterator it = m_indices.begin(); it != m_indices.end() - 1; ++it)
	{
		if (*it == -1 || *(it + 1) == -1
			|| vec.at(*it).z() <= CAM_NEAR || vec.at(*(it + 1)).z() <= CAM_NEAR
			|| vec.at(*it).z() > 1 || vec.at(*(it + 1)).z() > 1)
		{
			continue;
		}
		//drawLine(vec.at(*it), vec.at(*(it + 1)), color);
		drawLine(vec.at(*it), vec.at(*(it + 1)), swapColors(i));
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
