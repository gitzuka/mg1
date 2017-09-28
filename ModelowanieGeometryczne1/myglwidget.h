#pragma once
#ifndef MYGLWIDGET_H
#define MYGLWIDGET_H

#include "scene.h"

class MyGLWidget : public QGLWidget
{
	Q_OBJECT
public:
	explicit MyGLWidget(QWidget *parent = 0);
	~MyGLWidget();

	Scene *m_scene;

	int getWidth() const;
	int getHeight() const;
	void setWidth(int width);
	void setHeight(int height);

protected:
	void initializeGL();
	void paintGL();
	void resizeGL(int width, int height);

	QSize minimumSizeHint() const;
	QSize sizeHint() const;
	void mousePressEvent(QMouseEvent *event);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent  *event);

private:
	QPoint lastPos;
	int m_width;
	int m_height;

signals:
	void mousePressed(QMouseEvent *event);
	void mouseMoved(QMouseEvent *event);
	void keyPressed(QKeyEvent *event);
	//signals:
//	void cursorMoveEvent(float x, float y, float z);
//	void cursor3dItemAcquired(int id);
//	void torusAdded(int) const;
//	void bezierCurveC0Added(int) const;
//	void point3dAdded(int id) const;
	//void triggered(QAction* action);

public slots:
	void checkBox_pointerStateChanged(int checked);
//	void createCurveC0fromPoints(const QList<int> &ids);

//public slots:
	//void listWidget_ObjectsListObjAdded(QList<QPair<QListWidgetItem*, int>> &objects, QListWidgetItem *item);
	//void drawableItemClicked(int id);
	//void listWidget_ObjectsListObjRemoved(const QList<QPair<QListWidgetItem*, int>> &objects, int index);
	//void listWidget_itemRightClicked(const QList<QPair<QListWidgetItem*, int>> &objects, const QList<int> &selectedObjects, int index, const QPoint &pos);
	//void listWidget_itemRightClicked(const QList<int> &selectedObjects, const QPoint &pos);
};

#endif //MYGLWIDGET_H
