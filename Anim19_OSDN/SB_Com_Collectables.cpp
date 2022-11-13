/*
Copyright (c) 2022 GameDirectorSB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Com_Collectables.h"

SB_Com_Collectables::SB_Com_Collectables()
{
}

SB_Com_Collectables::~SB_Com_Collectables()
{
}

// *************************************************************************
//				Add_New_Object:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Com_Collectables::Add_New_Object(int Index, bool From_MeshViewer)
{
	char Mesh_File[255];
	char ConNum[256];
	char Ogre_Name[256];

	Base_Object* Object = App->SBC_Scene->B_Object[Index];


	strcpy_s(Ogre_Name, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(Ogre_Name, ConNum);

	strcpy(Mesh_File, Object->Mesh_FileName);

	Object->Object_Ent = App->Cl19_Ogre->mSceneMgr->createEntity(Ogre_Name, Mesh_File, App->SBC_Scene->Project_Resource_Group);
	Object->Object_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->Object_Node->attachObject(Object->Object_Ent);

	Object->Object_Node->setVisible(true);

	Object->Object_Node->setOrientation(Object->Mesh_Quat);

	// If from MeshViewer Get Placement Method
	if (From_MeshViewer == 1 && App->SBC_MeshViewer->Placement_Camera == 1)
	{
		Ogre::Vector3 Pos = App->SBC_Object->GetPlacement();
		Object->Mesh_Pos = Pos;
		Object->Object_Node->setPosition(Pos);
	}
	else
	{
		Object->Object_Node->setPosition(Object->Mesh_Pos);
	}


	App->SBC_Scene->Scene_Loaded = 1;


	//---------------------- Static
	if (Object->Type == Enums::Bullet_Type_Static)
	{
		if (Object->Shape == Enums::Shape_Box)
		{
			App->SBC_Objects_Create->Add_Physics_Box(false, Index);
		}
	}

	ShowWindow(App->GD_Properties_Hwnd, 1);

	return 1;
}

// *************************************************************************
// *		Set_Collectables_Defaults:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void SB_Com_Collectables::Set_Collectables_Defaults(int Index)
{
	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_ID = 0;
	strcpy(App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Name, "Not_Set");

	strcpy(App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Sound_File, "footstep.ogg");
	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Play = 1;
	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->SndVolume = 0.5;

	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths = 1; // Add
	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Value = 1;
}
