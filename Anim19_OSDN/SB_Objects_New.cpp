/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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

#include "StdAfx.h"
#include "GD19_App.h"
#include "SB_Objects_New.h"

#include <BulletCollision\CollisionDispatch\btGhostObject.h>

#pragma warning( disable : 4482)

SB_Objects_New::SB_Objects_New(void)
{
}

SB_Objects_New::~SB_Objects_New(void)
{
}

// *************************************************************************
//							Add_New_Area Terry							   *
// *************************************************************************
bool SB_Objects_New::Add_New_Area(void)
{
	int Index = App->Cl_Scene_Data->ObjectCount;


	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	strcpy(Object->Name, App->SBC_MeshViewer->Object_Name);
	strcpy(Object->MeshName, App->SBC_MeshViewer->Selected_MeshFile);
	strcpy(Object->MeshName_FullPath, App->SBC_MeshViewer->Selected_MeshFile);

	char PathFile[256];
	char ConNum[256];
	char ATest[256];

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(PathFile, Object->MeshName);
	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, PathFile, App->Cl19_Ogre->App_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);

	Object->OgreNode->setVisible(true);
	Object->OgreNode->setScale(Object->Mesh_Scale);

	Ogre::Vector3 Pos = App->Cl_Objects_Com->Centre_of_Trimesh(Index);
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);

	//---------------------- Tri_Mesh

	Object->create_New_Trimesh(Object->OgreEntity);

	Object->Usage = Enums::Usage_Room;


	//HTREEITEM Temp = App->Cl_FileView->Add_Room_Object(Object->Name, Index);
	//Object->ListViewItem = Temp;

	App->Cl_Scene_Data->Scene_Has_Area = 1;
	App->Cl_Scene_Data->SceneLoaded = 1;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line

	return 1;
}

// *************************************************************************
//						Add_New_CollectableEntity Terry Bernie			   *
// *************************************************************************
bool SB_Objects_New::Add_New_CollectableEntity()
{
	int Index = App->Cl_Scene_Data->ObjectCount;

	if (App->SBC_MeshViewer->Physics_Type == Enums::Bullet_Type_Volume)
	{
		Add_Physics_Volume_Box();
		return 1;
	}

	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	App->Cl_Scene_Data->Cl_Object[Index]->HasSound = 1;
	
	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Name, App->SBC_MeshViewer->Object_Name);
	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName, App->SBC_MeshViewer->Selected_MeshFile);
	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName_FullPath, App->SBC_MeshViewer->Selected_MeshFile);

	char PathFile[256];
	char ConNum[256];
	char ATest[256];
	
	
	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(PathFile, Object->MeshName);
	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, PathFile, App->Cl19_Ogre->App_Resource_Group);

	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);

	Object->OgreNode->setVisible(true);
	Object->OgreNode->setScale(Object->Mesh_Scale);

	Ogre::Vector3 Pos = Object->GetPlacement();
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);



	App->Cl_Scene_Data->SceneLoaded = 1;

	//---------------------- Static
	if (App->SBC_MeshViewer->Physics_Type == Enums::Bullet_Type_Static)
	{
		if (App->SBC_MeshViewer->Physics_Shape == Enums::Shape_Box)
		{
			Add_New_Physics_Static_Box(false);
			Object->Physics_Valid = 1;
		}

		if (App->SBC_MeshViewer->Physics_Shape == Enums::Sphere)
		{
			Add_New_Physics_Static_Sphere(false);
			Object->Physics_Valid = 1;
		}

		if (App->SBC_MeshViewer->Physics_Shape == Enums::Capsule)
		{
			Add_New_Physics_Static_Capsule(false);
			Object->Physics_Valid = 1;
		}

		if (App->SBC_MeshViewer->Physics_Shape == Enums::Cylinder)
		{
			Add_New_Physics_Static_Cylinder(false);
			Object->Physics_Valid = 1;
		}

		if (App->SBC_MeshViewer->Physics_Shape == Enums::Cone)
		{
			Add_New_Physics_Static_Cone(false);
			Object->Physics_Valid = 1;
		}
	}

	Object->Usage = Enums::Usage_Colectable;
	Object->bt_body->setUserIndex(Enums::Usage_Colectable);
	Object->bt_body->setUserIndex2(Index);

	Object->Folder = Enums::Folder_Collectables;


	//HTREEITEM Temp = App->Cl_FileView->Add_Collectable(App->SBC_MeshViewer->Object_Name, Index);
	//Object->ListViewItem = Temp;

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line
	return 1;
}

