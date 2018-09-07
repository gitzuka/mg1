#include "bezierSurfaceC2.h"

BezierSurfaceC2::BezierSurfaceC2(ObjectType type, const QString &name, const BezierSurfaceData &parameters) : BezierSurface(type, name, parameters)
{
}

BezierSurfaceC2::~BezierSurfaceC2()
{
}

QVector3D BezierSurfaceC2::calculateDerivative(double t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const
{
	float *coeff = calculateBasis(t, 3);
	QVector3D d0 = b - a;
	QVector3D d1 = c - b;
	QVector3D d2 = d - c;
	QVector3D derivative = coeff[0] * d0 + coeff[1] * d1 + coeff[2] * d2;
	delete[] coeff;
	coeff = nullptr;
	return derivative;
}

//void BezierSurfaceC2::createVertices()
//{
//	m_vertices.clear();
//	m_vertices.reserve((m_parameters.m_u + 1) * (m_parameters.m_v + 1) + m_points.size());
//	for (int i = 0; i < m_points.size(); ++i)
//	{
//		m_vertices.push_back(QVector4D(m_points.at(i)->getPosition(), 1.0f));
//	}
//	float u = 1.0f / m_parameters.m_u;
//	float v = 1.0f / m_parameters.m_v;
//	for (const auto &patch : m_patches)
//	{
//		for (float i = 0; i <= 1.0f; i += u)
//		{
//			for (float j = 0; j <= 1.0f; j += v)
//			{
//				m_vertices.push_back(QVector4D(getPointOnSurface(patch, i, j), 1.0f));
//			}
//		}
//	}
//
//	float curveFactor = 0.04f;
//	for (const auto &patch : m_patches)
//	{
//		for (float i = 0; i <= 1.0f; i += u)
//		{
//			int prevIndex = m_vertices.size();
//			int ind = 0;
//			for (float k = 0; k < 1.0f; k += curveFactor)
//			{
//				m_vertices.push_back(QVector4D(getPointOnSurface(patch, i, k), 1.0f));
//				m_indices.push_back(ind + prevIndex);
//				m_indices.push_back(ind + prevIndex + 1);
//				++ind;
//			}
//			m_vertices.push_back(QVector4D(getPointOnSurface(patch, i, 1.0f), 1.0f));
//			m_indices.push_back(-1);
//		}
//	}
//	for (const auto &patch : m_patches)
//	{
//		for (float i = 0; i <= 1.0f; i += v)
//		{
//			int prevIndex = m_vertices.size();
//			int ind = 0;
//			for (float k = 0; k < 1.0f; k += curveFactor)
//			{
//				m_vertices.push_back(QVector4D(getPointOnSurface(patch, k, i), 1.0f));
//				m_indices.push_back(ind + prevIndex);
//				m_indices.push_back(ind + prevIndex + 1);
//				++ind;
//			}
//			m_vertices.push_back(QVector4D(getPointOnSurface(patch, 1.0f, i), 1.0f));
//			m_indices.push_back(-1);
//		}
//	}
//	if (m_showBezierGrid)
//	{
//		generateIndices();
//	}
//	if (m_showControlGrid)
//	{
//		generateControlPointsIndices();
//	}
//}

void BezierSurfaceC2::planeSurfacePatches()
{
	for (int i = 0; i < m_parameters.m_patchesY; ++i)
	{
		for (int j = 0; j < m_parameters.m_patchesX; ++j)
		{
			BezierPatch patch(j, i);
			int cornerX = j;
			int cornerY = i;

			for (int k = 0; k < 4; ++k)
			{
				for (int n = 0; n < 4; ++n)
				{
					int pointX = cornerX + n;
					int pointY = cornerY + k;
					patch.addPoint(m_points.at(pointX + pointY * (m_parameters.m_patchesX + 3)));
				}
			}
			m_patches.push_back(patch);
		}
	}
}

void BezierSurfaceC2::cylinderSurfacePatches()
{
	for (int i = 0; i < m_parameters.m_patchesY; i++)
	{
		for (int j = 0; j < m_parameters.m_patchesX; j++)
		{
			BezierPatch patch(j, i);
			int cornerIndexX = j;
			int cornerIndexY = i;

			for (int k = 0; k < 4; k++)
			{
				for (int l = 0; l < 4; l++)
				{
					int pointX = (cornerIndexX + l) % m_parameters.m_patchesX;
					int pointY = cornerIndexY + k;
					patch.addPoint(m_points.at(pointX + pointY * (m_parameters.m_patchesX)));
				}
			}
			m_patches.push_back(patch);
		}
	}
}

void BezierSurfaceC2::planeSurfacePatchesPoints()
{
	int pointsX = m_parameters.m_patchesX + 3;
	int pointsY = m_parameters.m_patchesY + 3;

	float distX = m_parameters.m_sizeX / (pointsX - 1);
	float distY = m_parameters.m_sizeY / (pointsY - 1);

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

void BezierSurfaceC2::cylinderSurfacePatchesPoints()
{
	int pointsX = m_parameters.m_patchesX;
	int pointsY = m_parameters.m_patchesY + 3;
	float angle = 360.0f / pointsX;
	float distY = 0;
	if (pointsY - 1 != 0)
	{
		distY = m_parameters.m_height / (pointsY - 1);
	}

	for (int i = 0; i < pointsY; i++)
	{
		for (int j = 0; j < pointsX; j++)
		{
			std::shared_ptr<Point3D> point = std::make_shared<Point3D>(ObjectType::point3D, "Point3D");
			float x = cos(j * angle * M_PI / 180.0f) * m_parameters.m_radius;
			float z = sin(j * angle * M_PI / 180.0f) * m_parameters.m_radius;
			point->setPosition(QVector4D(i * distY, x, z, 1));
			m_points.push_back(point);
		}
	}
}

QVector3D BezierSurfaceC2::calculateSurfacePoint(float t, QVector3D a, QVector3D b, QVector3D c, QVector3D d) const
{
	/*float coeff[4];
	coeff[0] = 1;
	float temp, result;
	for (int i = 1; i < 4; ++i)
	{
		result = 0;
		for (int j = 0; j < i; ++j)
		{
			temp = coeff[j] / i;
			coeff[j] = result + (j - t + 1) * temp;
			result = (t + i - 1 - j) * temp;
		}
		coeff[i] = result;
	}*/
	float *coeff = calculateBasis(t, 4);
	QVector3D point = coeff[0] * a + coeff[1] * b + coeff[2] * c + coeff[3] * d;
	delete[] coeff;
	coeff = nullptr;
	return point;
}

float* BezierSurfaceC2::calculateBasis(float t, int deg) const
{
	float *coeff = new float[deg];
	coeff[0] = 1;
	float temp, result;
	for (int i = 1; i < deg; ++i)
	{
		result = 0;
		for (int j = 0; j < i; ++j)
		{
			temp = coeff[j] / i;
			coeff[j] = result + (j - t + 1) * temp;
			result = (t + i - 1 - j) * temp;
		}
		coeff[i] = result;
	}

	return coeff;
}
