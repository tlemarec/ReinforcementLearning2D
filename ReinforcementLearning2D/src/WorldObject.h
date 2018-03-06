#ifndef WorldObjectHPP
#define WorldObjectHPP

#include <Box2D\Box2D.h>
#include <SFML\Graphics.hpp>

#define SCALE 30.f

class WorldObject
{
protected:
	b2Body * physicalBody;

public:
	static enum ObjectType { Dynamic, Static };

	WorldObject(b2World& world, b2BodyType bodyType, float xPos = 0.f, float yPos = 0.f)
	{
		b2BodyDef bodyDef;
		bodyDef.type = bodyType;
		bodyDef.position.Set(xPos / SCALE, yPos / SCALE);
		bodyDef.angle = -(b2_pi);
		physicalBody = world.CreateBody(&bodyDef);
	}

	virtual void positionUpdate() = 0;

	virtual void imageRender(sf::RenderWindow& renderWindow) = 0;

	b2Vec2 getPosition();

	void printPosition(std::string name);

	b2Body* getPhysicalBody();
};

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

	virtual void positionUpdate();

	virtual void imageRender(sf::RenderWindow& renderWindow);
};

class CircleWorldObject : public WorldObject
{
private:
	sf::CircleShape renderShape;
public:
	CircleWorldObject(b2World& world, b2BodyType bodyType, const sf::Color &color = sf::Color::White, float xPos = 0.f, float yPos = 0.f, float radiusInPixels = 30.f) : WorldObject(world, bodyType, xPos, yPos)
	{
		b2FixtureDef fixture;
		fixture.friction = 0.7f;
		fixture.restitution = 0.1f;
		fixture.density = 1.0f;


		b2CircleShape bodyShape;
		bodyShape.m_radius = radiusInPixels / SCALE / 2.f;
		fixture.shape = &bodyShape;
		physicalBody->CreateFixture(&fixture);

		renderShape.setOrigin(radiusInPixels / 2.f, radiusInPixels / 2.f);
		renderShape.setRadius(radiusInPixels / 2.f);
		renderShape.setPointCount(50);
		renderShape.setOutlineColor(color);
		renderShape.setOutlineThickness(-5.f);
		renderShape.setFillColor(color);
		positionUpdate();
	}

	virtual void positionUpdate();

	virtual void imageRender(sf::RenderWindow& renderWindow);
};

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
		fixture.density = 1.0f;

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

	virtual void positionUpdate();

	virtual void imageRender(sf::RenderWindow& renderWindow);
};
#endif