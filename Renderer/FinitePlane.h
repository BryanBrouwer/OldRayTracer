#pragma once
#include "Shape.h"
class FinitePlane :
	public Shape
{
private:
	vec3 Corner;
	vec3 Width;
	vec3 Height;
	vec3 Normal;
	vec3 Color;
	bool Reflective;
	bool Transparant;
	float IOR;

public:
	FinitePlane(vec3 cornerleft, float width, float heigt, vec3 color, bool reflective, bool trans, float ior);
	~FinitePlane();
	vec3 getCenter();
	vec3 getColor();
	bool Intersection(const Ray& ray, float &t);
	vec3 getSurfaceNormal(vec3 hitpoint);
	bool checkReflective();
	bool checkTransparant();
	float getIOR();
};

