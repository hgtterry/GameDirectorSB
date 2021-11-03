/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Camera.h"


SB_Camera::SB_Camera()
{
}


SB_Camera::~SB_Camera()
{
}

// *************************************************************************
// *	  				Reset_View Terry Bernie							   *
// *************************************************************************
void SB_Camera::Reset_View(void)
{
	App->Cl_Grid->GridNode->setPosition(0, 0, 0);
	App->Cl_Grid->GridNode->resetOrientation();

	App->Cl_Grid->HairNode->setPosition(0, 0, 0);
	App->Cl_Grid->HairNode->resetOrientation();

	App->Cl19_Ogre->mCamera->setPosition(Ogre::Vector3(0, 90, 100));
	App->Cl19_Ogre->mCamera->lookAt(Ogre::Vector3(0, 30, 0));

}

// *************************************************************************
// *				Zoom   Terry Bernie								   *
// *************************************************************************
void SB_Camera::Zoom(void)
{
	if (App->CL_Vm_Model->Model_Loaded == 1)
	{
		Reset_View();
		App->Cl19_Ogre->mCamera->setPosition(App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].x, App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].y, App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].z);

		Ogre::Vector3 Move;
		Move.x = 0;
		Move.y = 0;//App->CL_Model_Data->S_BoundingBox[0]->Size[0].y;
				   //Move.z = App->CL_Model_Data->S_BoundingBox[0]->Size[0].y*2;

		if (App->CL_Vm_Model->S_BoundingBox[0]->Size[0].z > App->CL_Vm_Model->S_BoundingBox[0]->Size[0].y)
		{
			Move.z = App->CL_Vm_Model->S_BoundingBox[0]->Size[0].z * 2;
		}
		else
		{
			Move.z = App->CL_Vm_Model->S_BoundingBox[0]->Size[0].y * 2;
		}

		App->Cl19_Ogre->mCamera->moveRelative(Move);
	}

}
