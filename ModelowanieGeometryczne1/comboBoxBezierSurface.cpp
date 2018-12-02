#include "comboBoxBezierSurface.h"

ComboBoxBezierSurface::ComboBoxBezierSurface(QWidget* parent) : m_prevSurfaceId(-1)
{
}

ComboBoxBezierSurface::~ComboBoxBezierSurface()
{
}

void ComboBoxBezierSurface::addItem(int objectId, const QString& name)
{
	m_bezierSurfacesIds.append(objectId);
	QComboBox::addItem(name);
}

int ComboBoxBezierSurface::getSurfaceId() const
{
	return m_prevSurfaceId;
}

void ComboBoxBezierSurface::changeItemText(int objectId, const QString& text)
{
	for (int i = 0; i < m_bezierSurfacesIds.count(); ++i)
	{
		if (objectId == m_bezierSurfacesIds.at(i))
		{
			this->setItemText(i, text);
			return;
		}
	}
}

void ComboBoxBezierSurface::deleteItem(int objectId)
{
	
	for (int i = 0; i < m_bezierSurfacesIds.count(); ++i)
	{
		if (objectId == m_bezierSurfacesIds.at(i))
		{
			if (i == this->currentIndex())
			{
				emit itemRemoved();
				//m_prevSurfaceId = m_bezierSurfacesIds.at(objectId);
			}
			m_bezierSurfacesIds.removeAt(i);
			this->removeItem(this->currentIndex());
			
			if (m_bezierSurfacesIds.count() == 0)
			{
				emit allItemsRemoved();
			}
			return;
		}
	}
}

void ComboBoxBezierSurface::selectSurface(int itemId)
{
	if (itemId >= 0)
	{
		emit itemSelected(m_bezierSurfacesIds.at(itemId), m_prevSurfaceId);
		m_prevSurfaceId = m_bezierSurfacesIds.at(itemId);
	}
}
