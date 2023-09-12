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
#include "A_CreateConeDialog.h"

A_CreateConeDialog::A_CreateConeDialog(void)
{
	m_Style = 0;
	m_Width = 200;
	m_Height = 300;
	m_VerticalStrips = 4;
	m_Thickness = 16;
	m_TCut = false;

	m_UseCamPos = 0;

	strcpy(ConeName,"Cone");
}

A_CreateConeDialog::~A_CreateConeDialog(void)
{
}

// *************************************************************************
// *	  	Start_CreateCone_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateConeDialog::Start_CreateCone_Dlg()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();
	pConeTemplate = Level_GetConeTemplate (App->CLSB_Doc->pLevel);

	App->CL_TabsControl->Enable_Tabs_Dlg(false);
	DialogBox(App->hInst, (LPCTSTR)IDD_CREATE_CONE, App->MainHwnd, (DLGPROC)CreateCone_Proc);
}

// *************************************************************************
// *        CreateBox_Proc:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
LRESULT CALLBACK A_CreateConeDialog::CreateCone_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		App->CL_CreateConeDialog->Set_Members();

		App->CL_CreateConeDialog->Set_DLG_Members(hDlg);

		SetDlgItemText(hDlg, IDC_EDITNAME, (LPCTSTR)"Cone");


		// ----------- Style Solid Hollow Funnel
		if(App->CL_CreateConeDialog->m_Style == 0)
		{
			HWND temp = GetDlgItem(hDlg, IDC_SOLID);
			SendMessage(temp, BM_SETCHECK, 1, 0);
		}

		if(App->CL_CreateConeDialog->m_Style == 1)
		{
			HWND temp = GetDlgItem(hDlg, IDC_HOLLOW);
			SendMessage(temp, BM_SETCHECK, 1, 0);
		}

		if(App->CL_CreateConeDialog->m_Style == 2)
		{
			HWND temp = GetDlgItem(hDlg, IDC_FUNNEL);
			SendMessage(temp, BM_SETCHECK, 1, 0);
		}
		// ----------------------------------------------


		HWND temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
		SendMessage(temp,BM_SETCHECK,1,0);
		App->CL_CreateConeDialog->m_UseCamPos = 0;

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STGENERAL) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STDIAMETER) == (HWND)lParam)
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

		if (GetDlgItem(hDlg, IDC_STVERTSTRIPS) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STWALLSIZE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STSTYLE) == (HWND)lParam)
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

		if (GetDlgItem(hDlg, IDC_TCUT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_FUNNEL) == (HWND)lParam)
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

	case WM_COMMAND:
		{

			if (LOWORD(wParam) == IDC_CKWORLDCENTRE)
			{
				HWND temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
				SendMessage(temp,BM_SETCHECK,1,0);

				temp = GetDlgItem(hDlg, IDC_CKCAMPOSITION);
				SendMessage(temp,BM_SETCHECK,0,0);

				App->CL_CreateConeDialog->m_UseCamPos = 0;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_CKCAMPOSITION)
			{
				HWND temp = GetDlgItem(hDlg, IDC_CKCAMPOSITION);
				SendMessage(temp,BM_SETCHECK,1,0);

				temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
				SendMessage(temp,BM_SETCHECK,0,0);

				App->CL_CreateConeDialog->m_UseCamPos = 1;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_HOLLOW)
			{
				App->CL_CreateConeDialog->m_Style = 1;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_SOLID)
			{
				App->CL_CreateConeDialog->m_Style = 0;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_FUNNEL)
			{
				App->CL_CreateConeDialog->m_Style = 2;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_TCUT)
			{
				HWND temp = GetDlgItem(hDlg, IDC_TCUT);

				int test = SendMessage(temp, BM_GETCHECK, 0, 0);
				if (test == BST_CHECKED)
				{
					App->CL_CreateConeDialog->m_TCut = 1;
					return 1;
				}
				else
				{
					App->CL_CreateConeDialog->m_TCut = 0;
					return 1;
				}

				return TRUE;
			}

			if (LOWORD(wParam) == ID_DEFAULT)
			{
				App->CL_CreateConeDialog->Set_Defaults(hDlg);
				return TRUE;
			}

			// -----------------------------------------------------------------
			if (LOWORD(wParam) == IDOK)
			{
				App->CL_CreateConeDialog->Get_DLG_Members(hDlg);
				App->CL_CreateConeDialog->Set_ConeTemplate(); 
				App->CL_CreateConeDialog->CreateCone();

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
// *		   CreateCone:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_CreateConeDialog::CreateCone() 
{
	m_pDoc->OnToolsTemplate();

	Brush *pCone;

	pCone = BrushTemplate_CreateCone (pConeTemplate);
	if (pCone != NULL)
	{
		m_pDoc->LastTemplateTypeName = ConeName;
		CreateNewTemplateBrush (pCone);
	}
	else
	{
		App->Say("No Cone");
	}
}

// *************************************************************************
// *       CreateNewTemplateBrush:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateConeDialog::CreateNewTemplateBrush(Brush *pBrush)
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

	pTemplatePos = Level_GetTemplatePos (App->CLSB_Doc->pLevel);

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

	Brush_Move (m_pDoc->CurBrush, &MoveVec);

	App->CLSB_Doc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
	m_pDoc->SetModifiedFlag ();
}

// *************************************************************************
// *		 Set_Members:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_CreateConeDialog::Set_Members() 
{
	m_Style = pConeTemplate->Style;
	m_Width = pConeTemplate->Width;
	m_Height = pConeTemplate->Height;
	m_VerticalStrips = pConeTemplate->VerticalStrips;
	m_Thickness = pConeTemplate->Thickness;
	m_TCut = pConeTemplate->TCut;
}

// *************************************************************************
// *		 Set_DLG_Members:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateConeDialog::Set_DLG_Members(HWND hDlg) 
{
	char buf[MAX_PATH];
	sprintf(buf, "%0.0f", m_Width);
	SetDlgItemText(hDlg, IDC_EDIT1, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_Height);
	SetDlgItemText(hDlg, IDC_EDIT10, (LPCTSTR)buf);

	sprintf(buf, "%0.0i", m_VerticalStrips);
	SetDlgItemText(hDlg, IDC_EDIT11, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_Thickness);
	SetDlgItemText(hDlg, IDC_EDIT12, (LPCTSTR)buf);


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
void A_CreateConeDialog::Get_DLG_Members(HWND hDlg) 
{
	char buf[MAX_PATH];

	GetDlgItemText(hDlg, IDC_EDIT1, (LPTSTR)buf,MAX_PATH);
	m_Width = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_EDIT10, (LPTSTR)buf,MAX_PATH);
	m_Height = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_EDIT11, (LPTSTR)buf,MAX_PATH);
	m_VerticalStrips = (float)atof(buf);
	
	GetDlgItemText(hDlg, IDC_EDIT12, (LPTSTR)buf,MAX_PATH);
	m_Thickness = (float)atof(buf);

	GetDlgItemText(hDlg,IDC_EDITNAME,(LPTSTR)buf,MAX_PATH);
	strcpy(ConeName,buf);
}

