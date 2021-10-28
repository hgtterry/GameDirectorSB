#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "EQ15_Physics.h"


EQ15_Physics::EQ15_Physics()
{
	PhysicsPannel_Hwnd = nullptr;
}


EQ15_Physics::~EQ15_Physics()
{
}

// *************************************************************************
// *				Start_Physics_Pannel Terry Flanigan		  		 	   *
// *************************************************************************
bool EQ15_Physics::Start_Physics_Pannel()
{
	PhysicsPannel_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PHYSICSPANEL, App->Fdlg, (DLGPROC)Start_Physics_Proc);
	ShowWindow(PhysicsPannel_Hwnd, 0);
	return 1;
}

// *************************************************************************
// *						Groups_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK EQ15_Physics::Start_Physics_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		/*SendDlgItemMessage(hDlg, IDC_RGGROUPNAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_RGTEXTURENAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_INFO, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CHANGETEXTURE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));*/

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
		ShowWindow(App->CL_Physics_E15->PhysicsPannel_Hwnd, 0);

		break;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

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
			App->CL_Physics_E15->Update_Model();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTPHYTEST)
		{
			int f = App->SBC_Player->mObject->getCollisionFlags();

			if (App->Cl19_Ogre->OgreListener->GD_Dubug_Physics == 0)
			{
				App->Cl19_Ogre->OgreListener->GD_Dubug_Physics = 1;
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
				App->Cl19_Ogre->BulletListener->ShowDebug = 1;

				App->SBC_Player->ShowDebug = 1;
				App->SBC_Player->mObject->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
			}
			else
			{
				App->Cl19_Ogre->OgreListener->GD_Dubug_Physics = 0;
				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 0;
				App->Cl19_Ogre->BulletListener->ShowDebug = 0;
				App->SBC_Player->ShowDebug = 0;
				App->SBC_Player->mObject->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
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
void EQ15_Physics::Update_Model(void)
{
	strcpy(App->CL_Vm_Model->Model_FolderPath, App->Cl_Vm_Preferences->Pref_Ogre_Path);
	strcpy(App->CL_Vm_Model->FileName, App->Cl_Vm_Preferences->Pref_Ogre_JustFileName);

	App->CL_Bullet_AddRoom->AddToScene(0);

	App->Say("Model Updated");
}

// *************************************************************************
// *					Enable_Physics Terry Flanigan					   *
// *************************************************************************
void EQ15_Physics::Enable_Physics(void)
{
	int f = App->SBC_Player->mObject->getCollisionFlags();

	App->Cl19_Ogre->OgreListener->GD_Dubug_Physics = 1;
	App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
	App->Cl19_Ogre->BulletListener->ShowDebug = 1;

	App->SBC_Player->ShowDebug = 1;
	App->SBC_Player->mObject->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
}
