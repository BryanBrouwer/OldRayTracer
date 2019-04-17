#include "Ray.h"



Ray::Ray(vec3 origin, vec3 direction)
{
	Origin = origin;

	Direction= direction;
	Direction = Direction.normalize();
}


Ray::~Ray()
{
}

vec3 Ray::getOrigin() const
{
	return Origin;
}

vec3 Ray::getDirection() const
{
	return Direction;
}

vec3 Ray::getPoint(float t) const
{
	return (Origin + Direction * t);
}
