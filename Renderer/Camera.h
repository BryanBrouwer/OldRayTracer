#pragma once
#include "MathLibrary.h"
class mat4;
class Camera
{
public:
	Camera();
	~Camera();
	mat4 getMatrix();
	void reset();
	void moveX(const float& movement);
	void moveY(const float& movement);
	void moveZ(const float& movement);
	void rotateX(const float& rotation);
	void rotateZ(const float& rotation);
	void rotateY(const float& rotation);

private:
	mat4 CamtoWorld;
	mat4 defaultMatrix;
};

