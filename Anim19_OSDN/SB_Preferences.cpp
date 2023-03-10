/*
Copyright (c) 2021 EquitySB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

:- Terry and Hazel Flanigan 2022

*/

#include "stdafx.h"
#include "resource.h"
#include "GD19_App.h"
#include "SB_Preferences.h"

SB_Preferences::SB_Preferences()
{
	Show_Preferences_GUI = 0;
	Preferences_Page = 0;

	PosX = 500;
	PosY = 500;

	// Start Up

	strcpy(QL_User_File,"Not_Set");

	Prefs_QuickLoad_Default_f = 1;
	Prefs_StartScreen_Flag = 1;
	Prefs_FullScreen_Flag = 1;
	Prefs_Load_LastScene_Flag = 1;

	// Game Options
	Prefs_PlayerCanJump_Flag = 0;
}

SB_Preferences::~SB_Preferences()
{
	
}


// *************************************************************************
// *	 Start_Preferences_GUI:- Terry and Hazel Flanigan 2023  		   *
// *************************************************************************
void SB_Preferences::Start_Preferences_GUI()
{

	Read_Preferences();

	App->SBC_Panels->Close_Gui_Panels();
	App->SBC_Panels->Enable_All_Panels(false);

	Show_Preferences_GUI = 1;
}

// *************************************************************************
// *		Preferences_Property_GUI:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void SB_Preferences::Preferences_GUI()
{

	ImGui::SetNextWindowPos(ImVec2(PosX, PosY));
	ImGui::SetNextWindowSize(ImVec2(350, 200), ImGuiCond_FirstUseEver);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	if (!ImGui::Begin("Preferences", &Show_Preferences_GUI, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
		return;
	}

	//ImGui::BeginDisabled(true);

	ImGuiColorEditFlags misc_flags2 = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	
	ImGui::Columns(2);
	ImGui::SetColumnWidth(-1, 120);

	if (ImGui::Selectable("   Start Up ", Preferences_Page == 0, 0, ImVec2(100, 0)))
	{
		Preferences_Page = 0;
	}

	if (ImGui::Selectable("     Game ", Preferences_Page == 1, 0, ImVec2(100, 0)))
	{
		Preferences_Page = 1;
	}

	if (ImGui::Selectable("     Test ", Preferences_Page == 2, 0, ImVec2(100, 0)))
	{
		Preferences_Page = 2;
	}

	
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();
	ImGui::Spacing();

	// ---------------------------------------------------------------- Start Up
	if (Preferences_Page == 0)
	{
		ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();

		ImGui::Text("Start Up:");
		
		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Checkbox("Show Start Up Screen", &Prefs_StartScreen_Flag))
		{
			Write_Preferences();
		}

		if (ImGui::Checkbox("Default Quick File", &Prefs_QuickLoad_Default_f))
		{
			Write_Preferences();
		}

		if (ImGui::Checkbox("Full Screen", &Prefs_FullScreen_Flag))
		{
			Write_Preferences();
		}

		if (ImGui::Checkbox("Load Last Scene", &Prefs_Load_LastScene_Flag))
		{
			Write_Preferences();
		}

		/*if (ImGui::InputInt("##1", &App->CL_Ogre->OgreListener->Bullet_Step, 1))
		{
			
		}*/
	}

	// ---------------------------------------------------------------- Game
	if (Preferences_Page == 1)
	{
		ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();

		ImGui::Text("Game Options:");

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Checkbox("Player Can Jump", &Prefs_PlayerCanJump_Flag))
		{
			App->SBC_DCC->Player_CanJump = Prefs_PlayerCanJump_Flag;
			Write_Preferences();
		}

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		
		/*if (ImGui::Checkbox("Default Quick File", &Prefs_TestFile_Flag))
		{
			Write_Preferences();
		}

		if (ImGui::Checkbox("Full Screen", &Prefs_FullScreen_Flag))
		{
			Write_Preferences();
		}

		if (ImGui::Checkbox("Load Last Scene", &Prefs_Load_LastScene_Flag))
		{
			Write_Preferences();
		}*/

		/*if (ImGui::InputInt("##1", &App->CL_Ogre->OgreListener->Bullet_Step, 1))
		{

		}*/

	}

	// ---------------------------------------------------------------- Test App
	if (Preferences_Page == 2)
	{
		ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();

		ImGui::Text("Development:");

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Checkbox("New Properties", &App->SBC_Gui_Propreties->Show_Properties_Panel_Flag))
		{
			Write_Preferences();
		}

		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
		ImGui::Spacing();
	}

	ImGui::PopStyleVar();
	ImGui::Columns(0);

	ImGui::Spacing();
	ImGui::Spacing();

	if (ImGui::Button("Close", ImVec2(100, 0)))
	{
		ImGui::PopStyleColor();
		Preferences_Page = 0;
		Close_Preferences_GUI();
		Show_Preferences_GUI = 0;
	}

	ImVec2 Size = ImGui::GetWindowSize();
	PosX = ((float)App->CL_Ogre->OgreListener->View_Width / 2) - (Size.x / 2);
	PosY = ((float)App->CL_Ogre->OgreListener->View_Height / 2) - (Size.y / 2);;

	//ImGui::BeginDisabled(false);
	ImGui::End();
}

