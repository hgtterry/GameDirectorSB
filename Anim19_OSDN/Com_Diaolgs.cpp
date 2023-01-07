/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include <tchar.h>
#include <shellapi.h>
#include "Shlobj.h"
#include "io.h"
#include "Com_Diaolgs.h"


Com_Diaolgs::Com_Diaolgs()
{
	BrowserMessage[0] = 0;
	szSelectedDir[0] = 0;
}


Com_Diaolgs::~Com_Diaolgs()
{
}

// *************************************************************************
// *							StartBrowser   							   *
// *************************************************************************
bool Com_Diaolgs::StartBrowser(char* szInitDir, HWND hDlg)
{
	szSelectedDir[0] = 0;

	TCHAR dname[MAX_PATH * 2];
	IMalloc *imalloc; SHGetMalloc(&imalloc);
	BROWSEINFO bi; ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = hDlg;
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
int __stdcall Com_Diaolgs::BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData)
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
			EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);
			strcpy(App->Com_CDialogs->szSelectedDir, "");
		}
		else
		{
			strcpy(App->Com_CDialogs->szSelectedDir, szDir);
			strcat(App->Com_CDialogs->szSelectedDir, "\\");
		}
	}

	return 0;
}
