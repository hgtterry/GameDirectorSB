/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Collision.h"

SB_Collision::SB_Collision()
{
	ObjectIndex = 0;
	DoMove = 0;

	FinalPosition = 0;

	x = 0;
	y = 0;
	z = 0;

	px = 0;
	py = 0;
	pz = 0;
}

SB_Collision::~SB_Collision()
{
}

// *************************************************************************
// *			Message_Entity:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Collision::Message_Entity(int Index)
{
	if (App->GDCL_Scene_Data->B_Object[Index]->Triggered == 1) // Retrigger Yes No
	{
		return 1;
	}

	if (App->GDCL_Scene_Data->B_Object[Index]->Triggered == 1) // Retrigger Yes No
	{
		return 1;
	}

	//-----------------  Do Action
	App->GDCL_Scene_Data->B_Object[Index]->Show_Message_Flag = 1;
	App->GDCL_Scene_Data->B_Object[Index]->Triggered = 1;

	return 1;
}

// **************************************************************************
// *				Play_Sound:- Terry and Hazel Flanigan 2022				*
// **************************************************************************
bool SB_Collision::Play_Sound(int Index)
{

	//if (App->Cl_Scene_Data->Cl_Object[Index]->HasSound == 1 && App->Cl_Scene_Data->Cl_Object[Index]->Play_v2 == 1)
	{
		char buff[1024];
		strcpy(buff, App->GDCL_SoundMgr->Default_Folder);
		strcat(buff, "\\Media\\Sounds\\");

		strcat(buff, App->GDCL_Scene_Data->B_Object[Index]->Sound_File);

		App->GDCL_SoundMgr->SndFile = App->GDCL_SoundMgr->SoundEngine->play2D(buff, false, true, true);
		App->GDCL_SoundMgr->SndFile->setVolume(App->GDCL_Scene_Data->B_Object[Index]->SndVolume);
		App->GDCL_SoundMgr->SndFile->setIsPaused(false);

		App->GDCL_Scene_Data->B_Object[Index]->Triggered = 1;
	}

	return 1;
}

// *************************************************************************
// *			Move_Entity:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
bool SB_Collision::Move_Entity_Collision(int Index)
{
	//FlashWindow(App->MainHwnd, true);

	//if (App->SBC_Scene->B_Object[Index]->Triggered == 1) // Retrigger Yes No
	//{
	//	return 1;
	//}

	App->GDCL_Scene_Data->B_Object[Index]->Triggered = 1;

	Ogre::Vector3 M_Pos;
	Ogre::Vector3 P_Pos;
	ObjectIndex = Index;

	int ObjectToMove = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Object_To_Move_Index;

	//if (App->GDCL_Scene_Data->B_Object[ObjectToMove]->Deleted == 0)
	{
		
		M_Pos = App->GDCL_Scene_Data->B_Object[ObjectToMove]->Mesh_Pos;
		P_Pos = App->GDCL_Scene_Data->B_Object[ObjectToMove]->Physics_Pos;

		App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos = Ogre::Vector3(M_Pos);
		App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos = Ogre::Vector3(P_Pos);

		x = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x;
		y = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y;
		z = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z;

		px = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.x;
		py = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.y;
		pz = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.z;

		if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_x)
		{
			FinalPosition = x + App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Move_Distance;
		}

		if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_y)
		{
			FinalPosition = y + App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Move_Distance;
		}

		if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_z)
		{
			FinalPosition = z + App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Move_Distance;
		}

		//	Play_Sound(Index);

		char Sound[1024];
		strcpy(Sound, App->GDCL_SoundMgr->Default_Folder);
		strcat(Sound, "\\Media\\Sounds\\");
		strcat(Sound, App->GDCL_Scene_Data->B_Object[ObjectIndex]->Sound_File);

		App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile = App->GDCL_SoundMgr->SoundEngine->play2D(Sound, false, true, true);
		App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->setVolume(App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndVolume);
		App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->setIsPaused(false);

		DoMove = 1; // Trigger Ogre Listener to update

	}

	return 1;
}

