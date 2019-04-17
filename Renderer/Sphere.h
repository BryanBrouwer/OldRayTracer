#pragma once
#include "Shape.h"
class Sphere :
	public Shape
{
private:
	float Radius;
	vec3 Center;
	vec3 Color;
	bool Reflective;
	bool Transparant;
	float IOR;
public:
	Sphere(vec3 center, vec3 color, float radius, bool reflective, bool trans, float ior);	
	~Sphere();
	bool Intersection(const Ray& ray, float &t);
	vec3 getCenter();
	vec3 getColor();
	vec3 getNormal(vec3 p);
	vec3 getSurfaceNormal(vec3 hitpoint);
	bool checkReflective();
	bool checkTransparant();
	float getIOR();
};

