/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan B.Parkin H.C.Flanigan

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

#include "StdAfx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Properties.h"

GD19_Properties::GD19_Properties(void)
{
	Current_Selected_Object = 0;

	Properties_Dlg_hWnd = NULL;
	Properties_hLV = NULL;

	btext[0] = 0;

	Edit_Category = Enums::Edit_Mesh_Object;
	Edit_Physics = 0;

	ToggleObjectDebug = 0;
	Object_Selection = 1;
	Physics_Selection = 0;
	Is_Player = 0;

	Properties_Dlg_Active = 0;
}

GD19_Properties::~GD19_Properties(void)
{
}

// *************************************************************************
// *					Start_GD_Properties Terry Bernie   		 	 	   *
// *************************************************************************
void GD19_Properties::Start_GD_Properties(void)
{
	if (Properties_Dlg_Active == 1)
	{
		return;
	}

	Properties_Dlg_Active = 1;
	HMENU mMenu = GetMenu(App->MainHwnd);
///	CheckMenuItem(mMenu, ID_WINDOW_SHOWMODELGLBAL, MF_BYCOMMAND | MF_CHECKED);

	Properties_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_GD_PROPERTIES, App->Fdlg, (DLGPROC)GD_Properties_Proc);
	ShowWindow(Properties_Dlg_hWnd, 1);

	Create_Properties_hLV();
	//Set_DataView();

}
// *************************************************************************
// *					GD_Properties_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK GD19_Properties::GD_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STOBJECTNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BTOBJECT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTPHYSICS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		

		App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;

		return 1;
	}

	case WM_CTLCOLORSTATIC:
	{
		
		if (GetDlgItem(hDlg, IDC_STOBJECTNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->DialogBackGround;
		}
		//--------------------------------------------
		if (GetDlgItem(hDlg, IDC_STP1) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STP2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STP3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		//--------------------------------------------
		if (GetDlgItem(hDlg, IDC_STR1) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STR2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STR3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		//--------------------------------------------
		if (GetDlgItem(hDlg, IDC_STS1) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STS2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STS3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->DialogBackGround;
	}

	case WM_CLOSE:
	{
		App->Cl_Properties->Properties_Dlg_Active = 0;
		ShowWindow(App->Cl_Properties->Properties_Dlg_hWnd, 0);

		HMENU mMenu = GetMenu(App->MainHwnd);
		///CheckMenuItem(mMenu, ID_WINDOW_SHOWMODELGLBAL, MF_BYCOMMAND | MF_UNCHECKED);

		break;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->hwndFrom == App->Cl_Properties->Properties_hLV)
		{
			switch (some_item->code)
			{
			case NM_CLICK:
			{
				//App->Cl_Properties->ListView_OnClickOptions(lParam);
			}
			}
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		
//	//	if (LOWORD(wParam) == IDC_BTHELP)
//		{
//			App->Cl_Utilities->OpenHTML("Help\\PropertiesPanel.html");
//			return 1;
//		}
//
//	//	if (LOWORD(wParam) == IDC_BTDELETE)
//		{ 
//			int Index = App->Cl_Properties->Current_Selected_Object;
//			bool Result = App->Cl_LookUps->Check_Usage(Index);
//
//			if (Result == 0)
//			{
//				App->Say("Used by another Entity");
//
//				App->Cl_Dialogs->YesNo("Permanently Delete", App->Cl_Scene_Data->Cl_Object[Index]->Name);
//
//				if (App->Cl_Dialogs->Canceled == 0)
//				{
//					App->Cl_Scene_Data->Cl_Object[Index]->Deleted = 1;
//					App->Cl_Scene_Data->Delete_Object(Index);
//					App->Cl_FileView->DeleteItem();
//				}
//			}
//			else
//			{
//				App->Cl_Dialogs->YesNo("Permanently Object", App->Cl_Scene_Data->Cl_Object[Index]->Name);
//
//				if (App->Cl_Dialogs->Canceled == 0)
//				{
//					App->Cl_Scene_Data->Cl_Object[Index]->Deleted = 1;
//					App->Cl_Scene_Data->Delete_Object(Index);
//					App->Cl_FileView->DeleteItem();
//				}
//			}
//			
//			return 1;
//		}
//
//	//	if (LOWORD(wParam) == IDC_BTTEST)
//		{
//			int Index = App->Cl_Properties->Current_Selected_Object;
//			App->Cl_Scene_Data->Reset_Triggers();
//			App->Cl_Collision->Move_Entity(Index);
//			return 1;
//		}
//
		
		break;
	}
	}
	return FALSE;
}

// *************************************************************************
// *					Create_Properties_hLV Terry Bernie				   *
// *************************************************************************
void GD19_Properties::Create_Properties_hLV(void)
{
	int NUM_COLS = 2;
	Properties_hLV = CreateWindowEx(0, WC_LISTVIEW, "",
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_VSCROLL | LVS_REPORT | LVS_NOCOLUMNHEADER | LVS_SHOWSELALWAYS, 7, 50,
		230, 240, Properties_Dlg_hWnd, 0, App->hInst, NULL);

	DWORD exStyles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

	ListView_SetExtendedListViewStyleEx(Properties_hLV, exStyles, exStyles);

	ListView_SetBkColor(Properties_hLV, RGB(255, 255, 255));
	ListView_SetTextBkColor(Properties_hLV, RGB(255, 255, 255));

	LV_COLUMN lvC;
	memset(&lvC, 0, sizeof(LV_COLUMN));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	std::string headers[] =
	{
		"", ""
	};
	int headerSize[] =
	{
		100, 120
	};

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_InsertColumn(Properties_hLV, header, &lvC);
	}
	//HFONT Font;
	//Font = CreateFont(-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
	SendMessage(Properties_hLV, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

	//Update_ListView_Objects();
	return;
}



// *************************************************************************
// *				ListView_Object_OnClick  Terry Bernie				   *
// *************************************************************************
bool GD19_Properties::ListView_Object_Physics_OnClick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		
	}

	return 1;
}



