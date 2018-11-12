#pragma once
#include <vector>
#include <memory>

//#include "bezierSurfaceC0.h"
//#include "bezierSurfaceC2.h"
//#include "point3d.h"
//#include "torus.h"
//class Torus;
//class BezierSurfaceC2;
//class BezierSurfaceC0;
//class QString;
//class QFile;
//class Point3D;

namespace fileManager
{

#include "bezierSurfaceC0.h"
#include "bezierSurfaceC2.h"
#include "point3d.h"
#include "torus.h"

	using surfaceC0Ids = QPair<std::vector<std::shared_ptr<BezierSurfaceC0>>, std::vector<int>>;
	using surfaceC2Ids = QPair<std::vector<std::shared_ptr<BezierSurfaceC2>>, std::vector<std::vector<int>>>;

	static std::vector<std::shared_ptr<Point3D>> getPoints(const QString& fileContent)
	{
		std::vector<std::shared_ptr<Point3D>> points;
		QJsonDocument d = QJsonDocument::fromJson(fileContent.toUtf8());
		QJsonObject jsonObj = d.object();
		QJsonArray jPoints = jsonObj["points"].toArray();
		std::vector<QString> pointsNames;
		std::vector<QVector3D> pointsCoords;
		for (const auto &point : jPoints)
		{
			QJsonObject obj = point.toObject();
			points.emplace_back(std::make_shared<Point3D>(DrawableObject::ObjectType::point3D, obj["name"].toString(),
				QVector4D(obj["x"].toDouble(), obj["y"].toDouble(),
					obj["z"].toDouble(), 1)));
		}
		return points;
	}

	//static std::vector<std::shared_ptr<BezierSurfaceC0>> getSurfacesC0(const QString& fileContent)
	//static QPair<std::vector<std::shared_ptr<BezierSurfaceC0>>, std::vector<std::vector<int>>> getSurfacesC0(const QString& fileContent)
	//static QPair<std::vector<std::shared_ptr<BezierSurfaceC0>>, std::vector<int>> getSurfacesC0(const QString& fileContent)
	//{
	//	std::vector<std::shared_ptr<BezierSurfaceC0>> surfaces;
	//	QJsonDocument d = QJsonDocument::fromJson(fileContent.toUtf8());
	//	QJsonObject jsonObj = d.object();
	//	QJsonArray surfacesC0 = jsonObj["surfacesC0"].toArray();
	//	//std::vector<QString> surfacesC0Names;
	//	//std::vector<QPair<double, double>> surfacesC0uv;
	//	//std::vector<QPair<double, double>> surfacesC0flakeUV;
	//	//std::vector<std::vector<int>> surfacesC0pointsIds;
	//	std::vector<int> surfacesC0pointsIds;
	//	for (const auto &surface : surfacesC0)
	//	{
	//		QJsonObject obj = surface.toObject();
	//		//surfacesC0Names.emplace_back(obj["name"].toString());
	//		//surfacesC0uv.emplace_back(QPair<double, double>(obj["u"].toDouble(), obj["v"].toDouble()));
	//		//surfacesC0flakeUV.emplace_back(QPair<double, double>(obj["flakeU"].toDouble(), obj["flakeV"].toDouble()));
	//		QJsonArray idsArray = obj["points"].toArray();
	//		for (const auto &idArr : idsArray)
	//		{
	//			QJsonArray ids = idArr.toArray();
	//			std::vector<int> pointIds;
	//			for (const auto &id : ids)
	//			{
	//				pointIds.emplace_back(id.toInt());
	//			}
	//			surfacesC0pointsIds.emplace_back(pointIds);
	//		}
	//		//////////
	//		BezierSurfaceData data;
	//		data.m_u = obj["u"].toDouble();
	//		data.m_v = obj["v"].toDouble();
	//		//data.m_patchesX = obj["flakeU"].toDouble();
	//		//data.m_patchesY = obj["flakeV"].toDouble();
	//		data.m_patchesX = (idsArray.count() - 1 ) / 3;
	//		data.m_patchesY = (idsArray.at(0).toArray().count() - 1) / 3;
	//		if (obj["cylinder"].toBool())
	//			data.m_surfaceType = BezierSurfaceData::SurfaceType::cylinder;
	//		else
	//			data.m_surfaceType = BezierSurfaceData::SurfaceType::plane;
	//		surfaces.emplace_back(std::make_shared<BezierSurfaceC0>(DrawableObject::ObjectType::bezierSurfaceC0, obj["name"].toString(), data));
	//		//////////
	//	}
	//	surfaceC0Ids surfacesIds = surfaceC0Ids(surfaces, surfacesC0pointsIds);
	//	//return surfaces;
	//	return surfacesIds;
	//}

