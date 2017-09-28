#include "point3d.h"

Point3D::Point3D(ObjectType type, QString name, const QMatrix4x4 &projMatrix) :
	DrawableObject(type, name), m_projMatrix(projMatrix), m_uiPoint3D(*this)
{
	Point3D::createVertices();
	Point3D::generateIndices();
}

void Point3D::draw(std::vector<QVector4D>& vec) const
{
	draw(vec, m_color);
	
}

void Point3D::draw(std::vector<QVector4D>& vec, float3 color) const
{
	for (std::vector<int>::const_iterator it = m_indices.begin(); it != m_indices.end(); ++it)
	{
		if (*it == -1 || *(it + 1) == -1
			|| vec.at(*it).z() <= CAM_NEAR || vec.at(*(it + 1)).z() <= CAM_NEAR
			|| vec.at(*it).z() > 1 || vec.at(*(it + 1)).z() > 1)
		{
			continue;
		}
		//drawLine(m_projMatrix.inverted() * vec.at(*it), m_projMatrix.inverted() * vec.at(*(it + 1)), color);
		drawLine(vec.at(*it), vec.at(*(it + 1)), color);
	}
}

void Point3D::setModelMatrix(const QMatrix4x4 &matrix)
{
	//m_modelMatrix = matrix;
	m_center = matrix.column(3).toVector3D();
}

QMatrix4x4 Point3D::getModelMatrix()
{
	QMatrix4x4 mat = m_modelMatrix;
	mat.setColumn(3, m_modelMatrix.column(3) + m_center);
	return mat;
}

QVector4D Point3D::getPosition() const
{
	return QVector4D(m_center);
}

void Point3D::setCenter(const QVector3D &point)
{
	m_center = point;
}

QVector3D Point3D::getCenter() const
{
	return m_center;
}

void Point3D::createVertices()
{
	m_vertices.push_back(QVector4D(0.001, 0.001, 0.001, 1));
	m_vertices.push_back(QVector4D(0.001, -0.001, 0.001, 1));
	m_vertices.push_back(QVector4D(-0.001, -0.001, 0.001, 1));
	m_vertices.push_back(QVector4D(-0.001, 0.001, 0.001, 1));
	m_vertices.push_back(QVector4D(0.001, 0.001, -0.001, 1));
	m_vertices.push_back(QVector4D(0.001, -0.001, -0.001, 1));
	m_vertices.push_back(QVector4D(-0.001, -0.001, -0.001, 1));
	m_vertices.push_back(QVector4D(-0.001, 0.001, -0.001, 1));
}

void Point3D::generateIndices()
{
	m_indices.push_back(0);
	m_indices.push_back(1);
	m_indices.push_back(2);
	m_indices.push_back(3);
	m_indices.push_back(0);
	m_indices.push_back(-1);
	m_indices.push_back(4);
	m_indices.push_back(5);
	m_indices.push_back(6);
	m_indices.push_back(7);
	m_indices.push_back(4);
	m_indices.push_back(0);
	m_indices.push_back(-1);
	m_indices.push_back(1);
	m_indices.push_back(5);
	m_indices.push_back(-1);
	m_indices.push_back(2);
	m_indices.push_back(6);
	m_indices.push_back(-1);
	m_indices.push_back(3);
	m_indices.push_back(7);
	m_indices.push_back(-1);
}