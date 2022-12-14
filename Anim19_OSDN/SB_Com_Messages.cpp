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
#include "SB_Com_Messages.h"

SB_Com_Messages::SB_Com_Messages()
{
}

SB_Com_Messages::~SB_Com_Messages()
{
}

// *************************************************************************
//				Add_New_Message:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Com_Messages::Add_New_Message()
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
bool SB_Com_Messages::Create_Message_Entity(int Index)
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

	App->SBC_Objects_Create->Set_Physics(Index);

	return 1;
}

// *************************************************************************
// *		Set_Message_Defaults:- Terry and Hazel Flanigan 2022	  	   *
// *************************************************************************
void SB_Com_Messages::Set_Message_Defaults(int Index)
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

