#pragma once
#include <vector>
#include <stdlib.h> //for abs()
#include "Robot.h"
using namespace std;

//Allow the creation and choice by the user of a training situation : Robot Model, Objectif (scenario), topology of the net, Input and Output value of the net.
void chooseSituation(int* m_situation)
{
	cout << "\n Choose one of the training situation :" << endl;

	// Situation 1
	cout << "\n----------- Situation 1 : Enter 1 -----------" << endl;
	cout << "| Robot Model : wheelo, a simple wheel." << endl;
	cout << "| Training Scenario : Train wheelo to rotate at a speed of 1 rad/s." << endl;
	cout << "| Topology : 1 3 1. " << endl;
	cout << "| Network Input Value : wheeloo's angular velocity." << endl;
	cout << "| Network Output Value : Used as wheeloo's angular velocity." << endl;
	cout << "---------------------------------------------\n" << endl;

	// Situation 2
	cout << "\n----------- Situation 2 : Enter 2 -----------" << endl;
	cout << "| Robot Model : wheelo, a simple wheel. A marker is added to spot the target position." << endl;
	cout << "| Training Scenario : Train wheelo to go and stop at position x = screenwidth/4 pixels." << endl;
	cout << "| Topology : 2 3 1. " << endl;
	cout << "| Network Input Value : wheeloo's angular velocity and wheeloo's position." << endl;
	cout << "| Network Output Value : Used as wheeloo's angular velocity." << endl;
	cout << "---------------------------------------------\n" << endl;

	cout << "Your choice : " << endl;

	cin >> *m_situation;

}

//Instanciate the robot according to the choosen situation.
void situationRobotSetup(int* m_situation, Robot* m_robot, b2World* m_world, int m_screenWidth, int m_screenHeight)
{
	switch (*m_situation)
	{
	case 1:
	default:
	{
		m_robot->addCircleComponent(*m_world, b2_dynamicBody, sf::Color::White, 100.f, m_screenHeight / 2.f - 300, 120.f);
		break;
	}
	case 2:
	{
		m_robot->addCircleComponent(*m_world, b2_dynamicBody, sf::Color::White, 1660.f, m_screenHeight / 2.f - 300, 120.f);
		m_robot->addRectangleComponent(*m_world, b2_staticBody, sf::Color::White, m_screenWidth / 4.f, m_screenHeight / 2.f - 300, 10.f, 50.f);
		break;
	}
	}

	// Add ground
	m_robot->addRectangleComponent(*m_world, b2_staticBody, sf::Color::White, m_screenWidth / 4.f, m_screenHeight / 2.f, m_screenWidth, 50.f); 
}

//Setup the topology of the Net according to the choosen situation.
void situationTopologySetup(int* m_situation, vector<unsigned>* m_netTopology, int* m_trainingPassCap)
{
	switch (*m_situation)
	{
	case 1:
	default:
	{
		*m_netTopology = { 1,3,1 };
		*m_trainingPassCap = 1000;
		break;
	}
	case 2:
	{
		*m_netTopology = { 2,3,1 };
		*m_trainingPassCap = 2000;
		break;
	}
	}
}

//Generate the Input and Target value of the Net before a learning pass, according to the choosen situation.
void situationTrainingData(int* m_situation, vector<double>* m_inputVals, vector<double>* m_targetVals, vector<double>* m_resultVals, Robot* m_robot, int* m_screenWidth)
{
	switch (*m_situation)
	{
	case 1:
	default:
	{
		(*m_inputVals)[0] = double(m_robot->getMotorBody()->GetAngularVelocity());
		(*m_targetVals)[0] = 1;
		break;
	}
	case 2:
	{
		(*m_inputVals)[1] = double((m_robot->getMotorBody()->GetPosition()).x*SCALE);
		(*m_targetVals)[0] = double((((*m_screenWidth / 4.f) - (*m_inputVals)[1] > 0) - ((*m_screenWidth / 4.f) - (*m_inputVals)[1] < 0))*abs((*m_screenWidth / 4.f) - (*m_inputVals)[1]) / 800);
		break;
	}
	}
	
}