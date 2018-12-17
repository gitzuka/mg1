#pragma once
#include <memory>
#include <qopengltexture.h>

class BezierPatch;
class QVector3D;
class BezierSurface;

class HeightmapGenerator
{
public:
	HeightmapGenerator(int size, float precision, float sizeX = 15.0f, float sizeZ = 15.0f);
	~HeightmapGenerator();
	void updateMap(const std::shared_ptr<BezierSurface> &surface, float radius);
	void updateMapSpheres(const std::shared_ptr<BezierSurface> &surface);
	//QOpenGLTexture *getTexture() const;
	float *getMap() const;
	void initSphereData(float radius);

private:
	int m_size;
	float m_minX;
	float m_maxX;
	float m_minZ;
	float m_maxZ;
	float m_precision;
	float m_xfactor;
	float m_zfactor;
	//std::vector<std::vector<float>> m_map;
	float *m_map;
	QVector3D *m_normals;
	std::vector<QPair<int, float>> m_sphereHeights;
	std::vector<QPair<int, int>> m_sphereIndices;

	QPoint convertToPoint(const QVector3D &position) const;
	QVector3D getNormal(const std::shared_ptr<BezierSurface> &surface, double u, double v) const;
	void addSphere(const QPoint &pos, float height);
	bool checkCoords(const QPoint &pos) const;
};
