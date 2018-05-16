#include "uiTorus.h"
#include "torus.h"
#include <memory>
#include "ui_modelowaniegeometryczne1.h"

UiTorus::UiTorus(std::shared_ptr<Torus> torus) : m_torus(torus)
{
}

void UiTorus::connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const
{
	QObject::connect(ui->listWidget_ObjectsList, &ListWidgetMain::changeItemTextEvent, this, &UiTorus::changeName);
	QObject::connect(this, &UiTorus::nameChanged, ui->comboBox_Torus, &ComboBoxTorus::changeItemText);
	QObject::connect(ui->comboBox_Torus, &ComboBoxTorus::smallrChanged, this, &UiTorus::smallRChanged);
	QObject::connect(ui->comboBox_Torus, &ComboBoxTorus::bigRChanged, this, &UiTorus::bigRChanged);
	QObject::connect(ui->comboBox_Torus, &ComboBoxTorus::minorSegmentsChanged, this, &UiTorus::minorSegmentsChanged);
	QObject::connect(ui->comboBox_Torus, &ComboBoxTorus::majorSegmentsChanged, this, &UiTorus::majorSegmentsChanged);
	//QObject::connect(listWidget, &ListWidgetMain::changeItemTextEvent, this, &UiTorus::changeName);
	//QObject::connect(this, &UiTorus::nameChanged, comboBox, &ComboBoxTorus::changeItemText);
	///*QObject::connect(comboBox, &ComboBoxTorus::changeSmallr, this, &UiTorus::smallRChanged);
	//QObject::connect(comboBox, &ComboBoxTorus::changeBigR, this, &UiTorus::bigRChanged);
	//QObject::connect(comboBox, &ComboBoxTorus::changeMinorSegments, this, &UiTorus::minorSegmentsChanged);
	//QObject::connect(comboBox, &ComboBoxTorus::changeMajorSegments, this, &UiTorus::majorSegmentsChanged);*/
	//QObject::connect(comboBox, &ComboBoxTorus::smallrChanged, this, &UiTorus::smallRChanged);
	//QObject::connect(comboBox, &ComboBoxTorus::bigRChanged, this, &UiTorus::bigRChanged);
	//QObject::connect(comboBox, &ComboBoxTorus::minorSegmentsChanged, this, &UiTorus::minorSegmentsChanged);
	//QObject::connect(comboBox, &ComboBoxTorus::majorSegmentsChanged, this, &UiTorus::majorSegmentsChanged);
}

std::shared_ptr<DrawableObject> UiTorus::getObject()
{
	return m_torus;
}

void UiTorus::changeName(const QString& name, int id)
{
	if (id != m_torus->getId())
		return;
	m_torus->setName(name);
	emit nameChanged(m_torus->getId(), name);
}

void UiTorus::smallRChanged(double r, int objectId)
{
	if (m_torus->getId() == objectId)
	{
		m_torus->setSmallRadius(r);
	}
}

void UiTorus::bigRChanged(double R, int objectId)
{
	if (m_torus->getId() == objectId)
	{
		m_torus->setBigRadius(R);
	}
}

void UiTorus::minorSegmentsChanged(int segments, int objectId)
{
	if (m_torus->getId() == objectId)
	{
		m_torus->setMinorSegments(segments);
	}
}

void UiTorus::majorSegmentsChanged(int segments, int objectId)
{
	if (m_torus->getId() == objectId)
	{
		m_torus->setMajorSegments(segments);
	}
}
