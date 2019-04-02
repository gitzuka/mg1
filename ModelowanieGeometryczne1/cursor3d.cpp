#include "cursor3d.h"
#include "camera.h"
#include "uiConnector.h"
#include "colors.h"
#include "3dmath.h"
#include "point3d.h"
#include "uiBezierCurveC0.h"
#include "uiBezierCurveC2.h"
#include "uiBezierC2Interpolated.h"

Cursor3D::Cursor3D(ObjectType type) : DrawableObject(type, "Cursor3D"),
m_worldCoords(QVector3D(0, 0, 0)), m_posX(0), m_posY(0), m_posZ(0), m_mode(Mode::Translate)
{
	Cursor3D::createVertices();
	Cursor3D::generateIndices();
}

void Cursor3D::draw(std::vector<QVector4D>& vec) const
{
	for (std::vector<int>::const_iterator it = m_indices.begin(); it != m_indices.end(); ++it)
	{
		if (*it == -1 || *(it + 1) == -1
			|| vec.at(*it).z() <= CAM_NEAR || vec.at(*(it + 1)).z() <= CAM_NEAR
			|| vec.at(*it).z() > 1 || vec.at(*(it + 1)).z() > 1)
		{
			continue;
		}
		drawLine(vec.at(*it), vec.at(*(it + 1)), float3(1.0f, 0, 0));
	}
}

void Cursor3D::draw(std::vector<QVector4D>& vec, float3 color) const
{
	for (std::vector<int>::const_iterator it = m_indices.begin(); it != m_indices.end(); ++it)
	{
		if (*it == -1 || *(it + 1) == -1
			|| vec.at(*it).z() <= CAM_NEAR || vec.at(*(it + 1)).z() <= CAM_NEAR
			|| vec.at(*it).z() > 1 || vec.at(*(it + 1)).z() > 1)
		{
			continue;
		}
		drawLine(vec.at(*it), vec.at(*(it + 1)), color);
	}
}

void Cursor3D::setModelMatrix(const QMatrix4x4 &matrix)
{
	m_modelMatrix = matrix;
}

void Cursor3D::createVertices()
{
	m_vertices.push_back(QVector4D(0, 0.0, 0.0, 1));
	m_vertices.push_back(QVector4D(0.1, 0.0, 0.0, 1));
	m_vertices.push_back(QVector4D(0, 0.1, 0.0, 1));
	m_vertices.push_back(QVector4D(0, 0, 0.1, 1));
}

void Cursor3D::generateIndices()
{
	m_indices.push_back(0);
	m_indices.push_back(1);
	m_indices.push_back(-1);
	m_indices.push_back(0);
	m_indices.push_back(2);
	m_indices.push_back(-1);
	m_indices.push_back(0);
	m_indices.push_back(3);
	m_indices.push_back(-1);
}

void Cursor3D::addPoint(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects)
{
	if (m_activeObjects.size() == 1 && m_activeObjects.at(0) != nullptr)
	{
		switch (m_activeObjects.at(0)->m_type)
		{
		case ObjectType::bezierCurveC0:
		{
			int id = getClosestPointId(sceneObjects);
			static_cast<UiBezierCurveC0*>(sceneObjects.find(m_activeObjects.at(0)->getId())->second.get())->addPoint(sceneObjects.find(id)->second.get()->getObject(), m_activeObjects.at(0)->getId());
			break;
		}
		case ObjectType::bezierCurveC2:
		{
			int id = getClosestPointId(sceneObjects);
			static_cast<UiBezierCurveC2*>(sceneObjects.find(m_activeObjects.at(0)->getId())->second.get())->addPoint(sceneObjects.find(id)->second.get()->getObject(), m_activeObjects.at(0)->getId());
			break;
		}
		case ObjectType::bezierC2Interpolated:
		{
			int id = getClosestPointId(sceneObjects);
			static_cast<UiBezierC2Interpolated*>(sceneObjects.find(m_activeObjects.at(0)->getId())->second.get())->addPoint(sceneObjects.find(id)->second.get()->getObject(), m_activeObjects.at(0)->getId());
			break;
		}
		}
	}
}

