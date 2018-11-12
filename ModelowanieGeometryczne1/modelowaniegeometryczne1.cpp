#include "modelowaniegeometryczne1.h"
#include "torus.h"
#include "uiTorus.h"
#include "uiPoint3d.h"
#include "uiBezierCurveC0.h"
#include "uiBezierCurveC2.h"
#include "uiBezierC2Interpolated.h"
#include <QString>
#include <QObject>
#include "uiBezierSurfaceC0.h"
#include "uiBezierSurfaceC2.h"
#include "bezierSurfaceSettings.h"
#include "fileManager.h"

ModelowanieGeometryczne1::ModelowanieGeometryczne1(QWidget *parent)
	: QMainWindow(parent), m_activeObjectId(-1)
{
	ui.setupUi(this);
	m_scene.initialize();
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
	connect(this, SIGNAL(cursor3dItemAcquired(int)), ui.listWidget_BC2Int, SLOT(highlightItem(int)));
	connect(this, SIGNAL(cursor3dItemAcquired(int)), ui.listWidget_BSC0, SLOT(highlightItem(int)));
	connect(this, SIGNAL(cursor3dItemAcquired(int)), ui.listWidget_BSC2, SLOT(highlightItem(int)));
	connect(this, SIGNAL(mouseClicked(bool)), &m_scene, SLOT(performCursorAction(bool)));
	connect(this, SIGNAL(escKeyPressed()), &m_scene, SLOT(resetCursor()));
	connect(this, SIGNAL(loadedFile(const QString&)), &m_scene, SLOT(loadScene(const QString&)));

	connect(ui.radioButton_stereo, SIGNAL(toggled(bool)), this, SLOT(stereo_button_toggled(bool)));
	connect(ui.radioButton_Idle, SIGNAL(toggled(bool)), this, SLOT(radioBtnIdleToggled(bool)));
	connect(ui.radioButton_Translate, SIGNAL(toggled(bool)), this, SLOT(radioBtnTranslateToggled(bool)));
	connect(ui.radioButton_Add, SIGNAL(toggled(bool)), this, SLOT(radioBtnAddToggled(bool)));
	connect(ui.radioButton_Delete, SIGNAL(toggled(bool)), this, SLOT(radioBtnDeleteToggled(bool)));

	connect(ui.actionLoad_Scene, &QAction::triggered, this, &ModelowanieGeometryczne1::loadScene);
	connect(ui.actionSave_Scene, &QAction::triggered, this, &ModelowanieGeometryczne1::saveScene);

	connect(ui.pushButton_BSC0, SIGNAL(clicked()), this, SLOT(pushButton_BSC0Clicked()));
	connect(ui.pushButton_BSC2, SIGNAL(clicked()), this, SLOT(pushButton_BSC2Clicked()));

	connect(ui.doubleSpinBox_PosX, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinbox_PosXValueChanged(double)));
	connect(ui.doubleSpinBox_PosY, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinbox_PosYValueChanged(double)));
	connect(ui.doubleSpinBox_PosZ, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinbox_PosZValueChanged(double)));
	connect(ui.doubleSpinBox_RotX, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinbox_RotXValueChanged(double)));
	connect(ui.doubleSpinBox_RotY, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinbox_RotYValueChanged(double)));
	connect(ui.doubleSpinBox_RotZ, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinbox_RotZValueChanged(double)));
	connect(ui.doubleSpinBox_CursorX, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinbox_CursorXValueChanged(double)));
	connect(ui.doubleSpinBox_CursorY, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinbox_CursorYValueChanged(double)));
	connect(ui.doubleSpinBox_CursorZ, SIGNAL(valueChanged(double)), this, SLOT(doubleSpinbox_CursorZValueChanged(double)));
	connect(ui.doubleSpinBox_CursorX, SIGNAL(valueChanged(double)), this, SLOT(updateMyGLWidget()));
	connect(ui.doubleSpinBox_CursorY, SIGNAL(valueChanged(double)), this, SLOT(updateMyGLWidget()));
	connect(ui.doubleSpinBox_CursorZ, SIGNAL(valueChanged(double)), this, SLOT(updateMyGLWidget()));

	connect(ui.checkBox_pointer, SIGNAL(stateChanged(int)), ui.myGLWidget, SLOT(checkBox_pointerStateChanged(int)));
	connect(ui.pushButton_Intersections, SIGNAL(clicked()), this, SLOT(pushButton_IntersectionsClicked()));
	connect(ui.pushButton_AddObject, SIGNAL(clicked()), this, SLOT(pushButton_AddObjectClicked()));
	connect(ui.pushButton_DeleteObject, SIGNAL(clicked()), ui.listWidget_ObjectsList, SLOT(removeItem()));
	connect(ui.pushButton_DeleteObject, SIGNAL(clicked()), ui.myGLWidget, SLOT(updateGL()));
	connect(ui.comboBox_BezierCurveC0, SIGNAL(itemRemoved()), ui.listWidget_BC0Parameters, SLOT(clear()));
	connect(ui.comboBox_BC2, SIGNAL(itemRemoved()), ui.listWidget_BC2, SLOT(clear()));
	connect(ui.comboBox_BC2Int, SIGNAL(itemRemoved()), ui.listWidget_BC2Int, SLOT(clear()));
	connect(ui.comboBox_BezierCurveC0, SIGNAL(itemSelected(int, int)), ui.listWidget_BC0Parameters, SLOT(updateCurveId(int)));
	connect(ui.comboBox_BezierCurveC0, SIGNAL(itemSelected(int, int)), this, SLOT(showBC0CheckBoxes(int, int)));
	connect(ui.comboBox_BC2, SIGNAL(itemSelected(int, int)), ui.listWidget_BC2, SLOT(updateCurveId(int)));
	connect(ui.comboBox_BC2, SIGNAL(itemSelected(int, int)), this, SLOT(showBC2CheckBoxes(int, int)));
	connect(ui.comboBox_BC2Int, SIGNAL(itemSelected(int, int)), this, SLOT(showBC2IntCheckBoxes(int, int)));
	connect(ui.comboBox_BC2Int, SIGNAL(itemSelected(int, int)), ui.listWidget_BC2Int, SLOT(updateCurveId(int)));
	connect(ui.comboBox_BSC0, SIGNAL(itemSelected(int, int)), ui.listWidget_BSC0, SLOT(updateSurfaceId(int)));
	connect(ui.comboBox_BSC0, SIGNAL(itemSelected(int, int)), this, SLOT(showBSC0CheckBoxes(int, int)));
	connect(ui.comboBox_BSC0, SIGNAL(allItemsRemoved()), ui.listWidget_BSC0, SLOT(clear()));
	connect(ui.comboBox_BSC2, SIGNAL(itemSelected(int, int)), ui.listWidget_BSC2, SLOT(updateSurfaceId(int)));
	connect(ui.comboBox_BSC2, SIGNAL(itemSelected(int, int)), this, SLOT(showBSC2CheckBoxes(int, int)));
	connect(ui.comboBox_BSC2, SIGNAL(allItemsRemoved()), ui.listWidget_BSC2, SLOT(clear()));
	connect(ui.comboBox_BezierCurveC0, SIGNAL(currentIndexChanged(int)), ui.comboBox_BezierCurveC0, SLOT(selectCurve(int)));
	connect(ui.comboBox_BC2, SIGNAL(currentIndexChanged(int)), ui.comboBox_BC2, SLOT(selectCurve(int)));
	connect(ui.comboBox_BC2Int, SIGNAL(currentIndexChanged(int)), ui.comboBox_BC2Int, SLOT(selectCurve(int)));
	connect(ui.comboBox_BSC0, SIGNAL(currentIndexChanged(int)), ui.comboBox_BSC0, SLOT(selectSurface(int)));
	connect(ui.comboBox_BSC2, SIGNAL(currentIndexChanged(int)), ui.comboBox_BSC2, SLOT(selectSurface(int)));

	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), &m_scene, SLOT(deleteObject(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_Torus, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_BezierCurveC0, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_BC2, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_BC2Int, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_BSC0, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(removeItemEvent(int)), ui.comboBox_BSC2, SLOT(deleteItem(int)));
	connect(ui.listWidget_ObjectsList, SIGNAL(itemSelected(QList<int>&)), &m_scene, SLOT(selectCursorObjects(QList<int>&)));
	connect(ui.listWidget_ObjectsList, SIGNAL(itemSelected(QList<int>&)), this, SLOT(updateMyGLWidget()));
	connect(ui.listWidget_ObjectsList, SIGNAL(itemSelected(QList<int>&)), this, SLOT(getObjectDetails(QList<int>&)));
	connect(ui.listWidget_ObjectsList, SIGNAL(rightClick(const QPoint&, const QList<int>&)), &m_scene, SLOT(createObjectMenu(const QPoint&, const QList<int>&)));

	connect(ui.listWidget_BC0Parameters, SIGNAL(removedItem(int, int)), ui.myGLWidget, SLOT(updateGL()));
	connect(ui.listWidget_BC2, SIGNAL(removedItem(int, int)), ui.myGLWidget, SLOT(updateGL()));
	connect(ui.listWidget_BC2Int, SIGNAL(removedItem(int, int)), ui.myGLWidget, SLOT(updateGL()));

	connect(&m_scene, SIGNAL(addedBezierCurveC0(const QString&, int, const UiBezierCurveC0*)), ui.listWidget_ObjectsList, SLOT(addBezierCurveC0(const QString&, int)));
	connect(&m_scene, SIGNAL(addedBezierCurveC0(const QString&, int, const UiBezierCurveC0*)), this, SLOT(comboBox_BezierCurveC0_AddItem(const QString&, int, const UiBezierCurveC0*)));
	connect(&m_scene, SIGNAL(addedBezierCurveC2(const QString&, int, const UiBezierCurveC2*)), ui.listWidget_ObjectsList, SLOT(addBezierCurveC2(const QString&, int)));
	connect(&m_scene, SIGNAL(addedBezierCurveC2(const QString&, int, const UiBezierCurveC2*)), this, SLOT(comboBox_BezierCurveC2_AddItem(const QString&, int, const UiBezierCurveC2*)));
	connect(&m_scene, SIGNAL(addedBezierC2Interpolated(const QString&, int, const UiBezierC2Interpolated*)), ui.listWidget_ObjectsList, SLOT(addBezierC2Interpolated(const QString&, int)));
	connect(&m_scene, SIGNAL(addedBezierC2Interpolated(const QString&, int, const UiBezierC2Interpolated*)), this, SLOT(comboBox_BezierCurveC2Int_AddItem(const QString&, int, const UiBezierC2Interpolated*)));
	connect(&m_scene, SIGNAL(addedBezierSurfaceC0(const QString&, int, UiBezierSurfaceC0*)), ui.listWidget_ObjectsList, SLOT(addObject(const QString&, int)));
	connect(&m_scene, SIGNAL(addedBezierSurfaceC0(const QString&, int, UiBezierSurfaceC0*)), this, SLOT(comboBox_BezierSurfaceC0_AddItem(const QString&, int, UiBezierSurfaceC0*)));
	connect(&m_scene, SIGNAL(addedBezierSurfaceC2(const QString&, int, UiBezierSurfaceC2*)), ui.listWidget_ObjectsList, SLOT(addObject(const QString&, int)));
	connect(&m_scene, SIGNAL(addedBezierSurfaceC2(const QString&, int, UiBezierSurfaceC2*)), this, SLOT(comboBox_BezierSurfaceC2_AddItem(const QString&, int, UiBezierSurfaceC2*)));
	connect(&m_scene, SIGNAL(addedTorus(const QString&, int, const UiTorus*)), ui.listWidget_ObjectsList, SLOT(addTorus(const QString&, int)));
	connect(&m_scene, SIGNAL(addedTorus(const QString&, int, const UiTorus*)), this, SLOT(comboBox_Torus_AddItem(const QString&, int, const UiTorus*)));
	connect(&m_scene, SIGNAL(addedPoint3D(const QString&, int, const UiPoint3D*)), ui.listWidget_ObjectsList, SLOT(addPoint3D(const QString&, int)));
	connect(&m_scene, SIGNAL(addedPoint3D(const QString&, int, const UiPoint3D*)), this, SLOT(connectPoint3D(const QString&, int, const UiPoint3D*)));
	connect(&m_scene, SIGNAL(createdBSControlPoint(const QString&, int, const UiPoint3D*)), this, SLOT(connectPoint3D(const QString&, int, const UiPoint3D*)));
	connect(&m_scene, SIGNAL(editModeBC0(int)), ui.listWidget_ObjectsList, SLOT(highlightActiveItem(int)));
	connect(&m_scene, SIGNAL(editModeBC2(int)), ui.listWidget_ObjectsList, SLOT(highlightActiveItem(int)));
	connect(&m_scene, SIGNAL(editModeBC2Int(int)), ui.listWidget_ObjectsList, SLOT(highlightActiveItem(int)));
	connect(&m_scene, SIGNAL(objectDeactivated(int)), ui.listWidget_ObjectsList, SLOT(removeHighlightActive()));
	connect(&m_scene, SIGNAL(objectActivated(int)), ui.listWidget_ObjectsList, SLOT(highlightActiveItem(int)));
}