// *************************************************************************
//						Add_New_MessageEntity Terry Bernie				   *
// *************************************************************************
bool SB_Objects_New::Add_New_MessageEntity()
{
	int Index = App->Cl_Scene_Data->ObjectCount;

	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, "Test Text");

	App->Cl_Scene_Data->Cl_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->Cl_Scene_Data->Cl_Object[Index]->Shape = Enums::Shape_Box;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName, "Test_cube.mesh");

	char ConNum[256];
	char ATest[256];
	char Name[256];
	
	strcpy_s(Name, "Message_");
	_itoa(Index, ConNum, 10);
	strcat(Name, ConNum);

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Object->Name, Name);
	strcpy(Object->MeshName, "Test_cube.mesh");
	strcpy(Object->MeshName_FullPath, "Test_cube.mesh");

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "Test_cube.mesh", App->Cl19_Ogre->App_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(1, 1, 1);

	Ogre::Vector3 Pos = Object->GetPlacement();
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);
	//------------------

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2; // Size by Bounding Box
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();
	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btVector3 initialPosition(btVector3(Centre.x, Centre.y, Centre.z));
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_Message;
	Object->bt_body->setUserIndex(Enums::Usage_Message);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Folder = Enums::Folder_Message_Entity;
	Object->Physics_Valid = 1;

	///HTREEITEM Temp = App->Cl_FileView->Add_Message_Entity(Object->Name, Index);
	///Object->ListViewItem = Temp;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line
	return 1;
}

// *************************************************************************
//						Add_New_MoveEntity Terry Bernie					   *
// *************************************************************************
bool SB_Objects_New::Add_New_MoveEntity()
{
	int Index = App->Cl_Scene_Data->ObjectCount;

	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];
	//------------------------------------------------------------------------ Move Type

	App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType = new Move_Type2;
	App->Cl_Scene_Data->Set_Move_Defaults(Index);


	App->Cl_Scene_Data->Cl_Object[Index]->HasSound = 1;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, "Test Text");

	App->Cl_Scene_Data->Cl_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->Cl_Scene_Data->Cl_Object[Index]->Shape = Enums::Shape_Box;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName, "Test_cube.mesh");

	char ConNum[256];
	char ATest[256];
	char Name[256];
	
	strcpy_s(Name, "Move_");
	_itoa(Index, ConNum, 10);
	strcat(Name, ConNum);

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Object->Name, Name);
	strcpy(Object->MeshName, "DoorEntity_GD.mesh");
	strcpy(Object->MeshName_FullPath, "DoorEntity_GD.mesh");

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "DoorEntity_GD.mesh", App->Cl19_Ogre->App_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(1, 1, 1);

	Ogre::Vector3 Pos = Object->GetPlacement();
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);
	Object->S_MoveType->MeshPos = Pos;   // Record Mesh Pos in Move Structure
	//------------------

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2; // Size by Bounding Box
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();
	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btVector3 initialPosition(btVector3(Centre.x, Centre.y, Centre.z));
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_Move;
	Object->bt_body->setUserIndex(Enums::Usage_Move);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Folder = Enums::Folder_Move_Entity;
	Object->Physics_Valid = 1;

	///HTREEITEM Temp = App->Cl_FileView->Add_Move_Entity(Object->Name, Index);
	///Object->ListViewItem = Temp;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line

	return 1;
}

// *************************************************************************
//						Add_New_SoundEntity Terry Bernie				   *
// *************************************************************************
bool SB_Objects_New::Add_New_SoundEntity()
{
	int Index = App->Cl_Scene_Data->ObjectCount;

	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, "Welcome.ogg");
	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mFileAndPath, App->Cl_SoundMgr->Default_Folder);
	strcat(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mFileAndPath, "\\Media\\Sounds\\");
	strcat(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mFileAndPath, "Welcome.ogg");

	App->Cl_Scene_Data->Cl_Object[Index]->HasSound = 1;
	
	App->Cl_Scene_Data->Cl_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->Cl_Scene_Data->Cl_Object[Index]->Shape = Enums::Shape_Box;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName, "SoundEntity_GD.mesh");

	char ConNum[256];
	char ATest[256];
	char Name[256];
	
	strcpy_s(Name, "Sound_");
	_itoa(Index, ConNum, 10);
	strcat(Name, ConNum);

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Object->Name, Name);
	strcpy(Object->MeshName, "SoundEntity_GD.mesh");
	strcpy(Object->MeshName_FullPath, "SoundEntity_GD.mesh");

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "SoundEntity_GD.mesh", App->Cl19_Ogre->App_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(1, 1, 1);

	Ogre::Vector3 Pos = Object->GetPlacement();
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);
	//------------------

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2; // Size by Bounding Box
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();
	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btVector3 initialPosition(btVector3(Centre.x, Centre.y, Centre.z));
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_Sound;
	Object->bt_body->setUserIndex(Enums::Usage_Sound);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Folder = Enums::Folder_Sound_Entity;
	Object->Physics_Valid = 1;

	///HTREEITEM Temp = App->Cl_FileView->Add_Sound_Entity(Object->Name, Index);
	///Object->ListViewItem = Temp;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line
	return 1;
}

