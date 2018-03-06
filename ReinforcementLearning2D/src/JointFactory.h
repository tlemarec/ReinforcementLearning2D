#ifndef JointFactoryHPP
#define JointFactoryHPP

#include <Box2D\Box2D.h>

#define SCALE 30.f

void RevoluteJoint(b2World world,b2Body* bodyA, b2Body* bodyB, b2Vec2 anchorAInPixels, b2Vec2 anchorBInPixels, float referenceAngle = -b2_pi / 2.f)
{
	b2RevoluteJointDef jointCenterDef;
	jointCenterDef.bodyA = bodyA;
	jointCenterDef.bodyB = bodyB;
	jointCenterDef.collideConnected = false;
	jointCenterDef.localAnchorA.Set(anchorAInPixels.x / SCALE, anchorAInPixels.y / SCALE);
	jointCenterDef.localAnchorB.Set(anchorBInPixels.x / SCALE, anchorBInPixels.y / SCALE);
	jointCenterDef.referenceAngle = referenceAngle;
	b2RevoluteJoint* joint = (b2RevoluteJoint*)world.CreateJoint(&jointCenterDef);
}


#endif
