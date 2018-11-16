#include "listWidgetMain.h"
#include <QtGui>
#include "point3d.h"

ListWidgetMain::ListWidgetMain(QWidget* parent)
	: QListWidget(parent), m_activeItem(nullptr)
{
	connect(this, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(itemTextChanged(QListWidgetItem*)));
	connect(this, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClick(QListWidgetItem*)));
}


ListWidgetMain::~ListWidgetMain()
{
	this->clear();
}

void ListWidgetMain::mousePressEvent(QMouseEvent *event)
{
	if (event->button() == Qt::RightButton)
	{
		QListWidgetItem *item = this->itemAt(event->pos());
		if (item == nullptr)
		{
			return;
		}
		emit rightClick(this->mapToGlobal(event->pos()), m_selectedObjectsIds);
	}
	else
	{
		QListWidget::mousePressEvent(event);
	}
}

int ListWidgetMain::findItemId(QListWidgetItem *item) const
{
	int id = -1;
	for (int i = 0; i < m_objectsList.count(); ++i)
	{
		if (m_objectsList.at(i).first == item)
		{
			id = m_objectsList.at(i).second;
			break;
		}
	}
	return id;
}

void ListWidgetMain::updatePointsList(int id)
{
	for (int i = 0; i < m_selectedObjectsIds.count(); ++i)
	{
		if (m_selectedObjectsIds.at(i) == id)
		{
			m_selectedObjectsIds.removeAt(i);
			return;
		}
	}
	m_selectedObjectsIds.append(id);
}

void ListWidgetMain::addTorus(const QString &text, int objectId)
{
	addItem(text);
	m_objectsList.append(qMakePair(this->item(this->count() - 1), objectId));
	this->item(this->count() - 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void ListWidgetMain::addPoint3D(const QString& text, int objectId)
{
	addItem(text);
	m_objectsList.append(qMakePair(this->item(this->count() - 1), objectId));
	this->item(this->count() - 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void ListWidgetMain::addObject(const QString& text, int objectId)
{
	addItem(text);
	m_objectsList.append(qMakePair(this->item(this->count() - 1), objectId));
	this->item(this->count() - 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void ListWidgetMain::removeItem()
{
	if (this->currentRow() < 0)
	{
		return;
	}
	for (int i =0; i<m_undeleteable.count(); ++i)
	{
		if (m_objectsList.at(currentRow()).second == m_undeleteable.at(i))
		{
			return;
		}
	}
	emit removeItemEvent(m_objectsList.at(currentRow()).second);
	m_objectsList.removeAt(currentRow());
	QListWidgetItem *item = takeItem(currentRow());
	this->removeItemWidget(item);
	delete item;
}

void ListWidgetMain::highlightItem(int objectId)
{
	for (int i = 0; i < m_objectsList.count(); ++i)
	{
		if (m_objectsList.at(i).second == objectId)
		{
			this->setCurrentItem(m_objectsList.at(i).first);
			return;
		}
	}
}

void ListWidgetMain::highlightActiveItem(int objectId)
{
	for (int i = 0; i < m_objectsList.count(); ++i)
	{
		if (m_objectsList.at(i).second == objectId)
		{
			m_objectsList.at(i).first->setBackground(Qt::green);
			m_activeItem = m_objectsList.at(i).first;
			return;
		}
	}
}

void ListWidgetMain::removeHighlightActive()
{
	if (m_activeItem != nullptr)
	{
		m_activeItem->setBackground(Qt::white);
		m_activeItem = nullptr;
	}
}

void ListWidgetMain::deleteSurfacePoints(const std::vector<int> &pointsIds)
{
	int index = 0, index2 = 0;
	while (pointsIds.at(0) != m_undeleteable.at(index2))
	{
		++index2;
	}
	while (pointsIds.at(0) != m_objectsList.at(index).second)
	{
		++index;
	}
	for (int i = 0; i < pointsIds.size(); ++i)
	{
		m_undeleteable.removeAt(index2);
		m_objectsList.removeAt(index);
		QListWidgetItem *item = takeItem(index);
		this->removeItemWidget(item);
		delete item;
	}
}

void ListWidgetMain::addPoints(const std::vector<std::shared_ptr<Point3D>> &points)
{
	for (const auto &point : points)
	{
		m_undeleteable.append(point->getId());
		addItem(point->getName());
		m_objectsList.append(qMakePair(this->item(this->count() - 1), point->getId()));
		this->item(this->count() - 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	}
}

void ListWidgetMain::itemClick(QListWidgetItem *item)
{
	if (!(QGuiApplication::keyboardModifiers() & Qt::ControlModifier))
	{
		m_selectedObjectsIds.clear();
	}
	int id = m_objectsList.at(this->currentRow()).second;
	updatePointsList(id);
	emit itemSelected(m_selectedObjectsIds);
}

void ListWidgetMain::itemTextChanged(QListWidgetItem* item)
{
	emit changeItemTextEvent(item->text(), findItemId(item));
}

void ListWidgetMain::addBezierCurveC0(const QString &text, int objectId)
{
	addItem(text);
	m_objectsList.append(qMakePair(this->item(this->count() - 1), objectId));
	this->item(this->count() - 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void ListWidgetMain::addBezierCurveC2(const QString& text, int objectId)
{
	addItem(text);
	m_objectsList.append(qMakePair(this->item(this->count() - 1), objectId));
	this->item(this->count() - 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void ListWidgetMain::addBezierC2Interpolated(const QString& text, int objectId)
{
	addItem(text);
	m_objectsList.append(qMakePair(this->item(this->count() - 1), objectId));
	this->item(this->count() - 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}
