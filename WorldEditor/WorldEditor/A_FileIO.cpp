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

#include "stdafx.h"
#include "AB_App.h"
#include "A_FileIO.h"
//#include <shellapi.h>
#include "Shlobj.h"
#include "io.h"

SB_FileIO::SB_FileIO()
{
	FileName[0] = 0;
	PathFileName[0] = 0;
	BrowserMessage[0] = 0;

	szSelectedDir[0] = 0;
}

SB_FileIO::~SB_FileIO()
{

}

// *************************************************************************
// *							StartBrowser   							   *
// *************************************************************************
bool SB_FileIO::StartBrowser(char* szInitDir)
{
	TCHAR dname[MAX_PATH * 2];
	IMalloc* imalloc; SHGetMalloc(&imalloc);
	BROWSEINFO bi; ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = App->MainHwnd;
	bi.pszDisplayName = dname;
	bi.lpszTitle = BrowserMessage;
	bi.lParam = (LPARAM)szInitDir;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	bi.lpfn = BrowseCallbackProc;

	CoInitialize(NULL);
	ITEMIDLIST* pidl = SHBrowseForFolder(&bi);

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
int __stdcall SB_FileIO::BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData)
{
	//Initialization callback message
	if (uMsg == BFFM_INITIALIZED)
	{
		//SendMessage(hWnd, BFFM_SETSELECTION, 1, (LPARAM) szInitialPathName); 

		LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);

		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)path);

	}

	if (uMsg == BFFM_SELCHANGED)
	{
		TCHAR szDir[MAX_PATH * 2] = { 0 };

		BOOL bRet = SHGetPathFromIDList((LPITEMIDLIST)lParam, szDir);
		if (bRet)
		{
			if (_taccess(szDir, 00) != 0)
			{
				bRet = FALSE;
			}
			else
			{
				SHFILEINFO sfi;
				::SHGetFileInfo((LPCTSTR)lParam, 0, &sfi, sizeof(sfi),
					SHGFI_PIDL | SHGFI_ATTRIBUTES);

				if (sfi.dwAttributes & SFGAO_LINK)
					bRet = FALSE;
			}
		}

		if (!bRet)
		{
			::EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);
			strcpy(App->CLSB_FileIO->szSelectedDir, "");
		}
		else
			strcpy(App->CLSB_FileIO->szSelectedDir, szDir);
	}

	return 0;
}

// *************************************************************************
// *				SaveSelectedFile  09/04/04   						   *
// *************************************************************************
bool SB_FileIO::SaveSelectedFile(char* Extension,char* File)
{
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = PathFileName;
	ofn.nMaxFile = sizeof(PathFileName);
	ofn.lpstrFilter =Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = FileName;
	ofn.nMaxFileTitle = sizeof(FileName);
	ofn.lpstrInitialDir = File;
	ofn.lpstrTitle = "Save File";

	ofn.Flags = 
		OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |	
		OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT ;
	if (GetSaveFileName(&ofn) == TRUE)
	{
		return 1;
	}

	return 0;

}

// *************************************************************************
// *						OpenFile Terry Bernie						   *
// *************************************************************************
bool SB_FileIO::Open_File_Model(char* Extension, char* Title, char* StartDirectory)
{
	FileName[0] = 0;
	PathFileName[0] = 0;

	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = PathFileName;						// full path and file name
	ofn.nMaxFile = sizeof(PathFileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(FileName);;
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
// *					CheckExtention  09/04/04   					 	   *
// *************************************************************************
bool SB_FileIO::CheckExtention(char *FileName)
{
	int ch='.';
	char *IsIt;	
	IsIt=strchr(FileName,ch);	

	if (IsIt==NULL) // if no extension . extension return 0
	{
		return 0;
	}	

	return 1; // file name has an extension return 1;
}
