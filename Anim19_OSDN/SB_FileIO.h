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
class SB_FileIO
{
public:
	SB_FileIO();
	~SB_FileIO();

	bool Open_Project_File(char* Extension, char* Title, char* StartDirectory);
	bool SearchFolders(char* Path, char* File);
	bool Search_For_Folder(char* FolderPath);
	void CheckPath(char *pString, char *FileName);
	bool GetColor();

	void  Init_History(); // p
	void  LoadHistory();
	void  Save_FileHistory();
	void  RecentFileHistory_Update(); //p
	void  ResentHistory_Clear(); // p

	char Project_File_Name[MAX_PATH];
	char Project_Path_File_Name[MAX_PATH];
	char JustFileName[MAX_PATH];

	char UserData_Folder[MAX_PATH];
	char DeskTop_Folder[MAX_PATH];

	bool Cannceled;

	std::vector<std::string> mPreviousFiles;

	CHOOSECOLOR color;
	OPENFILENAME ofn;

	FILE *WriteRecentFiles;
	FILE *ReadRecentFiles;

	HMENU mHistoryMenu;

#define EQUITY_NUM_RECENT_FILES 0x8
#define EQUITY_RECENT_FILE_ID(_n_) (5000 + _n_)

};

