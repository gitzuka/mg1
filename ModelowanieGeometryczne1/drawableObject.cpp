#include "drawableObject.h"
#include "utils.h"
#include "camera.h"
int DrawableObject::current_id = 0;

DrawableObject::DrawableObject(ObjectType type, const QString &name, bool enabled, bool intersectable)
	: m_type(type), m_enabled(enabled), m_color(), m_name(name), m_scale(QVector3D(1, 1, 1)),
	  m_rotation(QQuaternion(1, 0, 0, 0)), m_intersectable(intersectable), m_id(current_id++)
{
}

void DrawableObject::setColor(float x, float y, float z)
{
	m_color = float3(x, y, z);
}

void DrawableObject::setColor(float3 color)
{
	m_color = color;
}

void DrawableObject::drawLine(const QVector4D &p1, const QVector4D &p2, float3 color) const
{
	glLineWidth(LINE_WIDTH);
	glBegin(GL_LINES);
	glColor3f(color.x(), color.y(), color.z());
	glVertex2f(p1.x(), p1.y());
	glVertex2f(p2.x(), p2.y());
	glEnd();
}

void DrawableObject::translate(const QVector4D& vec)
{
	m_modelMatrix.translate(vec.toVector3D());
}

int DrawableObject::getId() const
{
	return m_id;
}

const std::vector<QVector4D>& DrawableObject::getVertices() const
{
	return m_vertices;
}

const QString& DrawableObject::getName() const
{
	return m_name;
}

bool DrawableObject::isIntersectable() const
{
	return m_intersectable;
}

void DrawableObject::setName(const QString &name)
{
	m_name = name;
}

QVector3D DrawableObject::getPosition() const
{
	return QVector3D(m_modelMatrix.row(0).w(), m_modelMatrix.row(1).w(), m_modelMatrix.row(2).w());
}

QVector3D DrawableObject::getRotation() const
{
	return m_rotation.toEulerAngles();
}

void DrawableObject::rotate(QVector3D eulerAngles)
{
	/*QQuaternion q1 = QQuaternion::fromAxisAndAngle(QVector3D(1,0,0), eulerAngles.x());
	QQuaternion q2 = QQuaternion::fromAxisAndAngle(QVector3D(0, 1, 0), eulerAngles.y());
	QQuaternion q3 = QQuaternion::fromAxisAndAngle(QVector3D(0, 0, 1), eulerAngles.z());*/
	//m_rotation = (q1 * q2 * q3).normalized();
	m_rotation = QQuaternion::fromEulerAngles(eulerAngles).normalized();
	m_modelMatrix = Camera::createTranslation(m_pos) * QMatrix4x4(m_rotation.toRotationMatrix()) * Camera::createScaling(m_scale);
}

void DrawableObject::setPosition(QVector3D pos)
{
	m_pos = pos;
	m_modelMatrix = Camera::createTranslation(m_pos) * QMatrix4x4(m_rotation.toRotationMatrix()) * Camera::createScaling(m_scale);
}

void DrawableObject::setScale(QVector3D scale)
{
	m_scale = scale;
	m_modelMatrix = Camera::createTranslation(m_pos)* QMatrix4x4(m_rotation.toRotationMatrix()) * Camera::createScaling(m_scale);
}

const QMatrix4x4& DrawableObject::getModelMatrix() const
{
	return m_modelMatrix;
}
