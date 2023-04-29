/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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
*/ // :- Terry and Hazel Flanigan 2023

#include "stdafx.h"
#include "WV_App.h"
#include "resource.h"
#include "WE_SPLITVIEWS.h"

#define	TOP_POS					8
#define	BOTTOM_POS				400
#define	SPLITTER_BAR_WIDTH		5
#define WIDTH_ADJUST			2
#define BOTTOM_POS_BOTLEFT		5

WE_SpliterViews::WE_SpliterViews()
{
	

	//Spliter_Main_Hwnd = nullptr;
	Left_Window_Hwnd = nullptr;
	Right_Window_Hwnd = nullptr;

	Bottom_Left_Hwnd = nullptr;
	Bottom_Right_Hwnd = nullptr;

	LEFT_WINDOW_WIDTH = 500;

	LEFT_WINDOW_DEPTH = 215;
	TOP_POS_BOTLEFT = 215;

	RIGHT_MINIMUM_SPACE = 1000;
	LEFT_MINIMUM_SPACE = 15;

	nleftWnd_width = LEFT_WINDOW_WIDTH;
	nleftWnd_Depth = LEFT_WINDOW_DEPTH;

	Do_Width = 0;
	Do_Depth = 0;
	Do_All = 0;

	BackGround_Brush = CreateSolidBrush(RGB(64, 64, 64));
}

WE_SpliterViews::~WE_SpliterViews()
{
}

// *************************************************************************
// *	  			Init_Views:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WE_SpliterViews::Init_Views()
{
	RECT rect;
	GetClientRect(App->Fdlg, &rect);

	LEFT_WINDOW_WIDTH = rect.right / 2;
	nleftWnd_width = rect.right / 2;

	LEFT_WINDOW_DEPTH = rect.bottom / 2;
	TOP_POS_BOTLEFT = rect.bottom / 2;
	nleftWnd_Depth = LEFT_WINDOW_DEPTH;

	RIGHT_MINIMUM_SPACE = rect.right - 15;
	LEFT_MINIMUM_SPACE = rect.left + 15;
	return 1;
}

