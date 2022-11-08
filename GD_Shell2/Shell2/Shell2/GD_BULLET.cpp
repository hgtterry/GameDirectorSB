#include "StdAfx.h"
#include "BT_App.h"
#include "resource.h"
#include "GD_BULLET.h"


GD_BULLET::GD_BULLET(void)
{
	collisionConfiguration = NULL;
	dispatcher = NULL;
	overlappingPairCache = NULL;
	solver = NULL;
	dynamicsWorld = NULL;

	GD_Physics_On = 1;
	GD_Reset_Player = 1;
}


GD_BULLET::~GD_BULLET(void)
{
}

// *************************************************************************
// *						Init_Bullet Terry Bernie   			 	 	   *
// *************************************************************************
bool GD_BULLET::Init_Bullet()
{
	collisionConfiguration = new btDefaultCollisionConfiguration();

	///use the default collision dispatcher. For parallel processing you can use a diffent dispatcher (see Extras/BulletMultiThreaded)
	dispatcher = new	btCollisionDispatcher(collisionConfiguration);

	///btDbvtBroadphase is a good general purpose broadphase. You can also try out btAxis3Sweep.
	overlappingPairCache = new btDbvtBroadphase();

	///the default constraint solver. For parallel processing you can use a different solver (see Extras/BulletMultiThreaded)
	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher,overlappingPairCache,solver,collisionConfiguration);

	//dynamicsWorld->getDebugDrawer()->setDebugMode( btIDebugDraw::DBG_DrawWireframe);
	
	dynamicsWorld->setGravity(btVector3(0,-30,0));


	btAlignedObjectArray<btCollisionShape*> collisionShapes;

	return 0;
}
//void QuaternionToEuler(const btQuaternion &TQuat, btVector3 &TEuler) {
//	btScalar W = TQuat.getW();
//	btScalar X = TQuat.getX();
//	btScalar Y = TQuat.getY();
//	btScalar Z = TQuat.getZ();
//	float WSquared = W * W;
//	float XSquared = X * X;
//	float YSquared = Y * Y;
//	float ZSquared = Z * Z;
//
//	TEuler.setX(atan2f(2.0f * (Y * Z + X * W), -XSquared - YSquared + ZSquared + WSquared));
//	TEuler.setY(asinf(-2.0f * (X * Z - Y * W)));
//	TEuler.setZ(atan2f(2.0f * (X * Y + Z * W), XSquared - YSquared - ZSquared + WSquared));
//	TEuler *= core::RADTODEG;
//}
// *************************************************************************
// *	  				Reset_Physics Terry Bernie						   *
// *************************************************************************
void GD_BULLET::Reset_Physics(void)
{
	App->Ogre17->PhysicsFrameListener->GD_Run_Physics = 0;

	float x = 0;
	float y = 0;
	float z = 0;

	int Count = 0;
	while (Count < App->GDCL_Scene_Data->ObjectCount)
	{
		if(App->GDCL_Scene_Data->S_Object[Count]->Usage == Enums::Usage_Dynamic)
		{
			btVector3 zeroVector(0,0,0);

			x = App->GDCL_Scene_Data->S_Object[Count]->Physics_Pos.x;
			y = App->GDCL_Scene_Data->S_Object[Count]->Physics_Pos.y;
			z = App->GDCL_Scene_Data->S_Object[Count]->Physics_Pos.z;
			btVector3 initialPosition(x,y,z);

			btTransform startTransform;
			startTransform.setIdentity();
			startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f));
			startTransform.setOrigin(initialPosition);

			App->GDCL_Scene_Data->S_Object[Count]->bt_body->clearForces();
			App->GDCL_Scene_Data->S_Object[Count]->bt_body->setLinearVelocity(zeroVector);
			App->GDCL_Scene_Data->S_Object[Count]->bt_body->setAngularVelocity(zeroVector);

			App->GDCL_Scene_Data->S_Object[Count]->bt_body->setWorldTransform(startTransform);
			App->GDCL_Scene_Data->S_Object[Count]->bt_body->getMotionState()->setWorldTransform(startTransform);
			App->GDCL_Scene_Data->S_Object[Count]->bt_body->activate(true);
		}

		/*if(App->GDCL_Scene_Data->S_Object[Count]->Usage == Enums::Usage_Sound)
		{
			btVector3 zeroVector(0,0,0);

			x = App->GDCL_Scene_Data->S_Object[Count]->Physics_Pos.x;
			y = App->GDCL_Scene_Data->S_Object[Count]->Physics_Pos.y;
			z = App->GDCL_Scene_Data->S_Object[Count]->Physics_Pos.z;
			btVector3 initialPosition(x,y,z);

			btTransform startTransform;
			startTransform.setIdentity();
			startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f));
			startTransform.setOrigin(initialPosition);

			App->GDCL_Scene_Data->S_Object[Count]->bt_body->clearForces();
			App->GDCL_Scene_Data->S_Object[Count]->bt_body->setLinearVelocity(zeroVector);
			App->GDCL_Scene_Data->S_Object[Count]->bt_body->setAngularVelocity(zeroVector);

			App->GDCL_Scene_Data->S_Object[Count]->bt_body->setWorldTransform(startTransform);
			App->GDCL_Scene_Data->S_Object[Count]->bt_body->getMotionState()->setWorldTransform(startTransform);
			App->GDCL_Scene_Data->S_Object[Count]->bt_body->activate(true);
		}*/

		Count++;
	}
	
	/*if(App->GDCL_Player->PlayerAdded == 1 && GD_Reset_Player == 1)
	{
		btVector3 zeroVector(0,0,0);

		x = App->GDCL_Player->StartPos.x;
		y = App->GDCL_Player->StartPos.y;
		z = App->GDCL_Player->StartPos.z;
		btVector3 initialPosition(x,y,z);

		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setRotation(btQuaternion(1.0f, 0.0f, 0.0f, 0.0f));
		startTransform.setOrigin(initialPosition);

		App->GDCL_Player->mObject->clearForces();
		App->GDCL_Player->mObject->setLinearVelocity(zeroVector);
		App->GDCL_Player->mObject->setAngularVelocity(zeroVector);

		App->GDCL_Player->mObject->setWorldTransform(startTransform);
		App->GDCL_Player->mObject->getMotionState()->setWorldTransform(startTransform);
		App->GDCL_Player->mObject->activate(true);
	}*/

	App->Ogre17->PhysicsFrameListener->GD_Run_Physics = 1;
}