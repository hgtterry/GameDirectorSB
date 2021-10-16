/*
Copyright(c) Equity15 2019 Inflanite Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty.In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions :

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software.If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#include "stdafx.h"
#include "GD19_App.h"
#include "EQ15_Bullet_AddRoom.h"


EQ15_Bullet_AddRoom::EQ15_Bullet_AddRoom()
{
}


EQ15_Bullet_AddRoom::~EQ15_Bullet_AddRoom()
{
}


// *************************************************************************
// *					AddToScene Terry Flanigan 						   *
// *************************************************************************
void EQ15_Bullet_AddRoom::AddToScene(void)
{

	if (App->Cl19_Ogre->OgreModel_Ent && App->Cl19_Ogre->OgreModel_Node)
	{
		App->Cl19_Ogre->OgreModel_Node->detachAllObjects();
		App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->Cl19_Ogre->OgreModel_Node);
		App->Cl19_Ogre->mSceneMgr->destroyEntity(App->Cl19_Ogre->OgreModel_Ent);
		App->Cl19_Ogre->OgreModel_Ent = NULL;
		App->Cl19_Ogre->OgreModel_Node = NULL;
	}

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(App->Cl19_Ogre->TempResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App->Cl19_Ogre->TempResourceGroup);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(App->CL_Vm_Model->Texture_FolderPath,
		"FileSystem",
		App->Cl19_Ogre->TempResourceGroup);

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (...)
	{

	}

	App->Cl19_Ogre->OgreModel_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("UserMesh", App->CL_Vm_Model->FileName, App->Cl19_Ogre->TempResourceGroup);
	App->Cl19_Ogre->OgreModel_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	App->Cl19_Ogre->OgreModel_Node->attachObject(App->Cl19_Ogre->OgreModel_Ent);

	App->Cl19_Ogre->OgreModel_Node->setVisible(true);
	App->Cl19_Ogre->OgreModel_Node->setPosition(0, 0, 0);
	App->Cl19_Ogre->OgreModel_Node->setScale(1, 1, 1);

	App->Cl_Grid->Grid_SetVisible(1);
}

// *************************************************************************
//							Add_New_Room Terry							   *
// *************************************************************************
bool EQ15_Bullet_AddRoom::Add_New_Room(void)
{
	int Index = App->Cl_Scene_Data->ObjectCount;


	App->Cl_Scene_Data->Cl_Object[Index] = new GD19_Objects();
	App->Cl_Scene_Data->Cl_Object[Index]->Object_ID = App->Cl_Scene_Data->Object_ID_Counter;

	// Only on newly created objects
	App->Cl_Scene_Data->Object_ID_Counter++;

	GD19_Objects* Object = App->Cl_Scene_Data->Cl_Object[Index];

	strcpy(Object->Name, App->Cl_Mesh_Viewer->Object_Name);
	strcpy(Object->MeshName, App->Cl_Mesh_Viewer->Selected_MeshFile);
	strcpy(Object->MeshName_FullPath, App->Cl_Mesh_Viewer->Selected_MeshFile);

	char PathFile[256];
	char ConNum[256];
	char ATest[256];

	strcpy_s(ATest, "GDEnt_");
	_itoa(Index, ConNum, 10);
	strcat(ATest, ConNum);

	strcpy(PathFile, Object->MeshName);
	Object->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity(ATest, PathFile, App->Cl19_Ogre->PermResourceGroup);
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

	App->Cl_Scene_Data->Scene_Has_Area = 1;
	App->Cl_Scene_Data->SceneLoaded = 1;

	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Scene_Data->ObjectCount++;  // Must be last line

	return 1;
}