void Cursor3D::deletePoint(std::unordered_map<int, std::unique_ptr<UiConnector>>& sceneObjects)
{
	if (m_activeObjects.size() == 1 && m_activeObjects.at(0) != nullptr)
	{
		switch (m_activeObjects.at(0)->m_type)
		{
		case ObjectType::bezierCurveC0:
		{
			int id = getClosestPointId(sceneObjects);
			static_cast<UiBezierCurveC0*>(sceneObjects.find(m_activeObjects.at(0)->getId())->second.get())->removePoint(id, m_activeObjects.at(0)->getId());
			break;
		}
		case ObjectType::bezierCurveC2:
		{
			int id = getClosestPointId(sceneObjects);
			static_cast<UiBezierCurveC2*>(sceneObjects.find(m_activeObjects.at(0)->getId())->second.get())->removePoint(id, m_activeObjects.at(0)->getId());
			break;
		}
		case ObjectType::bezierC2Interpolated:
		{
			int id = getClosestPointId(sceneObjects);
			static_cast<UiBezierC2Interpolated*>(sceneObjects.find(m_activeObjects.at(0)->getId())->second.get())->removePoint(id, m_activeObjects.at(0)->getId());
			break;
		}
		}
	}
}

bool Cursor3D::addToActive(std::shared_ptr<DrawableObject> sceneObject)
{
	int id = sceneObject->getId();
	if (m_activeObjects.count(id) > 0)
	{
		m_activeObjects.find(id)->second.get()->setColor(Colors::DEFAULT_OBJECT_COLOR);
		m_activeObjects.erase(id);
		return false;
	}
	m_activeObjects.emplace(id, sceneObject);
	m_activeObjects.find(id)->second.get()->setColor(Colors::ACTIVE_OBJECT_COLOR);
	return true;
}

int Cursor3D::getClosestPointId(std::unordered_map<int, std::unique_ptr<UiConnector>>& sceneObjects) const
{
	float minDistance = std::numeric_limits<float>::max();
	float distance;
	int id = -1;
	for (auto const &object : sceneObjects)
	{
		if (!object.second.get()->getObject()->m_enabled || object.second.get()->getObject()->m_type != ObjectType::point3D)
		{
			continue;
		}
		distance = math3d::calculateDistance3D(this->getPosition(), object.second.get()->getObject()->getPosition());
		if (distance < TARGETING_DISTANCE && distance < minDistance)
		{
			minDistance = distance;
			id = object.second.get()->getObject()->getId();
		}
	}
	return id;
}

//int Cursor3D::acquireObject(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects)
//{
//	if (m_obtainedObject != nullptr)
//	{
//		releaseObject();
//		return -1;
//	}
//	int id = getClosestObjectId(sceneObjects);
//	if (id != -1)
//	{
//		m_obtainedObject = sceneObjects.find(id)->second.get()->getObject();
//		m_obtainedObject->setColor(Colors::OBTAINED_OBJECT_COLOR);
//	}
//	return id;
//}

void Cursor3D::markObject(std::unordered_map<int, std::unique_ptr<UiConnector>>& sceneObjects, bool multiple)
{
	if (!multiple && m_activeObjects.size() >= 1)
	{
		clearAllObjects();
		return;

	}
	int id = getClosestObjectId(sceneObjects);
	if (id != -1)
	{
		addToActive(sceneObjects.find(id)->second.get()->getObject());
	}
}

void Cursor3D::markObject(std::shared_ptr<DrawableObject> sceneObject, bool multiple)
{
	if (!multiple && m_activeObjects.size() >= 1)
	{
		clearAllObjects();
		return;

	}
	addToActive(sceneObject);
}

