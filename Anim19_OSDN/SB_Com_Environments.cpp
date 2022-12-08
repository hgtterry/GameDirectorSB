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
#include "SB_Com_Environments.h"

SB_Com_Environments::SB_Com_Environments()
{
}

SB_Com_Environments::~SB_Com_Environments()
{
}

// *************************************************************************
// *			Rename_Environ:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Com_Environments::Rename_Environ(int Index)
{
	strcpy(App->Cl_Dialogs->btext, "Change Environ Name");
	strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Scene->B_Object[Index]->Mesh_Name);

	App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects, 1);

	if (App->Cl_Dialogs->Canceled == 1)
	{
		return;
	}

	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, App->Cl_Dialogs->Chr_Text);

	App->SBC_FileView->Change_Item_Name(App->SBC_Scene->B_Object[Index]->FileViewItem, App->Cl_Dialogs->Chr_Text);

	Mark_As_Altered_Environ(Index);

}

// *************************************************************************
// *		Add_New_Environ_Entiry:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Com_Environments::Add_New_Environ_Entity(bool FirstOne)
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Object_Count;

	App->SBC_Scene->B_Object[Index] = new Base_Object();
	App->SBC_Scene->B_Object[Index]->S_Environ[0] = new Environ_type;
	Set_Environ_Defaults(Index);
	

	App->SBC_Scene->B_Object[Index]->Type = Enums::Bullet_Type_Static;
	App->SBC_Scene->B_Object[Index]->Shape = Enums::Shape_Box;
	App->SBC_Scene->B_Object[Index]->This_Object_UniqueID = App->SBC_Scene->UniqueID_Object_Counter; // Unique ID

	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_FileName, "EnvironmentEntity_GD.mesh");

	strcpy_s(B_Name, "Environ_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, B_Name);

	if (FirstOne == 0)
	{
		Ogre::Vector3 Pos = App->SBC_Object->GetPlacement(-50);
		App->SBC_Scene->B_Object[Index]->Mesh_Pos = Pos;
	}
	else
	{
		Ogre::Vector3 Pos = Ogre::Vector3(0, 0, 0);
	}

	Create_Environ_Entity(Index);

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Evirons_Folder, App->SBC_Scene->B_Object[Index]->Mesh_Name, Index, true);
	App->SBC_Scene->B_Object[Index]->FileViewItem = Temp;

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Evirons_Folder);
	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[Index]->FileViewItem);

	App->SBC_Scene->UniqueID_Object_Counter++;
	App->SBC_Scene->Object_Count++;

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Sounds_Folder);
	return 1;
}

// *************************************************************************
// *		Create_Environ_Entity:- Terry and Hazel Flanigan	2022		   *
// *************************************************************************
bool SB_Com_Environments::Create_Environ_Entity(int Index)
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

	App->SBC_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Object->Phys_Body = new btRigidBody(rbInfo);
	Object->Phys_Body->setRestitution(1.0);
	Object->Phys_Body->setFriction(1.5);
	Object->Phys_Body->setUserPointer(Object->Object_Node);
	Object->Phys_Body->setWorldTransform(startTransform);

	Object->Usage = Enums::Usage_EnvironEntity;
	Object->Phys_Body->setUserIndex(Enums::Usage_EnvironEntity);
	Object->Phys_Body->setUserIndex2(Index);

	Object->Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	int f = Object->Phys_Body->getCollisionFlags();

	Object->Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT
		| btCollisionObject::CF_KINEMATIC_OBJECT
		| btCollisionObject::CF_NO_CONTACT_RESPONSE);


	App->SBC_Bullet->dynamicsWorld->addRigidBody(Object->Phys_Body);

	//Set_Physics(Index);

	return 1;
}

// *************************************************************************
// *		Set_Environ_Defaults:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Com_Environments::Set_Environ_Defaults(int Index)
{
	App->SBC_Scene->B_Object[Index]->Altered = 0;

	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Environment_ID = 0;
	strcpy(App->SBC_Scene->B_Object[Index]->S_Environ[0]->Environment_Name,"Not_Set");

	//----------------------- Sound
	strcpy(App->SBC_Scene->B_Object[Index]->S_Environ[0]->Sound_File, "The_Sun.ogg");
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndFile = NULL;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Play = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Loop = 1;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndVolume = 0.5;

	//----------------------- Light
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.x = 1;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.y = 1;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.z = 1;

	App->SBC_Scene->B_Object[Index]->S_Environ[0]->DiffuseColour.x = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->DiffuseColour.y = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->DiffuseColour.z = 0;

	App->SBC_Scene->B_Object[Index]->S_Environ[0]->SpecularColour.x = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->SpecularColour.y = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->SpecularColour.z = 0;

	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Light_Position.x = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Light_Position.y = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Light_Position.z = 0;

	// Sky
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Curvature = 15;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Distance = 4000;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Enabled = 0;
	strcpy(App->SBC_Scene->B_Object[Index]->S_Environ[0]->Material, "Examples/CloudySky");
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Tiling = 15;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->type = 1;

	// Fog
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On = 0;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Mode = FOG_LINEAR;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Density = 0.001000;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start = 50;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End = 300;
	App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour = Ogre::Vector3(1, 1, 1);
}