// *************************************************************************
//						Add_New_TeleportEntity Terry Bernie			   *
// *************************************************************************
bool SB_Objects_New::Add_New_TeleportEntity()
{
	int Index = App->Cl_Scene_Data->ObjectCount;

	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	// Create Teleport and use Player Start Position as Default
	App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0] = new Teleport_type2;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Name, App->Cl_Scene_Data->S_Player_Locations[0]->Name);
	App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Player_Position = App->Cl_Scene_Data->S_Player_Locations[0]->Current_Position;
	App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Physics_Position = App->Cl_Scene_Data->S_Player_Locations[0]->Physics_Position;
	App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Physics_Rotation = App->Cl_Scene_Data->S_Player_Locations[0]->Physics_Rotation;

	// Create Sound 
	App->Cl_Scene_Data->Cl_Object[Index]->HasSound = 1;
	
	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, "Test Text");

	App->Cl_Scene_Data->Cl_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->Cl_Scene_Data->Cl_Object[Index]->Shape = Enums::Shape_Box;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName, "TeleportSend.mesh");

	char ConNum[256];
	char ATest[256];
	char Name[256];
	
	strcpy_s(Name, "Teleport_");
	_itoa(Index, ConNum, 10);
	strcat(Name, ConNum);

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Object->Name, Name);
	strcpy(Object->MeshName, "TeleportSend.mesh");
	strcpy(Object->MeshName_FullPath, "TeleportSend.mesh");

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "TeleportSend.mesh", App->Cl19_Ogre->App_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(1, 1, 1);

	Ogre::Vector3 Pos = Object->GetPlacement();
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);
	//------------------

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2; // Size by Bounding Box
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();
	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btVector3 initialPosition(btVector3(Centre.x, Centre.y, Centre.z));
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_Teleport;
	Object->bt_body->setUserIndex(Enums::Usage_Teleport);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Folder = Enums::Folder_Teleports;
	Object->Physics_Valid = 1;

	///HTREEITEM Temp = App->Cl_FileView->Add_Teleport(Object->Name, Index);
	///Object->ListViewItem = Temp;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line
	return 1;
}

// *************************************************************************
//						Add_New_EnvironmentEntity Terry Bernie			   *
// *************************************************************************
bool SB_Objects_New::Add_New_EnvironmentEntity()
{
	int Index = App->Cl_Scene_Data->ObjectCount;

	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	// Create Sound 
	App->Cl_Scene_Data->Cl_Object[Index]->HasSound = 1;
	
	//  Environment
	App->Cl_Scene_Data->Cl_Object[Index]->S_Environment[0] = new Environment2;
	App->Cl_Scene_Data->Cl_Object[Index]->S_Environment[0]->FogOn = 0;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, "Test Text"); // ??

	App->Cl_Scene_Data->Cl_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->Cl_Scene_Data->Cl_Object[Index]->Shape = Enums::Shape_Box;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName, "GD10Env.mesh");

	char ConNum[256];
	char ATest[256];
	char Name[256];

	strcpy_s(Name, "Env_");
	_itoa(Index, ConNum, 10);
	strcat(Name, ConNum);

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Object->Name, Name);
	strcpy(Object->MeshName, "GD10Env.mesh"); // Needs Chaning to Environment
	strcpy(Object->MeshName_FullPath, "GD10Env.mesh");

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "GD10Env.mesh", App->Cl19_Ogre->App_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(1, 1, 1);

	Ogre::Vector3 Pos = Object->GetPlacement();
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);
	//------------------

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2; // Size by Bounding Box
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();
	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btVector3 initialPosition(btVector3(Centre.x, Centre.y, Centre.z));
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_Environment;
	Object->bt_body->setUserIndex(Enums::Usage_Environment);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Folder = Enums::Folder_Environment;
	Object->Physics_Valid = 1;

	///HTREEITEM Temp = App->Cl_FileView->Add_Environment(Object->Name, Index);
	///Object->ListViewItem = Temp;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line
	return 1;
}

