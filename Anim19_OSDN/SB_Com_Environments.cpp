/*
Copyright (c) 2021 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Com_Environments.h"

SB_Com_Environments::SB_Com_Environments()
{
}

SB_Com_Environments::~SB_Com_Environments()
{
}

// *************************************************************************
// *			Add_New_Environment:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Com_Environments::Add_New_Environment()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Environment_Count;

	App->SBC_Scene->B_Environment[Index] = new Base_Environment();
	App->SBC_Scene->B_Environment[Index]->Set_Environment_Defaults();

	strcpy_s(B_Name, "Environment_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Environment[Index]->Name, B_Name);

	App->SBC_Scene->B_Environment[Index]->This_Object_ID = App->SBC_Scene->UniqueID_Environment_Count;

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Environments_Folder, App->SBC_Scene->B_Environment[Index]->Name, Index, true);
	App->SBC_Scene->B_Environment[Index]->FileViewItem = Temp;

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Environments_Folder);

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Environment[Index]->FileViewItem);

	Mark_As_Altered(Index);

	App->SBC_Scene->UniqueID_Environment_Count++;
	App->SBC_Scene->Environment_Count++;

	App->Say("\r\nNew Environment Added");
}

// *************************************************************************
// *			Mark_As_Altered:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_Com_Environments::Mark_As_Altered(int Index)
{
	App->SBC_Scene->B_Environment[Index]->Altered = 1;

	App->SBC_Scene->Scene_Modified = 1;

	App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Environment[Index]->FileViewItem);
}

// *************************************************************************
// *	Add_Environments_From_File:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Com_Environments::Add_Environments_From_File() // From File
{

	int Environments_Count = App->SBC_Scene->Environment_Count;
	int Count = 0;

	while (Count < Environments_Count)
	{

		HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Environments_Folder, App->SBC_Scene->B_Environment[Count]->Name, Count, false);
		App->SBC_Scene->B_Environment[Count]->FileViewItem = Temp;

		Count++;
	}

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Environments_Folder);

	return 1;
}

// **************************************************************************
// *	  		Delete_Environment:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
void SB_Com_Environments::Delete_Environment()
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	App->SBC_Scene->B_Environment[Index]->Deleted = 1;

	App->SBC_FileView->DeleteItem();

	App->SBC_Scene->Scene_Modified = 1;
}

// *************************************************************************
// *			Rename_Environment:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Com_Environments::Rename_Environment(int Index)
{
	Base_Environment* Environment = App->SBC_Scene->B_Environment[Index];

	strcpy(App->Cl_Dialogs->btext, "Change Object Name");
	strcpy(App->Cl_Dialogs->Chr_Text, Environment->Name);

	App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects, 1);

	if (App->Cl_Dialogs->Canceled == 1)
	{
		return;
	}

	strcpy(Environment->Name, App->Cl_Dialogs->Chr_Text);

	Environment->Altered = 1;
	App->SBC_Scene->Scene_Modified = 1;
	App->SBC_FileView->Mark_Altered(Environment->FileViewItem);

	App->SBC_FileView->Change_Item_Name(Environment->FileViewItem, Environment->Name);
}

// *************************************************************************
// *		Add_New_Environ_Entiry:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Com_Environments::Add_New_Environ_Entity()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->B_Object[Index] = new Base_Object();
	App->SBC_Scene->B_Object[Index]->S_Environ[0] = new Environ_type;
	Set_Environ_Defaults(Index);
	

	App->SBC_Scene->B_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->SBC_Scene->B_Object[Index]->Shape = Enums::Shape_Box;
	App->SBC_Scene->B_Object[Index]->This_Object_ID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_FileName, "EnvironmentEntity_GD.mesh");

	strcpy_s(B_Name, "Environ_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, B_Name);

	Ogre::Vector3 Pos = App->SBC_Object->GetPlacement(-50);
	App->SBC_Scene->B_Object[Index]->Mesh_Pos = Pos;

	Create_Environ_Entity(Index);

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Evirons_Folder, App->SBC_Scene->B_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->B_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[Index]->FileViewItem);

	App->SBC_Scene->UniqueID_Object_Counter++;
	App->SBC_Scene->Object_Count++;

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Sounds_Folder);
	return 1;
}

// *************************************************************************
// *		Create_Environ_Entity:- Terry and Hazel Flanigan	2022		   *
// *************************************************************************
bool SB_Com_Environments::Create_Environ_Entity(int Index)
{
	char Mesh_File[255];
	char ConNum[256];
	char Ogre_Name[256];

	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	// ----------------- Mesh

	strcpy_s(Ogre_Name, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(Ogre_Name, ConNum);

	strcpy(Mesh_File, Object->Mesh_FileName);

	Object->Object_Ent = App->Cl19_Ogre->mSceneMgr->createEntity(Ogre_Name, Mesh_File, App->Cl19_Ogre->App_Resource_Group);
	Object->Object_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->Object_Node->attachObject(Object->Object_Ent);

	Object->Object_Node->setVisible(true);

	Object->Object_Node->setOrientation(Object->Mesh_Quat);
	Object->Object_Node->setPosition(Object->Mesh_Pos);

	App->SBC_Scene->Scene_Loaded = 1;

	// ----------------- Physics

	AxisAlignedBox worldAAB = Object->Object_Ent->getBoundingBox();
	worldAAB.transformAffine(Object->Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0, 0, 0, 1));

	btScalar mass;
	mass = 0.0f;

	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);
	startTransform.setOrigin(initialPosition);

	Ogre::Vector3 Size = App->SBC_Object->GetMesh_BB_Size(Object->Object_Node);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->Phys_Body = new btRigidBody(rbInfo);
	Object->Phys_Body->setRestitution(1.0);
	Object->Phys_Body->setFriction(1.5);
	Object->Phys_Body->setUserPointer(Object->Object_Node);
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Usage = Enums::Usage_EnvironEntity;
	Object->Phys_Body->setUserIndex(Enums::Usage_EnvironEntity);
	Object->Phys_Body->setUserIndex2(Index);

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	int f = Object->Phys_Body->getCollisionFlags();

	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT
		| btCollisionObject::CF_KINEMATIC_OBJECT
		| btCollisionObject::CF_NO_CONTACT_RESPONSE);


	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	//Set_Physics(Index);

	return 1;
}

// *************************************************************************
// *		Set_Environ_Defaults:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void SB_Com_Environments::Set_Environ_Defaults(int Index)
{
	App->SBC_Scene->B_Object[Index]->Altered = 0;

	//----------------------- Sound
	strcpy(App->SBC_Scene->B_Object[Index]->S_Environ[0]->Sound_File, "The_Sun.ogg");
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndFile = NULL;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Play = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Loop = 1;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndVolume = 0.5;

	//----------------------- Light
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.x = 1;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.y = 1;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.z = 1;

	App->SBC_Scene->B_Object[Index]->S_Environ[0]->DiffuseColour.x = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->DiffuseColour.y = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->DiffuseColour.z = 0;

	App->SBC_Scene->B_Object[Index]->S_Environ[0]->SpecularColour.x = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->SpecularColour.y = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->SpecularColour.z = 0;

	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Light_Position.x = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Light_Position.y = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Light_Position.z = 0;

	// Sky
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Curvature = 15;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Distance = 4000;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Enabled = 0;
	strcpy(App->SBC_Scene->B_Object[Index]->S_Environ[0]->Material, "Examples/CloudySky");
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Tiling = 15;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->type = 1;

	// Fog
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Mode = FOG_LINEAR;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Density = 0.001000;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start = 50;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End = 300;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour = Ogre::Vector3(1, 1, 1);
}
