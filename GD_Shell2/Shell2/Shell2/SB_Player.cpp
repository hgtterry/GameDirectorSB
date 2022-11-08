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
#include "BT_App.h"
#include "SB_Player.h"


SB_Player::SB_Player()
{
	Player_Props_HWND = nullptr;

	ShowDebug = 0;
	Show_Physics_Debug = 1;

	Toggle_Objects_Flag = 1;
	Toggle_Physics_Flag = 0;

	Col_Object_Index = 0;
	Last_ColisionIndex = 0;

	Col_numManifolds = 0;
	Col_Player_Index = 0;

	Round = 0;
	Distance = 0;
	Life_Time = 0;

	is_Animated = 0;

	Current_Position.ZERO;
	Physics_Position.setZero();
	Physics_Rotation = btQuaternion(1, 0, 0, 0);
}


SB_Player::~SB_Player()
{
}

// *************************************************************************
// *	  					Reset_Class Bernie							   *
// *************************************************************************
void SB_Player::Reset_Class(void)
{
	int Count = 0;

	//while (Count < App->SBC_Scene->Player_Count) // Remove Ogre Objects
	//{
	//	if (App->SBC_Scene->B_Player[Count])
	//	{
	//		if (App->SBC_Scene->B_Player[Count]->Player_Ent && App->SBC_Scene->B_Player[Count]->Player_Node)
	//		{
	//			App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->SBC_Scene->B_Player[Count]->Player_Node);
	//			App->Cl19_Ogre->mSceneMgr->destroyEntity(App->SBC_Scene->B_Player[Count]->Player_Ent);
	//			App->Cl19_Ogre->mSceneMgr->destroyCamera(App->SBC_Scene->B_Player[Count]->CameraPitch);
	//			App->SBC_Scene->B_Player[Count]->Player_Ent = nullptr;
	//			App->SBC_Scene->B_Player[Count]->Player_Node = nullptr;
	//			App->SBC_Scene->B_Player[Count]->CameraPitch = nullptr;
	//		}

	//		delete App->SBC_Scene->B_Player[Count];
	//		App->SBC_Scene->B_Player[Count] = nullptr;
	//	}

	//	Count++;
	//}

	App->GDCL_Scene_Data->Player_Count = 0;
	App->GDCL_Scene_Data->Player_Added = 0;

}


// *************************************************************************
// *	  					Create_Player_Object Bernie					   *
// *************************************************************************
void SB_Player::Create_Player_Object(void)
{
	int Index = App->GDCL_Scene_Data->Player_Count;

	App->GDCL_Scene_Data->B_Player[Index] = new Base_Player();

	Initialize();

	App->GDCL_Scene_Data->B_Player[Index]->CameraPitch = App->Ogre17->mSceneMgr->createCamera("PlayerPitch10");

	App->GDCL_Scene_Data->Player_Count++;

}

