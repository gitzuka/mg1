#pragma once
#include "utils.h"
#include <QMatrix4x4>
#include <QVector3D>

class Camera
{
public:
	Camera();

	float m_pitch;
	float m_yaw;
	QPoint m_mousePos;
	QVector3D m_eyeVector;
	QVector3D m_origin;
	QMatrix4x4 m_viewMatrix;
	QMatrix4x4 m_projectionMatrix;
	QMatrix4x4 m_m_projectionMatrixStereoL, m_m_projectionMatrixStereoR;
	QMatrix4x4 m_projView;
	QMatrix4x4 m_projViewInv;

	void updateView();
	void keyPressed(const unsigned char key);
	void mouseMoved(float x, float y);
	void updateStereoscopy(float e, float width, float heigth);
	QVector3D getEyeVector() const;
	QVector3D getRightVector() const;
	QVector3D getUpVector() const;
	QVector3D getForwardVector() const;

	static QMatrix4x4 createLookAt(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz);
	static QMatrix4x4 createLookAt(const QVector3D &eye, const QVector3D &target, const QVector3D &up);
	static QVector4D transform(const QVector4D &point, const QMatrix4x4 &matrix);
	static QMatrix4x4 createTranslation(float x, float y, float z);
	static QMatrix4x4 createTranslation(const QVector3D &vec);
	static QMatrix4x4 createProjection(float width, float heigth, float near = CAM_NEAR, float far = CAM_FAR, float angle = FOV);
	static QMatrix4x4 createStereoProjection(bool isLeft, float width, float heigth, float e = 0.1f, float near = CAM_NEAR, float far = CAM_FAR, float angle = FOV);
	static QMatrix4x4 createScaling(float factor);
	static QMatrix4x4 createScaling(QVector3D factor);
	static QMatrix4x4 createRotationX(float angle);
	static QMatrix4x4 createRotationY(float angle);
	static QMatrix4x4 createRotationZ(float angle);
	static QMatrix4x4 createIdentity();
	static QVector4D multiplyByMatrix(const QMatrix4x4 &mat, const QVector4D &vec);
};
