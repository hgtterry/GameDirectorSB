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

#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_FileIO.h"
#include <shellapi.h>
#include "Shlobj.h"
#include "io.h"
#include <string>


ME_FileIO::ME_FileIO()
{
	Model_FileName[0] = 0;
	Model_Path_FileName[0] = 0;

	Texture_FileName[0] = 0;
	Texture_Path_FileName[0] = 0;

	BrowserMessage[0] = 0;
	szSelectedDir[0] = 0;

	ReadRecentFiles = nullptr;
}


ME_FileIO::~ME_FileIO()
{
}

// *************************************************************************
// *						OpenFile Terry Bernie						   *
// *************************************************************************
bool ME_FileIO::Open_File_Model(char* Extension, char* Title, char* StartDirectory)
{
	
	Model_FileName[0] = 0;
	Model_Path_FileName[0] = 0;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Model_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Model_Path_FileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Model_FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Model_FileName);;
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return 1;
	}
	return 0;
}

// *************************************************************************
// *					OpenTextureFile Terry Bernie			  	 	   *
// *************************************************************************
bool ME_FileIO::OpenTextureFile(char* Title, char* StartDirectory, bool SaveLocation)
{
	Texture_FileName[0] = 0;
	Texture_Path_FileName[0] = 0;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->Fdlg;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Texture_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Texture_Path_FileName);
	ofn.lpstrFilter = "Available Formats\0*.bmp;*.tga;*.jpg;*.png;*.dds;*.pcx;*.tif;*.tiff;\0Windows Bitmap  (*.bmp)\0*.bmp\0Truevision Targa  (*.tga) \0*.tga\0JPEG  (*.jpg) \0*.jpg\0Portable Network Graphics (*.png) \0*.png\0Direct Draw  (*.dds) \0*.dds\0ZSoft PCX  (*.pcx) \0*.pcx\0Tagged Image File Format  (*.tif) \0*.tif\0Tagged Image File Format  (*.tiff) \0*.tiff\0";

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Texture_FileName;				// Just File Name
	ofn.nMaxFileTitle = sizeof(Texture_FileName);
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == TRUE)
	{
		return 1;
	}

	return 0;
}

// *************************************************************************
// *					Get_Model_File_Name Terry Flanigan				   *
// *************************************************************************
std::string ME_FileIO::Get_Model_File_Name()
{
	return Model_FileName;
}

// *************************************************************************
// *				Get_Model_Path_File_Name Terry Flanigan				   *
// *************************************************************************
std::string ME_FileIO::Get_Model_Path_File_Name()
{
	return Model_Path_FileName;
}

// *************************************************************************
// *							StartBrowser   							   *
// *************************************************************************
bool ME_FileIO::StartBrowser(char* szInitDir)
{
	TCHAR dname[MAX_PATH * 2];
	IMalloc *imalloc; SHGetMalloc(&imalloc);
	BROWSEINFO bi; ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = App->Fdlg;
	bi.pszDisplayName = dname;
	bi.lpszTitle = BrowserMessage;
	bi.lParam = (LPARAM)szInitDir;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	bi.lpfn = BrowseCallbackProc;

	CoInitialize(NULL);
	ITEMIDLIST *pidl = SHBrowseForFolder(&bi);

	if (pidl)
	{
		imalloc->Free(pidl);
		imalloc->Release();
		return 1;
	}

	imalloc->Free(pidl);
	imalloc->Release();

	return 0;
}
// *************************************************************************
// *						BrowseCallbackProc   						   *
// *************************************************************************
int __stdcall ME_FileIO::BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData)
{
	//Initialization callback message
	if (uMsg == BFFM_INITIALIZED)
	{
		//SendMessage(hWnd, BFFM_SETSELECTION, 1, (LPARAM) szInitialPathName); 
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);

	}

	//Selection change message - store the selected directory
	if (uMsg == BFFM_SELCHANGED)
	{
		TCHAR szDir[MAX_PATH * 2] = { 0 };

		// fail if non-filesystem
		BOOL bRet = SHGetPathFromIDList((LPITEMIDLIST)lParam, szDir);
		if (bRet)
		{
			//If the folder cannot be "read" then fail
			if (_taccess(szDir, 00) != 0)
			{
				bRet = FALSE;
			}
			else
			{
				SHFILEINFO sfi;
				::SHGetFileInfo((LPCTSTR)lParam, 0, &sfi, sizeof(sfi),
					SHGFI_PIDL | SHGFI_ATTRIBUTES);

				// fail if pidl is a link
				if (sfi.dwAttributes & SFGAO_LINK)
					bRet = FALSE;
			}
		}

		// if invalid selection, disable the OK button
		if (!bRet)
		{
			::EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);
			strcpy(App->CL_FileIO->szSelectedDir, "");
		}
		else
			strcpy(App->CL_FileIO->szSelectedDir, szDir);
	}

	return 0;
}

