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
	std::vector<QVector4D> updateEnvelopeMap(const std::shared_ptr<BezierSurface> &surface, float radius);
	void updateEnvelopeMapCircles(const std::shared_ptr<BezierSurface> &surface);
	float *getMap() const;
	void initSphereData(float radius);
	void initCircleData(float radius);

private:
	int m_size;
	float m_minX;
	float m_maxX;
	float m_minZ;
	float m_maxZ;
	float m_precision;
	float m_xfactor;
	float m_zfactor;
	float *m_map;
	QVector3D *m_normals;
	std::vector<QPair<int, float>> m_sphereHeights;
	std::vector<QPair<int, int>> m_sphereIndices;
	std::vector<QPair<int, float>> m_circleHeights;
	std::vector<QPair<int, int>> m_circleIndices;

	QPoint convertToPoint(const QVector3D &position) const;
	QVector3D getNormal(const std::shared_ptr<BezierSurface> &surface, double u, double v) const;
	void addSphere(const QPoint &pos, float height);
	bool checkCoords(const QPoint &pos) const;
};
