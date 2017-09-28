#pragma once

#include <QObject>

class UiScene : public QObject
{
	Q_OBJECT
public:
	UiScene();

	//private:

//signals:

public slots:
	void addedObject(QString name);
	void removedObject();

	//private:
	//	QList<int> m_pointsIds;
	//
	//signals:
	//	void pointAdded(int id);
	//	void pointRemoved(int id);
	//
	//	public slots:
	//	void addPoint(int id);
	//	void removePoint(int id);
};