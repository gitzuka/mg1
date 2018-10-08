#pragma once
#include "uiConnector.h"

class TrimmingCurve;
class UiTrimmingCurve : public UiConnector
{
	Q_OBJECT

public:
	explicit UiTrimmingCurve(std::shared_ptr<TrimmingCurve> trimmingCurve);

	void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const override;
	std::shared_ptr<DrawableObject> getObject() override;

public slots:
	void changeName(const QString &name, int id) override;

private:
	std::shared_ptr<TrimmingCurve> m_trimmingCurve;

signals:
	void nameChanged(int id, const QString &name);
};
