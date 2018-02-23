#pragma once
#include "drawableObject.h"
#include "uiPoint3d.h"

class Ui_ModelowanieGeometryczne1Class;

class Point3D : public DrawableObject
{
public:
	Point3D(ObjectType type, QString name, const QMatrix4x4 &projMatrix, const QMatrix4x4 &viewMatrix);

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	const QMatrix4x4& getModelMatrix() const override;
	QVector4D getPosition() const override;
	//void connectToUI(ListWidgetParameters *listWidget, ListWidgetObjects *listWidgetObj) const override;
	void connectToUI(const Ui_ModelowanieGeometryczne1Class ui) const override;

	//void setCenter(const QVector3D &point);
	void setCenter(const QMatrix4x4 &matrix);
	const QVector4D& getCenter() const;
	//void drawStereo(std::vector<QVector4D> &vec) const override;
	//void drawStereo2(std::vector<QVector4D> &vecL, std::vector<QVector4D> &vecR) const override;
	
	//QVector4D getCenter() const;

private:
	QVector4D m_center;
	const QMatrix4x4 &m_projMatrix;
	const QMatrix4x4 &m_viewMatrix;
	UiPoint3D m_uiPoint3D;

	void createVertices() override;
	void generateIndices() override;
};
