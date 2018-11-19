#include "formPV.h"
#include "drawableObject.h"
FormPV::FormPV(QWidget* parent)
{
	ui.setupUi(this);
}

void FormPV::initialize(const QString& name1, const QString& name2, const QVector4D& uvRange1, const QVector4D& uvRange2, const std::vector<QVector4D> &parametrization)
{
	ui.label_Name1->setText(name1);
	ui.label_Name2->setText(name2);
	ui.label_U1->setText(QString::number(uvRange1.x()) + ", " + QString::number(uvRange1.y()));
	ui.label_U2->setText(QString::number(uvRange2.z()) + ", " + QString::number(uvRange2.w()));
	ui.label_V1->setText(QString::number(uvRange1.x()) + ", " + QString::number(uvRange1.y()));
	ui.label_V2->setText(QString::number(uvRange2.z()) + ", " + QString::number(uvRange2.w()));
	QPair<bool, bool> trim = ui.parametrizationViewer->fillPixMap(parametrization, uvRange1, uvRange2);
	if (trim.first)
		ui.label_Trim1->setText("true");
	else
		ui.label_Trim1->setText("false");
	if (trim.second)
		ui.label_Trim2->setText("true");
	else
		ui.label_Trim2->setText("false");
	ui.graphicsView->setScene(ui.parametrizationViewer->getScene());
	ui.graphicsView_2->setScene(ui.parametrizationViewer->getScene2());
}
