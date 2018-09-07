#pragma once
#include "uiConnector.h"
#include "BezierSurface.h"

class Scene;

class UiBezierSurface : public UiConnector
{
	Q_OBJECT
public:
	virtual ~UiBezierSurface();

	virtual void connectToUi(const Ui_ModelowanieGeometryczne1Class *ui) const = 0;
	virtual void connectToScene(const Scene *scene) const = 0;
	std::shared_ptr<DrawableObject> getObject() override;
	std::shared_ptr<BezierSurface> getBezierSurface();
	QCheckBox* getCBBezierGrid() const;
	QCheckBox* getCBControlGrid() const;

protected:
	explicit UiBezierSurface(std::shared_ptr<BezierSurface> bezierSurface);
	QCheckBox *m_checkBoxBezierGrid;
	QCheckBox *m_checkBoxControlGrid;

private:
	std::shared_ptr<BezierSurface> m_bezierSurface;

signals:
	void nameChanged(int id, const QString &name);
	void requestedPoints(const std::vector<std::shared_ptr<Point3D>> &points);
	void requestedPoints2(const std::vector<std::shared_ptr<Point3D>> &points) const;
	void deletingSurface(const std::vector<int> &ids);
	void surfaceDeleted(int surfaceId);

public slots:
	void changeName(const QString &name, int id) override;
	void updateSurface() const;
	void updateScreenSize(float width, float height);
	void updateSurfaceData(BezierSurfaceData data);
	void getPoints(int surfaceId);
	void changeBezierGridState(int state);
	void changeControlGridState(int state);
};
