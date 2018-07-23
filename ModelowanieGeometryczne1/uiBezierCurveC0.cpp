#include "uiBezierCurveC0.h"
#include "bezierCurveC0.h"
#include "scene.h"
#include "ui_modelowaniegeometryczne1.h"

UiBezierCurveC0::UiBezierCurveC0(std::shared_ptr<BezierCurveC0> BC0) : m_BC0(BC0), m_checkBoxPolyline(new QCheckBox("Show Polyline"))
{
}

UiBezierCurveC0::~UiBezierCurveC0()
{
	delete m_checkBoxPolyline;
}

void UiBezierCurveC0::connectToUi(const Ui_ModelowanieGeometryczne1Class* ui) const
{
	QObject::connect(ui->listWidget_ObjectsList, &ListWidgetMain::changeItemTextEvent, this, &UiBezierCurveC0::changeName);
	QObject::connect(this, &UiBezierCurveC0::nameChanged, ui->comboBox_BezierCurveC0, &ComboBoxBezierCurveC0::changeItemText);
	QObject::connect(ui->comboBox_BezierCurveC0, &ComboBoxBezierCurveC0::itemSelected, this, &UiBezierCurveC0::getPointsIds);
	QObject::connect(this, &UiBezierCurveC0::requestedPoints, ui->listWidget_BC0Parameters, &ListWidgetBC0::displayPoints);
	QObject::connect(this, &UiBezierCurveC0::curveDeleted, ui->comboBox_BezierCurveC0, &ComboBoxBezierCurveC0::deleteItem);
	QObject::connect(ui->listWidget_BC0Parameters, &ListWidgetBC0::removedItem, this, &UiBezierCurveC0::removePoint);
	QObject::connect(this, &UiBezierCurveC0::pointAdded, ui->listWidget_BC0Parameters, &ListWidgetBC0::pointAddedToBC0);

	QObject::connect(m_checkBoxPolyline, &QCheckBox::stateChanged, this, &UiBezierCurveC0::changePolylineState);
	QObject::connect(m_checkBoxPolyline, &QCheckBox::stateChanged, ui->myGLWidget, &MyGLWidget::updateGL);
}

std::shared_ptr<DrawableObject> UiBezierCurveC0::getObject()
{
	return m_BC0;
}

void UiBezierCurveC0::connectToScene(const Scene* scene) const
{
	QObject::connect(scene, &Scene::update, this, &UiBezierCurveC0::updateCurve);
}

void UiBezierCurveC0::addPoint(const std::shared_ptr<DrawableObject> &point, int curveId)
{
	if (curveId != m_BC0->getId())
		return;
	if (m_BC0->addControlPoint(point))
	{
		emit pointAdded(point->getId(), point->getName());
	}
}

void UiBezierCurveC0::assignPoints(const std::vector<std::shared_ptr<DrawableObject>>& points, int curveId)
{
	if (curveId != m_BC0->getId())
		return;
	if (m_BC0->assignControlPoints(points))
	{
		for (int i =0; i<points.size(); ++i)
		{
			emit pointAdded(points.at(i)->getId(), points.at(i)->getName());
		}
	}
}

void UiBezierCurveC0::removePoint(int pointId, int curveId)
{
	if (curveId != m_BC0->getId())
		return;
	
	for (int i = 0; i < m_BC0->m_controlPoints.count(); ++i)
	{
		if (m_BC0->m_controlPoints.at(i)->getId() == pointId)
		{
			m_BC0->m_controlPoints.removeAt(i);
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

QCheckBox* UiBezierCurveC0::getCBPolyline() const
{
	return m_checkBoxPolyline;
}
