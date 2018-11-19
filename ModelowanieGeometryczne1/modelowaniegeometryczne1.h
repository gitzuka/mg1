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
	QStringList ui_drawableObjects =
	{ 
		"Torus", "Point3D", "BezierCurveC0", "BezierCurveC2", "BezierC2Interpolated", "BezierSurfaceC0", "BezierSurfaceC2" 
	};
	QList<int> m_selectedObjectsIds;
	int m_activeObjectId;
	int m_prevActiveObjectId;

	void connectSignals();
	void label_3dCoordsChangeText(float x, float y, float z);
	void setDetailSpinboxesSignalsState(bool state);
	BezierSurfaceData::SurfaceType surfaceTypePopup() const;
	

signals:
	void cursor3dItemAcquired(int);
	void escKeyPressed();
	void mouseClicked(bool multiple = false);
	void loadedFile(const QString &fileContent);
	void saveFile(const QString &path);

private slots:
	void pushButton_AddObjectClicked();
	void pushButton_BSC0Clicked();
	void pushButton_BSC2Clicked();
	void label_screenCoordsChangeText(QMouseEvent *event);
	void comboBox_Torus_AddItem(const QString &name, int id, const UiTorus *uiTorus);
	void comboBox_BezierCurveC0_AddItem(const QString &name, int id, const UiBezierCurveC0 *uiBezierC0);
	void comboBox_BezierCurveC2_AddItem(const QString &name, int id, const UiBezierCurveC2 *uiBezierC2);
	void comboBox_BezierCurveC2Int_AddItem(const QString &name, int id, const UiBezierC2Interpolated *uiBezierC2Int);
	void comboBox_BezierSurfaceC0_AddItem(const QString &name, int id, UiBezierSurfaceC0 *uiBezierSurfaceC0);
	void comboBox_BezierSurfaceC2_AddItem(const QString &name, int id, UiBezierSurfaceC2 *uiBezierSurfaceC2);
	void connectPoint3D(const QString &name, int id, const UiPoint3D *uiPoint3d);
	void myGLWidgetKeyPressed(QKeyEvent *event);
	void myGLWidgetMouseMoved(QMouseEvent *event);
	void myGLWidgetMousePressed(QMouseEvent *event);
	void updateMyGLWidget();
	void showBC0CheckBoxes(int currId, int prevId);
	void showBC2CheckBoxes(int currId, int prevId);
	void showBSC0CheckBoxes(int currId, int prevId);
	void showBSC2CheckBoxes(int currId, int prevId);
	void showBC2IntCheckBoxes(int currId, int prevId);
	void radioBtnIdleToggled(bool checked);
	void radioBtnTranslateToggled(bool checked);
	void radioBtnAddToggled(bool checked);
	void radioBtnDeleteToggled(bool checked);
	void doubleSpinbox_eValueChanged(double e);
	void stereo_button_toggled(bool checked);
	void getBSData(BezierSurfaceData data, const QString &name);
	void getObjectDetails(QList<int> &objectsIds);
	void doubleSpinbox_PosXValueChanged(double val);
	void doubleSpinbox_PosYValueChanged(double val);
	void doubleSpinbox_PosZValueChanged(double val);
	void doubleSpinbox_RotXValueChanged(double val);
	void doubleSpinbox_RotYValueChanged(double val);
	void doubleSpinbox_RotZValueChanged(double val);
	void doubleSpinbox_CursorXValueChanged(double val);
	void doubleSpinbox_CursorYValueChanged(double val);
	void doubleSpinbox_CursorZValueChanged(double val);
	void pushButton_IntersectionsClicked();
	void loadScene();
	void saveScene();
	void showParametrizationViewer(const std::vector<QVector4D> &parametrization, const QVector4D &uvRange1, const QVector4D &uvRange2, const QString& name1, const QString& name2);
};

#endif // MODELOWANIEGEOMETRYCZNE1_H
