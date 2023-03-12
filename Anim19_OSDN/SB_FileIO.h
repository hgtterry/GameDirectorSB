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
	bool OpenTextureFile(char* Title, char* StartDirectory, bool SaveLocation);

	bool SearchFolders(char* Path, char* File);

	// Returns 1 if File Exits 0 if no file
	bool Check_File_Exist(char* Full_Path); 

	void Get_FileName_FromPath(char* pString, char* FileName);
	bool GetColor();
	bool Directory_Vaild(LPCTSTR szPath);

	void Start_RecentProjects_Dlg(int Selected_Recent);
	void List_Recent_Files(HWND hDlg);
	void List_Recent_Projects(HWND hDlg);

	void  Init_History();
	void  RecentFileHistory_Update();
	void  ResentHistory_Clear(bool FirstTime);

	int mSelected_Recent;

	char Texture_FileName[MAX_PATH];
	char Texture_Path_FileName[MAX_PATH];

	char Project_File_Name[MAX_PATH];
	char Project_Path_File_Name[MAX_PATH];
	char JustFileName[MAX_PATH];

	char Data_mFilename[MAX_PATH];
	char Data_Path_mFilename[MAX_PATH];

	char UserData_Folder[MAX_PATH];
	char DeskTop_Folder[MAX_PATH];
	char RecentFile[MAX_PATH];

	bool Cannceled;

	std::vector<std::string> mPreviousFiles;

	CHOOSECOLOR color;

protected:

	static LRESULT CALLBACK RecentProjects_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void  LoadHistory();
	void  Save_FileHistory();

	OPENFILENAME ofn;

	FILE *WriteRecentFiles;
	FILE *ReadRecentFiles;

	//HMENU mHistoryMenu;

#define EQUITY_NUM_RECENT_FILES 0x8
//#define EQUITY_RECENT_FILE_ID(_n_) (5000 + _n_)

};

