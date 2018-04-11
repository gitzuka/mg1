#include "cursor3d.h"
#include "camera.h"
#include "uiConnector.h"

Cursor3D::Cursor3D(ObjectType type) : DrawableObject(type, "Cursor3D"),
m_worldCoords(QVector3D(0, 0, 0)), m_obtainedColor(1,1,0)
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

int Cursor3D::acquireObject(const QList<std::shared_ptr<DrawableObject>> &objects)
{
	if (m_obtainedObject != nullptr)
	{
		releaseObject();
		return -1;
	}
	int index = getClosestObject(objects);
	if (index != -1)
	{
		m_obtainedObject = objects.at(index);
		m_obtainedObject->setColor(m_obtainedColor.x(), m_obtainedColor.y(), m_obtainedColor.z());
	}
	return index;
}

void Cursor3D::releaseObject()
{
	m_obtainedObject->setColor(1, 1, 1);
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

float Cursor3D::calculateDistance2D(float x1, float x2, float y1, float y2) const
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1));
}

float Cursor3D::calculateDistance2D(const std::shared_ptr<DrawableObject> &object1, const std::shared_ptr<DrawableObject> &object2) const
{
	return calculateDistance2D(object1->getModelMatrix().row(0).w(), object2->getModelMatrix().row(0).w(),
		object1->getModelMatrix().row(1).w(), object2->getModelMatrix().row(1).w());
}

float Cursor3D::calculateDistance3D(float x1, float x2, float y1, float y2, float z1, float z2) const
{
	return sqrt((x2 - x1)*(x2 - x1) + (y2 - y1)*(y2 - y1) + (z2 - z1)*(z2 - z1));
}

float Cursor3D::calculateDistance3D(const std::shared_ptr<DrawableObject> &object1, const std::shared_ptr<DrawableObject> &object2) const
{
	return calculateDistance3D(object1->getPosition().x(), object2->getPosition().x(),
		object1->getPosition().y(), object2->getPosition().y(),
		object1->getPosition().z(), object2->getPosition().z());
}

float Cursor3D::calculateDistance3D(const QVector4D &vec1, const QVector4D &vec2) const
{
	return calculateDistance3D(vec1.x(), vec2.x(),
		vec1.y(), vec2.y(),
		vec1.z(), vec2.z());
}

int Cursor3D::getClosestObject(const QList<std::shared_ptr<DrawableObject>> &objects) const
{
	float minDistance = std::numeric_limits<float>::max();
	float distance;
	int index = -1;
	for (int i = 0; i < objects.count(); ++i)
	{
		if (objects.at(i)->getId() == this->getId())
		{
			continue;
		}
		distance = calculateDistance3D(this->getPosition(), objects.at(i)->getPosition());
		if (distance < TARGETING_DISTANCE && distance < minDistance)
		{
			minDistance = distance;
			index = i;
		}
	}
	return index;
}

int Cursor3D::getClosestObject(std::unordered_map<int, std::unique_ptr<UiConnector>> sceneObjects) const
{
	float minDistance = std::numeric_limits<float>::max();
	float distance;
	int index = -1;
	for (auto const& object : sceneObjects)
	{
		if (object.second.get()->getObject()->getId() == this->getId())
		{
			continue;
		}
		distance = calculateDistance3D(this->getPosition(), object.second.get()->getObject()->getPosition());
		if (distance < TARGETING_DISTANCE && distance < minDistance)
		{
			minDistance = distance;
			index = object.second.get()->getObject()->getId();
		}
	}
	return index;
}
