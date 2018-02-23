#include "point3d.h"
#include "ui_modelowaniegeometryczne1.h"

Point3D::Point3D(ObjectType type, QString name, const QMatrix4x4 &projMatrix, const QMatrix4x4 &viewMatrix) :
	DrawableObject(type, name), m_projMatrix(projMatrix), m_viewMatrix(viewMatrix), m_uiPoint3D(*this), m_center(QVector4D(0, 0, 0, 1))
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
		drawLine(vec.at(*it), vec.at(*(it + 1)), color);
	}
}

void Point3D::setModelMatrix(const QMatrix4x4 &matrix)
{
	QVector4D prev = m_center;
	m_center = QVector4D(matrix.column(3).toVector3D(), 1);
	for (std::vector<QVector4D>::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		*it = *it + m_center - prev;
	}
	//m_modelMatrix = matrix;
	//m_modelMatrix.setColumn(3, m_modelMatrix.column(3) + QVector3D(m_center) - prev);
}

const QMatrix4x4& Point3D::getModelMatrix() const
{
	//QMatrix4x4 mat = m_modelMatrix;
	//QVector4D center = m_projMatrix * m_viewMatrix *m_modelMatrix * m_center;
	//mat.setColumn(3, m_modelMatrix.column(3) + QVector3D(m_center));
	//mat.setColumn(3, m_modelMatrix.column(3) + QVector3D(center));
	//return mat;
	return m_modelMatrix;
}

QVector4D Point3D::getPosition() const
{
	return m_center;// +m_modelMatrix.column(3).toVector3D();
}

void Point3D::connectToUI(const Ui_ModelowanieGeometryczne1Class ui) const
{
	m_uiPoint3D.connect(ui.listWidget_Parameters, ui.listWidget_ObjectsList);
}

//void Point3D::setCenter(const QVector3D &point)
//{
//	//m_center = point;
//	m_modelMatrix.column(3).setX(point.x());
//	m_modelMatrix.column(3).setY(point.y());
//	m_modelMatrix.column(3).setZ(point.z());
//}

void Point3D::setCenter(const QMatrix4x4 &matrix)
{
	m_modelMatrix = matrix;
	//m_modelMatrix.setColumn(3, m_modelMatrix.column(3) + QVector3D(m_center));
	//m_center = m_modelMatrix * m_center;
	//m_center = m_projMatrix * m_viewMatrix *m_modelMatrix * m_center;
}

const QVector4D& Point3D::getCenter() const
{
	return m_center;
}

void Point3D::connectToUI(ListWidgetParameters* listWidget, ListWidgetObjects* listWidgetObj) const
{
	m_uiPoint3D.connect(listWidget, listWidgetObj);
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