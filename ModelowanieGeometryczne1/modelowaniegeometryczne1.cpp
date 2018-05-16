#include "modelowaniegeometryczne1.h"
#include "torus.h"
#include "bezierCurveC0.h"
#include "uiTorus.h"
#include "uiPoint3d.h"
#include "uiBezierCurveC0.h"
#include "uiBezierCurveC2.h"
#include <QString>
#include <QObject>

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
	connect(ui.myGLWidget, SIGNAL(mouseMoved(QMouseEvent*)), this, SLOT(label_screenCoordsChangeText(QMouseEvent*)));

	connect(this, SIGNAL(cursor3dItemAcquired(int)), ui.listWidget_ObjectsList, SLOT(highlightItem(int)));
	connect(this, SIGNAL(cursor3dItemAcquired(int)), ui.listWidget_BC0Parameters, SLOT(highlightItem(int)));
	connect(this, SIGNAL(cursor3dItemAcquired(int)), ui.listWidget_BC2, SLOT(highlightItem(int)));

	connect(ui.radioButton_stereo, SIGNAL(toggled(bool)), this, SLOT(stereo_button_toggled(bool)));
	connect(ui.checkBox_pointer, SIGNAL(stateChanged(int)), ui.myGLWidget, SLOT(checkBox_pointerStateChanged(int)));
	connect(ui.pushButton_AddObject, SIGNAL(clicked()), this, SLOT(pushButton_AddObjectClicked()));
	connect(ui.pushButton_DeleteObject, SIGNAL(clicked()), ui.listWidget_ObjectsList, SLOT(removeItem()));
	connect(ui.comboBox_BezierCurveC0, SIGNAL(itemRemoved()), ui.listWidget_BC0Parameters, SLOT(clear()));
	connect(ui.comboBox_BC2, SIGNAL(itemRemoved()), ui.listWidget_BC2, SLOT(clear()));
	connect(ui.comboBox_BezierCurveC0, SIGNAL(itemSelected(int, int)), ui.listWidget_BC0Parameters, SLOT(updateCurveId(int)));
	connect(ui.comboBox_BezierCurveC0, SIGNAL(itemSelected(int, int)), this, SLOT(showBC0CheckBoxes(int, int)));
	connect(ui.comboBox_BC2, SIGNAL(itemSelected(int, int)), ui.listWidget_BC2, SLOT(updateCurveId(int)));
	connect(ui.comboBox_BC2, SIGNAL(itemSelected(int, int)), this, SLOT(showBC2CheckBoxes(int, int)));
	connect(ui.comboBox_BezierCurveC0, SIGNAL(currentIndexChanged(int)), ui.comboBox_BezierCurveC0, SLOT(selectCurve(int)));
	connect(ui.comboBox_BC2, SIGNAL(currentIndexChanged(int)), ui.comboBox_BC2, SLOT(selectCurve(int)));

	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), &m_scene, SLOT(deleteObject(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_Torus, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_BezierCurveC0, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_BC2, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(rightClick(const QPoint&, const QList<int>&)), &m_scene, SLOT(createObjectMenu(const QPoint&, const QList<int>&)));

	connect(ui.listWidget_BC0Parameters, SIGNAL(removedItem(int, int)), ui.myGLWidget, SLOT(updateGL()));
	connect(ui.listWidget_BC2, SIGNAL(removedItem(int, int)), ui.myGLWidget, SLOT(updateGL()));

	connect(&m_scene, SIGNAL(addedBezierCurveC0(const QString&, int, const UiBezierCurveC0*)), ui.listWidget_ObjectsList, SLOT(addBezierCurveC0(const QString&, int)));
	connect(&m_scene, SIGNAL(addedBezierCurveC0(const QString&, int, const UiBezierCurveC0*)), this, SLOT(comboBox_BezierCurveC0_AddItem(const QString&, int, const UiBezierCurveC0*)));
	connect(&m_scene, SIGNAL(addedBezierCurveC2(const QString&, int, const UiBezierCurveC2*)), ui.listWidget_ObjectsList, SLOT(addBezierCurveC2(const QString&, int)));
	connect(&m_scene, SIGNAL(addedBezierCurveC2(const QString&, int, const UiBezierCurveC2*)), this, SLOT(comboBox_BezierCurveC2_AddItem(const QString&, int, const UiBezierCurveC2*)));
	connect(&m_scene, SIGNAL(addedTorus(const QString&, int, const UiTorus*)), ui.listWidget_ObjectsList, SLOT(addTorus(const QString&, int)));
	connect(&m_scene, SIGNAL(addedTorus(const QString&, int, const UiTorus*)), this, SLOT(comboBox_Torus_AddItem(const QString&, int, const UiTorus*)));
	connect(&m_scene, SIGNAL(addedPoint3D(const QString&, int, const UiPoint3D*)), ui.listWidget_ObjectsList, SLOT(addPoint3D(const QString&, int)));
	connect(&m_scene, SIGNAL(addedPoint3D(const QString&, int, const UiPoint3D*)), this, SLOT(connectPoint3D(const QString&, int, const UiPoint3D*)));
	connect(&m_scene, SIGNAL(editModeBC0(int)), ui.listWidget_ObjectsList, SLOT(highlightActiveItem(int)));
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

void ModelowanieGeometryczne1::comboBox_Torus_AddItem(const QString &name, int id, const UiTorus *uiTorus)
{
	uiTorus->connectToUi(&ui);
	ui.comboBox_Torus->addItem(id, name);
}

void ModelowanieGeometryczne1::comboBox_BezierCurveC0_AddItem(const QString &name, int id, const UiBezierCurveC0 *uiBezierC0)
{
	uiBezierC0->connectToUi(&ui);
	uiBezierC0->connectToScene(&m_scene);
	ui.comboBox_BezierCurveC0->addItem(id, name);
}

void ModelowanieGeometryczne1::comboBox_BezierCurveC2_AddItem(const QString &name, int id, const UiBezierCurveC2 *uiBezierC2)
{
	uiBezierC2->connectToUi(&ui);
	uiBezierC2->connectToScene(&m_scene);
	ui.comboBox_BC2->addItem(id, name);
}

void ModelowanieGeometryczne1::connectPoint3D(const QString& name, int id, const UiPoint3D* uiPoint3d)
{
	uiPoint3d->connectToUi(&ui);
}

void ModelowanieGeometryczne1::myGLWidgetKeyPressed(QKeyEvent *event)
{
	m_scene.m_camera.keyPressed(event->key());
	switch (event->key())
	{
	case Qt::Key_Escape:
	{
		//dz = TRANSLATION_STEP;
		break;
	}
	}
}

void ModelowanieGeometryczne1::myGLWidgetMouseMoved(QMouseEvent *event)
{
	float dx = event->x() - m_scene.m_camera.m_mousePos.x();
	float dy = event->y() - m_scene.m_camera.m_mousePos.y();
	/*if (event->buttons() & Qt::LeftButton)
	{
	}
	else*/ if (event->buttons() & Qt::RightButton)
	{
		m_scene.m_camera.mouseMoved(dx, dy);
	}
	if (m_scene.m_isCursor3d)
	{
		//TODO: cursor z translation
		/*if (QGuiApplication::keyboardModifiers() & Qt::ControlModifier)
		{
			m_scene.m_cursorPosZ = dy;
		}*/
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
		/*if (QGuiApplication::keyboardModifiers() & Qt::AltModifier)
		{

		}*/
		int id = m_scene.updateCursor();
		if (id != -1)
		{
			emit cursor3dItemAcquired(id);
		}
	}
}

void ModelowanieGeometryczne1::updateMyGLWidget()
{
	ui.myGLWidget->updateGL();
}

void ModelowanieGeometryczne1::showBC0CheckBoxes(int currId, int prevId)
{
	const UiBezierCurveC0 *uibc0 = static_cast<const UiBezierCurveC0*>(m_scene.getUiConntector(prevId));
	if (uibc0 != nullptr)
	{
		ui.verticalLayout_BC2->removeWidget(uibc0->getCBPolyline());
		uibc0->getCBPolyline()->hide();
	}
	uibc0 = static_cast<const UiBezierCurveC0*>(m_scene.getUiConntector(currId));
	if (uibc0 != nullptr)
	{
		uibc0->getCBPolyline()->show();
		ui.verticalLayout_BC2->addWidget(uibc0->getCBPolyline());
	}
}

void ModelowanieGeometryczne1::showBC2CheckBoxes(int currId, int prevId)
{
	UiBezierCurveC2 *uibc2 = static_cast<UiBezierCurveC2*>(m_scene.getUiConntector(prevId));
	if (uibc2 != nullptr)
	{
		uibc2->getCBPolyline()->hide();
		uibc2->getCBDeBoor()->hide();
		ui.verticalLayout_BC2->removeWidget(uibc2->getCBPolyline());
		ui.verticalLayout_BC2->removeWidget(uibc2->getCBDeBoor());
	}
	uibc2 = static_cast<UiBezierCurveC2*>(m_scene.getUiConntector(currId));
	if (uibc2 != nullptr)
	{
		uibc2->getCBPolyline()->show();
		uibc2->getCBDeBoor()->show();
		ui.verticalLayout_BC2->addWidget(uibc2->getCBPolyline());
		ui.verticalLayout_BC2->addWidget(uibc2->getCBDeBoor());
	}
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