#pragma once
#include "drawableObject.h"

class TrimmingCurve : public DrawableObject
{
public:
	TrimmingCurve(ObjectType type, QString name);
	TrimmingCurve(ObjectType type, QString name, std::vector<QVector4D> vertices);
	~TrimmingCurve();

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;

	void setVertices(std::vector<QVector4D> &vertices);

private:
	void createVertices() override;
	void generateIndices() override;
};
