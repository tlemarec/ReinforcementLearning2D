#include <windows.h>
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <stdio.h>
#include <iostream>

#include "WorldObject.h"
#include "Robot.h"
#include "Neuron.h"
#include "Network.h"

#define SCALE 30.f


int main(int argc, char** argv)
{

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	//System info
	::SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	std::cout << "width : " << screenWidth << ", height : " << screenHeight << std::endl;

	//SFML Window
	sf::RenderWindow window(sf::VideoMode(screenWidth / 2, screenHeight / 2), "Louis-Marie");
	window.setFramerateLimit(60);

	//Box2d World generation
	b2Vec2 gravity(0.f, 10.f);
	b2World world(gravity);

	RectangleWorldObject ground(world, b2_staticBody, sf::Color::White, screenWidth / 4.f, screenHeight / 2.f, screenWidth / 2.f, 50.f);

	//Robot generation
	Robot wheeloo;
	wheeloo.addCircleComponent(world, b2_dynamicBody, sf::Color::White, 200.f, 100.f, 120.f);
	//wheeloo.addRectangleComponent(world, b2_dynamicBody, sf::Color::White, 800.f, 100.f, 120.f);

	//Neural network generation

	
	std::vector<unsigned> topology;
	topology.push_back(3);
	topology.push_back(2);
	topology.push_back(1);
	Net myNet(topology);
	
	//Simulation
	float timeStep = 1.f / 30.f;
	int velocityIterations = 6;
	int positionIterations = 2;
	while (window.isOpen())
	{

		for (int i = 0; i < 60; ++i)
		{
			// Step Simulation
			world.Step(timeStep, velocityIterations, positionIterations);
			window.clear();
			//SFML Render
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			ground.positionUpdate();
			ground.imageRender(window);

			wheeloo.robotPositionUpdate();
			wheeloo.robotImageRender(window);

			window.display();
		}
	}

	std::cin.get();
	return EXIT_SUCCESS;
}
