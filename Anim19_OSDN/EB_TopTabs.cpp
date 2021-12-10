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
#include "EB_TopTabs.h"


EB_TopTabs::EB_TopTabs()
{
	Tabs_hWnd = nullptr;

	File_ETB_hWnd =		nullptr;
	Camera_ETB_hWnd =	nullptr;
	Textures_ETB_hWnd = nullptr;

	TexturesCombo_Hwnd = nullptr;

	Toggle_Tabs_File_Flag = 1;
	Toggle_Tabs_Cam_Flag = 0;
	Toggle_Tabs_Textures_Flag = 0;
}


EB_TopTabs::~EB_TopTabs()
{
}

// *************************************************************************
// *						Start_Tabs_Headers Terry					   *
// *************************************************************************
void EB_TopTabs::Start_Tabs(void)
{
	Tabs_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_ETB_TAB1, App->SBC_Equity->MeshViewDialog_Hwnd, (DLGPROC)Tabs_Proc);

	Start_Files_ETB();
	Start_Camera_ETB();
	Start_Textures_ETB();

	ShowWindow(File_ETB_hWnd, SW_SHOW);
}

// *************************************************************************
// *								Tabs_Proc_Proc						   *
// *************************************************************************
LRESULT CALLBACK EB_TopTabs::Tabs_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_ETBFILE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ETBCAM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ETBBTTEXTURES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_ETBFILE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->EBC_TopTabs->Toggle_Tabs_File_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_ETBCAM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->EBC_TopTabs->Toggle_Tabs_Cam_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_ETBBTTEXTURES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->EBC_TopTabs->Toggle_Tabs_Textures_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_ETBFILE)
		{

			App->EBC_TopTabs->Hide_Tabs();
			ShowWindow(App->EBC_TopTabs->File_ETB_hWnd, SW_SHOW);
			App->EBC_TopTabs->Toggle_Tabs_File_Flag = 1;

			RedrawWindow(App->EBC_TopTabs->Tabs_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ETBCAM)
		{
			App->EBC_TopTabs->Hide_Tabs();
			ShowWindow(App->EBC_TopTabs->Camera_ETB_hWnd, SW_SHOW);
			App->EBC_TopTabs->Toggle_Tabs_Cam_Flag = 1;

			RedrawWindow(App->EBC_TopTabs->Tabs_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ETBBTTEXTURES)
		{
			App->EBC_TopTabs->Hide_Tabs();
			ShowWindow(App->EBC_TopTabs->Textures_ETB_hWnd, SW_SHOW);
			App->EBC_TopTabs->Toggle_Tabs_Textures_Flag = 1;

			//App->CL_Vm_Groups->Start_Groups();
			ShowWindow(App->EBC_Groups->RightGroups_Hwnd, SW_SHOW);

			RedrawWindow(App->EBC_TopTabs->Tabs_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

	}

	}
	return FALSE;
}

// *************************************************************************
// *						Start_Files_TB Terry Flanigan				   *
// *************************************************************************
void EB_TopTabs::Start_Files_ETB(void)
{
	File_ETB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_ETB_FILE, Tabs_hWnd, (DLGPROC)Files_ETB_Proc);
}

// *************************************************************************
// *					Files_TB_Proc Terry Flanigan					   *
// *************************************************************************
LRESULT CALLBACK EB_TopTabs::Files_ETB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_TBBTELOAD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBBTEQLOAD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_ETBBTUPDATE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ETBBTCONVERT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{

		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_TBBTELOAD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBBTEQLOAD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_ETBBTUPDATE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_ETBBTCONVERT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_TBBTELOAD)
		{
			Debug1
			//App->SBC_Import->Load_Scene("Level   *.SBLevel\0*.SBLevel\0", "Level");
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBBTEQLOAD)
		{
			char mFileName[1024];
			strcpy(mFileName,"C:\\Users\\Equity\\Desktop\\Models\\Obj_Models\\Cube.obj");
			App->SBC_Import->Reload_FromResentFiles(mFileName);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ETBBTUPDATE)
		{
			App->SBC_Equity->Update_Model();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ETBBTCONVERT)
		{
			App->SBC_Equity->Convert_Model();
			return TRUE;
		}

		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *						Start_Camera_TB Terry Berine				   *
// *************************************************************************
void EB_TopTabs::Start_Camera_ETB(void)
{
	Camera_ETB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_ETB_CAM, Tabs_hWnd, (DLGPROC)Camera_ETB_Proc);
	//Init_Bmps_Camera();
}

// *************************************************************************
// *								Camera_TB_Proc						   *
// *************************************************************************
LRESULT CALLBACK EB_TopTabs::Camera_ETB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_ETBRESETVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ETBZOOM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTMOUSESPEED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_FULLSCREEN, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_ETBZOOM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_ETBRESETVIEW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_ETBRESETVIEW)
		{
			App->SBC_Equity->Reset_View();
			return 1;
		}

		if (LOWORD(wParam) == IDC_ETBZOOM)
		{
			App->SBC_Equity->Zoom();
			return 1;
		}

		return FALSE;
	}

	}
	return FALSE;
}

// *************************************************************************
// *						Start_Files_TB Terry Flanigan				   *
// *************************************************************************
void EB_TopTabs::Start_Textures_ETB(void)
{
	Textures_ETB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_ETB_TEXTURES, Tabs_hWnd, (DLGPROC)Textures_ETB_Proc);
}

// *************************************************************************
// *					Textures_TB_Proc Terry Flanigan					   *
// *************************************************************************
LRESULT CALLBACK EB_TopTabs::Textures_ETB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_CBTEXTURES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		App->EBC_TopTabs->TexturesCombo_Hwnd = GetDlgItem(hDlg, IDC_CBTEXTURES);
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{

		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_TBBTELOAD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_CBTEXTURES)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				HWND temp = GetDlgItem(hDlg, IDC_CBTEXTURES);
				int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
				App->EBC_Groups->Update_Groups_Dialog(Index);
				
			}
			}

			return TRUE;
		}

		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *						Hide_Tabs Terry Berine						   *
// *************************************************************************
void EB_TopTabs::Hide_Tabs(void)
{
	ShowWindow(File_ETB_hWnd, SW_HIDE);
	ShowWindow(Camera_ETB_hWnd, SW_HIDE);
	ShowWindow(Textures_ETB_hWnd, SW_HIDE);

	Toggle_Tabs_File_Flag = 0;
	Toggle_Tabs_Cam_Flag = 0;
	Toggle_Tabs_Textures_Flag = 0;
	
}

// *************************************************************************
// *					Update_Textures_Combo Terry Berine				   *
// *************************************************************************
void EB_TopTabs::Update_Textures_Combo(void)
{
	SendMessage(TexturesCombo_Hwnd, CB_RESETCONTENT, 0, 0);

	int Count = 0;
	while (Count < App->CL_Vm_Model->GroupCount)
	{
		SendMessage(TexturesCombo_Hwnd, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->CL_Vm_Model->S_MeshGroup[Count]->Text_FileName);
		Count++;
	}

	SendMessage(TexturesCombo_Hwnd, CB_SETCURSEL, 0, 0);
}
