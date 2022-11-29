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
	DropList_Data = 0;

	Canceled = 0;
	YesNo_Flag = 0;

	btext[0] = 0;
	Chr_Text[0] = 0;

	DoFPS = 0;
	Saved_DoFPS = 0;

	Chr_DropText[0] = 0;

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
	
		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LISTSELECTION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STSELECTED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SetDlgItemText(hDlg, IDC_TITLE, (LPCTSTR)App->Cl_Dialogs->btext);
		SetDlgItemText(hDlg, IDC_STSELECTED, (LPCTSTR)App->SBC_Dialogs->Chr_DropText);
		
		HWND tempList = GetDlgItem(hDlg, IDC_LISTSELECTION);

		if (App->SBC_Dialogs->DropList_Data == Enums::DropDialog_TrigMoveObject)
		{
			App->SBC_Dialogs->ListObjects(tempList);
			return TRUE;
		}

		if (App->SBC_Dialogs->DropList_Data == Enums::DropDialog_TrigMoveAxis)
		{
			App->SBC_Dialogs->List_Axis(tempList);
			return TRUE;
		}

		if (App->SBC_Dialogs->DropList_Data == Enums::DropDialog_Locations)
		{
			App->SBC_Dialogs->List_Locations(tempList);
			return TRUE;
		}

		if (App->SBC_Dialogs->DropList_Data == Enums::DropDialog_Counters)
		{
			App->SBC_Dialogs->List_Counters(tempList);
			return TRUE;
		}

		if (App->SBC_Dialogs->DropList_Data == Enums::DropDialog_Messages)
		{
			App->SBC_Dialogs->List_Messages(tempList);
			return TRUE;
		}

		if (App->SBC_Dialogs->DropList_Data == Enums::DropDialog_Display)
		{
			App->SBC_Dialogs->List_Display(tempList);
			return TRUE;
		}

		if (App->SBC_Dialogs->DropList_Data == Enums::DropDialog_Maths)
		{
			App->SBC_Dialogs->List_Maths(tempList);
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

		if (GetDlgItem(hDlg, IDC_STSELECTED) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
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

		if (LOWORD(wParam) == IDC_LISTSELECTION)
		{
			char buff[256];
			int Index = 0;
			Index = SendDlgItemMessage(hDlg, IDC_LISTSELECTION, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			if (Index == -1)
			{
				return 1;
			}

			SendDlgItemMessage(hDlg, IDC_LISTSELECTION, LB_GETTEXT, (WPARAM)Index, (LPARAM)buff);
		
			SetDlgItemText(hDlg, IDC_STSELECTED, buff);

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDOK)
		{
			char buff[256];
			GetDlgItemText(hDlg, IDC_STSELECTED, (LPTSTR)buff, 256);
			strcpy(App->SBC_Dialogs->Chr_DropText, buff);

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
// *			ListObjects:- Terry and Hazel Flanigan 2022		 		   *
// *************************************************************************
void SB_Dialogs::ListObjects(HWND List)
{
	int Count = 0;
	int Total = App->SBC_Scene->Object_Count;

	while (Count < Total)
	{
		
		if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Static)
		{
			SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_Scene->B_Object[Count]->Mesh_Name);
		}
	
		Count++;
	}

	SendMessage(List, LB_SELECTSTRING, -1, (LPARAM)App->SBC_Dialogs->Chr_DropText);
}

// *************************************************************************
// *		List_Locations:- Terry and Hazel Flanigan 2022		 		   *
// *************************************************************************
void SB_Dialogs::List_Locations(HWND List)
{
	int Count = 0;
	while (Count < App->SBC_Scene->Player_Location_Count)
	{
		if (App->SBC_Scene->B_Locations[Count]->Deleted == 0)
		{
			SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_Scene->B_Locations[Count]->Name);
		}
		Count++;
	}

	SendMessage(List, LB_SELECTSTRING, -1, (LPARAM)App->SBC_Dialogs->Chr_DropText);
}

// *************************************************************************
// *			List_Counters:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_Dialogs::List_Counters(HWND List)
{
	int Count = 0;
	
	while (Count < App->SBC_Scene->Counters_Count)
	{
		if (App->SBC_Scene->B_Counter[Count]->Deleted == 0)
		{
			SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_Scene->B_Counter[Count]->Panel_Name);
		}
		Count++;
	}

	SendMessage(List, LB_SELECTSTRING, -1, (LPARAM)App->SBC_Dialogs->Chr_DropText);
}

