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

	std::shared_ptr<DrawableObject> m_obtainedObject;
	QVector3D m_worldCoords;
	///Idle mode to mark several objects without moving them
	enum class Mode { Idle, Translate, Add, Delete };

	void draw(std::vector<QVector4D> &vec) const override;
	void draw(std::vector<QVector4D> &vec, float3 color) const override;
	void setModelMatrix(const QMatrix4x4 &matrix) override;
	QVector4D getPosition() const override;
	
	int markObject(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects);
	void releaseObject();
	void updatePosition(float posX, float posY, float posZ, const Camera &camera);
	void updatePosition(float x, float y, int width, int height, const Camera &camera);
	void clearMarkedObjects();
	void clearAllObjects();
	int getClosestObject(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects) const;
	Mode getMode() const;
	void changeMode(Mode mode);
	///mouse was pressed, take action based on cursor mode
	void performAction(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects);
	void setActiveObject(std::shared_ptr<DrawableObject> sceneObject);
	void removeActiveOjbect();
	const std::shared_ptr<DrawableObject>& getActiveObject() const;

private:
	float m_posX;
	float m_posY;
	float m_posZ;
	std::vector<std::shared_ptr<DrawableObject>> m_obtainedObjects;
	std::vector<std::shared_ptr<DrawableObject>> m_markedObjects;
	///object to be edited
	std::shared_ptr<DrawableObject> m_activeObject;
	Mode m_mode;

	void createVertices() override;
	void generateIndices() override;
	///to active object
	void addPoint(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects);
	///from active object
	void deletePoint(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects);
	int acquireObject(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects);
	int getClosestPoint(std::unordered_map<int, std::unique_ptr<UiConnector>> &sceneObjects) const;
};
