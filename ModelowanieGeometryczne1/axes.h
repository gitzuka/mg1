#pragma once
#include "drawableObject.h"

class Axes : public DrawableObject
{
public:
	Axes(ObjectType type);

	bool m_x, m_y, m_z;

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;

private:
	const int m_axeVertNum;

	void createVertices() override;
	void generateIndices() override;
	void drawLines(const std::vector<QVector4D>& vec, int index, float3 color) const;
	void drawX(const std::vector<QVector4D>& vec) const;
	void drawY(const std::vector<QVector4D>& vec) const;
	void drawZ(const std::vector<QVector4D>& vec) const;
};
