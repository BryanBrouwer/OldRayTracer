#pragma once
#include <SFML/Graphics.hpp>
#include "MathLibrary.h"
#include "Scene.h"
#include "Camera.h"
#include <vector>
using namespace std;
class Tracer;
class Scene;
class vec3;
class mat4;
class Camera;

class Application
{
public:
	Application();
	~Application();
	bool onCreate();
	bool onUpdate();
	bool onDestroy();

	bool Running;


private:

	sf::Color temp;
	sf::Texture texture;
	sf::Texture oldtexture;
	sf::RenderWindow window;
	sf::Image renderer;
	sf::Sprite sprite;
	float tranStep;
	float RotationStep;
	float FOV;

	int Width;
	int Height;
	float AspectRatio;
	bool UpdateRender;

	Tracer* myTracer;
	Camera* myCam;
	//std::unique_ptr<Tracer> myTracer;
	vector<Scene> Scenes;
	vec3 background;
	sf::Color backgroundColor;
	bool validChose;
	bool Trace(int w, int h);
	bool Render();
};