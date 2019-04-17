#include "Node.h"



Node::Node(const vec3 & boxMin)
{
	BoundingBox[0] = boxMin;
	BoundingBox[1] = vec3(boxMin.m_X + 1.f, boxMin.m_Y + 1.f, boxMin.m_Z + 2.f);
	LeftCorner = boxMin;
}

Node::~Node()
{
	//	delete[] Shapes;
	for (int i = 0; i < Shapes.size(); i++)
	{
		delete(Shapes[i]);
	}
	Shapes.clear();
}

void Node::AddShape(Shape * shape)
{
	Shapes.push_back(shape);
}
