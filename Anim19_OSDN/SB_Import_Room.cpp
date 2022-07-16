#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Import_Room.h"



SB_Import_Room::SB_Import_Room()
{
	OgreModel_Ent = nullptr;
	OgreModel_Node = nullptr;

	Room_FileName[0] = 0,
	Room_Path_FileName[0] = 0,

	TempResourceGroup = "TemporyResourceGroup";
}


SB_Import_Room::~SB_Import_Room()
{
}


// *************************************************************************
// *					AddToScene Terry Bernie 						   *
// *************************************************************************
void SB_Import_Room::AddToScene(void)
{

	if (OgreModel_Ent && OgreModel_Node)
	{
		OgreModel_Node->detachAllObjects();
		App->Cl19_Ogre->mSceneMgr->destroySceneNode(OgreModel_Node);
		App->Cl19_Ogre->mSceneMgr->destroyEntity(OgreModel_Ent);
		OgreModel_Ent = nullptr;
		OgreModel_Node = nullptr;
	}

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(TempResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(TempResourceGroup);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Texture_FolderPath,
		"FileSystem",
		TempResourceGroup);

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (...)
	{

	}

	OgreModel_Ent = App->Cl19_Ogre->mSceneMgr->createEntity("UserMesh", FileName, TempResourceGroup);
	OgreModel_Node = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	OgreModel_Node->attachObject(OgreModel_Ent);

	OgreModel_Node->setVisible(true);
	OgreModel_Node->setPosition(0, 0, 0);
	OgreModel_Node->setScale(1, 1, 1);
}

// *************************************************************************
// *					Open_Room_File Terry Bernie						   *
// *************************************************************************
bool SB_Import_Room::Open_Room_File(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Room_FileName, "");
	strcpy(Room_Path_FileName, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Room_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Room_Path_FileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Room_FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Room_FileName);;
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return 1;
	}
	return 0;
}