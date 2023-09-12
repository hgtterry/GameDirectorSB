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

	Rotation.x = 0;
	Rotation.y = 0;
	Rotation.z = 0;

	FinalScale.X = 1;
	FinalScale.Y = 1;
	FinalScale.Z = 1;

	PosX_Delta = 1;
	PosY_Delta = 1;
	PosZ_Delta = 1;

	ScaleX_Delta = 1;
	ScaleY_Delta = 1;
	ScaleZ_Delta = 1;

	RotX_Delta = 1;
	RotY_Delta = 1;
	RotZ_Delta = 1;

	ScaleLock_Flag = 1;

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

		//Lock_Textures(true);

		SelBrushList_Center(m_pDoc->pSelBrushes, &m_pDoc->SelectedGeoCenter);

		CenterOfSelection = m_pDoc->SelectedGeoCenter;

		Get_Brush();

		if (App->CLSB_Equity->EquitySB_Dialog_Visible == 0)
		{
			Dimensions_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_BRUSHDIMENSIONS, App->MainHwnd, (DLGPROC)Dimensions_Dlg_Proc);
		}
		else
		{
			Dimensions_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_BRUSHDIMENSIONS, App->Equity_Dlg_hWnd, (DLGPROC)Dimensions_Dlg_Proc);
		}

		ScaleLock_Flag = 1;

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
		SendDlgItemMessage(hDlg, IDC_STROTATION2, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_STPOSX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPOSY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPOSZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STROTX2, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STROTY2, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STROTZ2, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STSIZEX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STSIZEY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STSIZEZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_POSX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_POSY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_POSZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_ROTX3, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_ROTY3, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_ROTZ3, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_SCALEX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_SCALEY, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ED_BRUSH_SCALEZ, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_CBPOSXDELTA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CBPOSYDELTA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CBPOSZDELTA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_CBROTXDELTA3, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CBROTYDELTA3, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CBROTZDELTA3, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_SIZELOCK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		App->CLSB_Brushes->Update_Deltas_Dlg(hDlg);

		// ----------- ScaleLock
		if (App->CLSB_Brushes->ScaleLock_Flag == 1)
		{
			HWND temp = GetDlgItem(hDlg, IDC_SIZELOCK);
			SendMessage(temp, BM_SETCHECK, 1, 0);
			App->CLSB_Brushes->EnableScaleControls_Dlg(hDlg, false);
		}

		App->CLSB_Brushes->Update_Pos_Dlg(hDlg);

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

		if (GetDlgItem(hDlg, IDC_STROTATION2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STROTX2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STROTY2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STROTZ2) == (HWND)lParam)
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

		
		if (GetDlgItem(hDlg, IDC_STSIZEX) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STSIZEY) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STSIZEZ) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_SIZELOCK) == (HWND)lParam)
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

	case WM_HSCROLL:
	{
		// ------------------------------------------------------------- Position
		// -------- Pos X
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBPOSXH))
		{
			switch ((int)LOWORD(wParam))
			{
			case SB_LINERIGHT:
			{
				App->CLSB_Brushes->CenterOfSelection.X += App->CLSB_Brushes->PosX_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;
			}

			case SB_LINELEFT:
			{
				App->CLSB_Brushes->CenterOfSelection.X -= App->CLSB_Brushes->PosX_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;
			}
			}

			App->CLSB_Brushes->Update_Pos_Dlg(hDlg);

			return 0;
		}

		// ------- Pos Y
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBPOSYH))
		{
			switch ((int)LOWORD(wParam))
			{
			case SB_LINERIGHT:
			{
				App->CLSB_Brushes->CenterOfSelection.Y += App->CLSB_Brushes->PosY_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;
			}

			case SB_LINELEFT:
			{
				App->CLSB_Brushes->CenterOfSelection.Y -= App->CLSB_Brushes->PosY_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;
			}
			}

			App->CLSB_Brushes->Update_Pos_Dlg(hDlg);

			return 0;
		}

		// ------- Pos Y
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBPOSZH))
		{
			switch ((int)LOWORD(wParam))
			{
			case SB_LINERIGHT:
			{
				App->CLSB_Brushes->CenterOfSelection.Z += App->CLSB_Brushes->PosZ_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;
			}

			case SB_LINELEFT:
			{
				App->CLSB_Brushes->CenterOfSelection.Z -= App->CLSB_Brushes->PosZ_Delta;
				App->CLSB_Brushes->Move_Brush();
				break;
			}
			}

			App->CLSB_Brushes->Update_Pos_Dlg(hDlg);

			return 0;
		}

		// ------------------------------------------------------------- Rotation
		// -------- Rot X
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBROTXH))
		{
			float m_Delta = App->CLSB_Brushes->RotX_Delta * GE_PI/180;

			switch ((int)LOWORD(wParam))
			{
			case SB_LINERIGHT:
			{

				App->CLSB_Brushes->Rotation.x += +App->CLSB_Brushes->RotX_Delta;
				App->CLSB_Brushes->Rotate_Brush(m_Delta,0,0);
				break;
			}

			case SB_LINELEFT:
			{
				App->CLSB_Brushes->Rotation.x += -App->CLSB_Brushes->RotX_Delta;
				App->CLSB_Brushes->Rotate_Brush(-m_Delta,0,0);
				break;
			}
			}

			App->CLSB_Brushes->Update_Pos_Dlg(hDlg);

			return 0;
		}

		// ------- Rot Y
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBROTYH))
		{
			float m_Delta = App->CLSB_Brushes->RotY_Delta * GE_PI / 180;

			switch ((int)LOWORD(wParam))
			{
			case SB_LINERIGHT:
			{
				App->CLSB_Brushes->Rotation.y += +App->CLSB_Brushes->RotY_Delta;
				App->CLSB_Brushes->Rotate_Brush(0, m_Delta, 0);
				break;
			}

			case SB_LINELEFT:
			{
				App->CLSB_Brushes->Rotation.y += -App->CLSB_Brushes->RotY_Delta;
				App->CLSB_Brushes->Rotate_Brush(0, -m_Delta, 0);
				break;
			}
			}

			App->CLSB_Brushes->Update_Pos_Dlg(hDlg);

			return 0;
		}

		// ------- Rot Y
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBROTZH))
		{
			float m_Delta = App->CLSB_Brushes->RotZ_Delta * GE_PI / 180;

			switch ((int)LOWORD(wParam))
			{
			case SB_LINERIGHT:
			{
				App->CLSB_Brushes->Rotation.z += +App->CLSB_Brushes->RotZ_Delta;
				App->CLSB_Brushes->Rotate_Brush(0,0, m_Delta);
				App->CLSB_Brushes->Move_Brush();
				break;
			}

			case SB_LINELEFT:
			{
				App->CLSB_Brushes->Rotation.z += -App->CLSB_Brushes->RotZ_Delta;
				App->CLSB_Brushes->Rotate_Brush(0, 0, -m_Delta);
				break;
			}
			}

			App->CLSB_Brushes->Update_Pos_Dlg(hDlg);

			return 0;
		}

		// ------------------------------------------------------------- SCALE
		// -------- Scale X
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBSCALEX))
		{
			switch ((int)LOWORD(wParam))
			{
			case SB_LINERIGHT:
			{
				if (App->CLSB_Brushes->ScaleLock_Flag == 1)
				{
					App->CLSB_Brushes->Scale_Brush_Lock(1);
				}
				else
				{
					float Delta = App->CLSB_Brushes->ScaleX_Delta;
					float scale = (App->CLSB_Brushes->Size.x + Delta) / App->CLSB_Brushes->Size.x;

					App->CLSB_Brushes->Scale_Brush(scale, 1, 1);
				}

				break;
			}

			case SB_LINELEFT:
			{
				if (App->CLSB_Brushes->ScaleLock_Flag == 1)
				{
					App->CLSB_Brushes->Scale_Brush_Lock(0);
				}
				else
				{
					if (App->CLSB_Brushes->Size.x > 1)
					{
						float Delta = App->CLSB_Brushes->ScaleX_Delta;
						float scale = (App->CLSB_Brushes->Size.x + -Delta) / App->CLSB_Brushes->Size.x;

						App->CLSB_Brushes->Scale_Brush(scale, 1, 1);
					}
				}
				break;
			}
			}

			App->CLSB_Brushes->Update_Pos_Dlg(hDlg);

			return 0;
		}

		// -------- Scale Y
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBSCALEY))
		{
			switch ((int)LOWORD(wParam))
			{
			case SB_LINERIGHT:
			{
				float scale = (App->CLSB_Brushes->Size.y + 1) / App->CLSB_Brushes->Size.y;

				App->CLSB_Brushes->Scale_Brush(1, scale, 1);
				break;
			}

			case SB_LINELEFT:
			{
				if (App->CLSB_Brushes->Size.y > 1)
				{
					float scale = (App->CLSB_Brushes->Size.y + -1) / App->CLSB_Brushes->Size.y;

					App->CLSB_Brushes->Scale_Brush(1, scale, 1);
				}
				break;
			}
			}

			App->CLSB_Brushes->Update_Pos_Dlg(hDlg);

			return 0;
		}

		// -------- Scale Z
		if (HWND(lParam) == GetDlgItem(hDlg, IDC_SBSCALEZ))
		{
			switch ((int)LOWORD(wParam))
			{
			case SB_LINERIGHT:
			{
				float scale = (App->CLSB_Brushes->Size.z + 1) / App->CLSB_Brushes->Size.z;

				App->CLSB_Brushes->Scale_Brush(1, 1,scale);
				break;
			}

			case SB_LINELEFT:
			{
				if (App->CLSB_Brushes->Size.z > 1)
				{
					float scale = (App->CLSB_Brushes->Size.z + -1) / App->CLSB_Brushes->Size.z;

					App->CLSB_Brushes->Scale_Brush(1, 1, scale);
				}
				break;
			}
			}

			App->CLSB_Brushes->Update_Pos_Dlg(hDlg);

			return 0;
		}

		
		return 0;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_SIZELOCK)
		{
			HWND temp = GetDlgItem(hDlg, IDC_SIZELOCK);

			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				App->CLSB_Brushes->ScaleLock_Flag = 1;
				App->CLSB_Brushes->EnableScaleControls_Dlg(hDlg,false);
				return 1;
			}
			else
			{
				App->CLSB_Brushes->ScaleLock_Flag = 0;
				App->CLSB_Brushes->EnableScaleControls_Dlg(hDlg, true);
				return 1;
			}

			return TRUE;
		}

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

		if (LOWORD(wParam) == IDC_CBROTXDELTA3)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[MAX_PATH]{ 0 };

				HWND temp = GetDlgItem(hDlg, IDC_CBROTXDELTA3);
				int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
				SendMessage(temp, CB_GETLBTEXT, Index, (LPARAM)buff);

				App->CLSB_Brushes->RotX_Delta = atof(buff);
			}
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CBROTYDELTA3)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[MAX_PATH]{ 0 };

				HWND temp = GetDlgItem(hDlg, IDC_CBROTYDELTA3);
				int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
				SendMessage(temp, CB_GETLBTEXT, Index, (LPARAM)buff);

				App->CLSB_Brushes->RotY_Delta = atof(buff);
			}
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CBROTZDELTA3)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{
				char buff[MAX_PATH]{ 0 };

				HWND temp = GetDlgItem(hDlg, IDC_CBROTZDELTA3);
				int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
				SendMessage(temp, CB_GETLBTEXT, Index, (LPARAM)buff);

				App->CLSB_Brushes->RotZ_Delta = atof(buff);
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

	App->CLSB_Doc->UpdateAllViews(UAV_ALLVIEWS | REBUILD_QUICK, NULL);
}

