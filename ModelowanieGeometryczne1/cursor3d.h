#pragma once
#include "drawableObject.h"
#include <memory>

class Camera;

class Cursor3D : public DrawableObject
{
public:
	Cursor3D(ObjectType type);

	std::shared_ptr<DrawableObject> m_obtainedObject;
	QVector3D m_worldCoords;

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	QVector4D getPosition() const override;
	
	int acquireObject(const QList<std::shared_ptr<DrawableObject>> &objects);
	void releaseObject();
	void updatePosition(float x, float y, float z, int width, int heigth, const Camera &camera);
	int getClosestObject(const QList<std::shared_ptr<DrawableObject>> &objects) const;

private:
	void createVertices() override;
	void generateIndices() override;
	float calculateDistance2D(float x1, float x2, float y1, float y2) const;
	float calculateDistance2D(const std::shared_ptr<DrawableObject> &object1, const std::shared_ptr<DrawableObject> &object2) const;
	float calculateDistance3D(float x1, float x2, float y1, float y2, float z1, float z2) const;
	float calculateDistance3D(const std::shared_ptr<DrawableObject> &object1, const std::shared_ptr<DrawableObject> &object2) const;
	float calculateDistance3D(const QVector4D &vec1, const QVector4D &vec2) const;
};
