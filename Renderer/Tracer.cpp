#include "Tracer.h"
#include <iostream>
#include <algorithm>

Tracer::Tracer(int width, int height, float aspectratio, vec3 background)
{
	ScreenWidth = width;
	ScreenHeight = height;
	AspectRatio = aspectratio;
	ReflectDepth = 5;
	Background = background;
	//CameraPosition = vec3(0.f, 0.f, -10.f);
}

Tracer::~Tracer()
{

	for (int i = 0; i < lights.size(); i++)
	{
		delete(lights[i]);
	}
	lights.clear();
	//	delete Shapes that couldnt go into BVH
	for (int i = 0; i < Shapes.size(); i++)
	{
		delete(Shapes[i]);
	}
	Shapes.clear();
	//delete bvhs, which also deletes the nodes, which also delete the shapes saved in the nodes
	for (int i = 0; i < Bvhs.size(); i++)
	{
		delete(Bvhs[i]);
	}
}

void Tracer::AddShape(Shape * shape)
{
	Shapes.push_back(shape);
}

//Add to vectors
void Tracer::AddLight(Lights * light)
{
	lights.push_back(light);
}

void Tracer::AddBVH(BVH* bvh)
{
	Bvhs.push_back(bvh);
}


void Tracer::updateCamPos(const mat4 & convertmat)
{
	CameraPosition = convertmat * CameraPosition;
}

// Reflection Checks
vec3 Tracer::CheckReflection(const Ray& ray, Shape* shape)
{
	vec3 ReflectedColor = shape->getColor();
	float t = 0.f;
	if (shape->checkReflective() == true)
	{
		for (int i = 0; i < Shapes.size(); i++)
		{
			if (Shapes[i] != shape)
			{
				if (Shapes[i]->checkTransparant() == false)
				{
					if (Shapes[i]->Intersection(ray, t))
					{
						ReflectDepth++;
						vec3 hitpoint = ray.getPoint(t);
						hitpoint = hitpoint.normalize();
						vec3 NextRayDirection = ReflectedRayDirection(Shapes[i]->getSurfaceNormal(hitpoint), ray.getDirection());
						const Ray raynew(hitpoint, NextRayDirection);
						ReflectedColor = CheckReflection(raynew, Shapes[i]);
						if (ReflectDepth > MaxReflect)
						{
							return Background;
						}

						ReflectedColor = ReflectedColor * 0.8f;

						for (int j = 0; j < 3; j++)
						{
							if (ReflectedColor[j] > 255.f)
							{
								ReflectedColor[j] = 255.f;
							}
						}
					}
				}
			}
		}
	}
	return ReflectedColor;
}

//Calculate Reflected Ray Direction
vec3 Tracer::ReflectedRayDirection(const vec3& surfacenormal, const vec3& primairyraydirection)
{
	//Normalize required vectors
	vec3 SphereSurfaceNormal = surfacenormal;
	vec3 PrimairyRayDirection = primairyraydirection;
	SphereSurfaceNormal = SphereSurfaceNormal.normalize();
	PrimairyRayDirection = PrimairyRayDirection.normalize();

	//Calculate reflected ray according to my calculations
	vec3 B = (SphereSurfaceNormal * SphereSurfaceNormal.dot(PrimairyRayDirection));
	vec3 A = (PrimairyRayDirection - B);
	vec3 ReflectedRay = A - B;

	ReflectedRay = ReflectedRay.normalize();

	return ReflectedRay;
}

vec3 Tracer::getRefraction(const Ray& ray, Shape* shape, const vec3& hitpoint)
{
	vec3 RefractionDir = vec3(0,0,0);
	vec3 AOI = ray.getDirection();
	vec3 Hit = hitpoint;
	vec3 N = shape->getSurfaceNormal(Hit);
	float IdotN = AOI.dot(N);
	float IORSecond = shape->getIOR();
	float IORFirst = 1.f;
	
	if (IdotN < 0)
	{
		IdotN = -IdotN;
	}
	else if (IdotN > 0)
	{
		N = vec3(0,0,0) - N;
		IORFirst = shape->getIOR();
		IORSecond = 1.f;
	}

	float IORCalc = IORFirst / IORSecond;
	float K = (1 - IORCalc * IORCalc * (1 - IdotN * IdotN));
	if (K < 0)
	{
		return vec3(0,0,0);
	}

	vec3 tempColor = ((AOI * IORCalc) + (N *(IORCalc * IdotN - sqrtf(K))));
	RefractionDir = tempColor;
	RefractionDir = RefractionDir.normalize();
	return RefractionDir;
}