// *************************************************************************
// *		 Set_ConeTemplate:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateConeDialog::Set_ConeTemplate() 
{
	pConeTemplate->Style = m_Style;
	pConeTemplate->Width = m_Width;
	pConeTemplate->Height = m_Height;
	pConeTemplate->VerticalStrips = m_VerticalStrips;
	pConeTemplate->Thickness = m_Thickness;
	pConeTemplate->TCut = m_TCut;
}

// *************************************************************************
// *	    	Set_Defaults:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateConeDialog::Set_Defaults(HWND hDlg) 
{
	m_Style = 0;
	m_Width = 200;
	m_Height = 300;
	m_VerticalStrips = 4;
	m_Thickness = 16;
	m_TCut = false;

	Set_DLG_Members(hDlg);

	/*if(m_Solid == 0)
	{
		HWND temp = GetDlgItem(hDlg,IDC_SOLID);
		SendMessage(temp,BM_SETCHECK,1,0);

		temp = GetDlgItem(hDlg,IDC_HOLLOW);
		SendMessage(temp,BM_SETCHECK,0,0);
	}
	else
	{
		HWND temp = GetDlgItem(hDlg,IDC_HOLLOW);
		SendMessage(temp,BM_SETCHECK,1,0);

		temp = GetDlgItem(hDlg,IDC_SOLID);
		SendMessage(temp,BM_SETCHECK,0,0);
	}*/
}
