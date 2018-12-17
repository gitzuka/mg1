#include "scene.h"
#include "point3d.h"
#include "bezierCurveC0.h"
#include "torus.h"
#include "uiTorus.h"
#include "uiPoint3d.h"
#include "uiCursor3d.h"
#include "colors.h"
#include "bezierCurveC2.h"
#include "uiBezierCurveC2.h"
#include "uiBezierC2Interpolated.h"
#include "bezierC2Interpolated.h"
#include "uiBezierSurfaceC0.h"
#include "uiBezierSurfaceC2.h"
#include "uiTrimmingCurve.h"
#include "trimmingCurve.h"
#include "uiAxes.h"
#include "fileManager.h"
#include "Intersections.h"
#include "3dmath.h"
#include "HeightmapGenerator.h"
#include "pathsGenerator.h"

Scene::Scene() : m_stereoscopy(false), m_isCursor3d(false)
{
}

void Scene::addUiConnector(std::unique_ptr<UiConnector> uiConnector)
{
	m_uiConnectors.emplace(std::make_pair(uiConnector->getObject()->getId(), std::move(uiConnector)));
}

void Scene::createCurveC0fromPoints(const QList<int> &ids)
{
	std::shared_ptr<BezierCurveC0> bezierCurveC0 = std::make_shared<BezierCurveC0>(BezierCurveC0::ObjectType::bezierCurveC0, "BezierCurveC0");
	std::unique_ptr<UiBezierCurveC0> uiConnector = std::make_unique<UiBezierCurveC0>(bezierCurveC0);
	addUiConnector(std::move(uiConnector));
	emit addedBezierCurveC0("BezierCurveC0", bezierCurveC0->getId(), static_cast<const UiBezierCurveC0*>(getUiConntector(bezierCurveC0->getId())));
	std::vector<std::shared_ptr<DrawableObject>> points;
	for (int i = 0; i < ids.count(); ++i)
	{
		points.push_back(getSceneObject(ids.at(i)));
	}
	static_cast<UiBezierCurveC0*>(getUiConntector(bezierCurveC0->getId()))->assignPoints(points, bezierCurveC0->getId());

}

void Scene::createCurveC2fromPoints(const QList<int> &ids)
{
	std::shared_ptr<BezierCurveC2> bezierCurveC2 = std::make_shared<BezierCurveC2>(BezierCurveC2::ObjectType::bezierCurveC2, "BezierCurveC2");
	std::unique_ptr<UiBezierCurveC2> uiConnector = std::make_unique<UiBezierCurveC2>(bezierCurveC2);
	addUiConnector(std::move(uiConnector));
	emit addedBezierCurveC2("BezierCurveC2", bezierCurveC2->getId(), static_cast<const UiBezierCurveC2*>(getUiConntector(bezierCurveC2->getId())));
	std::vector<std::shared_ptr<DrawableObject>> points;
	points.reserve(ids.count());
	for (int i = 0; i < ids.count(); ++i)
	{
		points.push_back(getSceneObject(ids.at(i)));
	}
	static_cast<UiBezierCurveC2*>(getUiConntector(bezierCurveC2->getId()))->assignPoints(points, bezierCurveC2->getId());
}

void Scene::createCurveC2IntfromPoints(const QList<int>& ids)
{
	std::shared_ptr<BezierC2Interpolated> bezierCurveC2Int = std::make_shared<BezierC2Interpolated>(BezierC2Interpolated::ObjectType::bezierC2Interpolated, "BezierC2Interpolated");
	std::unique_ptr<UiBezierC2Interpolated> uiConnector = std::make_unique<UiBezierC2Interpolated>(bezierCurveC2Int);
	addUiConnector(std::move(uiConnector));
	emit addedBezierC2Interpolated("BezierC2Interpolated", bezierCurveC2Int->getId(), static_cast<const UiBezierC2Interpolated*>(getUiConntector(bezierCurveC2Int->getId())));
	std::vector<std::shared_ptr<DrawableObject>> points;
	points.reserve(ids.count());
	for (int i = 0; i < ids.count(); ++i)
	{
		points.push_back(getSceneObject(ids.at(i)));
	}
	static_cast<UiBezierC2Interpolated*>(getUiConntector(bezierCurveC2Int->getId()))->assignPoints(points, bezierCurveC2Int->getId());
}

