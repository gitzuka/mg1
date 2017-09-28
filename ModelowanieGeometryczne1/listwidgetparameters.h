#pragma once
#ifndef LISTWIDGETPARAMETERS_H
#define LISTWIDGETPARAMETERS_H
#include <QListWidget>

class ListWidgetParameters : public QListWidget
{
	Q_OBJECT

public:
	explicit ListWidgetParameters(QWidget *parent = 0);
	~ListWidgetParameters();


private:
	void mousePressEvent(QMouseEvent *event);

signals:
	void rightClick(const QPoint &pos);

public slots:
	void comboBox_BezierCurveC0DisplayPoints(int);
	void pointAddedToBC0(int id);
	void pointRemovedFromBC0(int id);
	void updatePointName(QString name, int id);

};

#endif // LISTWIDGETPARAMETERS_H