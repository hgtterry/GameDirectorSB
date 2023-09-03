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
#include "A_CreateBoxDialog.h"

A_CreateBoxDialog::A_CreateBoxDialog(void)
{
	m_YSize = 128.0f;
	m_Solid = 0;
	m_XSizeBot = 128.0f;
	m_XSizeTop = 128.0f;
	m_ZSizeBot = 128.0f;
	m_ZSizeTop = 128.0f;
	m_TCut = false;
	m_Thickness = 16.0f;
	m_TSheet = false;

	m_UseCamPos = 0;

	Solid_Flag = 1;
	Hollow_Flag = 0;
	Cut_Flag = 0;

	strcpy(BoxName,"Box");
}

A_CreateBoxDialog::~A_CreateBoxDialog(void)
{
}

// *************************************************************************
// *	  	Start_CreateBox_Dlg:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateBoxDialog::Start_CreateBox_Dlg()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	pBoxTemplate = Level_GetBoxTemplate (m_pDoc->pLevel);

	App->CL_TabsControl->Enable_Tabs_Dlg(false);

	DialogBox(App->hInst, (LPCTSTR)IDD_CREATEBOX, App->MainHwnd, (DLGPROC)CreateBox_Proc);
}

// *************************************************************************
// *        CreateBox_Proc:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
LRESULT CALLBACK A_CreateBoxDialog::CreateBox_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STBOTTOM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STBOTX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STBOTZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_XSIZEBOT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ZSIZEBOT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_STTOP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTOPX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STZTOP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_XSIZETOP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ZSIZETOP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_BT_BOXSOLID, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_BOXHOLLOW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_BOXCUTBRUSH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STGENERAL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STYSIZE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STWALL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_YSIZE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_THICKNESS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
	
		SendDlgItemMessage(hDlg, IDC_STNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDITNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BOXDEFAULTS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_BOXROOM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		App->CL_CreateBoxDialog->Set_Members();
		App->CL_CreateBoxDialog->Set_DLG_Members(hDlg);
		App->CL_CreateBoxDialog->Set_Defaults(hDlg);

		int Count = App->CL_Brush->Get_Brush_Count();
		char Num[32];
		char Name[32];
		itoa(Count, Num, 10);
		strcpy(Name, "Box_");
		strcat(Name, Num);

		SetDlgItemText(hDlg, IDC_EDITNAME, (LPCTSTR)Name);

		
		HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);

		Temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
		SendMessage(Temp,BM_SETCHECK,1,0);
		App->CL_CreateBoxDialog->m_UseCamPos = 0;

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STTOP) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STBOTTOM) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STTOPX) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STWALL) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STGENERAL) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_TCUT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_TSHEET) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STZTOP) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STBOTX) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STBOTZ) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STYSIZE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		// --------------------------------------------------
		if (GetDlgItem(hDlg, IDC_STNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STCAMPOS) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_CKWORLDCENTRE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_CKCAMPOSITION) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
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

		if (some_item->idFrom == IDC_BT_BOXSOLID && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_CreateBoxDialog->Solid_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_BOXHOLLOW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_CreateBoxDialog->Hollow_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_BOXCUTBRUSH && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_CreateBoxDialog->Cut_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BOXDEFAULTS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_BOXROOM && some_item->code == NM_CUSTOMDRAW)
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
		
		
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_BT_BOXSOLID)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);
			SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_SolidBox_Bmp);

			App->CL_CreateBoxDialog->Zero_Dlg_Flags(hDlg);
			App->CL_CreateBoxDialog->m_Solid = 0;
			App->CL_CreateBoxDialog->Solid_Flag = 1;

			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_BOXHOLLOW)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);
			SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HollowBox_Bmp);
			
			App->CL_CreateBoxDialog->Zero_Dlg_Flags(hDlg);
			App->CL_CreateBoxDialog->m_Solid = 1;
			App->CL_CreateBoxDialog->Hollow_Flag = 1;

			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_BOXCUTBRUSH)
		{

			if (App->CL_CreateBoxDialog->Cut_Flag == 0)
			{
				//App->CL_CreateBoxDialog->Zero_Dlg_Flags(hDlg);
				App->CL_CreateBoxDialog->m_TCut = 1;
				App->CL_CreateBoxDialog->Cut_Flag = 1;

				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				return 1;
			}
			else
			{
				//App->CL_CreateBoxDialog->Zero_Dlg_Flags(hDlg);
				App->CL_CreateBoxDialog->m_TCut = 0;
				App->CL_CreateBoxDialog->Cut_Flag = 0;

				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				return 1;
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKWORLDCENTRE)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
			SendMessage(temp, BM_SETCHECK, 1, 0);

			temp = GetDlgItem(hDlg, IDC_CKCAMPOSITION);
			SendMessage(temp, BM_SETCHECK, 0, 0);

			App->CL_CreateBoxDialog->m_UseCamPos = 0;
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKCAMPOSITION)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CKCAMPOSITION);
			SendMessage(temp, BM_SETCHECK, 1, 0);

			temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
			SendMessage(temp, BM_SETCHECK, 0, 0);

			App->CL_CreateBoxDialog->m_UseCamPos = 1;
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TCUT)
		{
			HWND temp = GetDlgItem(hDlg, IDC_TCUT);

			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				App->CL_CreateBoxDialog->m_TCut = 1;
				return 1;
			}
			else
			{
				App->CL_CreateBoxDialog->m_TCut = 0;
				return 1;
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BOXDEFAULTS)
		{
			App->CL_CreateBoxDialog->Set_Defaults(hDlg);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_BOXROOM)
		{
			App->CL_CreateBoxDialog->Set_Room(hDlg);
			return TRUE;
		}
		
		// -----------------------------------------------------------------
		if (LOWORD(wParam) == IDOK)
		{

			App->CL_CreateBoxDialog->Get_DLG_Members(hDlg);
			App->CL_CreateBoxDialog->Set_BoxTemplate();
			App->CL_CreateBoxDialog->CreateCube();

			App->CL_TabsControl->Enable_Tabs_Dlg(true);
			App->CL_TabsTemplates_Dlg->Enable_Insert_Button(true);

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;

		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CL_TabsControl->Enable_Tabs_Dlg(true);
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;

		}

		break;
	}
	}
	return FALSE;
}

