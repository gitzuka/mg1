#pragma once
#include <QObject>
#include "listwidgetparameters.h"

class Point3D;
class UiPoint3D : public QObject
{
	Q_OBJECT

public:
	UiPoint3D(Point3D &point);

	void connect(ListWidgetParameters *listWidget);


public slots:
	void changeName(QString name);

private:
	Point3D &m_point3d;

signals:
	void nameChanged(QString name);
};