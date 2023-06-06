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

#include "StdAfx.h"
#include "AB_App.h"
#include "SB_Camera.h"

SB_Camera::SB_Camera(void)
{
}

SB_Camera::~SB_Camera(void)
{
}

// *************************************************************************
// *			Reset_View:- Terry and Hazel Flanigan 2023				   *
// *************************************************************************
void SB_Camera::Reset_View(void)
{
	App->CLSB_Grid->GridNode->setPosition(0, 0, 0);
	App->CLSB_Grid->GridNode->resetOrientation();

	App->CLSB_Grid->HairNode->setPosition(0, 0, 0);
	App->CLSB_Grid->HairNode->resetOrientation();

	//App->CL_Ogre->RenderListener->RX = 0;
	//App->CL_Ogre->RenderListener->RZ = 0;

	App->CLSB_Ogre->mCamera->setPosition(Ogre::Vector3(0, 90, 100));
	App->CLSB_Ogre->mCamera->lookAt(Ogre::Vector3(0, 30, 0));
}

// *************************************************************************
// *			Set_Camera_Mode:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Camera::Set_Camera_Mode(int Mode)
{
	App->CLSB_Ogre->OgreListener->CameraMode = Mode;
}
