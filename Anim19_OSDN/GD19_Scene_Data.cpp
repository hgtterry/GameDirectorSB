#include "StdAfx.h"
#include "resource.h"
#include "GD19_App.h"
#include "GD19_Scene_Data.h"


GD19_Scene_Data::GD19_Scene_Data(void)
{
	Init_Class();
} 


GD19_Scene_Data::~GD19_Scene_Data(void)
{
}

// *************************************************************************
// *	  				Init_Class Terry Bernie							   *
// *************************************************************************
bool GD19_Scene_Data::Init_Class(void)
{
	SceneLoaded = 0;
	Scene_Has_Area = 0;

	S_Flags[0] = NULL;
	S_Scene[0] = NULL;
	S_Camera[0] = NULL;
	S_LoadOptions[0] = NULL;

	Player_Location_Count = 0;
	ObjectCount = 0;
	Stock_Messgae_Count = 0;
	Stock_Sound_Count = 0;

	NewObjectID = 0;
	CurrentCamMode = 0;

	strcpy(mFilename, "No Set");
	strcpy(Path_mFilename, "No Set");

	strcpy(Data_mFilename, "No Set");
	strcpy(Data_Path_mFilename, "No Set");

	Object_ID_Counter = 0;	//Objects 0 to 2000
	Locations_ID_Counter = 2000; //Locations 2000 to 3000
	StockSounds_ID_Counter = 3000; // Stock sounds 3000 to 4000

	return 1;
}

// *************************************************************************
// *	  				Init_Scene Terry Bernie							   *
// *************************************************************************
bool GD19_Scene_Data::Init_Scene(void)
{
	App->Cl_Scene_Data->S_Scene[0] = new Scene_Type();
	App->Cl_Scene_Data->SetScene_Defaults();

	App->Cl_Scene_Data->S_Camera[0] = new Camera_Type();

	App->Cl_Scene_Data->S_LoadOptions[0] = new Load_Options_Type();
	App->Cl_Scene_Data->SetOptions_Defaults();

	App->Cl_Scene_Data->S_Flags[0]  = new Flags_Type();
	SetFlags_Defaults();

	//------------------------ Default Message
	//App->GDCL_Add_NewObject->Add_Stock_Message();
	
	return 1;
}

// *************************************************************************
//					Set_Mesgaes_Defaults Terry Bernie			  		   *
// *************************************************************************
void GD19_Scene_Data::Set_Mesgaes_Defaults(int Index)
{

	strcpy(S_Messages[Index]->Name,"None");
	strcpy(S_Messages[Index]->Default_Text,"Test Text");

	S_Messages[Index]->Font_Size = 48;

	S_Messages[Index]->Colour = Ogre::Vector3(1,1,1);
	S_Messages[Index]->overlay = NULL;
	S_Messages[Index]->panel = NULL;
	S_Messages[Index]->textArea1 = NULL;
	S_Messages[Index]->textArea2 = NULL;
	S_Messages[Index]->Pos_Vert = -20;
	S_Messages[Index]->Pos_Hoz =  -70;
}

