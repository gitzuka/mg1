#include "float3.h"

float3::float3() : m_x(1), m_y(1), m_z(1)
{
}

float3::float3(float x, float y, float z) : m_x(x), m_y(y), m_z(z)
{

}

inline void float3::setX(float x)
{
	m_x = x;
}

inline void float3::setY(float y)
{
	m_y = y;
}

inline void float3::setZ(float z)
{
	m_z = z;
}

inline void float3::setXYZ(float x, float y, float z)
{
	m_x = x;
	m_y = y;
	m_z = z;
}

float float3::x() const
{
	return m_x;
}

float float3::y() const
{
	return m_y;
}

float float3::z() const
{
	return m_z;
}

float3 float3::operator+(const float3 & f) const
{
	float3 vec;
	vec.m_x = this->m_x + f.m_x;
	vec.m_y = this->m_y + f.m_y;
	vec.m_z = this->m_z + f.m_z;
	return vec;
}

float3 float3::operator-(const float3 & f) const
{
	float3 vec;
	vec.m_x = this->m_x - f.m_x;
	vec.m_y = this->m_y - f.m_y;
	vec.m_z = this->m_z - f.m_z;
	return vec;
}

float3 float3::operator*(const float3 & f) const
{
	float3 vec;
	vec.m_x = this->m_x * f.m_x;
	vec.m_y = this->m_y * f.m_y;
	vec.m_z = this->m_z * f.m_z;
	return vec;
}

float3 float3::operator/(const float3 & f) const
{
	float3 vec;
	vec.m_x = this->m_x / f.m_x;
	vec.m_y = this->m_y / f.m_y;
	vec.m_z = this->m_z / f.m_z;
	return vec;
}
