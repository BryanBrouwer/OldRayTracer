#include "MathLibrary.h"


using namespace std;

vec2::vec2()
{
	m_X = 0.f;
	m_Y = 0.f;
}

vec2::vec2(float a_X, float a_Y)
{
	m_X = a_X;
	m_Y = a_Y;
}

vec2 & vec2::operator=(const vec2 & rhs)
{
	m_X = rhs.m_X;
	m_Y = rhs.m_Y;
	return *this;
}

vec2 & vec2::operator+=(const vec2 & a_Rhs)
{
	m_X += a_Rhs.m_X;
	m_Y += a_Rhs.m_Y;
	return *this;
}

vec2 & vec2::operator-=(const vec2 & a_Rhs)
{
	m_X -= a_Rhs.m_X;
	m_Y -= a_Rhs.m_Y;
	return *this;
}

vec2 & vec2::operator*=(float a_Rhs)
{
	m_X *= a_Rhs;
	m_Y *= a_Rhs;
	return *this;
}

vec2 & vec2::operator/=(float a_Rhs)
{
	m_X /= a_Rhs;
	m_Y /= a_Rhs;
	return *this;
}

float vec2::operator[](int a_Index) const
{
	return v[a_Index];
}

float & vec2::operator[](int a_Index)
{
	return v[a_Index];
}

//inline float vec2::dot(vec2 const & a_Rhs) const


//inline float vec2::length() const
//{
//	return sqrt(m_X*m_X + m_Y * m_Y);
//}

vec2 & vec2::normalize()
{
	float l = length();
	m_X /= l;
	m_Y /= l;
	return *this;
}

vec2 operator+(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	return vec2(a_Lhs.m_X + a_Rhs.m_X, a_Lhs.m_Y + a_Rhs.m_Y);
}

vec2 operator-(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	return vec2(a_Lhs.m_X - a_Rhs.m_X, a_Lhs.m_Y - a_Rhs.m_Y);
}

vec2 operator*(const vec2 & a_Lhs, float a_Rhs)
{
	return vec2(a_Lhs.m_X * a_Rhs, a_Lhs.m_Y * a_Rhs);
}

vec2 operator/(const vec2 & a_Lhs, float a_Rhs)
{
	return vec2(a_Lhs.m_X / a_Rhs, a_Lhs.m_Y / a_Rhs);
}

bool operator==(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	if (a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y)
	{
		return true;
	}

	return false;
}

bool operator!=(const vec2 & a_Lhs, const vec2 & a_Rhs)
{
	if (a_Lhs.m_X != a_Rhs.m_X && a_Lhs.m_Y != a_Rhs.m_Y)
	{
		return true;
	}
	return false;
}

vec3 operator+(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return vec3(a_Lhs.m_X + a_Rhs.m_X, a_Lhs.m_Y + a_Rhs.m_Y, a_Lhs.m_Z + a_Rhs.m_Z);
}

vec3 operator-(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	return vec3(a_Lhs.m_X - a_Rhs.m_X, a_Lhs.m_Y - a_Rhs.m_Y, a_Lhs.m_Z - a_Rhs.m_Z);
}

vec3 operator*(const vec3 & a_Lhs, float a_Rhs)
{
	return vec3(a_Lhs.m_X * a_Rhs, a_Lhs.m_Y * a_Rhs, a_Lhs.m_Z * a_Rhs);
}

vec3 operator/(const vec3 & a_Lhs, float a_Rhs)
{
	return vec3(a_Lhs.m_X / a_Rhs, a_Lhs.m_Y / a_Rhs, a_Lhs.m_Z / a_Rhs);
}

bool operator==(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	if (a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y && a_Lhs.m_Z == a_Rhs.m_Z)
	{
		return true;
	}
	return false;
}

bool operator!=(const vec3 & a_Lhs, const vec3 & a_Rhs)
{
	if (a_Lhs.m_X == a_Rhs.m_X && a_Lhs.m_Y == a_Rhs.m_Y && a_Lhs.m_Z == a_Rhs.m_Z)
	{
		return false;
	}
	return true;
}

mat4 operator+(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	mat4 temp = mat4();
	for (int i = 0; i < 16; i++)
	{
		temp.m[i] = a_Lhs.m[i] + a_Rhs.m[i];
	}
	return temp;
}

mat4 operator-(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	mat4 temp = mat4();
	for (int i = 0; i < 16; i++)
	{
		temp.m[i] = a_Lhs.m[i] - a_Rhs.m[i];
	}
	return temp;
}

