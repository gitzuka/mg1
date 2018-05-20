#include "cursor3d.h"
#include "camera.h"
#include "uiConnector.h"
#include "colors.h"
#include "3dmath.h"
#include "point3d.h"
#include "uiBezierCurveC0.h"
#include "uiBezierCurveC2.h"

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

QVector4D Cursor3D::getPosition() const
{
	return QVector4D(m_modelMatrix.row(0).w(), m_modelMatrix.row(1).w(), m_modelMatrix.row(2).w(), 1);
}

void Cursor3D::createVertices()
{
	m_vertices.push_back(QVector4D(0, 0.0, 0.0, 1));
	m_vertices.push_back(QVector4D(0.08, 0.0, 0.0, 1));
	m_vertices.push_back(QVector4D(0, 0.08, 0.0, 1));
	m_vertices.push_back(QVector4D(0, 0, 0.08, 1));
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
	if (m_activeObject != nullptr)
	{
		switch (m_activeObject->m_type)
		{
		case ObjectType::bezierCurveC0:
		{
			int id = getClosestPoint(sceneObjects);
			static_cast<UiBezierCurveC0*>(sceneObjects.find(m_activeObject->getId())->second.get())->addPoint(sceneObjects.find(id)->second.get()->getObject(), m_activeObject->getId());
			break;
		}
		case ObjectType::bezierCurveC2:
		{
			int id = getClosestPoint(sceneObjects);
			static_cast<UiBezierCurveC2*>(sceneObjects.find(m_activeObject->getId())->second.get())->addPoint(sceneObjects.find(id)->second.get()->getObject(), m_activeObject->getId());
			break;
		}
		}
	}
}

void Cursor3D::deletePoint(std::unordered_map<int, std::unique_ptr<UiConnector>>& sceneObjects)
{
	if (m_activeObject != nullptr)
	{
		switch (m_activeObject->m_type)
		{
		case ObjectType::bezierCurveC0:
		{
			int id = getClosestPoint(sceneObjects);
			static_cast<UiBezierCurveC0*>(sceneObjects.find(m_activeObject->getId())->second.get())->removePoint(id, m_activeObject->getId());
			break;
		}
		case ObjectType::bezierCurveC2:
		{
			int id = getClosestPoint(sceneObjects);
			static_cast<UiBezierCurveC2*>(sceneObjects.find(m_activeObject->getId())->second.get())->removePoint(id, m_activeObject->getId());
			break;
		}
		}
	}
}

int Cursor3D::getClosestPoint(std::unordered_map<int, std::unique_ptr<UiConnector>>& sceneObjects) const
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

int Cursor3D::acquireObject(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects)
{
	if (m_obtainedObject != nullptr)
	{
		releaseObject();
		return -1;
	}
	int id = getClosestObject(sceneObjects);
	if (id != -1)
	{
		m_obtainedObject = sceneObjects.find(id)->second.get()->getObject();
		m_obtainedObject->setColor(Colors::OBTAINED_OBJECT_COLOR);
	}
	return id;
}

int Cursor3D::markObject(std::unordered_map<int, std::unique_ptr<UiConnector>>& sceneObjects)
{
	int id = getClosestObject(sceneObjects);
	if (id != -1)
	{
		m_markedObjects.push_back(sceneObjects.find(id)->second.get()->getObject());
		sceneObjects.find(id)->second.get()->getObject()->setColor(Colors::ACTIVE_OBJECT_COLOR);
	}
	return id;
}

void Cursor3D::releaseObject()
{
	m_obtainedObject->setColor(Colors::DEFAULT_OBJECT_COLOR);
	m_obtainedObject = nullptr;
}

