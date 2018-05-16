#include "comboboxBezierCurveC0.h"

ComboBoxBezierCurveC0::ComboBoxBezierCurveC0(QWidget* parent) : m_prevCurveId(-1)
{
}

ComboBoxBezierCurveC0::~ComboBoxBezierCurveC0()
{
}

void ComboBoxBezierCurveC0::addItem(int objectId, const QString &name)
{
	m_bezierCurveC0Ids.append(objectId);
	QComboBox::addItem(name);
}

void ComboBoxBezierCurveC0::deleteItem(int objectId)
{
	for (int i = 0; i < m_bezierCurveC0Ids.count(); ++i)
	{
		if (objectId == m_bezierCurveC0Ids.at(i))
		{
			if (i == this->currentIndex())
			{
				emit itemRemoved();
			}
			this->removeItem(this->currentIndex());
			m_bezierCurveC0Ids.removeAt(i);
			return;
		}
	}
}

void ComboBoxBezierCurveC0::selectCurve(int itemId)
{
	if (itemId >= 0)
	{
		emit itemSelected(m_bezierCurveC0Ids.at(itemId), m_prevCurveId);
		m_prevCurveId = m_bezierCurveC0Ids.at(itemId);
	}
}

void ComboBoxBezierCurveC0::changeItemText(int objectId, const QString& text)
{
	for (int i = 0; i < m_bezierCurveC0Ids.count(); ++i)
	{
		if (objectId == m_bezierCurveC0Ids.at(i))
		{
			this->setItemText(i, text);
			return;
		}
	}
}
