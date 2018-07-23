#pragma once
#include <vector>
#include "drawableObject.h"
#include <QVector4D>

class Torus : public DrawableObject
{
public:
	Torus(ObjectType type, QString name);
	Torus(float r, float R, int minor, int major, ObjectType type, QString name);

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;

	void setSmallRadius(float);
	void setBigRadius(float);
	void setMinorSegments(int);
	void setMajorSegments(int);

private:
	float m_smallRadius;
	float m_bigRadius;
	int m_minorSegments;
	int m_majorSegments;

	void createVertices() override;
	void generateIndices() override;
};