// *************************************************************************
// *			Resize_Windowns:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool WE_SpliterViews::Resize_Windows(HWND hDlg, int NewWidth, int NewDepth)
{
	RECT rect;
	GetClientRect(hDlg, &rect);

	int Top_Windows_Top_Y = 8;
	int Left_Windows_Start_X = 0;

	int NewDepth_Depth = NewDepth - 11;

	/*[in] int  X,
	[in] int  Y,
	[in] int  nWidth,
	[in] int  nHeight,*/

	MoveWindow(App->CL_SplitterViews->Left_Window_Hwnd,
		Left_Windows_Start_X,
		Top_Windows_Top_Y,
		rect.left + (NewWidth - WIDTH_ADJUST),
		NewDepth_Depth,
		FALSE);


	MoveWindow(App->CL_SplitterViews->Right_Window_Hwnd,
		Left_Windows_Start_X + NewWidth + WIDTH_ADJUST,
		Top_Windows_Top_Y,
		rect.right - (NewWidth + WIDTH_ADJUST),
		NewDepth_Depth,
		FALSE);

	// Bottom Windows
	MoveWindow(App->CL_SplitterViews->Bottom_Left_Hwnd,
		Left_Windows_Start_X,
		rect.top + NewDepth,
		Left_Windows_Start_X + (NewWidth - WIDTH_ADJUST),
		rect.bottom - (NewDepth + BOTTOM_POS_BOTLEFT),
		FALSE);

	MoveWindow(App->ViewGLhWnd,
		Left_Windows_Start_X + NewWidth + WIDTH_ADJUST,
		rect.top + NewDepth,
		rect.right - (NewWidth + WIDTH_ADJUST),
		rect.bottom - (NewDepth + BOTTOM_POS_BOTLEFT),
		FALSE);

	RedrawWindow(App->Fdlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	return 1;
}

// *************************************************************************
// *						ViewerTest Terry Flanigan		  			   *
// *************************************************************************
bool WE_SpliterViews::ViewerTest(HWND hwnd)
{
	PAINTSTRUCT	ps;
	HDC			hDC;
	RECT		Rect;

	hDC = BeginPaint(hwnd, &ps);
	GetClientRect(hwnd, &Rect);
	Rect.left--;
	Rect.bottom--;

	HBRUSH hBrush = CreateSolidBrush(RGB(64, 64, 64));
	FillRect(hDC, &Rect, (HBRUSH)hBrush); // BackGround
	DeleteObject(hBrush);

	HPEN pen = CreatePen(PS_SOLID, 0, RGB(0, 0, 0));
	SelectObject(hDC, pen);
	Draw_Grid(hDC, 8, Rect); // Snap

	HPEN pen2 = CreatePen(PS_SOLID, 0, RGB(112, 112, 112));
	SelectObject(hDC, pen2);
	Draw_Grid(hDC, 64, Rect); // Grid

	EndPaint(hwnd, &ps);

	DeleteObject(pen);
	DeleteObject(pen2);
	return 1;
}

// *************************************************************************
// *	  			Draw_Grid:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool WE_SpliterViews::Draw_Grid(HDC hDC, int Interval, RECT Rect)
{
	int cnt = Rect.bottom / Interval;

	int SP = 0;
	int Count = 0;

	// horizontal lines
	while (Count < cnt + 1)
	{
		MoveToEx(hDC, 0, SP, NULL);
		LineTo(hDC, Rect.right, SP);

		SP = SP + Interval;
		Count++;
	}

	cnt = Rect.right / Interval;
	SP = 0;
	Count = 0;
	// vertical lines
	while (Count < cnt + 1)
	{
		MoveToEx(hDC, SP, 0, NULL);
		LineTo(hDC, SP, Rect.bottom);

		SP = SP + Interval;
		Count++;
	}

	return 1;
}

// *************************************************************************
// *			ViewerMain_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK WE_SpliterViews::ViewerMain_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	static HCURSOR	hcSizeEW = NULL;
	static HCURSOR	hcSizeNS = NULL;
	static HCURSOR	hcBoth = NULL;

	static  BOOL        xSizing;
	static  BOOL        ySizing;

	static UINT			nwnd_resizing = 0;

	RECT rect;

	switch (message)
	{

	case WM_INITDIALOG:
	{
		hcSizeEW = LoadCursor(NULL, IDC_SIZEWE);
		hcSizeNS = LoadCursor(NULL, IDC_SIZENS);
		hcBoth = LoadCursor(NULL, IDC_SIZEALL);
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	//case WM_PAINT:
	//{
	//	PAINTSTRUCT ps;
	//	HDC hdc = BeginPaint(hDlg, &ps);

	//	// All painting occurs here, between BeginPaint and EndPaint.
	//	FillRect(hdc, &ps.rcPaint, (HBRUSH)App->AppBackground);
	//	EndPaint(hDlg, &ps);
	//}

	case WM_SIZE:
	{
		//App->CL_SplitterViews->Init_Views();
		App->CL_SplitterViews->Resize_Windows(hDlg, App->CL_SplitterViews->nleftWnd_width, App->CL_SplitterViews->nleftWnd_Depth);

		GetClientRect(hDlg, &rect);
		RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		//InvalidateRect(hDlg, &rect, TRUE);
		return 0;
	}

	case WM_LBUTTONDOWN:
	{
		int                 xPos;
		int                 yPos;

		// Varible used to get the mouse cursor x and y co-ordinates
		xPos = (int)LOWORD(lParam);
		yPos = (int)HIWORD(lParam);

		// Checks whether the mouse is over the splitter window
		xSizing = (xPos > App->CL_SplitterViews->nleftWnd_width - SPLITTER_BAR_WIDTH && xPos < App->CL_SplitterViews->nleftWnd_width + SPLITTER_BAR_WIDTH);
		ySizing = (yPos > App->CL_SplitterViews->nleftWnd_Depth - SPLITTER_BAR_WIDTH && yPos < App->CL_SplitterViews->nleftWnd_Depth + SPLITTER_BAR_WIDTH);

		if (xSizing && ySizing == 0)
		{
			// Api to capture mouse input
			SetCapture(hDlg);
			if (xSizing)
			{
				SetCursor(hcSizeEW);
			}
		}

		if (ySizing && xSizing == 0)
		{
			// Api to capture mouse input
			SetCapture(hDlg);
			if (ySizing)
			{
				SetCursor(hcSizeNS);
			}
		}

		if (xSizing && ySizing)
		{
			SetCapture(hDlg);
			if (ySizing)
			{
				SetCursor(hcBoth);;
			}
		}

		return 1;
	}

	case WM_LBUTTONUP:
	{
		if (xSizing)
		{
			RECT    focusrect;
			HDC     hdc;

			ReleaseCapture();

			hdc = GetDC(hDlg);
			GetClientRect(hDlg, &rect);

			if (xSizing)
			{
				SetRect(&focusrect, App->CL_SplitterViews->nleftWnd_width - (WIDTH_ADJUST * 2), rect.top + TOP_POS,
					App->CL_SplitterViews->nleftWnd_width + WIDTH_ADJUST,
					rect.bottom - 80);

				DrawFocusRect(hdc, &focusrect);

				xSizing = FALSE;
			}

			ReleaseDC(hDlg, hdc);
		}

		if (ySizing)
		{
			HDC     hdc;

			ReleaseCapture();

			hdc = GetDC(hDlg);
			GetClientRect(hDlg, &rect);

			if (ySizing)
			{
				ySizing = FALSE;
			}

			ReleaseDC(hDlg, hdc);
		}

		App->CL_SplitterViews->Resize_Windows(hDlg, App->CL_SplitterViews->nleftWnd_width, App->CL_SplitterViews->nleftWnd_Depth);
		//RedrawWindow(App->Fdlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		//InvalidateRect(hDlg, &rect, true);
		App->Resize_OgreWin();
		return 1;
	}

	case WM_MOUSEMOVE:
	{

		int   xPos;
		int   yPos;

		// Get the x and y co-ordinates of the mouse
		xPos = (int)LOWORD(lParam);
		yPos = (int)HIWORD(lParam);

		if (xPos < App->CL_SplitterViews->LEFT_MINIMUM_SPACE || xPos > App->CL_SplitterViews->RIGHT_MINIMUM_SPACE)
		{
			return 0;
		}

		// Checks if the left button is pressed during dragging the splitter
		if (wParam == MK_LBUTTON)
		{

			if (xSizing && App->CL_SplitterViews->Do_Width == 1)
			{
				RECT    focusrect;
				HDC     hdc;

				hdc = GetDC(hDlg);
				GetClientRect(hDlg, &rect);

				if (xSizing && App->CL_SplitterViews->Do_Width == 1)
				{
					SetRect(&focusrect, App->CL_SplitterViews->nleftWnd_width - (WIDTH_ADJUST * 2), rect.top + TOP_POS,
						App->CL_SplitterViews->nleftWnd_width + WIDTH_ADJUST,
						rect.bottom - 6);

					DrawFocusRect(hdc, &focusrect);

					App->CL_SplitterViews->nleftWnd_width = xPos;

					SetRect(&focusrect, App->CL_SplitterViews->nleftWnd_width - (WIDTH_ADJUST * 2), rect.top + TOP_POS,
						App->CL_SplitterViews->nleftWnd_width + WIDTH_ADJUST,
						rect.bottom - 6);

					DrawFocusRect(hdc, &focusrect);
				}

				ReleaseDC(hDlg, hdc);
			}

			if (ySizing && App->CL_SplitterViews->Do_Depth == 1)
			{
				RECT    focusrect;
				HDC     hdc;

				hdc = GetDC(hDlg);
				GetClientRect(hDlg, &rect);

				if (ySizing && App->CL_SplitterViews->Do_Depth == 1)
				{
					SetRect(&focusrect, 0, App->CL_SplitterViews->nleftWnd_Depth, rect.right, App->CL_SplitterViews->nleftWnd_Depth + (WIDTH_ADJUST * 2));

					DrawFocusRect(hdc, &focusrect);

					App->CL_SplitterViews->nleftWnd_Depth = yPos;

					SetRect(&focusrect, 0, App->CL_SplitterViews->nleftWnd_Depth, rect.right, App->CL_SplitterViews->nleftWnd_Depth + (WIDTH_ADJUST * 2));

					DrawFocusRect(hdc, &focusrect);
				}

				ReleaseDC(hDlg, hdc);
			}

		}

		if ((xPos > App->CL_SplitterViews->nleftWnd_width - SPLITTER_BAR_WIDTH && xPos < App->CL_SplitterViews->nleftWnd_width + SPLITTER_BAR_WIDTH))
		{
			if (App->CL_SplitterViews->Do_All == 0)
			{
				SetCursor(hcSizeEW);
			}

			App->CL_SplitterViews->Do_Width = 1;
		}
		else
		{
			App->CL_SplitterViews->Do_Width = 0;
		}

		if ((yPos > App->CL_SplitterViews->nleftWnd_Depth - SPLITTER_BAR_WIDTH && yPos < App->CL_SplitterViews->nleftWnd_Depth + SPLITTER_BAR_WIDTH))
		{
			if (App->CL_SplitterViews->Do_All == 0)
			{
				SetCursor(hcSizeNS);
			}

			App->CL_SplitterViews->Do_Depth = 1;
		}
		else
		{
			App->CL_SplitterViews->Do_Depth = 0;
		}

		if (App->CL_SplitterViews->Do_Width == 1 && App->CL_SplitterViews->Do_Depth == 1)
		{
			SetCursor(hcBoth);
			App->CL_SplitterViews->Do_All = 1;
		}
		else
		{
			App->CL_SplitterViews->Do_All = 0;
		}


		return 1;
	}

	case WM_COMMAND:
	{

	}
	break;
	}
	return FALSE;
}

// *************************************************************************
// *	  	Create_Left_Window:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void WE_SpliterViews::Create_Left_Window()
{
	RECT rect;

	Left_Window_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_VIEW_TOPLEFT, App->Fdlg, (DLGPROC)Left_Window_Proc);

	//GetClientRect(Left_Window_Hwnd, &rect);

	/*SetWindowPos(Left_Window_Hwnd, NULL,
		rect.left, rect.top + TOP_POS,
		LEFT_WINDOW_WIDTH,
		(rect.bottom - rect.top) - (TOP_POS + BOTTOM_POS),
		SWP_NOZORDER);*/

}

