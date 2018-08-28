#pragma once
#ifndef LISTWIDGETBEZIERSURFACE_H
#define LISTWIDGETBEZIERSURFACE_H
#include <QListWidget>
#include <memory>

class Point3D;
class BezierPatch;
class ListWidgetBezierSurface : public QListWidget
{
	Q_OBJECT

public:
	explicit ListWidgetBezierSurface(QWidget *parent = 0);
	~ListWidgetBezierSurface();

private:
	QList<QPair<QListWidgetItem*, int>> m_points;
	int m_surfaceId;

public slots:
	//void displayPoints(const std::vector<BezierPatch> &patches);
	void displayPoints(const std::vector<std::shared_ptr<Point3D>> &points);
	void updatePointName(int id, const QString &name);
	void updateSurfaceId(int id);
	void highlightItem(int objectId);
};

#endif // LISTWIDGETBEZIERSURFACE_H