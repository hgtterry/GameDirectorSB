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

// ------------------------------------------------------------------------------------------ Teleporters
// *************************************************************************
// *		Add_New_Teleporter:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Com_Entity::Add_New_Teleporter()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->B_Object[Index] = new Base_Object();

	App->SBC_Scene->B_Object[Index]->S_Teleport[0] = new Teleport_type;
	Set_Teleports_Defaults(Index);

	App->SBC_Scene->B_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->SBC_Scene->B_Object[Index]->Shape = Enums::Shape_Box;
	App->SBC_Scene->B_Object[Index]->This_Object_UniqueID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_FileName, "TeleportSend.mesh");

	strcpy_s(B_Name, "Teleport_Ent_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, B_Name);

	Ogre::Vector3 Pos = App->SBC_Object->GetPlacement(-50);
	App->SBC_Scene->B_Object[Index]->Mesh_Pos = Pos;

	Create_Teleport_Entity(Index);

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Teleporters_Folder, App->SBC_Scene->B_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->B_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[Index]->FileViewItem);

	App->SBC_Scene->UniqueID_Object_Counter++;
	App->SBC_Scene->Object_Count++;

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Teleporters_Folder);

	return 1;
}

// *************************************************************************
// *		Create_Teleport_Entity:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Com_Entity::Create_Teleport_Entity(int Index)
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

	Object->Object_Ent = App->SBC_Ogre->mSceneMgr->createEntity(Ogre_Name, Mesh_File, App->SBC_Ogre->App_Resource_Group);
	Object->Object_Node = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
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

	App->SBC_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->Phys_Body = new btRigidBody(rbInfo);
	Object->Phys_Body->setRestitution(1.0);
	Object->Phys_Body->setFriction(1.5);
	Object->Phys_Body->setUserPointer(Object->Object_Node);
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Usage = Enums::Usage_Teleport;
	Object->Phys_Body->setUserIndex(Enums::Usage_Teleport);
	Object->Phys_Body->setUserIndex2(Index);

	int f = Object->Phys_Body->getCollisionFlags();

	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT
		| btCollisionObject::CF_KINEMATIC_OBJECT
		| btCollisionObject::CF_NO_CONTACT_RESPONSE);


	App->SBC_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	App->SBC_Scene->B_Object[Index]->Physics_Valid = 1;

	App->SBC_Physics->Set_Physics(Index);

	return 1;
}

// *************************************************************************
// *	  Set_Teleports_Defaults:- Terry and Hazel Flanigan 2022	 	   *
// *************************************************************************
void SB_Com_Entity::Set_Teleports_Defaults(int Index)
{
	float x = 0;
	float y = 0;
	float z = 0;

	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Location_ID = 0;

	strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Name, "Start_Location");

	strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Sound_File, "magicspell.ogg");
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->SndVolume = 0.5;
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Play = 1;

	x = App->SBC_Scene->B_Player[0]->StartPos.x;
	y = App->SBC_Scene->B_Player[0]->StartPos.y;
	z = App->SBC_Scene->B_Player[0]->StartPos.z;

	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Physics_Position = btVector3(x, y, z);
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Physics_Rotation = App->SBC_Scene->B_Player[0]->Physics_Rotation;

	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Trigger_Value = 0;
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Counter_ID = 0;
	strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Counter_Name, "None");
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Counter_Disabled = 1;
}

// ------------------------------------------------------------------------------------------ Sounds
// *************************************************************************
// *				Add_New_Sound:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Com_Entity::Add_New_Sound()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->B_Object[Index] = new Base_Object();

	strcpy(App->SBC_Scene->B_Object[Index]->Sound_File, "Welcome.ogg");
	strcpy(App->SBC_Scene->B_Object[Index]->Sound_Path, App->SBC_SoundMgr->Default_Folder);
	strcat(App->SBC_Scene->B_Object[Index]->Sound_Path, "\\Media\\Sounds\\");
	strcat(App->SBC_Scene->B_Object[Index]->Sound_Path, "Welcome.ogg");

	App->SBC_Scene->B_Object[Index]->HasSound = 1;

	App->SBC_Scene->B_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->SBC_Scene->B_Object[Index]->Shape = Enums::Shape_Box;
	App->SBC_Scene->B_Object[Index]->This_Object_UniqueID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_FileName, "SoundEntity_GD.mesh");

	strcpy_s(B_Name, "Sound_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, B_Name);

	Ogre::Vector3 Pos = App->SBC_Object->GetPlacement(-50);
	App->SBC_Scene->B_Object[Index]->Mesh_Pos = Pos;

	Create_Sound_Entity(Index);

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Sounds_Folder, App->SBC_Scene->B_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->B_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[Index]->FileViewItem);

	App->SBC_Scene->UniqueID_Object_Counter++;
	App->SBC_Scene->Object_Count++;

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Sounds_Folder);
	return 1;
}