// *************************************************************************
//						 Add_New_Area_Change Terry Bernie			   *
// *************************************************************************
bool SB_Objects_New::Add_New_Area_Change()
{
	int Index = App->Cl_Scene_Data->ObjectCount;

	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];


	// Create Sound 
	App->Cl_Scene_Data->Cl_Object[Index]->HasSound = 1;
	
	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, "Test Text");

	App->Cl_Scene_Data->Cl_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->Cl_Scene_Data->Cl_Object[Index]->Shape = Enums::Shape_Box;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName, "GD10RoomChange.mesh");

	char ConNum[256];
	char ATest[256];
	char Name[256];

	strcpy_s(Name, "RoomChange_");
	_itoa(Index, ConNum, 10);
	strcat(Name, ConNum);

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Object->Name, Name);
	strcpy(Object->MeshName, "GD10RoomChange.mesh"); // Needs Chaning to Environment
	strcpy(Object->MeshName_FullPath, "GD10RoomChange.mesh");

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "GD10RoomChange.mesh", App->Cl19_Ogre->App_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(1, 1, 1);

	Ogre::Vector3 Pos = Object->GetPlacement();
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);
	//------------------

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2; // Size by Bounding Box
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();
	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btVector3 initialPosition(btVector3(Centre.x, Centre.y, Centre.z));
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_RoomChange;
	Object->bt_body->setUserIndex(Enums::Usage_RoomChange);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Folder = Enums::Folder_RoomChange;
	Object->Physics_Valid = 1;

	///HTREEITEM Temp = App->Cl_FileView->Add_Area_Change(Object->Name, Index);
	///Object->ListViewItem = Temp;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line
	return 1;
}

// *************************************************************************
//						Add_New_Change_Level Terry Bernie			   *
// *************************************************************************
bool SB_Objects_New::Add_New_Change_Level()
{
	int Index = App->Cl_Scene_Data->ObjectCount;

	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	
	// Create Sound 
	App->Cl_Scene_Data->Cl_Object[Index]->HasSound = 1;
	
	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, "Test Text");

	App->Cl_Scene_Data->Cl_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->Cl_Scene_Data->Cl_Object[Index]->Shape = Enums::Shape_Box;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName, "TeleportRecieve.mesh");

	char ConNum[256];
	char ATest[256];
	char Name[256];

	strcpy_s(Name, "Change_Level_");
	_itoa(Index, ConNum, 10);
	strcat(Name, ConNum);

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Object->Name, Name);
	strcpy(Object->MeshName, "TeleportRecieve.mesh"); // Needs Chaning to Environment
	strcpy(Object->MeshName_FullPath, "TeleportRecieve.mesh");

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "TeleportRecieve.mesh", App->Cl19_Ogre->App_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(1, 1, 1);

	Ogre::Vector3 Pos = Object->GetPlacement();
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);
	//------------------

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2; // Size by Bounding Box
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();
	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btVector3 initialPosition(btVector3(Centre.x, Centre.y, Centre.z));
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_ChangeLevel;
	Object->bt_body->setUserIndex(Enums::Usage_ChangeLevel);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Folder = Enums::Folder_Change_Level;
	Object->Physics_Valid = 1;

	///HTREEITEM Temp = App->Cl_FileView->Add_Change_Level(Object->Name, Index);
	///Object->ListViewItem = Temp;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line
	return 1;
}

