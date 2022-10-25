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

	S_LoadOptions[0] = NULL;

	Player_Location_Count = 0;
	Stock_Messgae_Count = 0;
	Stock_Sound_Count = 0;

	NewObjectID = 0;
	CurrentCamMode = 0;

	strcpy(mFilename, "No Set");
	strcpy(Path_mFilename, "No Set");

	strcpy(Data_mFilename, "No Set");
	strcpy(Data_Path_mFilename, "No Set");

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

	App->Cl_Scene_Data->S_LoadOptions[0] = new Load_Options_Type();
	App->Cl_Scene_Data->SetOptions_Defaults();

	App->Cl_Scene_Data->S_Flags[0]  = new Flags_Type();
	SetFlags_Defaults();

	//------------------------ Default Message
	//App->GDCL_Add_NewObject->Add_Stock_Message();
	
	return 1;
}

// *************************************************************************
//					SetFlags_Defaults Terry Bernie				  		   *
// *************************************************************************
void GD19_Scene_Data::SetFlags_Defaults(void)
{
	S_Flags[0]->GameMode = 0;
}

// *************************************************************************
//						Set_Move_Defaults Terry Bernie				  	   *
// *************************************************************************
void GD19_Scene_Data::Set_Move_Defaults(int Index)
{
	App->SBC_Scene->B_Object[Index]->S_MoveType[0]->IsNegative = 1;
	App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Move_Distance = -50;
	App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Newpos = 0;
	App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Speed = 10.0;
	App->SBC_Scene->B_Object[Index]->S_MoveType[0]->WhatDirection = Enums::Axis_x;
	App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Object_Index = 0;
	App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Object_ID = 0;
	App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Triggered = 0;
	App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Re_Trigger = 0;
	strcpy(App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Object_Name,"None");
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
// *	  				Reset_Triggers Terry Bernie						   *
// *************************************************************************
void GD19_Scene_Data::Reset_Triggers(void)
{
	Ogre::Vector3 M_Pos;
	Ogre::Vector3 P_Pos;
	
	int Count=0;
	int Total = App->SBC_Scene->Object_Count;

	while (Count < Total)
	{
		if(App->SBC_Scene->B_Object[Count]->Deleted == 0)
		{
			if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Move)
			{
				int ObjectToMove = App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Object_Index;

				M_Pos = App->SBC_Scene->B_Object[ObjectToMove]->Mesh_Pos;
				P_Pos = App->SBC_Scene->B_Object[ObjectToMove]->Physics_Pos;
				
				App->SBC_Scene->B_Object[Count]->S_MoveType[0]->MeshPos  = Ogre::Vector3(M_Pos);
				App->SBC_Scene->B_Object[Count]->S_MoveType[0]->PhysicsPos = Ogre::Vector3(P_Pos);

				App->SBC_Scene->B_Object[ObjectToMove]->Object_Node->setPosition(M_Pos);
				App->SBC_Scene->B_Object[ObjectToMove]->Phys_Body->getWorldTransform().setOrigin(btVector3(P_Pos.x,P_Pos.y,P_Pos.z));

				App->SBC_Scene->B_Object[Count]->Triggered = 0;
			}

			/*if (Cl_Object[Count]->Usage == Enums::Usage_Colectable)
			{
				Cl_Object[Count]->OgreEntity->setVisible(TRUE);
				
				Cl_Object[Count]->OgreNode->setPosition(Cl_Object[Count]->Mesh_Pos);

				P_Pos = Cl_Object[Count]->Physics_Pos;
				Cl_Object[Count]->bt_body->getWorldTransform().setOrigin(btVector3(P_Pos.x, P_Pos.y, P_Pos.z));

				Cl_Object[Count]->Triggered = 0;
			}*/
		}

		Count++;
	}
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


