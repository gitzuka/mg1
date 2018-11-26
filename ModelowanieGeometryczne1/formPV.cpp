#include "formPV.h"
#include "drawableObject.h"
#include "bezierSurface.h"

FormPV::FormPV(QWidget* parent)
{
	ui.setupUi(this);
	connect(ui.pushButton_Trim1, SIGNAL(clicked()), this, SLOT(buttonTrim1Clicked()));
	connect(ui.pushButton_Trim2, SIGNAL(clicked()), this, SLOT(buttonTrim2Clicked()));
}

void FormPV::initialize(std::shared_ptr<DrawableObject> surface1, std::shared_ptr<DrawableObject> surface2, const QVector4D& uvRange1, const QVector4D& uvRange2, const std::vector<QVector4D> &parametrization)
{
	ui.label_Name1->setText(surface1->getName());
	ui.label_Name2->setText(surface2->getName());
	ui.label_U1->setText(QString::number(uvRange1.x()) + ", " + QString::number(uvRange1.y()));
	ui.label_U2->setText(QString::number(uvRange2.z()) + ", " + QString::number(uvRange2.w()));
	ui.label_V1->setText(QString::number(uvRange1.x()) + ", " + QString::number(uvRange1.y()));
	ui.label_V2->setText(QString::number(uvRange2.z()) + ", " + QString::number(uvRange2.w()));
	QPair<bool, bool> trim = ui.parametrizationViewer->fillPixMap(parametrization, uvRange1, uvRange2, m_map1, m_map2);
	ui.pushButton_Trim1->setEnabled(trim.first);
	ui.pushButton_Trim2->setEnabled(trim.second);
	ui.graphicsView->setScene(ui.parametrizationViewer->getScene());
	ui.graphicsView_2->setScene(ui.parametrizationViewer->getScene2());
	m_surface1 = surface1;
	m_surface2 = surface2;
}

void FormPV::buttonTrim1Clicked()
{
	if (m_surface1->m_type == DrawableObject::ObjectType::bezierSurfaceC0 || m_surface1->m_type == DrawableObject::ObjectType::bezierSurfaceC2)
	{
		std::static_pointer_cast<BezierSurface>(m_surface1)->trimSurface(m_map1);
	}
}

void FormPV::buttonTrim2Clicked()
{
	if (m_surface2->m_type == DrawableObject::ObjectType::bezierSurfaceC0 || m_surface2->m_type == DrawableObject::ObjectType::bezierSurfaceC2)
	{
		std::static_pointer_cast<BezierSurface>(m_surface2)->trimSurface(m_map2);
	}
}
