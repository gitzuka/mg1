#include "modelowaniegeometryczne1.h"
#include "torus.h"
#include "point3d.h"
#include "bezierCurveC0.h"

ModelowanieGeometryczne1::ModelowanieGeometryczne1(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	m_scene.m_cursor = std::make_shared<Cursor3D>(Cursor3D::ObjectType::cursor3D);

	connectSignals();
	model = new QStringListModel(this);
	model->setStringList(ui_drawableObjects);
	ui.comboBox_DrawableObjects->setModel(model);
	ui.myGLWidget->m_scene = &m_scene;
}

ModelowanieGeometryczne1::~ModelowanieGeometryczne1()
{
	delete model;
}

void ModelowanieGeometryczne1::connectSignals()
{
	connect(ui.doubleSpinBox_e, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinbox_eValueChanged(double)));
	connect(ui.doubleSpinBox_smallR, SIGNAL(valueChanged(double)), ui.comboBox_Torus, SLOT(changeSmallr(double)));
	connect(ui.doubleSpinBox_bigR, SIGNAL(valueChanged(double)), ui.comboBox_Torus, SLOT(changeBigR(double)));
	connect(ui.spinBox_minorSegments, SIGNAL(valueChanged(int)), ui.comboBox_Torus, SLOT(changeMinorSegments(int)));
	connect(ui.spinBox_majorSegments, SIGNAL(valueChanged(int)), ui.comboBox_Torus, SLOT(changeMajorSegments(int)));

	connect(ui.doubleSpinBox_smallR, SIGNAL(valueChanged(double)), this, SLOT(updateMyGLWidget()));
	connect(ui.doubleSpinBox_bigR, SIGNAL(valueChanged(double)), this, SLOT(updateMyGLWidget()));
	connect(ui.spinBox_minorSegments, SIGNAL(valueChanged(int)), this, SLOT(updateMyGLWidget()));
	connect(ui.spinBox_majorSegments, SIGNAL(valueChanged(int)), this, SLOT(updateMyGLWidget()));

	connect(ui.myGLWidget, SIGNAL(keyPressed(QKeyEvent *)), this, SLOT(myGLWidgetKeyPressed(QKeyEvent *)));
	connect(ui.myGLWidget, SIGNAL(mouseMoved(QMouseEvent *)), this, SLOT(myGLWidgetMouseMoved(QMouseEvent *)));
	connect(ui.myGLWidget, SIGNAL(mousePressed(QMouseEvent *)), this, SLOT(myGLWidgetMousePressed(QMouseEvent *)));

	connect(this, SIGNAL(cursor3dItemAcquired(int)), ui.listWidget_ObjectsList, SLOT(highlightItem(int)));
	connect(ui.myGLWidget, SIGNAL(mouseMoved(QMouseEvent*)), this, SLOT(label_screenCoordsChangeText(QMouseEvent*)));

	connect(ui.radioButton_stereo, SIGNAL(toggled(bool)), this, SLOT(stereo_button_toggled(bool)));
	connect(ui.checkBox_pointer, SIGNAL(stateChanged(int)), ui.myGLWidget, SLOT(checkBox_pointerStateChanged(int)));
	connect(ui.pushButton_AddObject, SIGNAL(clicked()), this, SLOT(pushButton_AddObjectClicked()));
	connect(ui.pushButton_DeleteObject, SIGNAL(clicked()), ui.listWidget_ObjectsList, SLOT(removeItem()));
	//connect(ui.comboBox_BezierCurveC0, SIGNAL(currentIndexChanged(int)), ui.listWidget_Parameters, SLOT(comboBox_BezierCurveC0DisplayPoints(int)));
	//connect(ui.comboBox_BezierCurveC0, SIGNAL(itemSelected(int)), ui.listWidget_Parameters, SLOT(comboBox_BezierCurveC0DisplayPoints(int)));
	connect(ui.comboBox_BezierCurveC0, SIGNAL(itemRemoved()), ui.listWidget_Parameters, SLOT(clear()));


	connect(ui.comboBox_BezierCurveC0, SIGNAL(currentIndexChanged(int)), ui.comboBox_BezierCurveC0, SLOT(selectCurve(int)));

	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_BezierCurveC0, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_Torus, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(rightClick(const QPoint&, const QList<int>&)), &m_scene, SLOT(createObjectMenu(const QPoint&, const QList<int>&)));

	connect(&m_scene, SIGNAL(addedBezierCurveC0(QString, int, const std::shared_ptr<BezierCurveC0>&)), ui.listWidget_ObjectsList, SLOT(addBezierCurveC0(QString, int)));
	connect(&m_scene, SIGNAL(addedBezierCurveC0(QString, int, const std::shared_ptr<BezierCurveC0>&)), this, SLOT(comboBox_BezierCurveC0_AddItem(QString, int, const std::shared_ptr<BezierCurveC0>&)));

	connect(&m_scene, SIGNAL(addedTorus(QString, int, const std::shared_ptr<Torus>&)), ui.listWidget_ObjectsList, SLOT(addTorus(QString, int)));
	connect(&m_scene, SIGNAL(addedTorus(QString, int, const std::shared_ptr<Torus>&)), this, SLOT(comboBox_Torus_AddItem(QString, int, const std::shared_ptr<Torus>&)));

	connect(&m_scene, SIGNAL(addedPoint3D(QString, int, const std::shared_ptr<DrawableObject>&)), ui.listWidget_ObjectsList, SLOT(addPoint3D(QString, int)));
}

