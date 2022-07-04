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
#include "ME_App.h"
#include "resource.h"
#include "ME_TopBar.h"


ME_TopBar::ME_TopBar()
{
	TabsHwnd = nullptr;
	Tabs_TB_hWnd = nullptr;

	Group_TB_hWnd = nullptr;
	Model_TB_hWnd = nullptr;
	Camera_TB_hWnd = nullptr;

	Show_Model_Data = 0;
	Toggle_Grid_Flag = 1;
	Toggle_BBox_Flag = 0;
	Toggle_Faces_Flag = 0;

	Toggle_Tabs_Group_Flag = 0;
	Toggle_Tabs_Model_Flag = 1;
	Toggle_Tabs_Camera_Flag = 0;

	Toggle_Dimensions_Flag = 0;

	Toggle_Group_ONLY_Flag = 0;
	Toggle_Group_HIDE_Flag = 0;
	Toggle_Group_ALL_Flag = 1;

	Toggle_GroupInfo_Flag = 0;
}


ME_TopBar::~ME_TopBar()
{
}

// *************************************************************************
// *					Reaet_Class Terry Flanigan						   *
// *************************************************************************
void ME_TopBar::Reset_Class(void)
{
	Hide_Tabs();

	Toggle_Dimensions_Flag = 0;
	Toggle_Group_ONLY_Flag = 0;
	Toggle_Group_HIDE_Flag = 0;
	Toggle_Group_ALL_Flag = 1;
	Toggle_GroupInfo_Flag = 0;

	Toggle_Tabs_Model_Flag = 1;

	ShowWindow(Model_TB_hWnd, SW_SHOW);

	App->CL_TopBar->Toggle_Dimensions_Flag = 0;
	App->CL_ImGui->Show_Dimensions = 0;
	App->CL_Panels->Show_Panels(1);

	RedrawWindow(App->CL_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *	  				Start_TopBar_Globals  	Terry					   *
// *************************************************************************
bool ME_TopBar::Start_TopBar()
{
	TabsHwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TOPBAR, App->Fdlg, (DLGPROC)TopBar_Proc);
	Init_Bmps_Globals();
	return 1;
}

// *************************************************************************
// *						TopBar_Globals_Proc Terry					   *
// *************************************************************************
LRESULT CALLBACK ME_TopBar::TopBar_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->CL_TopBar->TabsHwnd = hDlg;

		App->CL_TopBar->Start_Tabs_Headers();

		App->CL_TopBar->Start_Group_TB();
		App->CL_TopBar->Start_Model_TB();
		App->CL_TopBar->Start_Camera_TB();

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

	case WM_COMMAND:

		//-------------------------------------------------------- Show Grid
		if (LOWORD(wParam) == IDC_TBSHOWGRID)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWGRID);

			if (App->CL_Grid->ShowGridFlag == 1)
			{
				App->CL_Grid->Grid_SetVisible(0);
				App->CL_Grid->ShowGridFlag = 0;

				App->CL_TopBar->Toggle_Grid_Flag = 0;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOff_Bmp);
			}
			else
			{
				App->CL_Grid->Grid_SetVisible(1);
				App->CL_Grid->ShowGridFlag = 1;

				App->CL_TopBar->Toggle_Grid_Flag = 1;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

			}
			return TRUE;
		}

		//-------------------------------------------------------- Show Hair
		if (LOWORD(wParam) == IDC_TBSHOWHAIR)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWHAIR);

			if (App->CL_Grid->ShowHair == 1)
			{
				App->CL_Grid->ShowHair = 0;
				App->CL_Grid->Hair_SetVisible(0);

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOff_Bmp);
			}
			else
			{
				App->CL_Grid->ShowHair = 1;
				App->CL_Grid->Hair_SetVisible(1);

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);
			}
			return TRUE;
		}

		//-------------------------------------------------------- Show Info
		if (LOWORD(wParam) == IDC_TBINFO)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_TBINFO);

			SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfoOn_Bmp);

			App->CL_Panels->Enable_Panels(0);

			App->CL_Dialogs->What_List = Enums::Show_List_Model;
			App->CL_Dialogs->Show_ListData();

			App->CL_Panels->Enable_Panels(1);

			SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSHOWFACES)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWFACES);

				if (App->CL_Ogre->RenderListener->ShowFaces == 1)
				{
				if (App->CL_Ogre->RenderListener->ShowFaces == 1)
					App->CL_Ogre->RenderListener->ShowFaces = 0;

					App->CL_TopBar->Toggle_Faces_Flag = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);
				}
				else
				{
					App->CL_Ogre->RenderListener->ShowFaces = 1;
					App->CL_TopBar->Toggle_Faces_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOn_Bmp);
				}
			}
			return TRUE;
		}

		//-------------------------------------------------------- Show Textures
		if (LOWORD(wParam) == IDC_BTSHOWTEXTURES)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_BTSHOWTEXTURES);

				if (App->CL_Ogre->RenderListener->ShowTextured == 1)
				{
					App->CL_Ogre->RenderListener->ShowTextured = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);
				}
				else
				{
					App->CL_Ogre->RenderListener->ShowTextured = 1;
					
					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOn_Bmp);
				}
			}
			return TRUE;
		}
		
		//-------------------------------------------------------- Show Normals
		if (LOWORD(wParam) == IDC_BTSHOWNORMALS)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_BTSHOWNORMALS);

				if (App->CL_Ogre->RenderListener->ShowNormals == 1)
				{
					App->CL_Ogre->RenderListener->ShowNormals = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);
				}
				else
				{
					App->CL_Ogre->RenderListener->ShowNormals = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOn_Bmp);
				}
			}
			return TRUE;
		}

		//-------------------------------------------------------- Show Light
		if (LOWORD(wParam) == IDC_BTSHOWLIGHT)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_BTSHOWLIGHT);

				if (App->CL_Ogre->RenderListener->Light_Activated == 1)
				{
					App->CL_Ogre->RenderListener->Light_Activated = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);
				}
				else
				{
					App->CL_Ogre->RenderListener->Light_Activated = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOn_Bmp);
				}
			}
			return TRUE;
		}

		//-------------------------------------------------------- Show Points
		if (LOWORD(wParam) == IDC_BTSHOWPOINTS)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_BTSHOWPOINTS);

				if (App->CL_Ogre->RenderListener->ShowPoints == 1)
				{
					App->CL_Ogre->RenderListener->ShowPoints = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);
				}
				else
				{
					App->CL_Ogre->RenderListener->ShowPoints = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOn_Bmp);
				}
			}
			return TRUE;
		}
		
		//-------------------------------------------------------- Show Bound Box
		if (LOWORD(wParam) == IDC_TBBOUNDBOX)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBBOUNDBOX);

				if (App->CL_Ogre->RenderListener->ShowBoundingBox == 1)
				{
					App->CL_Ogre->RenderListener->ShowBoundingBox = 0;
					App->CL_TopBar->Toggle_BBox_Flag = 0;


					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOff_Bmp);
				}
				else
				{
					App->CL_Ogre->RenderListener->ShowBoundingBox = 1;
					App->CL_TopBar->Toggle_BBox_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOn_Bmp);
				}
			}
			return TRUE;
		}
		break;
	}
	return FALSE;
}

