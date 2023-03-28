/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "AB_App.h"
#include "resource.h"
#include "A_TabsControl.h"

A_TabsControl::A_TabsControl(void)
{
	f_TabsDlg_Active = 0;
	Tabs_Control_Hwnd = NULL;
}

A_TabsControl::~A_TabsControl(void)
{
}

// *************************************************************************
// *	  	Tabs_Control_Dlg:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_TabsControl::Show_Tabs_Control_Dlg(bool Show)
{
	if (App->CL_TextureDialog->f_TextureDlg_Active == 1)
	{
		ShowWindow(Tabs_Control_Hwnd, Show);
	}
}

// *************************************************************************
// *	  	Start_Tabs_Control_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsControl::Start_Tabs_Control_Dlg()
{
	if (App->Debug_App == 1)
	{
		Tabs_Control_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TABSDIALOG, App->MainHwnd, (DLGPROC)Tabs_Control_Proc);

		f_TabsDlg_Active = 1;
		App->CL_TextureDialog->Start_TextureDialog();
		App->CL_TabsGroups_Dlg->Start_GroupsDialog();

		App->CL_TabsTemplates_Dlg->Start_TemplatesDialog();
		App->CL_TabsTemplates_Dlg->Show_TemplatesDialog(true);

	}
}

// *************************************************************************
// *        Tabs_Control_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_TabsControl::Tabs_Control_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		//SendDlgItemMessage(hDlg, IDC_ST_GD_GROUPS, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		/*SendDlgItemMessage(hDlg, IDC_LISTTDTEXTURES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTTDAPPLY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));*/
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_ST_GD_GROUPS) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}*/

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		/*LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BTTDAPPLY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_TBTEXTURES)
			{
				App->CL_TabsControl->Hide_Dialogs();
				App->CL_TextureDialog->Show_Dialog(true);
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_TBTEMPLATES)
			{
				App->CL_TabsControl->Hide_Dialogs();
				App->CL_TabsTemplates_Dlg->Show_TemplatesDialog(true);
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_TBGROUPS)
			{
				App->CL_TabsControl->Hide_Dialogs();
				App->CL_TabsGroups_Dlg->Show_GroupsDialog(true);
				return TRUE;
			}

			// -----------------------------------------------------------------
			if (LOWORD(wParam) == IDOK)
			{
				App->CL_TabsControl->f_TabsDlg_Active = 0;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if (LOWORD(wParam) == IDCANCEL)
			{
				App->CL_TabsControl->f_TabsDlg_Active = 0;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			break;
		}
	}
	return FALSE;
}

// *************************************************************************
// *	  	Hide_Dialogs:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_TabsControl::Hide_Dialogs()
{
	App->CL_TextureDialog->Show_Dialog(false);
	App->CL_TabsGroups_Dlg->Show_GroupsDialog(false);
	App->CL_TabsTemplates_Dlg->Show_TemplatesDialog(false);
}
