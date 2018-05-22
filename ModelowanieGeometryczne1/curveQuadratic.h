#pragma once
#include <memory>
#include "point3d.h"
#include "curve.h"

class CurveQuadratic : public Curve
{
public:
	CurveQuadratic(float width, float height, const QVector4D &p1, const QVector4D &p2, const QVector4D &p3);

	//std::vector<QVector4D> generateCurve() override;
	void generateCurve(std::vector<QVector4D> &vec) override;

private:
	const QVector4D &m_p1, &m_p2, &m_p3;
	float m_width, m_height;

	QVector4D deCasteljau(float t) override;
	float getLength() const override;
};

