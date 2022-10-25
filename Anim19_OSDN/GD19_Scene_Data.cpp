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




