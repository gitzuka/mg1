#include "uiBezierC2Interpolated.h"
#include "bezierC2Interpolated.h"
#include "scene.h"
#include "ui_modelowaniegeometryczne1.h"

UiBezierC2Interpolated::UiBezierC2Interpolated(std::shared_ptr<BezierC2Interpolated> BC2Interpolated) : m_BC2Interpolated(BC2Interpolated),
m_checkBoxPolyline(new QCheckBox("Show Polyline"))
{
}

UiBezierC2Interpolated::~UiBezierC2Interpolated()
{
	delete m_checkBoxPolyline;
}

void UiBezierC2Interpolated::connectToUi(const Ui_ModelowanieGeometryczne1Class* ui) const
{
	QObject::connect(ui->listWidget_ObjectsList, &ListWidgetMain::changeItemTextEvent, this, &UiBezierC2Interpolated::changeName);
	QObject::connect(this, &UiBezierC2Interpolated::nameChanged, ui->comboBox_BC2Int, &ComboBoxBezierCurveC0::changeItemText);
	QObject::connect(ui->comboBox_BC2Int, &ComboBoxBezierCurveC0::itemSelected, this, &UiBezierC2Interpolated::getPointsIds);
	QObject::connect(this, &UiBezierC2Interpolated::requestedPoints, ui->listWidget_BC2Int, &ListWidgetBC0::displayPoints);
	QObject::connect(this, &UiBezierC2Interpolated::curveDeleted, ui->comboBox_BC2Int, &ComboBoxBezierCurveC0::deleteItem);
	QObject::connect(ui->listWidget_BC2Int, &ListWidgetBC0::removedItem, this, &UiBezierC2Interpolated::removePoint);
	QObject::connect(this, &UiBezierC2Interpolated::pointAdded, ui->listWidget_BC2Int, &ListWidgetBC0::pointAddedToBC0);

	QObject::connect(m_checkBoxPolyline, &QCheckBox::stateChanged, this, &UiBezierC2Interpolated::changePolylineState);
	QObject::connect(m_checkBoxPolyline, &QCheckBox::stateChanged, ui->myGLWidget, &MyGLWidget::updateGL);
}

std::shared_ptr<DrawableObject> UiBezierC2Interpolated::getObject()
{
	return m_BC2Interpolated;
}

void UiBezierC2Interpolated::connectToScene(const Scene* scene) const
{
	QObject::connect(scene, &Scene::update, this, &UiBezierC2Interpolated::updateCurve);
}

void UiBezierC2Interpolated::addPoint(const std::shared_ptr<DrawableObject> &point, int curveId)
{
	if (curveId != m_BC2Interpolated->getId())
		return;
	if (m_BC2Interpolated->addControlPoint(point))
	{
		emit pointAdded(point->getId(), point->getName());
	}
}

void UiBezierC2Interpolated::assignPoints(const std::vector<std::shared_ptr<DrawableObject>>& points, int curveId)
{
	if (curveId != m_BC2Interpolated->getId())
		return;
	if (m_BC2Interpolated->assignControlPoints(points))
	{
		for (int i = 0; i < points.size(); ++i)
		{
			emit pointAdded(points.at(i)->getId(), points.at(i)->getName());
		}
	}
}

void UiBezierC2Interpolated::removePoint(int pointId, int curveId)
{
	if (curveId != m_BC2Interpolated->getId())
		return;

	for (int i = 0; i < m_BC2Interpolated->m_controlPoints.count(); ++i)
	{
		if (m_BC2Interpolated->m_controlPoints.at(i)->getId() == pointId)
		{
			m_BC2Interpolated->m_controlPoints.removeAt(i);
			return;
		}
	}
}

void UiBezierC2Interpolated::changeName(const QString &name, int id)
{
	if (id != m_BC2Interpolated->getId())
		return;
	m_BC2Interpolated->setName(name);
	emit nameChanged(m_BC2Interpolated->getId(), name);
}

void UiBezierC2Interpolated::updateCurve() const
{
	m_BC2Interpolated->createVertices();
	m_BC2Interpolated->generateIndices();
}

void UiBezierC2Interpolated::updateScreenSize(float width, float height)
{
	m_BC2Interpolated->m_width = width;
	m_BC2Interpolated->m_height = height;
}

void UiBezierC2Interpolated::getPointsIds(int curveId)
{
	if (curveId == m_BC2Interpolated->getId())
	{
		emit requestedPoints(m_BC2Interpolated->getControlPoints());
	}
}

void UiBezierC2Interpolated::changePolylineState(int state)
{
	m_BC2Interpolated->m_showPolyline = state;
}

void UiBezierC2Interpolated::deleteCurve()
{
	emit curveDeleted(m_BC2Interpolated->getId());
}

QCheckBox* UiBezierC2Interpolated::getCBPolyline() const
{
	return m_checkBoxPolyline;
}
