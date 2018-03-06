#ifndef JointFactoryHPP
#define JointFactoryHPP

/*
//Joint Center
b2RevoluteJointDef jointCenterDef;
jointCenterDef.bodyA = armLeft.getPhysicalBody();
jointCenterDef.bodyB = armRight.getPhysicalBody();
jointCenterDef.collideConnected = false;
jointCenterDef.localAnchorA.Set(-250.f / SCALE, 0.f / SCALE);
jointCenterDef.localAnchorB.Set(-250.f / SCALE, 0.f / SCALE);
jointCenterDef.referenceAngle = -b2_pi / 2.f;
b2RevoluteJoint* jointCenter = (b2RevoluteJoint*)world.CreateJoint(&jointCenterDef);


//Joint Left
b2RevoluteJointDef jointLeftDef;
jointLeftDef.bodyA = wheelLeft.getPhysicalBody();
jointLeftDef.bodyB = armLeft.getPhysicalBody();
jointLeftDef.collideConnected = false;
jointLeftDef.localAnchorA.Set(0.f / SCALE, 0.f / SCALE);
jointLeftDef.localAnchorB.Set(250.f / SCALE, 0.f / SCALE);
jointLeftDef.referenceAngle = 0.f;
b2RevoluteJoint* jointLeft = (b2RevoluteJoint*)world.CreateJoint(&jointLeftDef);

//Joint Right
b2RevoluteJointDef jointRightDef;
jointRightDef.bodyA = wheelRight.getPhysicalBody();
jointRightDef.bodyB = armRight.getPhysicalBody();
jointRightDef.collideConnected = false;
jointRightDef.localAnchorA.Set(0.f / SCALE, 0.f / SCALE);
jointRightDef.localAnchorB.Set(250.f / SCALE, 0.f / SCALE);
jointRightDef.referenceAngle = 0.f;
b2RevoluteJoint* jointRight = (b2RevoluteJoint*)world.CreateJoint(&jointRightDef);
*/


#endif
