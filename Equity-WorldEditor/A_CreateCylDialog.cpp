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
#include "A_CreateCylDialog.h"

A_CreateCylDialog::A_CreateCylDialog(void)
{

	m_BotXOffset = 0.0;
	m_BotXSize = 128.0;
	m_BotZOffset = 0.0;
	m_BotZSize = 128.0;
	m_Solid = 0;
	m_TopXOffset = 0.0;
	m_TopXSize = 128.0;
	m_TopZOffset = 0.0;
	m_TopZSize = 128.0;
	m_YSize = 512.0;
	m_RingLength = 0.0;
	m_TCut = FALSE;
	m_VerticalStripes = 0;
	m_Thickness = 0.0f;

	strcpy(CylinderName,"Cylinder Test");

}

A_CreateCylDialog::~A_CreateCylDialog(void)
{
}

// *************************************************************************
// *	  	Start_CreateCyl_Dlg:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateCylDialog::Start_CreateCyl_Dlg()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	pCylinderTemplate = Level_GetCylinderTemplate (m_pDoc->pLevel);

	DialogBox(App->hInst, (LPCTSTR)IDD_CREATE_CYL, App->MainHwnd, (DLGPROC)CreateCyl_Proc);
}

// *************************************************************************
// *        CreateBox_Proc:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
LRESULT CALLBACK A_CreateCylDialog::CreateCyl_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		//SendDlgItemMessage(hDlg, IDC_BTSETVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		App->CL_CreateCylDialog->Set_Members();

		App->CL_CreateCylDialog->Set_DLG_Members(hDlg);

		SetDlgItemText(hDlg, IDC_EDITNAME, (LPCTSTR)"Cylinder_Test");

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

		if (GetDlgItem(hDlg, IDC_SOLID) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_HOLLOW) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_RING) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

	
		if (GetDlgItem(hDlg, IDC_STTOPXSIZE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STTOPZSIZE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STTOPXOFFSET) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STTOPZOFFSET) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

	
		if (GetDlgItem(hDlg, IDC_STWALLTHICKNESS) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STRINGLENGTH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STSTRIPES) == (HWND)lParam)
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

		if (GetDlgItem(hDlg, IDC_STBOTXSIZE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STBOTZSIZE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STBOTXOFFSET) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STBOTZOFFSET) == (HWND)lParam)
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

		/*if (some_item->idFrom == IDC_BTSETVIEW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item,App->CL_Dialogs->F_Textured);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		{

			/*if (LOWORD(wParam) == IDC_HOLLOW)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);
				SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HollowBox_Bmp);
				App->CL_CreateBoxDialog->m_Solid = 1;

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_SOLID)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);
				SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_SolidBox_Bmp);

				App->CL_CreateBoxDialog->m_Solid = 0;

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
			}*/

			//if (LOWORD(wParam) == IDC_TSHEET)
			//{
			//	/*HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);
			//	SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_SolidBox_Bmp);*/

			//	return TRUE;
			//}

			//if (LOWORD(wParam) == IDC_Defaults)
			//{
			//	/*HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);
			//	SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_SolidBox_Bmp);*/

			//	return TRUE;
			//}

			// -----------------------------------------------------------------
			if (LOWORD(wParam) == IDOK)
			{
				char buff[MAX_PATH];
				GetDlgItemText(hDlg,IDC_EDITNAME,(LPTSTR)buff,MAX_PATH);
				strcpy(App->CL_CreateCylDialog->CylinderName,buff);

				App->CL_CreateCylDialog->Get_DLG_Members(hDlg);

				App->CL_CreateCylDialog->Set_CylinderTemplate(); 

				App->CL_CreateCylDialog->CreateCylinder();

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
	}
	return FALSE;
}

// *************************************************************************
// *		   CreateCylinder:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateCylDialog::CreateCylinder() 
{
	m_pDoc->OnToolsTemplate();

	Brush *pCylinder;

	pCylinder = BrushTemplate_CreateCylinder (pCylinderTemplate);
	if (pCylinder != NULL)
	{
		m_pDoc->LastTemplateTypeName =CylinderName;
		CreateNewTemplateBrush(pCylinder);
	}
	else
	{
		App->Say("No pCube");
	}
}

// *************************************************************************
// *       CreateNewTemplateBrush:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateCylDialog::CreateNewTemplateBrush(Brush *pBrush)
{
	geVec3d *pTemplatePos;
	geVec3d MoveVec;
	geVec3d BrushPos;

	assert (pBrush != NULL);

	if (m_pDoc->BTemplate != NULL)
	{
		Brush_Destroy (&m_pDoc->BTemplate);
	}

	m_pDoc->CurBrush = pBrush;

	m_pDoc->TempEnt	= FALSE;
	m_pDoc->SetDefaultBrushTexInfo (m_pDoc->CurBrush);
	Brush_Bound (m_pDoc->CurBrush);
	Brush_Center (m_pDoc->CurBrush, &BrushPos);

	pTemplatePos = Level_GetTemplatePos (m_pDoc->pLevel);

	//pTemplatePos->X = pTemplatePos->X +500;
	

	geVec3d_Subtract (pTemplatePos, &BrushPos, &MoveVec);

	Brush_Move (m_pDoc->CurBrush, &MoveVec);

	m_pDoc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
	m_pDoc->SetModifiedFlag ();
}