	static std::vector<QPair<std::shared_ptr<BezierSurfaceC0>, std::vector<int>>> getSurfacesC0(const QString& fileContent)
	{
		std::vector<QPair<std::shared_ptr<BezierSurfaceC0>, std::vector<int>>> surfaceId;
		QJsonDocument d = QJsonDocument::fromJson(fileContent.toUtf8());
		QJsonObject jsonObj = d.object();
		QJsonArray surfacesC0 = jsonObj["surfacesC0"].toArray();
		for (const auto &surface : surfacesC0)
		{
			QJsonObject obj = surface.toObject();
			QJsonArray idsArray = obj["points"].toArray();
				std::vector<int> pointIds;
			for (const auto &idArr : idsArray)
			{
				QJsonArray ids = idArr.toArray();
				for (const auto &id : ids)
				{
					pointIds.emplace_back(id.toInt());
				}
			}
			BezierSurfaceData data;
			data.m_u = obj["u"].toDouble();
			data.m_v = obj["v"].toDouble();
			data.m_patchesX = (idsArray.count() - 1 ) / 3;
			data.m_patchesY = (idsArray.at(0).toArray().count() - 1) / 3;
			if (obj["cylinder"].toBool())
				data.m_surfaceType = BezierSurfaceData::SurfaceType::cylinder;
			else
				data.m_surfaceType = BezierSurfaceData::SurfaceType::plane;
			surfaceId.emplace_back(QPair<std::shared_ptr<BezierSurfaceC0>, std::vector<int>>(
				std::make_shared<BezierSurfaceC0>(DrawableObject::ObjectType::bezierSurfaceC0, obj["name"].toString(),
				                                  data), pointIds));
		}
		return surfaceId;
	}

	static std::vector<QPair<std::shared_ptr<BezierSurfaceC2>, std::vector<int>>> getSurfacesC2(const QString& fileContent)
	{
		std::vector<QPair<std::shared_ptr<BezierSurfaceC2>, std::vector<int>>> surfaceId;
		QJsonDocument d = QJsonDocument::fromJson(fileContent.toUtf8());
		QJsonObject jsonObj = d.object();
		QJsonArray surfacesC2 = jsonObj["surfacesC2"].toArray();
		for (const auto &surface : surfacesC2)
		{
			QJsonObject obj = surface.toObject();
			QJsonArray idsArray = obj["points"].toArray();
				std::vector<int> pointIds;
			for (const auto &idArr : idsArray)
			{
				QJsonArray ids = idArr.toArray();
				for (const auto &id : ids)
				{
					pointIds.emplace_back(id.toInt());
				}
			}
			BezierSurfaceData data;
			data.m_u = obj["u"].toDouble();
			data.m_v = obj["v"].toDouble();
			data.m_patchesX = idsArray.count() - 3;
			data.m_patchesY = idsArray.at(0).toArray().count() - 3;
			if (obj["cylinder"].toBool())
				data.m_surfaceType = BezierSurfaceData::SurfaceType::cylinder;
			else
				data.m_surfaceType = BezierSurfaceData::SurfaceType::plane;
			surfaceId.emplace_back(QPair<std::shared_ptr<BezierSurfaceC2>, std::vector<int>>(
				std::make_shared<BezierSurfaceC2>(DrawableObject::ObjectType::bezierSurfaceC0, obj["name"].toString(),
				                                  data), pointIds));
		}
		return surfaceId;
	}

