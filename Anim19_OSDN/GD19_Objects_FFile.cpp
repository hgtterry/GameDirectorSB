#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_Objects_FFile.h"

GD19_Objects_FFile::GD19_Objects_FFile(void)
{
	
}

GD19_Objects_FFile::~GD19_Objects_FFile(void)
{
}

// *************************************************************************
//					Add_Objects_FromFile Terry Bernie					   *
// *************************************************************************
bool GD19_Objects_FFile::Add_Objects_FromFile() // From File
{
	/*char ConNum[256];
	char ATest[256];
	char Name[255];
	char Mesh_File[255];*/

	int Object_Count = App->Cl_Scene_Data->ObjectCount;
	int Count = 0;

	while (Count < Object_Count)
	{
		if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Sound)
		{
			Add_SoundEntity_FFile(Count);
		}
		else if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Message)
		{
			Add_MessageEntity_FFile(Count);
		}
		else if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Move)
		{
			Add_MoveEntity_FFile(Count);
		}
		else if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Colectable)
		{
			Add_CollectableEntity_FFile(Count);
		}
		else if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Teleport)
		{
			Add_TeleportEntity_FFile(Count);
		}
		else
		{
			Add_Object_FFile(Count);
		}

		Count++;
	}

	/*App->Cl_FileView->Select_Item(NULL);
	ShowWindow(App->GD_Properties_Hwnd,1);
	App->Cl_Ogre->OgreListener->GD_Dubug_Physics = 1;*/
	return 1;
}

bool GD19_Objects_FFile::Add_Object_FFile(int Object_Index)
{
	char ConNum[256];
	char ATest[256];
	char Mesh_File[255];
	int Count = Object_Index;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Count];

	strcpy(ATest, "GDEnt_");
	_itoa(Count, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Mesh_File, Object->MeshName);

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, Mesh_File, App->Cl19_Ogre->Equity_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);

	Object->OgreNode->setVisible(true);
	Object->OgreNode->setScale(Object->Mesh_Scale);

	Ogre::Vector3 Pos = Object->Mesh_Pos;
	Ogre::Quaternion Rot = Object->Mesh_Quat;

	Object->OgreNode->setOrientation(Rot);
	Object->OgreNode->setPosition(Pos);

	//---------------------- Static and Dynamic
	if (Object->Type == Enums::Bullet_Type_Static || Object->Type == Enums::Bullet_Type_Dynamic)
	{
		if (Object->Shape == Enums::Shape_Box)
		{
			Add_Physics_Static_Box_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Sphere)
		{
			Add_Physics_Static_Sphere_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Capsule)
		{
			Add_Physics_Static_Capsule_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Cylinder)
		{
			Add_Physics_Static_Cylinder_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Cone)
		{
			Add_Physics_Static_Cone_FFile(false, Count);
			Object->Physics_Valid = 1;
		}
	}

	//---------------------- Tri_Mesh
	if (Object->Shape == Enums::Shape_TriMesh)
	{
		Object->createTrimesh(Object->OgreEntity, Count);
		Object->Physics_Valid = 1;
	}

	if (Object->Usage == Enums::Usage_Room) // Rooms
	{
		HTREEITEM Temp = App->Cl_FileView->Add_Room_Object(Object->Name, Count);
		Object->ListViewItem = Temp;


		App->Cl_Scene_Data->Scene_Has_Area = 1;
	}
	else
	{
		HTREEITEM Temp = App->Cl_FileView->Add_MiscFile(Object->Name, Count);
		Object->ListViewItem = Temp;

	
	}

	App->SBC_FileView->Select_Item(NULL);
	ShowWindow(App->GD_Properties_Hwnd, 1);
	App->Cl19_Ogre->OgreListener->Dubug_Physics_Draw = 1;

	return 1;
}