void Scene::createBC0menu(const QPoint& pos, int id)
{
	QMenu myMenu;
	QAction *edit = myMenu.addAction("Edit mode");
	connect(edit, &QAction::triggered, this, [this, &id]()
	{
		setActiveObject(id);
		emit editModeBC0(id);
	});
	myMenu.exec(pos);
}

void Scene::createBC2menu(const QPoint& pos, int id)
{
	QMenu myMenu;
	QAction *edit = myMenu.addAction("Edit mode");
	connect(edit, &QAction::triggered, this, [this, &id]()
	{
		setActiveObject(id);
		emit editModeBC2(id);
	});
	myMenu.exec(pos);
}

void Scene::createBC2IntMenu(const QPoint& pos, int id)
{
	QMenu myMenu;
	QAction *edit = myMenu.addAction("Edit mode");
	connect(edit, &QAction::triggered, this, [this, &id]()
	{
		setActiveObject(id);
		emit editModeBC2Int(id);
	});
	myMenu.exec(pos);
}

void Scene::createPoint3Dmenu(const QPoint& pos, const QList<int>& ids)
{
	for (int i = 0; i < ids.count(); ++i)
	{
		if (getSceneObject(ids.at(i)) == nullptr || getSceneObject(ids.at(i))->m_type != DrawableObject::ObjectType::point3D)
		{
			return;
		}
	}
	QMenu myMenu;
	QAction *createBC0 = myMenu.addAction("Create Bezier Curve C0");
	connect(createBC0, &QAction::triggered, this, [this, &ids]()
	{
		createCurveC0fromPoints(ids);
	});
	QAction *createBC2 = myMenu.addAction("Create Bezier Curve C2");
	connect(createBC2, &QAction::triggered, this, [this, &ids]()
	{
		createCurveC2fromPoints(ids);
	});
	QAction *createBC2Int = myMenu.addAction("Create Bezier Curve C2 Interpolated");
	connect(createBC2Int, &QAction::triggered, this, [this, &ids]()
	{
		createCurveC2IntfromPoints(ids);
	});
	myMenu.exec(pos);
}

void Scene::createIntersectionMenu(const QPoint& pos, const QList<int>& ids)
{
	for (int i = 0; i < ids.count(); ++i)
	{
		if (getSceneObject(ids.at(i)) == nullptr || !getSceneObject(ids.at(i))->isIntersectable())
		{
			return;
		}
	}
	QMenu myMenu;
	QAction *createIntersection = myMenu.addAction("Check Intersections");
	connect(createIntersection, &QAction::triggered, this, [this, &ids]()
	{
		checkIntersections(ids);
	});
	myMenu.exec(pos);
}

void Scene::createTrimmingCurveMenu(const QPoint& pos, int id)
{
	QMenu myMenu;
	QAction *edit = myMenu.addAction("Upgrade to interpolated curve");
	connect(edit, &QAction::triggered, this, [this, &id]()
	{
		std::static_pointer_cast<TrimmingCurve>(getUiConntector(id)->getObject())->upgradeToInterpolating();
		//setActiveObject(id);
		//emit editModeBC2Int(id);
	});
	myMenu.exec(pos);
}

