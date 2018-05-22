#pragma once
#include "drawableObject.h"
#include <memory>
#include <unordered_map>

class Camera;
class UiConnector;

class Cursor3D : public DrawableObject
{
public:
	Cursor3D(ObjectType type);

	friend class UiCursor3D;

	//std::shared_ptr<DrawableObject> m_obtainedObject;
	QVector3D m_worldCoords;
	//Idle mode to mark several objects without moving them
	enum class Mode { Idle, Translate, Add, Delete };

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	QVector4D getPosition() const override;
	
	//void updatePosition(float posX, float posY, float posZ, const Camera &camera);
	void updatePosition(float x, float y, int width, int height, const Camera &camera);
	void clearAllObjects();
	Mode getMode() const;
	void changeMode(Mode mode);
	//mouse was pressed, take action based on cursor mode
	void performAction(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects, bool multiple = false);
	void setActiveObject(std::shared_ptr<DrawableObject> sceneObject);
	//returns object if there is only one active, otherwise nullptr
	std::shared_ptr<DrawableObject> getActiveObject() const;

private:
	float m_posX;
	float m_posY;
	float m_posZ;
	//object to be edited
	//std::shared_ptr<DrawableObject> m_activeObject;
	//std::vector<std::shared_ptr<DrawableObject>> m_activeObjects;
	std::unordered_map<int, std::shared_ptr<DrawableObject>> m_activeObjects;
	Mode m_mode;

	void createVertices() override;
	void generateIndices() override;
	//to active object
	void addPoint(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects);
	//from active object
	void deletePoint(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects);
	//returns false if objects already exists and erases it, otherwise adds object and returns true
	bool addToActive(std::shared_ptr<DrawableObject> sceneObject);
	void markObject(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects, bool multiple);
	int getClosestPointId(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects) const;
	int getClosestObjectId(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects) const;
	int getNewClosestObjectId(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects) const;
};