// *************************************************************************
//					SetFlags_Defaults Terry Bernie				  		   *
// *************************************************************************
void GD19_Scene_Data::SetFlags_Defaults(void)
{
	S_Flags[0]->GameMode = 0;
}
// *************************************************************************
//					SetObjectDefaults Terry Bernie				  		   *
// *************************************************************************
void GD19_Scene_Data::SetObjectDefaults(int Index)
{

	

	return;
}
// *************************************************************************
//						Set_Move_Defaults Terry Bernie				  	   *
// *************************************************************************
void GD19_Scene_Data::Set_Move_Defaults(int Index)
{
	/*Cl_Object[Index]->S_MoveType->IsNegative = 1;
	Cl_Object[Index]->S_MoveType->Distance = -50;
	Cl_Object[Index]->S_MoveType->Newpos = 0;
	Cl_Object[Index]->S_MoveType->Speed = 10.0;
	Cl_Object[Index]->S_MoveType->WhatDirection = Enums::Axis_x;
	Cl_Object[Index]->S_MoveType->Object_Index = 0;
	Cl_Object[Index]->S_MoveType->Object_ID = 0;
	Cl_Object[Index]->S_MoveType->Triggered = 0;
	Cl_Object[Index]->S_MoveType->Re_Trigger = 0;
	strcpy(Cl_Object[Index]->S_MoveType->Object_Name,"None");*/
	return;
}
// *************************************************************************
// *						SetOptions_Defaults Terry Bernie			   *
// *************************************************************************
void GD19_Scene_Data::SetOptions_Defaults(void)
{
	S_LoadOptions[0]->Has_Player = 0;
	S_LoadOptions[0]->Has_Debug = 0;
	S_LoadOptions[0]->Has_Messages = 0;
	S_LoadOptions[0]->Has_Objects = 0;
	S_LoadOptions[0]->Has_Particles = 0;
	S_LoadOptions[0]->Has_Planes = 0;
	S_LoadOptions[0]->Has_Weapons = 0;
	
}
// *************************************************************************
// *						SetScene_Defaults Terry Bernie				   *
// *************************************************************************
void GD19_Scene_Data::SetScene_Defaults(void)
{
	S_Scene[0]->SceneType = 0;
	S_Scene[0]->LastSceneType = 0;
	S_Scene[0]->PlaneCount=0;

	S_Scene[0]->Fog[0].FogOn = 0;
	S_Scene[0]->Fog[0].Mode = FOG_LINEAR;
	S_Scene[0]->Fog[0].Density = 0.001000;
	S_Scene[0]->Fog[0].Start = 50;
	S_Scene[0]->Fog[0].End = 300;
	S_Scene[0]->Fog[0].Colour = Ogre::Vector3(1,1,1);

	S_Scene[0]->AmbientColour.x = 1;
	S_Scene[0]->AmbientColour.y = 1;
	S_Scene[0]->AmbientColour.z = 1;

	S_Scene[0]->DiffuseColour.x = 0;
	S_Scene[0]->DiffuseColour.y = 0;
	S_Scene[0]->DiffuseColour.z = 0;

	S_Scene[0]->SpecularColour.x = 0;
	S_Scene[0]->SpecularColour.y = 0;
	S_Scene[0]->SpecularColour.z = 0;

	// Sound
	strcpy(S_Scene[0]->Sound[0].SoundFileAndPath,App->SBC_SoundMgr->Default_Folder);
	strcat(S_Scene[0]->Sound[0].SoundFileAndPath,"\\Media\\Sounds\\");
	strcat(S_Scene[0]->Sound[0].SoundFileAndPath,"The_Sun.ogg");
	strcpy(S_Scene[0]->Sound[0].SoundFile,"The_Sun.ogg");

	S_Scene[0]->Sound[0].Volume = 1;
	S_Scene[0]->Sound[0].Loop = 0;
	S_Scene[0]->Sound[0].Is3D = 0;
	S_Scene[0]->Sound[0].Play = 1;
	S_Scene[0]->Sound[0].Pan = 0;
	S_Scene[0]->Sound[0].Data0 = 0;
	S_Scene[0]->Sound[0].Data1 = 0;
	S_Scene[0]->Sound[0].SndFile = NULL;

	// Sky
	S_Scene[0]->Sky[0].Curvature = 15;
	S_Scene[0]->Sky[0].Distance = 4000;
	S_Scene[0]->Sky[0].Enabled = 0;
	strcpy(S_Scene[0]->Sky[0].Material,"Examples/CloudySky");
	S_Scene[0]->Sky[0].Tiling = 15;
	S_Scene[0]->Sky[0].type = 1;
}

