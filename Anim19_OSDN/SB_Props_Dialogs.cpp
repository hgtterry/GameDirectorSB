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
}

SB_Props_Dialogs::~SB_Props_Dialogs()
{
}

// **************************************************************************
// *	  		Start_Props_Dialogs:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
bool SB_Props_Dialogs::Start_Props_Dialogs()
{

	Dialog_Dimensions();
	Start_Dialog_PhysicsReset();
	Start_Dialog_Debug();
	Start_Panels_Test_Dlg();

	return 1;
}

// *************************************************************************
// *	  				 Dialog_Dimensions	Terry Bernie				   *
// *************************************************************************
bool SB_Props_Dialogs::Dialog_Dimensions()
{

	Dimensions_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_DIMENSIONS, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Dialog_Dimensions_Proc);
	Hide_Dimensions_Dlg(0);

	return 1;
}
// *************************************************************************
// *				Dialog_Text_Proc	Terry Bernie  					   *
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
// *	  			 Start_Dialog_PhysicsReset	Terry Bernie			   *
// *************************************************************************
bool SB_Props_Dialogs::Start_Dialog_PhysicsReset()
{

	PhysicsReset_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROPS_PHYSRESET, App->SBC_Properties->Properties_Dlg_hWnd, (DLGPROC)Dialog_PhysicsReset_Proc);
	Hide_Physics_Reset_Dlg(0);

	return 1;
}

// *************************************************************************
// *				Dialog_PhysicsReset_Proc	Terry Bernie  			   *
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
			Debug
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
		return (LONG)App->DialogBackGround;
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
// *				Hide_Dimensions_Dlg Terry Flanigan					   *
// *************************************************************************
void SB_Props_Dialogs::Hide_Dimensions_Dlg(bool Show)
{
	ShowWindow(Dimensions_Dlg_hWnd, Show);
}

// *************************************************************************
// *				Hide_Physics_Reset_Dlg Terry Flanigan				   *
// *************************************************************************
void SB_Props_Dialogs::Hide_Physics_Reset_Dlg(bool Show)
{
	ShowWindow(PhysicsReset_Dlg_hWnd, Show);
}

// *************************************************************************
// *				Hide_Physics_Reset_Dlg Terry Flanigan				   *
// *************************************************************************
void SB_Props_Dialogs::Hide_Debug_Dlg(bool Show)
{
	ShowWindow(Debug_Dlg_hWnd, Show);
}

// *************************************************************************
// *				Hide_Physics_Reset_Dlg Terry Flanigan				   *
// *************************************************************************
void SB_Props_Dialogs::Hide_Panel_Test_Dlg(bool Show)
{
	ShowWindow(Panel_Test_Dlg_hWnd, Show);
}
