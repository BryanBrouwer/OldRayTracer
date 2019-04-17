#pragma once
#include "Shape.h"
class Plane :
	public Shape
{
private:
	vec3 Center;
	vec3 Normal;
	vec3 Color;
	bool Reflective;
	bool Transparant;
	float IOR;

public:
	Plane();
	Plane(vec3 center, vec3 normal, vec3 color, bool reflective, bool trans, float IOR);
	~Plane();
	bool Intersection(const Ray& ray, float &t);
	vec3 getCenter();
	vec3 getColor();
	vec3 getNormal();
	vec3 getSurfaceNormal(vec3 hitpoint);
	bool checkReflective();
	bool checkTransparant();
	float getIOR();
};