mat4 operator*(const mat4 & a_Lhs, const mat4 & a_Rhs)
{
	mat4 temp = mat4();
	for (int i = 0; i < 4; i++)
	{
		temp.m[i] = a_Lhs.m[0] * a_Rhs.m[i] + a_Lhs.m[1] * a_Rhs.m[i + 4] + a_Lhs.m[2] * a_Rhs.m[i + 8] + a_Lhs.m[3] * a_Rhs.m[i + 12];
		temp.m[i + 4] = a_Lhs.m[4] * a_Rhs.m[i] + a_Lhs.m[5] * a_Rhs.m[i + 4] + a_Lhs.m[6] * a_Rhs.m[i + 8] + a_Lhs.m[7] * a_Rhs.m[i + 12];
		temp.m[i + 8] = a_Lhs.m[8] * a_Rhs.m[i] + a_Lhs.m[9] * a_Rhs.m[i + 4] + a_Lhs.m[10] * a_Rhs.m[i + 8] + a_Lhs.m[11] * a_Rhs.m[i + 12];
		temp.m[i + 12] = a_Lhs.m[12] * a_Rhs.m[i] + a_Lhs.m[13] * a_Rhs.m[i + 4] + a_Lhs.m[14] * a_Rhs.m[i + 8] + a_Lhs.m[15] * a_Rhs.m[i + 12];
	}
	return temp;
}

vec3 operator*(const mat4 & a_Lhs, const vec3 & a_Rhs)
{
	//float temp[4];
	//vec3 tempvec3;
	//temp[0] = a_Rhs.v[0];
	//temp[1] = a_Rhs.v[1];
	//temp[2] = a_Rhs.v[2];
	//temp[3] = 1.f;

	//tempvec3.v[0] = temp[0] * a_Lhs.m[0] + temp[1] * a_Lhs.m[4] + temp[2] * a_Lhs.m[8] + temp[3] * a_Lhs.m[12];
	//tempvec3.v[1] = temp[0] * a_Lhs.m[1] + temp[1] * a_Lhs.m[5] + temp[2] * a_Lhs.m[9] + temp[3] * a_Lhs.m[13];
	//tempvec3.v[2] = temp[0] * a_Lhs.m[2] + temp[1] * a_Lhs.m[6] + temp[2] * a_Lhs.m[10] + temp[3] * a_Lhs.m[14];


	//return tempvec3;

	const float vec[4]{ a_Rhs.v[0],a_Rhs.v[1],a_Rhs.v[2], 1.f };
	float returner[4];

	for (int r = 0; r < 4; r++)
	{
		// Create the 2 vec that will be dotted
		float operation[4];
		for (int c = 0; c < 4; c++)
			operation[c] = a_Lhs.m[c + r * 4];

		// Dot the 2 vec and put result in correct row
		float dot = 0;
		for (int i = 0; i < 4; i++)
			dot += vec[i] * operation[i];
		returner[r] = dot;
	}

	return vec3(returner[0], returner[1], returner[2]);
}

vec3::vec3()
{
	m_X = 0.f;
	m_Y = 0.f;
	m_Z = 0.f;
}

vec3::vec3(float a_X, float a_Y, float a_Z)
{
	m_X = a_X;
	m_Y = a_Y;
	m_Z = a_Z;
}

vec3 & vec3::operator=(const vec3 & rhs)
{
	m_X = rhs.m_X;
	m_Y = rhs.m_Y;
	m_Z = rhs.m_Z;
	return *this;
}

vec3 & vec3::operator+=(const vec3 & a_Rhs)
{
	m_X += a_Rhs.m_X;
	m_Y += a_Rhs.m_Y;
	m_Z += a_Rhs.m_Z;
	return *this;
}

vec3 & vec3::operator-=(const vec3 & a_Rhs)
{
	m_X -= a_Rhs.m_X;
	m_Y -= a_Rhs.m_Y;
	m_Z -= a_Rhs.m_Z;
	return *this;
}

vec3 & vec3::operator*=(float a_Rhs)
{
	m_X *= a_Rhs;
	m_Y *= a_Rhs;
	m_Z *= a_Rhs;
	return *this;
}

vec3 & vec3::operator/=(float a_Rhs)
{
	m_X /= a_Rhs;
	m_Y /= a_Rhs;
	m_Z /= a_Rhs;
	return *this;
}

float vec3::operator[](int a_Index) const
{
	return v[a_Index];
}

float & vec3::operator[](int a_Index)
{
	return v[a_Index];
}

//inline float vec3::dot(vec3 const & a_Rhs) const
//{
//	return (m_X * a_Rhs.m_X + m_Y * a_Rhs.m_Y + m_Z * a_Rhs.m_Z);
//}

