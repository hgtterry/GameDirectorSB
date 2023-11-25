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
#include "resource.h"
#include "AB_App.h"
#include "SB_PB.h"

SB_PB::SB_PB()
{
	ProgBarHwnd = nullptr;
	Dio = 0;
	Pani = 0;
	g_pos = 0;
	Bar = 0;
	Steps = 3000;
	ClearBarDlg = 0;
}

SB_PB::~SB_PB()
{
}

// *************************************************************************
// *							Start_ProgressBar						   *
// *************************************************************************
bool SB_PB::Start_ProgressBar()
{

	ProgBarHwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_PROGRESS_BAR, App->MainHwnd, (DLGPROC)ProgressNewBarProc);

	Dio = 0;
	Pani = 0;
	ClearBarDlg = 1;

	InvalidateRect(ProgBarHwnd, NULL, FALSE);

	return 1;
}
// *************************************************************************
// *						ProgressNewBarProc			  				   *
// *************************************************************************
LRESULT CALLBACK SB_PB::ProgressNewBarProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	HBRUSH holdBrush;
	HPEN hPen, holdPen;
	PAINTSTRUCT ps;
	RECT rect;

	HDC hdc;
	int till;
	int step, full;

	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_PBBANNER, WM_SETFONT, (WPARAM)App->Font_Banner, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_PBACTION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_PB_STATUS, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		App->CLSB_PB->ProgBarHwnd = hDlg;
		App->CLSB_PB->g_pos = 0;
		App->CLSB_PB->Bar = GetDlgItem(hDlg, IDC_STBAR);

		SetDlgItemText(hDlg, IDC_PBBANNER, (LPCTSTR)"Converting");

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STBAR) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_PBACTION) == (HWND)lParam)
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_PBBANNER) == (HWND)lParam)
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_PB_STATUS) == (HWND)lParam)
		{
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_PAINT:
	{

		hdc = BeginPaint(App->CLSB_PB->Bar, &ps);

		GetClientRect(App->CLSB_PB->Bar, &rect);

		till = (rect.right / App->CLSB_PB->Steps) * App->CLSB_PB->g_pos * 1;
		step = rect.right / 10.0;
		full = (rect.right / App->CLSB_PB->Steps);

		hPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
		holdPen = (HPEN)SelectObject(hdc, hPen);


		if (App->CLSB_PB->ClearBarDlg == 1)
		{
			holdBrush = (HBRUSH)SelectObject(hdc, App->Brush_White);
			::Rectangle(hdc, 0, 0, rect.right, 32);
			App->CLSB_PB->ClearBarDlg = 0;
		}
		else
		{
			holdBrush = (HBRUSH)SelectObject(hdc, App->Brush_Green);
			::Rectangle(hdc, 0, 0, till, 32);
		}

		SelectObject(hdc, holdBrush);

		DeleteObject(hPen);

		EndPaint(hDlg, &ps);
		break;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			bool test = IsWindowEnabled(GetDlgItem(hDlg, IDOK));
			if (test == 0)
			{
				App->Custom_Button_Greyed(item);
			}
			else
			{
				App->Custom_Button_Normal(item);
			}

			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}

// *************************************************************************
// *							Stop_Progress_Bar 						   *
// *************************************************************************
bool SB_PB::Stop_Progress_Bar(char* ProcessText)
{
	EnableWindow(GetDlgItem(ProgBarHwnd, IDOK), 1);


	SetDlgItemText(ProgBarHwnd, IDC_PBBANNER, (LPCTSTR)"Finished");
	SetDlgItemText(ProgBarHwnd, IDC_ST_PB_STATUS, (LPCTSTR)ProcessText);

	InvalidateRect(ProgBarHwnd, NULL, FALSE);

	MSG msg;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	InvalidateRect(ProgBarHwnd, NULL, FALSE);

	return 1;
}

// *************************************************************************
// *							Set_Progress 							   *
// *************************************************************************
bool SB_PB::Set_Progress(char* ProcessText, float TotalSteps)
{
	MSG msg;
	char buff[1024];
	strcpy(buff, "Processing :- ");
	strcat(buff, ProcessText);

	g_pos = 0;
	Steps = TotalSteps;

	SetDlgItemText(ProgBarHwnd, IDC_PBACTION, (LPCTSTR)buff);

	ClearBarDlg = 1;

	InvalidateRect(ProgBarHwnd, NULL, FALSE);

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	InvalidateRect(ProgBarHwnd, NULL, FALSE);

	return 1;
}

// *************************************************************************
// *							Set_Progress_Text 						   *
// *************************************************************************
bool SB_PB::Set_Progress_Text(char* ProcessText)
{
	MSG msg;
	char buff[1024];
	strcpy(buff, "Processing :- ");
	strcat(buff, ProcessText);

	SetDlgItemText(ProgBarHwnd, IDC_PBACTION, (LPCTSTR)buff);
	SetDlgItemText(ProgBarHwnd, IDC_ST_PB_STATUS, (LPCTSTR)ProcessText);

	InvalidateRect(ProgBarHwnd, NULL, FALSE);
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	InvalidateRect(ProgBarHwnd, NULL, FALSE);
	return 1;
}


// *************************************************************************
// *								Nudge 								   *
// *************************************************************************
bool SB_PB::Nudge(char* Message)
{
	Set_Progress_Text(Message);

	MSG msg;
	g_pos++;

	RedrawWindow(ProgBarHwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	Sleep(100);

	RedrawWindow(ProgBarHwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	return 1;
}

// *************************************************************************
// *							Close									   *
// *************************************************************************
bool SB_PB::Close()
{
	DestroyWindow(ProgBarHwnd);
	return 1;
}