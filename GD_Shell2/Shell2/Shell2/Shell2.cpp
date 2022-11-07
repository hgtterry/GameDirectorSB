/*	
	Copyright (c) 2009 - 2013 W.T.Flanigan Bernard Parkin and H.C.Flanigan

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
#include "Shell2.h"

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

BT_App *			App = NULL;


// *************************************************************************
// *				WinMain   Terry Bernie  							   *
// *************************************************************************
int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{

	App = new BT_App();
	_getcwd(App->GameDirecory_FullPath,1024);

	App->InitApp();

	App->SetStructures();	

	App->GDCL_Bullet->Init_Bullet();
	App->GDCL_Scene_Data->Init_Scene();

	App->ScreenHeight = GetSystemMetrics(SM_CYSCREEN);
	App->ScreenWidth = GetSystemMetrics(SM_CXSCREEN);

	//App->CL10_Load_Scene->Load_Config_File();

	App->Ogre17->InitOgre();
	

	App->GDCL_Scene_Data->Start_Scene();
	//App->GDCL_Scene_Data->GameMode();

	App->Ogre17->mRoot->startRendering();

	// --------------------------------------------- Close
	//if (App->FullScreen == 0)
	{
		if (App->Ogre17->mRoot)
		{
			delete App->Ogre17->mRoot;
			App->Ogre17->mRoot = NULL;
		}

		SystemParametersInfo(SPI_SETSCREENSAVEACTIVE,TRUE,NULL,TRUE);
	}
	//else
	{
		SystemParametersInfo(SPI_SETSCREENSAVEACTIVE,TRUE,NULL,TRUE);
	}

	return 0;
}