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
#include "A_CreateStaircaseDialog.h"

A_CreateStaircaseDialog::A_CreateStaircaseDialog(void)
{
	m_Height = 128.0;
	m_Length = 128.0;
	m_Width = 64.0;
	m_MakeRamp = false;
	m_TCut = false;
	m_NumberOfStairs = 0;

	strcpy(StaircaseName,"Spheroid");
}

A_CreateStaircaseDialog::~A_CreateStaircaseDialog(void)
{
}

// *************************************************************************
// *	  	Start_CreateArch_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateStaircaseDialog::Start_CreateStaircase_Dlg()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	pStaircaseTemplate = Level_GetStaircaseTemplate (App->CLSB_Doc->pLevel);

	App->CL_TabsControl->Enable_Tabs_Dlg(false);
	DialogBox(App->hInst, (LPCTSTR)IDD_STAIRCASEDIALOG, App->MainHwnd, (DLGPROC)CreateStaircase_Proc);
}

// *************************************************************************
// *        CreateBox_Proc:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
LRESULT CALLBACK A_CreateStaircaseDialog::CreateStaircase_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		
		App->CL_CreateStaircaseDialog->Set_Members();

		App->CL_CreateStaircaseDialog->Set_DLG_Members(hDlg);

		SetDlgItemText(hDlg, IDC_EDITNAME, (LPCTSTR)"Staircase");


		
		HWND temp = GetDlgItem(hDlg, IDC_CHECK1);

		if (App->CL_CreateStaircaseDialog->m_MakeRamp == 1)
		{
			SendMessage(temp, BM_SETCHECK, 1, 0);
			return 1;
		}
		else
		{
			SendMessage(temp, BM_SETCHECK, 0, 0);
			return 1;
		}


		temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
		SendMessage(temp,BM_SETCHECK,1,0);
		App->CL_CreateStaircaseDialog->m_UseCamPos = 0;

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

		if (GetDlgItem(hDlg, IDC_STHEIGHT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STWIDTH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STLENGTH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STSTEPS) == (HWND)lParam)
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

		if (GetDlgItem(hDlg, IDC_CHECK1) == (HWND)lParam)
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

				App->CL_CreateStaircaseDialog->m_UseCamPos = 0;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_CKCAMPOSITION)
			{
				HWND temp = GetDlgItem(hDlg, IDC_CKCAMPOSITION);
				SendMessage(temp,BM_SETCHECK,1,0);

				temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
				SendMessage(temp,BM_SETCHECK,0,0);

				App->CL_CreateStaircaseDialog->m_UseCamPos = 1;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_TCUT)
			{
				HWND temp = GetDlgItem(hDlg, IDC_TCUT);

				int test = SendMessage(temp, BM_GETCHECK, 0, 0);
				if (test == BST_CHECKED)
				{
					App->CL_CreateStaircaseDialog->m_TCut = 1;
					return 1;
				}
				else
				{
					App->CL_CreateStaircaseDialog->m_TCut = 0;
					return 1;
				}

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_CHECK1)
			{
				HWND temp = GetDlgItem(hDlg, IDC_CHECK1);

				int test = SendMessage(temp, BM_GETCHECK, 0, 0);
				if (test == BST_CHECKED)
				{
					App->CL_CreateStaircaseDialog->m_MakeRamp = 1;
					return 1;
				}
				else
				{
					App->CL_CreateStaircaseDialog->m_MakeRamp = 0;
					return 1;
				}
	
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_Defaults)
			{
				App->CL_CreateStaircaseDialog->Set_Defaults(hDlg);
				return TRUE;
			}

			// -----------------------------------------------------------------
			if (LOWORD(wParam) == IDOK)
			{
				App->CL_CreateStaircaseDialog->Get_DLG_Members(hDlg);

				App->CL_CreateStaircaseDialog->Set_StaircaseTemplate(); 

				App->CL_CreateStaircaseDialog->CreateStaircase();

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
// *		   CreateStaircase:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateStaircaseDialog::CreateStaircase() 
{
	m_pDoc->OnToolsTemplate();

	Brush *pStaircase;

	pStaircase = BrushTemplate_CreateStaircase (pStaircaseTemplate);
	if (pStaircase != NULL)
	{
		m_pDoc->LastTemplateTypeName = StaircaseName;
		CreateNewTemplateBrush (pStaircase);
	}
	else
	{
		App->Say("No Staircase");
	}
}

// *************************************************************************
// *       CreateNewTemplateBrush:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateStaircaseDialog::CreateNewTemplateBrush(Brush *pBrush)
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
void A_CreateStaircaseDialog::Set_Members() 
{
	m_Height = pStaircaseTemplate->Height;
	m_Length = pStaircaseTemplate->Length;
	m_Width = pStaircaseTemplate->Width;
	m_MakeRamp = pStaircaseTemplate->MakeRamp;
	m_TCut = pStaircaseTemplate->TCut;
	m_NumberOfStairs = pStaircaseTemplate->NumberOfStairs;
}

// *************************************************************************
// *		 Set_DLG_Members:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateStaircaseDialog::Set_DLG_Members(HWND hDlg) 
{
	char buf[MAX_PATH];
	sprintf(buf, "%0.0f", m_Height);
	SetDlgItemText(hDlg, IDC_HEIGHT, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_Width);
	SetDlgItemText(hDlg, IDC_WIDTH, (LPCTSTR)buf);

	sprintf(buf, "%0.0f", m_Length);
	SetDlgItemText(hDlg, IDC_LENGTH, (LPCTSTR)buf);

	sprintf(buf, "%i", m_NumberOfStairs);
	SetDlgItemText(hDlg, IDC_NUMBEROFSTAIRS, (LPCTSTR)buf);


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
void A_CreateStaircaseDialog::Get_DLG_Members(HWND hDlg) 
{
	char buf[MAX_PATH];

	GetDlgItemText(hDlg, IDC_HEIGHT, (LPTSTR)buf,MAX_PATH);
	m_Height = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_WIDTH, (LPTSTR)buf,MAX_PATH);
	m_Width = (int)atoi(buf);

	GetDlgItemText(hDlg, IDC_LENGTH, (LPTSTR)buf,MAX_PATH);
	m_Length = (int)atoi(buf);
	
	GetDlgItemText(hDlg, IDC_NUMBEROFSTAIRS, (LPTSTR)buf,MAX_PATH);
	m_NumberOfStairs = (int)atoi(buf);

	GetDlgItemText(hDlg,IDC_EDITNAME,(LPTSTR)buf,MAX_PATH);
	strcpy(StaircaseName,buf);
}

// *************************************************************************
// *		 Set_StaircaseTemplate:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateStaircaseDialog::Set_StaircaseTemplate() 
{
	pStaircaseTemplate->Height = m_Height;
	pStaircaseTemplate->Length = m_Length;
	pStaircaseTemplate->MakeRamp= m_MakeRamp;
	pStaircaseTemplate->NumberOfStairs = m_NumberOfStairs;
	pStaircaseTemplate->TCut = m_TCut;
	pStaircaseTemplate->Width = m_Width;
}

// *************************************************************************
// *	    	Set_Defaults:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateStaircaseDialog::Set_Defaults(HWND hDlg) 
{
	m_Height = 128.0;
	m_Length = 128.0;
	m_Width = 64.0;
	m_MakeRamp = false;
	m_TCut = false;
	m_NumberOfStairs = 0;

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

