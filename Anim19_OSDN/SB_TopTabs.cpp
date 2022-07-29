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
#include "SB_TopTabs.h"


SB_TopTabs::SB_TopTabs()
{
	TabsHwnd = nullptr;

	Tabs_TB_hWnd = nullptr;

	Camera_TB_hWnd = nullptr;
	Dimensions_TB_hWnd = nullptr;
	Physics_TB_hWnd = nullptr;
	Editors_TB_hWnd = nullptr;
	File_TB_hWnd = nullptr;

	MouseOption_DlgHwnd = nullptr;

	// Main Controls
	Toggle_Grid_Flag = 1;
	Toggle_Hair_Flag = 1;

	Toggle_Tabs_Old_Flag = 0;
	Toggle_Tabs_Dimensions_Flag = 0;
	Toggle_Tabs_Shapes_Flag = 0;
	Toggle_Tabs_Editors_Flag = 0;
	Toggle_Tabs_File_Flag = 1;

	Toggle_GroupsOnly_Flag = 0;

	// Camera
	Toggle_FreeCam_Flag = 1;
	Toggle_FirstCam_Flag = 0;
}


SB_TopTabs::~SB_TopTabs()
{
}

// *************************************************************************
// *	  					Reset_Class  	Terry						   *
// *************************************************************************
void SB_TopTabs::Reset_Class()
{

	Toggle_Tabs_Old_Flag = 1;
	Toggle_Tabs_Dimensions_Flag = 0;
	Toggle_GroupsOnly_Flag = 0;

	// Camera
	Toggle_FreeCam_Flag = 1;
	Toggle_FirstCam_Flag = 0;

	Reset_Main_Controls();
	
	App->SBC_TopTabs->Hide_Tabs();
	ShowWindow(App->SBC_TopTabs->File_TB_hWnd, SW_SHOW);
	App->SBC_TopTabs->Toggle_Tabs_Old_Flag = 1;

	RedrawWindow(App->SBC_TopTabs->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	return;
}

// *************************************************************************
// *	  				Start_TopBar_Globals  	Terry					   *
// *************************************************************************
bool SB_TopTabs::Start_TopBar_Globals()
{
	CreateDialog(App->hInst, (LPCTSTR)IDD_TOPBAR, App->Fdlg, (DLGPROC)TopBar_Globals_Proc);
	Init_Bmps_Globals();
	return 1;
}

// *************************************************************************
// *						TopBar_Globals_Proc Terry					   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::TopBar_Globals_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->SBC_TopTabs->TabsHwnd = hDlg;

		App->SBC_TopTabs->Start_Tabs_Headers();
		App->SBC_TopTabs->Start_Camera_TB();
		App->SBC_TopTabs->Start_Dimensions_TB();
		App->SBC_TopTabs->Start_Physics_TB();
		App->SBC_TopTabs->Start_Editors_TB();
		App->SBC_TopTabs->Start_Files_TB();

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_TBSHOWGRID && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_TopTabs->Toggle_Grid_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSHOWHAIR && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_TopTabs->Toggle_Hair_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		//-------------------------------------------------------- Show Grid
		if (LOWORD(wParam) == IDC_TBSHOWGRID)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWGRID);

			if (App->Cl_Grid->ShowGridFlag == 1)
			{
				App->Cl_Grid->Grid_SetVisible(0);
				App->Cl_Grid->ShowGridFlag = 0;

				App->SBC_TopTabs->Toggle_Grid_Flag = 0;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOff_Bmp);
			}
			else
			{
				App->Cl_Grid->Grid_SetVisible(1);
				App->Cl_Grid->ShowGridFlag = 1;

				App->SBC_TopTabs->Toggle_Grid_Flag = 1;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

			}
			return TRUE;
		}

		//-------------------------------------------------------- Show Hair
		if (LOWORD(wParam) == IDC_TBSHOWHAIR)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWHAIR);

			if (App->Cl_Grid->ShowHair == 1)
			{
				App->Cl_Grid->ShowHair = 0;
				App->Cl_Grid->Hair_SetVisible(0);

				App->SBC_TopTabs->Toggle_Hair_Flag = 0;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOff_Bmp);
			}
			else
			{
				App->Cl_Grid->ShowHair = 1;
				App->Cl_Grid->Hair_SetVisible(1);

				App->SBC_TopTabs->Toggle_Hair_Flag = 1;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);
			}
			return TRUE;
		}

		//-------------------------------------------------------- Show Info
		if (LOWORD(wParam) == IDC_TBINFO)
		{
			if (App->CL_Vm_ImGui->Show_Model_Data == 1)
			{
				App->CL_Vm_ImGui->Show_Model_Data = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_Model_Data = 1;
			}
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

// *************************************************************************
// *						Start_Tabs_Headers Terry					   *
// *************************************************************************
void SB_TopTabs::Start_Tabs_Headers(void)
{
	Tabs_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_TAB, App->SBC_TopTabs->TabsHwnd, (DLGPROC)Tabs_Headers_Proc);
}

