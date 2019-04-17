#include "BVH.h"



//BVH::BVH()
//{
//	//planeSetNormals[0] = vec3(1, 0, 0);
//	//planeSetNormals[1] = vec3(0, 1, 0);
//	//planeSetNormals[2] = vec3(0, 0, 1);
//	//float temp = (sqrtf(3.f) / 3.f);
//	//planeSetNormals[3] = vec3(temp, temp, temp);
//	//planeSetNormals[4] = vec3(-temp, temp, temp);
//	//planeSetNormals[5] = vec3(-temp, -temp, temp);
//	//planeSetNormals[6] = vec3(-temp, -temp, -temp);
//
//	//for (int i = 0; i < numPlanesSetNormals; i++)
//	//{
//	//	D[i][0] = INFINITY;
//	//	D[i][1] = -INFINITY;
//
//	//	PreCompNumerator[i] = 0.f;
//	//	PreDenominator[i] = 0.f;
//	//}
//}


BVH::BVH()
{
}

BVH::BVH(const vec3 & boxMin, const float & Width, const float & Height, const float & Depth)
{
	BoundingBox[0] = boxMin;
	BoundingBox[1] = vec3(boxMin.m_X + Width, boxMin.m_Y + Height, boxMin.m_Z + Depth);

}

BVH::~BVH()
{
	//	delete[] Shapes;
	for (int i = 0; i < Nodes.size(); i++)
	{
		delete(Nodes[i]);
	}
	Nodes.clear();
}

void BVH::addNode(Node * node)
{
	Nodes.push_back(node);
}


//bool BVH::intersectAABB(const Ray ray)
//{
//	//calcReqMaths(ray);
//	//float tNear = -INFINITY;
//	//float tFar = INFINITY;
//
//
//
//	return false;
//}

//void BVH::calcReqMaths(const Ray ray)
//{
//	for (int i = 0; i < numPlanesSetNormals; i++)
//	{
//		PreCompNumerator[i] = (planeSetNormals[i].dot(ray.getOrigin()));
//		PreDenominator[i] = (planeSetNormals[i].dot(ray.getDirection()));
//	}
//}
