#pragma once
#ifndef LISTWIDGETOBJECTS_H
#define LISTWIDGETOBJECTS_H
#include <QListWidget>
#include <memory>

class Point3D;
class ListWidgetMain : public QListWidget
{
	Q_OBJECT

public:
	explicit ListWidgetMain(QWidget *parent = 0);
	~ListWidgetMain();

private:
	QList<QPair<QListWidgetItem*, int>> m_objectsList;
	QList<int> m_selectedObjectsIds;
	QList<QPair<QListWidgetItem*, int>> m_poinsList;
	QList<int> m_undeletable;
	QListWidgetItem *m_activeItem;

	void mousePressEvent(QMouseEvent *event) override;
	int findItemId(QListWidgetItem *item) const;
	void updatePointsList(int id);

signals:
	void rightClick(const QPoint &pos, const QList<int> &selectedObjectIds);
	void changeItemTextEvent(const QString &text, int objectId);
	void removeItemEvent(int objectId);
	void itemSelected(QList<int> &objectIds);

public slots:
	void addBezierCurveC0(const QString &text, int objectId);
	void addBezierCurveC2(const QString &text, int objectId);
	void addBezierC2Interpolated(const QString &text, int objectId);
	void addTorus(const QString &text, int objectId);
	void addPoint3D(const QString &text, int objectId);
	void addObject(const QString &text, int objectId);
	void removeItem();
	void highlightItem(int objectId);
	void highlightActiveItem(int objectId);
	void removeHighlightActive();
	void deleteSurfacePoints(const std::vector<int> &pointsIds);
	void addPoints(const std::vector<std::shared_ptr<Point3D>> &points);

private slots:
	void itemTextChanged(QListWidgetItem *item);
	void itemClick(QListWidgetItem *item);
	void hideShowPoints(int state);
};

#endif // LISTWIDGETOBJECTS_H