#include <Box2D\Box2D.h>
#include "Robot.h"

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

b2Body * Robot::getComponent(int i)
{
	return components[i]->getPhysicalBody();
}

//void Robot::setMotor(b2World world, b2Body* bodyA, b2Body* bodyB, b2Vec2 anchorAInPixels, b2Vec2 anchorBInPixels, float referenceAngle)
//{
//	//motor = RevoluteJoint(world, bodyA, bodyB, anchorAInPixels, anchorBInPixels, referenceAngle);
//	RevoluteJoint(motor, world, bodyA, bodyB, anchorAInPixels, anchorBInPixels, referenceAngle);
//}


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

std::vector<float> Robot::getRobotPosition() const
{
	b2Vec2 b2VectorPosition = components[0]->getPosition();
	std::vector<float> vectorPosition(2,0.f);
	vectorPosition[0] = b2VectorPosition.x;
	vectorPosition[1] = b2VectorPosition.y;
	return vectorPosition;
}
