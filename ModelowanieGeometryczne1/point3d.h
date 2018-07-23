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

	void setPosition(const QVector4D &point);
	void setAncestor(std::weak_ptr<DrawableObject> ancestor);
	void notifyAncestorsPositionChanged();

private:
	std::unordered_map<int, std::weak_ptr<DrawableObject>> m_ancestors;

	void createVertices() override;
	void generateIndices() override;
};
