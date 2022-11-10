/*
Copyright (c) 2022 GameDirectorSB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Build
{
public:
	SB_Build();
	~SB_Build();

	void Start_Project_Build();

	char StartFolder[MAX_PATH];
	char GameName[MAX_PATH];



protected:
	static LRESULT CALLBACK Project_Build_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool Build_Project();
	bool Build_Project_Ini();
	bool Build_Level_Folder();
	bool Build_Main_Asset_Folder();
	bool Copy_Assets(char* SourceFolder, char* DestinationFolder);
	bool Build_Area_Folder();
	bool Build_Areas_Data();
	bool Build_Players_Folder();
	bool Build_Player_Data();
	bool Build_Cameras_Folder();
	bool Build_Cameras_Data();
	bool Build_Objects_Folder();
	bool Build_Objects_Data();
	bool Build_Display_Folder();
	bool Build_Display_Data();

	void Copy_Sound_Files(void);

	//------------------------------------------
	void Read_From_Config(void);
	void Create_ProjectFolder(void);
	void Copy_SystemFiles(void);
	void Copy_ZipFiles(void);
	void Copy_Level_Files(void);
	void Create_Game_IniFile(void);
	void Create_Config_File(void);

	char ProjectFolder[MAX_PATH];
	char Sub_ProjectFolder[MAX_PATH];

	char Sub_Build_Folder[MAX_PATH];

	char SourceFile[MAX_PATH];
	char DestinationFile[MAX_PATH];
	char MediaFolder[MAX_PATH];

	char CoreDataFolder[MAX_PATH];
	char SoundFolder[MAX_PATH];

	//------------------------------------------

	char m_Build_Sub_Folder[MAX_PATH];
	char m_Ini_Path_File_Name[MAX_PATH];
	char m_Level_Folder_Path[MAX_PATH];
	char m_Main_Assets_Path[MAX_PATH];
	char m_Aera_Folder_Path[MAX_PATH];
	char m_Players_Folder_Path[MAX_PATH];
	char m_Cameras_Folder_Path[MAX_PATH];
	char m_Objects_Folder_Path[MAX_PATH];
	char m_Display_Folder_Path[MAX_PATH];

	FILE *WriteFile;
};

