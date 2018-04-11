#pragma once
#include "point3d.h"
#include "torus.h"
#include "curveCubic.h"
//#include "listwidgetobjects.h"
#include "uiBezierCurveC0.h"
#include <memory>

class BezierCurveC0 : public DrawableObject
{
public:
	BezierCurveC0(ObjectType type, QString name);
	~BezierCurveC0();

	friend class UiBezierCurveC0;

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	QVector4D getPosition() const override;
	void addControlPoint(const std::shared_ptr<DrawableObject> &point);
	
	QList<int> getControlPointIds() const;
	const QList<std::shared_ptr<Point3D>>& getControlPoints() const;
	//void connectToUI(ComboBoxBezierCurveC0 *comboBox, ListWidgetObjects *listWidget, Scene *scene, ListWidgetParameters *listWidgetParams) const;

private:
	//float calculateDistanceBetweenPoints(std::shared_ptr<DrawableObject> &point1, std::shared_ptr<DrawableObject> &point2);
	//QVector4D getBezierPointCubic(const std::shared_ptr<Point3D>& p0, const std::shared_ptr<Point3D>& p1, const std::shared_ptr<Point3D>& p2, const std::shared_ptr<Point3D>& p3, float t);
	QList<std::shared_ptr<Point3D>> m_controlPoints;
	std::unique_ptr<Curve> m_curveQuadratic;
	std::unique_ptr<Curve> m_curveCubic;
	//UiBezierCurveC0 m_uiBCC0;
	float m_width = 800;
	float m_height = 600;
	bool m_showPolyline;

	void createVertices() override;
	void generateIndices() override;
	void addControlPoint(int pointId);
	void removeControlPoint(const std::shared_ptr<DrawableObject> &point);
	void removeControlPoint(int pointId);
};
