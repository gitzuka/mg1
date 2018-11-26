#pragma once

class BezierPatch;
class QVector2D;
class QVector3D;
class QVector4D;

class IntersectableObject
{
public:
	virtual ~IntersectableObject()
	{
	}
	virtual QVector3D getPointByUV(double u, double v) const = 0;
	virtual QVector2D approximatePointOnSurface(const QVector3D &worldPosition) const = 0;
	virtual QVector2D approximatePointOnSurface(const QVector3D &worldPosition, const QVector2D &uvRef, float distance) const = 0;
	virtual QVector3D getUDerivative(double u, double v) const = 0;
	virtual QVector3D getVDerivative(double u, double v) const = 0;
	virtual QVector4D getRangeUV(double u, double v) const = 0;
	virtual QVector4D getRangeUV() const = 0;
	virtual bool isUWrapped() const;
	virtual bool isVWrapped() const;

protected:
	IntersectableObject(bool uWrapped = false, bool vWrapped = false);
	bool m_uWrapped;
	bool m_vWrapped;
};
