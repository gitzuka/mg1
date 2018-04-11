#include "scene.h"
#include "point3d.h"
#include "bezierCurveC0.h"
#include "uiTorus.h"
#include "uiPoint3d.h"
#include "uiCursor3d.h"

Scene::Scene() : m_cursorPosX(0.0f), m_cursorPosY(0.0f), m_cursorPosZ(0.0f),
m_stereoscopy(false), m_isCursor3d(false), m_colorL(1.0f, 0, 0), m_colorR(0, 0, 1.0f)
{
}

//int Scene::countObjects() const
//{
//	return m_objects.count();
//}

void Scene::addObject(const std::shared_ptr<DrawableObject> &object)
{
	//m_objects.push_back(object);
}

void Scene::addUiConnector(std::unique_ptr<UiConnector> uiConnector)
{
	//m_uiConnectors.push_back(std::move(uiConnector));
	m_uiConnectors.emplace(std::make_pair(uiConnector->getObject()->getId(), std::move(uiConnector)));
}

void Scene::createCurveC0fromPoints(const QList<int> &ids)
{
	std::shared_ptr<BezierCurveC0> bezierCruveC0 = std::make_shared<BezierCurveC0>(BezierCurveC0::ObjectType::bezierCurveC0, "BezierCurveC0");
	//emit addedBezierCurveC0("BezierCurveC0", bezierCruveC0->getId(), bezierCruveC0);
	addObject(bezierCruveC0);
	for (int i = 0; i < ids.count(); ++i)
	{
		//bezierCruveC0->addControlPoint(getObjectByID(ids.at(i)));
		bezierCruveC0->addControlPoint(m_uiConnectors.find(ids.at(i))->second.get()->getObject());
	}
	std::unique_ptr<UiBezierCurveC0> uiConnector = std::make_unique<UiBezierCurveC0>(bezierCruveC0);
	emit addedBezierCurveC0(bezierCruveC0->getName(), bezierCruveC0->getId(), static_cast<UiBezierCurveC0*>(uiConnector.get()));
	addUiConnector(std::move(uiConnector));
}

void Scene::createBC0menu(const QPoint& pos, int id)
{
	QMenu myMenu;
	QAction *edit = myMenu.addAction("Edit mode");
	connect(edit, &QAction::triggered, this, [this, &id]()
	{
		setActiveObject(id);
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
	myMenu.exec(pos);
}

void Scene::setActiveObject(int id)
{
	m_activeObject = m_uiConnectors.find(id)->second.get()->getObject();
}

void Scene::createObjectMenu(const QPoint &pos, const QList<int> &ids)
{
	if (ids.count() <= 0)
		return;
	if (ids.count() == 1)
	{
		if (m_uiConnectors.find(ids.at(0))->second.get()->getObject()->m_type == DrawableObject::ObjectType::bezierCurveC0)
			createBC0menu(pos, ids.at(0));
		return;
	}
	createPoint3Dmenu(pos, ids);
	/*for (int i = 0; i < idsCount; ++i)
	{
		if (getObjectByID(ids.at(i)) == nullptr || getObjectByID(ids.at(i))->m_type != DrawableObject::ObjectType::point3D)
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
	myMenu.exec(pos);*/
}

//void Scene::deleteObject(const std::shared_ptr<DrawableObject> &object)
//{
//	for (int i = 0; i < m_objects.count(); ++i)
//	{
//		if (m_objects.at(i)->getId() == object->getId())
//		{
//			if (m_activeObject != nullptr && object->getId() == m_activeObject->getId())
//			{
//				m_activeObject = nullptr;
//			}
//			m_uiConnectors.erase(object->getId());
//			m_objects.removeAt(i);
//			return;
//		}
//	}
//}

void Scene::deleteObject(int id)
{
	m_uiConnectors.erase(id);
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
		/*for (int i = 0; i < m_objects.count(); ++i)
		{
			std::vector<QVector4D> vertices;
			vertices.reserve(getObject(i)->getVertices().size());
			for (std::vector<QVector4D>::const_iterator it = getObject(i)->getVertices().begin(); it != getObject(i)->getVertices().end(); ++it)
			{
				QVector4D vec = PV * getObject(i)->getModelMatrix() * (*it);
				vec /= vec.w();
				vertices.push_back(vec);
			}
			getObject(i)->draw(vertices);
		}*/
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
			sceneObject.second.get()->getObject()->draw(verticesL, m_colorL);
			sceneObject.second.get()->getObject()->draw(verticesR, m_colorR);
		}
		/*QMatrix4x4 PVL = m_camera.m_m_projectionMatrixStereoL * m_camera.m_viewMatrix;
		QMatrix4x4 PVR = m_camera.m_m_projectionMatrixStereoR * m_camera.m_viewMatrix;
		for (int i = 0; i < m_objects.count(); ++i)
		{
			std::vector<QVector4D> verticesL, verticesR;
			verticesL.reserve(getObject(i)->getVertices().size());
			verticesR.reserve(getObject(i)->getVertices().size());
			for (std::vector<QVector4D>::const_iterator it = getObject(i)->getVertices().begin(); it != getObject(i)->getVertices().end(); ++it)
			{
				QVector4D vecL = PVL * getObject(i)->getModelMatrix() * (*it);
				QVector4D vecR = PVR * getObject(i)->getModelMatrix() * (*it);
				vecL /= vecL.w();
				vecR /= vecR.w();
				verticesL.push_back(vecL);
				verticesR.push_back(vecR);
			}
			getObject(i)->draw(verticesL, m_colorL);
			getObject(i)->draw(verticesR, m_colorR);
		}*/
	}
}
//TODO: uncomment
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