void ModelowanieGeometryczne1::label_3dCoordsChangeText(float x, float y, float z)
{
	QString text = "Cursor3D coords: "
		+ QString::number(x, 'g', 4) + ", "
		+ QString::number(y, 'g', 4) + ", "
		+ QString::number(z, 'g', 4);
	ui.label_3dCoords->setText(text);
}

void ModelowanieGeometryczne1::setDetailSpinboxesSignalsState(bool state)
{
	ui.doubleSpinBox_PosX->blockSignals(state);
	ui.doubleSpinBox_PosY->blockSignals(state);
	ui.doubleSpinBox_PosZ->blockSignals(state);
	ui.doubleSpinBox_RotX->blockSignals(state);
	ui.doubleSpinBox_RotY->blockSignals(state);
	ui.doubleSpinBox_RotZ->blockSignals(state);
}

BezierSurfaceData::SurfaceType ModelowanieGeometryczne1::surfaceTypePopup() const
{
	QMessageBox msgBox;
	msgBox.setText("Choose type of Bezier Surface");
	QPushButton *planeButton = msgBox.addButton(tr("Plane"), QMessageBox::AcceptRole);
	QPushButton *cylinderButton = msgBox.addButton(tr("Cylinder"), QMessageBox::AcceptRole);
	msgBox.exec();
	if (msgBox.clickedButton() == cylinderButton)
	{
		return BezierSurfaceData::SurfaceType::cylinder;
	}
	if (msgBox.clickedButton() == planeButton)
	{
		return BezierSurfaceData::SurfaceType::plane;
	}
	return BezierSurfaceData::SurfaceType::plane;
}

