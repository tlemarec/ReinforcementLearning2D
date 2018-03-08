#include <windows.h>
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "WorldObject.h"
#include "Robot.h"
#include "JointFactory.h"
#include "Network.h"
#include "NetworkDataOutput.h"
#include "NetworkInterface.h"

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
	sf::RenderWindow window(sf::VideoMode(screenWidth / 2, screenHeight / 2), "Louis-Marie de la famille Michelin");
	window.setFramerateLimit(60);

	//Box2d World generation
	b2Vec2 gravity(0.f, 10.f);
	b2World world(gravity);
	RectangleWorldObject ground(world, b2_staticBody, sf::Color::White, screenWidth / 4.f, screenHeight / 2.f, screenWidth / 2.f, 50.f);

	//Robot generation
	Robot wheeloo;
	wheeloo.addCircleComponent(world, b2_dynamicBody, sf::Color::White, 100.f, 900.f, 120.f);
	wheeloo.addRectangleComponent(world, b2_staticBody, sf::Color::White, 800.f, 800.f, 10.f, 50.f);
	wheeloo.getMotorBody()->SetAngularVelocity(0.f);
	
	//Instanciate Neural Network
	vector<unsigned> topology;
	topology.push_back(2);
	topology.push_back(3);
	topology.push_back(1);
	Net myNet(topology);

	vector<double> inputVals(2), targetVals(1), resultVals(1);
	int trainingPass = 0;

	//Create output file to store learning data
	std::ofstream outputFile("DataOutput.txt", ios::out);
	assert(outputFile.is_open());

	//Simulation
	float timeStep = 1.f / 30.f;
	int velocityIterations = 6;
	int positionIterations = 2;
	while (window.isOpen() && trainingPass < 200)
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
			
			//Neural Network learning 
			++trainingPass;
			
			// Get new input data and feed it forward:
			inputVals[0] = double(wheeloo.getMotorBody()->GetAngularVelocity());
			inputVals[1] = double((wheeloo.getMotorBody()->GetPosition()).x*SCALE);
			if (inputVals.size() != topology[0])
				break;
			myNet.feedForward(inputVals);

			// Collect the net's actual results:
			myNet.getResults(resultVals);
			
			// Train the net what the outputs should have been: (x > 0) - (x < 0)
			targetVals[0] = double(((800 - inputVals[1] > 0) - (800 - inputVals[1] < 0))*abs(800 - inputVals[1])/800);
			assert(targetVals.size() == topology.back());

			myNet.backProp(targetVals);

			//Store learning data
			dataOutput(outputFile, myNet, trainingPass, inputVals, resultVals, targetVals);
			
			//Use Neural Network output
			wheeloo.getMotorBody()->SetAngularVelocity(float(resultVals[0]));
		}
	}

	outputFile.close();
	std::cin.get();
	return EXIT_SUCCESS;
}
