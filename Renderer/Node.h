#pragma once
#include "BVHmath.h"
#include "Shape.h"
class Shape;

class Node :
	public BVHmath
{
public:
	Node(const vec3& boxMin);
	~Node();
	vector<Shape*> Shapes;
	void AddShape(Shape* shape);
	vec3 LeftCorner;
};