vec3 Tracer::CalcSeparateBlinnPhong(const vec3& raydirection, const vec3& hitpoint, const vec3& surfacenormal)
{
	vec3 BlinnPhongColorReflect = vec3(0, 0, 0);
	vec3 SurfaceNormal = surfacenormal;
	//blinn - phong shading
	for (int i = 0; i < lights.size(); i++)
	{

		vec3 lightDirection = lights[i]->getPointCords() - hitpoint;
		lightDirection = lightDirection.normalize();
		vec3 RayToEye = vec3(0, 0, 0) - raydirection;
		vec3 HalfVec = ((lightDirection + RayToEye) / (lightDirection + RayToEye).length());
		HalfVec = HalfVec.normalize();
		constexpr float ReflectionPower = 1000.f;

		BlinnPhongColorReflect = (BlinnPhongColorReflect + (lights[i]->getSpecularColor() * pow(max(0.f, SurfaceNormal.dot(HalfVec)), ReflectionPower) * lights[i]->getIntensity()));
	}
	return BlinnPhongColorReflect;
}


//Trace all Shapes
vec3 Tracer::Trace(int x, int y, const float & fov, const mat4 & convertmat)
{
	//convert ints to float and set default color
	float X = static_cast<float>(x);
	float Y = static_cast<float>(y);
	float Width = static_cast<float>(ScreenWidth);
	float Height = static_cast<float>(ScreenHeight);
	FOV = fov;
	vec3 PixelColor = Background;


	//new with camera
	float Scale = tanf(degToRad*(FOV * 0.5f));
	float NDCX = ((X + 0.5f) / Width);
	float NDCY = ((Y + 0.5f) / Height);
	float CamX = ((2.f * NDCX - 1.f) * AspectRatio * Scale);
	float CamY = ((1.f - 2.f * NDCY) * Scale);

	
	vec3 tempOrigin = vec3(0, 0, -10.f);
	const vec3 vecOrigin = convertmat * tempOrigin;
	//const vec3 vecOrigin = CameraPosition;
	

	vec3 tempDir = vec3(CamX, CamY, -1.f);
	vec3 vecDirection = convertmat * tempDir;

	//set Maximum distance
	maxDis = 3000.f;
	Dis = 0.f;
	vecDirection = vecDirection.normalize();

	//Ray creation
	const Ray ray(vecOrigin, vecDirection - vecOrigin);
	int firstBVH = 5;

	float BVHMaxDis = 3000.f;
	float BVHDis = 0.f;
	for (int i = 0; i < Bvhs.size(); i++)
	{
		if (Bvhs[i]->intersect(ray, BVHDis))
		{
			if (BVHDis < BVHMaxDis)
			{
				firstBVH = i;

			}
		}
	}

	int firstNode = 5;
	float NODEMaxDis = 3000.f;
	float NODEDis = 0.f;
	int NodesSize = static_cast<int>(Bvhs[firstBVH]->Nodes.size());
	for (int i = 0; i < NodesSize; i++)
	{
		if (Bvhs[firstBVH]->Nodes[i]->intersect(ray, Dis))
		{
			if (NODEDis < NODEMaxDis)
			{
				firstNode = i;
			}
		}
	}

	int nodeShapesSize = static_cast<int>(Bvhs[firstBVH]->Nodes[firstNode]->Shapes.size());
	for (int i = 0; i < nodeShapesSize; i++)
	{
		auto tempShape = Bvhs[firstBVH]->Nodes[firstNode]->Shapes[i];
		if (tempShape->Intersection(ray, Dis))
		{
			if (Dis < maxDis)
			{
				maxDis = Dis;
				vec3 color = Shading(ray, tempShape, Dis);
				PixelColor = color;
			}
		}
	}

	//check for intersection and apply shading for the shapes that could be placed inside bvh
	for (int i = 0; i < Shapes.size(); i++)
	{
		if (Shapes[i]->Intersection(ray, Dis))
		{
			if (Dis < maxDis)
			{
				maxDis = Dis;
				vec3 color = Shading(ray, Shapes[i], Dis);
				PixelColor = color;
			}
		}
	}




	// clamp color values
	for (int v = 0; v < 3; v++)
	{
		if (PixelColor[v] > 255.f)
		{
			PixelColor[v] = 254.f;
		}
		else if (PixelColor[v] < 0.01f)
			{
				PixelColor[v] = 0.01f;
			}
	}

	return PixelColor;
}