// *************************************************************************
//						ClearScene Terry Bernie					  		   *
// *************************************************************************
void GD19_Scene_Data::ClearScene(void)
{
	
	App->Cl_Bullet->GD_Physics_On = 0;
	App->Cl19_Ogre->OgreListener->GD_Run_Physics = 0;
	///App->RedrawWindow_Dlg(App->Physics_Console_Hwnd);

	App->Cl19_Ogre->OgreListener->Dubug_Physics_Draw = 0;


	if (App->Cl19_Ogre->mSceneMgr!=NULL)
	{
		App->Cl19_Ogre->OgreListener->Animate_Ogre = 0;

		if(App->SBC_Scene->Player_Added == 1)
		{
			App->SBC_Scene->Player_Added = 0;
			App->Cl19_Ogre->OgreListener->Animate_State->setEnabled(false);
			App->Cl19_Ogre->OgreListener->Animate_State2->setEnabled(false);
			App->Cl19_Ogre->OgreListener->Animate_State = NULL;
			App->Cl19_Ogre->OgreListener->Animate_State2 = NULL;


			App->SBC_Scene->B_Player[0]->Player_Node->detachAllObjects();  // Remove Player
			App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->SBC_Scene->B_Player[0]->Player_Node);
			App->Cl19_Ogre->mSceneMgr->destroyEntity(App->SBC_Scene->B_Player[0]->Player_Ent);
			App->SBC_Scene->B_Player[0]->Player_Node = NULL;
			App->SBC_Scene->B_Player[0]->Player_Ent = NULL;
		}

		
		App->SBC_Resources->Unload_Materials();
		App->SBC_Resources->Remove_OblectMesh();

	}
	
	 //remove the rigidbodies from the dynamics world and delete them
    int i;
    for (i = App->Cl_Bullet->dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
    {
            btCollisionObject* obj = App->Cl_Bullet->dynamicsWorld->getCollisionObjectArray()[i];
            App->Cl_Bullet->dynamicsWorld->removeCollisionObject( obj );
            delete obj;
    }

	ShowWindow(App->GD_Properties_Hwnd,0);

	int Count = 0;
	while (Count < ObjectCount) // Remove Ogre Objects
	{
		/*if(Cl_Object[Count])
		{
			delete Cl_Object[Count];
			Cl_Object[Count] = NULL;
		}*/

		Count++;
	}

	// Remove Player Locations
	Count = 0;
	while (Count < Player_Location_Count) // Remove Player Locations
	{
		if (S_Player_Locations[Count])
		{
			delete S_Player_Locations[Count];
			S_Player_Locations[Count] = NULL;
		}

		Count++;
	}

	// Remove Sound Stock
	Count = 0;
	while (Count < Stock_Sound_Count) // Remove Player Locations
	{
		if (St_Sounds[Count])
		{
			delete St_Sounds[Count];
			St_Sounds[Count] = NULL;
		}

		Count++;
	}


	App->SBC_SoundMgr->Sound_File.resize(0);
	App->SBC_SoundMgr->Sound_File.shrink_to_fit();
	App->SBC_SoundMgr->SoundFile_Count = 0;

	
	//App->GDCL_Scene_Data->Init_Class();
	Scene_Has_Area = 0;
	Object_ID_Counter = 0;
	Locations_ID_Counter = 2000;
	StockSounds_ID_Counter = 3000;

	Player_Location_Count = 0;
	Stock_Sound_Count = 0;
	ObjectCount = 0;

	SceneLoaded = 0;

	App->SBC_FileView->Delete_AllItems();
}

