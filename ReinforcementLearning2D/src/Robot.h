#ifndef RobotHPP
#define RobotHPP

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <memory>
#include"WorldObject.h"

//Allow an easy manipulation of all WorldObject added to the b2World. THe ground is added to. Typically, Robot include a method to update the position of all its WorldObject, using the similar method of each WorldObject.
class Robot
{

public:
	//Default constructor
	Robot() {}
	//Add a CircleWorldObject to the component table
	void addCircleComponent(b2World& world, b2BodyType bodyType, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float radiusInPixels = 30.f);
	
	//Add a RectangleWorldObject to the component table
	void addRectangleComponent(b2World& world, b2BodyType bodyType, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f);

	//Add a ConvexWorldObject to the component table
	void addConvexComponent(b2World& world, b2BodyType bodyType, const ConvexWorldObject::ConvexShape shape = ConvexWorldObject::ConvexShape::EquilateralTriangle, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f);

	//--------Getters--------
	
	//Return the b2Body of the worldObject stored at position 'i' in 'components'
	b2Body* getComponentBody(int i);
	
	//Return the b2Body of the worldObject chosen as the motor body of the Robot, to allow easy manipulation of its angularVelocity, etc...
	b2Body* getMotorBody();
	
	//Return the position of the motor component
	std::vector<float> getRobotPosition() const;
	
	//--------Setters--------
	//Set motor component as the component stored at index 'i' in 'components'
	void setMotorComponent(int i);

	//Update the position of all SFML shapes associated to all WorldObject contained in 'component'
	void robotPositionUpdate();
	
	//Rendering all SFML shapes associated to all WorldObject contained in 'component'
	void robotImageRender(sf::RenderWindow& renderWindow);


private:
	//Table of all the World objects composing the Robot
	std::vector<std::shared_ptr<WorldObject> > components;

	//Index in 'components' of the WorldObject choosen as 'Motor', to easily manipulate the robot by applying a torque on the motor per exemple
	int motor = 0;

};


#endif