// *************************************************************************
// *					SearchFolders Terry Bernie			 		 	   *
// *************************************************************************
bool ME_FileIO::SearchFolders(char* Path, char* File)
{
	char pSearchPath[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(pSearchPath, Path);
	strcat(pSearchPath, File);

	hFind = FindFirstFile(pSearchPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	else
	{
		FindClose(hFind);
		return 1;
	}

	return 0;
}

// *************************************************************************
// *					Search_For_Folder Terry Bernie				 	   *
// *************************************************************************
bool ME_FileIO::Search_For_Folder(char* FolderPath)
{
	char pSearchPath[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(pSearchPath, FolderPath);

	hFind = FindFirstFile(pSearchPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	else
	{
		FindClose(hFind);
		return 1;
	}

	return 0;
}

// *************************************************************************
// *						Init_History() Terry Bernie					   *
// *************************************************************************
void ME_FileIO::Init_History()
{
	char DirCheck[1024];
	strcpy(DirCheck, UserData_Folder);
	strcat(DirCheck, "\\");
	strcat(DirCheck, "Vima19");

	bool check = 0;
	check = Search_For_Folder(DirCheck);
	if (check == 0)
	{
		mPreviousFiles.resize(EQUITY_NUM_RECENT_FILES);

		CreateDirectory(DirCheck, NULL);
		ResentHistory_Clear(); // Set all slots to Empty
		Save_FileHistory();
		LoadHistory();
	}
	else
	{
		LoadHistory();
	}
}

// *************************************************************************
// *						LoadHistory() Terry Bernie					   *
// *************************************************************************
void ME_FileIO::LoadHistory()
{
	mPreviousFiles.resize(EQUITY_NUM_RECENT_FILES);

	char buffer[1024];
	char buf[1024];

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Vima19.ini");

	
	ReadRecentFiles = nullptr;

	ReadRecentFiles = fopen(buf, "rt");

	if (!ReadRecentFiles)
	{
		App->Say("Cant Find Recent Files");
		return;
	}

	// Read in File Names from RecentFiles.ini
	for (unsigned int i = 0; i < EQUITY_NUM_RECENT_FILES; ++i)
	{
		memset(buffer, 0, 1024);
		fgets(buffer, 1024, ReadRecentFiles);

		char Path[1024];
		strcpy(Path, buffer);
		int Len = strlen(Path);
		Path[Len - 1] = 0;

		mPreviousFiles[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	mHistoryMenu = CreateMenu();

	// Check for empty slots and gray out
	for (int i = EQUITY_NUM_RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);
		if (Result == 0)
		{
			iFlags = MF_GRAYED | MF_DISABLED;
		}

		AppendMenu(mHistoryMenu, MF_STRING | iFlags, EQUITY_RECENT_FILE_ID(i), szText);
	}

	ModifyMenu(GetMenu(App->MainHwnd), ID_FILE_RECENTFILES, MF_BYCOMMAND | MF_POPUP,
		(UINT_PTR)mHistoryMenu, "Recent files");
	return;
}

// *************************************************************************
// *					Save_FileHistory Terry Bernie					   *
// *************************************************************************
void ME_FileIO::Save_FileHistory()
{

	WriteRecentFiles = nullptr;

	char buf[1024];
	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Vima19.ini");


	WriteRecentFiles = fopen(buf, "wt");

	if (!WriteRecentFiles)
	{
		App->Say("Why Cant Find Recent Files");
		return;
	}

	// Save out to RecentFile.ini
	for (unsigned int i = 0; i < EQUITY_NUM_RECENT_FILES; ++i)
	{
		char szName[1024];
		strcpy(szName, mPreviousFiles[i].c_str());

		fprintf(WriteRecentFiles, "%s\n", szName);
	}

	fclose(WriteRecentFiles);
	return;
}
// *************************************************************************
// *					RecentFileHistory_Update Terry Bernie			   *
// *************************************************************************
void ME_FileIO::RecentFileHistory_Update()
{
	if (!mHistoryMenu)return;

	std::string sz = std::string(App->CL_Model->Path_FileName);
	if (mPreviousFiles[EQUITY_NUM_RECENT_FILES - 1] == sz)return;

	// add the new file to the list of recent files
	for (unsigned int i = 0; i < EQUITY_NUM_RECENT_FILES - 1; ++i)
	{
		mPreviousFiles[i] = mPreviousFiles[i + 1];
	}

	mPreviousFiles[EQUITY_NUM_RECENT_FILES - 1] = sz;

	// Check for empty slots and gray out
	for (int i = EQUITY_NUM_RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);
		if (Result == 0)
		{
			iFlags = MF_GRAYED | MF_DISABLED;
		}

		ModifyMenu(mHistoryMenu, EQUITY_RECENT_FILE_ID(i),
			MF_STRING | MF_BYCOMMAND | iFlags, EQUITY_RECENT_FILE_ID(i), szText);
	}

	// Save Changes
	Save_FileHistory();

	return;
}
// *************************************************************************
// *			ResentHistory_Clear Terry Bernie Hazel Nathan			   *
// *************************************************************************
void ME_FileIO::ResentHistory_Clear()
{
	App->CL_Dialogs->YesNo("Delete file history.", "Are you sure all File history will be Deleted Procede.");
	if (App->CL_Dialogs->Canceled == 1)
	{
		return;
	}

	// Set all slots to <empty>
	for (unsigned int i = 0; i < EQUITY_NUM_RECENT_FILES; ++i)
	{
		mPreviousFiles[i] = std::string("<empty>");
	}

	// Repopulate Menu system
	for (int i = EQUITY_NUM_RECENT_FILES - 1; i >= 0; --i)
	{
		ModifyMenu(mHistoryMenu, EQUITY_RECENT_FILE_ID(i),
			MF_STRING | MF_BYCOMMAND | MF_GRAYED | MF_DISABLED, EQUITY_RECENT_FILE_ID(i), "<empty>");
	}

	// Save Changes
	Save_FileHistory();
}

// *************************************************************************
// *					LoadHistory_Equity Terry Bernie					   *
// *************************************************************************
void ME_FileIO::LoadHistory_Equity()
{
	mPreviousFiles.resize(EQUITY_NUM_RECENT_FILES);

	char buffer[1024];
	char buf[1024];

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Vima19.ini");

	ReadRecentFiles = fopen(buf, "rt");

	if (!ReadRecentFiles)
	{
		App->Say("Cant Find Recent Files");
		return;
	}

	// Read in File Names from RecentFiles.ini
	for (unsigned int i = 0; i < EQUITY_NUM_RECENT_FILES; ++i)
	{
		memset(buffer, 0, 1024);
		fgets(buffer, 1024, ReadRecentFiles);

		char Path[1024];
		strcpy(Path, buffer);
		int Len = strlen(Path);
		Path[Len - 1] = 0;

		mPreviousFiles[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	mHistoryMenu = CreateMenu();

	// Check for empty slots and gray out
	for (int i = EQUITY_NUM_RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);
		if (Result == 0)
		{
			iFlags = MF_GRAYED | MF_DISABLED;
		}

		AppendMenu(mHistoryMenu, MF_STRING | iFlags, EQUITY_RECENT_FILE_ID(i), szText);
	}

	ModifyMenu(GetMenu(App->MainHwnd), ID_FILE_RECENTFILES, MF_BYCOMMAND | MF_POPUP,
		(UINT_PTR)mHistoryMenu, "Recent files");
	return;
}
