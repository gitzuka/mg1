#pragma once
#include "cursor3d.h"
#include "camera.h"
#include <memory>
#include "bezierCurveC0.h"
#include <unordered_map>
#include "BezierSurfaceC0.h"
#include "axes.h"
#include "uiBezierSurfaceC2.h"

class UiTrimmingCurve;
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
	std::shared_ptr<Axes> m_axes;
	Camera m_camera;

	void draw() const;
	void toggleCursor3D(bool isActive);
	void updateCursorPosition(float x, float y, int width, int heigth, bool z);
	int createDrawableObject(const QString &name);
	UiConnector* getUiConntector(int id) const;
	void createBezierSurfaceC0(const BezierSurfaceData &data);
	void createBezierSurfaceC2(const BezierSurfaceData &data);
	void showAxes(char axis) const;
	void initialize();

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
	void createTrimmingCurveMenu(const QPoint &pos, int id);
	void checkIntersections(const QList<int> &ids);
	void setActiveObject(int id);
	//returns nullptr if object not found
	std::shared_ptr<DrawableObject> getSceneObject(int id);
	QPair<int, DrawableObject::ObjectType> createUiConnector(const QString &name);
	void createBezierSurfaceC0(const std::shared_ptr<BezierSurfaceC0> &surface, bool loaded = false);
	void createBezierSurfaceC2(const std::shared_ptr<BezierSurfaceC2> &surface, bool loaded = false);

public slots:
	void updateControlPoints(std::vector<std::shared_ptr<Point3D>> controlPoints, const std::vector<int> &prevIds);
	void removeUiConnectors(const std::vector<int> &ids);

private slots:
	void performCursorAction(bool multiple = false);
	void resetCursor();
	void createObjectMenu(const QPoint &pos, const QList<int> &ids);
	void deleteObject(int id);
	void selectCursorObjects(QList<int> &ids);
	void loadScene(const QString &fileContent);
	void saveScene(const QString &path);
	void newtonStepChanged(double val);
	void selfIntersectionDistChanged(double val);
	void newtonWrapDistChanged(double val);
	void gradientStepChanged(double val);
	void closestPointStepChanged(double val);
	void newtonWrapIterChanged(int val);
	//void translateObjects(const QVector3D &pos, const QVector3D &translate);
	void translateObjects(const QVector3D &pos);
	void findClosestPoint(const QPoint &pos, int width, int height, bool add);
	void generateHeightMap();

signals:
	void addedTorus(const QString &name, int id, const UiTorus *uiTorus);
	void addedBezierCurveC0(const QString &name, int id, const UiBezierCurveC0 *uiBezierC0);
	void addedBezierCurveC2(const QString &name, int id, const UiBezierCurveC2 *uiBezierC2);
	void addedBezierC2Interpolated(const QString &name, int id, const UiBezierC2Interpolated *uiBezierC2);
	void addedBezierSurfaceC0(const QString &name, int id, UiBezierSurfaceC0 *uiBezierSurfaceC0);
	void addedBezierSurfaceC2(const QString &name, int id, UiBezierSurfaceC2 *uiBezierSurfaceC2);
	void addedPoint3D(const QString &name, int id, const UiPoint3D *object);
	void addedTrimmingCurve(const QString &name, int id, const UiTrimmingCurve *trimmingCurve);
	void update() const;
	void editModeBC0(int id);
	void editModeBC2(int id);
	void editModeBC2Int(int id);
	void objectActivated(int id);
	void objectDeactivated(int id);
	void createdBSControlPoint(const QString &name, int id, const UiPoint3D *object);
	void intersectionNotFound();
	void intersectionFound(const std::vector<QVector4D>& parametrization, const QVector4D& uvRange1,
	                       const QVector4D& uvRange2, std::shared_ptr<DrawableObject> surface1,
	                       std::shared_ptr<DrawableObject> surface2, QPair<bool, bool> s1Wrap, QPair<bool, bool> s2Wrap);
};
