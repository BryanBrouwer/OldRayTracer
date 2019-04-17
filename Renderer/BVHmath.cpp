#include "BVHmath.h"



BVHmath::BVHmath()
{
}


BVHmath::~BVHmath()
{
}

bool BVHmath::intersect(const Ray & ray, float & t)
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

void BVHmath::swap(float & value1, float & value2)
{
	float temp = value1;
	value1 = value2;
	value2 = temp;
}
