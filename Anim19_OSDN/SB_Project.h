/*
Copyright (c) 2021 Stage Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

#pragma once

// ------------------------ Load Options
typedef struct Load_Options
{
	int Has_Aera;
	int Has_Player;
	int Has_Camera;
	int Has_Objects;

}Load_Options;

class SB_Project
{
public:
	SB_Project();
	~SB_Project();

	bool Start_Create_Project();

	bool Save_Project();
	bool Save_Project_Ini();
	bool Save_Level_Folder();

	bool Save_Aera_Folder();
	bool Save_Aeras_Data();

	bool Save_Players_Folder();
	bool Save_Player_Data();

	bool Load_Project();
	bool Load_Project_Aera();

	bool Load_Scene_Auto();
	bool Load_Scene();

	bool Write_Level_File();
	bool Write_Player();
	bool Write_Camera();
	bool Write_Objects();

	char Project_Name[255];
	char Project_Path[1024];
	char Project_FullPath[1024];

	char Project_Ini_FilePath[1024];

	char Level_Folder_Path_World[1024];



	char m_Level_Name[MAX_PATH];
	char m_Aera_Folder_Path[MAX_PATH];
	char m_Level_Folder_Path[MAX_PATH];		// Level Just Path
	char m_Players_Folder_Path[MAX_PATH];

	char m_Ini_Path_File_Name[MAX_PATH];


	// --------------------------------------------------------------------------- 
	char Level_File_Name[MAX_PATH];			// Level File Name ( 211121 )
	char Level_Path_File_Name[MAX_PATH];	// Level Path and File Name  ( 211121 )
	char Level_Folder_Path[MAX_PATH];		// Level Just Path


	char Scene_Path_FileName[1024]; 


	char Scene_JustPath[1024];

	bool Project_Loaded;

protected:

	static LRESULT CALLBACK Create_Project_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool Create_Project();

	bool Set_Paths();
	bool Write_Project_Ini();
	bool Create_Level_Folder();
	bool Add_World();
	

	bool Read_Player();
	bool Read_Camera();


	FILE *Write_Ini;
	FILE *Write_Player_Ini;
	FILE *Write_Object_Ini;
	FILE *WriteFile;
};

