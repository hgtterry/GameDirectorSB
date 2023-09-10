#pragma once

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

// ------------------------ Load Options
typedef struct Load_Options
{
	int Has_Area;
	int Has_Player;
	int Has_Camera;
	int Has_Objects;
	int Has_Counters;

}Load_Options;

class SB_Project
{
public:
	SB_Project(void);
	~SB_Project(void);

	bool Load_Project();

	char m_Project_Name[MAX_PATH];
	char m_Level_Name[MAX_PATH];
	char m_Level_File_Name[MAX_PATH];
	char m_Aera_Folder_Path[MAX_PATH];
	char m_Level_Folder_Path[MAX_PATH];		// Level Just Path
	char m_Players_Folder_Path[MAX_PATH];
	char m_Objects_Folder_Path[MAX_PATH];
	char m_Cameras_Folder_Path[MAX_PATH];
	char m_Display_Folder_Path[MAX_PATH];
	char m_Enviromnet_Folder_Path[MAX_PATH];

	char m_Main_Assets_Path[MAX_PATH];		// Asset Path where Object mesh are added too and used on Loading
	char m_Project_Sub_Folder[MAX_PATH];	// Curent Default Project Location not including project folder

	char m_Ini_Path_File_Name[MAX_PATH];

private:
	void Set_Paths();
	bool Load_Get_Resource_Path();
};

