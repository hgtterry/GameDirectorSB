#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_Panels.h"

#pragma warning( disable : 4800)

ME_Panels::ME_Panels()
{
}


ME_Panels::~ME_Panels()
{
}

// *************************************************************************
// *						Resize_OgreWin Inflanite					   *
// *************************************************************************
bool ME_Panels::ResizeOgre_Window(void)
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
	SetWindowPos(App->ViewGLhWnd, NULL, 4, 80, NewWidth + 384, NewHeight + 68, SWP_NOZORDER);

	if (App->CL_Ogre->Ogre_Started == 1)
	{
		RECT rect;
		GetClientRect(App->ViewGLhWnd, &rect);

		if ((rect.bottom - rect.top) != 0 && App->CL_Ogre->mCamera != 0)
		{
			App->CL_Ogre->mWindow->windowMovedOrResized();
			App->CL_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CL_Ogre->mWindow->getWidth() / (Ogre::Real)App->CL_Ogre->mWindow->getHeight());
			App->CL_Ogre->mCamera->yaw(Ogre::Radian(0));

			Root::getSingletonPtr()->renderOneFrame();
		}

	}

	Move_FileView_Window();
	Place_GlobalGroups();

	return 1;
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

	SetWindowPos(App->CL_TopBar->Tabs_TB_hWnd, NULL, 220, 2,
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

	hdwp = BeginDeferWindowPos(5);

	DeferWindowPos(hdwp, App->CL_Groups->RightGroups_Hwnd, NULL, p.x + widthX - 295, PosY + 5,
		0, 0, SWP_NOSIZE | SWP_NOZORDER);

	DeferWindowPos(hdwp, App->CL_Motions->RightMotions_Hwnd, NULL, p.x + widthX - 295, PosY + 5,
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
// *			Resize_FileView:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool ME_Panels::Resize_FileView(void)
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
	//HWND Temp3 = GetDlgItem(App->ListPanel, IDC_BT_INFO_FILEVIEW);

	hdwp = BeginDeferWindowPos(4);

	DeferWindowPos(hdwp, Temp, NULL, 2, 2,
		NewWidth + 388, NewHeight + 71, SWP_NOZORDER);

	/*DeferWindowPos(hdwp, Temp3, NULL, 10, NewHeight + 113,
		0, 07, SWP_NOSIZE | SWP_NOZORDER);*/

	return EndDeferWindowPos(hdwp);
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

// *************************************************************************
// *					Hide_Panels Terry Flanigan						   *
// *************************************************************************
void ME_Panels::Hide_Panels()
{
	ShowWindow(App->CL_Groups->RightGroups_Hwnd,false);
	App->CL_Groups->RightGroups_Visable = 0;

	ShowWindow(App->CL_Motions->RightMotions_Hwnd, false);
	App->CL_Motions->RightMotions_Visable = 0;
}