// *************************************************************************
//								Add_New_Particle Terry					   *
// *************************************************************************
bool SB_Objects_New::Add_New_Particle()
{
	int Index = App->Cl_Scene_Data->ObjectCount;

	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, "Welcome.ogg");
	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mFileAndPath, App->Cl_SoundMgr->Default_Folder);
	strcat(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mFileAndPath, "\\Media\\Sounds\\");
	strcat(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mFileAndPath, "Welcome.ogg");

	App->Cl_Scene_Data->Cl_Object[Index]->HasSound = 1;

	App->Cl_Scene_Data->Cl_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->Cl_Scene_Data->Cl_Object[Index]->Shape = Enums::Shape_Box;

	strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName, "Smoke1");

	char ConNum[256];
	char ATest[256];
	char Name[256];

	strcpy_s(Name, "Particle_");
	_itoa(Index, ConNum, 10);
	strcat(Name, ConNum);

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Object->Name, Name);
	//strcpy(Object->MeshName, "SoundEntity_GD.mesh");
	//strcpy(Object->MeshName_FullPath, "SoundEntity_GD.mesh");

	/*Object->OgreEntity = App->Cl_Ogre->mSceneMgr->createEntity(ATest, "SoundEntity_GD.mesh", App->Cl_Ogre->PermResourceGroup);
	Object->OgreNode = App->Cl_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(1, 1, 1);*/

	/*SceneNode* myNode = static_cast<SceneNode*>(App->Cl_Ogre->mSceneMgr->getRootSceneNode()->createChild());
	BillboardSet* mySet = App->Cl_Ogre->mSceneMgr->createBillboardSet("mySet");
	Billboard* myBillboard = mySet->createBillboard(Vector3(0, 0, 0));
	myNode->attachObject(mySet);
	mySet->setMaterialName("SoundEntityMat_GD1", App->Cl_Ogre->PermResourceGroup);*/
	

	Object->Ogre_Particle = App->Cl19_Ogre->mSceneMgr->createParticleSystem(ATest, "Examples/Smoke1");
	Object->Ogre_Particle->setKeepParticlesInLocalSpace(true);

	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->Ogre_Particle);
	Object->OgreNode->scale(10,10,10);
	//Object->OgreNode->setVisible(true);

	Ogre::Vector3 Pos = Object->GetPlacement();
	Object->Mesh_Pos = Pos;
	Object->OgreNode->setPosition(Pos);
	////------------------

	Object->Ogre_Particle->setSpeedFactor(0.2);
	

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2; // Size by Bounding Box
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	//Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();
	//Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);
	Object->Physics_Pos = Ogre::Vector3(Pos.x, Pos.y, Pos.z);

	btVector3 initialPosition(btVector3(Pos.x, Pos.y, Pos.z));
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	//Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_Particle;
	Object->bt_body->setUserIndex(Enums::Usage_Particle);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);
	
	Object->Folder = Enums::Folder_Particle;
	Object->Physics_Valid = 1;

	///HTREEITEM Temp = App->Cl_FileView->Add_Particle_Entity(Object->Name, Index);
	///Object->ListViewItem = Temp;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line

	return 1;
}

// *************************************************************************
//						Add_New_Physics_Static_Box Terry Bernie			   *
// *************************************************************************
void SB_Objects_New::Add_New_Physics_Static_Box(bool Dynamic)
{
	int Index = App->SBC_Scene->Object_Count;

	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	if (Dynamic == 1)
	{
		/*Object->Type = Enums::Bullet_Type_Dynamic;
		Object->Shape = Enums::Shape_Box;*/

	}
	else
	{
		/*Object->Type = Enums::Bullet_Type_Static;
		Object->Shape = Enums::Shape_Box;*/
	}

	AxisAlignedBox worldAAB = Object->Object_Ent->getBoundingBox();
	worldAAB.transformAffine(Object->Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();
	

	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btScalar mass;
	if (Dynamic == 1)
	{
		mass = 1.0f;
	}
	else
	{
		mass = 0.0f;
	}

	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

	startTransform.setOrigin(initialPosition);

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->Object_Node);
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

	if (Dynamic == 1)
	{
		Object->Usage = Enums::Usage_Dynamic;
		Object->Phys_Body->setUserIndex(Enums::Usage_Dynamic);
		Object->Phys_Body->setUserIndex2(Index);
	}
	else
	{
		Object->Usage = Enums::Usage_Static;
		Object->Phys_Body->setUserIndex(Enums::Usage_Static);
		Object->Phys_Body->setUserIndex2(Index);
	}

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	int f = Object->Phys_Body->getCollisionFlags();
	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	//Object->Collect_Object_Data();


	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);
}


