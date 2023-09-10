/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Project.h"

SB_Project::SB_Project(void)
{
	strcpy(m_Main_Assets_Path, "None");

	strcpy(m_Project_Sub_Folder, App->WorldEditor_Directory);
	strcat(m_Project_Sub_Folder, "\\");
	strcat(m_Project_Sub_Folder, "Projects");
	strcat(m_Project_Sub_Folder, "\\");
	strcat(m_Project_Sub_Folder, "First_Project");
	strcat(m_Project_Sub_Folder, "_Prj");

	strcpy(m_Project_Name, "First_Project");
	strcpy(m_Level_Name, "First_Level");

	m_Level_Folder_Path[0] = 0;
	m_Players_Folder_Path[0] = 0;
	m_Objects_Folder_Path[0] = 0;
	m_Cameras_Folder_Path[0] = 0;
	m_Enviromnet_Folder_Path[0] = 0;

	m_Ini_Path_File_Name[0] = 0;

	m_Level_File_Name[0] = 0;

	//WriteFile = NULL;

	//Project_Loaded = 0;
	//Directory_Changed_Flag = 0;
	//Set_QuickLoad_Flag = 1;

	m_Ini_Path_File_Name[0] = 0;
}

SB_Project::~SB_Project(void)
{
}

// *************************************************************************
// *	  		Load_Project:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Load_Project()
{
	char Default_Project[MAX_PATH];
	strcpy(Default_Project, App->WorldEditor_Directory);
	strcat(Default_Project, "\\Levels\\First_Project_Prj\\Project.SBProj");

	strcpy(App->CLSB_FileIO->Project_Path_File_Name, Default_Project);
	strcpy(App->CLSB_FileIO->Project_Path_File_Name, Default_Project);
	strcpy(App->CLSB_FileIO->Project_Path_File_Name, Default_Project);

	m_Ini_Path_File_Name[0] = 0;

	App->CLSB_Scene->Clear_Level();
	App->CLSB_Scene->Create_Resources_Group();

	Set_Paths();

	// ------------------------------------------------------------------- 
	Load_Options* Options = new Load_Options;

	Options->Has_Area = 0;
	Options->Has_Player = 0;
	Options->Has_Camera = 0;
	Options->Has_Objects = 0;
	Options->Has_Counters = 0;

	int Int1 = 0;
	char chr_Tag1[1024];
	char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	App->CLSB_Ini->SetPathName(m_Ini_Path_File_Name);

	App->CLSB_Ini->GetString("Version_Data", "Version", chr_Tag1, 1024);
	
	//App->Cl_Ini->GetString("Files", "Level_Name", m_Level_Name, MAX_PATH);
	//App->Cl_Ini->GetString("Files", "Project_Name", m_Project_Name, MAX_PATH);
	//App->Cl_Ini->GetString("Files", "Game_Name", App->SBC_Build->GameName, MAX_PATH, "YourGameName");


	Options->Has_Area = App->CLSB_Ini->GetInt("Options", "Areas_Count", 0, 10);
	Options->Has_Player = App->CLSB_Ini->GetInt("Options", "Players_Count", 0, 10);
	Options->Has_Camera = App->CLSB_Ini->GetInt("Options", "Cameras_Count", 0, 10);
	Options->Has_Objects = App->CLSB_Ini->GetInt("Options", "Objects_Count", 0, 10);
	Options->Has_Counters = App->CLSB_Ini->GetInt("Options", "Counters_Count", 0, 10);

	//App->SBC_Scene->UniqueID_Object_Counter = App->Cl_Ini->GetInt("Options", "Objects_ID_Count", 0, 10);
	//App->SBC_Scene->UniqueID_Counters_Count = App->Cl_Ini->GetInt("Options", "Counters_ID_Count", 0, 10);
	//App->SBC_Scene->UniqueID_Area_Count = App->Cl_Ini->GetInt("Options", "Areas_ID_Count", 0, 10);

	//App->SBC_Build->GameOptions->Show_FPS = App->Cl_Ini->GetInt("Config", "Show_FPS", 0, 10);
	//App->SBC_Build->GameOptions->FullScreen = App->Cl_Ini->GetInt("Config", "Game_FullScreen", 1, 10);
	//App->SBC_Build->GameOptions->Zipped_Assets_Flag = App->Cl_Ini->GetInt("Config", "Zipped_Assets", 1, 10);
	//App->SBC_Build->GameOptions->Front_Dialog_Flag = App->Cl_Ini->GetInt("Config", "Use_Front_Dlg", 1, 10);

	////-------------------------------------- Set Resource Path

	Load_Get_Resource_Path();

	// ------------------------------------- Aera
	if (Options->Has_Area > 0)
	{
		//bool test = Load_Project_Aera();
		App->CLSB_Scene->Build_World(0);
		App->CLSB_Bullet->Create_Brush_Trimesh(0);
		App->CLSB_Model->Set_BondingBox_Brushes();

		App->CLSB_Scene->Area_Added = 1;
	}

	// ------------------------------------- Player
	if (Options->Has_Player > 0)
	{
	//	bool test = Load_Project_Player();
	//	App->SBC_DCC->Player_CanJump = App->CL_Prefs->Prefs_PlayerCanJump_Flag;

		App->CLSB_Player->Create_Player_Object();
		App->CLSB_Properties->Update_ListView_Player();

		App->CLSB_Scene->B_Player[0]->FileViewItem = App->CLSB_FileView->Add_Item(App->CLSB_FileView->FV_Players_Folder, "Player_1", 0, false);
		App->CLSB_FileView->Set_FolderActive(App->CLSB_FileView->FV_Players_Folder);
		App->CLSB_FileView->SelectItem(App->CLSB_FileView->FV_Players_Folder);
		App->CLSB_FileView->ExpandRoot();
	}
	
	//// ------------------------------------- Camera
	//if (Options->Has_Camera > 0)
	//{
	//	Load_Project_Camera();
	//	App->SBC_Scene->Camera_Added = 1;
	//	App->SBC_Com_Camera->Set_Camera(0);
	//	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Cameras_Folder);
	//}

	//// ------------------------------------- Objects
	//if (Options->Has_Objects > 0)
	//{
	//	V_Load_Project_Objects();
	//	App->SBC_Objects_Create->Add_Objects_From_File();
	//}

	//// ------------------------------------- Counters
	//if (Options->Has_Counters > 0)
	//{
	//	Load_Project_Counters();
	//	App->SBC_Display->Add_Counters_From_File();
	//}


	//App->CL_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;

	//App->SBC_FileView->Change_Level_Name();
	//App->SBC_FileView->Change_Project_Name();
	//App->SBC_FileView->Redraw_FileView();

	//App->SBC_Scene->Scene_Modified = 0;

	//int Test = App->SBC_Com_Environments->Get_First_Environ();
	//if (Test == -1)
	//{
	//	App->SBC_Com_Environments->Add_New_Environ_Entity(1);
	//	int mIndex = App->SBC_Com_Environments->Get_First_Environ();
	//	App->SBC_Com_Environments->Set_First_Environment(mIndex);

	//	App->SBC_Scene->Scene_Modified = 1;
	//}
	//else
	//{
	//	App->SBC_Com_Environments->Set_First_Environment(Test);
	//}

	App->CLSB_Scene->Scene_Loaded = 1;
	//App->SBC_Project->Project_Loaded = 1;

	//delete Options;

	//App->Set_Main_TitleBar(App->SBC_FileIO->Project_Path_File_Name);
	//App->SBC_FileIO->RecentFileHistory_Update();
	//App->CL_Prefs->Update_User_File(App->SBC_FileIO->Project_Path_File_Name);

	//App->SBC_FileView->SelectItem(App->SBC_FileView->FV_LevelFolder);

	//EnableMenuItem(App->mMenu, ID_FILE_SAVEPROJECTALL, MF_GRAYED);

	return 1;
}

