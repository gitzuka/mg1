#pragma once
#include "drawableObject.h"
#include "point3d.h"
#include "bezierPatch.h"
#include "intersectableObject.h"

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
	float m_sizeX;
	float m_sizeY;
};

class BezierSurface : public DrawableObject, public IntersectableObject
{
public:
	virtual ~BezierSurface();

	friend class UiBezierSurface;

	virtual QVector3D calculateDerivative(double t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const = 0;
	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	QVector2D approximatePointOnSurface(const QVector3D &pos) const override;
	QVector2D approximatePointOnSurface(const QVector3D &worldPosition, const QVector2D &uvRef, float distance) const override;
	QVector3D getUDerivative(double u, double v) const override;
	QVector3D getVDerivative(double u, double v) const override;
	QVector3D getPointByUV(double u, double v) const override;
	BezierPatch getPatchByUV(double u, double v) const;
	QVector2D getPatchUV(const BezierPatch& patch, double u, double v) const;
	QVector4D getRangeUV(double u, double v) const override;
	QVector4D getRangeUV() const override;

	void trimSurface(const std::vector<std::vector<bool>> &draw, bool interior);
	BezierSurfaceData::SurfaceType getSurfaceType() const;
	const BezierSurfaceData& getSurfaceData() const;
	const std::vector<BezierPatch>& getPatches() const;
	const std::vector<std::shared_ptr<Point3D>>& getPoints() const;
	std::vector<int> getPointsIds() const;
	void pointMoved(int id);
	void setPosition(QVector3D pos) override;
	void rotate(QVector3D eulerAngles) override;
	virtual void initializeFromPoints(const std::vector<int> &ids, const std::vector<std::shared_ptr<Point3D>> &points) = 0;

protected:
	BezierSurface(ObjectType type, const QString &name, const BezierSurfaceData &parameters);

	int m_width;
	int m_height;
	bool m_showBezierGrid;
	bool m_showControlGrid;
	int m_curveFactor;
	BezierSurfaceData m_parameters;
	std::vector<BezierPatch> m_patches;
	std::vector<std::shared_ptr<Point3D>> m_points;

	virtual void planeSurfacePatches() = 0;
	virtual void cylinderSurfacePatches() = 0;
	virtual void planeSurfacePatchesPoints() = 0;
	virtual void cylinderSurfacePatchesPoints() = 0;
	virtual QVector3D calculateSurfacePoint(float t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const = 0;
	QVector3D getPointOnSurface(const BezierPatch& patch, double u, double v) const;
	void generateControlPointsIndices();
	void generateIndices() override;
	void createVertices() override;
	void clearSurface();

private:
	void initialize(BezierSurfaceData parameters);
};
