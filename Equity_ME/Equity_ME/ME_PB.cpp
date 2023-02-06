#include "StdAfx.h"
#include "resource.h"
#include "ME_App.h"
#include "ME_PB.h"
//#include "WinGDI.h"

ME_PB::ME_PB(void)
{
	ProgBarHwnd = nullptr;
	Dio = 0;
	Pani = 0;
	g_pos = 0;
	Bar = 0;
	Steps = 3000;
	ClearBarDlg = 0;
}

ME_PB::~ME_PB(void)
{
}


// *************************************************************************
// *							StartNewProgressBar						   *
// *************************************************************************
bool ME_PB::StartNewProgressBar()
{

	ProgBarHwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROGRESS_BAR,App->Fdlg, (DLGPROC)ProgressNewBarProc);

	Dio = 0;
	Pani = 0;
	return 1;
}
// *************************************************************************
// *						ProgressNewBarProc			  				   *
// *************************************************************************
LRESULT CALLBACK ME_PB::ProgressNewBarProc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
		
		SendDlgItemMessage(hDlg, IDC_PBBANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_PBACTION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_PB_STATUS, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		
		App->CL_PB->g_pos = 0;
		App->CL_PB->Bar = GetDlgItem(hDlg, IDC_STBAR);
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

		hdc = BeginPaint(App->CL_PB->Bar, &ps);

		GetClientRect(App->CL_PB->Bar, &rect);

		till = (rect.right / App->CL_PB->Steps) * App->CL_PB->g_pos * 1;
		step = rect.right / 10.0;
		full = (rect.right / App->CL_PB->Steps);

		hPen = CreatePen(PS_NULL, 1, RGB(0, 0, 0));
		holdPen = (HPEN)SelectObject(hdc, hPen);


		if (App->CL_PB->ClearBarDlg == 1)
		{
			holdBrush = (HBRUSH)SelectObject(hdc, App->Brush_White);
			::Rectangle(hdc, 0, 0, rect.right, 32);
			App->CL_PB->ClearBarDlg = 0;
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
			App->Custom_Button_Normal(item);
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
bool ME_PB::Stop_Progress_Bar(char* ProcessText)
{
	EnableWindow(GetDlgItem(ProgBarHwnd, IDOK), 1);

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
bool ME_PB::Set_Progress(char* ProcessText, float TotalSteps)
{
	MSG msg;
	char buff[1024];
	strcpy(buff, "Processing :- ");
	strcat(buff, ProcessText);

	g_pos = 0;
	Steps = TotalSteps;

	SetDlgItemText(ProgBarHwnd, IDC_PBACTION, (LPCTSTR)buff);

	App->CL_PB->ClearBarDlg = 1;

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
bool ME_PB::Set_Progress_Text(char* ProcessText)
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
bool ME_PB::Nudge()
{
	MSG msg;

	App->CL_PB->g_pos++;
	InvalidateRect(ProgBarHwnd, NULL, FALSE);

	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return 1;
}
// *************************************************************************
// *							Close									   *
// *************************************************************************
bool ME_PB::Close()
{
	DestroyWindow(ProgBarHwnd);
	return 1;
}
