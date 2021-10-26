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
#include "SB_Project.h"


SB_Project::SB_Project()
{
}


SB_Project::~SB_Project()
{
}

// *************************************************************************
// *	  				Create_Project Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Create_Project()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_PROJECT, App->Fdlg, (DLGPROC)Create_Project_Proc);
	return 1;
}
// *************************************************************************
// *					Dialog_GameModeStart_Dlg_Proc	  				   *
// *************************************************************************
LRESULT CALLBACK SB_Project::Create_Project_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->Cl_Dialogs->Canceled = 0;
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_STARTCUR && some_item->code == NM_CUSTOMDRAW)
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
		}*/

		return CDRF_DODEFAULT;
	}
	case WM_COMMAND:

		/*if (LOWORD(wParam) == IDC_STARTCUR)
		{
			App->Cl_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return 1;
		}

		if (LOWORD(wParam) == IDC_STARTLEVEL)
		{
			App->Cl_Bullet->Reset_Physics();
			App->Cl_Dialogs->Canceled = 0;
			EndDialog(hDlg, LOWORD(wParam));
		}*/

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;

	}
	return FALSE;
}
