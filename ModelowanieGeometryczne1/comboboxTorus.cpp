#include "comboboxTorus.h"

ComboBoxTorus::ComboBoxTorus(QWidget* parent)
{
}

ComboBoxTorus::~ComboBoxTorus()
{
}

void ComboBoxTorus::addItem(int objectId, const QString& name)
{
	QComboBox::addItem(name);
	m_torusIds.append(objectId);
}

void ComboBoxTorus::deleteItem(int objectId)
{
	for (int i = 0; i < m_torusIds.count(); ++i)
	{
		if (m_torusIds.at(i) == objectId)
		{
			this->removeItem(i);
			m_torusIds.removeAt(i);
			return;
		}
	}
}

void ComboBoxTorus::changeSmallr(double r)
{
	if (currentIndex() > -1)
	{
		emit smallrChanged(r, m_torusIds.at(currentIndex()));
	}
}

void ComboBoxTorus::changeBigR(double r)
{
	if (currentIndex() > -1)
	{
		emit bigRChanged(r, m_torusIds.at(currentIndex()));
	}
}

void ComboBoxTorus::changeMinorSegments(int segments)
{
	if (currentIndex() > -1)
	{
		emit minorSegmentsChanged(segments, m_torusIds.at(currentIndex()));
	}
}

void ComboBoxTorus::changeMajorSegments(int segments)
{
	if (currentIndex() > -1)
	{
		emit majorSegmentsChanged(segments, m_torusIds.at(currentIndex()));
	}
}

void ComboBoxTorus::changeItemText(int objectId, const QString& text)
{
	for (int i = 0; i < m_torusIds.count(); ++i)
	{
		if (objectId == m_torusIds.at(i))
		{
			this->setItemText(i, text);
			return;
		}
	}
}
