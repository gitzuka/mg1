#include "bezierSurface.h"
#include "utils.h"
#include "camera.h"
#include <unordered_set>
#include <set>

BezierSurface::BezierSurface(ObjectType type, const QString &name, const BezierSurfaceData &parameters) : DrawableObject(type, name, true, true),
m_width(800), m_height(600), m_showBezierGrid(false), m_showControlGrid(false), m_curveFactor(0.05f), m_parameters(parameters)
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
	QVector3D vec = matrix.column(3).toVector3D();
	for (int i = 0; i < m_points.size(); ++i)
	{
		m_points.at(i)->setModelMatrix(matrix);
	}
	m_modelMatrix = matrix;
}

QVector2D BezierSurface::approximatePointOnSurface(QVector3D pos) const
{
	float minDist = std::numeric_limits<float>::infinity();
	QVector2D uv;
	for (int i = 0; i < 3 * m_parameters.m_patchesY + 1; ++i)
	{
		for (int j = 0; j < 3 * m_parameters.m_patchesX + 1; ++j)
		{
			float u = j / 3.0f;
			float v = i / 3.0f;
			QVector3D surfacePoint = getPointByUV(u, v);
			float dist = (pos - surfacePoint).length();
			if (dist < minDist)
			{
				uv = QVector2D(u, v);
				minDist = dist;
			}
		}
	}

	return uv;
}

QVector3D BezierSurface::getUDerivative(double u, double v) const
{
	BezierPatch patch = getPatchByUV(u, v);
	QVector2D uv = getPatchUV(patch, u, v);

	QVector3D d0 = calculateSurfacePoint(uv.y(), patch.getPoints().at(0)->getPosition(), patch.getPoints().at(4)->getPosition(), patch.getPoints().at(8)->getPosition(), patch.getPoints().at(12)->getPosition());
	QVector3D d1 = calculateSurfacePoint(uv.y(), patch.getPoints().at(1)->getPosition(), patch.getPoints().at(5)->getPosition(), patch.getPoints().at(9)->getPosition(), patch.getPoints().at(13)->getPosition());
	QVector3D d2 = calculateSurfacePoint(uv.y(), patch.getPoints().at(2)->getPosition(), patch.getPoints().at(6)->getPosition(), patch.getPoints().at(10)->getPosition(), patch.getPoints().at(14)->getPosition());
	QVector3D d3 = calculateSurfacePoint(uv.y(), patch.getPoints().at(3)->getPosition(), patch.getPoints().at(7)->getPosition(), patch.getPoints().at(11)->getPosition(), patch.getPoints().at(15)->getPosition());

	return calculateDerivative(uv.x(), d0, d1, d2, d3);
}

QVector3D BezierSurface::getVDerivative(double u, double v) const
{
	BezierPatch patch = getPatchByUV(u, v);
	QVector2D uv = getPatchUV(patch, u, v);

	QVector3D d0 = calculateSurfacePoint(uv.x(), patch.getPoints().at(0)->getPosition(), patch.getPoints().at(1)->getPosition(), patch.getPoints().at(2)->getPosition(), patch.getPoints().at(3)->getPosition());
	QVector3D d1 = calculateSurfacePoint(uv.x(), patch.getPoints().at(4)->getPosition(), patch.getPoints().at(5)->getPosition(), patch.getPoints().at(6)->getPosition(), patch.getPoints().at(7)->getPosition());
	QVector3D d2 = calculateSurfacePoint(uv.x(), patch.getPoints().at(8)->getPosition(), patch.getPoints().at(9)->getPosition(), patch.getPoints().at(10)->getPosition(), patch.getPoints().at(11)->getPosition());
	QVector3D d3 = calculateSurfacePoint(uv.x(), patch.getPoints().at(12)->getPosition(), patch.getPoints().at(13)->getPosition(), patch.getPoints().at(14)->getPosition(), patch.getPoints().at(15)->getPosition());

	return calculateDerivative(uv.y(), d0, d1, d2, d3);
}

BezierPatch BezierSurface::getPatchByUV(double u, double v) const
{
	int patchU = static_cast<int>(u);
	int patchV = static_cast<int>(v);

	if (patchU < 0)
		patchU = 0;
	else if (patchU >= m_parameters.m_patchesX)
		patchU = m_parameters.m_patchesX - 1;
	if (patchV >= m_parameters.m_patchesY)
		patchV = m_parameters.m_patchesY - 1;
	else if (patchV < 0)
		patchV = 0;

	BezierPatch bezierPatch(-1, -1);
	for (const auto &patch : m_patches)
	{
		if (patchU == patch.getU() && patchV == patch.getV())
			return patch;
	}
	return bezierPatch;
}

