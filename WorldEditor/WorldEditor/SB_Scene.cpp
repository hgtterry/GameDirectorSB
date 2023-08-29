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
#include "SB_Scene.h"

SB_Scene::SB_Scene()
{
	FullScreenMode_Flag = 0;
}

SB_Scene::~SB_Scene()
{
}

// *************************************************************************
// *		Go_FullScreen_Mode:- Terry and Hazel Flanigan 2022		  	   *
// *************************************************************************
void SB_Scene::Go_FullScreen_Mode(void)
{
	FullScreenMode_Flag = 1;

	//App->SBC_Scene->CurrentCamMode = App->CL_Ogre->OgreListener->GD_CameraMode;

	//App->FullScreen = 1;
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	SetWindowPos(App->ViewGLhWnd, HWND_TOP, 0, 0, cx, cy, NULL);

	SetParent(App->ViewGLhWnd, NULL);

	App->CLSB_Ogre->mWindow->resize(cx, cy);

	App->CLSB_Ogre->mWindow->windowMovedOrResized();
	App->CLSB_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CLSB_Ogre->mWindow->getWidth() / (Ogre::Real)App->CLSB_Ogre->mWindow->getHeight());

	Root::getSingletonPtr()->renderOneFrame();
}
