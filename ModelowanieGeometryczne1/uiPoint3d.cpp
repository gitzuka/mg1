#include "uiPoint3d.h"
#include "point3d.h"

UiPoint3D::UiPoint3D(Point3D &point) : m_point3d(point)
{
}

void UiPoint3D::changeName(QString name)
{
	m_point3d.setName(name);
	emit nameChanged(name);
}

void UiPoint3D::connect(ListWidgetParameters *listWidget)
{
}
