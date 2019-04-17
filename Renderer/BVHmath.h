#pragma once
#include "MathLibrary.h"
#include "Ray.h"
#include <vector>
using namespace std;
class vec3;
class Ray;

class BVHmath
{
public:
	BVHmath();
	virtual ~BVHmath();
	bool intersect(const Ray& ray, float& t);
	void swap(float& value1, float& value2);
protected:
	vec3 BoundingBox[2];
};

