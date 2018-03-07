#ifndef JointFactoryHPP
#define JointFactoryHPP

#include <Box2D\Box2D.h>

#define SCALE 30.f

//Still unusable
b2RevoluteJointDef* RevoluteJointDef(b2World world,b2Body* bodyA, b2Body* bodyB, b2Vec2 anchorAInPixels = b2Vec2(0.f, 0.f), b2Vec2 anchorBInPixels = b2Vec2(0.f, 0.f), float referenceAngle = 0.f, bool enableMotor = true, float maxTorque = 10.f, float motorSpeed = 0.f)
{
	b2RevoluteJointDef jointDef;
	jointDef.bodyA = bodyA;
	jointDef.bodyB = bodyB;
	jointDef.collideConnected = false;
	jointDef.localAnchorA.Set(anchorAInPixels.x / SCALE, anchorAInPixels.y / SCALE);
	jointDef.localAnchorB.Set(anchorBInPixels.x / SCALE, anchorBInPixels.y / SCALE);
	jointDef.referenceAngle = referenceAngle;
	jointDef.enableMotor = enableMotor;
	jointDef.maxMotorTorque = 100.0f;
	jointDef.motorSpeed = -10.0f;
	return &jointDef;
	
	//b2RevoluteJoint* joint = (b2RevoluteJoint*)world.CreateJoint(&jointDef);

	//motor
	//b2RevoluteJointDef jointDef;
	//jointDef.bodyA = wheeloo.getComponent(0);
	//jointDef.bodyB = wheeloo.getComponent(1);
	//jointDef.collideConnected = false;
	//jointDef.localAnchorA.Set(b2Vec2(0.f, 0.f).x / SCALE, b2Vec2(0.f, 0.f).y / SCALE);
	//jointDef.localAnchorB.Set(b2Vec2(0.f, 0.f).x / SCALE, b2Vec2(0.f, 0.f).y / SCALE);
	//jointDef.referenceAngle = 0.f;
	//jointDef.enableMotor = true;
	//jointDef.maxMotorTorque = 100.0f;
	//jointDef.motorSpeed = -10.0f;
	//b2JointDef jointDef = RevoluteJointDef(world, wheeloo.getComponent(0), wheeloo.getComponent(1));
	
	//wheeloo.addRectangleComponent(world, b2_dynamicBody, sf::Color::White, 800.f, 100.f, 120.f);
}


#endif
