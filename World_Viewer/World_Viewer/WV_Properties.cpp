/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "WV_App.h"
#include "resource.h"
#include "WV_Properties.h"

WV_Properties::WV_Properties(void)
{
	Show_World_Physics_Debug = 0;
	Show_Player_Physics_Debug = 0;

	Properties_Dlg_Hwnd = nullptr;
}

WV_Properties::~WV_Properties(void)
{
}

// *************************************************************************
// *		Start_Properties_Dialog:- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
bool WV_Properties::Start_Properties_Dialog()
{
	Properties_Dlg_Hwnd = CreateDialog(App->hInst, (LPCTSTR)IDD_GD_PROPERTIES, App->MainHwnd, (DLGPROC)Properties_Proc);
	
	return 1;
}

// *************************************************************************
// *			Properties_Proc:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
LRESULT CALLBACK WV_Properties::Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
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

	case WM_CLOSE:
	{
		break;
	}


	case WM_NOTIFY:
	{


		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_BTTEST)
		{
			App->CL_Import_3DT->Load("C:\\Users\\Acer\\Desktop\\RF_World\\Test.3dt");

			if (App->CL_pDoc->pLevel == NULL)
			{
				return 1;
			}

			App->CL_BrushTabs_Dlg->Start_BrushTab_Dlg();

			return 1;
		}
		
		if (LOWORD(wParam) == IDC_BT_PHYSICSOUTLINE)
		{
			if (App->CL_Properties->Show_World_Physics_Debug == 1)
			{
				App->CL_Properties->Show_World_Physics_Debug = 0;

				int f = App->CL_Scene->B_Area[0]->Phys_Body->getCollisionFlags();
				App->CL_Scene->B_Area[0]->Phys_Body->setCollisionFlags(f | (1 << 5)); // Off

				App->CL_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->CL_Ogre->BulletListener->Clear_Debug_Render();
				App->CL_Ogre->BulletListener->Render_Debug_Flag = 1;
			}
			else
			{
				App->CL_Properties->Show_World_Physics_Debug = 1;

				int f = App->CL_Scene->B_Area[0]->Phys_Body->getCollisionFlags();
				App->CL_Scene->B_Area[0]->Phys_Body->setCollisionFlags(f & (~(1 << 5))); // on

				App->CL_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->CL_Ogre->BulletListener->Clear_Debug_Render();
				App->CL_Ogre->BulletListener->Render_Debug_Flag = 1;

			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTPLAYEROUTLINE)
		{
			if (App->CL_Properties->Show_Player_Physics_Debug == 1)
			{
				App->CL_Properties->Show_Player_Physics_Debug = 0;

				int f = App->CL_Scene->B_Player[0]->Phys_Body->getCollisionFlags();
				App->CL_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f | (1 << 5)); // Off

				App->CL_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->CL_Ogre->BulletListener->Clear_Debug_Render();
				App->CL_Ogre->BulletListener->Render_Debug_Flag = 1;
			}
			else
			{
				App->CL_Properties->Show_Player_Physics_Debug = 1;

				int f = App->CL_Scene->B_Player[0]->Phys_Body->getCollisionFlags();
				App->CL_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f & (~(1 << 5))); // on

				App->CL_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->CL_Ogre->BulletListener->Clear_Debug_Render();
				App->CL_Ogre->BulletListener->Render_Debug_Flag = 1;

			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_PHYSICS)
		{
			App->CL_Ogre->OgreListener->GD_Run_Physics = 1;
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	}
	return FALSE;
}