// *************************************************************************
//					Add_New_Physics_Static_Sphere Terry Bernie			   *
// *************************************************************************
void SB_Objects_New::Add_New_Physics_Static_Sphere(bool Dynamic)
{
	int Index = App->Cl_Scene_Data->ObjectCount;
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	if (Dynamic == 1)
	{
		Object->Type = Enums::Bullet_Type_Dynamic;
		Object->Shape = Enums::Sphere;

	}
	else
	{
		Object->Type = Enums::Bullet_Type_Static;
		Object->Shape = Enums::Sphere;
	}

	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();

	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btScalar mass;

	if (Dynamic == 1)
	{
		mass = 1.0f;
	}
	else
	{
		mass = 0.0f;
	}

	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

	startTransform.setOrigin(initialPosition);

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(Object->OgreNode);
	Object->Physics_Size = Ogre::Vector3(Radius, 0, 0);

	btCollisionShape* newRigidShape = new btSphereShape(Radius);
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	if (Dynamic == 1)
	{
		Object->Usage = Enums::Usage_Dynamic;
		Object->bt_body->setUserIndex(Enums::Usage_Dynamic);
		Object->bt_body->setUserIndex2(Index);
	}
	else
	{
		Object->Usage = Enums::Usage_Static;
		Object->bt_body->setUserIndex(Enums::Usage_Static);
		Object->bt_body->setUserIndex2(Index);
	}

	Object->bt_body->setCustomDebugColor(btVector3(0, 1, 1));
	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Object->Collect_Object_Data();

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);
}

// *************************************************************************
//					Add_New_Physics_Static_Capsule Terry Bernie			   *
// *************************************************************************
void SB_Objects_New::Add_New_Physics_Static_Capsule(bool Dynamic)
{
	int Index = App->Cl_Scene_Data->ObjectCount;
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	if (Dynamic == 1)
	{
		Object->Type = Enums::Bullet_Type_Dynamic;
		Object->Shape = Enums::Capsule;

	}
	else
	{
		Object->Type = Enums::Bullet_Type_Static;
		Object->Shape = Enums::Capsule;
	}


	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();

	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btScalar mass;
	if (Dynamic == 1)
	{
		mass = 1.0f;
	}
	else
	{
		mass = 0.0f;
	}

	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

	startTransform.setOrigin(initialPosition);

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(Object->OgreNode);
	Object->Physics_Size = Ogre::Vector3(Radius, sy, 0);

	btCollisionShape* newRigidShape = new btCapsuleShape(Radius, sy);
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCustomDebugColor(btVector3(0, 1, 1));

	if (Dynamic == 1)
	{
		Object->Usage = Enums::Usage_Dynamic;
		Object->bt_body->setUserIndex(Enums::Usage_Dynamic);
		Object->bt_body->setUserIndex2(Index);
	}
	else
	{
		Object->Usage = Enums::Usage_Static;
		Object->bt_body->setUserIndex(Enums::Usage_Static);
		Object->bt_body->setUserIndex2(Index);
	}

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Object->Collect_Object_Data();

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);
}

// *************************************************************************
//					Add_New_Physics_Static_Cylinder Terry Bernie		   *
// *************************************************************************
void SB_Objects_New::Add_New_Physics_Static_Cylinder(bool Dynamic)
{
	int Index = App->Cl_Scene_Data->ObjectCount;
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	if (Dynamic == 1)
	{
		Object->Type = Enums::Bullet_Type_Dynamic;
		Object->Shape = Enums::Cylinder;
	}
	else
	{
		Object->Type = Enums::Bullet_Type_Static;
		Object->Shape = Enums::Cylinder;
	}

	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();

	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btScalar mass;
	if (Dynamic == 1)
	{
		mass = 1.0f;
	}
	else
	{
		mass = 0.0f;
	}

	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

	startTransform.setOrigin(initialPosition);

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(Object->OgreNode);
	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btCylinderShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCustomDebugColor(btVector3(0, 1, 1));

	if (Dynamic == 1)
	{
		Object->Usage = Enums::Usage_Dynamic;
		Object->bt_body->setUserIndex(Enums::Usage_Dynamic);
		Object->bt_body->setUserIndex2(Index);
	}
	else
	{
		Object->Usage = Enums::Usage_Static;
		Object->bt_body->setUserIndex(Enums::Usage_Static);
		Object->bt_body->setUserIndex2(Index);
	}

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Object->Collect_Object_Data();

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);
}

