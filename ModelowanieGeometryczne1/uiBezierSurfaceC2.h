#pragma once
#include "uiBezierSurface.h"
#include "bezierSurfaceC2.h"

class UiBezierSurfaceC2 : public UiBezierSurface
{
public:
	explicit UiBezierSurfaceC2(std::shared_ptr<BezierSurfaceC2> bezierSurfaceC2);
	~UiBezierSurfaceC2();

	void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const override;
	void connectToScene(const Scene *scene) const override;

private:
	std::shared_ptr<BezierSurfaceC2> m_bezierSurfaceC2;
};
