#pragma once
#include "BezierSurface.h"

class BezierSurfaceC2 : public BezierSurface
{
public:
	BezierSurfaceC2(ObjectType type, const QString &name, const BezierSurfaceData &parameters);
	~BezierSurfaceC2();

	void pointMoved(int id) override;

private:
	void createVertices() override;
	void planeSurfacePatches() override;
	void cylinderSurfacePatches() override;
	void planeSurfacePatchesPoints() override;
	void cylinderSurfacePatchesPoints() override;
	QVector3D calculateSurfacePoint(float t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const override;

};