//inline vec3 vec3::cross(vec3 const & a_Rhs) const
//{
//	float cX, cY, cZ;
//	cX = this->m_X * a_Rhs.m_Z - this->m_Z * a_Rhs.m_Y;
//	cY = this->m_Z * a_Rhs.m_X - this->m_X * a_Rhs.m_Z;
//	cZ = this->m_X * a_Rhs.m_Y - this->m_Y * a_Rhs.m_X;
//
//	return vec3(cX, cY, cZ);
//}

//inline float vec3::length() const
//{
//	return sqrt(m_X*m_X + m_Y * m_Y + m_Z * m_Z);
//}


vec3 & vec3::normalize()
{
	float l = length();
	m_X /= l;
	m_Y /= l;
	m_Z /= l;
	return *this;
}


mat4::mat4()
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = 0;
	}
}

mat4::mat4(vec3 a_Row0, float a_03, vec3 a_Row1, float a_13, vec3 a_Row2, float a_23, vec3 a_Row3, float a_33)
{
	vec3 vecList[4];	//small array for easy adding everything to the matrix
	float floatList[4]; //
	vecList[0] = a_Row0;
	vecList[1] = a_Row1;
	vecList[2] = a_Row2;
	vecList[3] = a_Row3;

	floatList[0] = a_03;
	floatList[1] = a_13;
	floatList[2] = a_23;
	floatList[3] = a_33;

	for (int row = 0; row < 4; row++)
	{
		for (int j = 0; j < 3; j++)
		{
			m[row * 4 + j] = vecList[row].v[j];
			m[row * 4 + 3] = floatList[row];
		}
	}
	m[0] = a_Row0.v[0];

}

mat4::mat4(float a_00, float a_01, float a_02, float a_03, float a_10, float a_11, float a_12, float a_13, float a_20, float a_21, float a_22, float a_23, float a_30, float a_31, float a_32, float a_33)
{
	m[0] = a_00;
	m[1] = a_01;
	m[2] = a_02;
	m[3] = a_03;
	m[4] = a_10;
	m[5] = a_11;
	m[6] = a_12;
	m[7] = a_13;
	m[8] = a_20;
	m[9] = a_21;
	m[10] = a_22;
	m[11] = a_23;
	m[12] = a_30;
	m[13] = a_31;
	m[14] = a_32;
	m[15] = a_33;
}

mat4 & mat4::operator=(const mat4 & rhs)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] = rhs.m[i];
	}
	return *this;
}

mat4 & mat4::operator+=(const mat4 & a_Rhs)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] += a_Rhs.m[i];
	}
	return *this;
}

mat4 & mat4::operator-=(const mat4 & a_Rhs)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] -= a_Rhs.m[i];
	}
	return *this;
}

mat4 & mat4::operator*=(const mat4 & a_Rhs)
{
	mat4 temp = mat4();
	for (int i = 0; i < 4; i++)
	{
		temp.m[i] = m[0] * a_Rhs.m[i] + m[1] * a_Rhs.m[i + 4] + m[2] * a_Rhs.m[i + 8] + m[3] * a_Rhs.m[i + 12];
		temp.m[i + 4] = m[4] * a_Rhs.m[i] + m[5] * a_Rhs.m[i + 4] + m[6] * a_Rhs.m[i + 8] + m[7] * a_Rhs.m[i + 12];
		temp.m[i + 8] = m[8] * a_Rhs.m[i] + m[9] * a_Rhs.m[i + 4] + m[10] * a_Rhs.m[i + 8] + m[11] * a_Rhs.m[i + 12];
		temp.m[i + 12] = m[12] * a_Rhs.m[i] + m[13] * a_Rhs.m[i + 4] + m[14] * a_Rhs.m[i + 8] + m[15] * a_Rhs.m[i + 12];
	}
	for (int i = 0; i < 16; i++)
	{
		m[i] = temp.m[i];
	}
	return *this;
}

mat4 & mat4::operator*=(float a_Rhs)
{
	for (int i = 0; i < 16; i++)
	{
		m[i] *= a_Rhs;
	}
	return *this;
}

