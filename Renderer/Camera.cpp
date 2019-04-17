#include "Camera.h"



Camera::Camera()
{
	defaultMatrix = mat4().identity();
	CamtoWorld = defaultMatrix;
}


Camera::~Camera()
{
}

mat4 Camera::getMatrix()
{
	return CamtoWorld;
}

void Camera::reset()
{
	CamtoWorld = defaultMatrix;
}

void Camera::moveX(const float & movement)
{
	CamtoWorld *= CamtoWorld.translate(vec3(-movement, 0, 0));
}

void Camera::moveY(const float & movement)
{
	CamtoWorld *= CamtoWorld.translate(vec3(0, -movement, 0));
}

void Camera::moveZ(const float & movement)
{
	CamtoWorld *= CamtoWorld.translate(vec3(0, 0, -movement));
}

void Camera::rotateX(const float & rotation)
{
	CamtoWorld *= CamtoWorld.rotateX(rotation);
}

void Camera::rotateZ(const float & rotation)
{
	CamtoWorld *= CamtoWorld.rotateZ(rotation);
}

void Camera::rotateY(const float & rotation)
{
	CamtoWorld *= CamtoWorld.rotateY(rotation);
}
