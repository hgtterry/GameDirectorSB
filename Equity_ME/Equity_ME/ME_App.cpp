/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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


ME_App::ME_App()
{
	CL_Ogre =		nullptr;
	CL_Utilities =	nullptr;
	CL_Grid =		nullptr;
	CL_ImGui =		nullptr;
	CL_Assimp =		nullptr;
	CL_Import =		nullptr;
	CL_FileIO =		nullptr;
	CL_Model =		nullptr;
	CL_TopBar =		nullptr;
	CL_FileView =	nullptr;

	hInst =			nullptr;

	MainHwnd =		nullptr;
	ViewGLhWnd =	nullptr;
	ListPanel =		nullptr;

	AppBackground = nullptr;
	BlackBrush =	nullptr;

	EquityDirecory_FullPath[0] = 0;
}


ME_App::~ME_App()
{
}

// *************************************************************************
// *						InitApp Inflanite							   *
// *************************************************************************
bool ME_App::InitApp(void)
{
	CL_Ogre =		new ME_Ogre();
	CL_Utilities =	new ME_Utilities();
	CL_Grid =		new ME_Grid();
	CL_ImGui =		new ME_ImGui();
	CL_Assimp =		new ME_Assimp();
	CL_Import =		new ME_Import();
	CL_FileIO =		new ME_FileIO();
	CL_Model =		new ME_Model();
	CL_TopBar =		new ME_TopBar();
	CL_FileView =	new ME_FileView();

	SetBrushes_Fonts();
	return 1;
}

// *************************************************************************
// *					SetMainWinCentre Inflanite						   *
// *************************************************************************
bool ME_App::SetMainWin_Centre(void)
{
	int ClientWidth_X = GetSystemMetrics(SM_CXSCREEN);
	int ClientHeight_Y = GetSystemMetrics(SM_CYSCREEN);

	RECT Control;
	GetClientRect(MainHwnd, &Control);

	int AllX = (ClientWidth_X / 2) - (Control.right / 2) - 10;
	int AllY = (ClientHeight_Y / 2) - (Control.bottom / 2) - 30;

	SetWindowPos(MainHwnd, NULL, AllX, AllY, 0, 0, SWP_NOSIZE);

	return 1;
}

// *************************************************************************
// *					SetBrushes_Fonts Inflanite						   *
// *************************************************************************
void ME_App::SetBrushes_Fonts(void)
{
	AppBackground = CreateSolidBrush(RGB(213, 222, 242));
	BlackBrush = CreateSolidBrush(RGB(0, 0, 0));
}

// *************************************************************************
// *						Resize_OgreWin Inflanite					   *
// *************************************************************************
bool ME_App::ResizeOgre_Window(void)
{
	RECT rcl;

	int WidthClient = 0;
	int HeightClient;
	int NewWidth = 0;
	int NewHeight = 0;

	GetClientRect(MainHwnd, &rcl);

	WidthClient = rcl.right - rcl.left - 1010;
	NewWidth = 417 + WidthClient + 200;

	HeightClient = rcl.bottom - rcl.top;
	NewHeight = HeightClient - 150;

	//-----------------Ogre Window
	SetWindowPos(ViewGLhWnd, NULL, 4, 80, NewWidth + 384, NewHeight + 68, SWP_NOZORDER);

	if (App->CL_Ogre->Ogre_Started == 1)
	{
		RECT rect;
		GetClientRect(App->ViewGLhWnd, &rect);

		if ((rect.bottom - rect.top) != 0 && App->CL_Ogre->mCamera != 0)
		{
			App->CL_Ogre->mWindow->windowMovedOrResized();
			App->CL_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CL_Ogre->mWindow->getWidth() / (Ogre::Real)App->CL_Ogre->mWindow->getHeight());
			App->CL_Ogre->mCamera->yaw(Ogre::Radian(0));
			Ogre::Root::getSingletonPtr()->renderOneFrame();
		}

	}

	/*App->Cl_Panels->MovePhysicsView();
	App->Cl_Panels->Move_FileView_Window();
	App->Cl_Panels->Place_GlobalGroups();*/

	return 1;
}

// *************************************************************************
// *								Say_Win								   *
// *************************************************************************
void ME_App::Say_Win(const char* Message)
{
	char text[1024];
	strcpy(text, Message);
	MessageBox(MainHwnd, Message, "Message", MB_OK);
}

