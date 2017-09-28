#include "uiBezierCurveC0.h"
#include "bezierCurveC0.h"
#include "Scene.h"

UiBezierCurveC0::UiBezierCurveC0(BezierCurveC0 &BC0) :m_BC0(BC0)
{
}

void UiBezierCurveC0::addPoint(int id)
{
	m_pointsIds.append(id);
	emit pointAdded(id);
}

void UiBezierCurveC0::removePoint(int id)
{
	for (int i=0; i<m_pointsIds.count(); ++i)
	{
		if (m_pointsIds.at(i) == id)
		{
			m_pointsIds.removeAt(i);
			emit pointRemoved(id);
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
void UiBezierCurveC0::connectToUi(ComboBoxBezierCurveC0 *comboBox, ListWidgetObjects *listWidget, Scene *scene) const
{
	QObject::connect(listWidget, &ListWidgetObjects::changeItemTextEvent, this, &UiBezierCurveC0::changeName);
	QObject::connect(this, &UiBezierCurveC0::nameChanged, comboBox, &ComboBoxBezierCurveC0::changeItemText);
	QObject::connect(scene, &Scene::update, this, &UiBezierCurveC0::updateCurve);

	//QObject::connect(&m_uiBCC0, &UiBezierCurveC0::pointAdded, widget, &ListWidgetParameters::pointAddedToBC0);
	//QObject::connect(&m_uiBCC0, &UiBezierCurveC0::pointRemoved, widget, &ListWidgetParameters::pointRemovedFromBC0);
}