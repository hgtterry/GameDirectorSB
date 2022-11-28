/*
Copyright (c) 2022 EquitySB Inflanite Software W.T.Flanigan H.C.Flanigan

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

// :- Terry and Hazel Flanigan 2022

*/

#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "SB_Props_Dialogs.h"

SB_Props_Dialogs::SB_Props_Dialogs()
{
	Dimensions_Dlg_hWnd = nullptr;
	PhysicsReset_Dlg_hWnd = nullptr;
	Debug_Dlg_hWnd = nullptr;
	Panel_Test_Dlg_hWnd = nullptr;
	Area_Props_HWND = nullptr;
	Details_Goto_Hwnd = nullptr;

	Show_Area_Physics_Debug = 0;
}

SB_Props_Dialogs::~SB_Props_Dialogs()
{
}

// **************************************************************************
// *	  		Start_Props_Dialogs:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
bool SB_Props_Dialogs::Start_Props_Dialogs()
{

	Start_Dialog_Dimensions();
	Start_Dialog_PhysicsReset();
	Start_Dialog_Debug();
	Start_Panels_Test_Dlg();
	Start_Area_PropsPanel();
	Start_Details_Goto_Dlg();

	return 1;
}

// *************************************************************************
// *	  Start_Dialog_Dimensions:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Props_Dialogs::Start_Dialog_Dimensions()
{

	Dimensions_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_DIMENSIONS, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Dialog_Dimensions_Proc);
	
	Init_Bmps_Dimensions();
	Hide_Dimensions_Dlg(0,0);

	return 1;
}
// *************************************************************************
// *		Dialog_Text_Proc:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
LRESULT CALLBACK SB_Props_Dialogs::Dialog_Dimensions_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_POSITION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_ROTATION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_SCALE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CK_LOCK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{

		if (GetDlgItem(hDlg, IDC_CK_LOCK) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_Panel;
		}

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Panel;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_POSITION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Dimensions->Show_Position);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_SCALE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Dimensions->Show_Scale);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_ROTATION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Dimensions->Show_Rotation);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_CK_LOCK)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_LOCK);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				int EditCat = App->SBC_Properties->Edit_Category;
				if (EditCat == Enums::FV_Edit_Object || EditCat == Enums::Edit_Teleport)
				{
					int Index = App->SBC_Properties->Current_Selected_Object;
					App->SBC_Scene->B_Object[Index]->Dimensions_Locked = 1;

					App->SBC_Scene->B_Object[Index]->Altered = 1;
					App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Object[Index]->FileViewItem);
					App->SBC_Scene->Scene_Modified = 1;
				}

				EnableWindow(GetDlgItem(hDlg, IDC_BT_POSITION), 0);
				EnableWindow(GetDlgItem(hDlg, IDC_BT_SCALE), 0);
				EnableWindow(GetDlgItem(hDlg, IDC_BT_ROTATION), 0);
				return 1;
			}
			else
			{
				int EditCat = App->SBC_Properties->Edit_Category;
				if (EditCat == Enums::FV_Edit_Object || EditCat == Enums::Edit_Teleport)
				{
					int Index = App->SBC_Properties->Current_Selected_Object;
					App->SBC_Scene->B_Object[Index]->Dimensions_Locked = 0;

					App->SBC_Scene->B_Object[Index]->Altered = 1;
					App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Object[Index]->FileViewItem);
					App->SBC_Scene->Scene_Modified = 1;
				}

				if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
				{
					if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
					{
						App->SBC_Dialogs->YesNo("Edit Area", "Are You Sure", 1);
						bool Doit = App->SBC_Dialogs->Canceled;
						if (Doit == 1)
						{
							SendMessage(temp, BM_SETCHECK, 1, 0);
							return TRUE;
						}
					}
				}

				EnableWindow(GetDlgItem(hDlg, IDC_BT_POSITION), 1);
				EnableWindow(GetDlgItem(hDlg, IDC_BT_SCALE), 1);
				EnableWindow(GetDlgItem(hDlg, IDC_BT_ROTATION), 1);
				return 1;
			}
			return TRUE;
		}
		
		if (LOWORD(wParam) == IDC_BT_POSITION)
		{

			if (App->SBC_Dimensions->Show_Position == 1)
			{
				App->SBC_Dimensions->Show_Position = 0;
				App->SBC_Markers->Hide_Axis_Marker();
			}
			else
			{
				App->SBC_Markers->Hide_Axis_Marker();
				App->SBC_Dimensions->Show_Position = 1;
				App->SBC_Dimensions->Show_Scale = 0;
				App->SBC_Dimensions->Show_Rotation = 0;
			}

			RedrawWindow(App->SBC_Props_Dialog->Dimensions_Dlg_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_SCALE)
		{

			if (App->SBC_Dimensions->Show_Scale == 1)
			{
				App->SBC_Dimensions->Show_Scale = 0;
				App->SBC_Markers->Hide_Axis_Marker();
			}
			else
			{
				App->SBC_Markers->Hide_Axis_Marker();
				App->SBC_Dimensions->Show_Scale = 1;
				App->SBC_Dimensions->Show_Position = 0;
				App->SBC_Dimensions->Show_Rotation = 0;
			}

			RedrawWindow(App->SBC_Props_Dialog->Dimensions_Dlg_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_ROTATION)
		{

			if (App->SBC_Dimensions->Show_Rotation == 1)
			{
				App->SBC_Dimensions->Show_Rotation = 0;
				App->SBC_Markers->Hide_Axis_Marker();
			}
			else
			{
				App->SBC_Markers->Hide_Axis_Marker();
				App->SBC_Dimensions->Show_Rotation = 1;
				App->SBC_Dimensions->Show_Position = 0;
				App->SBC_Dimensions->Show_Scale = 0;
			}

			RedrawWindow(App->SBC_Props_Dialog->Dimensions_Dlg_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			return 1;
		}

		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	}
	return FALSE;
}

// *************************************************************************
// *		Init_Bmps_Dimensions:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Props_Dialogs::Init_Bmps_Dimensions()
{
	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	SendMessage(hTooltip_TB_2, TTM_SETMAXTIPWIDTH, 0, 150);

	HWND Temp = GetDlgItem(Dimensions_Dlg_hWnd, IDC_BT_POSITION);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Start the Dimensions Dialog in Position Mode";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti1);

	Temp = GetDlgItem(Dimensions_Dlg_hWnd, IDC_BT_ROTATION);
	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Start the Dimensions Dialog in Rotation Mode";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	Temp = GetDlgItem(Dimensions_Dlg_hWnd, IDC_BT_SCALE);
	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti3);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Start the Dimensions Dialog in Scale Mode";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti3);
}

