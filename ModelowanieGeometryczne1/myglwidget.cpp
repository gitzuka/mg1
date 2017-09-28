#include "myglwidget.h"
#include <QtGui>
#include <GL/GLU.h>
#include "torus.h"
#include "bezierCurveC0.h"
#include "modelowaniegeometryczne1.h"


MyGLWidget::MyGLWidget(QWidget *parent)
	: QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
	//initializeObjects();
}

//void MyGLWidget::initializeObjects()
//{
//	m_scene.m_cursor = std::make_shared<Cursor3D>(Cursor3D::ObjectType::cursor3D);
//	m_scene.m_cursor->createVertices();
//	m_scene.m_cursor->generateIndices();
//}


MyGLWidget::~MyGLWidget()
{
}

int MyGLWidget::getWidth() const
{
	return m_width;
}

int MyGLWidget::getHeight() const
{
	return m_height;
}

void MyGLWidget::setWidth(int width)
{
	m_width = width;
}

void MyGLWidget::setHeight(int height)
{
	m_height = height;
}

QSize MyGLWidget::minimumSizeHint() const
{
	return QSize(800, 600);
}

QSize MyGLWidget::sizeHint() const
{
	return QSize(800, 600);
}

void MyGLWidget::initializeGL()
{
	qglClearColor(Qt::black);
	/*glViewport(0, 0, 800, 600);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, 800, 0, 600, -1, 1);
	glMatrixMode(GL_MODELVIEW);*/
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void MyGLWidget::paintGL()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	m_scene->draw();
}

void MyGLWidget::resizeGL(int width, int height)
{
	glViewport(0, 0, width, height);
	setWidth(width);
	setHeight(height);
	m_scene->m_camera.m_projectionMatrix = Camera::createProjection(m_width, m_height);
	m_scene->m_camera.updateStereoscopy(0.1f, m_width, m_height);
	updateGL();
}

void MyGLWidget::mousePressEvent(QMouseEvent *event)
{
	emit mousePressed(event);
	updateGL();
}



void MyGLWidget::mouseMoveEvent(QMouseEvent *event)
{
	emit mouseMoved(event);
	updateGL();
}

void MyGLWidget::keyPressEvent(QKeyEvent *event)
{
	emit keyPressed(event);
	updateGL();
}

void MyGLWidget::checkBox_pointerStateChanged(int checked)
{
	if (checked)
	{
		this->setCursor(Qt::BlankCursor);
	}
	else
	{
		this->setCursor(Qt::ArrowCursor);
	}
	m_scene->toggleCursor3D(checked);
	updateGL();
}
//
//void MyGLWidget::createCurveC0fromPoints(const QList<int> &ids)
//{
//	std::shared_ptr<BezierCurveC0> object = std::make_shared<BezierCurveC0>(BezierCurveC0::ObjectType::bezierCurveC0);
//	for (int i=0; i<ids.count(); ++i)
//	{
//		object->addControlPoint(m_scene.getObjectByID(ids.at(i)));
//	}
//	emit bezierCurveC0Added(object->getId());
//	object->createVertices();
//	object->generateIndices();
//	m_scene.addObject(object);
//	updateGL();
//}

//void MyGLWidget::drawableItemClicked(int id)
//{
//	if (m_scene.m_isCursor3d)
//	{
//		m_scene.updateCursor();
//	}
//	updateGL();
//}

//void MyGLWidget::listWidget_itemRightClicked(const QList<int> &selectedObjects, const QPoint &pos)
//{
//	for (int i = 0; i < selectedObjects.count(); ++i)
//	{
//		if (m_scene.getObjectByID(selectedObjects.at(i)) == nullptr || m_scene.getObjectByID(selectedObjects.at(i))->m_type != DrawableObject::ObjectType::point3D)
//		{
//			return;
//		}
//	}
//	QMenu myMenu;
//	QAction *createBC0 = myMenu.addAction("Create Bezier Curve C0");
//	connect(createBC0, &QAction::triggered, this, [this, &selectedObjects]()
//	{
//		//createCurveC0fromPoints(selectedObjects);
//	});
//	myMenu.exec(pos);
//}