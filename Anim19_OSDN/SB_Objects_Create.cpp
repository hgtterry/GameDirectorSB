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
//					Add_Objects_FromFile Terry Bernie					   *
// *************************************************************************
bool SB_Objects_Create::Add_Objects_From_File() // From File
{
	/*char ConNum[256];
	char ATest[256];
	char Name[255];
	char Mesh_File[255];*/

	int Object_Count = App->SBC_Scene->Object_Count;
	int Count = 0;

	while (Count < Object_Count)
	{
		//if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Sound)
		//{
		//	//Add_SoundEntity_FFile(Count);
		//}
		//else if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Message)
		//{
		//	//Add_MessageEntity_FFile(Count);
		//}
		//else if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Move)
		//{
		//	//Add_MoveEntity_FFile(Count);
		//}
		//else if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Colectable)
		//{
		//	//Add_CollectableEntity_FFile(Count);
		//}
		//else if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Teleport)
		//{
		//	//Add_TeleportEntity_FFile(Count);
		//}
		//else
		//{

		App->SBC_Objects_Create->Add_New_Object(Count);
		//}

		Count++;
	}

	if (Object_Count > 0)
	{
		App->SBC_FileView->Set_FolderActive(App->SBC_FileView->GD_ObjectsFolder);
		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 1);
		App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[0]->ListViewItem);
	}

	//App->Cl_FileView->Select_Item(NULL);
	

	return 1;
}
// *************************************************************************
//							Dispatcher_New Terry Flanigan				   *
// *************************************************************************
bool SB_Objects_Create::Dispatcher_New()
{
	int Index = App->SBC_Scene->Object_Count;

	if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area) // Area
	{
		//Add_New_Area();
	}
	else if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Collectables) // Collectables
	{
		//Add_New_CollectableEntity();
	}
	else
	{
		Add_New_Object(Index);
	}
	return 1;
}

// *************************************************************************
//							Update_MV_Details Terry Flanigan			   *
// *************************************************************************
void SB_Objects_Create::Update_MV_Details()
{
	int Index = App->SBC_Scene->Object_Count;

	strcpy(m_ResourcePath, App->SBC_MeshViewer->mResource_Folder);
	App->SBC_Scene->Add_Resource_Location(m_ResourcePath);

	App->SBC_Scene->B_Object[Index] = new Base_Object();
	
	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	Object->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	strcpy(Object->Mesh_Name, App->SBC_MeshViewer->Object_Name);
	strcpy(Object->Mesh_FileName, App->SBC_MeshViewer->Selected_MeshFile);
	strcpy(Object->Mesh_Resource_Path, m_ResourcePath);

	Object->Type = App->SBC_MeshViewer->Physics_Type;
	Object->Shape = App->SBC_MeshViewer->Physics_Shape;

	App->SBC_Objects_Create->Dispatcher_New();
	
	App->Cl_Scene_Data->Object_ID_Counter++;
	App->SBC_Scene->Object_Count++;  // Must be last line

	// ---- Copy Asset
	strcpy(SourceFile, App->SBC_MeshViewer->mResource_Folder);
	strcat(SourceFile, App->SBC_MeshViewer->Selected_MeshFile);

	strcpy(DestinationFile, App->SBC_Project->m_Objects_Assets_Path);
	strcat(DestinationFile, App->SBC_MeshViewer->Selected_MeshFile);

	CopyFile(SourceFile, DestinationFile, false);
}

// *************************************************************************
//								Add_New_Object Terry					   *
// *************************************************************************
bool SB_Objects_Create::Add_New_Object(int Index)
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
	Object->Object_Node->setPosition(Object->Mesh_Pos);

	App->Cl_Scene_Data->SceneLoaded = 1;

	
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

	////---------------------- Dynamic
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
	if (App->SBC_MeshViewer->Physics_Type == Enums::Bullet_Type_TriMesh)
	{
		//		Object->create_New_Trimesh(Object->OgreEntity);
	}

	if (Object->Usage == Enums::Usage_Room) // Rooms
	{
		//		HTREEITEM Temp = App->Cl_FileView->Add_Room_Object(Object->Name, Index);
		//		Object->ListViewItem = Temp;
		App->Cl_Scene_Data->Scene_Has_Area = 1;
	}
	else
	{
		Object->Folder = Enums::Folder_Objects;
		HTREEITEM Temp = App->SBC_FileView->Add_ObjectFile(Object->Mesh_Name, Index);
		Object->ListViewItem = Temp;
	}


	ShowWindow(App->GD_Properties_Hwnd, 1);

	return 1;
}

