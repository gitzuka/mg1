#ifndef MODELOWANIEGEOMETRYCZNE1_H
#define MODELOWANIEGEOMETRYCZNE1_H

#include <QtWidgets/QMainWindow>
#include "ui_modelowaniegeometryczne1.h"
#include "scene.h"

class ModelowanieGeometryczne1 : public QMainWindow
{
	Q_OBJECT

public:
	ModelowanieGeometryczne1(QWidget *parent = 0);
	~ModelowanieGeometryczne1();

	//QList<QPair<QListWidgetItem*, int>> m_objectsList;

private:
	Scene m_scene;
	Ui::ModelowanieGeometryczne1Class ui;
	QStringListModel *model;
	QStringList ui_drawableObjects = { "Torus", "Point3D", "BezierCurveC0" };
	//QList<int> m_torusIds;
	//QList<int> m_bezierCurveC0Ids;
	QList<int> m_selectedObjectsIds;

	//void updatePointsList(int id);
	void connectSignals();
	void label_3dCoordsChangeText(float x, float y, float z);
	//int findItemId(QListWidgetItem* item) const;

signals:
	void cursor3dItemAcquired(int);

private slots:
	void pushButton_AddObjectClicked();
	//void listWidget_itemClicked(QListWidgetItem *item);
	void label_screenCoordsChangeText(QMouseEvent *event);
	//void highlightItem(int id);
	//void listWidget_itemRightClicked(const QPoint &point) const;
	void comboBox_Torus_AddItem(QString name, int id, const std::shared_ptr<Torus> &object);
	void comboBox_BezierCurveC0_AddItem(const QString &name, int id, const std::shared_ptr<BezierCurveC0> &object);
	//void point3dItemAdded(int id);
	//void comboBox_BezierCurveC0DisplayPoints(int id);
	void myGLWidgetKeyPressed(QKeyEvent *event);
	void myGLWidgetMouseMoved(QMouseEvent *event);
	void myGLWidgetMousePressed(QMouseEvent *event);
	void updateMyGLWidget();

	void doubleSpinbox_eValueChanged(double e);
	void stereo_button_toggled(bool checked);
	//void checkBox_pointerStateChanged(int checked);
	//void createCurveC0fromPoints(const QList<int> &ids);
};

#endif // MODELOWANIEGEOMETRYCZNE1_H