// *************************************************************************
// *			Left_Window_Proc:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
LRESULT CALLBACK WE_SpliterViews::Left_Window_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		//SendDlgItemMessage(hDlg, IDC_STBANNERTL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_STBANNERTL) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}*/
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->CL_SplitterViews->BackGround_Brush;
	}

	case WM_PAINT:
	{
		App->CL_SplitterViews->ViewerTest(hDlg);
		return 0;
	}

	}

	return FALSE;
}

// *************************************************************************
// *	  	Create_Right_Window:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void WE_SpliterViews::Create_Right_Window()
{
	RECT rect;

	Right_Window_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_VIEW_TOPRIGHT, App->Fdlg, (DLGPROC)Right_Window_Proc);

	GetClientRect(Right_Window_Hwnd, &rect);

	SetWindowPos(Right_Window_Hwnd, NULL,
		rect.left + LEFT_WINDOW_WIDTH + SPLITTER_BAR_WIDTH,
		rect.top + TOP_POS,
		rect.right - (rect.left + LEFT_WINDOW_WIDTH + SPLITTER_BAR_WIDTH),
		(rect.bottom - rect.top) - (TOP_POS + BOTTOM_POS),
		SWP_NOZORDER);
}

// *************************************************************************
// *			Right_Window_Proc:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
LRESULT CALLBACK WE_SpliterViews::Right_Window_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->CL_SplitterViews->BackGround_Brush;
	}

	case WM_PAINT:
	{
		App->CL_SplitterViews->ViewerTest(hDlg);
		return 0;
	}

	}

	return FALSE;
}

