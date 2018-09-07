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

	static void trimParams(QVector4D range, QVector2D &params)
	{
		if (params.x() < range.x())
			params.setX(range.x());
		if (params.y() < range.z())
			params.setY(range.z());
		if (params.x() > range.y())
			params.setX(range.y());
		if (params.y() > range.w())
			params.setY(range.w());
	}

	static QVector2D findClosestPoint(std::shared_ptr<IntersectableObject> surface, QVector3D cursorPos)
	{
		QVector2D uv = surface->approximatePointOnSurface(cursorPos);
		QVector3D point = surface->getPointByUV(uv.x(), uv.y());
		//QVector3D point = cursorPos;
		double alpha = gradientAlpha;
		double currDist = std::numeric_limits<double>::infinity();

		int i = 0;
		do
		{
			QVector3D diff = point - cursorPos;
			/*QVector3D du = diff * surface->getUDerivative(uv.x(), uv.y());
			QVector3D dv = diff * surface->getVDerivative(uv.x(), uv.y());
			QVector2D grad = 2 * QVector2D(du.x() + du.y() + du.z(), dv.x() + dv.y() + dv.z());*/

			QVector3D du = surface->getUDerivative(uv.x(), uv.y());
			QVector3D dv = surface->getVDerivative(uv.x(), uv.y());
			QVector2D grad = 2 * QVector2D(QVector3D::dotProduct(diff, du), QVector3D::dotProduct(diff, dv));

			QVector2D dk = uv - alpha * grad;
			QVector3D nextPoint = surface->getPointByUV(dk.x(), dk.y());

			double dist = (nextPoint - point).lengthSquared();

			QVector4D uvRange = surface->getRangeUV(dk.x(), dk.y());
			if (surface->isWrapped())
			{
				if (dist > currDist || dk.x() < uvRange.x() || dk.y() < uvRange.z() || dk.x() > uvRange.y() || dk.y() > uvRange.w())
				{
					alpha *= 0.5f;
					if (alpha < gradientEps)
						break;
				}
			}
			if (dist > currDist)
			{
				break;
			}
			trimParams(uvRange, dk);
			/*if (dist > currDist || dk.x() < uvRange.x() || dk.y() < uvRange.z() || dk.x() > uvRange.y() || dk.y() > uvRange.w())
			{
				alpha *= 0.5f;
				if (alpha < gradientEps)
					break;
			}*/
			currDist = dist;
			uv = dk;
			point = nextPoint;
			++i;
			if (i > maxIter)
				break;
		} while (currDist > gradientEps);

		return uv;
	}

	

	static QVector4D findIntersectionPoint(std::shared_ptr<IntersectableObject> surface1, std::shared_ptr<IntersectableObject> surface2, QVector2D uv1, QVector2D uv2)
	{
		double alpha = gradientAlpha;
		double currDist = std::numeric_limits<double>::infinity();
		QVector4D uvuv = QVector4D(uv1.x(), uv1.y(), uv2.x(), uv2.y());

		int i = 0;
		do
		{
			QVector3D p1 = surface1->getPointByUV(uv1.x(), uv1.y());
			QVector3D p2 = surface1->getPointByUV(uv2.x(), uv2.y());

			QVector3D du1 = surface1->getUDerivative(uv1.x(), uv1.y());
			QVector3D dv1 = surface1->getVDerivative(uv1.x(), uv1.y());
			QVector3D du2 = surface2->getUDerivative(uv2.x(), uv2.y());
			QVector3D dv2 = surface2->getVDerivative(uv2.x(), uv2.y());

			QVector3D diff1 = 2 * (p1 - p2);
			if (i == 0)
				diff1 = QVector3D(0, 0, 0);
			//QVector3D diff2 = 2 * (p2 - p1);

			QVector4D grad = QVector4D(QVector3D::dotProduct(diff1, du1), QVector3D::dotProduct(diff1, dv1),
				QVector3D::dotProduct(-diff1, du2), QVector3D::dotProduct(-diff1, dv2));

			QVector4D dk = uvuv - alpha * grad;
			double dist = (dk - uvuv).lengthSquared();

			QVector4D uvRange1 = surface1->getRangeUV(dk.x(), dk.y());
			QVector4D uvRange2 = surface2->getRangeUV(dk.z(), dk.w());
			if (dist >= currDist || dk.x() < uvRange1.x() || dk.y() < uvRange1.z() || dk.x() > uvRange1.y() || dk.y() > uvRange1.w()
				|| dk.x() < uvRange2.x() || dk.y() < uvRange2.z() || dk.x() > uvRange2.y() || dk.y() > uvRange2.w())
			{
				alpha *= 0.5f;
				if (alpha < gradientEps)
					break;
			}
			else
			{
				currDist = dist;
				uvuv = dk;
			}
			++i;
			if (i > maxIter)
				break;
		} while (currDist > gradientEps);

		return uvuv;
	}

	//static QVector2D findClosestPoint(std::shared_ptr<BezierSurface> surface, QVector3D cursorPos)
	//{
	//	QVector2D uv = surface->approximatePointOnSurface(cursorPos);
	//	QVector3D point = surface->getPointByUV(uv.x(), uv.y());
	//	double alpha = gradientAlpha;
	//	double currDist = std::numeric_limits<double>::infinity();

	//	int i = 0;
	//	do
	//	{
	//		QVector3D diff = point - cursorPos;
	//		QVector3D du = diff * surface->getUDerivative(uv.x(), uv.y());
	//		QVector3D dv = diff * surface->getVDerivative(uv.x(), uv.y());

	//		QVector2D grad = 2 * QVector2D(QVector3D::dotProduct(diff, du), QVector3D::dotProduct(diff, dv));
	//		//QVector2D grad = 2 * QVector2D(du.x() + du.y() + du.z(), dv.x() + dv.y() + dv.z());

	//		QVector2D dk = uv - alpha * grad;
	//		QVector3D nextPoint = surface->getPointByUV(dk.x(), dk.y());

	//		//double dist = (nextPoint - point).lengthSquared();
	//		double dist = (nextPoint - cursorPos).lengthSquared();

	//		BezierPatch patch = surface->getPatchByUV(dk.x(), dk.y());

	//			//if (dist > currDist || dk.x() < 0 || dk.y() < 0 || dk.x() > 1 || dk.y() > 1)
	//		if (dist > currDist || dk.x() < patch.getU() || dk.y() < patch.getV() || dk.x() > (patch.getU() + 1) || dk.y() > (patch.getV() + 1))
	//		{
	//			alpha *= 0.5f;
	//			if (alpha < gradientEps)
	//				break;
	//		}
	//		else
	//		{
	//			currDist = dist;
	//			uv = dk;
	//			point = nextPoint;
	//		}
	//		++i;
	//		if (i > maxIter)
	//			break;
	//	} while (currDist > gradientEps);

	//	return uv;
	//}



	//static QVector4D findIntersectionPoint(std::shared_ptr<BezierSurface> surface1, std::shared_ptr<BezierSurface> surface2, QVector2D uv1, QVector2D uv2)
	//{
	//	double alpha = gradientAlpha;
	//	double currDist = std::numeric_limits<double>::infinity();
	//	QVector4D uvuv = QVector4D(uv1.x(), uv1.y(), uv2.x(), uv2.y());

	//	int i = 0;
	//	do
	//	{
	//		QVector3D p1 = surface1->getPointByUV(uv1.x(), uv1.y());
	//		QVector3D p2 = surface1->getPointByUV(uv2.x(), uv2.y());

	//		QVector3D du1 = surface1->getUDerivative(uv1.x(), uv1.y());
	//		QVector3D dv1 = surface1->getVDerivative(uv1.x(), uv1.y());
	//		QVector3D du2 = surface2->getUDerivative(uv2.x(), uv2.y());
	//		QVector3D dv2 = surface2->getVDerivative(uv2.x(), uv2.y());

	//		QVector3D diff1 = 2 * (p1 - p2);
	//		//QVector3D diff2 = 2 * (p2 - p1);

	//		QVector4D grad = QVector4D(QVector3D::dotProduct(diff1, du1), QVector3D::dotProduct(diff1, dv1), 
	//			QVector3D::dotProduct(-diff1, du2), QVector3D::dotProduct(-diff1, dv2));

	//		QVector4D dk = uvuv - alpha * grad;
	//		double dist = (dk - uvuv).lengthSquared();

	//		BezierPatch patch1 = surface1->getPatchByUV(dk.x(), dk.y());
	//		BezierPatch patch2 = surface2->getPatchByUV(dk.z(), dk.w());
	//		if (dist >= currDist || dk.x() < patch1.getU() || dk.y() < patch1.getV() || dk.x() > (patch1.getU() + 1) || dk.y() > (patch1.getV() + 1)
	//			|| dk.z() < patch2.getU() || dk.w() < patch2.getV() || dk.z() > (patch2.getU() + 1) || dk.w() > (patch2.getV() + 1))
	//		{
	//			alpha *= 0.5f;
	//			if (alpha < gradientEps)
	//				break;
	//		}
	//		else
	//		{
	//			currDist = dist;
	//			uvuv = dk;
	//		}
	//		++i;
	//		if (i > maxIter)
	//			break;
	//	} while (currDist > gradientEps);

	//	return uvuv;
	//}
}