// *************************************************************************
// *	  					Initialize Terry Bernie						   *
// *************************************************************************
void SB_Player::Initialize()
{
	Ogre::Vector3 Pos;

	int Index = App->GDCL_Scene_Data->Player_Count;

	Base_Player* pBase = App->GDCL_Scene_Data->B_Player[Index];

	// ------------------- Ogre
	/*if (pBase->Player_Ent && pBase->Player_Node)
	{
		App->Ogre17->mSceneMgr->destroySceneNode(pBase->Player_Node);
		App->Ogre17->mSceneMgr->destroyEntity(pBase->Player_Ent);
		App->Ogre17->mSceneMgr->destroyCamera(pBase->CameraPitch);
		pBase->Player_Ent = nullptr;
		pBase->Player_Node = nullptr;
		pBase->CameraPitch = nullptr;
	}*/

	pBase->Player_Ent = App->Ogre17->mSceneMgr->createEntity("Player_10", "axes.mesh", App->Ogre17->PermResourceGroup);
	pBase->Player_Node = App->Ogre17->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	pBase->Player_Node->attachObject(pBase->Player_Ent);

	Pos.x = pBase->StartPos.x;
	Pos.y = pBase->StartPos.y;
	Pos.z = pBase->StartPos.z;

	pBase->Player_Node->setPosition(Pos.x, Pos.y, Pos.z);

	pBase->Player_Node->setVisible(true);

	// ------------------------ Bulet
	btVector3 pos = btVector3(Pos.x, Pos.y, Pos.z);
	btVector3 inertia = btVector3(0, 0, 0);
	btQuaternion rot = btQuaternion(0,0,0,1);
	btDefaultMotionState *state = new btDefaultMotionState(btTransform(rot, pos));

	//mShape = new btSphereShape(btScalar(radius));
	pBase->Phys_Shape = new btCapsuleShape(btScalar(pBase->Capsule_Radius), btScalar(pBase->Capsule_Height));
	pBase->Phys_Body = new btRigidBody(pBase->Capsule_Mass, state, pBase->Phys_Shape, inertia);
	pBase->Phys_Body->setActivationState(DISABLE_DEACTIVATION);
	pBase->Phys_Body->setAngularFactor(0.0);

	pBase->Phys_Body->setUserPointer(pBase->Player_Node);

	pBase->Phys_Body->setUserIndex(Enums::Usage_Player);


	int f = pBase->Phys_Body->getCollisionFlags();
	pBase->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	//pBase->Phys_Body->getWorldTransform().setRotation(btQuaternion(1,0,1,1));
	App->GDCL_Scene_Data->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->GDCL_Scene_Data->B_Player[0]->Physics_Rotation);
	App->GDCL_Bullet->dynamicsWorld->addRigidBody(pBase->Phys_Body);

	// Save for later
	Current_Position = pBase->Player_Node->getPosition();
	Physics_Position = pBase->Phys_Body->getWorldTransform().getOrigin();
	Physics_Rotation = pBase->Phys_Body->getWorldTransform().getRotation();

	//pBase->Physics_Rotation = pBase->Phys_Body->getWorldTransform().getRotation();

	App->GDCL_Scene_Data->Player_Added = 1;

}

// *************************************************************************
// *					Hide_Player_Dlg Terry Bernie 					   *
// *************************************************************************
void SB_Player::Hide_Player_Dlg(bool Show)
{
	ShowWindow(Player_Props_HWND, Show);
}

// *************************************************************************
// *	  					Adjust_CapsuleTerry Bernie					   *
// *************************************************************************
void SB_Player::Adjust_Capsule(void)
{
	App->GDCL_Scene_Data->B_Player[0]->Phys_Shape = new btCapsuleShape(btScalar(App->GDCL_Scene_Data->B_Player[0]->Capsule_Radius), btScalar(App->GDCL_Scene_Data->B_Player[0]->Capsule_Height));
	App->GDCL_Scene_Data->B_Player[0]->Phys_Body->setCollisionShape(App->GDCL_Scene_Data->B_Player[0]->Phys_Shape);

}

// *************************************************************************
// *	  					Rotate Terry Bernie							   *
// *************************************************************************
bool SB_Player::OnGround() const
{
	return App->GDCL_Scene_Data->B_Player[0]->mOnGround;
}

// need to use ray cast for ground collision to handle stair case
#define __RAYTEST__


