/*	
	Copyright (c) 2009 - 2013 W.T.Flanigan Bernard Parkin and H.C.Flanigan

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
#include "StdAfx.h"
#include "BT_App.h" //???
#include "GameDirectorOgre.h"
#pragma warning( disable : 4996 4311 4305)

GameDirectorOgre::GameDirectorOgre(void)
{
	mRoot =  NULL;
	//body = NULL;
	mWindow =  NULL;
	mSceneMgr =  NULL;
	mCamera =  NULL;
	PlacementCam = NULL;

	PhysicsFrameListener =  NULL;
	
	PermResourceGroup = "PermanentResourceGroup";

	WinHwnd = NULL;

	Full_Screen = 1; // Default Full Screen
}

GameDirectorOgre::~GameDirectorOgre(void)
{

}
// *************************************************************************
// *				InitOgre (Terry Bernie)							   *
// *************************************************************************
void GameDirectorOgre::InitOgre(void)
{
	OgreCreateRoot();
	SetUpResources();
	Configure();
	chooseSceneManager();
	createCamera();
	createViewports();
	loadResources();
	createFrameListener();

	m_imgui.Init(mSceneMgr, NULL); //RenderHwnd);

}
// *************************************************************************
// *				OgreCreateRoot (Terry Bernie)						   *
// *************************************************************************
bool GameDirectorOgre::OgreCreateRoot(void)
{
	Ogre::String pluginsPath;
	pluginsPath = mResourcePath + "plugins.cfg";

	mRoot = OGRE_NEW Ogre::Root(pluginsPath,mResourcePath + "GDEditor.cfg", mResourcePath + "GDEditor.log");
	return 1;
}

// *************************************************************************
// *				SetUpResources (Terry Bernie)						   *
// *************************************************************************
bool GameDirectorOgre::SetUpResources(void)
{
	Ogre::String File; 
	char Copy[1024];

	strcpy(Copy,App->GameDirecory_FullPath);
	App->GDCL_Utilities->ReverseBackSlash(Copy);
	File = App->GDCL_Utilities->Return_Chr;
	
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(PermResourceGroup);

	//-------------------------------- Zip Files
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Media/Core_Data/OgreCore.zip", "Zip", PermResourceGroup);

	//-------------------------------- File System
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/App_Resources", "FileSystem", PermResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/Zipper", "FileSystem", PermResourceGroup);

	return 1;
}

// *************************************************************************
// *				Configure (Terry Bernie)							   *
// *************************************************************************
bool GameDirectorOgre::Configure(void)
{
	Ogre::RenderSystem* rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	if (!(rs->getName() == "OpenGL Rendering Subsystem"))
	{
		return false; //No RenderSystem found
	}

	Full_Screen = 1;

	char buff[1025];
	if (Full_Screen == 1)
	{
		sprintf(buff, "%i x %i @ 32-bit", App->ScreenWidth, App->ScreenHeight);
		rs->setConfigOption("Video Mode", buff);
	}
	else
	{
		sprintf(buff, "%i x %i @ 32-bit colour", 1024, 768);
		rs->setConfigOption("Full Screen", "No");
	}
	
	mRoot->setRenderSystem(rs);

	mWindow = mRoot->initialise(true, "poo");// App->GDCL_Scene_Data->S_Scene[0]->GDSceneName);
	
	//if (Full_Screen == 1)
	{
		//mWindow->setFullscreen(true, App->ScreenWidth, App->ScreenHeight);
	}
	
	return 1;
	
}
// *************************************************************************
// *				chooseSceneManager (Terry Bernie)					   *
// *************************************************************************
bool GameDirectorOgre::chooseSceneManager(void)
{
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager");

	mSceneMgr->setAmbientLight(Ogre::ColourValue(1,1,1));
	return 1;
}
// *************************************************************************
// *					createCamera (Terry Bernie)						   *
// *************************************************************************
bool GameDirectorOgre::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("MainCamera");
	mCamera->setPosition(Ogre::Vector3(0,-50,40));
	mCamera->lookAt(Ogre::Vector3(0,-50,0));
	mCamera->setNearClipDistance(Ogre::Real(0.1));
	mCamera->setFarClipDistance(Ogre::Real(8000));

	PlacementCam = mSceneMgr->createCamera("PlacementCam");
	return 1;
}
// *************************************************************************
// *					createViewports (Terry Bernie)					   *
// *************************************************************************
bool GameDirectorOgre::createViewports(void)
{
	mWindow->removeAllViewports();
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	
	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(0);

	vp->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.5));

	return 1;
}
// *************************************************************************
// *					loadResources (Terry Bernie)					   *
// *************************************************************************
bool GameDirectorOgre::loadResources(void)
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

		return 1;
	}
// *************************************************************************
// *				createFrameListener (Terry Bernie)					   *
// *************************************************************************
bool GameDirectorOgre::createFrameListener(void)
{
	
	PhysicsFrameListener = new BT_PhysicsListener(mCamera,mTerrain);
	mRoot->addFrameListener(PhysicsFrameListener);

	return 1;
}

// *************************************************************************
// *				Get_View_Height_Width (Terry Bernie)				   *
// *************************************************************************
bool GameDirectorOgre::Get_View_Height_Width(void)
{
	Ogre::Viewport* vp = mWindow->getViewport(0);

	PhysicsFrameListener->View_Width = vp->getActualWidth();
	PhysicsFrameListener->View_Height = vp->getActualHeight();

	return 1;
}