#pragma once
#include "uiBezierSurface.h"
#include "BezierSurfaceC0.h"

class UiBezierSurfaceC0 : public UiBezierSurface
{
public:
	explicit UiBezierSurfaceC0(std::shared_ptr<BezierSurfaceC0> bezierSurfaceC0, bool loaded = false);
	~UiBezierSurfaceC0();

	void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const override;
	void connectToScene(const Scene *scene) const override;

private:
	std::shared_ptr<BezierSurfaceC0> m_bezierSurfaceC0;

};
