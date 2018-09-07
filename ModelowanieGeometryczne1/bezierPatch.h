#pragma once
#include <vector>
#include "point3d.h"

class BezierPatch
{
public:
	BezierPatch(int u, int v);

	int getU() const;
	int getV() const;
	const std::vector<std::shared_ptr<Point3D>>& getPoints() const;
	void addPoint(const std::shared_ptr<DrawableObject> &point);

private:
	int m_u;
	int m_v;
	std::vector<std::shared_ptr<Point3D>> m_points;
};
