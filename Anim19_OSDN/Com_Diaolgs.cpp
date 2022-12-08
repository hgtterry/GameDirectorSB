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
// *	  				Start_Mouse_SensitivityTerry Bernie				   *
// *************************************************************************
void Com_Diaolgs::Start_Mouse_Sensitivity(HWND hDlg)
{
	DialogBox(App->hInst, (LPCTSTR)IDD_MOUSESENSITIVITY, hDlg, (DLGPROC)Mouse_Sensitivity_Proc);
}
// *************************************************************************
// *				Dialog_OgreReloadMesh_Proc Terry Bernie	  			   *
// *************************************************************************
LRESULT CALLBACK Com_Diaolgs::Mouse_Sensitivity_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STBANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_CKNORMAL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKSLOW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKVERYSLOW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKFAST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		App->SBC_TopTabs->MouseOption_DlgHwnd = hDlg;

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STBANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		/*if (GetDlgItem(hDlg, IDC_CKUSER1) == (HWND)lParam)
		{
		SetBkColor((HDC)wParam, RGB(0, 255, 0));
		SetTextColor((HDC)wParam, RGB(0, 0, 0));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (UINT)App->AppBackground;
		}*/
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_CKNORMAL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dialogs->Mouse_Normal2);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CKSLOW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dialogs->Mouse_Slow2);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CKVERYSLOW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dialogs->Mouse_VerySlow2);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CKFAST && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Dialogs->Mouse_Fast2);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_CKNORMAL)
		{
			if (App->SBC_Ogre->OgreListener->Equity_Running == 1)
			{
				//App->EBC_Listener->mMoveSensitivity = 50;
				//App->EBC_Listener->mMoveSensitivityMouse = 50;
			}
			else
			{
				App->SBC_Ogre->OgreListener->mMoveSensitivity = 50;
				App->SBC_Ogre->OgreListener->mMoveSensitivityMouse = 50;
			}

			App->SBC_TopTabs->UnCheck_All_MouseOption(hDlg);
			App->Cl_Dialogs->Mouse_Normal2 = 1;

			InvalidateRect(hDlg, NULL, false);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKSLOW)
		{
			if (App->SBC_Ogre->OgreListener->Equity_Running == 1)
			{
				//App->EBC_Listener->mMoveSensitivity = 5;
				//App->EBC_Listener->mMoveSensitivityMouse = 5;
			}
			else
			{
				App->SBC_Ogre->OgreListener->mMoveSensitivity = 5;
				App->SBC_Ogre->OgreListener->mMoveSensitivityMouse = 5;
			}

			App->SBC_TopTabs->UnCheck_All_MouseOption(hDlg);
			App->Cl_Dialogs->Mouse_Slow2 = 1;

			InvalidateRect(hDlg, NULL, false);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKVERYSLOW)
		{
			if (App->SBC_Ogre->OgreListener->Equity_Running == 1)
			{
				//App->EBC_Listener->mMoveSensitivity = 1;
				//App->EBC_Listener->mMoveSensitivityMouse = 1;
			}
			else
			{
				App->SBC_Ogre->OgreListener->mMoveSensitivity = 1;
				App->SBC_Ogre->OgreListener->mMoveSensitivityMouse = 1;
			}

			App->SBC_TopTabs->UnCheck_All_MouseOption(hDlg);
			App->Cl_Dialogs->Mouse_VerySlow2 = 1;

			InvalidateRect(hDlg, NULL, false);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKFAST)
		{
			if (App->SBC_Ogre->OgreListener->Equity_Running == 1)
			{
				//App->EBC_Listener->mMoveSensitivity = 250;
				//App->EBC_Listener->mMoveSensitivityMouse = 250;
			}
			else
			{
				App->SBC_Ogre->OgreListener->mMoveSensitivity = 250;
				App->SBC_Ogre->OgreListener->mMoveSensitivityMouse = 250;
			}


			App->SBC_TopTabs->UnCheck_All_MouseOption(hDlg);
			App->Cl_Dialogs->Mouse_Fast2 = 1;

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		/*if (LOWORD(wParam) == IDC_BTTEST)
		{
		App->Say("Test");
		return TRUE;
		}*/

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
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
			::EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);
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