// *************************************************************************
// *		Create_Sound_Entity:- Terry and Hazel Flanigan	2022		   *
// *************************************************************************
bool SB_Com_Entity::Create_Sound_Entity(int Index)
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

	Object->Object_Ent = App->SBC_Ogre->mSceneMgr->createEntity(Ogre_Name, Mesh_File, App->SBC_Ogre->App_Resource_Group);
	Object->Object_Node = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
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

	App->SBC_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->Phys_Body = new btRigidBody(rbInfo);
	Object->Phys_Body->setRestitution(1.0);
	Object->Phys_Body->setFriction(1.5);
	Object->Phys_Body->setUserPointer(Object->Object_Node);
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Usage = Enums::Usage_Sound;
	Object->Phys_Body->setUserIndex(Enums::Usage_Sound);
	Object->Phys_Body->setUserIndex2(Index);


	int f = Object->Phys_Body->getCollisionFlags();
	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT
		| btCollisionObject::CF_KINEMATIC_OBJECT
		| btCollisionObject::CF_NO_CONTACT_RESPONSE);


	App->SBC_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	App->SBC_Scene->B_Object[Index]->Physics_Valid = 1;

	App->SBC_Physics->Set_Physics(Index);

	return 1;
}

// ------------------------------------------------------------------------------------------ Messages
// *************************************************************************
//				Add_New_Message:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Com_Entity::Add_New_Message()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->B_Object[Index] = new Base_Object();
	App->SBC_Scene->B_Object[Index]->S_Message[0] = new Message_type;
	Set_Message_Defaults(Index);

	App->SBC_Scene->B_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->SBC_Scene->B_Object[Index]->Shape = Enums::Shape_Box;
	App->SBC_Scene->B_Object[Index]->This_Object_UniqueID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_FileName, "Test_cube.mesh");

	strcpy_s(B_Name, "Message_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, B_Name);

	Ogre::Vector3 Pos = App->SBC_Object->GetPlacement(-50);
	App->SBC_Scene->B_Object[Index]->Mesh_Pos = Pos;

	Create_Message_Entity(Index);

	App->SBC_Scene->B_Object[Index]->Set_ImGui_Panel_Name();



	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Message_Trigger_Folder, App->SBC_Scene->B_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->B_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[Index]->FileViewItem);

	App->SBC_Scene->UniqueID_Object_Counter++;
	App->SBC_Scene->Object_Count++;

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Message_Trigger_Folder);
	return 1;
}

// **************************************************************************
// *		Create_Message_Entity:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
bool SB_Com_Entity::Create_Message_Entity(int Index)
{
	char Mesh_File[255];
	char ConNum[256];
	char Ogre_Name[256];

	Base_Object* MObject = App->SBC_Scene->B_Object[Index];

	// ----------------- Mesh

	strcpy_s(Ogre_Name, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(Ogre_Name, ConNum);

	strcpy(Mesh_File, MObject->Mesh_FileName);

	MObject->Object_Ent = App->SBC_Ogre->mSceneMgr->createEntity(Ogre_Name, Mesh_File, App->SBC_Ogre->App_Resource_Group);
	MObject->Object_Node = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	MObject->Object_Node->attachObject(MObject->Object_Ent);

	MObject->Object_Node->setVisible(true);

	MObject->Object_Node->setOrientation(MObject->Mesh_Quat);
	MObject->Object_Node->setPosition(MObject->Mesh_Pos);

	App->SBC_Scene->Scene_Loaded = 1;

	// ----------------- Physics

	AxisAlignedBox worldAAB = MObject->Object_Ent->getBoundingBox();
	worldAAB.transformAffine(MObject->Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	MObject->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0, 0, 0, 1));

	btScalar mass;
	mass = 0.0f;

	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);
	startTransform.setOrigin(initialPosition);

	Ogre::Vector3 Size = App->SBC_Object->GetMesh_BB_Size(MObject->Object_Node);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	MObject->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->SBC_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	MObject->Phys_Body = new btRigidBody(rbInfo);
	MObject->Phys_Body->setRestitution(1.0);
	MObject->Phys_Body->setFriction(1.5);
	MObject->Phys_Body->setUserPointer(MObject->Object_Node);
	MObject->Phys_Body->setWorldTransform(startTransform);

	MObject->Usage = Enums::Usage_Message;
	MObject->Phys_Body->setUserIndex(Enums::Usage_Message);
	MObject->Phys_Body->setUserIndex2(Index);

	int f = MObject->Phys_Body->getCollisionFlags();

	MObject->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT
		| btCollisionObject::CF_KINEMATIC_OBJECT
		| btCollisionObject::CF_NO_CONTACT_RESPONSE);


	App->SBC_Bullet->dynamicsWorld->addRigidBody(MObject->Phys_Body);

	App->SBC_Scene->B_Object[Index]->Physics_Valid = 1;

	App->SBC_Physics->Set_Physics(Index);

	return 1;
}

