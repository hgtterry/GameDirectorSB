/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "ME_Export.h"


ME_Export::ME_Export()
{
	Is_Canceled = 0;
}


ME_Export::~ME_Export()
{
}

// *************************************************************************
// *					Object_Model Terry Bernie						   *
// *************************************************************************
void ME_Export::Object_Model(void)
{
	if (App->CL_Model->Model_Loaded == 0)
	{
		App->Say("No Model Loaded to Export");
		return;
	}

	bool test = App->CL_Export_Object->Create_ObjectFile();

	if (test == 1)
	{
		App->Say("Wavefront Object file Created successfully");
	}
}

// *************************************************************************
// *					Milkshape_Model Terry Bernie					   *
// *************************************************************************
void ME_Export::Milkshape_Model(void)
{
	if (App->CL_Model->Model_Loaded == 1)
	{
		App->CL_Export_Milk->Export_To_Milk(0);

		return;
	}
}

// *************************************************************************
// *					Ogre3D_Model Terry Bernie						   *
// *************************************************************************
void ME_Export::Ogre3D_Model(void)
{
	if (App->CL_Model->Model_Loaded == 0)
	{
		App->Say("No Model Loaded to Export");
		return;
	}

	if (App->CL_Model->Model_Type == Enums::LoadedFile_Actor)
	{
		App->Say("Not available for the Actor format just yet.");
		return;
	}

	App->CL_Export_Ogre3D->Export_AssimpToOgre();
}

// *************************************************************************
// *	  		Start_Export_Dlg:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void ME_Export::Start_Export_Dlg()
{
	App->CL_Export->Is_Canceled = 0;
	DialogBox(App->hInst, (LPCTSTR)IDD_EXPORT_OPTIONS_DLG, App->Fdlg, (DLGPROC)Export_Dlg_Proc);
}
// *************************************************************************
// *        Export_Dlg_Proc:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
LRESULT CALLBACK ME_Export::Export_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_ST_BANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_FOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_BROWSE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_NAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_CHANGE_NAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CK_SUBFOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_SUBFOLDER_NAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_FOLDER_NAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_ST_FLD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_FN, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SetDlgItemText(hDlg, IDC_ST_FOLDER, App->CL_FileIO->szSelectedDir);
		SetDlgItemText(hDlg, IDC_ST_NAME, App->CL_Model->JustName);
		SetDlgItemText(hDlg, IDC_ST_SUBFOLDER_NAME, App->CL_Export_Ogre3D->Directory_Name);
		
		HWND Temp = GetDlgItem(hDlg, IDC_CK_SUBFOLDER);
		SendMessage(Temp, BM_SETCHECK, BST_CHECKED, 0);
		App->CL_Export_Ogre3D->Add_Sub_Folder = 1;

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_ST_FOLDER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_ST_NAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_ST_SUBFOLDER_NAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_CK_SUBFOLDER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_BANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_FLD) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_FN) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
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
		

		if (some_item->idFrom == IDC_BT_FOLDER_NAME && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_CHANGE_NAME && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_BROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDCANCEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_CK_SUBFOLDER)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_SUBFOLDER);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				EnableWindow(GetDlgItem(hDlg, IDC_ST_SUBFOLDER_NAME), 1);
				EnableWindow(GetDlgItem(hDlg, IDC_BT_FOLDER_NAME), 1);
				App->CL_Export_Ogre3D->Add_Sub_Folder = 1;
				return 1;
			}
			else
			{
				EnableWindow(GetDlgItem(hDlg, IDC_ST_SUBFOLDER_NAME),0);
				EnableWindow(GetDlgItem(hDlg, IDC_BT_FOLDER_NAME), 0);
				App->CL_Export_Ogre3D->Add_Sub_Folder = 0;
				return 1;
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_CHANGE_NAME)
		{
			strcpy(App->CL_Dialogs->btext, "Change File Name");
			strcpy(App->CL_Dialogs->Chr_Text, App->CL_Model->JustName);

			App->CL_Dialogs->Dialog_Text();

			if (App->CL_Dialogs->Is_Canceled == 0)
			{
				strcpy(App->CL_Model->JustName, App->CL_Dialogs->Chr_Text);
			}

			SetDlgItemText(hDlg, IDC_ST_NAME, App->CL_Model->JustName);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_FOLDER_NAME)
		{
			strcpy(App->CL_Dialogs->btext, "Change Folder Name");
			strcpy(App->CL_Dialogs->Chr_Text, App->CL_Export_Ogre3D->Directory_Name);

			App->CL_Dialogs->Dialog_Text();

			if (App->CL_Dialogs->Is_Canceled == 0)
			{
				strcpy(App->CL_Export_Ogre3D->Directory_Name, App->CL_Dialogs->Chr_Text);
			}

			SetDlgItemText(hDlg, IDC_ST_SUBFOLDER_NAME, App->CL_Export_Ogre3D->Directory_Name);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_BROWSE)
		{
			strcpy(App->CL_FileIO->BrowserMessage, "Select Folder To Place Ogre Files");
			int Test = App->CL_FileIO->StartBrowser("");
			if (Test == 0) { return 1; }

			SetDlgItemText(hDlg, IDC_ST_FOLDER, App->CL_FileIO->szSelectedDir);

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDOK)
		{
			App->CL_Export->Is_Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CL_Export->Is_Canceled = 1;

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}

	} // Switch End

	return FALSE;
}
