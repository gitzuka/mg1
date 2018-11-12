#include "BezierSurfaceC0.h"
#include "curveCubic.h"
#include "3dmath.h"

BezierSurfaceC0::BezierSurfaceC0(ObjectType type, const QString &name, const BezierSurfaceData &parameters) : BezierSurface(type, name, parameters)
{
}

BezierSurfaceC0::~BezierSurfaceC0()
{
}

QVector3D BezierSurfaceC0::calculateDerivative(double t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const
{
	double tnew = 1 - t;
	QVector3D d0 = 3 * (b - a);
	QVector3D d1 = 3 * (c - b);
	QVector3D d2 = 3 * (d - c);

	QVector3D dd0 = d0 * tnew + d1 * t;
	QVector3D dd1 = d1 * tnew + d2 * t;

	return QVector3D(dd0 * tnew + dd1 * t);
}

void BezierSurfaceC0::initializeFromPoints(const std::vector<int>& ids,
	const std::vector<std::shared_ptr<Point3D>>& points)
{
	m_points.clear();
	int X = m_parameters.m_patchesX * 3 + 1;
	int Y = m_parameters.m_patchesY * 3 + 1;
	for (int i = 0; i < Y; ++i)
	{
		for (int j = 0; j < X; ++j)
		{
			m_points.emplace_back(points[ids[j * Y + i]]);
		}
	}
	planeSurfacePatches();
	if (m_parameters.m_surfaceType == BezierSurfaceData::SurfaceType::cylinder)
	{
		m_points.clear();
		for (int i = 0; i < Y; ++i)
		{
			for (int j = 0; j < X - 1; ++j)
			{
				if (std::find(m_points.begin(), m_points.end(), points[ids[j * Y + i]]) == m_points.end())
				{
					m_points.emplace_back(points[ids[j * Y + i]]);
				}
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

	float distX = m_parameters.m_sizeX / (pointsX - 1);
	float distY = m_parameters.m_sizeY / (pointsY - 1);

	for (int i = 0; i < pointsY; ++i)
	{
		for (int j = 0; j < pointsX; ++j)
		{
			std::shared_ptr<Point3D> point = std::make_shared<Point3D>(ObjectType::point3D, "Point3D");
			point->setPosition(QVector4D(j * distX, 0, -i * distY, 1));
			//point->DrawableObject::setPosition(QVector3D(j * distX, 0, -i * distY));
			m_points.push_back(point);
		}
	}
}

void BezierSurfaceC0::cylinderSurfacePatchesPoints()
{
	/*int pointsX = 3 * m_parameters.m_patchesX;
	int pointsY = 3 * m_parameters.m_patchesY + 1;*/
	int pointsX = 3 * m_parameters.m_patchesX;
	int pointsY = 3 * m_parameters.m_patchesY + 1;
	float angle = 360.0f / pointsX;
	float distY = m_parameters.m_height / (pointsY - 1);
	for (int i = 0; i < pointsY; i++)
	{
		for (int j = 0; j < pointsX; j++)
		{
			std::shared_ptr<Point3D> point = std::make_shared<Point3D>(ObjectType::point3D, "Point3D");
			float x = cos(j * angle * M_PI / 180.0f) * m_parameters.m_radius;
			float y = sin(j * angle * M_PI / 180.0f) * m_parameters.m_radius;
			point->setPosition(QVector4D(x, i * distY, y, 1));
			//point->DrawableObject::setPosition(QVector3D(x, i * distY, y));
			m_points.push_back(point);
		}
	}
}

QVector3D BezierSurfaceC0::calculateSurfacePoint(float t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const
{
	float tnew = 1 - t;
	a = a * tnew + b * t;
	b = b * tnew + c * t;
	c = c * tnew + d * t;

	a = a * tnew + b * t;
	b = b * tnew + c * t;

	return QVector3D(a * tnew + b * t);
}

