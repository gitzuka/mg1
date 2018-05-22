#include "uiBezierCurveC2.h"
#include "bezierCurveC2.h"
#include "scene.h"
#include "ui_modelowaniegeometryczne1.h"

UiBezierCurveC2::UiBezierCurveC2(std::shared_ptr<BezierCurveC2> BC2) : m_BC2(BC2), m_checkBoxPolyline(new QCheckBox("Show Polyline")),
	m_checkBox_deBoor(new QCheckBox("B-Spline basis"))
{
}

UiBezierCurveC2::~UiBezierCurveC2()
{
	m_BC2->assignPrevCPIds();
	emit bezierCurve2Destroyed(m_BC2->getPrevControlPointsIds());
	delete m_checkBoxPolyline;
	delete m_checkBox_deBoor;
}

void UiBezierCurveC2::connectToUi(const Ui_ModelowanieGeometryczne1Class* ui) const
{
	QObject::connect(ui->listWidget_ObjectsList, &ListWidgetMain::changeItemTextEvent, this, &UiBezierCurveC2::changeName);
	QObject::connect(this, &UiBezierCurveC2::nameChanged, ui->comboBox_BC2, &ComboBoxBezierCurveC0::changeItemText);
	QObject::connect(ui->comboBox_BC2, &ComboBoxBezierCurveC0::itemSelected, this, &UiBezierCurveC2::getPointsIds);
	QObject::connect(this, &UiBezierCurveC2::requestedPoints, ui->listWidget_BC2, &ListWidgetBC2::displayPoints);
	QObject::connect(this, &UiBezierCurveC2::curveDeleted, ui->comboBox_BC2, &ComboBoxBezierCurveC0::deleteItem);
	QObject::connect(ui->listWidget_BC2, &ListWidgetBC2::removedItem, this, &UiBezierCurveC2::removePoint);
	QObject::connect(this, &UiBezierCurveC2::pointAdded, ui->listWidget_BC2, &ListWidgetBC2::pointAddedToBC2);

	QObject::connect(m_checkBoxPolyline, &QCheckBox::stateChanged, this, &UiBezierCurveC2::changePolylineState);
	QObject::connect(m_checkBoxPolyline, &QCheckBox::stateChanged, ui->myGLWidget, &MyGLWidget::updateGL);
	QObject::connect(m_checkBox_deBoor, &QCheckBox::stateChanged, this, &UiBezierCurveC2::changeBasis);
}

std::shared_ptr<DrawableObject> UiBezierCurveC2::getObject()
{
	return m_BC2;
}

void UiBezierCurveC2::connectToScene(const Scene* scene) const
{
	QObject::connect(scene, &Scene::update, this, &UiBezierCurveC2::updateCurve);
	QObject::connect(this, &UiBezierCurveC2::addedControlPoints, scene, &Scene::updateControlPoints);
	QObject::connect(this, &UiBezierCurveC2::bezierCurve2Destroyed, scene, &Scene::removeUiConnectors);
}

void UiBezierCurveC2::deleteCurve()
{
	emit curveDeleted(m_BC2->getId());
}

QCheckBox* UiBezierCurveC2::getCBPolyline() const
{
	return m_checkBoxPolyline;
}

QCheckBox* UiBezierCurveC2::getCBDeBoor() const
{
	return m_checkBox_deBoor;
}

void UiBezierCurveC2::assignAncestorControlPoints()
{
	std::vector<std::shared_ptr<Point3D>> vec = m_BC2->getControlPoints();
	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		it->get()->setAncestor(m_BC2);
	}
}

void UiBezierCurveC2::addPoint(const std::shared_ptr<DrawableObject>& point, int curveId)
{
	if (curveId != m_BC2->getId())
		return;
	if (m_BC2->addDeBoorPoint(point))
	{
		emit pointAdded(point->getId(), point->getName());
		emit addedControlPoints(m_BC2->getControlPoints(), m_BC2->getPrevControlPointsIds());
		assignAncestorControlPoints();
	}
}

void UiBezierCurveC2::assignPoints(const std::vector<std::shared_ptr<DrawableObject>>& points, int curveId)
{
	if (curveId != m_BC2->getId())
		return;
	if (m_BC2->assignDeBoorPoints(points))
	{
		for (int i = 0; i < points.size(); ++i)
		{
			emit pointAdded(points.at(i)->getId(), points.at(i)->getName());
		}
		emit addedControlPoints(m_BC2->getControlPoints(), m_BC2->getPrevControlPointsIds());
		assignAncestorControlPoints();

	}
}

void UiBezierCurveC2::removePoint(int pointId, int curveId)
{
	if (curveId != m_BC2->getId())
		return;

	for (int i = 0; i < m_BC2->m_deBoorPoints.count(); ++i)
	{
		if (m_BC2->m_deBoorPoints.at(i)->getId() == pointId)
		{
			m_BC2->m_deBoorPoints.removeAt(i);
			emit addedControlPoints(m_BC2->getControlPoints(), m_BC2->getPrevControlPointsIds());
			assignAncestorControlPoints();
			return;
		}
	}
}

void UiBezierCurveC2::changeName(const QString& name, int id)
{
	if (id != m_BC2->getId())
		return;
	m_BC2->setName(name);
	emit nameChanged(m_BC2->getId(), name);
}

void UiBezierCurveC2::updateCurve() const
{
	if (!m_BC2->m_bSplineBasis)
	{
		m_BC2->translateCotrolPoints();
	}
	m_BC2->createVertices();
	m_BC2->generateIndices();
}

void UiBezierCurveC2::updateScreenSize(float width, float height)
{
	m_BC2->m_width = width;
	m_BC2->m_height = height;
}

void UiBezierCurveC2::getPointsIds(int curveId)
{
	if (curveId == m_BC2->getId())
	{
		emit requestedPoints(m_BC2->getDeBoorPoints());
	}
}

void UiBezierCurveC2::changeBasis(int state)
{
	m_BC2->changeBasis(state);
}

void UiBezierCurveC2::changePolylineState(int state)
{
	m_BC2->m_showPolyline = state;
}
