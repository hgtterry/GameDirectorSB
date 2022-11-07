/*
Copyright (c) 2022 GameDirectorSB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Build.h"

SB_Build::SB_Build()
{
}

SB_Build::~SB_Build()
{
}

// *************************************************************************
// *	  	Start_Project_Build:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Build::Start_Project_Build()
{
	//App->CL10_Project->Read_From_Config();

	DialogBox(App->hInst, (LPCTSTR)IDD_BUILD_DIALOG, App->Fdlg, (DLGPROC)Project_Build_Proc);
}

// *************************************************************************
// *		Project_Build_Proc:- Terry and Hazel Flanigan 2022	  		   *
// *************************************************************************
LRESULT CALLBACK SB_Build::Project_Build_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_EDGAMENAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STGAMENAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPATH, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		//SetDlgItemText(hDlg, IDC_EDGAMENAME, (LPCTSTR)App->CL10_Project->GameName);
		//SetDlgItemText(hDlg, IDC_STLOCATION, (LPCTSTR)App->CL10_Project->StartFolder);



		/*if (App->CL10_Project->CF_Full_Screen == 1)
		{
			SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 1, 0);
		}
		else
		{
			SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 0, 0);
		}*/


		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_EDGAMENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		if (GetDlgItem(hDlg, IDC_STLOCATION) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		if (GetDlgItem(hDlg, IDC_CKFULLSCREEN) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		if (GetDlgItem(hDlg, IDC_STGAMENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STPATH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTBROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_CKFULLSCREEN)
		{

			/*if (App->CL10_Project->CF_Full_Screen == 1)
			{
				SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 0, 0);
				App->CL10_Project->CF_Full_Screen = 0;
			}
			else
			{
				SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 1, 0);
				App->CL10_Project->CF_Full_Screen = 1;
			}*/
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTBROWSE)
		{
			/*strcpy(App->SBC_FileIO->BrowserMessage, "Select a Folder for Game Files a Sub folder will be created");
			int Test = App->CL_FileIO->StartBrowser(App->DeskTop_Folder);
			if (Test == 0) { return 1; }
			strcpy(App->CL10_Project->StartFolder, App->CL_FileIO->szSelectedDir);
			SetDlgItemText(hDlg, IDC_STLOCATION, (LPCTSTR)App->CL10_Project->StartFolder);*/

			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			char GameName[255];
			char PathName[255];
			GetDlgItemText(hDlg, IDC_EDGAMENAME, (LPTSTR)GameName, 255);
			GetDlgItemText(hDlg, IDC_STLOCATION, (LPTSTR)PathName, 255);
			int result = 1;

			// Check Name Entered
			result = strcmp(GameName, "");
			if (result == 0)
			{
				App->Say("No Game Name Specified");
				return 1;
			}

			// Check Path Selected
			result = strcmp(PathName, "");
			if (result == 0)
			{
				App->Say("No Path Specified");
				return 1;
			}

			//strcpy(App->CL_FileIO->szSelectedDir, PathName);
			//strcpy(App->CL10_Project->StartFolder, PathName);

			//strcpy(App->CL10_Project->GameName, GameName);

			//App->CL10_Project->Write_To_Config(); // Writre to Config File

			//App->CL10_Project->Create_ProjectFolder();

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;

	}
	return FALSE;
}