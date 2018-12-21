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
	void setParametrization(std::vector<QVector4D> &parametrization);
	const std::vector<QVector4D>& getParametrization() const;
	void upgradeToInterpolating();
	void rotate(QVector3D eulerAngles) override;

private:
	void createVertices() override;
	void generateIndices() override;
	float3 swapColors(int i) const;
	std::vector<QVector4D> m_parametrization;
	std::vector<float> calculateDistances(const std::vector<QVector4D> &controlPoints) const;
	std::vector<QVector3D> computeBCoeff(const std::vector<QVector3D> &c, const std::vector<QVector3D> &d, const std::vector<float> &distances, const std::vector<QVector4D> &controlPoints) const;
	void initializeMatrixData(std::vector<float>& upperDiag, std::vector<float>& middleDiag,
	                          std::vector<float>& lowerDiag, std::vector<QVector3D>& rhsVec,
	                          const std::vector<float>& distances, const std::vector<QVector4D>& controlPoints) const;
	
	void getCubicCurve(const std::vector<QVector4D> &points);
};