// *************************************************************************
// *			List_Messages:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_Dialogs::List_Messages(HWND List)
{
	/*int Count = 0;
	while (Count < App->SBC_Scene->TextMessage_Count) // Needs_Removing
	{
		if (App->SBC_Scene->B_Message[Count]->Deleted == 0)
		{
			SendMessage(DropHwnd, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_Scene->B_Message[Count]->TextMessage_Name);
		}
		Count++;
	}*/

	SendMessage(List, LB_SELECTSTRING, -1, (LPARAM)App->SBC_Dialogs->Chr_DropText);
}

// *************************************************************************
// *			List_Axis:- Terry and Hazel Flanigan 2022			 	   *
// *************************************************************************
void SB_Dialogs::List_Axis(HWND List)
{
	SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"X");
	SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Y");
	SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Z");

	SendMessage(List, LB_SELECTSTRING, -1, (LPARAM)App->SBC_Dialogs->Chr_DropText);
}

// *************************************************************************
// *			List_Maths:- Terry and Hazel Flanigan 2022			 	   *
// *************************************************************************
void SB_Dialogs::List_Maths(HWND List)
{
	SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Add");
	SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Subtract");

	SendMessage(List, LB_SELECTSTRING, -1, (LPARAM)App->SBC_Dialogs->Chr_DropText);
}

// *************************************************************************
// *			List_Display:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_Dialogs::List_Display(HWND List)
{
	SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Auto");
	SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"Always");

	SendMessage(List, LB_SELECTSTRING, -1, (LPARAM)App->SBC_Dialogs->Chr_DropText);
}

// **************************************************************************
// *	  		Front_Screen:- Terry and Hazel Flanigan 2022				*
// **************************************************************************
void SB_Dialogs::Front_Screen()
{
	if (App->SBC_Prefs->Show_StartScreen == 1)
	{
		DialogBox(App->hInst, (LPCTSTR)IDD_FRONTDLG, App->Fdlg, (DLGPROC)Front_Screen_Proc);
	}
}

// *************************************************************************
// *		Front_Screen_Proc:- Terry and Hazel Flanigan 2022	  		   *
// *************************************************************************
LRESULT CALLBACK SB_Dialogs::Front_Screen_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->SetTitleBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_STBANNER, WM_SETFONT, (WPARAM)App->Font_Banner, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_CK_FR_DONTSHOW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BT_FR_CHANGELOG, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_QUICKSTART, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
	
		SendDlgItemMessage(hDlg, IDC_ST_WTHC, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STTEST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SetDlgItemText(hDlg, IDC_STBANNER, App->Version);
		SetDlgItemText(hDlg, IDC_ST_WTHC, "W.T.Flanigan and H.C.Flanigan");
		
		char Text[MAX_PATH];
		LoadString(App->hInst, IDS_STRINGFRONT, Text, MAX_PATH);
		SetDlgItemText(hDlg, IDC_STTEST, Text);
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STTEST) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_CK_FR_DONTSHOW) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_WTHC) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STBANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
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

		if (some_item->idFrom == IDC_BT_FR_CHANGELOG && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_QUICKSTART && some_item->code == NM_CUSTOMDRAW)
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

		if (LOWORD(wParam) == IDC_CK_FR_DONTSHOW)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_BL_DESKTOP);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				App->SBC_Prefs->Show_StartScreen = 0;
				App->SBC_Prefs->Write_Preferences();

				return 1;
			}
			else
			{
				App->SBC_Prefs->Show_StartScreen = 1;
				App->SBC_Prefs->Write_Preferences();

				return 1;
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_QUICKSTART)
		{
			App->Cl_Utilities->OpenHTML("Help\\QuickStart.html");
			return TRUE;
		}
		
		if (LOWORD(wParam) == IDC_BT_FR_CHANGELOG)
		{
			App->Cl_Utilities->OpenHTML("Help\\ChangeLog.html");
			return TRUE;
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

		break;

	}
	return FALSE;
}

// *************************************************************************
// *	  	Dialog_Counter():- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Dialogs::Dialog_Counter()
{
	App->SBC_Dialogs->Canceled = 0;

	DialogBox(App->hInst, (LPCTSTR)IDD_PROPS_COUNTER, App->Fdlg, (DLGPROC)Dialog_Counter_Proc);
	return 1;
}

