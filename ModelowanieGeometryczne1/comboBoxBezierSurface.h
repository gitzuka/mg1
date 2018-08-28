#pragma once
#ifndef COMBOBOXBEZIERSURFACE_H
#define COMBOBOXBEZIERSURFACE_H
#include <QComboBox>


class ComboBoxBezierSurface : public QComboBox
{
	Q_OBJECT

public:
	explicit ComboBoxBezierSurface(QWidget *parent = 0);
	~ComboBoxBezierSurface();

	void addItem(int objectId, const QString &name);
	int getSurfaceId() const;

private:
	QList<int> m_bezierSurfacesIds;
	int m_prevSurfaceId;

signals:
	void itemSelected(int curveId, int prevCurveId);
	void itemRemoved();
	void allItemsRemoved();

public slots:
	void changeItemText(int objectId, const QString &text);
	void deleteItem(int objectId);

private slots:
	void selectSurface(int itemId);

};

#endif // COMBOBOXBEZIERSURFACE_H