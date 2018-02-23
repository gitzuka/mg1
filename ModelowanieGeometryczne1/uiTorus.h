#pragma once
#include <QObject>
#include "listwidgetobjects.h"
#include "listwidgetparameters.h"
#include "comboboxTorus.h"

class Torus;

class UiTorus : public QObject
{
	Q_OBJECT
public:
	UiTorus(Torus &torus);
	void connectToUi(ComboBoxTorus *comboBox, ListWidgetObjects *listWidget) const;

private:
	QList<int> m_pointsIds;
	Torus &m_torus;

signals:
	void nameChanged(int id, const QString &name);

public slots:
	void changeName(const QString &name, int id);
	void smallRChanged(double r, int objectId);
	void bigRChanged(double R, int objectId);
	void minorSegmentsChanged(int segments, int objectId);
	void majorSegmentsChanged(int segments, int objectId);
};