// *************************************************************************
// *        Dialog_Counter_Proc:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
LRESULT CALLBACK SB_Dialogs::Dialog_Counter_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->SetTitleBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_EDTRIGGERVALUE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STCOUNTERNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_COUNTER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTRIGGERVALUE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STMATHS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_CT_COUNTER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CK_ENABLE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_CT_MATHS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_STBANNER, WM_SETFONT, (WPARAM)App->Font_Banner, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_CT_MATHS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		App->SBC_Dialogs->UpDate_Counter_Dialog(hDlg);

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{

		if (GetDlgItem(hDlg, IDC_STCOUNTERNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STMATHS) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STTRIGGERVALUE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_CT_MATHS) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STBANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_CK_ENABLE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_CT_COUNTER) == (HWND)lParam)
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

		if (some_item->idFrom == IDC_BT_COUNTER && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

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

		if (some_item->idFrom == IDC_BT_CT_MATHS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BT_CT_MATHS)
		{
			int Index = App->SBC_Properties->Current_Selected_Object;

			// Collectables
			if (App->SBC_Properties->Edit_Category == Enums::Edit_Collectable)
			{
				int Counter_Index = App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_ID;

				strcpy(App->Cl_Dialogs->btext, "Set Maths Option");

				if (App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths == 1)
				{
					strcpy(App->SBC_Dialogs->Chr_DropText, "Add");
				}

				if (App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths == 2)
				{
					strcpy(App->SBC_Dialogs->Chr_DropText, "Subtract");
				}

				App->SBC_Dialogs->DropList_Data = Enums::DropDialog_Maths;
				App->SBC_Dialogs->Dialog_DropGen();

				if (App->SBC_Dialogs->Canceled == 0)
				{
					int TestChr;

					// Add
					TestChr = strcmp(App->SBC_Dialogs->Chr_DropText, "Add");
					if (TestChr == 0)
					{
						App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths = 1;
					}

					// Subtract
					TestChr = strcmp(App->SBC_Dialogs->Chr_DropText, "Subtract");
					if (TestChr == 0)
					{
						App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths = 2;
					}

					App->SBC_Dialogs->UpDate_Counter_Dialog(hDlg);
				}

			}

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDC_BT_COUNTER)
		{
			int Index = App->SBC_Properties->Current_Selected_Object;

			strcpy(App->Cl_Dialogs->btext, "Select Counter");

			if (App->SBC_Properties->Edit_Category == Enums::Edit_Move_Entity)
			{
				int Counter_Index = App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Counter_ID;

				strcpy(App->SBC_Dialogs->Chr_DropText, App->SBC_Scene->B_Counter[Counter_Index]->Panel_Name);
				App->SBC_Dialogs->DropList_Data = Enums::DropDialog_Counters;
				App->SBC_Dialogs->Dialog_DropGen();

				if (App->SBC_Dialogs->Canceled == 0)
				{
					strcpy(App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Counter_Name, App->SBC_Dialogs->Chr_DropText);

					int CounterIndex = App->SBC_Display->GetIndex_By_Name(App->SBC_Dialogs->Chr_DropText);

					App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Counter_ID = CounterIndex;

				}

				App->SBC_Dialogs->UpDate_Counter_Dialog(hDlg);
			}

			if (App->SBC_Properties->Edit_Category == Enums::Edit_Message)
			{
				int Counter_Index = App->SBC_Scene->B_Object[Index]->S_Message[0]->Counter_ID;

				strcpy(App->SBC_Dialogs->Chr_DropText, App->SBC_Scene->B_Counter[Counter_Index]->Panel_Name);
				App->SBC_Dialogs->DropList_Data = Enums::DropDialog_Counters;
				App->SBC_Dialogs->Dialog_DropGen();

				if (App->SBC_Dialogs->Canceled == 0)
				{
					strcpy(App->SBC_Scene->B_Object[Index]->S_Message[0]->Counter_Name, App->SBC_Dialogs->Chr_DropText);

					int CounterIndex = App->SBC_Display->GetIndex_By_Name(App->SBC_Dialogs->Chr_DropText);

					App->SBC_Scene->B_Object[Index]->S_Message[0]->Counter_ID = CounterIndex;

				}

				App->SBC_Dialogs->UpDate_Counter_Dialog(hDlg);
			}

			// Collectables
			if (App->SBC_Properties->Edit_Category == Enums::Edit_Collectable)
			{
				int Counter_Index = App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_ID;

				strcpy(App->SBC_Dialogs->Chr_DropText, App->SBC_Scene->B_Counter[Counter_Index]->Panel_Name);
				App->SBC_Dialogs->DropList_Data = Enums::DropDialog_Counters;
				App->SBC_Dialogs->Dialog_DropGen();

				if (App->SBC_Dialogs->Canceled == 0)
				{
					strcpy(App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Name, App->SBC_Dialogs->Chr_DropText);

					int CounterIndex = App->SBC_Display->GetIndex_By_Name(App->SBC_Dialogs->Chr_DropText);

					App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_ID = CounterIndex;

				}

				App->SBC_Dialogs->UpDate_Counter_Dialog(hDlg);
				return TRUE;
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CK_ENABLE)
		{
			int Index = App->SBC_Properties->Current_Selected_Object;

			HWND temp = GetDlgItem(hDlg, IDC_CK_ENABLE);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				App->SBC_Dialogs->Set_Counter_Dialog(hDlg, false);

				// Move Entity
				if (App->SBC_Properties->Edit_Category == Enums::Edit_Move_Entity)
				{
					App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Counter_Disabled = 1;
					return 1;
				}

				// Messages
				if (App->SBC_Properties->Edit_Category == Enums::Edit_Message)
				{
					App->SBC_Scene->B_Object[Index]->S_Message[0]->Counter_Disabled = 1;
					return 1;
				}

				// Collectables
				if (App->SBC_Properties->Edit_Category == Enums::Edit_Collectable)
				{
					App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Disabled = 1;
					return 1;
				}

				return 1;
			}
			else
			{
				// Move Entity
				App->SBC_Dialogs->Set_Counter_Dialog(hDlg, true);

				if (App->SBC_Properties->Edit_Category == Enums::Edit_Move_Entity)
				{
					App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Counter_Disabled = 0;
					return 1;
				}

				// Messages
				if (App->SBC_Properties->Edit_Category == Enums::Edit_Message)
				{
					App->SBC_Scene->B_Object[Index]->S_Message[0]->Counter_Disabled = 0;
					return 1;
				}

				// Collectables
				if (App->SBC_Properties->Edit_Category == Enums::Edit_Collectable)
				{
					App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Disabled = 0;
					return 1;
				}

				return 1;
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			char buff[256];
			int result = 0;
			GetDlgItemText(hDlg, IDC_EDTRIGGERVALUE, (LPTSTR)buff, 256);
			strcpy(App->Cl_Dialogs->Chr_Int, buff);
			App->Cl_Dialogs->mInt = atoi(buff);

			if (App->SBC_Properties->Edit_Category == Enums::Edit_Move_Entity)
			{
				int Index = App->SBC_Properties->Current_Selected_Object;
				App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Trigger_Value = atoi(buff);
			}

			if (App->SBC_Properties->Edit_Category == Enums::Edit_Message)
			{
				int Index = App->SBC_Properties->Current_Selected_Object;
				App->SBC_Scene->B_Object[Index]->S_Message[0]->Trigger_Value = atoi(buff);
			}

			// Collectables
			if (App->SBC_Properties->Edit_Category == Enums::Edit_Collectable)
			{
				int Index = App->SBC_Properties->Current_Selected_Object;
				App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Value = atoi(buff);
			}

			App->SBC_Dialogs->Canceled = 0;
			//App->Cl_Dialogs->Active_Dlg_Int = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->SBC_Dialogs->Canceled = 1;
			//App->Cl_Dialogs->Active_Dlg_Int = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *	  	UpDate_Counter_Dialog:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Dialogs::UpDate_Counter_Dialog(HWND hDlg)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	// Move Entity
	if (App->SBC_Properties->Edit_Category == Enums::Edit_Move_Entity)
	{
		if (App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Counter_Disabled == 1)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_ENABLE);
			SendMessage(temp, BM_SETCHECK, 1, 0);
			Set_Counter_Dialog(hDlg, false);
		}
		else
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_ENABLE);
			SendMessage(temp, BM_SETCHECK, 0, 0);
			Set_Counter_Dialog(hDlg, true);
		}

		char chr_TriggerVal[20];
		_itoa(App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Trigger_Value, chr_TriggerVal, 10);
		SetDlgItemText(hDlg, IDC_EDTRIGGERVALUE, (LPCTSTR)chr_TriggerVal);

		char chr_CounterName[20];
		strcpy(chr_CounterName, App->SBC_Scene->B_Counter[App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Counter_ID]->Panel_Name);
		SetDlgItemText(hDlg, IDC_STCOUNTERNAME, (LPCTSTR)chr_CounterName);

		return 1;
	}

	// Messages
	if (App->SBC_Properties->Edit_Category == Enums::Edit_Message)
	{
		if (App->SBC_Scene->B_Object[Index]->S_Message[0]->Counter_Disabled == 1)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_ENABLE);
			SendMessage(temp, BM_SETCHECK, 1, 0);
			Set_Counter_Dialog(hDlg, false);
		}
		else
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_ENABLE);
			SendMessage(temp, BM_SETCHECK, 0, 0);
			Set_Counter_Dialog(hDlg, true);
		}

		char chr_TriggerVal[20];
		_itoa(App->SBC_Scene->B_Object[Index]->S_Message[0]->Trigger_Value, chr_TriggerVal, 10);
		SetDlgItemText(hDlg, IDC_EDTRIGGERVALUE, (LPCTSTR)chr_TriggerVal);

		char chr_CounterName[20];
		strcpy(chr_CounterName, App->SBC_Scene->B_Counter[App->SBC_Scene->B_Object[Index]->S_Message[0]->Counter_ID]->Panel_Name);
		SetDlgItemText(hDlg, IDC_STCOUNTERNAME, (LPCTSTR)chr_CounterName);
		

		return 1;
	}

	// Collectables
	if (App->SBC_Properties->Edit_Category == Enums::Edit_Collectable)
	{
		if (App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Disabled == 1)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_ENABLE);
			SendMessage(temp, BM_SETCHECK, 1, 0);
			Set_Counter_Dialog(hDlg, false);
		}
		else
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_ENABLE);
			SendMessage(temp, BM_SETCHECK, 0, 0);
			Set_Counter_Dialog(hDlg, true);
		}

		char chr_TriggerVal[20];
		_itoa(App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Value, chr_TriggerVal, 10);
		SetDlgItemText(hDlg, IDC_EDTRIGGERVALUE, (LPCTSTR)chr_TriggerVal);

		char chr_CounterName[20];
		strcpy(chr_CounterName, App->SBC_Scene->B_Counter[App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_ID]->Panel_Name);
		SetDlgItemText(hDlg, IDC_STCOUNTERNAME, (LPCTSTR)chr_CounterName);

		if (App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths == 1)
		{
			SetDlgItemText(hDlg, IDC_STMATHS, (LPCTSTR)"Add");
		}

		if (App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths == 2)
		{
			SetDlgItemText(hDlg, IDC_STMATHS, "Subtract");
		}

		return 1;
	}

	return 1;
}

