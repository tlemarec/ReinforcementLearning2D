#ifndef RobotHPP
#define RobotHPP

#include <iostream>
#include <stdlib.h>
#include <vector>
#include <memory>
#include"WorldObject.h"

class Robot
{
private:
	std::vector<std::shared_ptr<WorldObject> > components;
	
public:
	//b2RevoluteJoint* motor;

	Robot() {}
	
	void addCircleComponent(b2World& world, b2BodyType bodyType, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float radiusInPixels = 30.f);

	void addRectangleComponent(b2World& world, b2BodyType bodyType, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f);

	void addConvexComponent(b2World& world, b2BodyType bodyType, const ConvexWorldObject::ConvexShape shape = ConvexWorldObject::ConvexShape::EquilateralTriangle, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f);

	b2Body* getComponent(int i);
	
	//void setMotor(b2World world, b2Body* bodyA, b2Body* bodyB, b2Vec2 anchorAInPixels, b2Vec2 anchorBInPixels, float referenceAngle = -b2_pi / 2.f);
	
	void robotPositionUpdate();

	void robotImageRender(sf::RenderWindow& renderWindow);

	std::vector<float> getRobotPosition() const;
};


#endif