// *************************************************************************
// *		Set_Message_Defaults:- Terry and Hazel Flanigan 2022	  	   *
// *************************************************************************
void SB_Com_Entity::Set_Message_Defaults(int Index)
{
	App->SBC_Scene->B_Object[Index]->S_Message[0]->Trigger_Value = 0;
	App->SBC_Scene->B_Object[Index]->S_Message[0]->Counter_ID = 0;
	strcpy(App->SBC_Scene->B_Object[Index]->S_Message[0]->Counter_Name, "None");
	App->SBC_Scene->B_Object[Index]->S_Message[0]->Counter_Disabled = 1;

	strcpy(App->SBC_Scene->B_Object[Index]->S_Message[0]->Message_Text, "Welcome");
	App->SBC_Scene->B_Object[Index]->S_Message[0]->Message_PosX = 250;
	App->SBC_Scene->B_Object[Index]->S_Message[0]->Message_PosY = 10;

	App->SBC_Scene->B_Object[Index]->S_Message[0]->PosXCentre_Flag = 0;
	App->SBC_Scene->B_Object[Index]->S_Message[0]->PosYCentre_Flag = 0;

	App->SBC_Scene->B_Object[Index]->S_Message[0]->Text_Colour = Ogre::Vector4(0, 0, 0, 255);
	App->SBC_Scene->B_Object[Index]->S_Message[0]->BackGround_Colour = Ogre::Vector4(239, 239, 239, 255);

	App->SBC_Scene->B_Object[Index]->S_Message[0]->Show_BackGround = 1;
	return;
}

// ------------------------------------------------------------------------------------------ Particles
// *************************************************************************
// *			Add_New_Particle:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Com_Entity::Add_New_Particle(char* Script)
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->B_Object[Index] = new Base_Object();
	App->SBC_Scene->B_Object[Index]->S_Particle[0] = new Particle_type;
	Set_Particle_Defaults(Index);

	strcpy(App->SBC_Scene->B_Object[Index]->S_Particle[0]->ParticleScript, Script);

	App->SBC_Scene->B_Object[Index]->Type = Enums::Bullet_Type_None;
	App->SBC_Scene->B_Object[Index]->Shape = Enums::NoShape;
	App->SBC_Scene->B_Object[Index]->This_Object_UniqueID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_FileName, "DoorEntity_GD.mesh");

	strcpy_s(B_Name, "Particle_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, B_Name);

	Ogre::Vector3 Pos = App->SBC_Object->GetPlacement(-50);
	App->SBC_Scene->B_Object[Index]->Mesh_Pos = Pos;
	App->SBC_Scene->B_Object[Index]->Mesh_Scale = Ogre::Vector3(1, 1, 1);

	CreateParticle(Index);

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Particles_Folder, App->SBC_Scene->B_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->B_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[Index]->FileViewItem);

	App->SBC_Scene->UniqueID_Object_Counter++;
	App->SBC_Scene->Object_Count++;

}

// *************************************************************************
// *			CreateParticle:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Com_Entity::CreateParticle(int Index)
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

	Object->Object_Ent = App->SBC_Ogre->mSceneMgr->createEntity(Ogre_Name, Mesh_File, App->SBC_Ogre->App_Resource_Group);


	// ----------------------------------------------------------------------
	char buf[100];
	char Name[100];
	_itoa(Index, buf, 10);
	strcpy(Name, "TestPart_");
	strcat(Name, buf);


	Object->S_Particle[0]->Particle = App->SBC_Ogre->mSceneMgr->createParticleSystem(Name, Object->S_Particle[0]->ParticleScript);
	if (Object->S_Particle[0]->Particle == NULL)
	{
		App->Say("Poop");
	}

	Object->S_Particle[0]->Particle->setKeepParticlesInLocalSpace(true);

	Ogre::SceneNode* PartNode = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();

	PartNode->attachObject(Object->S_Particle[0]->Particle);

	PartNode->setPosition(Object->Mesh_Pos);

	PartNode->setScale(Object->Mesh_Scale);

	Object->Object_Node = PartNode;

	Object->Object_Node->setScale(Object->Mesh_Scale);
	Object->Object_Node->setOrientation(Object->Mesh_Quat);

	Object->S_Particle[0]->Particle->setSpeedFactor(Object->S_Particle[0]->SpeedFactor);
}

