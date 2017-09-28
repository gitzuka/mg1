#pragma once
#include "drawableObject.h"
#include "uiPoint3d.h"

class Point3D : public DrawableObject
{
public:
	Point3D(ObjectType type, QString name, const QMatrix4x4 &projMatrix);

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	QMatrix4x4 getModelMatrix() override;
	QVector4D getPosition() const override;

	void setCenter(const QVector3D &point);
	QVector3D getCenter() const;
	//void drawStereo(std::vector<QVector4D> &vec) const override;
	//void drawStereo2(std::vector<QVector4D> &vecL, std::vector<QVector4D> &vecR) const override;
	
	//QVector4D getCenter() const;

private:
	QVector3D m_center;
	const QMatrix4x4 &m_projMatrix;
	UiPoint3D m_uiPoint3D;

	void createVertices() override;
	void generateIndices() override;
};
