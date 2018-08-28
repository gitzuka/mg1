#pragma once
#include "drawableObject.h"
#include "point3d.h"
#include "bezierPatch.h"

struct BezierSurfaceData
{
	enum class SurfaceType
	{
		plane, cylinder
	};

	SurfaceType m_surfaceType;
	int m_u;
	int m_v;
	int m_patchesX;
	int m_patchesY;
	float m_radius;
	float m_height;
};

class BezierSurface : public DrawableObject
{
public:
	virtual ~BezierSurface();

	friend class UiBezierSurface;

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	void setU(int u);
	void setV(int v);
	BezierSurfaceData::SurfaceType getSurfaceType() const;
	const BezierSurfaceData& getSurfaceData() const;
	const std::vector<BezierPatch>& getPatches() const;
	const std::vector<std::shared_ptr<Point3D>>& getPoints() const;
	std::vector<int> getPointsIds() const;
	virtual void pointMoved(int id) = 0;

protected:
	BezierSurface(ObjectType type, const QString &name, const BezierSurfaceData &parameters);

	int m_width;
	int m_height;
	BezierSurfaceData m_parameters;
	std::vector<BezierPatch> m_patches;
	std::vector<std::shared_ptr<Point3D>> m_points;

	virtual void planeSurfacePatches() = 0;
	virtual void cylinderSurfacePatches() = 0;
	virtual void planeSurfacePatchesPoints() = 0;
	virtual void cylinderSurfacePatchesPoints() = 0;
	virtual QVector3D calculateSurfacePoint(float t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const = 0;
	QVector3D getPointOnSurface(BezierPatch patch, float u, float v) const;

private:
	virtual void createVertices() = 0;
	void generateIndices() override;
	void initialize(BezierSurfaceData parameters);
	void generateControlPointsIndices();
};
