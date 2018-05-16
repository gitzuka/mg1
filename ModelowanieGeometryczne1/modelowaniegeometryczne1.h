#ifndef MODELOWANIEGEOMETRYCZNE1_H
#define MODELOWANIEGEOMETRYCZNE1_H

#include <QtWidgets/QMainWindow>
#include "ui_modelowaniegeometryczne1.h"
#include "scene.h"

class UiPoint3D;
class UiTorus;

class ModelowanieGeometryczne1 : public QMainWindow
{
	Q_OBJECT

public:
	ModelowanieGeometryczne1(QWidget *parent = 0);
	~ModelowanieGeometryczne1();

private:
	Scene m_scene;
	Ui::ModelowanieGeometryczne1Class ui;
	QStringListModel *model;
	QStringList ui_drawableObjects = { "Torus", "Point3D", "BezierCurveC0", "BezierCurveC2" };
	QList<int> m_selectedObjectsIds;

	void connectSignals();
	void label_3dCoordsChangeText(float x, float y, float z);

signals:
	void cursor3dItemAcquired(int);

private slots:
	void pushButton_AddObjectClicked();
	void label_screenCoordsChangeText(QMouseEvent *event);
	void comboBox_Torus_AddItem(const QString &name, int id, const UiTorus *uiTorus);
	void comboBox_BezierCurveC0_AddItem(const QString &name, int id, const UiBezierCurveC0 *uiBezierC0);
	void comboBox_BezierCurveC2_AddItem(const QString &name, int id, const UiBezierCurveC2 *uiBezierC2);
	void connectPoint3D(const QString &name, int id, const UiPoint3D *uiPoint3d);
	void myGLWidgetKeyPressed(QKeyEvent *event);
	void myGLWidgetMouseMoved(QMouseEvent *event);
	void myGLWidgetMousePressed(QMouseEvent *event);
	void updateMyGLWidget();
	void showBC0CheckBoxes(int currId, int prevId);
	void showBC2CheckBoxes(int currId, int prevId);

	void doubleSpinbox_eValueChanged(double e);
	void stereo_button_toggled(bool checked);
};

#endif // MODELOWANIEGEOMETRYCZNE1_H
