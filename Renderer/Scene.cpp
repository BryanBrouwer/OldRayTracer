#include "Scene.h"


Scene::Scene(Tracer * tracer, string scenedescr, int scenenumb)
{
	myTracer = tracer;
	SceneDescription = scenedescr;
	SceneNumber = scenenumb;
}

Scene::~Scene()
{
}

bool Scene::onCreate()
{
	createBVH();
	//IOR Water = 1.3, Glass = 1.5, air = 1.f
	//coords: X = [-1.77777779 , 1.77777779], Y = [-1 , 1]

	if (SceneNumber == 1)
	{
		tempShapes.push_back(new Sphere(vec3(1.f, 1.0f, 2.0f), vec3(100, 1, 1), 0.3f, false, false, 0.f));
		tempShapes.push_back(new Sphere(vec3(0.3f, 0.5f, 1.f), vec3(135, 135, 135), 0.3f, false, true, 1.5f));
		tempShapes.push_back(new Sphere(vec3(-0.6f, 0.5f, 0.5f), vec3(135.f, 135.f, 135.f), 0.3f, true, false, 0.f));
		
		tempShapes.push_back(new Plane(vec3(0.0f, -0.1f, 0.0f), vec3(0.f, -0.1f, 0.f), vec3(255, 0, 0), false, false, 0.f));

		myTracer->AddLight(new PointLight(vec3(0.5f, -0.5f, 0.4f), 1.f, vec3(0.f, 0.f, 0.f), vec3(230.f, 230.f, 230.f)));
		//myTracer->AddLight(PointLight(vec3(-0.5f, -0.5f, 0.4f), 1.f, vec3(0.f, 0.f, 0.f), vec3(230.f, 230.f, 230.f)));

	}
	else if (SceneNumber == 2)
	{
		//myTracer->AddShape(new Sphere(vec3(0, (0), 1.f), vec3(50 , 100, 100), 0.1f, false, false, 0.f));
		//myTracer->AddShape(new FinitePlane(vec3(-0.2f, -0.2f, -4.f), 0.5f, 0.5f, vec3(100.f, 0, 0), true, false, 0.f));
		//myTracer->AddShape(new Disk(vec3(0.f, -0.2f, 0.f), 1.f, vec3(0, 100, 0), false, false, 0.f));

		for (float i = -0.5f; i < 0.5f; i = i + 0.011f)
		{
			for (float j = -0.5f; j < 0.5f; j = j + 0.11f)
			{
				tempShapes.push_back(new AABB(vec3(i, (j), 0.5f), 0.05f, 0.05f, 0.05f, vec3(50 + (i * 100.f), 100 - (i * 100.f), 100 + (i * 200.f)), false, false, 0.f));
			}
		}

		//tempShapes.push_back(new AABB(vec3(0.5f, (0.5f), 0.5f), 0.05f, 0.05f, 0.05f, vec3(50 + (0.5 * 100.f), 100 - (0.5 * 100.f), 100 + (0.5 * 200.f)), false, false, 0.f));
		//tempShapes.push_back(new AABB(vec3(-0.5f, (-0.5f), 0.5f), 0.05f, 0.05f, 0.05f, vec3(50 + (0.5 * 100.f), 100 - (0.5 * 100.f), 100 + (0.5 * 200.f)), false, false, 0.f));

		myTracer->AddLight(new PointLight(vec3(0.f, 0.f, -2.f), 1.f, vec3(1.f, 1.f, 255.f), vec3(100.f, 100.f, 100.f)));
	}
	else if (SceneNumber == 3)
	{
		/*myTracer->AddShape(new Sphere(vec3(0.f, 0.f, 0.0f), vec3(100, 1, 1), 0.1f, false, false, 0.f));
		myTracer->AddShape(new Sphere(vec3(0.f, 0.8f, 0.0f), vec3(100, 1, 1), 0.1f, false, false, 0.f));*/

		myTracer->AddLight(new PointLight(vec3(0.f, 0.5f, -2.f), 1.f, vec3(1.f, 1.f, 255.f), vec3(100.f, 100.f, 100.f)));
		//myTracer->AddShape(new Plane(vec3(0.0f, -0.1f, 0.0f), vec3(0.f, 0.1f, 0.f), vec3(255, 0, 0), false, false, 0.f));

		for (float i = -1.4f; i < 1.6f; i = i + 0.2f)
		{
			for (float j = -1.f; j < 1.0f; j = j + 0.2f)
			{
				tempShapes.push_back(new Sphere(vec3(i, (j), 0.5f), vec3(50 + (i * 100.f), 100 - (i * 100.f), 100 + (i * 200.f)), 0.1f, false, false, 0.f));
			}
		}
	}
	else if (SceneNumber == 4)
	{
		for (float i = -0.5f; i < 0.5f; i = i + 0.011f)
		{
			for (float j = -0.5f; j < 0.5f; j = j + 0.11f)
			{
				myTracer->AddShape(new AABB(vec3(i, (j), 0.5f), 0.05f, 0.05f, 0.05f, vec3(50 + (i * 100.f), 100 - (i * 100.f), 100 + (i * 200.f)), false, false, 0.f));
			}
		}
		myTracer->AddLight(new PointLight(vec3(0.f, 0.f, -2.f), 1.f, vec3(1.f, 1.f, 255.f), vec3(100.f, 100.f, 100.f)));
	}
	else if (SceneNumber == 5)
	{
		myTracer->AddLight(new PointLight(vec3(2.f, -1.f, -1.f), 1.f, vec3(1.f, 1.f, 255.f), vec3(100.f, 100.f, 100.f)));
		tempShapes.push_back(new Sphere(vec3(-0.2f, 0.1f, 5.f), vec3(100, 1, 1), 0.3f, false, false, 0.f));
		tempShapes.push_back(new Sphere(vec3(0.f, -0.2f, 1.f), vec3(135, 135, 135), 0.2f, false, true, 1.5f));
		tempShapes.push_back(new Sphere(vec3(0.3f, 0.1f, 8.f), vec3(135, 135, 135), 0.3f, true, false, 1.5f));
		tempShapes.push_back(new FinitePlane(vec3(-2.f, -2.f, -5.f), 3.f, 2.f, vec3(10.f, 50.f, 46.f), false, false, 0.f));
		tempShapes.push_back(new AABB(vec3(0.1f, (0.3f), 0.f), 0.2f, 0.2f, 0.5f, vec3(50 + (1.f * 100.f), 100 - (0.5f * 100.f), 100 + (0.2f * 200.f)), false, false, 0.f));
	}
	else if (SceneNumber == 6)
	{
		myTracer->AddLight(new PointLight(vec3(0.f, 0.f, -2.f), 1.f, vec3(1.f, 1.f, 255.f), vec3(100.f, 100.f, 100.f)));
		tempShapes.push_back(new AABB(vec3(-0.2f, (-0.2f), 0.5f), 0.4f, 0.4f, 0.4f, vec3(50 + (1.f * 100.f), 100 - (0.5f * 100.f), 100 + (0.2f * 200.f)), false, false, 0.f));
	}

	for (int i = 0; i < tempShapes.size(); i++)
	{
		if (dynamic_cast<AABB*>(tempShapes[i]))
		{
			assignShape(tempShapes[i]);
		}
		else
		{
			myTracer->AddShape(tempShapes[i]);
		}
	}

	for (int i = 0; i < 4; i++)
	{
		myTracer->AddBVH(tempBVH[i]);
	}

	printf("Amount of shapes: %i", static_cast<int>(tempShapes.size()));
	printf("\r\n");
	return true;
}

