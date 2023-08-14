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
#include "SB_Preferences.h"

SB_Preferences::SB_Preferences(void)
{
	WriteData = nullptr;
}

SB_Preferences::~SB_Preferences(void)
{
}

// *************************************************************************
// *	  	Start_Preferences_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
bool SB_Preferences::Start_Preferences_Dlg()
{

	DialogBox(App->hInst, (LPCTSTR)IDD_SB_PREFERENCES, App->MainHwnd, (DLGPROC)Preferences_Dlg_Proc);

	return 1;
}

// *************************************************************************
// *        Preferences_Dlg_Proc:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
LRESULT CALLBACK SB_Preferences::Preferences_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_CK_JUSTEQUITY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CK_NEWEQUITY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		if (App->Just_Equity == 1)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_JUSTEQUITY);
			SendMessage(temp, BM_SETCHECK, 1, 0);
		}
		else
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_JUSTEQUITY);
			SendMessage(temp, BM_SETCHECK, 0, 0);
		}

		
		HWND temp = GetDlgItem(hDlg, IDC_CK_NEWEQUITY);
		SendMessage(temp, BM_SETCHECK, 1, 0);
		

		return TRUE;

	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_CK_JUSTEQUITY) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_CK_NEWEQUITY) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
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

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_CK_JUSTEQUITY)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_JUSTEQUITY);

			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				App->Just_Equity = 1;
				return 1;
			}
			else
			{
				App->Just_Equity = 0;
				return 1;
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			App->CLSB_Preferences->Write_Preferences();
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
	}

	return FALSE;
}

// *************************************************************************
// *						Read_Preferences Terry Flanigan 			   *
// *************************************************************************
bool SB_Preferences::Read_Preferences()
{
	char chr_Tag1[MAX_PATH];
	chr_Tag1[0] = 0;
	
	char Preferences_Path[MAX_PATH];

	strcpy(Preferences_Path, App->WorldEditor_Directory);
	//strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "PreferencesWE.ini");

	App->CLSB_Ini->SetPathName(Preferences_Path);


	App->Just_Equity = App->CLSB_Ini->GetInt("Equity","Just_Equity", 0, 10);
	
	if (App->Just_Equity == 1)
	{
		App->CLSB_Equity->Close_Equity_Flag = 1;
	}
	else
	{
		App->CLSB_Equity->Close_Equity_Flag = 0;
	}

	return 1;
}

// *************************************************************************
// *						Write_Preferences Terry Flanigan 			   *
// *************************************************************************
bool SB_Preferences::Write_Preferences()
{
	WriteData = nullptr;

	char Preferences_Path[MAX_PATH];

	strcpy(Preferences_Path, App->WorldEditor_Directory);
	//strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "PreferencesWE.ini");

	//App->Say(Preferences_Path);

	WriteData = fopen(Preferences_Path, "wt");
	if (!WriteData)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	fprintf(WriteData, "%s\n", "[Equity]");
	fprintf(WriteData, "%s%i\n", "Just_Equity=", App->Just_Equity);
	
	fclose(WriteData);
	
	//Read_Preferences();
	return 1;
}
