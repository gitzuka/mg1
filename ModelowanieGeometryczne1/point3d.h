#pragma once
#include "drawableObject.h"
#include <unordered_map>
#include <memory>

class Point3D : public DrawableObject
{
public:
	Point3D(ObjectType type, QString name, bool enabled = true);
	Point3D(ObjectType type, QString name, QVector4D position, bool enabled = true);

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	const QMatrix4x4& getModelMatrix() const override;
	QVector4D getPosition() const override;

	//void setPosition(const QVector3D &point);
	//void setPosition(const QMatrix4x4 &matrix);
	void setPosition(const QVector4D &point);
	void setAncestor(std::weak_ptr<DrawableObject> ancestor);
	void notifyAncestorsPositionChanged();
	//const QVector4D& getCenter() const;
	//const QList<int>& getAncestors() const;
	
	//QVector4D getCenter() const;

private:
	//QVector4D m_center;
	//QList<int> m_ancestors;
	std::unordered_map<int, std::weak_ptr<DrawableObject>> m_ancestors;

	void createVertices() override;
	void generateIndices() override;
};
