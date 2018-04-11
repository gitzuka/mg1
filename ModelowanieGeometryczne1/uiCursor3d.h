#pragma once
#include "uiConnector.h"
class Cursor3D;

class UiCursor3D : public UiConnector
{
	Q_OBJECT
public:
	explicit UiCursor3D(std::shared_ptr<Cursor3D> cursor3d);
	void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const override;

private:
	std::shared_ptr<Cursor3D> m_cursor3d;
};