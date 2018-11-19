#include "parametrizationViewer.h"
#include <QVector4D>
#include <QImage>
#include <qpainter.h>

ParametrizationViewer::ParametrizationViewer(QWidget* parent) : QWidget(parent)
{
	// ui->setupUi(this);
}

QPair<bool, bool> ParametrizationViewer::fillPixMap(const std::vector<QVector4D>& parametrization, const QVector4D &uvRange1, const QVector4D &uvRange2)
{
	int pixelFactor = 125;
	int width1 = pixelFactor * (uvRange1.y() - uvRange1.x());
	int height1 = pixelFactor * (uvRange1.w() - uvRange1.z());
	int width2 = pixelFactor * (uvRange2.y() - uvRange2.x());
	int height2 = pixelFactor * (uvRange2.y() - uvRange2.x());

	QImage map1 = QImage(width1, height1, QImage::Format_RGB888);
	QImage map2 = QImage(width2, height2, QImage::Format_RGB888);
	QColor curveColor = QColor(Qt::GlobalColor::black);
	map1.fill(Qt::white);
	map2.fill(Qt::white);
	std::vector<QPoint> pixels;
	QPolygon pol1, pol2;
	for (auto it = parametrization.begin(); it != parametrization.end(); ++it)
	{
		pol1.append(convertToPixels(it->x(), it->y(), pixelFactor, width1, height1));
		pol2.append(convertToPixels(it->z(), it->w(), pixelFactor, width2, height2));
		pixels.emplace_back(convertToPixels(it->x(), it->y(), pixelFactor, width1, height1));
		//pixels.emplace_back(convertToPixels(it->z(), it->w(), pixelFactor, width2, height2));
		//map1.setPixelColor(convertToPixels(it->x(), it->y(), pixelFactor, width1, height1), curveColor);
		//map2.setPixelColor(convertToPixels(it->z(), it->w(), pixelFactor, width2, height2), curveColor);
	}

	QPixmap pixmap1 = QPixmap::fromImage(map1);
	QPixmap pixmap2 = QPixmap::fromImage(map2);

	QPainter p1 (&pixmap1);
	p1.setPen(Qt::black);
	for (auto it = pixels.begin(); it != pixels.end() - 1; ++it)
	{
		p1.drawLine(*it, *(it + 1));
	}


	m_scene = new QGraphicsScene(this);
	m_scene->addPixmap(pixmap1);
    m_scene->setSceneRect(pixmap1.rect());

	m_scene2 = new QGraphicsScene(this);
	m_scene2->addPixmap(pixmap2);
    m_scene2->setSceneRect(pixmap2.rect());

	//QPainterPath path1;
	//path1.addPolygon(pol1);
	//m_scene->addPath(path1, QPen(Qt::black));
	//
	//QPainterPath path2;
	//path2.addPolygon(pol2);
	//m_scene2->addPath(path2, QPen(Qt::black));
	

	return QPair<bool, bool>();
}

QGraphicsScene* ParametrizationViewer::getScene()
{
	return m_scene;
}

QGraphicsScene* ParametrizationViewer::getScene2()
{
	return m_scene2;
}

QPoint ParametrizationViewer::convertToPixels(float x, float y, int factor, int w, int h) const
{
	QPoint point;
	point.setX(x * factor);
	point.setY(y * factor);
	if (point.x() >= w)
		point.setX(w - 1);
	if (point.y() >= h)
		point.setY(h - 1);
	return point;
}

void ParametrizationViewer::floodFill(int x, int y, int oldcolor, int newcolor) const
{

}
