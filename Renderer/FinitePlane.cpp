#include "FinitePlane.h"


FinitePlane::FinitePlane(vec3 corner, float width, float height, vec3 color, bool reflective, bool trans, float ior)
{
	Corner = corner;
	Width = vec3(corner.m_X + width, corner.m_Y, corner.m_Z);
	Height = vec3(corner.m_X, corner.m_Y + height, corner.m_Z);
	Color = color;
	Reflective = reflective;
	Transparant = trans;
	IOR = ior;

	vec3 temp;
	temp = (Width - Corner).cross((Height - Corner));
	temp = vec3(0, 0, 0) - temp;
	Normal = temp.normalize();
}

FinitePlane::~FinitePlane()
{
}

vec3 FinitePlane::getCenter()
{
	return Corner;
}

vec3 FinitePlane::getColor()
{
	return Color;
}

bool FinitePlane::Intersection(const Ray& ray, float & t)
{
	vec3 RayD = ray.getDirection();
	vec3 RayO = ray.getOrigin();

	float denom = Normal.dot(RayD);
	if (std::abs(denom) > 1e-6 && std::abs(denom) < 1.f)
	{
		float tTemp = (-(RayO.dot(Normal) + Corner.dot(Normal)) / denom);
		vec3 hitPoint = (RayO + RayD * tTemp);
		if (((Corner.dot(Height - Corner) <= hitPoint.dot(Height - Corner)) && (hitPoint.dot(Height - Corner) <= Height.dot(Height - Corner))) && ((Corner.dot(Width - Corner) <= hitPoint.dot(Width - Corner)) && (hitPoint.dot(Width - Corner) <= Width.dot(Width- Corner))))
		{
			tTemp = tTemp * 1.00001f;
			t = tTemp;
			return true;
		}
	}
	return false;
}

vec3 FinitePlane::getSurfaceNormal(vec3 hitpoint)
{
	hitpoint = hitpoint;
	return Normal;
}

bool FinitePlane::checkReflective()
{
	return Reflective;
}

bool FinitePlane::checkTransparant()
{
	return Transparant;
}

float FinitePlane::getIOR()
{
	return IOR;
}
