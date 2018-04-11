#include "uiPoint3d.h"
#include "point3d.h"
#include "ui_modelowaniegeometryczne1.h"

UiPoint3D::UiPoint3D(std::shared_ptr<Point3D> point) : m_point3d(point)
{
}

void UiPoint3D::connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const
{
	QObject::connect(ui->listWidget_ObjectsList , &ListWidgetObjects::changeItemTextEvent, this, &UiPoint3D::changeName);
	QObject::connect(this, &UiPoint3D::nameChanged, ui->listWidget_BC0Parameters, &ListWidgetParameters::updatePointName);
}

std::shared_ptr<DrawableObject> UiPoint3D::getObject()
{
	return m_point3d;
}

void UiPoint3D::changeName(const QString &name, int id)
{
	if (id != m_point3d->getId())
		return;
	m_point3d->setName(name);
	emit nameChanged(m_point3d->getId(), name);
}

//void UiPoint3D::removePoint(int pointId)
//{
//	//m_point3d->
//}

//void UiPoint3D::connect(ListWidgetParameters *listWidgetParams, ListWidgetObjects *listWidgetObj) const
//{
//	QObject::connect(listWidgetObj, &ListWidgetObjects::changeItemTextEvent, this, &UiPoint3D::changeName);
//	QObject::connect(this, &UiPoint3D::nameChanged, listWidgetParams, &ListWidgetParameters::updatePointName);
//}
