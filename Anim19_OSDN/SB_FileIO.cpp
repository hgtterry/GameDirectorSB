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

#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "SB_FileIO.h"


SB_FileIO::SB_FileIO()
{
	Texture_FileName[0] = 0;
	Texture_Path_FileName[0] = 0;

	Project_File_Name[0] = 0;
	Project_Path_File_Name[0] = 0;

	strcpy(Data_mFilename, "No Set");
	strcpy(Data_Path_mFilename, "No Set");

	JustFileName[0] = 0;

	Cannceled = 0;
}


SB_FileIO::~SB_FileIO()
{
}

// *************************************************************************
// *					Open_Project_File Terry Flanigan				   *
// *************************************************************************
bool SB_FileIO::Open_Project_File(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Project_File_Name, "");
	strcpy(Project_Path_File_Name, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Project_Path_File_Name;						// full path and file name
	ofn.nMaxFile = sizeof(Project_Path_File_Name);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Project_File_Name;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Project_File_Name);
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		strcpy(Data_mFilename, Project_File_Name);
		strcpy(Data_Path_mFilename, Project_Path_File_Name);
		return 1;
	}

	return 0;
}

// *************************************************************************
// *					OpenTextureFile Terry Bernie			  	 	   *
// *************************************************************************
bool SB_FileIO::OpenTextureFile(char* Title, char* StartDirectory, bool SaveLocation)
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
// *						Init_History() Terry Bernie					   *
// *************************************************************************
void  SB_FileIO::Init_History()
{
	char DirCheck[1024];
	strcpy(DirCheck, UserData_Folder);
	strcat(DirCheck, "\\");
	strcat(DirCheck, "Equity");

	bool check = 0;
	check = Check_File_Exist(DirCheck);
	if (check == 0)
	{
		mPreviousFiles.resize(EQUITY_NUM_RECENT_FILES);

		CreateDirectory(DirCheck, NULL);

		char buf[1024];
		strcpy(buf, UserData_Folder);
		strcat(buf, "\\Equity\\Equity_SB.ini");
		WriteRecentFiles = fopen(buf, "wt");
		fclose(WriteRecentFiles);

		ResentHistory_Clear(1); // Set all slots to Empty
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
void  SB_FileIO::LoadHistory()
{
	mPreviousFiles.resize(EQUITY_NUM_RECENT_FILES);

	char buffer[1024];
	char buf[1024];

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Equity\\Equity_SB.ini");

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
// *					RecentFileHistory_Update Terry Bernie			   *
// *************************************************************************
void  SB_FileIO::RecentFileHistory_Update()
{
	if (!mHistoryMenu)return;

	std::string sz = std::string(App->SBC_FileIO->Project_Path_File_Name);
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
void  SB_FileIO::ResentHistory_Clear(bool FirstTime)
{
	if (FirstTime == 0)
	{
		App->SBC_Dialogs->YesNo("Delete file history.", "Are you sure all File history will be Deleted Procede.", 1);
		if (App->Cl_Dialogs->Canceled == 1)
		{
			return;
		}
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
// *					Save_FileHistory Terry Bernie					   *
// *************************************************************************
void  SB_FileIO::Save_FileHistory()
{

	//	WriteRecentFiles = 0;

	char buf[1024];
	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Equity\\Equity_SB.ini");


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
// *					SearchFolders Terry Bernie			 		 	   *
// *************************************************************************
bool SB_FileIO::SearchFolders(char* Path, char* File)
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
// *		Check_File_Exist:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
bool SB_FileIO::Check_File_Exist(char* Full_Path)
{
	char pSearchPath[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(pSearchPath, Full_Path);

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
// *					Directory_Vaild Terry Flanigan	   				   *
// *************************************************************************
bool SB_FileIO::Directory_Vaild(LPCTSTR szPath)
{
	DWORD dwAttrib = GetFileAttributes(szPath);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES &&
		(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

// *************************************************************************
// *						CheckPath Terry Bernie	   					   *
// *************************************************************************
void SB_FileIO::CheckPath(char *pString, char *FileName)
{
	JustFileName[0] = 0;

	int Count = 0;
	int Mark = 0;
	bool Test = 0;

	while (*pString != 0)
	{
		if (*pString == '\\' || *pString == '/')
		{
			Test = 1;
			Mark = Count;
		}

		Count++;
		pString++;
	}

	if (Mark == 0 && Test == 0)
	{
		strcpy(JustFileName, FileName);
	}
	else
	{
		if (Mark == 0 && Test == 1)
		{
			Mark = 1;
			strcpy(JustFileName, (FileName + Mark));
		}
		else
		{
			strcpy(JustFileName, (FileName + Mark) + 1);
		}
	}
}

// *************************************************************************
// *					GetColor   Terry Bernie							   *
// *************************************************************************
bool SB_FileIO::GetColor()
{
	Cannceled = 0;
	COLORREF ccref[8];//custom colors
	COLORREF selcolor = 0x000000;//the default selected color

	memset(&color, 0, sizeof(color));
	color.lStructSize = sizeof(CHOOSECOLOR);
	color.hwndOwner = App->MainHwnd;
	color.lpCustColors = ccref;
	color.rgbResult = selcolor;
	color.Flags = CC_RGBINIT;

	if (ChooseColor(&color))
	{
		Cannceled = 0;
		selcolor = color.rgbResult;
		return 1;
	}

	Cannceled = 1;
	return 1;
}
