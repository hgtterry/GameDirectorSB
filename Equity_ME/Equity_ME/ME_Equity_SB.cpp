/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "resource.h"
#include "ME_App.h"
#include "ME_Equity_SB.h"


ME_Equity_SB::ME_Equity_SB()
{
}


ME_Equity_SB::~ME_Equity_SB()
{
}

// *************************************************************************
// *	  				 Start_WE_import	Terry Flanigan				   *
// *************************************************************************
bool ME_Equity_SB::Start_WE_import()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_WEQUICKLOAD, App->MainHwnd, (DLGPROC)WE_import_Proc);
	return 1;
}

// *************************************************************************
// *					WE_import_Proc	Terry Flanigan 					   *
// *************************************************************************
LRESULT CALLBACK ME_Equity_SB::WE_import_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_STWEPATHFILE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTXLFILEPATH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		/*SendDlgItemMessage(hDlg, IDC_STQLOGREFILE, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STQLOGREPATH, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));*/

		SetDlgItemText(hDlg, IDC_STWEPATHFILE, (LPCTSTR)App->CL_Prefs->Pref_WE_Path_FileName);
		SetDlgItemText(hDlg, IDC_STTXLFILEPATH, (LPCTSTR)App->CL_Prefs->Pref_Txl_Path_FileName);

		/*SetDlgItemText(hDlg, IDC_STQLOGREFILE, (LPCTSTR)App->Cl_Vm_Preferences->Pref_Ogre_JustFileName);
		SetDlgItemText(hDlg, IDC_STQLOGREPATH, (LPCTSTR)App->Cl_Vm_Preferences->Pref_Ogre_Path);*/

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_STQLOGREFILE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STQLOGREPATH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}*/

		if (GetDlgItem(hDlg, IDC_STWEPATHFILE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STTXLFILEPATH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STATICTXL) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STATICWE) == (HWND)lParam)
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

		if (some_item->idFrom == IDC_3DSBROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TXLBROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_3DSBROWSE)
		{
			int Result = App->CL_FileIO->Open_File_Model("RF World   *.rfw\0*.rfw\0", "RF World rfw", NULL);
			if (Result == 0)
			{
				return 1;
			}

			strcpy(App->CL_Prefs->Pref_WE_Path_FileName, App->CL_FileIO->Model_Path_FileName);
			strcpy(App->CL_Prefs->Pref_WE_JustFileName, App->CL_FileIO->Model_FileName);

			SetDlgItemText(hDlg, IDC_STWEPATHFILE, (LPCTSTR)App->CL_Prefs->Pref_WE_Path_FileName);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TXLBROWSE)
		{

			//int test = App->Cl_Vm_WorldEditor->Txt_OpenFile("Texture Libary   *.txl\0*.txl\0", "Texure Editor", NULL);// S_Prefs[0]->TXLFolder);
			//if (test == 0)
			//{
			//	return 1;
			//}

			//strcpy(App->Cl_Vm_Preferences->Pref_Txl_Path_FileName, App->Cl_Vm_WorldEditor->Txt_Path_FileName);

			//SetDlgItemText(hDlg, IDC_STTXLFILEPATH, (LPCTSTR)App->Cl_Vm_Preferences->Pref_Txl_Path_FileName);

			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			//App->Cl_Vm_Preferences->Write_Preferences();

			App->CL_Model->Clear_Model_And_Reset();

			strcpy(App->CL_FileIO->Model_Path_FileName, App->CL_Prefs->Pref_WE_Path_FileName);
			strcpy(App->CL_FileIO->Model_FileName, App->CL_Prefs->Pref_WE_JustFileName);

			App->CL_Model->Set_Paths();

			App->CL_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;

			bool Test = App->CL_Assimp->LoadFile(App->CL_Prefs->Pref_WE_Path_FileName);
			if (Test == 0)
			{
				App->Say("Failed To Load");
				return 0;
			}

			App->CL_Model->Model_Type = Enums::LoadedFile_Assimp;

			//App->Cl_Vm_WorldEditor->LoadTextures_TXL();

			//App->CL_Vm_Model->Model_Loaded = 1;
			//App->Cl_Vm_WorldEditor->Adjust();

			EndDialog(hDlg, LOWORD(wParam));

			App->CL_Import->Set_Equity();

			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

	}

	break;

	}
	return FALSE;
}