// *************************************************************************
// *	  Create_Bottom_Left_Window:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void WE_SpliterViews::Create_Bottom_Left_Window()
{
	RECT rect;

	Bottom_Left_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_VIEW_BOTTOMLEFT, App->Fdlg, (DLGPROC)Bottom_Left_Proc);

	GetClientRect(Bottom_Left_Hwnd, &rect);

	SetWindowPos(Bottom_Left_Hwnd, NULL,
		rect.left, rect.top + TOP_POS_BOTLEFT,
		LEFT_WINDOW_WIDTH,
		(rect.bottom - rect.top) - (TOP_POS_BOTLEFT + BOTTOM_POS_BOTLEFT),
		SWP_NOZORDER);
}

// *************************************************************************
// *			Bottom_Left_Proc:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
LRESULT CALLBACK WE_SpliterViews::Bottom_Left_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->CL_SplitterViews->BackGround_Brush;
	}

	case WM_PAINT:
	{
		App->CL_SplitterViews->ViewerTest(hDlg);
		return 0;
	}

	}

	return FALSE;
}

// *************************************************************************
// *						Resize_OgreWin Inflanite					   *
// *************************************************************************
bool WE_SpliterViews::Resize_Fldg(void)
{
	RECT rcl;

	int WidthClient = 0;
	int HeightClient;
	int NewWidth = 0;
	int NewHeight = 0;

	GetClientRect(App->MainHwnd, &rcl);

	WidthClient = rcl.right - rcl.left - 1010;
	NewWidth = 417 + WidthClient + 200;

	HeightClient = rcl.bottom - rcl.top;
	NewHeight = HeightClient - 150;

	////-----------------Ogre Window
	SetWindowPos(App->Fdlg, NULL, 4, 80, NewWidth + 384, NewHeight + 68, SWP_NOZORDER);

	//if (App->CL_Ogre->Ogre_Started == 1)
	//{
	//	RECT rect;
	//	GetClientRect(App->ViewGLhWnd, &rect);

	//	if ((rect.bottom - rect.top) != 0 && App->CL_Ogre->mCamera != 0)
	//	{
	//		App->CL_Ogre->mWindow->windowMovedOrResized();
	//		App->CL_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CL_Ogre->mWindow->getWidth() / (Ogre::Real)App->CL_Ogre->mWindow->getHeight());
	//		App->CL_Ogre->mCamera->yaw(Ogre::Radian(0));

	//		Root::getSingletonPtr()->renderOneFrame();
	//	}

	//}

	//Move_FileView_Window();
	//Place_GlobalGroups();

	return 1;
}
