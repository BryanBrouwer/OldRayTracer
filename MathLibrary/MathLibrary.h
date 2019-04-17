#pragma once
#include <cmath>
class vec2
{
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union {
		struct
		{
			float m_X;
			float m_Y;
		};
		float v[2];
	};
#pragma warning(pop)

public:
	vec2();
	vec2(float a_X, float a_Y);

	vec2& operator=(const vec2& rhs);

	vec2& operator+=(const vec2 &a_Rhs);
	vec2& operator-=(const vec2 &a_Rhs);
	vec2& operator*=(float a_Rhs);
	vec2& operator/=(float a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	inline float dot(vec2 const& a_Rhs) const
	{
		return (m_X * a_Rhs.m_X + m_Y * a_Rhs.m_Y);
	}

	vec2& normalize();
	inline float length() const
	{
		return sqrt(m_X*m_X + m_Y * m_Y);
	}
};

vec2 operator+(const vec2 &a_Lhs, const vec2 &a_Rhs);
vec2 operator-(const vec2 &a_Lhs, const vec2 &a_Rhs);
vec2 operator*(const vec2 &a_Lhs, float a_Rhs);
vec2 operator/(const vec2 &a_Lhs, float a_Rhs);
bool operator==(const vec2 &a_Lhs, const vec2 &a_Rhs);
bool operator!=(const vec2 &a_Lhs, const vec2 &a_Rhs);

class vec3 {
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union {
		struct
		{
			float m_X;
			float m_Y;
			float m_Z;
		};
		float v[3];
	};
#pragma warning(pop)

public:
	vec3();
	vec3(float a_X, float a_Y, float a_Z);

	vec3& operator=(const vec3& rhs);

	vec3& operator+=(const vec3 &a_Rhs);
	vec3& operator-=(const vec3 &a_Rhs);
	vec3& operator*=(float a_Rhs);
	vec3& operator/=(float a_Rhs);

	float operator[](int a_Index) const;
	float& operator[](int a_Index);

	inline float dot(vec3 const& a_Rhs) const
	{
		return (m_X * a_Rhs.m_X + m_Y * a_Rhs.m_Y + m_Z * a_Rhs.m_Z);
	}
	inline vec3 cross(vec3 const& a_Rhs) const
	{
		float cX, cY, cZ;
		cX = this->m_Y * a_Rhs.m_Z - this->m_Z * a_Rhs.m_Y;
		cY = this->m_Z * a_Rhs.m_X - this->m_X * a_Rhs.m_Z;
		cZ = this->m_X * a_Rhs.m_Y - this->m_Y * a_Rhs.m_X;

		return vec3(cX, cY, cZ);
	}
	vec3& normalize();
	inline float length() const
	{
		return sqrt(m_X*m_X + m_Y * m_Y + m_Z * m_Z);
	}
};

vec3 operator+(const vec3 &a_Lhs, const vec3 &a_Rhs);
vec3 operator-(const vec3 &a_Lhs, const vec3 &a_Rhs);
vec3 operator*(const vec3 &a_Lhs, float a_Rhs);
vec3 operator/(const vec3 &a_Lhs, float a_Rhs);
bool operator==(const vec3 &a_Lhs, const vec3 &a_Rhs);
bool operator!=(const vec3 &a_Lhs, const vec3 &a_Rhs);

class mat4
{
public:
#pragma warning(push)
#pragma warning(disable : 4201)
	union {
		struct
		{
			float m_00; float m_01; float m_02; float m_03;
			float m_10; float m_11; float m_12; float m_13;
			float m_20; float m_21; float m_22; float m_23;
			float m_30; float m_31; float m_32; float m_33;
		};
		float m[16];
	};
#pragma warning(pop)

public:
	mat4();
	mat4(vec3 a_Row0, float a_03,
		vec3 a_Row1, float a_13,
		vec3 a_Row2, float a_23,
		vec3 a_Row3, float a_33);
	mat4(float a_00, float a_01, float a_02, float a_03,
		float a_10, float a_11, float a_12, float a_13,
		float a_20, float a_21, float a_22, float a_23,
		float a_30, float a_31, float a_32, float a_33);

	mat4& operator=(const mat4& rhs);

	mat4& operator+=(const mat4 &a_Rhs);
	mat4& operator-=(const mat4 &a_Rhs);
	mat4& operator*=(const mat4 &a_Rhs);
	mat4& operator*=(float a_Rhs);

