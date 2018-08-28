#include "BezierSurfaceC0.h"

BezierSurfaceC0::BezierSurfaceC0(ObjectType type, const QString &name, const BezierSurfaceData &parameters) : BezierSurface(type, name, parameters)
{
}

BezierSurfaceC0::~BezierSurfaceC0()
{
}

void BezierSurfaceC0::pointMoved(int id)
{
	createVertices();
}

void BezierSurfaceC0::createVertices()
{
	m_vertices.clear();
	m_vertices.reserve((m_parameters.m_u + 1) * (m_parameters.m_v + 1) + m_points.size());
	for (int i = 0; i < m_points.size(); ++i)
	{
		m_vertices.push_back(QVector4D(m_points.at(i)->getPosition(), 1.0f));
	}
	float u = 1.0f / m_parameters.m_u;
	float v = 1.0f / m_parameters.m_v;
	for (const auto &patch : m_patches)
	{
		for (float i = 0; i <= 1.0f; i += u)
		{
			for (float j = 0; j <= 1.0f; j += v)
			{
				m_vertices.push_back(QVector4D(getPointOnSurface(patch, i, j), 1.0f));
			}
		}
	}
}

void BezierSurfaceC0::planeSurfacePatches()
{
	for (int i = 0; i < m_parameters.m_patchesY; ++i)
	{
		for (int j = 0; j < m_parameters.m_patchesX; ++j)
		{
			BezierPatch patch(j, i);
			int cornerX = j * 3;
			int cornerY = i * 3;

			for (int k = 0; k < 4; ++k)
			{
				for (int n = 0; n < 4; ++n)
				{
					int pointX = cornerX + n;
					int pointY = cornerY + k;
					patch.addPoint(m_points.at(pointX + pointY * (3 * m_parameters.m_patchesX + 1)));
				}
			}
			m_patches.push_back(patch);
		}
	}
}

void BezierSurfaceC0::cylinderSurfacePatches()
{
	for (int i = 0; i < m_parameters.m_patchesY; i++)
	{
		for (int j = 0; j < m_parameters.m_patchesX; j++)
		{
			BezierPatch patch(j, i);
			int cornerIndexX = j * 3;
			int cornerIndexY = i * 3;
			for (int k = 0; k < 4; k++)
			{
				for (int l = 0; l < 4; l++)
				{
					int pointX = cornerIndexX + l;
					int pointY = cornerIndexY + k;

					if (pointX == m_parameters.m_patchesX * 3)
					{
						pointX = 0;
					}
					patch.addPoint(m_points.at(pointX + pointY * (3 * m_parameters.m_patchesX)));
				}
			}
			m_patches.push_back(patch);
		}
	}
}

void BezierSurfaceC0::planeSurfacePatchesPoints()
{
	int pointsX = 3 * m_parameters.m_patchesX + 1;
	int pointsY = 3 * m_parameters.m_patchesY + 1;

	float screenFactor = 0.001f;
	float distX = screenFactor * m_width / (pointsX - 1);
	float distY = screenFactor * m_height / (pointsY - 1);

	for (int i = 0; i < pointsY; ++i)
	{
		for (int j = 0; j < pointsX; ++j)
		{
			std::shared_ptr<Point3D> point = std::make_shared<Point3D>(ObjectType::point3D, "Point3D");
			point->setPosition(QVector4D(j * distX, 0, -i * distY, 1));
			m_points.push_back(point);
		}
	}
}

void BezierSurfaceC0::cylinderSurfacePatchesPoints()
{
	int pointsX = 3 * m_parameters.m_patchesX;
	int pointsY = 3 * m_parameters.m_patchesY + 1;
	float angle = 360.0f / pointsX;
	float screenFactor = 0.001f;
	float distY = screenFactor * m_height / (pointsY - 1);
	for (int j = 0; j < pointsY; j++)
	{
		for (int i = 0; i < pointsX; i++)
		{
			std::shared_ptr<Point3D> point = std::make_shared<Point3D>(ObjectType::point3D, "Point3D");
			float x = cos(i * angle * M_PI / 180.0f) * m_parameters.m_radius;
			float y = sin(i * angle *M_PI / 180.0f) * m_parameters.m_radius;
			point->setPosition(QVector4D(x, j * distY, y, 1));
			m_points.push_back(point);
		}
	}
}

QVector3D BezierSurfaceC0::calculateSurfacePoint(float t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const
{
	float param = 1 - t;
	a = a * param + b * t;
	b = b * param + c * t;
	c = c * param + d * t;

	a = a * param + b * t;
	b = b * param + c * t;

	return QVector3D(a * param + b * t);
}