// *************************************************************************
// *					 	GameMode(Terry Bernie)			 		 	   *
// *************************************************************************
bool GD19_Scene_Data::GameMode(void)
{
	App->Cl_Grid->Grid_SetVisible(0);
	App->Cl_Grid->Hair_SetVisible(0);

	App->Cl_Grid->Arrow_Node->setVisible(0);

	///App->Cl19_Ogre->textArea->hide();

	if (S_Scene[0]->Sound[0].Play == 1)
	{
		int result = 1;
		result = strcmp(S_Scene[0]->Sound[0].SoundFile, "None");
		if (result == 1) // Could be Unsafe 
		{
			S_Scene[0]->Sound[0].SndFile = App->SBC_SoundMgr->SoundEngine->play2D(S_Scene[0]->Sound[0].SoundFileAndPath,
				S_Scene[0]->Sound[0].Loop,true,true);

			S_Scene[0]->Sound[0].SndFile->setVolume(S_Scene[0]->Sound[0].Volume);
			S_Scene[0]->Sound[0].SndFile->setIsPaused(false);
		}
	}

	CurrentCamMode = App->Cl19_Ogre->OgreListener->GD_CameraMode;
	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;
	

	App->Cl_Visuals->BoxNode->setVisible(false);

	App->Cl19_Ogre->OgreListener->Dubug_Physics_Draw = 0;

	Show_Entities(false); // Hide All Visible Trigers

	SetCursorPos(500,500);
	S_Flags[0]->GameMode = 1;

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	//SetWindowPos(App->ViewGLhWnd,HWND_TOP,0,0,0,0,SWP_NOSIZE|SWP_NOZORDER);
	SetWindowPos(App->ViewGLhWnd, NULL, 0, 0, cx,cy, SWP_NOZORDER);
	SetParent(App->ViewGLhWnd,NULL);

	App->Cl19_Ogre->mWindow->resize(cx,cy);

	App->Cl19_Ogre->mWindow->windowMovedOrResized();
	App->Cl19_Ogre->mCamera->setAspectRatio((Ogre::Real)App->Cl19_Ogre->mWindow->getWidth() / (Ogre::Real)App->Cl19_Ogre->mWindow->getHeight());

	Root::getSingletonPtr()->renderOneFrame(); 

	SetCapture(App->ViewGLhWnd);// Bernie
	App->Cl19_Ogre->OgreListener->Pl_LeftMouseDown = 1;
	
	App->CUR = SetCursor(NULL);

	Reset_Triggers();
	
	return 1;
}
// *************************************************************************
// *					 	EditorMode(Terry Bernie)			 	 	   *
// *************************************************************************
bool GD19_Scene_Data::EditorMode(void)
{
	App->Cl_Grid->Grid_SetVisible(1);
	App->Cl_Grid->Hair_SetVisible(1);

	// App->Cl19_Ogre->OgreListener->showDebugOverlay(1);

	if (S_Scene[0]->Sound[0].SndFile == NULL)
	{
	}
	else
	{
		S_Scene[0]->Sound[0].SndFile->setIsPaused(true);
		S_Scene[0]->Sound[0].SndFile->drop();
		S_Scene[0]->Sound[0].SndFile = NULL;
	}

	S_Flags[0]->GameMode = 0;
	App->Cl19_Ogre->OgreListener->Pl_LeftMouseDown = 0;
	ReleaseCapture();
	SetCursor(App->CUR);

	/*App->Select_C->BoxNode->setVisible(true);
	App->Select_C->Gizmo->setVisible(true);*/

	App->Cl19_Ogre->OgreListener->Dubug_Physics_Draw = 1;
	Show_Entities(true); // Show All Visible Trigers

	App->Cl19_Ogre->OgreListener->GD_CameraMode = CurrentCamMode;
	
	App->Cl_Visuals->BoxNode->setVisible(true);
	App->Cl_Grid->Arrow_Node->setVisible(true);

	///if (App->Cl19_Ogre->OgreListener->Show_Camara_Positions == 1)
	{
		///App->Cl19_Ogre->textArea->show();
	}
	///else
	{
		///App->Cl19_Ogre->textArea->hide();
	}

	Reset_Triggers();
	return 1;
}

