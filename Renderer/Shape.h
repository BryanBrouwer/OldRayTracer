#pragma once
#include "MathLibrary.h"
#include "Ray.h"
class vec3;
class Ray;

class Shape
{
public:
	Shape();
	virtual ~Shape();
	virtual vec3 getCenter()=0;
	virtual vec3 getColor()=0;
	virtual bool Intersection(const Ray& ray, float &t)=0;
	virtual vec3 getSurfaceNormal(vec3 hitpoint) = 0;
	virtual bool checkReflective()=0;
	virtual bool checkTransparant() = 0;
	virtual float getIOR() = 0;
	virtual vec3 getMin();
	virtual vec3 getMax();
};