void ModelowanieGeometryczne1::pushButton_AddObjectClicked()
{
	QString text = ui.comboBox_DrawableObjects->currentText();
	if (text == "BezierSurfaceC0" || text == "BezierSurfaceC2")
	{
		BezierSurfaceSettings *formBS = new BezierSurfaceSettings(this);
		formBS->initialize(surfaceTypePopup(), text);
		connect(formBS, SIGNAL(closing(BezierSurfaceData, const QString&)), this, SLOT(getBSData(BezierSurfaceData, const QString&)));
		formBS->setAttribute(Qt::WA_DeleteOnClose);
		formBS->show();
		ui.myGLWidget->updateGL();
		return;
	}
	m_scene.createDrawableObject(text);
	ui.myGLWidget->updateGL();
}

void ModelowanieGeometryczne1::pushButton_BSC0Clicked()
{
	UiBezierSurface *uiBezierSurface = static_cast<UiBezierSurface*>(m_scene.getUiConntector(ui.comboBox_BSC0->getSurfaceId()));
	if (uiBezierSurface == nullptr)
	{
		return;
	}
	BezierSurfaceSettings *formBS = new BezierSurfaceSettings(this);
	formBS->initialize(std::static_pointer_cast<BezierSurface>(uiBezierSurface->getObject())->getSurfaceData());
	connect(formBS, SIGNAL(closing(BezierSurfaceData, const QString&)), uiBezierSurface, SLOT(updateSurfaceData(BezierSurfaceData)));
	formBS->setAttribute(Qt::WA_DeleteOnClose);
	formBS->show();
	ui.myGLWidget->updateGL();
}

