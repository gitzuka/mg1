#pragma once

class float3
{
public:
	float3();
	float3(float, float, float);
	void setX(float);
	void setY(float);
	void setZ(float);
	void setXYZ(float, float, float);
	float x() const;
	float y() const;
	float z() const;
	float3 operator+(const float3& f) const;
	float3 operator-(const float3& f) const;
	float3 operator*(const float3& f) const;
	float3 operator/(const float3& f) const;
private:
	float m_x;
	float m_y;
	float m_z;
};