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

	bool Load_Project();
	bool Start_Save_Project_Dialog();

	char m_Project_Name[MAX_PATH];
	char m_Level_Name[MAX_PATH];
	char m_Level_File_Name[MAX_PATH];
	char m_Aera_Folder_Path[MAX_PATH];
	char m_Level_Folder_Path[MAX_PATH];		// Level Just Path
	char m_Players_Folder_Path[MAX_PATH];
	char m_Objects_Folder_Path[MAX_PATH];
	char m_Cameras_Folder_Path[MAX_PATH];

	char m_Objects_Assets_Path[MAX_PATH];	// Assets Path and \\

	char m_Project_Sub_Folder[MAX_PATH];	// Curent Default Project Location not including project folder
	
	char m_Ini_Path_File_Name[MAX_PATH];

	string test;

	bool Project_Loaded;

protected:

	static LRESULT CALLBACK Save_Project_Dialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool Save_Project();
	bool Save_Project_Ini();
	bool Save_Level_Folder();

	bool Save_Cameras_Folder();
	bool Save_Cameras_Data();

	bool Save_Aera_Folder();
	bool Save_Aeras_Data();

	bool Save_Players_Folder();
	bool Save_Player_Data();

	bool Save_Objects_Folder();
	bool Save_Objects_Data();

	bool Load_Project_Aera();
	bool Load_Project_Player();
	bool Load_Project_Camera();
	bool Load_Project_Objects();

	void Set_Paths();

	FILE *WriteFile;
};