// *************************************************************************
// *							Tabs_Headers_Proc_Proc					   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::Tabs_Headers_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_CBMOTIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_TBOLD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBDIMENSIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBSHAPES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TAB_EDITORS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBFILE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_TBOLD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->SBC_TopTabs->Toggle_Tabs_Old_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBDIMENSIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->SBC_TopTabs->Toggle_Tabs_Dimensions_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSHAPES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->SBC_TopTabs->Toggle_Tabs_Shapes_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TAB_EDITORS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->SBC_TopTabs->Toggle_Tabs_Editors_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBFILE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->SBC_TopTabs->Toggle_Tabs_File_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_TBFILE)
		{

			App->SBC_TopTabs->Hide_Tabs();
			ShowWindow(App->SBC_TopTabs->File_TB_hWnd, SW_SHOW);
			App->SBC_TopTabs->Toggle_Tabs_File_Flag = 1;

			//App->Cl19_Ogre->OgreListener->ImGui_Render_Tab = Enums::ImGui_Camera;

			RedrawWindow(App->SBC_TopTabs->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBOLD)
		{
			App->SBC_TopTabs->Hide_Tabs();
			ShowWindow(App->SBC_TopTabs->Camera_TB_hWnd, SW_SHOW);
			App->SBC_TopTabs->Toggle_Tabs_Old_Flag = 1;

			App->Cl19_Ogre->OgreListener->ImGui_Render_Tab = Enums::ImGui_Camera;

			//ShowWindow(App->SBC_Physics->PhysicsPannel_Hwnd, SW_SHOW);

			RedrawWindow(App->SBC_TopTabs->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBDIMENSIONS)
		{
			App->SBC_TopTabs->Hide_Tabs();
			ShowWindow(App->SBC_TopTabs->Dimensions_TB_hWnd, SW_SHOW);
			App->SBC_TopTabs->Toggle_Tabs_Dimensions_Flag = 1;

			App->Cl19_Ogre->OgreListener->ImGui_Render_Tab = Enums::ImGui_Dimensions;

			RedrawWindow(App->SBC_TopTabs->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSHAPES)
		{
			App->SBC_TopTabs->Hide_Tabs();

			ShowWindow(App->SBC_TopTabs->Physics_TB_hWnd, SW_SHOW);
			//ShowWindow(App->SBC_Physics->PhysicsPannel_Hwnd, SW_SHOW);

			App->SBC_TopTabs->Toggle_Tabs_Shapes_Flag = 1;

			App->Cl19_Ogre->OgreListener->ImGui_Render_Tab = Enums::ImGui_None;

			RedrawWindow(App->SBC_TopTabs->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TAB_EDITORS)
		{
			App->SBC_TopTabs->Hide_Tabs();

			ShowWindow(App->SBC_TopTabs->Editors_TB_hWnd, SW_SHOW);

			App->SBC_TopTabs->Toggle_Tabs_Editors_Flag = 1;

			App->Cl19_Ogre->OgreListener->ImGui_Render_Tab = Enums::ImGui_None;

			RedrawWindow(App->SBC_TopTabs->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

	}
	}
	return FALSE;
}

// *************************************************************************
// *						Hide_Tabs Terry Berine						   *
// *************************************************************************
void SB_TopTabs::Hide_Tabs(void)
{
	ShowWindow(Camera_TB_hWnd, SW_HIDE);
	ShowWindow(Dimensions_TB_hWnd, SW_HIDE);
	ShowWindow(Physics_TB_hWnd, SW_HIDE);
	ShowWindow(Editors_TB_hWnd, SW_HIDE);
	ShowWindow(File_TB_hWnd, SW_HIDE);

	ShowWindow(App->SBC_Physics->PhysicsPannel_Hwnd, 0);

	Toggle_Tabs_Old_Flag = 0;
	Toggle_Tabs_Dimensions_Flag = 0;
	Toggle_Tabs_Shapes_Flag = 0;
	Toggle_Tabs_Editors_Flag = 0;
	Toggle_Tabs_File_Flag = 0;
}

// *************************************************************************
// *						Reset_Main Controlls Terry Berine			   *
// *************************************************************************
void SB_TopTabs::Reset_Main_Controls(void)
{

	HWND Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWGRID);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWHAIR);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBINFO);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);

	// Main Controls

	Toggle_Hair_Flag = 1;
	App->Cl_Grid->ShowHair = 1;
	App->Cl_Grid->Hair_SetVisible(1);

	Toggle_Grid_Flag = 1;
	App->Cl_Grid->Grid_SetVisible(1);
	App->Cl_Grid->ShowGridFlag = 1;
}

