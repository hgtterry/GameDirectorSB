/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Objects_Create.h"

SB_Objects_Create::SB_Objects_Create(void)
{
	m_ResourcePath[0] = 0;
}

SB_Objects_Create::~SB_Objects_Create(void)
{
}

// *************************************************************************
//			Add_Objects_From_File:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Objects_Create::Add_Objects_From_File() // From File
{
	
	int Object_Count = App->SBC_Scene->Object_Count;
	int Count = 0;

	while (Count < Object_Count)
	{
		if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Sound)
		{
			Create_Sound_Entity(Count);

			HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Sounds_Folder, App->SBC_Scene->B_Object[Count]->Mesh_Name, Count, false);
			App->SBC_Scene->B_Object[Count]->FileViewItem = Temp;

			App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Sounds_Folder);
		}
		else if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Message)
		{
			App->SBC_Com_Messages->Create_Message_Entity(Count);
			App->SBC_Scene->B_Object[Count]->Set_ImGui_Panel_Name();

			HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Message_Trigger_Folder, App->SBC_Scene->B_Object[Count]->Mesh_Name, Count, false);
			App->SBC_Scene->B_Object[Count]->FileViewItem = Temp;

			App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Message_Trigger_Folder);
		}
		else if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Move)
		{
			App->SBC_Com_MoveEntity->Create_Move_Entity(Count);

			HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Move_Folder, App->SBC_Scene->B_Object[Count]->Mesh_Name, Count, false);
			App->SBC_Scene->B_Object[Count]->FileViewItem = Temp;

			App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Move_Folder);

		}
		else if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Teleport)
		{
			Create_TeleportEntity(Count);

			HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Teleporters_Folder, App->SBC_Scene->B_Object[Count]->Mesh_Name, Count, false);
			App->SBC_Scene->B_Object[Count]->FileViewItem = Temp;

			App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Teleporters_Folder);

		}
		else if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Colectable)
		{
			
			App->SBC_Com_Collectables->Create_Collectable_Entity(Count);

			HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Collectables_Folder, App->SBC_Scene->B_Object[Count]->Mesh_Name, Count, false);
			App->SBC_Scene->B_Object[Count]->FileViewItem = Temp;

			App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Collectables_Folder);

		}
		else if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Teleport)
		{
			//Add_TeleportEntity_FFile(Count);
		}
		else
		{
			App->SBC_Objects_Create->Add_New_Object(Count,0);
			App->SBC_Scene->B_Object[Count]->Altered = 0;
			App->SBC_Scene->B_Object[Count]->Folder = Enums::Folder_Objects;
			App->SBC_Scene->B_Object[Count]->FileViewItem = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Objects_Folder, App->SBC_Scene->B_Object[Count]->Mesh_Name, Count, false);
		}

		Count++;
	}

	if (Object_Count > 0)
	{
		App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Objects_Folder);
		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 1);
		App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[0]->FileViewItem);
	}

	return 1;
}

// *************************************************************************
//		Add_Objects_From_MeshViewer:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Objects_Create::Add_Objects_From_MeshViewer()
{

	if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Collectables) // Collectables
	{
		App->SBC_Com_Collectables->Add_New_Collectable();
		return;
	}


	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->B_Object[Index] = new Base_Object();
	
	Base_Object* Object = App->SBC_Scene->B_Object[Index];
	Object->This_Object_ID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID


	strcpy(Object->Mesh_Name, App->SBC_MeshViewer->Object_Name);
	strcpy(Object->Mesh_FileName, App->SBC_MeshViewer->Selected_MeshFile);
	strcpy(Object->Mesh_Resource_Path, m_ResourcePath);
	strcpy(Object->Material_File, App->SBC_MeshViewer->m_Material_File);

	Object->Type = App->SBC_MeshViewer->Physics_Type;
	Object->Shape = App->SBC_MeshViewer->Physics_Shape;


	App->SBC_Objects_Create->Dispatch_MeshViewer();

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[Index]->FileViewItem);


	App->SBC_Scene->UniqueID_Object_Counter++; // Unique ID
	App->SBC_Scene->Object_Count++;  // Must be last line

	App->SBC_Scene->Scene_Modified = 1;
	
}