// *************************************************************************
// *	  	Set_Counter_Dialog:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Dialogs::Set_Counter_Dialog(HWND hDlg, bool Enable)
{
	EnableWindow(GetDlgItem(hDlg, IDC_BT_COUNTER), Enable);
	EnableWindow(GetDlgItem(hDlg, IDC_STCOUNTERNAME), Enable);

	EnableWindow(GetDlgItem(hDlg, IDC_STMATHS), Enable);
	EnableWindow(GetDlgItem(hDlg, IDC_BT_CT_MATHS), Enable);

	EnableWindow(GetDlgItem(hDlg, IDC_EDTRIGGERVALUE), Enable);
	
	return 1;
}

// *************************************************************************
// *	  GameMode_StartPosition_Dlg():- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
bool SB_Dialogs::GameMode_StartPosition_Dlg()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_GMSTART, App->Fdlg, (DLGPROC)GameMode_StartPosition_Dlg_Proc);
	return 1;
}
// *************************************************************************
// *	Dialog_GameModeStart_Dlg_Proc:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
LRESULT CALLBACK SB_Dialogs::GameMode_StartPosition_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STARTCUR, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STARTLEVEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_QUITGM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKFPS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		App->Cl_Dialogs->Canceled = 0;
		App->SBC_Dialogs->DoFPS = 0;
		App->SBC_Dialogs->Saved_DoFPS = App->CL_Vm_ImGui->Show_FPS;

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_CKFPS) == (HWND)lParam)
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

		if (some_item->idFrom == IDC_STARTCUR && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_STARTLEVEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_QUITGM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}
	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_CKFPS)
		{

			HWND temp = GetDlgItem(hDlg, IDC_CKFPS);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				App->SBC_Dialogs->DoFPS = 1;
				return 1;
			}
			else
			{
				App->SBC_Dialogs->DoFPS = 0;

				return 1;
			}
			return 1;
		}

		if (LOWORD(wParam) == IDC_STARTCUR)
		{
			App->SBC_Dialogs->Canceled = 0;
			App->CL_Vm_ImGui->Show_FPS = App->SBC_Dialogs->DoFPS;
			EndDialog(hDlg, LOWORD(wParam));
			return 1;
		}

		if (LOWORD(wParam) == IDC_STARTLEVEL)
		{
			App->SBC_Physics->Reset_Physics();
			App->SBC_Dialogs->Canceled = 0;
			App->CL_Vm_ImGui->Show_FPS = App->SBC_Dialogs->DoFPS;
			EndDialog(hDlg, LOWORD(wParam));
		}
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			App->SBC_Dialogs->Canceled = 1;
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_QUITGM)
		{
			App->SBC_Dialogs->Canceled = 1;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;

	}
	return FALSE;
}

