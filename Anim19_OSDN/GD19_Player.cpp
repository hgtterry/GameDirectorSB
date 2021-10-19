#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_Player.h"


GD19_Player::GD19_Player(void)
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

	is_Animated = 0;

	Forward_Timer = 0;

	Current_Position.ZERO;
	Physics_Position.setZero();
	Physics_Rotation = btQuaternion(1, 0, 0, 0);

	ListViewItem = NULL;
}


GD19_Player::~GD19_Player(void)
{
}

// *************************************************************************
// *	  						SetUp Terry Bernie						   *
// *************************************************************************
void GD19_Player::SetUp(void)
{
	Initialize(StartPos,Capsule_Mass, Capsule_Radius,Capsule_Height);
	CameraPitch = App->Cl19_Ogre->mSceneMgr->createCamera("PlayerPitch");

	Player_Ent->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	// Get the two halves of the idle animation.
	App->Cl19_Ogre->OgreListener->Animate_State = Player_Ent->getAnimationState("IdleBase");
	App->Cl19_Ogre->OgreListener->Animate_State2 = Player_Ent->getAnimationState("IdleTop");

	// Enable both of them and set them to loop.
	App->Cl19_Ogre->OgreListener->Animate_State->setLoop(true);
	App->Cl19_Ogre->OgreListener->Animate_State2->setLoop(true);
	App->Cl19_Ogre->OgreListener->Animate_State->setEnabled(true);
	App->Cl19_Ogre->OgreListener->Animate_State2->setEnabled(true);

	App->Cl19_Ogre->OgreListener->Animate_Ogre = 1;
}

// *************************************************************************
// *	  						Load_Player Terry Bernie				   *
// *************************************************************************
void GD19_Player::Load_Player(void)
{
	Initialize(StartPos,Capsule_Mass, Capsule_Radius,Capsule_Height);

//	App->Cl_FileView_V2->Add_Player_Name(App->Cl_Player->PlayerName);

//	CameraPitch = App->Cl_Ogre->mSceneMgr->createCamera("PlayerPitch");
	
	//Player_Ent->getSkeleton()->setBlendMode(ANIMBLEND_CUMULATIVE);

	//// Get the two halves of the idle animation.
	//App->Cl19_Ogre->OgreListener->Animate_State = Player_Ent->getAnimationState("IdleBase");
	//App->Cl19_Ogre->OgreListener->Animate_State2 = Player_Ent->getAnimationState("IdleTop");

	//// Enable both of them and set them to loop.
	//App->Cl19_Ogre->OgreListener->Animate_State->setLoop(true);
	//App->Cl19_Ogre->OgreListener->Animate_State2->setLoop(true);
	//App->Cl19_Ogre->OgreListener->Animate_State->setEnabled(true);
	//App->Cl19_Ogre->OgreListener->Animate_State2->setEnabled(true);

	//App->Cl19_Ogre->OgreListener->Animate_Ogre = 1;
}

