#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_Collision.h"


GD19_Collision::GD19_Collision(void)
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

GD19_Collision::~GD19_Collision(void)
{
}

// *************************************************************************
// *						Sound_Entity Terry Bernie					   *
// *************************************************************************
bool GD19_Collision::Sound_Entity(int Index)
{
	//if (App->Cl_Scene_Data->Cl_Object[Index]->Re_Trigger == false && App->Cl_Scene_Data->Cl_Object[Index]->Triggered == 1) // Retrigger Yes No
	//{
	//	return 1;
	//}

	//if (App->Cl_Scene_Data->Cl_Object[Index]->Triggered == 1) // Retrigger Yes No
	//{
	//	return 1;
	//}

	//Play_Sound(Index);
	
	return 1;
}

// *************************************************************************
// *						Message_Entity Terry Bernie					   *
// *************************************************************************
bool GD19_Collision::Message_Entity(int Index)
{
	//if (App->Cl_Scene_Data->Cl_Object[Index]->Re_Trigger == false && App->Cl_Scene_Data->Cl_Object[Index]->Triggered == 1) // Retrigger Yes No
	//{
	//	return 1;
	//}

	//if (App->Cl_Scene_Data->Cl_Object[Index]->Triggered == 1) // Retrigger Yes No
	//{
	//	return 1;
	//}
	//

	//
	//int result = 0;
	//result = strcmp(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, "None");
	//if (result != 0)
	//{
	//	
	//	int Stock_Index = App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].Stock_mIndex;
	//	App->Cl_Panels_Com->Set_User_Text(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, Stock_Index);

	//	App->Cl_Panels_Com->Show_Overlay(1, Stock_Index);

	//	Play_Sound(Index);

	//	App->Cl_Scene_Data->Cl_Object[Index]->Triggered = 1;
	//}
	//Play_Sound(Index);
	return 1;
}

// *************************************************************************
// *						Do_Collectable Terry Bernie					   *
// *************************************************************************
bool GD19_Collision::Do_Collectable(int Index)
{
	
	/*App->Cl_Scene_Data->Cl_Object[Index]->OgreEntity->setVisible(0);
	App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(100,100,100);
	App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setOrigin(btVector3(100, 100, 100));*/

	/*if (App->GDCL_Scene_Data->CL_Object[Index]->HasSound == 1)
	{
		char buff[1024];
		strcpy(buff, App->GDCL_SoundMgr->Default_Folder);
		strcat(buff, "\\Media\\Sounds\\");
		strcat(buff, App->GDCL_Scene_Data->CL_Object[Index]->S_Sounds[0]->SoundFile);

		App->GDCL_Scene_Data->CL_Object[Index]->S_Sounds[0]->SndFile = App->GDCL_SoundMgr->SoundEngine->play2D(buff, false, true, true);
		App->GDCL_Scene_Data->CL_Object[Index]->S_Sounds[0]->SndFile->setVolume(App->GDCL_Scene_Data->CL_Object[Index]->S_Sounds[0]->Volume);
		App->GDCL_Scene_Data->CL_Object[Index]->S_Sounds[0]->SndFile->setIsPaused(false);
	}*/

	Play_Sound(Index);

	return 1;
}

// *************************************************************************
// *						Do_Teleport Terry Bernie					   *
// *************************************************************************
bool GD19_Collision::Do_Teleport(int Index)
{
	/*App->SBC_Scene->SBC_Base_Player[0]->Player_Node->setPosition(App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Player_Position);
	App->SBC_Scene->SBC_Base_Player[0]->Phys_Body->getWorldTransform().setOrigin(App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Physics_Position);
	App->SBC_Scene->SBC_Base_Player[0]->Phys_Body->getWorldTransform().setRotation(App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Physics_Rotation);

	
	Play_Sound(Index);*/

	return 1;
}

// *************************************************************************
// *						Do_Environment Terry Bernie					   *
// *************************************************************************
bool GD19_Collision::Do_Environment(int Index)
{
	//if (App->Cl_Scene_Data->Cl_Object[Index]->Re_Trigger == false && App->Cl_Scene_Data->Cl_Object[Index]->Triggered == 1) // Retrigger Yes No
	//{
	//	return 1;
	//}

	//if (App->Cl_Scene_Data->Cl_Object[Index]->Triggered == 1) // Retrigger Yes No
	//{
	//	return 1;
	//}

	//if (App->Cl_Scene_Data->Cl_Object[Index]->HasSound == 1)
	//{
	//	if (App->Cl_Scene_Data->Cl_Object[Index]->S_Environment[0]->FogOn == 0)
	//	{
	//		App->Cl_Scene_Data->Cl_Object[Index]->S_Environment[0]->FogOn = 1;
	//		App->Cl_Environment->EnableFog(true);
	//	}
	//	else
	//	{
	//		App->Cl_Scene_Data->Cl_Object[Index]->S_Environment[0]->FogOn = 0;
	//		App->Cl_Environment->EnableFog(false);
	//	}

	//		Play_Sound(Index);
	//}

	return 1;
}