// *************************************************************************
// *	  	Start_Dialog_PhysicsReset:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
bool SB_Props_Dialogs::Start_Dialog_PhysicsReset()
{

	PhysicsReset_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_PHYSRESET, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Dialog_PhysicsReset_Proc);
	
	Init_Bmps_PhysicsReset();
	Hide_Physics_Reset_Dlg(0);

	return 1;
}

// *************************************************************************
// *	  Dialog_PhysicsReset_Proc:- Terry and Hazel Flanigan 2022  	   *
// *************************************************************************
LRESULT CALLBACK SB_Props_Dialogs::Dialog_PhysicsReset_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_PHYSRESET, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TEST_ENTITY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->DialogBackGround;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_PHYSRESET && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TEST_ENTITY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}
		
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_BT_TEST_ENTITY)
		{
			App->SBC_Com_MoveEntity->Test_Move_Entity(App->SBC_Properties->Current_Selected_Object);
			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_PHYSRESET)
		{
			//App->SBC_Physics->Reset_Triggers();
			App->SBC_Com_MoveEntity->Reset_Move_Entity(App->SBC_Properties->Current_Selected_Object);
			return 1;
		}

		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	}
	return FALSE;
}

// *************************************************************************
// *		Init_Bmps_PhysicsReset:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Props_Dialogs::Init_Bmps_PhysicsReset()
{
	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	SendMessage(hTooltip_TB_2, TTM_SETMAXTIPWIDTH, 0, 150);

	HWND Temp = GetDlgItem(PhysicsReset_Dlg_hWnd, IDC_BT_TEST_ENTITY);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Test this Entity";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti1);

	Temp = GetDlgItem(PhysicsReset_Dlg_hWnd, IDC_BT_PHYSRESET);
	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Reset just this Entity";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti2);
}

