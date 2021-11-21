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
#include "resource.h"
#include "SB_Camera.h"


SB_Camera::SB_Camera()
{
	Cam_Props_HWND = nullptr;

	CamPos_X = 0;
	CamPos_Y = 90;
	CamPos_Z = 100;

	LookAt_X = 0;
	LookAt_Y = 30;
	LookAt_Z = 0;

	strcpy(Camera_Name, "Cam_1");

	ListViewItem = nullptr;
}


SB_Camera::~SB_Camera()
{
}

// *************************************************************************
// *	  			Start_Camera_PropsPanel Terry Bernie				   *
// *************************************************************************
bool SB_Camera::Start_Camera_PropsPanel()
{
	
	Cam_Props_HWND = CreateDialog(App->hInst,(LPCTSTR)IDD_PROPS_CAMERA,App->Cl_Properties->Properties_Dlg_hWnd,(DLGPROC)Camera_PropsPanel_Proc);
	return 1;
}
// *************************************************************************
// *		  	Camera_PropsPanel_Proc  Terry Bernie					   *
// *************************************************************************
LRESULT CALLBACK SB_Camera::Camera_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_BTCAMSAVE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTCAMGOTO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
	
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BTCAMSAVE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTCAMGOTO && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BTCAMSAVE)
		{
			App->SBC_Project->Write_Camera();
			App->Say("Camera Saved");
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTCAMGOTO)
		{
			App->SBC_Camera->Set_Camera();
			return TRUE;
		}
		
		
		break;
	}
	return FALSE;
}

// *************************************************************************
// *					Hide_Cam_Dlg Terry Bernie 						   *
// *************************************************************************
void SB_Camera::Hide_Cam_Dlg(bool Show)
{
		ShowWindow(Cam_Props_HWND, Show);
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
// *	  				Set_Camera Terry Bernie							   *
// *************************************************************************
void SB_Camera::Set_Camera(void)
{
	App->Cl19_Ogre->mCamera->setPosition(Ogre::Vector3(CamPos_X, CamPos_Y, CamPos_Z));
	App->Cl19_Ogre->mCamera->lookAt(Ogre::Vector3(LookAt_X, LookAt_Y, LookAt_Z));
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
