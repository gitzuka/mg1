#include "curveCubic.h"

CurveCubic::CurveCubic(float width, float height, const QVector4D &p1, const QVector4D &p2, const QVector4D &p3, const QVector4D &p4)
	: m_p1(p1), m_p2(p2), m_p3(p3), m_p4(p4), m_width(width), m_height(height)
{
}

void CurveCubic::generateCurve(std::vector<QVector4D>& vec)
{
	int length = floor(getLength());
	float step = 1.0 / length;
	for (int i = 0; i <= length; ++i)
	{
		vec.push_back(deCasteljau(step * i));
	}
}

QVector4D CurveCubic::deCasteljau(float t)
{
	return QVector4D(QVector3D(pow(1 - t, 3) * m_p1 +
		3 * pow(1 - t, 2) * t * m_p2 +
		3 * (1 - t) * pow(t, 2) * m_p3 +
		pow(t, 3) * m_p4), 1.0f);
}

float CurveCubic::getLength() const
{
	float x = m_width * (m_p4.x() - m_p1.x());
	float y = m_height * (m_p4.y() - m_p1.y());
	return sqrt(pow(x, 2) + pow(y, 2));
}
