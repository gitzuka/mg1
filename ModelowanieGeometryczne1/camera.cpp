#include "camera.h"
#include <qmath.h>


Camera::Camera() : m_pitch(0), m_yaw(0), m_eyeVector(0, 0, 1), m_viewMatrix(createTranslation(-m_eyeVector))
{
}


void Camera::updateView()
{
	QMatrix4x4 matPitch = createRotationX(m_pitch);
	QMatrix4x4 matYaw = createRotationY(m_yaw);

	m_viewMatrix = matPitch * matYaw * createTranslation(-m_eyeVector);
	m_projView = m_projectionMatrix * m_viewMatrix;
	m_projViewInv = m_projView.inverted();
}

void Camera::keyPressed(const unsigned char key)
{
	float dx = 0, dz = 0, dy = 0;
	switch (key)
	{
	case 'W':
	{
		dz = TRANSLATION_STEP;
		break;
	}
	case 'S':
	{
		dz = -TRANSLATION_STEP;
		break;
	}
	case 'A':
	{
		dx = -TRANSLATION_STEP;
		break;
	}
	case 'D':
	{
		dx = TRANSLATION_STEP;
		break;
	}
	case 'R':
	{
		dy = TRANSLATION_STEP;
		break;
	}
	case 'F':
	{
		dy = -TRANSLATION_STEP;
	}
	default:
		break;
	}
	QVector3D forward(m_viewMatrix.row(2).x(), m_viewMatrix.row(2).y(), m_viewMatrix.row(2).z());
	QVector3D vertical(m_viewMatrix.row(1).x(), m_viewMatrix.row(1).y(), m_viewMatrix.row(1).z());
	QVector3D strafe(m_viewMatrix.row(0).x(), m_viewMatrix.row(0).y(), m_viewMatrix.row(0).z());

	m_eyeVector += (-dz * forward + dx * strafe + dy * vertical) * SPEED;
	updateView();
}

void Camera::mouseMoved(float x, float y)
{
	m_yaw += x * MOUSE_SENSITIVITY;
	m_pitch += y * MOUSE_SENSITIVITY;

	updateView();
}

void Camera::updateStereoscopy(float e, float width, float heigth)
{
	m_m_projectionMatrixStereoL = createStereoProjection(true, width, heigth, e);
	m_m_projectionMatrixStereoR = createStereoProjection(false, width, heigth, e);
}

QMatrix4x4 Camera::createLookAt(float eyex, float eyey, float eyez, float centerx, float centery, float centerz, float upx, float upy, float upz)
{
	QMatrix4x4 mat;
	QVector3D x, y, z;

	z.setX(eyex - centerx);
	z.setY(eyey - centery);
	z.setZ(eyez - centerz);
	z.normalize();

	y.setX(upx);
	y.setY(upy);
	y.setZ(upz);

	x = QVector3D::crossProduct(y, z);
	x.normalize();

	y.crossProduct(z, x);
	y.normalize();

	mat = {
		x.x(), x.y(),  x.z(), -x.x() * eyex - x.y() * eyey - x.z()*eyez,
		y.x(), y.y(),  y.z(), -y.x() * eyex - y.y() * eyey - y.z()*eyez,
		z.x(), z.y(),  z.z(), -z.x() * eyex - z.y() * eyey - z.z()*eyez,
		0,0,0,1
	};
	return mat;
}

QMatrix4x4 Camera::createLookAt(const QVector3D &eye, const QVector3D &target, const QVector3D &up)
{
	QVector3D f = eye - target;
	f.normalize();
	QVector3D s = QVector3D::crossProduct(f, up);
	s.normalize();
	QVector3D v = QVector3D::crossProduct(s, f);
	f *= -1;

	QMatrix4x4 V = QMatrix4x4(s.x(), s.y(), s.z(), -QVector3D::dotProduct(s, eye),
		v.x(), v.y(), v.z(), -QVector3D::dotProduct(v, eye),
		f.x(), f.y(), f.z(), QVector3D::dotProduct(f, eye),
		0, 0, 0, 1.0f);
	return V;
	//return createLookAt(eye.x(), eye.y(), eye.z(), center.x(), center.y(), center.z(), up.x(), up.y(), up.z());
}

QVector4D Camera::transform(const QVector4D &point, const QMatrix4x4 &matrix)
{
	return point * matrix;
}

QMatrix4x4 Camera::createTranslation(float x, float y, float z)
{
	QMatrix4x4 translation = {
		1, 0, 0, x,
		0, 1, 0, y,
		0, 0, 1, z,
		0 ,0, 0, 1
	};
	return translation;
}

QMatrix4x4 Camera::createTranslation(const QVector3D &vec)
{
	return createTranslation(vec.x(), vec.y(), vec.z());
}

