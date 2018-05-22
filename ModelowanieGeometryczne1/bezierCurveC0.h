#pragma once
#include "point3d.h"
#include "curveCubic.h"
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
	
	QList<int> getControlPointIds() const;
	const QList<std::shared_ptr<Point3D>>& getControlPoints() const;

private:
	QList<std::shared_ptr<Point3D>> m_controlPoints;
	float m_width = 800;
	float m_height = 600;
	bool m_showPolyline;

	void createVertices() override;
	void generateIndices() override;
	bool addControlPoint(const std::shared_ptr<DrawableObject> &point);
	bool assignControlPoints(const std::vector<std::shared_ptr<DrawableObject>> &points);
	void removeControlPoint(const std::shared_ptr<DrawableObject> &point);
	void removeControlPoint(int pointId);
};