// *************************************************************************
// *	  	Start_Panels_Test_Dlg:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Props_Dialogs::Start_Panels_Test_Dlg()
{

	Panel_Test_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_PANELTEST, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Panels_Test_Proc);
	Hide_Panel_Test_Dlg(0);

	return 1;
}

// *************************************************************************
// *				Panels_Test_Proc:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
LRESULT CALLBACK SB_Props_Dialogs::Panels_Test_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_PANELTEST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_PANSETTINGS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->DialogBackGround;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_PANELTEST && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_PANSETTINGS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}
	
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BT_PANELTEST)
		{
			if (App->SBC_Properties->Edit_Category == Enums::Edit_Counters)
			{
				if (App->SBC_Scene->B_Counter[App->SBC_Properties->Current_Selected_Object]->Show_Panel_Flag == 1)
				{
					App->SBC_Scene->B_Counter[App->SBC_Properties->Current_Selected_Object]->Show_Panel_Flag = 0;
				}
				else
				{
					App->SBC_Scene->B_Counter[App->SBC_Properties->Current_Selected_Object]->Show_Panel_Flag = 1;
				}
			}

			if (App->SBC_Properties->Edit_Category == Enums::Edit_Message)
			{
				if (App->SBC_Scene->B_Object[App->SBC_Properties->Current_Selected_Object]->Show_Message_Flag == 1)
				{
					App->SBC_Scene->B_Object[App->SBC_Properties->Current_Selected_Object]->Show_Message_Flag = 0;
				}
				else
				{
					App->SBC_Scene->B_Object[App->SBC_Properties->Current_Selected_Object]->Show_Message_Flag = 1;
				}
			}

			return 1;
		}

		/*if (LOWORD(wParam) == IDC_BT_PANSETTINGS)
		{
			return 1;
		}*/

		
		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	}
	return FALSE;
}

// *************************************************************************
// *	  			 Start_Dialog_Debug	Terry Bernie			   *
// *************************************************************************
bool SB_Props_Dialogs::Start_Dialog_Debug()
{

	Debug_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_DEBUG, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Dialog_Debug_Proc);
	
	Init_Bmps_Debug();
	Hide_Debug_Dlg(0);

	return 1;
}

