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

public slots:
	void checkBox_pointerStateChanged(int checked);
};

#endif //MYGLWIDGET_H
