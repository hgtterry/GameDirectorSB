#include "stdafx.h"
#include "GD19_App.h"
#include "Base_Area.h"


Base_Area::Base_Area()
{
	Area_Ent =	nullptr;
	Area_Node = nullptr;

	mObject =	nullptr;
	mShape =	nullptr;

	/*strcpy(Name, "None");
	strcpy(MeshName, "None");
	strcpy(MeshName_FullPath, "None");*/

	// Actor Scale ------------------------------------------------------
	//Mesh_Scale.x = 1;
	//Mesh_Scale.y = 1;
	//Mesh_Scale.z = 1;

	//// Actor Pos
	//Mesh_Pos.x = 0;
	//Mesh_Pos.y = 0;
	//Mesh_Pos.z = 0;

	//// Actor Rotation
	//Mesh_Rot.x = 0;
	//Mesh_Rot.y = 0;
	//Mesh_Rot.z = 0;

	//// Actor Quat
	//Mesh_Quat.w = 1;
	//Mesh_Quat.x = 0;
	//Mesh_Quat.y = 0;
	//Mesh_Quat.z = 0;

	// Physics Scale ------------------------------------------------------
	Physics_Scale.x = 1;
	Physics_Scale.y = 1;
	Physics_Scale.z = 1;

	// Physics Pos
	Physics_Pos.x = 0;
	Physics_Pos.y = 0;
	Physics_Pos.z = 0;

	// Physics Rotation
	Physics_Rot.x = 0;
	Physics_Rot.y = 0;
	Physics_Rot.z = 0;

	// Physics Size
	/*Physics_Size.x = 0;
	Physics_Size.y = 0;
	Physics_Size.z = 0;*/

	// Physics Quat
	Physics_Quat.w = 1;
	Physics_Quat.x = 0;
	Physics_Quat.y = 0;
	Physics_Quat.z = 0;
	Physics_Valid = 0;


	Usage = Enums::Usage_None;

	// Object Folder
	Folder = Enums::Folder_None;

	// Object Shape
	Shape = -1;

	// Flag it is valid
	/*Deleted = 0;

	Show_Debug = 0;
	bt_body = NULL;
	IsInCollision = 0;

	Triggered = 0;

	HasSound = 0;*/

	/*strcpy(Entity[0].mTextItem, "Welcome");
	strcpy(Entity[0].Stock_mName, "None");
	Entity[0].Stock_mIndex = 0;

	Re_Trigger = 1;

	ListViewItem = NULL;*/

	Object_ID = 0; // THis Needs Checking

	/*Sound_ID_v2 = 0;
	Play_v2 = 1;

	Ogre_Particle = nullptr;

	OgreNode = nullptr;
	OgreEntity = nullptr;*/
}


Base_Area::~Base_Area()
{
}


// *************************************************************************
//						Collect_Object_Data Terry Bernie				   *
// *************************************************************************
void Base_Area::Collect_Object_Data(void)
{
	int Index = App->SBC_Scene->Area_Count;

	float x = 0;
	float y = 0;
	float z = 0;

	x = mObject->getWorldTransform().getOrigin().getX();
	y = mObject->getWorldTransform().getOrigin().getY();
	z = mObject->getWorldTransform().getOrigin().getZ();

	Physics_Pos.x = x;
	Physics_Pos.y = y;
	Physics_Pos.z = z;

	x = mObject->getCollisionShape()->getLocalScaling().getX();
	y = mObject->getCollisionShape()->getLocalScaling().getY();
	z = mObject->getCollisionShape()->getLocalScaling().getZ();

	Physics_Scale.x = x;
	Physics_Scale.y = y;
	Physics_Scale.z = z;
}
