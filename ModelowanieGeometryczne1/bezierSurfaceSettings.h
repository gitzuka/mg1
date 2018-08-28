#pragma once
#ifndef BEZIERCSURFACESETTINGS_H
#define BEZIERCSURFACESETTINGS_H
#include "ui_bezierSurfaceSettings.h"
#include "bezierSurface.h"

class BezierSurfaceSettings : public QDialog
{
	Q_OBJECT
public:
	explicit BezierSurfaceSettings(QWidget *parent = 0);
	~BezierSurfaceSettings();

	Ui::FormBSSettings* getUi();
	//initialize when creating new BezierSurface object
	void initialize(BezierSurfaceData::SurfaceType type, const QString &name);
	//initializes UI with BezierSurfaceData (when editing)
	void initialize(BezierSurfaceData data);

private:
	Ui::FormBSSettings ui;
	BezierSurfaceData m_data;
	QString m_name;

signals:
	void closing(BezierSurfaceData data, const QString &name);

private slots:
	void buttonClicked();
};

#endif
