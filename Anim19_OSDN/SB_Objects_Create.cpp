#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Objects_Create.h"

SB_Objects_Create::SB_Objects_Create(void)
{
}

SB_Objects_Create::~SB_Objects_Create(void)
{
}

// *************************************************************************
//							Dispatcher_New Terry Flanigan				   *
// *************************************************************************
bool SB_Objects_Create::Dispatcher_New()
{

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
		Add_New_Object();
	}
	return 1;
}

// *************************************************************************
//								Add_New_Object Terry					   *
// *************************************************************************
bool SB_Objects_Create::Add_New_Object()
{
	int Index = App->SBC_Scene->Object_Count;

	/*if (App->GDSBC_MeshViewer->Physics_Type == Enums::Bullet_Type_Volume)
	{
		Add_Physics_Volume_Box();
		return 1;
	}*/

	App->SBC_Scene->B_Object[Index] = new Base_Object();
	App->SBC_Scene->B_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	strcpy(Object->Mesh_Name, App->SBC_MeshViewer->Object_Name);
	strcpy(Object->Mesh_FileName, App->SBC_MeshViewer->Selected_MeshFile);
	strcpy(Object->Mesh_Resource_Path, App->SBC_MeshViewer->Folder_Vec[0].Folder_Path);

	char PathFile[256];
	char ConNum[256];
	char ATest[256];

	App->SBC_Scene->Add_Resource_Location(App->SBC_MeshViewer->Folder_Vec[0].Folder_Path);

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(PathFile, Object->Mesh_FileName);
	Object->Object_Ent = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, PathFile, App->SBC_Scene->Project_Resource_Group);
	Object->Object_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object->Object_Node->attachObject(Object->Object_Ent);

	Object->Object_Node->setVisible(true);
	Object->Object_Node->setScale(Object->Mesh_Scale);

	Ogre::Vector3 Pos = Ogre::Vector3(1, 1, 1);// Object->GetPlacement();
	Object->Mesh_Pos = Pos;
	Object->Object_Node->setPosition(Pos);

	strcpy(Object->Mesh_Resource_Path, App->SBC_MeshViewer->Folder_Vec[0].Folder_Path); // Resource Path

	App->Cl_Scene_Data->SceneLoaded = 1;


	//---------------------- Static
	if (App->SBC_MeshViewer->Physics_Type == Enums::Bullet_Type_Static)
	{
		if (App->SBC_MeshViewer->Physics_Shape == Enums::Shape_Box)
		{
			Object->Type = Enums::Bullet_Type_Static;
			Object->Shape = Enums::Shape_Box;

			Add_New_Physics_Static_Box(false);
			Object->Physics_Valid = 1;
		}

		/*if (App->SBC_MeshViewer->Physics_Shape == Enums::Sphere)
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
		}*/
	}

	////---------------------- Dynamic
	if (App->SBC_MeshViewer->Physics_Type == Enums::Bullet_Type_Dynamic)
	{
		if (App->SBC_MeshViewer->Physics_Shape == Enums::Shape_Box)
		{
			Object->Type = Enums::Bullet_Type_Dynamic;
			Object->Shape = Enums::Shape_Box;

			Add_New_Physics_Static_Box(true);
			Object->Physics_Valid = 1;
		}

		/*if (App->SBC_MeshViewer->Physics_Shape == Enums::Sphere)
		{
			Add_New_Physics_Static_Sphere(true);
			Object->Physics_Valid = 1;
		}

		if (App->SBC_MeshViewer->Physics_Shape == Enums::Capsule)
		{
			Add_New_Physics_Static_Capsule(true);
			Object->Physics_Valid = 1;
		}

		if (App->SBC_MeshViewer->Physics_Shape == Enums::Cylinder)
		{
			Add_New_Physics_Static_Cylinder(true);
			Object->Physics_Valid = 1;
		}

		if (App->SBC_MeshViewer->Physics_Shape == Enums::Cone)
		{
			Add_New_Physics_Static_Cone(true);
			Object->Physics_Valid = 1;
		}*/
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
		HTREEITEM Temp = App->SBC_FileView->Add_ObjectFile(App->SBC_MeshViewer->Object_Name, Index);
		Object->ListViewItem = Temp;
	}


	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->SBC_Scene->Object_Count++;  // Must be last line

	return 1;
}

// *************************************************************************
//						Add_New_Physics_Static_Box Terry Bernie			   *
// *************************************************************************
void SB_Objects_Create::Add_New_Physics_Static_Box(bool Dynamic)
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