// *************************************************************************
// *	  					Initialize Terry Bernie						   *
// *************************************************************************
void GD19_Player::Initialize(const Ogre::Vector3 p, float mass, float radius, float height)
{
	// Bug been Called Twice
	// ------------------- Ogre

	if (Player_Ent && Player_Node)
	{
		App->Cl19_Ogre->mSceneMgr->destroySceneNode(Player_Node);
		App->Cl19_Ogre->mSceneMgr->destroyEntity(Player_Ent);
		Player_Ent = nullptr;
		Player_Node = nullptr;

	}
	
	Player_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("Player_1","axes.mesh",App->Cl19_Ogre->PermResourceGroup);
	Player_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Player_Node->attachObject(Player_Ent); 
	Player_Node->setPosition(p.x, p.y, p.z);

	// ------------------------ Bulet
	btVector3 pos = btVector3(p.x, p.y, p.z);
	btVector3 inertia = btVector3(0, 0, 0);
	btQuaternion rot = btQuaternion(1, 0, 0, 0);
	btDefaultMotionState *state = new btDefaultMotionState(btTransform(rot, pos));

	//mShape = new btSphereShape(btScalar(radius));
	mShape = new btCapsuleShape(btScalar(radius), btScalar(height));
	mObject = new btRigidBody(mass, state, mShape, inertia);
	mObject->setActivationState(DISABLE_DEACTIVATION);
	mObject->setAngularFactor(0.0);

	mObject->setUserPointer(Player_Node);

	mObject->setUserIndex(Enums::Usage_Player);
	
	
	int f = mObject->getCollisionFlags();
	mObject->setCollisionFlags(f|btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
	
	App->Cl_Bullet->dynamicsWorld->addRigidBody(mObject);

	// Save for later
	Current_Position = Player_Node->getPosition(); 
	Physics_Position = mObject->getWorldTransform().getOrigin();
	Physics_Rotation = mObject->getWorldTransform().getRotation();

	PlayerAdded = 1;

	btCollisionWorld* Poo = NULL;
	PostStep(Poo);
}

// *************************************************************************
// *	  					Initialize_New Terry Bernie					   *
// *************************************************************************
void GD19_Player::Initialize_New(const Ogre::Vector3 p, float mass, float radius, float height)
{
	// Bug been Called Twice
	// ------------------- Ogre
	Player_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("Player_1", "Sinbad.mesh", App->Cl19_Ogre->PermResourceGroup);
	Player_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Player_Node->attachObject(Player_Ent);
	Player_Node->setPosition(p.x, p.y, p.z);

	// ------------------------ Bulet
	btVector3 pos = btVector3(p.x, p.y, p.z);
	btVector3 inertia = btVector3(0, 0, 0);
	btQuaternion rot = btQuaternion(1, 0, 0, 0);
	btDefaultMotionState* state = new btDefaultMotionState(btTransform(rot, pos));

	//mShape = new btSphereShape(btScalar(radius));
	mShape = new btCapsuleShape(btScalar(radius), btScalar(height));
	mObject = new btRigidBody(mass, state, mShape, inertia);
	mObject->setActivationState(DISABLE_DEACTIVATION);
	mObject->setAngularFactor(0.0);

	mObject->setUserPointer(Player_Node);

	mObject->setUserIndex(Enums::Usage_Player);


	int f = mObject->getCollisionFlags();
	mObject->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(mObject);

	// Save for later
	Current_Position = Player_Node->getPosition();
	Physics_Position = mObject->getWorldTransform().getOrigin();
	Physics_Rotation = mObject->getWorldTransform().getRotation();

	PlayerAdded = 1;

	btCollisionWorld* Poo = NULL;
	PostStep(Poo);
}

// *************************************************************************
// *	  					Adjust_CapsuleTerry Bernie					   *
// *************************************************************************
void GD19_Player::Adjust_Capsule(void)
{
	mShape = new btCapsuleShape(btScalar(Capsule_Radius), btScalar(Capsule_Height));
	mObject->setCollisionShape(mShape);
}

// *************************************************************************
// *	  					Stop Terry Bernie							   *
// *************************************************************************
void GD19_Player::Stop(void)
{

	mObject->setLinearVelocity(btVector3(0,0,0));

	if (is_Animated == 1)
	{
		App->Cl19_Ogre->OgreListener->Animate_State->setEnabled(false);
		App->Cl19_Ogre->OgreListener->Animate_State2->setEnabled(false);
		App->Cl19_Ogre->OgreListener->Animate_State = Player_Ent->getAnimationState("IdleBase");
		App->Cl19_Ogre->OgreListener->Animate_State2 = Player_Ent->getAnimationState("IdleTop");
		App->Cl19_Ogre->OgreListener->Animate_State->setLoop(true);
		App->Cl19_Ogre->OgreListener->Animate_State2->setLoop(true);
		App->Cl19_Ogre->OgreListener->Animate_State->setEnabled(true);
		App->Cl19_Ogre->OgreListener->Animate_State2->setEnabled(true);
	}

}

// *************************************************************************
// *	  					Forward Terry Bernie						   *
// *************************************************************************
void GD19_Player::Forward(float delta)
{
	if(PlayerAdded == 1)
	{
		if (is_Animated == 1 && IsMOving == 0)
		{

			/*App->Cl_Ogre->OgreListener->Animate_State->setEnabled(false);
			App->Cl_Ogre->OgreListener->Animate_State2->setEnabled(false);
			App->Cl_Ogre->OgreListener->Animate_State = Player_Ent->getAnimationState("RunBase");
			App->Cl_Ogre->OgreListener->Animate_State2 = Player_Ent->getAnimationState("RunTop");
			App->Cl_Ogre->OgreListener->Animate_State->setLoop(true);
			App->Cl_Ogre->OgreListener->Animate_State2->setLoop(true);
			App->Cl_Ogre->OgreListener->Animate_State->setEnabled(true);
			App->Cl_Ogre->OgreListener->Animate_State2->setEnabled(true);*/

		}

		
		Forward_Timer -= delta;

		if (Forward_Timer < 0)
		{
			Forward_Timer = 0.01; // 0.01

			btVector3 vel;

			btTransform xform = mObject->getWorldTransform();
			btVector3 cur = mObject->getLinearVelocity();
			btVector3 basis = xform.getBasis()[2];
			vel = -Ground_speed * 10 * basis;
			mObject->setLinearVelocity(btVector3(vel[0], cur[1], vel[2]));
			
		}

		//App->CL10_Utils->log(delta);
		Check_Collisions();
	}
}

// *************************************************************************
// *	  					Move_Right Terry Bernie						   *
// *************************************************************************
void GD19_Player::Move_Right(void)
{
	if (PlayerAdded == 1)
	{
		if (is_Animated == 1 && IsMOving == 0)
		{

			/*App->Cl_Ogre->OgreListener->Animate_State->setEnabled(false);
			App->Cl_Ogre->OgreListener->Animate_State2->setEnabled(false);
			App->Cl_Ogre->OgreListener->Animate_State = Player_Ent->getAnimationState("RunBase");
			App->Cl_Ogre->OgreListener->Animate_State2 = Player_Ent->getAnimationState("RunTop");
			App->Cl_Ogre->OgreListener->Animate_State->setLoop(true);
			App->Cl_Ogre->OgreListener->Animate_State2->setLoop(true);
			App->Cl_Ogre->OgreListener->Animate_State->setEnabled(true);
			App->Cl_Ogre->OgreListener->Animate_State2->setEnabled(true);*/

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
void GD19_Player::Move_Left(void)
{
	if (PlayerAdded == 1)
	{
		if (is_Animated == 1 && IsMOving == 0)
		{

			/*App->Cl_Ogre->OgreListener->Animate_State->setEnabled(false);
			App->Cl_Ogre->OgreListener->Animate_State2->setEnabled(false);
			App->Cl_Ogre->OgreListener->Animate_State = Player_Ent->getAnimationState("RunBase");
			App->Cl_Ogre->OgreListener->Animate_State2 = Player_Ent->getAnimationState("RunTop");
			App->Cl_Ogre->OgreListener->Animate_State->setLoop(true);
			App->Cl_Ogre->OgreListener->Animate_State2->setLoop(true);
			App->Cl_Ogre->OgreListener->Animate_State->setEnabled(true);
			App->Cl_Ogre->OgreListener->Animate_State2->setEnabled(true);*/

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
void GD19_Player::Back(void)
{
	if(PlayerAdded == 1)
	{
		if(is_Animated == 1 && IsMOving_Back == 0)
		{
			/*App->Cl_Ogre->OgreListener->Animate_State->setEnabled(false);
			App->Cl_Ogre->OgreListener->Animate_State2->setEnabled(false);
			App->Cl_Ogre->OgreListener->Animate_State = Player_Ent->getAnimationState("RunBase");
			App->Cl_Ogre->OgreListener->Animate_State2 = Player_Ent->getAnimationState("RunTop");
			App->Cl_Ogre->OgreListener->Animate_State->setLoop(true);
			App->Cl_Ogre->OgreListener->Animate_State2->setLoop(true);
			App->Cl_Ogre->OgreListener->Animate_State->setEnabled(true);
			App->Cl_Ogre->OgreListener->Animate_State2->setEnabled(true);*/
		}

		btVector3 vel;

		btTransform xform = mObject->getWorldTransform();
		btVector3 cur = mObject->getLinearVelocity();
		btVector3 basis = xform.getBasis()[2];
		vel = Ground_speed * 10 * basis;			 //cur[1],
		mObject->setLinearVelocity(btVector3(vel[0], cur[1], vel[2]));
		Check_Collisions();
	}
}

// *************************************************************************
// *	  					Rotate Terry Bernie							   *
// *************************************************************************
void GD19_Player::Rotate(const Ogre::Vector3 axis, bool normalize)
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
void GD19_Player::Rotate_FromCam(const Ogre::Vector3 axis, float delta, bool normalize)
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
void GD19_Player::Jump(const Ogre::Vector3 axis, float force)
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
bool GD19_Player::OnGround() const
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
void GD19_Player::PostStep(btCollisionWorld *collisionWorld)
{
	//const float STEP_HEIGHT = 5.0;

	//btVector3 from = mObject->getWorldTransform().getOrigin();
	//btVector3 to = from - btVector3(0,STEP_HEIGHT, 0);

	//// detect ground collision and update "on ground" status
	//ClosestNotMeRayResultCallback callback(mObject);
	//App->GDCL_Bullet->dynamicsWorld->getCollisionWorld()->rayTest(from, to, callback);
	//
	//// check there is something below the character
	//if(callback.hasHit()) 
	//{
	//	btVector3 end = from + (to - from) * callback.m_closestHitFraction;
	//	btVector3 normal = callback.m_hitNormalWorld;

	//	// slope test
	//	btScalar slopeDot = normal.dot(btVector3(0, 1, 0));
	//	//  mHighSlope = (slopeDot < 0.6) ? true : false;
	//	//  mSlopeNormal = normal;

	//	// compute the distance to the floor
	//	float distance = btDistance(end, from);

	//	if(distance > 1.0 )
	//	{
	//		mOnGround = 1;
	//	}
	//}
	//else
	//{
	//	mOnGround = false;
	//}
} 

// *************************************************************************
// *	  				Check_Collisions Terry Bernie					   *
// *************************************************************************
void GD19_Player::Check_Collisions(void)
{
	int PlayerIndex = 0;
	int UsageIndex = 0;

	/* Browse all collision pairs */
	int numManifolds = App->Cl_Bullet->dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i=0; i<numManifolds; i++)
	{
		btPersistentManifold* contactManifold = App->Cl_Bullet->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		PlayerIndex = obA->getUserIndex(); // Should Be Player

		if ( PlayerIndex == Enums::Usage_Player)
		{
			Life_Time = 0;
			//Distance = 0;
			ColisionIndex = obB->getUserIndex2(); // Object Index

			UsageIndex = obB->getUserIndex();

			// Sound Entity
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
						if(App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 0)
						{
							///App->Cl_Scene_Data->Sound_Entity(ColisionIndex);
							Last_ColisionIndex = ColisionIndex;
						}
					}
					else if(Life_Time < 10)
					{
						if(App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 1)
						{
							App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered = 0;
						}
					}
				}
			}

			// Message Entity
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
						if(App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 0)
						{
							App->Cl_Collision->Message_Entity(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if(App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 1)
						{
							int Stock_Index = App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Entity[0].Stock_mIndex;
							App->Cl_Panels_Com->Show_Overlay(0, Stock_Index);
							App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered = 0;
						}
					}
				}
			}
			
			// Move Entity
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
						if(App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 0)
						{
							App->Cl_Collision->Move_Entity(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if(App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 1)
						{
							/*int Stock_Index = App->GDCL_Scene_Data->CL_Object[ColisionIndex]->Entity[0].Stock_mIndex;
							App->GDCL_Scene_Data->S_Messages[Stock_Index]->overlay->hide();
							App->GDCL_Scene_Data->CL_Object[ColisionIndex]->Triggered = 0;*/
						}
					}
				}
			}

			// Collectable Entity
			if (UsageIndex == Enums::Usage_Colectable)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{
					App->Cl_Collision->Do_Collectable(ColisionIndex);
					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 0)
						{
							
							App->Cl_Collision->Do_Collectable(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 1)
						{
							
						}
					}
				}
			}

			// Teleport Entity
			if (UsageIndex == Enums::Usage_Teleport)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{
					App->Cl_Collision->Do_Teleport(ColisionIndex);
					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 0)
						{

						///	App->Cl_Scene_Data->Do_Teleport(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 1)
						{

						}
					}
				}
			}
			
			// Environment Entity
			if (UsageIndex == Enums::Usage_Environment)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 0)
						{

							App->Cl_Collision->Do_Environment(ColisionIndex);
							Last_ColisionIndex = ColisionIndex;
						}
					}
					else if (Round < 10)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 1)
						{
							App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered = 0;
						}
					}
				}
			}
		}

	}
}