// *************************************************************************
// *						Start_Camera_TB Terry Berine				   *
// *************************************************************************
void SB_TopTabs::Start_Camera_TB(void)
{
	Camera_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB1, Tabs_TB_hWnd, (DLGPROC)Camera_TB_Proc);
	Init_Bmps_Camera();
}

// *************************************************************************
// *								Camera_TB_Proc						   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::Camera_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_TBRESETVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBZOOM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_FIRST_MODE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_FREECAM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
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

		if (some_item->idFrom == IDC_FREECAM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_TopTabs->Toggle_FreeCam_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_FIRST_MODE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_TopTabs->Toggle_FirstCam_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBZOOM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBRESETVIEW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTMOUSESPEED && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_FULLSCREEN && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_TBRESETVIEW)
		{
			App->SBC_Camera->Reset_View();
			return 1;
		}

		if (LOWORD(wParam) == IDC_TBZOOM)
		{
			App->SBC_Camera->Zoom();
			return 1;
		}

		if (LOWORD(wParam) == IDC_BTMOUSESPEED)
		{
			App->Com_CDialogs->Start_Mouse_Sensitivity(App->Fdlg);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_FULLSCREEN)
		{
			App->Cl19_Ogre->Go_FullScreen_Mode();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_FIRST_MODE)
		{
			if (App->SBC_Scene->Player_Added == 1)
			{
				App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;
				App->SBC_TopTabs->Toggle_FirstCam_Flag = 1;
				App->SBC_TopTabs->Toggle_FreeCam_Flag = 0;
				RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_FREECAM)
		{
			App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;
			App->SBC_TopTabs->Toggle_FirstCam_Flag = 0;
			App->SBC_TopTabs->Toggle_FreeCam_Flag = 1;
			RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}


		return FALSE;
	}

	}
	return FALSE;
}

// *************************************************************************
// *						Init_Bmps_Camera Terry Bernie				   *
// *************************************************************************
void SB_TopTabs::Init_Bmps_Camera(void)
{
	HWND hTooltip_TB_1 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	// --------------------------------------------------- 
	HWND Temp = GetDlgItem(Camera_TB_hWnd, IDC_TBRESETVIEW);

	TOOLINFO ti = { 0 };
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti.uId = (UINT_PTR)Temp;
	ti.lpszText = "Reset to Default View";
	ti.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Camera_TB_hWnd, IDC_TBZOOM);

	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Reset and Zoom to fit Model In Window";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Camera_TB_hWnd, IDC_BTMOUSESPEED);

	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti3);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Adujust Mouse and Keys Speed";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti3);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Camera_TB_hWnd, IDC_FULLSCREEN);

	TOOLINFO ti4 = { 0 };
	ti4.cbSize = sizeof(ti4);
	ti4.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti4.uId = (UINT_PTR)Temp;
	ti4.lpszText = "Go Fullscreen Press esc to return";
	ti4.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti4);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Camera_TB_hWnd, IDC_TBMODEL);

	TOOLINFO ti5 = { 0 };
	ti5.cbSize = sizeof(ti5);
	ti5.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti5.uId = (UINT_PTR)Temp;
	ti5.lpszText = "Camera Mode Rotate Model";
	ti5.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti5);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Camera_TB_hWnd, IDC_TBWORLD);

	TOOLINFO ti6 = { 0 };
	ti6.cbSize = sizeof(ti6);
	ti6.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti6.uId = (UINT_PTR)Temp;
	ti6.lpszText = "Camera Mode You Move Around Model";
	ti6.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti6);

	// --------------------------------------------------- 

}

// *************************************************************************
// *						Init_Bmps_Dimensions Terry Bernie			   *
// *************************************************************************
void SB_TopTabs::Init_Bmps_Dimensions(void)
{
	HWND hTooltip_TB_Dim = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	// --------------------------------------------------- 
	HWND Temp = GetDlgItem(Dimensions_TB_hWnd, IDC_TBROTATION);

	TOOLINFO ti = { 0 };
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti.uId = (UINT_PTR)Temp;
	ti.lpszText = "Rotate Model";
	ti.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Dim, TTM_ADDTOOL, 0, (LPARAM)&ti);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Dimensions_TB_hWnd, IDC_TBSCALE);

	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Scale Model";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Dim, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Dimensions_TB_hWnd, IDC_TBPOSITION);

	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti3);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Position Model";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Dim, TTM_ADDTOOL, 0, (LPARAM)&ti3);

}

