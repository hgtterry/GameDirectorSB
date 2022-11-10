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
	Object_Count = 0;
	Camera_Count = 0;
	Entity_Count = 0;

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

	B_Player[100] = { nullptr };
	B_Area[100] = { nullptr };
	B_Area[0] = nullptr;
}


SB_Scene::~SB_Scene()
{

}

// *************************************************************************
// *						Reset_Class Terry Flanigan					   *
// *************************************************************************
void SB_Scene::Reset_Class()
{
	int i; // Remove Physics Objects
	for (i = App->Cl_Bullet->dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
	{
		btCollisionObject* obj = App->Cl_Bullet->dynamicsWorld->getCollisionObjectArray()[i];
		App->Cl_Bullet->dynamicsWorld->removeCollisionObject(obj);
		delete obj;
	}

	int Count = 0; // Remove Ogre Objects
	while (Count < Object_Count) 
	{
		if (B_Object[Count]->Object_Node && B_Object[Count]->Object_Ent)
		{
			B_Object[Count]->Object_Node->detachAllObjects();

			App->Cl19_Ogre->mSceneMgr->destroySceneNode(B_Object[Count]->Object_Node);

			App->Cl19_Ogre->mSceneMgr->destroyEntity(B_Object[Count]->Object_Ent);

			B_Object[Count]->Object_Node = NULL;
			B_Object[Count]->Object_Ent = NULL;
		}

		Count++;
	}

	Count = 0; // Remove Object Classes
	while (Count < Object_Count)
	{
		if (B_Object[Count])
		{
			delete B_Object[Count];
			B_Object[Count] = NULL;
		}

		Count++;
	}

	// Zero Counters
	Scene_Loaded = 0;
	Area_Added = 0;
	Player_Added = 0;
	Camera_Added = 0;

	Counters_Count = 0;
	UniqueID_Counters_Count = 0;

	Object_Count = 0;
	UniqueID_Object_Counter = 0;

	MessageNew_Count = 0;
	UniqueID_MessageNew_Count = 500;

	Player_Count = 0;
	Area_Count = 0;
	Camera_Count = 0;
}

// *************************************************************************
// *						Clear_Level Terry Flanigan					   *
// *************************************************************************
bool SB_Scene::Clear_Level()
{

	App->SBC_Project->Reset_Class();
	App->SBC_FileView->Reset_Class();
	App->SBC_TopTabs->Reset_Class();
	App->SBC_Properties->Reset_Class();

	App->Set_Main_TitleBar(" ");

	if (App->SBC_Scene->Scene_Loaded == 1)
	{
		App->SBC_Physics->Enable_Physics(0);

		App->SBC_Player->Reset_Class();
		App->SBC_Aera->Reset_Class();


		// Bullet Related
		int i;
		for (i = App->Cl_Bullet->dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--)
		{
			btCollisionObject* obj = App->Cl_Bullet->dynamicsWorld->getCollisionObjectArray()[i];
			App->Cl_Bullet->dynamicsWorld->removeCollisionObject(obj);
			delete obj;
		}
	}

	Scene_Modified = 0;

	Reset_Class(); // This One

	UniqueID_Object_Counter = 0;
	Object_Count = 0;
	
	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamNone;

	App->SBC_Camera->Reset_View();

	Delete_Resources_Group();
	Project_Resources_Created = 0;

	App->SBC_FileView->SelectItem(App->SBC_FileView->FV_LevelFolder);

	return 1;
}

// *************************************************************************
// *					Create_Resources_Group	Terry Bernie 		 	   *
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
// *					Delete_Resources_Group	Terry Bernie 		 	   *
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
// *				Game_Mode:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Scene::Game_Mode(void)
{
	App->Cl_Grid->Grid_SetVisible(0);
	App->Cl_Grid->Hair_SetVisible(0);
	App->Cl_Grid->Arrow_Node->setVisible(0);

	////App->Cl19_Ogre->textArea->hide();

	if (App->SBC_Scene->B_Area[0]->S_Environment[0]->Play == 1)
	{
		int result = 1;
		result = strcmp(App->SBC_Scene->B_Area[0]->S_Environment[0]->Sound_File, "None");
		if (result == 1) // Could be Unsafe 
		{
			char buff[1024];
			strcpy(buff, App->SBC_SoundMgr->Default_Folder);
			strcat(buff, "\\Media\\Sounds\\");

			strcat(buff, App->SBC_Scene->B_Area[0]->S_Environment[0]->Sound_File);

			App->SBC_Scene->B_Area[0]->S_Environment[0]->SndFile = App->SBC_SoundMgr->SoundEngine->play2D(buff, App->SBC_Scene->B_Area[0]->S_Environment[0]->Loop, true, true);

			App->SBC_Scene->B_Area[0]->S_Environment[0]->SndFile->setVolume(App->SBC_Scene->B_Area[0]->S_Environment[0]->SndVolume);
			App->SBC_Scene->B_Area[0]->S_Environment[0]->SndFile->setIsPaused(false);
		}
	}

	App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;

	CurrentCamMode = App->Cl19_Ogre->OgreListener->GD_CameraMode;
	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;


	App->Cl_Visuals->BoxNode->setVisible(false);

	//App->Cl19_Ogre->OgreListener->GD_Dubug_Physics = 0;

	Show_Entities(false); // Hide All Visible Trigers

	SetCursorPos(500, 500);
	//S_Flags[0]->GameMode = 1;

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(App->ViewGLhWnd,HWND_TOP,0,0,0,0,SWP_NOSIZE|SWP_NOZORDER);
	SetWindowPos(App->ViewGLhWnd, NULL, 0, 0, cx, cy, SWP_NOZORDER);
	SetParent(App->ViewGLhWnd, NULL);

	App->Cl19_Ogre->mWindow->resize(cx, cy);

	App->Cl19_Ogre->mWindow->windowMovedOrResized();
	App->Cl19_Ogre->mCamera->setAspectRatio((Ogre::Real)App->Cl19_Ogre->mWindow->getWidth() / (Ogre::Real)App->Cl19_Ogre->mWindow->getHeight());

	Root::getSingletonPtr()->renderOneFrame();

	SetCapture(App->ViewGLhWnd);// Bernie

	App->Cl19_Ogre->OgreListener->Pl_LeftMouseDown = 1;

	App->CUR = SetCursor(NULL);

	App->SBC_Physics->Reset_Triggers();

	return 1;
}
// *************************************************************************
// *				Editor_Mode:- Terry and Hazel Flanigan 2022	 	 	   *
// *************************************************************************
bool SB_Scene::Editor_Mode(void)
{
	App->Cl_Grid->Grid_SetVisible(1);
	App->Cl_Grid->Hair_SetVisible(1);

	App->Cl19_Ogre->OgreListener->Pl_LeftMouseDown = 0;
	ReleaseCapture();
	SetCursor(App->CUR);

	if (App->SBC_Scene->Scene_Loaded == 1)
	{
		if (App->SBC_Scene->B_Area[0]->S_Environment[0]->SndFile == NULL)
		{
		}
		else
		{
			App->SBC_Scene->B_Area[0]->S_Environment[0]->SndFile->setIsPaused(true);
			App->SBC_Scene->B_Area[0]->S_Environment[0]->SndFile->drop();
			App->SBC_Scene->B_Area[0]->S_Environment[0]->SndFile = NULL;
		}

		Show_Entities(true); // Show All Visible Trigers

		App->SBC_Physics->Reset_Triggers();
	}


	App->Cl19_Ogre->OgreListener->GD_CameraMode = CurrentCamMode;

	return 1;
}

// *************************************************************************
// *			Show_Entities:- Terry and Hazel Flanigan 2022	 	 	   *
// *************************************************************************
bool SB_Scene::Show_Entities(bool YesNo)
{
	int Count = 0;
	while (Count < Object_Count)
	{
		if (B_Object[Count]->Deleted == 0)
		{
			if (B_Object[Count]->Usage == Enums::Usage_Sound)
			{
				B_Object[Count]->Object_Node->setVisible(YesNo);
			}
			if (B_Object[Count]->Usage == Enums::Usage_Message)
			{
				B_Object[Count]->Object_Node->setVisible(YesNo);
			}
			if (B_Object[Count]->Usage == Enums::Usage_Move)
			{
				B_Object[Count]->Object_Node->setVisible(YesNo);
			}
			if (B_Object[Count]->Usage == Enums::Usage_Teleport)
			{
				B_Object[Count]->Object_Node->setVisible(YesNo);
			}
			if (B_Object[Count]->Usage == Enums::Usage_Environment)
			{
				B_Object[Count]->Object_Node->setVisible(YesNo);
			}
		}
		Count++;
	}
	return 1;
}