// *************************************************************************
// *					 Show_Entities(Terry Bernie)			 	 	   *
// *************************************************************************
bool GD19_Scene_Data::Show_Entities(bool YesNo)
{
	/*int Count = 0;
	while (Count < ObjectCount)
	{
		if (Cl_Object[Count]->Deleted == 0)
		{
			if (Cl_Object[Count]->Usage == Enums::Usage_Sound)
			{
				Cl_Object[Count]->OgreNode->setVisible(YesNo);
			}
			if (Cl_Object[Count]->Usage == Enums::Usage_Message)
			{
				Cl_Object[Count]->OgreNode->setVisible(YesNo);
			}
			if (Cl_Object[Count]->Usage == Enums::Usage_Move)
			{
				Cl_Object[Count]->OgreNode->setVisible(YesNo);
			}
			if (Cl_Object[Count]->Usage == Enums::Usage_Teleport)
			{
				Cl_Object[Count]->OgreNode->setVisible(YesNo);
			}
			if (Cl_Object[Count]->Usage == Enums::Usage_Environment)
			{
				Cl_Object[Count]->OgreNode->setVisible(YesNo);
			}
		}
		Count++;
	}*/
	return 1;
}

// *************************************************************************
// *	  			Is_Meshes_Used Terry Bernie							   *
// *************************************************************************
bool GD19_Scene_Data::Is_Meshes_Used(char* Name)
{
	//int Count = 0;
	//int Total = ObjectCount;

	//if (strcmp(Name, "Sinbad.mesh") == 0) // Needs to be Actual Player Mesh
	//{
	//	return 1;
	//}

	//while (Count < Total)
	//{
	//	if (Cl_Object[Count]->Deleted == 0)
	//	{
	//		int Result = 1;
	//		Result = strcmp(Cl_Object[Count]->MeshName, Name);
	//		if (Result == 0)
	//		{
	//			return 1;
	//		}
	//	}

	//	Count++;
	//}

	return 0;
}

// *************************************************************************
// *	  			GetJustIndex_ByName Terry Bernie					   *
// *************************************************************************
int GD19_Scene_Data::GetJustIndex_ByName(char* Name)
{
	/*int Count=0;
	int Total = ObjectCount;

	while (Count < Total)
	{
		if(Cl_Object[Count]->Deleted==0)
		{
			int Result=1;
			Result=strcmp(Cl_Object[Count]->Name,Name);
			if (Result==0)
			{
				return Count;
			}
		}

		Count++;
	}*/

	return -1;
}

// *************************************************************************
// *	  				Reset_Triggers Terry Bernie						   *
// *************************************************************************
void GD19_Scene_Data::Reset_Triggers(void)
{
	/*Ogre::Vector3 M_Pos;
	Ogre::Vector3 P_Pos;
	
	int Count=0;
	int Total = ObjectCount;

	while (Count < Total)
	{
		if(Cl_Object[Count]->Deleted == 0)
		{
			if (Cl_Object[Count]->Usage == Enums::Usage_Move)
			{
				int ObjectToMove = Cl_Object[Count]->S_MoveType->Object_Index;

				M_Pos = Cl_Object[ObjectToMove]->Mesh_Pos;
				P_Pos = Cl_Object[ObjectToMove]->Physics_Pos;
				
				Cl_Object[Count]->S_MoveType->MeshPos  = Ogre::Vector3(M_Pos);
				Cl_Object[Count]->S_MoveType->PhysicsPos = Ogre::Vector3(P_Pos);

				Cl_Object[ObjectToMove]->OgreNode->setPosition(M_Pos);
				Cl_Object[ObjectToMove]->bt_body->getWorldTransform().setOrigin(btVector3(P_Pos.x,P_Pos.y,P_Pos.z));

				Cl_Object[Count]->Triggered = 0;
			}

			if (Cl_Object[Count]->Usage == Enums::Usage_Colectable)
			{
				Cl_Object[Count]->OgreEntity->setVisible(TRUE);
				
				Cl_Object[Count]->OgreNode->setPosition(Cl_Object[Count]->Mesh_Pos);

				P_Pos = Cl_Object[Count]->Physics_Pos;
				Cl_Object[Count]->bt_body->getWorldTransform().setOrigin(btVector3(P_Pos.x, P_Pos.y, P_Pos.z));

				Cl_Object[Count]->Triggered = 0;
			}
		}

		Count++;
	}*/
}

