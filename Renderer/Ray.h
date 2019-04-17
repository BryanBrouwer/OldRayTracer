#pragma once
#include "MathLibrary.h"
class vec3;

class Ray
{
private:
	vec3 Origin;
	vec3 Direction;

public:
	Ray(vec3 origin, vec3 direction);
	~Ray();


	vec3 getOrigin() const;
	vec3 getDirection() const;
	vec3 getPoint(float t) const;

};

