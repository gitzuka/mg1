#include "parametrizationViewer.h"
#include <QVector4D>
#include <QImage>
#include <qpainter.h>
#include <qqueue.h>

ParametrizationViewer::ParametrizationViewer(QWidget *parent, int pixelFactor, QColor curve, QColor empty, QColor filled) : m_scene(nullptr), m_scene2(nullptr), m_pixelFactor(pixelFactor), m_curve(curve), m_empty(empty),
m_filled(filled)
{
}

ParametrizationViewer::~ParametrizationViewer()
{
	delete m_scene;
	delete m_scene2;
}


QPair<bool, bool> ParametrizationViewer::fillPixMap(const std::vector<QVector4D>& parametrization, const QVector4D &uvRange1, const QVector4D &uvRange2,
	std::vector<std::vector<bool>> &boolmap1, std::vector<std::vector<bool>> &boolmap2, QPair<bool, bool> s1Wrap, QPair<bool, bool> s2Wrap)
{
	int width1 = m_pixelFactor * (uvRange1.y() - uvRange1.x());
	int height1 = m_pixelFactor * (uvRange1.w() - uvRange1.z());
	int width2 = m_pixelFactor * (uvRange2.y() - uvRange2.x());
	int height2 = m_pixelFactor * (uvRange2.y() - uvRange2.x());
	QPair<bool, bool> trimmable;
	QImage map1 = QImage(width1, height1, QImage::Format_RGB888);
	QImage map2 = QImage(width2, height2, QImage::Format_RGB888);
	map1.fill(m_empty);
	map2.fill(m_empty);
	std::vector<QPoint> pixels;
	std::vector<QPoint> pixels2;
	for (auto it = parametrization.begin(); it != parametrization.end(); ++it)
	{
		pixels.emplace_back(convertToPixels(it->x(), it->y(), m_pixelFactor, width1, height1));
		pixels2.emplace_back(convertToPixels(it->z(), it->w(), m_pixelFactor, width2, height2));
	}

	QPixmap pixmap1 = QPixmap::fromImage(map1);
	QPixmap pixmap2 = QPixmap::fromImage(map2);

	if (s1Wrap.first || s1Wrap.second)
		drawCurve(pixmap1, pixels, s1Wrap.first, s1Wrap.second);
	else
	{
		QPainter p1(&pixmap1);
		p1.setPen(m_curve);
		for (auto it = pixels.begin(); it != pixels.end() - 1; ++it)
		{
			p1.drawLine(*it, *(it + 1));
		}
	}

	if (s2Wrap.first || s2Wrap.second)
		drawCurve(pixmap2, pixels2, s2Wrap.first, s2Wrap.second);
	else
	{
		QPainter p2(&pixmap2);
		p2.setPen(m_curve);
		for (auto it = pixels2.begin(); it != pixels2.end() - 1; ++it)
		{
			p2.drawLine(*it, *(it + 1));
		}
	}

	QPoint startPoint1 = QPoint(0, 0);
	QImage map11 = pixmap1.toImage();
	while (map11.pixelColor(startPoint1) == m_curve)
	{
		startPoint1.setX(startPoint1.x() + 1);
		startPoint1.setY(startPoint1.y() + 1);
	}
	floodFill2(map11, startPoint1, m_empty, m_filled, s1Wrap.first, s1Wrap.second);
	trimmable.first = isTrimmable(map11, boolmap1);

	QPixmap pixmap11 = QPixmap::fromImage(map11);
	m_scene = new QGraphicsScene(this);
	m_scene->addPixmap(pixmap11);
	m_scene->setSceneRect(pixmap11.rect());

	startPoint1 = QPoint(0, 0);
	QImage map22 = pixmap2.toImage();
	while (map22.pixelColor(startPoint1) == m_curve)
	{
		startPoint1.setX(startPoint1.x() + 1);
		startPoint1.setY(startPoint1.y() + 1);
	}
	floodFill2(map22, startPoint1, m_empty, m_filled, s2Wrap.first, s2Wrap.second);
	trimmable.second = isTrimmable(map22, boolmap2);

	QPixmap pixmap22 = QPixmap::fromImage(map22);
	m_scene2 = new QGraphicsScene(this);
	m_scene2->addPixmap(pixmap22);
	m_scene2->setSceneRect(pixmap22.rect());

	return trimmable;
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

void ParametrizationViewer::floodFill(QImage &img, const QPoint &point, QColor oldColor, QColor newColor) const
{
	QQueue<QPoint> q;
	q.enqueue(point);
	while (q.count() > 0)
	{
		QPoint n = q.dequeue();
		if (!colorMatch(img.pixelColor(n.x(), n.y()), oldColor))
			continue;
		QPoint w = n, e = QPoint(n.x() + 1, n.y());
		while ((w.x() >= 0) && colorMatch(img.pixelColor(w.x(), w.y()), oldColor))
		{
			img.setPixelColor(w.x(), w.y(), newColor);
			if ((w.y() > 0) && colorMatch(img.pixelColor(w.x(), w.y() - 1), oldColor))
				q.enqueue(QPoint(w.x(), w.y() - 1));
			if ((w.y() < img.height() - 1) && colorMatch(img.pixelColor(w.x(), w.y() + 1), oldColor))
				q.enqueue(QPoint(w.x(), w.y() + 1));
			w.setX(w.x() - 1);
		}
		while ((e.x() <= img.width() - 1) && colorMatch(img.pixelColor(e.x(), e.y()), oldColor))
		{
			img.setPixelColor(e.x(), e.y(), newColor);
			if ((e.y() > 0) && colorMatch(img.pixelColor(e.x(), e.y() - 1), oldColor))
				q.enqueue(QPoint(e.x(), e.y() - 1));
			if ((e.y() < img.height() - 1) && colorMatch(img.pixelColor(e.x(), e.y() + 1), oldColor))
				q.enqueue(QPoint(e.x(), e.y() + 1));
			e.setX(e.x() + 1);
		}
	}
}

void ParametrizationViewer::floodFill2(QImage& img, const QPoint& point, QColor oldColor, QColor newColor,
	bool uWrapped, bool vWrapped) const
{
	if (!(uWrapped || vWrapped))
	{
		floodFill(img, point, oldColor, newColor);
		return;
	}
	QQueue<QPoint> q;
	q.enqueue(point);
	while (q.count() > 0)
	{
		QPoint n = q.dequeue();
		if (!colorMatch(img.pixelColor(n.x(), n.y()), oldColor))
			continue;
		QPoint w = n, e = QPoint(n.x() + 1, n.y());

		while ((w.x() >= 0) && colorMatch(img.pixelColor(w.x(), w.y()), oldColor))
		{
			img.setPixelColor(w.x(), w.y(), newColor);
			if ((w.y() > 0) && colorMatch(img.pixelColor(w.x(), w.y() - 1), oldColor))
				q.enqueue(QPoint(w.x(), w.y() - 1));
			else if (vWrapped && (w.y() == 0) && colorMatch(img.pixelColor(w.x(), img.height() - 1), oldColor))
				q.enqueue(QPoint(w.x(), img.height() - 1));
			if ((w.y() < img.height() - 1) && colorMatch(img.pixelColor(w.x(), w.y() + 1), oldColor))
				q.enqueue(QPoint(w.x(), w.y() + 1));
			else if (vWrapped && (w.y() >= img.height() - 1) && colorMatch(img.pixelColor(w.x(), 0), oldColor))
				q.enqueue(QPoint(w.x(), 0));
			w.setX(w.x() - 1);
			if (uWrapped && w.x() < 0)
				q.enqueue(QPoint(img.width() - 1, w.y()));
		}
		while ((e.x() <= img.width() - 1) && colorMatch(img.pixelColor(e.x(), e.y()), oldColor))
		{
			img.setPixelColor(e.x(), e.y(), newColor);
			if ((e.y() > 0) && colorMatch(img.pixelColor(e.x(), e.y() - 1), oldColor))
				q.enqueue(QPoint(e.x(), e.y() - 1));
			else if ((e.y() <= 0) && colorMatch(img.pixelColor(e.x(), img.height() - 1), oldColor))
				q.enqueue(QPoint(e.x(), img.height() - 1));
			if ((e.y() < img.height() - 1) && colorMatch(img.pixelColor(e.x(), e.y() + 1), oldColor))
				q.enqueue(QPoint(e.x(), e.y() + 1));
			else if(vWrapped && (e.y() >= img.height() - 1) && colorMatch(img.pixelColor(e.x(), 0), oldColor))
				q.enqueue(QPoint(e.x(), 0));
			e.setX(e.x() + 1);
			if (uWrapped && e.x() > img.width() - 1)
				q.enqueue(QPoint(0, w.y()));
		}
	}
}

bool ParametrizationViewer::isValid(QImage &img, const QPoint &point, QColor oldColor) const
{
	if (point.x() >= img.width() || point.x() < 0 || point.y() >= img.height() || point.y() < 0)
		return false;
	return img.pixelColor(point) == oldColor;
}

bool ParametrizationViewer::colorMatch(QColor c1, QColor c2) const
{
	return (c1 == c2);
}

bool ParametrizationViewer::isTrimmable(const QImage& img, std::vector<std::vector<bool>> &map) const
{
	bool empty = false, filled = false, curve = false;
	for (int i = 0; i < img.width(); ++i)
	{
		std::vector<bool> col;
		for (int j = 0; j < img.height(); ++j)
		{
			if (img.pixelColor(i, j) == m_empty)
			{
				empty = true;
				col.emplace_back(false);
				continue;
			}
			else if (img.pixelColor(i, j) == m_curve)
			{
				curve = true;
			}
			else if (img.pixelColor(i, j) == m_filled)
			{
				filled = true;
			}
			col.emplace_back(true);

		}
		map.emplace_back(std::move(col));
	}
	return (filled && curve && empty);
}

void ParametrizationViewer::drawCurve(QPixmap& map, const std::vector<QPoint>& pixels, bool uWrapped,
	bool vWrapped) const
{
	int width = map.width();
	QPainter p(&map);
	p.setPen(m_curve);
	for (auto it = pixels.begin(); it != pixels.end() - 1; ++it)
	{
		if (uWrapped)
		{
			if (abs(it->x() - (it + 1)->x()) > map.width() / 2)
			{
				QPoint p1, p2;
				if (it->x() < map.width() / 2)
				{
					p1.setX(0);
					p2.setX(map.width() - 1);
				}
				else
				{
					p1.setX(map.width() - 1);
					p2.setX(0);
				}
				p1.setY(it->y());
				p.drawLine(*it, p1);
				p2.setY((it + 1)->y());
				p.drawLine(*(it + 1), p2);
				continue;
			}
		}
		if (vWrapped)
		{
			if (abs(it->y() - (it + 1)->y()) > map.height() / 2)
			{
				QPoint p1, p2;
				if (it->y() < map.height() / 2)
				{
					p1.setY(0);
					p2.setY(map.height() - 1);
				}
				else
				{
					p1.setY(map.height() - 1);
					p2.setY(0);
				}
				p1.setX(it->x());
				p.drawLine(*it, p1);
				p2.setX((it + 1)->x());
				p.drawLine(*(it + 1), p2);
				continue;
			}
		}
		p.drawLine(*it, *(it + 1));
	}
}