// *************************************************************************
// *				Rotate_Brush:- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
void SB_Brushes::Rotate_Brush(float SX, float SY, float SZ)
{
	App->Get_Current_Document();

	FinalScale.X = SX;
	FinalScale.Y = SY;
	FinalScale.Z = SZ;

	App->m_pDoc->RotateSelectedBrushList(App->CLSB_Brushes->m_pDoc->pSelBrushes, &FinalScale);

	App->CLSB_Doc->UpdateAllViews(UAV_ALLVIEWS | UAV_ALL3DVIEWS | REBUILD_QUICK, NULL);
}

// *************************************************************************
// *				Scale_Brush:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
void SB_Brushes::Scale_Brush(float SX, float SY, float SZ)
{
	App->Get_Current_Document();

	FinalScale.X = SX;
	FinalScale.Y = SY;
	FinalScale.Z = SZ;

	App->m_pDoc->ScaleSelectedBrushes(&FinalScale);
	
	App->CLSB_Doc->UpdateAllViews(UAV_ALLVIEWS | REBUILD_QUICK, NULL);
}

// *************************************************************************
// *			Scale_Brush_Lock:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Brushes::Scale_Brush_Lock(bool increase)
{
	App->Get_Current_Document();

	float scaleX = 1;
	float scaleY = 1;
	float scaleZ = 1;

	if (increase == 1)
	{
		scaleX = (App->CLSB_Brushes->Size.x + 1) / App->CLSB_Brushes->Size.x;
		scaleY = (App->CLSB_Brushes->Size.y + 1) / App->CLSB_Brushes->Size.y;
		scaleZ = (App->CLSB_Brushes->Size.z + 1) / App->CLSB_Brushes->Size.z;
	}
	else
	{
		scaleX = (App->CLSB_Brushes->Size.x + -1) / App->CLSB_Brushes->Size.x;
		scaleY = (App->CLSB_Brushes->Size.y + -1) / App->CLSB_Brushes->Size.y;
		scaleZ = (App->CLSB_Brushes->Size.z + -1) / App->CLSB_Brushes->Size.z;
	}
	
	FinalScale.X = scaleX;
	FinalScale.Y = scaleY;
	FinalScale.Z = scaleZ;

	App->m_pDoc->ScaleSelectedBrushes(&FinalScale);

	App->CLSB_Doc->UpdateAllViews(UAV_ALLVIEWS | REBUILD_QUICK, NULL);
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
// *		Fill_ComboBox_RotDelta:- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
void SB_Brushes::Fill_ComboBox_RotDelta(HWND hDlg)
{
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"1");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"45");
	SendMessage(hDlg, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"90");

	SendMessage(hDlg, CB_SETCURSEL, 0, 0);
}

