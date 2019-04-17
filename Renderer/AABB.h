#pragma once
#include "Shape.h"
class AABB :
	public Shape
{
private:
	vec3 BoundingBox[2];
	vec3 Color;
	vec3 Center;
	bool Reflective;
	bool Transparant;
	float IOR;
	void swap(float& value1, float& value2);
	// corners for normal calc
	vec3 A, B, C, D, A2, B2, C2, D2;


public:
	AABB(const vec3& boxMin, const float& Width, const float& Height, const float& Depth, const vec3& color, bool reflect, bool trans, float ior);
	~AABB();
	bool Intersection(const Ray& ray, float &t);
	vec3 getCenter();
	vec3 getMin();
	vec3 getMax();
	vec3 getColor();
	vec3 getSurfaceNormal(vec3 hitpoint);
	bool checkReflective();
	bool checkTransparant();
	float getIOR();
};