// *************************************************************************
//					Add_PhysicsNew__Static_Cone Terry Bernie			   *
// *************************************************************************
void SB_Objects_New::Add_New_Physics_Static_Cone(bool Dynamic)
{
	int Index = App->Cl_Scene_Data->ObjectCount;
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	if (Dynamic == 1)
	{
		Object->Type = Enums::Bullet_Type_Dynamic;
		Object->Shape = Enums::Cone;
	}
	else
	{
		Object->Type = Enums::Bullet_Type_Static;
		Object->Shape = Enums::Cone;
	}

	Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();

	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btScalar mass;
	if (Dynamic == 1)
	{
		mass = 1.0f;
	}
	else
	{
		mass = 0.0f;
	}

	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

	startTransform.setOrigin(initialPosition);

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->OgreNode);
	float sx = Size.x / 2;
	float sy = Size.y;// / 2;
	float sz = Size.z / 2;

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(Object->OgreNode);
	Object->Physics_Size = Ogre::Vector3(Radius, sy, 0);

	btCollisionShape* newRigidShape = new btConeShape(Radius, sy);
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(startTransform);

	Object->bt_body->setCustomDebugColor(btVector3(0, 1, 1));

	if (Dynamic == 1)
	{
		Object->Usage = Enums::Usage_Dynamic;
		Object->bt_body->setUserIndex(Enums::Usage_Dynamic);
		Object->bt_body->setUserIndex2(Index);
	}
	else
	{
		Object->Usage = Enums::Usage_Static;
		Object->bt_body->setUserIndex(Enums::Usage_Static);
		Object->bt_body->setUserIndex2(Index);
	}

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Object->Collect_Object_Data();

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);
}


// *************************************************************************
//						Add_Physics_Volume_Box Terry Bernie				   *
// *************************************************************************
void SB_Objects_New::Add_Physics_Volume_Box()
{
	int Index = App->Cl_Scene_Data->ObjectCount;

	btGhostObject* ghostObject = new btGhostObject();

	ghostObject->setCollisionShape(new btBoxShape(btVector3(100, 100, 100)));

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btVector3 initialPosition(40, -63, 0);
	startTransform.setOrigin(initialPosition);

	ghostObject->setWorldTransform(startTransform);

	ghostObject->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);
	ghostObject->setUserIndex2(777);

	App->Cl_Bullet->dynamicsWorld->addCollisionObject(ghostObject, btBroadphaseProxy::SensorTrigger, btBroadphaseProxy::AllFilter & ~btBroadphaseProxy::SensorTrigger);
}

// *************************************************************************
//							Add_Stock_Message Terry Bernie				   *
// *************************************************************************
void SB_Objects_New::Add_Stock_Message()
{
	char ConNum[256];
	char AName[256];

	int MessageIndex = App->Cl_Scene_Data->Stock_Messgae_Count;
	App->Cl_Scene_Data->S_Messages[MessageIndex] = new Stock_Messages_type();
	App->Cl_Scene_Data->Set_Mesgaes_Defaults(MessageIndex);

	strcpy(AName, "Message_");
	_itoa(MessageIndex, ConNum, 10);
	strcat(AName, ConNum);

	strcpy(App->Cl_Scene_Data->S_Messages[MessageIndex]->Name, AName);

	OverlayManager& overlayManager = OverlayManager::getSingleton();
	App->Cl_Scene_Data->S_Messages[MessageIndex]->panel = static_cast<OverlayContainer*>(overlayManager.createOverlayElement("Panel", AName));

	App->Cl_Scene_Data->S_Messages[MessageIndex]->panel->setMetricsMode(Ogre::GMM_RELATIVE_ASPECT_ADJUSTED);
	App->Cl_Scene_Data->S_Messages[MessageIndex]->panel->setHorizontalAlignment(Ogre::GuiHorizontalAlignment::GHA_CENTER);
	App->Cl_Scene_Data->S_Messages[MessageIndex]->panel->setVerticalAlignment(Ogre::GuiVerticalAlignment::GVA_CENTER);
	App->Cl_Scene_Data->S_Messages[MessageIndex]->panel->setPosition(-20, -30);
	App->Cl_Scene_Data->S_Messages[MessageIndex]->panel->setDimensions(100, 100);

	strcpy(AName, "TextArea_");
	_itoa(MessageIndex, ConNum, 10);
	strcat(AName, ConNum);

	App->Cl_Scene_Data->S_Messages[MessageIndex]->textArea1 = static_cast<TextAreaOverlayElement*>(overlayManager.createOverlayElement("TextArea", AName));

	float Vert = App->Cl_Scene_Data->S_Messages[MessageIndex]->Pos_Vert;
	float Hoz = App->Cl_Scene_Data->S_Messages[MessageIndex]->Pos_Hoz;

	App->Cl_Scene_Data->S_Messages[MessageIndex]->textArea1->setMetricsMode(Ogre::GMM_PIXELS);
	App->Cl_Scene_Data->S_Messages[MessageIndex]->textArea1->setPosition(Hoz, Vert);
	App->Cl_Scene_Data->S_Messages[MessageIndex]->textArea1->setDimensions(100, 100);
	App->Cl_Scene_Data->S_Messages[MessageIndex]->textArea1->setCaption(App->Cl_Scene_Data->S_Messages[MessageIndex]->Default_Text);
	App->Cl_Scene_Data->S_Messages[MessageIndex]->textArea1->setCharHeight((Ogre::Real)App->Cl_Scene_Data->S_Messages[MessageIndex]->Font_Size);
	App->Cl_Scene_Data->S_Messages[MessageIndex]->textArea1->setFontName("BlueHighway");
	App->Cl_Scene_Data->S_Messages[MessageIndex]->textArea1->setColour(ColourValue(1, 1, 1));
	//App->Cl_Scene_Data->S_Messages[MessageIndex]->textArea1->setColourTop(ColourValue(1,1,1));


	// Create an overlay, and add the panel
	strcpy(AName, "OverlayName_");
	_itoa(MessageIndex, ConNum, 10);
	strcat(AName, ConNum);

	App->Cl_Scene_Data->S_Messages[MessageIndex]->overlay = overlayManager.create(AName);
	App->Cl_Scene_Data->S_Messages[MessageIndex]->overlay->add2D(App->Cl_Scene_Data->S_Messages[MessageIndex]->panel);

	// Add the text area to the panel
	App->Cl_Scene_Data->S_Messages[MessageIndex]->panel->addChild(App->Cl_Scene_Data->S_Messages[MessageIndex]->textArea1); // C Styl
//	App->Cl_Scene_Data->S_Messages[MessageIndex]->panel->addChild(S_Message[0]->textArea2);

	App->Cl_Scene_Data->Stock_Messgae_Count++;
}