//void Cursor3D::updatePosition(float posX, float posY, float posZ, const Camera &camera)
//{
//	m_worldCoords = QVector3D(posX - camera.m_viewMatrix.row(0).w(),
//		posY - camera.m_viewMatrix.row(1).w(),
//		posZ - camera.m_viewMatrix.row(2).w() - 1);
//	setModelMatrix((Camera::createRotationX(camera.m_pitch) * Camera::createRotationY(camera.m_yaw)).inverted()
//		* Camera::createTranslation(m_worldCoords));
//
//	if (m_obtainedObject != nullptr)
//	{
//		m_obtainedObject->setModelMatrix(getModelMatrix());
//	}
//	//float posX = x / (width * 0.5f) - 1.0f;
//	//float posY = -y / (heigth * 0.5f) + 1.0f;
//	//float posZ = 0;
//
//	//m_worldCoords = QVector3D(posX - camera.m_viewMatrix.row(0).w(),
//	//	posY - camera.m_viewMatrix.row(1).w(),
//	//	posZ - camera.m_viewMatrix.row(2).w() - 1);
//	//m_modelMatrix = (Camera::createRotationX(camera.m_pitch) * Camera::createRotationY(camera.m_yaw)).inverted()
//	//	* Camera::createTranslation(m_worldCoords);
//	//if (m_obtainedObject != nullptr)
//	//{
//	//	//m_obtainedObject->getModelMatrix() = m_modelMatrix;
//	//	m_obtainedObject->setModelMatrix(m_modelMatrix);
//	//}
//}
void Cursor3D::updatePosition(float x, float y, int width, int height, const Camera &camera, bool translate)
{
	m_posX = x / (width * 0.5f) - 1.0f;
	m_posY = -y / (height * 0.5f) + 1.0f;
	/*QVector3D right = camera.getRightVector();
	QVector3D up = camera.getUpVector();
	QVector3D forward = camera.getForwardVector();
	QVector3D eye = camera.getEyeVector();*/
	QVector3D prevPos = m_worldCoords;
	m_worldCoords = m_posX * camera.getRightVector() - (camera.getForwardVector() - camera.getEyeVector()) + m_posY * camera.getUpVector();
	/*QVector3D pos;
	if (z)
	{
		pos = m_posY * (forward - eye);
	}
	else
	{
		pos = m_posX * right - (forward - eye) + m_posY * up;
	}*/
	setModelMatrix(Camera::createTranslation(m_worldCoords));
	if (m_mode == Mode::Translate || translate)
	{
		prevPos = m_worldCoords - prevPos;
		translateObjects(prevPos);
		/*for (auto activeObject : m_activeObjects)
		{
			activeObject.second->translate(prevPos);
			if (activeObject.second->m_type == ObjectType::point3D)
			{
				std::static_pointer_cast<Point3D>(activeObject.second)->notifyAncestorsPositionChanged();
			}
		}*/
	}
}

void Cursor3D::translateObjects(const QVector3D& pos)
{
	for (auto obj : m_activeObjects)
	{
		obj.second->translate(pos);
		if (obj.second->m_type == ObjectType::point3D)
		{
			std::static_pointer_cast<Point3D>(obj.second)->notifyAncestorsPositionChanged();
		}
	}
}

//void Cursor3D::translateObjects(const QVector3D& pos, const QVector3D& translate)
//{
//
//	if (m_activeObjects.size() == 1)
//	{
//		m_activeObjects.begin()->second->setPosition(pos);
//		if (m_activeObjects.begin()->second->m_type == DrawableObject::ObjectType::point3D)
//		{
//			std::static_pointer_cast<Point3D>(m_activeObjects.begin()->second)->notifyAncestorsPositionChanged();
//		}
//		return;
//	}
//	for (auto obj : m_activeObjects)
//	{
//		obj.second->translate(translate);
//		if (obj.second->m_type == DrawableObject::ObjectType::point3D)
//		{
//			std::static_pointer_cast<Point3D>(obj.second)->notifyAncestorsPositionChanged();
//		}
//	}
//}

//void Cursor3D::updatePosition(float x, float y, int width, int height, const Camera &camera)
//{
//	m_posX = x / (width * 0.5f) - 1.0f;
//	m_posY = -y / (height * 0.5f) + 1.0f;
//	QVector3D prevPos = m_worldCoords;
//	m_worldCoords = QVector3D(m_posX - camera.m_viewMatrix.row(0).w(),
//		m_posY - camera.m_viewMatrix.row(1).w(),
//		m_posZ - camera.m_viewMatrix.row(2).w() - 1);
//	setModelMatrix((Camera::createRotationX(camera.m_pitch) * Camera::createRotationY(camera.m_yaw)).inverted()
//		* Camera::createTranslation(m_worldCoords));
//	if (m_mode == Mode::Translate)
//	{
//		prevPos = m_worldCoords - prevPos;
//		for (auto activeObject : m_activeObjects)
//		{
//			activeObject.second->translate(prevPos);
//			if (activeObject.second->m_type == DrawableObject::ObjectType::point3D)
//			{
//				std::static_pointer_cast<Point3D>(activeObject.second)->notifyAncestorsPositionChanged();
//			}
//		}
//	}
//
//	//switch (m_mode)
//	//{
//	//case Mode::Idle:
//	//{
//	//	break;
//	//}
//	//case Mode::Translate:
//	//{
//	//	/*if (m_obtainedObject != nullptr)
//	//	{
//	//		m_obtainedObject->setModelMatrix(getModelMatrix());
//	//		if (m_obtainedObject->m_type == DrawableObject::ObjectType::point3D)
//	//		{
//	//			std::static_pointer_cast<Point3D>(m_obtainedObject)->notifyAncestorsPositionChanged();
//	//		}
//	//	}*/
//	//	prevPos = m_worldCoords - prevPos;
//	//	for (auto activeObject : m_activeObjects)
//	//	{
//	//		activeObject.second->translate(prevPos);
//	//		if (activeObject.second->m_type == DrawableObject::ObjectType::point3D)
//	//		{
//	//			std::static_pointer_cast<Point3D>(activeObject.second)->notifyAncestorsPositionChanged();
//	//		}
//	//	}
//	//	break;
//	//}
//	//case Mode::Add:
//	//{
//	//	break;
//	//}
//	//case Mode::Delete:
//	//{
//	//	break;
//	//}
//	//}
//}

