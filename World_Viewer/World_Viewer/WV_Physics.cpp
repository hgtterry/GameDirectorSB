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
#include "WV_App.h"
#include "resource.h"
#include "WV_Physics.h"


WV_Physics::WV_Physics()
{

}


WV_Physics::~WV_Physics()
{
}





// *************************************************************************
// *				Update_Model (Terry Bernie)							   *
// *************************************************************************
void WV_Physics::Update_Model(void)
{
	/*strcpy(App->CL_Vm_Model->Model_FolderPath, App->Cl_Vm_Preferences->Pref_Ogre_Path);
	strcpy(App->CL_Vm_Model->FileName, App->Cl_Vm_Preferences->Pref_Ogre_JustFileName);

	App->CL_Bullet_AddRoom->AddToScene(0);

	App->Say("Model Updated");*/
}

// *************************************************************************
// *		 Enable_Physics:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void WV_Physics::Enable_Physics(bool Enable)
{
	
	//int f = App->SBC_Scene->B_Player[0]->Phys_Body->getCollisionFlags();

	//App->CL_Ogre->OgreListener->Dubug_Physics_Draw = Enable;
	////App->CL_Ogre->OgreListener->GD_Run_Physics = Enable;
	//App->CL_Ogre->BulletListener->Render_Debug_Flag = Enable;

	//App->SBC_Player->ShowDebug = Enable;

	//App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

}

// *************************************************************************
// *			 Physics_On:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void WV_Physics::Physics_On(bool Enable)
{
	App->CL_Ogre->OgreListener->GD_Run_Physics = Enable;
	RedrawWindow(App->Physics_Console_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}


// *************************************************************************
// *	  		Reset_Physics:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void WV_Physics::Reset_Physics(void)
{
	
	App->CL_Ogre->OgreListener->GD_Run_Physics = 0;

	float w = 1;
	float x = 0;
	float y = 0;
	float z = 0;

	if (App->CL_Scene->Player_Added == 1)// && GD_Reset_Player == 1)
	{
		btVector3 zeroVector(0, 0, 0);

		x = App->CL_Scene->B_Player[0]->StartPos.x;
		y = App->CL_Scene->B_Player[0]->StartPos.y;
		z = App->CL_Scene->B_Player[0]->StartPos.z;

		btVector3 initialPosition(x, y, z);

		btTransform startTransform;
		startTransform.setIdentity();
		startTransform.setRotation(btQuaternion(1.0f, 0.0f, 0.0f, 0.0f));
		startTransform.setOrigin(initialPosition);

		App->CL_Scene->B_Player[0]->Phys_Body->clearForces();
		App->CL_Scene->B_Player[0]->Phys_Body->setLinearVelocity(zeroVector);
		App->CL_Scene->B_Player[0]->Phys_Body->setAngularVelocity(zeroVector);

		App->CL_Scene->B_Player[0]->Phys_Body->setWorldTransform(startTransform);
		App->CL_Scene->B_Player[0]->Phys_Body->getMotionState()->setWorldTransform(startTransform);
		App->CL_Scene->B_Player[0]->Phys_Body->activate(true);

		App->CL_Scene->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->CL_Scene->B_Player[0]->Physics_Rotation);
	}

	//App->CL_Ogre->OgreListener->GD_Run_Physics = 1;
}