// *************************************************************************
// *				Dialog_Debug_Proc_Proc	Terry Bernie  				   *
// *************************************************************************
LRESULT CALLBACK SB_Props_Dialogs::Dialog_Debug_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_PHYSDEBUG, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_SHOWMESH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Panel;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_PHYSDEBUG && some_item->code == NM_CUSTOMDRAW)
		{
			if (App->SBC_Scene->Object_Count > 0)
			{
				int Index = App->SBC_Properties->Current_Selected_Object;

				LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item, App->SBC_Scene->B_Object[Index]->Physics_Debug_On);
				return CDRF_DODEFAULT;
			}
			else
			{
				LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item, 0);
				return CDRF_DODEFAULT;
			}
		}

		if (some_item->idFrom == IDC_BT_SHOWMESH && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Object->Show_Mesh_Debug);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BT_SHOWMESH)
		{
			int Index = App->SBC_Properties->Current_Selected_Object;

			if (App->SBC_Object->Show_Mesh_Debug == 1)
			{
				App->SBC_Scene->B_Object[Index]->Object_Node->setVisible(false);
				App->SBC_Object->Show_Mesh_Debug = 0;
			}
			else
			{
				App->SBC_Scene->B_Object[Index]->Object_Node->setVisible(true);
				App->SBC_Object->Show_Mesh_Debug = 1;
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_PHYSDEBUG)
		{
			int Index = App->SBC_Properties->Current_Selected_Object;

			int f = App->SBC_Scene->B_Object[Index]->Phys_Body->getCollisionFlags();

			if (App->SBC_Scene->Object_Count > 0)
			{
				if (App->SBC_Scene->B_Object[Index]->Physics_Debug_On == 1)
				{
					App->SBC_Object->Show_Physics_Debug = 0;
					App->SBC_Scene->B_Object[Index]->Phys_Body->setCollisionFlags(f | (1 << 5)); // Off

					App->SBC_Scene->B_Object[Index]->Physics_Debug_On = 0;

					App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 0;
					App->Cl19_Ogre->RenderFrame();
					App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 1;
				}
				else
				{
					App->SBC_Scene->B_Object[Index]->Physics_Debug_On = 1;
					App->SBC_Object->Show_Physics_Debug = 1;
					App->SBC_Scene->B_Object[Index]->Phys_Body->setCollisionFlags(f & (~(1 << 5))); // on
				}
			}

			return 1;
		}

		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	}
	return FALSE;
}

// *************************************************************************
// *			Init_Bmps_Debug:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Props_Dialogs::Init_Bmps_Debug()
{
	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	HWND Temp = GetDlgItem(Debug_Dlg_hWnd, IDC_BT_SHOWMESH);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Show or Hide the Mesh";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti1);

	Temp = GetDlgItem(Debug_Dlg_hWnd, IDC_BT_PHYSDEBUG);
	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Show or Hide the Physics Outline";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti2);
}

// *************************************************************************
// *	  	Start_Area_PropsPanel:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Props_Dialogs::Start_Area_PropsPanel()
{
	Area_Props_HWND = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_AERA, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Area_PropsPanel_Proc);
}

