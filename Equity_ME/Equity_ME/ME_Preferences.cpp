#include "stdafx.h"
#include "resource.h"
#include "ME_App.h"
#include "ME_Preferences.h"


ME_Preferences::ME_Preferences()
{
	Show_Preferences_GUI = 0;
	Preferences_Page = 0;

	Prefs_TestFile_Flag = 0;
	Prefs_StartScreen_Flag = 0;
	Prefs_FullScreen_Flag = 0;
	Prefs_Load_LastScene_Flag = 0;

	PosX = 500;
	PosY = 500;

	strcpy(Pref_Txl_Path_FileName, "Not_Set");

	strcpy(Pref_WE_JustFileName, "Not_Set");
	strcpy(Pref_WE_Path_FileName, "Not_Set");

	strcpy(Pref_Ogre_JustFileName, "Not_Set");
	strcpy(Pref_Ogre_Path, "Not_Set");

	WriteScene = nullptr;
}


ME_Preferences::~ME_Preferences()
{
}

// *************************************************************************
// *	 Start_Preferences_GUI:- Terry and Hazel Flanigan 2023  		   *
// *************************************************************************
void ME_Preferences::Start_Preferences_GUI()
{

	Read_Preferences();

	//App->SBC_Panels->Close_Gui_Panels();
	//App->SBC_Panels->Enable_All_Panels(false);

	Show_Preferences_GUI = 1;
}

// *************************************************************************
// *		Preferences_Property_GUI:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void ME_Preferences::Preferences_GUI()
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

		/*if (ImGui::Checkbox("Show Start Up Screen", &Prefs_StartScreen_Flag))
		{
			Write_Preferences();
		}

		if (ImGui::Checkbox("Default Quick File", &Prefs_TestFile_Flag))
		{
			Write_Preferences();
		}*/

		if (ImGui::Checkbox("Full Screen", &Prefs_FullScreen_Flag))
		{
			Write_Preferences();
		}

		/*if (ImGui::Checkbox("Load Last Scene", &Prefs_Load_LastScene_Flag))
		{
			Write_Preferences();
		}*/

		/*if (ImGui::InputInt("##1", &App->SBC_Ogre->OgreListener->Bullet_Step, 1))
		{

		}*/
	}

	// ---------------------------------------------------------------- Game
	if (Preferences_Page == 1)
	{
		/*ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();

		ImGui::Text("Game Options:");

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Checkbox("Player Can Jump", &Prefs_PlayerCanJump_Flag))
		{
			App->SBC_DCC->Player_CanJump = Prefs_PlayerCanJump_Flag;
			Write_Preferences();
		}*/

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

		/*if (ImGui::InputInt("##1", &App->SBC_Ogre->OgreListener->Bullet_Step, 1))
		{

		}*/

	}

	// ---------------------------------------------------------------- Test App
	if (Preferences_Page == 2)
	{
		/*ImGui::NextColumn();
		ImGui::AlignTextToFramePadding();

		ImGui::Text("Development:");

		ImGui::Spacing();
		ImGui::Spacing();

		if (ImGui::Checkbox("New Properties", &App->SBC_Gui_Propreties->Show_Properties_Panel_Flag))
		{
			Write_Preferences();
		}*/

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
	PosX = ((float)App->CL_Ogre->Ogre_Listener->View_Width / 2) - (Size.x / 2);
	PosY = ((float)App->CL_Ogre->Ogre_Listener->View_Height / 2) - (Size.y / 2);;

	//ImGui::BeginDisabled(false);
	ImGui::End();
}

// *************************************************************************
// *	 Close_Preferences_GUI:- Terry and Hazel Flanigan 2022  		   *
// *************************************************************************
void ME_Preferences::Close_Preferences_GUI()
{

	//App->SBC_Panels->Enable_All_Panels(true);

	Show_Preferences_GUI = 0;
}

// *************************************************************************
// *						Read_Preferences Terry Flanigan 			   *
// *************************************************************************
bool ME_Preferences::Read_Preferences()
{
	/*char chr_Tag1[MAX_Path];
	char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;*/

	char Preferences_Path[MAX_PATH];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Preferences.ini");

	App->CL_Ini->SetPathName(Preferences_Path);

	Prefs_FullScreen_Flag = App->CL_Ini->GetInt("Start_Up", "Start_FullScreen", 1, 10);



	/*App->CL_Ini->GetString("WE_Fast_Load", "Pref_WE_JustFileName", chr_Tag1, 1024);
	strcpy(Pref_WE_JustFileName, chr_Tag1);

	App->CL_Ini->GetString("WE_Fast_Load", "Pref_WE_Path_FileName", chr_Tag1, 1024);
	strcpy(Pref_WE_Path_FileName, chr_Tag1);

	App->CL_Ini->GetString("WE_Fast_Load", "Pref_Txl_Path_FileName", chr_Tag2, 1024);
	strcpy(Pref_Txl_Path_FileName, chr_Tag2);

	App->CL_Ini->GetString("WE_Fast_Load", "Pref_Ogre_JustFileName", chr_Tag2, 1024);
	strcpy(Pref_Ogre_JustFileName, chr_Tag2);

	App->CL_Ini->GetString("WE_Fast_Load", "Pref_Ogre_Path_FileName", chr_Tag2, 1024);
	strcpy(Pref_Ogre_Path, chr_Tag2);*/

	return 1;
}

// *************************************************************************
// *						Write_Preferences Terry Flanigan 			   *
// *************************************************************************
bool ME_Preferences::Write_Preferences()
{
	WriteScene = nullptr;

	char Preferences_Path[MAX_PATH];

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

	fprintf(WriteScene, "%s\n", "[Start_Up]");
	fprintf(WriteScene, "%s%i\n", "Start_FullScreen=", Prefs_FullScreen_Flag);

	fprintf(WriteScene, "%s\n", " ");

	/*fprintf(WriteScene, "%s\n", "[WE_Fast_Load]");
	fprintf(WriteScene, "%s%s\n", "Pref_WE_JustFileName=", Pref_WE_JustFileName);
	fprintf(WriteScene, "%s%s\n", "Pref_WE_Path_FileName=", Pref_WE_Path_FileName);
	fprintf(WriteScene, "%s%s\n", "Pref_Txl_Path_FileName=", Pref_Txl_Path_FileName);
	fprintf(WriteScene, "%s%s\n", "Pref_Ogre_JustFileName=", Pref_Ogre_JustFileName);
	fprintf(WriteScene, "%s%s\n", "Pref_Ogre_Path_FileName=", Pref_Ogre_Path);*/

	fprintf(WriteScene, "%s\n", " ");
	fclose(WriteScene);

	//Read_Preferences();
	return 1;
}
