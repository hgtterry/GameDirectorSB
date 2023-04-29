#include "stdafx.h"
#include "WV_App.h"
#include "Base_Area.h"


Base_Area::Base_Area()
{
	Area_Ent =		nullptr;
	Area_Node =		nullptr;

	Phys_Body =		nullptr;
	Phys_Shape =	nullptr;

	// Actor Scale ------------------------------------------------------
	Mesh_Scale.x = 1;
	Mesh_Scale.y = 1;
	Mesh_Scale.z = 1;

	// Actor Pos
	Mesh_Pos.x = 0;
	Mesh_Pos.y = 0;
	Mesh_Pos.z = 0;

	// Mesh Rotation
	Mesh_Rot.x = 0;
	Mesh_Rot.y = 0;
	Mesh_Rot.z = 0;

	// Mesh Quat
	Mesh_Quat.w = 1;
	Mesh_Quat.x = 0;
	Mesh_Quat.y = 0;
	Mesh_Quat.z = 0;

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

	// Physics Quat
	Physics_Quat.w = 1;
	Physics_Quat.x = 0;
	Physics_Quat.y = 0;
	Physics_Quat.z = 0;
	Physics_Valid = 0;


	Usage = 123;// Enums::Usage_None;

	// Object Folder
	Folder = 0;// Enums::Folder_None;

	// Object Shape
	Shape = -1;

	This_Object_UniqueID = 0;

	strcpy(Area_Name, "Room_1");
	strcpy(Material_File,"Not_Loaded");
	
	Area_FileName[0] = 0;
	Area_Path_And_FileName[0] = 0;
	Area_Resource_Path[0] = 0;

	Altered = 1;
	Physics_Debug_On = 0;
}


Base_Area::~Base_Area()
{
}


//// *************************************************************************
////						Collect_Object_Data Terry Bernie				   *
//// *************************************************************************
//void Base_Area::Collect_Object_Data(void)
//{
//	int Index = App->SBC_Scene->Area_Count;
//
//	float x = 0;
//	float y = 0;
//	float z = 0;
//
//	x = Phys_Body->getWorldTransform().getOrigin().getX();
//	y = Phys_Body->getWorldTransform().getOrigin().getY();
//	z = Phys_Body->getWorldTransform().getOrigin().getZ();
//
//	Physics_Pos.x = x;
//	Physics_Pos.y = y;
//	Physics_Pos.z = z;
//
//	x = Phys_Body->getCollisionShape()->getLocalScaling().getX();
//	y = Phys_Body->getCollisionShape()->getLocalScaling().getY();
//	z = Phys_Body->getCollisionShape()->getLocalScaling().getZ();
//
//	Physics_Scale.x = x;
//	Physics_Scale.y = y;
//	Physics_Scale.z = z;
//}
