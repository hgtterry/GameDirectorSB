/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Panels.h"

#pragma warning( disable : 4800)

SB_Panels::SB_Panels()
{
}


SB_Panels::~SB_Panels()
{
}

// *************************************************************************
// *			Resize_FileView:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Panels::Resize_FileView(void)
{
	RECT rcl;

	HDWP hdwp;

	int WidthClient = 0;
	int HeightClient;
	int NewWidth = 0;
	int NewHeight = 0;

	GetClientRect(App->ListPanel, &rcl);

	WidthClient = rcl.right - rcl.left - 1010;
	NewWidth = 417 + WidthClient + 200;

	HeightClient = rcl.bottom - rcl.top;
	NewHeight = HeightClient - 150;

	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	HWND Temp3 = GetDlgItem(App->ListPanel, IDC_BT_INFO_FILEVIEW);
	
	hdwp = BeginDeferWindowPos(4);

	DeferWindowPos(hdwp, Temp, NULL, 2, 2,
		NewWidth + 388, NewHeight + 71, SWP_NOZORDER);

	DeferWindowPos(hdwp, Temp3, NULL, 10, NewHeight + 113,
		0, 07, SWP_NOSIZE | SWP_NOZORDER);

	return EndDeferWindowPos(hdwp);
}

// *************************************************************************
// *			MoveCentralView:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Panels::MovePhysicsView(void)
{
	if (App->SBC_Gui_Dialogs->Show_Physics_Console == 1)
	{
		App->SBC_Gui_Dialogs->Physics_Console_StartPos = 0;
	}
	return 1;
}

// *************************************************************************
// *		Move_FileView_Window:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Panels::Move_FileView_Window(void)
{
	POINT p = { 0 };

	int Diff = MapWindowPoints(App->ViewGLhWnd, NULL, &p, 1);

	int PosX = p.x;
	int PosY = p.y;

	SetWindowPos(App->ListPanel, NULL, PosX + 0, PosY + 5,
		0, 0, SWP_NOSIZE | SWP_NOZORDER);

	return 1;
}

// *************************************************************************
// *			Place_GlobalGroups:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Panels::Place_GlobalGroups(void)
{
	POINT p = { 0 };

	int Diff = MapWindowPoints(App->ViewGLhWnd, NULL, &p, 1);

	HDWP hdwp;

	RECT rect;
	GetWindowRect(App->ViewGLhWnd, &rect);

	int widthX = rect.right - rect.left;
	int heightY = rect.bottom - rect.top;

	int PosX = p.x;
	int PosY = p.y;

	hdwp = BeginDeferWindowPos(2);

	DeferWindowPos(hdwp, App->SBC_Properties->Properties_Dlg_hWnd, NULL, p.x + widthX - 255, PosY + 5,
		0, 0, SWP_NOSIZE | SWP_NOZORDER);

	///DeferWindowPos(hdwp, App->GD_Stock_Hwnd, NULL, p.x + widthX - 250, PosY + 10,
		///0, 0, SWP_NOSIZE | SWP_NOZORDER);

	return EndDeferWindowPos(hdwp);
}

// *************************************************************************
// *				Disable_Panels:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Panels::Enable_All_Panels(bool Enable)
{
	EnableWindow(App->ListPanel, Enable);
	EnableWindow(App->SBC_Properties->Properties_Dlg_hWnd, Enable);
	EnableWindow(App->SBC_TopTabs->TabsHwnd, Enable);

}
