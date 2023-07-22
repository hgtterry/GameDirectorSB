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
#include "SB_Brushes.h"

SB_Brushes::SB_Brushes(void)
{
	Dimensions_Dlg_hWnd = nullptr;

	CenterOfSelection.X = 0;
	CenterOfSelection.Y = 0;
	CenterOfSelection.Z = 0;

	PosX_Delta = 1;
	PosY_Delta = 1;
	PosZ_Delta = 1;

	Dimensions_Dlg_Running = 0;
}

SB_Brushes::~SB_Brushes(void)
{
}

// *************************************************************************
// *	  	Start_Dimensions_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Brushes::Start_Dimensions_Dlg()
{
	if (Dimensions_Dlg_Running == 0)
	{
		m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

		Lock_Textures(true);

		SelBrushList_Center(m_pDoc->pSelBrushes, &m_pDoc->SelectedGeoCenter);

		CenterOfSelection = m_pDoc->SelectedGeoCenter;

		Dimensions_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_BRUSHDIMENSIONS, App->MainHwnd, (DLGPROC)Dimensions_Dlg_Proc);

		Dimensions_Dlg_Running = 1;
	}
}

// *************************************************************************
// *		  Dimensions_Dlg_Proc:- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
LRESULT CALLBACK SB_Brushes::Dimensions_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_STPOSITION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STROTITION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_STPOSX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPOSY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPOSZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STROTX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STROTY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STROTZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_POSX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_POSY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_POSZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_CBPOSXDELTA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CBPOSYDELTA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CBPOSZDELTA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		HWND CB_hWnd = GetDlgItem(hDlg, IDC_CBPOSXDELTA);
		App->CLSB_Brushes->Fill_ComboBox_PosDelta(CB_hWnd);

		CB_hWnd = GetDlgItem(hDlg, IDC_CBPOSYDELTA);
		App->CLSB_Brushes->Fill_ComboBox_PosDelta(CB_hWnd);

		CB_hWnd = GetDlgItem(hDlg, IDC_CBPOSZDELTA);
		App->CLSB_Brushes->Fill_ComboBox_PosDelta(CB_hWnd);

		char buf[255];
		sprintf(buf, "%f", App->CLSB_Brushes->CenterOfSelection.X);
		SetDlgItemText(hDlg, IDC_ED_BRUSH_POSX, buf);

		sprintf(buf, "%f", App->CLSB_Brushes->CenterOfSelection.Y);
		SetDlgItemText(hDlg, IDC_ED_BRUSH_POSY, buf);

		sprintf(buf, "%f", App->CLSB_Brushes->CenterOfSelection.Z);
		SetDlgItemText(hDlg, IDC_ED_BRUSH_POSZ, buf);

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		// Position
		if (GetDlgItem(hDlg, IDC_STPOSX) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STPOSY) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STPOSZ) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STPOSITION) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		// Rotation
		if (GetDlgItem(hDlg, IDC_STROTX) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STROTY) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STROTZ) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STROTATION) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		
		
		return FALSE;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

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

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_VSCROLL:
	{
		// -------- Pos X
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBPOSX))
		{
			switch ((int)LOWORD(wParam))
			{
			case SB_LINEUP:
			{
				App->CLSB_Brushes->CenterOfSelection.X += App->CLSB_Brushes->PosX_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;
			}

			case SB_LINEDOWN:
			{
				App->CLSB_Brushes->CenterOfSelection.X -= App->CLSB_Brushes->PosX_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;
			}
			}

			App->CLSB_Brushes->Update_Pos_Dlg();

			return 0;
		}

		// -------- Pos Y
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBPOSY))
		{
			switch ((int)LOWORD(wParam))
			{
			case SB_LINEUP:
				App->CLSB_Brushes->CenterOfSelection.Y += App->CLSB_Brushes->PosY_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;

			case SB_LINEDOWN:

				App->CLSB_Brushes->CenterOfSelection.Y -= App->CLSB_Brushes->PosY_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;
			}

			App->CLSB_Brushes->Update_Pos_Dlg();

			return 0;
		}

		// -------- Pos Z
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBPOSZ))
		{
			switch ((int)LOWORD(wParam))
			{
			case SB_LINEUP:
				App->CLSB_Brushes->CenterOfSelection.Z += App->CLSB_Brushes->PosZ_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;

			case SB_LINEDOWN:
				App->CLSB_Brushes->CenterOfSelection.Z -= App->CLSB_Brushes->PosZ_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;
			}

			App->CLSB_Brushes->Update_Pos_Dlg();

			return 0;
		}

		return 0;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_CBPOSXDELTA)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[MAX_PATH]{ 0 };

				HWND temp = GetDlgItem(hDlg, IDC_CBPOSXDELTA);
				int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
				SendMessage(temp, CB_GETLBTEXT, Index, (LPARAM)buff);

				App->CLSB_Brushes->PosX_Delta = atof(buff);
			}
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CBPOSYDELTA)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[MAX_PATH]{ 0 };

				HWND temp = GetDlgItem(hDlg, IDC_CBPOSYDELTA);
				int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
				SendMessage(temp, CB_GETLBTEXT, Index, (LPARAM)buff);

				App->CLSB_Brushes->PosY_Delta = atof(buff);
			}
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CBPOSZDELTA)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[MAX_PATH]{ 0 };

				HWND temp = GetDlgItem(hDlg, IDC_CBPOSZDELTA);
				int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
				SendMessage(temp, CB_GETLBTEXT, Index, (LPARAM)buff);

				App->CLSB_Brushes->PosZ_Delta = atof(buff);
			}
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			App->CLSB_Brushes->Dimensions_Dlg_Running = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CLSB_Brushes->Dimensions_Dlg_Running = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;

	}
	return FALSE;
}