// *************************************************************************
//							Add_Stock_Sound Terry Bernie				   *
// *************************************************************************
void SB_Objects_New::Add_Stock_Sound()
{
	char ConNum[256];
	char AName[256];

	int SoundIndex = App->Cl_Scene_Data->Stock_Sound_Count;
	App->Cl_Scene_Data->St_Sounds[SoundIndex] = new Stock_Sound_type();
	//App->Cl_Scene_Data->Set_Sound_Defaults(SoundIndex);

	strcpy(AName, "Sound_");
	_itoa(SoundIndex, ConNum, 10);
	strcat(AName, ConNum);

	strcpy(App->Cl_Scene_Data->St_Sounds[SoundIndex]->Name, AName);
	App->Cl_Scene_Data->St_Sounds[SoundIndex]->Deleted = 0;
	App->Cl_Scene_Data->St_Sounds[SoundIndex]->Is3D = 0;
	App->Cl_Scene_Data->St_Sounds[SoundIndex]->Loop = 0;
	App->Cl_Scene_Data->St_Sounds[SoundIndex]->Pan = 0;
	App->Cl_Scene_Data->St_Sounds[SoundIndex]->Play = 0;
	App->Cl_Scene_Data->St_Sounds[SoundIndex]->SndFile = NULL;
	strcpy(App->Cl_Scene_Data->St_Sounds[SoundIndex]->SoundFile,"footstep.ogg");
	strcpy(App->Cl_Scene_Data->St_Sounds[SoundIndex]->SoundFileAndPath,"footstep.ogg");
	App->Cl_Scene_Data->St_Sounds[SoundIndex]->Volume = 1;
	App->Cl_Scene_Data->St_Sounds[SoundIndex]->Sound_ID = App->Cl_Scene_Data->StockSounds_ID_Counter;

	App->Cl_Scene_Data->StockSounds_ID_Counter++; // Only on new Objects
	App->Cl_Scene_Data->Stock_Sound_Count++;

}

// *************************************************************************
//							Add_Stock_Panel Terry Bernie				   *
// *************************************************************************
void SB_Objects_New::Add_Stock_Panel()
{
	// Add New Panel Object 310719 // Needs Moving
	int Panel_Number = App->Cl_Panels_Com->Create_Panel();

	char Name[256];
	strcpy(Name, App->Cl_Panels_Com->Get_Panel_Name(Panel_Number));
}

// *************************************************************************
//					Get_BoundingBox_World_Centre Terry Bernie			   *
// *************************************************************************
Ogre::Vector3 SB_Objects_New::Get_BoundingBox_World_Centre(int Object_Index)
{
	AxisAlignedBox worldAAB = App->Cl_Scene_Data->Cl_Object[Object_Index]->OgreEntity->getBoundingBox();
	worldAAB.transformAffine(App->Cl_Scene_Data->Cl_Object[Object_Index]->OgreNode->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	return Centre;
}