// *************************************************************************
// *						Init_Bmps_Globals Terry Bernie				   *
// *************************************************************************
void ME_TopBar::Init_Bmps_Globals(void)
{

	HWND Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWGRID);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWHAIR);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBINFO);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBBOUNDBOX);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWFACES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);
	
	Temp = GetDlgItem(TabsHwnd, IDC_BTSHOWTEXTURES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);
	
	Temp = GetDlgItem(TabsHwnd, IDC_BTSHOWPOINTS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_BTSHOWBONES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_BTSHOWNORMALS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_BTSHOWLIGHT);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);

	
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

	Temp = GetDlgItem(TabsHwnd, IDC_TBBOUNDBOX);
	TOOLINFO ti11 = { 0 };
	ti11.cbSize = sizeof(ti11);
	ti11.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti11.uId = (UINT_PTR)Temp;
	ti11.lpszText = "Toggle Bounding Box";
	ti11.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti11);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWFACES);
	TOOLINFO ti12 = { 0 };
	ti12.cbSize = sizeof(ti12);
	ti12.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti12.uId = (UINT_PTR)Temp;
	ti12.lpszText = "Toggle Show Faces";
	ti12.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti12);

	Temp = GetDlgItem(TabsHwnd, IDC_BTSHOWTEXTURES);
	TOOLINFO ti13 = { 0 };
	ti13.cbSize = sizeof(ti13);
	ti13.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti13.uId = (UINT_PTR)Temp;
	ti13.lpszText = "Toggle Show Textures";
	ti13.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti13);

	Temp = GetDlgItem(TabsHwnd, IDC_BTSHOWPOINTS);
	TOOLINFO ti14 = { 0 };
	ti14.cbSize = sizeof(ti14);
	ti14.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti14.uId = (UINT_PTR)Temp;
	ti14.lpszText = "Toggle Show Mesh Points";
	ti14.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti14);
	
	Temp = GetDlgItem(TabsHwnd, IDC_BTSHOWBONES);
	TOOLINFO ti15 = { 0 };
	ti15.cbSize = sizeof(ti15);
	ti15.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti15.uId = (UINT_PTR)Temp;
	ti15.lpszText = "Toggle Show Bones";
	ti15.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti15);

	Temp = GetDlgItem(TabsHwnd, IDC_BTSHOWNORMALS);
	TOOLINFO ti16 = { 0 };
	ti16.cbSize = sizeof(ti16);
	ti16.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti16.uId = (UINT_PTR)Temp;
	ti16.lpszText = "Toggle Show Normals";
	ti16.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti16);
	
	Temp = GetDlgItem(TabsHwnd, IDC_BTSHOWLIGHT);
	TOOLINFO ti17 = { 0 };
	ti17.cbSize = sizeof(ti17);
	ti17.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti17.uId = (UINT_PTR)Temp;
	ti17.lpszText = "Toggle Show Light";
	ti17.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti17);
	
}