// *************************************************************************
// *	  					Save_Location Terry							   *
// *************************************************************************
void GD19_Player::Save_Location(char* name)
{

	int Count = App->Cl_Scene_Data->Player_Location_Count;

	App->Cl_Scene_Data->S_Player_Locations[Count] = new Player_Location_type();
	App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted = 0;

	App->Cl_Scene_Data->S_Player_Locations[Count]->Location_ID = App->Cl_Scene_Data->Locations_ID_Counter;
	App->Cl_Scene_Data->Locations_ID_Counter++;


	strcpy(App->Cl_Scene_Data->S_Player_Locations[Count]->Name,name);
	App->Cl_Scene_Data->S_Player_Locations[Count]->Current_Position = App->Cl_Player->Player_Node->getPosition();
	App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Position = App->Cl_Player->mObject->getWorldTransform().getOrigin();
	App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation = App->Cl_Player->mObject->getWorldTransform().getRotation();
	App->Cl_Scene_Data->Player_Location_Count++;
	
}

// *************************************************************************
// *	  					Goto_Locatio Terry							   *
// *************************************************************************
void GD19_Player::Goto_Location(int Index)
{

	Player_Node->setPosition(App->Cl_Scene_Data->S_Player_Locations[Index]->Current_Position);

	mObject->getWorldTransform().setOrigin(App->Cl_Scene_Data->S_Player_Locations[Index]->Physics_Position);

	mObject->getWorldTransform().setRotation(App->Cl_Scene_Data->S_Player_Locations[Index]->Physics_Rotation);
}
