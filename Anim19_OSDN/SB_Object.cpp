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
#include "GD19_App.h"
#include "resource.h"
#include "SB_Object.h"

SB_Object::SB_Object(void)
{
	Show_Physics_Debug = 0;
	Show_Mesh_Debug = 1;
	Hide_All_Except_Flag = 0;
}

SB_Object::~SB_Object(void)
{
}

// *************************************************************************
// *		Hide_AllObjects_Except:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Object::Hide_AllObjects_Except(int Index,bool Show)
{
	int Count = 0;
	while (Count < App->SBC_Scene->Object_Count)
	{
		App->SBC_Scene->B_Object[Count]->Object_Node->setVisible(Show);
		Count++;
	}

	Count = 0;
	while (Count < App->SBC_Scene->Area_Count)
	{
		App->SBC_Scene->B_Area[Count]->Area_Node->setVisible(Show);
		Count++;
	}

	App->SBC_Scene->B_Object[Index]->Object_Node->setVisible(true);
}

// *************************************************************************
// *			Rename_Object:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Object::Rename_Object(int Index)
{
	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	strcpy(App->Cl_Dialogs->btext, "Change Object Name");
	strcpy(App->Cl_Dialogs->Chr_Text, Object->Mesh_Name);

	App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects, 1);

	if (App->Cl_Dialogs->Canceled == 1)
	{
		return;
	}

	strcpy(Object->Mesh_Name, App->Cl_Dialogs->Chr_Text);

	Object->Altered = 1;
	App->SBC_Scene->Scene_Modified = 1;
	App->SBC_FileView->Mark_Altered(Object->FileViewItem);

	App->SBC_FileView->Change_Item_Name(Object->FileViewItem, Object->Mesh_Name);
}

// *************************************************************************
//		Get_BoundingBox_World_Centre:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
Ogre::Vector3 SB_Object::Get_BoundingBox_World_Centre(int Object_Index)
{
	if (App->SBC_Scene->B_Object[Object_Index]->Shape == Enums::Shape_TriMesh)
	{
		Ogre::Vector3 Pos = App->SBC_Scene->B_Object[Object_Index]->Object_Node->getPosition();
		return Pos;
	}
	else
	{
		AxisAlignedBox worldAAB = App->SBC_Scene->B_Object[Object_Index]->Object_Ent->getBoundingBox();
		worldAAB.transformAffine(App->SBC_Scene->B_Object[Object_Index]->Object_Node->_getFullTransform());
		Ogre::Vector3 Centre = worldAAB.getCenter();

		return Centre;
	}
}

// *************************************************************************
//				Copy_Object:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Object::Copy_Object(int Object_Index)
{
	Base_Object* Object = App->SBC_Scene->B_Object[Object_Index];

	char ConNum[256];
	char NewName[MAX_PATH];
	int Object_Count = App->SBC_Scene->Object_Count;

	strcpy_s(NewName, "Object_");
	_itoa(Object_Count, ConNum, 10);
	strcat(NewName, ConNum);

	strcpy(App->Cl_Dialogs->btext, "New Object Name");
	strcpy(App->Cl_Dialogs->Chr_Text, NewName);

	App->Cl_Dialogs->Dialog_Text(2, 1);

	if (App->Cl_Dialogs->Canceled == 1)
	{
		return ;
	}

	App->SBC_Scene->B_Object[Object_Count] = new Base_Object();
	Base_Object* New_Object = App->SBC_Scene->B_Object[Object_Count];

	strcpy(New_Object->Mesh_Name, App->Cl_Dialogs->Chr_Text);
	strcpy(New_Object->Mesh_FileName, Object->Mesh_FileName);
	strcpy(New_Object->Mesh_Resource_Path, Object->Mesh_Resource_Path);

	New_Object->Type = Object->Type;
	New_Object->Shape = Object->Shape;

	New_Object->Mesh_Pos = Object->Mesh_Pos;
	New_Object->Mesh_Scale = Object->Mesh_Scale;
	New_Object->Mesh_Rot = Object->Mesh_Rot;
	New_Object->Mesh_Quat = Object->Mesh_Quat;
	New_Object->Physics_Quat = Object->Physics_Quat;

	App->SBC_Objects_Create->Add_New_Object(Object_Count,0);

	App->SBC_Scene->B_Object[Object_Count]->FileViewItem = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Objects_Folder, App->SBC_Scene->B_Object[Object_Count]->Mesh_Name, Object_Count, false);
	
	App->SBC_Scene->Object_Count++;

	App->Say("Copied");
}

