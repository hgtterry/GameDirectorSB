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
// *	  				Start_Export_Dlg Terry Flanigan					   *
// *************************************************************************
void ME_Export::Start_Export_Dlg()
{
	App->CL_Export->Is_Canceled = 0;
	DialogBox(App->hInst, (LPCTSTR)IDD_EXPORT_OPTIONS_DLG, App->Fdlg, (DLGPROC)Export_Dlg_Proc);
}
// *************************************************************************
// *        		Export_Dlg_Proc  Terry Flanigan						   *
// *************************************************************************
LRESULT CALLBACK ME_Export::Export_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_ST_FOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_BROWSE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_ST_FOLDER, App->CL_FileIO->szSelectedDir);
		
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

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_BROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
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
