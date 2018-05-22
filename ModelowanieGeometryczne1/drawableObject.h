#pragma once
#include <QtOpenGL>
#include "float3.h"

class DrawableObject
{
public:
	virtual ~DrawableObject() {}

	enum class ObjectType { torus, point3D, cursor3D, bezierCurveC0, bezierCurveC2 };
	
	const ObjectType m_type;
	bool m_enabled;

	virtual void draw(std::vector<QVector4D> &vec) const = 0;
	virtual void draw(std::vector<QVector4D> &vec, float3 color) const = 0;
	virtual void setModelMatrix(const QMatrix4x4 &matrix) = 0;
	virtual QVector4D getPosition() const = 0;
	virtual const QMatrix4x4& getModelMatrix() const;

	void setColor(float r, float g, float b);
	void setColor(float3 color);
	void drawLine(const QVector4D &p1, const QVector4D &p2, float3 color) const;
	void translate(const QVector4D &vec);
	int getId() const;
	const std::vector<QVector4D>& getVertices() const;
	const QString& getName() const;
	void setName(const QString &name);
	

protected:
	DrawableObject(ObjectType type, const QString &name, bool enabled = true);

	std::vector<QVector4D> m_vertices;
	std::vector<int> m_indices;
	float3 m_color;
	QString m_name;
	QMatrix4x4 m_modelMatrix;

	virtual void createVertices() = 0;
	virtual void generateIndices() = 0;

private:
	static int current_id;
	int m_id;
};
