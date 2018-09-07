#pragma once
#include "cursor3d.h"
#include "camera.h"
#include <memory>
#include "bezierCurveC0.h"
#include <unordered_map>
#include "BezierSurfaceC0.h"

class UiBezierCurveC2;
class UiPoint3D;
class UiTorus;
class UiCursor3D;
class UiBezierC2Interpolated;
class UiBezierSurfaceC0;
class UiBezierSurfaceC2;

class Scene : public QObject
{
	Q_OBJECT
public:
	Scene();

	bool m_stereoscopy;
	bool m_isCursor3d;
	std::shared_ptr<Cursor3D> m_cursor;
	Camera m_camera;

	void draw() const;
	void toggleCursor3D(bool isActive);
	void updateCursorPosition(float x, float y, int width, int heigth, bool z);
	int createDrawableObject(const QString &name);
	UiConnector* getUiConntector(int id) const;
	void createBezierSurfaceC0(const BezierSurfaceData &data);
	void createBezierSurfaceC2(const BezierSurfaceData &data);

private:
	std::unordered_map<int, std::unique_ptr<UiConnector>> m_uiConnectors;

	void addUiConnector(std::unique_ptr<UiConnector> uiConnector);
	void createCurveC0fromPoints(const QList<int> &objectIds);
	void createCurveC2fromPoints(const QList<int> &objectIds);
	void createCurveC2IntfromPoints(const QList<int> &objectIds);
	void createBC0menu(const QPoint &pos, int id);
	void createBC2menu(const QPoint &pos, int id);
	void createBC2IntMenu(const QPoint &pos, int id);
	void createPoint3Dmenu(const QPoint &pos, const QList<int> &ids);
	void createIntersectionMenu(const QPoint &pos, const QList<int> &ids);
	void checkIntersections(const QList<int> &ids);
	void setActiveObject(int id);
	//returns nullptr if object not found
	std::shared_ptr<DrawableObject> getSceneObject(int id);
	QPair<int, DrawableObject::ObjectType> createUiConnector(const QString &name);

public slots:
	void updateControlPoints(std::vector<std::shared_ptr<Point3D>> controlPoints, const std::vector<int> &prevIds);
	void removeUiConnectors(const std::vector<int> &ids);

private slots:
	void performCursorAction(bool multiple = false);
	void resetCursor();
	void createObjectMenu(const QPoint &pos, const QList<int> &ids);
	void deleteObject(int id);
	void selectCursorObjects(QList<int> &ids);

signals:
	void addedTorus(const QString &name, int id, const UiTorus *uiTorus);
	void addedBezierCurveC0(const QString &name, int id, const UiBezierCurveC0 *uiBezierC0);
	void addedBezierCurveC2(const QString &name, int id, const UiBezierCurveC2 *uiBezierC2);
	void addedBezierC2Interpolated(const QString &name, int id, const UiBezierC2Interpolated *uiBezierC2);
	void addedBezierSurfaceC0(const QString &name, int id, UiBezierSurfaceC0 *uiBezierSurfaceC0);
	void addedBezierSurfaceC2(const QString &name, int id, UiBezierSurfaceC2 *uiBezierSurfaceC2);
	void addedPoint3D(const QString &name, int id, const UiPoint3D *object);
	void update() const;
	void editModeBC0(int id);
	void editModeBC2(int id);
	void editModeBC2Int(int id);
	void objectActivated(int id);
	void objectDeactivated(int id);
	void createdBSControlPoint(const QString &name, int id, const UiPoint3D *object);
};
