#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "VM_TopBar.h"


VM_TopBar::VM_TopBar()
{
	TabsHwnd =	nullptr;
	
	Tabs_TB_hWnd = nullptr;

	Camera_TB_hWnd =		nullptr;
	Motions_TB_hWnd =		nullptr;
	Dimensions_TB_hWnd =	nullptr;
	Groups_TB_hWnd =		nullptr;

	Toggle_Faces_Flag = 0;
	Toggle_Textures_Flag = 0;
	Toggle_Points_Flag = 0;
	Toggle_Bones_Flag = 0;
	Toggle_Normals_Flag = 0;
	Toggle_BBox_Flag = 0;

	Toggle_Tabs_Old_Flag = 1;
	Toggle_Tabs_Motions_Flag = 0;
	Toggle_Tabs_Dimensions_Flag = 0;
	Toggle_Tabs_Groups_Flag = 0;
	Toggle_GroupsOnly_Flag = 0;

	// Motions
	Toggle_Play_Flag = 0;

	// Camera
	Toggle_Model_Flag = 1;
	Toggle_World_Flag = 0;
}


VM_TopBar::~VM_TopBar()
{
}

// *************************************************************************
// *	  					Reset_Class  	Terry						   *
// *************************************************************************
void VM_TopBar::Reset_Class()
{
	Toggle_Faces_Flag = 0;
	Toggle_Textures_Flag = 0;
	Toggle_Points_Flag = 0;
	Toggle_Bones_Flag = 0;

	Toggle_Tabs_Old_Flag = 1;
	Toggle_Tabs_Motions_Flag = 0;
	Toggle_Tabs_Dimensions_Flag = 0;
	Toggle_Tabs_Groups_Flag = 0;
	Toggle_GroupsOnly_Flag = 0;

	// Motions
	Toggle_Play_Flag = 0;

	// Camera
	Toggle_Model_Flag = 1;
	Toggle_World_Flag = 0;

	App->Cl19_Ogre->RenderListener->ShowOnlySubMesh = 0;

	App->CL_Vm_TopBar->Hide_Tabs();
	ShowWindow(App->CL_Vm_TopBar->Camera_TB_hWnd, SW_SHOW);
	App->CL_Vm_TopBar->Toggle_Tabs_Old_Flag = 1;

	RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	return;
}

// *************************************************************************
// *	  					Start_TopBar  	Terry						   *
// *************************************************************************
bool VM_TopBar::Start_TopBar()
{
	CreateDialog(App->hInst,(LPCTSTR)IDD_TOPBAR,App->Fdlg,(DLGPROC)TopMain_Proc);
	Init_Bmps_TB2();
	return 1;
}