// *************************************************************************
// *		Load_Environment:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Com_Environments::Set_First_Environment(int Index)
{
	float x = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.x;
	float y = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.y;
	float z = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.z;

	App->Cl19_Ogre->mSceneMgr->setAmbientLight(ColourValue(x, y, z));

	if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On == 1)
	{
		EnableFog(true);
	}
	else
	{
		App->Cl19_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}
}

// *************************************************************************
// *	  			EnableFog:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Com_Environments::EnableFog(bool SetFog)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	if (SetFog == true)
	{
		float Start = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start;
		float End = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End;
		float Density = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Density;

		float x = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.x;
		float y = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.y;
		float z = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.z;

		App->Cl19_Ogre->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x, y, z), Density, (Ogre::Real)Start, (Ogre::Real)End);
	}
	else
	{
		App->Cl19_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}

	return 1;
}

// *************************************************************************
// *	  			EnableFog:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Com_Environments::EnableFog_Collision(bool SetFog ,int Index)
{
	
	if (SetFog == true)
	{
		float Start = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start;
		float End = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End;
		float Density = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Density;

		float x = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.x;
		float y = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.y;
		float z = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.z;

		App->Cl19_Ogre->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x, y, z), Density, (Ogre::Real)Start, (Ogre::Real)End);
	}
	else
	{
		App->Cl19_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}
}

// *************************************************************************
// *	Set_Environment_From_Environ:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void SB_Com_Environments::Set_Environment_From_Environ(int Index)
{
	
	float x = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.x;
	float y = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.y;
	float z = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.z;
	
	App->Cl19_Ogre->mSceneMgr->setAmbientLight(ColourValue(x, y, z));

	
	if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On == 1)
	{
		EnableFog_Collision(true, Index);
	}
	else
	{
		App->Cl19_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}

}

// *************************************************************************
// *	Mark_As_Altered_Environ:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_Com_Environments::Mark_As_Altered_Environ(int Index)
{
	App->SBC_Scene->B_Object[Index]->Altered = 1;

	App->SBC_Scene->Scene_Modified = 1;

	App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Object[Index]->FileViewItem);
}

// *************************************************************************
// *		Get_First_Environ:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
int SB_Com_Environments::Get_First_Environ()
{
	int Count = 0;
	while (Count < App->SBC_Scene->Object_Count)
	{
		if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_EnvironEntity)
		{
			return Count;
		}

		Count++;
	}

	return -1;
}

// *************************************************************************
// *				GameMode:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_Com_Environments::GameMode(bool Is_On)
{
	int First_Environ = App->SBC_Com_Environments->Get_First_Environ();

	if (Is_On == 1)
	{
		char buff[1024];
		strcpy(buff, App->SBC_SoundMgr->Default_Folder);
		strcat(buff, "\\Media\\Sounds\\");

		strcat(buff, App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->Sound_File);

		App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->SndFile = App->SBC_SoundMgr->SoundEngine->play2D(buff, App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->Loop, true, true);

		App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->SndFile->setVolume(App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->SndVolume);
		App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->SndFile->setIsPaused(false);

		App->SBC_Collision->Old_Sound_Index = First_Environ;
	}
	else
	{
		if (App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->SndFile == NULL)
		{
		}
		else
		{
			App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->SndFile->setIsPaused(true);
			App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->SndFile->drop();
			App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->SndFile = NULL;
		}
	}

	float x = App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->AmbientColour.x;
	float y = App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->AmbientColour.y;
	float z = App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->AmbientColour.z;

	App->Cl19_Ogre->mSceneMgr->setAmbientLight(ColourValue(x, y, z));

	if (App->SBC_Scene->B_Object[First_Environ]->S_Environ[0]->Fog_On == 1)
	{
		EnableFog(true);
	}
	else
	{
		App->Cl19_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}
}

// *************************************************************************
// *		Set_Environment_By_Index:- Terry and Hazel Flanigan 2022 	   *
// *************************************************************************
int SB_Com_Environments::Set_Environment_By_Index(bool PlayMusic,int Index)
{

	float x = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.x;
	float y = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.y;
	float z = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.z;
	App->Cl19_Ogre->mSceneMgr->setAmbientLight(ColourValue(x, y, z));


	// Fog
	if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On == 1)
	{
		float Start = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start;
		float End = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End;
		float Density = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Density;

		float x = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.x;
		float y = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.y;
		float z = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.z;

		App->Cl19_Ogre->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x, y, z), Density, (Ogre::Real)Start, (Ogre::Real)End);
	}
	else
	{
		App->Cl19_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}

	if (PlayMusic == 1)
	{
		char buff[1024];
		strcpy(buff, App->SBC_SoundMgr->Default_Folder);
		strcat(buff, "\\Media\\Sounds\\");

		if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Play == 1)
		{
			strcat(buff, App->SBC_Scene->B_Object[Index]->S_Environ[0]->Sound_File);

			App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndFile = App->SBC_SoundMgr->SoundEngine->play2D(buff, App->SBC_Scene->B_Object[Index]->S_Environ[0]->Loop, true, true);

			App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndFile->setVolume(App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndVolume);
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndFile->setIsPaused(false);
		}
	}
	else
	{
		if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndFile == NULL)
		{
		}
		else
		{
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndFile->setIsPaused(true);
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndFile->drop();
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndFile = NULL;
		}
	}

	return 1;
}