float mat4::determinant() const
{
	//float determinant, a, b, c, d;
//a = ( (m[0]) *	((m[5]) * ((m[10] * m[15]) - (m[11] * m[14])))		- ((m[6]) * ((m[9] * m[15]) - (m[11] * m[13])))		+ ((m[7]) * ((m[9] * m[14]) - (m[10] * m[13])))	);
//b = ( (m[1]) *	((m[4]) * ((m[10] * m[15]) - (m[11] * m[14])))		- ((m[6]) * ((m[8] * m[15]) - (m[11] * m[12])))		+ ((m[7]) * ((m[8] * m[14]) - (m[10] * m[12])))	);
//c = ( (m[2]) *	((m[4]) * ((m[9] * m[15]) - (m[11] * m[13])))		- ((m[5]) * ((m[8] * m[15]) - (m[11] * m[12])))		+ ((m[7]) * ((m[8] * m[13]) - (m[9] * m[12])))	);
//d = ( (m[3]) *	((m[4]) * ((m[9] * m[14]) - (m[10] * m[13])))		- ((m[5]) * ((m[8] * m[14]) - (m[10] * m[12])))		+ ((m[6]) * ((m[8] * m[13]) - (m[9] * m[12])))	);
//determinant = a - b + c - d;
//return determinant;
	//mine didn't work so i looked one up on the internet and now i can see i missed some bits

	float value;
	value =
		m_03 * m_12 * m_21 * m_30 - m_02 * m_13 * m_21 * m_30 - m_03 * m_11 * m_22 * m_30 + m_01 * m_13 * m_22 * m_30 +
		m_02 * m_11 * m_23 * m_30 - m_01 * m_12 * m_23 * m_30 - m_03 * m_12 * m_20 * m_31 + m_02 * m_13 * m_20 * m_31 +
		m_03 * m_10 * m_22 * m_31 - m_00 * m_13 * m_22 * m_31 - m_02 * m_10 * m_23 * m_31 + m_00 * m_12 * m_23 * m_31 +
		m_03 * m_11 * m_20 * m_32 - m_01 * m_13 * m_20 * m_32 - m_03 * m_10 * m_21 * m_32 + m_00 * m_13 * m_21 * m_32 +
		m_01 * m_10 * m_23 * m_32 - m_00 * m_11 * m_23 * m_32 - m_02 * m_11 * m_20 * m_33 + m_01 * m_12 * m_20 * m_33 +
		m_02 * m_10 * m_21 * m_33 - m_00 * m_12 * m_21 * m_33 - m_01 * m_10 * m_22 * m_33 + m_00 * m_11 * m_22 * m_33;
	return value;
}


mat4 mat4::identity()
{
	mat4 temp = mat4();
	temp.m[0] = 1;
	temp.m[5] = 1;
	temp.m[10] = 1;
	temp.m[15] = 1;

	return temp;
}
	//rotations can quite easily be gotten from using a unit circle 
mat4 mat4::rotateX(float a_Radians)
{
	mat4 temp = mat4();
	temp.m_00 = 1;
	temp.m_33 = 1;
	temp.m_11 = cos(a_Radians);
	temp.m_12 = -1.f * sin(a_Radians);
	temp.m_21 = sin(a_Radians);
	temp.m_22 = cos(a_Radians);
	return temp;
}

mat4 mat4::rotateY(float a_Radians)
{
	mat4 temp = mat4();
	temp.m_11 = 1;
	temp.m_33 = 1;
	temp.m_00 = cos(a_Radians);
	temp.m_20 = -1.f * sin(a_Radians);
	temp.m_02 = sin(a_Radians);
	temp.m_22 = cos(a_Radians);
	return temp;
}

mat4 mat4::rotateZ(float a_Radians)
{
	mat4 temp = mat4();
	temp.m_22 = 1;
	temp.m_33 = 1;
	temp.m_00 = cos(a_Radians);
	temp.m_01 = -1.f * sin(a_Radians);
	temp.m_10 = sin(a_Radians);
	temp.m_11 = cos(a_Radians);
	return temp;
}

mat4 mat4::translate(const vec3 & a_Translation)
{
	mat4 r(1, 0, 0, a_Translation.m_X, 0, 1, 0, a_Translation.m_Y, 0, 0, 1, a_Translation.m_Z, 0, 0, 0, 1);
	return r;
}

mat4 mat4::lookat(const vec3 & a_Eye, const vec3 & a_Center, const vec3 & a_Up)
{
	vec3 x, y, z;
	z = (a_Center - a_Eye).normalize();	//forward vector
	x = (a_Up.cross(z)).normalize();	//right vector
	y = z.cross(x);						//up vector
	mat4 temp = mat4(-x.m_X, y.m_X, z.m_X, 0.0f,
		x.m_Y, y.m_Y, -z.m_Y, 0.0f,
		x.m_Z, y.m_Z, -z.m_Z, 0.0f,
		-x.dot(a_Eye), -y.dot(a_Eye), z.dot(a_Eye), 1.0f);
		return temp;
}

mat4 mat4::projection(float a_FovY, float a_AspectRatio, float a_Near, float a_Far)
{
	float width = 1 / (tanf(a_FovY * 0.5f) * a_AspectRatio);
	float height = 1 / tanf(a_FovY * 0.5f);
	return mat4(
		width, 0, 0, 0,
		0, height, 0, 0,
		0, 0, -(-a_Near - a_Far) / (a_Near - a_Far), -1.f,
		0, 0, (2 * a_Near * a_Far) / (a_Near - a_Far), 0
	);
}
