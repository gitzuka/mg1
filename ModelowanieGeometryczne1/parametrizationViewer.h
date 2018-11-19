#pragma once
#include <QWidget>
#include <qgraphicsscene.h>

class ParametrizationViewer : public QWidget
{
	//Q_OBJECT
public:
	ParametrizationViewer(QWidget *parent = 0);

	QPair<bool, bool> fillPixMap(const std::vector<QVector4D> &parametrization, const QVector4D &uvRange1, const QVector4D &uvRange2);
	QGraphicsScene *getScene();
	QGraphicsScene *getScene2();

private:
	QGraphicsScene *m_scene;
	QGraphicsScene *m_scene2;

	QPoint convertToPixels(float x, float y, int factor, int w, int h) const;
	void floodFill(int x,int y,int oldcolor,int newcolor) const;
};
