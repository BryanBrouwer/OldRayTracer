#include "Sphere.h"
#include <SFML/Graphics/Texture.hpp>
#include <iostream>
using namespace std;

Sphere::Sphere(vec3 center, vec3 color, float radius, bool reflective, bool trans, float ior)
{
	Center = center;
	Color = color;
	Radius = radius;
	Reflective = reflective;
	Transparant = trans;
	IOR = ior;
}


Sphere::~Sphere()
{
}

bool Sphere::Intersection(const Ray& ray, float &t)
{
	vec3 o = ray.getOrigin();
	vec3 d = ray.getDirection();
	vec3 v = o - Center;
	float tEnd = 0;
	const float b = 2.f * v.dot(d);
	const float c = v.dot(v) - Radius * Radius;
	float delta = b * b - 4.f * c;

	if (delta < 0.f) return false;

	const float t1 = (-b - sqrt(delta)) / 2.f;
	const float t2 = (-b + sqrt(delta)) / 2.f;

	if (t1 < 0 && t2 < 0)
	{
		return false;
	}

	if (t1 < t2)
	{
		tEnd = t1;
	}
	else if (t1 > t2)
	{
		tEnd = t2;
	}

	tEnd = tEnd * 1.00001f;

	t = tEnd;
	return true;

}

vec3 Sphere::getCenter()
{
	return Center;
}

vec3 Sphere::getColor()
{
	return Color;
}

vec3 Sphere::getNormal(vec3 p)
{
	return (p - Center) *(-1 / Radius);
}

vec3 Sphere::getSurfaceNormal(vec3 hitpoint)
{
	vec3 temp;
	temp = hitpoint - Center;
	temp = temp.normalize();
	return temp;
}

bool Sphere::checkReflective()
{
	return Reflective;
}

bool Sphere::checkTransparant()
{
	return Transparant;
}

float Sphere::getIOR()
{
	return IOR;
}
