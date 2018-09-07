#pragma once

class BezierPatch;
class QVector2D;
class QVector3D;

class IntersectableObject
{
public:
	virtual ~IntersectableObject() { }
	//virtual BezierPatch getPatchByUV(double u, double v) const = 0;
	//virtual QVector2D getPatchUV(BezierPatch patch, double u, double v) const = 0;
	//virtual QVector3D calculateDerivative(double t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const = 0;
	virtual QVector3D getPointByUV(double u, double v) const = 0;
	virtual QVector2D approximatePointOnSurface(QVector3D worldPosition) const = 0;
	virtual QVector3D getUDerivative(double u, double v) const = 0;
	virtual QVector3D getVDerivative(double u, double v) const = 0;
	virtual QVector4D getRangeUV(double u, double v) const = 0;
	virtual bool isWrapped() const = 0;
};
