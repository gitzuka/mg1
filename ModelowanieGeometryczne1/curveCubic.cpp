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

void CurveCubic::generateCurve(std::vector<int> &ind, std::vector<QVector4D>& vec, float width, float height, 
	const QVector4D& p1, const QVector4D& p2, const QVector4D& p3, const QVector4D& p4)
{
	int length = floor(getLength(p1, p4, width, height));
	float step = 1.0 / length;
	int prevIndex = vec.size();
	for (int i = 0; i < length; ++i)
	{
		vec.push_back(deCasteljau(step * i, p1, p2, p3, p4));
		ind.push_back(i + prevIndex);
		ind.push_back(i + 1 + prevIndex);
	}
	vec.push_back(deCasteljau(step * length, p1, p2, p3, p4));

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

QVector4D CurveCubic::deCasteljau(float t, const QVector4D& p1, const QVector4D& p2, const QVector4D& p3, const QVector4D& p4)
{
	return QVector4D(QVector3D(pow(1 - t, 3) * p1 +
		3 * pow(1 - t, 2) * t * p2 +
		3 * (1 - t) * pow(t, 2) * p3 +
		pow(t, 3) * p4), 1.0f);
}

float CurveCubic::getLength(const QVector4D& p1, const QVector4D& p2, float width, float height)
{
	float x = width * (p2.x() - p1.x());
	float y = height * (p2.y() - p1.y());
	float z = (height + width) / 2.0f * (p2.z() - p1.z());
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}
