#include "listwidgetparameters.h"
#include "Point3D.h"

ListWidgetParameters::ListWidgetParameters(QWidget* parent)
	: QListWidget(parent)
{
}

ListWidgetParameters::~ListWidgetParameters()
{
}

void ListWidgetParameters::mousePressEvent(QMouseEvent * event)
{
}

void ListWidgetParameters::displayPoints(const QList<std::shared_ptr<Point3D>> &points)
{
	this->clear();
	m_points.clear();
	for (int i = 0; i < points.size(); ++i)
	{
		this->addItem(points.at(i)->getName());
		m_points.append(qMakePair(this->item(this->count() - 1), points.at(i)->getId()));
	}
}

void ListWidgetParameters::pointAddedToBC0(int id)
{
	//this->addItem(point->getName());
}

void ListWidgetParameters::pointRemovedFromBC0(int id)
{
	this->takeItem(id);
}

void ListWidgetParameters::updatePointName(int id, const QString &name)
{
	for (int i = 0; i < m_points.count(); ++i)
	{
		if (m_points.at(i).second == id)
		{
			this->item(i)->setText(name);
			return;
		}
	}
}

//void ListWidgetParameters::comboBox_BezierCurveC0DisplayPoints(int id)
//{
//	int i = 0;
//}