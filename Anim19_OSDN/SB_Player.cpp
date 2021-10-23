/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Player.h"


SB_Player::SB_Player()
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
	Ground_speed = 4.2;
	PlayerHeight =16.0;
	TurnRate = 0.04;

	StartPos.x = 0;
	StartPos.y = -50;
	StartPos.z = 0;

	Capsule_Mass = 1.0;
	Capsule_Radius = 4.4;
	Capsule_Height = 17.0;

	strcpy(PlayerName, "Player_1");

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
}


SB_Player::~SB_Player()
{
}

// *************************************************************************
// *	  						SetUp Terry Bernie						   *
// *************************************************************************
void SB_Player::SetUp(void)
{
	Initialize(StartPos, Capsule_Mass, Capsule_Radius, Capsule_Height);
	CameraPitch = App->Cl19_Ogre->mSceneMgr->createCamera("PlayerPitch");
}

// *************************************************************************
// *	  						Load_Player Terry Bernie				   *
// *************************************************************************
void SB_Player::Load_Player(void)
{
	Initialize(StartPos, Capsule_Mass, Capsule_Radius, Capsule_Height);

	CameraPitch = App->Cl19_Ogre->mSceneMgr->createCamera("PlayerPitch");

}

// *************************************************************************
// *	  					Initialize Terry Bernie						   *
// *************************************************************************
void SB_Player::Initialize(const Ogre::Vector3 p, float mass, float radius, float height)
{
	
	// ------------------- Ogre
	if (Player_Ent && Player_Node)
	{
		App->Cl19_Ogre->mSceneMgr->destroySceneNode(Player_Node);
		App->Cl19_Ogre->mSceneMgr->destroyEntity(Player_Ent);
		Player_Ent = nullptr;
		Player_Node = nullptr;

	}

	Player_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("Player_1", "axes.mesh", App->Cl19_Ogre->PermResourceGroup);
	Player_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Player_Node->attachObject(Player_Ent);
	Player_Node->setPosition(p.x, p.y, p.z);

	Player_Node->setVisible(false);

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
void SB_Player::Adjust_Capsule(void)
{
	mShape = new btCapsuleShape(btScalar(Capsule_Radius), btScalar(Capsule_Height));
	mObject->setCollisionShape(mShape);
}

// *************************************************************************
// *	  					Stop Terry Bernie							   *
// *************************************************************************
void SB_Player::Stop(void)
{

	mObject->setLinearVelocity(btVector3(0, 0, 0));
}

// *************************************************************************
// *	  					Forward Terry Bernie						   *
// *************************************************************************
void SB_Player::Forward(float delta)
{
	if (PlayerAdded == 1)
	{
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

		Check_Collisions();
	}
}

// *************************************************************************
// *	  					Move_Right Terry Bernie						   *
// *************************************************************************
void SB_Player::Move_Right(void)
{
	if (PlayerAdded == 1)
	{
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
void SB_Player::Move_Left(void)
{
	if (PlayerAdded == 1)
	{
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
void SB_Player::Back(void)
{
	if (PlayerAdded == 1)
	{
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
void SB_Player::Rotate(const Ogre::Vector3 axis, bool normalize)
{
	if (PlayerAdded == 1)
	{
		btTransform xform = mObject->getWorldTransform();
		btMatrix3x3 R = xform.getBasis();
		R = R * btMatrix3x3(btQuaternion(btVector3(axis[0], axis[1], axis[2]), TurnRate));

		if (normalize) {
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
void SB_Player::Rotate_FromCam(const Ogre::Vector3 axis, float delta, bool normalize)
{
	if (PlayerAdded == 1)
	{
		btTransform xform = mObject->getWorldTransform();
		btMatrix3x3 R = xform.getBasis();
		R = R * btMatrix3x3(btQuaternion(btVector3(axis[0], axis[1], axis[2]), delta));

		if (normalize) {
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
void SB_Player::Jump(const Ogre::Vector3 axis, float force)
{
	btVector3 pos = mObject->getWorldTransform().getOrigin();
	pos[1] = pos[1] + 0.2;

	mObject->getWorldTransform().setOrigin(btVector3(pos[0], pos[1], pos[2]));

}

// *************************************************************************
// *	  					Rotate Terry Bernie							   *
// *************************************************************************
bool SB_Player::OnGround() const
{
	return mOnGround;
}

// need to use ray cast for ground collision to handle stair case
#define __RAYTEST__

// *************************************************************************
// *	  					PostStep Terry Bernie						   *
// *************************************************************************
void SB_Player::PostStep(btCollisionWorld *collisionWorld)
{
	
}

// *************************************************************************
// *	  				Check_Collisions Terry Bernie					   *
// *************************************************************************
void SB_Player::Check_Collisions(void)
{
	int PlayerIndex = 0;
	int UsageIndex = 0;

	/* Browse all collision pairs */
	int numManifolds = App->Cl_Bullet->dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i<numManifolds; i++)
	{
		btPersistentManifold* contactManifold = App->Cl_Bullet->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		PlayerIndex = obA->getUserIndex(); // Should Be Player

		if (PlayerIndex == Enums::Usage_Player)
		{
			Life_Time = 0;
			//Distance = 0;
			ColisionIndex = obB->getUserIndex2(); // Object Index

			UsageIndex = obB->getUserIndex();

			// Sound Entity
			if (UsageIndex == Enums::Usage_Sound)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j<numContacts; j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 0)
						{
							///App->Cl_Scene_Data->Sound_Entity(ColisionIndex);
							Last_ColisionIndex = ColisionIndex;
						}
					}
					else if (Life_Time < 10)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 1)
						{
							App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered = 0;
						}
					}
				}
			}

			// Message Entity
			if (UsageIndex == Enums::Usage_Message)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j<numContacts; j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 0)
						{
							App->Cl_Collision->Message_Entity(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 1)
						{
							int Stock_Index = App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Entity[0].Stock_mIndex;
							App->Cl_Panels_Com->Show_Overlay(0, Stock_Index);
							App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered = 0;
						}
					}
				}
			}

			// Move Entity
			if (UsageIndex == Enums::Usage_Move)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j<numContacts; j++)
				{

					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 0)
						{
							App->Cl_Collision->Move_Entity(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[ColisionIndex]->Triggered == 1)
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
void SB_Player::Save_Location(char* name)
{

	int Count = App->Cl_Scene_Data->Player_Location_Count;

	App->Cl_Scene_Data->S_Player_Locations[Count] = new Player_Location_type();
	App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted = 0;

	App->Cl_Scene_Data->S_Player_Locations[Count]->Location_ID = App->Cl_Scene_Data->Locations_ID_Counter;
	App->Cl_Scene_Data->Locations_ID_Counter++;


	strcpy(App->Cl_Scene_Data->S_Player_Locations[Count]->Name, name);
	App->Cl_Scene_Data->S_Player_Locations[Count]->Current_Position = App->SBC_Player->Player_Node->getPosition();
	App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Position = App->SBC_Player->mObject->getWorldTransform().getOrigin();
	App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation = App->SBC_Player->mObject->getWorldTransform().getRotation();
	App->Cl_Scene_Data->Player_Location_Count++;

}

// *************************************************************************
// *	  					Goto_Locatio Terry							   *
// *************************************************************************
void SB_Player::Goto_Location(int Index)
{

	Player_Node->setPosition(App->Cl_Scene_Data->S_Player_Locations[Index]->Current_Position);

	mObject->getWorldTransform().setOrigin(App->Cl_Scene_Data->S_Player_Locations[Index]->Physics_Position);

	mObject->getWorldTransform().setRotation(App->Cl_Scene_Data->S_Player_Locations[Index]->Physics_Rotation);
}