// *************************************************************************
//			Dispatch_MeshViewer:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Objects_Create::Dispatch_MeshViewer()
{
	int Index = App->SBC_Scene->Object_Count;

	if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area) // Area
	{
		App->SBC_Area->Add_Aera_To_Project(0, App->SBC_MeshViewer->Selected_MeshFile, m_ResourcePath);
		App->Say("Dispatch_MeshViewer");
	}
	else
	{
		Add_New_Object(Index, 1);
		App->SBC_Scene->B_Object[Index]->Altered = 1;
		App->SBC_Scene->B_Object[Index]->Folder = Enums::Folder_Objects;
		App->SBC_Scene->B_Object[Index]->FileViewItem = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Objects_Folder, 
			App->SBC_Scene->B_Object[Index]->Mesh_Name, Index, true);

	}
	return 1;
}

// *************************************************************************
//				Add_New_Object:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Objects_Create::Add_New_Object(int Index,bool From_MeshViewer)
{
	char Mesh_File[255];
	char ConNum[256];
	char Ogre_Name[256];
	
	Base_Object* Object = App->SBC_Scene->B_Object[Index];


	strcpy_s(Ogre_Name, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(Ogre_Name, ConNum);

	strcpy(Mesh_File ,Object->Mesh_FileName);

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
			Add_Physics_Box(false,Index);
		}

		if (Object->Shape == Enums::Sphere)
		{
			Add_Physics_Sphere(false, Index);
		}

		if (Object->Shape == Enums::Capsule)
		{
			Add_Physics_Capsule(false, Index);
		}

		if (Object->Shape == Enums::Cylinder)
		{
			Add_Physics_Cylinder(false, Index);
		}

		if (Object->Shape == Enums::Cone)
		{
			Add_Physics_Cone(false, Index);
		}
	}

	//---------------------- Dynamic
	if (Object->Type == Enums::Bullet_Type_Dynamic)
	{
		if (Object->Shape == Enums::Shape_Box)
		{
			Add_Physics_Box(true,Index);
		}

		if (Object->Shape == Enums::Sphere)
		{
			Add_Physics_Sphere(true, Index);
		}

		if (Object->Shape == Enums::Capsule)
		{
			Add_Physics_Capsule(true, Index);
		}

		if (Object->Shape == Enums::Cylinder)
		{
			Add_Physics_Cylinder(true,Index);
		}

		if (Object->Shape == Enums::Cone)
		{
			Add_Physics_Cone(true,Index);
		}
	}

	//---------------------- Tri_Mesh
	if (Object->Type == Enums::Bullet_Type_TriMesh)
	{
		create_New_Trimesh(Index);
	}


	if (Object->Usage == Enums::Usage_Room) // Rooms
	{
		App->SBC_Scene->Area_Added = 1;
	}
	
	ShowWindow(App->GD_Properties_Hwnd, 1);

	return 1;
}

// *************************************************************************
//				Add_Physics_Box:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Objects_Create::Add_Physics_Box(bool Dynamic,int Index)
{

	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	if (Dynamic == 1)
	{
		Object->Type = Enums::Bullet_Type_Dynamic;
		Object->Shape = Enums::Shape_Box;

	}
	else
	{
		Object->Type = Enums::Bullet_Type_Static;
		Object->Shape = Enums::Shape_Box;
	}

	AxisAlignedBox worldAAB = Object->Object_Ent->getBoundingBox();
	worldAAB.transformAffine(Object->Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0, 0, 0, 1));

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

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Set_Physics(Index);
}

// *************************************************************************
//			Add_Physics_Sphere:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Objects_Create::Add_Physics_Sphere(bool Dynamic, int Index)
{
	Base_Object* Object = App->SBC_Scene->B_Object[Index];
	
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

	float Radius = App->SBC_Object->GetMesh_BB_Radius(Object->Object_Node);
	Object->Physics_Size = Ogre::Vector3(Radius, 0, 0);

	btCollisionShape* newRigidShape = new btSphereShape(Radius);
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

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Set_Physics(Index);
}

