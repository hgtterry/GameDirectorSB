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
#include "SB_Com_Particles.h"

SB_Com_Particles::SB_Com_Particles()
{
}

SB_Com_Particles::~SB_Com_Particles()
{
}

// *************************************************************************
// *		Set_Particle_Defaults:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Com_Particles::Set_Particle_Defaults(int Index)
{
	Base_Object* V_Object = App->SBC_Scene->V_Object[Index];

	V_Object->Phys_Body = NULL;
	V_Object->Physics_Valid = 0;
	V_Object->Usage = Enums::Usage_Particle;

	V_Object->S_Particle[0]->Particle = NULL;
	V_Object->S_Particle[0]->SpeedFactor = 0.5;
	strcpy(V_Object->S_Particle[0]->ParticleScript, "GD_Smoke1");
}

// *************************************************************************
// *			Add_New_Particle:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Com_Particles::Add_New_Particle(char* Script)
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->V_Object[Index] = new Base_Object();
	App->SBC_Scene->V_Object[Index]->S_Particle[0] = new Particle_type;
	App->CL_Com_Particles->Set_Particle_Defaults(Index);

	strcpy(App->SBC_Scene->V_Object[Index]->S_Particle[0]->ParticleScript, Script);

	App->SBC_Scene->V_Object[Index]->Type = Enums::Bullet_Type_None;
	App->SBC_Scene->V_Object[Index]->Shape = Enums::NoShape;
	App->SBC_Scene->V_Object[Index]->This_Object_UniqueID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->SBC_Scene->V_Object[Index]->Mesh_FileName, "DoorEntity_GD.mesh");

	strcpy_s(B_Name, "Particle_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->V_Object[Index]->Mesh_Name, B_Name);

	Ogre::Vector3 Pos = App->CL_Object->GetPlacement(-50);
	App->SBC_Scene->V_Object[Index]->Mesh_Pos = Pos;
	App->SBC_Scene->V_Object[Index]->Mesh_Scale = Ogre::Vector3(1, 1, 1);

	Create_Particle_Entity(Index);

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Particles_Folder, App->SBC_Scene->V_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->V_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->SelectItem(App->SBC_Scene->V_Object[Index]->FileViewItem);

	App->SBC_Scene->UniqueID_Object_Counter++;
	App->SBC_Scene->Object_Count++;

}

// *************************************************************************
// *		Create_Particle_Entity:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Com_Particles::Create_Particle_Entity(int Index)
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


	// ----------------------------------------------------------------------
	char buf[100];
	char Name[100];
	_itoa(Index, buf, 10);
	strcpy(Name, "TestPart_");
	strcat(Name, buf);


	Object->S_Particle[0]->Particle = App->CL_Ogre->mSceneMgr->createParticleSystem(Name, Object->S_Particle[0]->ParticleScript);
	if (Object->S_Particle[0]->Particle == NULL)
	{
		App->Say("Poop");
	}

	Object->S_Particle[0]->Particle->setKeepParticlesInLocalSpace(true);

	Ogre::SceneNode* PartNode = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();

	PartNode->attachObject(Object->S_Particle[0]->Particle);

	PartNode->setPosition(Object->Mesh_Pos);

	PartNode->setScale(Object->Mesh_Scale);

	Object->Object_Node = PartNode;

	Object->Object_Node->setScale(Object->Mesh_Scale);
	Object->Object_Node->setOrientation(Object->Mesh_Quat);

	Object->S_Particle[0]->Particle->setSpeedFactor(Object->S_Particle[0]->SpeedFactor);
}

// *************************************************************************
//				Copy_Particle:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Com_Particles::Copy_Particle(int Object_Index)
{
	Base_Object* Source_Object = App->SBC_Scene->V_Object[Object_Index];


	char ConNum[256];
	char NewName[MAX_PATH];
	int New_Object_Index = App->SBC_Scene->Object_Count;

	strcpy_s(NewName, "Particle_");
	_itoa(New_Object_Index, ConNum, 10);
	strcat(NewName, ConNum);

	strcpy(App->SBC_Dialogs->btext, "New Object Name");
	strcpy(App->SBC_Dialogs->Chr_Text, NewName);

	App->SBC_Dialogs->Start_Copy_Dlg(Enums::Check_Names_Objects, true, false);

	if (App->SBC_Dialogs->Canceled == 1)
	{
		return;
	}

	App->SBC_Scene->V_Object[New_Object_Index] = new Base_Object();
	App->SBC_Scene->V_Object[New_Object_Index]->S_Particle[0] = new Particle_type;
	App->CL_Com_Particles->Set_Particle_Defaults(New_Object_Index);

	Base_Object* New_Object = App->SBC_Scene->V_Object[New_Object_Index];


	strcpy(New_Object->Mesh_Name, App->SBC_Dialogs->Chr_Text);
	strcpy(New_Object->Mesh_FileName, Source_Object->Mesh_FileName);
	strcpy(New_Object->Mesh_Resource_Path, Source_Object->Mesh_Resource_Path);

	New_Object->S_Particle[0]->Particle = Source_Object->S_Particle[0]->Particle;
	New_Object->S_Particle[0]->SpeedFactor = Source_Object->S_Particle[0]->SpeedFactor;
	strcpy(New_Object->S_Particle[0]->ParticleScript, Source_Object->S_Particle[0]->ParticleScript);

	New_Object->Type = Source_Object->Type;

	if (App->CL_Object->m_UseCamera_Placment_f == 1 )
	{
		Ogre::Vector3 Pos = App->CL_Object->GetPlacement();
		New_Object->Mesh_Pos = Pos;
	}
	else
	{
		New_Object->Mesh_Pos = Source_Object->Mesh_Pos;
	}

	New_Object->Shape = Source_Object->Shape;
	New_Object->Mesh_Scale = Source_Object->Mesh_Scale;
	New_Object->Mesh_Rot = Source_Object->Mesh_Rot;
	New_Object->Mesh_Quat = Source_Object->Mesh_Quat;
	New_Object->Physics_Quat = Source_Object->Physics_Quat;

	Create_Particle_Entity(New_Object_Index);

	App->SBC_Scene->V_Object[New_Object_Index]->FileViewItem = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Particles_Folder, App->SBC_Scene->V_Object[New_Object_Index]->Mesh_Name, New_Object_Index, false);

	App->SBC_Scene->Object_Count++;

	App->SBC_FileView->SelectItem(App->SBC_Scene->V_Object[New_Object_Index]->FileViewItem);

	App->Say("Copied");
}