// *************************************************************************
// *						Move_Entity Terry Bernie					   *
// *************************************************************************
bool GD19_Collision::Move_Entity(int Index)
{
	//FlashWindow(App->MainHwnd, true);

	//if (App->SBC_Scene->B_Object[Index]->Triggered == 1) // Retrigger Yes No
	//{
	//	return 1;
	//}

	App->SBC_Scene->B_Object[Index]->Triggered = 1;

	Ogre::Vector3 M_Pos;
	Ogre::Vector3 P_Pos;
	ObjectIndex = Index;

	int ObjectToMove = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Object_Index;
	
	if (App->SBC_Scene->B_Object[ObjectToMove]->Deleted == 0)
	{
		FlashWindow(App->MainHwnd, true);

		M_Pos = App->SBC_Scene->B_Object[ObjectToMove]->Mesh_Pos;
		P_Pos = App->SBC_Scene->B_Object[ObjectToMove]->Physics_Pos;

		App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos = Ogre::Vector3(M_Pos);
		App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos = Ogre::Vector3(P_Pos);

		x = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x;
		y = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y;
		z = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z;

		px = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.x;
		py = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.y;
		pz = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.z;

		if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_x)
		{
			FinalPosition = x + App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Move_Distance;
		}

		if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_y)
		{
			FinalPosition = y + App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Move_Distance;
		}

		if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_z)
		{
			FinalPosition = z + App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Move_Distance;
		}

	//	Play_Sound(Index);

	//	DoMove = 1; // Trigger Ogre Listener to update

	}

	return 1;
}

// *************************************************************************
// *					MoveObject (Terry Bernie)						   *
// *************************************************************************
void GD19_Collision::MoveObject(Ogre::Real Time)
{
	if (App->SBC_Scene->B_Object[ObjectIndex]->Deleted == 0)
	{
		// X Axis
		if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_x)
		{

			if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->IsNegative == false)
			{
				int ObjectToMove = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Object_Index;

				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x += App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.x += App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				x = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x;
				px = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.x;

				App->SBC_Scene->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->SBC_Scene->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x > FinalPosition)
				{

					/*App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
					App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
					App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

					DoMove = 0; // Stop Listener
				}

				return;
			}
			else
			{
				int ObjectToMove = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Object_Index;

				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x -= App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.x -= App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				x = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x;
				px = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.x;

				App->SBC_Scene->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->SBC_Scene->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.x < FinalPosition)
				{
					/*App->Cl_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
					App->Cl_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
					App->Cl_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

					DoMove = 0; // Stop Listener
				}

				return;
			}
		}

		// Y Axis
		if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_y)
		{
			if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->IsNegative == false)
			{
				int ObjectToMove = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Object_Index;

				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y += App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.y += App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				y = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y;
				py = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.y;

				App->SBC_Scene->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->SBC_Scene->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y > FinalPosition)
				{
					/*App->Cl_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
					App->Cl_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
					App->Cl_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

					DoMove = 0; // Stop Listener
				}

				return;
			}
			else
			{
				int ObjectToMove = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Object_Index;

				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y -= App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.y -= App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				y = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y;
				py = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.y;

				App->SBC_Scene->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->SBC_Scene->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.y < FinalPosition)
				{
					/*App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
					App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
					App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

					DoMove = 0; // Stop Listener
				}

				return;
			}
		}

		// Z Axis
		if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->WhatDirection == Enums::Axis_z)
		{
			if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->IsNegative == false)
			{
				int ObjectToMove = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Object_Index;

				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z += App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.z += App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				z = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z;
				pz = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.z;

				App->SBC_Scene->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->SBC_Scene->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z > FinalPosition)
				{
					/*App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
					App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
					App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

					DoMove = 0; // Stop Listener
				}

				return;
			}
			else
			{
				int ObjectToMove = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Object_Index;

				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z -= App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;
				App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.z -= App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->Speed * Time;

				z = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z;
				pz = App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->PhysicsPos.z;

				App->SBC_Scene->B_Object[ObjectToMove]->Object_Node->setPosition(x, y, z);
				App->SBC_Scene->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(px, py, pz));

				if (App->SBC_Scene->B_Object[ObjectIndex]->S_MoveType[0]->MeshPos.z < FinalPosition)
				{
					/*App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->stop();
					App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile->drop();
					App->GDCL_Scene_Data->CL_Object[ObjectIndex]->S_Sounds[0]->SndFile = NULL;*/

					DoMove = 0; // Stop Listener
				}

				return;
			}
		}
	}

	return;
}

// *************************************************************************
// *						Play_Sound Terry Bernie						   *
// *************************************************************************
bool GD19_Collision::Play_Sound(int Index)
{

	/*if (App->Cl_Scene_Data->Cl_Object[Index]->HasSound == 1 && App->Cl_Scene_Data->Cl_Object[Index]->Play_v2 == 1)
	{
		char buff[1024];
		strcpy(buff, App->Cl_SoundMgr->Default_Folder);
		strcat(buff, "\\Media\\Sounds\\");

		int SndIndex = App->Cl_Scene_Data->Cl_Object[Index]->Sound_ID_v2;

		strcat(buff, App->Cl_Scene_Data->St_Sounds[SndIndex]->SoundFile);

		App->Cl_Scene_Data->St_Sounds[SndIndex]->SndFile = App->Cl_SoundMgr->SoundEngine->play2D(buff, false, true, true);
		App->Cl_Scene_Data->St_Sounds[SndIndex]->SndFile->setVolume(App->Cl_Scene_Data->St_Sounds[SndIndex]->Volume);
		App->Cl_Scene_Data->St_Sounds[SndIndex]->SndFile->setIsPaused(false);

		App->Cl_Scene_Data->Cl_Object[Index]->Triggered = 1;
	}*/

	return 1;
}

