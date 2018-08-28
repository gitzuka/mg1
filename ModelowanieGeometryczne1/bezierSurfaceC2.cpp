#include "bezierSurfaceC2.h"

BezierSurfaceC2::BezierSurfaceC2(ObjectType type, const QString &name, const BezierSurfaceData &parameters) : BezierSurface(type, name, parameters)
{
}

BezierSurfaceC2::~BezierSurfaceC2()
{
}

void BezierSurfaceC2::pointMoved(int id)
{
}

void BezierSurfaceC2::createVertices()
{
}

void BezierSurfaceC2::planeSurfacePatches()
{
}

void BezierSurfaceC2::cylinderSurfacePatches()
{
}

void BezierSurfaceC2::planeSurfacePatchesPoints()
{
}

void BezierSurfaceC2::cylinderSurfacePatchesPoints()
{
}

QVector3D BezierSurfaceC2::calculateSurfacePoint(float t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const
{
	return QVector3D();
}
