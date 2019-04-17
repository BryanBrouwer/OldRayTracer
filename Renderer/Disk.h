#pragma once
#include "Shape.h"
class Disk :
	public Shape
{
private:
	vec3 Center;
	vec3 Normal;
	vec3 Color;
	bool Reflective;
	bool Transparant;
	float IOR;
	float Radius, Radius2;

public:
	Disk(vec3 center, float radius, vec3 color, bool reflect, bool transparant, float ior);
	~Disk();
	bool Intersection(const Ray& ray, float &t);
	vec3 getCenter();
	vec3 getColor();
	vec3 getSurfaceNormal(vec3 hitpoint);
	bool checkReflective();
	bool checkTransparant();
	float getIOR();

};