// *************************************************************************
// *	 Close_Preferences_GUI:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Preferences::Close_Preferences_GUI()
{
	
	App->SBC_Panels->Enable_All_Panels(true);

	Show_Preferences_GUI = 0;
}

// *************************************************************************
// *			Set_Defaults:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Preferences::Set_Defaults()
{
	// -------------------------- Quick Load
	Prefs_QuickLoad_Default_f = 1;
	strcpy(QL_User_File, "Not_Set");

	Prefs_StartScreen_Flag = 1;
	Prefs_FullScreen_Flag = 1;
	Write_Preferences();
}

// *************************************************************************
// *			Write_Preferences:- Terry and Hazel Flanigan 2022 		   *
// *************************************************************************
bool SB_Preferences::Write_Preferences()
{
	
	WriteScene = NULL;

	char Preferences_Path[1024];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);;
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Preferences.ini");

	WriteScene = fopen(Preferences_Path, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	

	fprintf(WriteScene, "%s\n", "[Quick_Load]");
	fprintf(WriteScene, "%s%i\n", "QL_Use_TestFile=", Prefs_QuickLoad_Default_f);
	fprintf(WriteScene, "%s%s\n", "QL_User_File=", QL_User_File);

	fprintf(WriteScene, "%s\n", " ");

	fprintf(WriteScene, "%s\n", "[Start_Up]");
	fprintf(WriteScene, "%s%i\n", "Show_StartScreen=", Prefs_StartScreen_Flag);
	fprintf(WriteScene, "%s%i\n", "Start_FullScreen=", Prefs_FullScreen_Flag);
	fprintf(WriteScene, "%s%i\n", "Load_LastScene=", Prefs_Load_LastScene_Flag);

	fprintf(WriteScene, "%s\n", "[Game]");
	fprintf(WriteScene, "%s%i\n", "Player_CanJump=", Prefs_PlayerCanJump_Flag);

	fprintf(WriteScene, "%s\n", "[Development]");
	fprintf(WriteScene, "%s%i\n", "New_Properties=", App->SBC_Gui_Propreties->Show_Properties_Panel_Flag);

	fclose(WriteScene);

	//Read_Preferences();
	return 1;
}

// *************************************************************************
// *			Read_Preferences:- Terry and Hazel Flanigan 2022 		   *
// *************************************************************************
bool SB_Preferences::Read_Preferences()
{
	
	char chr_Tag1[MAX_PATH] = { 0 };
	chr_Tag1[0] = 0;

	char Preferences_Path[MAX_PATH];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Preferences.ini");

	App->Cl_Ini->SetPathName(Preferences_Path);

	Prefs_QuickLoad_Default_f = App->Cl_Ini->GetInt("Quick_Load", "QL_Use_TestFile",1, 10);

	App->Cl_Ini->GetString("Quick_Load", "QL_User_File", chr_Tag1, MAX_PATH);
	strcpy(QL_User_File, chr_Tag1);


	Prefs_StartScreen_Flag = App->Cl_Ini->GetInt("Start_Up", "Show_StartScreen",1, 10);
	Prefs_FullScreen_Flag = App->Cl_Ini->GetInt("Start_Up", "Start_FullScreen", 1, 10);
	Prefs_Load_LastScene_Flag = App->Cl_Ini->GetInt("Start_Up", "Load_LastScene", 1, 10);

	// Game
	Prefs_PlayerCanJump_Flag = App->Cl_Ini->GetInt("Game", "Player_CanJump", 0, 10);

	// Development

	App->SBC_Gui_Propreties->Show_Properties_Panel_Flag = App->Cl_Ini->GetInt("Development", "New_Properties", 0, 10);

	return 1;
}

// *************************************************************************
// *			Do_Quick_Load:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Preferences::Do_Quick_Load()
{
	if (Prefs_QuickLoad_Default_f == 1)
	{
		char Default_Project[MAX_PATH];
		strcpy(Default_Project, App->EquityDirecory_FullPath);
		strcat(Default_Project, "\\Projects\\RF_Project_Prj\\Project.SBProj");

		App->SBC_Import->Quick_Load_Flag = 1;
		App->SBC_Import->Reload_FromResentFiles(Default_Project);
		App->SBC_Import->Quick_Load_Flag = 0;
	}
	else
	{
		int Result = strcmp(QL_User_File, "Not_Set");
		if (Result == 0)
		{
			App->Say("Quick Load Not Set");
		}
		else
		{
			App->SBC_Import->Quick_Load_Flag = 1;
			App->SBC_Import->Reload_FromResentFiles(QL_User_File);
			App->SBC_Import->Quick_Load_Flag = 0;
		}
	}
}

// *************************************************************************
// *			Update_User_File:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Preferences::Update_User_File(char* PathAndFile)
{
	strcpy(App->CL_Prefs->QL_User_File, PathAndFile);
	App->CL_Prefs->Write_Preferences();
}