// *************************************************************************
// *			Update_Deltas_Dlg:- Terry and Hazel Flanigan 2023	 	   *
// *************************************************************************
void SB_Brushes::Update_Deltas_Dlg(HWND hDlg)
{
	// Pos
	HWND CB_hWnd = GetDlgItem(hDlg, IDC_CBPOSXDELTA);
	App->CLSB_Brushes->Fill_ComboBox_PosDelta(CB_hWnd);

	CB_hWnd = GetDlgItem(hDlg, IDC_CBPOSYDELTA);
	App->CLSB_Brushes->Fill_ComboBox_PosDelta(CB_hWnd);

	CB_hWnd = GetDlgItem(hDlg, IDC_CBPOSZDELTA);
	App->CLSB_Brushes->Fill_ComboBox_PosDelta(CB_hWnd);

	// Rot
	CB_hWnd = GetDlgItem(hDlg, IDC_CBROTXDELTA3);
	App->CLSB_Brushes->Fill_ComboBox_RotDelta(CB_hWnd);

	CB_hWnd = GetDlgItem(hDlg, IDC_CBROTYDELTA3);
	App->CLSB_Brushes->Fill_ComboBox_RotDelta(CB_hWnd);

	CB_hWnd = GetDlgItem(hDlg, IDC_CBROTZDELTA3);
	App->CLSB_Brushes->Fill_ComboBox_RotDelta(CB_hWnd);
}

