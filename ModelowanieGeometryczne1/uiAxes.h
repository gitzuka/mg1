#pragma once
#include "uiConnector.h"
class Axes;

///this is a "dummy class"
class UiAxes : public UiConnector
{
	Q_OBJECT
public:
	explicit UiAxes(std::shared_ptr<Axes> axes);
	void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const override;
	std::shared_ptr<DrawableObject> getObject() override;

private:
	std::shared_ptr<Axes> m_axes;

public slots:
	void changeName(const QString &name, int id) override;
};