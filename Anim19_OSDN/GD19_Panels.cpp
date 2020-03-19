/*
Copyright (c) GameDirector 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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

GD19_Panels::GD19_Panels()
{
}


GD19_Panels::~GD19_Panels()
{
}

// *************************************************************************
// *						Resize_FileView Terry Bernie				   *
// *************************************************************************
bool GD19_Panels::Resize_FileView(void)
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
	//HWND Tree2 = GetDlgItem(App->ListPanel, IDC_TREE2);

	HWND Temp2 = GetDlgItem(App->ListPanel, IDC_ENVIONMENT);
	HWND Temp3 = GetDlgItem(App->ListPanel, IDC_LEVELS);
	HWND Temp4 = GetDlgItem(App->ListPanel, IDC_STOCK);

	hdwp = BeginDeferWindowPos(4);

	//-----------------Ogre Window
	DeferWindowPos(hdwp, Temp, NULL, 10, 10,
		NewWidth + 370, NewHeight + 71, SWP_NOZORDER);

	//DeferWindowPos(hdwp, Tree2, NULL, 10, 10,
		//NewWidth + 370, NewHeight + 71, SWP_NOZORDER);

	DeferWindowPos(hdwp, Temp2, NULL, 10, NewHeight + 115,
		0, 07, SWP_NOSIZE | SWP_NOZORDER);

	DeferWindowPos(hdwp, Temp3, NULL, 10, NewHeight + 87,
		0, 07, SWP_NOSIZE | SWP_NOZORDER);

	DeferWindowPos(hdwp, Temp4, NULL, 113, NewHeight + 87,
		0, 07, SWP_NOSIZE | SWP_NOZORDER);

	return EndDeferWindowPos(hdwp);
}

// *************************************************************************
// *						MoveCentralView Terry Bernie				   *
// *************************************************************************
bool GD19_Panels::MovePhysicsView(void)
{
	POINT p = { 0 };
	RECT rect;

	int Diff = MapWindowPoints(App->ViewGLhWnd, NULL, &p, 1);

	int PosX = p.x;
	int PosY = p.y;

	GetWindowRect(App->ViewGLhWnd, &rect);

	int widthX = rect.right - rect.left;
	int heightY = rect.bottom - rect.top;

	SetWindowPos(App->Physics_Console_Hwnd, NULL, PosX + 14, PosY + heightY - 110,
		0, 0, SWP_NOSIZE | SWP_NOZORDER);

	return 1;
}

// *************************************************************************
// *						Move_FileView_Window Terry Bernie			   *
// *************************************************************************
bool GD19_Panels::Move_FileView_Window(void)
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
// *						Place_GlobalGroups Terry Bernie				   *
// *************************************************************************
bool GD19_Panels::Place_GlobalGroups(void)
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

	DeferWindowPos(hdwp, App->Cl_Properties->Properties_Dlg_hWnd, NULL, p.x + widthX - 255, PosY + 5,
		0, 0, SWP_NOSIZE | SWP_NOZORDER);

	///DeferWindowPos(hdwp, App->GD_Stock_Hwnd, NULL, p.x + widthX - 250, PosY + 10,
		///0, 0, SWP_NOSIZE | SWP_NOZORDER);


	return EndDeferWindowPos(hdwp);
}
