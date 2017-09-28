#pragma once
#include "cursor3d.h"
#include "camera.h"
#include <memory>
#include <uiScene.h>
#include "bezierCurveC0.h"


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
	std::shared_ptr<Cursor3D> m_cursor;
	std::shared_ptr<DrawableObject> m_activeObject;
	Camera m_camera;

	int countObjects() const;
	void deleteObject(const std::shared_ptr<DrawableObject> &object);
	void deleteObject(int index);
	void draw() const;
	void toggleCursor3D(bool isActive);
	void updateCursorPosition(float x, float y, int width, int heigth);
	int updateCursor();
	const UiScene* getUiComponent() const;
	std::shared_ptr<DrawableObject> getObject(int index) const;
	std::shared_ptr<DrawableObject> getObjectByID(int id) const;
	int createDrawableObject(QString name);

private:
	QList<std::shared_ptr<DrawableObject>> m_objects;
	UiScene m_uiScene;
	float3 m_colorL;
	float3 m_colorR;

	void addObject(const std::shared_ptr<DrawableObject> &object);
	void createCurveC0fromPoints(const QList<int> &objectIds);

public slots:
	void createObjectMenu(const QPoint &pos, const QList<int> &ids);

private slots:
	void removedObject();

signals:
	void addedTorus(QString name, int id, const std::shared_ptr<Torus> &object);
	void addedBezierCurveC0(QString name, int id, const std::shared_ptr<BezierCurveC0> &object);
	void addedPoint3D(QString name, int id, const std::shared_ptr<DrawableObject> &object);
	void update() const;
};
