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
	std::vector<unsigned> topology { 1,3,1 };
	Net myNet(topology);

	vector<double> inputVals(topology[0]), targetVals(topology.back()), resultVals(topology.back());
	int trainingPassCount = 0;

	//Create output file to store learning data
	std::ofstream outputFile("DataOutput.txt", ios::out);
	assert(outputFile.is_open());

	//Simulation
	float timeStep = 1.f / 30.f;
	int velocityIterations = 6;
	int positionIterations = 2;
	while (window.isOpen() && trainingPassCount < 200)
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
			
			// Get new input data and feed it forward:
			
			inputVals[0] = double(wheeloo.getMotorBody()->GetAngularVelocity());
			//inputVals[1] = double((wheeloo.getMotorBody()->GetPosition()).x*SCALE);
			
			//(*m_targetVals)[0] = double(((800 - (*m_inputVals)[1] > 0) - (800 - (*m_inputVals)[1] < 0))*abs(800 - (*m_inputVals)[1]) / 800);
			targetVals[0] = 1;


			TrainingPass(&trainingPassCount, &myNet, &topology, &inputVals, &targetVals, &resultVals, outputFile);
			
			//Use Neural Network output
			wheeloo.getMotorBody()->SetAngularVelocity(float(resultVals[0]));
		}
	}
	outputFile.close();
	cout << "Simulation finished, 'ReinforcementLearning2D\ReinforcementLearning2D\DataOutput.txt' generated. \nPress Enter to end. " << endl;
	std::cin.get();
	return EXIT_SUCCESS;
}
