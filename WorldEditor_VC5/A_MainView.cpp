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

#include "A_MainView.h"

A_MainView::A_MainView(void)
{
}

A_MainView::~A_MainView(void)
{
}

// *************************************************************************
// *	  	Start_Main_View_Dlg:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_MainView::Start_Main_View_Dlg()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_SB_TESTDIALOG, App->MainHwnd, (DLGPROC)Main_View_Proc);
	return 1;
}

// *************************************************************************
// *        	Main_View_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_MainView::Main_View_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		{
			//SetWindowLong(GetDlgItem(hDlg, IDC_STTEST), GWL_WNDPROC, (LONG)ViewerTest);

			App->CL_Main_View->Start_LeftTop_Dlg(hDlg);
			return TRUE;
		}

	case WM_CTLCOLORSTATIC:
		{
			return FALSE;
		}

	case WM_CTLCOLORDLG:
		{
			return (LONG)App->AppBackground;
		}

	case WM_NOTIFY:
		{
			LPNMHDR some_item = (LPNMHDR)lParam;

			return CDRF_DODEFAULT;
		}

	//case WM_PAINT:
 //       {
 //           //PAINTSTRUCT ps;
 //           //HDC hdc = BeginPaint(hWnd, &ps);
 //          
	//		//App->CL_Main_View->Start_LeftTop_Dlg(hDlg);
 //           //EndPaint(hWnd, &ps);
	//		return 0;
 //       }

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK)
			{
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
// *	  	Start_LeftTop_Dlg:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_MainView::Start_LeftTop_Dlg(HWND hDlg)
{
	CreateDialog(App->hInst, (LPCTSTR)IDD_SB_LEFTTOP, hDlg, (DLGPROC)LeftTop_Proc);
	return 1;
}

// *************************************************************************
// *        	LeftTop_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK A_MainView::LeftTop_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		{
			//SetWindowLong(GetDlgItem(hDlg, IDC_STLEFTTOP), GWL_WNDPROC, (LONG)ViewerTest);
			return TRUE;
		}

	case WM_CTLCOLORSTATIC:
		{
			return FALSE;
		}

	case WM_CTLCOLORDLG:
		{
			return (LONG)App->AppBackground;
		}

	case WM_NOTIFY:
		{
			LPNMHDR some_item = (LPNMHDR)lParam;

			return CDRF_DODEFAULT;
		}

		case WM_PAINT:
        {
			App->CL_Main_View->ViewerTest(hDlg);
			return 0;
        }

	case WM_COMMAND:
		{
			if (LOWORD(wParam) == IDOK)
			{
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
// *						ViewerTest Terry Flanigan		  			   *
// *************************************************************************
bool A_MainView::ViewerTest(HWND hwnd)
{
		PAINTSTRUCT	ps;
		HDC			hDC;
		RECT		Rect;

		hDC = BeginPaint(hwnd, &ps);
		GetClientRect(hwnd, &Rect);
		Rect.left--;
		Rect.bottom--;

		HBRUSH hBrush = CreateSolidBrush(RGB(128,128,128));
		FillRect(hDC, &Rect, (HBRUSH)hBrush);
		DeleteObject(hBrush);
		
		HPEN pen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
		SelectObject(hDC, pen);

		App->CL_Main_View->Draw_Grid(hDC,8,Rect);

		HPEN pen2 = CreatePen(PS_SOLID, 0, RGB(255, 255, 255));
		SelectObject(hDC, pen2);

		App->CL_Main_View->Draw_Grid(hDC,32,Rect);

		EndPaint(hwnd, &ps);

		//DeleteObject(hBrush);
		DeleteObject(pen);

		RedrawWindow(hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		return 0;
	
	return 1;//DefWindowProc(hwnd, msg, wParam, lParam);
}

// *************************************************************************
// *	  			Draw_Grid:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool A_MainView::Draw_Grid(HDC hDC, int Interval,RECT Rect)
{
	int cnt = Rect.bottom/Interval;

	int SP = 0;
	int Count = 0;

	// horizontal lines
	while (Count < cnt)
	{
		MoveToEx(hDC,0,SP,NULL);
		LineTo(hDC,Rect.right,SP);

		SP = SP + Interval;
		Count++;
	}

	cnt = Rect.right/Interval;
	SP = 0;
	Count = 0;
	// vertical lines
	while (Count < cnt)
	{
		MoveToEx(hDC,SP,0,NULL);
		LineTo(hDC,SP,Rect.bottom);

		SP = SP + Interval;
		Count++;
	}

	return 1;
}