// *************************************************************************
// *		   CreateCube:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_CreateBoxDialog::CreateCube() 
{
	App->Get_Current_Document();

	App->m_pDoc->OnToolsTemplate();

	Brush *pCube;
	pCube = BrushTemplate_CreateBox (pBoxTemplate);
	if (pCube != NULL)
	{
		App->m_pDoc->LastTemplateTypeName = BoxName;
		
		CreateNewTemplateBrush(pCube);

	}
	else
	{
		App->Say("No pCube");
	}
}

// *************************************************************************
// *       CreateNewTemplateBrush:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateBoxDialog::CreateNewTemplateBrush(Brush *pBrush)
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

	App->m_pDoc->CurBrush = pBrush;

	App->m_pDoc->TempEnt	= FALSE;
	App->m_pDoc->SetDefaultBrushTexInfo (App->m_pDoc->CurBrush);
	Brush_Bound (App->m_pDoc->CurBrush);
	Brush_Center (App->m_pDoc->CurBrush, &BrushPos);

	pTemplatePos = Level_GetTemplatePos (App->m_pDoc->pLevel);

	if (m_UseCamPos == 1)
	{
		geVec3d Pos;

		Pos = App->CLSB_Camera_WE->Get_Camera_Position();

		pTemplatePos->X = Pos.X;
		pTemplatePos->Y = Pos.Y;
		pTemplatePos->Z = Pos.Z;
	}
	else
	{
		pTemplatePos->X = 0;
		pTemplatePos->Y = 0;
		pTemplatePos->Z = 0;
	}
	

	geVec3d_Subtract (pTemplatePos, &BrushPos, &MoveVec);

	Brush_Move (App->m_pDoc->CurBrush, &MoveVec);

	App->m_pDoc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
	App->m_pDoc->SetModifiedFlag ();
}

// *************************************************************************
// *		 Set_Members:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_CreateBoxDialog::Set_Members() 
{
	m_YSize = pBoxTemplate->YSize;
	m_Solid = pBoxTemplate->Solid;
	m_XSizeBot = pBoxTemplate->XSizeBot;
	m_XSizeTop = pBoxTemplate->XSizeTop;
	m_ZSizeBot = pBoxTemplate->ZSizeBot;
	m_ZSizeTop = pBoxTemplate->ZSizeTop;
	m_TCut = pBoxTemplate->TCut;
	m_Thickness = pBoxTemplate->Thickness;
	m_TSheet = pBoxTemplate->TSheet;
}

// *************************************************************************
// *		 Set_DLG_Members:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateBoxDialog::Set_DLG_Members(HWND hDlg) 
{
	char buf[MAX_PATH];
	sprintf(buf, "%0.0f", m_XSizeTop);
	SetDlgItemText(hDlg, IDC_XSIZETOP, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_ZSizeTop);
	SetDlgItemText(hDlg, IDC_ZSIZETOP, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_XSizeBot);
	SetDlgItemText(hDlg, IDC_XSIZEBOT, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_ZSizeBot);
	SetDlgItemText(hDlg, IDC_ZSIZEBOT, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_YSize);
	SetDlgItemText(hDlg, IDC_YSIZE, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_Thickness);
	SetDlgItemText(hDlg, IDC_THICKNESS, (LPCTSTR)buf);

	HWND temp = GetDlgItem(hDlg, IDC_TCUT);
	if (m_TCut == 1)
	{
		SendMessage(temp,BM_SETCHECK,1,0);
	}
	else
	{
		SendMessage(temp,BM_SETCHECK,0,0);
	}
}

