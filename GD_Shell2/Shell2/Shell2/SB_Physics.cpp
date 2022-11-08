/*
Copyright (c) 2021 Stage Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Physics.h"


SB_Physics::SB_Physics()
{
	Toggle_Enable_Flag = 0;
}


SB_Physics::~SB_Physics()
{
}


// *************************************************************************
// *				Update_Model (Terry Bernie)							   *
// *************************************************************************
void SB_Physics::Update_Model(void)
{
	/*strcpy(App->CL_Vm_Model->Model_FolderPath, App->Cl_Vm_Preferences->Pref_Ogre_Path);
	strcpy(App->CL_Vm_Model->FileName, App->Cl_Vm_Preferences->Pref_Ogre_JustFileName);

	App->CL_Bullet_AddRoom->AddToScene(0);

	App->Say("Model Updated");*/
}

// *************************************************************************
// *		 Enable_Physics:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Physics::Enable_Physics(bool Enable)
{
	//App->Log_Messageg("void SB_Physics::Enable_Physics(bool Enable)");

	int f = App->GDCL_Scene_Data->B_Player[0]->Phys_Body->getCollisionFlags();

	//App->Ogre17->OgreListener->Dubug_Physics_Draw = Enable;

	App->Ogre17->PhysicsFrameListener->GD_Run_Physics = Enable;

	//App->Ogre17->BulletListener->Render_Debug_Flag = Enable;

	App->SBC_Player->ShowDebug = Enable;

	App->GDCL_Scene_Data->B_Player[0]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->SBC_Physics->Toggle_Enable_Flag = Enable;

}

// *************************************************************************
// *	  		Reset_Physics:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Physics::Reset_Physics(void)
{
	//App->Log_Messageg("void GD19_Bullet::Reset_Physics(void)");

	App->Ogre17->PhysicsFrameListener->GD_Run_Physics = 0;

	float w = 1;
	float x = 0;
	float y = 0;
	float z = 0;

	int Count = 0;
	while (Count < App->GDCL_Scene_Data->Object_Count)
	{
		if (App->GDCL_Scene_Data->B_Object[Count]->Usage == Enums::Usage_Dynamic)
		{
			btVector3 zeroVector(0, 0, 0);

			x = App->GDCL_Scene_Data->B_Object[Count]->Physics_Pos.x;
			y = App->GDCL_Scene_Data->B_Object[Count]->Physics_Pos.y;
			z = App->GDCL_Scene_Data->B_Object[Count]->Physics_Pos.z;
			btVector3 initialPosition(x, y, z);

			btTransform startTransform;
			startTransform.setIdentity();

			startTransform.setRotation(btQuaternion(App->GDCL_Scene_Data->B_Object[Count]->Physics_Quat.x,
				App->GDCL_Scene_Data->B_Object[Count]->Physics_Quat.y,
				App->GDCL_Scene_Data->B_Object[Count]->Physics_Quat.z,
				App->GDCL_Scene_Data->B_Object[Count]->Physics_Quat.w));

			startTransform.setOrigin(initialPosition);

			App->GDCL_Scene_Data->B_Object[Count]->Phys_Body->clearForces();
			App->GDCL_Scene_Data->B_Object[Count]->Phys_Body->setLinearVelocity(zeroVector);
			App->GDCL_Scene_Data->B_Object[Count]->Phys_Body->setAngularVelocity(zeroVector);

			App->GDCL_Scene_Data->B_Object[Count]->Phys_Body->setWorldTransform(startTransform);
			App->GDCL_Scene_Data->B_Object[Count]->Phys_Body->getMotionState()->setWorldTransform(startTransform);
			App->GDCL_Scene_Data->B_Object[Count]->Phys_Body->activate(true);

			App->GDCL_Scene_Data->B_Object[Count]->Object_Node->setPosition(App->GDCL_Scene_Data->B_Object[Count]->Mesh_Pos);
			App->GDCL_Scene_Data->B_Object[Count]->Object_Node->setOrientation(App->GDCL_Scene_Data->B_Object[Count]->Mesh_Quat);

		}

		/*if(App->GDCL_Scene_Data->CL_Object[Count]->Usage == Enums::Usage_Sound)
		{
			btVector3 zeroVector(0,0,0);

			x = App->GDCL_Scene_Data->CL_Object[Count]->Physics_Pos.x;
			y = App->GDCL_Scene_Data->CL_Object[Count]->Physics_Pos.y;
			z = App->GDCL_Scene_Data->CL_Object[Count]->Physics_Pos.z;
			btVector3 initialPosition(x,y,z);

			btTransform startTransform;
			startTransform.setIdentity();
			startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1.0f));
			startTransform.setOrigin(initialPosition);

			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->clearForces();
			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->setLinearVelocity(zeroVector);
			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->setAngularVelocity(zeroVector);

			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->setWorldTransform(startTransform);
			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->getMotionState()->setWorldTransform(startTransform);
			App->GDCL_Scene_Data->CL_Object[Count]->bt_body->activate(true);
		}*/

		Count++;
	}

	if (App->GDCL_Scene_Data->Player_Added == 1)// && GD_Reset_Player == 1)
	{
		btVector3 zeroVector(0, 0, 0);

		x = App->GDCL_Scene_Data->B_Player[0]->StartPos.x;
		y = App->GDCL_Scene_Data->B_Player[0]->StartPos.y;
		z = App->GDCL_Scene_Data->B_Player[0]->StartPos.z;

		btVector3 initialPosition(x, y, z);

		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setRotation(btQuaternion(1.0f, 0.0f, 0.0f, 0.0f));
		startTransform.setOrigin(initialPosition);

		App->GDCL_Scene_Data->B_Player[0]->Phys_Body->clearForces();
		App->GDCL_Scene_Data->B_Player[0]->Phys_Body->setLinearVelocity(zeroVector);
		App->GDCL_Scene_Data->B_Player[0]->Phys_Body->setAngularVelocity(zeroVector);

		App->GDCL_Scene_Data->B_Player[0]->Phys_Body->setWorldTransform(startTransform);
		App->GDCL_Scene_Data->B_Player[0]->Phys_Body->getMotionState()->setWorldTransform(startTransform);
		App->GDCL_Scene_Data->B_Player[0]->Phys_Body->activate(true);

		App->GDCL_Scene_Data->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->GDCL_Scene_Data->B_Player[0]->Physics_Rotation);
	}

	//App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
}

