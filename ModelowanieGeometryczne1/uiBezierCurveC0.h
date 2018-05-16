#pragma once
#include <memory>
#include "uiConnector.h"

class Scene;
class BezierCurveC0;
class Point3D;

class UiBezierCurveC0 : public UiConnector
{
	Q_OBJECT
public:
	explicit UiBezierCurveC0(std::shared_ptr<BezierCurveC0> BC0);
	~UiBezierCurveC0();
	void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const override;
	std::shared_ptr<DrawableObject> getObject() override;
	void connectToScene(const Scene *scene) const;
	void deleteCurve();
	QCheckBox* getCBPolyline() const;

private:
	std::shared_ptr<BezierCurveC0> m_BC0;
	QCheckBox *m_checkBoxPolyline;

signals:
	void pointAdded(int id, const QString &name);
	void nameChanged(int id, const QString &name);
	void requestedPoints(const QList<std::shared_ptr<Point3D>> &points);
	void curveDeleted(int curveId);

public slots:
	void addPoint(const std::shared_ptr<DrawableObject> &point, int curveId);
	void assignPoints(const std::vector<std::shared_ptr<DrawableObject>> &points, int curveId);
	void removePoint(int pointId, int curveId);
	void changeName(const QString &name, int id) override;
	void updateCurve() const;
	void updateScreenSize(float width, float height);
	void getPointsIds(int curveId);

private slots:
	void changePolylineState(int state);
};