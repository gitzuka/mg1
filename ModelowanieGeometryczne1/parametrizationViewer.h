#pragma once
#include <QWidget>
#include <qgraphicsscene.h>

class ParametrizationViewer : public QWidget
{
	//Q_OBJECT
public:
	explicit ParametrizationViewer(QWidget *parent = 0, int pixelFactor = 125, QColor curve = Qt::black, QColor empty = Qt::white, QColor filled = Qt::blue);
	~ParametrizationViewer();

	QPair<bool, bool> fillPixMap(const std::vector<QVector4D> &parametrization, const QVector4D &uvRange1, const QVector4D &uvRange2);
	QGraphicsScene *getScene();
	QGraphicsScene *getScene2();

private:
	QGraphicsScene *m_scene;
	QGraphicsScene *m_scene2;
	int m_pixelFactor;
	QColor m_curve;
	QColor m_empty;
	QColor m_filled;

	QPoint convertToPixels(float x, float y, int factor, int w, int h) const;
	void floodFill(QImage &img, const QPoint &point, QColor oldColor, QColor newColor) const;
	bool isValid(QImage &img, const QPoint &point, QColor oldColor) const;
	bool colorMatch(QColor c1, QColor c2) const;
	bool isTrimmable(const QImage &img) const;
};
