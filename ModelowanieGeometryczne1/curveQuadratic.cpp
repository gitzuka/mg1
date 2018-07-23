#include "curveQuadratic.h"

CurveQuadratic::CurveQuadratic(float width, float height, const QVector4D &p1, const QVector4D &p2, const QVector4D &p3) :
	m_p1(p1), m_p2(p2), m_p3(p3), m_width(width), m_height(height)
{
}

void CurveQuadratic::generateCurve(std::vector<QVector4D> &vec)
{
	int length = floor(getLength());
	float step = 1.0f / length;

	for (int i = 0; i <= length; ++i)
	{
		vec.push_back(deCasteljau(step * i));
	}
}

QVector4D CurveQuadratic::deCasteljau(float t)
{
	return QVector4D(QVector3D(m_p1 * pow(1 - t, 2) + 
		2 * m_p2 * t * (1 - t) +
		m_p3 * pow(t, 2)), 1.0f);
}

float CurveQuadratic::getLength() const
{
	float x = m_width * (m_p3.x() - m_p1.x());
	float y = m_height * (m_p3.y() - m_p1.y());
	return sqrt(pow(x, 2) + pow(y, 2));
	//return sqrt(pow(m_p3.x() - m_p1.x(), 2) + pow(m_p3.y() - m_p1.y(), 2));
}