// *************************************************************************
// *	  		Reset_Triggers:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Physics::Reset_Triggers(void)
{
	Ogre::Vector3 M_Pos;
	Ogre::Vector3 P_Pos;

	int Count = 0;
	int Total = App->GDCL_Scene_Data->Object_Count;

	while (Count < Total)
	{
		if (App->GDCL_Scene_Data->B_Object[Count]->Deleted == 0)
		{
			// ------------------------------------- Move Entities
			if (App->GDCL_Scene_Data->B_Object[Count]->Usage == Enums::Usage_Move)
			{
				int ObjectToMove = App->GDCL_Scene_Data->B_Object[Count]->S_MoveType[0]->Object_To_Move_Index;

				M_Pos = App->GDCL_Scene_Data->B_Object[ObjectToMove]->Mesh_Pos;
				P_Pos = App->GDCL_Scene_Data->B_Object[ObjectToMove]->Physics_Pos;

				App->GDCL_Scene_Data->B_Object[Count]->S_MoveType[0]->MeshPos = Ogre::Vector3(M_Pos);
				App->GDCL_Scene_Data->B_Object[Count]->S_MoveType[0]->PhysicsPos = Ogre::Vector3(P_Pos);

				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Object_Node->setPosition(M_Pos);
				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(P_Pos.x, P_Pos.y, P_Pos.z));

				App->GDCL_Scene_Data->B_Object[Count]->Triggered = 0;
			}

			// ------------------------------------- Colectables
			if (App->GDCL_Scene_Data->B_Object[Count]->Usage == Enums::Usage_Colectable)
			{
				App->GDCL_Scene_Data->B_Object[Count]->Object_Ent->setVisible(TRUE);

				App->GDCL_Scene_Data->B_Object[Count]->Object_Node->setPosition(App->GDCL_Scene_Data->B_Object[Count]->Mesh_Pos);

				P_Pos = App->GDCL_Scene_Data->B_Object[Count]->Physics_Pos;
				App->GDCL_Scene_Data->B_Object[Count]->Phys_Body->getWorldTransform().setOrigin(btVector3(P_Pos.x, P_Pos.y, P_Pos.z));

				App->GDCL_Scene_Data->B_Object[Count]->Triggered = 0;
			}
		}

		Count++;
	}
}



