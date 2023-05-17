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
*/

#include "stdafx.h"
#include "WV_App.h"
#include "WV_Ogre.h"

WV_Ogre::WV_Ogre(void)
{
	RenderHwnd =	nullptr;
	mRoot =			nullptr;
	mWindow =		nullptr;
	mSceneMgr =		nullptr;
	mCamera =		nullptr;
	PlacementCam =	nullptr;
	OgreListener =	nullptr;
	manObj =		nullptr;
	ModelNode =		nullptr;

	OgreModel_Ent =  nullptr;
	OgreModel_Node = nullptr;

	App_Resource_Group = "App_Resource_Group";

	Block_RenderingQueued = 0;

	FPSLock = 4200;

	Fps_Tick = 4000;

	PCFreq = 0.0;
	CounterStart = 0;

	FPStimer.reset();
}

WV_Ogre::~WV_Ogre(void)
{
}

// *************************************************************************
// *				InitOgre:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_Ogre::InitOgre(void)
{
	OgreCreateRoot();
	SetUpResources();
	Configure();
	chooseSceneManager();
	createCamera();
	createViewports();
	Initialise_Resources();

	manObj = mSceneMgr->createManualObject("sampleArea");
	ModelNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ModelNode->attachObject(manObj);

	// Set Up Grid Functions
	 
	App->CL_Grid->Grid_Update(1);
	App->CL_Grid->Hair_Update(1);


	App->CL_Grid->DummyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	m_imgui.Init(mSceneMgr,RenderHwnd);

	createFrameListener();
	
	App->CL_Grid->Reset_View();
	App->CL_Grid->Grid_SetVisible(true);

	return 1;
}

// *************************************************************************
// *		Ogre_Render_Loop:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_Ogre::Ogre_Render_Loop(void)
{
	mRoot->clearEventTimes();

	while (true)
	{
		Ogre::WindowEventUtilities::messagePump();

		if (mWindow->isClosed()) return false;

		if (FPStimer.getMicroseconds() > Fps_Tick) // FPSLock)
		{
			if (Block_RenderingQueued == 0)
			{

				// mRoot->renderOneFrame()
				if (!mRoot->_fireFrameStarted())
				{
					return false;
				}

				if (!mRoot->_updateAllRenderTargets())
				{
					return false;
				}

				if (!mRoot->_fireFrameEnded())
				{
					return false;
				}

				FPStimer.reset();
		
			}
		}
	}

	return 1;
}

// *************************************************************************
// *		OgreCreateRoot:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
bool WV_Ogre::OgreCreateRoot(void)
{
	Ogre::String pluginsPath;
	pluginsPath = mResourcePath + "plugins.cfg";

	if (App->Debug_App == 1)
	{
		mRoot = OGRE_NEW Ogre::Root(pluginsPath, mResourcePath + "Equity_CFG.cfg", mResourcePath + "EquitySB.log");
		Ogre::LogManager::getSingleton().createLog(mResourcePath + "App.log");
	}
	else
	{
		mRoot = OGRE_NEW Ogre::Root(pluginsPath, mResourcePath + "Equity_CFG.cfg", mResourcePath + "");
	}
	
	return 1;
}

// **************************************************************************
// *			SetUpResources:- Terry and Hazel Flanigan 2022				*
// **************************************************************************
bool WV_Ogre::SetUpResources(void)
{

	Ogre::String File;
	char Copy[1024];

	strcpy(Copy, App->EquityDirecory_FullPath);
	//App->Cl_Utilities->ReverseBackSlash(Copy);
	//File = App->Cl_Utilities->Return_Chr;
	
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App_Resource_Group);

	//-------------------------------- Zip Files
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Media/Core_Data/OgreCore.zip", "Zip",App_Resource_Group);

	//-------------------------------- File System
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/App_Resources" ,"FileSystem", App_Resource_Group);
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/New_Particles", "FileSystem", App_Resource_Group);
	
	return 1;
}

// *************************************************************************
// *		Initialise_Resources:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool WV_Ogre::Initialise_Resources(void)
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	return 1;
}

// *************************************************************************
// *			Get_Main_Folders:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool WV_Ogre::Get_Main_Folders()
{
	char Path[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(Path, App->EquityDirecory_FullPath);
	strcat(Path, "\\Media\\Actors\\*.*");

	char Mesh_Path[1024];
	strcpy(Mesh_Path, App->EquityDirecory_FullPath);
	strcat(Mesh_Path, "\\Media\\Actors\\");

	hFind = FindFirstFile(Path, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0)
				{

				}
				else
				{
					char New_Path[1024];
					strcpy(New_Path, Mesh_Path);
					strcat(New_Path, FindFileData.cFileName);

					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(New_Path, "FileSystem", App_Resource_Group);
					Get_Sub_Folders(FindFileData.cFileName);
				}

			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}

	return 0;
}