void Scene::checkIntersections(const QList<int>& ids)
{
	if (ids.count() == 1)
	{
		std::shared_ptr<IntersectableObject> surface = std::dynamic_pointer_cast<IntersectableObject>(getUiConntector(ids.at(0))->getObject());
		//std::vector<std::vector<QVector4D>> curves = Intersections::getTrimmingCurve(surface, m_cursor->getPosition());
		std::vector<QVector4D> params = Intersections::getTrimmingCurve(surface, m_cursor->getPosition());
		if (params.empty())
		{
			emit intersectionNotFound();
			return;
		}
		std::vector<QVector4D> vertices;
		for (const auto p : params)
		{
			vertices.emplace_back(QVector4D(surface->getPointByUV(p.x(), p.y()), 1.0f));
		}
		int id = createDrawableObject("TrimmingCurve");
		std::shared_ptr<TrimmingCurve> curve = std::dynamic_pointer_cast<TrimmingCurve>(getUiConntector(id)->getObject());
		curve->setVertices(vertices);
		curve->setParametrization(params);
		if (curve->getVertices().size() >= 2)
		{
			emit intersectionFound(curve->getParametrization(), surface->getRangeUV(), surface->getRangeUV(),
				getUiConntector(ids.at(0))->getObject(), getUiConntector(ids.at(0))->getObject(),
				QPair<bool, bool>(surface->isUWrapped(), surface->isVWrapped()),
				QPair<bool, bool>(surface->isUWrapped(), surface->isVWrapped()));
		}
		return;
		/*for (const auto c : curves)
		{
			vertices.reserve(c.size());
			for (int i = 0; i < c.size(); ++i)
			{
				vertices.emplace_back(surface->getPointByUV(c.at(i).x(), c.at(i).y()), 1.0f);
			}
			int id = createDrawableObject("TrimmingCurve");
			std::shared_ptr<TrimmingCurve> curve = std::dynamic_pointer_cast<TrimmingCurve>(getUiConntector(id)->getObject());
			curve->setVertices(vertices);
			auto params = c;
			curve->setParametrization(params);
			if (curve->getVertices().size() >= 2)
			{
				emit intersectionFound(curve->getParametrization(), surface->getRangeUV(), surface->getRangeUV(),
					getUiConntector(ids.at(0))->getObject(), getUiConntector(ids.at(0))->getObject(),
					QPair<bool, bool>(surface->isUWrapped(), surface->isVWrapped()),
					QPair<bool, bool>(surface->isUWrapped(), surface->isVWrapped()));
			}
		}*/
	}


	if (ids.count() != 2)
	{
		return;
	}
	std::shared_ptr<IntersectableObject> surface1 = std::dynamic_pointer_cast<IntersectableObject>(getUiConntector(ids.at(0))->getObject());
	std::shared_ptr<IntersectableObject> surface2 = std::dynamic_pointer_cast<IntersectableObject>(getUiConntector(ids.at(1))->getObject());
	std::vector<QVector4D> params = Intersections::getTrimmingCurve(surface1, surface2, m_cursor->getPosition());
	if (params.empty())
	{
		emit intersectionNotFound();
		return;
	}
	std::vector<QVector4D> vertices;
	for (const auto p : params)
	{
		vertices.emplace_back(QVector4D(surface1->getPointByUV(p.x(), p.y()), 1.0f));
	}
	//
	/*std::vector<QVector4D> vertices2;
	for (const auto p : params)
	{
		vertices2.emplace_back(QVector4D(surface2->getPointByUV(p.z(), p.w()), 1.0f));
	}*/
	//
	int id = createDrawableObject("TrimmingCurve");
	std::shared_ptr<TrimmingCurve> curve = std::dynamic_pointer_cast<TrimmingCurve>(getUiConntector(id)->getObject());
	curve->setVertices(vertices);
	curve->setParametrization(params);
	if (curve->getVertices().size() >= 2)
	{
		emit intersectionFound(curve->getParametrization(), surface1->getRangeUV(), surface2->getRangeUV(),
			getUiConntector(ids.at(0))->getObject(),
			getUiConntector(ids.at(1))->getObject(),
			QPair<bool, bool>(surface1->isUWrapped(), surface1->isVWrapped()),
			QPair<bool, bool>(surface2->isUWrapped(), surface2->isVWrapped()));
	}


	/*id = createDrawableObject("TrimmingCurve");
	std::shared_ptr<TrimmingCurve> curve2 = std::dynamic_pointer_cast<TrimmingCurve>(getUiConntector(id)->getObject());
	curve2->setColor(0, 255, 0);
	curve2->setVertices(vertices2);*/
	//curve2->setParametrization(params);
}

