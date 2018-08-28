#include "bezierSurface.h"
#include "utils.h"

BezierSurface::BezierSurface(ObjectType type, const QString &name, const BezierSurfaceData &parameters) : DrawableObject(type, name),
m_width(800), m_height(600), m_parameters(parameters)
{
}

BezierSurface::~BezierSurface()
{
}

void BezierSurface::draw(std::vector<QVector4D>& vec) const
{
	draw(vec, m_color);
}

void BezierSurface::draw(std::vector<QVector4D>& vec, float3 color) const
{
	if (m_vertices.size() < 2 || m_indices.size() < 2)
	{
		return;
	}
	for (std::vector<int>::const_iterator it = m_indices.begin(); it != m_indices.end() - 1; ++it)
	{
		if (*it == -1 || *(it + 1) == -1
			|| vec.at(*it).z() <= CAM_NEAR || vec.at(*(it + 1)).z() <= CAM_NEAR
			|| vec.at(*it).z() > 1 || vec.at(*(it + 1)).z() > 1)
		{
			continue;
		}
		drawLine(vec.at(*it), vec.at(*(it + 1)), color);
	}
}

void BezierSurface::setModelMatrix(const QMatrix4x4 &matrix)
{
	m_modelMatrix = matrix;
}

void BezierSurface::setU(int u)
{
	m_parameters.m_u = u;
}

void BezierSurface::setV(int v)
{
	m_parameters.m_v = v;
}

BezierSurfaceData::SurfaceType BezierSurface::getSurfaceType() const
{
	return m_parameters.m_surfaceType;
}

const BezierSurfaceData& BezierSurface::getSurfaceData() const
{
	return m_parameters;
}

const std::vector<BezierPatch>& BezierSurface::getPatches() const
{
	return m_patches;
}

const std::vector<std::shared_ptr<Point3D>> &BezierSurface::getPoints() const
{
	return m_points;
}

std::vector<int> BezierSurface::getPointsIds() const
{
	std::vector<int> ids;
	ids.reserve(m_points.size());
	for (int i = 0; i < m_points.size(); ++i)
	{
		ids.push_back(m_points.at(i)->getId());
	}
	return ids;
}

void BezierSurface::initialize(BezierSurfaceData parameters)
{
	m_parameters = parameters;
	if (m_parameters.m_surfaceType == BezierSurfaceData::SurfaceType::plane)
	{
		planeSurfacePatchesPoints();
		planeSurfacePatches();
	}
	else
	{
		cylinderSurfacePatchesPoints();
		cylinderSurfacePatches();
	}
}

void BezierSurface::generateControlPointsIndices()
{
	for (int x = 0; x < m_parameters.m_patchesX * 3 + 1; ++x)
	{
		for (int y = 0; y < m_parameters.m_patchesY * 3 + 1; ++y)
		{
			m_indices.push_back(x * (m_parameters.m_patchesY * 3 + 1) + y);
		}
		m_indices.push_back(-1);
	}
	for (int y = 0; y < m_parameters.m_patchesY * 3 + 1; ++y)
	{
		for (int x = 0; x < m_parameters.m_patchesX * 3 + 1; ++x)
		{
			m_indices.push_back(x * (m_parameters.m_patchesY * 3 + 1) + y);
		}
		m_indices.push_back(-1);
	}
}

QVector3D BezierSurface::getPointOnSurface(BezierPatch patch, float u, float v) const
{
	QVector3D a = calculateSurfacePoint(v, patch.getPoints().at(0)->getPosition(), patch.getPoints().at(4)->getPosition(), patch.getPoints().at(8)->getPosition(), patch.getPoints().at(12)->getPosition());
	QVector3D b = calculateSurfacePoint(v, patch.getPoints().at(1)->getPosition(), patch.getPoints().at(5)->getPosition(), patch.getPoints().at(9)->getPosition(), patch.getPoints().at(13)->getPosition());
	QVector3D c = calculateSurfacePoint(v, patch.getPoints().at(2)->getPosition(), patch.getPoints().at(6)->getPosition(), patch.getPoints().at(10)->getPosition(), patch.getPoints().at(14)->getPosition());
	QVector3D d = calculateSurfacePoint(v, patch.getPoints().at(3)->getPosition(), patch.getPoints().at(7)->getPosition(), patch.getPoints().at(11)->getPosition(), patch.getPoints().at(15)->getPosition());

	return calculateSurfacePoint(u, a, b, c, d);
}

void BezierSurface::generateIndices()
{
	m_indices.clear();
	m_indices.reserve(3 * m_vertices.size());
	//generateControlPointsIndices();

	float u = 1.0f / m_parameters.m_u;
	float v = 1.0f / m_parameters.m_v;

	for (int n = 0; n < m_patches.size(); ++n)
	{
		int k = 0;
		for (float i = 0; i <= 1.0f; i += u)
		{
			for (float j = 0; j <= 1.0f; j += v)
			{
				m_indices.push_back(k + m_points.size() + (m_parameters.m_u + 1) * (m_parameters.m_v + 1) * n);
				++k;
			}
			m_indices.push_back(-1);
		}
		for (float j = 0; j <= m_parameters.m_v; ++j)
		{
			for (float i = 0; i <= m_parameters.m_u; ++i)
			{
				m_indices.push_back(i * (m_parameters.m_v + 1) + j + m_points.size() + (m_parameters.m_u + 1) * (m_parameters.m_v + 1) * n);
			}
			m_indices.push_back(-1);
		}
	}
}