// *************************************************************************
//						Start_Scene Terry Bernie						   *
// *************************************************************************
bool GD19_Scene_Data::Start_Scene()
{
	// ------------------------------ Things needed
//	App->Cl_Visuals->MarkerBB_Setup();
//	// --------------------------------------------
//
//	int Index = ObjectCount;
//
//	Cl_Object[Index] = new GD19_Objects();
//	
//	strcpy(Cl_Object[Index]->MeshName,"RF_Level1.mesh");
//
//	Cl_Object[Index]->OgreEntity = App->Cl19_Ogre->mSceneMgr->createEntity("Start_Room","RF_Level1.mesh",App->Cl19_Ogre->App_Resource_Group);
//	Cl_Object[Index]->OgreNode = App->Cl19_Ogre->mSceneMgr->getRootSceneNode()->createChildSceneNode();
//	Cl_Object[Index]->OgreNode->attachObject(Cl_Object[Index]->OgreEntity);
//	
//	Cl_Object[Index]->OgreNode->setVisible(true);
//	Cl_Object[Index]->OgreNode->setScale(Cl_Object[Index]->Mesh_Scale);
//	Cl_Object[Index]->OgreNode->setPosition(57.000000, -47.000000, -107.000000);
//
//	Cl_Object[Index]->Mesh_Pos = Ogre::Vector3(57.000000, -47.000000, -107.000000);
//
//	strcpy(Cl_Object[Index]->Name,"Main_Room2");
//
//	//App->SBC_Player->SetUp();
//	
//	App->Cl19_Ogre->OgreListener->Dubug_Physics_Draw = 1;
//
//	App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
//
//	
//	App->Cl_SoundMgr->SndFile = App->Cl_SoundMgr->SoundEngine->play2D("Media\\Sounds\\Welcome.ogg",false,true,true);
//	App->Cl_SoundMgr->SndFile->setVolume(App->Cl_SoundMgr->SndVolume);
//	App->Cl_SoundMgr->SndFile->setIsPaused(false);
//
//	S_LoadOptions[0]->Has_Objects = 1;
//	S_LoadOptions[0]->Has_Player = 1;
//
//	
//
//	SceneLoaded = 1;
//
//	ObjectCount++;  // Must be last line
//	
//	
//	//App->Cl_Object_Props->Update_Properties_Mesh();
//
////	App->SBC_Objects_New->Add_Stock_Message();
//	//App->CL10_Objects_New->Add_Stock_Sound();
////	App->SBC_Objects_New->Add_Stock_Panel();
//	
//	Start_UpScene();
//	
//	//App->Cl_Load_Scene->OpenScene(0);
//	
//	//ShowWindow(App->GD_Properties_Hwnd,1);

	return 1;

}

