/*
Copyright (c) 2021 EquitySB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Dialogs.h"


SB_Dialogs::SB_Dialogs()
{
	Canceled = 0;
	YesNo_Flag = 0;

	btext[0] = 0;
	Chr_Text[0] = 0;

	MessageString[0] = 0;;
	MessageString2[0] = 0;
}


SB_Dialogs::~SB_Dialogs()
{
}

// *************************************************************************
// *	  			Dialog_Text:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Dialogs::Dialog_Text()
{
	Canceled = 0;

	DialogBox(App->hInst, (LPCTSTR)IDD_PROP_TEXT, App->Fdlg, (DLGPROC)Dialog_Text_Proc);

	return 1;
}
// **************************************************************************
// *				Dialog_Text_Proc:- Terry and Hazel Flanigan 2022		*
// **************************************************************************
LRESULT CALLBACK SB_Dialogs::Dialog_Text_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		App->SetTitleBar(hDlg);

		HFONT Font;
		Font = CreateFont(-20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Courier Black");
		SendDlgItemMessage(hDlg, IDC_TITLENAME, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_EDITTEXT, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_TITLENAME, (LPCTSTR)App->SBC_Dialogs->btext);

		SetDlgItemText(hDlg, IDC_EDITTEXT, (LPCTSTR)App->SBC_Dialogs->Chr_Text);

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_TITLENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
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

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK)
		{
			char buff[255];
			GetDlgItemText(hDlg, IDC_EDITTEXT, (LPTSTR)buff, 255);

			strcpy(App->SBC_Dialogs->Chr_Text, buff);

			App->SBC_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->SBC_Dialogs->Canceled = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	break;

	}
	return FALSE;
}

// **************************************************************************
// *	  			 YesNo:- Terry and Hazel Flanigan 2022					*
// **************************************************************************
void SB_Dialogs::YesNo(char *Text, char *Text2,bool YesNo)
{
	Canceled = 0;

	YesNo_Flag = YesNo;

	strcpy(MessageString, Text);
	strcpy(MessageString2, Text2);

	DialogBox(App->hInst, (LPCTSTR)IDD_YESNO, App->Fdlg, (DLGPROC)YesNo_Proc);
}

// *************************************************************************
// *		YesNo_Proc_Proc:- Terry and Hazel Flanigan 2022	  			   *
// *************************************************************************
LRESULT CALLBACK SB_Dialogs::YesNo_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->SetTitleBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_BANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTEXT, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_BANNER, App->SBC_Dialogs->MessageString);
		SetDlgItemText(hDlg, IDC_STTEXT, App->SBC_Dialogs->MessageString2);

		if (App->SBC_Dialogs->YesNo_Flag == 1)
		{
			SetDlgItemText(hDlg, IDOK, "Yes");
			SetDlgItemText(hDlg, IDCANCEL, "No");
		}

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_BANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		if (GetDlgItem(hDlg, IDC_STTEXT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		return FALSE;
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

		return CDRF_DODEFAULT;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_COMMAND:

		if (LOWORD(wParam) == IDOK)
		{
			App->SBC_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->SBC_Dialogs->Canceled = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;

	}
	return FALSE;
}

// *************************************************************************
// *	  		Dialog_DropGen:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Dialogs::Dialog_DropGen()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_DROPGEN, App->Fdlg, (DLGPROC)Dialog_DropGen_Proc);

	return 1;
}
// *************************************************************************
// *		Dialog_DropGen_Proc:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
LRESULT CALLBACK SB_Dialogs::Dialog_DropGen_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		App->SetTitleBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_TITLE, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CBGEN, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_TITLE, (LPCTSTR)App->Cl_Dialogs->btext);

		HWND temp = GetDlgItem(hDlg, IDC_CBGEN);

		if (App->Cl_Dialogs->DropList_Data == Enums::DropDialog_TrigMoveObject)
		{
			App->SBC_Dialogs->ListObjects(temp);
			return TRUE;
		}

		if (App->Cl_Dialogs->DropList_Data == Enums::DropDialog_TrigMoveAxis)
		{
			App->SBC_Dialogs->ListAxis(temp);
			return TRUE;
		}

		if (App->Cl_Dialogs->DropList_Data == Enums::DropDialog_Locations)
		{
			App->SBC_Dialogs->List_Locations(temp);
			return TRUE;
		}


		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{

		if (GetDlgItem(hDlg, IDC_TITLE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			char buff[256];
			GetDlgItemText(hDlg, IDC_CBGEN, (LPTSTR)buff, 256);
			strcpy(App->Cl_Dialogs->Chr_DropText, buff);

			App->SBC_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->SBC_Dialogs->Canceled = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *					ListObjects Terry Bernie				 		   *
// *************************************************************************
void SB_Dialogs::ListObjects(HWND DropHwnd)
{
	int Count = 0;
	int Total = App->SBC_Scene->Object_Count;

	while (Count < Total)
	{
		{
			//if (App->SBC_Scene->B_Object[Count]->Type == Enums::Bullet_Type_Static)
			{
				if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Static)
				{
					SendMessage(DropHwnd, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_Scene->B_Object[Count]->Mesh_Name);
				}
			}
		}

		Count++;
	}

	SendMessage(DropHwnd, CB_SETCURSEL, 0, 0);
}

// *************************************************************************
// *					List_Locations Terry Bernie				 		   *
// *************************************************************************
void SB_Dialogs::List_Locations(HWND DropHwnd)
{
	int Count = 0;
	while (Count < App->Cl_Scene_Data->Player_Location_Count)
	{
		if (App->SBC_Scene->B_Locations[Count]->Deleted == 0)
		{
			SendMessage(DropHwnd, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_Scene->B_Locations[Count]->Name);
		}
		Count++;
	}

	SendMessage(DropHwnd, CB_SETCURSEL, 0, 0);
}

// *************************************************************************
// *					ListAxis Terry Bernie					 		   *
// *************************************************************************
void SB_Dialogs::ListAxis(HWND DropHwnd)
{
	int Count = 0;
	bool Any = 0;

	SendMessage(DropHwnd, CB_ADDSTRING, 0, (LPARAM)"X");
	SendMessage(DropHwnd, CB_ADDSTRING, 0, (LPARAM)"Y");
	SendMessage(DropHwnd, CB_ADDSTRING, 0, (LPARAM)"Z");

	SendMessage(DropHwnd, CB_SETCURSEL, 0, 0);
}