// *************************************************************************
// *		 Set_Members:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_CreateCylDialog::Set_Members() 
{
	m_BotXOffset = pCylinderTemplate->BotXOffset;
	m_BotXSize = pCylinderTemplate->BotXSize;
	m_BotZOffset = pCylinderTemplate->BotZOffset;
	m_BotZSize = pCylinderTemplate->BotZSize;
	m_Solid = pCylinderTemplate->Solid;
	m_TopXOffset = pCylinderTemplate->TopXOffset;
	m_TopXSize = pCylinderTemplate->TopXSize;
	m_TopZOffset = pCylinderTemplate->TopZOffset;
	m_TopZSize = pCylinderTemplate->TopZSize;
	m_YSize = pCylinderTemplate->YSize;
	m_RingLength = pCylinderTemplate->RingLength;
	m_TCut = pCylinderTemplate->TCut;
	m_VerticalStripes = pCylinderTemplate->VerticalStripes;
	m_Thickness = pCylinderTemplate->Thickness;
}

// *************************************************************************
// *		 Set_DLG_Members:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateCylDialog::Set_DLG_Members(HWND hDlg) 
{
	char buf[MAX_PATH];
	sprintf(buf, "%0.0f", m_TopXSize);
	SetDlgItemText(hDlg, IDC_TOPXSIZE, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_TopZSize);
	SetDlgItemText(hDlg, IDC_TOPZSIZE, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_TopXOffset);
	SetDlgItemText(hDlg, IDC_TOPXOFF, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_TopZOffset);
	SetDlgItemText(hDlg, IDC_TOPZOFF, (LPCTSTR)buf);


	sprintf(buf, "%0.0f", m_BotXSize);
	SetDlgItemText(hDlg, IDC_BOTXSIZE, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_BotZSize);
	SetDlgItemText(hDlg, IDC_BOTZSIZE, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_BotXOffset);
	SetDlgItemText(hDlg, IDC_BOTXOFF, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_BotZOffset);
	SetDlgItemText(hDlg, IDC_BOTZOFF, (LPCTSTR)buf);


	sprintf(buf, "%0.0f", m_YSize);
	SetDlgItemText(hDlg, IDC_YSIZE, (LPCTSTR)buf);

	sprintf(buf, "%i", m_VerticalStripes);
	SetDlgItemText(hDlg, IDC_VERTSTRIPES, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_Thickness);
	SetDlgItemText(hDlg, IDC_THICKNESS, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_RingLength);
	SetDlgItemText(hDlg, IDC_RINGLENGTH, (LPCTSTR)buf);


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
void A_CreateCylDialog::Get_DLG_Members(HWND hDlg) 
{
	char buf[MAX_PATH];

	GetDlgItemText(hDlg, IDC_TOPXSIZE, (LPTSTR)buf,MAX_PATH);
	m_TopXSize = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_TOPZSIZE, (LPTSTR)buf,MAX_PATH);
	m_TopZSize = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_TOPXOFF, (LPTSTR)buf,MAX_PATH);
	m_TopXOffset = (float)atof(buf);
	
	GetDlgItemText(hDlg, IDC_TOPZOFF, (LPTSTR)buf,MAX_PATH);
	m_TopZOffset = (float)atof(buf);


	GetDlgItemText(hDlg, IDC_BOTXSIZE, (LPTSTR)buf,MAX_PATH);
	m_BotXSize = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_BOTZSIZE, (LPTSTR)buf,MAX_PATH);
	m_BotZSize = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_BOTXOFF, (LPTSTR)buf,MAX_PATH);
	m_BotXOffset = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_BOTZOFF, (LPTSTR)buf,MAX_PATH);
	m_BotZOffset = (float)atof(buf);


	GetDlgItemText(hDlg, IDC_YSIZE, (LPTSTR)buf,MAX_PATH);
	m_YSize = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_VERTSTRIPES, (LPTSTR)buf,MAX_PATH);
	m_VerticalStripes = (int)atoi(buf);

	GetDlgItemText(hDlg, IDC_THICKNESS, (LPTSTR)buf,MAX_PATH);
	m_Thickness = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_RINGLENGTH, (LPTSTR)buf,MAX_PATH);
	m_RingLength = (float)atof(buf);
}

// *************************************************************************
// *		 Set_CylinderTemplate:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateCylDialog::Set_CylinderTemplate() 
{
	pCylinderTemplate->BotXOffset = m_BotXOffset;
	pCylinderTemplate->BotXSize = m_BotXSize;
	pCylinderTemplate->BotZOffset = m_BotZOffset;
	pCylinderTemplate->BotZSize = m_BotZSize;
	pCylinderTemplate->Solid = m_Solid;
	pCylinderTemplate->TopXOffset = m_TopXOffset;
	pCylinderTemplate->TopXSize = m_TopXSize;
	pCylinderTemplate->TopZOffset = m_TopZOffset;
	pCylinderTemplate->TopZSize = m_TopZSize;
	pCylinderTemplate->YSize = m_YSize;
	pCylinderTemplate->RingLength = m_RingLength;
	pCylinderTemplate->TCut = m_TCut;
	pCylinderTemplate->VerticalStripes = m_VerticalStripes;
	pCylinderTemplate->Thickness = m_Thickness;
}