void Scene::updateCursorPosition(float x, float y, int width, int heigth)
{
	m_cursorPosX = x / (width * 0.5f) - 1.0f;
	m_cursorPosY = -y / (heigth * 0.5f) + 1.0f;
	//m_cursor->updatePosition(m_cursorPosX, m_cursorPosY, m_cursorPosZ, m_camera);
	m_cursor->m_worldCoords = QVector3D(m_cursorPosX - m_camera.m_viewMatrix.row(0).w(),
		m_cursorPosY - m_camera.m_viewMatrix.row(1).w(),
		m_cursorPosZ - m_camera.m_viewMatrix.row(2).w() - 1);
	m_cursor->setModelMatrix((Camera::createRotationX(m_camera.m_pitch) * Camera::createRotationY(m_camera.m_yaw)).inverted()
		* Camera::createTranslation(m_cursor->m_worldCoords));	

	if (m_cursor->m_obtainedObject != nullptr)
	{
		m_cursor->m_obtainedObject->setModelMatrix(m_cursor->getModelMatrix());
	}
}



//std::shared_ptr<DrawableObject> Scene::getObject(int index) const
//{
//	if (m_objects.count() <= 0)
//	{
//		return nullptr;
//	}
//	return m_objects.at(index);
//}

//std::shared_ptr<DrawableObject> Scene::getObjectByID(int id) const
//{
//	for (int i = 0; i < m_objects.count(); ++i)
//	{
//		if (m_objects.at(i)->getId() == id)
//		{
//			return m_objects.at(i);
//		}
//	}
//	return nullptr;
//}

int Scene::createDrawableObject(const QString &name)
{
	std::shared_ptr<DrawableObject> object;
	std::unique_ptr<UiConnector> uiConnector;
	if (name == "Torus")
	{
		object = std::make_shared<Torus>(DrawableObject::ObjectType::torus, name);
		uiConnector = std::make_unique<UiTorus>(std::static_pointer_cast<Torus>(object));
		emit addedTorus(name, object->getId(), static_cast<UiTorus*>(uiConnector.get()));
	}
	else if (name == "Point3D")
	{
		object = std::make_shared<Point3D>(Point3D::ObjectType::point3D, name, m_camera.m_projectionMatrix, m_camera.m_viewMatrix);
		uiConnector = std::make_unique<UiPoint3D>(std::static_pointer_cast<Point3D>(object));
		emit addedPoint3D(name, object->getId(), static_cast<UiPoint3D*>(uiConnector.get()));
	}
	else if (name == "BezierCurveC0")
	{
		object = std::make_shared<BezierCurveC0>(BezierCurveC0::ObjectType::bezierCurveC0, name);
		uiConnector = std::make_unique<UiBezierCurveC0>(std::static_pointer_cast<BezierCurveC0>(object));
		emit addedBezierCurveC0(name, object->getId(), static_cast<UiBezierCurveC0*>(uiConnector.get()));
	}
	addObject(object);
	addUiConnector(std::move(uiConnector));
	return object->getId();
}

int Scene::updateCursor()
{
	if (m_activeObject != nullptr)
	{
		int id = m_cursor->getClosestObject(m_uiConnectors);
		//int id = m_cursor->getClosestObject(m_objects);
		//m_cursor->m_obtainedObject = m_uiConnectors.find(id)->second.get()->getObject();
		if (m_activeObject->m_type == DrawableObject::ObjectType::bezierCurveC0)
		{
			std::static_pointer_cast<BezierCurveC0>(m_activeObject)->addControlPoint(m_uiConnectors.find(id)->second.get()->getObject());
		}
		return -1;
	}
	return m_cursor->acquireObject(m_uiConnectors);
}
