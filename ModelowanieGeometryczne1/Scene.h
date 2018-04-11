#pragma once
#include "cursor3d.h"
#include "camera.h"
#include <memory>
#include "bezierCurveC0.h"
//#include "torus.h"
//#include "UiConnector.h"
#include <unordered_map>

class UiPoint3D;
class UiTorus;
class UiCursor3D;

class Scene : public QObject
{
	Q_OBJECT
public:
	Scene();

	float m_cursorPosX;
	float m_cursorPosY;
	float m_cursorPosZ;
	bool m_stereoscopy;
	bool m_isCursor3d;
	//std::shared_ptr<Cursor3D> m_cursor;
	std::shared_ptr<Cursor3D> m_cursor;
	Camera m_camera;

	//int countObjects() const;
	//void deleteObject(const std::shared_ptr<DrawableObject> &object);
	void draw() const;
	void toggleCursor3D(bool isActive);
	void updateCursorPosition(float x, float y, int width, int heigth);
	int updateCursor();
	//std::shared_ptr<DrawableObject> getObject(int index) const;
	//std::shared_ptr<DrawableObject> getObjectByID(int id) const;
	int createDrawableObject(const QString &name);

private:
	//QList<std::shared_ptr<DrawableObject>> m_objects;
	std::unordered_map<int, std::unique_ptr<UiConnector>> m_uiConnectors;
	float3 m_colorL;
	float3 m_colorR;
	//std::shared_ptr<UiBezierCurveC0> uiBezier;
	std::shared_ptr<DrawableObject> m_activeObject;

	void addObject(const std::shared_ptr<DrawableObject> &object);
	void addUiConnector(std::unique_ptr<UiConnector> uiConnector);
	void createCurveC0fromPoints(const QList<int> &objectIds);
	void createBC0menu(const QPoint &pos, int id);
	void createPoint3Dmenu(const QPoint &pos, const QList<int> &ids);
	void setActiveObject(int id);

public slots:
	void createObjectMenu(const QPoint &pos, const QList<int> &ids);
	void deleteObject(int id);

signals:
	void addedTorus(const QString &name, int id, const UiTorus *uiTorus);
	void addedBezierCurveC0(const QString &name, int id, const UiBezierCurveC0 *uiBezierC0);
	void addedPoint3D(const QString &name, int id, const UiPoint3D *object);
	void update() const;
};