// *************************************************************************
//						Add_SoundEntity Terry Bernie					   *
// *************************************************************************
bool GD19_Objects_FFile::Add_SoundEntity_FFile(int Object_Index)
{
	char ConNum[256];
	char ATest[256];

	int Index = Object_Index;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	Object->Type = Enums::Bullet_Type_Static;
	Object->Shape = Enums::Shape_Box;

	strcpy_s(ATest, "GDEnt_");
	_itoa(Object_Index, ConNum, 10);
	strcat(ATest, ConNum);

	//------------------ Add Ogre Mesh
	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "SoundEntity_GD.mesh", App->Cl19_Ogre->Equity_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(Object->Mesh_Scale);

	Ogre::Vector3 Pos = Object->Mesh_Pos;
	Object->OgreNode->setPosition(Pos);

	Ogre::Quaternion Rot = Object->Mesh_Quat;
	Object->OgreNode->setOrientation(Rot);
	//----------------------------------------------------------------------------------

	Ogre::Vector3 Size = Object->Physics_Size;

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(Size.x, Size.y, Size.z));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform mStartTransform = App->Cl_Objects_Com->Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btDefaultMotionState* myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(mStartTransform);

	Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_Sound;
	Object->bt_body->setUserIndex(Enums::Usage_Sound);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Objects_Com->Set_Physics_Scale(Index); // Set Physics Scale

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Folder = Enums::Folder_Sound_Entity;
	Object->Physics_Valid = 1;

	HTREEITEM Temp = App->Cl_FileView->Add_Sound_Entity(Object->Name, Index);
	Object->ListViewItem = Temp;

	//App->Cl_FileView_V2->Add_SoundName(Object->Name);

	//App->Cl_FileView->Select_Item(NULL,NULL);
	ShowWindow(App->GD_Properties_Hwnd, 1);

	return 1;
}

// *************************************************************************
//						Add_MessageEntity Terry Bernie					   *
// *************************************************************************
bool GD19_Objects_FFile::Add_MessageEntity_FFile(int Object_Index)
{
	char ConNum[256];
	char ATest[256];
	int Index = Object_Index;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	Object->Type = Enums::Bullet_Type_Static;
	Object->Shape = Enums::Shape_Box;

	strcpy_s(ATest, "GDEnt_");
	_itoa(Object_Index, ConNum, 10);
	strcat(ATest, ConNum);

	//------------------ Add Ogre Mesh
	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "Test_cube.mesh", App->Cl19_Ogre->Equity_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(Object->Mesh_Scale);

	Ogre::Vector3 Pos = Object->Mesh_Pos;
	Object->OgreNode->setPosition(Pos);

	Ogre::Quaternion Rot = Object->Mesh_Quat;
	Object->OgreNode->setOrientation(Rot);
	//----------------------------------------------------------------------------------

	Ogre::Vector3 Size = Object->Physics_Size;

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(Size.x, Size.y, Size.z));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform mStartTransform = App->Cl_Objects_Com->Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform


	btDefaultMotionState* myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(mStartTransform);

	Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_Message;
	Object->bt_body->setUserIndex(Enums::Usage_Message);
	Object->bt_body->setUserIndex2(Index);

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Objects_Com->Set_Physics_Scale(Index); // Set Physics Scale

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Folder = Enums::Folder_Message_Entity;
	Object->Physics_Valid = 1;

	HTREEITEM Temp = App->Cl_FileView->Add_Message_Entity(Object->Name, Index);
	Object->ListViewItem = Temp;

//	App->Cl_FileView_V2->Add_MessageName(Object->Name);

	//App->Cl_FileView->Select_Item(NULL,NULL);
	ShowWindow(App->GD_Properties_Hwnd, 1);

	return 1;
}

// *************************************************************************
//						Add_MoveEntity Terry Bernie						   *
// *************************************************************************
bool GD19_Objects_FFile::Add_MoveEntity_FFile(int Object_Index)
{
	int Index = Object_Index;
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	// Correct Index if Different
	int New_Index = App->Cl_LookUps->GetIndex_From_ID(Object->S_MoveType->Object_ID);

	if (New_Index > -1)
	{
		Object->S_MoveType->Object_Index = New_Index;
	}
	else
	{
		App->Say("Load Error:- Cant Assign Index for Object to Move");
	}

	// --------------------------------------------------------
	char ConNum[256];
	char ATest[256];


	Object->Type = Enums::Bullet_Type_Static;
	Object->Shape = Enums::Shape_Box;

	strcpy_s(ATest, "GDEnt_");
	_itoa(Object_Index, ConNum, 10);
	strcat(ATest, ConNum);

	//------------------ Add Ogre Mesh
	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "DoorEntity_GD.mesh", App->Cl19_Ogre->Equity_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);
	Object->OgreNode->scale(Object->Mesh_Scale);

	Ogre::Vector3 Pos = Object->Mesh_Pos;
	Object->OgreNode->setPosition(Pos);

	Ogre::Quaternion Rot = Object->Mesh_Quat;
	Object->OgreNode->setOrientation(Rot);
	//----------------------------------------------------------------------------------

	Ogre::Vector3 Size = Object->Physics_Size;

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(Size.x, Size.y, Size.z));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform mStartTransform = App->Cl_Objects_Com->Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform


	btDefaultMotionState* myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(mStartTransform);

	Object->bt_body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_Move;
	Object->bt_body->setUserIndex(Enums::Usage_Move);
	Object->bt_body->setUserIndex2(Index);

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Objects_Com->Set_Physics_Scale(Index); // Set Physics Scale

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);

	Object->Folder = Enums::Folder_Move_Entity;
	Object->Physics_Valid = 1;

	HTREEITEM Temp = App->Cl_FileView->Add_Move_Entity(Object->Name, Index);
	Object->ListViewItem = Temp;