// *************************************************************************
// *			Get_Sub_Folders:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
bool WV_Ogre::Get_Sub_Folders(char* Sub_folder)
{
	char Path[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(Path, App->EquityDirecory_FullPath);
	strcat(Path, "\\Media\\Actors\\");
	strcat(Path, Sub_folder);
	strcat(Path, "\\*.*");

	char Mesh_Path[1024];
	strcpy(Mesh_Path, App->EquityDirecory_FullPath);
	strcat(Mesh_Path, "\\Media\\Actors\\");
	strcat(Mesh_Path, Sub_folder);
	strcat(Mesh_Path, "\\");

	hFind = FindFirstFile(Path, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0)
				{

				}
				else
				{
					char New_Path[1024];
					strcpy(New_Path, Mesh_Path);
					strcat(New_Path, FindFileData.cFileName);

					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(New_Path, "FileSystem", App_Resource_Group);

				}

			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}

	return 0;
}

// *************************************************************************
// *				Configure:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_Ogre::Configure(void)
{

	Ogre::RenderSystem* rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	if (!(rs->getName() == "OpenGL Rendering Subsystem"))
	{
		return false; //No RenderSystem found
	}

	mRoot->setRenderSystem(rs);
	
	mWindow = mRoot->initialise(false);
	Ogre::NameValuePairList options;

	options["vsync"] = true;

	options["externalWindowHandle"] =
		Ogre::StringConverter::toString((size_t)RenderHwnd);
	
	mWindow = mRoot->createRenderWindow("Main RenderWindow", 1024, 768, false, &options);

	return true;
}

// *************************************************************************
// *		chooseSceneManager:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_Ogre::chooseSceneManager(void)
{
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager"); // Temp
	
	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	
	return 1;
}

// *************************************************************************
// *			createCamera:- Terry and Hazel Flanigan 202				   *
// *************************************************************************
bool WV_Ogre::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("MainCamera");
	mCamera->setPosition(Ogre::Vector3(0, 90, 100));
	mCamera->lookAt(Ogre::Vector3(0, 30, 0));
	mCamera->setNearClipDistance(Ogre::Real(0.1));
	mCamera->setFarClipDistance(Ogre::Real(8000));

	PlacementCam = mSceneMgr->createCamera("PlacementCam");
	return 1;
}

// *************************************************************************
// *			createViewports:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_Ogre::createViewports(void)
{
	mWindow->removeAllViewports();
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(0);

	vp->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.5));

	return 1;
}

// *************************************************************************
// *		createFrameListener:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WV_Ogre::createFrameListener(void)
{
	// Physics Frame Listener
	OgreListener = new WV_OgreListener();
	mRoot->addFrameListener(OgreListener);

	String RenderSystemName = mSceneMgr->getDestinationRenderSystem()->getName();
	
	BulletListener = NULL;

	if ("OpenGL Rendering Subsystem" == RenderSystemName)
	{
		BulletListener = new WV_Debug_Render();

		mSceneMgr->addRenderQueueListener(BulletListener);

		BulletListener->setDebugMode(BulletListener->getDebugMode()
			| btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);
		App->CL_Bullet->dynamicsWorld->setDebugDrawer(BulletListener);
	}

	return 1;
}

// *************************************************************************
// *			RenderFrame:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool WV_Ogre::RenderFrame(void)
{
	Ogre::Root::getSingletonPtr()->renderOneFrame();
	return 1;
}

// *************************************************************************
// *		Get_View_Height_Width:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool WV_Ogre::Get_View_Height_Width(void)
{
	Ogre::Viewport* vp = mWindow->getViewport(0);

	OgreListener->View_Width = vp->getActualWidth();
	OgreListener->View_Height= vp->getActualHeight();
	
	return 1;
}

// *************************************************************************
// *			GetVersion:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void WV_Ogre::GetVersion_OpenGL(char* buff)
{
	int  major = mRoot->getRenderSystem()->getDriverVersion().major;
	int  minor = mRoot->getRenderSystem()->getDriverVersion().minor;

	Ogre::String name = mRoot->getRenderSystem()->getName();

	char c_GLVer[256];
	strcpy(c_GLVer, name.c_str());

	char cMajor[20];
	char cMinor[20];
	_itoa(major, cMajor, 10);
	_itoa(minor, cMinor, 10);
	strcpy(buff, " ");
	strcat(buff, c_GLVer);
	strcat(buff, " ");
	strcat(buff, cMajor);
	strcat(buff, ".");
	strcat(buff, cMinor);
}
