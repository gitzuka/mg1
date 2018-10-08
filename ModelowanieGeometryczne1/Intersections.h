#pragma once
#include <memory>

class QVector3D;
class BezierSurface;
class QVector2D;

namespace Intersections
{
	using Surface = const std::shared_ptr<IntersectableObject> &;
	double gradientAlpha = 0.5f;
	double gradientEps = 0.000000000001f;
	double newtonEps = 0.0001f;
	int maxIter = 10000;
	int maxIterNewton = 1000;

	static bool wrapParams(const QVector4D &range, QVector2D &params)
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

	static bool trimParams(const QVector4D &range, QVector2D &params)
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

	static bool checkParametrisation(QVector4D &params, const QVector4D &uvRange1, const QVector4D &uvRange2, bool wrapped1, bool wrapped2)
	{
		bool changed1 = false, changed2 = false;
		QVector2D params1 = QVector2D(params.x(), params.y());
		QVector2D params2 = QVector2D(params.z(), params.w());
		wrapped1 ? changed1 = wrapParams(uvRange1, params1) : changed1 = trimParams(uvRange1, params1);
		wrapped2 ? changed2 = wrapParams(uvRange2, params2) : changed2 = trimParams(uvRange2, params2);
		params = QVector4D(params1.x(), params1.y(), params2.x(), params2.y());
		return (changed1 || changed2);
	}

	static QVector2D getGradient(Surface surface, const QVector2D &uv, const QVector3D &point)
	{
		QVector3D diff = (surface->getPointByUV(uv.x(), uv.y()) - point);
		QVector3D du = surface->getUDerivative(uv.x(), point.y());
		QVector3D dv = surface->getVDerivative(uv.x(), uv.y());
		return 2 * QVector2D(QVector3D::dotProduct(diff, du), QVector3D::dotProduct(diff, dv));
	}

	static QVector4D getGradients(Surface surface1, Surface surface2, const QVector4D &uvuv)
	{
		QVector3D diff = surface1->getPointByUV(uvuv.x(), uvuv.y()) - surface2->getPointByUV(uvuv.z(), uvuv.w());
		QVector3D du1 = surface1->getUDerivative(uvuv.x(), uvuv.y());
		QVector3D dv1 = surface1->getVDerivative(uvuv.x(), uvuv.y());
		QVector3D du2 = surface2->getUDerivative(uvuv.z(), uvuv.w());
		QVector3D dv2 = surface2->getVDerivative(uvuv.z(), uvuv.w());
		return 2 * QVector4D(QVector3D::dotProduct(diff, du1), QVector3D::dotProduct(diff, dv1),
			QVector3D::dotProduct(-diff, du2), QVector3D::dotProduct(-diff, dv2));
	}

	static QVector2D findClosestPoint(Surface surface, const QVector3D &cursorPos)
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

