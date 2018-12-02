#include "formPV.h"
#include "drawableObject.h"
#include "bezierSurface.h"
#include "torus.h"

FormPV::FormPV(QWidget* parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_Trim1, SIGNAL(clicked()), this, SLOT(buttonTrim1Clicked()));
	connect(ui.pushButton_Trim2, SIGNAL(clicked()), this, SLOT(buttonTrim2Clicked()));
	connect(ui.pushButton_TrimExt1, SIGNAL(clicked()), this, SLOT(buttonTrimExt1Clicked()));
	connect(ui.pushButton_TrimExt2, SIGNAL(clicked()), this, SLOT(buttonTrimExt2Clicked()));
	connect(ui.pushButton_noTrim1, SIGNAL(clicked()), this, SLOT(buttonNoTrim1()));
	connect(ui.pushButton_2, SIGNAL(clicked()), this, SLOT(buttonNoTrim2()));
}

void FormPV::initialize(std::shared_ptr<DrawableObject> surface1, std::shared_ptr<DrawableObject> surface2,
	const QVector4D& uvRange1, const QVector4D& uvRange2,
	const std::vector<QVector4D>& parametrization,
	QPair<bool, bool> s1Wrap, QPair<bool, bool> s2Wrap)
{
	ui.label_Name1->setText(surface1->getName());
	ui.label_Name2->setText(surface2->getName());
	ui.label_U1->setText(QString::number(uvRange1.x()) + ", " + QString::number(uvRange1.y()));
	ui.label_U2->setText(QString::number(uvRange2.z()) + ", " + QString::number(uvRange2.w()));
	ui.label_V1->setText(QString::number(uvRange1.x()) + ", " + QString::number(uvRange1.y()));
	ui.label_V2->setText(QString::number(uvRange2.z()) + ", " + QString::number(uvRange2.w()));
	QPair<bool, bool> trim = ui.parametrizationViewer->fillPixMap(parametrization, uvRange1, uvRange2, m_map1, m_map2, s1Wrap, s2Wrap);
	ui.pushButton_Trim1->setEnabled(trim.first);
	ui.pushButton_TrimExt1->setEnabled(trim.first);
	ui.pushButton_Trim2->setEnabled(trim.second);
	ui.pushButton_TrimExt2->setEnabled(trim.second);
	ui.graphicsView->setScene(ui.parametrizationViewer->getScene());
	ui.graphicsView_2->setScene(ui.parametrizationViewer->getScene2());
	m_surface1 = surface1;
	m_surface2 = surface2;
}

void FormPV::buttonTrim1Clicked()
{
	if (m_surface1->m_type == DrawableObject::ObjectType::bezierSurfaceC0 || m_surface1->m_type == DrawableObject::ObjectType::bezierSurfaceC2)
	{
		std::static_pointer_cast<BezierSurface>(m_surface1)->trimSurface(m_map1, true);
	}
	if (m_surface1->m_type == DrawableObject::ObjectType::torus)
	{
		std::static_pointer_cast<Torus>(m_surface1)->trim(m_map1, true);
	}
}

void FormPV::buttonTrim2Clicked()
{
	if (m_surface2->m_type == DrawableObject::ObjectType::bezierSurfaceC0 || m_surface2->m_type == DrawableObject::ObjectType::bezierSurfaceC2)
	{
		std::static_pointer_cast<BezierSurface>(m_surface2)->trimSurface(m_map2, true);
	}
	else if (m_surface2->m_type == DrawableObject::ObjectType::torus)
	{
		std::static_pointer_cast<Torus>(m_surface2)->trim(m_map2, true);
	}
}

void FormPV::buttonTrimExt1Clicked()
{
	if (m_surface1->m_type == DrawableObject::ObjectType::bezierSurfaceC0 || m_surface1->m_type == DrawableObject::ObjectType::bezierSurfaceC2)
	{
		std::static_pointer_cast<BezierSurface>(m_surface1)->trimSurface(m_map1, false);
	}
	if (m_surface1->m_type == DrawableObject::ObjectType::torus)
	{
		std::static_pointer_cast<Torus>(m_surface1)->trim(m_map1, false);
	}
}

void FormPV::buttonTrimExt2Clicked()
{
	if (m_surface2->m_type == DrawableObject::ObjectType::bezierSurfaceC0 || m_surface2->m_type == DrawableObject::ObjectType::bezierSurfaceC2)
	{
		std::static_pointer_cast<BezierSurface>(m_surface2)->trimSurface(m_map2, false);
	}
	else if (m_surface2->m_type == DrawableObject::ObjectType::torus)
	{
		std::static_pointer_cast<Torus>(m_surface2)->trim(m_map2, false);
	}
}

void FormPV::buttonNoTrim1()
{
	if (m_surface1->m_type == DrawableObject::ObjectType::bezierSurfaceC0 || m_surface1->m_type == DrawableObject::ObjectType::bezierSurfaceC2)
	{
		std::static_pointer_cast<BezierSurface>(m_surface1)->undoTrimming();
	}
	else if (m_surface1->m_type == DrawableObject::ObjectType::torus)
	{
		std::static_pointer_cast<Torus>(m_surface1)->undoTrimming();
	}
}

void FormPV::buttonNoTrim2()
{
	if (m_surface2->m_type == DrawableObject::ObjectType::bezierSurfaceC0 || m_surface2->m_type == DrawableObject::ObjectType::bezierSurfaceC2)
	{
		std::static_pointer_cast<BezierSurface>(m_surface2)->undoTrimming();
	}
	else if (m_surface2->m_type == DrawableObject::ObjectType::torus)
	{
		std::static_pointer_cast<Torus>(m_surface2)->undoTrimming();
	}
}
