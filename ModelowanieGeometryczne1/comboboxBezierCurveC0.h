#pragma once
#ifndef COMBOBOXBEZIERCURVEC0_H
#define COMBOBOXBEZIERCURVEC0_H
#include <QComboBox>


class ComboBoxBezierCurveC0 : public QComboBox
{
	Q_OBJECT

public:
	explicit ComboBoxBezierCurveC0(QWidget *parent = 0);
	~ComboBoxBezierCurveC0();

	void addItem(int objectId, const QString &name);

private:
	QList<int> m_bezierCurveC0Ids;
	int m_prevCurveId;

signals:
	void itemSelected(int curveId, int prevCurveId);
	void itemRemoved();

public slots:
	void changeItemText(int objectId, const QString &text);
	void deleteItem(int objectId);
	//void pointRemovedFromBC0(int id);

private slots:
	void selectCurve(int itemId);

};

#endif // COMBOBOXBEZIERCURVEC0_H