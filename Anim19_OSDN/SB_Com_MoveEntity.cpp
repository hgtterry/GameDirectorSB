/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Com_MoveEntity.h"

SB_Com_MoveEntity::SB_Com_MoveEntity()
{
}

SB_Com_MoveEntity::~SB_Com_MoveEntity()
{
}

// *************************************************************************
// *		Add_New_Move_Entity:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Com_MoveEntity::Add_New_Move_Entity()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->V_Object[Index] = new Base_Object();

	App->SBC_Scene->V_Object[Index]->S_MoveType[0] = new Move_Type;
	Set_Move_Defaults(Index); // Check

	App->SBC_Scene->V_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->SBC_Scene->V_Object[Index]->Shape = Enums::Shape_Box;
	App->SBC_Scene->V_Object[Index]->This_Object_UniqueID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->SBC_Scene->V_Object[Index]->Mesh_FileName, "DoorEntity_GD.mesh");

	strcpy_s(B_Name, "MoveEnt_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->V_Object[Index]->Mesh_Name, B_Name);

	Ogre::Vector3 Pos = App->CL_Object->GetPlacement(-50);
	App->SBC_Scene->V_Object[Index]->Mesh_Pos = Pos;

	Create_Move_Entity(Index);

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Move_Folder, App->SBC_Scene->V_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->V_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->SelectItem(App->SBC_Scene->V_Object[Index]->FileViewItem);

	App->SBC_Scene->UniqueID_Object_Counter++;
	App->SBC_Scene->Object_Count++;


	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Move_Folder);
	return 1;
}

// **************************************************************************
// *			Create_Move_Entity:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
bool SB_Com_MoveEntity::Create_Move_Entity(int Index)
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

	Ogre::Vector3 Size = App->CL_Object->GetMesh_BB_Size(Object->Object_Node);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->SBC_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->Phys_Body = new btRigidBody(rbInfo);
	Object->Phys_Body->setRestitution(1.0);
	Object->Phys_Body->setFriction(1.5);
	Object->Phys_Body->setUserPointer(Object->Object_Node);
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Usage = Enums::Usage_Move;
	Object->Phys_Body->setUserIndex(Enums::Usage_Move);
	Object->Phys_Body->setUserIndex2(Index);

	int f = Object->Phys_Body->getCollisionFlags();

	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT
		| btCollisionObject::CF_KINEMATIC_OBJECT
		| btCollisionObject::CF_NO_CONTACT_RESPONSE);


	App->SBC_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	App->SBC_Scene->V_Object[Index]->Physics_Valid = 1;

	App->SBC_Physics->Set_Physics(Index);

	return 1;
}

// *************************************************************************
// *		Set_Move_Defaults:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
void SB_Com_MoveEntity::Set_Move_Defaults(int Index)
{
	Base_Object* V_Object = App->SBC_Scene->V_Object[Index];

	V_Object->S_MoveType[0]->IsNegative = 1;
	V_Object->S_MoveType[0]->Move_Distance = -50;
	V_Object->S_MoveType[0]->Newpos = 0;
	V_Object->S_MoveType[0]->Speed = 10.0;
	V_Object->S_MoveType[0]->WhatDirection = Enums::Axis_x;
	V_Object->S_MoveType[0]->Object_To_Move_Index = 0;
	V_Object->S_MoveType[0]->Triggered = 0;
	V_Object->S_MoveType[0]->Re_Trigger = 0;
	strcpy(V_Object->S_MoveType[0]->Object_Name, "None");

	V_Object->S_MoveType[0]->Trigger_Value = 0;
	V_Object->S_MoveType[0]->Counter_ID = 0;
	strcpy(V_Object->S_MoveType[0]->Counter_Name, "None");
	V_Object->S_MoveType[0]->Counter_Disabled = 1;

	return;
}

// *************************************************************************
// *		Reset_Move_Entity:- Terry and Hazel Flanigan 2022		  	   *
// *************************************************************************
void SB_Com_MoveEntity::Reset_Move_Entity(int Index)
{
	App->SBC_Collision->DoMove = 0;
	App->SBC_SoundMgr->SoundEngine->stopAllSounds();

	Ogre::Vector3 M_Pos;
	Ogre::Vector3 P_Pos;

	int ObjectToMove = App->SBC_Scene->V_Object[Index]->S_MoveType[0]->Object_To_Move_Index;

	M_Pos = App->SBC_Scene->V_Object[ObjectToMove]->Mesh_Pos;
	P_Pos = App->SBC_Scene->V_Object[ObjectToMove]->Physics_Pos;

	App->SBC_Scene->V_Object[Index]->S_MoveType[0]->MeshPos = Ogre::Vector3(M_Pos);
	App->SBC_Scene->V_Object[Index]->S_MoveType[0]->PhysicsPos = Ogre::Vector3(P_Pos);

	App->SBC_Scene->V_Object[ObjectToMove]->Object_Node->setPosition(M_Pos);
	App->SBC_Scene->V_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(P_Pos.x, P_Pos.y, P_Pos.z));

	App->SBC_Scene->V_Object[Index]->Triggered = 0;
}

// *************************************************************************
// *		Test_Move_Entity:- Terry and Hazel Flanigan 2022		  	   *
// *************************************************************************
void SB_Com_MoveEntity::Test_Move_Entity(int Index)
{
	App->SBC_Collision->Set_Move_Entity(Index);
}

// *************************************************************************
// *			Copy_Move_Entity:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Com_MoveEntity::Copy_Move_Entity(int Object_Index)
{
	Base_Object* Source_Object = App->SBC_Scene->V_Object[Object_Index];


	char ConNum[256];
	char NewName[MAX_PATH];
	int New_Object_Index = App->SBC_Scene->Object_Count;

	strcpy_s(NewName, "MoveEnt_");
	_itoa(New_Object_Index, ConNum, 10);
	strcat(NewName, ConNum);

	strcpy(App->SBC_Dialogs->btext, "New Move Object Name");
	strcpy(App->SBC_Dialogs->Chr_Text, NewName);

	App->SBC_Dialogs->Start_Copy_Dlg(Enums::Check_Names_Objects, true, false);

	if (App->SBC_Dialogs->Canceled == 1)
	{
		return;
	}

	App->SBC_Scene->V_Object[New_Object_Index] = new Base_Object();
	App->SBC_Scene->V_Object[New_Object_Index]->S_MoveType[0] = new Move_Type;
	Set_Move_Defaults(New_Object_Index); // Check

	Base_Object* New_Object = App->SBC_Scene->V_Object[New_Object_Index];

	New_Object->S_MoveType[0] = Source_Object->S_MoveType[0];
	


	strcpy(New_Object->Mesh_Name, App->SBC_Dialogs->Chr_Text);
	strcpy(New_Object->Mesh_FileName, Source_Object->Mesh_FileName);
	strcpy(New_Object->Mesh_Resource_Path, Source_Object->Mesh_Resource_Path);


	New_Object->Type = Source_Object->Type;

	if (App->CL_Object->m_UseCamera_Placment_f == 1)
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

	Create_Move_Entity(New_Object_Index);

	App->SBC_Scene->V_Object[New_Object_Index]->FileViewItem = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Move_Folder, App->SBC_Scene->V_Object[New_Object_Index]->Mesh_Name, New_Object_Index, true);

	App->SBC_Scene->Object_Count++;

	App->SBC_FileView->SelectItem(App->SBC_Scene->V_Object[New_Object_Index]->FileViewItem);

	App->Say("Copied");
}
