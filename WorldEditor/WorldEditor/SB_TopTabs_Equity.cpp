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
	Camera_TB_hWnd = nullptr;

	Toggle_Tabs_Test_Flag = 0;
	Toggle_Dimensions_Flag = 0;

	Toggle_Camera_First_Flag = 0;
	Toggle_Camera_Free_Flag = 0;
	Toggle_Camera_Model_Flag = 1;

	Toggle_Tabs_Camera_Flag = 1;
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
	Start_Camera_TB();

	Hide_Tabs();
	ShowWindow(Camera_TB_hWnd, SW_SHOW);
	Toggle_Tabs_Camera_Flag = 1;

	RedrawWindow(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *		Start_Tabs_Headers:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs_Equity::Start_Tabs_Headers(void)
{
	Tabs_TB_hWnd_Eq = nullptr;

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
		SendDlgItemMessage(hDlg, IDC_BT_TT_CAMERA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
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

		if (some_item->idFrom == IDC_BT_TT_CAMERA && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CLSB_TopTabs_Equity->Toggle_Tabs_Camera_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BT_TT_TEST)
		{
			App->CLSB_TopTabs_Equity->Hide_Tabs();
			ShowWindow(App->CLSB_TopTabs_Equity->Test_TB_hWnd, SW_SHOW);
			App->CLSB_TopTabs_Equity->Toggle_Tabs_Test_Flag = 1;

			RedrawWindow(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			//App->CL_Ogre->Ogre_Listener->ImGui_Render_Tab = Enums::ImGui_Render_Group;
			//App->CL_Panels->Show_Panels(1);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_TT_CAMERA)
		{
			App->CLSB_TopTabs_Equity->Hide_Tabs();
			ShowWindow(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, SW_SHOW);
			App->CLSB_TopTabs_Equity->Toggle_Tabs_Camera_Flag = 1;

			RedrawWindow(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			return TRUE;
		}
	}
	}
	return FALSE;
}

// *************************************************************************
// *			Hide_Tabs:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_TopTabs_Equity::Hide_Tabs(void)
{

	ShowWindow(App->CLSB_TopTabs_Equity->Test_TB_hWnd, SW_HIDE);
	ShowWindow(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, SW_HIDE);


	Toggle_Tabs_Test_Flag = 0;
	Toggle_Tabs_Camera_Flag = 0;


}

// *************************************************************************
// *			Start_Files_TB:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs_Equity::Start_Files_TB(void)
{
	Test_TB_hWnd = nullptr;

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
		SendDlgItemMessage(hDlg, IDC_BTTBDIMENSIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_EQ_GROUPS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
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

		if (some_item->idFrom == IDC_BT_EQ_GROUPS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTTBDIMENSIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_TopTabs_Equity->Toggle_Dimensions_Flag);
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

			App->CLSB_Export_World->Export_World_GD3D(1);

			pDoc->ResetAllSelections();
			pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);

			App->CLSB_Equity->mAutoLoad = 1;
			App->CLSB_Equity->Auto_Load_File();
			return 1;
		}

		if (LOWORD(wParam) == IDC_BTTBDIMENSIONS)
		{

			if (App->CLSB_Dimensions->Show_Position == 1)
			{
				App->CLSB_Dimensions->Show_Position = 0;
				//App->CL_Panels->Show_Panels(1);
			}
			else
			{
				App->CLSB_Dimensions->Show_Position = 1;
				//App->CL_Panels->Show_Panels(0);
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_EQ_GROUPS)
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				strcpy(App->CLSB_Dialogs->btext, "Groups");
				strcpy(App->CLSB_Dialogs->Chr_DropText, App->CLSB_Model->Group[0]->GroupName);
				App->CLSB_Dialogs->DropList_Data = 0;

				App->CLSB_Dialogs->Start_Dialog_DropGen();
			}
			return 1;
		}

		return FALSE;
	}

	}
	return FALSE;
}

// *************************************************************************
// *			Start_Camera_TB:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs_Equity::Start_Camera_TB(void)
{
	Camera_TB_hWnd = nullptr;

	Camera_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_EQ_CAMERA, Tabs_TB_hWnd_Eq, (DLGPROC)Camera_TB_Proc);
}

