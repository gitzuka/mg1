#pragma once
#include <QtOpenGL>

class Curve
{
public:
	virtual ~Curve() {}

	virtual void generateCurve(std::vector<QVector4D> &vec) = 0;

protected:
	virtual QVector4D deCasteljau(float t) = 0;
	virtual float getLength() const = 0;
};

//public:
//	virtual ~Curve() {}
//
//	void drawCurveCubic(const Point3D &p1, const Point3D &p2, const Point3D &p3, const Point3D &p4, float width, float height) const;
//	void drawCurveQuadratic(const Point3D &p1, const Point3D &p2, const Point3D &p3, float width, float height) const;
//
//	virtual QVector4D deCasteljau() const = 0;
//
//
//private:
//	QVector4D deCasteljauCubic(float t, const QVector4D &p1, const QVector4D &p2, const QVector4D &p3, const QVector4D &p4) const;
//	QVector4D deCasteljauQuadratic(float t, const  QVector4D &p1, const QVector4D &p2, const QVector4D &p3) const;