void Scene::setActiveObject(int id)
{
	if (m_cursor->getActiveObject() != nullptr)
	{
		emit objectDeactivated(m_cursor->getActiveObject()->getId());
		m_cursor->setActiveObject(nullptr);
	}
	m_cursor->setActiveObject(getUiConntector(id)->getObject());
	emit objectActivated(m_cursor->getActiveObject()->getId());
}

std::shared_ptr<DrawableObject> Scene::getSceneObject(int id)
{
	std::shared_ptr<DrawableObject> sceneObj;
	try
	{
		sceneObj = m_uiConnectors.find(id)->second.get()->getObject();
	}
	catch (std::out_of_range &e)
	{
		sceneObj = nullptr;
	}
	return sceneObj;
}

QPair<int, DrawableObject::ObjectType> Scene::createUiConnector(const QString& name)
{
	std::unique_ptr<UiConnector> uiConnector;
	if (name == "Torus")
	{
		uiConnector = std::make_unique<UiTorus>(std::make_shared<Torus>(DrawableObject::ObjectType::torus, name));
	}
	else if (name == "Point3D")
	{
		uiConnector = std::make_unique<UiPoint3D>(std::make_shared<Point3D>(Point3D::ObjectType::point3D, name));
	}
	else if (name == "BezierCurveC0")
	{
		uiConnector = std::make_unique<UiBezierCurveC0>(std::make_shared<BezierCurveC0>(BezierCurveC0::ObjectType::bezierCurveC0, name));
	}
	else if (name == "BezierCurveC2")
	{
		uiConnector = std::make_unique<UiBezierCurveC2>(std::make_shared<BezierCurveC2>(BezierCurveC2::ObjectType::bezierCurveC2, name));
	}
	else if (name == "BezierC2Interpolated")
	{
		uiConnector = std::make_unique<UiBezierC2Interpolated>(std::make_shared<BezierC2Interpolated>(BezierC2Interpolated::ObjectType::bezierC2Interpolated, name));
	}
	else if (name == "TrimmingCurve")
	{
		uiConnector = std::make_unique<UiTrimmingCurve>(std::make_shared<TrimmingCurve>(TrimmingCurve::ObjectType::trimmingCurve, name));
	}

	int id = uiConnector->getObject()->getId();
	DrawableObject::ObjectType type = uiConnector->getObject()->m_type;
	addUiConnector(std::move(uiConnector));
	return QPair<int, DrawableObject::ObjectType>(id, type);
}

void Scene::createObjectMenu(const QPoint &pos, const QList<int> &ids)
{
	if (ids.count() <= 0)
		return;
	if (ids.count() == 1)
	{
		if (getSceneObject(ids.at(0))->m_type == DrawableObject::ObjectType::bezierCurveC0)
		{
			createBC0menu(pos, ids.at(0));
			return;
		}
		if (getSceneObject(ids.at(0))->m_type == DrawableObject::ObjectType::bezierCurveC2)
		{
			createBC2menu(pos, ids.at(0));
			return;
		}
		if (getSceneObject(ids.at(0))->m_type == DrawableObject::ObjectType::bezierC2Interpolated)
		{
			createBC2IntMenu(pos, ids.at(0));
			return;
		}
		if (getSceneObject(ids.at(0))->m_type == DrawableObject::ObjectType::trimmingCurve)
		{
			createTrimmingCurveMenu(pos, ids.at(0));
			return;
		}
	}
	if (ids.count() == 2 || ids.count() == 1)
	{
		createIntersectionMenu(pos, ids);
		return;
	}
	createPoint3Dmenu(pos, ids);
}

void Scene::deleteObject(int id)
{
	m_uiConnectors.erase(id);
}