// *************************************************************************
//							Start_UpScene Terry Bernie					   *
// *************************************************************************
bool GD19_Scene_Data::Start_UpScene()
{
	/*char StartFile[1024];
	strcpy(StartFile, App->EquityDirecory_FullPath);
	strcat(StartFile, "\\");
	strcat(StartFile, "Data\\StartUp.gcf");

	App->Cl_Ini->SetPathName(StartFile);

	char Check[1024];
	App->Cl_Ini->GetPathName(Check, 1024);


	bool Default = App->Cl_Ini->GetBool("Startup", "Default", 1);
	if (Default == 1)
	{
		char FileName[255];
		char ParhFile[255];
		strcpy(FileName, "StartLevel_40.GDScene");

		strcpy(ParhFile, App->EquityDirecory_FullPath);
		strcat(ParhFile, "\\");
		strcat(ParhFile, "Media\\Levels\\StartLevel_40.GDScene");

		strcpy(App->CL_Vm_FileIO->Scene_FileName, FileName);
		strcpy(App->CL_Vm_FileIO->Scene_Path_FileName, ParhFile);
		return 1;
	}
	else
	{
		App->Cl_Ini->GetString("Startup", "Scene_FileName", App->CL_Vm_FileIO->Scene_FileName,1024);
		App->Cl_Ini->GetString("Startup", "Scene_Path_FileName", App->CL_Vm_FileIO->Scene_Path_FileName,1024);
		return 1;
	}*/


	return 0;
}

// *************************************************************************
// *					Open_Project_Dlg Terry Bernie					   *
// *************************************************************************
bool GD19_Scene_Data::Open_Project_Dlg(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(mFilename, "");
	strcpy(Path_mFilename, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Path_mFilename;						// full path and file name
	ofn.nMaxFile = sizeof(Path_mFilename);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = mFilename;						// Just File Name
	ofn.nMaxFileTitle = sizeof(mFilename);
	ofn.lpstrInitialDir = "";
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		strcpy(Data_mFilename, mFilename);
		strcpy(Data_Path_mFilename, Path_mFilename);
		return 1;
	}
	return 0;
}

// *************************************************************************
//							Start_UpScene Terry Bernie					   *
// *************************************************************************
bool GD19_Scene_Data::Get_UserFile()
{
	bool test = Open_Project_Dlg("Scene File   *.GDScene\0*.GDScene\0", "Scene File", NULL);
	if (test == 0)
	{
		return 0;
	}
	return 1;
}

