/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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
*/ // :- Terry and Hazel Flanigan 2023

#include "stdafx.h"
#include "WV_App.h"
#include "WV_Load_Ogre.h"

WV_Load_Ogre::WV_Load_Ogre(void)
{
	OgreModel_Ent = nullptr;
	OgreModel_Node = nullptr;

	ResourcePath[0] = 0;
	ModelName[0] = 0;

	TempResourceGroup = "TemporyResourceGroup";
}

WV_Load_Ogre::~WV_Load_Ogre(void)
{
}

// *************************************************************************
// *					AddToScene Terry Bernie 						   *
// *************************************************************************
void WV_Load_Ogre::AddToScene(void)
{
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(TempResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(ResourcePath,"FileSystem",TempResourceGroup);

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
	}
	catch (...)
	{

	}


	if (OgreModel_Ent && OgreModel_Node)
	{
		OgreModel_Node->detachAllObjects();
		App->CL_Ogre->mSceneMgr->destroySceneNode(OgreModel_Node);
		App->CL_Ogre->mSceneMgr->destroyEntity(OgreModel_Ent);
		OgreModel_Ent = nullptr;
		OgreModel_Node = nullptr;
	}

	OgreModel_Ent = App->CL_Ogre->mSceneMgr->createEntity("UserMesh", ModelName, TempResourceGroup);
	OgreModel_Node = App->CL_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	OgreModel_Node->attachObject(OgreModel_Ent);

	OgreModel_Node->setVisible(true);
	OgreModel_Node->setPosition(0, 0, 0);
	OgreModel_Node->setScale(1, 1, 1);

	//App->CL_Grid->Grid_SetVisible(1);
}
