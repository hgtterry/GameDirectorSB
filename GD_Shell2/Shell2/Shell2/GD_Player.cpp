#include "StdAfx.h"
#include "BT_App.h"
#include "GD_Player.h"


GD_Player::GD_Player(void)
{
	ShowDebug = 0;
	PlayerAdded = 0;

	Player_Ent = NULL; 
	Player_Node = NULL;

	IsMOving = 0;
	IsMOving_Back = 0;
	IsMOving_Right = 0;
	IsMOving_Left = 0;

	mOnGround = 1;
	Ground_speed = 2.2;
	PlayerHeight = 6.0;
	TurnRate = 0.02;

	StartPos.x = 0;
	StartPos.y = -50;
	StartPos.z = 0;

	Capsule_Mass = 1.0;
	Capsule_Radius = 1.4;
	Capsule_Height = 7.0;

	strcpy(PlayerName,"Player_1");

	ColisionIndex = 0;
	Last_ColisionIndex = 0;

	Round = 0;
	Distance = 0;
	Life_Time = 0;
}


GD_Player::~GD_Player(void)
{
}


// *************************************************************************
// *	  						SetUp Terry Bernie						   *
// *************************************************************************
void GD_Player::SetUp(void)
{
	Initialize(StartPos,Capsule_Mass, Capsule_Radius,Capsule_Height);

	CameraPitch = App->Ogre17->mSceneMgr->createCamera("PlayerPitch");

	Player_Ent->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	
	// Get the two halves of the idle animation.
	App->Ogre17->PhysicsFrameListener->Animate_State = Player_Ent->getAnimationState("IdleBase");
	App->Ogre17->PhysicsFrameListener->Animate_State2 = Player_Ent->getAnimationState("IdleTop");

	// Enable both of them and set them to loop.
	App->Ogre17->PhysicsFrameListener->Animate_State->setLoop(true);
	App->Ogre17->PhysicsFrameListener->Animate_State2->setLoop(true);
	App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(true);
	App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(true);

	App->Ogre17->PhysicsFrameListener->Animate_Ogre = 1;
}

// *************************************************************************
// *	  						Load_Player Terry Bernie				   *
// *************************************************************************
void GD_Player::Load_Player(void)
{
	Initialize(StartPos,Capsule_Mass, Capsule_Radius,Capsule_Height);
	
	Player_Ent->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	// Get the two halves of the idle animation.
	App->Ogre17->PhysicsFrameListener->Animate_State = Player_Ent->getAnimationState("IdleBase");
	App->Ogre17->PhysicsFrameListener->Animate_State2 = Player_Ent->getAnimationState("IdleTop");

	// Enable both of them and set them to loop.
	App->Ogre17->PhysicsFrameListener->Animate_State->setLoop(true);
	App->Ogre17->PhysicsFrameListener->Animate_State2->setLoop(true);
	App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(true);
	App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(true);

	App->Ogre17->PhysicsFrameListener->Animate_Ogre = 1;
}