// *************************************************************************
// *	  		Set_Paths:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Project::Set_Paths()
{

	strcpy(m_Level_File_Name, App->CLSB_FileIO->Project_File_Name);
	strcpy(m_Project_Sub_Folder, App->CLSB_FileIO->Project_Path_File_Name);
	strcpy(m_Ini_Path_File_Name, App->CLSB_FileIO->Project_Path_File_Name);

	strcpy(m_Level_Folder_Path, App->CLSB_FileIO->Project_Path_File_Name);

	// Get path no file 
	int len1 = strlen(m_Level_File_Name);
	int len2 = strlen(m_Project_Sub_Folder);
	strcpy(m_Project_Sub_Folder, m_Project_Sub_Folder);
	m_Project_Sub_Folder[len2 - (len1 + 1)] = 0;

	//GetFileTitleA(App->CL_Equity_SB->Pref_WE_Path_FileName, JustFileName, MAX_PATH);
}

// *************************************************************************
// *	  	Load_Get_Resource_Path:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Load_Get_Resource_Path()
{
	
	m_Main_Assets_Path[0] = 0;

	strcpy(m_Main_Assets_Path, m_Project_Sub_Folder);
	strcat(m_Main_Assets_Path, "\\");

	strcat(m_Main_Assets_Path, m_Level_Name);
	strcat(m_Main_Assets_Path, "\\");

	strcat(m_Main_Assets_Path, "Assets");
	strcat(m_Main_Assets_Path, "\\");

	App->CLSB_Scene->Add_Resource_Location_Project(m_Main_Assets_Path);

	return 1;
}