// *************************************************************************
// *		Clear_Modified_Objects:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Object::Clear_Modified_Objects()
{
	// ---------------- Areas
	int Count = 0;
	while (Count < App->SBC_Scene->Area_Count)
	{
		if (App->SBC_Scene->B_Area[Count]->Altered == 1)
		{
			App->SBC_Scene->B_Area[Count]->Altered = 0;
			App->SBC_FileView->Mark_Clear(App->SBC_Scene->B_Area[Count]->FileViewItem);
		}

		Count++;
	}

	// ---------------- Players
	Count = 0;
	while (Count < App->SBC_Scene->Player_Count)
	{
		if (App->SBC_Scene->B_Player[Count]->Altered == 1)
		{
			App->SBC_Scene->B_Player[Count]->Altered = 0;
			App->SBC_FileView->Mark_Clear(App->SBC_Scene->B_Player[Count]->FileViewItem);
		}

		Count++;
	}

	// ---------------- Cameras
	Count = 0;
	while (Count < App->SBC_Scene->Camera_Count)
	{
		if (App->SBC_Scene->B_Camera[Count]->Altered == 1)
		{
			App->SBC_Scene->B_Camera[Count]->Altered = 0;
			App->SBC_FileView->Mark_Clear(App->SBC_Scene->B_Camera[Count]->FileViewItem);
		}

		Count++;
	}

	// ---------------- Objects
	Count = 0;
	while (Count < App->SBC_Scene->Object_Count)
	{
		if (App->SBC_Scene->B_Object[Count]->Altered == 1)
		{
			App->SBC_Scene->B_Object[Count]->Altered = 0;
			App->SBC_FileView->Mark_Clear(App->SBC_Scene->B_Object[Count]->FileViewItem);
		}

		Count++;
	}

	// ---------------- Display Counters
	Count = 0;
	while (Count < App->SBC_Scene->Counters_Count)
	{
		if (App->SBC_Scene->B_Counter[Count]->Altered == 1)
		{
			App->SBC_Scene->B_Counter[Count]->Altered = 0;
			App->SBC_FileView->Mark_Clear(App->SBC_Scene->B_Counter[Count]->FileViewItem);
		}

		Count++;
	}

	// ---------------- Folders
	if (App->SBC_Scene->Object_Count > 0)
	{
		App->SBC_FileView->Mark_Clear_Folder(App->SBC_FileView->FV_Objects_Folder);
		App->SBC_FileView->Mark_Clear_Folder(App->SBC_FileView->FV_Message_Trigger_Folder);
		App->SBC_FileView->Mark_Clear_Folder(App->SBC_FileView->FV_Move_Folder);
		App->SBC_FileView->Mark_Clear_Folder(App->SBC_FileView->FV_Sounds_Folder);
	}

	App->SBC_FileView->Mark_Clear_Folder(App->SBC_FileView->FV_Environments_Folder);

	App->SBC_Scene->Scene_Modified = 0;

	EnableMenuItem(App->mMenu, ID_FILE_SAVEPROJECTALL, MF_GRAYED);
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


	CamPos = App->Cl19_Ogre->mCamera->getPosition();
	mYaw = App->Cl19_Ogre->mCamera->getOrientation().getYaw();

	App->Cl19_Ogre->PlacementCam->setPosition(CamPos);

	CamRot = Ogre::Quaternion::IDENTITY;
	App->Cl19_Ogre->PlacementCam->setOrientation(CamRot);
	App->Cl19_Ogre->PlacementCam->yaw(mYaw);

	Ogre::Vector3 TranslateVector = Ogre::Vector3::ZERO;

	//float Radius = OgreNode->getAttachedObject(0)->getBoundingRadius();
	//Radius = (Radius * 7) + 2;

	
	TranslateVector.z = Distance; // Distance from Camera/Player

	CamPos = App->Cl19_Ogre->mCamera->getPosition();

	App->Cl19_Ogre->PlacementCam->moveRelative(TranslateVector);

	Placement = App->Cl19_Ogre->PlacementCam->getPosition();
	Placement.y = CamPos.y - 3; // = Placement.y - (float)13.5 / 2;

	return Placement;
}