// *************************************************************************
// *						TopBar_Proc Terry							   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::TopMain_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->CL_Vm_TopBar->TabsHwnd = hDlg;
	
		SendDlgItemMessage(hDlg, IDC_TBSHOWFACES, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBSHOWTEXTURE, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBPOINTS, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBSHOWBONES, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBNORMALS, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBBOUNDBOX, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		
		App->CL_Vm_TopBar->Start_Tabs();
		App->CL_Vm_TopBar->Start_View_TB();
		App->CL_Vm_TopBar->Start_Motions_TB();
		App->CL_Vm_TopBar->Start_Dimensions_TB();
		App->CL_Vm_TopBar->Start_Groups_TB();
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{

		/*if(GetDlgItem(hDlg,IDC_BANNER) == (HWND)lParam)
		{
		SetBkColor((HDC) wParam, RGB(0, 255, 0));
		SetTextColor((HDC) wParam, RGB(0,0,255));
		SetBkMode((HDC) wParam, TRANSPARENT);
		return (UINT) App->AppBackground;
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

		if (some_item->idFrom == IDC_TBSHOWTEXTURE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Textures_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSHOWFACES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Faces_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBPOINTS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Points_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSHOWBONES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Bones_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBNORMALS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Normals_Flag);
			return CDRF_DODEFAULT;
		}
		
		if (some_item->idFrom == IDC_TBBOUNDBOX && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_BBox_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		
		// -----------------------------------------------------

		if (LOWORD(wParam) == IDC_TBSHOWTEXTURE)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				if (App->Cl19_Ogre->RenderListener->ShowTextured == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowTextured = 0;
					App->CL_Vm_TopBar->Toggle_Textures_Flag = 0;
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowTextured = 1;
					App->CL_Vm_TopBar->Toggle_Textures_Flag = 1;
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSHOWFACES)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				if (App->Cl19_Ogre->RenderListener->ShowFaces == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowFaces = 0;
					App->CL_Vm_TopBar->Toggle_Faces_Flag = 0;
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowFaces = 1;
					App->CL_Vm_TopBar->Toggle_Faces_Flag = 1;
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBPOINTS)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				if (App->Cl19_Ogre->RenderListener->ShowPoints == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowPoints = 0;
					App->CL_Vm_TopBar->Toggle_Points_Flag = 0;
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowPoints = 1;
					App->CL_Vm_TopBar->Toggle_Points_Flag = 1;
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSHOWBONES)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				if (App->CL_Vm_Model->BoneCount == 0)
				{
					App->Say("Model has no Bone/Joint structure.");
					return FALSE;
				}

				if (App->Cl19_Ogre->RenderListener->ShowBones == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowBones = 0;
					App->CL_Vm_TopBar->Toggle_Bones_Flag = 0;
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowBones = 1;
					App->CL_Vm_TopBar->Toggle_Bones_Flag = 1;
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBNORMALS)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				if (App->Cl19_Ogre->RenderListener->ShowNormals == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowNormals = 0;
					App->CL_Vm_TopBar->Toggle_Normals_Flag = 0;
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowNormals = 1;
					App->CL_Vm_TopBar->Toggle_Normals_Flag = 1;
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBBOUNDBOX)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				if (App->Cl19_Ogre->RenderListener->ShowBoundingBox == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowBoundingBox = 0;
					App->CL_Vm_TopBar->Toggle_BBox_Flag = 0;
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowBoundingBox = 1;
					App->CL_Vm_TopBar->Toggle_BBox_Flag = 1;
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBLIGHT)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				if (App->Cl19_Ogre->RenderListener->Light_Activated == 1)
				{
					App->Cl19_Ogre->RenderListener->Light_Activated = 0;
				}
				else
				{
					App->Cl19_Ogre->RenderListener->Light_Activated = 1;
				}
			}
			return TRUE;
		}

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
// *							Start_Tabs Terry						   *
// *************************************************************************
void VM_TopBar::Start_Tabs(void)
{
	Tabs_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_TAB, App->CL_Vm_TopBar->TabsHwnd, (DLGPROC)Tabs_Proc);
}

// *************************************************************************
// *								Tabs_Proc_Proc						   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::Tabs_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_CBMOTIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_TBOLD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBMOTIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBDIMENSIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBGROUPS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
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
			App->Custom_Button_Toggle_Tabs(item, App->CL_Vm_TopBar->Toggle_Tabs_Old_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBMOTIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_Vm_TopBar->Toggle_Tabs_Motions_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBDIMENSIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_Vm_TopBar->Toggle_Tabs_Dimensions_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBGROUPS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_Vm_TopBar->Toggle_Tabs_Groups_Flag);
			return CDRF_DODEFAULT;
		}
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_TBOLD)
		{
			App->CL_Vm_TopBar->Hide_Tabs();
			ShowWindow(App->CL_Vm_TopBar->Camera_TB_hWnd, SW_SHOW);
			App->CL_Vm_TopBar->Toggle_Tabs_Old_Flag = 1;

			RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBMOTIONS)
		{
			App->CL_Vm_TopBar->Hide_Tabs();
			ShowWindow(App->CL_Vm_TopBar->Motions_TB_hWnd, SW_SHOW);
			App->CL_Vm_TopBar->Toggle_Tabs_Motions_Flag = 1;
			App->CL_Vm_ImGui->Show_Motion_List = 1;
			
			RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}


		if (LOWORD(wParam) == IDC_TBDIMENSIONS)
		{
			App->CL_Vm_TopBar->Hide_Tabs();
			ShowWindow(App->CL_Vm_TopBar->Dimensions_TB_hWnd, SW_SHOW);
			App->CL_Vm_TopBar->Toggle_Tabs_Dimensions_Flag = 1;
			
			RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBGROUPS)
		{
			App->CL_Vm_TopBar->Hide_Tabs();
			
			ShowWindow(App->CL_Vm_TopBar->Groups_TB_hWnd, SW_SHOW);
			ShowWindow(App->CL_Vm_Groups->RightGroups_Hwnd, SW_SHOW);
			App->CL_Vm_ImGui->Show_Group_List = 1;

			App->CL_Vm_TopBar->Toggle_Tabs_Groups_Flag = 1;

			RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

	}
	}
	return FALSE;
}

// *************************************************************************
// *						Hide_Tabs Terry Berine						   *
// *************************************************************************
void VM_TopBar::Hide_Tabs(void)
{
	ShowWindow(App->CL_Vm_TopBar->Camera_TB_hWnd, SW_HIDE);
	ShowWindow(App->CL_Vm_TopBar->Motions_TB_hWnd, SW_HIDE);
	ShowWindow(App->CL_Vm_TopBar->Dimensions_TB_hWnd, SW_HIDE);
	ShowWindow(App->CL_Vm_TopBar->Groups_TB_hWnd, SW_HIDE);
	
	ShowWindow(App->CL_Vm_Groups->RightGroups_Hwnd, 0);

	App->CL_Vm_ImGui->Show_Group_List = 0;
	App->CL_Vm_ImGui->Show_Motion_List = 0;

	Toggle_Tabs_Old_Flag = 0;
	Toggle_Tabs_Motions_Flag = 0;
	Toggle_Tabs_Dimensions_Flag = 0;
	Toggle_Tabs_Groups_Flag = 0;
}

// *************************************************************************
// *						Start_View_TB Terry Berine					   *
// *************************************************************************
void VM_TopBar::Start_View_TB(void)
{
	Camera_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB1, Tabs_TB_hWnd, (DLGPROC)View_TB_Proc);
	Init_Bmps_TB1();
}

// *************************************************************************
// *								View_TB_Proc						   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::View_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_TBRESETVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBZOOM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBMODEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBWORLD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_SELECTION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_ToolBar->Selection_Active);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_SHOWMESHPOINTS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_ToolBar->FreeCam_Active);
			return CDRF_DODEFAULT;
		}*/

		if (some_item->idFrom == IDC_TBMODEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Model_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBWORLD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_World_Flag);
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

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_TBRESETVIEW)
		{
			App->Cl_Grid->Reset_View();
			return 1;
		}

		if (LOWORD(wParam) == IDC_TBZOOM)
		{
			App->Cl_Grid->Zoom();
			return 1;
		}

		if (LOWORD(wParam) == IDC_BTMOUSESPEED)
		{
			App->Cl_Dialogs->Start_Mouse_Sensitivity();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_FULLSCREEN)
		{
			App->Cl19_Ogre->Go_FullScreen_Mode();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBMODEL)
		{
			App->Cl19_Ogre->OgreListener->CameraMode = 1;
			App->CL_Vm_TopBar->Toggle_Model_Flag = 1;
			App->CL_Vm_TopBar->Toggle_World_Flag = 0;
			RedrawWindow(App->CL_Vm_TopBar->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBWORLD)
		{
			App->Cl19_Ogre->OgreListener->CameraMode = 0;
			App->CL_Vm_TopBar->Toggle_World_Flag = 1;
			App->CL_Vm_TopBar->Toggle_Model_Flag = 0;
			RedrawWindow(App->CL_Vm_TopBar->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		return FALSE;
	}

	}
	return FALSE;
}

// *************************************************************************
// *						Init_Bmps_TB1 Terry Bernie					   *
// *************************************************************************
void VM_TopBar::Init_Bmps_TB1(void)
{
	//HWND hTooltip_TB_1 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	//// --------------------------------------------------- 
	//HWND Temp = GetDlgItem(TB_1, IDC_FULLSCREEN);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_FullScreen_Bmp);

	//TOOLINFO ti = { 0 };
	//ti.cbSize = sizeof(ti);
	//ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti.uId = (UINT_PTR)Temp;
	//ti.lpszText = "Full Screen View";
	//ti.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti);

	//// --------------------------------------------------- 

	//Temp = GetDlgItem(TB_1, IDC_BTMODELINFO);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);

	//TOOLINFO ti2 = { 0 };
	//ti2.cbSize = sizeof(ti);
	//ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti2.uId = (UINT_PTR)Temp;
	//ti2.lpszText = "Model Information";
	//ti2.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	//// --------------------------------------------------- 

	//Temp = GetDlgItem(TB_1, IDC_BTMOUSESPEED);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MouseSensitivity_Bmp);

	//TOOLINFO ti3 = { 0 };
	//ti3.cbSize = sizeof(ti);
	//ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti3.uId = (UINT_PTR)Temp;
	//ti3.lpszText = "Set Mouse Sensitivity";
	//ti3.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti3);

	//// --------------------------------------------------- 

	//Temp = GetDlgItem(TB_1, IDC_BTLOCATIONS);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_Projection_Bmp);

	//TOOLINFO ti4 = { 0 };
	//ti4.cbSize = sizeof(ti);
	//ti4.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti4.uId = (UINT_PTR)Temp;
	//ti4.lpszText = "Location:- Save and Move to Locations within the Scene";
	//ti4.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti4);

	//// --------------------------------------------------- 

	//Temp = GetDlgItem(TB_1, IDC_SELECTION);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);

	//TOOLINFO ti5 = { 0 };
	//ti5.cbSize = sizeof(ti);
	//ti5.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti5.uId = (UINT_PTR)Temp;
	//ti5.lpszText = "Selection Mode Press Space bar to Select";
	//ti5.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti5);

	//// --------------------------------------------------- 

	//Temp = GetDlgItem(TB_1, IDC_BUILDGAME);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOff_Bmp);

	//TOOLINFO ti6 = { 0 };
	//ti6.cbSize = sizeof(ti);
	//ti6.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti6.uId = (UINT_PTR)Temp;
	//ti6.lpszText = "Build Stand Alone GAme";
	//ti6.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti6);

	//// --------------------------------------------------- 

	//Temp = GetDlgItem(TB_1, IDC_GAMEMODE);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);

	//TOOLINFO ti7 = { 0 };
	//ti7.cbSize = sizeof(ti);
	//ti7.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti7.uId = (UINT_PTR)Temp;
	//ti7.lpszText = "Game Mode Preview";
	//ti7.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti7);

	//// --------------------------------------------------- 

	//Temp = GetDlgItem(TB_1, IDC_IMGUIDEBUG);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOff_Bmp);

	//TOOLINFO ti8 = { 0 };
	//ti8.cbSize = sizeof(ti);
	//ti8.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti8.uId = (UINT_PTR)Temp;
	//ti8.lpszText = "Debug Game/App";
	//ti8.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti8);

	//// --------------------------------------------------- 

	//Temp = GetDlgItem(TB_1, IDC_FREECAM);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);

	//TOOLINFO ti9 = { 0 };
	//ti9.cbSize = sizeof(ti);
	//ti9.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti9.uId = (UINT_PTR)Temp;
	//ti9.lpszText = "Free Camera No Collision";
	//ti9.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti9);

	//// --------------------------------------------------- 

	//Temp = GetDlgItem(TB_1, IDC_THIRDPERSON);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);

	//TOOLINFO ti10 = { 0 };
	//ti10.cbSize = sizeof(ti);
	//ti10.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti10.uId = (UINT_PTR)Temp;
	//ti10.lpszText = "3rd Person View Not available yet";
	//ti10.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti10);

	//// --------------------------------------------------- 

	///*Temp = GetDlgItem(TB_1, IDC_FIRSTPERSON);
	//SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);

	//TOOLINFO ti11 = { 0 };
	//ti11.cbSize = sizeof(ti);
	//ti11.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	//ti11.uId = (UINT_PTR)Temp;
	//ti11.lpszText = "1st Person View with Physics";
	//ti11.hwnd = App->MainHwnd;
	//SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti11);*/
}

// *************************************************************************
// *						Init_Bmps_TB2 Terry Bernie					   *
// *************************************************************************
void VM_TopBar::Init_Bmps_TB2(void)
{
	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	HWND Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWTEXTURE);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Toggle Textures";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti1);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWFACES);
	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Toggle Faces";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	Temp = GetDlgItem(TabsHwnd, IDC_TBPOINTS);
	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti3);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Toggle Points";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti3);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWBONES);
	TOOLINFO ti4 = { 0 };
	ti4.cbSize = sizeof(ti4);
	ti4.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti4.uId = (UINT_PTR)Temp;
	ti4.lpszText = "Toggle Bones";
	ti4.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti4);

	Temp = GetDlgItem(TabsHwnd, IDC_TBNORMALS);
	TOOLINFO ti5 = { 0 };
	ti5.cbSize = sizeof(ti5);
	ti5.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti5.uId = (UINT_PTR)Temp;
	ti5.lpszText = "Toggle Normals";
	ti5.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti5);

	Temp = GetDlgItem(TabsHwnd, IDC_TBBOUNDBOX);
	TOOLINFO ti6 = { 0 };
	ti6.cbSize = sizeof(ti6);
	ti6.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti6.uId = (UINT_PTR)Temp;
	ti6.lpszText = "Toggle Bounding Box";
	ti6.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti6);

}

