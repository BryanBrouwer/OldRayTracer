#include "PointLight.h"



PointLight::PointLight()	//default constructor with everything on 0
{
	PointCords = vec3(0, 0, 0);
	Direction = vec3(0, 0, 0);
	Intensity = 0.f;
	Color = vec3(0, 0, 0);
	SpecularColor = vec3(100.f, 100.f, 100.f);
}


PointLight::PointLight(vec3 cords, float intensity, vec3 color, vec3 specularcolor)
{
	PointCords = cords;
	Direction = vec3(0, 0, 0);
	Intensity = intensity;
	Color = color;
	SpecularColor = specularcolor;
}

PointLight::~PointLight()
{
}

vec3 PointLight::getPointCords()
{
	return PointCords;
}

float PointLight::getIntensity()
{
	return Intensity;
}

vec3 PointLight::getDirection()
{
	return Direction;
}

vec3 PointLight::getColor()
{
	return Color;
}

vec3 PointLight::getSpecularColor()
{
	return SpecularColor;
}