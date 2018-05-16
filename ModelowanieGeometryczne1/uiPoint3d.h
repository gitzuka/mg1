#pragma once
//#include "point3d.h"
#include "uiConnector.h"
#include <memory>

class Point3D;
class UiPoint3D : public UiConnector
{
	Q_OBJECT

public:
	//UiPoint3D(Point3D &point);
	UiPoint3D(std::shared_ptr<Point3D> point);

	void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const override;
	std::shared_ptr<DrawableObject> getObject() override;
	//void connect(ListWidgetBC0 *listWidget, ListWidgetMain *listWidgetObj) const;

public slots:
	void changeName(const QString &name, int id) override;

//private slots:
//	void removePoint(int pointId);

private:
	std::shared_ptr<Point3D> m_point3d;

signals:
	void nameChanged(int id, const QString &name);
};