/*
Copyright (c) 2022- 2023 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "resource.h"
#include "ME_Splitter.h"

#define LEFT_WINDOW_WIDTH		200
#define	TOP_POS					80
#define	BOTTOM_POS				80
#define	LEFT_MINIMUM_SPACE		150
#define	RIGHT_MINIMUM_SPACE		500
#define	SPLITTER_BAR_WIDTH		20
#define WIDTH_ADJUST			2

ME_Splitter::ME_Splitter()
{
	Spliter_Main_Hwnd = nullptr;
	Left_Window_Hwnd = nullptr;
	Right_Window_Hwnd = nullptr;
}

ME_Splitter::~ME_Splitter()
{
}

// *************************************************************************
// *	  			Start_Splitter:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void ME_Splitter::Start_Splitter()
{
	Spliter_Main_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SPLITTER, App->Fdlg, (DLGPROC)Splitter_Proc);

	Create_Left_Window();

}

// *************************************************************************
// *			Splitter_Proc:- Terry and Hazel Flanigan 2023 			   *
// *************************************************************************
LRESULT CALLBACK ME_Splitter::Splitter_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static  int     nleftWnd_width = 0;
	static HCURSOR	hcSizeEW = NULL;

	static  BOOL        xSizing;
	static UINT			nwnd_resizing = 0;

	RECT rect;

	switch (message)
	{
	case WM_INITDIALOG:
	{
		hcSizeEW = LoadCursor(NULL, IDC_SIZEWE);
		/*SendDlgItemMessage(hDlg, IDC_TITLENAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDITTEXT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_TITLENAME, (LPCTSTR)App->CL_Dialogs->btext);
		SetDlgItemText(hDlg, IDC_EDITTEXT, (LPCTSTR)App->CL_Dialogs->Chr_Text);*/

		nleftWnd_width = LEFT_WINDOW_WIDTH;

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_TITLENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}*/
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		/*LPNMHDR some_item = (LPNMHDR)lParam;

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
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_MOUSEMOVE:
	{
		int   xPos;
		int   yPos;

		// Get the x and y co-ordinates of the mouse
		xPos = (int)LOWORD(lParam);
		yPos = (int)HIWORD(lParam);

		if (xPos < LEFT_MINIMUM_SPACE || xPos > RIGHT_MINIMUM_SPACE)
		{
			return 0;
		}

		// Checks if the left button is pressed during dragging the splitter
		if (wParam == MK_LBUTTON)
		{
			// If the window is d`agged using the splitter, get the
			// cursors current postion and draws a focus rectangle 
			if (xSizing)
			{
				RECT    focusrect;
				HDC     hdc;

				hdc = GetDC(hDlg);
				GetClientRect(hDlg, &rect);

				if (xSizing)
				{
					SetRect(&focusrect, nleftWnd_width - (WIDTH_ADJUST * 2), rect.top + TOP_POS,
						nleftWnd_width + WIDTH_ADJUST,
						rect.bottom - BOTTOM_POS);

					DrawFocusRect(hdc, &focusrect);

					// Get the size of the left window to increase
					nleftWnd_width = xPos;

					// Draws a focus rectangle
					SetRect(&focusrect, nleftWnd_width - (SPLITTER_BAR_WIDTH * 2), rect.top + 80,
						nleftWnd_width + SPLITTER_BAR_WIDTH,
						rect.bottom - BOTTOM_POS);

					DrawFocusRect(hdc, &focusrect);

				}
				ReleaseDC(hDlg, hdc);
			}

			FlashWindow(App->MainHwnd, true);
		}
		// Set the cursor image to east west direction when the mouse is over 
		// the splitter window
		
		if ((xPos > nleftWnd_width - SPLITTER_BAR_WIDTH && xPos < nleftWnd_width +SPLITTER_BAR_WIDTH))
		{
			SetCursor(hcSizeEW);
		}
		return 1;
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
	}

	break;

	}
	return FALSE;
}



// *************************************************************************
// *	  	Create_Left_Window:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void ME_Splitter::Create_Left_Window()
{
	RECT rect;

	Left_Window_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SPLITTERLEFT, Spliter_Main_Hwnd, (DLGPROC)Left_Window_Proc);

	GetClientRect(Left_Window_Hwnd, &rect);

	SetWindowPos(Left_Window_Hwnd, NULL, rect.left, rect.top + TOP_POS, LEFT_WINDOW_WIDTH, 
		(rect.bottom - rect.top) - (TOP_POS + BOTTOM_POS), SWP_NOZORDER);
}

// *************************************************************************
// *			Left_Window_Proc:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
LRESULT CALLBACK ME_Splitter::Left_Window_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		/*SendDlgItemMessage(hDlg, IDC_TITLENAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDITTEXT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_TITLENAME, (LPCTSTR)App->CL_Dialogs->btext);
		SetDlgItemText(hDlg, IDC_EDITTEXT, (LPCTSTR)App->CL_Dialogs->Chr_Text);*/

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_TITLENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}*/
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_White;
	}

	case WM_NOTIFY:
	{
		/*LPNMHDR some_item = (LPNMHDR)lParam;

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
		}*/

		return CDRF_DODEFAULT;
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
	}

	break;

	}
	return FALSE;
}
