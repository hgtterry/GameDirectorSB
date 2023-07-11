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

class SB_RecentFiles
{
public:
	SB_RecentFiles(void);
	~SB_RecentFiles(void);

	void Start_RecentFiles_Dlg();

	void Init_History();

	char UserData_Folder[MAX_PATH];

private:

	static LRESULT CALLBACK RecentFiles_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool Search_For_Folder(char* FolderPath);
	void ResentHistory_Files_Clear();
	void Save_FileHistory_Files();
	void LoadHistory_Files();
	bool Check_File_Exist(char* Full_Path);
	void List_Recent_Files(HWND hDlg);

	std::vector<std::string> mPreviousFiles_Files;

	FILE* WriteRecentFiles;
	FILE* ReadRecentFiles;

#define RECENT_FILES 0x8
};

