#include "drawableObject.h"
int DrawableObject::current_id = 0;

DrawableObject::DrawableObject(ObjectType type, QString name)
	: m_type(type), m_color(), m_name(name), m_id(current_id++)
{
}

//void DrawableObject::setCenter(const QVector4D &point)
//{
//	m_center = point;
//}
//
//QVector4D DrawableObject::getCenter() const
//{
//	return QVector4D(m_modelMatrix.row(0).w(), m_modelMatrix.row(1).w(), m_modelMatrix.row(2).w(), 1);
//}

//QVector4D DrawableObject::getPosition() const
//{
//	return QVector4D(m_modelMatrix.row(0).w(), m_modelMatrix.row(1).w(), m_modelMatrix.row(2).w(), 1);
//}

void DrawableObject::setColor(float x, float y, float z)
{
	m_color = float3(x, y, z);
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

int DrawableObject::getId() const
{
	return m_id;
}

const std::vector<QVector4D>& DrawableObject::getVertices() const
{
	return m_vertices;
}

const QString DrawableObject::getName() const
{
	return m_name;
}

void DrawableObject::setName(QString name)
{
	m_name = name;
}

QMatrix4x4 DrawableObject::getModelMatrix()
{
	return m_modelMatrix;
}
