#pragma once
#include <QWidget>
#include <qgraphicsscene.h>

class ParametrizationViewer : public QWidget
{
	//Q_OBJECT
public:
	explicit ParametrizationViewer(QWidget *parent = 0, int pixelFactor = 125, QColor curve = Qt::black, QColor empty = Qt::white, QColor filled = Qt::blue);
	~ParametrizationViewer();

	QPair<bool, bool> fillPixMap(const std::vector<QVector4D> &parametrization, const QVector4D &uvRange1, const QVector4D &uvRange2,
		std::vector<std::vector<bool>> &boolmap1, std::vector<std::vector<bool>> &boolmap2, QPair<bool, bool> s1Wrap, QPair<bool, bool> s2Wrap);
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
	void floodFill2(QImage &img, const QPoint &point, QColor oldColor, QColor newColor, bool uWrapped, bool vWrapped) const;
	bool isValid(QImage &img, const QPoint &point, QColor oldColor) const;
	bool colorMatch(QColor c1, QColor c2) const;
	bool isTrimmable(const QImage &img, std::vector<std::vector<bool>> &map) const;
	void drawCurve(QPixmap &map, const std::vector<QPoint> &pixels, bool uWrapped, bool vWrapped) const;
};
