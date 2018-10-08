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
#include "Intersections.h"
#include "uiTrimmingCurve.h"
#include "trimmingCurve.h"

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

void Scene::checkIntersections(const QList<int>& ids)
{
	std::shared_ptr<IntersectableObject> surface1 = std::dynamic_pointer_cast<IntersectableObject>(getUiConntector(ids.at(0))->getObject());
	std::shared_ptr<IntersectableObject> surface2 = std::dynamic_pointer_cast<IntersectableObject>(getUiConntector(ids.at(1))->getObject());
	QVector3D testpoint = QVector3D(0.0, 0.f, 0.f);
	testpoint = m_cursor->getPosition();
	int id = createDrawableObject("Point3D");
	getUiConntector(id)->getObject()->setPosition(testpoint);
	getUiConntector(id)->getObject()->setColor(float3(0, 255, 0));
	QVector4D uvuv = Intersections::findIntersectionPoint(surface1, surface2, testpoint);
	QVector3D point1 = surface1->getPointByUV(uvuv.x(), uvuv.y());
	id = createDrawableObject("Point3D");
	getUiConntector(id)->getObject()->setPosition(point1);
	getUiConntector(id)->getObject()->setColor(float3(255, 0, 0));
	QVector3D point2 = surface2->getPointByUV(uvuv.z(), uvuv.w());
	id = createDrawableObject("Point3D");
	getUiConntector(id)->getObject()->setPosition(point2);
	getUiConntector(id)->getObject()->setColor(float3(0, 0, 255));

	std::vector<QVector4D> params = Intersections::getTrimmingCurve(surface1, surface2, testpoint);
	std::vector<QVector4D> vertices;
	vertices.reserve(params.size());
	for (int i = 0; i < params.size(); ++i)
	{
		vertices.push_back(QVector4D(surface1->getPointByUV(params.at(i).x(), params.at(i).y()), 1.0f));
	}
	id = createDrawableObject("TrimmingCurve");
	std::shared_ptr<TrimmingCurve> curve = std::dynamic_pointer_cast<TrimmingCurve>(getUiConntector(id)->getObject());
	curve->setVertices(vertices);

	std::vector<QVector4D> vertices2;
	vertices2.reserve(params.size());
	for (int i = 0; i < params.size(); ++i)
	{
		vertices2.push_back(QVector4D(surface2->getPointByUV(params.at(i).z(), params.at(i).w()), 1.0f));
	}
	id = createDrawableObject("TrimmingCurve");
	std::shared_ptr<TrimmingCurve> curve2 = std::dynamic_pointer_cast<TrimmingCurve>(getUiConntector(id)->getObject());
	curve2->setColor(128, 128, 0);
	curve2->setVertices(vertices2);

	/*std::vector<QVector4D> vertices3;
	vertices3.reserve(params.size());
	for (int i = 0; i < params.size(); ++i)
	{
		vertices3.push_back(QVector4D(surface1->getPointByUV(params.at(i).z(), params.at(i).w()), 1.0f));
	}
	id = createDrawableObject("TrimmingCurve");
	std::shared_ptr<TrimmingCurve> curve3 = std::dynamic_pointer_cast<TrimmingCurve>(getUiConntector(id)->getObject());
	curve3->setColor(0, 128, 0); 
	curve3->setVertices(vertices3);

	std::vector<QVector4D> vertices4;
	vertices4.reserve(params.size());
	for (int i = 0; i < params.size(); ++i)
	{
		vertices4.push_back(QVector4D(surface2->getPointByUV(params.at(i).x(), params.at(i).y()), 1.0f));
	}
	id = createDrawableObject("TrimmingCurve");
	std::shared_ptr<TrimmingCurve> curve4 = std::dynamic_pointer_cast<TrimmingCurve>(getUiConntector(id)->getObject());
	curve4->setColor(128, 0, 0);
	curve4->setVertices(vertices4);*/
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
	catch (std::out_of_range e)
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
	}
	if (ids.count() == 2)
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
	if (m_isCursor3d && m_cursor->getMode() == Cursor3D::Mode::Idle)
	{
		m_cursor->clearAllObjects();
		for (int i = 0; i < ids.count(); ++i)
		{
			m_cursor->addActiveObject(getSceneObject(ids.at(i)));
		}
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
			for (std::vector<QVector4D>::const_iterator it = sceneObject.second.get()->getObject()->getVertices().begin(); it != sceneObject.second.get()->getObject()->getVertices().end(); ++it)
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
	if (isActive)
	{
		addUiConnector(std::make_unique<UiCursor3D>(m_cursor));
	}
	else
	{
		m_uiConnectors.erase(m_cursor->getId());
	}
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
	catch (std::out_of_range e)
	{
		return nullptr;
	}
	return m_uiConnectors.find(id)->second.get();
}

void Scene::createBezierSurfaceC2(const BezierSurfaceData &data)
{
	std::unique_ptr<UiBezierSurfaceC2> uiConnector =
		std::make_unique<UiBezierSurfaceC2>(std::make_shared<BezierSurfaceC2>(BezierSurfaceC2::ObjectType::bezierSurfaceC2, "BezierSurfaceC2", data));
	for (const auto &point : uiConnector->getBezierSurface()->getPoints())
	{
		std::unique_ptr<UiPoint3D> uiPoint3D = std::make_unique<UiPoint3D>(point);
		emit createdBSControlPoint("", -1, uiPoint3D.get());
		addUiConnector(std::move(uiPoint3D));
	}
	int id = uiConnector->getObject()->getId();
	addUiConnector(std::move(uiConnector));
	emit addedBezierSurfaceC2("BezierSurfaceC2", id, static_cast<UiBezierSurfaceC2*>(getUiConntector(id)));
}

void Scene::createBezierSurfaceC0(const BezierSurfaceData &data)
{
	std::unique_ptr<UiBezierSurfaceC0> uiConnector =
		std::make_unique<UiBezierSurfaceC0>(std::make_shared<BezierSurfaceC0>(BezierSurfaceC0::ObjectType::bezierSurfaceC0, "BezierSurfaceC0", data));
	for (const auto &point : uiConnector->getBezierSurface()->getPoints())
	{
		std::unique_ptr<UiPoint3D> uiPoint3D = std::make_unique<UiPoint3D>(point);
		emit createdBSControlPoint("", -1, uiPoint3D.get());
		addUiConnector(std::move(uiPoint3D));
	}
	int id = uiConnector->getObject()->getId();
	addUiConnector(std::move(uiConnector));
	emit addedBezierSurfaceC0("BezierSurfaceC0", id, static_cast<UiBezierSurfaceC0*>(getUiConntector(id)));
}
