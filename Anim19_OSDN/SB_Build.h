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

	void Read_From_Config(void);
	void Create_ProjectFolder(void);
	void Copy_SystemFiles(void);
	void Copy_ZipFiles(void);
	void Copy_Level_Files(void);
	void Create_Game_IniFile(void);
	void Create_Config_File(void);

	char ProjectFolder[MAX_PATH];
	char Sub_ProjectFolder[MAX_PATH];

	char SourceFile[MAX_PATH];
	char DestinationFile[MAX_PATH];
	char MediaFolder[MAX_PATH];

	char ActorsFolder[MAX_PATH];
	char MaterialsFolder[MAX_PATH];
	char TexturesFolder[MAX_PATH];
	char CoreDataFolder[MAX_PATH];
	char SoundFolder[MAX_PATH];

	char LevelsFolder[MAX_PATH];
};

