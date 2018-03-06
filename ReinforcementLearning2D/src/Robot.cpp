#include "Robot.h"
#include <iostream>

void Robot::addCircleComponent(b2World & world, b2BodyType bodyType, const sf::Color & color, float xPos, float yPos, float radiusInPixels)
{
	//components.push_back(std::shared_ptr<CircleWorldObject>( new CircleWorldObject(world, bodyType, color, xPos, yPos, radiusInPixels))); //First Option, make_shared is simpler (no new)
	components.push_back(std::make_shared<CircleWorldObject>(CircleWorldObject(world, bodyType, color, xPos, yPos, radiusInPixels)));
}

void Robot::addRectangleComponent(b2World& world, b2BodyType bodyType, const sf::Color &color, float xPos, float yPos, float widthInPixels, float heightInPixels)
{
	components.push_back(std::make_shared<RectangleWorldObject>(RectangleWorldObject(world, bodyType, color, xPos, yPos, widthInPixels, heightInPixels)));
}

void Robot::addConvexComponent(b2World& world, b2BodyType bodyType, const ConvexWorldObject::ConvexShape shape, const sf::Color &color, float xPos, float yPos, float widthInPixels, float heightInPixels)
{
	components.push_back(std::make_shared<RectangleWorldObject>(RectangleWorldObject(world, bodyType, color, xPos, yPos, widthInPixels, heightInPixels)));
}

void Robot::robotPositionUpdate()
{
	for (int i(0); i < components.size(); ++i)
	{
		components[i]->positionUpdate();
	}
}

void Robot::robotImageRender(sf::RenderWindow & renderWindow)
{
	for (int i(0); i < components.size(); ++i)
	{
		components[i]->imageRender(renderWindow);
	}
}

std::vector<float> Robot::getRobotPosition()
{
	b2Vec2 b2VectorPosition = components[0]->getPosition();
	std::vector<float> vectorPosition(2,0.f);
	vectorPosition[0] = b2VectorPosition.x;
	vectorPosition[1] = b2VectorPosition.y;
	return vectorPosition;
}