void ModelowanieGeometryczne1::label_3dCoordsChangeText(float x, float y, float z)
{
	QString text = "Cursor3D coords: "
		+ QString::number(x) + ", "
		+ QString::number(y) + ", "
		+ QString::number(z);
	ui.label_3dCoords->setText(text);
}

void ModelowanieGeometryczne1::pushButton_AddObjectClicked()
{
	m_scene.createDrawableObject(ui.comboBox_DrawableObjects->currentText());
	ui.myGLWidget->updateGL();
}

void ModelowanieGeometryczne1::label_screenCoordsChangeText(QMouseEvent* event)
{
	QString text = "Screen coords: "
		+ QString::number(event->pos().x()) + ", "
		+ QString::number(event->pos().y());
	ui.label_screenCoords->setText(text);
}

void ModelowanieGeometryczne1::comboBox_Torus_AddItem(QString name, int id, const std::shared_ptr<Torus> &object)
{
	object->connectToUI(ui.comboBox_Torus, ui.listWidget_ObjectsList);
	ui.comboBox_Torus->addItem(id, name);
}

void ModelowanieGeometryczne1::comboBox_BezierCurveC0_AddItem(const QString &name, int id, const std::shared_ptr<BezierCurveC0> &object)
{
	object->connectToUI(ui.comboBox_BezierCurveC0, ui.listWidget_ObjectsList, &m_scene, ui.listWidget_Parameters);
	ui.comboBox_BezierCurveC0->addItem(id, name);

}

void ModelowanieGeometryczne1::myGLWidgetKeyPressed(QKeyEvent *event)
{
	m_scene.m_camera.keyPressed(event->key());
}

void ModelowanieGeometryczne1::myGLWidgetMouseMoved(QMouseEvent * event)
{
	float dx = event->x() - m_scene.m_camera.m_mousePos.x();
	float dy = event->y() - m_scene.m_camera.m_mousePos.y();
	if (event->buttons() & Qt::LeftButton)
	{
	}
	else if (event->buttons() & Qt::RightButton)
	{
		m_scene.m_camera.mouseMoved(dx, dy);
	}
	else if (QGuiApplication::keyboardModifiers() & Qt::ControlModifier)
	{
		m_scene.m_cursorPosZ = dy;
	}
	if (m_scene.m_isCursor3d)
	{
		m_scene.updateCursorPosition(event->x(), event->y(), ui.myGLWidget->getWidth(), ui.myGLWidget->getHeight());
	}
	m_scene.m_camera.m_mousePos = event->pos();
	QVector4D c = m_scene.m_cursor->getPosition();
	label_3dCoordsChangeText(c.x(), c.y(), c.z());
}

void ModelowanieGeometryczne1::myGLWidgetMousePressed(QMouseEvent *event)
{
	m_scene.m_camera.m_mousePos = event->pos();
	if (event->button() == Qt::LeftButton && m_scene.m_isCursor3d)
	{
		int index = m_scene.updateCursor();
		if (index != -1)
		{
			emit cursor3dItemAcquired(m_scene.getObject(index)->getId());
		}
	}
}

void ModelowanieGeometryczne1::updateMyGLWidget()
{
	ui.myGLWidget->updateGL();
}

void ModelowanieGeometryczne1::doubleSpinbox_eValueChanged(double e)
{
	m_scene.m_camera.updateStereoscopy(e, ui.myGLWidget->getWidth(), ui.myGLWidget->getHeight());
	ui.myGLWidget->updateGL();
}

void ModelowanieGeometryczne1::stereo_button_toggled(bool checked)
{
	m_scene.m_stereoscopy = checked;
	ui.myGLWidget->updateGL();
}