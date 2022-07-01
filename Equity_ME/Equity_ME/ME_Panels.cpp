#include "stdafx.h"
#include "ME_App.h"
#include "ME_Panels.h"


ME_Panels::ME_Panels()
{
}


ME_Panels::~ME_Panels()
{
}

// *************************************************************************
// *						Move_FileView_Window Terry Bernie			   *
// *************************************************************************
bool ME_Panels::Move_FileView_Window(void)
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
bool ME_Panels::Place_GlobalGroups(void)
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

	DeferWindowPos(hdwp, App->CL_Groups->RightGroups_Hwnd, NULL, p.x + widthX - 295, PosY + 5,
		0, 0, SWP_NOSIZE | SWP_NOZORDER);

	
	return EndDeferWindowPos(hdwp);
}

// *************************************************************************
// *						Resize Inflanite							   *
// *************************************************************************
bool ME_Panels::Resize(void)
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

	//-----------------Ogre Window
	SetWindowPos(App->ViewGLhWnd, NULL, 0, 41, NewWidth + 384, NewHeight + 100, SWP_NOZORDER);
	
	return 1;
}

// *************************************************************************
// *					Enable Paneles Terry Flanigan					   *
// *************************************************************************
void ME_Panels::Enable_Panels(int show)
{
	EnableWindow(App->ListPanel, show);
	EnableWindow(App->CL_Groups->RightGroups_Hwnd, show);
}

// *************************************************************************
// *					Show Paneles Terry Flanigan					   *
// *************************************************************************
void ME_Panels::Show_Panels(int show)
{
	ShowWindow(App->ListPanel, show);
	ShowWindow(App->CL_Groups->RightGroups_Hwnd, show);
}