QVector2D BezierSurface::getPatchUV(BezierPatch patch, double u, double v) const
{
	return QVector2D(u - patch.getU(), v - patch.getV());
}

QVector4D BezierSurface::getRangeUV(double u, double v) const
{
	BezierPatch patch = getPatchByUV(u, v);
	return QVector4D(patch.getU(), patch.getU() + 1, patch.getV(), patch.getV() + 1);
}

QVector3D BezierSurface::getPointByUV(double u, double v) const
{
	BezierPatch patch = getPatchByUV(u, v);
	QVector2D uv = getPatchUV(patch, u, v);

	return getPointOnSurface(patch, uv.x(), uv.y());
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

void BezierSurface::pointMoved(int id)
{
	createVertices();
}

bool BezierSurface::isWrapped() const
{
	return m_isWrapped;
}

void BezierSurface::setPosition(QVector3D pos)
{
	m_pos = pos;
	for (int i = 0; i < m_points.size(); ++i)
	{
		m_points.at(i)->setBezierSurfacePosition(pos, m_rotation);
	}
	m_modelMatrix = Camera::createTranslation(pos) * QMatrix4x4(m_rotation.toRotationMatrix());
}

void BezierSurface::rotate(QVector3D eulerAngles)
{
	QQuaternion q1 = QQuaternion::fromAxisAndAngle(QVector3D(1, 0, 0), eulerAngles.x()).normalized();
	QQuaternion q2 = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), eulerAngles.y()).normalized();
	QQuaternion q3 = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), eulerAngles.z()).normalized();
	//m_rotation = q3 * q1 * q2;
	m_rotation = q1 * q2 * q3;
	for (int i = 0; i < m_points.size(); ++i)
	{
		m_points.at(i)->setBezierSurfacePosition(m_pos, m_rotation);
	}
	m_modelMatrix = Camera::createTranslation(m_pos) * QMatrix4x4(m_rotation.toRotationMatrix());
}

