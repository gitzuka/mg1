#include "uiBezierSurfaceC2.h"
#include "scene.h"

UiBezierSurfaceC2::UiBezierSurfaceC2(std::shared_ptr<BezierSurfaceC2> bezierSurfaceC2) : UiBezierSurface(bezierSurfaceC2),
	m_bezierSurfaceC2(bezierSurfaceC2)
{
}

void UiBezierSurfaceC2::connectToUi(const Ui_ModelowanieGeometryczne1Class* ui) const
{
}

void UiBezierSurfaceC2::connectToScene(const Scene* scene) const
{
	QObject::connect(scene, &Scene::update, this, &UiBezierSurface::updateSurface);
}