// *************************************************************************
//			Add_Physics_Capsule:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Objects_Create::Add_Physics_Capsule(bool Dynamic, int Index)
{
	Base_Object* Object = App->SBC_Scene->B_Object[Index];

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

	AxisAlignedBox worldAAB = Object->Object_Ent->getBoundingBox();
	worldAAB.transformAffine(Object->Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	//Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();

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

	Ogre::Vector3 Size = App->SBC_Object->GetMesh_BB_Size(Object->Object_Node);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	float Radius = App->SBC_Object->GetMesh_BB_Radius(Object->Object_Node);
	Object->Physics_Size = Ogre::Vector3(Radius, sy, 0);

	btCollisionShape* newRigidShape = new btCapsuleShape(Radius, sy);
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->Phys_Body = new btRigidBody(rbInfo);
	Object->Phys_Body->setRestitution(1.0);
	Object->Phys_Body->setFriction(1.5);
	Object->Phys_Body->setUserPointer(Object->Object_Node);
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

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

	int f = Object->Phys_Body->getCollisionFlags();
	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Set_Physics(Index);
}

// *************************************************************************
//						Add_Physics_Cylinder Terry Flanigan				   *
// *************************************************************************
void SB_Objects_Create::Add_Physics_Cylinder(bool Dynamic, int Index)
{
	Base_Object* Object = App->SBC_Scene->B_Object[Index];

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

	AxisAlignedBox worldAAB = Object->Object_Ent->getBoundingBox();
	worldAAB.transformAffine(Object->Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();
	//Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();

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

	Ogre::Vector3 Size = App->SBC_Object->GetMesh_BB_Size(Object->Object_Node);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	float Radius = App->SBC_Object->GetMesh_BB_Radius(Object->Object_Node);
	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btCylinderShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->Phys_Body = new btRigidBody(rbInfo);
	Object->Phys_Body->setRestitution(1.0);
	Object->Phys_Body->setFriction(1.5);
	Object->Phys_Body->setUserPointer(Object->Object_Node);
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

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

	int f = Object->Phys_Body->getCollisionFlags();
	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Set_Physics(Index);
}

// *************************************************************************
//					Add_PhysicsNew__Static_Cone Terry Bernie			   *
// *************************************************************************
void SB_Objects_Create::Add_Physics_Cone(bool Dynamic,int Index)
{
	Base_Object* Object = App->SBC_Scene->B_Object[Index];

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

	Ogre::Vector3 Centre = App->SBC_Object->Get_BoundingBox_World_Centre(Index);

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

	Ogre::Vector3 Size = App->SBC_Object->GetMesh_BB_Size(Object->Object_Node);
	float sx = Size.x / 2;
	float sy = Size.y;// / 2;
	float sz = Size.z / 2;

	float Radius = App->SBC_Object->GetMesh_BB_Radius(Object->Object_Node);
	Object->Physics_Size = Ogre::Vector3(Radius, sy, 0);

	btCollisionShape* newRigidShape = new btConeShape(Radius, sy);
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->Phys_Body = new btRigidBody(rbInfo);
	Object->Phys_Body->setRestitution(1.0);
	Object->Phys_Body->setFriction(1.5);
	Object->Phys_Body->setUserPointer(Object->Object_Node);
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

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

	int f = Object->Phys_Body->getCollisionFlags();
	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Set_Physics(Index);
}

// *************************************************************************
// *				Add_New_Sound:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Objects_Create::Add_New_Sound()
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
	App->SBC_Scene->B_Object[Index]->This_Object_ID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

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
bool SB_Objects_Create::Create_Sound_Entity(int Index)
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

	Object->Usage = Enums::Usage_Sound;
	Object->Phys_Body->setUserIndex(Enums::Usage_Sound);
	Object->Phys_Body->setUserIndex2(Index);

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	int f = Object->Phys_Body->getCollisionFlags();

	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT
		| btCollisionObject::CF_KINEMATIC_OBJECT
		| btCollisionObject::CF_NO_CONTACT_RESPONSE);


	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Set_Physics(Index);

	return 1;
}

