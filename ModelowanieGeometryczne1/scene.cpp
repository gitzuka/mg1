#include "scene.h"
#include "point3d.h"
#include "bezierCurveC0.h"

Scene::Scene() : m_cursorPosX(0.0f), m_cursorPosY(0.0f), m_cursorPosZ(0.0f),
m_stereoscopy(false), m_isCursor3d(false), m_colorL(1.0f, 0, 0), m_colorR(0, 0, 1.0f)
{
	/*m_objects.push_back(std::make_shared<Point3D>(Point3D::ObjectType::point3D, m_camera.m_projectionMatrix));
	m_objects.push_back(std::make_shared<Point3D>(Point3D::ObjectType::point3D, m_camera.m_projectionMatrix));
	m_objects.push_back(std::make_shared<Point3D>(Point3D::ObjectType::point3D, m_camera.m_projectionMatrix));
	m_objects.push_back(std::make_shared<Point3D>(Point3D::ObjectType::point3D, m_camera.m_projectionMatrix));
	m_objects.push_back(std::make_shared<BezierCurveC0>(BezierCurveC0::ObjectType::bezierCurveC0));

	m_objects.at(0)->createVertices();
	m_objects.at(0)->generateIndices();
	m_objects.at(1)->createVertices();
	m_objects.at(1)->generateIndices();
	m_objects.at(2)->createVertices();
	m_objects.at(2)->generateIndices();
	m_objects.at(3)->createVertices();
	m_objects.at(3)->generateIndices();


	std::static_pointer_cast<Point3D>(m_objects.at(0))->m_modelMatrix(0, 3) = -0.4;
	std::static_pointer_cast<Point3D>(m_objects.at(0))->m_modelMatrix(1, 3) = 0;
	std::static_pointer_cast<Point3D>(m_objects.at(0))->m_modelMatrix(2, 3) = -0.5;
	std::static_pointer_cast<Point3D>(m_objects.at(0))->m_modelMatrix(3, 3) = 1;

	std::static_pointer_cast<Point3D>(m_objects.at(1))->m_modelMatrix(0, 3) = -0.2;
	std::static_pointer_cast<Point3D>(m_objects.at(1))->m_modelMatrix(1, 3) = 0.2;
	std::static_pointer_cast<Point3D>(m_objects.at(1))->m_modelMatrix(2, 3) = 0;
	std::static_pointer_cast<Point3D>(m_objects.at(1))->m_modelMatrix(3, 3) = 1;

	std::static_pointer_cast<Point3D>(m_objects.at(2))->m_modelMatrix(0, 3) = 0.2;
	std::static_pointer_cast<Point3D>(m_objects.at(2))->m_modelMatrix(1, 3) = 0.4;
	std::static_pointer_cast<Point3D>(m_objects.at(2))->m_modelMatrix(2, 3) = 0;
	std::static_pointer_cast<Point3D>(m_objects.at(2))->m_modelMatrix(3, 3) = 1;

	std::static_pointer_cast<Point3D>(m_objects.at(3))->m_modelMatrix(0, 3) = 0.4;
	std::static_pointer_cast<Point3D>(m_objects.at(3))->m_modelMatrix(1, 3) = 0;
	std::static_pointer_cast<Point3D>(m_objects.at(3))->m_modelMatrix(2, 3) =- 0.5;
	std::static_pointer_cast<Point3D>(m_objects.at(3))->m_modelMatrix(3, 3) = 1;

	std::static_pointer_cast<Point3D>(m_objects.at(0))->setCenter(QVector3D(-0.4, 0, 0));
	std::static_pointer_cast<Point3D>(m_objects.at(1))->setCenter(QVector3D(-0.2, 0.2, 0));
	std::static_pointer_cast<Point3D>(m_objects.at(2))->setCenter(QVector3D(0.2, 0.4, 0));
	std::static_pointer_cast<Point3D>(m_objects.at(3))->setCenter(QVector3D(0.4, 0, 0));
	std::static_pointer_cast<BezierCurveC0>(m_objects.at(4))->addControlPoint(m_objects.at(0));
	std::static_pointer_cast<BezierCurveC0>(m_objects.at(4))->addControlPoint(m_objects.at(1));
	std::static_pointer_cast<BezierCurveC0>(m_objects.at(4))->addControlPoint(m_objects.at(2));
	std::static_pointer_cast<BezierCurveC0>(m_objects.at(4))->addControlPoint(m_objects.at(3));

	m_objects.at(4)->createVertices();
	m_objects.at(4)->generateIndices();*/
}

