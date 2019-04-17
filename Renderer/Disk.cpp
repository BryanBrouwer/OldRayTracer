#include "Disk.h"



Disk::Disk(vec3 center, float radius, vec3 color, bool reflect, bool transparant, float ior)
{
	Center = center;
	Normal = vec3(0, 0, 0) - center;
	Radius = radius;
	Radius2 = Radius * Radius;
	Color = color;
	Reflective = reflect;
	Transparant = transparant;
	IOR = ior;
}

Disk::~Disk()
{
}

bool Disk::Intersection(const Ray & ray, float & t)
{
	vec3 RayO = ray.getOrigin();
	vec3 RayD = ray.getDirection();
	// assuming vectors are all normalized
	float denom = Normal.dot(RayD);
	if (std::abs(denom) > 1e-6)
	{
		vec3 test = Center - RayO;
		t = test.dot(Normal) / denom;
		vec3 hitpoint = (RayO + RayD * t);
		vec3 dist = hitpoint - Center;
		float d2 = dist.dot(dist);
		return (d2 <= Radius2);
	}

	return false;
}

vec3 Disk::getCenter()
{
	return Center;
}

vec3 Disk::getColor()
{
	return Color;
}


vec3 Disk::getSurfaceNormal(vec3 hitpoint)
{
	hitpoint = hitpoint;
	return Normal;
}

bool Disk::checkReflective()
{
	return Reflective;
}

bool Disk::checkTransparant()
{
	return Transparant;
}

float Disk::getIOR()
{
	return IOR;
}
