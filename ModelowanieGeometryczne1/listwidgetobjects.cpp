#include "listwidgetobjects.h"
#include <QtGui>
#include <QMenu>
#include "drawableObject.h"

ListWidgetObjects::ListWidgetObjects(QWidget* parent)
	: QListWidget(parent)
{
	connect(this, SIGNAL(itemChanged(QListWidgetItem*)), this, SLOT(itemTextChanged(QListWidgetItem*)));
	connect(this, SIGNAL(itemClicked(QListWidgetItem*)), this, SLOT(itemClick(QListWidgetItem*)));
}


ListWidgetObjects::~ListWidgetObjects()
{
}

void ListWidgetObjects::mousePressEvent(QMouseEvent *event)
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

int ListWidgetObjects::findItemId(QListWidgetItem *item) const
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

void ListWidgetObjects::updatePointsList(int id)
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

void ListWidgetObjects::addTorus(const QString &text, int objectId)
{
	addItem(text);
	m_objectsList.append(qMakePair(this->item(this->count() - 1), objectId));
	this->item(this->count() - 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	m_torusIds.append(objectId);
}

void ListWidgetObjects::addPoint3D(const QString& text, int objectId)
{
	addItem(text);
	m_objectsList.append(qMakePair(this->item(this->count() - 1), objectId));
	this->item(this->count() - 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
}

void ListWidgetObjects::removeItem()
{
	if (this->currentRow() < 0)
	{
		return;
	}
	emit removeItemEvent(m_objectsList.at(currentRow()).second);
	m_objectsList.removeAt(currentRow());
	this->removeItemWidget(takeItem(currentRow()));
}

void ListWidgetObjects::highlightItem(int objectId)
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

void ListWidgetObjects::itemClick(QListWidgetItem *item)
{
	if (!(QGuiApplication::keyboardModifiers() & Qt::ControlModifier))
	{
		m_selectedObjectsIds.clear();
	}
	int id = m_objectsList.at(this->currentRow()).second;
	updatePointsList(id);

	//ui.myGLWidget->drawableItemClicked(m_objectsList.at(ui.listWidget_ObjectsList->currentRow()).second);
	//ui.myGLWidget->drawableItemClicked(id);


	//void MyGLWidget::drawableItemClicked(int id)
	//{
	//	if (m_scene.m_isCursor3d)
	//	{
	//		m_scene.updateCursor();
	//	}
	//	updateGL();
	//}
}

void ListWidgetObjects::itemTextChanged(QListWidgetItem* item)
{
	emit changeItemTextEvent(item->text(), findItemId(item));
}

void ListWidgetObjects::addBezierCurveC0(const QString &text, int objectId)
{
	addItem(text);
	m_objectsList.append(qMakePair(this->item(this->count() - 1), objectId));
	this->item(this->count() - 1)->setFlags(Qt::ItemIsEditable | Qt::ItemIsEnabled | Qt::ItemIsSelectable);
	m_bezierCurveC0Ids.append(objectId);
}
