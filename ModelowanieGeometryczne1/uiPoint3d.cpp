#include "uiPoint3d.h"
#include "point3d.h"

UiPoint3D::UiPoint3D(Point3D &point) : m_point3d(point)
{
}

void UiPoint3D::changeName(const QString &name, int id)
{
	if (id != m_point3d.getId())
		return;
	m_point3d.setName(name);
	emit nameChanged(m_point3d.getId(), name);
}

void UiPoint3D::connect(ListWidgetParameters *listWidgetParams, ListWidgetObjects *listWidgetObj) const
{
	QObject::connect(listWidgetObj, &ListWidgetObjects::changeItemTextEvent, this, &UiPoint3D::changeName);
	QObject::connect(this, &UiPoint3D::nameChanged, listWidgetParams, &ListWidgetParameters::updatePointName);
}