// **************************************************************************
// *	  			GetIndex_By_Name:- Terry and Hazel Flanigan 2022		*
// **************************************************************************
int SB_Object::GetIndex_By_Name(char* Name)
{
	int Count = 0;
	int Total = App->SBC_Scene->Object_Count;

	while (Count < Total)
	{
		if (App->SBC_Scene->B_Object[Count]->Deleted == 0)
		{
			int Result = 1;
			Result = strcmp(App->SBC_Scene->B_Object[Count]->Mesh_Name, Name);
			if (Result == 0)
			{
				return Count;
			}
		}

		Count++;
	}

	return -1;
}

// **************************************************************************
// *	  		Delete_Object:- Terry and Hazel Flanigan 2022				*
// **************************************************************************
void SB_Object::Delete_Object()
{
	int MeshIndex = App->SBC_Properties->Current_Selected_Object;
	btRigidBody* body = App->SBC_Scene->B_Object[MeshIndex]->Phys_Body;

	if (body)
	{
		App->Cl_Bullet->dynamicsWorld->removeCollisionObject(body);
	}

	App->SBC_Scene->B_Object[MeshIndex]->Deleted = 1;
	App->SBC_Scene->B_Object[MeshIndex]->Object_Node->setVisible(false);

	App->SBC_FileView->DeleteItem();
	App->SBC_Scene->Scene_Modified = 1;

}

// *************************************************************************
// *	  Set_Teleports_Defaults:- Terry and Hazel Flanigan 2022	 	   *
// *************************************************************************
void SB_Object::Set_Teleports_Defaults(int Index)
{
	float x = 0;
	float y = 0;
	float z = 0;

	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Location_ID = 0;

	strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Name, "Start_Location");

	strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Sound_File,"magicspell.ogg");
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->SndVolume = 0.5;
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Play = 1;

	x = App->SBC_Scene->B_Player[0]->StartPos.x;
	y = App->SBC_Scene->B_Player[0]->StartPos.y;
	z = App->SBC_Scene->B_Player[0]->StartPos.z;

	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Physics_Position = btVector3(x,y,z);
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Physics_Rotation = App->SBC_Scene->B_Player[0]->Physics_Rotation;
}


// *************************************************************************
// *	  		GetMesh_BB_Size:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
Ogre::Vector3 SB_Object::GetMesh_BB_Size(SceneNode* mNode)
{
	AxisAlignedBox aab = mNode->getAttachedObject(0)->getBoundingBox();
	Ogre::Vector3 min = aab.getMinimum() * mNode->getScale();
	Ogre::Vector3 max = aab.getMaximum() * mNode->getScale();
	Ogre::Vector3 center = aab.getCenter() * mNode->getScale();
	Ogre::Vector3 size(fabs(max.x - min.x), fabs(max.y - min.y), fabs(max.z - min.z));
	float radius = (size.x > size.z) ? size.z / 2.0f : size.x / 2.0f;

	return size;
}

// *************************************************************************
// *	  		GetMesh_BB_Radius:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
float SB_Object::GetMesh_BB_Radius(SceneNode* mNode)
{
	AxisAlignedBox aab = mNode->getAttachedObject(0)->getBoundingBox();
	Ogre::Vector3 min = aab.getMinimum() * mNode->getScale();
	Ogre::Vector3 max = aab.getMaximum() * mNode->getScale();
	Ogre::Vector3 center = aab.getCenter() * mNode->getScale();
	Ogre::Vector3 size(fabs(max.x - min.x), fabs(max.y - min.y), fabs(max.z - min.z));
	float radius = (size.x > size.z) ? size.z / 2.0f : size.x / 2.0f;

	return radius;
}
	