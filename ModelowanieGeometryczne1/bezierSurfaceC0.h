#pragma once
#include "BezierSurface.h"
#include "drawableObject.h"

class BezierPatch;

class BezierSurfaceC0 : public BezierSurface
{
public:
	BezierSurfaceC0(ObjectType type, const QString &name, const BezierSurfaceData &parameters);
	~BezierSurfaceC0();

	void pointMoved(int id) override;

private:
	void createVertices() override;
	void planeSurfacePatches() override;
	void cylinderSurfacePatches() override;
	void planeSurfacePatchesPoints() override;
	void cylinderSurfacePatchesPoints() override;
	QVector3D calculateSurfacePoint(float t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const override;
};
