#pragma once
#include "MathLibrary.h"
#include "Tracer.h"
#include "BVHmath.h"
#include "Sphere.h"
#include "Plane.h"
#include "Shape.h"
#include "Lights.h"
#include "Disk.h"
#include "PointLight.h"
#include "AABB.h"
#include "BVH.h"
#include "Node.h"
#include "FinitePlane.h"

class PointLight;
class Tracer;
class BVHmath;
class Sphere;
class Disk;
class AABB;
class Shape;
class Plane;
class BVH;
class Node;
class FinitePlane;

class Scene
{
public:
	Scene(Tracer* tracer, string scenedescr, int scenenumb);
	~Scene();

	bool onCreate();
	string GetDescr();
	int GetSceneNumber();
	
private:
	void createBVH();
	bool assignShape(Shape * cube);
	string SceneDescription;
	int SceneNumber;
	BVH* tempBVH[4];
	vector<Shape*> tempShapes;
	Tracer* myTracer;
};

