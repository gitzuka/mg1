#pragma once
#include "point3d.h"
#include "curveCubic.h"
#include "uiBezierCurveC2.h"
#include <memory>

class BezierCurveC2 : public DrawableObject
{
public:
	BezierCurveC2(ObjectType type, QString name);
	~BezierCurveC2();

	friend class UiBezierCurveC2;

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	QVector4D getPosition() const override;

	QList<int> getDeBoorPointIds() const;
	const QList<std::shared_ptr<Point3D>>& getDeBoorPoints() const;
	std::vector<std::shared_ptr<Point3D>> getControlPoints() const;
	const std::vector<int>& getPrevControlPointsIds() const;
	void pointMoved(int id);

private:
	QList<std::shared_ptr<Point3D>> m_deBoorPoints;
	std::vector<std::shared_ptr<Point3D>> m_controlPoints;
	std::vector<int> m_prevControlPointsIds;
	float m_width = 800;
	float m_height = 600;
	bool m_showPolyline;
	bool m_bSplineBasis;

	void createVertices() override;
	void generateIndices() override;

	void generateControlPoints();
	void assignPrevCPIds();
	bool addDeBoorPoint(const std::shared_ptr<DrawableObject> &point);
	bool assignDeBoorPoints(const std::vector<std::shared_ptr<DrawableObject>> &points);
	void removeDeBoorPoint(const std::shared_ptr<DrawableObject> &point);
	void removeDeBoorPoint(int pointId);
	void translateDeBoors(const std::shared_ptr<DrawableObject> &point, int controlPointIndex, int deBoorIndex);
	void translateCotrolPoints();
	int getDeBoorToTranslate(const std::shared_ptr<DrawableObject>& point);
	void changeBasis(bool deBoor);
};