int Scene::countObjects() const
{
	return m_objects.count();
}

void Scene::addObject(const std::shared_ptr<DrawableObject> &object)
{
	m_objects.push_back(object);
}

void Scene::createCurveC0fromPoints(const QList<int> &ids)
{
	std::shared_ptr<BezierCurveC0> bezierCruveC0 = std::make_shared<BezierCurveC0>(BezierCurveC0::ObjectType::bezierCurveC0, "BezierCurveC0");
	emit addedBezierCurveC0("BezierCurveC0", bezierCruveC0->getId(), bezierCruveC0);
	addObject(bezierCruveC0);
	for (int i = 0; i < ids.count(); ++i)
	{
		bezierCruveC0->addControlPoint(getObjectByID(ids.at(i)));
	}
}

void Scene::createObjectMenu(const QPoint &pos, const QList<int> &ids)
{
	for (int i = 0; i < ids.count(); ++i)
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
	myMenu.exec(pos);
	//std::shared_ptr<BezierCurveC0> object = std::make_shared<BezierCurveC0>(BezierCurveC0::ObjectType::bezierCurveC0);
	//for (int i = 0; i < ids.count(); ++i)
	//{
	//	object->addControlPoint(m_scene.getObjectByID(ids.at(i)));
	//}
	////emit bezierCurveC0Added(object->getId());
	////object->createVertices();
	////object->generateIndices();
	//m_scene.addObject(object);
}

void Scene::deleteObject(const std::shared_ptr<DrawableObject> &object)
{
	for (int i = 0; i < m_objects.count(); ++i)
	{
		if (m_objects.at(i)->getId() == object->getId())
		{
			if (m_activeObject != nullptr && object->getId() == m_activeObject->getId())
			{
				m_activeObject = nullptr;
			}
			m_objects.removeAt(i);
			return;
		}
	}
}

void Scene::deleteObject(int index)
{
	for (int i = 0; i < m_objects.count(); ++i)
	{
		if (m_objects.at(i)->getId() == index)
		{
			if (m_objects.at(i) == m_cursor->m_obtainedObject)
			{
				m_cursor->m_obtainedObject = nullptr;
			}
			if (m_activeObject != nullptr && m_objects.at(i) == m_activeObject)
			{
				m_activeObject = nullptr;
			}
			m_objects.removeAt(i);
			return;
		}
	}
}

void Scene::draw() const
{
	emit update();
	if (!m_stereoscopy)
	{
		QMatrix4x4 PV = m_camera.m_projectionMatrix * m_camera.m_viewMatrix;
		for (int i = 0; i < countObjects(); ++i)
		{
			std::vector<QVector4D> vertices;
			for (std::vector<QVector4D>::const_iterator it = getObject(i)->getVertices().begin(); it != getObject(i)->getVertices().end(); ++it)
			{
				QVector4D vec = PV * getObject(i)->getModelMatrix() * (*it);
				vec /= vec.w();
				vertices.push_back(vec);
			}
			getObject(i)->draw(vertices);
		}
	}
	else
	{
		QMatrix4x4 PVL = m_camera.m_m_projectionMatrixStereoL * m_camera.m_viewMatrix;
		QMatrix4x4 PVR = m_camera.m_m_projectionMatrixStereoR * m_camera.m_viewMatrix;

		for (int i = 0; i < countObjects(); ++i)
		{
			std::vector<QVector4D> verticesL, verticesR;
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
		}
	}
}

