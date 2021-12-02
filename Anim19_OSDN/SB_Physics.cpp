/*
Copyright (c) 2021 Stage Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Physics.h"


SB_Physics::SB_Physics()
{
	PhysicsPannel_Hwnd = nullptr;

	Toggle_Enable_Flag = 0;
}


SB_Physics::~SB_Physics()
{
}

// *************************************************************************
// *				Start_Physics_Pannel Terry Flanigan		  		 	   *
// *************************************************************************
bool SB_Physics::Start_Physics_Pannel()
{
	PhysicsPannel_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PHYSICSPANEL, App->Fdlg, (DLGPROC)Start_Physics_Proc);
	ShowWindow(PhysicsPannel_Hwnd, 0);
	return 1;
}

// *************************************************************************
// *						Groups_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK SB_Physics::Start_Physics_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_BTPHYTEST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

	}

	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_RGGROUPNAME) == (HWND)lParam)
		{
		SetBkColor((HDC)wParam, RGB(0, 255, 0));
		SetTextColor((HDC)wParam, RGB(0, 0, 0));
		SetBkMode((HDC)wParam, TRANSPARENT);
		return (UINT)App->AppBackground;
		}*/

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_CLOSE:
	{
		ShowWindow(App->SBC_Physics->PhysicsPannel_Hwnd, 0);

		break;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BTPHYTEST && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Physics->Toggle_Enable_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_BTPHYLOAD)
		{
			App->SBC_Import->Bullet_Load_Room("Ogre3D   *.mesh\0*.mesh\0", "Ogre3D");
			strcpy(App->Cl_Vm_Preferences->Pref_Ogre_JustFileName, App->CL_Vm_Model->FileName);
			strcpy(App->Cl_Vm_Preferences->Pref_Ogre_Path, App->CL_Vm_Model->Model_FolderPath);
			App->Cl_Vm_Preferences->Write_Preferences();

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTPHYRESET)
		{
			//if (App->Cl_Scene_Data->SceneLoaded == 1)
			{
				App->Cl_Bullet->Reset_Physics();
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTUPDATEMODEL)
		{
			App->SBC_Physics->Update_Model();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTPHYTEST)
		{
			int f = App->SBC_Player->mObject->getCollisionFlags();

			if (App->Cl19_Ogre->OgreListener->Dubug_Physics_Draw == 0)
			{
				App->SBC_Physics->Enable_Physics(1);
			}
			else
			{
				App->SBC_Physics->Enable_Physics(0);
			}
			return TRUE;
		}
	}
	}

	return FALSE;
}

// *************************************************************************
// *				Update_Model (Terry Bernie)							   *
// *************************************************************************
void SB_Physics::Update_Model(void)
{
	strcpy(App->CL_Vm_Model->Model_FolderPath, App->Cl_Vm_Preferences->Pref_Ogre_Path);
	strcpy(App->CL_Vm_Model->FileName, App->Cl_Vm_Preferences->Pref_Ogre_JustFileName);

	App->CL_Bullet_AddRoom->AddToScene(0);

	App->Say("Model Updated");
}

// *************************************************************************
// *					Enable_Physics Terry Flanigan					   *
// *************************************************************************
void SB_Physics::Enable_Physics(bool Enable)
{
	int f = App->SBC_Player->mObject->getCollisionFlags();

	App->Cl19_Ogre->OgreListener->Dubug_Physics_Draw = Enable;
	App->Cl19_Ogre->OgreListener->GD_Run_Physics = Enable;
	App->Cl19_Ogre->BulletListener->Render_Debug_Flag = Enable;

	App->SBC_Player->ShowDebug = Enable;

	App->SBC_Player->mObject->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);

	App->SBC_Physics->Toggle_Enable_Flag = Enable;

	RedrawWindow(App->SBC_Physics->PhysicsPannel_Hwnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}