// *************************************************************************
// *		 Get_DLG_Members:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateBoxDialog::Get_DLG_Members(HWND hDlg) 
{

	char buff[MAX_PATH];

	GetDlgItemText(hDlg,IDC_YSIZE,(LPTSTR)buff,MAX_PATH);
	m_YSize = (float)atof(buff);

	GetDlgItemText(hDlg,IDC_XSIZEBOT,(LPTSTR)buff,MAX_PATH);
	m_XSizeBot = (float)atof(buff);

	GetDlgItemText(hDlg,IDC_XSIZETOP,(LPTSTR)buff,MAX_PATH);
	m_XSizeTop = (float)atof(buff);

	GetDlgItemText(hDlg,IDC_ZSIZEBOT,(LPTSTR)buff,MAX_PATH);
	m_ZSizeBot = (float)atof(buff);

	GetDlgItemText(hDlg,IDC_ZSIZETOP,(LPTSTR)buff,MAX_PATH);
	m_ZSizeTop = (float)atof(buff);

	GetDlgItemText(hDlg,IDC_THICKNESS,(LPTSTR)buff,MAX_PATH);
	m_Thickness = (float)atof(buff);


	GetDlgItemText(hDlg,IDC_EDITNAME,(LPTSTR)buff,MAX_PATH);
	strcpy(App->CL_CreateBoxDialog->BoxName,buff);

}

// *************************************************************************
// *		 Set_BoxTemplate:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateBoxDialog::Set_BoxTemplate() 
{
	pBoxTemplate->YSize = m_YSize;
	pBoxTemplate->Solid = m_Solid;
	pBoxTemplate->XSizeBot = m_XSizeBot;
	pBoxTemplate->XSizeTop = m_XSizeTop;
	pBoxTemplate->ZSizeBot = m_ZSizeBot;
	pBoxTemplate->ZSizeTop = m_ZSizeTop;
	pBoxTemplate->TCut = m_TCut;
	pBoxTemplate->Thickness = m_Thickness;
	pBoxTemplate->TSheet = m_TSheet;
}

// *************************************************************************
// *	    	Set_Defaults:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateBoxDialog::Set_Defaults(HWND hDlg) 
{
	m_YSize = 128.0f;
	m_Solid = 0;
	m_XSizeBot = 128.0f;
	m_XSizeTop = 128.0f;
	m_ZSizeBot = 128.0f;
	m_ZSizeTop = 128.0f;
	m_TCut = false;
	m_Thickness = 16.0f;
	m_TSheet = false;

	Set_DLG_Members(hDlg);

	App->CL_CreateBoxDialog->Zero_Dlg_Flags(hDlg);
	App->CL_CreateBoxDialog->m_Solid = 0;
	App->CL_CreateBoxDialog->Solid_Flag = 1;

	App->CL_CreateBoxDialog->m_TCut = 0;
	App->CL_CreateBoxDialog->Cut_Flag = 0;

	RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *	    		Set_Room:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateBoxDialog::Set_Room(HWND hDlg)
{
	m_YSize = 360.0f;
	m_Solid = 1;
	m_XSizeBot = 680.0f;
	m_XSizeTop = 680.0f;
	m_ZSizeBot = 560.0f;
	m_ZSizeTop = 560.0f;
	m_TCut = false;
	m_Thickness = 16.0f;
	m_TSheet = false;

	Set_DLG_Members(hDlg);

	App->CL_CreateBoxDialog->Zero_Dlg_Flags(hDlg);
	App->CL_CreateBoxDialog->m_Solid = 1;
	App->CL_CreateBoxDialog->Solid_Flag = 0;
	App->CL_CreateBoxDialog->Hollow_Flag = 1;

	App->CL_CreateBoxDialog->m_TCut = 0;
	App->CL_CreateBoxDialog->Cut_Flag = 0;

	RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *	CreateDefault_TemplateCube:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateBoxDialog::CreateDefault_TemplateCube()
{
	App->Get_Current_Document();

	pBoxTemplate = Level_GetBoxTemplate(App->m_pDoc->pLevel);

	//Set_Members();

	//Set_BoxTemplate();

	Brush* pCube;
	pCube = BrushTemplate_CreateBox(pBoxTemplate);
	if (pCube != NULL)
	{
		App->m_pDoc->LastTemplateTypeName = BoxName;
		CreateNewTemplateBrush(pCube);

		App->CL_TabsControl->Enable_Tabs_Dlg(true);
		App->CL_TabsTemplates_Dlg->Enable_Insert_Button(true);

		Debug
	}
	else
	{
		App->Say("No pCube");
	}
}

// *************************************************************************
// *			Zero_Dlg_Flags:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateBoxDialog::Zero_Dlg_Flags(HWND hDlg)
{

	Solid_Flag = 0;
	Hollow_Flag = 0;

	RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}
