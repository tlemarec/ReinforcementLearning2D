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
	int motor = 0;
	
public:

	Robot() {}
	
	void addCircleComponent(b2World& world, b2BodyType bodyType, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float radiusInPixels = 30.f);

	void addRectangleComponent(b2World& world, b2BodyType bodyType, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f);

	void addConvexComponent(b2World& world, b2BodyType bodyType, const ConvexWorldObject::ConvexShape shape = ConvexWorldObject::ConvexShape::EquilateralTriangle, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f);

	b2Body* getComponentBody(int i);

	void setMotorComponent(int i);

	b2Body* getMotorBody();

	void robotPositionUpdate();

	void robotImageRender(sf::RenderWindow& renderWindow);

	std::vector<float> getRobotPosition() const;
};


#endif