// *************************************************************************
// *	  					 Dialog_GetUserFile Terry Bernie			   *
// *************************************************************************
bool GD19_Scene_Data::Dialog_GetUserFile(HWND Parent)
{
	DialogBox(App->hInst, (LPCTSTR)IDD_STARTUP, Parent, (DLGPROC)Dialog_GetUserFile_Proc);
	return 1;
}
// *************************************************************************
// *						Dialog_GetUserFile_Proc	  					   *
// *************************************************************************
LRESULT CALLBACK GD19_Scene_Data::Dialog_GetUserFile_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

	
		HFONT Font2;
		Font2 = CreateFont(-20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");

		SendDlgItemMessage(hDlg, IDC_CKDEFAULT, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTAGFILE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_CHECKYES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		
		char StartFile[1024];
		strcpy(StartFile, App->EquityDirecory_FullPath);
		strcat(StartFile, "\\");
		strcat(StartFile, "Data\\StartUp.gcf");

		App->Cl_Ini->SetPathName(StartFile);

		bool Default = App->Cl_Ini->GetBool("Startup", "Default", 1);
		if (Default == 1)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CKDEFAULT);
			SendMessage(temp, BM_SETCHECK, 1, 0);
			EnableWindow(GetDlgItem(hDlg, IDC_STUSERFILE), 0);
			EnableWindow(GetDlgItem(hDlg, IDC_BTBROWSE), 0);
		}
		else
		{
			HWND temp = GetDlgItem(hDlg, IDC_CKDEFAULT);
			SendMessage(temp, BM_SETCHECK, 0, 0);
			EnableWindow(GetDlgItem(hDlg, IDC_STUSERFILE), 1);
			EnableWindow(GetDlgItem(hDlg, IDC_BTBROWSE), 1);
		}

		char buff[1024];
		App->Cl_Ini->GetString("Startup", "Scene_Path_FileName",buff,1024);
		SetDlgItemText(hDlg, IDC_STUSERFILE, (LPTSTR)buff);
		strcpy(App->Cl_Scene_Data->Data_Path_mFilename,buff);

		App->Cl_Ini->GetString("Startup", "Scene_FileName", buff, 1024);
		strcpy(App->Cl_Scene_Data->Data_mFilename, buff);
		

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{

		if (GetDlgItem(hDlg, IDC_STUSERFILE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		if (GetDlgItem(hDlg, IDC_CKDEFAULT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		if (GetDlgItem(hDlg, IDC_STTAGFILE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}


	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BTBROWSE)
		{
			bool test = App->Cl_Scene_Data->Open_Project_Dlg("Project   *.SBProj\0*.SBProj\0", "Project File", NULL);
			if (test == 0)
			{
				return 0;
			}
			
			SetDlgItemText(hDlg, IDC_STUSERFILE, (LPTSTR)App->Cl_Scene_Data->Path_mFilename);
			return 1;
			
		}
		if (LOWORD(wParam) == IDC_CKDEFAULT)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CKDEFAULT);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				SetDlgItemText(hDlg, IDC_STUSERFILE, (LPTSTR)App->Default_Project);
				EnableWindow(GetDlgItem(hDlg, IDC_STUSERFILE), 0);
				EnableWindow(GetDlgItem(hDlg, IDC_BTBROWSE), 0);
				return 1;
			}
			else
			{
				EnableWindow(GetDlgItem(hDlg, IDC_STUSERFILE), 1);
				EnableWindow(GetDlgItem(hDlg, IDC_BTBROWSE), 1);
				return 1;
			}

			return 1;
		}

		if (LOWORD(wParam) == IDOK)
		{
			bool test2 = 0;
			HWND temp = GetDlgItem(hDlg, IDC_CKDEFAULT);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				test2 = App->Cl_Ini->WriteBool("Startup", "Default", 1);
				if (test2 == 0)
				{
					App->Say("Error Writing 1");
				}

				test2 = App->Cl_Ini->WriteString("Startup", "Scene_Path_FileName", App->Default_Project);
				SetDlgItemText(hDlg, IDC_STUSERFILE, (LPTSTR)App->Default_Project);
				if (test2 == 0)
				{
					App->Say("Error Writing 1");
				}

			}
			else
			{
				test2 = App->Cl_Ini->WriteBool("Startup", "Default",0);
				if (test2 == 0)
				{
					App->Say("Error Writing 2");
				}
		
				test2 = App->Cl_Ini->WriteString("Startup", "Scene_FileName", App->Cl_Scene_Data->Data_mFilename);
				if (test2 == 0)
				{
					App->Say("Error Writing 3");
				}

				test2 = App->Cl_Ini->WriteString("Startup", "Scene_Path_FileName", App->Cl_Scene_Data->Data_Path_mFilename);
				if (test2 == 0)
				{
					App->Say("Error Writing 4");
				}
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;

	}
	return FALSE;
}

// *************************************************************************
// *					 Delete_Object(Terry Bernie)			 	 	   *
// *************************************************************************
bool GD19_Scene_Data::Delete_Object(int Index)
{
	//Cl_Object[Index]->OgreNode->setVisible(false);

	///*App->GDCL_Scene_Data->CL_Object[Index]->OgreNode->detachAllObjects();
	//App->Cl_Ogre->mSceneMgr->destroySceneNode(App->GDCL_Scene_Data->CL_Object[Index]->OgreNode);
	//App->Cl_Ogre->mSceneMgr->destroyEntity(App->GDCL_Scene_Data->CL_Object[Index]->OgreEntity);

	//App->GDCL_Scene_Data->CL_Object[Index]->OgreEntity = 0;
	//App->GDCL_Scene_Data->CL_Object[Index]->OgreNode = 0;*/

	//App->Cl_Bullet->dynamicsWorld->removeRigidBody(Cl_Object[Index]->bt_body);
	//Cl_Object[Index]->bt_body = 0;
	
	return 1;
}
