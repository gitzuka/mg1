#include "HeightmapGenerator.h"
#include "uiBezierSurface.h"
#include "fileManager.h"

HeightmapGenerator::HeightmapGenerator(int size, float precision, float sizeX, float sizeZ)
	: m_size(size), m_minX(0.5f * -sizeX), m_maxX(sizeX * 0.5f), m_minZ(-sizeZ * 0.5f), m_maxZ(sizeZ * 0.5f),
	m_precision(precision), m_xfactor(0.5f * size / m_maxX), m_zfactor(0.5f * size / m_maxZ),
	m_map(new float[size * size]()) //m_normals(new QVector3D[size * size])
{
}

HeightmapGenerator::~HeightmapGenerator()
{
	delete[] m_map;
	//delete[] m_normals;
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
					//QPoint coords = convertToPoint(pos);
					//addSphere(coords, pos.y());
					//continue;
				}
				if (normal.y() < 0)
				{
					normal = -normal;
				}
				pos += normal * radius;
				QPoint coords = convertToPoint(pos);
				if (checkCoords(coords) || pos.y() <= m_map[coords.x() + m_size * coords.y()])
					continue;
				//m_normals[coords.x() + m_size * coords.y()] = normal;
				m_map[coords.x() + m_size * coords.y()] = pos.y();
			}
		}
	}
}

void HeightmapGenerator::updateMapPrecise(const std::shared_ptr<BezierSurface>& surface, float radius, const QString& fileHeightmap)
{
	float precision = 1.0f / m_precision;
	float vPrecision = 15.0f;
	float safeHeight = 2.0f;
	float eps = 10e-6;
	float uvPrecision = 0.0001f;
	QVector4D uv = surface->getRangeUV();
	m_positions.clear();
	int mod = 0;
	std::vector<float> uzero;
	int width, height;
	float *heightmap = fileManager::loadHeightmap(fileHeightmap, height, width);
	for (int i = uv.x(); i <= uv.y() * m_precision; ++i)
	{
		float u = precision * i;
		std::vector<QVector4D> positions;
		positions.reserve(m_precision * uv.w());
		for (int j = uv.z(); j <= uv.w() * vPrecision; ++j)
		{
			float v = j / vPrecision;
			QVector3D pos = surface->getPointByUV(u, v);
			if (pos.y() < safeHeight)
			{
				continue;
				positions.clear();
				mod == 0 ? mod = 1 : mod = 0;
				break;
			}
			QVector3D normal = getNormal(surface, u, v).normalized();
			if (normal.length() < eps || !isfinite(normal.length()))
			{
				//qDebug("name: " + surface->getName().toLatin1() + " u: " + QString::number(precision * i).toLatin1() + " v: " + QString::number(precision * j).toLatin1() + " length: " + QString::number(normal.length()).toLatin1());

				continue;
				normal = getNormal(surface, u, v, uvPrecision).normalized();
				if (normal.length() < eps || !isfinite(normal.length()))
				{
					continue;
				}
			}
			if (normal.y() < 0)
			{
				continue;
			}
			pos += normal * radius;
			QPoint coords = convertToPoint(pos);


			if (heightmap[coords.x() + width * coords.y()] >= pos.y())
			{
				//if (!(positions.size() < 4))
				if (!(positions.empty()))
				{
					m_paths.emplace_back(positions);
					positions.clear();
				}
				continue;
			}
			positions.emplace_back(QVector4D(pos, 1));
		}
		if (!positions.empty())
			m_paths.emplace_back(positions);
	}
	delete[] heightmap;
}

