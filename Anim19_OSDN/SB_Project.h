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

	bool Start_Save_Project_Dialog();

	bool N_Save_Project();
	bool N_Save_Project_Ini();
	bool N_Save_Level_Folder();

	bool N_Save_Aera_Folder();
	bool N_Save_Aeras_Data();

	bool N_Save_Players_Folder();
	bool N_Save_Player_Data();

	bool N_Load_Project();
	bool N_Load_Project_Aera();
	bool N_Load_Project_Player();

	char m_Project_Name[MAX_PATH];
	char m_Level_Name[MAX_PATH];
	char m_Aera_Folder_Path[MAX_PATH];
	char m_Level_Folder_Path[MAX_PATH];		// Level Just Path
	char m_Players_Folder_Path[MAX_PATH];

	char m_Project_Sub_Folder[MAX_PATH];	// Curent Default Project Location not including project folder
	
	char m_Ini_Path_File_Name[MAX_PATH];


	//------------------------------------------------  Good

	char m_Project_Folder_Path[MAX_PATH];		// Project folder Location Full Path [10/08/22]

	//------------------------------------------------ 

	bool Write_Level_File();
	bool Write_Player();
	bool Write_Camera();
	bool Write_Objects();

	char Project_Ini_FilePath[1024];

	char Level_Folder_Path_World[1024];

	string test;

	// --------------------------------------------------------------------------- 
	char Level_File_Name[MAX_PATH];			// Level File Name ( 211121 )
	
	bool Project_Loaded;

protected:

	static LRESULT CALLBACK Create_Project_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void N_Set_Paths();

	bool Read_Player();
	bool Read_Camera();

	FILE *Write_Ini;
	FILE *Write_Player_Ini;
	FILE *Write_Object_Ini;
	FILE *WriteFile;
};

