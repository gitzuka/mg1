#pragma once
#include <vector>
#include "drawableObject.h"
#include <QVector4D>
#include "intersectableObject.h"

class Torus : public DrawableObject, public IntersectableObject
{
public:
	Torus(ObjectType type, QString name);
	Torus(float r, float R, int minor, int major, ObjectType type, QString name);

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	QVector2D approximatePointOnSurface(QVector3D pos) const override;
	QVector3D getUDerivative(double u, double v) const override;
	QVector3D getVDerivative(double u, double v) const override;
	//BezierPatch getPatchByUV(double u, double v) const override;
	//QVector2D getPatchUV(BezierPatch patch, double u, double v) const override;
	QVector3D getPointByUV(double u, double v) const override;
	QVector4D getRangeUV(double u, double v) const override;
	bool isWrapped() const override;

	void setSmallRadius(float);
	void setBigRadius(float);
	void setMinorSegments(int);
	void setMajorSegments(int);

private:
	float m_smallRadius;
	float m_bigRadius;
	int m_minorSegments;
	int m_majorSegments;
	bool m_isWrapped;

	void createVertices() override;
	void generateIndices() override;
};

