#include "Application.h"
#include <iostream>
#include <time.h>
#include <SFML/Graphics/Texture.hpp>
#include "Tracer.h"
#include "Sphere.h"
#include "Ray.h"



Application::Application()
{
	AspectRatio = 16.f / 9.f;
	background = vec3(100, 100, 150);
	validChose = false;
	UpdateRender = true;
	tranStep = 0.5f;		//5.f is nice maar probeer 0.5f te houden
	RotationStep = 1.0f;
	FOV = 90.f;
}


Application::~Application()
{
	delete myTracer;
	delete myCam;
	Scenes.clear();
}

bool Application::onCreate()
{
	//create SFML color for background
	backgroundColor = sf::Color(static_cast<sf::Uint8>(background[0]), static_cast<sf::Uint8>(background[1]), static_cast<sf::Uint8>(background[2]), 255);
	
	//set screenwidth and calculate screenheigt using aspectratio
	//float screenwidth = 1280.f;
	//float screenheight = screenwidth / AspectRatio;
	
	float screenheight = 720;
	float screenwidth = screenheight * AspectRatio;

	Width = static_cast<int>(screenwidth);
	Height = static_cast<int>(screenheight);

	myCam = new Camera();

	//create tracer, and all available scene's
	myTracer = new Tracer(Width, Height, AspectRatio, background);
	Scenes.push_back(Scene(myTracer, "3 spheres and infiniteplane with light.", 1));
	Scenes.push_back(Scene(myTracer, "910 cubes with a light, working BVH.", 2));
	Scenes.push_back(Scene(myTracer, "lots of spheres", 3));
	Scenes.push_back(Scene(myTracer, "910 cubes with a ligth, BVH disabled", 4));
	Scenes.push_back(Scene(myTracer, "Spheres, one normal sphere, one reflective, one refractive, finite plane, and a cube", 5));
	Scenes.push_back(Scene(myTracer, "One cube and a light", 6));

	cout << "Choses and descriptions: " << endl;
	for (int i = 0; i < Scenes.size(); i++)
	{
		cout << Scenes[i].GetSceneNumber() - 1 << " " << Scenes[i].GetDescr() << endl;
	}
	cout << endl;

	int SceneSize = static_cast<int>(Scenes.size()) - 1;
	
	//Choose a scene
	printf("\rPlease choose a scene between: 0 and %i", SceneSize);
	printf(" were both end values are also a valid choose \r");
	cout << endl;
	int Chosen;
	cin >> Chosen;
	while (!validChose)
	{
		if (Chosen > SceneSize || Chosen < 0)
		{
			printf("\r Invalid chose please choose a valid number. \r");
			cin >> Chosen;
		}
		else
		{
			validChose = true;
		}
	}

	Scenes[Chosen].onCreate();
	printf(Scenes[Chosen].GetDescr().c_str());
	printf("\r\n W,A,S,D,R,F to move. \r\n Up,Down,Left,Right to rotate. \r\n T,G to increase and decrease FOV");

	//create window
	window.create(sf::VideoMode(Width, Height), "Render");
	//Render();

	return true;
}

bool Application::onUpdate()
{
	while (window.isOpen())
	{
		//check translation
		if (!UpdateRender)
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			{
				UpdateRender = true;
				myCam->moveX(-tranStep);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			{
				UpdateRender = true;
				myCam->moveX(tranStep);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			{
				UpdateRender = true;
				myCam->moveY(-tranStep);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			{
				UpdateRender = true;
				myCam->moveY(tranStep);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
			{
				UpdateRender = true;
				myCam->moveZ(tranStep);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
			{
				UpdateRender = true;
				myCam->moveZ(-tranStep);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
			{
				UpdateRender = true;
				myCam->rotateY(RotationStep);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
			{
				UpdateRender = true;
				myCam->rotateY(-RotationStep);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				UpdateRender = true;
				myCam->rotateX(RotationStep);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				UpdateRender = true;
				myCam->rotateX(-RotationStep);
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::T))
			{
				UpdateRender = true;
				FOV += 10.f;
			}
			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::G))
			{
				UpdateRender = true;
				FOV -= 10.f;
			}
		}

		if (UpdateRender)
		{
			myTracer->updateCamPos(myCam->getMatrix());
			Render();
		}

		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				window.close();
				Running = false;
			}
		}

		window.clear();

		window.draw(sprite);

		window.display();
	}

	return true;
}

bool Application::onDestroy()
{

	return true;
}

bool Application::Trace(int w, int h)
{
	const vec3 color = myTracer->Trace(w, h, FOV, myCam->getMatrix());	
	temp = sf::Color(static_cast<sf::Uint8>(color[0]), static_cast<sf::Uint8>(color[1]), static_cast<sf::Uint8>(color[2]), 255);
	renderer.setPixel(w, h, temp);

	return true;
}

bool Application::Render()
{
	renderer.create(Width, Height, sf::Color::Black);
	// trace
	sf::Clock clock;
	sf::Clock ClockRendertime;
	for (int w = 0; w < Width; w++)
	{
		for (int h = 0; h < Height; h++)
		{
			//trace the array and apply color
			Trace(w, h);

			// timer for displaying the window
			sf::Time ElapsedTime = clock.getElapsedTime();
			if (ElapsedTime.asSeconds() >= 0.1f)
			{
				texture.loadFromImage(renderer);
				sprite.setTexture(texture, true);
				window.clear();
				window.draw(sprite);
				window.display();
				clock.restart();
			}

		}
	}
	sf::Time RenderTime = ClockRendertime.getElapsedTime();
	printf("\r\n %f", RenderTime.asSeconds());
	texture.loadFromImage(renderer);
	renderer.saveToFile("Temporary.png");
	sprite.setTexture(texture, true);
	UpdateRender = false;
//	myCam->reset();
	return true;
}
