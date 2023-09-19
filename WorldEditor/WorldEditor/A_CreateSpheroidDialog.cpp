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
#include "A_CreateSpheroidDialog.h"

A_CreateSpheroidDialog::A_CreateSpheroidDialog(void)
{
	m_HorizontalBands	=4;
	m_VerticalBands		=8;
	m_YSize				=256.0;
	m_Solid				=0;
	m_Thickness			=10;

	m_UseCamPos = 0;

	strcpy(SpheroidName,"Spheroid");

}

A_CreateSpheroidDialog::~A_CreateSpheroidDialog(void)
{
}

// *************************************************************************
// *	  	Start_CreateArch_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateSpheroidDialog::Start_CreateSpheroid_Dlg()
{
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

	pSpheroidTemplate = Level_GetSpheroidTemplate (App->CLSB_Doc->pLevel);

	App->CL_TabsControl->Enable_Tabs_Dlg(false);
	DialogBox(App->hInst, (LPCTSTR)IDD_CREATE_SPHEROID, App->MainHwnd, (DLGPROC)CreateSpheroid_Proc);
}

// *************************************************************************
// *        CreateBox_Proc:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
LRESULT CALLBACK A_CreateSpheroidDialog::CreateSpheroid_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		//SendDlgItemMessage(hDlg, IDC_BTSETVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		App->CL_CreateSpheroidDialog->Set_Members();

		App->CL_CreateSpheroidDialog->Set_DLG_Members(hDlg);

		SetDlgItemText(hDlg, IDC_EDITNAME, (LPCTSTR)"Spheroid");

		
		HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);

		if(App->CL_CreateSpheroidDialog->m_Solid == 0)
		{
			SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_SolidSpheroid_Bmp);
			HWND temp = GetDlgItem(hDlg,IDC_SOLID);
			SendMessage(temp,BM_SETCHECK,1,0);
		}
		else
		{
			SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HollowSpheroid_Bmp);
			HWND temp = GetDlgItem(hDlg,IDC_HOLLOW);
			SendMessage(temp,BM_SETCHECK,1,0);
		}


		HWND temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
		SendMessage(temp,BM_SETCHECK,1,0);
		App->CL_CreateSpheroidDialog->m_UseCamPos = 0;

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

		if (GetDlgItem(hDlg, IDC_STRADIUS) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STVERTICLESTIPES) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STHORISTIPS) == (HWND)lParam)
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

				App->CL_CreateSpheroidDialog->m_UseCamPos = 0;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_CKCAMPOSITION)
			{
				HWND temp = GetDlgItem(hDlg, IDC_CKCAMPOSITION);
				SendMessage(temp,BM_SETCHECK,1,0);

				temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
				SendMessage(temp,BM_SETCHECK,0,0);

				App->CL_CreateSpheroidDialog->m_UseCamPos = 1;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_HOLLOW)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);
				SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HollowSpheroid_Bmp);
				App->CL_CreateSpheroidDialog->m_Solid = 1;

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_SOLID)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);
				SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_SolidSpheroid_Bmp);

				App->CL_CreateSpheroidDialog->m_Solid = 0;

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_TCUT)
			{
				HWND temp = GetDlgItem(hDlg, IDC_TCUT);

				int test = SendMessage(temp, BM_GETCHECK, 0, 0);
				if (test == BST_CHECKED)
				{
					App->CL_CreateSpheroidDialog->m_TCut = 1;
					return 1;
				}
				else
				{
					App->CL_CreateSpheroidDialog->m_TCut = 0;
					return 1;
				}

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_Defaults)
			{

				App->CL_CreateSpheroidDialog->Set_Defaults(hDlg);
				return TRUE;
			}

			// -----------------------------------------------------------------
			if (LOWORD(wParam) == IDOK)
			{
				App->CL_CreateSpheroidDialog->Get_DLG_Members(hDlg);

				App->CL_CreateSpheroidDialog->Set_SpheroidTemplate(); 

				App->CL_CreateSpheroidDialog->CreateSpheroid();

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
// *		   CreateSpheroid:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateSpheroidDialog::CreateSpheroid() 
{
	m_pDoc->OnToolsTemplate();

	Brush *pSpheroid;

	pSpheroid = BrushTemplate_CreateSpheroid (pSpheroidTemplate);
	if (pSpheroid != NULL)
	{
		m_pDoc->LastTemplateTypeName = SpheroidName;
		CreateNewTemplateBrush (pSpheroid);
	}
	else
	{
		App->Say("No Spheroid");
	}
}

// *************************************************************************
// *       CreateNewTemplateBrush:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateSpheroidDialog::CreateNewTemplateBrush(Brush *pBrush)
{
	geVec3d *pTemplatePos;
	geVec3d MoveVec;
	geVec3d BrushPos;

	assert (pBrush != NULL);

	if (App->CLSB_Doc->BTemplate != NULL)
	{
		Brush_Destroy (&App->CLSB_Doc->BTemplate);
	}

	App->CLSB_Doc->CurBrush = pBrush;

	App->CLSB_Doc->TempEnt	= FALSE;
	m_pDoc->SetDefaultBrushTexInfo (App->CLSB_Doc->CurBrush);
	Brush_Bound (App->CLSB_Doc->CurBrush);
	Brush_Center (App->CLSB_Doc->CurBrush, &BrushPos);

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

	Brush_Move (App->CLSB_Doc->CurBrush, &MoveVec);

	App->CLSB_Doc->UpdateAllViews (UAV_ALL3DVIEWS, NULL);
	m_pDoc->SetModifiedFlag ();
}

// *************************************************************************
// *		 Set_Members:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void A_CreateSpheroidDialog::Set_Members() 
{
	m_HorizontalBands	= pSpheroidTemplate->HorizontalBands;
	m_VerticalBands		= pSpheroidTemplate->VerticalBands;
	m_YSize				= pSpheroidTemplate->YSize;
	m_Solid				= pSpheroidTemplate->Solid;
	m_Thickness			= pSpheroidTemplate->Thickness;
}

// *************************************************************************
// *		 Set_DLG_Members:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateSpheroidDialog::Set_DLG_Members(HWND hDlg) 
{
	char buf[MAX_PATH];
	sprintf(buf, "%0.0f", m_YSize);
	SetDlgItemText(hDlg, IDC_YSIZE, (LPCTSTR)buf);

	sprintf(buf, "%i", m_VerticalBands);
	SetDlgItemText(hDlg, IDC_VERTSTRIPES, (LPCTSTR)buf);

	sprintf(buf, "%i", m_HorizontalBands);
	SetDlgItemText(hDlg, IDC_HORSTRIPES, (LPCTSTR)buf);

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
void A_CreateSpheroidDialog::Get_DLG_Members(HWND hDlg) 
{
	char buf[MAX_PATH];

	GetDlgItemText(hDlg, IDC_YSIZE, (LPTSTR)buf,MAX_PATH);
	m_YSize = (float)atof(buf);

	GetDlgItemText(hDlg, IDC_VERTSTRIPES, (LPTSTR)buf,MAX_PATH);
	m_VerticalBands = (int)atoi(buf);

	GetDlgItemText(hDlg, IDC_HORSTRIPES, (LPTSTR)buf,MAX_PATH);
	m_HorizontalBands = (int)atoi(buf);
	
	GetDlgItemText(hDlg, IDC_THICKNESS, (LPTSTR)buf,MAX_PATH);
	m_Thickness = (float)atof(buf);

	GetDlgItemText(hDlg,IDC_EDITNAME,(LPTSTR)buf,MAX_PATH);
	strcpy(SpheroidName,buf);
}

// *************************************************************************
// *		 Set_SpheroidTemplate:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void A_CreateSpheroidDialog::Set_SpheroidTemplate() 
{
	pSpheroidTemplate->HorizontalBands = m_HorizontalBands;
	pSpheroidTemplate->VerticalBands = m_VerticalBands;
	pSpheroidTemplate->YSize = m_YSize;
	pSpheroidTemplate->Thickness = m_Thickness;
	pSpheroidTemplate->TCut = m_TCut;
	pSpheroidTemplate->Solid = m_Solid;
}

// *************************************************************************
// *	    	Set_Defaults:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateSpheroidDialog::Set_Defaults(HWND hDlg) 
{
	m_HorizontalBands	= 4;
	m_VerticalBands		= 8;
	m_YSize				= 256.0;
	m_Solid				= 0;
	m_Thickness			= 10;

	Set_DLG_Members(hDlg);

	HWND Temp = GetDlgItem(hDlg, IDC_PICTURE);

	if(m_Solid == 0)
	{
		SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_SolidSpheroid_Bmp);
		HWND temp = GetDlgItem(hDlg,IDC_SOLID);
		SendMessage(temp,BM_SETCHECK,1,0);

		temp = GetDlgItem(hDlg,IDC_HOLLOW);
		SendMessage(temp,BM_SETCHECK,0,0);
	}
	else
	{
		SendMessage(Temp, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HollowSpheroid_Bmp);
		HWND temp = GetDlgItem(hDlg,IDC_HOLLOW);
		SendMessage(temp,BM_SETCHECK,1,0);

		temp = GetDlgItem(hDlg,IDC_SOLID);
		SendMessage(temp,BM_SETCHECK,0,0);
	}
}
