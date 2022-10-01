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

	CurrentCamMode = 0;

	SBC_Base_Player[100] = { nullptr };
	SBC_Base_Area[100] = { nullptr };
	SBC_Base_Area[0] = nullptr;
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

	Player_Count = 0;
	Area_Count = 0;
	Camera_Count = 0;
	Object_Count = 0;
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

	App->Cl_Scene_Data->ObjectCount = 0;

	Reset_Class(); // This One
	
	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamNone;

	App->SBC_Camera->Reset_View();

	Delete_Resources_Group();

	App->SBC_FileView->SelectItem(App->SBC_FileView->FV_LevelFolder);

	return 1;
}

// *************************************************************************
// *					Create_Resources_Group	Terry Bernie 		 	   *
// *************************************************************************
bool SB_Scene::Create_Resources_Group()
{
	//bool Test = Ogre::ResourceGroupManager::getSingleton().resourceGroupExists(Project_Resource_Group);

	//if (Test == 0)
	{
		Ogre::ResourceGroupManager::getSingleton().createResourceGroup(Project_Resource_Group);
		//Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(Project_Resource_Group);
		App->Say("Resouce Group Created");
	}

	return 1;
}

// *************************************************************************
// *					Delete_Resources_Group	Terry Bernie 		 	   *
// *************************************************************************
bool SB_Scene::Delete_Resources_Group()
{

	bool Test = Ogre::ResourceGroupManager::getSingleton().resourceGroupExists(Project_Resource_Group);

	if (Test == 1)
	{
		Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(Project_Resource_Group);
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
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Resource_Location, "FileSystem", Project_Resource_Group);
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

	//if (S_Scene[0]->Sound[0].Play == 1)
	//{
	//	int result = 1;
	//	result = strcmp(S_Scene[0]->Sound[0].SoundFile, "None");
	//	if (result == 1) // Could be Unsafe 
	//	{
	//		S_Scene[0]->Sound[0].SndFile = App->Cl_SoundMgr->SoundEngine->play2D(S_Scene[0]->Sound[0].SoundFileAndPath,
	//			S_Scene[0]->Sound[0].Loop, true, true);

	//		S_Scene[0]->Sound[0].SndFile->setVolume(S_Scene[0]->Sound[0].Volume);
	//		S_Scene[0]->Sound[0].SndFile->setIsPaused(false);
	//	}
	//}

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
	//App->Cl19_Ogre->OgreListener->Pl_LeftMouseDown = 1;

	//App->CUR = SetCursor(NULL);

	//Reset_Triggers();

	return 1;
}
// *************************************************************************
// *				Editor_Mode:- Terry and Hazel Flanigan 2022	 	 	   *
// *************************************************************************
bool SB_Scene::Editor_Mode(void)
{
	App->Cl_Grid->Grid_SetVisible(1);
	App->Cl_Grid->Hair_SetVisible(1);

	// App->Cl19_Ogre->OgreListener->showDebugOverlay(1);

	//if (S_Scene[0]->Sound[0].SndFile == NULL)
	//{
	//}
	//else
	//{
	//	S_Scene[0]->Sound[0].SndFile->setIsPaused(true);
	//	S_Scene[0]->Sound[0].SndFile->drop();
	//	S_Scene[0]->Sound[0].SndFile = NULL;
	//}

	//S_Flags[0]->GameMode = 0;
	//App->Cl19_Ogre->OgreListener->Pl_LeftMouseDown = 0;
	//ReleaseCapture();
	//SetCursor(App->CUR);

	///*App->Select_C->BoxNode->setVisible(true);
	//App->Select_C->Gizmo->setVisible(true);*/

	//App->Cl19_Ogre->OgreListener->GD_Dubug_Physics = 1;
	//Show_Entities(true); // Show All Visible Trigers

	//App->Cl19_Ogre->OgreListener->GD_CameraMode = CurrentCamMode;

	//App->Cl_Visuals->BoxNode->setVisible(true);
	//App->Cl_Grid->Arrow_Node->setVisible(true);

	////if (App->Cl19_Ogre->OgreListener->Show_Camara_Positions == 1)
	//{
	//	//App->Cl19_Ogre->textArea->show();
	//}
	////else
	//{
	//	//App->Cl19_Ogre->textArea->hide();
	//}

	//Reset_Triggers();
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



