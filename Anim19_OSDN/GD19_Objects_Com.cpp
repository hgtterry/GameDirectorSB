#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_Objects_Com.h"

GD19_Objects_Com::GD19_Objects_Com(void)
{
	CopyObject_Index = 0;
}

GD19_Objects_Com::~GD19_Objects_Com(void)
{
}

// *************************************************************************
// *	  				GetMesh_Center Terry Bernie						   *
// *************************************************************************
Ogre::Vector3 GD19_Objects_Com::GetMesh_Center(int Index, SceneNode* mNode)
{
	AxisAlignedBox aab = mNode->getAttachedObject(0)->getBoundingBox();//getBoundingBox(); 
	Ogre::Vector3 min = aab.getMinimum() * mNode->getScale();
	Ogre::Vector3 max = aab.getMaximum() * mNode->getScale();
	Ogre::Vector3 center = aab.getCenter() * mNode->getScale();
	Ogre::Vector3 size(fabs(max.x - min.x), fabs(max.y - min.y), fabs(max.z - min.z));
	float radius = (size.x > size.z) ? size.z / 2.0f : size.x / 2.0f;

	return center;
}

// *************************************************************************
// *	  				GetMesh_BB_Data Terry Bernie					   *
// *************************************************************************
bool GD19_Objects_Com::GetMesh_BB_Data(int SL, Ogre::SceneNode* Node)
{
	Ogre::Vector3 Dimen = GetMesh_BB_Size(Node);

	App->Cl_Scene_Data->Cl_Object[SL]->Mesh_BB_Width = Dimen.x;
	App->Cl_Scene_Data->Cl_Object[SL]->Mesh_BB_Height = Dimen.y;
	App->Cl_Scene_Data->Cl_Object[SL]->Mesh_BB_Depth = Dimen.z;

	App->Cl_Scene_Data->Cl_Object[SL]->Mesh_BB_Quat = Node->getOrientation();

	Ogre::Vector3 Cent = GetMesh_Center(SL, Node);
	App->Cl_Scene_Data->Cl_Object[SL]->Mesh_BB_Center = Cent;
	return 1;
}

// *************************************************************************
// *	  				GetMesh_BB_Size Terry Bernie					   *
// *************************************************************************
Ogre::Vector3 GD19_Objects_Com::GetMesh_BB_Size(SceneNode* mNode)
{
	AxisAlignedBox aab = mNode->getAttachedObject(0)->getBoundingBox();
	Ogre::Vector3 min = aab.getMinimum() * mNode->getScale();
	Ogre::Vector3 max = aab.getMaximum() * mNode->getScale();
	Ogre::Vector3 center = aab.getCenter() * mNode->getScale();
	Ogre::Vector3 size(fabs(max.x - min.x), fabs(max.y - min.y), fabs(max.z - min.z));
	float radius = (size.x > size.z) ? size.z / 2.0f : size.x / 2.0f;

	return size;
}

// *************************************************************************
// *	  				GetMesh_BB_Radius Terry Bernie					   *
// *************************************************************************
float GD19_Objects_Com::GetMesh_BB_Radius(SceneNode* mNode)
{
	AxisAlignedBox aab = mNode->getAttachedObject(0)->getBoundingBox();
	Ogre::Vector3 min = aab.getMinimum() * mNode->getScale();
	Ogre::Vector3 max = aab.getMaximum() * mNode->getScale();
	Ogre::Vector3 center = aab.getCenter() * mNode->getScale();
	Ogre::Vector3 size(fabs(max.x - min.x), fabs(max.y - min.y), fabs(max.z - min.z));
	float radius = (size.x > size.z) ? size.z / 2.0f : size.x / 2.0f;

	return radius;
}

// *************************************************************************
//						Set_Physics_PosRot Terry Bernie					   *
// *************************************************************************
btTransform GD19_Objects_Com::Set_Physics_PosRot(int Object_Index)
{
	int Index = Object_Index;

	btTransform startTransform;
	startTransform.setIdentity();

	//------------ Position
	float x = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Pos.x;
	float y = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Pos.y;
	float z = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Pos.z;
	startTransform.setOrigin(btVector3(x, y, z));

	//------------ Rotation
	float rw = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.w;
	float rx = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.x;
	float ry = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.y;
	float rz = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.z;
	startTransform.setRotation(btQuaternion(rx, ry, rz, rw));

	return startTransform;
}

// *************************************************************************
//						Set_Physics_Scale Terry Bernie					   *
// *************************************************************************
void GD19_Objects_Com::Set_Physics_Scale(int Object_Index)
{
	int Index = Object_Index;

	//------------ Scale
	float sx = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale.x;
	float sy = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale.y;
	float sz = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Scale.z;
	App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionShape()->setLocalScaling(btVector3(sx, sy, sz));
}