	float determinant() const;
	inline mat4& inverse()
	{
		float d;
		d = determinant();

		mat4 temp = mat4();
		temp.m[0] = m_12 * m_23*m_31 - m_13 * m_22*m_31 + m_13 * m_21*m_32 - m_11 * m_23*m_32 - m_12 * m_21*m_33 + m_11 * m_22*m_33;
		temp.m[1] = m_03 * m_22*m_31 - m_02 * m_23*m_31 - m_03 * m_21*m_32 + m_01 * m_23*m_32 + m_02 * m_21*m_33 - m_01 * m_22*m_33;
		temp.m[2] = m_02 * m_13*m_31 - m_03 * m_12*m_31 + m_03 * m_11*m_32 - m_01 * m_13*m_32 - m_02 * m_11*m_33 + m_01 * m_12*m_33;
		temp.m[3] = m_03 * m_12*m_21 - m_02 * m_13*m_21 - m_03 * m_11*m_22 + m_01 * m_13*m_22 + m_02 * m_11*m_23 - m_01 * m_12*m_23;
		temp.m[4] = m_13 * m_22*m_30 - m_12 * m_23*m_30 - m_13 * m_20*m_32 + m_10 * m_23*m_32 + m_12 * m_20*m_33 - m_10 * m_22*m_33;
		temp.m[5] = m_02 * m_23*m_30 - m_03 * m_22*m_30 + m_03 * m_20*m_32 - m_00 * m_23*m_32 - m_02 * m_20*m_33 + m_00 * m_22*m_33;
		temp.m[6] = m_03 * m_12*m_30 - m_02 * m_13*m_30 - m_03 * m_10*m_32 + m_00 * m_13*m_32 + m_02 * m_10*m_33 - m_00 * m_12*m_33;
		temp.m[7] = m_02 * m_13*m_20 - m_03 * m_12*m_20 + m_03 * m_10*m_22 - m_00 * m_13*m_22 - m_02 * m_10*m_23 + m_00 * m_12*m_23;
		temp.m[8] = m_11 * m_23*m_30 - m_13 * m_21*m_30 + m_13 * m_20*m_31 - m_10 * m_23*m_31 - m_11 * m_20*m_33 + m_10 * m_21*m_33;
		temp.m[9] = m_03 * m_21*m_30 - m_01 * m_23*m_30 - m_03 * m_20*m_31 + m_00 * m_23*m_31 + m_01 * m_20*m_33 - m_00 * m_21*m_33;
		temp.m[10] = m_01 * m_13*m_30 - m_03 * m_11*m_30 + m_03 * m_10*m_31 - m_00 * m_13*m_31 - m_01 * m_10*m_33 + m_00 * m_11*m_33;
		temp.m[11] = m_03 * m_11*m_20 - m_01 * m_13*m_20 - m_03 * m_10*m_21 + m_00 * m_13*m_21 + m_01 * m_10*m_23 - m_00 * m_11*m_23;
		temp.m[12] = m_12 * m_21*m_30 - m_11 * m_22*m_30 - m_12 * m_20*m_31 + m_10 * m_22*m_31 + m_11 * m_20*m_32 - m_10 * m_21*m_32;
		temp.m[13] = m_01 * m_22*m_30 - m_02 * m_21*m_30 + m_02 * m_20*m_31 - m_00 * m_22*m_31 - m_01 * m_20*m_32 + m_00 * m_21*m_32;
		temp.m[14] = m_02 * m_11*m_30 - m_01 * m_12*m_30 - m_02 * m_10*m_31 + m_00 * m_12*m_31 + m_01 * m_10*m_32 - m_00 * m_11*m_32;
		temp.m[15] = m_01 * m_12*m_20 - m_02 * m_11*m_20 + m_02 * m_10*m_21 - m_00 * m_12*m_21 - m_01 * m_10*m_22 + m_00 * m_11*m_22;

		temp *= (1 / d);

		for (int i = 0; i < 16; i++)
		{
			m[i] = temp.m[i];
		}
		return *this;
	}

	static mat4 identity();
	static mat4 rotateX(float a_Radians);
	static mat4 rotateY(float a_Radians);
	static mat4 rotateZ(float a_Radians);
	static mat4 translate(const vec3 &a_Translation);

	static mat4 lookat(const vec3 &a_Eye, const vec3 &a_Center, const vec3 &a_Up);
	static mat4 projection(float a_FovY, float a_AspectRatio, float a_Near, float a_Far);
};

mat4 operator+(const mat4 &a_Lhs, const mat4 &a_Rhs);
mat4 operator-(const mat4 &a_Lhs, const mat4 &a_Rhs);
mat4 operator*(const mat4 &a_Lhs, const mat4 &a_Rhs);
vec3 operator*(const mat4 &a_Lhs, const vec3 &a_Rhs);
