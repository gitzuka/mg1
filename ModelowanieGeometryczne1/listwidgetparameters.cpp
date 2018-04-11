#include "listwidgetparameters.h"
#include "Point3D.h"

ListWidgetParameters::ListWidgetParameters(QWidget* parent)
	: QListWidget(parent), m_curveId(-1)
{
}

ListWidgetParameters::~ListWidgetParameters()
{
	this->clear();
}

void ListWidgetParameters::mousePressEvent(QMouseEvent * event)
{
	if (event->button() == Qt::RightButton)
	{
		QListWidgetItem *item = this->itemAt(event->pos());
		if (item == nullptr)
		{
			return;
		}
		createObjectMenu(this->mapToGlobal(event->pos()), item);
		//createObjectMenu(event->pos(), item->)
		//emit rightClick(this->mapToGlobal(event->pos()));
	}
	else
	{
		QListWidget::mousePressEvent(event);
	}
}

void ListWidgetParameters::createObjectMenu(const QPoint &pos, QListWidgetItem *item)
{
	QMenu myMenu;
	QAction *removePoint = myMenu.addAction("Remove point");
	connect(removePoint, &QAction::triggered, this, [this, item]()
	{
		removeItem(item);
	});
	myMenu.exec(pos);

}

void ListWidgetParameters::removeItem(QListWidgetItem *item)
{
	emit removedItem(m_points.at(this->row(item)).second, m_curveId);
	m_points.removeAt(this->row(item));
	this->removeItemWidget(item);
	delete item;
}

//void ListWidgetParameters::deleteItems()
//{
//	while (int i = this->count() > 0)
//	{
//		delete takeItem(0);
//
//	}
//}

void ListWidgetParameters::displayPoints(const QList<std::shared_ptr<Point3D>> &points)
{
	this->clear();
	//deleteItems();
	m_points.clear();
	for (int i = 0; i < points.size(); ++i)
	{
		this->addItem(points.at(i)->getName());
		m_points.append(qMakePair(this->item(this->count() - 1), points.at(i)->getId()));
	}
}

//TODO:: asdf
void ListWidgetParameters::pointAddedToBC0(int id)
{
	//this->addItem(point->getName());
}

//TODO: asdf
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

void ListWidgetParameters::updateCurveId(int id)
{
	m_curveId = id;
}


//void ListWidgetParameters::comboBox_BezierCurveC0DisplayPoints(int id)
//{
//	int i = 0;
//}