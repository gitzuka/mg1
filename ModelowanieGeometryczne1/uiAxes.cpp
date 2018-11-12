#include "uiAxes.h"
#include "axes.h"

UiAxes::UiAxes(std::shared_ptr<Axes> axes) : m_axes(axes)
{
}

void UiAxes::connectToUi(const Ui_ModelowanieGeometryczne1Class * ui) const
{
}

std::shared_ptr<DrawableObject> UiAxes::getObject()
{
	return m_axes;
}

void UiAxes::changeName(const QString& name, int id)
{
}
