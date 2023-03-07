#include "stdafx.h"
#include "resource.h"
#include "ME_App.h"
#include "ME_Preferences.h"


ME_Preferences::ME_Preferences()
{
	Show_Preferences_GUI = 0;
	Preferences_Page = 0;


	char Default_Project[MAX_PATH];
	strcpy(Default_Project, App->EquityDirecory_FullPath);
	strcat(Default_Project, "\\Models\\Cube.obj");
	strcpy(QL_User_File, Default_Project);



	Prefs_QuickLoad_Default_f = 0;
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
		}*/

		if (ImGui::Checkbox("Default Quick Load", &Prefs_QuickLoad_Default_f))
		{
			Write_Preferences();
		}

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

	//ImGui::Image(&App->CL_Ogre->RenderListener->g_Texture[0], ImVec2(256, 256));

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
	char chr_Tag1[MAX_PATH];
	//char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	//chr_Tag2[0] = 0;

	char Preferences_Path[MAX_PATH];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Preferences.ini");

	App->CL_Ini->SetPathName(Preferences_Path);

	Prefs_QuickLoad_Default_f = App->CL_Ini->GetInt("Quick_Load", "QL_Use_TestFile", 1, 10);

	
	int Test = App->CL_Ini->GetString("Quick_Load", "QL_User_File", chr_Tag1, MAX_PATH);
	if (Test > 0)
	{
		strcpy(QL_User_File, chr_Tag1);
	}
	else
	{
		char Default_Project[MAX_PATH];
		strcpy(Default_Project, App->EquityDirecory_FullPath);
		strcat(Default_Project, "\\Models\\Cube.obj");
	}


	Prefs_FullScreen_Flag = App->CL_Ini->GetInt("Start_Up", "Start_FullScreen", 1, 10);

	return 1;
}

// *************************************************************************
// *						Write_Preferences Terry Flanigan 			   *
// *************************************************************************
bool ME_Preferences::Write_Preferences()
{
	WriteScene = nullptr;

	char Preferences_Path[MAX_PATH];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);
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

// *************************************************************************
// *			Do_Quick_Load:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void ME_Preferences::Do_Quick_Load()
{

	if (App->CL_Prefs->Prefs_QuickLoad_Default_f == 1)
	{

		char Default_Project[MAX_PATH];
		strcpy(Default_Project, App->EquityDirecory_FullPath);
		strcat(Default_Project, "\\Models\\Cube.obj");

		App->CL_Import->Reload_FromResentFiles(Default_Project);

		//App->SBC_Import->Quick_Load_Flag = 1;
		//App->SBC_Import->Quick_Load_Flag = 0;
	}
	else
	{
		int Result = strcmp(App->CL_Prefs->QL_User_File, "Not_Set");
		if (Result == 0)
		{
			App->Say("Quick Load Not Set");
		}
		else
		{
			//App->SBC_Import->Quick_Load_Flag = 1;
			App->CL_Import->Reload_FromResentFiles(App->CL_Prefs->QL_User_File);
			//App->SBC_Import->Quick_Load_Flag = 0;
		}
	}
}

// *************************************************************************
// *			Update_User_File:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void ME_Preferences::Update_User_File(char * PathAndFile)
{
	strcpy(App->CL_Prefs->QL_User_File, PathAndFile);
	App->CL_Prefs->Write_Preferences();
}
