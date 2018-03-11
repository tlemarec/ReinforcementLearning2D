#ifndef WorldObjectHPP
#define WorldObjectHPP

#include <stdio.h>
#include <iostream>
#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

#define SCALE 30.f

//Link a b2Body with an SFML shape. Mother class of various variation of WorldObject. Each variation has 2 attribute : One b2Body and one SFML Shape.
class WorldObject
{
protected:
	b2Body * physicalBody;

public:
	WorldObject(b2World& world, b2BodyType bodyType, float xPos = 0.f, float yPos = 0.f)
	{
		b2BodyDef bodyDef;
		bodyDef.type = bodyType;
		bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
		bodyDef.angle = -(b2_pi);
		physicalBody = world.CreateBody(&bodyDef);
	}

	//Update the position of the SFML Shape. Function defined in all class inheriting from WorldObject.
	virtual void positionUpdate() = 0;

	//Render the SFML Shape.
	virtual void imageRender(sf::RenderWindow& renderWindow) = 0;

	//Send on the 'cout' stream, the position of the b2Body.
	void printPosition(std::string name);

	//-------Getter-----------

	//Get the position of the b2Body
	b2Vec2 getPosition();

	//Get the b2Body
	b2Body* getPhysicalBody();
};

//Inherit from WorldObject, add an SFML shape of type : Convex.
class ConvexWorldObject : public WorldObject
{
private:
	sf::ConvexShape renderShape;

public:
	static enum ConvexShape { EquilateralTriangle };

	ConvexWorldObject(b2World& world, b2BodyType bodyType, const ConvexWorldObject::ConvexShape shape = ConvexWorldObject::ConvexShape::EquilateralTriangle, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f) : WorldObject(world, bodyType, xPos, yPos)
	{
		b2FixtureDef fixture;
		fixture.density = 1.f;
		fixture.friction = 0.7f;
		fixture.restitution = 0.1f;

		switch (shape)
		{
		case EquilateralTriangle:
		default:
		{
			b2PolygonShape bodyShape;
			b2Vec2 points[3] = { b2Vec2(widthInPixels / SCALE,0), b2Vec2(-widthInPixels / SCALE, widthInPixels / SCALE), b2Vec2(-widthInPixels / SCALE, -widthInPixels / SCALE) };
			bodyShape.Set(points, 3);
			fixture.shape = &bodyShape;
			physicalBody->CreateFixture(&fixture);

			renderShape.setPointCount(3);
			renderShape.setPoint(0, sf::Vector2f((points[0].x * SCALE), (points[0].y * SCALE)));
			renderShape.setPoint(1, sf::Vector2f((points[1].x * SCALE), (points[1].y * SCALE)));
			renderShape.setPoint(2, sf::Vector2f((points[2].x * SCALE), (points[2].y * SCALE)));
			renderShape.setFillColor(color);
			positionUpdate();
			break;
		}
		}
	}

	//Update the position of the SFML Shape.
	virtual void positionUpdate();

	//Render the SFML Shape.
	virtual void imageRender(sf::RenderWindow& renderWindow);
};

//Inherit from WorldObject, add an SFML shape of type : Circle.
class CircleWorldObject : public WorldObject
{
private:
	sf::CircleShape renderShape;
	sf::CircleShape referenceShape;
public:
	CircleWorldObject(b2World& world, b2BodyType bodyType, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float radiusInPixels = 30.f) : WorldObject(world, bodyType, xPos, yPos)
	{
		b2FixtureDef fixture;
		fixture.friction = 10.f;
		fixture.restitution = 0.1f;
		fixture.density = 1.0f;


		b2CircleShape bodyShape;
		bodyShape.m_radius = radiusInPixels / SCALE / 2.f;
		fixture.shape = &bodyShape;
		physicalBody->CreateFixture(&fixture);

		renderShape.setOrigin(radiusInPixels / 2.f, radiusInPixels / 2.f);
		renderShape.setRadius(radiusInPixels / 2.f);
		renderShape.setPointCount(50);
		renderShape.setFillColor(color);

		referenceShape.setOrigin(radiusInPixels / 2.f, radiusInPixels / 2.f -radiusInPixels*0.4f );
		referenceShape.setRadius(radiusInPixels / 10.f);
		referenceShape.setPointCount(10);
		referenceShape.setFillColor(sf::Color::Blue);

		positionUpdate();
	}

	//Update the position of the SFML Shape.
	virtual void positionUpdate();

	//Render the SFML Shape.
	virtual void imageRender(sf::RenderWindow& renderWindow);
};

//Inherit from WorldObject, add an SFML shape of type : Rectangle.
class RectangleWorldObject : public WorldObject
{
private:
	sf::RectangleShape renderShape;
public:
	RectangleWorldObject(b2World& world, b2BodyType bodyType, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float widthInPixels = 30.f, float heightInPixels = 30.f) : WorldObject(world, bodyType, xPos, yPos)
	{
		b2FixtureDef fixture;
		fixture.friction = 0.7f;
		fixture.restitution = 0.1f;
		fixture.density = 0.0f;

		b2PolygonShape bodyShape;
		bodyShape.SetAsBox(widthInPixels / 2.f / SCALE, heightInPixels / 2.f / SCALE);
		fixture.shape = &bodyShape;
		physicalBody->CreateFixture(&fixture);

		renderShape.setOrigin(widthInPixels / 2.f, heightInPixels / 2.f);
		renderShape.setFillColor(sf::Color::Transparent);
		renderShape.setSize(sf::Vector2f(widthInPixels, heightInPixels));
		renderShape.setOutlineColor(color);
		renderShape.setOutlineThickness(-5);
		renderShape.setFillColor(color);
		positionUpdate();
	}

	//Update the position of the SFML Shape.
	virtual void positionUpdate();

	//Render the SFML Shape.
	virtual void imageRender(sf::RenderWindow& renderWindow);
};
#endif