// *************************************************************************
// *			Update_Pos_Dlg:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
void SB_Brushes::Update_Pos_Dlg(HWND hDlg)
{
	//Lock_Textures(true);

	Get_Brush();
	SelBrushList_Center(m_pDoc->pSelBrushes, &m_pDoc->SelectedGeoCenter);
	CenterOfSelection = m_pDoc->SelectedGeoCenter;
	
	char buf[255];

	// Pos
	sprintf(buf, "%.3f", CenterOfSelection.X);
	SetDlgItemText(hDlg, IDC_ED_BRUSH_POSX, buf);

	sprintf(buf, "%.3f", CenterOfSelection.Y);
	SetDlgItemText(hDlg, IDC_ED_BRUSH_POSY, buf);

	sprintf(buf, "%.3f", CenterOfSelection.Z);
	SetDlgItemText(hDlg, IDC_ED_BRUSH_POSZ, buf);

	// Rotation
	sprintf(buf, "%.2f", Rotation.x);
	SetDlgItemText(hDlg, IDC_ED_BRUSH_ROTX3, buf);

	sprintf(buf, "%.2f", Rotation.y);
	SetDlgItemText(hDlg, IDC_ED_BRUSH_ROTY3, buf);

	sprintf(buf, "%.2f", Rotation.z);
	SetDlgItemText(hDlg, IDC_ED_BRUSH_ROTZ3, buf);

	// Scale
	sprintf(buf, "%.2f", Size.x);
	SetDlgItemText(hDlg, IDC_ED_BRUSH_SCALEX, buf);

	sprintf(buf, "%.2f", Size.y);
	SetDlgItemText(hDlg, IDC_ED_BRUSH_SCALEY, buf);

	sprintf(buf, "%.2f", Size.z);
	SetDlgItemText(hDlg, IDC_ED_BRUSH_SCALEZ, buf);

}