//Shading to be called for each Shape
vec3 Tracer::Shading(const Ray& ray, Shape* shape, const float& t)
{
	//Create all needed vec3's
	vec3 color = vec3(0,0,0);
	vec3 tempColor = Background;
	vec3 calcColor = shape->getColor();
	vec3 hitpoint = ray.getPoint(t);
	vec3 SurfaceNormal = shape->getSurfaceNormal(hitpoint);
	vec3 RayDirect = ray.getDirection();

	//check reflection
	if (shape->checkReflective() == true)
	{
		vec3 newrayDirection = ReflectedRayDirection(SurfaceNormal.normalize(), RayDirect);
		const Ray raycheck(hitpoint.normalize(), newrayDirection);
		calcColor = CheckReflection(raycheck, shape);

		vec3 blinnphong = CalcSeparateBlinnPhong(RayDirect, hitpoint, SurfaceNormal);

		calcColor = calcColor +  blinnphong;

		color = calcColor;
	}

	//reset Reflection depth
	ReflectDepth = 0;

	if (shape->checkTransparant() == true)
	{
		vec3 newDir = getRefraction(ray, shape, hitpoint);
		vec3 newOrigin = hitpoint.normalize();
		const Ray newRay(newOrigin, newDir);
		float newDis = 0.0f;
		float newMaxDis = 30.f;
		tempColor = Background - vec3(30,30,30);
		for (int i = 0; i < Shapes.size(); i++)
		{
			if (Shapes[i] != shape)
			{
				if (Shapes[i]->Intersection(newRay, newDis))
				{
					if (newDis < newMaxDis)
					{
						newMaxDis = newDis;
						tempColor = Shapes[i]->getColor();
					}
				}
			}
		}
		vec3 blinnphong = CalcSeparateBlinnPhong(RayDirect, hitpoint, SurfaceNormal);

		color = tempColor + blinnphong;
	}

	if (shape->checkReflective() == false && shape->checkTransparant() == false)
	{
		for (int i = 0; i < lights.size(); i++)
		{
			vec3 lightDirection = lights[i]->getPointCords() - hitpoint;
			lightDirection = lightDirection.normalize();
			float LambRatio = max(0.f, (SurfaceNormal.dot(lightDirection)));

			//blinn - phong shading
			vec3 RayToEye = vec3(0, 0, 0) - RayDirect;
			vec3 HalfVec = ((lightDirection + RayToEye) / (lightDirection + RayToEye).length());
			HalfVec = HalfVec.normalize();
			constexpr float ReflectionPower = 1000.f;

			vec3 BlinnPhongColor = lights[i]->getSpecularColor() * pow(max(0.f, SurfaceNormal.dot(HalfVec)), ReflectionPower);
			vec3 Lambertian = (calcColor * LambRatio);

			tempColor = (Lambertian + BlinnPhongColor)* lights[i]->getIntensity();
			//vec3 tempLightColor = lights[i].getColor() * lights[i].getIntensity() * LambRatio;
			color = color + tempColor/* tempLightColor*/;
		}
	}
	return color;
}
