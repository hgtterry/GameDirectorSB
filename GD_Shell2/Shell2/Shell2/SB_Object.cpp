/*
Copyright (c) 2022 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

:- Terry and Hazel Flanigan 2022

*/

#include "stdafx.h"
#include "BT_App.h"
#include "SB_Object.h"

SB_Object::SB_Object(void)
{
	Object_PropDlg_Hwnd = nullptr;

	Show_Physics_Debug = 0;
	Show_Mesh_Debug = 1;
}

SB_Object::~SB_Object(void)
{
}


// *************************************************************************
// *			Hide_Object_Dlg:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Object::Hide_Object_Dlg(bool Show)
{
	ShowWindow(Object_PropDlg_Hwnd, Show);
}

// *************************************************************************
//		Get_BoundingBox_World_Centre:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
Ogre::Vector3 SB_Object::Get_BoundingBox_World_Centre(int Object_Index)
{
	if (App->GDCL_Scene_Data->B_Object[Object_Index]->Shape == Enums::Shape_TriMesh)
	{
		Ogre::Vector3 Pos = App->GDCL_Scene_Data->B_Object[Object_Index]->Object_Node->getPosition();
		return Pos;
	}
	else
	{
		AxisAlignedBox worldAAB = App->GDCL_Scene_Data->B_Object[Object_Index]->Object_Ent->getBoundingBox();
		worldAAB.transformAffine(App->GDCL_Scene_Data->B_Object[Object_Index]->Object_Node->_getFullTransform());
		Ogre::Vector3 Centre = worldAAB.getCenter();

		return Centre;
	}
}


// *************************************************************************
// *	  		GetPlacement:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
Ogre::Vector3 SB_Object::GetPlacement(int Distance)
{

	Ogre::Vector3 Placement;
	Ogre::Vector3 CamPos;
	Ogre::Quaternion CamRot;
	Ogre::Radian mYaw;
	Ogre::Vector3 mDirection;


	CamPos = App->Ogre17->mCamera->getPosition();
	mYaw = App->Ogre17->mCamera->getOrientation().getYaw();

	App->Ogre17->PlacementCam->setPosition(CamPos);

	CamRot = Ogre::Quaternion::IDENTITY;
	App->Ogre17->PlacementCam->setOrientation(CamRot);
	App->Ogre17->PlacementCam->yaw(mYaw);

	Ogre::Vector3 TranslateVector = Ogre::Vector3::ZERO;

	//float Radius = OgreNode->getAttachedObject(0)->getBoundingRadius();
	//Radius = (Radius * 7) + 2;

	
	TranslateVector.z = Distance; // Distance from Camera/Player

	CamPos = App->Ogre17->mCamera->getPosition();

	App->Ogre17->PlacementCam->moveRelative(TranslateVector);

	Placement = App->Ogre17->PlacementCam->getPosition();
	Placement.y = CamPos.y - 3; // = Placement.y - (float)13.5 / 2;

	return Placement;
}

// **************************************************************************
// *	  			GetIndex_By_Name:- Terry and Hazel Flanigan 2022		*
// **************************************************************************
int SB_Object::GetIndex_By_Name(char* Name)
{
	int Count = 0;
	int Total = App->GDCL_Scene_Data->Object_Count;

	while (Count < Total)
	{
		if (App->GDCL_Scene_Data->B_Object[Count]->Deleted == 0)
		{
			int Result = 1;
			Result = strcmp(App->GDCL_Scene_Data->B_Object[Count]->Mesh_Name, Name);
			if (Result == 0)
			{
				return Count;
			}
		}

		Count++;
	}

	return -1;
}

// *************************************************************************
// *	  Set_Teleports_Defaults:- Terry and Hazel Flanigan 2022	 	   *
// *************************************************************************
void SB_Object::Set_Teleports_Defaults(int Index)
{
	float x = 0;
	float y = 0;
	float z = 0;

	App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->Location_ID = 0;
	strcpy(App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->Name, "Start_Location");

	strcpy(App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->Sound_File,"magicspell.ogg");
	App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->SndVolume = 0.5;
	App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->Play = 1;

	x = App->GDCL_Scene_Data->B_Player[0]->StartPos.x;
	y = App->GDCL_Scene_Data->B_Player[0]->StartPos.y;
	z = App->GDCL_Scene_Data->B_Player[0]->StartPos.z;

	App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->Physics_Position = btVector3(x,y,z);
	App->GDCL_Scene_Data->B_Object[Index]->S_Teleport[0]->Physics_Rotation = App->GDCL_Scene_Data->B_Player[0]->Physics_Rotation;
}

// *************************************************************************
// *	Set_Collectables_Sound_Defaults:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void SB_Object::Set_Collectables_Sound_Defaults(int Index)
{
	App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Counter_ID = -1;
	strcpy(App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Counter_Name, "Not_Set");

	strcpy(App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Sound_File, "footstep.ogg");
	App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->Play = 1;
	App->GDCL_Scene_Data->B_Object[Index]->S_Collectable[0]->SndVolume = 0.5;
}

// *************************************************************************
//			Set_Move_Defaults:- Terry and Hazel Flanigan 2022		  	   *
// *************************************************************************
void SB_Object::Set_Move_Defaults(int Index)
{
	App->GDCL_Scene_Data->B_Object[Index]->S_MoveType[0]->IsNegative = 1;
	App->GDCL_Scene_Data->B_Object[Index]->S_MoveType[0]->Move_Distance = -50;
	App->GDCL_Scene_Data->B_Object[Index]->S_MoveType[0]->Newpos = 0;
	App->GDCL_Scene_Data->B_Object[Index]->S_MoveType[0]->Speed = 10.0;
	App->GDCL_Scene_Data->B_Object[Index]->S_MoveType[0]->WhatDirection = Enums::Axis_x;
	App->GDCL_Scene_Data->B_Object[Index]->S_MoveType[0]->Object_To_Move_Index = 0;
	App->GDCL_Scene_Data->B_Object[Index]->S_MoveType[0]->Triggered = 0;
	App->GDCL_Scene_Data->B_Object[Index]->S_MoveType[0]->Re_Trigger = 0;
	strcpy(App->GDCL_Scene_Data->B_Object[Index]->S_MoveType[0]->Object_Name, "None");
	return;
}
	