#pragma once
#include "MathLibrary.h"
#include "Shape.h"
#include "Sphere.h"
#include "Plane.h"
#include "Ray.h"
#include "PointLight.h"
#include "Lights.h"
#include "BVH.h"
#include "Node.h"
#include <vector>

using namespace std;
class Ray;
class Sphere;
class Shape;
class Plane;
class vec3;
class mat4;
class PointLight;
class Lights;
class BVH;


class Tracer
{
private:
	float maxDis;
	float Dis;
	int ScreenWidth;
	int ScreenHeight;
	int ReflectDepth;
	float AspectRatio;
	float FOV;

	const int MaxReflect = 5;
	const float degToRad = 3.141592653589793238462643383279502884f / 180.0f;
	vec3 Background;
	vec3 CameraPosition;
	
	vec3 CheckReflection(const Ray& ray, Shape* shape);
	vec3 ReflectedRayDirection(const vec3& surfacenormal, const vec3& primairyraydirection);
	vec3 getRefraction(const Ray& ray, Shape* shape, const vec3& hitpoint);
	vec3 CalcSeparateBlinnPhong(const vec3& raydirection, const vec3& hitpoint, const vec3& surfacenormal);
	vec3 Shading(const Ray& ray, Shape* shape, const float& t);

	vector<Lights *> lights;
	vector<BVH*> Bvhs;
	vector<Shape*> Shapes;

public:
	Tracer(int width, int height, float aspectratio, vec3 background);
	~Tracer();
	void AddShape(Shape* shape);
	void AddLight(Lights * light);
	void AddBVH(BVH* bvh);
	void updateCamPos(const mat4& convermat);
	vec3 Trace(int x, int y, const float& fov, const mat4& convertMat);
};

