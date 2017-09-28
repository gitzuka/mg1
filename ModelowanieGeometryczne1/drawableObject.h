#pragma once
#include <QtOpenGL>
#include "utils.h"
#include "float3.h"


class DrawableObject
{
public:
	virtual ~DrawableObject() {}

	enum ObjectType { torus, point3D, cursor3D, bezierCurveC0 };
	
	const ObjectType m_type;

	virtual void draw(std::vector<QVector4D> &vec) const = 0;
	virtual void draw(std::vector<QVector4D> &vec, float3 color) const = 0;
	virtual void setModelMatrix(const QMatrix4x4 &matrix) = 0;
	virtual QVector4D getPosition() const = 0;
	virtual QMatrix4x4 getModelMatrix();


	//void setCenter(const QVector4D &point);
	//QVector4D getPosition() const;
	void setColor(float r, float g, float b);
	void drawLine(const QVector4D &p1, const QVector4D &p2, float3 color) const;
	int getId() const;
	const std::vector<QVector4D>& getVertices() const;
	const QString getName() const;
	void setName(QString name);
	

protected:
	DrawableObject(ObjectType type, QString name);

	std::vector<QVector4D> m_vertices;
	std::vector<int> m_indices;
	float3 m_color;
	QString m_name;
	QMatrix4x4 m_modelMatrix;

	virtual void createVertices() = 0;
	virtual void generateIndices() = 0;

private:
	//QVector4D m_center;
	static int current_id;
	int m_id;
};