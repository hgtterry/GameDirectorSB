/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "VM_Dimensions.h"


VM_Dimensions::VM_Dimensions()
{
}


VM_Dimensions::~VM_Dimensions()
{
}

// *************************************************************************
// *	  				Centre_Model_Mid Terry Bernie					   *
// *************************************************************************
void VM_Dimensions::Centre_Model_Mid(void)
{
	if (App->CL_Vm_Model->Model_Loaded == 1)
	{
		float X = -App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].x;
		float Y = -App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].y;
		float Z = -App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].z;

		if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
		{

		}
		else
		{
			int Count = 0;
			int VertCount = 0;
			while (Count < App->CL_Vm_Model->GroupCount)
			{
				VertCount = 0;
				while (VertCount < App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount)
				{
					App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].x += X;
					App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].y += Y;
					App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].z += Z;
					VertCount++;
				}
				Count++;
			}

			App->CL_Vm_Model->GetBoundingBoxModel_Update();
		}
	}

	/*Ogre::Root::getSingletonPtr()->renderOneFrame();
	Ogre::Root::getSingletonPtr()->renderOneFrame();
	App->CL_Global_Model->UpdatePositionData(PositionDlg_Hwnd);*/
}

// *************************************************************************
// *	  				Centre_Model_Base Terry Bernie					   *
// *************************************************************************
void VM_Dimensions::Centre_Model_Base(void)
{
	if (App->CL_Vm_Model->Model_Loaded == 1)
	{

		float X = -App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].x;
		float Y = -App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].y + App->CL_Vm_Model->S_BoundingBox[0]->Size[0].y / 2;
		float Z = -App->CL_Vm_Model->S_BoundingBox[0]->Centre[0].z;

		if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
		{
			/*App->CL_Export_Actor->Actor_Position.X = 0;
			App->CL_Export_Actor->Actor_Position.Y = 0;
			App->CL_Export_Actor->Actor_Position.Z = 0;
			App->CL_Export_Actor->MoveActor();*/
		}
		else
		{
			int Count = 0;
			int VertCount = 0;
			while (Count < App->CL_Vm_Model->GroupCount)
			{
				VertCount = 0;
				while (VertCount < App->CL_Vm_Model->S_MeshGroup[Count]->GroupVertCount)
				{
					App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].x += X;
					App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].y += Y;
					App->CL_Vm_Model->S_MeshGroup[Count]->vertex_Data[VertCount].z += Z;
					VertCount++;
				}
				Count++;
			}

			App->CL_Vm_Model->GetBoundingBoxModel_Update();
		}
	}

	/*Ogre::Root::getSingletonPtr()->renderOneFrame();
	Ogre::Root::getSingletonPtr()->renderOneFrame();
	App->CL_Global_Model->UpdatePositionData(PositionDlg_Hwnd);*/
}