// *************************************************************************
// *	  				Check_Collisions Terry Bernie					   *
// *************************************************************************
void SB_Player::Check_Collisions(void)
{
	int PlayerIndex = 0;
	int UsageIndex = 0;

	/* Browse all collision pairs */
	int numManifolds = App->GDCL_Bullet->dynamicsWorld->getDispatcher()->getNumManifolds();
	for (int i = 0; i<numManifolds; i++)
	{
		btPersistentManifold* contactManifold = App->GDCL_Bullet->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		PlayerIndex = obA->getUserIndex(); // Should Be Player

		if (PlayerIndex == Enums::Usage_Player)
		{
			Life_Time = 0;
			//Distance = 0;
			Col_Object_Index = obB->getUserIndex2(); // Object Index

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

					/*if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
						{
							///App->Cl_Scene_Data->Sound_Entity(ColisionIndex);
							Last_ColisionIndex = Col_Object_Index;
						}
					}
					else if (Life_Time < 10)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
						{
							App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered = 0;
						}
					}*/
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

					/*if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
						{
							App->Cl_Collision->Message_Entity(Col_Object_Index);
						}
					}
					else if (Round == 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
						{
							int Stock_Index = App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Entity[0].Stock_mIndex;
							App->Cl_Panels_Com->Show_Overlay(0, Stock_Index);
							App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered = 0;
						}
					}*/
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

					//if (Round < 0)
					//{
					//	if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
					//	{
					//		App->Cl_Collision->Move_Entity(Col_Object_Index);
					//	}
					//}
					//else if (Round == 0)
					//{
					//	if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
					//	{
					//		/*int Stock_Index = App->GDCL_Scene_Data->CL_Object[ColisionIndex]->Entity[0].Stock_mIndex;
					//		App->GDCL_Scene_Data->S_Messages[Stock_Index]->overlay->hide();
					//		App->GDCL_Scene_Data->CL_Object[ColisionIndex]->Triggered = 0;*/
					//	}
					//}
				}
			}

			// Collectable Entity
			if (UsageIndex == Enums::Usage_Colectable)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{
					//App->Cl_Collision->Do_Collectable(Col_Object_Index);
					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					/*if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
						{

							App->Cl_Collision->Do_Collectable(Col_Object_Index);
						}
					}
					else if (Round == 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
						{

						}
					}*/
				}
			}

			// Teleport Entity
			if (UsageIndex == Enums::Usage_Teleport)
			{
				int numContacts = contactManifold->getNumContacts();
				for (int j = 0; j < numContacts; j++)
				{
					//App->Cl_Collision->Do_Teleport(Col_Object_Index);
					btManifoldPoint& pt = contactManifold->getContactPoint(j);

					Life_Time = pt.getLifeTime();
					Distance = pt.getDistance();
					Round = (int)Distance;

					/*if (Round < 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
						{

							///	App->Cl_Scene_Data->Do_Teleport(ColisionIndex);
						}
					}
					else if (Round == 0)
					{
						if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
						{

						}
					}*/
				}
			}

			// Environment Entity
			//if (UsageIndex == Enums::Usage_Environment)
			//{
			//	int numContacts = contactManifold->getNumContacts();
			//	for (int j = 0; j < numContacts; j++)
			//	{

			//		btManifoldPoint& pt = contactManifold->getContactPoint(j);

			//		Life_Time = pt.getLifeTime();
			//		Distance = pt.getDistance();
			//		Round = (int)Distance;

			//		/*if (Round < 0)
			//		{
			//			if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 0)
			//			{

			//				App->Cl_Collision->Do_Environment(Col_Object_Index);
			//				Last_ColisionIndex = Col_Object_Index;
			//			}
			//		}
			//		else if (Round < 10)
			//		{
			//			if (App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered == 1)
			//			{
			//				App->Cl_Scene_Data->Cl_Object[Col_Object_Index]->Triggered = 0;
			//			}
			//		}*/
			//	}
			//}
		}

	}
}