// *************************************************************************
// *			MoveObject_Listener:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Collision::MoveObject_Listener(Ogre::Real Time)
{
	if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->Deleted == 0)
	{
		// X Axis
		if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_x)
		{

			if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->IsNegative == false)
			{
				int ObjectToMove = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Object_To_Move_Index;

				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x += App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.x += App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				x = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x;
				px = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.x;

				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x > FinalPosition)
				{

					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->stop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->drop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile = NULL;

					DoMove = 0; // Stop Listener
				}

				return;
			}
			else
			{
				int ObjectToMove = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Object_To_Move_Index;

				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x -= App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.x -= App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				x = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x;
				px = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.x;

				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x < FinalPosition)
				{

					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->stop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->drop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile = NULL;

					DoMove = 0; // Stop Listener
				}

				return;
			}
		}

		// Y Axis
		if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_y)
		{
			if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->IsNegative == false)
			{
				int ObjectToMove = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Object_To_Move_Index;

				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y += App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.y += App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				y = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y;
				py = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.y;

				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y > FinalPosition)
				{
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->stop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->drop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile = NULL;

					DoMove = 0; // Stop Listener
				}

				return;
			}
			else
			{
				int ObjectToMove = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Object_To_Move_Index;

				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y -= App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.y -= App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				y = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y;
				py = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.y;

				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y < FinalPosition)
				{
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->stop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->drop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile = NULL;

					DoMove = 0; // Stop Listener
				}

				return;
			}
		}

		// Z Axis
		if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_z)
		{
			if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->IsNegative == false)
			{
				int ObjectToMove = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Object_To_Move_Index;

				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z += App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.z += App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				z = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z;
				pz = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.z;

				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z > FinalPosition)
				{
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->stop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->drop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile = NULL;

					DoMove = 0; // Stop Listener
				}

				return;
			}
			else
			{
				int ObjectToMove = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Object_To_Move_Index;

				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z -= App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.z -= App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				z = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z;
				pz = App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.z;

				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->GDCL_Scene_Data->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->GDCL_Scene_Data->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z < FinalPosition)
				{
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->stop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile->drop();
					App->GDCL_Scene_Data->B_Object[ObjectIndex]->SndFile = NULL;

					DoMove = 0; // Stop Listener
				}

				return;
			}
		}
	}

	return;
}

// *************************************************************************
// *						Do_Teleport Terry Bernie					   *
// *************************************************************************
bool SB_Collision::Do_Teleport(int Index)
{
	//App->GDCL_Scene_Data->SBC_Base_Player[0]->Player_Node->setPosition(App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Player_Position);
	App->GDCL_Scene_Data->B_Player[0]->Phys_Body->getWorldTransform().setOrigin(App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->Physics_Position);
	App->GDCL_Scene_Data->B_Player[0]->Phys_Body->getWorldTransform().setRotation(App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->Physics_Rotation);

	if (App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->Play == 1)
	{
		char Sound[1024];
		strcpy(Sound, App->GDCL_SoundMgr->Default_Folder);
		strcat(Sound, "\\Media\\Sounds\\");
		strcat(Sound, App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->Sound_File);

		App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->SndFile = App->GDCL_SoundMgr->SoundEngine->play2D(Sound, false, true, true);
		App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->SndFile->setVolume(App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->SndVolume);
		App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->SndFile->setIsPaused(false);
	}
	

	return 1;
}

// *************************************************************************
// *						Do_Collectable Terry Bernie					   *
// *************************************************************************
bool SB_Collision::Do_Collectable(int Index)
{
	
	App->GDCL_Scene_Data->B_Object[Index]->Triggered = 1;

	App->GDCL_Scene_Data->B_Object[Index]->Object_Ent->setVisible(0);
	App->GDCL_Scene_Data->B_Object[Index]->Object_Node->setPosition(100, 100, 100);
	App->GDCL_Scene_Data->B_Object[Index]->Phys_Body->getWorldTransform().setOrigin(btVector3(100, 100, 100));

	if (App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Play == 1)
	{
		char Sound[1024];
		strcpy(Sound, App->GDCL_SoundMgr->Default_Folder);
		strcat(Sound, "\\Media\\Sounds\\");
		strcat(Sound, App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Sound_File);

		App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->SndFile = App->GDCL_SoundMgr->SoundEngine->play2D(Sound, false, true, true);
		App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->SndFile->setVolume(App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->SndVolume);
		App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->SndFile->setIsPaused(false);

	}

	if (App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Counter_ID > -1)
	{
		int CouterID = App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Counter_ID;

		if (App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Maths == 1)
		{
			App->GDCL_Scene_Data->B_Counter[CouterID]->Counter += App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Value;
			return 1;
		}

		if (App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Maths == 2)
		{
			App->GDCL_Scene_Data->B_Counter[CouterID]->Counter += -App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Value;
			return 1;
		}
	}

	return 1;
}

//
//// *************************************************************************
//// *						Do_Environment Terry Bernie					   *
//// *************************************************************************
//bool GD19_Collision::Do_Environment(int Index)
//{
//	//if (App->Cl_Scene_Data->Cl_Object[Index]->Re_Trigger == false && App->Cl_Scene_Data->Cl_Object[Index]->Triggered == 1) // Retrigger Yes No
//	//{
//	//	return 1;
//	//}
//
//	//if (App->Cl_Scene_Data->Cl_Object[Index]->Triggered == 1) // Retrigger Yes No
//	//{
//	//	return 1;
//	//}
//
//	//if (App->Cl_Scene_Data->Cl_Object[Index]->HasSound == 1)
//	//{
//	//	if (App->Cl_Scene_Data->Cl_Object[Index]->S_Environment[0]->FogOn == 0)
//	//	{
//	//		App->Cl_Scene_Data->Cl_Object[Index]->S_Environment[0]->FogOn = 1;
//	//		App->Cl_Environment->EnableFog(true);
//	//	}
//	//	else
//	//	{
//	//		App->Cl_Scene_Data->Cl_Object[Index]->S_Environment[0]->FogOn = 0;
//	//		App->Cl_Environment->EnableFog(false);
//	//	}
//
//	//		Play_Sound(Index);
//	//}
//
//	return 1;
//}