	//static std::vector<std::shared_ptr<BezierSurfaceC2>> getSurfacesC2(const QString& fileContent)
	//static QPair<std::vector<std::shared_ptr<BezierSurfaceC2>>, std::vector<std::vector<int>>> getSurfacesC2(const QString& fileContent)
	//static std::vector<QPair<std::shared_ptr<BezierSurfaceC2>, std::vector<int>>> getSurfacesC2(const QString& fileContent)
	//{
	//	std::vector<std::shared_ptr<BezierSurfaceC2>> surfaces;
	//	QJsonDocument d = QJsonDocument::fromJson(fileContent.toUtf8());
	//	QJsonObject jsonObj = d.object();
	//	QJsonArray surfacesC2 = jsonObj["surfacesC2"].toArray();
	//	//std::vector<QString> surfacesC2Names;
	//	//std::vector<QPair<double, double>> surfacesC2uv;
	//	//std::vector<QPair<double, double>> surfacesC2flakeUV;
	//	//std::vector<int> surfacesC2pointsIds;
	//	std::vector<std::vector<int>> surfacesC0pointsIds;
	//	for (const auto &surface : surfacesC2)
	//	{
	//		QJsonObject obj = surface.toObject();
	//		//surfacesC2Names.emplace_back(obj["name"].toString());
	//		//surfacesC2uv.emplace_back(QPair<double, double>(obj["u"].toDouble(), obj["v"].toDouble()));
	//		//surfacesC2flakeUV.emplace_back(QPair<double, double>(obj["flakeU"].toDouble(), obj["flakeV"].toDouble()));
	//		QJsonArray idsArray = obj["points"].toArray();
	//		for (const auto &idArr : idsArray)
	//		{
	//			QJsonArray ids = idArr.toArray();
	//			std::vector<int> pointIds;
	//			for (const auto &id : ids)
	//			{
	//				pointIds.emplace_back(id.toInt());
	//			}
	//			surfacesC0pointsIds.emplace_back(pointIds);
	//		}
	//		//
	//		BezierSurfaceData data;
	//		data.m_u = obj["u"].toDouble();
	//		data.m_v = obj["v"].toDouble();
	//		data.m_patchesX = obj["flakeU"].toDouble();
	//		data.m_patchesY = obj["flakeV"].toDouble();
	//		if (obj["cylinder"].toBool())
	//			data.m_surfaceType = BezierSurfaceData::SurfaceType::cylinder;
	//		else
	//			data.m_surfaceType = BezierSurfaceData::SurfaceType::plane;
	//		surfaces.emplace_back(std::make_shared<BezierSurfaceC2>(DrawableObject::ObjectType::bezierSurfaceC2, obj["name"].toString(), data));
	//		//
	//	}

	//	surfaceC2Ids surfacesIds = surfaceC2Ids(surfaces, surfacesC0pointsIds);
	//	//return surfaces;
	//	return surfacesIds;
	//}

	static std::vector<std::shared_ptr<Torus>> getTori(const QString& fileContent)
	{
		std::vector<std::shared_ptr<Torus>> tori;
		QJsonDocument d = QJsonDocument::fromJson(fileContent.toUtf8());
		QJsonObject jsonObj = d.object();
		QJsonArray toruses = jsonObj["toruses"].toArray();
		std::vector<double> r;
		std::vector<double> R;
		std::vector<int> minorU;
		std::vector<int> majorV;
		std::vector<QVector3D> centers;
		std::vector<QVector3D> rotations;
		std::vector<QVector3D> scales;
		for (const auto &jTorus : toruses)
		{
			QJsonObject obj = jTorus.toObject();
			auto torus = std::make_shared<Torus>(obj["r"].toDouble(), obj["R"].toDouble(), obj["u"].toInt(),
				obj["v"].toInt(), DrawableObject::ObjectType::torus, "Torus");
			QJsonObject center = obj["center"].toObject();
			torus->setPosition(QVector3D(center["x"].toDouble(), center["y"].toDouble(), center["z"].toDouble()));
			QJsonObject rotation = obj["rotation"].toObject();
			torus->rotate(QVector3D(rotation["x"].toDouble(), rotation["y"].toDouble(), rotation["z"].toDouble()));
			QJsonObject scale = obj["scale"].toObject();
			tori.emplace_back(torus);
			scales.emplace_back(QVector3D(scale["x"].toDouble(), scale["y"].toDouble(), scale["z"].toDouble()));
		}
		return tori;
	}
};
