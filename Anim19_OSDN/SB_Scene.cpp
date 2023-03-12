/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Scene.h"


SB_Scene::SB_Scene()
{
	Project_Resource_Group = "Project_Resource_Group";
	
	Scene_Loaded = 0;
	Player_Added = 0;
	Area_Added = 0;
	Camera_Added = 0;

	Player_Count = 0;

	Area_Count = 0;
	UniqueID_Area_Count = 0;

	Object_Count = 0;
	V_Object_Count = 0;

	Camera_Count = 0;
	UniqueID_Camera_Count = 0;

	Counters_Count = 0;
	UniqueID_Counters_Count = 0;

	Project_Resources_Created = 0;

	UniqueID_Object_Counter = 0;

	MessageNew_Count = 0;
	UniqueID_MessageNew_Count = 500;

	CurrentCamMode = 0;
	Scene_Modified = 0;

	Player_Location_Count = 0;
	Locations_ID_Counter = 0;

	GameMode_Flag = 0;
	GameMode_Running_Flag = 0;
	FullScreenMode_Flag = 0;

	B_Player[20] = { nullptr };
	B_Area[20] = { nullptr };
	B_Camera[20] = { nullptr };
	B_Locations[20] = { nullptr };
	B_Counter[20] = { nullptr };

	V_Object.reserve(200);
}


SB_Scene::~SB_Scene()
{

}

// *************************************************************************
// *			Zero_Pointers:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Scene::Zero_Pointers()
{
	int Count = 0;

	Count = 0;
	while (Count < 20)
	{
		B_Player[Count] = NULL;
		B_Area[Count] = NULL;
		B_Camera[Count] = NULL;
		B_Locations[Count] = NULL;
		B_Counter[Count] = NULL;
	
		Count++;
	}
}

// *************************************************************************
// *			Reset_Class:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Scene::Reset_Class()
{
	int i; // Remove Physics Objects
	for (i = App->SBC_Bullet->dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = App->SBC_Bullet->dynamicsWorld->getCollisionObjectArray()[i];
		App->SBC_Bullet->dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	int Count = 0; // Remove Ogre Objects
	while (Count < Object_Count)
	{
		if (V_Object[Count]->Object_Node && V_Object[Count]->Object_Ent)
		{
			V_Object[Count]->Object_Node->detachAllObjects();

			App->CL_Ogre->mSceneMgr->destroySceneNode(V_Object[Count]->Object_Node);

			App->CL_Ogre->mSceneMgr->destroyEntity(V_Object[Count]->Object_Ent);

			V_Object[Count]->Object_Node = NULL;
			V_Object[Count]->Object_Ent = NULL;
		}

		Count++;
	}

	
	// Remove V_Objects
	Count = 0;
	int NumObjects = V_Object.size();

	while (Count < NumObjects)
	{
		delete V_Object[Count];
		Count++;
	}

	V_Object.resize(0);
}

// *************************************************************************
// *			Clear_Level:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
bool SB_Scene::Clear_Level()
{
	App->SBC_Gui_Environ->Reset_Class();
	App->SBC_Project->Reset_Class();
	App->SBC_FileView->Reset_Class();
	App->SBC_TopTabs->Reset_Class();
	App->SBC_Properties->Reset_Class();

	App->SBC_Markers->BoxNode->setVisible(false);
	App->SBC_Markers->Arrow_Node->setVisible(false);

	App->Set_Main_TitleBar(" ");

	
	if (App->SBC_Scene->Scene_Loaded == 1)
	{
		App->SBC_Physics->Enable_Physics(0);

		App->SBC_Player->Reset_Class();

		App->SBC_Com_Area->Reset_Class();

		// Bullet Related
		int i;
		for (i = App->SBC_Bullet->dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = App->SBC_Bullet->dynamicsWorld->getCollisionObjectArray()[i];
			App->SBC_Bullet->dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
	}


	Scene_Modified = 0;

	Reset_Class(); // This One

	App->CL_Ogre->OgreListener->GD_CameraMode = Enums::CamNone;

	App->SBC_Com_Camera->Reset_View();

	Delete_Resources_Group();
	Project_Resources_Created = 0;

	Reset_Counters();

	App->SBC_FileView->SelectItem(App->SBC_FileView->FV_LevelFolder);

	App->CL_Ogre->mSceneMgr->destroyCamera("PlayerRay");
	App->CL_Ogre->mSceneMgr->destroyAllParticleSystems();

	return 1;
}

// *************************************************************************
// *			Reset_Counters:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Scene::Reset_Counters()
{
	Object_Count = 0;
	UniqueID_Object_Counter = 0;

	Camera_Count = 0;
	UniqueID_Camera_Count = 0;

	Counters_Count = 0;
	UniqueID_Counters_Count = 0;

	Project_Resources_Created = 0;

	MessageNew_Count = 0;
	UniqueID_MessageNew_Count = 500;

	CurrentCamMode = 0;
	Scene_Modified = 0;

	Scene_Loaded = 0;

	Player_Location_Count = 0;
	Locations_ID_Counter = 0;
}

// *************************************************************************
// *		Create_Resources_Group:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Scene::Create_Resources_Group()
{
	if (Project_Resources_Created == 0)
	{
		Ogre::ResourceGroupManager::getSingleton().createResourceGroup(Project_Resource_Group);
		Project_Resources_Created = 1;
	}

	return 1;
}

// *************************************************************************
// *		Delete_Resources_Group:- Terry and Hazel Flanigan 2022 		   *
// *************************************************************************
bool SB_Scene::Delete_Resources_Group()
{

	if (Project_Resources_Created == 1)
	{
		Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(Project_Resource_Group);
		Project_Resources_Created = 0;
	}

	return 1;
}

// *************************************************************************
// *	Add_Resource_Location_Project:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
bool SB_Scene::Add_Resource_Location_Project(char* Resource_Location)
{
	bool Test = Ogre::ResourceGroupManager::getSingleton().resourceLocationExists(Resource_Location, Project_Resource_Group);

	if (Test == 0)
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Resource_Location, "FileSystem",Project_Resource_Group);
		Ogre::ResourceGroupManager::getSingleton().clearResourceGroup(Project_Resource_Group);
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(Project_Resource_Group);
	}
	
	return 1;
}

