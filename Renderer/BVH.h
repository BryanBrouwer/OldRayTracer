#pragma once
#include "BVHmath.h"
#include "Node.h"
class Node;

class BVH : public BVHmath
{
public:
	BVH();
	BVH(const vec3& boxMin, const float& Width, const float& Height, const float& Depth);
	~BVH();
	vector<Node *> Nodes;
	void addNode(Node* node);

private:
//	static const int numPlanesSetNormals = 7;
//	//static vec3 planeSetNormals[numPlanesSetNormals];
//	float D[numPlanesSetNormals][2];
//	float PreCompNumerator[numPlanesSetNormals];
//	float PreDenominator[numPlanesSetNormals];
//	void calcReqMaths(const Ray ray);
};