// *************************************************************************
// *		EnableScaleControls_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Brushes::EnableScaleControls_Dlg(HWND hDlg, bool Enable)
{
	EnableWindow(GetDlgItem(hDlg, IDC_ED_BRUSH_SCALEY), Enable);
	EnableWindow(GetDlgItem(hDlg, IDC_ED_BRUSH_SCALEZ), Enable);
	
	EnableWindow(GetDlgItem(hDlg, IDC_SBSCALEY), Enable);
	EnableWindow(GetDlgItem(hDlg, IDC_SBSCALEZ), Enable);
	
	EnableWindow(GetDlgItem(hDlg, IDC_CBSIZEYDELTA), Enable);
	EnableWindow(GetDlgItem(hDlg, IDC_CBSIZEZDELTA), Enable);

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
		Face_SetTextureLock(pFace, 256);
	}

	//m_pDoc->UpdateAllViews(UAV_RENDER_ONLY, NULL);
}

// *************************************************************************
// *			 	Get_Brush:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Brushes::Get_Brush()
{
	App->Get_Current_Document();

	int NumberOfBrushes;
	Brush* pBrush;

	NumberOfBrushes = SelBrushList_GetSize(App->m_pDoc->pSelBrushes);

	if (NumberOfBrushes)
	{
		pBrush = SelBrushList_GetBrush(App->m_pDoc->pSelBrushes, (NumberOfBrushes - 1));
	}
	else
	{
		App->Say("Cant Get Brush");
	}

	Size.x = (fabs(pBrush->BoundingBox.Max.X - pBrush->BoundingBox.Min.X));
	Size.y = (fabs(pBrush->BoundingBox.Max.Y - pBrush->BoundingBox.Min.Y));
	Size.z = (fabs(pBrush->BoundingBox.Max.Z - pBrush->BoundingBox.Min.Z));

	geVec3d mSize;
	mSize.X = 2;
	mSize.Y = 2;
	mSize.Z = 2;

	//Brush_Scale3d(pBrush, &mSize);
	//App->Say(pBrush->Name);
}

// *************************************************************************
// *			Centre_CentreBrush:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Brushes::Centre_CentreBrush()
{
	App->Get_Current_Document();

	int Index = App->CL_World->Get_Brush_Index_By_Name("XYZ");
	if (Index == -1)
	{
		App->Say("Error");
		return;
	}

	Brush* Selected_Brush = NULL;
	Selected_Brush = App->CL_World->Get_Brush_ByIndex(Index);
	if (Selected_Brush == NULL)
	{
		App->Say("Error");
		return;
	}
	else
	{
		geVec3d Centre;
		Centre.X = 0;
		Centre.Y = 0;
		Centre.Z = 0;

		SelBrushList_Add(App->m_pDoc->pSelBrushes, Selected_Brush);
		App->m_pDoc->MoveSelectedBrushList(App->m_pDoc->pSelBrushes, &Centre);
	}
}