// *************************************************************************
// *						Start_Tabs_Headers Terry					   *
// *************************************************************************
void ME_TopBar::Start_Tabs_Headers(void)
{
	Tabs_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_TAB, TabsHwnd, (DLGPROC)Tabs_Headers_Proc);
}

// *************************************************************************
// *							Tabs_Headers_Proc_Proc					   *
// *************************************************************************
LRESULT CALLBACK ME_TopBar::Tabs_Headers_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_TBGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBMODEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBCAMERA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_TBGROUP && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_TopBar->Toggle_Tabs_Group_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBMODEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_TopBar->Toggle_Tabs_Model_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBCAMERA && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_TopBar->Toggle_Tabs_Camera_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_TBGROUP)
		{
			App->CL_TopBar->Hide_Tabs();
			ShowWindow(App->CL_TopBar->Group_TB_hWnd, SW_SHOW);
			App->CL_TopBar->Toggle_Tabs_Group_Flag = 1;

			RedrawWindow(App->CL_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBMODEL)
		{
			App->CL_TopBar->Hide_Tabs();
			ShowWindow(App->CL_TopBar->Model_TB_hWnd, SW_SHOW);
			App->CL_TopBar->Toggle_Tabs_Model_Flag = 1;

			RedrawWindow(App->CL_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBCAMERA)
		{
			App->CL_TopBar->Hide_Tabs();
			ShowWindow(App->CL_TopBar->Camera_TB_hWnd, SW_SHOW);
			App->CL_TopBar->Toggle_Tabs_Camera_Flag = 1;

			RedrawWindow(App->CL_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

	}
	}
	return FALSE;
}

// *************************************************************************
// *						Hide_Tabs Terry Berine						   *
// *************************************************************************
void ME_TopBar::Hide_Tabs(void)
{
	ShowWindow(Group_TB_hWnd, SW_HIDE);
	ShowWindow(Model_TB_hWnd, SW_HIDE);
	ShowWindow(Camera_TB_hWnd, SW_HIDE);

	Toggle_Tabs_Group_Flag = 0;
	Toggle_Tabs_Model_Flag = 0;
	Toggle_Tabs_Camera_Flag = 0;
}

// *************************************************************************
// *						Start_Group_TB Terry Flanigan				   *
// *************************************************************************
void ME_TopBar::Start_Group_TB(void)
{
	Group_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_GROUP, Tabs_TB_hWnd, (DLGPROC)Group_TB_Proc);
	Init_Bmps_Group();
}

