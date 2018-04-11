#include "uiBezierCurveC0.h"
#include "bezierCurveC0.h"
#include "Scene.h"
#include "ui_modelowaniegeometryczne1.h"

//UiBezierCurveC0::UiBezierCurveC0(BezierCurveC0 &BC0) : m_BC0(BC0)
UiBezierCurveC0::UiBezierCurveC0(std::shared_ptr<BezierCurveC0> BC0) : m_BC0(BC0), m_checkBoxPolyline(new QCheckBox("Show Polyline"))
{
}

UiBezierCurveC0::~UiBezierCurveC0()
{
	delete m_checkBoxPolyline;
}

void UiBezierCurveC0::connectToUi(const Ui_ModelowanieGeometryczne1Class* ui) const
{
	QObject::connect(ui->listWidget_ObjectsList, &ListWidgetObjects::changeItemTextEvent, this, &UiBezierCurveC0::changeName);
	QObject::connect(this, &UiBezierCurveC0::nameChanged, ui->comboBox_BezierCurveC0, &ComboBoxBezierCurveC0::changeItemText);
	QObject::connect(ui->comboBox_BezierCurveC0, &ComboBoxBezierCurveC0::itemSelected, this, &UiBezierCurveC0::getPointsIds);
	QObject::connect(this, &UiBezierCurveC0::requestedPoints, ui->listWidget_BC0Parameters, &ListWidgetParameters::displayPoints);
	QObject::connect(this, &UiBezierCurveC0::curveDeleted, ui->comboBox_BezierCurveC0, &ComboBoxBezierCurveC0::deleteItem);
	QObject::connect(ui->listWidget_BC0Parameters, &ListWidgetParameters::removedItem, this, &UiBezierCurveC0::removePoint);
	//QObject::connect(this, &UiBezierCurveC0::removePoint, ui->myGLWidget, &MyGLWidget::updateGL);

	QObject::connect(m_checkBoxPolyline, &QCheckBox::stateChanged, this, &UiBezierCurveC0::changePolylineState);
	QObject::connect(m_checkBoxPolyline, &QCheckBox::stateChanged, ui->myGLWidget, &MyGLWidget::updateGL);
	ui->verticalLayout_BC0->addWidget(m_checkBoxPolyline);
}

std::shared_ptr<DrawableObject> UiBezierCurveC0::getObject()
{
	return m_BC0;
}

void UiBezierCurveC0::connectToScene(const Scene* scene) const
{
	QObject::connect(scene, &Scene::update, this, &UiBezierCurveC0::updateCurve);
}

//TODO: connect with ui
void UiBezierCurveC0::addPoint(int pointId, int curveId)
{
	if (curveId != m_BC0->getId())
		return;
	//m_pointsIds.append(pointId);
	emit pointAdded(pointId);
}

void UiBezierCurveC0::removePoint(int pointId, int curveId)
{
	if (curveId != m_BC0->getId())
		return;
	//m_pointsIds = m_BC0->getControlPointIds();
	
	for (int i = 0; i < m_BC0->m_controlPoints.count(); ++i)
	{
		if (m_BC0->m_controlPoints.at(i)->getId() == pointId)
		{
			m_BC0->m_controlPoints.removeAt(i);
			//emit pointRemoved(i);
			return;
		}
	}
}

void UiBezierCurveC0::changeName(const QString &name, int id)
{
	if (id != m_BC0->getId())
		return;
	m_BC0->setName(name);
	emit nameChanged(m_BC0->getId(), name);
}

void UiBezierCurveC0::updateCurve() const
{
	m_BC0->createVertices();
	m_BC0->generateIndices();
}

void UiBezierCurveC0::updateScreenSize(float width, float height)
{
	m_BC0->m_width = width;
	m_BC0->m_height = height;
}

void UiBezierCurveC0::getPointsIds(int curveId)
{
	if (curveId == m_BC0->getId())
	{
		emit requestedPoints(m_BC0->getControlPoints());
	}
}

void UiBezierCurveC0::changePolylineState(int state)
{
	m_BC0->m_showPolyline = state;
}

void UiBezierCurveC0::deleteCurve()
{
	emit curveDeleted(m_BC0->getId());
}

//void UiBezierCurveC0::connectToUi(ComboBoxBezierCurveC0 *comboBox, ListWidgetObjects *listWidget, Scene *scene, ListWidgetParameters *listWidgetParams) const
//{
//	QObject::connect(listWidget, &ListWidgetObjects::changeItemTextEvent, this, &UiBezierCurveC0::changeName);
//	//QObject::connect(listWidget, &ListWidgetObjects::removeItemEvent, this, &UiBezierCurveC0::deleteCurve);
//	QObject::connect(this, &UiBezierCurveC0::nameChanged, comboBox, &ComboBoxBezierCurveC0::changeItemText);
//	QObject::connect(scene, &Scene::update, this, &UiBezierCurveC0::updateCurve);
//	QObject::connect(comboBox, &ComboBoxBezierCurveC0::itemSelected, this, &UiBezierCurveC0::getPointsIds);
//	QObject::connect(this, &UiBezierCurveC0::requestedPointsIds, listWidgetParams, &ListWidgetParameters::displayPoints);
//	QObject::connect(this, &UiBezierCurveC0::curveDeleted, comboBox, &ComboBoxBezierCurveC0::deleteItem);
//	//QObject::connect(this, &UiBezierCurveC0::nameChanged, listWidgetParams, &ListWidgetParameters::updatePointName);
//	//QObject::connect(this, &UiBezierCurveC0::pointAdded, listWidgetParams, &ListWidgetParameters::pointAddedToBC0);
//
//
//	//QObject::connect(&m_uiBCC0, &UiBezierCurveC0::pointRemoved, widget, &ListWidgetParameters::pointRemovedFromBC0);
//}
