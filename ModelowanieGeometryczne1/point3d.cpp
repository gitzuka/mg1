#include "point3d.h"
#include "ui_modelowaniegeometryczne1.h"
#include "bezierCurveC2.h"
#include "uiBezierSurfaceC2.h"

Point3D::Point3D(ObjectType type, QString name, bool enabled) :
	DrawableObject(type, name, enabled)
{
	Point3D::createVertices();
	Point3D::generateIndices();
	//m_color = float3(1, 0, 0);

}

Point3D::Point3D(ObjectType type, QString name, QVector4D position, bool enabled) :
	DrawableObject(type, name, enabled)
{
	m_modelMatrix.setColumn(3, position);
	Point3D::createVertices();
	Point3D::generateIndices();
	m_color = float3(1, 0, 0);
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

//template<class T, class U>
//std::weak_ptr<T>
//static_pointer_cast(std::weak_ptr<U> const& r)
//{
//	return std::static_pointer_cast<T>(std::shared_ptr<U>(r));
//}

void Point3D::setModelMatrix(const QMatrix4x4 &matrix)
{
	m_modelMatrix = matrix;
	/*for (std::unordered_map<int, std::weak_ptr<DrawableObject>>::iterator it = m_ancestors.begin(); it != m_ancestors.end(); ++it)
	{
		if (it->second._Get()->m_type == DrawableObject::ObjectType::bezierCurveC2)
		{
			static_pointer_cast<BezierCurveC2>(it->second)._Get()->pointMoved(it->second._Get()->getId());
		}
	}*/

	/*QVector4D prev = m_center;
	m_center = QVector4D(matrix.column(3).toVector3D(), 1);
	for (std::vector<QVector4D>::iterator it = m_vertices.begin(); it != m_vertices.end(); ++it)
	{
		*it = *it + m_center - prev;
	}
	for (std::unordered_map<int, std::weak_ptr<DrawableObject>>::iterator it = m_ancestors.begin(); it != m_ancestors.end(); ++it)
	{
		if (it->second._Get()->m_type == DrawableObject::ObjectType::bezierCurveC2)
		{
			static_pointer_cast<BezierCurveC2>(it->second)._Get()->pointMoved(it->second._Get()->getId());
		}
	}*/
}

const QMatrix4x4& Point3D::getModelMatrix() const
{
	return m_modelMatrix;
}

void Point3D::setPosition(const QVector4D& point)
{
	m_modelMatrix.setColumn(3, point);
}

void Point3D::setAncestor(std::weak_ptr<DrawableObject> ancestor)
{
	m_ancestors.emplace(ancestor._Get()->getId(), ancestor);
}

//TODO: bezier surface point moved
void Point3D::notifyAncestorsPositionChanged()
{
	for (std::unordered_map<int, std::weak_ptr<DrawableObject>>::iterator it = m_ancestors.begin(); it !=m_ancestors.end(); ++it)
	{
		if (it->second._Get()->m_type == DrawableObject::ObjectType::bezierCurveC2)
		{
			std::static_pointer_cast<BezierCurveC2>(it->second.lock())->pointMoved(this->getId());
		}
		else if (it->second._Get()->m_type == DrawableObject::ObjectType::bezierSurfaceC0)
		{
			std::static_pointer_cast<BezierSurfaceC0>(it->second.lock())->pointMoved(this->getId());
		}
		else if (it->second._Get()->m_type == DrawableObject::ObjectType::bezierSurfaceC2)
		{
			std::static_pointer_cast<BezierSurfaceC2>(it->second.lock())->pointMoved(this->getId());
		}
	}
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