// *************************************************************************
// *		Set_Particle_Defaults:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Com_Entity::Set_Particle_Defaults(int Index)
{
	App->SBC_Scene->B_Object[Index]->Phys_Body = NULL;
	App->SBC_Scene->B_Object[Index]->Physics_Valid = 0;
	App->SBC_Scene->B_Object[Index]->Usage = Enums::Usage_Particle;

	App->SBC_Scene->B_Object[Index]->S_Particle[0]->Particle = NULL;
	App->SBC_Scene->B_Object[Index]->S_Particle[0]->SpeedFactor = 0.5;
	strcpy(App->SBC_Scene->B_Object[Index]->S_Particle[0]->ParticleScript, "GD_Smoke1");
}

// ------------------------------------------------------------------------------------------ Collectables
// *************************************************************************
//			Add_New_Collectable:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Com_Entity::Add_New_Collectable()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->B_Object[Index] = new Base_Object();
	App->SBC_Scene->B_Object[Index]->S_Collectable[0] = new Collectable_type;
	App->SBC_Com_Entity->Set_Collectables_Defaults(Index);

	Base_Object* Object = App->SBC_Scene->B_Object[Index];
	Object->This_Object_UniqueID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(Object->Mesh_Name, App->SBC_MeshViewer->Object_Name);
	strcpy(Object->Mesh_FileName, App->SBC_MeshViewer->Selected_MeshFile);
	strcpy(Object->Mesh_Resource_Path, App->SBC_Objects_Create->m_ResourcePath);
	strcpy(Object->Material_File, App->SBC_MeshViewer->m_Material_File);

	strcpy_s(B_Name, "Collectable_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, B_Name);

	Ogre::Vector3 Pos = App->SBC_Object->GetPlacement(-50);
	App->SBC_Scene->B_Object[Index]->Mesh_Pos = Pos;

	Object->Type = Enums::Bullet_Type_Static;
	Object->Shape = Enums::Shape_Box;


	Create_Collectable_Entity(Index);

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Collectables_Folder, App->SBC_Scene->B_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->B_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[Index]->FileViewItem);
	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_EntitiesFolder);

	App->SBC_Scene->UniqueID_Object_Counter++; // Unique ID
	App->SBC_Scene->Object_Count++;  // Must be last line

	App->SBC_Scene->B_Object[Index]->Altered = 1;
	App->SBC_Scene->Scene_Modified = 1;

	return 1;
}

// *************************************************************************
//		Create_Collectable_Entity:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Com_Entity::Create_Collectable_Entity(int Index)
{
	char Mesh_File[255];
	char ConNum[256];
	char Ogre_Name[256];

	Base_Object* Object = App->SBC_Scene->B_Object[Index];


	strcpy_s(Ogre_Name, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(Ogre_Name, ConNum);

	strcpy(Mesh_File, Object->Mesh_FileName);

	Object->Object_Ent = App->SBC_Ogre->mSceneMgr->createEntity(Ogre_Name, Mesh_File, App->SBC_Scene->Project_Resource_Group);
	Object->Object_Node = App->SBC_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->Object_Node->attachObject(Object->Object_Ent);

	Object->Object_Node->setVisible(true);

	Object->Object_Node->setOrientation(Object->Mesh_Quat);

	Object->Object_Node->setPosition(Object->Mesh_Pos);

	App->SBC_Scene->Scene_Loaded = 1;

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

	App->SBC_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->Phys_Body = new btRigidBody(rbInfo);
	Object->Phys_Body->setRestitution(1.0);
	Object->Phys_Body->setFriction(1.5);
	Object->Phys_Body->setUserPointer(Object->Object_Node);
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Usage = Enums::Usage_Colectable;
	Object->Phys_Body->setUserIndex(Enums::Usage_Colectable);
	Object->Phys_Body->setUserIndex2(Index);

	int f = Object->Phys_Body->getCollisionFlags();
	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->SBC_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	App->SBC_Physics->Set_Physics(Index);

	App->SBC_Scene->B_Object[Index]->Folder = Enums::Folder_Collectables;

	return 1;
}

// *************************************************************************
// *		Set_Collectables_Defaults:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void SB_Com_Entity::Set_Collectables_Defaults(int Index)
{
	App->SBC_Scene->B_Object[Index]->Altered = 0;

	strcpy(App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Sound_File, "footstep.ogg");
	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Play = 1;
	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->SndVolume = 0.5;

	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths = 1; // Add
	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Value = 1;

	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_ID = 0;
	strcpy(App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Name, "Not_Set");

	App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Disabled = 0;

}
