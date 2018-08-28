#include "uiBezierSurface.h"

UiBezierSurface::UiBezierSurface(std::shared_ptr<BezierSurface> bezierSurface) : m_bezierSurface(bezierSurface)
{
	updateSurfaceData(m_bezierSurface->m_parameters);
	/*m_bezierSurface->initialize(m_bezierSurface->m_parameters);
	updateSurface();*/
}

UiBezierSurface::~UiBezierSurface()
{
}

std::shared_ptr<DrawableObject> UiBezierSurface::getObject()
{
	return m_bezierSurface;
}

std::shared_ptr<BezierSurface> UiBezierSurface::getBezierSurface()
{
	return m_bezierSurface;
}

void UiBezierSurface::changeName(const QString &name, int id)
{
	if (id != m_bezierSurface->getId())
		return;
	m_bezierSurface->setName(name);
	emit nameChanged(m_bezierSurface->getId(), name);
}

void UiBezierSurface::updateSurface() const
{
	m_bezierSurface->createVertices();
	m_bezierSurface->generateIndices();
}

void UiBezierSurface::updateScreenSize(float width, float height)
{
	m_bezierSurface->m_width = width;
	m_bezierSurface->m_height = height;
	updateSurface();
}

void UiBezierSurface::updateSurfaceData(BezierSurfaceData data)
{
	m_bezierSurface->initialize(data);
	for (auto &point : m_bezierSurface->getPoints())
	{
		point->setAncestor(m_bezierSurface);
	}
	updateSurface();
}

void UiBezierSurface::getPoints(int surfaceId)
{
	if (surfaceId == m_bezierSurface->getId())
	{
		emit requestedPoints(m_bezierSurface->getPoints());
	}
}