// *************************************************************************
// *						Init_Bmps_Globals Terry Bernie				   *
// *************************************************************************
void SB_TopTabs::Init_Bmps_Globals(void)
{

	HWND Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWGRID);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWHAIR);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBINFO);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);

	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	Temp = GetDlgItem(TabsHwnd, IDC_TBINFO);
	TOOLINFO ti8 = { 0 };
	ti8.cbSize = sizeof(ti8);
	ti8.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti8.uId = (UINT_PTR)Temp;
	ti8.lpszText = "Show Model Information";
	ti8.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti8);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWHAIR);
	TOOLINFO ti9 = { 0 };
	ti9.cbSize = sizeof(ti9);
	ti9.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti9.uId = (UINT_PTR)Temp;
	ti9.lpszText = "Toggle Main Cross Hair";
	ti9.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti9);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWGRID);
	TOOLINFO ti10 = { 0 };
	ti10.cbSize = sizeof(ti10);
	ti10.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti10.uId = (UINT_PTR)Temp;
	ti10.lpszText = "Toggle Main Grid";
	ti10.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti10);

}

// *************************************************************************
// *						Start_Dimensions_TB Terry					   *
// *************************************************************************
void SB_TopTabs::Start_Dimensions_TB(void)
{
	Dimensions_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_DIMENSIONS, Tabs_TB_hWnd, (DLGPROC)Dimensions_TB_Proc);
	Init_Bmps_Dimensions();
}

// *************************************************************************
// *								Dimensions_TB_Proc					   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::Dimensions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_TBROTATION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBPOSITION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBSCALE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_TBROTATION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_ImGui->Show_Rotation);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBPOSITION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_ImGui->Show_Position);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSCALE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_ImGui->Show_Scale);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_TBROTATION) // Rotation
		{

			if (App->CL_Vm_ImGui->Show_Rotation == 1)
			{
				App->CL_Vm_ImGui->Show_Rotation = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_Rotation = 1;
			}

			RedrawWindow(App->SBC_TopTabs->Dimensions_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBPOSITION) // Position
		{

			if (App->CL_Vm_ImGui->Show_Position == 1)
			{
				App->CL_Vm_ImGui->Show_Position = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_Position = 1;
			}

			RedrawWindow(App->SBC_TopTabs->Dimensions_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSCALE) // Scale
		{

			if (App->CL_Vm_ImGui->Show_Scale == 1)
			{
				App->CL_Vm_ImGui->Show_Scale = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_Scale = 1;
			}

			RedrawWindow(App->SBC_TopTabs->Dimensions_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		return FALSE;
	}
	}
	return FALSE;
}


// *************************************************************************
// *						Start_Physics_TB Terry						   *
// *************************************************************************
void SB_TopTabs::Start_Physics_TB(void)
{
	Physics_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_PHYSICS, Tabs_TB_hWnd, (DLGPROC)Physics_TB_Proc);
	//Init_Bmps_Groups();
}

// *************************************************************************
// *								Shapes_TB_Proc					   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::Physics_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{

		LPNMHDR some_item = (LPNMHDR)lParam;

		

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		
		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *						Start_Editors_TB Terry Flanigan				   *
// *************************************************************************
void SB_TopTabs::Start_Editors_TB(void)
{
	Editors_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_EDITORS, Tabs_TB_hWnd, (DLGPROC)Editors_TB_Proc);
	//Init_Bmps_Groups();
}

// *************************************************************************
// *					Editors_TB_Proc Terry Flanigan					   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::Editors_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_EDITORS_WE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{

		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_EDITORS_WE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_EDITORS_WE)
		{
			App->SBC_Equity->Start_Equity();
			return TRUE;
		}

		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *						Start_Files_TB Terry Flanigan				   *
// *************************************************************************
void SB_TopTabs::Start_Files_TB(void)
{
	File_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_FILE, Tabs_TB_hWnd, (DLGPROC)Files_TB_Proc);
	//Init_Bmps_Groups();
}

// *************************************************************************
// *					Files_TB_Proc Terry Flanigan					   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs::Files_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_TBBTLOAD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBBTQLOAD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBBTRESOURCES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{

		LPNMHDR some_item = (LPNMHDR)lParam;
		
		if (some_item->idFrom == IDC_TBBTRESOURCES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBBTLOAD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBBTQLOAD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_TBBTRESOURCES)
		{
			App->SBC_MeshViewer->StartMeshViewer();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBBTLOAD)
		{

			App->SBC_Import->Load_Scene("Level   *.SBLevel\0*.SBLevel\0", "Level");
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBBTQLOAD)
		{

			App->SBC_Project->Load_Scene_Auto();
			return TRUE;
		}

		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *					Check_Current_Option Terry Bernie				   *
// *************************************************************************
void SB_TopTabs::UnCheck_All_MouseOption(HWND hDlg)
{
	App->Cl_Dialogs->Mouse_Normal2 = 0;
	App->Cl_Dialogs->Mouse_Slow2 = 0;
	App->Cl_Dialogs->Mouse_VerySlow2 = 0;
	App->Cl_Dialogs->Mouse_Fast2 = 0;
}