//	App->Cl_FileView_V2->Add_MoveEntities(Object->Name);

	//App->Cl_FileView->Select_Item(NULL,NULL);
	ShowWindow(App->GD_Properties_Hwnd, 1);

	return 1;
}

// *************************************************************************
//				Add_CollectableEntity_FFile Terry Bernie				   *
// *************************************************************************
bool GD19_Objects_FFile::Add_CollectableEntity_FFile(int Object_Index)
{
	char ConNum[256];
	char ATest[256];
	int Count = Object_Index;
	char Mesh_File[255];

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Count];

	strcpy_s(ATest, "GDEnt_");
	_itoa(Count, ConNum, 10);
	strcat(ATest, ConNum);


	strcpy(Mesh_File, Object->MeshName);

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, Mesh_File, App->Cl19_Ogre->Equity_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);

	Object->OgreNode->setVisible(true);
	Object->OgreNode->setScale(Object->Mesh_Scale);

	Ogre::Vector3 Pos = Object->Mesh_Pos;
	Ogre::Quaternion Rot = Object->Mesh_Quat;

	Object->OgreNode->setOrientation(Rot);
	Object->OgreNode->setPosition(Pos);

	//---------------------- Static and Dynamic
	if (Object->Type == Enums::Bullet_Type_Static || Object->Type == Enums::Bullet_Type_Dynamic)
	{
		if (Object->Shape == Enums::Shape_Box)
		{
			Add_Physics_Static_Box_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Sphere)
		{
			Add_Physics_Static_Sphere_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Capsule)
		{
			Add_Physics_Static_Capsule_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Cylinder)
		{
			Add_Physics_Static_Cylinder_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Cone)
		{
			Add_Physics_Static_Cone_FFile(false, Count);
			Object->Physics_Valid = 1;
		}
	}


	HTREEITEM Temp = App->Cl_FileView->Add_Collectable(Object->Name, Count);
	Object->ListViewItem = Temp;

//	App->Cl_FileView_V2->Add_Collectable_Name(Object->Name);
	return 1;
}

// *************************************************************************
//						Add_TeleportEntity_FFile Terry Bernie			   *
// *************************************************************************
bool GD19_Objects_FFile::Add_TeleportEntity_FFile(int Object_Index)
{
	char ConNum[256];
	char ATest[256];

	int Count = Object_Index;
	char Mesh_File[255];

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Count];

	strcpy_s(ATest, "GDEnt_");
	_itoa(Count, ConNum, 10);
	strcat(ATest, ConNum);


	strcpy(Mesh_File, Object->MeshName);

	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, Mesh_File, App->Cl19_Ogre->Equity_Resource_Group);
	Object->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->OgreNode->attachObject(Object->OgreEntity);

	Object->OgreNode->setVisible(true);
	Object->OgreNode->setScale(Object->Mesh_Scale);

	Ogre::Vector3 Pos = Object->Mesh_Pos;
	Ogre::Quaternion Rot = Object->Mesh_Quat;

	Object->OgreNode->setOrientation(Rot);
	Object->OgreNode->setPosition(Pos);

	//---------------------- Static and Dynamic
	if (Object->Type == Enums::Bullet_Type_Static || Object->Type == Enums::Bullet_Type_Dynamic)
	{
		if (Object->Shape == Enums::Shape_Box)
		{
			Add_Physics_Static_Box_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Sphere)
		{
			Add_Physics_Static_Sphere_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Capsule)
		{
			Add_Physics_Static_Capsule_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Cylinder)
		{
			Add_Physics_Static_Cylinder_FFile(false, Count);
			Object->Physics_Valid = 1;
		}

		if (Object->Shape == Enums::Cone)
		{
			Add_Physics_Static_Cone_FFile(false, Count);
			Object->Physics_Valid = 1;
		}
	}


	HTREEITEM Temp = App->Cl_FileView->Add_Teleport(Object->Name, Count);
	Object->ListViewItem = Temp;

	

	return 1;
}