void ModelowanieGeometryczne1::pushButton_BSC2Clicked()
{
	UiBezierSurface *uiBezierSurface = static_cast<UiBezierSurface*>(m_scene.getUiConntector(ui.comboBox_BSC2->getSurfaceId()));
	if (uiBezierSurface == nullptr)
	{
		return;
	}
	BezierSurfaceSettings *formBS = new BezierSurfaceSettings(this);
	formBS->initialize(std::static_pointer_cast<BezierSurface>(uiBezierSurface->getObject())->getSurfaceData());
	connect(formBS, SIGNAL(closing(BezierSurfaceData, const QString&)), uiBezierSurface, SLOT(updateSurfaceData(BezierSurfaceData)));
	formBS->setAttribute(Qt::WA_DeleteOnClose);
	formBS->show();
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

void ModelowanieGeometryczne1::comboBox_BezierCurveC2Int_AddItem(const QString& name, int id, const UiBezierC2Interpolated* uiBezierC2Int)
{
	uiBezierC2Int->connectToUi(&ui);
	uiBezierC2Int->connectToScene(&m_scene);
	ui.comboBox_BC2Int->addItem(id, name);
}

void ModelowanieGeometryczne1::comboBox_BezierSurfaceC0_AddItem(const QString& name, int id, UiBezierSurfaceC0* uiBezierSurfaceC0)
{
	uiBezierSurfaceC0->connectToUi(&ui);
	uiBezierSurfaceC0->connectToScene(&m_scene);
	ui.comboBox_BSC0->addItem(id, name);
}

void ModelowanieGeometryczne1::comboBox_BezierSurfaceC2_AddItem(const QString& name, int id, UiBezierSurfaceC2* uiBezierSurfaceC2)
{
	uiBezierSurfaceC2->connectToUi(&ui);
	uiBezierSurfaceC2->connectToScene(&m_scene);
	ui.comboBox_BSC2->addItem(id, name);
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
		emit escKeyPressed();
		break;
	}
	case Qt::Key_1:
	{
		ui.radioButton_Idle->setChecked(true);
		break;
	}
	case Qt::Key_2:
	{
		ui.radioButton_Translate->setChecked(true);
		break;
	}
	case Qt::Key_3:
	{
		ui.radioButton_Add->setChecked(true);
		break;
	}
	case Qt::Key_4:
	{
		ui.radioButton_Delete->setChecked(true);
		break;
	}
	case 'X':
	{
		m_scene.showAxes('X');
		break;
	}
	case 'Y':
	{
		m_scene.showAxes('Y');
		break;
	}
	case 'Z':
	{
		m_scene.showAxes('Z');
		break;
	}
	}
}

