#pragma once
#ifndef LISTWIDGETOBJECTS_H
#define LISTWIDGETOBJECTS_H
#include <QListWidget>


class ListWidgetObjects : public QListWidget
{
	Q_OBJECT

public:
	explicit ListWidgetObjects(QWidget *parent = 0);
	~ListWidgetObjects();


private:
	QList<QPair<QListWidgetItem*, int>> m_objectsList;
	QList<int> m_bezierCurveC0Ids;
	QList<int> m_torusIds;
	QList<int> m_selectedObjectsIds;

	void mousePressEvent(QMouseEvent *event) override;
	int findItemId(QListWidgetItem *item) const;
	void updatePointsList(int id);

signals:
	void rightClick(const QPoint &pos, const QList<int> &selectedObjectIds);
	//void addBezierCurceC0Event(const QString &text, int objectId);
	//void addTorusEvent(const QString &text, int objectId);
	void changeItemTextEvent(const QString &text, int objectId);
	void removeItemEvent(int objectId);
	//void menuItecBC0Clicked(QList<int> &objects);

public slots:
	void addBezierCurveC0(const QString &text, int objectId);
	void addTorus(const QString &text, int objectId);
	void addPoint3D(const QString &text, int objectId);
	void removeItem();
	void highlightItem(int objectId);

	//void pointAddedToBC0(int id);
	//void pointRemovedFromBC0(int id);

private slots:
	void itemTextChanged(QListWidgetItem *item);
	void itemClick(QListWidgetItem *item);
};

#endif // LISTWIDGETOBJECTS_H