// *************************************************************************
// *			Camera_TB_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK SB_TopTabs_Equity::Camera_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BT_TT_MODEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_FIRST_MODEX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TT_FREE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TT_RESETCAM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_TT_ZEROCAM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_CAMERASPEED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_TT_MODEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_TopTabs_Equity->Toggle_Camera_Model_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_FIRST_MODEX && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_TopTabs_Equity->Toggle_Camera_First_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TT_FREE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CLSB_TopTabs_Equity->Toggle_Camera_Free_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TT_RESETCAM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_TT_ZEROCAM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_CAMERASPEED && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		
		if (LOWORD(wParam) == IDC_BT_TT_MODEL)
		{
			App->CLSB_TopTabs_Equity->Camera_Set_Model();
			return 1;
		}

		if (LOWORD(wParam) == IDC_FIRST_MODEX)
		{
			App->CLSB_TopTabs_Equity->Camera_Set_First();

			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_TT_FREE)
		{
			App->CLSB_TopTabs_Equity->Camera_Set_Free();
			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_TT_RESETCAM)
		{
			App->CLSB_Camera_EQ->Reset_View();
			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_TT_ZEROCAM)
		{
			App->CLSB_Camera_EQ->Zero_View();
			return 1;
		}

		if (LOWORD(wParam) == IDC_BT_CAMERASPEED)
		{
			App->CLSB_Dialogs->Start_Speed_Camera();
			return 1;
		}

		return FALSE;
	}

	}
	return FALSE;
}

// *************************************************************************
// *			Camera_Set_Model:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_TopTabs_Equity::Camera_Set_Model(void)
{
	App->CLSB_Camera_EQ->Set_Camera_Mode(Enums::CamModel);
	App->CLSB_TopTabs_Equity->Toggle_Camera_Model_Flag = 1;
	App->CLSB_TopTabs_Equity->Toggle_Camera_Free_Flag = 0;
	App->CLSB_TopTabs_Equity->Toggle_Camera_First_Flag = 0;

	RedrawWindow(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *			Camera_Set_Free:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_TopTabs_Equity::Camera_Set_Free(void)
{
	App->CLSB_Camera_EQ->Set_Camera_Mode(Enums::CamDetached);
	App->CLSB_TopTabs_Equity->Toggle_Camera_Free_Flag = 1;
	App->CLSB_TopTabs_Equity->Toggle_Camera_Model_Flag = 0;
	App->CLSB_TopTabs_Equity->Toggle_Camera_First_Flag = 0;

	if (App->CLSB_Model->Player_Added == 1)
	{
		int f = App->CLSB_Model->B_Player[0]->Phys_Body->getCollisionFlags();
		App->CLSB_Model->B_Player[0]->Phys_Body->setCollisionFlags(f & (~(1 << 5)));
	}

	RedrawWindow(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *			Camera_Set_First:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_TopTabs_Equity::Camera_Set_First(void)
{
	if (App->CLSB_Model->Player_Added == 1)
	{
		App->CLSB_Ogre->OgreListener->CameraMode = Enums::CamFirst;
		App->CLSB_TopTabs_Equity->Toggle_Camera_First_Flag = 1;
		App->CLSB_TopTabs_Equity->Toggle_Camera_Model_Flag = 0;
		App->CLSB_TopTabs_Equity->Toggle_Camera_Free_Flag = 0;

		App->CLSB_Model->B_Player[0]->Player_Node->setVisible(false);

		int f = App->CLSB_Model->B_Player[0]->Phys_Body->getCollisionFlags();
		App->CLSB_Model->B_Player[0]->Phys_Body->setCollisionFlags(f | (1 << 5));

		App->CLSB_Ogre->BulletListener->Render_Debug_Flag = 0;
		App->CLSB_Ogre->RenderFrame();
		App->CLSB_Ogre->BulletListener->Render_Debug_Flag = 1;

		App->CLSB_Ogre->OgreListener->GD_Run_Physics = 1;

		RedrawWindow(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}

}


