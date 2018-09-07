#include "uiBezierSurfaceC2.h"
#include "scene.h"
#include "ui_modelowaniegeometryczne1.h"

UiBezierSurfaceC2::UiBezierSurfaceC2(std::shared_ptr<BezierSurfaceC2> bezierSurfaceC2) : UiBezierSurface(bezierSurfaceC2),
	m_bezierSurfaceC2(bezierSurfaceC2)
{
}

UiBezierSurfaceC2::~UiBezierSurfaceC2()
{
	emit deletingSurface(m_bezierSurfaceC2->getPointsIds());
}

void UiBezierSurfaceC2::connectToUi(const Ui_ModelowanieGeometryczne1Class* ui) const
{
	QObject::connect(ui->listWidget_ObjectsList, &ListWidgetMain::changeItemTextEvent, this, &UiBezierSurfaceC2::changeName);
	QObject::connect(this, &UiBezierSurfaceC2::deletingSurface, ui->listWidget_ObjectsList, &ListWidgetMain::deleteSurfacePoints);
	QObject::connect(this, &UiBezierSurfaceC2::nameChanged, ui->comboBox_BSC2, &ComboBoxBezierSurface::changeItemText);
	QObject::connect(ui->comboBox_BSC2, &ComboBoxBezierSurface::itemSelected, this, &UiBezierSurface::getPoints);
	QObject::connect(this, &UiBezierSurfaceC2::requestedPoints, ui->listWidget_BSC2, &ListWidgetBezierSurface::displayPoints);
	QObject::connect(this, &UiBezierSurfaceC2::requestedPoints2, ui->listWidget_ObjectsList, &ListWidgetMain::addPoints);
	QObject::connect(this, &UiBezierSurfaceC2::surfaceDeleted, ui->comboBox_BSC2, &ComboBoxBezierSurface::deleteItem);
	emit requestedPoints2(m_bezierSurfaceC2->getPoints());
	QObject::connect(m_checkBoxBezierGrid, &QCheckBox::stateChanged, this, &UiBezierSurfaceC2::changeBezierGridState);
	QObject::connect(m_checkBoxBezierGrid, &QCheckBox::stateChanged, ui->myGLWidget, &MyGLWidget::updateGL);
	QObject::connect(m_checkBoxControlGrid, &QCheckBox::stateChanged, this, &UiBezierSurfaceC2::changeControlGridState);
	QObject::connect(m_checkBoxControlGrid, &QCheckBox::stateChanged, ui->myGLWidget, &MyGLWidget::updateGL);
}

void UiBezierSurfaceC2::connectToScene(const Scene* scene) const
{
	QObject::connect(this, &UiBezierSurfaceC2::deletingSurface, scene, &Scene::removeUiConnectors);

}
