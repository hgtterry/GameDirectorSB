#include "stdafx.h"
#include "ME_App.h"


ME_App::ME_App()
{
	hInst =			nullptr;

	MainHwnd =		nullptr;
	ViewGLhWnd =	nullptr;

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
