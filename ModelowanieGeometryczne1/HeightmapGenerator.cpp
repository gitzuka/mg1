#include "HeightmapGenerator.h"
#include "uiBezierSurface.h"

HeightmapGenerator::HeightmapGenerator(int size, float precision, float sizeX, float sizeZ)
	: m_size(size), m_minX(0.5f * -sizeX), m_maxX(sizeX * 0.5f), m_minZ(-sizeZ * 0.5f), m_maxZ(sizeZ * 0.5f),
	m_precision(precision), m_xfactor(0.5f * size / m_maxX), m_zfactor(0.5f * size / m_maxZ),
	m_map(new float[size * size]()), m_normals(new QVector3D[size * size])
{
}

HeightmapGenerator::~HeightmapGenerator()
{
	delete[] m_map;
	delete[] m_normals;
}

void HeightmapGenerator::updateMap(const std::shared_ptr<BezierSurface>& surface, float radius)
{
	//QVector4D rangeUV = surface->getRangeUV();
	//std::vector<float> test;
	float precision = 1.0f / m_precision;
	//initSphereData(radius);
	float safeHeight = 2.0f;
	float eps = 10e-6;
	for (const auto &patch : surface->getPatches())
	{
		for (int i = 0; i <= m_precision; ++i)
		{
			for (int j = 0; j <= m_precision; ++j)
			{
				QVector3D pos = surface->getPointOnSurface(patch, precision * i, precision * j);
				if (pos.y() < safeHeight)
					continue;
				QVector3D normal = getNormal(surface, patch.getU() + precision * i, patch.getV() + precision * j).normalized();
				if (normal.length() < eps || !isfinite(normal.length()))
				{
					continue;
					//qDebug("name: " + surface->getName().toLatin1() + " u: " + QString::number(precision * i).toLatin1() +" v: " + QString::number(precision * j).toLatin1() + " length: " + QString::number(normal.length()).toLatin1());
					QPoint coords = convertToPoint(pos);
					addSphere(coords, pos.y());
					continue;
				}
				if (normal.y() < 0)
				{
					normal = -normal;
				}
				pos += normal * radius;
				QPoint coords = convertToPoint(pos);
				if (checkCoords(coords) || pos.y() <= m_map[coords.x() + m_size * coords.y()])
					continue;
				m_normals[coords.x() + m_size * coords.y()] = normal;
				m_map[coords.x() + m_size * coords.y()] = pos.y();
			}
		}
	}
}

void HeightmapGenerator::updateMapSpheres(const std::shared_ptr<BezierSurface>& surface)
{
	int precisionFactor = 100;
	float precision = 1.0f / static_cast<float>(precisionFactor);
	//initSphereData(radius);
	float safeHeight = 2.0f;
	for (const auto &patch : surface->getPatches())
	{
		for (int i = 0; i <= precisionFactor; ++i)
		{
			for (int j = 0; j <= precisionFactor; ++j)
			{
				QVector3D pos = surface->getPointOnSurface(patch, precision * i, precision * j);
				if (pos.y() < safeHeight)
					continue;
				QVector3D normal = getNormal(surface, patch.getU() + precision * i, patch.getV() + precision * j).normalized();
				if (normal.length() == 0 || !isfinite(normal.length()))
				{
					QPoint coords = convertToPoint(pos);
					addSphere(coords, pos.y());
				}
			}
		}
	}
}

//QOpenGLTexture *HeightmapGenerator::getTexture() const
//{
//	QOpenGLTexture *texture = new QOpenGLTexture(QOpenGLTexture::Target::Target2DArray);
//	texture->setMinificationFilter(QOpenGLTexture::Nearest);
//	texture->setMagnificationFilter(QOpenGLTexture::Linear);
//	texture->setWrapMode(QOpenGLTexture::Repeat);
//	texture->setData(QOpenGLTexture::Depth, QOpenGLTexture::Float32, m_map);
//	return texture;
//}

float* HeightmapGenerator::getMap() const
{
	return m_map;
}

QPoint HeightmapGenerator::convertToPoint(const QVector3D &position) const
{
	QPoint p = QPoint((position.x() + m_maxX) * m_xfactor, (position.z() + m_maxZ) *m_zfactor);
	/*if (p.x() >= m_size)
		p.setX(m_size - 1);
	if (p.y() >= m_size)
		p.setY(m_size - 1);
	if (p.x() < 0)
		p.setX(0);
	if (p.y() < 0)
		p.setY(0);*/
	return p;
}

QVector3D HeightmapGenerator::getNormal(const std::shared_ptr<BezierSurface>& surface, double u, double v) const
{
	QVector3D du = surface->getUDerivative(u, v);
	QVector3D dv = surface->getVDerivative(u, v);
	return QVector3D::crossProduct(du, dv);
}

void HeightmapGenerator::addSphere(const QPoint &pos, float height)
{
	int currIndex = pos.x() + m_size * pos.y();
	for (int i = 0; i < m_sphereHeights.size(); ++i)
	{
		if (m_sphereIndices[i].first + pos.x() < 0 || m_sphereIndices[i].first + pos.x() > m_size || m_sphereIndices[i].second + pos.y() < 0 || m_sphereIndices[i].second + pos.y() > m_size)
			continue;
		if (m_sphereHeights[i].second + height > m_map[currIndex + m_sphereHeights[i].first])
			m_map[currIndex + m_sphereHeights[i].first] = m_sphereHeights[i].second + height;
	}
}

bool HeightmapGenerator::checkCoords(const QPoint& pos) const
{
	return (pos.x() >= m_size || pos.x() < 0 || pos.y() >= m_size || pos.y() < 0);
}

void HeightmapGenerator::initSphereData(float radius)
{
	m_sphereHeights.clear();
	m_sphereIndices.clear();
	int r = radius / (abs(m_maxX - m_minX)) * m_size;
	for (int i = -r; i <= r; ++i)
	{
		for (int j = -r; j <= r; ++j)
		{
			if (i * i + j * j <= r * r)
			{
				float x = static_cast<float>(i) / static_cast<float>(r) * radius;
				float height = sqrt(pow(radius, 2.0f) - pow(x, 2.0f));
				m_sphereHeights.emplace_back(QPair<int, float>(i + m_size * j, height));
				m_sphereIndices.emplace_back(QPair<int, int>(i, j));
			}
		}
	}
}
