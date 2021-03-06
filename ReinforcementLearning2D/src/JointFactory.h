#ifndef JointFactoryHPP
#define JointFactoryHPP

#include <Box2D\Box2D.h>

#define SCALE 30.f

//Allow an easy setup of a b2 Revolute Joint between 2 box2d bodies.
void RevoluteJointDefSetup(b2World world,  b2RevoluteJointDef* jointDef,b2Body* bodyA, b2Body* bodyB, b2Vec2 anchorAInPixels = b2Vec2(0.f, 0.f), b2Vec2 anchorBInPixels = b2Vec2(0.f, 0.f), float referenceAngle = 0.f, bool enableMotor = true, float maxTorque = 10.f, float motorSpeed = 0.f)
{
	jointDef->bodyA = bodyA;
	jointDef->bodyB = bodyB;
	jointDef->collideConnected = false;
	jointDef->localAnchorA.Set(anchorAInPixels.x / SCALE, anchorAInPixels.y / SCALE);
	jointDef->localAnchorB.Set(anchorBInPixels.x / SCALE, anchorBInPixels.y / SCALE);
	jointDef->referenceAngle = referenceAngle;
	jointDef->enableMotor = enableMotor;
	jointDef->maxMotorTorque = 100.0f;
	jointDef->motorSpeed = -10.0f;
}

#endif
