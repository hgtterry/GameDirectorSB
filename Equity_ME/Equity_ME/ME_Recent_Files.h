#pragma once

/*
Copyright (c) 2022- 2023 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

class ME_Recent_Files
{
public:
	ME_Recent_Files();
	~ME_Recent_Files();

	void Init_History();

	void ResentHistory_Models_Clear();
	void ResentHistory_Projects_Clear();

	void Save_FileHistory_Models();
	void Save_FileHistory_Projects();

	void LoadHistory_Models();
	void LoadHistory_Projects();

	void RecentFile_Models_History_Update();
	void RecentFile_Projects_History_Update();

	void LoadHistory_Equity();

	void List_Recent_Files(HWND hDlg);
	void List_Recent_Projects(HWND hDlg);


	char UserData_Folder[MAX_PATH];

	bool Search_For_Folder(char* FolderPath);

	std::vector<std::string> mPreviousFiles_Models;
	std::vector<std::string> mPreviousFiles_Projects;

	FILE* WriteRecentFiles;
	FILE* ReadRecentFiles;

#define RECENT_FILES 0x8
};

