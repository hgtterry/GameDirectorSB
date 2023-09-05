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
#include "SB_Properties.h"

SB_Properties::SB_Properties()
{
	Properties_Dlg_hWnd = nullptr;
}

SB_Properties::~SB_Properties()
{
}

// *************************************************************************
// *					Start_GD_Properties Terry Bernie   		 	 	   *
// *************************************************************************
void SB_Properties::Start_GD_Properties(void)
{
	/*if (Properties_Dlg_Active == 1)
	{
		return;
	}*/

	//Properties_Dlg_Active = 1;
	//HMENU mMenu = GetMenu(App->MainHwnd);
	//CheckMenuItem(mMenu, ID_WINDOWS_PROPERTIES, MF_BYCOMMAND | MF_CHECKED);

	Properties_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_PROPERTIES, App->Equity_Dlg_hWnd, (DLGPROC)GD_Properties_Proc);
	//ShowWindow(Properties_Dlg_hWnd, 1);

	//Init_Bmps_Properties();

	//Create_Properties_hLV();

}

// *************************************************************************
// *					GD_Properties_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK SB_Properties::GD_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		/*SendDlgItemMessage(hDlg, IDC_STOBJECTNAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		App->SBC_Properties->Edit_Category = Enums::FV_Edit_Object;*/

		return 1;
	}

	case WM_CTLCOLORSTATIC:
	{

		/*if (GetDlgItem(hDlg, IDC_STOBJECTNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->DialogBackGround;
		}*/

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_CLOSE:
	{
		/*App->SBC_Properties->Properties_Dlg_Active = 0;

		HMENU mMenu = GetMenu(App->MainHwnd);
		CheckMenuItem(mMenu, ID_WINDOWS_PROPERTIES, MF_BYCOMMAND | MF_UNCHECKED);

		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 0);*/

		break;
	}

	case WM_NOTIFY:
	{
		/*LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->hwndFrom == App->SBC_Properties->Properties_hLV)
		{
			switch (some_item->code)
			{
			case NM_CLICK:
			{
				App->SBC_Properties->ListView_OnClickOptions(lParam);
			}
			}
		}

		if (some_item->idFrom == IDC_BT_OBJECTHELP2 && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		/*if (LOWORD(wParam) == IDC_BT_OBJECTHELP2)
		{
			if (App->SBC_Properties->Edit_Category == Enums::FV_Edit_Level)
			{
				App->Cl_Utilities->OpenHTML("Help\\LevelFolder.html");
				return 1;
			}

			return 1;

		}*/

		break;
	}
	}
	return FALSE;
}
