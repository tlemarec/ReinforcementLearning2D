#include <windows.h>
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

#include "WorldObject.h"
#include "Robot.h"
#include "NetworkInterface.h"
#include "TrainingSituation.h"

#define SCALE 30.f


int main(int argc, char** argv)
{

	B2_NOT_USED(argc);
	B2_NOT_USED(argv);

	//System info
	::SetThreadDpiAwarenessContext(DPI_AWARENESS_CONTEXT_SYSTEM_AWARE);
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	cout << screenWidth << endl;
	
	// SFML Window
	sf::RenderWindow window(sf::VideoMode(screenWidth / 2, screenHeight / 2), "SFML Render.");
	window.setFramerateLimit(60);

	// Box2d World generation
	b2Vec2 gravity(0.f, 10.f);
	b2World world(gravity);
	
	// Let the user choose the Training Situation
	int situation;
	chooseSituation(&situation);

	// Robot generation
	Robot wheeloo;
	situationRobotSetup(&situation, &wheeloo, &world, screenWidth, screenHeight);
		
	// Instanciate Neural Network
	std::vector<unsigned> topology;
	int trainingPassCap;
	int trainingPassCount = 0;
	situationTopologySetup(&situation, &topology, &trainingPassCap);
	vector<double> inputVals(topology[0]), targetVals(topology.back()), resultVals(topology.back());
	Net myNet(topology);

	// Create output file to store learning data
	std::ofstream outputFile("DataOutput.txt", ios::out);
	assert(outputFile.is_open());

	// Simulation
	float timeStep = 1.f / 30.f;
	int velocityIterations = 6;
	int positionIterations = 2;
	while (window.isOpen() && trainingPassCount < trainingPassCap)
	{

		for (int i = 0; i < 60; ++i)
		{
			// Box2d Step Simulation
			world.Step(timeStep, velocityIterations, positionIterations);
			window.clear();
			
			// SFML Render
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			wheeloo.robotPositionUpdate();
			wheeloo.robotImageRender(window);
			window.display();

			// Get new input value et set target value
			situationTrainingData(&situation, &inputVals, &targetVals, &resultVals, &wheeloo, &screenWidth);

			// Feed the Network and collet the result
			TrainingPass(&trainingPassCount, &myNet, &topology, &inputVals, &targetVals, &resultVals, outputFile);
			
			// Use Neural Network result
			wheeloo.getMotorBody()->SetAngularVelocity(float(resultVals[0]));
		}
	}
	outputFile.close();
	cout << "Simulation finished, 'ReinforcementLearning2D\ReinforcementLearning2D\DataOutput.txt' generated.\n" << endl;
	system("pause");
	return EXIT_SUCCESS;
}
