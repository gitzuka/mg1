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
	void mousePressEvent(QMouseEvent *event);

	QList<QPair<QListWidgetItem*, int>> m_points;

signals:
	void rightClick(const QPoint &pos);

public slots:
	//void comboBox_BezierCurveC0DisplayPoints(int);
	void displayPoints(const QList<std::shared_ptr<Point3D>> &points);
	void pointAddedToBC0(int id);
	void pointRemovedFromBC0(int id);
	void updatePointName(int id, const QString &name);

};

#endif // LISTWIDGETPARAMETERS_H