// *************************************************************************
// *				Game_Restart:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_Scene::Game_Restart(void)
{

	App->SBC_Com_Environments->GameMode(0);
	App->SBC_SoundMgr->SoundEngine->stopAllSounds();

	GameMode_Running_Flag = 1;

	App->CL_Ogre->BulletListener->Render_Debug_Flag = 0;

	App->SBC_Grid->Grid_SetVisible(0);
	App->SBC_Grid->Hair_SetVisible(0);
	App->SBC_Markers->Arrow_Node->setVisible(0);

	App->CL_Ogre->OgreListener->GD_Run_Physics = 1;

	CurrentCamMode = App->CL_Ogre->OgreListener->GD_CameraMode;
	App->CL_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;

	App->SBC_Markers->BoxNode->setVisible(false);

	Show_Entities(false); // Hide All Visible Trigers

	SetCursorPos(App->CursorPosX, App->CursorPosY);
	
	if (App->SBC_Front_Dlg->Use_Front_Dlg_Flag == 0)
	{
		SetCapture(App->ViewGLhWnd);// Bernie
		App->CL_Ogre->OgreListener->Pl_LeftMouseDown = 1;
		App->CUR = SetCursor(NULL);
	}

	App->SBC_Physics->Reset_Triggers();

	App->SBC_Com_Environments->GameMode(1);

	return 1;
}

// *************************************************************************
// *				Game_Mode:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Scene::Game_Mode(void)
{
	if (App->SBC_Front_Dlg->Use_Front_Dlg_Flag == 1)
	{
		App->CL_Ogre->OgreListener->Block_Mouse = 1;
		App->SBC_Keyboard->Block_Keyboard = 1;
		App->Block_Mouse_Buttons = 1;
		App->SBC_Front_Dlg->Show_Front_Dlg_Flag = 1;
	}

	GameMode_Running_Flag = 1;

	App->CL_Ogre->BulletListener->Render_Debug_Flag = 0;
	
	App->SBC_Grid->Grid_SetVisible(0);
	App->SBC_Grid->Hair_SetVisible(0);
	App->SBC_Markers->Arrow_Node->setVisible(0);

	
	App->SBC_Com_Environments->GameMode(1);
	

	App->CL_Ogre->OgreListener->GD_Run_Physics = 1;

	CurrentCamMode = App->CL_Ogre->OgreListener->GD_CameraMode;
	App->CL_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;


	App->SBC_Markers->BoxNode->setVisible(false);

	Show_Entities(false); // Hide All Visible Trigers

	SetCursorPos(App->CursorPosX, App->CursorPosY);
	//S_Flags[0]->GameMode = 1;

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(App->ViewGLhWnd,HWND_TOP,0,0,0,0,SWP_NOSIZE|SWP_NOZORDER);
	SetWindowPos(App->ViewGLhWnd, NULL, 0, 0, cx, cy, SWP_NOZORDER);
	SetParent(App->ViewGLhWnd, NULL);

	App->CL_Ogre->mWindow->resize(cx, cy);

	App->CL_Ogre->mWindow->windowMovedOrResized();
	App->CL_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CL_Ogre->mWindow->getWidth() / (Ogre::Real)App->CL_Ogre->mWindow->getHeight());

	Root::getSingletonPtr()->renderOneFrame();

	if (App->SBC_Front_Dlg->Use_Front_Dlg_Flag == 0)
	{
		SetCapture(App->ViewGLhWnd);// Bernie
		App->CL_Ogre->OgreListener->Pl_LeftMouseDown = 1;
		App->CUR = SetCursor(NULL);
	}

	App->SBC_Physics->Reset_Triggers();

	App->SBC_Gui_Dialogs->Show_Physics_Console = 0;

	return 1;
}

