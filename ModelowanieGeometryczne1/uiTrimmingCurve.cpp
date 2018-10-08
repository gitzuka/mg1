#include "uiTrimmingCurve.h"
#include "trimmingCurve.h"

UiTrimmingCurve::UiTrimmingCurve(std::shared_ptr<TrimmingCurve> trimmingCurve) : m_trimmingCurve(trimmingCurve)
{
}

void UiTrimmingCurve::connectToUi(const Ui_ModelowanieGeometryczne1Class* ui) const
{
}

std::shared_ptr<DrawableObject> UiTrimmingCurve::getObject()
{
	return m_trimmingCurve;
}

void UiTrimmingCurve::changeName(const QString& name, int id)
{
	if (id != m_trimmingCurve->getId())
		return;
	m_trimmingCurve->setName(name);
	emit nameChanged(m_trimmingCurve->getId(), name);
}
