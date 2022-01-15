/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "ME_Ogre.h"


ME_Ogre::ME_Ogre()
{
	Ogre_Started = 0;

	Render_Hwnd =		nullptr;
	mRoot =				nullptr;
	mWindow =			nullptr;
	mSceneMgr =			nullptr;
	mOverlaySystem =	nullptr;
	mCamera =			nullptr;
	Ogre_Listener =		nullptr;

	App_Resource_Group = "App_Resource_Group";
	Equity_Resource_Group = "Equity_Resource_Group";

}


ME_Ogre::~ME_Ogre()
{
}

// *************************************************************************
// *						InitOgre Terry Bernie						   *
// *************************************************************************
bool ME_Ogre::Init_Ogre(void)
{
	Ogre_CreateRoot();
	SetUpResources();
	Configure();
	chooseSceneManager();
	createCamera();
	createViewports();
	loadResources();

	//manObj = mSceneMgr->createManualObject("sampleArea");
	//ModelNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//ModelNode->attachObject(manObj);

	// Set Up Grid Functions
	App->CL_Grid->Grid_Update(1);
	App->CL_Grid->Hair_Update(1);

	//App->Cl_Grid->DummyNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	//App->Cl_Visuals->Load_PickSight();
	//App->Cl_Grid->Load_Arrow();

	m_imgui.Init(mSceneMgr, Render_Hwnd);


	createFrameListener();

	return 1;
}

// *************************************************************************
// *				Ogre_CreateRoot (Terry Bernie)						   *
// *************************************************************************
bool ME_Ogre::Ogre_CreateRoot(void)
{
	Ogre::String pluginsPath;
	pluginsPath = mResourcePath + "plugins.cfg";

	mRoot = OGRE_NEW Ogre::Root(pluginsPath, mResourcePath + "Equity_CFG.cfg", mResourcePath + "Equity_ME_LOG.log");

	return 1;
}

// *************************************************************************
// *				SetUpResources (Terry Bernie)						   *
// *************************************************************************
bool ME_Ogre::SetUpResources(void)
{

	Ogre::String File;
	char Copy[1024];

	strcpy(Copy, App->EquityDirecory_FullPath);
	App->CL_Utilities->ReverseBackSlash(Copy);
	File = App->CL_Utilities->Return_Chr;

	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(Equity_Resource_Group);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App_Resource_Group);

	//-------------------------------- Zip Files
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Media/Core_Data/OgreCore.zip", "Zip",
		App_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Media/Core_Data/Equity.zip", "Zip",
		App_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Media/Core_Data/GDCore.zip", "Zip",
		App_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Media/Core_Data/Panels.zip", "Zip",
		App_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/Zipper", "FileSystem",
		App_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/fonts", "FileSystem",
		App_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/Particles", "FileSystem",
		App_Resource_Group);

	return 1;
}

// *************************************************************************
// *				Configure (Terry Bernie)							   *
// *************************************************************************
bool ME_Ogre::Configure(void)
{

	Ogre::RenderSystem* rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	if (!(rs->getName() == "OpenGL Rendering Subsystem"))
	{
		return false; //No RenderSystem found
	}

	mRoot->setRenderSystem(rs);

	mWindow = mRoot->initialise(false);
	Ogre::NameValuePairList options;

	options["externalWindowHandle"] =
		Ogre::StringConverter::toString((size_t)Render_Hwnd);

	mWindow = mRoot->createRenderWindow("Main RenderWindow", 1024, 768, false, &options);

	return true;
}

// *************************************************************************
// *				chooseSceneManager (Terry Bernie)					   *
// *************************************************************************
bool ME_Ogre::chooseSceneManager(void)
{
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager"); 
																  
	mOverlaySystem = new Ogre::OverlaySystem();

	mSceneMgr->addRenderQueueListener(mOverlaySystem);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));

	return 1;
}

// *************************************************************************
// *					createCamera (Terry Bernie)						   *
// *************************************************************************
bool ME_Ogre::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("MainCamera");
	mCamera->setPosition(Ogre::Vector3(0, 90, 100));
	mCamera->lookAt(Ogre::Vector3(0, 30, 0));
	mCamera->setNearClipDistance(Ogre::Real(0.1));
	mCamera->setFarClipDistance(Ogre::Real(8000));

	//PlacementCam = mSceneMgr->createCamera("PlacementCam");
	return 1;
}

// *************************************************************************
// *					createViewports (Terry Bernie)					   *
// *************************************************************************
bool ME_Ogre::createViewports(void)
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
bool ME_Ogre::loadResources(void)
{
	// Initialize, parse scripts etc
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	Ogre::FontManager* fontMgr = Ogre::FontManager::getSingletonPtr();

	Ogre::ResourcePtr font = fontMgr->create("MyFont", "General");

	font->setParameter("type", "truetype");

	font->setParameter("source", "cuckoo.ttf");

	font->setParameter("size", "32");

	font->setParameter("resolution", "96");

	font->load();

	return 1;
}

// *************************************************************************
// *				createFrameListener (Terry Bernie)					   *
// *************************************************************************
bool ME_Ogre::createFrameListener(void)
{
	//// Physics Frame Listener
	Ogre_Listener = new ME_OgreListener();
	mRoot->addFrameListener(Ogre_Listener);

	Ogre::String RenderSystemName = mSceneMgr->getDestinationRenderSystem()->getName();

	//RenderListener = NULL;
	//BulletListener = NULL;

	/*if ("OpenGL Rendering Subsystem" == RenderSystemName)
	{
		BulletListener = new GD_Bt_Render();

		mSceneMgr->addRenderQueueListener(BulletListener);

		BulletListener->setDebugMode(BulletListener->getDebugMode()
			| btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);
		App->Cl_Bullet->dynamicsWorld->setDebugDrawer(BulletListener);

	}*/

	return 1;
}

// *************************************************************************
// *				Get_View_Height_Width (Terry Bernie)				   *
// *************************************************************************
bool ME_Ogre::Get_View_Height_Width(void)
{
	Ogre::Viewport* vp = mWindow->getViewport(0);

	Ogre_Listener->View_Width = vp->getActualWidth();
	Ogre_Listener->View_Height = vp->getActualHeight();

	return 1;
}
