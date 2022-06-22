#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_Groups.h"


ME_Groups::ME_Groups()
{
	RightGroups_Hwnd = nullptr;
}


ME_Groups::~ME_Groups()
{
}

// *************************************************************************
// *							Start_Groups				  		 	   *
// *************************************************************************
bool ME_Groups::Start_Groups()
{
	RightGroups_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_RIGHTGROUPS, App->MainHwnd, (DLGPROC)Groups_Proc);
	ShowWindow(RightGroups_Hwnd, 1);
	return 1;
}

// *************************************************************************
// *						Groups_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK ME_Groups::Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		/*SendDlgItemMessage(hDlg, IDC_RGGROUPNAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_RGTEXTURENAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_INFO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CHANGETEXTURE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SetWindowLong(GetDlgItem(hDlg, IDC_BASETEXTURE2), GWL_WNDPROC, (LONG)ViewerBasePic);*/
	}

	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_RGGROUPNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_RGTEXTURENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_GROUPID) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}*/

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_CLOSE:
	{
		/*ShowWindow(App->EBC_Groups->RightGroups_Hwnd, 0);*/

		break;
	}
	case WM_NOTIFY:
	{
		/*LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_CHANGETEXTURE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_INFO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

	}

	}
	return FALSE;
}