void Scene::updateControlPoints(std::vector<std::shared_ptr<Point3D>> controlPoints, const std::vector<int> &oldIds)
{
	removeUiConnectors(oldIds);
	for (std::vector<std::shared_ptr<Point3D>>::const_iterator it = controlPoints.begin(); it != controlPoints.end(); ++it)
	{
		std::unique_ptr<UiPoint3D> uiConnector = std::make_unique<UiPoint3D>(*it);
		addUiConnector(std::move(uiConnector));
	}
}

void Scene::removeUiConnectors(const std::vector<int> &ids)
{
	for (std::vector<int>::const_iterator it = ids.begin(); it != ids.end(); ++it)
	{
		if (m_uiConnectors.size() < 1)
			return;
		m_uiConnectors.erase(*it);
	}
}

void Scene::selectCursorObjects(QList<int> &ids)
{
	//if (m_isCursor3d && m_cursor->getMode() == Cursor3D::Mode::Idle)
	if (m_cursor->getMode() == Cursor3D::Mode::Idle)
	{
		m_cursor->clearAllObjects();
		for (int i = 0; i < ids.count(); ++i)
		{
			m_cursor->addActiveObject(getSceneObject(ids.at(i)));
		}
	}
}

void Scene::loadScene(const QString& fileContent)
{
	std::vector<std::shared_ptr<Point3D>> points = fileManager::getPoints(fileContent);
	std::vector<std::shared_ptr<Torus>> tori = fileManager::getTori(fileContent);
	for (const auto &torus : tori)
	{
		auto uiConnector = std::make_unique<UiTorus>(torus);
		int id = uiConnector.get()->getObject()->getId();
		addUiConnector(std::move(uiConnector));

		emit addedTorus(torus->getName(), torus->getId(), static_cast<const UiTorus*>(getUiConntector(id)));
	}

	std::vector<QPair<std::shared_ptr<BezierSurfaceC0>, std::vector<int>>> sC0Ids = fileManager::getSurfacesC0(fileContent);
	for (auto &surfaceId : sC0Ids)
	{
		surfaceId.first->initializeFromPoints(surfaceId.second, points);
		createBezierSurfaceC0(surfaceId.first, true);
	}

	std::vector<QPair<std::shared_ptr<BezierSurfaceC2>, std::vector<int>>> sC2Ids = fileManager::getSurfacesC2(fileContent);
	for (auto &surfaceId : sC2Ids)
	{
		surfaceId.first->initializeFromPoints(surfaceId.second, points);
		createBezierSurfaceC2(surfaceId.first, true);
	}
}

void Scene::saveScene(const QString& path)
{
	fileManager::saveScene(m_uiConnectors, path);
	/*QFile saveFile(path);

	if (!saveFile.open(QIODevice::WriteOnly)) {
		qWarning("Couldn't open save file.");
		return;
	}
	std::shared_ptr<BezierSurfaceC0> surf;
	for (const auto &obj : m_uiConnectors)
	{
		if (obj.second.get()->getObject()->m_type == DrawableObject::ObjectType::bezierSurfaceC0)
			surf = std::static_pointer_cast<BezierSurfaceC0>(obj.second.get()->getObject());
	}
	QJsonArray points;
	QJsonArray jSurfs;
	jSurfs.append(fileManager::saveSurfaceC0(surf, points));
	QJsonObject scene;
	scene["points"] = points;
	scene["surfacesC0"] = jSurfs;
	QJsonDocument saveDoc(scene);
	saveFile.write(saveDoc.toJson());*/
}

void Scene::newtonStepChanged(double val)
{
	Intersections::newtonStep = val;
}

void Scene::selfIntersectionDistChanged(double val)
{
	Intersections::selfIntersectionDist = val;
}

void Scene::newtonWrapDistChanged(double val)
{
	Intersections::wrapDist = val;
}

void Scene::gradientStepChanged(double val)
{
	Intersections::intersectionPointAlpha = val;
}

void Scene::closestPointStepChanged(double val)
{
	Intersections::gradientAlpha = val;
}

