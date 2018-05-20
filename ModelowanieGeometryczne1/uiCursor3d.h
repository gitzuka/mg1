#pragma once
#include "uiConnector.h"
class Cursor3D;

///this is a "dummy class", all slots/signals for cursor3d should be handled in scene
class UiCursor3D : public UiConnector
{
	Q_OBJECT
public:
	explicit UiCursor3D(std::shared_ptr<Cursor3D> cursor3d);
	void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const override;
	std::shared_ptr<DrawableObject> getObject() override;

private:
	std::shared_ptr<Cursor3D> m_cursor3d;

public slots:
	void changeName(const QString &name, int id) override;
};