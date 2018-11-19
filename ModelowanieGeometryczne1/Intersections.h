#pragma once
#include <memory>

class QVector3D;
class BezierSurface;
class QVector2D;

namespace Intersections
{
	using Surface = const std::shared_ptr<IntersectableObject> &;
	double gradientAlpha = 0.5f;
	double gradientEps = 0.0000001f;
	double newtonEps = 0.001f;
	int maxIter = 10000;
	int maxIterNewton = 1000;

	struct NewtonWrapTrim
	{
		bool u1wrapped = false;
		bool u2wrapped = false;
		bool v1wrapped = false;
		bool v2wrapped = false;
		bool u1trimmed = false;
		bool u2trimmed = false;
		bool v1trimmed = false;
		bool v2trimmed = false;
		bool wasWrapped = false;
		bool wasTrimmed = false;
		bool wrappedSecondTime = false;
		bool wasChanged() const
		{
			//return u1wrapped || u2wrapped || v1wrapped || v2wrapped || u1trimmed || u2trimmed || v1trimmed || v2trimmed;
			return wasWrapped || wasTrimmed;
		}
		bool wrapU1()
		{
			if (u1wrapped)
			{
				wrappedSecondTime = true;
				return false;
			}
			return u1wrapped = true;
		}
		bool wrapU2()
		{
			if (u2wrapped)
			{
				wrappedSecondTime = true;
				return false;
			}
			return u2wrapped = true;
		}
		bool wrapV1()
		{
			if (v1wrapped)
			{
				wrappedSecondTime = true;
				return false;
			}
			return v1wrapped = true;
		}
		bool wrapV2()
		{
			if (v2wrapped)
			{
				wrappedSecondTime = true;
				return false;
			}
			return v2wrapped = true;
		}
		/*bool wasWrapped() const
		{
			return u1wrapped || u2wrapped || v1wrapped || v2wrapped;
		}
		bool wasTrimmed() const
		{
			return u1trimmed || u2trimmed || v1trimmed || v2trimmed;
		}*/
	};

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
			params.setX(range.y());
			wrapped = true;
		}
		if (params.y() > range.w())
		{
			params.setY(range.w());
			wrapped = true;
		}
		/*if (params.x() < range.x())
		{
			do
			{
				params.setX(params.x() + range.y());
			} while (params.x() < range.x());
			wrapped = true;
		}
		if (params.y() < range.z())
		{
			do
			{
				params.setY(params.y() + range.w());
			} while (params.y() < range.z());
			wrapped = true;
		}
		if (params.x() > range.y())
		{
			do
			{
				params.setX(params.x() - range.y());
			} while (params.x() > range.y());
			wrapped = true;
		}
		if (params.y() > range.w())
		{
			do
			{
				params.setY(params.y() - range.w());
			} while (params.y() > range.w());
			wrapped = true;
		}*/
		return wrapped;
	}

	static void wrapTrim(const QVector2D &range, float param, NewtonWrapTrim &wrapTrim, bool wrap, bool surface1)
	{
		//if(wrap)
	}

	static bool wrapU(const QVector4D &range, QVector2D &params, NewtonWrapTrim &wrapTrim, bool surface1)
	{
		/*if (params.x() < range.x())
		{
			wrapTrim.wasWrapped = true;
			do
			{
				params.setX(params.x() + range.y());
			} while (params.x() < range.x());
			if (surface1)
				wrapTrim.u1wrapped = true;
			else
				wrapTrim.u2wrapped = true;
		}
		if (params.x() > range.y())
		{
			wrapTrim.wasWrapped = true;
			do
			{
				params.setX(params.x() - range.y());
			} while (params.x() > range.y());
			if (surface1)
				wrapTrim.u1wrapped = true;
			else
				wrapTrim.u2wrapped = true;
		}*/
		if (params.x() < range.x())
		{
			wrapTrim.wasWrapped = true;
			do
			{
				params.setX(params.x() + range.y());
			} while (params.x() < range.x());
			if (surface1)
				return wrapTrim.wrapU1();
			return wrapTrim.wrapU2();
		}
		if (params.x() > range.y())
		{
			wrapTrim.wasWrapped = true;
			do
			{
				params.setX(params.x() - range.y());
			} while (params.x() > range.y());
			if (surface1)
				return wrapTrim.wrapU1();
			return wrapTrim.wrapU2();
		}
		return true;
	}

	static bool wrapV(const QVector4D &range, QVector2D &params, NewtonWrapTrim &wrapTrim, bool surface1)
	{
		if (params.y() < range.z())
		{
			wrapTrim.wasWrapped = true;
			do
			{
				params.setY(params.y() + range.w());
			} while (params.y() < range.z());
			if (surface1)
				return wrapTrim.wrapV1();
			return wrapTrim.wrapV2();
		}
		if (params.y() > range.w())
		{
			wrapTrim.wasWrapped = true;
			do
			{
				params.setY(params.y() - range.w());
			} while (params.y() > range.w());
			if (surface1)
				return wrapTrim.wrapV1();
			return wrapTrim.wrapV2();
		}
		return true;
	}

	static void trimU(const QVector4D &range, QVector2D &params, NewtonWrapTrim &wrapTrim, bool surface1)
	{
		if (params.x() < range.x())
		{
			wrapTrim.wasTrimmed = true;
			params.setX(range.x());
			if (surface1)
				wrapTrim.u1trimmed = true;
			else
				wrapTrim.u2trimmed = true;
		}
		if (params.x() > range.y())
		{
			wrapTrim.wasTrimmed = true;
			params.setX(range.y());
			if (surface1)
				wrapTrim.u1trimmed = true;
			else
				wrapTrim.u2trimmed = true;
		}

	}

	static void trimV(const QVector4D &range, QVector2D &params, NewtonWrapTrim &wrapTrim, bool surface1)
	{
		if (params.y() < range.z())
		{
			wrapTrim.wasTrimmed = true;
			params.setY(range.z());
			if (surface1)
				wrapTrim.v1trimmed = true;
			else
				wrapTrim.v2trimmed = true;
		}
		if (params.y() > range.w())
		{
			wrapTrim.wasTrimmed = true;
			params.setY(range.w());
			if (surface1)
				wrapTrim.v1trimmed = true;
			else
				wrapTrim.v2trimmed = true;
		}
	}

	static bool wrapParams(const QVector4D &range, QVector2D &params, NewtonWrapTrim &wrapTrim, bool surface1)
	{
		bool wrapped = false;
		if (params.x() < range.x())
		{
			do
			{
				params.setX(params.x() + range.y());
			} while (params.x() < range.x());
			if (surface1)
				wrapTrim.u1wrapped = true;
			else
				wrapTrim.u2wrapped = true;
			wrapped = true;
		}
		if (params.y() < range.z())
		{
			do
			{
				params.setY(params.y() + range.w());
			} while (params.y() < range.z());
			if (surface1)
				wrapTrim.v1wrapped = true;
			else
				wrapTrim.v2wrapped = true;
			wrapped = true;
		}
		if (params.x() > range.y())
		{
			do
			{
				params.setX(params.x() - range.y());
			} while (params.x() > range.y());
			if (surface1)
				wrapTrim.u1wrapped = true;
			else
				wrapTrim.u2wrapped = true;
			wrapped = true;
		}
		if (params.y() > range.w())
		{
			do
			{
				params.setY(params.y() - range.w());
			} while (params.y() > range.w());
			if (surface1)
				wrapTrim.v1wrapped = true;
			else
				wrapTrim.v2wrapped = true;
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

	static bool trimParams(const QVector4D &range, QVector2D &params, NewtonWrapTrim &wrapTrim, bool surface1)
	{
		bool trimmed = false;
		if (params.x() < range.x())
		{
			params.setX(range.x());
			if (surface1)
				wrapTrim.u1trimmed = true;
			else
				wrapTrim.u2trimmed = true;
			trimmed = true;
		}
		if (params.y() < range.z())
		{
			params.setY(range.z());
			if (surface1)
				wrapTrim.v1trimmed = true;
			else
				wrapTrim.v2trimmed = true;
			trimmed = true;
		}
		if (params.x() > range.y())
		{
			params.setX(range.y());
			if (surface1)
				wrapTrim.u1trimmed = true;
			else
				wrapTrim.u2trimmed = true;
			trimmed = true;
		}
		if (params.y() > range.w())
		{
			params.setY(range.w());
			if (surface1)
				wrapTrim.v1trimmed = true;
			else
				wrapTrim.v2trimmed = true;
			trimmed = true;
		}
		return trimmed;
	}

	static bool checkParametrization(QVector4D &params, Surface s1, Surface s2, NewtonWrapTrim &wrapTrim)
	{
		bool wrappedU1 = false;
		bool wrappedU2 = false;
		bool wrappedV1 = false;
		bool wrappedV2 = false;
		QVector4D uvRange1 = s1->getRangeUV(params.x(), params.y());
		QVector4D uvRange2 = s2->getRangeUV(params.z(), params.w());
		QVector2D params1 = QVector2D(params.x(), params.y());
		QVector2D params2 = QVector2D(params.z(), params.w());
		//if (s1->isUWrapped())
		s1->isUWrapped() ? wrapU(uvRange1, params1, wrapTrim, true) : trimU(uvRange1, params1, wrapTrim, true);
		s2->isUWrapped() ? wrapU(uvRange2, params2, wrapTrim, false) : trimU(uvRange2, params2, wrapTrim, false);
		s1->isVWrapped() ? wrapV(uvRange1, params1, wrapTrim, true) : trimV(uvRange1, params1, wrapTrim, true);
		s2->isVWrapped() ? wrapV(uvRange2, params2, wrapTrim, false) : trimV(uvRange2, params2, wrapTrim, false);
		//wrapped1 ? changed1 = wrapParams(uvRange1, params1, wrapTrim, true) : trimParams(uvRange1, params1, wrapTrim, true);
		//wrapped2 ? changed2 = wrapParams(uvRange2, params2, wrapTrim, false) : trimParams(uvRange2, params2, wrapTrim, false);
		params = QVector4D(params1.x(), params1.y(), params2.x(), params2.y());
		return wrapTrim.wasChanged();
	}

	static bool checkParametrization(QVector4D &params, const QVector4D &uvRange1, const QVector4D &uvRange2, bool wrapped1, bool wrapped2)
	{
		/*bool changed1 = false, changed2 = false;
		QVector2D params1 = QVector2D(params.x(), params.y());
		QVector2D params2 = QVector2D(params.z(), params.w());
		wrapped1 ? changed1 = wrapParams(uvRange1, params1) : changed1 = trimParams(uvRange1, params1);
		wrapped2 ? changed2 = wrapParams(uvRange2, params2) : changed2 = trimParams(uvRange2, params2);
		params = QVector4D(params1.x(), params1.y(), params2.x(), params2.y());
		return (changed1 || changed2);*/
		bool changed1 = false, changed2 = false;
		QVector2D params1 = QVector2D(params.x(), params.y());
		QVector2D params2 = QVector2D(params.z(), params.w());
		//QVector2D p1 = params1;
		//QVector2D p2 = params2;
		wrapped1 ? changed1 = wrapParams(uvRange1, params1) : changed1 = trimParams(uvRange1, params1);
		wrapped2 ? changed2 = wrapParams(uvRange2, params2) : changed2 = trimParams(uvRange2, params2);
		//params = QVector4D(p1.x(), p1.y(), p2.x(), p2.y());
		return (changed1 || changed2);
	}

	static bool checkParametrization2(QVector4D &params, const QVector4D &uvRange1, const QVector4D &uvRange2, bool wrapped1, bool wrapped2)
	{
		bool changed1 = false, changed2 = false;
		QVector2D params1 = QVector2D(params.x(), params.y());
		QVector2D params2 = QVector2D(params.z(), params.w());
		if (wrapped1)
			wrapParams(uvRange1, params1);
		else
			changed1 = trimParams(uvRange1, params1);
		if (wrapped2)
			wrapParams(uvRange2, params2);
		else
			changed2 = trimParams(uvRange2, params2);
		params = QVector4D(params1.x(), params1.y(), params2.x(), params2.y());
		if (wrapped1 || wrapped2)
			return false;
		return (changed1 || changed2);
		/*bool changed1 = false, changed2 = false;
		QVector2D params1 = QVector2D(params.x(), params.y());
		QVector2D params2 = QVector2D(params.z(), params.w());
		wrapped1 ? changed1 = wrapParams(uvRange1, params1) : changed1 = trimParams(uvRange1, params1);
		wrapped2 ? changed2 = wrapParams(uvRange2, params2) : changed2 = trimParams(uvRange2, params2);
		params = QVector4D(params1.x(), params1.y(), params2.x(), params2.y());
		return (changed1 || changed2);*/
	}

	static bool checkParametrization3(QVector4D &params, const QVector4D &uvRange1, const QVector4D &uvRange2, bool wrapped1, bool wrapped2, bool &wasWrapped1, bool &wasWrapped2)
	{
		bool changed1 = wasWrapped1, changed2 = wasWrapped2;
		QVector2D params1 = QVector2D(params.x(), params.y());
		QVector2D params2 = QVector2D(params.z(), params.w());
		if (wrapParams(uvRange1, params1))
			wasWrapped1 = true;
		if (wrapParams(uvRange2, params2))
			wasWrapped2 = true;
		params = QVector4D(params1.x(), params1.y(), params2.x(), params2.y());
		//return (wasWrapped1 || wasWrapped2);
		return (changed1 || changed2);
		/*bool changed1 = false, changed2 = false;
		bool wasWrappedT1 = wasWrapped1;
		bool wasWrappedT2 = wasWrapped2;
		if (!wrapped1)
			wasWrappedT1 = true;
		if (!wrapped2)
			wasWrappedT2 = true;
		QVector2D params1 = QVector2D(params.x(), params.y());
		QVector2D params2 = QVector2D(params.z(), params.w());
		wrapped1 ? changed1 = wrapParams(uvRange1, params1) : changed1 = trimParams(uvRange1, params1);
		if (changed1)
			wasWrapped1 = true;
		wrapped2 ? changed2 = wrapParams(uvRange2, params2) : changed2 = trimParams(uvRange2, params2);
		if (changed2)
			wasWrapped2 = true;
		params = QVector4D(params1.x(), params1.y(), params2.x(), params2.y());
		return ((changed1 && wasWrappedT1) || (changed2 && wasWrappedT2));*/
	}

	static QVector2D getGradient(Surface surface, const QVector2D &uv, const QVector3D &point)
	{
		QVector3D diff = (surface->getPointByUV(uv.x(), uv.y()) - point);
		QVector3D du = surface->getUDerivative(uv.x(), uv.y());
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
			//QVector3D::dotProduct(diff, du2), QVector3D::dotProduct(diff, dv2));
			QVector3D::dotProduct(-diff, du2), QVector3D::dotProduct(-diff, dv2));
	}

	static QVector2D findClosestPoint(Surface surface, const QVector3D &cursorPos)
	{
		double alpha = gradientAlpha;
		QVector2D point = surface->approximatePointOnSurface(cursorPos), dk = point;
		int i = 0;
		while (i++ < maxIter)
		{
			if (i >= maxIter)
			{
				qDebug("closest point max iter");
			}
			//QVector2D grad = getGradient(surface, point, cursorPos);
			dk = point - alpha * getGradient(surface, point, cursorPos);
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
			if (i >= maxIter)
			{
				qDebug("intersection point max iter");
			}
			QVector4D dk = uvuv - alpha * getGradients(surface1, surface2, uvuv);

			QVector4D uvRange1 = surface1->getRangeUV(dk.x(), dk.y());
			QVector4D uvRange2 = surface2->getRangeUV(dk.z(), dk.w());
			if (checkParametrization2(dk, uvRange1, uvRange2, surface1->isUWrapped(), surface2->isUWrapped()))
			{
				uvuv = dk;
				alpha *= 0.5f;
				continue;
			}

			double l = pow((surface1->getPointByUV(dk.x(), dk.y()) - surface2->getPointByUV(dk.z(), dk.w())).length(), 2.0f);
			//- pow((surface1->getPointByUV(uvuv.x(), uvuv.y()) - surface2->getPointByUV(uvuv.z(), uvuv.w())).length(), 2.0f);
			if (abs(l) < gradientEps)
			{
				uvuv = dk;
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

	static QMatrix4x4 calculateJacobi(Surface surface1, Surface surface2, const QVector3D &versor, const QVector4D &params)
	{
		QMatrix4x4 jacobi;
		QVector3D du1 = surface1->getUDerivative(params.x(), params.y());
		QVector3D dv1 = surface1->getVDerivative(params.x(), params.y());
		QVector3D du2 = surface2->getUDerivative(params.z(), params.w());
		QVector3D dv2 = surface2->getVDerivative(params.z(), params.w());
		//QVector3D normal1 = QVector3D::crossProduct(du1, dv1);
		//QVector3D normal2 = QVector3D::crossProduct(du2, dv2);
		//QVector3D versor2 = QVector3D::crossProduct(normal1, normal2).normalized();
		//versor /= QVector3D::crossProduct(normal1, normal2).length();
		jacobi.setRow(0, QVector4D(du1.x(), du1.y(), du1.z(), QVector3D::dotProduct(du1, versor)));
		jacobi.setRow(1, QVector4D(dv1.x(), dv1.y(), dv1.z(), QVector3D::dotProduct(dv1, versor)));
		jacobi.setRow(2, QVector4D(-du2.x(), -du2.y(), -du2.z(), 0));
		jacobi.setRow(3, QVector4D(-dv2.x(), -dv2.y(), -dv2.z(), 0));
		return jacobi.transposed();
	}

	static QVector4D calculateJacobiFunction(Surface surface1, Surface surface2,
		const QVector3D &versor, const QVector4D &prevParams, const QVector4D &params, double delta)
	{
		QVector3D point1 = surface1->getPointByUV(params.x(), params.y());
		QVector4D fun = QVector4D(point1 - surface2->getPointByUV(params.z(), params.w()), 0);
		fun.setW(QVector3D::dotProduct(point1 - surface1->getPointByUV(prevParams.x(), prevParams.y()), versor) - delta);
		return fun;
	}

	static bool findNextPoint(Surface surface1, Surface surface2,
		const QVector4D &params, const QVector3D versor, double delta, QVector4D &result, NewtonWrapTrim &paramsLogic)
	{
		QVector4D prevParams = params;
		result = params;
		//bool wasWrappd = paramsLogic.wasWrapped;
		//NewtonWrapTrim paramsLogic;
		while (abs(delta) > newtonEps)
		{
			int i = 0;
			while (i++ < maxIterNewton)
			{
				if (i >= maxIterNewton)
				{
					qDebug("newton max iter");
				}
				QVector4D fun = calculateJacobiFunction(surface1, surface2, versor, params, prevParams, delta);
				QMatrix4x4 jacobi = calculateJacobi(surface1, surface2, versor, prevParams).inverted();
				result = prevParams - jacobi * fun;
				QVector4D prevResult = result;
				if (checkParametrization(result, surface1, surface2, paramsLogic))
				{
					if (paramsLogic.wasTrimmed)
					{
						return false;
					}
					if (paramsLogic.wasWrapped)
					{
						break;
						//if (paramsLogic.wrappedSecondTime)
							//return false;
						if ((result - prevResult).length() < newtonEps)
						{
							break;
						}
						prevParams = result;
						continue;
					}
				}
				//if (surface1->isUWrapped() || surface2->isUWrapped())
				//{
				//	prevParams = result;
				//	if (checkParametrization3(result, uvRange1, uvRange2, surface1->isUWrapped(), surface2->isUWrapped(), wasWrapped1, wasWrapped2))
				//	{
				//		//return false;
				//		//break;
				//		if ((result - prevParams).length() < newtonEps)
				//		{
				//			break;
				//		}
				//		continue;
				//	}
				//}
				//else
				//{
				//	if (checkParametrization2(result, uvRange1, uvRange2, surface1->isUWrapped(), surface2->isUWrapped()))
				//	{
				//		return false;
				//	}
				//}
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
		//QVector4D prevParams = params;
		//result = params;
		//bool wasWrapepd1 = false, wasWrapepd2 = false;
		//while (abs(delta) > newtonEps)
		//{
		//	int i = 0;
		//	while (i++ < maxIterNewton)
		//	{
		//		if (i >= maxIterNewton)
		//		{
		//			qDebug("newton max iter");
		//		}
		//		//QVector3D versor2 = dir * getTangentVector(surface1, surface2, result);
		//		QVector4D fun = calculateJacobiFunction(surface1, surface2, versor, params, prevParams, delta);
		//		QMatrix4x4 jacobi = calculateJacobi(surface1, surface2, versor, prevParams).inverted();
		//		result = prevParams - jacobi * fun;

		//		QVector4D uvRange1 = surface1->getRangeUV(result.x(), result.y());
		//		QVector4D uvRange2 = surface2->getRangeUV(result.z(), result.w());

		//		if (checkParametrization2(result, uvRange1, uvRange2, surface1->isWrapped(), surface2->isWrapped()))// || (result - prevParams).length() < newtonEps
		//		//if (checkParametrization3(result, uvRange1, uvRange2, surface1->isWrapped(), surface2->isWrapped(), wasWrapepd1, wasWrapepd2))
		//		{

		//			return false;
		//		}
		//		if ((result - prevParams).length() < newtonEps)
		//		{
		//			break;
		//		}
		//		prevParams = result;
		//	}
		//	if (i > maxIterNewton)
		//	{
		//		delta *= 0.5f;
		//		continue;
		//	}
		//	break;
		//}

		//return delta > newtonEps;
	}

	static bool checkWrap(QVector3D startingPoint, QVector3D currentPoint, int iter)
	{
		int borderIter = 5;
		if (iter >= borderIter)
		{
			float eps = 0.005f;
			float len = (startingPoint - currentPoint).length();
			if (len < eps)
			{
				return true;
			}
		}
		return false;
	}

	static std::vector<QVector4D> getTrimmingCurve(Surface surface1, Surface surface2, const QVector3D &cursorPos)
	{
		double delta = 0.01f;
		std::vector<QVector4D> vertices;
		std::vector<std::vector<QVector4D>> curves;
		QVector4D intersectionPoint = findIntersectionPoint(surface1, surface2, cursorPos);
		QVector4D lastPoint = intersectionPoint;
		vertices.push_back(intersectionPoint);
		QVector4D nextPoint;
		double dist = std::numeric_limits<double>::infinity();
		int dir = 1;
		int i = 0;
		NewtonWrapTrim paramsLogic;
		while (i++ < maxIterNewton && dist > newtonEps)
		{
			QVector3D versor = dir * getTangentVector(surface1, surface2, lastPoint);
			if (!findNextPoint(surface1, surface2, lastPoint, versor, delta, nextPoint, paramsLogic))
			{
				if (dir == -1)
				{
					curves.emplace_back(vertices);
					break;
				}
				dir = -1;
				paramsLogic.wasTrimmed = false;
				paramsLogic.wasWrapped = false;
				curves.emplace_back(vertices);
				vertices.clear();
				lastPoint = intersectionPoint;
				continue;
			}
			vertices.push_back(nextPoint);
			if ((surface1->isUWrapped() || surface1->isVWrapped()) && checkWrap(
				surface1->getPointByUV(intersectionPoint.x(), intersectionPoint.y()),
				surface1->getPointByUV(nextPoint.x(), nextPoint.y()), i))
				break;
			if ((surface2->isUWrapped() || surface2->isVWrapped()) && checkWrap(
				surface2->getPointByUV(intersectionPoint.z(), intersectionPoint.w()),
				surface2->getPointByUV(nextPoint.z(), nextPoint.w()), i))
				break;
			/*if ((surface1->isUWrapped() || surface1->isVWrapped() || surface2->isUWrapped() || surface2->isVWrapped())
				&& (checkWrap(surface1->getPointByUV(intersectionPoint.x(), intersectionPoint.y()), surface1->getPointByUV(nextPoint.x(), nextPoint.y()), i)
				|| checkWrap(surface2->getPointByUV(intersectionPoint.z(), intersectionPoint.w()), surface2->getPointByUV(nextPoint.z(), nextPoint.w()), i)))
				break;*/
			dist = (lastPoint - nextPoint).length();
			if (dist < newtonEps)
			{
				qDebug("distance");
			}
			/*if ((nextPoint - intersectionPoint).length() < newtonEps)
			{
				qDebug("distance");
				break;
			}*/
			lastPoint = nextPoint;
		}
		//
		//return vertices;
		//
		//
		float eps = 0.03f;
		//if (curves.size() < 1)
		//	return std::vector<QVector4D>();
		if (curves.size() == 2)
		{
			std::reverse(curves[0].begin(), curves[0].end());
			vertices = curves[0];
			vertices.insert(std::end(vertices), std::begin(curves[1]), std::end(curves[1]));
			if (!vertices.empty() && (surface1->getPointByUV(vertices.begin()->x(), vertices.begin()->y()) - surface1->getPointByUV(vertices.begin()->x(), vertices.begin()->y())).length() < eps)
			{
				vertices.emplace_back(vertices[0]);
			}
		}
		//
		return vertices;
	}
}