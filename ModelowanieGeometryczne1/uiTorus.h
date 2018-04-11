#pragma once
#include "uiConnector.h"
#include <memory>

class Torus;

class UiTorus : public UiConnector
{
	Q_OBJECT
public:
	explicit UiTorus(std::shared_ptr<Torus> torus);
	//void connectToUi(ComboBoxTorus *comboBox, ListWidgetObjects *listWidget) const;
	void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const override;
	std::shared_ptr<DrawableObject> getObject() override;

private:
	QList<int> m_pointsIds;
	std::shared_ptr<Torus> m_torus;

signals:
	void nameChanged(int id, const QString &name);

public slots:
	void changeName(const QString &name, int id) override;
	void smallRChanged(double r, int objectId);
	void bigRChanged(double R, int objectId);
	void minorSegmentsChanged(int segments, int objectId);
	void majorSegmentsChanged(int segments, int objectId);
};