void HeightmapGenerator::updateMapPrecise2(const std::shared_ptr<BezierSurface>& surface, float radius)
{

	QVector4D uv = surface->getRangeUV();
	float u = 1;
	float safeHeight = 2.0f;
	float vPrecision = 15.0f;
	std::vector<QVector4D> positions;
	for (int j = uv.z(); j <= uv.w() * vPrecision; ++j)
	{
		float v = j / vPrecision;
		QVector3D pos = surface->getPointByUV(u, v);
		if (pos.y() < safeHeight)
		{
			continue;
		}
		pos += QVector3D(0, 1, 0) * radius;
			positions.emplace_back(QVector4D(pos, 1));
	}
	m_paths.emplace_back(positions);
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

std::vector<QVector4D> HeightmapGenerator::updateEnvelopeMap(const std::shared_ptr<BezierSurface>& surface, float radius)
{
	std::vector<QVector4D> positions;
	positions.reserve(16000);
	float eps = 10e-6;
	float safeHeight = 2.0f;
	float precision = 1.0f / m_precision;

	if (surface->getName() == "kadlub")
	{
		float constU = 1.99f;
		float constU2 = 5.005f;
		QVector4D uv = surface->getRangeUV();
		for (int v = uv.z(); v < uv.w() * m_precision; ++v)
		{
			if (v >= 0 && v <= 0.08f || v >= 7.911 && v <= 7.999f)
				continue;
			QVector3D pos = surface->getPointByUV(constU, v * precision);
			QVector3D normal = getNormal(surface, constU, v * precision).normalized();
			if (normal.length() < eps || !isfinite(normal.length()))
			{
				//qDebug(surface->getName().toLatin1() + "u: " + QString::number(constU).toLatin1() + " v: " + QString::number(v * precision).toLatin1());
				continue;
			}
			pos.setX(pos.x() + normal.x() * radius);
			pos.setZ(pos.z() + normal.z() * radius);
			positions.emplace_back(QVector4D(pos, 1.0f));
		}
		std::vector<QVector4D> tmp;
		for (int v = uv.z(); v < uv.w() * m_precision; ++v)
		{
			if (v >= 0 && v <= 0.107f || v >= 7.932f && v <= 7.999f)
				continue;
			QVector3D pos = surface->getPointByUV(constU2, v * precision);
			QVector3D normal = getNormal(surface, constU2, v * precision).normalized();
			if (normal.length() < eps || !isfinite(normal.length()))
			{
				//qDebug(surface->getName().toLatin1() + "u: " + QString::number(constU2).toLatin1() + " v: " + QString::number(v * precision).toLatin1());
				continue;
			}
			pos.setX(pos.x() + normal.x() * radius);
			pos.setZ(pos.z() + normal.z() * radius);
			tmp.emplace_back(QVector4D(pos, 1.0f));
		}
		positions.insert(positions.end(), std::make_move_iterator(tmp.rbegin()), std::make_move_iterator(tmp.rend()));

	}
	if (surface->getName() == "smiglo")
	{
		float constU = 2.99f;
		float constU2 = 7.00f;
		QVector4D uv = surface->getRangeUV();
		for (int v = uv.z(); v < uv.w() * m_precision; ++v)
		{
			if (v >= 0 && v <= 0.118f || v >= 5.881 && v <= 5.999f)
				continue;
			QVector3D pos = surface->getPointByUV(constU, v * precision);
			QVector3D normal = getNormal(surface, constU, v * precision).normalized();
			if (normal.length() < eps || !isfinite(normal.length()))
			{
				//qDebug(surface->getName().toLatin1() + "u: " + QString::number(constU).toLatin1() + " v: " + QString::number(v * precision).toLatin1());
				continue;
			}
			pos.setX(pos.x() + normal.x() * radius);
			pos.setZ(pos.z() + normal.z() * radius);
			positions.emplace_back(QVector4D(pos, 1.0f));
		}
		std::vector<QVector4D> tmp;
		for (int v = uv.z(); v < uv.w() * m_precision; ++v)
		{
			if (v >= 0 && v <= 0.176f || v >= 5.826 && v <= 5.999f)
				continue;
			QVector3D pos = surface->getPointByUV(constU2, v * precision);
			QVector3D normal = getNormal(surface, constU2, v * precision).normalized();
			if (normal.length() < eps || !isfinite(normal.length()))
			{
				//qDebug(surface->getName().toLatin1() + "u: " + QString::number(constU2).toLatin1() + " v: " + QString::number(v * precision).toLatin1());
				continue;
			}
			pos.setX(pos.x() + normal.x() * radius);
			pos.setZ(pos.z() + normal.z() * radius);
			tmp.emplace_back(QVector4D(pos, 1.0f));
		}
		positions.insert(positions.end(), std::make_move_iterator(tmp.rbegin()), std::make_move_iterator(tmp.rend()));

	}
	if (surface->getName() == "ploza")
	{
		float constU = 4.0017f;
		float constU2 = 1.4982f;
		QVector4D uv = surface->getRangeUV();
		for (int v = uv.z(); v < uv.w() * m_precision; ++v)
		{
			QVector3D pos = surface->getPointByUV(constU, v * precision);
			QVector3D normal = getNormal(surface, constU, v * precision).normalized();
			if (normal.length() < eps || !isfinite(normal.length()))
			{
				//qDebug(surface->getName().toLatin1() + "u: " + QString::number(constU).toLatin1() + " v: " + QString::number(v * precision).toLatin1());
				continue;
			}
			pos.setX(pos.x() + normal.x() * radius);
			pos.setZ(pos.z() + normal.z() * radius);
			positions.emplace_back(QVector4D(pos, 1.0f));
		}
		for (int v = uv.z(); v < uv.w() * m_precision; ++v)
		{
			QVector3D pos = surface->getPointByUV(constU2, v * precision);
			QVector3D normal = getNormal(surface, constU2, v * precision).normalized();
			if (normal.length() < eps || !isfinite(normal.length()))
			{
				qDebug(surface->getName().toLatin1() + "u: " + QString::number(constU2).toLatin1() + " v: " + QString::number(v * precision).toLatin1());
				continue;
			}
			pos.setX(pos.x() + normal.x() * radius);
			pos.setZ(pos.z() + normal.z() * radius);
			positions.emplace_back(QVector4D(pos, 1.0f));
		}

	}
	if (surface->getName() == "podstawka")
	{
		float constU = 0.99f;
		float constU2 = 3.0015f;
		QVector4D uv = surface->getRangeUV();
		for (int v = uv.z(); v < uv.w() * m_precision; ++v)
		{
			QVector3D pos = surface->getPointByUV(constU, v * precision);
			QVector3D normal = getNormal(surface, constU, v * precision).normalized();
			if (normal.length() < eps || !isfinite(normal.length()))
			{
				qDebug(surface->getName().toLatin1() + "u: " + QString::number(constU).toLatin1() + " v: " + QString::number(v * precision).toLatin1());
				continue;
			}
			pos.setX(pos.x() + normal.x() * radius);
			pos.setZ(pos.z() + normal.z() * radius);
			positions.emplace_back(QVector4D(pos, 1.0f));
		}
		for (int v = uv.z(); v < uv.w() * m_precision; ++v)
		{
			QVector3D pos = surface->getPointByUV(constU2, v * precision);
			QVector3D normal = getNormal(surface, constU2, v * precision).normalized();
			if (normal.length() < eps || !isfinite(normal.length()))
			{
				qDebug(surface->getName().toLatin1() + "u: " + QString::number(constU2).toLatin1() + " v: " + QString::number(v * precision).toLatin1());
				continue;
			}
			pos.setX(pos.x() + normal.x() * radius);
			pos.setZ(pos.z() + normal.z() * radius);
			positions.emplace_back(QVector4D(pos, 1.0f));
		}

	}
	return positions;
}

float* HeightmapGenerator::getMap() const
{
	return m_map;
}

QPoint HeightmapGenerator::convertToPoint(const QVector3D &position) const
{
	QPoint p = QPoint((position.x() + m_maxX) * m_xfactor, (position.z() + m_maxZ) * m_zfactor);
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

QVector3D HeightmapGenerator::getNormal(const std::shared_ptr<BezierSurface>& surface, double u, double v,
	double precision) const
{
	QVector3D p1 = surface->getPointByUV(u + precision, v + precision);
	QVector3D p2 = surface->getPointByUV(u - precision, v - precision);
	return (p2 + p1) / 2;// * precision);
}

//QVector3D HeightmapGenerator::getNormal(const std::shared_ptr<BezierSurface>& surface, double u1, double v1, double u2,
//	double v2) const
//{
//	QVector3D du1 = surface->getPointByUV( u1, v1);
//	//QVector3D dv1 = surface->getVDerivative(u1, v1);
//	QVector3D du2 = surface->getPointByUV(u2, v2);
//	//QVector3D dv2 = surface->getVDerivative(u2, v2);
//	return QVector3D((du1 + du2) /  0.0001f);
//	//return QVector3D::crossProduct((du1 + du2) * 0.5f, (dv1 + dv2) * 0.5f);
//}

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
				float y = static_cast<float>(j) / static_cast<float>(r) * radius;
				float dist = sqrt(pow(x, 2.0f) + pow(y, 2.0f));
				//float height = sqrt(pow(radius, 2.0f) - pow(x, 2.0f));
				float height = sqrt(pow(radius, 2.0f) - pow(dist, 2.0f));
				m_sphereHeights.emplace_back(QPair<int, float>(i + m_size * j, height));
				m_sphereIndices.emplace_back(QPair<int, int>(i, j));
			}
		}
	}
}

void HeightmapGenerator::initCircleData(float radius)
{
	m_circleHeights.clear();
	m_circleIndices.clear();
	int r = radius / (abs(m_maxX - m_minX)) * m_size;
	float height = 3.0f;
	for (int i = -r; i <= r; ++i)
	{
		for (int j = -r; j <= r; ++j)
		{
			if (i * i + j * j == r * r)
			{
				/*	float x = static_cast<float>(i) / static_cast<float>(r) * radius;
					float y = static_cast<float>(j) / static_cast<float>(r) * radius;
					float dist = sqrt(pow(x, 2.0f) + pow(y, 2.0f));
					float height = sqrt(pow(radius, 2.0f) - pow(dist, 2.0f));*/
				m_circleHeights.emplace_back(QPair<int, float>(i + m_size * j, height));
				m_circleIndices.emplace_back(QPair<int, int>(i, j));
			}
		}
	}
}

std::vector<QVector4D> HeightmapGenerator::getPositions() const
{
	return m_positions;
}

std::vector<std::vector<QVector4D>> HeightmapGenerator::getPaths() const
{
	return m_paths;
}