// *************************************************************************
// *						Init_Bmps_Motions Terry Bernie				   *
// *************************************************************************
void VM_TopBar::Init_Bmps_Motions(void)
{
	//HWND hTooltip_TB_1 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	// --------------------------------------------------- 
	HWND Temp = GetDlgItem(Motions_TB_hWnd, IDC_TBPLAY);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_Playoff);


	Temp = GetDlgItem(Motions_TB_hWnd, IDC_TBSTOP);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_PlayStop);

	/*TOOLINFO ti = { 0 };
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti.uId = (UINT_PTR)Temp;
	ti.lpszText = "Full Screen View";
	ti.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti);*/

	// --------------------------------------------------- 

}

// *************************************************************************
// *						Start_Motions_TB Terry						   *
// *************************************************************************
void VM_TopBar::Start_Motions_TB(void)
{
	Motions_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_MOTIONS, Tabs_TB_hWnd, (DLGPROC)Motions_TB_Proc);
	Init_Bmps_Motions();
}

// *************************************************************************
// *								Motions_TB_Proc						   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::Motions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_CBMOTIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBPOSE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_TBPLAY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Play_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSTOP && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, 0);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBPOSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_TBPLAY) // Play Motion
		{
			App->CL_Vm_Motions->Play_SelectedMotion();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSTOP) // Stop Motion
		{
			App->CL_Vm_Motions->Stop_SelectedMotion();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBPOSE) // Stop Motion
		{
			App->CL_Vm_Motions->Set_Pose();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_STEPTIMEBACK)
		{
			if (App->CL_Vm_Model->MotionCount == 0) { return 1; }

			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->GetBoneMoveMent();
				App->CL_Vm_Genesis3D->Animate(3);

			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_STEPTIMEPLUS)
		{

			if (App->CL_Vm_Model->MotionCount == 0) { return 1; }

			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->GetBoneMoveMent();
				App->CL_Vm_Genesis3D->Animate(2);

			}
			return TRUE;
		}

		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *						Start_Dimensions_TB Terry					   *
