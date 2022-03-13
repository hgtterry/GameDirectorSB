/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "resource.h"
#include "ME_TopBar.h"


ME_TopBar::ME_TopBar()
{
	TabsHwnd = nullptr;
}


ME_TopBar::~ME_TopBar()
{
}

// *************************************************************************
// *	  				Start_TopBar_Globals  	Terry					   *
// *************************************************************************
bool ME_TopBar::Start_TopBar()
{
	CreateDialog(App->hInst, (LPCTSTR)IDD_TOPBAR, App->Fdlg, (DLGPROC)TopBar_Proc);
	//Init_Bmps_Globals();
	return 1;
}

// *************************************************************************
// *						TopBar_Globals_Proc Terry					   *
// *************************************************************************
LRESULT CALLBACK ME_TopBar::TopBar_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->CL_TopBar->TabsHwnd = hDlg;

		/*App->SBC_TopTabs->Start_Tabs_Headers();
		App->SBC_TopTabs->Start_Camera_TB();
		App->SBC_TopTabs->Start_Dimensions_TB();
		App->SBC_TopTabs->Start_Physics_TB();
		App->SBC_TopTabs->Start_Editors_TB();
		App->SBC_TopTabs->Start_Files_TB();*/

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

		/*if (some_item->idFrom == IDC_TBSHOWGRID && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_TopTabs->Toggle_Grid_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSHOWHAIR && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_TopTabs->Toggle_Hair_Flag);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		//-------------------------------------------------------- Show Grid
		//if (LOWORD(wParam) == IDC_TBSHOWGRID)
		{
			/*HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWGRID);

			if (App->Cl_Grid->ShowGridFlag == 1)
			{
				App->Cl_Grid->Grid_SetVisible(0);
				App->Cl_Grid->ShowGridFlag = 0;

				App->SBC_TopTabs->Toggle_Grid_Flag = 0;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOff_Bmp);
			}
			else
			{
				App->Cl_Grid->Grid_SetVisible(1);
				App->Cl_Grid->ShowGridFlag = 1;

				App->SBC_TopTabs->Toggle_Grid_Flag = 1;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

			}*/
			//return TRUE;
		}

		//-------------------------------------------------------- Show Hair
		//if (LOWORD(wParam) == IDC_TBSHOWHAIR)
		{
			//HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWHAIR);

			/*if (App->Cl_Grid->ShowHair == 1)
			{
				App->Cl_Grid->ShowHair = 0;
				App->Cl_Grid->Hair_SetVisible(0);

				App->SBC_TopTabs->Toggle_Hair_Flag = 0;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOff_Bmp);
			}
			else
			{
				App->Cl_Grid->ShowHair = 1;
				App->Cl_Grid->Hair_SetVisible(1);

				App->SBC_TopTabs->Toggle_Hair_Flag = 1;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);
			}*/
			//return TRUE;
		}

		//-------------------------------------------------------- Show Info
		//if (LOWORD(wParam) == IDC_TBINFO)
		{
			/*if (App->CL_Vm_ImGui->Show_Model_Data == 1)
			{
				App->CL_Vm_ImGui->Show_Model_Data = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_Model_Data = 1;
			}*/
			//return TRUE;
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