// *************************************************************************
//					Add_Physics_Static_Box_FFile Terry Bernie			   *
// *************************************************************************
void GD19_Objects_FFile::Add_Physics_Static_Box_FFile(bool Dynamic, int Object_Index)
{
	int Index = Object_Index;
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	btTransform mStartTransform = App->Cl_Objects_Com->Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btScalar mass;
	mass = Object->Physics_Mass;

	btVector3 localInertia(0, 0, 0);

	Ogre::Vector3 Size = Object->Physics_Size; // --------- Size

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(Size.x, Size.y, Size.z));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(mStartTransform);

	Object->bt_body->setCustomDebugColor(btVector3(0, 1, 1));

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Objects_Com->Set_Physics_Scale(Index); // Set Physics Scale

	Object->bt_body->setUserIndex(Object->Usage);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);
}

// *************************************************************************
//						Add_Physics_Static_Sphere Terry Bernie			   *
// *************************************************************************
void GD19_Objects_FFile::Add_Physics_Static_Sphere_FFile(bool Dynamic, int Object_Index)
{
	int Index = Object_Index;
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	btTransform mStartTransform = App->Cl_Objects_Com->Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btScalar mass;
	mass = Object->Physics_Mass;

	btVector3 localInertia(0, 0, 0);

	Ogre::Vector3 Size = Object->Physics_Size; // --------- Size

	btCollisionShape* newRigidShape = new btSphereShape(Size.x); // Radius
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(mStartTransform);

	Object->bt_body->setCustomDebugColor(btVector3(0, 1, 1));

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Objects_Com->Set_Physics_Scale(Index); // Set Physics Scale

	Object->bt_body->setUserIndex(Object->Usage);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);
}

// *************************************************************************
//					Add_Physics_Static_Capsule_FFile Terry Bernie		   *
// *************************************************************************
void GD19_Objects_FFile::Add_Physics_Static_Capsule_FFile(bool Dynamic, int Object_Index)
{
	int Index = Object_Index;
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	btTransform mStartTransform = App->Cl_Objects_Com->Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btScalar mass;
	mass = Object->Physics_Mass;

	btVector3 localInertia(0, 0, 0);

	Ogre::Vector3 Size = Object->Physics_Size; // --------- Size

	btCollisionShape* newRigidShape = new btCapsuleShape(Size.x, Size.y); // Radius,Height
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(mStartTransform);

	Object->bt_body->setCustomDebugColor(btVector3(0, 1, 1));

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Objects_Com->Set_Physics_Scale(Index); // Set Physics Scale

	Object->bt_body->setUserIndex(Object->Usage);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);
}

// *************************************************************************
//						Add_Physics_Capsule_Cylinder Terry Bernie		   *
// *************************************************************************
void GD19_Objects_FFile::Add_Physics_Static_Cylinder_FFile(bool Dynamic, int Object_Index)
{
	int Index = Object_Index;
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	btTransform mStartTransform = App->Cl_Objects_Com->Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btScalar mass;
	mass = Object->Physics_Mass;

	btVector3 localInertia(0, 0, 0);

	Ogre::Vector3 Size = Object->Physics_Size; // --------- Size

	btCollisionShape* newRigidShape = new btCylinderShape(btVector3(Size.x, Size.y, Size.z));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(mStartTransform);

	Object->bt_body->setCustomDebugColor(btVector3(0, 1, 1));

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Objects_Com->Set_Physics_Scale(Index); // Set Physics Scale

	Object->bt_body->setUserIndex(Object->Usage);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);
}

// *************************************************************************
//					Add_Physics_Static_Cone_FFile Terry Bernie			   *
// *************************************************************************
void GD19_Objects_FFile::Add_Physics_Static_Cone_FFile(bool Dynamic, int Object_Index)
{
	int Index = Object_Index;
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	btTransform mStartTransform = App->Cl_Objects_Com->Set_Physics_PosRot(Index); // Get Physics Position And Rotation Transform

	btScalar mass;
	mass = Object->Physics_Mass;

	btVector3 localInertia(0, 0, 0);

	Ogre::Vector3 Size = Object->Physics_Size; // --------- Size

	btCollisionShape* newRigidShape = new btConeShape(Size.x, Size.y); // Radius,Height
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(mStartTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->bt_body = new btRigidBody(rbInfo);
	Object->bt_body->setRestitution(1.0);
	Object->bt_body->setFriction(1.5);
	Object->bt_body->setUserPointer(Object->OgreNode);
	Object->bt_body->setWorldTransform(mStartTransform);

	Object->bt_body->setCustomDebugColor(btVector3(0, 1, 1));

	int f = Object->bt_body->getCollisionFlags();
	Object->bt_body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->Cl_Objects_Com->Set_Physics_Scale(Index); // Set Physics Scale

	Object->bt_body->setUserIndex(Object->Usage);
	Object->bt_body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->bt_body);
}