// *************************************************************************
// *	  					Initialize Terry Bernie						   *
// *************************************************************************
void GD_Player::Initialize(const Ogre::Vector3 p, float mass, float radius, float height)
{
	// ------------------- Ogre
	Player_Ent = App->Ogre17->mSceneMgr->createEntity("Player_1","Sinbad.mesh",App->Ogre17->PermResourceGroup);
	Player_Node = App->Ogre17->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Player_Node->attachObject(Player_Ent); 
	Player_Node->setPosition(p.x, p.y, p.z);

	// ------------------------ Bulet
	btVector3 pos = btVector3(p.x, p.y, p.z);
	btVector3 inertia = btVector3(0, 0, 0);
	btQuaternion rot = btQuaternion(1, 0, 0, 0);
	btDefaultMotionState *state = new btDefaultMotionState(btTransform(rot, pos));

	mShape = new btCapsuleShape(btScalar(radius), btScalar(height));
	mObject = new btRigidBody(mass, state, mShape, inertia);
	mObject->setActivationState(DISABLE_DEACTIVATION);
	mObject->setAngularFactor(0.0);

	mObject->setUserPointer(Player_Node);

	mObject->setUserIndex(Enums::Usage_Player);
	
	
	int f = mObject->getCollisionFlags();
	mObject->setCollisionFlags(f|btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
	
	App->GDCL_Bullet->dynamicsWorld->addRigidBody(mObject);

	PlayerAdded = 1;

	btCollisionWorld* Poo = NULL;
	PostStep(Poo);
}

// *************************************************************************
// *	  					Adjust_CapsuleTerry Bernie					   *
// *************************************************************************
void GD_Player::Adjust_Capsule(void)
{
	mShape = new btCapsuleShape(btScalar(Capsule_Radius), btScalar(Capsule_Height));
	mObject->setCollisionShape(mShape);
}

// *************************************************************************
// *	  					Stop Terry Bernie							   *
// *************************************************************************
void GD_Player::Stop(void)
{

	mObject->setLinearVelocity(btVector3(0,0,0));

	App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(false);
	App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(false);
	App->Ogre17->PhysicsFrameListener->Animate_State = Player_Ent->getAnimationState("IdleBase");
	App->Ogre17->PhysicsFrameListener->Animate_State2 = Player_Ent->getAnimationState("IdleTop");
	App->Ogre17->PhysicsFrameListener->Animate_State->setLoop(true);
	App->Ogre17->PhysicsFrameListener->Animate_State2->setLoop(true);
	App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(true);
	App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(true);

}

// *************************************************************************
// *	  					Forward Terry Bernie						   *
// *************************************************************************
void GD_Player::Forward(void)
{
	if(PlayerAdded == 1)
	{
		if(IsMOving == 0)
		{
			App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(false);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(false);
			App->Ogre17->PhysicsFrameListener->Animate_State = Player_Ent->getAnimationState("RunBase");
			App->Ogre17->PhysicsFrameListener->Animate_State2 = Player_Ent->getAnimationState("RunTop");
			App->Ogre17->PhysicsFrameListener->Animate_State->setLoop(true);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setLoop(true);
			App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(true);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(true);
		}

		btVector3 vel;

		btTransform xform = mObject->getWorldTransform();
		btVector3 cur = mObject->getLinearVelocity();
		btVector3 basis = xform.getBasis()[2];
		vel = -Ground_speed * 10 * basis;
		mObject->setLinearVelocity(btVector3(vel[0], cur[1], vel[2]));
		Check_Collisions();
	}
}

// *************************************************************************
// *	  					Move_Right Terry Bernie						   *
// *************************************************************************
void GD_Player::Move_Right(void)
{
	if (PlayerAdded == 1)
	{
		if (IsMOving == 0)
		{

			App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(false);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(false);
			App->Ogre17->PhysicsFrameListener->Animate_State = Player_Ent->getAnimationState("RunBase");
			App->Ogre17->PhysicsFrameListener->Animate_State2 = Player_Ent->getAnimationState("RunTop");
			App->Ogre17->PhysicsFrameListener->Animate_State->setLoop(true);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setLoop(true);
			App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(true);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(true);

		}

		btVector3 vel;

		btTransform xform = mObject->getWorldTransform();
		btVector3 cur = mObject->getLinearVelocity();
		btVector3 basis = xform.getBasis()[2];
		vel = -Ground_speed * 10 * basis;

		mObject->setLinearVelocity(btVector3(vel[2], cur[1], -vel[0]));

		Check_Collisions();
	}
}

// *************************************************************************
// *	  					Move_Left Terry Bernie						   *
// *************************************************************************
void GD_Player::Move_Left(void)
{
	if (PlayerAdded == 1)
	{
		if (IsMOving == 0)
		{

			App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(false);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(false);
			App->Ogre17->PhysicsFrameListener->Animate_State = Player_Ent->getAnimationState("RunBase");
			App->Ogre17->PhysicsFrameListener->Animate_State2 = Player_Ent->getAnimationState("RunTop");
			App->Ogre17->PhysicsFrameListener->Animate_State->setLoop(true);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setLoop(true);
			App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(true);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(true);

		}

		btVector3 vel;

		btTransform xform = mObject->getWorldTransform();
		btVector3 cur = mObject->getLinearVelocity();
		btVector3 basis = xform.getBasis()[2];
		vel = -Ground_speed * 10 * basis;

		mObject->setLinearVelocity(btVector3(-vel[2], cur[1], vel[0]));

		Check_Collisions();
	}
}

// *************************************************************************
// *	  					Back Terry Bernie							   *
// *************************************************************************
void GD_Player::Back(void)
{
	if(PlayerAdded == 1)
	{
		if(IsMOving_Back == 0)
		{
			App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(false);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(false);
			App->Ogre17->PhysicsFrameListener->Animate_State = Player_Ent->getAnimationState("RunBase");
			App->Ogre17->PhysicsFrameListener->Animate_State2 = Player_Ent->getAnimationState("RunTop");
			App->Ogre17->PhysicsFrameListener->Animate_State->setLoop(true);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setLoop(true);
			App->Ogre17->PhysicsFrameListener->Animate_State->setEnabled(true);
			App->Ogre17->PhysicsFrameListener->Animate_State2->setEnabled(true);
		}

		btVector3 vel;

		btTransform xform = mObject->getWorldTransform();
		btVector3 cur = mObject->getLinearVelocity();
		btVector3 basis = xform.getBasis()[2];
		vel = Ground_speed * 10 * basis;
		mObject->setLinearVelocity(btVector3(vel[0], cur[1], vel[2]));
		Check_Collisions();
	}
}

// *************************************************************************
// *	  					Rotate Terry Bernie							   *
// *************************************************************************
void GD_Player::Rotate(const Ogre::Vector3 axis, bool normalize)
{
	if(PlayerAdded == 1)
	{
		btTransform xform = mObject->getWorldTransform();
		btMatrix3x3 R = xform.getBasis();
		R = R * btMatrix3x3(btQuaternion(btVector3(axis[0], axis[1], axis[2]), TurnRate));

		if(normalize) {
			R[0].normalize();
			R[2].normalize();
			R[1] = R[0].cross(R[2]);
		}

		xform.setBasis(R);
		mObject->setWorldTransform(xform);
	}
}

// *************************************************************************
// *	  					Rotate Terry Bernie							   *
// *************************************************************************
void GD_Player::Rotate_FromCam(const Ogre::Vector3 axis, float delta, bool normalize)
{
	if(PlayerAdded == 1)
	{
		btTransform xform = mObject->getWorldTransform();
		btMatrix3x3 R = xform.getBasis();
		R = R * btMatrix3x3(btQuaternion(btVector3(axis[0], axis[1], axis[2]), delta));

		if(normalize) {
			R[0].normalize();
			R[2].normalize();
			R[1] = R[0].cross(R[2]);
		}

		xform.setBasis(R);
		mObject->setWorldTransform(xform);
	}
}

// *************************************************************************
// *	  					Jump Terry Bernie							   *
// *************************************************************************
void GD_Player::Jump(const Ogre::Vector3 axis, float force)
{
	btVector3 pos = mObject->getWorldTransform().getOrigin();
	pos[1] = pos[1] + 0.2;

	mObject->getWorldTransform().setOrigin(btVector3(pos[0], pos[1], pos[2]));

	/*if(PlayerAdded == 1)
	{
		if(mOnGround == 1) 
		{
			mObject->applyForce(btVector3(0,330,0),btVector3(0,0,0));
		}
	}*/
}

// *************************************************************************
// *	  					Rotate Terry Bernie							   *
// *************************************************************************
bool GD_Player::OnGround() const
{
 return mOnGround;
}

//void SimpleCharacter::PreStep(btCollisionWorld *collisionWorld, btScalar dt)
//{
// if(mHighSlope) {
//  btVector3 uAxis = mSlopeNormal.cross(btVector3(0, 1, 0)).normalize();
//  btVector3 vAxis = uAxis.cross(mSlopeNormal);
//  btVector3 fixVel = vAxis / mSlopeNormal.dot(btVector3(0, 1, 0));
//  mObject->setLinearVelocity(mObject->getLinearVelocity() -fixVel);
// }
//
// // step up character
// Step(mObject, mStepHeight);
//}

// need to use ray cast for ground collision to handle stair case
#define __RAYTEST__

// *************************************************************************
// *	  					PostStep Terry Bernie						   *
// *************************************************************************
void GD_Player::PostStep(btCollisionWorld *collisionWorld)
{
	const float STEP_HEIGHT = 5.0;

	btVector3 from = mObject->getWorldTransform().getOrigin();
	btVector3 to = from - btVector3(0,STEP_HEIGHT, 0);

	// detect ground collision and update "on ground" status
	ClosestNotMeRayResultCallback callback(mObject);
	App->GDCL_Bullet->dynamicsWorld->getCollisionWorld()->rayTest(from, to, callback);
	
	// check there is something below the character
	if(callback.hasHit()) 
	{
		btVector3 end = from + (to - from) * callback.m_closestHitFraction;
		btVector3 normal = callback.m_hitNormalWorld;

		// slope test
		btScalar slopeDot = normal.dot(btVector3(0, 1, 0));
		//  mHighSlope = (slopeDot < 0.6) ? true : false;
		//  mSlopeNormal = normal;

		// compute the distance to the floor
		float distance = btDistance(end, from);

		if(distance > 1.0 )
		{
			mOnGround = 1;
		}
	}
	else
	{
		mOnGround = false;
	}
} 

// *************************************************************************
// *	  				Check_Collisions Terry Bernie					   *
// *************************************************************************
void GD_Player::Check_Collisions(void)
{
	int PlayerIndex = 0;
	int UsageIndex = 0;
	
	/* Browse all collision pairs */
	int numManifolds = App->GDCL_Bullet->dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i=0; i<numManifolds; i++)
	{
		btPersistentManifold* contactManifold = App->GDCL_Bullet->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		PlayerIndex = obA->getUserIndex(); // Should Be Player

		if ( PlayerIndex == Enums::Usage_Player)
		{
			Life_Time = 0;
			//Distance = 0;
			ColisionIndex = obB->getUserIndex2(); // Object Index

			UsageIndex = obB->getUserIndex();

			//------------------------------------------ Sound
			if(UsageIndex == Enums::Usage_Sound)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j=0;j<numContacts;j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if(App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered == 0)
						{
							App->GDCL_Collision->Sound_Entity(ColisionIndex);
							Last_ColisionIndex = ColisionIndex;
						}
					}
					else if(Life_Time < 10)
					{
						if(App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered == 1)
						{
							App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered = 0;
						}
					}
				}
			}

			//------------------------------------------ Message
			if(UsageIndex == Enums::Usage_Message)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j=0;j<numContacts;j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if(App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered == 0)
						{
							App->GDCL_Collision->Message_Entity(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if(App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered == 1)
						{
							int Stock_Index = App->GDCL_Scene_Data->S_Object[ColisionIndex]->Entity[0].Stock_mIndex;
							App->GDCL_Scene_Data->S_Messages[Stock_Index]->overlay->hide();
							App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered = 0;
						}
					}
				}
			}

			if (UsageIndex == Enums::Usage_Colectable)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{
					App->GDCL_Collision->Do_Collectable(ColisionIndex);
					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if (App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered == 0)
						{

							App->GDCL_Collision->Do_Collectable(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if (App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered == 1)
						{

						}
					}
				}
			}

			//------------------------------------------
			if(UsageIndex == Enums::Usage_Move)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j=0;j<numContacts;j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if(App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered == 0)
						{
							App->GDCL_Collision->Move_Entity(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if(App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered == 1)
						{
							/*int Stock_Index = App->GDCL_Scene_Data->S_Object[ColisionIndex]->Entity[0].Stock_mIndex;
							App->GDCL_Scene_Data->S_Messages[Stock_Index]->overlay->hide();
							App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered = 0;*/
						}
					}
				}
			}

			if (UsageIndex == Enums::Usage_Teleport)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{
					App->GDCL_Collision->Do_Teleport(ColisionIndex);
					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if (App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered == 0)
						{

							App->GDCL_Collision->Do_Teleport(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if (App->GDCL_Scene_Data->S_Object[ColisionIndex]->Triggered == 1)
						{

						}
					}
				}
			}


			// --------------------------------

		}
		
	}
}
