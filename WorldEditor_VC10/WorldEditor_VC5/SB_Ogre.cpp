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
#include "AB_App.h"
#include "SB_Ogre.h"

SB_Ogre::SB_Ogre(void)
{
	RenderHwnd =	NULL;
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

	OgreIsRunning = 0;

	FPStimer.reset();
}

SB_Ogre::~SB_Ogre(void)
{
}

// *************************************************************************
// *				InitOgre:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Ogre::InitOgre(void)
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

	//m_imgui.Init(mSceneMgr,RenderHwnd);

	createFrameListener();
	
	App->CL_Grid->Reset_View();
	App->CL_Grid->Grid_SetVisible(true);

	Ogre::Root::getSingletonPtr()->renderOneFrame();

	HWND Test_hWnd = NULL;
	Test_hWnd = FindWindow(0, "XYZ");

	if (!Test_hWnd)
	{
		Debug
	}

	

	

	SetWindowLongPtr(Test_hWnd, GWL_STYLE, WS_BORDER);
	SetWindowPos(Test_hWnd, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
	ShowWindow(Test_hWnd, SW_SHOW);

	SetWindowPos(Test_hWnd, NULL, 4, 4, 820, 450, SWP_NOZORDER);

	
	HWND Check_hWnd = NULL;
	Check_hWnd = SetParent(Test_hWnd, App->CL_Ogre_Dialog->TestHwnd);

	if (!Check_hWnd)
	{
		Debug
	}
	//ShowWindow(Test_hWnd, SW_SHOW);
	OgreIsRunning = 1;
	App->CL_Ogre->Ogre_Render_Loop();
	//App->CL_Ogre->mRoot->startRendering();

	delete App->CL_Ogre->mRoot;
	App->CL_Ogre->mRoot = NULL;

	//App->Say("hererrrr");
	return 1;
}

// *************************************************************************
// *		Ogre_Render_Loop:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Ogre::Ogre_Render_Loop(void)
{
	App->Flash_Window();
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
bool SB_Ogre::OgreCreateRoot(void)
{
	Ogre::String pluginsPath;
	pluginsPath = mResourcePath + "plugins.cfg";

	if (App->Debug_App == 1)
	{
		mRoot = OGRE_NEW Ogre::Root(pluginsPath, mResourcePath + "Equity_CFG.cfg", mResourcePath + "WWSB.log");
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
bool SB_Ogre::SetUpResources(void)
{

	Ogre::String File;
	char Copy[1024];

	strcpy(Copy, App->WorldEditor_Directory);
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
bool SB_Ogre::Initialise_Resources(void)
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

	return 1;
}

// *************************************************************************
// *			Get_Main_Folders:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Ogre::Get_Main_Folders()
{
	char Path[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(Path, App->WorldEditor_Directory);
	strcat(Path, "\\Media\\Actors\\*.*");

	char Mesh_Path[1024];
	strcpy(Mesh_Path, App->WorldEditor_Directory);
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
bool SB_Ogre::Get_Sub_Folders(char* Sub_folder)
{
	char Path[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(Path, App->WorldEditor_Directory);
	strcat(Path, "\\Media\\Actors\\");
	strcat(Path, Sub_folder);
	strcat(Path, "\\*.*");

	char Mesh_Path[1024];
	strcpy(Mesh_Path, App->WorldEditor_Directory);
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
bool SB_Ogre::Configure(void)
{

	Ogre::RenderSystem* rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	if (!(rs->getName() == "OpenGL Rendering Subsystem"))
	{
		return false; //No RenderSystem found
	}

	rs->setConfigOption("Full Screen", "No");
	mRoot->setRenderSystem(rs);
	mWindow = mRoot->initialise(true,"XYZ");

	mWindow->resize(200, 200);

	HWND Test_hWnd = NULL;
	Test_hWnd = FindWindow(0,"XYZ");
	
	//int test = SetWindowLong(Test_hWnd, GWL_WNDPROC, (LONG)App->CL_Ogre_Dialog->Ogre3D_Proc);

	/*if (test)
	{
		App->Say("Failed");
	}*/


	//if (!Test_hWnd)
	//{
	//	Debug
	//}

	//HWND Check_hWnd = NULL;
	//Check_hWnd = SetParent(Test_hWnd, App->MainHwnd);

	//if (!Check_hWnd)
	//{
	//	Debug
	//}

	////SetWindowLongA(Test_hWnd, GWL_STYLE, WS_BORDER);
	//mWindow->
	//Ogre::NameValuePairList options;

	//options["vsync"] = true;
	//RenderHwnd = GetDlgItem(App->CL_Ogre_Dialog->TestHwnd, IDC_STATICTEST);

	/*options["externalWindowHandle"] =
		Ogre::StringConverter::toString((int)RenderHwnd);
	
	if (RenderHwnd)
	{
		mWindow = mRoot->createRenderWindow("Main RenderWindow", 100, 100, false, &options);
		Debug
	}*/

	return true;
}

// *************************************************************************
// *		chooseSceneManager:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Ogre::chooseSceneManager(void)
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
bool SB_Ogre::createCamera(void)
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
bool SB_Ogre::createViewports(void)
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
bool SB_Ogre::createFrameListener(void)
{
	// Physics Frame Listener
	OgreListener = new SB_OgreListener();
	mRoot->addFrameListener(OgreListener);

	String RenderSystemName = mSceneMgr->getDestinationRenderSystem()->getName();
	
	/*BulletListener = NULL;

	if ("OpenGL Rendering Subsystem" == RenderSystemName)
	{
		BulletListener = new WV_Debug_Render();

		mSceneMgr->addRenderQueueListener(BulletListener);

		BulletListener->setDebugMode(BulletListener->getDebugMode()
			| btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);
		App->CL_Bullet->dynamicsWorld->setDebugDrawer(BulletListener);
	}*/

	return 1;
}

// *************************************************************************
// *			RenderFrame:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
bool SB_Ogre::RenderFrame(void)
{
	Ogre::Root::getSingletonPtr()->renderOneFrame();
	return 1;
}

// *************************************************************************
// *		Get_View_Height_Width:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_Ogre::Get_View_Height_Width(void)
{
	Ogre::Viewport* vp = mWindow->getViewport(0);

	OgreListener->View_Width = vp->getActualWidth();
	OgreListener->View_Height= vp->getActualHeight();
	
	return 1;
}

// *************************************************************************
// *			GetVersion:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_Ogre::GetVersion_OpenGL(char* buff)
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
