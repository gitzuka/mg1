#include "listWidgetBC2.h"
#include "Point3d.h"

ListWidgetBC2::ListWidgetBC2(QWidget* parent) : QListWidget(parent), m_curveId(-1)
{
}

ListWidgetBC2::~ListWidgetBC2()
{
	this->clear();
}

void ListWidgetBC2::mousePressEvent(QMouseEvent* event)
{
	if (event->button() == Qt::RightButton)
	{
		QListWidgetItem *item = this->itemAt(event->pos());
		if (item == nullptr)
		{
			return;
		}
		createObjectMenu(this->mapToGlobal(event->pos()), item);
	}
	else
	{
		QListWidget::mousePressEvent(event);
	}
}

void ListWidgetBC2::createObjectMenu(const QPoint &pos, QListWidgetItem * item)
{
	QMenu myMenu;
	QAction *removePoint = myMenu.addAction("Remove point");
	connect(removePoint, &QAction::triggered, this, [this, item]()
	{
		removeItem(item);
	});
	myMenu.exec(pos);
}

void ListWidgetBC2::removeItem(QListWidgetItem * item)
{
	emit removedItem(m_points.at(this->row(item)).second, m_curveId);
	m_points.removeAt(this->row(item));
	this->removeItemWidget(item);
	delete item;
}

void ListWidgetBC2::displayPoints(const QList<std::shared_ptr<Point3D>>& points)
{
	this->clear();
	m_points.clear();
	for (int i = 0; i < points.size(); ++i)
	{
		this->addItem(points.at(i)->getName());
		m_points.append(qMakePair(this->item(this->count() - 1), points.at(i)->getId()));
	}
}

void ListWidgetBC2::pointAddedToBC2(int id, const QString & name)
{
	this->addItem(name);
	m_points.append(qMakePair(this->item(this->count() - 1), id));
}

void ListWidgetBC2::updatePointName(int id, const QString & name)
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

void ListWidgetBC2::updateCurveId(int id)
{
	m_curveId = id;
}

void ListWidgetBC2::highlightItem(int objectId)
{
	for (int i = 0; i < m_points.count(); ++i)
	{
		if (m_points.at(i).second == objectId)
		{
			this->setCurrentItem(m_points.at(i).first);
			return;
		}
	}
}
