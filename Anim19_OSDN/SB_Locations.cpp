/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "resource.h"
#include "GD19_App.h"
#include "SB_Locations.h"

SB_Locations::SB_Locations(void)
{
	Locations_Dlg_hWnd = nullptr;

	Toggle_Player_Flag = 0;
	Toggle_FreeCam_Flag = 0;
}

SB_Locations::~SB_Locations(void)
{
}

// *************************************************************************
// *	  				Start_Projection Terry Bernie					   *
// *************************************************************************
void SB_Locations::Start_Locations_Dlg()
{
	Toggle_Player_Flag = App->SBC_TopTabs->Toggle_FirstCam_Flag;
	Toggle_FreeCam_Flag = App->SBC_TopTabs->Toggle_FreeCam_Flag;

	Locations_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_PROJECTION, App->Fdlg, (DLGPROC)Locations_Proc);
}
// *************************************************************************
// *					Projection_Proc Terry Bernie		 			   *
// *************************************************************************
LRESULT CALLBACK SB_Locations::Locations_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->Cl_Dialogs->ListBox_Index = 0;
		SendDlgItemMessage(hDlg, IDC_STBANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		//App->Cl_World->Store_Location();

		SendDlgItemMessage(hDlg, IDC_CKMOVECAM, WM_SETFONT, (WPARAM)App->Font_CB12, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_LOC_PLAYER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_LOC_FREECAM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BT_LOC_PLAYERTOCAMERA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		SendDlgItemMessage(hDlg, IDC_CKMOVECAM, BM_SETCHECK, 1, 0);

		int Count = 0;
		while (Count < App->SBC_Scene->Player_Location_Count)
		{
			if (App->SBC_Scene->B_Locations[Count]->Deleted == 0)
			{
				SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)App->SBC_Scene->B_Locations[Count]->Name);
			}
			Count++;
		}

		SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STBANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		if (GetDlgItem(hDlg, IDC_CKMOVECAM) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BTSAVE_LOCATION_PLAYER && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTMOVE_PLAYER && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTEDITT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTDELETE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDCANCEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		//----------------------------------- 
		if (some_item->idFrom == IDC_BT_LOC_PLAYER && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Locations->Toggle_Player_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_LOC_FREECAM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Locations->Toggle_FreeCam_Flag);
			return CDRF_DODEFAULT;
		}
		
		if (some_item->idFrom == IDC_BT_LOC_PLAYERTOCAMERA && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}
		
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		// --------------------- 1st Player
		if (LOWORD(wParam) == IDC_BT_LOC_PLAYER)
		{
			if (App->SBC_Scene->Player_Added == 1)
			{
				App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;
				App->SBC_TopTabs->Toggle_FirstCam_Flag = 1;
				App->SBC_TopTabs->Toggle_FreeCam_Flag = 0;

				App->SBC_Locations->Toggle_Player_Flag = 1;
				App->SBC_Locations->Toggle_FreeCam_Flag = 0;

				App->SBC_Scene->B_Player[0]->Player_Node->setVisible(false);

				int f = App->SBC_Scene->B_Player[0]->Phys_Body->getCollisionFlags();
				App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f | (1 << 5));

				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->Cl19_Ogre->RenderFrame();
				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 1;

				App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;

				RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				RedrawWindow(App->SBC_Locations->Locations_Dlg_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				EnableWindow(GetDlgItem(hDlg, IDC_BT_LOC_PLAYERTOCAMERA), 0);
			}

			return TRUE;

		}

		// --------------------- FreeCam
		if (LOWORD(wParam) == IDC_BT_LOC_FREECAM)
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;
				App->SBC_TopTabs->Toggle_FirstCam_Flag = 0;
				App->SBC_TopTabs->Toggle_FreeCam_Flag = 1;

				App->SBC_Locations->Toggle_FreeCam_Flag = 1;
				App->SBC_Locations->Toggle_Player_Flag = 0;

				int f = App->SBC_Scene->B_Player[0]->Phys_Body->getCollisionFlags();
				App->SBC_Scene->B_Player[0]->Phys_Body->setCollisionFlags(f & (~(1 << 5)));

				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 0;
				App->Cl19_Ogre->RenderFrame();
				App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 1;

				RedrawWindow(App->SBC_TopTabs->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
				RedrawWindow(App->SBC_Locations->Locations_Dlg_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				EnableWindow(GetDlgItem(hDlg, IDC_BT_LOC_PLAYERTOCAMERA), 1);
				
			}

			return TRUE;
		}

		// --------------------- Player To Camera
		if (LOWORD(wParam) == IDC_BT_LOC_PLAYERTOCAMERA)
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				Debug
			}

			return TRUE;
		}
		
		// --------------------- Rename
		if (LOWORD(wParam) == IDC_BTEDITT)
		{
			int Index = App->Cl_Dialogs->ListBox_Index;
			if (Index == 0)
			{
				App->Say("Start Location can not be Edited");
				return 1;
			}

			char buff[255];
			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_GETTEXT, (WPARAM)Index, (LPARAM)(LPCTSTR)buff);

			int Location_Index = App->Cl_LookUps->Player_Location_GetIndex_ByName(buff); // Get by Referance (Name)

			strcpy(App->Cl_Dialogs->btext, "Location Name");

			char numbuf[255];
			_itoa(App->SBC_Scene->Player_Location_Count, numbuf, 10);

			strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Scene->B_Locations[Location_Index]->Name);

			App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Locatoins, 1);

			if (App->Cl_Dialogs->Canceled == 1)
			{
				return TRUE;
			}


			strcpy(App->SBC_Scene->B_Locations[Location_Index]->Name, App->Cl_Dialogs->Chr_Text);

			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
			int Count = 0;
			while (Count < App->SBC_Scene->Player_Location_Count)
			{

				if (App->SBC_Scene->B_Locations[Count]->Deleted == 0)
				{
					SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)App->SBC_Scene->B_Locations[Count]->Name);
				}

				Count++;
			}

			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_SETCURSEL, (WPARAM)Index, (LPARAM)(LPCTSTR)0);
			return TRUE;
		}

		// Delete Location
		if (LOWORD(wParam) == IDC_BTDELETE)
		{

			int Index = App->Cl_Dialogs->ListBox_Index;
			if (Index == 0)
			{
				App->Say("Start Location can not be deleted");
				return 1;
			}

			char buff[255];
			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_GETTEXT, (WPARAM)Index, (LPARAM)(LPCTSTR)buff);

			int Location_Index = App->Cl_LookUps->Player_Location_GetIndex_ByName(buff); // Get by Referance (Name)

			char tag[255];
			strcpy(tag, "Delete Location  ");
			strcat(tag, App->SBC_Scene->B_Locations[Location_Index]->Name);

			App->SBC_Dialogs->YesNo(tag, "Are you sure", 1);
			if (App->Cl_Dialogs->Canceled == 0)
			{
				App->SBC_Scene->B_Locations[Location_Index]->Deleted = 1;
				SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
				int Count = 0;
				while (Count < App->SBC_Scene->Player_Location_Count)
				{
					if (App->SBC_Scene->B_Locations[Count]->Deleted == 0)
					{
						SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)App->SBC_Scene->B_Locations[Count]->Name);
					}

					Count++;
				}
			}

			//SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_SETCURSEL, (WPARAM)0, (LPARAM)(LPCTSTR)0);
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_BTMOVE_PLAYER)
		{
			int Index = App->Cl_Dialogs->ListBox_Index;
			char buff[255];
			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_GETTEXT, (WPARAM)Index, (LPARAM)(LPCTSTR)buff);

			int Location_Index = App->Cl_LookUps->Player_Location_GetIndex_ByName(buff); // Get by Referance (Name)

			if (Location_Index > -1)
			{
				App->SBC_Player->Goto_Location(Location_Index);

				HWND temp = GetDlgItem(hDlg, IDC_CKMOVECAM);
				int test = SendMessage(temp, BM_GETCHECK, 0, 0);
				if (test == BST_CHECKED)
				{
					App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;
					Root::getSingletonPtr()->renderOneFrame();
					Root::getSingletonPtr()->renderOneFrame();
					App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;
				}
			}
			else
			{
				App->Say("Cant Find Location");
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTSAVE_LOCATION_PLAYER)
		{
			strcpy(App->Cl_Dialogs->btext, "Location Name");

			char buf[255];
			char numbuf[255];
			_itoa(App->SBC_Scene->Player_Location_Count, numbuf, 10);

			strcpy(buf, "New_Location_");
			strcat(buf, numbuf);
			strcpy(App->Cl_Dialogs->Chr_Text, buf);

			App->Cl_Dialogs->Dialog_Text(1, 1);

			if (App->Cl_Dialogs->Canceled == 1)
			{
				return TRUE;
			}

			strcpy(buf, App->Cl_Dialogs->Chr_Text);
			App->SBC_Player->Save_Location(buf);

			SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_ADDSTRING, (WPARAM)0, (LPARAM)(LPCTSTR)buf);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_LSTLOCATIONS)
		{
			int Index = 0;

			Index = SendDlgItemMessage(hDlg, IDC_LSTLOCATIONS, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			if (Index == -1)
			{
				return 1;
			}

			App->Cl_Dialogs->ListBox_Index = Index;

			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			//App->Cl_Dialogs->Location_Dlg_Active = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;
	}
	return FALSE;
}
