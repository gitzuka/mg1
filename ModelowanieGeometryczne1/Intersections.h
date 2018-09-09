#pragma once
#include <memory>

class QVector3D;
class BezierSurface;
class QVector2D;

namespace Intersections
{
	double gradientAlpha = 0.5f;
	double gradientEps = 0.000000000001f;
	int maxIter = 10000;

	static bool wrapParams(QVector4D range, QVector2D &params)
	{
		bool wrapped = false;
		if (params.x() < range.x())
		{
			params.setX(range.y());
			wrapped = true;
		}
		if (params.y() < range.z())
		{
			params.setY(range.w());
			wrapped = true;
		}
		if (params.x() > range.y())
		{
			params.setX(range.x());
			wrapped = true;
		}
		if (params.y() > range.w())
		{
			params.setY(range.z());
			wrapped = true;
		}
		return wrapped;
	}

	static bool trimParams(QVector4D range, QVector2D &params)
	{
		bool trimmed = false;
		if (params.x() < range.x())
		{
			params.setX(range.x());
			trimmed = true;
		}
		if (params.y() < range.z())
		{
			params.setY(range.z());
			trimmed = true;
		}
		if (params.x() > range.y())
		{
			params.setX(range.y());
			trimmed = true;
		}
		if (params.y() > range.w())
		{
			params.setY(range.w());
			trimmed = true;
		}
		return trimmed;
	}

	static bool checkParametrisation(QVector4D &params, QVector4D uvRange1, QVector4D uvRange2, bool wrapped1, bool wrapped2)
	{
		bool changed1 = false, changed2 = false;
		QVector2D params1 = QVector2D(params.x(), params.y());
		QVector2D params2 = QVector2D(params.z(), params.w());
		wrapped1 ? changed1 = wrapParams(uvRange1, params1) : changed1 = trimParams(uvRange1, params1);
		wrapped2 ? changed2 = wrapParams(uvRange2, params2) : changed2 = trimParams(uvRange2, params2);
		params = QVector4D(params1.x(), params1.y(), params2.x(), params2.y());
		return (changed1 || changed2);
	}

	static QVector2D getGradient(const std::shared_ptr<IntersectableObject> &surface, QVector2D uv, QVector3D point)
	{
		QVector3D diff = (surface->getPointByUV(uv.x(), uv.y()) - point);
		QVector3D du = surface->getUDerivative(uv.x(), point.y());
		QVector3D dv = surface->getVDerivative(uv.x(), uv.y());
		return 2 * QVector2D(QVector3D::dotProduct(diff, du), QVector3D::dotProduct(diff, dv));
	}

	static QVector4D getGradient(const std::shared_ptr<IntersectableObject> &surface1, const std::shared_ptr<IntersectableObject> &surface2, QVector4D uvuv)
	{
		QVector3D diff = surface1->getPointByUV(uvuv.x(), uvuv.y()) - surface2->getPointByUV(uvuv.z(), uvuv.w());
		QVector3D du1 = surface1->getUDerivative(uvuv.x(), uvuv.y());
		QVector3D dv1 = surface1->getVDerivative(uvuv.x(), uvuv.y());
		QVector3D du2 = surface2->getUDerivative(uvuv.z(), uvuv.w());
		QVector3D dv2 = surface2->getVDerivative(uvuv.z(), uvuv.w());
		return 2 * QVector4D(QVector3D::dotProduct(diff, du1), QVector3D::dotProduct(diff, dv1),
			QVector3D::dotProduct(-diff, du2), QVector3D::dotProduct(-diff, dv2));
	}


	static QVector2D findClosestPoint(std::shared_ptr<IntersectableObject> surface, QVector3D cursorPos)
	{
		double alpha = gradientAlpha;
		QVector2D point = surface->approximatePointOnSurface(cursorPos), dk = point;
		int i = 0;
		while (i++ < maxIter)
		{
			QVector2D grad = getGradient(surface, point, cursorPos);
			dk = point - alpha * grad;
			QVector4D uvRange = surface->getRangeUV(dk.x(), dk.y());

			if (dk.x() < uvRange.x() || dk.x() > uvRange.y() || dk.y() < uvRange.z() || dk.y() > uvRange.w())
			{
				alpha *= 0.5f;
				continue;
			}

			double l = pow((surface->getPointByUV(dk.x(), dk.y()) - cursorPos).length(), 2)
				- pow((surface->getPointByUV(point.x(), point.y()) - cursorPos).length(), 2);
			if (abs(l) < gradientEps)
			{
				break;
			}
			if (l > 0)
			{
				alpha *= 0.5f;
			}
			else
			{
				point = dk;
			}
		}
		return point;
	}

	static QVector4D findIntersectionPoint(std::shared_ptr<IntersectableObject> surface1, std::shared_ptr<IntersectableObject> surface2, QVector3D cursorPos)
	{
		double alpha = 0.4f;
		int i = 0;

		QVector2D uv1 = findClosestPoint(surface1, cursorPos);
		QVector2D uv2 = findClosestPoint(surface2, cursorPos);
		QVector3D p1 = surface1->getPointByUV(uv1.x(), uv1.y());
		QVector3D p2 = surface2->getPointByUV(uv2.x(), uv2.y());
		QVector4D uvuv = QVector4D(uv1.x(), uv1.y(), uv2.x(), uv2.y());
		double currL = std::numeric_limits<double>::infinity();
		while (i++ < maxIter)
		{
			QVector4D dk = uvuv - alpha * getGradient(surface1, surface2, uvuv);

			QVector4D uvRange1 = surface1->getRangeUV(dk.x(), dk.y());
			QVector4D uvRange2 = surface2->getRangeUV(dk.z(), dk.w());
			if (checkParametrisation(dk, uvRange1, uvRange2, surface1->isWrapped(), surface2->isWrapped()))
			{
				uvuv = dk;
			}

			double l = pow((surface1->getPointByUV(dk.x(), dk.y()) - surface2->getPointByUV(dk.z(), dk.w())).length(), 2.0f);
			if (abs(l) < gradientEps)
			{
				break;
			}
			if (l < 0)
			{
				alpha *= 0.5f;
				continue;
			}
			uvuv = dk;
			currL = l;
		}
		return uvuv;
	}
}