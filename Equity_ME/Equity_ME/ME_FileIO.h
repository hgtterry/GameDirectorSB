/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class ME_FileIO
{
public:
	ME_FileIO();
	~ME_FileIO();

	bool Folder_Browser();
	bool Open_File_Model(char* Extension, char* Title, char* StartDirectory);
	bool OpenTextureFile(char* Title, char* StartDirectory, bool SaveLocation);
	bool StartBrowser(char* szInitDir);
	bool SearchFolders(char* Path, char* File);
	bool Search_For_Folder(char* FolderPath);
	void CheckPath(char *pString, char *FileName, char* mJustFileName);

	void Start_RecentProjects_Dlg(int Selected_Recent);

	char Model_FileName[MAX_PATH];
	char Model_Path_FileName[MAX_PATH];

	char Texture_FileName[MAX_PATH];
	char Texture_Path_FileName[MAX_PATH];
	char JustFileName[MAX_PATH];

	char RecentFile[MAX_PATH];

	int mSelected_Recent;
	std::string Get_Model_File_Name();
	std::string Get_Model_Path_File_Name();

	char BrowserMessage[MAX_PATH];
	TCHAR szSelectedDir[MAX_PATH];

	std::vector<std::string> mPreviousFiles_Models;
	std::vector<std::string> mPreviousFiles_Projects;

protected:
	static int __stdcall BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData);
	static LRESULT CALLBACK RecentProjects_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	
	FILE *WriteRecentFiles;
	FILE *ReadRecentFiles;

//#define RECENT_FILES 0x8


	OPENFILENAME ofn;
};