// *************************************************************************
// *				Move_Brush:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
void SB_Brushes::Move_Brush()
{
	geVec3d_Subtract(&App->CLSB_Brushes->CenterOfSelection, &App->CLSB_Brushes->m_pDoc->SelectedGeoCenter, &App->CLSB_Brushes->CenterOfSelection);

	App->CLSB_Brushes->m_pDoc->MoveSelectedBrushList(App->CLSB_Brushes->m_pDoc->pSelBrushes, &App->CLSB_Brushes->CenterOfSelection);

	App->CLSB_Brushes->m_pDoc->UpdateAllViews(UAV_ALLVIEWS | REBUILD_QUICK, NULL);
}

// *************************************************************************
// *		Fill_ComboBox_PosDelta:- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
void SB_Brushes::Fill_ComboBox_PosDelta(HWND hDlg)
{
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.1");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.2");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"0.5");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"10");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"20");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"100");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"128");

	SendMessage(hDlg, CB_SETCURSEL, 3, 0);
}

// *************************************************************************
// *			Update_Pos_Dlg:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
void SB_Brushes::Update_Pos_Dlg()
{
	CenterOfSelection = m_pDoc->SelectedGeoCenter;

	char buf[255];
	sprintf(buf, "%f", CenterOfSelection.X);
	SetDlgItemText(Dimensions_Dlg_hWnd, IDC_ED_BRUSH_POSX, buf);

	sprintf(buf, "%f", CenterOfSelection.Y);
	SetDlgItemText(Dimensions_Dlg_hWnd, IDC_ED_BRUSH_POSY, buf);

	sprintf(buf, "%f", CenterOfSelection.Z);
	SetDlgItemText(Dimensions_Dlg_hWnd, IDC_ED_BRUSH_POSZ, buf);
}

// *************************************************************************
// *			Lock_Textures:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
void SB_Brushes::Lock_Textures(bool flag)
{
	int NumberOfFaces = 0;
	Face* pFace;

	m_pDoc->SelectAllFacesInBrushes();

	NumberOfFaces = SelFaceList_GetSize(m_pDoc->pSelFaces);

	for (int i = 0; i < NumberOfFaces; ++i)
	{
		pFace = SelFaceList_GetFace(m_pDoc->pSelFaces, i);
		Face_SetTextureLock(pFace, flag);
	}

	//m_pDoc->UpdateAllViews(UAV_RENDER_ONLY, NULL);
}