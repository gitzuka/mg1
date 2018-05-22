#pragma once
#ifndef LISTWIDGETBC0_H
#define LISTWIDGETBC0_H
#include <QListWidget>
#include <memory>

class Point3D;
class ListWidgetBC0 : public QListWidget
{
	Q_OBJECT

public:
	explicit ListWidgetBC0(QWidget *parent = 0);
	~ListWidgetBC0();

private:
	QList<QPair<QListWidgetItem*, int>> m_points;
	int m_curveId; 

	void mousePressEvent(QMouseEvent *event);
	void createObjectMenu(const QPoint &pos, QListWidgetItem *item);
	void removeItem(QListWidgetItem *item);

signals:
	void rightClick(const QPoint &pos);
	void removedItem(int pointId, int curveId);

public slots:
	void displayPoints(const QList<std::shared_ptr<Point3D>> &points);
	void pointAddedToBC0(int id, const QString &name);
	void updatePointName(int id, const QString &name);
	void updateCurveId(int id);
	void highlightItem(int objectId);
};

#endif // LISTWIDGETBC0_H