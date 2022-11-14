#pragma once

// ------------------------ Load Options
typedef struct Load_Options
{
	int Has_Aera;
	int Has_Player;
	int Has_Camera;
	int Has_Objects;
	int Has_Counters;

}Load_Options;

class GD10_Load_Scene
{
public:
	GD10_Load_Scene();
	~GD10_Load_Scene();

	bool Load_Project();
	bool Load_Get_Resource_Path();
	bool Load_Project_Player();
	bool Load_Project_Aera();
	bool Load_Project_Objects();
	bool Load_Project_Counters();

	void Set_Paths();

	char m_Ini_Path_File_Name[MAX_PATH];
	char m_Level_File_Name[MAX_PATH];
	char m_Project_Sub_Folder[MAX_PATH];
	char m_Level_Folder_Path[MAX_PATH];
	char m_Main_Assets_Path[MAX_PATH];
	char m_Project_Name[MAX_PATH];
	char m_Level_Name[MAX_PATH];
	char m_Game_Name[MAX_PATH];

	// --------------------------------------------------------------
	bool Load_Config_File();

	bool OpenScene(bool AskForScene);

	char Scene_FileName[255];
	char Scene_Path_FileName[2048];
	
protected:

};

