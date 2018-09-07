#pragma once
#include "curve.h"

class CurveCubic : public Curve
{
public:
	CurveCubic(float width, float height, const QVector4D &p1, const QVector4D &p2, const QVector4D &p3, const QVector4D &p4);

	void generateCurve(std::vector<QVector4D> &vec) override;
	static void generateCurve(std::vector<int> &ind, std::vector<QVector4D> &vec, float width, float height, 
		const QVector4D &p1, const QVector4D &p2, const QVector4D &p3, const QVector4D &p4);

private:
	const QVector4D &m_p1, &m_p2, &m_p3, &m_p4;
	float m_width, m_height;

	QVector4D deCasteljau(float t) override;
	float getLength() const override;
	static QVector4D deCasteljau(float t, const QVector4D &p1, const QVector4D &p2, const QVector4D &p3, const QVector4D &p4);
	static float getLength(const QVector4D &p1, const QVector4D &p2, float width, float height);
};