void Cursor3D::updatePosition(float posX, float posY, float posZ, const Camera &camera)
{
	m_worldCoords = QVector3D(posX - camera.m_viewMatrix.row(0).w(),
		posY - camera.m_viewMatrix.row(1).w(),
		posZ - camera.m_viewMatrix.row(2).w() - 1);
	setModelMatrix((Camera::createRotationX(camera.m_pitch) * Camera::createRotationY(camera.m_yaw)).inverted()
		* Camera::createTranslation(m_worldCoords));

	if (m_obtainedObject != nullptr)
	{
		m_obtainedObject->setModelMatrix(getModelMatrix());
	}
	//float posX = x / (width * 0.5f) - 1.0f;
	//float posY = -y / (heigth * 0.5f) + 1.0f;
	//float posZ = 0;

	//m_worldCoords = QVector3D(posX - camera.m_viewMatrix.row(0).w(),
	//	posY - camera.m_viewMatrix.row(1).w(),
	//	posZ - camera.m_viewMatrix.row(2).w() - 1);
	//m_modelMatrix = (Camera::createRotationX(camera.m_pitch) * Camera::createRotationY(camera.m_yaw)).inverted()
	//	* Camera::createTranslation(m_worldCoords);
	//if (m_obtainedObject != nullptr)
	//{
	//	//m_obtainedObject->getModelMatrix() = m_modelMatrix;
	//	m_obtainedObject->setModelMatrix(m_modelMatrix);
	//}
}

void Cursor3D::updatePosition(float x, float y, int width, int height, const Camera &camera)
{
	m_posX = x / (width * 0.5f) - 1.0f;
	m_posY = -y / (height * 0.5f) + 1.0f;
	m_worldCoords = QVector3D(m_posX - camera.m_viewMatrix.row(0).w(),
		m_posY - camera.m_viewMatrix.row(1).w(),
		m_posZ - camera.m_viewMatrix.row(2).w() - 1);
	setModelMatrix((Camera::createRotationX(camera.m_pitch) * Camera::createRotationY(camera.m_yaw)).inverted()
		* Camera::createTranslation(m_worldCoords));

	switch (m_mode)
	{
	case Mode::Idle:
	{
		break;
	}
	case Mode::Translate:
	{
		if (m_obtainedObject != nullptr)
		{
			m_obtainedObject->setModelMatrix(getModelMatrix());
			if (m_obtainedObject->m_type == DrawableObject::ObjectType::point3D)
			{
				std::static_pointer_cast<Point3D>(m_obtainedObject)->notifyAncestorsPositionChanged();
			}
		}
		break;
	}
	case Mode::Add:
	{
		break;
	}
	case Mode::Delete:
	{
		break;
	}
	}
}

void Cursor3D::clearMarkedObjects()
{
	for (std::vector<std::shared_ptr<DrawableObject>>::iterator it = m_markedObjects.begin(); it != m_markedObjects.end(); ++it)
	{
		(*it)->setColor(Colors::DEFAULT_OBJECT_COLOR);
	}
	m_markedObjects.clear();
}

void Cursor3D::clearAllObjects()
{
	clearMarkedObjects();
	for (std::vector<std::shared_ptr<DrawableObject>>::iterator it = m_obtainedObjects.begin(); it != m_obtainedObjects.end(); ++it)
	{
		(*it)->setColor(Colors::DEFAULT_OBJECT_COLOR);
	}
	m_obtainedObjects.clear();
	m_obtainedObject->setColor(Colors::DEFAULT_OBJECT_COLOR);
	m_obtainedObject = nullptr;
}

int Cursor3D::getClosestObject(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects) const
{
	float minDistance = std::numeric_limits<float>::max();
	float distance;
	int id = -1;
	for (auto const &object : sceneObjects)
	{
		if (!object.second.get()->getObject()->m_enabled || object.second.get()->getObject()->m_type == ObjectType::bezierCurveC0
			|| object.second.get()->getObject()->m_type == ObjectType::bezierCurveC2 || object.second.get()->getObject()->getId() == this->getId())
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

void Cursor3D::performAction(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects)
{
	switch (m_mode)
	{
	case Mode::Idle:
	{
		markObject(sceneObjects);
		break;
	}
	case Mode::Translate:
	{
		acquireObject(sceneObjects);
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
	m_activeObject = sceneObject;
}

void Cursor3D::removeActiveOjbect()
{
	m_activeObject = nullptr;
}

const std::shared_ptr<DrawableObject>& Cursor3D::getActiveObject() const
{
	return m_activeObject;
}