void Scene::newtonWrapIterChanged(int val)
{
	Intersections::wrapIter = val;
}

void Scene::translateObjects(const QVector3D& pos)
{
	//QMatrix4x4 PV = m_camera.m_projectionMatrix * m_camera.m_viewMatrix;

//QVector3D position =  PV * pos;
	m_cursor->translateObjects(pos);
}

//void Scene::translateObjects(const QVector3D& pos, const QVector3D& translate)
//{
//	m_cursor->translateObjects(pos, translate);
//
//}

void Scene::findClosestPoint(const QPoint& pos, int width, int height, bool add)
{
	width *= 0.5f;
	height *= 0.5f;
	float minDist = std::numeric_limits<float>::max();
	QMatrix4x4 PV = m_camera.m_projectionMatrix * m_camera.m_viewMatrix;
	int id = -1;
	for (const auto &obj : m_uiConnectors)
	{
		if (obj.second->getObject()->m_type == DrawableObject::ObjectType::point3D)
		{
			QVector3D position = PV * obj.second->getObject()->getPosition();
			if (position.x() < -1 || position.x() > 1 || position.y() < -1 || position.y() > 1 || position.z() > 1 || position.z() < CAM_NEAR)
				continue;
			float posX = (position.x() + 1) * width;
			float posY = (-position.y() + 1) * height;
			float dist = math3d::calculateDistance2D((position.x() + 1) * width, pos.x(), (-position.y() + 1) * height, pos.y());
			if (dist < minDist && dist <= TARGETING_DISTANCE2D)
			{
				id = obj.first;
				minDist = dist;
			}
		}
	}
	if (id != -1)
	{
		m_cursor->markObject(getUiConntector(id)->getObject(), add);
	}
}

void Scene::performCursorAction(bool multiple)
{
	m_cursor->performAction(m_uiConnectors, multiple);
}

void Scene::resetCursor()
{
	m_cursor->clearAllObjects();
}

void Scene::draw() const
{
	emit update();
	if (!m_stereoscopy)
	{
		QMatrix4x4 PV = m_camera.m_projectionMatrix * m_camera.m_viewMatrix;
		std::vector<QVector4D> vertices;
		for (auto const& sceneObject : m_uiConnectors)
		{
			vertices.reserve(sceneObject.second.get()->getObject()->getVertices().size());
			QMatrix4x4 PVM = PV * sceneObject.second.get()->getObject()->getModelMatrix();
			for (auto it = sceneObject.second.get()->getObject()->getVertices().begin(); it != sceneObject.second.get()->getObject()->getVertices().end(); ++it)
			{
				QVector4D vec = PVM * (*it);
				vec /= vec.w();
				vertices.push_back(vec);
			}
			sceneObject.second.get()->getObject()->draw(vertices);
			vertices.clear();
		}
	}
	else
	{
		QMatrix4x4 PVL = m_camera.m_m_projectionMatrixStereoL * m_camera.m_viewMatrix;
		QMatrix4x4 PVR = m_camera.m_m_projectionMatrixStereoR * m_camera.m_viewMatrix;
		for (auto const& sceneObject : m_uiConnectors)
		{
			std::vector<QVector4D> verticesL, verticesR;
			verticesL.reserve(sceneObject.second.get()->getObject()->getVertices().size());
			verticesR.reserve(sceneObject.second.get()->getObject()->getVertices().size());
			QMatrix4x4 PVML = PVL * sceneObject.second.get()->getObject()->getModelMatrix();
			QMatrix4x4 PVMR = PVR * sceneObject.second.get()->getObject()->getModelMatrix();
			for (std::vector<QVector4D>::const_iterator it = sceneObject.second.get()->getObject()->getVertices().begin(); it != sceneObject.second.get()->getObject()->getVertices().end(); ++it)
			{
				QVector4D vecL = PVML * (*it);
				QVector4D vecR = PVMR * (*it);
				vecL /= vecL.w();
				vecR /= vecR.w();
				verticesL.push_back(vecL);
				verticesR.push_back(vecR);
			}
			sceneObject.second.get()->getObject()->draw(verticesL, Colors::STEREO_L_COLOR);
			sceneObject.second.get()->getObject()->draw(verticesR, Colors::STEREO_R_COLOR);
		}
	}
}

