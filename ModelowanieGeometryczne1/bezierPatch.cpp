#include "bezierPatch.h"
#include "point3d.h"

BezierPatch::BezierPatch(int u, int v) : m_u(u), m_v(v)
{
}

int BezierPatch::getU() const
{
	return m_u;
}

int BezierPatch::getV() const
{
	return m_v;
}

const std::vector<std::shared_ptr<Point3D>>& BezierPatch::getPoints() const
{
	return m_points;
}

void BezierPatch::addPoint(const std::shared_ptr<DrawableObject>& point)
{
	if (point->m_type != DrawableObject::ObjectType::point3D)
		return;
	m_points.push_back(std::static_pointer_cast<Point3D>(point));
}
