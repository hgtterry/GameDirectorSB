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

	// -------------------------- Quick Load

	strcpy(QL_User_File,"Not_Set");

	Prefs_TestFile_Flag = 1;
	Prefs_StartScreen_Flag = 1;
	Prefs_FullScreen_Flag = 1;
	Prefs_Load_LastScene_Flag = 1;
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

	Show_Preferences_GUI = 1;
}

// *************************************************************************
// *		Preferences_Property_GUI:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void SB_Preferences::Preferences_GUI()
{

	ImGui::SetNextWindowPos(ImVec2(PosX, PosY));
	ImGui::SetNextWindowSize(ImVec2(350, 210), ImGuiCond_FirstUseEver);

	ImGui::PushStyleColor(ImGuiCol_WindowBg, IM_COL32(239, 239, 239, 255));

	if (!ImGui::Begin("Preferences", &Show_Preferences_GUI, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar))
	{
		ImGui::End();
		return;
	}

	ImGuiColorEditFlags misc_flags2 = (ImGuiColorEditFlags_DisplayRGB | ImGuiColorEditFlags_InputRGB | ImGuiColorEditFlags_Uint8);

	ImGui::PushStyleVar(ImGuiStyleVar_FramePadding, ImVec2(2, 2));
	
	ImGui::Columns(2);
	ImGui::SetColumnWidth(-1, 120);

	if (ImGui::Button(" Start Up ", ImVec2(100, 0)))
	{
		Preferences_Page = 0;
	}

	/*if (ImGui::Button("Sound   ", ImVec2(100, 0)))
	{
		Preferences_Page = 1;
	}

	if (ImGui::Button("Fog   ", ImVec2(100, 0)))
	{
		Preferences_Page = 2;
	}

	if (ImGui::Button("Sky   ", ImVec2(100, 0)))
	{
		Preferences_Page = 3;
	}*/

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

		if (ImGui::Checkbox("Default Quick File", &Prefs_TestFile_Flag))
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


		if (ImGui::InputInt("##1", &App->SBC_Ogre->OgreListener->Bullet_Step, 1))
		{
			
		}

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
	PosX = ((float)App->SBC_Ogre->OgreListener->View_Width / 2) - (Size.x / 2);
	PosY = ((float)App->SBC_Ogre->OgreListener->View_Height / 2) - (Size.y / 2);;

	ImGui::End();
}

// *************************************************************************
// *	 Close_Preferences_GUI:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void SB_Preferences::Close_Preferences_GUI()
{
	///*App->Disable_Panels(false);
	//App->Show_Panels(true);*/

	//App->SBC_FileView->Show_FileView(true);
	//int Index = App->SBC_Properties->Current_Selected_Object;
	//App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);

	//Index = App->SBC_Com_Environments->Get_First_Environ();
	//App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);

	Show_Preferences_GUI = 0;
}

// *************************************************************************
// *			Set_Defaults:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Preferences::Set_Defaults()
{
	// -------------------------- Quick Load
	Prefs_TestFile_Flag = 1;
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
	fprintf(WriteScene, "%s%i\n", "QL_Use_TestFile=", Prefs_TestFile_Flag);
	fprintf(WriteScene, "%s%s\n", "QL_User_File=", QL_User_File);

	fprintf(WriteScene, "%s\n", " ");

	fprintf(WriteScene, "%s\n", "[Start_Up]");
	fprintf(WriteScene, "%s%i\n", "Show_StartScreen=", Prefs_StartScreen_Flag);
	fprintf(WriteScene, "%s%i\n", "Start_FullScreen=", Prefs_FullScreen_Flag);
	fprintf(WriteScene, "%s%i\n", "Load_LastScene=", Prefs_Load_LastScene_Flag);
	
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

	Prefs_TestFile_Flag = App->Cl_Ini->GetInt("Quick_Load", "QL_Use_TestFile",1, 10);

	App->Cl_Ini->GetString("Quick_Load", "QL_User_File", chr_Tag1, MAX_PATH);
	strcpy(QL_User_File, chr_Tag1);


	Prefs_StartScreen_Flag = App->Cl_Ini->GetInt("Start_Up", "Show_StartScreen",1, 10);
	Prefs_FullScreen_Flag = App->Cl_Ini->GetInt("Start_Up", "Start_FullScreen", 1, 10);
	Prefs_Load_LastScene_Flag = App->Cl_Ini->GetInt("Start_Up", "Load_LastScene", 1, 10);

	return 1;
}
