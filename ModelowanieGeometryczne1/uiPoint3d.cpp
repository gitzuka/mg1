#include "uiPoint3d.h"
#include "point3d.h"
#include "ui_modelowaniegeometryczne1.h"

UiPoint3D::UiPoint3D(std::shared_ptr<Point3D> point) : m_point3d(point)
{
}

void UiPoint3D::connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const
{
	QObject::connect(ui->listWidget_ObjectsList , &ListWidgetMain::changeItemTextEvent, this, &UiPoint3D::changeName);
	QObject::connect(this, &UiPoint3D::nameChanged, ui->listWidget_BC0Parameters, &ListWidgetBC0::updatePointName);
	QObject::connect(this, &UiPoint3D::nameChanged, ui->listWidget_BC2, &ListWidgetBC2::updatePointName);
	QObject::connect(this, &UiPoint3D::nameChanged, ui->listWidget_BC2Int, &ListWidgetBC0::updatePointName);
	QObject::connect(this, &UiPoint3D::nameChanged, ui->listWidget_BSC0, &ListWidgetBezierSurface::updatePointName);
	QObject::connect(this, &UiPoint3D::nameChanged, ui->listWidget_BSC2, &ListWidgetBezierSurface::updatePointName);
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
