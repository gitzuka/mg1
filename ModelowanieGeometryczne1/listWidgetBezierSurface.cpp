#include "listWidgetBezierSurface.h"
#include "Point3D.h"
#include "BezierPatch.h"

ListWidgetBezierSurface::ListWidgetBezierSurface(QWidget* parent)
	: QListWidget(parent), m_surfaceId(-1)
{
}

ListWidgetBezierSurface::~ListWidgetBezierSurface()
{
	this->clear();
}

//void ListWidgetBezierSurface::displayPoints(const std::vector<BezierPatch>& patches)
//{
//	this->clear();
//	m_points.clear();
//	for (const auto &patch : patches)
//	{
//		for (int i = 0; i < patch.getPoints().size(); ++i)
//		{
//			this->addItem(patch.getPoints().at(i)->getName());
//			m_points.append(qMakePair(this->item(this->count() - 1), patch.getPoints().at(i)->getId()));
//		}
//	}
//}

void ListWidgetBezierSurface::displayPoints(const std::vector<std::shared_ptr<Point3D>>& points)
{
	this->clear();
	m_points.clear();
	for (const auto &point : points)
	{
		this->addItem(point->getName());
		m_points.append(qMakePair(this->item(this->count() - 1), point->getId()));
	}
}

void ListWidgetBezierSurface::updatePointName(int id, const QString& name)
{
	for (int i = 0; i < m_points.count(); ++i)
	{
		if (m_points.at(i).second == id)
		{
			this->item(i)->setText(name);
			return;
		}
	}
}

void ListWidgetBezierSurface::updateSurfaceId(int id)
{
	m_surfaceId = id;
}

void ListWidgetBezierSurface::highlightItem(int objectId)
{
	for (int i = 0; i < m_points.count(); ++i)
	{
		if (m_points.at(i).second == objectId)
		{
			this->setCurrentItem(m_points.at(i).first);
			return;
		}
	}
}