// *************************************************************************
//						Set_Physics_Scale Terry Bernie					   *
// *************************************************************************
Ogre::Vector3 GD19_Objects_Com::Centre_of_Trimesh(int Object_Index)
{
	int Index = Object_Index;

	Ogre::Vector3 Position = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getPosition();
	Ogre::Quaternion Rot = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getOrientation();
	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(App->Cl_Scene_Data->Cl_Object[Index]->OgreNode);
	

	Ogre::Vector3 Centre = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getAttachedObject(0)->getBoundingBox().getCenter();
	Ogre::Vector3 WS = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->convertLocalToWorldPosition(Centre);

	Ogre::Vector3 Newpos;
	Newpos.x = WS.x;
	Newpos.y = -WS.y;
	Newpos.z = WS.z;

	return Newpos;
}

// *************************************************************************
// *	  					Copy_Object Terry Bernie					   *
// *************************************************************************
bool GD19_Objects_Com::Copy_Object()
{
	int Curr = App->SBC_Properties->Current_Selected_Object;

	App->Cl_Dialogs->YesNo("Copy Object", App->Cl_Scene_Data->Cl_Object[Curr]->Name);
	if (App->Cl_Dialogs->Canceled == 0)
	{
		CopyObject_Index = App->SBC_Properties->Current_Selected_Object;
	}
	
	return 1;
}

// *************************************************************************
// *	  					Paste_Object Terry Bernie					   *
// *************************************************************************
bool GD19_Objects_Com::Paste_Object()
{
	App->Cl_Dialogs->YesNo("Paste Object", App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Name);
	if (App->Cl_Dialogs->Canceled == 1)
	{
		return 1;
	}

	if (App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Usage == Enums::Usage_Sound)
	{
		Pre_Paste();
		App->Cl_Objects_New->Add_New_SoundEntity();
		Post_Paste();
	}
	else if (App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Usage == Enums::Usage_Message)
	{
		Pre_Paste();
		App->Cl_Objects_New->Add_New_MessageEntity();
		Post_Paste();
	}
	else if (App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Usage == Enums::Usage_Move)
	{
		Pre_Paste();
		App->Cl_Objects_New->Add_New_MoveEntity();
		Post_Paste();
	}
	else if (App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Usage == Enums::Usage_Colectable)
	{
		Pre_Paste();
		App->Cl_Objects_New->Add_New_CollectableEntity();
		Post_Paste();
	}
	else if (App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Usage == Enums::Usage_Teleport)
	{
		Pre_Paste();
		App->Cl_Objects_New->Add_New_TeleportEntity();
		Post_Paste();
	}
	else
	{
		Pre_Paste();
		App->Cl_Objects_New->Add_New_Object(); // Create Object
		Post_Paste();	
	}
	
	return 1;
}

// *************************************************************************
// *	  						Pre_Paste Terry Bernie					   *
// *************************************************************************
bool GD19_Objects_Com::Pre_Paste()
{
	char mName[1024];
	char ConNum[256];
	_itoa(App->Cl_Scene_Data->ObjectCount, ConNum, 10);
	strcpy(mName, App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Name);
	strcat(mName, ConNum);

	strcpy(App->SBC_MeshViewer->Object_Name, mName);
	strcpy(App->SBC_MeshViewer->Selected_MeshFile, App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->MeshName);

	App->SBC_MeshViewer->Physics_Type = App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Type;
	App->SBC_MeshViewer->Physics_Shape = App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Shape;
	return 1;
}

// *************************************************************************
// *	  						Post_Paste Terry Bernie					   *
// *************************************************************************
bool GD19_Objects_Com::Post_Paste()
{
	int Index = App->Cl_Scene_Data->ObjectCount - 1; // Need to go one back as it as been incremented
	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	// Ogre Rotation
	Object->OgreNode->setOrientation(App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Mesh_Quat);
	Object->Mesh_Quat = App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Mesh_Quat;

	// Ogre Scale
	Object->OgreNode->setScale(App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Mesh_Scale);
	Object->Mesh_Scale = App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Mesh_Scale;

	// Ogre Pos
	Ogre::Vector3 Pos = App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Mesh_Pos;

	Pos.x = Pos.x + 5;
	Pos.z = Pos.z + 5;
	Object->OgreNode->setPosition(Pos);
	Object->Mesh_Pos = Pos;



	Object->Physics_Size = App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Physics_Size;
	Object->Physics_Pos = App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Physics_Pos;
	Object->Physics_Quat = App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Physics_Quat;
	Object->Physics_Rot = App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Physics_Rot;

	//Physics Scale
	Object->Physics_Scale = App->Cl_Scene_Data->Cl_Object[CopyObject_Index]->Physics_Scale;
	Ogre::Vector3 Scale = Object->Physics_Scale;
	Object->bt_body->getCollisionShape()->setLocalScaling(btVector3(Scale.x, Scale.y, Scale.z));

	// Physics Pos
	Ogre::Vector3 Pos2 = App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos;
	Pos2.x += 15;
	App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Pos = Pos2;
	App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setPosition(Pos2);

	// Physics Rotation
	float w = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.w;
	float x = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.x;
	float y = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.y;
	float z = App->Cl_Scene_Data->Cl_Object[Index]->Physics_Quat.z;
	App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getWorldTransform().setRotation(btQuaternion(x, y, z, w));

	App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);
	App->Cl_Dimensions->UpDate_Physics_And_Visuals(Index);

	App->Cl_Visuals->MarkerBB_Addjust(Index);
	return 1;
}