// *************************************************************************
void VM_TopBar::Start_Dimensions_TB(void)
{
	Dimensions_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_DIMENSIONS, Tabs_TB_hWnd, (DLGPROC)Dimensions_TB_Proc);
}

// *************************************************************************
// *								Dimensions_TB_Proc					   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::Dimensions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_CBMOTIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{

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
			return TRUE;
		}
		
		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *						Start_Groups_TB Terry					   *
// *************************************************************************
void VM_TopBar::Start_Groups_TB(void)
{
	Groups_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_GROUPS, Tabs_TB_hWnd, (DLGPROC)Groups_TB_Proc);
}

// *************************************************************************
// *								Dimensions_TB_Proc					   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::Groups_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_GRCHANGETEXTURE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ONLYGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{

		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_ONLYGROUP && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_GroupsOnly_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_GRCHANGETEXTURE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_GRCHANGETEXTURE) 
		{
			App->CL_Vm_Groups->ChangeTexture_ModelLocation();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ONLYGROUP) 
		{
			if (App->Cl19_Ogre->RenderListener->ShowOnlySubMesh == 1)
			{
				App->Cl19_Ogre->RenderListener->ShowOnlySubMesh = 0;
				App->CL_Vm_TopBar->Toggle_GroupsOnly_Flag = 0;
			}
			else
			{
				App->Cl19_Ogre->RenderListener->ShowOnlySubMesh = 1;
				App->CL_Vm_TopBar->Toggle_GroupsOnly_Flag = 1;
			}

			return TRUE;
		}

		//if (LOWORD(wParam) == IDC_TBSCALE) // Scale
		//{
		//	if (App->CL_Vm_ImGui->Show_Scale == 1)
		//	{
		//		App->CL_Vm_ImGui->Show_Scale = 0;
		//	}
		//	else
		//	{
		//		App->CL_Vm_ImGui->Show_Scale = 1;
		//	}
		//	return TRUE;
		//}

		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *					TogglePlayBmp Inflanite						       *
// *************************************************************************
void VM_TopBar::TogglePlayBmp(void)
{
	HWND Temp = GetDlgItem(Motions_TB_hWnd, IDC_TBPLAY);

	if (Toggle_Play_Flag == 1)
	{
		SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_PlayOn);
	}
	else
	{
		SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_Playoff);
	}
}
