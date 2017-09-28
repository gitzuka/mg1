#include "listwidgetparameters.h"

ListWidgetParameters::ListWidgetParameters(QWidget* parent)
	: QListWidget(parent)
{
}

ListWidgetParameters::~ListWidgetParameters()
{
}

void ListWidgetParameters::mousePressEvent(QMouseEvent * event)
{
}

void ListWidgetParameters::pointAddedToBC0(int id)
{
	this->addItem("test");
}

void ListWidgetParameters::pointRemovedFromBC0(int id)
{
}

void ListWidgetParameters::updatePointName(QString name, int id)
{
	//for (int i=0; i<)
}

void ListWidgetParameters::comboBox_BezierCurveC0DisplayPoints(int id)
{
	int i = 0;
}