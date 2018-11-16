#include "uiBezierSurface.h"

UiBezierSurface::UiBezierSurface(std::shared_ptr<BezierSurface> bezierSurface, bool loaded)
	: m_checkBoxBezierGrid(new QCheckBox("Show Bezier Grid")), m_checkBoxControlGrid(new QCheckBox("Show Control Grid")), m_bezierSurface(bezierSurface)
{
	if (!loaded)
	{
		updateSurfaceData(m_bezierSurface->m_parameters);
	}
	else
		m_bezierSurface->createVertices();

}

UiBezierSurface::~UiBezierSurface()
{
	delete m_checkBoxBezierGrid;
	delete m_checkBoxControlGrid;
}

std::shared_ptr<DrawableObject> UiBezierSurface::getObject()
{
	return m_bezierSurface;
}

std::shared_ptr<BezierSurface> UiBezierSurface::getBezierSurface()
{
	return m_bezierSurface;
}

QCheckBox* UiBezierSurface::getCBBezierGrid() const
{
	return m_checkBoxBezierGrid;
}

QCheckBox* UiBezierSurface::getCBControlGrid() const
{
	return m_checkBoxControlGrid;
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
	//m_bezierSurface->generateIndices();
}

void UiBezierSurface::updateScreenSize(float width, float height)
{
	m_bezierSurface->m_width = width;
	m_bezierSurface->m_height = height;
	updateSurface();
}

void UiBezierSurface::updateSurfaceData(BezierSurfaceData data)
{
	if (!m_bezierSurface->getPoints().size() > 0)
	{
		m_bezierSurface->initialize(data);
		for (auto &point : m_bezierSurface->getPoints())
		{
			point->setAncestor(m_bezierSurface);
		}
	}
	m_bezierSurface->m_parameters = data;
	updateSurface();
}

void UiBezierSurface::getPoints(int surfaceId)
{
	if (surfaceId == m_bezierSurface->getId())
	{
		emit requestedPoints(m_bezierSurface->getPoints());
	}
}

void UiBezierSurface::changeControlGridState(int state)
{
	m_bezierSurface->m_showControlGrid = state;
	m_bezierSurface->createVertices();
}

void UiBezierSurface::changeBezierGridState(int state)
{
	m_bezierSurface->m_showBezierGrid = state;
	m_bezierSurface->createVertices();
}
