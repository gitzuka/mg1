#pragma once
#ifndef LISTWIDGETPARAMETERS_H
#define LISTWIDGETPARAMETERS_H
#include <QListWidget>
#include <memory>


class Point3D;
class ListWidgetParameters : public QListWidget
{
	Q_OBJECT

public:
	explicit ListWidgetParameters(QWidget *parent = 0);
	~ListWidgetParameters();

private:
	QList<QPair<QListWidgetItem*, int>> m_points;
	int m_curveId; 

	void mousePressEvent(QMouseEvent *event);
	void createObjectMenu(const QPoint &pos, QListWidgetItem *item);
	void removeItem(QListWidgetItem *item);
	//void deleteItems();

signals:
	void rightClick(const QPoint &pos);
	void removedItem(int pointId, int curveId);

public slots:
	//void comboBox_BezierCurveC0DisplayPoints(int);
	void displayPoints(const QList<std::shared_ptr<Point3D>> &points);
	void pointAddedToBC0(int id);
	void pointRemovedFromBC0(int id);
	void updatePointName(int id, const QString &name);
	void updateCurveId(int id);
};

#endif // LISTWIDGETPARAMETERS_H