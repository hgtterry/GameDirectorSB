#include "stdafx.h"
#include "GD19_App.h"
#include <tchar.h>
#include <shellapi.h>
#include "Shlobj.h"
#include "io.h"
#include "VM_FileIO.h"


VM_FileIO::VM_FileIO()
{

	Scene_FileName[0] = 0;
	Scene_Path_FileName[0] = 0;

	Model_FileName[0] = 0;
	Model_Path_FileName[0] = 0;

	Cannceled = 0;
}


VM_FileIO::~VM_FileIO()
{
}

// *************************************************************************
// *					Vm_OpenFile Terry Bernie						   *
// *************************************************************************
bool VM_FileIO::Vm_OpenFile(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Model_FileName, "");
	strcpy(Model_Path_FileName, "");

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
// *					OpenFile Terry Bernie							   *
// *************************************************************************
bool VM_FileIO::OpenFile(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Scene_FileName, "");
	strcpy(Scene_Path_FileName, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Scene_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Scene_Path_FileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Scene_FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Scene_FileName);;
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

// ************************************************************************
// *						SaveFileCom Terry Bernie		 		 	   *
// *************************************************************************
bool VM_FileIO::SaveFileCom(char* Extension, char* Title, char* StartDirectory)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = mSavePathFileCom;
	ofn.nMaxFile = sizeof(mSavePathFileCom);
	ofn.lpstrFilter = Extension;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = mSaveFileCom;
	ofn.nMaxFileTitle = sizeof(mSaveFileCom);
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = //OFN_PATHMUSTEXIST |
		OFN_NOCHANGEDIR |
		//OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		return 1;
	}

	return 0;
}

// *************************************************************************
// *							SaveFile		  			  		 	   *
// *************************************************************************
bool VM_FileIO::SaveFile(char* Extension, char* Title, char* FileName)
{

	Full_Path_And_File[0] = 0;
	Just_FileName[0] = 0;

	strcpy(Full_Path_And_File, FileName);
	strcpy(Just_FileName, FileName);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Full_Path_And_File; // Full Path
	ofn.nMaxFile = sizeof(Full_Path_And_File);
	ofn.lpstrFilter = Extension;
	;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Just_FileName;
	ofn.nMaxFileTitle = sizeof(Just_FileName); // Just File name
	ofn.lpstrInitialDir = "";
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn) == TRUE)
	{

		return 1;
	}

	return 0;
}

// *************************************************************************
// *					GetColor   Terry Bernie							   *
// *************************************************************************
bool VM_FileIO::GetColor()
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

// *************************************************************************
// *							Update_File_Info Terry		  	  	 	   *
// *************************************************************************
bool VM_FileIO::Update_File_Info(char* Full_Path, char* File_Name)
{
	strcpy(App->Cl_Scene_Data->S_Scene[0]->TerrainFileName, File_Name);
	strcpy(App->Cl_Scene_Data->S_Scene[0]->GDSceneName, File_Name);
	strcpy(App->Cl_Scene_Data->S_Scene[0]->Full_Path_AndFile, Full_Path);

	char mPath[256];
	strcpy(mPath, Full_Path);
	int FLen = strlen(File_Name);
	int PLen = strlen(Full_Path);
	mPath[PLen - FLen] = 0;
	strcpy(App->LevelDirectory, mPath);
	strcpy(App->Cl_Scene_Data->S_Scene[0]->Level_Directory, mPath);

	char Temp[256];
	strcpy(Temp, File_Name);
	int Len = strlen(Temp);
	Temp[Len - 8] = 0;
	strcpy(App->Cl_Scene_Data->S_Scene[0]->LevelName, Temp);

	return 0;
}

// *************************************************************************
// *					SearchFolders Terry Bernie			 		 	   *
// *************************************************************************
bool VM_FileIO::SearchFolders(char* Path, char* File)
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
// *							StartBrowser   							   *
// *************************************************************************
bool VM_FileIO::StartBrowser(char* szInitDir)
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
int __stdcall VM_FileIO::BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData)
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
			strcpy(App->Cl_File_IO->szSelectedDir, "");
		}
		else
			strcpy(App->Cl_File_IO->szSelectedDir, szDir);
	}

	return 0;
}

