#pragma once
#include <memory>
#include "uiConnector.h"

class Scene;
class BezierCurveC2;
class Point3D;

class UiBezierCurveC2 : public UiConnector
{
	Q_OBJECT
public:
	explicit UiBezierCurveC2(std::shared_ptr<BezierCurveC2> BC0);
	~UiBezierCurveC2();
	void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const override;
	std::shared_ptr<DrawableObject> getObject() override;
	void connectToScene(const Scene *scene) const;
	void deleteCurve();
	QCheckBox* getCBPolyline() const;
	QCheckBox* getCBDeBoor() const;

private:
	std::shared_ptr<BezierCurveC2> m_BC2;
	QCheckBox *m_checkBoxPolyline;
	QCheckBox *m_checkBox_deBoor;

	void assignAncestorControlPoints();

signals:
	void pointAdded(int id, const QString &name);
	void nameChanged(int id, const QString &name);
	void requestedPoints(const QList<std::shared_ptr<Point3D>> &points);
	void curveDeleted(int curveId);
	void addedControlPoints(std::vector<std::shared_ptr<Point3D>> controlPoints, const std::vector<int> &prevControlPoints);
	void bezierCurve2Destroyed(const std::vector<int> &controlPointsIds);

public slots:
	void assignPoints(const std::vector<std::shared_ptr<DrawableObject>> &points, int curveId);
	void addPoint(const std::shared_ptr<DrawableObject> &point, int curveId);
	void removePoint(int pointId, int curveId);

private slots:
	void changePolylineState(int state);
	void changeName(const QString &name, int id) override;
	void updateCurve() const;
	void updateScreenSize(float width, float height);
	void getPointsIds(int curveId);
	void changeBasis(int state);
};