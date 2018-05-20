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
		points.push_back(m_uiConnectors.find(ids.at(i))->second.get()->getObject());
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
		points.push_back(m_uiConnectors.find(ids.at(i))->second.get()->getObject());
	}
	static_cast<UiBezierCurveC2*>(getUiConntector(bezierCurveC2->getId()))->assignPoints(points, bezierCurveC2->getId());
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

void Scene::createPoint3Dmenu(const QPoint& pos, const QList<int>& ids)
{
	for (int i = 0; i < ids.count(); ++i)
	{
		if (m_uiConnectors.find(ids.at(i))->second.get()->getObject() == nullptr
			|| m_uiConnectors.find(ids.at(i))->second.get()->getObject()->m_type != DrawableObject::ObjectType::point3D)
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
	myMenu.exec(pos);
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
	/*m_activeObject = m_uiConnectors.find(id)->second.get()->getObject();
	m_activeObject->setColor(Colors::ACTIVE_OBJECT_COLOR);*/
}

void Scene::removeActiveObject(int id)
{
	/*if (m_activeObject != nullptr)
	{
		m_activeObject->setColor(Colors::DEFAULT_OBJECT_COLOR);
		m_activeObject = nullptr;
	}*/
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
		if (m_uiConnectors.find(ids.at(0))->second.get()->getObject()->m_type == DrawableObject::ObjectType::bezierCurveC0)
			createBC0menu(pos, ids.at(0));
		if (m_uiConnectors.find(ids.at(0))->second.get()->getObject()->m_type == DrawableObject::ObjectType::bezierCurveC2)
			createBC2menu(pos, ids.at(0));
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

void Scene::performCursorAction()
{
	m_cursor->performAction(m_uiConnectors);
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
		for (auto const& sceneObject : m_uiConnectors)
		{
			std::vector<QVector4D> vertices;
			vertices.reserve(sceneObject.second.get()->getObject()->getVertices().size());
			QMatrix4x4 PVM = PV * sceneObject.second.get()->getObject()->getModelMatrix();
			for (std::vector<QVector4D>::const_iterator it = sceneObject.second.get()->getObject()->getVertices().begin(); it != sceneObject.second.get()->getObject()->getVertices().end(); ++it)
			{
				QVector4D vec = PVM * (*it);
				vec /= vec.w();
				vertices.push_back(vec);
			}
			sceneObject.second.get()->getObject()->draw(vertices);
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
		//addUiConnector(std::move(m_uiCursor));
	}
	else
	{
		m_uiConnectors.erase(m_cursor->getId());
		//m_uiCursor =  std::move(m_uiConnectors.find(m_cursor->getId())->second.get());
	}
	m_isCursor3d = isActive;
}

void Scene::updateCursorPosition(float x, float y, int width, int heigth)
{
	/*m_cursorPosX = x / (width * 0.5f) - 1.0f;
	m_cursorPosY = -y / (heigth * 0.5f) + 1.0f;
	m_cursor->updatePosition(m_cursorPosX, m_cursorPosY, m_cursorPosZ, m_camera);*/
	m_cursor->updatePosition(x, y, width, heigth, m_camera);
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

//std::shared_ptr<Cursor3D>& Scene::getCursor()
//{
//	return m_uiCursor->getCursor();
//}

//int Scene::updateCursor()
//{
//	if (m_activeObject != nullptr)
//	{
//		int id = m_cursor->getClosestObject(m_uiConnectors);
//		//m_cursor->m_obtainedObject = m_uiConnectors.find(id)->second.get()->getObject();
//		if (m_activeObject->m_type == DrawableObject::ObjectType::bezierCurveC0)
//		{
//			static_cast<UiBezierCurveC0*>(m_uiConnectors.find(m_activeObject->getId())->second.get())->addPoint(m_uiConnectors.find(id)->second.get()->getObject(), m_activeObject->getId());
//		}
//		else if (m_activeObject->m_type == DrawableObject::ObjectType::bezierCurveC2)
//		{
//			static_cast<UiBezierCurveC2*>(m_uiConnectors.find(m_activeObject->getId())->second.get())->addPoint(m_uiConnectors.find(id)->second.get()->getObject(), m_activeObject->getId());
//		}
//		return -1;
//	}
//	return m_cursor->acquireObject(m_uiConnectors);
//}
