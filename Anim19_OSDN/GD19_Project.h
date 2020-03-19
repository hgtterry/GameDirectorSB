/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
class GD19_Project
{
public:

	GD19_Project(void);
	~GD19_Project(void);

	void Start_Project_Build();

	void Create_ProjectFolder(void);
	void Write_To_Config(void);
	void Read_From_Config(void);
	int Get_Transfer_Count(void);
	char LevelsFolder[1024];

protected:

	static LRESULT CALLBACK Project_Build_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	void Copy_SystemFiles(void);
	void Copy_ZipFiles(void);
	void Copy_Level_Files(void);

	void Create_Game_IniFile(void);
	void Create_Config_File(void);

	bool Transfer_UsedMaterials(void);
	bool Transfer_Meshes(void);
	bool Transfer_Textures(void);
	void Transfer_Environment_Sound(void);
	void Transfer_Sounds(void);

	void Start_List_Folders(HWND List, char* FileName, bool ListDlg);
	void List_Folders(HWND List, char* StartFolder, char* FileName, bool ListDlg);
	bool FindPath_New(char* File, char* Folder);

	char StartFolder[1024];
	char ProjectFolder[1024];
	char Sub_ProjectFolder[1024];

	char SourceFile[1024];
	char DestinationFile[1024];
	char MediaFolder[1024];


	char ActorsFolder[1024];
	char MaterialsFolder[1024];
	char TexturesFolder[1024];
	char CoreDataFolder[1024];
	char SoundFolder[1024];
	char GameName[255];

	char ResourcePath[2048];

	bool CF_Full_Screen;

	FILE* Write_IniFile;
};

