#pragma once
#include "Lights.h"

class PointLight :
	public Lights
{
public:
	PointLight();
	PointLight(vec3 cords, float intensity, vec3 color, vec3 specularcolor);
	~PointLight();
	vec3 getPointCords();
	float getIntensity();
	vec3 getDirection();
	vec3 getColor();
	vec3 getSpecularColor();

private:
	vec3 PointCords;
	float Intensity;
	vec3 SpecularColor;
	vec3 Direction;
	vec3 Color;
};

