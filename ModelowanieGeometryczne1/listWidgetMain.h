#pragma once
#ifndef LISTWIDGETOBJECTS_H
#define LISTWIDGETOBJECTS_H
#include <QListWidget>


class ListWidgetMain : public QListWidget
{
	Q_OBJECT

public:
	explicit ListWidgetMain(QWidget *parent = 0);
	~ListWidgetMain();

private:
	QList<QPair<QListWidgetItem*, int>> m_objectsList;
	QList<int> m_bezierCurveC0Ids;
	QList<int> m_bezierCurveC2Ids;
	QList<int> m_torusIds;
	QList<int> m_selectedObjectsIds;
	QListWidgetItem *m_activeItem;

	void mousePressEvent(QMouseEvent *event) override;
	int findItemId(QListWidgetItem *item) const;
	void updatePointsList(int id);

signals:
	void rightClick(const QPoint &pos, const QList<int> &selectedObjectIds);
	void changeItemTextEvent(const QString &text, int objectId);
	void removeItemEvent(int objectId);
	void itemSelected(QList<int> objectIds);

public slots:
	void addBezierCurveC0(const QString &text, int objectId);
	void addBezierCurveC2(const QString &text, int objectId);
	void addTorus(const QString &text, int objectId);
	void addPoint3D(const QString &text, int objectId);
	void removeItem();
	void highlightItem(int objectId);
	void highlightActiveItem(int objectId);
	void removeHighlightActive();

private slots:
	void itemTextChanged(QListWidgetItem *item);
	void itemClick(QListWidgetItem *item);
};

#endif // LISTWIDGETOBJECTS_H