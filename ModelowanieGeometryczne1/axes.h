#pragma once
#include "drawableObject.h"

class Axes : public DrawableObject
{
public:
	Axes(ObjectType type);

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;

	bool m_x, m_y, m_z;

private:
	void createVertices() override;
	void generateIndices() override;
};