// *************************************************************************
//			Add_New_Teleporter:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Objects_Create::Add_New_Teleporter()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->B_Object[Index] = new Base_Object();

	App->SBC_Scene->B_Object[Index]->S_Teleport[0] = new Teleport_type;
	App->SBC_Object->Set_Teleports_Defaults(Index);

	App->SBC_Scene->B_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->SBC_Scene->B_Object[Index]->Shape = Enums::Shape_Box;
	App->SBC_Scene->B_Object[Index]->This_Object_ID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_FileName, "TeleportSend.mesh");

	strcpy_s(B_Name, "Teleport_Ent_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, B_Name);

	Ogre::Vector3 Pos = App->SBC_Object->GetPlacement(-50);
	App->SBC_Scene->B_Object[Index]->Mesh_Pos = Pos;

	Create_TeleportEntity(Index);

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Teleporters_Folder, App->SBC_Scene->B_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->B_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[Index]->FileViewItem);

	App->SBC_Scene->UniqueID_Object_Counter++;
	App->SBC_Scene->Object_Count++;


	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Teleporters_Folder);
	return 1;
}

// *************************************************************************
//			Create_TeleportEntity:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Objects_Create::Create_TeleportEntity(int Index)
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

	Object->Usage = Enums::Usage_Teleport;
	Object->Phys_Body->setUserIndex(Enums::Usage_Teleport);
	Object->Phys_Body->setUserIndex2(Index);

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	int f = Object->Phys_Body->getCollisionFlags();

	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT
		| btCollisionObject::CF_KINEMATIC_OBJECT
		| btCollisionObject::CF_NO_CONTACT_RESPONSE);


	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Set_Physics(Index);
	return 1;
}

// *************************************************************************
//			Create_New_Trimesh:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
btBvhTriangleMeshShape* SB_Objects_Create::create_New_Trimesh(int Index)
{
	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	// Get the mesh from the entity
	Ogre::MeshPtr myMesh = Object->Object_Ent->getMesh();
	Ogre::Mesh::SubMeshIterator SubMeshIter = myMesh->getSubMeshIterator();

	// Create the triangle mesh
	btTriangleMesh* triMesh = NULL;
	btVector3 vert0, vert1, vert2;
	int i = 0;

	while (SubMeshIter.hasMoreElements())
	{
		i = 0;
		Ogre::SubMesh* subMesh = SubMeshIter.getNext();
		Ogre::IndexData* indexData = subMesh->indexData;
		Ogre::VertexData* vertexData = subMesh->vertexData;

		// -------------------------------------------------------
		// Get the position element
		const Ogre::VertexElement* posElem = vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
		// Get a pointer to the vertex buffer
		Ogre::HardwareVertexBufferSharedPtr vBuffer = vertexData->vertexBufferBinding->getBuffer(posElem->getSource());
		// Get a pointer to the index buffer
		Ogre::HardwareIndexBufferSharedPtr iBuffer = indexData->indexBuffer;

		// -------------------------------------------------------
		// The vertices and indices used to create the triangle mesh
		std::vector<Ogre::Vector3> vertices;
		vertices.reserve(vertexData->vertexCount);
		std::vector<unsigned long> indices;
		indices.reserve(indexData->indexCount);

		// -------------------------------------------------------
		// Lock the Vertex Buffer (READ ONLY)
		unsigned char* vertex = static_cast<unsigned char*> (vBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		float* pReal = NULL;

		for (size_t j = 0; j < vertexData->vertexCount; ++j, vertex += vBuffer->getVertexSize()) {
			posElem->baseVertexPointerToElement(vertex, &pReal);
			Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);

			vertices.push_back(pt);
		}
		vBuffer->unlock();
		// -------------------------------------------------------
		bool use32bitindexes = (iBuffer->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

		// -------------------------------------------------------
		// Lock the Index Buffer (READ ONLY)
		unsigned long* pLong = static_cast<unsigned long*> (iBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		unsigned short* pShort = reinterpret_cast<unsigned short*> (pLong);

		if (use32bitindexes) {
			for (size_t k = 0; k < indexData->indexCount; ++k) {
				//
				indices.push_back(pLong[k]);
			}
		}
		else {
			for (size_t k = 0; k < indexData->indexCount; ++k) {
				//
				indices.push_back(static_cast<unsigned long> (pShort[k]));
			}
		}
		iBuffer->unlock();

		// -------------------------------------------------------
		// We now have vertices and indices ready to go
		// ----

		if (triMesh == nullptr)
		{
			triMesh = new btTriangleMesh(use32bitindexes);
		}

		for (size_t y = 0; y < indexData->indexCount / 3; y++) {
			// Set each vertex
			vert0.setValue(vertices[indices[i]].x, vertices[indices[i]].y, vertices[indices[i]].z);
			vert1.setValue(vertices[indices[i + 1]].x, vertices[indices[i + 1]].y, vertices[indices[i + 1]].z);
			vert2.setValue(vertices[indices[i + 2]].x, vertices[indices[i + 2]].y, vertices[indices[i + 2]].z);

			// Add the triangle into the triangle mesh
			triMesh->addTriangle(vert0, vert1, vert2);

			// Increase index count
			i += 3;
		}

		//App->Say("here");
	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape(triMesh, false, true);
	//mShape->buildOptimizedBvh();

	float x = Object->Object_Node->getPosition().x;
	float y = Object->Object_Node->getPosition().y;
	float z = Object->Object_Node->getPosition().z;

	Object->Physics_Pos = Ogre::Vector3(x, y, z);
	Object->Physics_Rot = Ogre::Vector3(0, 0, 0);
	Object->Physics_Quat = Ogre::Quaternion(1, 0, 0, 0);

	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(0.0, inertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));
	btVector3 initialPosition(x, y, z);
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);


	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI
	(
		0,  // mass
		myMotionState,// initial position
		mShape,      // collision shape of body
		inertia   // local inertia
	);

	Object->Phys_Body = new btRigidBody(rigidBodyCI);
	Object->Phys_Body->clearForces();
	Object->Phys_Body->setLinearVelocity(btVector3(0, 0, 0));
	Object->Phys_Body->setAngularVelocity(btVector3(0, 0, 0));
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));
	int f = Object->Phys_Body->getCollisionFlags();
	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Object->Type = Enums::Bullet_Type_TriMesh;
	Object->Shape = Enums::Shape_TriMesh;


	Object->Phys_Body->setUserIndex(123);
	Object->Phys_Body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Object->Physics_Valid = 1;
	return mShape;
}