void Scene::toggleCursor3D(bool isActive)
{
	/*if (isActive)
	{
		addUiConnector(std::make_unique<UiCursor3D>(m_cursor));
	}
	else
	{
		m_uiConnectors.erase(m_cursor->getId());
	}*/
	m_isCursor3d = isActive;
}

void Scene::updateCursorPosition(float x, float y, int width, int heigth, bool z)
{
	m_cursor->updatePosition(x, y, width, heigth, m_camera, z);
}

int Scene::createDrawableObject(const QString &name)
{
	QPair<int, DrawableObject::ObjectType> idType = createUiConnector(name);
	switch (idType.second)
	{
	case DrawableObject::ObjectType::torus:
	{
		emit addedTorus(name, idType.first, static_cast<const UiTorus*>(getUiConntector(idType.first)));
		break;
	}
	case DrawableObject::ObjectType::point3D:
	{
		emit addedPoint3D(name, idType.first, static_cast<const UiPoint3D*>(getUiConntector(idType.first)));
		break;
	}
	case DrawableObject::ObjectType::bezierCurveC0:
	{
		emit addedBezierCurveC0(name, idType.first, static_cast<const UiBezierCurveC0*>(getUiConntector(idType.first)));
		break;
	}
	case DrawableObject::ObjectType::bezierCurveC2:
	{
		emit addedBezierCurveC2(name, idType.first, static_cast<const UiBezierCurveC2*>(getUiConntector(idType.first)));
		break;
	}
	case DrawableObject::ObjectType::bezierC2Interpolated:
	{
		emit addedBezierC2Interpolated(name, idType.first, static_cast<const UiBezierC2Interpolated*>(getUiConntector(idType.first)));
		break;
	}
	case DrawableObject::ObjectType::trimmingCurve:
	{
		emit addedTrimmingCurve(name, idType.first, static_cast<const UiTrimmingCurve*>(getUiConntector(idType.first)));
		break;
	}
	/*case DrawableObject::ObjectType::bezierSurfaceC0:
	{
		emit addedBezierSurfaceC0(name, idType.first, static_cast<const UiBezierSurfaceC0*>(getUiConntector(idType.first)));
		break;
	}
	case DrawableObject::ObjectType::bezierSurfaceC2:
	{
		emit addedBezierSurfaceC2(name, idType.first, static_cast<const UiBezierSurfaceC2*>(getUiConntector(idType.first)));
		break;
	}*/
	case DrawableObject::ObjectType::cursor3D:
	{
		break;
	}
	}
	return idType.first;
}

UiConnector* Scene::getUiConntector(int id) const
{
	try
	{
		UiConnector *connector = m_uiConnectors.at(id).get();
	}
	catch (std::out_of_range &e)
	{
		return nullptr;
	}
	return m_uiConnectors.find(id)->second.get();
}

void Scene::createBezierSurfaceC2(const BezierSurfaceData &data)
{
	createBezierSurfaceC2(std::make_shared<BezierSurfaceC2>(BezierSurfaceC2::ObjectType::bezierSurfaceC2, "BezierSurfaceC2", data));
}

void Scene::createBezierSurfaceC2(const std::shared_ptr<BezierSurfaceC2>& surface, bool loaded)
{
	std::unique_ptr<UiBezierSurfaceC2> uiConnector =
		std::make_unique<UiBezierSurfaceC2>(surface, loaded);
	for (const auto &point : uiConnector->getBezierSurface()->getPoints())
	{
		point->setAncestor(uiConnector->getObject());
		std::unique_ptr<UiPoint3D> uiPoint3D = std::make_unique<UiPoint3D>(point);
		emit createdBSControlPoint("", -1, uiPoint3D.get());
		addUiConnector(std::move(uiPoint3D));
	}
	int id = uiConnector->getObject()->getId();
	addUiConnector(std::move(uiConnector));
	//emit addedBezierSurfaceC2("BezierSurfaceC2", id, static_cast<UiBezierSurfaceC2*>(getUiConntector(id)));
	emit addedBezierSurfaceC2(getUiConntector(id)->getObject()->getName(), id, static_cast<UiBezierSurfaceC2*>(getUiConntector(id)));
}

