/*
Copyright (c) 2021 Stage Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

	What_List = 0;

	btext[0] = 0;
	Chr_Text[0] = 0;
}


SB_Dialogs::~SB_Dialogs()
{
}

// *************************************************************************
// *	  				 Dialog_Text	Terry Bernie					   *
// *************************************************************************
bool SB_Dialogs::Dialog_Text()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_PROP_TEXT, App->Fdlg, (DLGPROC)Dialog_Text_Proc);

	return 1;
}
// *************************************************************************
// *				Dialog_Text_Proc	Terry Bernie  					   *
// *************************************************************************
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

// *************************************************************************
// *	  				Show_ListData Terry Flanigan					   *
// *************************************************************************
bool SB_Dialogs::Show_List_Data()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_LISTDATA, App->Fdlg, (DLGPROC)GroupData_Proc);

	return 1;
}
// *************************************************************************
// *        		GroupData_Proc  Terry Flanigan						   *
// *************************************************************************
LRESULT CALLBACK SB_Dialogs::GroupData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		if (App->SBC_Dialogs->What_List == Enums::Show_List_Project)
		{
			App->SBC_Dialogs->List_App_Project(hDlg);
			return TRUE;
		}

		if (App->SBC_Dialogs->What_List == Enums::Show_List_Model)
		{
			//App->SBC_Dialogs->List_ModelData(hDlg);
			return TRUE;
		}

		if (App->SBC_Dialogs->What_List == Enums::Show_List_App)
		{
			//App->SBC_Dialogs->List_App_Data(hDlg);
			return TRUE;
		}

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

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
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
// *	  				List_App_Project Terry Flanigan					   *
// *************************************************************************
void SB_Dialogs::List_App_Project(HWND hDlg)
{

	char buf[255];

	sprintf(buf, "%s", "Project Folder Location");
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
	sprintf(buf, "%s", App->SBC_Project->m_Project_Folder_Path);
	SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	//sprintf(buf, "%s %s", "Full Path", App->SBC_Project->m_Project_Full_Path);
	//SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	//sprintf(buf, "%s %s", "Project Sub Folder", App->SBC_Project->m_Project_Sub_Folder);
	//SendDlgItemMessage(hDlg, IDC_LISTGROUP, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

}