// *************************************************************************
//					create_Aera_Trimesh_New Terry Bernie				   *
// *************************************************************************
btBvhTriangleMeshShape* SB_Objects_Create::create_Area_Trimesh_New(int Index, Base_Area* Object)
{

	// Get the mesh from the entity
	Ogre::MeshPtr myMesh = Object->Area_Ent->getMesh();
	Ogre::Mesh::SubMeshIterator SubMeshIter = myMesh->getSubMeshIterator();

	// Create the triangle mesh
	btTriangleMesh* triMesh = NULL;
	btVector3 vert0, vert1, vert2;
	int i = 0;

	while (SubMeshIter.hasMoreElements())
	{
		i = 0;
		Ogre::SubMesh* subMesh = SubMeshIter.getNext();
		Ogre::IndexData* indexData = subMesh->indexData;
		Ogre::VertexData* vertexData = subMesh->vertexData;

		// -------------------------------------------------------
		// Get the position element
		const Ogre::VertexElement* posElem = vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
		// Get a pointer to the vertex buffer
		Ogre::HardwareVertexBufferSharedPtr vBuffer = vertexData->vertexBufferBinding->getBuffer(posElem->getSource());
		// Get a pointer to the index buffer
		Ogre::HardwareIndexBufferSharedPtr iBuffer = indexData->indexBuffer;

		// -------------------------------------------------------
		// The vertices and indices used to create the triangle mesh
		std::vector<Ogre::Vector3> vertices;
		vertices.reserve(vertexData->vertexCount);
		std::vector<unsigned long> indices;
		indices.reserve(indexData->indexCount);

		// -------------------------------------------------------
		// Lock the Vertex Buffer (READ ONLY)
		unsigned char* vertex = static_cast<unsigned char*> (vBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		float* pReal = NULL;

		for (size_t j = 0; j < vertexData->vertexCount; ++j, vertex += vBuffer->getVertexSize()) {
			posElem->baseVertexPointerToElement(vertex, &pReal);
			Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);

			vertices.push_back(pt);
		}
		vBuffer->unlock();
		// -------------------------------------------------------
		bool use32bitindexes = (iBuffer->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

		// -------------------------------------------------------
		// Lock the Index Buffer (READ ONLY)
		unsigned long* pLong = static_cast<unsigned long*> (iBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		unsigned short* pShort = reinterpret_cast<unsigned short*> (pLong);

		if (use32bitindexes) {
			for (size_t k = 0; k < indexData->indexCount; ++k) {
				//
				indices.push_back(pLong[k]);
			}
		}
		else {
			for (size_t k = 0; k < indexData->indexCount; ++k) {
				//
				indices.push_back(static_cast<unsigned long> (pShort[k]));
			}
		}
		iBuffer->unlock();

		// -------------------------------------------------------
		// We now have vertices and indices ready to go
		// ----

		if (triMesh == nullptr)
		{
			triMesh = new btTriangleMesh(use32bitindexes);
		}

		for (size_t y = 0; y < indexData->indexCount / 3; y++) {
			// Set each vertex
			vert0.setValue(vertices[indices[i]].x, vertices[indices[i]].y, vertices[indices[i]].z);
			vert1.setValue(vertices[indices[i + 1]].x, vertices[indices[i + 1]].y, vertices[indices[i + 1]].z);
			vert2.setValue(vertices[indices[i + 2]].x, vertices[indices[i + 2]].y, vertices[indices[i + 2]].z);

			// Add the triangle into the triangle mesh
			triMesh->addTriangle(vert0, vert1, vert2);

			// Increase index count
			i += 3;
		}

	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape(triMesh, false, true);
	//mShape->buildOptimizedBvh();

	float x = Object->Area_Node->getPosition().x;
	float y = Object->Area_Node->getPosition().y;
	float z = Object->Area_Node->getPosition().z;

	Object->Physics_Pos = Ogre::Vector3(x, y, z);
	Object->Physics_Rot = Ogre::Vector3(0, 0, 0);
	Object->Physics_Quat = Ogre::Quaternion(1, 0, 0, 0);

	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(0.0, inertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));
	btVector3 initialPosition(x, y, z);
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	//myMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI
	(
		0,				// mass
		myMotionState,	// initial position
		mShape,			// collision shape of body
		inertia			// local inertia
	);

	Object->Phys_Body = new btRigidBody(rigidBodyCI);
	Object->Phys_Body->clearForces();
	Object->Phys_Body->setLinearVelocity(btVector3(0, 0, 0));
	Object->Phys_Body->setAngularVelocity(btVector3(0, 0, 0));
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));
	int f = Object->Phys_Body->getCollisionFlags();
	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	Object->Type = Enums::Bullet_Type_Static;
	Object->Shape = Enums::Shape_TriMesh;


	Object->Phys_Body->setUserIndex(123);
	Object->Phys_Body->setUserIndex2(Index);

	Object->Collect_Object_Data();

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Object->Physics_Valid = 1;
	return mShape;
}

// *************************************************************************
//							Set_Physics Terry Bernie					   *
// *************************************************************************
void SB_Objects_Create::Set_Physics(int Index)
{
	App->SBC_Scene->B_Object[Index]->Physics_Quat = App->SBC_Scene->B_Object[Index]->Object_Node->getOrientation();

	float w = App->SBC_Scene->B_Object[Index]->Physics_Quat.w;
	float x = App->SBC_Scene->B_Object[Index]->Physics_Quat.x;
	float y = App->SBC_Scene->B_Object[Index]->Physics_Quat.y;
	float z = App->SBC_Scene->B_Object[Index]->Physics_Quat.z;
	App->SBC_Scene->B_Object[Index]->Phys_Body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	App->SBC_Scene->B_Object[Index]->Object_Node->setScale(App->SBC_Scene->B_Object[Index]->Mesh_Scale);
	Ogre::Vector3 Scale = App->SBC_Scene->B_Object[Index]->Object_Node->getScale();
	App->SBC_Scene->B_Object[Index]->Phys_Body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));
	App->SBC_Dimensions->UpDate_Physics_And_Visuals(Index);

	App->SBC_Scene->B_Object[Index]->Physics_Valid = 1;
}