string Scene::GetDescr()
{
	return SceneDescription;
}

int Scene::GetSceneNumber()
{
	return SceneNumber;
}

void Scene::createBVH()
{
	//BVH temp1 = BVH(vec3(-2.f, -2.f, 0.f), 2.f, 2.f, 2.f);
	//BVH temp1 = BVH(vec3(0.f, 0.f, 0.f), )
	vec3 tempvec[4];
	
	int tempint = 0;
	for (float i = -2.f; i < 1.f; i = i + 2.f)
	{
		for (float j = -2.f; j < 1.f; j = j + 2.f)
		{
			tempBVH[tempint] = new BVH(vec3(i, j, 0.f), 2.f, 2.f, 2.f);
			tempvec[tempint] = vec3(i, j, 0.f);
			tempint++;
		}
	}

	for (int i = 0; i < 4; i++)
	{
		for (float j = tempvec[i].m_X; j < (tempvec[i].m_X + 2.f); j = j + 1.f)
		{
			for (float k = tempvec[i].m_Y; k < (tempvec[i].m_Y + 2.f); k = k + 1.f)
			{
				tempBVH[i]->addNode(new Node(vec3(j, k, 0.f)));
			}
		}
	}
}

bool Scene::assignShape(Shape * cube)
{
	int BVHnumb = 0;
	int NodeCheck = 3;
	vec3 min = cube->getMin();
	vec3 max = cube->getMax();
	if (max.m_X <= 0.f && max.m_Y <= 0.f)
	{
		BVHnumb = 0;
	}
	else if (min.m_X >= 0.f && min.m_Y >= 0.f)
	{
		BVHnumb = 3;
	}
	else if (min.m_X >= 0.f && max.m_Y <= 0.f)
	{
		BVHnumb = 2;
	}
	else if (max.m_X <= 0.f && min.m_Y >= 0.f)
	{
		BVHnumb = 1;
	}
	else {
		//cant place cube good in a bvh so always check for it
		myTracer->AddShape(cube);
		return true;
	}

	float testX, testY;
	testX = tempBVH[BVHnumb]->Nodes[NodeCheck]->LeftCorner.m_X;
	testY = tempBVH[BVHnumb]->Nodes[NodeCheck]->LeftCorner.m_Y;
	if (max.m_X <= testX && max.m_Y <= testY)
	{
		tempBVH[BVHnumb]->Nodes[0]->AddShape(cube);
	}
	else if (min.m_X >= testX && min.m_Y >= testY)
	{
		tempBVH[BVHnumb]->Nodes[3]->AddShape(cube);
	}
	else if (min.m_X >= testX && max.m_Y <= testY)
	{
		tempBVH[BVHnumb]->Nodes[2]->AddShape(cube);
	}
	else if (max.m_X <= testX && min.m_Y >= testY)
	{
		tempBVH[BVHnumb]->Nodes[1]->AddShape(cube);
	}
	else {
		//cant place cube good in a node so always check it
		myTracer->AddShape(cube);
		return true;
	}
	return true;
}
