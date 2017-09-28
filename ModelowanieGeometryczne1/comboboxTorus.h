#pragma once
#ifndef COMBOBOXTORUS_H
#define COMBOBOXTORUS_H
#include <QComboBox>


class ComboBoxTorus : public QComboBox
{
	Q_OBJECT

public:
	explicit ComboBoxTorus(QWidget *parent = 0);
	~ComboBoxTorus();

	void addItem(int objectId, const QString &name);

private:
	QList<int> m_torusIds;

signals:
	void smallrChanged(double r, int objectId);
	void bigRChanged(double R, int objectId);
	void minorSegmentsChanged(int segments, int objectId);
	void majorSegmentsChanged(int segments, int objectId);

public slots:
	void changeItemText(int objectId, const QString &text);
	void deleteItem(int objectId);
	void changeSmallr(double r);
	void changeBigR(double r);
	void changeMinorSegments(int segments);
	void changeMajorSegments(int segments);
};

#endif // COMBOBOXTORUS_H