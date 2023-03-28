/*
Copyright (c) 2022 - 2023 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Com_Entity.h"

SB_Com_Entity::SB_Com_Entity()
{
}

SB_Com_Entity::~SB_Com_Entity()
{
}

// *************************************************************************
// *		Add_New_User_Object:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Com_Entity::Add_New_User_Object(void)
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->V_Object[Index] = new Base_Object();
	//App->SBC_Scene->V_Object[Index]->S_Light[0] = new Light_type;

	Set_User_Objects_Defaults(Index);

	App->SBC_Scene->V_Object[Index]->Type = Enums::Bullet_Type_None;
	App->SBC_Scene->V_Object[Index]->Shape = Enums::NoShape;
	App->SBC_Scene->V_Object[Index]->This_Object_UniqueID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->SBC_Scene->V_Object[Index]->Mesh_FileName, "Cube.mesh");

	strcpy_s(B_Name, "User_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->V_Object[Index]->Mesh_Name, B_Name);

	Ogre::Vector3 Pos = App->CL_Object->GetPlacement(-50);
	App->SBC_Scene->V_Object[Index]->Mesh_Pos = Pos;
	App->SBC_Scene->V_Object[Index]->Mesh_Scale = Ogre::Vector3(1, 1, 1);

	Create_User_Object(Index);

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_UserObjects_Folder, App->SBC_Scene->V_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->V_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->SelectItem(App->SBC_Scene->V_Object[Index]->FileViewItem);

	App->SBC_Scene->UniqueID_Object_Counter++;
	App->SBC_Scene->Object_Count++;

}

// *************************************************************************
// *			Create_User_Object:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Com_Entity::Create_User_Object(int Index)
{
	char Mesh_File[255];
	char ConNum[256];
	char Ogre_Name[256];

	Base_Object* Object = App->SBC_Scene->V_Object[Index];


	// ----------------- Mesh

	strcpy_s(Ogre_Name, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(Ogre_Name, ConNum);

	strcpy(Mesh_File, Object->Mesh_FileName);

	Object->Object_Ent = App->CL_Ogre->mSceneMgr->createEntity(Ogre_Name, Mesh_File, App->CL_Ogre->App_Resource_Group);

	Object->Object_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->Object_Node->attachObject(Object->Object_Ent);

	Object->Object_Node->setVisible(true);
	Object->Object_Node->setPosition(Object->Mesh_Pos);

	//Object->Object_Ent->setMaterialName("Wall_1/HL_Wall");

	//Object->Object_Ent->getMesh()->getNumSubMeshes();
}


// *************************************************************************
// *	Set_User_Objects_Defaults:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Com_Entity::Set_User_Objects_Defaults(int Index)
{
	App->SBC_Scene->V_Object[Index]->Phys_Body = NULL;
	App->SBC_Scene->V_Object[Index]->Physics_Valid = 0;
	App->SBC_Scene->V_Object[Index]->Usage = Enums::Usage_UserObject;

}
