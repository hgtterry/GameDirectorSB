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
	m_TCut = false;
	m_VerticalStripes = 0;
	m_Thickness = 0.0f;

	m_UseCamPos = 0;

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

	pCylinderTemplate = Level_GetCylinderTemplate (App->CLSB_Doc->pLevel);

	App->CL_TabsControl->Enable_Tabs_Dlg(false);
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

		SetDlgItemText(hDlg, IDC_EDITNAME, (LPCTSTR)"Cylinder");

		// ----------- Style Solid Hollow Funnel
		if(App->CL_CreateCylDialog->m_Solid == 0)
		{
			HWND temp = GetDlgItem(hDlg, IDC_SOLID);
			SendMessage(temp, BM_SETCHECK, 1, 0);
		}

		if(App->CL_CreateCylDialog->m_Solid == 1)
		{
			HWND temp = GetDlgItem(hDlg, IDC_HOLLOW);
			SendMessage(temp, BM_SETCHECK, 1, 0);
		}

		if(App->CL_CreateCylDialog->m_Solid == 2)
		{
			HWND temp = GetDlgItem(hDlg, IDC_RING);
			SendMessage(temp, BM_SETCHECK, 1, 0);
		}
		// ----------------------------------------------

		HWND temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
		SendMessage(temp,BM_SETCHECK,1,0);
		App->CL_CreateCylDialog->m_UseCamPos = 0;

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

				App->CL_CreateCylDialog->m_UseCamPos = 0;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_CKCAMPOSITION)
			{
				HWND temp = GetDlgItem(hDlg, IDC_CKCAMPOSITION);
				SendMessage(temp,BM_SETCHECK,1,0);

				temp = GetDlgItem(hDlg, IDC_CKWORLDCENTRE);
				SendMessage(temp,BM_SETCHECK,0,0);

				App->CL_CreateCylDialog->m_UseCamPos = 1;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_HOLLOW)
			{
				App->CL_CreateCylDialog->m_Solid = 1;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_SOLID)
			{
				App->CL_CreateCylDialog->m_Solid = 0;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_RING)
			{
				App->CL_CreateCylDialog->m_Solid = 2;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_TCUT)
			{
				HWND temp = GetDlgItem(hDlg, IDC_TCUT);

				int test = SendMessage(temp, BM_GETCHECK, 0, 0);
				if (test == BST_CHECKED)
				{
					App->CL_CreateCylDialog->m_TCut = 1;
					return 1;
				}
				else
				{
					App->CL_CreateCylDialog->m_TCut = 0;
					return 1;
				}

				return TRUE;
			}

			if (LOWORD(wParam) == IDC_Defaults)
			{
				App->CL_CreateCylDialog->Set_Defaults(hDlg);
				return TRUE;
			}

			// -----------------------------------------------------------------
			if (LOWORD(wParam) == IDOK)
			{
				App->CL_CreateCylDialog->Get_DLG_Members(hDlg);
				App->CL_CreateCylDialog->Set_CylinderTemplate(); 
				App->CL_CreateCylDialog->CreateCylinder();

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
// *		   CreateCylinder:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateCylDialog::CreateCylinder() 
{
	m_pDoc->OnToolsTemplate();

	Brush *pCylinder;

	pCylinder = BrushTemplate_CreateCylinder (pCylinderTemplate);
	if (pCylinder != NULL)
	{
		m_pDoc->LastTemplateTypeName = CylinderName;
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

	GetDlgItemText(hDlg,IDC_EDITNAME,(LPTSTR)buf,MAX_PATH);
	strcpy(CylinderName,buf);
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


// *************************************************************************
// *	    	Set_Defaults:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void A_CreateCylDialog::Set_Defaults(HWND hDlg) 
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
	m_TCut = false;
	m_VerticalStripes = 6;
	m_Thickness = 16.0f;

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