void Scene::generateHeightMap() const
{
	/*int size = 1500;
	float precision = 500.0f;
	float millRadius = 0.85f;
	HeightmapGenerator hmGenerator(size, precision);
	hmGenerator.initSphereData(millRadius);
	for (const auto &obj : m_uiConnectors)
	{
		if (obj.second->getObject()->m_type == DrawableObject::ObjectType::bezierSurfaceC2)
		{
			hmGenerator.updateMap(std::static_pointer_cast<BezierSurface>(obj.second->getObject()), millRadius);
			hmGenerator.updateMapSpheres(std::static_pointer_cast<BezierSurface>(obj.second->getObject()));
		}
	}
	

	float *map = hmGenerator.getMap();
	fileManager::saveHeightmap(map, size, size, "hem.json");*/

	QFile file("hem.json");

	if (!file.open(QIODevice::ReadOnly))
	{
		qDebug("Unable to open file");
		return;
	}
	QString fileContent = file.readAll();

	PathsGenerator pg;
	pg.generateCrudePaths(fileContent);



	/*QImage img (size, size, QImage::Format::Format_RGB32);
	for (int i = 0; i < img.width(); ++i)
	{
		for (int j = 0; j < img.height(); ++j)
		{
			img.setPixel(i, j, map[i * img.width() + j]);
		}
	}
	bool save = img.save("test.jpg", "jpg");*/
}

void Scene::showAxes(char axis) const
{
	switch (axis)
	{
	case 'X':
	{
		m_axes->m_x = !m_axes->m_x;
		break;
	}
	case 'Y':
	{
		m_axes->m_y = !m_axes->m_y;
		break;
	}
	case 'Z':
	{
		m_axes->m_z = !m_axes->m_z;
		break;
	}
	}
}

void Scene::initialize()
{
	m_axes = std::make_shared<Axes>(DrawableObject::ObjectType::axes);
	addUiConnector(std::make_unique<UiAxes>(m_axes));
	m_cursor = std::make_shared<Cursor3D>(DrawableObject::ObjectType::cursor3D);
	addUiConnector(std::make_unique<UiCursor3D>(m_cursor));
}

void Scene::createBezierSurfaceC0(const BezierSurfaceData &data)
{
	createBezierSurfaceC0(std::make_shared<BezierSurfaceC0>(BezierSurfaceC0::ObjectType::bezierSurfaceC0, "BezierSurfaceC0", data));
}

void Scene::createBezierSurfaceC0(const std::shared_ptr<BezierSurfaceC0> &surface, bool loaded)
{
	std::unique_ptr<UiBezierSurfaceC0> uiConnector =
		std::make_unique<UiBezierSurfaceC0>(surface, loaded);
	for (const auto &point : uiConnector->getBezierSurface()->getPoints())
	{
		point->setAncestor(uiConnector->getObject());
		std::unique_ptr<UiPoint3D> uiPoint3D = std::make_unique<UiPoint3D>(point);
		emit createdBSControlPoint("", -1, uiPoint3D.get());
		addUiConnector(std::move(uiPoint3D));
	}
	int id = uiConnector->getObject()->getId();
	addUiConnector(std::move(uiConnector));
	//emit addedBezierSurfaceC0("BezierSurfaceC0", id, static_cast<UiBezierSurfaceC0*>(getUiConntector(id)));
	emit addedBezierSurfaceC0(getUiConntector(id)->getObject()->getName(), id, static_cast<UiBezierSurfaceC0*>(getUiConntector(id)));
}