// *************************************************************************
// *	  				Check_Collisions_New Terry Flanigan				   *
// *************************************************************************
void SB_Player::Check_Collisions_New(void)
{
	int UsageIndex = 0;
	Col_Player_Index = 0;
	Col_Usage_Index = 0;
	Col_numManifolds = 0;

	/* Browse all collision pairs */
	Col_numManifolds = App->GDCL_Bullet->dynamicsWorld->getDispatcher()->getNumManifolds();

	for (int i = 0; i < Col_numManifolds; i++)
	{
		btPersistentManifold* contactManifold = App->GDCL_Bullet->dynamicsWorld->getDispatcher()->getManifoldByIndexInternal(i);
		btCollisionObject* obA = (btCollisionObject*)(contactManifold->getBody0());
		btCollisionObject* obB = (btCollisionObject*)(contactManifold->getBody1());

		Col_Player_Index = obA->getUserIndex();  // Should Be Player
		Col_Object_Index = obB->getUserIndex2(); // Object Index

		UsageIndex = obB->getUserIndex();
		if (Col_Player_Index == Enums::Usage_Player)
		{
			Col_Object_Index = obB->getUserIndex2(); // Object Index
			Col_Usage_Index = obB->getUserIndex();

			if (Col_Usage_Index == 123)
			{
				//App->CL_Vm_ImGui->Show_Collision_Debug = 0;
			}
			else
			{
				//App->CL_Vm_ImGui->Show_Collision_Debug = 1;

				Col_Usage_Index = obB->getUserIndex();

				// -------------------- Message Collision
				//if (Col_Usage_Index == Enums::Usage_Message)
				//{
				//
				//	int numContacts = contactManifold->getNumContacts();
				//	for (int j = 0; j < numContacts; j++)
				//	{
				//		btManifoldPoint& pt = contactManifold->getContactPoint(j);

				//		Life_Time = pt.getLifeTime();
				//		Distance = pt.getDistance();
				//		Round = (int)Distance;

				//		if (Round < 0)
				//		{
				//			if (App->GDCL_Scene_Data->B_Object[Col_Object_Index]->Triggered == 0)
				//			{
				//				App->SBC_Collision->Message_Entity(Col_Object_Index);
				//			}
				//		}
				//		else if (Round == 0)
				//		{
				//			if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 1)
				//			{
				//				//int MessageIndex = App->SBC_Scene->B_Object[Col_Object_Index]->TextMessage_ID; // Needs_Removing
				//				//App->SBC_Scene->B_Message[MessageIndex]->Show_Panel_Flag = 0;

				//				App->SBC_Scene->B_Object[Col_Object_Index]->Show_Message_Flag = 0;
				//				App->SBC_Scene->B_Object[Col_Object_Index]->Triggered = 0;

				//			}
				//		}
				//	}
				//}

				// -------------------- Sound Collision
				/*if (Col_Usage_Index == Enums::Usage_Sound)
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
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 0)
							{
								App->SBC_Collision->Play_Sound(Col_Object_Index);
								Last_ColisionIndex = Col_Object_Index;
							}
						}
						else if (Life_Time < 10)
						{
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 1)
							{
								App->SBC_Scene->B_Object[Col_Object_Index]->Triggered = 0;
							}
						}
					}
				}*/

				// -------------------- Move Collision
				/*if (Col_Usage_Index == Enums::Usage_Move)
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
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 0)
							{
								App->SBC_Collision->Move_Entity_Collision(Col_Object_Index);
							}
						}
						else if (Round == 0)
						{
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 1)
							{
								
							}
						}
						
					}
				}*/

				// -------------------- Collectable Collision
				/*if (UsageIndex == Enums::Usage_Colectable)
				{
					int numContacts = contactManifold->getNumContacts();
					for (int j = 0; j < numContacts; j++)
					{
						if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 0)
						{
							App->SBC_Collision->Do_Collectable(Col_Object_Index);
						}
					}

				}*/

				// -------------------- Teleport Collision
				/*if (UsageIndex == Enums::Usage_Teleport)
				{
					int numContacts = contactManifold->getNumContacts();
					for (int j = 0; j < numContacts; j++)
					{
						App->SBC_Collision->Do_Teleport(Col_Object_Index);
						btManifoldPoint& pt = contactManifold->getContactPoint(j);

						Life_Time = pt.getLifeTime();
						Distance = pt.getDistance();
						Round = (int)Distance;

						if (Round < 0)
						{
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 0)
							{

								App->SBC_Collision->Do_Teleport(Col_Object_Index);
							}
						}
						else if (Round == 0)
						{
							if (App->SBC_Scene->B_Object[Col_Object_Index]->Triggered == 1)
							{

							}
						}
					}
				}*/
			}
		}
	}

}
// *************************************************************************
// *	  					Save_Location Terry							   *
// *************************************************************************
void SB_Player::Save_Location(char* name)
{

	/*int Count = App->SBC_Scene->Player_Location_Count;

	App->SBC_Scene->B_Locations[Count] = new Base_Locations();

	App->SBC_Scene->B_Locations[Count]->Deleted = 0;

	App->SBC_Scene->B_Locations[Count]->Location_ID = App->SBC_Scene->Locations_ID_Counter;
	App->SBC_Scene->Locations_ID_Counter++;

	strcpy(App->SBC_Scene->B_Locations[Count]->Name, name);
	App->SBC_Scene->B_Locations[Count]->Current_Position = App->SBC_Scene->B_Player[0]->Player_Node->getPosition();
	App->SBC_Scene->B_Locations[Count]->Physics_Position = App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getOrigin();
	App->SBC_Scene->B_Locations[Count]->Physics_Rotation = App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().getRotation();

	App->SBC_Scene->Player_Location_Count++;*/

}

// *************************************************************************
// *	  					Goto_Locatio Terry							   *
// *************************************************************************
void SB_Player::Goto_Location(int Index)
{

	/*App->SBC_Scene->B_Player[0]->Player_Node->setPosition(App->SBC_Scene->B_Locations[Index]->Current_Position);

	App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().setOrigin(App->SBC_Scene->B_Locations[Index]->Physics_Position);

	App->SBC_Scene->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->SBC_Scene->B_Locations[Index]->Physics_Rotation);*/
}
