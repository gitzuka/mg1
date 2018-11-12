#include "uiBezierSurfaceC0.h"
#include "scene.h"
#include "ui_modelowaniegeometryczne1.h"

UiBezierSurfaceC0::UiBezierSurfaceC0(std::shared_ptr<BezierSurfaceC0> bezierSurfaceC0, bool loaded) : UiBezierSurface(bezierSurfaceC0, loaded),
	m_bezierSurfaceC0(bezierSurfaceC0)
{
}

UiBezierSurfaceC0::~UiBezierSurfaceC0()
{
	emit deletingSurface(m_bezierSurfaceC0->getPointsIds());
}

void UiBezierSurfaceC0::connectToUi(const Ui_ModelowanieGeometryczne1Class* ui) const
{
	QObject::connect(ui->listWidget_ObjectsList, &ListWidgetMain::changeItemTextEvent, this, &UiBezierSurfaceC0::changeName);
	QObject::connect(this, &UiBezierSurfaceC0::deletingSurface, ui->listWidget_ObjectsList, &ListWidgetMain::deleteSurfacePoints);
	QObject::connect(this, &UiBezierSurfaceC0::nameChanged, ui->comboBox_BSC0, &ComboBoxBezierSurface::changeItemText);
	QObject::connect(ui->comboBox_BSC0, &ComboBoxBezierSurface::itemSelected, this, &UiBezierSurface::getPoints);
	QObject::connect(this, &UiBezierSurfaceC0::requestedPoints, ui->listWidget_BSC0, &ListWidgetBezierSurface::displayPoints);
	QObject::connect(this, &UiBezierSurfaceC0::requestedPoints2, ui->listWidget_ObjectsList, &ListWidgetMain::addPoints);
	QObject::connect(this, &UiBezierSurfaceC0::surfaceDeleted, ui->comboBox_BSC0, &ComboBoxBezierSurface::deleteItem);
	emit requestedPoints2(m_bezierSurfaceC0->getPoints());
	QObject::connect(m_checkBoxBezierGrid, &QCheckBox::stateChanged, this, &UiBezierSurfaceC0::changeBezierGridState);
	QObject::connect(m_checkBoxBezierGrid, &QCheckBox::stateChanged, ui->myGLWidget, &MyGLWidget::updateGL);
	QObject::connect(m_checkBoxControlGrid, &QCheckBox::stateChanged, this, &UiBezierSurfaceC0::changeControlGridState);
	QObject::connect(m_checkBoxControlGrid, &QCheckBox::stateChanged, ui->myGLWidget, &MyGLWidget::updateGL);
}

void UiBezierSurfaceC0::connectToScene(const Scene* scene) const
{
	QObject::connect(this, &UiBezierSurfaceC0::deletingSurface, scene, &Scene::removeUiConnectors);
}
