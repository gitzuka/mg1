#pragma once
#include "bezierSurfaceC0.h"
#include "bezierSurfaceC2.h"
#include "point3d.h"
#include "torus.h"
#include "uiConnector.h"
#include <vector>
#include <memory>
namespace fileManager
{



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
			data.m_patchesX = (idsArray.count() - 1) / 3;
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
				std::make_shared<BezierSurfaceC2>(DrawableObject::ObjectType::bezierSurfaceC2, obj["name"].toString(),
					data), pointIds));
		}
		return surfaceId;
	}

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

	static QJsonObject savePoint(const std::shared_ptr<Point3D> &point)
	{
		QJsonObject jPoint;
		jPoint["name"] = point->getName();
		jPoint["x"] = point->getPosition().x();
		jPoint["y"] = point->getPosition().y();
		jPoint["z"] = point->getPosition().z();
		return jPoint;
	}

	static QJsonObject saveSurfaceC0(const std::shared_ptr<BezierSurface> &surface, QJsonArray &jPoints)
	{
		QJsonObject jSurface;
		jSurface["name"] = surface->getName();
		jSurface["u"] = surface->getSurfaceData().m_u;
		jSurface["v"] = surface->getSurfaceData().m_v;
		jSurface["flakeU"] = surface->getSurfaceData().m_patchesX;
		jSurface["flakeV"] = surface->getSurfaceData().m_patchesY;
		std::vector<std::shared_ptr<Point3D>> points = surface->getPoints();
		int index = jPoints.size();
		for (const auto &point : points)
		{
			jPoints.append(savePoint(point));
		}
		QJsonArray indices;
		int X = 3 * surface->getSurfaceData().m_patchesX;
		int Y = 3 * surface->getSurfaceData().m_patchesY + 1;
		if (surface->getSurfaceType() == BezierSurfaceData::SurfaceType::plane)
		{
			jSurface["cylinder"] = false;
			X += 1;
		}
		for (int i = 0; i < X; ++i)
		{
			QJsonArray arr;
			for (int j = 0; j < Y; ++j)
			{
				arr.append(QJsonValue(index + j * X + i));
			}
			indices.append(arr);
		}
		if (surface->getSurfaceType() != BezierSurfaceData::SurfaceType::plane)
		{
			jSurface["cylinder"] = true;
			indices.append(indices[0]);

		}
		jSurface["points"] = indices;
		return jSurface;
	}

	static QJsonObject saveSurfaceC2(const std::shared_ptr<BezierSurface> &surface, QJsonArray &jPoints)
	{
		QJsonObject jSurface;
		jSurface["name"] = surface->getName();
		jSurface["u"] = surface->getSurfaceData().m_u;
		jSurface["v"] = surface->getSurfaceData().m_v;
		jSurface["flakeU"] = surface->getSurfaceData().m_patchesX;
		jSurface["flakeV"] = surface->getSurfaceData().m_patchesY;
		std::vector<std::shared_ptr<Point3D>> points = surface->getPoints();
		int index = jPoints.size();
		for (const auto &point : points)
		{
			jPoints.append(savePoint(point));
		}
		QJsonArray indices;
		if (surface->getSurfaceType() == BezierSurfaceData::SurfaceType::plane)
		{
			jSurface["cylinder"] = false;
			int X = surface->getSurfaceData().m_patchesX + 3;
			int Y = surface->getSurfaceData().m_patchesY + 3;
			for (int i = 0; i < X; ++i)
			{
				QJsonArray arr;
				for (int j = 0; j < Y; ++j)
				{
					arr.append(QJsonValue(index + j * X + i));
				}
				indices.append(arr);
			}
		}
		else
		{
			jSurface["cylinder"] = true;
			int X = surface->getSurfaceData().m_patchesX;
			int Y = surface->getSurfaceData().m_patchesY + 3;
			for (int i = 0; i < X; ++i)
			{
				QJsonArray arr;
				for (int j = 0; j < Y; ++j)
				{
					arr.append(QJsonValue(index + j * X + i));
				}
				indices.append(arr);
			}
			for (int i = 0; i < 3; ++i)
			{
				indices.append(indices[i]);
			}

		}
		jSurface["points"] = indices;
		return jSurface;
	}

	static QJsonObject saveTorus(const std::shared_ptr<Torus> &torus)
	{
		QJsonObject jTorus;
		jTorus["r"] = torus->getSmallRadius();
		jTorus["R"] = torus->getBigRadius();
		jTorus["u"] = torus->getMinorSegments();
		jTorus["v"] = torus->getMajorSegments();
		QJsonObject rotation;
		rotation["x"] = torus->getRotation().x();
		rotation["y"] = torus->getRotation().y();
		rotation["z"] = torus->getRotation().z();
		QJsonObject center;
		center["x"] = torus->getPosition().x();
		center["y"] = torus->getPosition().y();
		center["z"] = torus->getPosition().z();
		QJsonObject scale;
		scale["x"] = torus->getScale().x();
		scale["y"] = torus->getScale().y();
		scale["z"] = torus->getScale().z();
		jTorus["center"] = center;
		jTorus["rotation"] = rotation;
		jTorus["scale"] = scale;
		return jTorus;
	}

	static float* loadHeightmap(const QString &fileContent, int &height, int &width)
	{
		QJsonDocument document = QJsonDocument::fromJson(fileContent.toUtf8());
		QJsonObject jsonObj = document.object();
		height = jsonObj["height"].toInt();
		width = jsonObj["width"].toInt();
		float *heightmap = new float[width * height];
		QJsonArray heights = jsonObj["heights"].toArray();
		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				heightmap[i * width + j] = heights[i * width + j].toDouble();
			}
		}
		return heightmap;
	}

	static void saveHeightmap(const float *map, int width, int height, const QString &path)
	{
		QJsonObject jwidth;
		jwidth["width"] = width;
		QJsonObject jheight;
		jheight["height"] = height;
		QJsonArray heights;
		for (int i = 0; i < width; ++i)
		{
			for (int j = 0; j < height; ++j)
			{
				heights.append(map[i * width + j]);
			}
		}

		QFile saveFile(path);

		if (!saveFile.open(QIODevice::WriteOnly))
		{
			qWarning("Couldn't open save file.");
			return;
		}

		QJsonObject heightmap;
		heightmap["width"] = width;
		heightmap["height"] = height;
		heightmap["heights"] = heights;
		QJsonDocument saveDoc(heightmap);
		saveFile.write(saveDoc.toJson());
	}

	static void saveScene(const std::unordered_map<int, std::unique_ptr<UiConnector>> &uiConnectors, const QString &path)
	{
		//std::vector<std::shared_ptr<Point3D>> points;
		/*std::vector<std::shared_ptr<BezierSurfaceC0>> surfaces0;
		std::vector<std::shared_ptr<BezierSurfaceC2>> surfaces2;
		std::vector<std::shared_ptr<Torus>> tori;*/

		QJsonArray points;
		QJsonArray jSurfsC0;
		QJsonArray jSurfsC2;
		QJsonArray jTori;

		for (const auto &obj : uiConnectors)
		{
			switch (obj.second->getObject()->m_type)
			{
			case DrawableObject::ObjectType::bezierSurfaceC0:
			{
				jSurfsC0.append(saveSurfaceC0(std::static_pointer_cast<BezierSurfaceC0>(obj.second->getObject()), points));
				break;
			}
			case DrawableObject::ObjectType::bezierSurfaceC2:
			{
				jSurfsC2.append(saveSurfaceC2(std::static_pointer_cast<BezierSurfaceC2>(obj.second->getObject()), points));
				break;
			}
			case DrawableObject::ObjectType::torus:
			{
				jTori.append(saveTorus(std::static_pointer_cast<Torus>(obj.second->getObject())));
				break;
			}
			default:
				break;
			}
		}

		QFile saveFile(path);

		if (!saveFile.open(QIODevice::WriteOnly))
		{
			qWarning("Couldn't open save file.");
			return;
		}

		QJsonObject scene;
		scene["points"] = points;
		scene["surfacesC0"] = jSurfsC0;
		scene["surfacesC2"] = jSurfsC2;
		scene["toruses"] = jTori;
		QJsonDocument saveDoc(scene);
		saveFile.write(saveDoc.toJson());
	}
}