// *************************************************************************
//							Add_Physics_Box Terry Bernie				   *
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

	Set_Physics(Index);
}

// *************************************************************************
//						Add_Physics_Sphere Terry Flaniagn				   *
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

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(Object->Object_Node);
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
//						Add_Physics_Capsule Terry Bernie				   *
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

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->Object_Node);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(Object->Object_Node);
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

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->Object_Node);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(Object->Object_Node);
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

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->Object_Node);
	float sx = Size.x / 2;
	float sy = Size.y;// / 2;
	float sz = Size.z / 2;

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(Object->Object_Node);
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
//						Add_MessageEntity Terry Bernie					   *
// *************************************************************************
bool SB_Objects_Create::Add_Message_Entity(int Object_Index)
{
	int Index = App->SBC_Scene->Entity_Count;

	App->SBC_Scene->B_Entity[Index] = new Base_Entity();
	//App->SBC_Scene->B_Entity[Index]->Object_ID = App->SBC_Scene->Object_ID_Counter;
	
	// Only on newly created objects
	//App->Cl_Scene_Data->Object_ID_Counter++;

	Base_Entity* Object = App->SBC_Scene->B_Entity[Index];
	
	//strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, "Test Text");

	Object->Type = Enums::Bullet_Type_Static;
	Object->Shape = Enums::Shape_Box;

	//strcpy(App->Cl_Scene_Data->Cl_Object[Index]->MeshName, "Test_cube.mesh");

	char ConNum[256];
	char ATest[256];
	char Name[256];

	strcpy_s(Name, "Message_");
	_itoa(Index, ConNum, 10);
	strcat(Name, ConNum);

	strcpy_s(ATest, "GDEntity_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(Object->Mesh_Name, Name);
	strcpy(Object->Mesh_FileName, "Test_cube.mesh");
	//strcpy(Object->MeshName_FullPath, "Test_cube.mesh");

	Object->Object_Ent = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, "Test_cube.mesh", App->Cl19_Ogre->App_Resource_Group);
	Object->Object_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->Object_Node->attachObject(Object->Object_Ent);
	Object->Object_Node->scale(1, 1, 1);

	//Ogre::Vector3 Pos = Object->GetPlacement();
	//Object->Mesh_Pos = Pos;
	Object->Object_Node->setPosition(0,0,0);
	//------------------

	return 1;

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(Object->Object_Node);
	float sx = Size.x / 2;
	float sy = Size.y / 2; // Size by Bounding Box
	float sz = Size.z / 2;

	Object->Physics_Size = Ogre::Vector3(sx, sy, sz);

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(0, btVector3(0, 0, 0));

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	Ogre::Vector3 Centre = App->SBC_Object->Get_BoundingBox_World_Centre(Index);

	Object->Physics_Pos = Ogre::Vector3(Centre.x, Centre.y, Centre.z);

	btVector3 initialPosition(btVector3(Centre.x, Centre.y, Centre.z));
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(0, myMotionState, newRigidShape, btVector3(0, 0, 0));

	Object->Phys_Body = new btRigidBody(rbInfo);
	Object->Phys_Body->setRestitution(1.0);
	Object->Phys_Body->setFriction(1.5);
	Object->Phys_Body->setUserPointer(Object->Object_Node);
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Phys_Body->setCollisionFlags(btCollisionObject::CF_KINEMATIC_OBJECT | btCollisionObject::CF_NO_CONTACT_RESPONSE);

	Object->Usage = Enums::Usage_Message;
	Object->Phys_Body->setUserIndex(Enums::Usage_Message);
	Object->Phys_Body->setUserIndex2(Index);

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	Object->Folder = Enums::Folder_Message_Entity;
	Object->Physics_Valid = 1;

	//HTREEITEM Temp = App->Cl_FileView->Add_Message_Entity(Object->Name, Index);
	//Object->ListViewItem = Temp;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line
	return 1;
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