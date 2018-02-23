#include "uiBezierCurveC0.h"
#include "bezierCurveC0.h"
#include "Scene.h"

UiBezierCurveC0::UiBezierCurveC0(BezierCurveC0 &BC0) : m_BC0(BC0)
{
}

void UiBezierCurveC0::addPoint(int id)
{
	m_pointsIds.append(id);
	emit pointAdded(id);
}

void UiBezierCurveC0::removePoint(int id)
{
	for (int i = 0; i < m_pointsIds.count(); ++i)
	{
		if (m_pointsIds.at(i) == id)
		{
			m_pointsIds.removeAt(i);
			emit pointRemoved(i);
			return;
		}
	}
}

void UiBezierCurveC0::changeName(const QString &name, int id)
{
	if (id != m_BC0.getId())
		return;
	m_BC0.setName(name);
	emit nameChanged(m_BC0.getId(), name);
}

void UiBezierCurveC0::updateCurve() const
{
	m_BC0.createVertices();
	m_BC0.generateIndices();
}

void UiBezierCurveC0::updateScreenSize(float width, float height)
{
	m_BC0.m_width = width;
	m_BC0.m_height = height;
}

void UiBezierCurveC0::getPointsIds(int curveId)
{
	if (curveId == m_BC0.getId())
	{
		emit requestedPointsIds(m_BC0.getControlPoints());
	}
}

void UiBezierCurveC0::deleteCurve()
{
	emit curveDeleted(m_BC0.getId());
}

void UiBezierCurveC0::connectToUi(ComboBoxBezierCurveC0 *comboBox, ListWidgetObjects *listWidget, Scene *scene, ListWidgetParameters *listWidgetParams) const
{
	QObject::connect(listWidget, &ListWidgetObjects::changeItemTextEvent, this, &UiBezierCurveC0::changeName);
	//QObject::connect(listWidget, &ListWidgetObjects::removeItemEvent, this, &UiBezierCurveC0::deleteCurve);
	QObject::connect(this, &UiBezierCurveC0::nameChanged, comboBox, &ComboBoxBezierCurveC0::changeItemText);
	QObject::connect(scene, &Scene::update, this, &UiBezierCurveC0::updateCurve);
	QObject::connect(comboBox, &ComboBoxBezierCurveC0::itemSelected, this, &UiBezierCurveC0::getPointsIds);
	QObject::connect(this, &UiBezierCurveC0::requestedPointsIds, listWidgetParams, &ListWidgetParameters::displayPoints);
	QObject::connect(this, &UiBezierCurveC0::curveDeleted, comboBox, &ComboBoxBezierCurveC0::deleteItem);
	//QObject::connect(this, &UiBezierCurveC0::nameChanged, listWidgetParams, &ListWidgetParameters::updatePointName);
	//QObject::connect(this, &UiBezierCurveC0::pointAdded, listWidgetParams, &ListWidgetParameters::pointAddedToBC0);


	//QObject::connect(&m_uiBCC0, &UiBezierCurveC0::pointRemoved, widget, &ListWidgetParameters::pointRemovedFromBC0);
}
