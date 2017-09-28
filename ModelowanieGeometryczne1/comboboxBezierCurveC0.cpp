#include "comboboxBezierCurveC0.h"

ComboBoxBezierCurveC0::ComboBoxBezierCurveC0(QWidget* parent)
{
}

ComboBoxBezierCurveC0::~ComboBoxBezierCurveC0()
{
}

void ComboBoxBezierCurveC0::addItem(int objectId, const QString &name)
{
	QComboBox::addItem(name);
	m_bezierCurveC0Ids.append(objectId);
}

void ComboBoxBezierCurveC0::deleteItem(int objectId)
{
	for (int i = 0; i < m_bezierCurveC0Ids.count(); ++i)
	{
		if (objectId == m_bezierCurveC0Ids.at(i))
		{
			this->removeItem(i);
			m_bezierCurveC0Ids.removeAt(i);
			return;
		}
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
