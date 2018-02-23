#pragma once
#include <QObject>
#include "listwidgetparameters.h"
#include "listwidgetobjects.h"

class Point3D;
class UiPoint3D : public QObject
{
	Q_OBJECT

public:
	UiPoint3D(Point3D &point);

	void connect(ListWidgetParameters *listWidget, ListWidgetObjects *listWidgetObj) const;

public slots:
	void changeName(const QString &name, int id);

private:
	Point3D &m_point3d;

signals:
	void nameChanged(int id, const QString &name);
};