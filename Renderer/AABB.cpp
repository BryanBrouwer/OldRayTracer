#include "AABB.h"



void AABB::swap(float & value1, float & value2)
{
	float temp = value1;
	value1 = value2;
	value2 = temp;
}

AABB::AABB(const vec3 & boxMin, const float& Width, const float& Height, const float& Depth, const vec3 & color, bool reflect, bool trans, float ior)
{
	BoundingBox[0] = boxMin;
	BoundingBox[1] = vec3(boxMin.m_X + Width, boxMin.m_Y + Height, boxMin.m_Z + Depth);
	vec3 boxMax = BoundingBox[1];

	A = vec3(boxMin.m_X, boxMax.m_Y, boxMin.m_Z);
	B = boxMin;
	C = vec3(boxMax.m_X, boxMin.m_Y, boxMin.m_Z);
	D = vec3(boxMax.m_X, boxMax.m_Y, boxMin.m_Z);
	A2 = A;
	A2.m_Z = boxMax.m_Z;
	B2 = B;
	B2.m_Z = boxMax.m_Z;
	C2 = C;
	C2.m_Z = boxMax.m_Z;
	D2 = boxMax;

	Center = boxMin + boxMax;
	Center = vec3(Center.m_X / 2.f, Center.m_Y / 2.f, Center.m_Z / 2.f);

	Color = color;
	Reflective = reflect;
	Transparant = trans;
	IOR = ior;
}

AABB::~AABB()
{
}

bool AABB::Intersection(const Ray & ray, float & t)
{
	vec3 RayO = ray.getOrigin();
	vec3 RayD = ray.getDirection();
	float t0x, t1x, t0y, t1y, t0z, t1z;
	float tEnd = 0.f;
	t0x = ((BoundingBox[0].m_X - RayO.m_X) / RayD.m_X);
	t1x = ((BoundingBox[1].m_X - RayO.m_X) / RayD.m_X);

	if (t0x > t1x)
	{
		swap(t0x, t1x);
	}

	t0y = ((BoundingBox[0].m_Y - RayO.m_Y) / RayD.m_Y);
	t1y = ((BoundingBox[1].m_Y - RayO.m_Y) / RayD.m_Y);
	
	if (t0y > t1y)
	{
		swap(t0y, t1y);
	}

	if (t0x > t1y || t0y > t1x)
	{
		return false;
	}

	float tmin = (t0x > t0y) ? t0x : t0y;
	float tmax = (t1x < t1y) ? t1x : t1y;

	t0z = ((BoundingBox[0].m_Z - RayO.m_Z) / RayD.m_Z);
	t1z = ((BoundingBox[1].m_Z - RayO.m_Z) / RayD.m_Z);

	if (t0z > t1z)
	{
		swap(t0z, t1z);
	}

	if (tmin > t1z || t0z > tmax)
	{
		return false;
	}
	if (t0z > tmin) tmin = t0z;
	if (t1z < tmax) tmax = t1z;

	if (tmin < tmax)
	{
		tEnd = tmin;
	}
	else if (tmax < tmin)
	{
		tEnd = tmax;
	}
	
	if (tEnd < 0.001f)
	{
		return false;
	}
	tEnd = tEnd * 1.00001f;
	t = tEnd;

	return true;
}

vec3 AABB::getCenter()
{
	return Center;
}

vec3 AABB::getMin()
{
	return BoundingBox[0];
}

vec3 AABB::getMax()
{
	return BoundingBox[1];
}

vec3 AABB::getColor()
{
	return Color;
}

vec3 AABB::getSurfaceNormal(vec3 hitpoint)
{
	vec3 hitPoint = hitpoint;
	vec3 Normal;
	if (((B.dot(A - B) <= hitPoint.dot(A - B)) && (hitPoint.dot(A - B) <= A.dot(A - B))) && ((B.dot(C - B) <= hitPoint.dot(C - B)) && (hitPoint.dot(C - B) <= C.dot(C - B))))
	{
		//vec3 AD = D - A;
		//vec3 AB = B - A;
		//Normal = AD.cross(AB);
		Normal = vec3(0, 0, -1.f);
	}
	else if (((C.dot(D - C2) <= hitPoint.dot(D - C)) && (hitPoint.dot(D - C) <= D.dot(D - C))) && ((C.dot(C2 - C) <= hitPoint.dot(C2 - C)) && (hitPoint.dot(C2 - C) <= C2.dot(C2 - C))))
	{
		//vec3 DD2 = D2 - D;
		//vec3 DC = C - D;
		//Normal = DD2.cross(DC);
		Normal = vec3(1.f, 0, 0);

	}
	else if (((B2.dot(A2 - B2) <= hitPoint.dot(A2 - B2)) && (hitPoint.dot(A2 - B2) <= A2.dot(A2 - B2))) && ((B2.dot(B - B2) <= hitPoint.dot(B - B2)) && (hitPoint.dot(B - B2) <= B.dot(B - B2))))
	{
		//vec3 A2A = A - A2;
		//vec3 A2B2 = B2 - A2;
		//Normal = A2A.cross(A2B2);
		Normal = vec3(-1.f, 0, 0);
	}
	else if (((C2.dot(D2 - C2) <= hitPoint.dot(D2 - C2)) && (hitPoint.dot(D2 - C2) <= D2.dot(D2 - C2))) && ((C2.dot(B2 - C2) <= hitPoint.dot(B2 - C2)) && (hitPoint.dot(B2 - C2) <= B2.dot(B2 - C2))))
	{
		//vec3 D2A2 = A2 - D2;
		//vec3 D2C2 = C2 - D2;
		//Normal = D2A2.cross(D2C2);
		Normal = vec3(0, 0, 1.f);
	}
	else if (((A.dot(A2 - A) <= hitPoint.dot(A2 - A)) && (hitPoint.dot(A2 - A) <= A2.dot(A2 - A))) && ((A.dot(D - A) <= hitPoint.dot(D - A)) && (hitPoint.dot(D - A) <= D.dot(D - A))))
	{
		Normal = vec3(0, 1.f, 0);
	}
	else if (((B2.dot(B - B2) <= hitPoint.dot(B - B2)) && (hitPoint.dot(B - B2) <= B.dot(B - B2))) && ((B2.dot(C2 - B2) <= hitPoint.dot(C2 - B2)) && (hitPoint.dot(C2 - B2) <= C2.dot(C2 - B2))))
	{
		Normal = vec3(0, -1.f, 0);
	}
	//there is an easier way with making a vector from the center to the hitpoint, and look which is the biggest component and then use that
	
	return Normal;
}

bool AABB::checkReflective()
{
	return Reflective;
}

bool AABB::checkTransparant()
{
	return Transparant;
}

float AABB::getIOR()
{
	return IOR;
}
