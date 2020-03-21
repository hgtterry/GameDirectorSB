/*
Copyright (c) GameDirector 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
#include "GD19_Ogre.h"




GD19_Ogre::GD19_Ogre(void)
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

	RenderListener = nullptr;

	PermResourceGroup = "PermanentResourceGroup";
	TempResourceGroup = "TemporyResourceGroup";

}

GD19_Ogre::~GD19_Ogre(void)
{
}

// *************************************************************************
// *						InitOgre Terry Bernie						   *
// *************************************************************************
bool GD19_Ogre::InitOgre(void)
{
	OgreCreateRoot();
	SetUpResources();
	Configure();
	chooseSceneManager();
	createCamera();
	createViewports();
	loadResources();

	manObj = mSceneMgr->createManualObject("sampleArea");
	ModelNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	ModelNode->attachObject(manObj);

	// Set Up Grid Functions
	App->Cl_Grid->Grid_Update(1);
	App->Cl_Grid->Hair_Update(1);

	App->Cl_Grid->DummyNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
	App->Cl_Visuals->Load_PickSight();
	App->Cl_Grid->Load_Arrow();
	
	m_imgui.Init(mSceneMgr, RenderHwnd); // OIS mouse + keyboard

	
	createFrameListener();
	//App->Cl_Grid->Reset_View();


	////Ogre::ResourceGroupManager::getSingleton().createResourceGroup(TempResourceGroup);

	//CreateTextOverlay();

	return 1;
}

// *************************************************************************
// *				OgreCreateRoot (Terry Bernie)						   *
// *************************************************************************
bool GD19_Ogre::OgreCreateRoot(void)
{
	Ogre::String pluginsPath;
	pluginsPath = mResourcePath + "plugins.cfg";

	mRoot = OGRE_NEW Ogre::Root(pluginsPath, mResourcePath + "Equity_CFG.cfg", mResourcePath + "Equity_LOG.log");
	//Ogre::LogManager::getSingleton().setLogDetail(Ogre::LoggingLevel::LL_LOW);
	return 1;
}

// *************************************************************************
// *				SetUpResources (Terry Bernie)						   *
// *************************************************************************
bool GD19_Ogre::SetUpResources(void)
{

	Ogre::String File;
	char Copy[1024];

	strcpy(Copy, App->EquityDirecory_FullPath);
	App->Cl_Utilities->ReverseBackSlash(Copy);
	File = App->Cl_Utilities->Return_Chr;

	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(TempResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(PermResourceGroup);

	//-------------------------------- Zip Files
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Media/Core_Data/OgreCore.zip", "Zip",
		PermResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Media/Core_Data/Equity.zip", "Zip",
		PermResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Media/Core_Data/GDCore.zip", "Zip",
		PermResourceGroup);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation("Media/Core_Data/Panels.zip", "Zip",
		PermResourceGroup);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/Zipper", "FileSystem",
		PermResourceGroup);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/fonts", "FileSystem",
		PermResourceGroup);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/Particles", "FileSystem",
		PermResourceGroup);

	//-------------------------------- Materials
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/materials/Actor_scripts", "FileSystem",
		PermResourceGroup);


	//-------------------------------- Textures
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/textures", "FileSystem",
		PermResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/textures/Test", "FileSystem",
		PermResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/textures/misc", "FileSystem",
		PermResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/textures/Sinbad", "FileSystem",
		PermResourceGroup);
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/textures/Hall", "FileSystem",
		PermResourceGroup);



	//-------------------------------- Actors/Mesh
	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/Actors", "FileSystem",
		PermResourceGroup);

	Get_Main_Folders();


	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(File + "/Media/Levels/RF_Level1_Ogre", "FileSystem",
		PermResourceGroup);

	return 1;
}

// *************************************************************************
// *						Get_Main_Folders Terry Berni			 	   *
// *************************************************************************
bool GD19_Ogre::Get_Main_Folders()
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

					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(New_Path, "FileSystem", PermResourceGroup);
					Get_Sub_Folders(FindFileData.cFileName);
				}

			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}

	return 0;
}

// *************************************************************************
// *						Get_Sub_Folders Terry Berni				 	   *
// *************************************************************************
bool GD19_Ogre::Get_Sub_Folders(char* Sub_folder)
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

					Ogre::ResourceGroupManager::getSingleton().addResourceLocation(New_Path, "FileSystem", PermResourceGroup);

				}

			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}

	return 0;
}


// *************************************************************************
// *					loadResources (Terry Bernie)					   *
// *************************************************************************
bool GD19_Ogre::loadResources(void)
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
// *				Configure (Terry Bernie)							   *
// *************************************************************************
bool GD19_Ogre::Configure(void)
{

	Ogre::RenderSystem* rs = mRoot->getRenderSystemByName("OpenGL Rendering Subsystem");
	if (!(rs->getName() == "OpenGL Rendering Subsystem"))
	{
		return false; //No RenderSystem found
	}

	//	rs->setConfigOption("Full Screen", "No");
	//	rs->setConfigOption("Video Mode", "1024 x 768 @ 32-bit colour");

	mRoot->setRenderSystem(rs);
	
	mWindow = mRoot->initialise(false);
	Ogre::NameValuePairList options;

	options["externalWindowHandle"] =
		Ogre::StringConverter::toString((size_t)RenderHwnd);

	mWindow = mRoot->createRenderWindow("Main RenderWindow", 1024, 768, false, &options);

	//App->Cl_Panels->Width = mWindow->getWidth();
	//App->Cl_Panels->Height = mWindow->getHeight();

	return true;
}

// *************************************************************************
// *				chooseSceneManager (Terry Bernie)					   *
// *************************************************************************
bool GD19_Ogre::chooseSceneManager(void)
{
	mSceneMgr = mRoot->createSceneManager("DefaultSceneManager"); // Temp
	//ImGui::ImguiManager::getSingleton().init(scnMgr);

	mOverlaySystem = new Ogre::OverlaySystem();
	mSceneMgr->addRenderQueueListener(mOverlaySystem);

	mSceneMgr->setAmbientLight(Ogre::ColourValue(1, 1, 1));
	
	return 1;
}

// *************************************************************************
// *					createCamera (Terry Bernie)						   *
// *************************************************************************
bool GD19_Ogre::createCamera(void)
{
	mCamera = mSceneMgr->createCamera("MainCamera");
	mCamera->setPosition(Ogre::Vector3(0, -50, 40));
	mCamera->lookAt(Ogre::Vector3(0, -50, 0));
	mCamera->setNearClipDistance(Ogre::Real(0.1));
	mCamera->setFarClipDistance(Ogre::Real(8000));

	PlacementCam = mSceneMgr->createCamera("PlacementCam");
	return 1;
}

// *************************************************************************
// *					createViewports (Terry Bernie)					   *
// *************************************************************************
bool GD19_Ogre::createViewports(void)
{
	mWindow->removeAllViewports();
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);
	mCamera->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(0);

	vp->setBackgroundColour(Ogre::ColourValue(0.5, 0.5, 0.5));

	return 1;
}

// *************************************************************************
// *				createFrameListener (Terry Bernie)					   *
// *************************************************************************
bool GD19_Ogre::createFrameListener(void)
{
	//// Physics Frame Listener
	OgreListener = new GD19_OgreListener();
	mRoot->addFrameListener(OgreListener);

	String RenderSystemName = mSceneMgr->getDestinationRenderSystem()->getName();
	
	RenderListener = NULL;
	if ("OpenGL Rendering Subsystem" == RenderSystemName)
	{
		RenderListener = new VM_Render();
		mSceneMgr->addRenderQueueListener(RenderListener);
	}

	return 1;
}

// *************************************************************************
// *					Go_FullScreen Terry Bernie					  	   *
// *************************************************************************
void GD19_Ogre::Go_FullScreen_Mode(void)
{


	App->FullScreen = 1;
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(App->ViewGLhWnd, HWND_TOP, 0, 0, cx, cy, NULL);


	SetParent(App->ViewGLhWnd, NULL);


	mWindow->resize(cx, cy);

	mWindow->windowMovedOrResized();
	mCamera->setAspectRatio((Ogre::Real)mWindow->getWidth() / (Ogre::Real)mWindow->getHeight());

	Root::getSingletonPtr()->renderOneFrame();

}

// *************************************************************************
// *	  						ExitFullScreen							   *
// *************************************************************************
bool GD19_Ogre::ExitFullScreen()
{
	//if(Flags[0]->OgreIsRunning==1)
	{

		App->FullScreen = 0;
		SetParent(App->ViewGLhWnd, App->Fdlg);
		SetWindowPos(App->ViewGLhWnd, HWND_TOP, 235, 11, 542, 455, SWP_NOZORDER);
		App->Resize_OgreWin();

		mWindow->windowMovedOrResized();
		mCamera->setAspectRatio((Ogre::Real)mWindow->getWidth() / (Ogre::Real)mWindow->getHeight());
		mCamera->yaw(Radian(0));
		Root::getSingletonPtr()->renderOneFrame();
		App->Cl_Scene_Data->EditorMode();

	}
	return 1;
}

// *************************************************************************
// *					RenderFrame (Terry Bernie)						   *
// *************************************************************************
bool GD19_Ogre::RenderFrame(void)
{
	Ogre::Root::getSingletonPtr()->renderOneFrame();
	return 1;
}

// *************************************************************************
// *				Get_View_Height_Width (Terry Bernie)				   *
// *************************************************************************
bool GD19_Ogre::Get_View_Height_Width(void)
{
	Ogre::Viewport* vp = mWindow->getViewport(0);

	OgreListener->View_Width = vp->getActualWidth();
	OgreListener->View_Height= vp->getActualHeight();
	
	return 1;
}