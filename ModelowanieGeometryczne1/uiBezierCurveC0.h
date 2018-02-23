#pragma once
#include <QObject>
#include "listwidgetobjects.h"
#include "comboboxBezierCurveC0.h"
#include "listwidgetparameters.h"
#include <memory>

class Scene;
class BezierCurveC0;
class Point3D;
class UiBezierCurveC0 : public QObject
{
	Q_OBJECT
public:
	explicit UiBezierCurveC0(BezierCurveC0 &BC0);
	void connectToUi(ComboBoxBezierCurveC0 *comboBox, ListWidgetObjects *listWidget, Scene *scene, ListWidgetParameters *listWidgetParams) const;
	void deleteCurve();

private:
	QList<int> m_pointsIds;
	BezierCurveC0 &m_BC0;

signals:
	void pointAdded(int id);
	void pointRemoved(int id);
	void nameChanged(int id, const QString &name);
	void requestedPointsIds(const QList<std::shared_ptr<Point3D>> &points);
	void curveDeleted(int curveId);

public slots:
	void addPoint(int id);
	void removePoint(int id);
	void changeName(const QString &name, int id);
	void updateCurve() const;
	void updateScreenSize(float width, float height);
	void getPointsIds(int curveId);
};