void ModelowanieGeometryczne1::myGLWidgetMouseMoved(QMouseEvent *event)
{
	float dx = event->x() - m_scene.m_camera.m_mousePos.x();
	float dy = event->y() - m_scene.m_camera.m_mousePos.y();
	if (event->buttons() & Qt::MiddleButton)
	{
		m_scene.m_camera.mouseMoved(dx, dy);
	}
	if (m_scene.m_isCursor3d)
	{
		m_scene.updateCursorPosition(event->x(), event->y(), ui.myGLWidget->getWidth(), ui.myGLWidget->getHeight(), QGuiApplication::keyboardModifiers() & Qt::ControlModifier);
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
		if (QGuiApplication::keyboardModifiers() & Qt::ControlModifier)
		{
			emit mouseClicked(true);
		}
		else
		{
			emit mouseClicked();
		}
		//emit mousePressed();
		/*int id = m_scene.updateCursor();
		if (id != -1)
		{
			emit cursor3dItemAcquired(id);
		}*/
	}
	ui.myGLWidget->updateGL();
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
		ui.verticalLayout_BC0->removeWidget(uibc0->getCBPolyline());
		uibc0->getCBPolyline()->hide();
	}
	uibc0 = static_cast<const UiBezierCurveC0*>(m_scene.getUiConntector(currId));
	if (uibc0 != nullptr)
	{
		uibc0->getCBPolyline()->show();
		ui.verticalLayout_BC0->addWidget(uibc0->getCBPolyline());
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

void ModelowanieGeometryczne1::showBSC0CheckBoxes(int currId, int prevId)
{
	UiBezierSurfaceC0 *uibsc0 = static_cast<UiBezierSurfaceC0*>(m_scene.getUiConntector(prevId));
	if (uibsc0 != nullptr)
	{
		uibsc0->getCBBezierGrid()->hide();
		ui.verticalLayout_BSC0->removeWidget(uibsc0->getCBBezierGrid());
		uibsc0->getCBControlGrid()->hide();
		ui.verticalLayout_BSC0->removeWidget(uibsc0->getCBControlGrid());
	}
	uibsc0 = static_cast<UiBezierSurfaceC0*>(m_scene.getUiConntector(currId));
	if (uibsc0 != nullptr)
	{
		uibsc0->getCBBezierGrid()->show();
		ui.verticalLayout_BSC0->addWidget(uibsc0->getCBBezierGrid());
		uibsc0->getCBControlGrid()->show();
		ui.verticalLayout_BSC0->addWidget(uibsc0->getCBControlGrid());
	}
}

void ModelowanieGeometryczne1::showBSC2CheckBoxes(int currId, int prevId)
{
	UiBezierSurfaceC2 *uibsc2 = static_cast<UiBezierSurfaceC2*>(m_scene.getUiConntector(prevId));
	if (uibsc2 != nullptr)
	{
		uibsc2->getCBBezierGrid()->hide();
		ui.verticalLayout_BSC2->removeWidget(uibsc2->getCBBezierGrid());
		uibsc2->getCBControlGrid()->hide();
		ui.verticalLayout_BSC2->removeWidget(uibsc2->getCBControlGrid());
	}
	uibsc2 = static_cast<UiBezierSurfaceC2*>(m_scene.getUiConntector(currId));
	if (uibsc2 != nullptr)
	{
		uibsc2->getCBBezierGrid()->show();
		ui.verticalLayout_BSC2->addWidget(uibsc2->getCBBezierGrid());
		uibsc2->getCBControlGrid()->show();
		ui.verticalLayout_BSC2->addWidget(uibsc2->getCBControlGrid());
	}
}

void ModelowanieGeometryczne1::showBC2IntCheckBoxes(int currId, int prevId)
{
	UiBezierC2Interpolated *uibc2Int = static_cast<UiBezierC2Interpolated*>(m_scene.getUiConntector(prevId));
	if (uibc2Int != nullptr)
	{
		uibc2Int->getCBPolyline()->hide();
		ui.verticalLayout_BC2Int->removeWidget(uibc2Int->getCBPolyline());
	}
	uibc2Int = static_cast<UiBezierC2Interpolated*>(m_scene.getUiConntector(currId));
	if (uibc2Int != nullptr)
	{
		uibc2Int->getCBPolyline()->show();
		ui.verticalLayout_BC2Int->addWidget(uibc2Int->getCBPolyline());
	}
}

void ModelowanieGeometryczne1::radioBtnIdleToggled(bool checked)
{
	if (checked)
		m_scene.m_cursor->changeMode(Cursor3D::Mode::Idle);
}

void ModelowanieGeometryczne1::radioBtnTranslateToggled(bool checked)
{
	if (checked)
		m_scene.m_cursor->changeMode(Cursor3D::Mode::Translate);
}

void ModelowanieGeometryczne1::radioBtnAddToggled(bool checked)
{
	if (checked)
		m_scene.m_cursor->changeMode(Cursor3D::Mode::Add);
}

void ModelowanieGeometryczne1::radioBtnDeleteToggled(bool checked)
{
	if (checked)
		m_scene.m_cursor->changeMode(Cursor3D::Mode::Delete);
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

void ModelowanieGeometryczne1::getBSData(BezierSurfaceData data, const QString &name)
{
	if (name == "BezierSurfaceC0")
	{
		m_scene.createBezierSurfaceC0(data);
	}
	else if (name == "BezierSurfaceC2")
	{
		m_scene.createBezierSurfaceC2(data);
	}
}

void ModelowanieGeometryczne1::getObjectDetails(QList<int>& objectsIds)
{
	m_prevActiveObjectId = m_activeObjectId;
	m_activeObjectId = objectsIds.at(0);
	auto object = m_scene.getUiConntector(m_activeObjectId);
	if (object == nullptr || m_prevActiveObjectId == m_activeObjectId)
	{
		return;
	}
	QVector3D pos = object->getObject()->getPosition();
	setDetailSpinboxesSignalsState(true);
	ui.doubleSpinBox_PosX->setValue(pos.x());
	ui.doubleSpinBox_PosY->setValue(pos.y());
	ui.doubleSpinBox_PosZ->setValue(pos.z());
	QVector3D rot = object->getObject()->getRotation();
	ui.doubleSpinBox_RotX->setValue(rot.x());
	ui.doubleSpinBox_RotY->setValue(rot.y());
	ui.doubleSpinBox_RotZ->setValue(rot.z());
	setDetailSpinboxesSignalsState(false);
}

void ModelowanieGeometryczne1::doubleSpinbox_PosXValueChanged(double val)
{
	auto object = m_scene.getUiConntector(m_activeObjectId);
	if (object == nullptr)
	{
		return;
	}
	object->getObject()->setPosition(QVector3D(val, ui.doubleSpinBox_PosY->value(), ui.doubleSpinBox_PosZ->value()));
	updateMyGLWidget();
}

void ModelowanieGeometryczne1::doubleSpinbox_PosYValueChanged(double val)
{
	auto object = m_scene.getUiConntector(m_activeObjectId);
	if (object == nullptr)
	{
		return;
	}
	object->getObject()->setPosition(QVector3D(ui.doubleSpinBox_PosX->value(), val, ui.doubleSpinBox_PosZ->value()));
	updateMyGLWidget();
}

void ModelowanieGeometryczne1::doubleSpinbox_PosZValueChanged(double val)
{
	auto object = m_scene.getUiConntector(m_activeObjectId);
	if (object == nullptr)
	{
		return;
	}
	object->getObject()->setPosition(QVector3D(ui.doubleSpinBox_PosX->value(), ui.doubleSpinBox_PosY->value(), val));
	updateMyGLWidget();
}

void ModelowanieGeometryczne1::doubleSpinbox_RotXValueChanged(double val)
{
	auto object = m_scene.getUiConntector(m_activeObjectId);
	if (object == nullptr)
	{
		return;
	}
	object->getObject()->rotate(QVector3D(val, ui.doubleSpinBox_RotY->value(), ui.doubleSpinBox_RotZ->value()));
	updateMyGLWidget();
}

void ModelowanieGeometryczne1::doubleSpinbox_RotYValueChanged(double val)
{
	auto object = m_scene.getUiConntector(m_activeObjectId);
	if (object == nullptr)
	{
		return;
	}
	object->getObject()->rotate(QVector3D(ui.doubleSpinBox_RotX->value(), val, ui.doubleSpinBox_RotZ->value()));
	updateMyGLWidget();
}

void ModelowanieGeometryczne1::doubleSpinbox_RotZValueChanged(double val)
{
	auto object = m_scene.getUiConntector(m_activeObjectId);
	if (object == nullptr)
	{
		return;
	}
	object->getObject()->rotate(QVector3D(ui.doubleSpinBox_RotX->value(), ui.doubleSpinBox_RotY->value(), val));
	updateMyGLWidget();
}

void ModelowanieGeometryczne1::doubleSpinbox_CursorXValueChanged(double val)
{
	m_scene.m_cursor->setPosition(QVector3D(ui.doubleSpinBox_CursorX->value(), ui.doubleSpinBox_CursorY->value(), ui.doubleSpinBox_CursorZ->value()));
}

void ModelowanieGeometryczne1::doubleSpinbox_CursorYValueChanged(double val)
{
	m_scene.m_cursor->setPosition(QVector3D(ui.doubleSpinBox_CursorX->value(), ui.doubleSpinBox_CursorY->value(), ui.doubleSpinBox_CursorZ->value()));
}

void ModelowanieGeometryczne1::doubleSpinbox_CursorZValueChanged(double val)
{
	m_scene.m_cursor->setPosition(QVector3D(ui.doubleSpinBox_CursorX->value(), ui.doubleSpinBox_CursorY->value(), ui.doubleSpinBox_CursorZ->value()));
}

void ModelowanieGeometryczne1::pushButton_IntersectionsClicked()
{/*
	std::shared_ptr<BezierSurface> surface = std::static_pointer_cast<BezierSurface>(m_scene.getUiConntector(1)->getObject());
	QVector3D testpoint = QVector3D(0.4f, 0.4f, -0.4f);
	int id = m_scene.createDrawableObject("Point3D");
	m_scene.getUiConntector(id)->getObject()->setPosition(testpoint);
	m_scene.getUiConntector(id)->getObject()->setName("testpoint");
	m_scene.getUiConntector(id)->getObject()->setColor(float3(0, 255, 0));
	QVector2D d = Intersections::findClosestPoint(surface, testpoint);
	QVector3D curorPos = m_scene.m_cursor->getPosition();
	QVector3D point = surface->getPointByUV(d.x(), d.y());
	id = m_scene.createDrawableObject("Point3D");
	m_scene.getUiConntector(id)->getObject()->setPosition(point);
	m_scene.getUiConntector(id)->getObject()->setName("IntersectionPoint");
	m_scene.getUiConntector(id)->getObject()->setColor(float3(255,0,0));*/
}

void ModelowanieGeometryczne1::loadScene()
{
	QString filename = QFileDialog::getOpenFileName(this,
		tr("Open scene file"), "",
		tr("Scene files (*.json)"));
	if (filename.isEmpty())
	{
		return;
	}
	QFile file(filename);

	if (!file.open(QIODevice::ReadOnly))
	{
		QMessageBox::information(this, tr("Unable to open file"),
			file.errorString());
		return;
	}
	QString fileContent = file.readAll();
	emit loadedFile(fileContent);
}

void ModelowanieGeometryczne1::saveScene()
{

}
