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
#include "A_TabsTemplates_Dlg.h"

A_TabsTemplates_Dlg::A_TabsTemplates_Dlg(void)
{
	TemplatesDlg_Hwnd = NULL;
}

A_TabsTemplates_Dlg::~A_TabsTemplates_Dlg(void)
{
}

// *************************************************************************
// *	  	Show_TemplatesDialog:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsTemplates_Dlg::Show_TemplatesDialog(bool Show)
{
	ShowWindow(TemplatesDlg_Hwnd, Show);
}

// *************************************************************************
// *	  	Start_TemplatesDialog:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsTemplates_Dlg::Start_TemplatesDialog()
{
	TemplatesDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TABSTEMPLATES, App->CL_TabsControl->Tabs_Control_Hwnd, (DLGPROC)Templates_Proc);
	Set_Icons();
}

// *************************************************************************
// *        TemplatesDialog_Proc:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
LRESULT CALLBACK A_TabsTemplates_Dlg::Templates_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		/*SendDlgItemMessage(hDlg, IDC_STTDTXLNAME, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_LISTTDTEXTURES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTTDAPPLY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));*/
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_STATIC) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
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

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_BTTDAPPLY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDC_GD_CUBE_PRIMITIVE)
			{
				App->CL_CreateBoxDialog->Start_CreateBox_Dlg();
				return 1;
			}

			if (LOWORD(wParam) == IDC_GD_CYLINDER_PRIMITIVE)
			{
				App->CL_CreateCylDialog->Start_CreateCyl_Dlg();
				return 1;
			}

			if (LOWORD(wParam) == IDC_GD_CONE_PRIMITIVE)
			{
				App->CL_CreateConeDialog->Start_CreateCone_Dlg();
				return 1;
			}

			if (LOWORD(wParam) == IDC_GD_SPHEROID_PRIMITIVE)
			{
				App->CL_CreateSpheroidDialog->Start_CreateSpheroid_Dlg();
				return 1;
			}

			if (LOWORD(wParam) == IDC_GD_STAIRCASE_PRIMITIVE)
			{
				App->CL_CreateStaircaseDialog->Start_CreateStaircase_Dlg();
				return 1;
			}

			if (LOWORD(wParam) == IDC_GD_ARCH_PRIMITIVE)
			{
				App->CL_CreateArchDialog->Start_CreateArch_Dlg();
				return 1;
			}
			
			// -----------------------------------------------------------------
			if (LOWORD(wParam) == IDOK)
			{
				//App->CL_TextureDialog->f_TextureDlg_Active = 0;
				//EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if (LOWORD(wParam) == IDCANCEL)
			{
				//App->CL_TextureDialog->f_TextureDlg_Active = 0;
				//EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			break;
		}
	}
	return FALSE;
}

// *************************************************************************
// *	  		Set_Icons:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_TabsTemplates_Dlg::Set_Icons()
{
	HWND Temp = GetDlgItem(TemplatesDlg_Hwnd, IDC_GD_CUBE_PRIMITIVE);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(HANDLE)App->Hnd_Box_Icon);

	Temp = GetDlgItem(TemplatesDlg_Hwnd, IDC_GD_CYLINDER_PRIMITIVE);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(HANDLE)App->Hnd_Cyl_Icon);

	Temp = GetDlgItem(TemplatesDlg_Hwnd, IDC_GD_CONE_PRIMITIVE);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(HANDLE)App->Hnd_Cone_Icon);

	Temp = GetDlgItem(TemplatesDlg_Hwnd, IDC_GD_SPHEROID_PRIMITIVE);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(HANDLE)App->Hnd_Spheriod_Icon);

	Temp = GetDlgItem(TemplatesDlg_Hwnd, IDC_GD_STAIRCASE_PRIMITIVE);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(HANDLE)App->Hnd_Stairs_Icon);

	Temp = GetDlgItem(TemplatesDlg_Hwnd, IDC_GD_ARCH_PRIMITIVE);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_ICON, (LPARAM)(HANDLE)App->Hnd_Arch_Icon);

}


// *************************************************************************
// *       CreateNewTemplateBrush:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsTemplates_Dlg::CreateNewTemplateBrush(Brush *pBrush)
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	geVec3d *pTemplatePos;
	geVec3d MoveVec;
	geVec3d BrushPos;

	assert (pBrush != NULL);

	if (m_pDoc->BTemplate != NULL)
	{
		Brush_Destroy (&m_pDoc->BTemplate);
	}

	m_pDoc->BTemplate = pBrush;
	m_pDoc->CurBrush = pBrush;

	m_pDoc->TempEnt	= FALSE;
	m_pDoc->SetDefaultBrushTexInfo (m_pDoc->CurBrush);
	Brush_Bound (m_pDoc->CurBrush);
	Brush_Center (m_pDoc->CurBrush, &BrushPos);

	pTemplatePos = Level_GetTemplatePos (m_pDoc->pLevel);
	geVec3d_Subtract (pTemplatePos, &BrushPos, &MoveVec);
	Brush_Move (m_pDoc->CurBrush, &MoveVec);

	m_pDoc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
	m_pDoc->SetModifiedFlag ();
}
