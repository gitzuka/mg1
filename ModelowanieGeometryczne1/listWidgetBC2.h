#pragma once
#ifndef LISTWIDGETBC2_H
#define LISTWIDGETBC2_H
#include <QListWidget>
#include <memory>

class Point3D;
class ListWidgetBC2 : public QListWidget
{
	Q_OBJECT

public:
	explicit ListWidgetBC2(QWidget *parent = 0);
	~ListWidgetBC2();

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
	void pointAddedToBC2(int id, const QString &name);
	void updatePointName(int id, const QString &name);
	void updateCurveId(int id);
	void highlightItem(int objectId);
};

#endif // LISTWIDGETBC2_H