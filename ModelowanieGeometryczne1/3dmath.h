#pragma once
#include <QVector4D>
#include <memory>
#include "drawableObject.h"
namespace math3d 
{
	static QVector4D getPointBetweenPoints(QVector4D p1, QVector4D p2, float distanceRatio);
	static QVector4D getPointBetweenPoints(QVector3D p1, QVector3D p2, float distanceRatio);
	static float calculateDistance2D(float x1, float x2, float y1, float y2);
	static float calculateDistance2D(const std::shared_ptr<DrawableObject> &object1, const std::shared_ptr<DrawableObject> &object2);
	static float calculateDistance3D(float x1, float x2, float y1, float y2, float z1, float z2);
	static float calculateDistance3D(const std::shared_ptr<DrawableObject> &object1, const std::shared_ptr<DrawableObject> &object2);
	static float calculateDistance3D(const QVector4D &vec1, const QVector4D &vec2);

	inline QVector4D getPointBetweenPoints(QVector4D p1, QVector4D p2, float distanceRatio)
	{
		return (p1 + (p2 - p1) * distanceRatio);
	}

	inline QVector4D getPointBetweenPoints(QVector3D p1, QVector3D p2, float distanceRatio)
	{
		return QVector4D(p1 + (p2 - p1) * distanceRatio, 1.0f);
	}

	inline float calculateDistance2D(float x1, float x2, float y1, float y2)
	{
		return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
	}

	inline float calculateDistance2D(const std::shared_ptr<DrawableObject>& object1, const std::shared_ptr<DrawableObject>& object2)
	{
		return calculateDistance2D(object1->getModelMatrix().row(0).w(), object2->getModelMatrix().row(0).w(),
			object1->getModelMatrix().row(1).w(), object2->getModelMatrix().row(1).w());
	}

	inline float calculateDistance3D(float x1, float x2, float y1, float y2, float z1, float z2)
	{
		return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) + (z2 - z1)*(z2 - z1));
	}

	inline float calculateDistance3D(const std::shared_ptr<DrawableObject>& object1, const std::shared_ptr<DrawableObject>& object2)
	{
		return calculateDistance3D(object1->getPosition().x(), object2->getPosition().x(),
			object1->getPosition().y(), object2->getPosition().y(),
			object1->getPosition().z(), object2->getPosition().z());
	}

	inline float calculateDistance3D(const QVector4D& vec1, const QVector4D& vec2)
	{
		return calculateDistance3D(vec1.x(), vec2.x(),
			vec1.y(), vec2.y(),
			vec1.z(), vec2.z());
	}
}
