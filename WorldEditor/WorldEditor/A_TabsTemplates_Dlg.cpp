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

	Insert_Enabled_Flag = 0;
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
	App->Get_Current_Document();

	TemplatesDlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TABSTEMPLATES, App->CL_TabsControl->Tabs_Control_Hwnd, (DLGPROC)Templates_Proc);
	Set_Icons();

	Enable_Insert_Button(true);
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
		SendDlgItemMessage(hDlg, IDC_ST_GD_TEMPLATES, WM_SETFONT, (WPARAM)App->Font_CB18, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTINSERT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ACTOR, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_ST_GD_TEMPLATES) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
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

		if (some_item->idFrom == IDC_ACTOR && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTINSERT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		{
		if (LOWORD(wParam) == IDC_ACTOR)
		{
			App->CLSB_Loader->Load_ActorWorld();
			return 1;
		}
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

		if (LOWORD(wParam) == IDC_BTINSERT)
		{
			App->Get_Current_Document();

			if (App->m_pDoc->mModeTool == ID_TOOLS_TEMPLATE)
			{
				if (App->CL_Brush->Get_Brush_Count() == 0)
				{
					App->CLSB_Doc->AddBrushToWorld();

					App->CLSB_Level->Check_For_Centre_Texture();
					App->CLSB_Level->Check_For_Centre_Brush();
					App->CLSB_Level->Change_Centre_Brush_Texture();

					App->m_pDoc->SetModifiedFlag();
				}
				else
				{
					App->CLSB_Doc->AddBrushToWorld();
					App->m_pDoc->SetModifiedFlag();
				}
				
			}

			App->m_pDoc->DoGeneralSelect();

			App->CL_World->Reset_Editor();

			App->CL_TabsTemplates_Dlg->Enable_Insert_Button(false);

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
// *	  	Enable_Insert_Button:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsTemplates_Dlg::Enable_Insert_Button(bool Enable)
{
	EnableWindow(GetDlgItem(TemplatesDlg_Hwnd,IDC_BTINSERT),Enable);
	Insert_Enabled_Flag = Enable;

	RedrawWindow(App->CL_TabsTemplates_Dlg->TemplatesDlg_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}


// *************************************************************************
// *       CreateNewTemplateBrush:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_TabsTemplates_Dlg::CreateNewTemplateBrush(Brush *pBrush)
{
	App->Get_Current_Document();
	
	geVec3d *pTemplatePos;
	geVec3d MoveVec;
	geVec3d BrushPos;

	assert (pBrush != NULL);

	if (App->m_pDoc->BTemplate != NULL)
	{
		Brush_Destroy (&App->m_pDoc->BTemplate);
	}

	App->m_pDoc->BTemplate = pBrush;
	App->m_pDoc->CurBrush = pBrush;

	App->m_pDoc->TempEnt	= FALSE;
	App->m_pDoc->SetDefaultBrushTexInfo (App->m_pDoc->CurBrush);
	Brush_Bound (App->m_pDoc->CurBrush);
	Brush_Center (App->m_pDoc->CurBrush, &BrushPos);

	pTemplatePos = Level_GetTemplatePos (App->CLSB_Doc->pLevel);
	geVec3d_Subtract (pTemplatePos, &BrushPos, &MoveVec);
	Brush_Move (App->m_pDoc->CurBrush, &MoveVec);

	App->m_pDoc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
	App->m_pDoc->SetModifiedFlag ();
}