// *************************************************************************
// *	  		Reset_Triggers:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void WV_Physics::Reset_Triggers(void)
{
	//App->SBC_Collision->DoMove = 0;

	//if (App->SBC_Scene->GameMode_Running_Flag == 0)
	//{
	//	App->SBC_SoundMgr->SoundEngine->stopAllSounds();
	//}

	//Ogre::Vector3 M_Pos;
	//Ogre::Vector3 P_Pos;

	//int Count = 0;
	//int Total = App->SBC_Scene->Object_Count;

	//while (Count < Total)
	//{
	//	if (App->SBC_Scene->V_Object[Count]->Deleted == 0)
	//	{
	//		// ------------------------------------- Move Entities
	//		if (App->SBC_Scene->V_Object[Count]->Usage == Enums::Usage_Move)
	//		{
	//			int ObjectToMove = App->SBC_Scene->V_Object[Count]->S_MoveType[0]->Object_To_Move_Index;

	//			M_Pos = App->SBC_Scene->V_Object[ObjectToMove]->Mesh_Pos;
	//			P_Pos = App->SBC_Scene->V_Object[ObjectToMove]->Physics_Pos;

	//			App->SBC_Scene->V_Object[Count]->S_MoveType[0]->MeshPos = Ogre::Vector3(M_Pos);
	//			App->SBC_Scene->V_Object[Count]->S_MoveType[0]->PhysicsPos = Ogre::Vector3(P_Pos);

	//			App->SBC_Scene->V_Object[ObjectToMove]->Object_Node->setPosition(M_Pos);
	//			App->SBC_Scene->V_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(P_Pos.x, P_Pos.y, P_Pos.z));

	//			App->SBC_Scene->V_Object[Count]->Triggered = 0;
	//		}

	//		// ------------------------------------- Colectables
	//		if (App->SBC_Scene->V_Object[Count]->Usage == Enums::Usage_Colectable)
	//		{
	//			App->SBC_Scene->V_Object[Count]->Object_Ent->setVisible(TRUE);

	//			App->SBC_Scene->V_Object[Count]->Object_Node->setPosition(App->SBC_Scene->V_Object[Count]->Mesh_Pos);

	//			P_Pos = App->SBC_Scene->V_Object[Count]->Physics_Pos;
	//			App->SBC_Scene->V_Object[Count]->Phys_Body->getWorldTransform().setOrigin(btVector3(P_Pos.x, P_Pos.y, P_Pos.z));

	//			App->SBC_Scene->V_Object[Count]->Triggered = 0;

	//		}

	//		// ------------------------------------- Messages
	//		if (App->SBC_Scene->V_Object[Count]->Usage == Enums::Usage_Message)
	//		{
	//			App->SBC_Scene->V_Object[Count]->Show_Message_Flag = 0;
	//		}
	//	}

	//	Count++;
	//}

	//Count = 0;
	//Total = App->SBC_Scene->Counters_Count;
	//while (Count < Total)
	//{
	//	App->SBC_Scene->B_Counter[Count]->Counter = App->SBC_Scene->B_Counter[Count]->Start_Value;
	//	Count++;
	//}
}

// *************************************************************************
//							Set_Physics Terry Bernie					   *
// *************************************************************************
void WV_Physics::Set_Physics(int Index)
{
	/*App->SBC_Scene->V_Object[Index]->Physics_Quat = App->SBC_Scene->V_Object[Index]->Object_Node->getOrientation();

	float w = App->SBC_Scene->V_Object[Index]->Physics_Quat.w;
	float x = App->SBC_Scene->V_Object[Index]->Physics_Quat.x;
	float y = App->SBC_Scene->V_Object[Index]->Physics_Quat.y;
	float z = App->SBC_Scene->V_Object[Index]->Physics_Quat.z;
	App->SBC_Scene->V_Object[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	App->SBC_Scene->V_Object[Index]->Object_Node->setScale(App->SBC_Scene->V_Object[Index]->Mesh_Scale);

	Ogre::Vector3 Scale = App->SBC_Scene->V_Object[Index]->Object_Node->getScale();
	App->SBC_Scene->V_Object[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

	UpDate_Physics_And_Visuals(Index);

	App->SBC_Scene->V_Object[Index]->Physics_Valid = 1;*/
}

// *************************************************************************
// *				UpDate_Physics_And_Visuals Terry Flanigtan		 	   *
// *************************************************************************
void WV_Physics::UpDate_Physics_And_Visuals(int Index)
{
	//if (App->SBC_Scene->V_Object[Index]->Shape == Enums::Shape_TriMesh)
	//{

	//}
	//else
	//{
	//	//if (App->SBC_Scene->V_Object[Index]->Physics_Valid == 1)
	//	{
	//		Set_Physics_Position(Index);
	//	}
	//}


	//App->SBC_Markers->MarkerBB_Addjust(Index);

	//// Needs Looking at
	//App->SBC_Scene->V_Object[Index]->Altered = 1;
	//App->SBC_FileView->Mark_Altered(App->SBC_Scene->V_Object[Index]->FileViewItem);
	//App->SBC_Scene->Scene_Modified = 1;
}

// *************************************************************************
// *	  				Set_Physics_Position Terry Flanigan				   *
// *************************************************************************
void WV_Physics::Set_Physics_Position(int Index)
{
	/*AxisAlignedBox worldAAB = App->SBC_Scene->V_Object[Index]->Object_Ent->getBoundingBox();
	worldAAB.transformAffine(App->SBC_Scene->V_Object[Index]->Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();
	App->SBC_Scene->V_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(Centre.x, Centre.y, Centre.z));
	App->SBC_Scene->V_Object[Index]->Physics_Pos = Centre;*/
}

