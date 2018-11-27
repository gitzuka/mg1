#pragma once
#include "drawableObject.h"
#include <memory>

class Point3D;
class BezierC2Interpolated : public DrawableObject
{
public:
	BezierC2Interpolated(ObjectType type, QString name);
	~BezierC2Interpolated();

	friend class UiBezierC2Interpolated;
	friend class TrimmingCurve;

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;

	QList<int> getControlPointIds() const;
	const QList<std::shared_ptr<Point3D>>& getControlPoints() const;

private:
	QList<std::shared_ptr<Point3D>> m_controlPoints;
	bool m_showPolyline;
	float m_width = 800;
	float m_height = 600;

	void createVertices() override;
	void generateIndices() override;
	std::vector<float> calculateDistances() const;
	std::vector<QVector3D> computeDCoeff(const std::vector<QVector3D> &c, const std::vector<float> &distances) const;
	std::vector<QVector3D> computeBCoeff(const std::vector<QVector3D> &c, const std::vector<QVector3D> &d, const std::vector<float> &distances) const;
	std::vector<QVector3D> computeMatrix(const std::vector<float> &upperDiag, const std::vector<float> &middleDiag, const std::vector<float> &lowerDiag, const std::vector<QVector3D> &rhsVec) const;
	void initializeMatrixData(std::vector<float> &upperDiag, std::vector<float> &middleDiag, std::vector<float> &lowerDiag, std::vector<QVector3D> &rhsVec, const std::vector<float> &distances) const;
	void convertPowerToBernstein(QVector3D a, QVector3D b, QVector3D c, QVector3D d, std::vector<QVector4D> &out);
	void getCubicCurve(const std::vector<QVector4D> &points);
	bool addControlPoint(const std::shared_ptr<DrawableObject> &point);
	bool assignControlPoints(const std::vector<std::shared_ptr<DrawableObject>> &points);
	void removeControlPoint(const std::shared_ptr<DrawableObject> &point);
	void removeControlPoint(int pointId);
};