// *************************************************************************
// *								Group_TB_Proc						   *
// *************************************************************************
LRESULT CALLBACK ME_TopBar::Group_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BTGROUPINFO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BTONLYGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTHIDEGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTALLGROUPS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BTGROUPINFO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_TopBar->Toggle_GroupInfo_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTONLYGROUP && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_TopBar->Toggle_Group_ONLY_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTHIDEGROUP && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_TopBar->Toggle_Group_HIDE_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTALLGROUPS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_TopBar->Toggle_Group_ALL_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
	
		if (LOWORD(wParam) == IDC_BTONLYGROUP)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				if (App->CL_TopBar->Toggle_Group_ONLY_Flag == 1)
				{
					App->CL_TopBar->Toggle_Group_ONLY_Flag = 0;
					App->CL_TopBar->Toggle_Group_ALL_Flag = 1;

					App->CL_Ogre->RenderListener->Show_HideGroup = 0;
					App->CL_Ogre->RenderListener->ShowOnlySubMesh = 0;
				}
				else
				{
					App->CL_TopBar->Toggle_Group_ONLY_Flag = 1;
					App->CL_TopBar->Toggle_Group_HIDE_Flag = 0;
					App->CL_TopBar->Toggle_Group_ALL_Flag = 0;

					App->CL_Ogre->RenderListener->Show_HideGroup = 0;
					App->CL_Ogre->RenderListener->ShowOnlySubMesh = 1;
				}

				RedrawWindow(App->CL_TopBar->Group_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_BTHIDEGROUP)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				if (App->CL_TopBar->Toggle_Group_HIDE_Flag == 1)
				{
					App->CL_TopBar->Toggle_Group_HIDE_Flag = 0;
					App->CL_TopBar->Toggle_Group_ALL_Flag = 1;

					App->CL_Ogre->RenderListener->ShowOnlySubMesh = 0;
					App->CL_Ogre->RenderListener->Show_HideGroup = 0;
				}
				else
				{
					App->CL_TopBar->Toggle_Group_HIDE_Flag = 1;
					App->CL_TopBar->Toggle_Group_ONLY_Flag = 0;
					App->CL_TopBar->Toggle_Group_ALL_Flag = 0;

					App->CL_Ogre->RenderListener->ShowOnlySubMesh = 0;
					App->CL_Ogre->RenderListener->Show_HideGroup = 1;

				}
				
				RedrawWindow(App->CL_TopBar->Group_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_BTALLGROUPS)
		{
			if (App->CL_Model->Model_Loaded == 1)
			{
				App->CL_TopBar->Toggle_Group_ALL_Flag = 1;
				App->CL_TopBar->Toggle_Group_HIDE_Flag = 0;
				App->CL_TopBar->Toggle_Group_ONLY_Flag = 0;

				App->CL_Ogre->RenderListener->ShowOnlySubMesh = 0;
				App->CL_Ogre->RenderListener->Show_HideGroup = 0;

				RedrawWindow(App->CL_TopBar->Group_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			}

			return 1;
		}

		return FALSE;
	}

	}
	return FALSE;
}

// *************************************************************************
// *						Init_Bmps_Group Terry Bernie				   *
// *************************************************************************
void ME_TopBar::Init_Bmps_Group(void)
{
	HWND hTooltip_TB_1 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	// --------------------------------------------------- 
	HWND Temp = GetDlgItem(Group_TB_hWnd, IDC_BTGROUPINFO);

	TOOLINFO ti = { 0 };
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti.uId = (UINT_PTR)Temp;
	ti.lpszText = "Show Group Information";
	ti.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti);

	// --------------------------------------------------- 
}

// *************************************************************************
// *						Start_Model_TB Terry Flanigan				   *
// *************************************************************************
void ME_TopBar::Start_Model_TB(void)
{
	Model_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_MODEL, Tabs_TB_hWnd, (DLGPROC)Model_TB_Proc);
	//Init_Bmps_Group();
}

// *************************************************************************
// *								Model_TB_Proc						   *
// *************************************************************************
LRESULT CALLBACK ME_TopBar::Model_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BTTBDIMENSIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if(some_item->idFrom == IDC_BTTBDIMENSIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_TopBar->Toggle_Dimensions_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BTTBDIMENSIONS)
		{
			//if (App->CL_Model->Model_Loaded == 1) // Check_Here
			{
				if (App->CL_ImGui->Show_Dimensions == 1)
				{
					App->CL_TopBar->Toggle_Dimensions_Flag = 0;
					App->CL_ImGui->Show_Dimensions = 0;
					App->CL_Panels->Show_Panels(1);
				}
				else
				{
					App->CL_TopBar->Toggle_Dimensions_Flag = 1;
					App->CL_ImGui->Show_Dimensions = 1;
					App->CL_Panels->Show_Panels(0);
				}
			}

			return 1;
		}

		return FALSE;
	}

	}
	return FALSE;
}

// *************************************************************************
// *						Start_Camera_TB Terry Flanigan				   *
// *************************************************************************
void ME_TopBar::Start_Camera_TB(void)
{
	Camera_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_CAMERA, Tabs_TB_hWnd, (DLGPROC)Camera_TB_Proc);
	//Init_Bmps_Group();
}

// *************************************************************************
// *								Camera_TB_Proc						   *
// *************************************************************************
LRESULT CALLBACK ME_TopBar::Camera_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BTTBRESETVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTTBSPEED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BTTBRESETVIEW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, 0);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTTBSPEED && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, 0);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BTTBRESETVIEW)
		{
			App->CL_Grid->Reset_View();
			return 1;
		}

		if (LOWORD(wParam) == IDC_BTTBSPEED)
		{
			App->CL_Panels->Enable_Panels(0);

			App->CL_Dialogs->Start_Speed_Camera();

			App->CL_Panels->Enable_Panels(1);
			return 1;
		}
		
		return FALSE;
	}

	}
	return FALSE;
}