// *************************************************************************
// *		Area_PropsPanel_Proc:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
LRESULT CALLBACK SB_Props_Dialogs::Area_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_PHYSICSAREADEBUG, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_AREA_ENVIRONMENT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Panel;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_PHYSICSAREADEBUG && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Props_Dialog->Show_Area_Physics_Debug);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_AREA_ENVIRONMENT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Environment->Environment_Dlg_Active);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_PHYSICSAREADEBUG)
		{
			int Index = App->SBC_Properties->Current_Selected_Object;

			int f = App->SBC_Scene->B_Area[Index]->Phys_Body->getCollisionFlags();

			if (App->SBC_Props_Dialog->Show_Area_Physics_Debug == 1)
			{
				App->SBC_Props_Dialog->Show_Area_Physics_Debug = 0;
				App->SBC_Scene->B_Area[Index]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->Cl19_Ogre->RenderFrame();
				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 1;
			}
			else
			{
				App->SBC_Props_Dialog->Show_Area_Physics_Debug = 1;
				App->SBC_Scene->B_Area[Index]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_AREA_ENVIRONMENT)
		{
			if (App->Cl_Environment->Environment_Dlg_Active == 1)
			{
				App->Cl_Environment->Environment_Dlg_Active = 0;
				EndDialog(App->Cl_Environment->Environment_hWnd, LOWORD(wParam));
			}
			else
			{
				App->Cl_Environment->Start_Environment();
			}
			return 1;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *	Start_Details_Goto_PropsPanel:- Terry and Hazel Flanigan 2022 	   *
// *************************************************************************
void SB_Props_Dialogs::Start_Details_Goto_Dlg(void)
{
	Details_Goto_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_OBJECT, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Details_Goto_Proc);
	
	Init_Bmps_DetailsGo();
	Hide_Details_Goto_Dlg(0);

}

// *************************************************************************
// *			Details_Goto_Proc:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
LRESULT CALLBACK SB_Props_Dialogs::Details_Goto_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_GOTO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_DETAIL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->DialogBackGround;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_GOTO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_DETAIL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BT_DETAIL)
		{
			if (App->CL_Vm_ImGui->Show_Object_Data == 1)
			{
				App->CL_Vm_ImGui->Show_Object_Data = 0;
			}
			else
			{
				App->SBC_LookUps->Update_Types();
				App->CL_Vm_ImGui->Show_Object_Data = 1;
			}
			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_GOTO)
		{
			App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;

			int Index = App->SBC_Properties->Current_Selected_Object;
			Ogre::Vector3 Centre = App->SBC_Scene->B_Object[Index]->Object_Node->getAttachedObject(0)->getBoundingBox().getCenter();
			Ogre::Vector3 WS = App->SBC_Scene->B_Object[Index]->Object_Node->convertLocalToWorldPosition(Centre);
			App->Cl19_Ogre->mCamera->setPosition(WS);
			return 1;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *		Init_Bmps_DetailsGo:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Props_Dialogs::Init_Bmps_DetailsGo()
{
	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	HWND Temp = GetDlgItem(Details_Goto_Hwnd, IDC_BT_DETAIL);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Show Details of the Select Object/Entity";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti1);

	Temp = GetDlgItem(Details_Goto_Hwnd, IDC_BT_GOTO);
	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Move the Camera to the Centre of the Selected Object";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti2);
}

// *************************************************************************
// *		Hide_Dimensions_Dlg:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Props_Dialogs::Hide_Dimensions_Dlg(bool Show, bool Lock_Dimensions)
{
	
	if (Lock_Dimensions == 1)
	{
		HWND temp = GetDlgItem(Dimensions_Dlg_hWnd, IDC_CK_LOCK);
		SendMessage(temp, BM_SETCHECK, 1, 0);

		EnableWindow(GetDlgItem(Dimensions_Dlg_hWnd, IDC_BT_POSITION), 0);
		EnableWindow(GetDlgItem(Dimensions_Dlg_hWnd, IDC_BT_SCALE), 0);
		EnableWindow(GetDlgItem(Dimensions_Dlg_hWnd, IDC_BT_ROTATION), 0);
	}
	else
	{
		HWND temp = GetDlgItem(Dimensions_Dlg_hWnd, IDC_CK_LOCK);
		SendMessage(temp, BM_SETCHECK, 0, 0);

		EnableWindow(GetDlgItem(Dimensions_Dlg_hWnd, IDC_BT_POSITION), 1);
		EnableWindow(GetDlgItem(Dimensions_Dlg_hWnd, IDC_BT_SCALE), 1);
		EnableWindow(GetDlgItem(Dimensions_Dlg_hWnd, IDC_BT_ROTATION), 1);
	}

	ShowWindow(Dimensions_Dlg_hWnd, Show);
}

// *************************************************************************
// *		Hide_Physics_Reset_Dlg:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Props_Dialogs::Hide_Physics_Reset_Dlg(bool Show)
{
	ShowWindow(PhysicsReset_Dlg_hWnd, Show);

}

// *************************************************************************
// *			Hide_Debug_Dlg:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Props_Dialogs::Hide_Debug_Dlg(bool Show)
{
	ShowWindow(Debug_Dlg_hWnd, Show);
}

// *************************************************************************
// *		Hide_Panel_Test_Dlg:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Props_Dialogs::Hide_Panel_Test_Dlg(bool Show)
{
	ShowWindow(Panel_Test_Dlg_hWnd, Show);
}

// *************************************************************************
// *		  Hide_Area_Dlg:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Props_Dialogs::Hide_Area_Dlg(bool Show)
{
	ShowWindow(Area_Props_HWND, Show);
}

// *************************************************************************
// *		Hide_Details_Goto_Dlg:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Props_Dialogs::Hide_Details_Goto_Dlg(bool Show)
{
	ShowWindow(Details_Goto_Hwnd, Show);
}
