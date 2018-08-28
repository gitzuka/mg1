#include "bezierSurfaceSettings.h"
#include "bezierSurface.h"

BezierSurfaceSettings::BezierSurfaceSettings(QWidget* parent)
{
	ui.setupUi(this);
}

BezierSurfaceSettings::~BezierSurfaceSettings()
{
}

Ui::FormBSSettings* BezierSurfaceSettings::getUi()
{
	return &ui;
}

void BezierSurfaceSettings::initialize(BezierSurfaceData::SurfaceType type, const QString &name)
{
	m_name = name;
	if (type == BezierSurfaceData::SurfaceType::plane)
	{
		ui.doubleSpinBox_h->setEnabled(false);
		ui.doubleSpinBox_r->setEnabled(false);
	}
	m_data.m_surfaceType = type;
	connect(ui.pushButton_BSSettings, SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui.pushButton_BSSettings, SIGNAL(clicked()), this, SLOT(hide()));
}

void BezierSurfaceSettings::initialize(BezierSurfaceData data)
{
	if (data.m_surfaceType == BezierSurfaceData::SurfaceType::plane)
	{
		ui.doubleSpinBox_h->setEnabled(false);
		ui.doubleSpinBox_r->setEnabled(false);
		ui.spinBox_patchesX->setEnabled(false);
		ui.spinBox_patchesY->setEnabled(false);
	}
	ui.doubleSpinBox_h->setValue(data.m_height);
	ui.doubleSpinBox_r->setValue(data.m_radius);
	ui.spinBox_V->setValue(data.m_v);
	ui.spinBox_u->setValue(data.m_u);
	ui.spinBox_patchesX->setValue(data.m_patchesX);
	ui.spinBox_patchesY->setValue(data.m_patchesY);
	connect(ui.pushButton_BSSettings, SIGNAL(clicked()), this, SLOT(buttonClicked()));
	connect(ui.pushButton_BSSettings, SIGNAL(clicked()), this, SLOT(hide()));
}

void BezierSurfaceSettings::buttonClicked()
{
	m_data.m_u = ui.spinBox_u->value();
	m_data.m_v = ui.spinBox_V->value();
	m_data.m_patchesX = ui.spinBox_patchesX->value();
	m_data.m_patchesY = ui.spinBox_patchesY->value();
	m_data.m_radius = ui.doubleSpinBox_r->value();
	m_data.m_height = ui.doubleSpinBox_h->value();
	emit closing(m_data, m_name);
	this->close();
}