	static QVector4D findIntersectionPoint(Surface surface1, Surface surface2, const QVector3D &cursorPos)
	{
		double alpha = 0.4f;
		int i = 0;

		QVector2D uv1 = findClosestPoint(surface1, cursorPos);
		QVector2D uv2 = findClosestPoint(surface2, cursorPos);
		QVector4D uvuv = QVector4D(uv1.x(), uv1.y(), uv2.x(), uv2.y());
		double currL = std::numeric_limits<double>::infinity();
		while (i++ < maxIter)
		{
			QVector4D dk = uvuv - alpha * getGradients(surface1, surface2, uvuv);

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

	/*static QMatrix4x4 calculateJacobi(Surface surface1, Surface surface2, const QVector4D &params)
	{
		QMatrix4x4 jacobi;
		QVector3D du1 = surface1->getUDerivative(params.x(), params.y());
		QVector3D dv1 = surface1->getVDerivative(params.x(), params.y());
		QVector3D du2 = surface2->getUDerivative(params.z(), params.w());
		QVector3D dv2 = surface2->getVDerivative(params.z(), params.w());
		QVector3D normal1 = QVector3D::crossProduct(du1, dv1);
		QVector3D normal2 = QVector3D::crossProduct(du2, dv2);
		QVector3D versor = QVector3D::crossProduct(normal1, normal2);
		versor /= QVector3D::crossProduct(normal1, normal2).length();
		jacobi.setRow(0, QVector4D(du1.x(), du1.y(), du1.z(), QVector3D::dotProduct(du1, versor)));
		jacobi.setRow(1, QVector4D(dv1.x(), dv1.y(), dv1.z(), QVector3D::dotProduct(dv1, versor)));
		jacobi.setRow(2, QVector4D(-du2.x(), -du2.y(), -du2.z(), 0));
		jacobi.setRow(3, QVector4D(-dv2.x(), -dv2.y(), -dv2.z(), 0));
		return jacobi;
	}*/

	static QMatrix4x4 calculateJacobi(Surface surface1, Surface surface2, const QVector3D &versor, const QVector4D &params)
	{
		QMatrix4x4 jacobi;
		QVector3D du1 = surface1->getUDerivative(params.x(), params.y());
		QVector3D dv1 = surface1->getVDerivative(params.x(), params.y());
		QVector3D du2 = surface2->getUDerivative(params.z(), params.w());
		QVector3D dv2 = surface2->getVDerivative(params.z(), params.w());
		QVector3D normal1 = QVector3D::crossProduct(du1, dv1);
		QVector3D normal2 = QVector3D::crossProduct(du2, dv2);
		QVector3D versor2 = QVector3D::crossProduct(normal1, normal2).normalized();
		//versor /= QVector3D::crossProduct(normal1, normal2).length();
		jacobi.setRow(0, QVector4D(du1.x(), du1.y(), du1.z(), QVector3D::dotProduct(du1, versor2)));
		jacobi.setRow(1, QVector4D(dv1.x(), dv1.y(), dv1.z(), QVector3D::dotProduct(dv1, versor2)));
		jacobi.setRow(2, QVector4D(-du2.x(), -du2.y(), -du2.z(), 0));
		jacobi.setRow(3, QVector4D(-dv2.x(), -dv2.y(), -dv2.z(), 0));
		return jacobi.transposed();
	}

	static QVector4D calculateJacobiFunction(Surface surface1, Surface surface2,
		const QVector3D &versor, const QVector4D &prevParams, const QVector4D &params, double delta)
	{
		QVector4D fun;
		QVector3D point1 = surface1->getPointByUV(params.x(), params.y());
		fun = QVector4D(point1 - surface2->getPointByUV(params.z(), params.w()), 0);
		fun.setW(QVector3D::dotProduct(point1 - surface1->getPointByUV(prevParams.x(), prevParams.y()), versor) - delta);
		return fun;
	}

	static bool findNextPoint(Surface surface1, Surface surface2,
		const QVector4D &params, const QVector3D &versor, double delta, QVector4D &result)
	{
		QVector4D prevParams = params;
		result = params;
		while (abs(delta) > newtonEps)
		{
			int i = 0;
			while (i++ < maxIterNewton)
			{
				QVector4D fun = calculateJacobiFunction(surface1, surface2, versor, params, prevParams, delta);
				QMatrix4x4 jacobi = calculateJacobi(surface1, surface2, versor, prevParams).inverted();
				result = prevParams - jacobi * fun;

				QVector4D uvRange1 = surface1->getRangeUV(result.x(), result.y());
				QVector4D uvRange2 = surface2->getRangeUV(result.z(), result.w());
				if (checkParametrisation(result, uvRange1, uvRange2, surface1->isWrapped(), surface2->isWrapped()) || (result - prevParams).length() < newtonEps)
				{
					break;
					//return false;
				}
				if ((result - prevParams).length() < newtonEps)
				{
					break;
				}
				prevParams = result;
			}
			if (i > maxIterNewton)
			{
				delta *= 0.5f;
				continue;
			}
			break;
		}

		return delta > newtonEps;
	}

	static QVector3D getNormal(Surface surface, double u, double v)
	{
		QVector3D du = surface->getUDerivative(u, v);
		QVector3D dv = surface->getVDerivative(u, v);
		return QVector3D::crossProduct(du, dv);
	}

	static QVector3D getTangentVector(Surface surface1, Surface surface2, const QVector4D &commonPoint)
	{
		QVector3D n1 = getNormal(surface1, commonPoint.x(), commonPoint.y());
		QVector3D n2 = getNormal(surface2, commonPoint.z(), commonPoint.w());
		return QVector3D::crossProduct(n1, n2).normalized();
	}

	static std::vector<QVector4D> getTrimmingCurve(Surface surface1, Surface surface2, const QVector3D &cursorPos)
	{
		double delta = 0.02f;
		std::vector<QVector4D> vertices;
		QVector4D intersectionPoint = findIntersectionPoint(surface1, surface2, cursorPos);
		QVector4D lastPoint = intersectionPoint;
		vertices.push_back(intersectionPoint);
		QVector4D nextPoint;
		double dist = std::numeric_limits<double>::infinity();
		int dir = 1;
		int i = 0;
		while (i++ < maxIterNewton && dist > newtonEps)
		{
			QVector3D versor = dir * getTangentVector(surface1, surface2, lastPoint); //lastPoint
			if (!findNextPoint(surface1, surface2, lastPoint, versor, delta, nextPoint))
			{
				//break;
				if (dir == -1)
				{
					vertices.push_back(nextPoint);
					break;
				}
				dir = -1;
				vertices.push_back(nextPoint);
				std::reverse(vertices.begin(), vertices.end());
				vertices.push_back(intersectionPoint);
				lastPoint = intersectionPoint;
				continue;
			}
			vertices.push_back(nextPoint);
			dist = (lastPoint - nextPoint).length();
			lastPoint = nextPoint;
		}
		return vertices;
	}
}