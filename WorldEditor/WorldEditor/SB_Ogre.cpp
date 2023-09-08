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
	Pause_Rendring = 0;

	FPSLock = 4200;

	Fps_Tick = 4000;
	RenderHwnd = nullptr;
	//Ogre_Window_hWnd = nullptr;

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
	App->CLSB_Grid->Grid_Update(1);
	App->CLSB_Grid->Hair_Update(1);


	App->CLSB_Grid->DummyNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();

	m_imgui.Init(mSceneMgr, RenderHwnd);

	createFrameListener();
	
	App->CLSB_Grid->Reset_View();
	App->CLSB_Grid->Grid_SetVisible(true);

	return 1;
}

// *************************************************************************
// *		Ogre_Render_Loop:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Ogre::Ogre_Render_Loop(void)
{
	mRoot->clearEventTimes();
	App->CLSB_TopTabs->OgreRunning_Flag = 1;

	while (true)
	{
		Ogre::WindowEventUtilities::messagePump();

		if (mWindow->isClosed()) return false;

		if (FPStimer.getMicroseconds() > Fps_Tick) // FPSLock)
		{
			if (Block_RenderingQueued == 0 && Pause_Rendring == 0)
			{
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
	mResourcePath = "";
	Ogre::String pluginsPath;
	pluginsPath = mResourcePath + "plugins.cfg";

	if (App->Debug_App == 1)
	{
		mRoot = new Ogre::Root(pluginsPath, mResourcePath + "Equity_CFG.cfg", mResourcePath + "WWSB.log");
		Ogre::LogManager::getSingleton().createLog(mResourcePath + "App.log");
		Ogre::LogManager::getSingleton().createLog(mResourcePath + "Error.log");
	}
	else
	{
		mRoot = new Ogre::Root(pluginsPath, mResourcePath + "Equity_CFG.cfg", mResourcePath + "");
		Ogre::LogManager::getSingleton().createLog(mResourcePath + "Error.log");
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

	
	mRoot->setRenderSystem(rs);

	mWindow = mRoot->initialise(false);
	Ogre::NameValuePairList options;

	options["externalWindowHandle"] =
		Ogre::StringConverter::toString((size_t)RenderHwnd);

	mWindow = mRoot->createRenderWindow("Main RenderWindow", 1024, 768, false, &options);
	
	
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
	
	RenderListener = NULL;
	if ("OpenGL Rendering Subsystem" == RenderSystemName)
	{
		RenderListener = new SB_Render();
		mSceneMgr->addRenderQueueListener(RenderListener);
	}

	BulletListener = NULL;

	if ("OpenGL Rendering Subsystem" == RenderSystemName)
	{
		BulletListener = new GD_Bt_Render();

		mSceneMgr->addRenderQueueListener(BulletListener);

		BulletListener->setDebugMode(BulletListener->getDebugMode()
			| btIDebugDraw::DBG_MAX_DEBUG_DRAW_MODE);

		App->CLSB_Bullet->dynamicsWorld->setDebugDrawer(BulletListener);
	}

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

// *************************************************************************
// *	  						ExitFullScreen							   *
// *************************************************************************
bool SB_Ogre::ExitFullScreen()
{
	//if(Flags[0]->OgreIsRunning==1)
	{

		//App->FullScreen = 0;
		SetParent(App->ViewGLhWnd, App->Equity_Dlg_hWnd);
		SetWindowPos(App->ViewGLhWnd, HWND_TOP, 235, 11, 542, 455, SWP_NOZORDER);
		App->CLSB_Equity->Resize_3DView();

		mWindow->windowMovedOrResized();
		mCamera->setAspectRatio((Ogre::Real)mWindow->getWidth() / (Ogre::Real)mWindow->getHeight());
		mCamera->yaw(Radian(0));
		Root::getSingletonPtr()->renderOneFrame();

		App->CLSB_Scene->FullScreenMode_Flag = 0;
		//App->SBC_Scene->Editor_Mode();

	}
	return 1;
}

// *************************************************************************
// *					Do_Basketball (Terry Bernie)					   *
// *************************************************************************
void SB_Ogre::Do_Basketball()
{
	Ogre::Entity* Object_Ent;
	Ogre::SceneNode* Object_Node;

	Object_Ent = mSceneMgr->createEntity("Ball", "basketball.mesh", App_Resource_Group);
	Object_Node = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	Object_Node->attachObject(Object_Ent);

	Object_Node->setVisible(true);

	//Object_Node->setOrientation(Object->Mesh_Quat);

	Object_Node->setPosition(0,-10,-50);

	AxisAlignedBox worldAAB = Object_Ent->getBoundingBox();
	worldAAB.transformAffine(Object_Node->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btScalar mass;
	mass = 1.0f;
	
	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

	startTransform.setOrigin(initialPosition);

	float Radius = 8;// App->CL_Object->GetMesh_BB_Radius(Object_Node);
	

	btCollisionShape* newRigidShape = new btSphereShape(Radius);
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->CLSB_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	btRigidBody* Phys_Body;

	Phys_Body = new btRigidBody(rbInfo);
	Phys_Body->setRestitution(1.0);
	Phys_Body->setFriction(1.5);
	Phys_Body->setUserPointer(Object_Node);
	Phys_Body->setWorldTransform(startTransform);

	//int f = Phys_Body->getCollisionFlags();
	//Phys_Body->setCollisionFlags(f | btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->CLSB_Bullet->dynamicsWorld->addRigidBody(Phys_Body);

}