void Cursor3D::clearAllObjects()
{
	for (std::unordered_map<int, std::shared_ptr<DrawableObject>>::iterator it = m_activeObjects.begin(); it != m_activeObjects.end(); ++it)
	{
		(*it).second.get()->setColor(Colors::DEFAULT_OBJECT_COLOR);
	}
	m_activeObjects.clear();
}

int Cursor3D::getClosestObjectId(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects) const
{
	float minDistance = std::numeric_limits<float>::max();
	float distance;
	int id = -1;
	for (auto const &object : sceneObjects)
	{
		if (!object.second.get()->getObject()->m_enabled || object.second.get()->getObject()->m_type == ObjectType::bezierCurveC0
			|| object.second.get()->getObject()->m_type == ObjectType::bezierCurveC2 || object.second.get()->getObject()->m_type == ObjectType::bezierC2Interpolated
			|| object.second.get()->getObject()->getId() == this->getId())
		{
			continue;
		}
		distance = math3d::calculateDistance3D(this->getPosition(), object.second.get()->getObject()->getPosition());
		if (distance < TARGETING_DISTANCE && distance < minDistance)
		{
			minDistance = distance;
			id = object.second.get()->getObject()->getId();
		}
	}
	return id;
}

int Cursor3D::getNewClosestObjectId(std::unordered_map<int, std::unique_ptr<UiConnector>>& sceneObjects) const
{
	float minDistance = std::numeric_limits<float>::max();
	float distance;
	int id = -1;
	for (auto const &object : sceneObjects)
	{
		if (!object.second.get()->getObject()->m_enabled || object.second.get()->getObject()->m_type == ObjectType::bezierCurveC0
			|| object.second.get()->getObject()->m_type == ObjectType::bezierCurveC2 || object.second.get()->getObject()->m_type == ObjectType::bezierC2Interpolated
			|| object.second.get()->getObject()->getId() == this->getId())
		{
			continue;
		}
		distance = math3d::calculateDistance3D(this->getPosition(), object.second.get()->getObject()->getPosition());
		if (distance < TARGETING_DISTANCE && distance < minDistance)
		{
			minDistance = distance;
			id = object.second.get()->getObject()->getId();
		}
	}
	return id;
}

Cursor3D::Mode Cursor3D::getMode() const
{
	return m_mode;
}

void Cursor3D::changeMode(Mode mode)
{
	m_mode = mode;
}

QVector3D Cursor3D::moveToObject()
{
	if (!m_activeObjects.empty())
		setPosition(m_activeObjects.begin()->second->getPosition());
	return getPosition();
}

void Cursor3D::performAction(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects, bool multiple)
{
	switch (m_mode)
	{
	case Mode::Idle:
	{
		markObject(sceneObjects, multiple);
		break;
	}
	case Mode::Translate:
	{
		markObject(sceneObjects, false);
		break;
	}
	case Mode::Add:
	{
		addPoint(sceneObjects);
		break;
	}
	case Mode::Delete:
	{
		deletePoint(sceneObjects);
		break;
	}
	}
}

void Cursor3D::setActiveObject(std::shared_ptr<DrawableObject> sceneObject)
{
	clearAllObjects();
	m_activeObjects.emplace(sceneObject->getId(), sceneObject);
	m_activeObjects.at(0)->setColor(Colors::ACTIVE_OBJECT_COLOR);
}

void Cursor3D::addActiveObject(std::shared_ptr<DrawableObject> sceneObject)
{
	sceneObject->setColor(Colors::ACTIVE_OBJECT_COLOR);
	m_activeObjects.emplace(sceneObject->getId(), sceneObject);
}

std::shared_ptr<DrawableObject> Cursor3D::getActiveObject() const
{
	if (m_activeObjects.size() != 1)
	{
		return nullptr;
	}
	return m_activeObjects.at(0);
}