void BezierSurface::initialize(BezierSurfaceData parameters)
{
	m_parameters = parameters;
	if (m_parameters.m_surfaceType == BezierSurfaceData::SurfaceType::plane)
	{
		planeSurfacePatchesPoints();
		planeSurfacePatches();
		m_isWrapped = false;
	}
	else
	{
		cylinderSurfacePatchesPoints();
		cylinderSurfacePatches();
		m_isWrapped = true;
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

QVector3D BezierSurface::getPointOnSurface(BezierPatch patch, double u, double v) const
{
	QVector3D a = calculateSurfacePoint(v, patch.getPoints().at(0)->getPosition(), patch.getPoints().at(4)->getPosition(), patch.getPoints().at(8)->getPosition(), patch.getPoints().at(12)->getPosition());
	QVector3D b = calculateSurfacePoint(v, patch.getPoints().at(1)->getPosition(), patch.getPoints().at(5)->getPosition(), patch.getPoints().at(9)->getPosition(), patch.getPoints().at(13)->getPosition());
	QVector3D c = calculateSurfacePoint(v, patch.getPoints().at(2)->getPosition(), patch.getPoints().at(6)->getPosition(), patch.getPoints().at(10)->getPosition(), patch.getPoints().at(14)->getPosition());
	QVector3D d = calculateSurfacePoint(v, patch.getPoints().at(3)->getPosition(), patch.getPoints().at(7)->getPosition(), patch.getPoints().at(11)->getPosition(), patch.getPoints().at(15)->getPosition());

	return calculateSurfacePoint(u, a, b, c, d);
}

void BezierSurface::generateIndices()
{
	float u = 1.0f / m_parameters.m_u;
	float v = 1.0f / m_parameters.m_v;
	for (const auto &patch : m_patches)
	{
		for (float i = 0; i <= 1.0f; i += u)
		{
			int prevIndex = m_vertices.size();
			int ind = 0;
			for (float k = 0; k < 1.0f; k += m_curveFactor)
			{
				m_vertices.push_back(QVector4D(getPointOnSurface(patch, i, k), 1.0f));
				m_indices.push_back(ind + prevIndex);
				m_indices.push_back(ind + prevIndex + 1);
				++ind;
			}
			m_vertices.push_back(QVector4D(getPointOnSurface(patch, i, 1.0f), 1.0f));
			m_indices.push_back(-1);
		}
	}
	for (const auto &patch : m_patches)
	{
		for (float i = 0; i <= 1.0f; i += v)
		{
			int prevIndex = m_vertices.size();
			int ind = 0;
			for (float k = 0; k < 1.0f; k += m_curveFactor)
			{
				m_vertices.push_back(QVector4D(getPointOnSurface(patch, k, i), 1.0f));
				m_indices.push_back(ind + prevIndex);
				m_indices.push_back(ind + prevIndex + 1);
				++ind;
			}
			m_vertices.push_back(QVector4D(getPointOnSurface(patch, 1.0f, i), 1.0f));
			m_indices.push_back(-1);
		}
	}
}

void BezierSurface::createVertices()
{
	m_vertices.clear();
	m_indices.clear();
	//int curveFactor = 20;
	int curveFactor = 16;
	m_vertices.reserve((m_parameters.m_u + 1) * (m_parameters.m_v + 1) + m_points.size());
	for (int i = 0; i < m_points.size(); ++i)
	{
		m_vertices.push_back(QVector4D(m_points.at(i)->getPosition(), 1.0f));
	}
	float u = 1.0f / m_parameters.m_u;
	float v = 1.0f / m_parameters.m_v;

	for (const auto &patch : m_patches)
	{
		for (int i = 0; i <= m_parameters.m_u; ++i)
		{
			for (int j = 0; j <= m_parameters.m_v; ++j)
			{
				m_vertices.push_back(QVector4D(getPointOnSurface(patch, u * i, v * j), 1.0f));
			}
		}
	}

	for (const auto &patch : m_patches)
	{
		for (int i = 0; i <= m_parameters.m_u; ++i)
		{
			int prevIndex = m_vertices.size();
			int ind = 0;
			for (int j = 0; j < curveFactor; ++j)
			{
				m_vertices.push_back(QVector4D(getPointOnSurface(patch, u * i, m_curveFactor * j), 1.0f));
				m_indices.push_back(ind + prevIndex);
				m_indices.push_back(ind + prevIndex + 1);
				++ind;
			}
			m_vertices.push_back(QVector4D(getPointOnSurface(patch, u * i, 1.0f), 1.0f));
			m_indices.push_back(-1);
		}
	}
	for (const auto &patch : m_patches)
	{
		for (int i = 0; i <= m_parameters.m_v; ++i)
		{
			int prevIndex = m_vertices.size();
			int ind = 0;
			for (int j = 0; j < curveFactor; ++j)
			{
				m_vertices.push_back(QVector4D(getPointOnSurface(patch, m_curveFactor * j, v * i), 1.0f));
				m_indices.push_back(ind + prevIndex);
				m_indices.push_back(ind + prevIndex + 1);
				++ind;
			}
			m_vertices.push_back(QVector4D(getPointOnSurface(patch, 1.0f, v * i), 1.0f));
			m_indices.push_back(-1);
		}
	}


	/*for (const auto &patch : m_patches)
	{
		for (float i = 0; i <= 1.0f; i += u)
		{
			for (float j = 0; j <= 1.0f; j += v)
			{
				m_vertices.push_back(QVector4D(getPointOnSurface(patch, i, j), 1.0f));
			}
		}
	}

	for (const auto &patch : m_patches)
	{
		for (float i = 0; i <= 1.0f; i += u)
		{
			int prevIndex = m_vertices.size();
			int ind = 0;
			for (float k = 0; k < 1.0f; k += m_curveFactor)
			{
				m_vertices.push_back(QVector4D(getPointOnSurface(patch, i, k), 1.0f));
				m_indices.push_back(ind + prevIndex);
				m_indices.push_back(ind + prevIndex + 1);
				++ind;
			}
			m_vertices.push_back(QVector4D(getPointOnSurface(patch, i, 1.0f), 1.0f));
			m_indices.push_back(-1);
		}
	}
	for (const auto &patch : m_patches)
	{
		for (float i = 0; i <= 1.0f; i += v)
		{
			int prevIndex = m_vertices.size();
			int ind = 0;
			for (float k = 0; k < 1.0f; k += m_curveFactor)
			{
				m_vertices.push_back(QVector4D(getPointOnSurface(patch, k, i), 1.0f));
				m_indices.push_back(ind + prevIndex);
				m_indices.push_back(ind + prevIndex + 1);
				++ind;
			}
			m_vertices.push_back(QVector4D(getPointOnSurface(patch, 1.0f, i), 1.0f));
			m_indices.push_back(-1);
		}
	}*/
	if (m_showBezierGrid)
	{
		generateIndices();
	}
	if (m_showControlGrid)
	{
		generateControlPointsIndices();
	}
}