QMatrix4x4 Camera::createProjection(float width, float heigth, float near, float far, float angle)
{
	float apsectRatio = width / heigth;
	float top = near * tan(M_PI / 180.0f * angle * 0.5f);
	//float top =  near * tan(qDegreesToRadians(angle * 0.5f));
	float bottom = -top;
	float right = top * apsectRatio;
	//float right = 1;
	float left = -right;


	/*QMatrix4x4 projection = {
		2.0f / width, 0, 0, 0,
		0, 2.0f / heigth, 0, 0,
		0, 0, 1 / (far - near),  - near / (far - near),
		0, 0, 0, 1
	};
	return projection;*/
	/*QMatrix4x4 projection = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 1 / PROJECTION_R, 1
	};
	return projection;*/

		//float ar = width / heigth; //aspect ratio
		//float tang = tan(angle * 0.5f);
		//QMatrix4x4 projection =
		//{
		//	1.0f / (ar * tang), 0, 0, 0,
		//	0, 1.0f / tang, 0, 0,
		//	0, 0, (-near - far) / (near - far), 2 * near * far / (near - far),
		//	0, 0, 1.0f, 0
		//};
		//return projection;

	QMatrix4x4 projection =
	{
		2 * near / (right - left), 0, (right + left) / (right - left) , 0,
		0, 2 * near / (top - bottom), (top + bottom) / (top - bottom), 0,
		0, 0, (far + near) / (near - far), 2 * far * near / (near - far),
		0, 0, -1.0f, 0
	};
	return projection;
}

QMatrix4x4 Camera::createStereoProjection(bool isLeft, float width, float heigth, float e, float near, float far, float angle)
{
	float apsectRatio = width / heigth;
	float top = near * tan(M_PI / 180.0f * angle * 0.5f);
	float bottom = -top;
	float left, right;
	float frustumShift = e * 0.5f * near / far;
	if (isLeft)
	{
		left = -top * apsectRatio + frustumShift;
		right = top * apsectRatio + frustumShift;
		QMatrix4x4 projection =
		{
			2 * near / (right - left), 0, (right + left) / (right - left), e * 0.5f,
			0, 2 * near / (top - bottom), (top + bottom) / (top - bottom), 0,
			0, 0, -(far + near) / (far - near), -2 * far*near / (far - near),
			0, 0, -1.0f, 0
		};
		return projection;
	}
	else
	{
		left = -top * apsectRatio - frustumShift;
		right = top * apsectRatio - frustumShift;
		QMatrix4x4 projection =
		{
			2 * near / (right - left), 0, (right + left) / (right - left) , -e * 0.5f,
			0, 2 * near / (top - bottom), (top + bottom) / (top - bottom), 0,
			0, 0, -(far + near) / (far - near), -2 * far*near / (far - near),
			0, 0, -1.0f, 0
		};
		return projection;
	}


	/*if (left)
		e = -e;
	QMatrix4x4 projection = {
		1, 0, e / 2 * r, 0,
		0, 1, 0, 0,
		0, 0, 0, 0,
		0, 0, 1 / r, 1
	};
	return projection;*/
}

QMatrix4x4 Camera::createScaling(float factor)
{
	QMatrix4x4 scaling = {
		factor, 0, 0, 0,
		0, factor, 0, 0,
		0, 0, factor, 0,
		0, 0, 0, 1
	};
	return scaling;
}

QMatrix4x4 Camera::createRotationX(float angle)
{
	float sinus = sin(angle);
	float cosinus = cos(angle);
	QMatrix4x4 rotationX = {
		1 ,0, 0, 0,
		0, cosinus, -sinus, 0,
		0, sinus, cosinus, 0,
		0, 0, 0, 1
	};
	return rotationX;
}

QMatrix4x4 Camera::createRotationY(float angle)
{
	float sinus = sin(angle);
	float cosinus = cos(angle);
	QMatrix4x4 rotationY = {
		cosinus, 0, sinus, 0,
		0, 1, 0, 0,
		-sinus, 0, cosinus, 0,
		0, 0, 0, 1
	};
	return rotationY;
}

QMatrix4x4 Camera::createRotationZ(float angle)
{
	float sinus = sin(angle);
	float cosinus = cos(angle);
	QMatrix4x4 rotationZ = {
		cosinus, -sinus, 0, 0,
		sinus, cosinus, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return rotationZ;
}

QMatrix4x4 Camera::createIdentity()
{
	QMatrix4x4 indentity = {
	   1, 0, 0, 0,
	   0, 1, 0, 0,
	   0, 0, 1, 0,
	   0, 0, 0, 1 };
	return indentity;
}

QVector4D Camera::multiplyByMatrix(const QMatrix4x4 &mat, const QVector4D &vec)
{
	QVector4D vector;
	float x = mat.row(0).w();
	vector.setX(vec.x()*mat.row(0).x() + vec.y()*mat.row(0).y() + vec.z()*mat.row(0).z() + vec.w()*mat.row(0).w());
	vector.setY(vec.x()*mat.row(1).x() + vec.y()*mat.row(1).y() + vec.z()*mat.row(1).z() + vec.w()*mat.row(1).w());
	vector.setZ(vec.x()*mat.row(2).x() + vec.y()*mat.row(2).y() + vec.z()*mat.row(2).z() + vec.w()*mat.row(2).w());
	vector.setW(vec.x()*mat.row(3).x() + vec.y()*mat.row(3).y() + vec.z()*mat.row(3).z() + vec.w()*mat.row(3).w());
	return vector;
}
