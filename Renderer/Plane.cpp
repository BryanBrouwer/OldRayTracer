#include "Plane.h"

#include <cmath>

Plane::Plane()
{
	Normal = vec3(0, 1, 0);
	Center = vec3(0, 1, 0);
	Normal.normalize();
	Color = vec3(0, 0, 0);
	Reflective = false;
}

Plane::Plane(vec3 center, vec3 normal, vec3 color, bool reflective, bool trans, float ior)
{
	Center = center;
	//Center.normalize();
	Normal = normal;
	Normal.normalize();
	Color = color;
	Reflective = reflective;
	Transparant = trans;
	IOR = ior;
}

Plane::~Plane()
{
}

bool Plane::Intersection(const Ray& ray,float &t)
{
	vec3 RayO = ray.getOrigin();
	vec3 RayD = ray.getDirection();
//	float dotRayDNormal = RayD.dot(Normal); // calculate the dot product of RayD and the plane surface normal

	// assuming vectors are all normalized
	float denom = Normal.dot(RayD);
	if (std::abs(denom) > 1e-6) 
	{
		vec3 test = Center - RayO;
		t = test.dot(Normal) / denom;
		return (t >= 0);
	}

	//my first plane intersection code
	//if (std::abs(dotRayDNormal) > 1e-6)
	//{
	//	//no intersection because the equation is never possible
	//	const float t1 = -(((RayO - Center).dot(Normal)) / dotRayDNormal);
	//	const float t2 = (((Center - RayO).dot(Normal)) / dotRayDNormal);

	//	if (t1 < t2)
	//	{
	//		t = t1;
	//	}
	//	else if (t1 > t2)
	//	{
	//		t = t2;
	//	}
	//	else if (t1 == t2)
	//	{
	//		t = t1;
	//	}
	//	return true;
	//}

	return false;
}

//	return true;
//}

vec3 Plane::getCenter()
{
	return Center;
}

vec3 Plane::getColor()
{
	return Color;
}

vec3 Plane::getNormal()
{
	return Normal;
}

vec3 Plane::getSurfaceNormal(vec3 hitpoint)
{
	vec3 temp;
	temp = hitpoint - Center;
	temp = temp.normalize();
	//return temp;
	//hitpoint = hitpoint;
	return Normal;
}

bool Plane::checkReflective()
{
	return Reflective;
}

bool Plane::checkTransparant()
{
	return Transparant;
}

float Plane::getIOR()
{
	return IOR;
}
