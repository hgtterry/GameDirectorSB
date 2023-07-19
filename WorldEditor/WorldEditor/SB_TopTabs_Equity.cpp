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
#include "SB_TopTabs_Equity.h"

SB_TopTabs_Equity::SB_TopTabs_Equity(void)
{
	Tabs_TB_hWnd_Eq = nullptr;
	Test_TB_hWnd = nullptr;


	Toggle_Tabs_Test_Flag = 1;
}

SB_TopTabs_Equity::~SB_TopTabs_Equity(void)
{
}

// *************************************************************************
// *			Start_Tabs:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_TopTabs_Equity::Start_Tabs(void)
{
	Start_Tabs_Headers();
	Start_Files_TB();
}

// *************************************************************************
// *		Start_Tabs_Headers:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs_Equity::Start_Tabs_Headers(void)
{
	Tabs_TB_hWnd_Eq = CreateDialog(App->hInst, (LPCTSTR)IDD_TOPTABS_EQUITY, App->CLSB_Equity->Equity_Main_hWnd, (DLGPROC)Tabs_Headers_Proc);
}

// *************************************************************************
// *		Tabs_Headers_Proc_Proc:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs_Equity::Tabs_Headers_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_TT_TEST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_TT_TEST && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CLSB_TopTabs_Equity->Toggle_Tabs_Test_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BT_TT_TEST)
		{
			Debug
			/*App->CL_TopBar->Hide_Tabs();
			ShowWindow(App->CL_TopBar->Files_TB_hWnd, SW_SHOW);
			App->CL_TopBar->Toggle_Tabs_File_Flag = 1;

			RedrawWindow(App->CL_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			App->CL_Ogre->Ogre_Listener->ImGui_Render_Tab = Enums::ImGui_Render_Group;

			App->CL_Panels->Show_Panels(1);*/

			return TRUE;
		}

		/*if (LOWORD(wParam) == IDC_TBGROUP)
		{
			App->CL_TopBar->Hide_Tabs();
			ShowWindow(App->CL_TopBar->Group_TB_hWnd, SW_SHOW);
			App->CL_TopBar->Toggle_Tabs_Group_Flag = 1;

			RedrawWindow(App->CL_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			App->CL_Ogre->Ogre_Listener->ImGui_Render_Tab = Enums::ImGui_Render_Group;

			App->CL_Panels->Show_Panels(1);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBMODEL)
		{
			App->CL_TopBar->Hide_Tabs();
			ShowWindow(App->CL_TopBar->Model_TB_hWnd, SW_SHOW);
			App->CL_TopBar->Toggle_Tabs_Model_Flag = 1;

			RedrawWindow(App->CL_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			App->CL_Ogre->Ogre_Listener->ImGui_Render_Tab = Enums::ImGui_Render_Model;

			if (App->CL_ImGui->Show_Dimensions == 1)
			{
				App->CL_Panels->Show_Panels(0);
			}
			else
			{
				App->CL_Panels->Show_Panels(1);
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBCAMERA)
		{
			App->CL_TopBar->Hide_Tabs();
			ShowWindow(App->CL_TopBar->Camera_TB_hWnd, SW_SHOW);
			App->CL_TopBar->Toggle_Tabs_Camera_Flag = 1;

			RedrawWindow(App->CL_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			App->CL_Ogre->Ogre_Listener->ImGui_Render_Tab = Enums::ImGui_Render_Camera;

			App->CL_Panels->Show_Panels(1);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBANIMATION)
		{
			App->CL_TopBar->Hide_Tabs();
			ShowWindow(App->CL_TopBar->Animation_TB_hWnd, SW_SHOW);
			App->CL_TopBar->Toggle_Tabs_Animation_Flag = 1;

			RedrawWindow(App->CL_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			App->CL_Ogre->Ogre_Listener->ImGui_Render_Tab = Enums::ImGui_Render_Animation;

			App->CL_Panels->Show_Panels(1);

			return TRUE;
		}*/

	}
	}
	return FALSE;
}

// *************************************************************************
// *			Start_Files_TB:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs_Equity::Start_Files_TB(void)
{
	Test_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_EQ_TEST, Tabs_TB_hWnd_Eq, (DLGPROC)Files_TB_Proc);
}

// *************************************************************************
// *			Files_TB_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs_Equity::Files_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_UPDATE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_UPDATE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_UPDATE)
		{
			CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

			pDoc->SelectAll();
			pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);

			App->CL_Export_World->Export_World_GD3D(1);

			pDoc->ResetAllSelections();
			pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);

			App->CLSB_Equity->mAutoLoad = 1;
			App->CLSB_Equity->Auto_Load_File();
			return 1;
		}

		return FALSE;
	}

	}
	return FALSE;
}