void Scene::toggleCursor3D(bool isActive)
{
	if (isActive)
	{
		addObject(m_cursor);
	}
	else
	{
		deleteObject(m_cursor);
	}
	m_isCursor3d = isActive;
}

void Scene::updateCursorPosition(float x, float y, int width, int heigth)
{
	m_cursorPosX = x / (width * 0.5f) - 1.0f;
	m_cursorPosY = -y / (heigth * 0.5f) + 1.0f;

	m_cursor->m_worldCoords = QVector3D(m_cursorPosX - m_camera.m_viewMatrix.row(0).w(),
		m_cursorPosY - m_camera.m_viewMatrix.row(1).w(),
		m_cursorPosZ - m_camera.m_viewMatrix.row(2).w() - 1);
	/*m_cursor->m_modelMatrix = (Camera::createRotationX(m_camera.m_pitch) * Camera::createRotationY(m_camera.m_yaw)).inverted()
		* Camera::createTranslation(m_cursor->m_worldCoords);	*/
	m_cursor->setModelMatrix((Camera::createRotationX(m_camera.m_pitch) * Camera::createRotationY(m_camera.m_yaw)).inverted()
		* Camera::createTranslation(m_cursor->m_worldCoords));
	//* Camera::createRotationX(180);
//m_cursorPosX = 0.5f;
//m_cursorPosY = 0;
//m_cursor->m_modelMatrix = PVinv * Camera::createTranslation(m_cursorPosX + m_camera.m_viewMatrix.row(0).w(), m_cursorPosY, 0);
//m_cursor->m_modelMatrix = PVinv * Camera::createTranslation(m_cursorPosX, m_cursorPosY, 0);
//m_cursor->m_modelMatrix(0, 3) = (m_cursorPosX - m_camera.m_viewMatrix.row(0).w());
//m_cursor->m_modelMatrix(1, 3) = m_cursorPosY - m_camera.m_viewMatrix.row(1).w();// +yTrans;
	if (m_cursor->m_obtainedObject != nullptr)
	{
		m_cursor->m_obtainedObject->setModelMatrix(m_cursor->getModelMatrix());
	}
}



std::shared_ptr<DrawableObject> Scene::getObject(int index) const
{
	if (m_objects.count() <= 0)
	{
		return nullptr;
	}
	return m_objects.at(index);
}

std::shared_ptr<DrawableObject> Scene::getObjectByID(int id) const
{
	for (int i = 0; i < m_objects.count(); ++i)
	{
		if (m_objects.at(i)->getId() == id)
		{
			return m_objects.at(i);
		}
	}
	return nullptr;
}

int Scene::createDrawableObject(QString name)
{
	std::shared_ptr<DrawableObject> object;
	if (name == "Torus")
	{
		object = std::make_shared<Torus>(DrawableObject::ObjectType::torus, name);
		emit addedTorus(name, object->getId(), std::static_pointer_cast<Torus>(object));
	}
	else if (name == "Point3D")
	{
		object = std::make_shared<Point3D>(Point3D::ObjectType::point3D, name, m_camera.m_projectionMatrix);
		emit addedPoint3D(name, object->getId(), object);
	}
	else if (name == "BezierCurveC0")
	{
		object = std::make_shared<BezierCurveC0>(BezierCurveC0::ObjectType::bezierCurveC0, name);
		emit addedBezierCurveC0(name, object->getId(), std::static_pointer_cast<BezierCurveC0>(object));
	}
	addObject(object);
	return object->getId();
}


void Scene::removedObject()
{
}

int Scene::updateCursor()
{
	return m_cursor->acquireObject(m_objects);
}

const UiScene* Scene::getUiComponent() const
{
	return &m_uiScene;
}