// *************************************************************************
// *				Editor_Mode:- Terry and Hazel Flanigan 2022	 	 	   *
// *************************************************************************
bool SB_Scene::Editor_Mode(void)
{
	GameMode_Running_Flag = 0;
	FullScreenMode_Flag = 0;

	App->CL_Ogre->BulletListener->Render_Debug_Flag = 1;

	App->SBC_Grid->Grid_SetVisible(1);
	App->SBC_Grid->Hair_SetVisible(1);

	App->CL_Ogre->OgreListener->Pl_LeftMouseDown = 0;
	ReleaseCapture();
	SetCursor(App->CUR);

	if (App->SBC_Scene->Scene_Loaded == 1)
	{
		App->SBC_Com_Environments->GameMode(0);

		Show_Entities(true); // Show All Visible Trigers

		App->SBC_Physics->Reset_Triggers();
	}


	App->CL_Ogre->OgreListener->GD_CameraMode = CurrentCamMode;
	
	App->CL_Vm_ImGui->Show_FPS = App->SBC_Dialogs->Saved_DoFPS;

	App->SBC_Gui_Dialogs->Show_Physics_Console = 1;
	return 1;
}

// *************************************************************************
// *		Go_FullScreen_Mode:- Terry and Hazel Flanigan 2022		  	   *
// *************************************************************************
void SB_Scene::Go_FullScreen_Mode(void)
{
	FullScreenMode_Flag = 1;

	App->SBC_Scene->CurrentCamMode = App->CL_Ogre->OgreListener->GD_CameraMode;

	App->FullScreen = 1;
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(App->ViewGLhWnd, HWND_TOP, 0, 0, cx, cy, NULL);

	SetParent(App->ViewGLhWnd, NULL);

	App->CL_Ogre->mWindow->resize(cx, cy);

	App->CL_Ogre->mWindow->windowMovedOrResized();
	App->CL_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CL_Ogre->mWindow->getWidth() / (Ogre::Real)App->CL_Ogre->mWindow->getHeight());

	Root::getSingletonPtr()->renderOneFrame();
}

// *************************************************************************
// *			Show_Entities:- Terry and Hazel Flanigan 2022	 	 	   *
// *************************************************************************
bool SB_Scene::Show_Entities(bool YesNo)
{
	int Count = 0;
	while (Count < Object_Count)
	{
		if (V_Object[Count]->Deleted == 0)
		{
			if (V_Object[Count]->Usage == Enums::Usage_Sound)
			{
				V_Object[Count]->Object_Node->setVisible(YesNo);
			}

			if (V_Object[Count]->Usage == Enums::Usage_Message)
			{
				V_Object[Count]->Object_Node->setVisible(YesNo);
			}

			if (V_Object[Count]->Usage == Enums::Usage_Move)
			{
				V_Object[Count]->Object_Node->setVisible(YesNo);
			}

			if (V_Object[Count]->Usage == Enums::Usage_Teleport)
			{
				V_Object[Count]->Object_Node->setVisible(YesNo);
			}

			if (V_Object[Count]->Usage == Enums::Usage_Environment)
			{
				V_Object[Count]->Object_Node->setVisible(YesNo);
			}

			if (V_Object[Count]->Usage == Enums::Usage_EnvironEntity)
			{
				V_Object[Count]->Object_Node->setVisible(YesNo);
			}
		}
		Count++;
	}
	return 1;
}

// *************************************************************************
// *		Set_Object_SizeCounter:- Terry and Hazel Flanigan 2022	  	   *
// *************************************************************************
int SB_Scene::Set_Object_SizeCounter()
{
	V_Object_Count = V_Object.size();
	return V_Object_Count;
}

// *************************************************************************
// *		Get_Object_SizeCounter:- Terry and Hazel Flanigan 2022	  	   *
// *************************************************************************
int SB_Scene::Get_Object_SizeCounter()
{
	V_Object_Count = V_Object.size();
	return V_Object_Count;
}



