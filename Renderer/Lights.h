#pragma once
#include "MathLibrary.h"
class vec3;

class Lights
{
public:
	Lights();
	virtual ~Lights();
	
	virtual float getIntensity()=0;
	virtual vec3 getDirection()=0;
	virtual vec3 getColor()=0;
	virtual vec3 getPointCords()=0;
	virtual vec3 getSpecularColor()=0;
};

