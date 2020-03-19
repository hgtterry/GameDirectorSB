/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan B.Parkin H.C.Flanigan

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
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Properties.h"

GD19_Properties::GD19_Properties(void)
{
	Current_Selected_Object = 0;

	Properties_Dlg_hWnd = NULL;
	Properties_hLV = NULL;

	btext[0] = 0;

	Edit_Category = Enums::Edit_Mesh_Object;
	Edit_Physics = 0;

	ToggleObjectDebug = 0;
	Object_Selection = 1;
	Physics_Selection = 0;
	Is_Player = 0;

	Properties_Dlg_Active = 0;

}

GD19_Properties::~GD19_Properties(void)
{
}

// *************************************************************************
// *					Start_GD_Properties Terry Bernie   		 	 	   *
// *************************************************************************
void GD19_Properties::Start_GD_Properties(void)
{
	if (Properties_Dlg_Active == 1)
	{
		return;
	}

	Properties_Dlg_Active = 1;
	HMENU mMenu = GetMenu(App->MainHwnd);
///	CheckMenuItem(mMenu, ID_WINDOW_SHOWMODELGLBAL, MF_BYCOMMAND | MF_CHECKED);

	Properties_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_GD_PROPERTIES, App->Fdlg, (DLGPROC)GD_Properties_Proc);
	ShowWindow(Properties_Dlg_hWnd, 1);

	Create_Properties_hLV();
	//Set_DataView();

}
// *************************************************************************
// *					GD_Properties_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK GD19_Properties::GD_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		// all
		SendDlgItemMessage(hDlg, IDC_STOBJECTNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		/*SendDlgItemMessage(hDlg, IDC_STTRANSFORM, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STVALUE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STITEM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		HWND Temp = GetDlgItem(hDlg, IDC_BTHELP);
		SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_InfoSmall_Bmp);

		Temp = GetDlgItem(hDlg, IDC_BTHELPENTITY);
		SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_InfoSmall_Bmp);*/

		App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;

		return 1;
	}

	case WM_CTLCOLORSTATIC:
	{
		/// all
		//if (GetDlgItem(hDlg, IDC_STVALUE) == (HWND)lParam)
		//{
		//	SetBkColor((HDC)wParam, RGB(0, 255, 0));
		//	SetTextColor((HDC)wParam, RGB(0, 0, 0));
		//	SetBkMode((HDC)wParam, TRANSPARENT);
		//	return (UINT)App->DialogBackGround;
		//}
		//if (GetDlgItem(hDlg, IDC_STITEM) == (HWND)lParam)
		//{
		//	SetBkColor((HDC)wParam, RGB(0, 255, 0));
		//	SetTextColor((HDC)wParam, RGB(0, 0, 0));
		//	SetBkMode((HDC)wParam, TRANSPARENT);
		//	return (UINT)App->DialogBackGround;
		//}
		if (GetDlgItem(hDlg, IDC_STOBJECTNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->DialogBackGround;
		}
		//--------------------------------------------
		if (GetDlgItem(hDlg, IDC_STP1) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STP2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STP3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		//--------------------------------------------
		if (GetDlgItem(hDlg, IDC_STR1) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STR2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STR3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		//--------------------------------------------
		if (GetDlgItem(hDlg, IDC_STS1) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STS2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STS3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		////--------------------------------------------
		//if (GetDlgItem(hDlg, IDC_STTRANSFORM) == (HWND)lParam)
		//{
		//	SetBkColor((HDC)wParam, RGB(0, 255, 0));
		//	SetTextColor((HDC)wParam, RGB(0, 0, 255));
		//	SetBkMode((HDC)wParam, TRANSPARENT);
		//	return (UINT)App->DialogBackGround;
		//}

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->DialogBackGround;
	}

	case WM_CLOSE:
	{
		App->Cl_Properties->Properties_Dlg_Active = 0;
		ShowWindow(App->Cl_Properties->Properties_Dlg_hWnd, 0);

		HMENU mMenu = GetMenu(App->MainHwnd);
		///CheckMenuItem(mMenu, ID_WINDOW_SHOWMODELGLBAL, MF_BYCOMMAND | MF_UNCHECKED);

		break;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

	/////	if (some_item->idFrom == IDC_BTTEST && some_item->code == NM_CUSTOMDRAW)
	//	{
	//		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
	//		App->Custom_Button_Normal(item);
	//		return CDRF_DODEFAULT;
	//	}
	//	// ------------------------------------------ 
	/////	if (some_item->idFrom == IDC_BUTTRANSFORM && some_item->code == NM_CUSTOMDRAW)
	//	{
	//		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
	//		App->Custom_Button_Normal(item);
	//		return CDRF_DODEFAULT;
	//	}
	//	// ------------------------------------------ 
	/////	if (some_item->idFrom == IDC_BUTEDITPOS && some_item->code == NM_CUSTOMDRAW)
	//	{
	//		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
	//		App->Custom_Button_Normal(item);
	//		return CDRF_DODEFAULT;
	//	}

	/////	if (some_item->idFrom == IDC_BUTEDITROT && some_item->code == NM_CUSTOMDRAW)
	//	{
	//		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
	//		App->Custom_Button_Normal(item);
	//		return CDRF_DODEFAULT;
	//	}

	/////	if (some_item->idFrom == IDC_BUTEDITSCALE && some_item->code == NM_CUSTOMDRAW)
	//	{
	//		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
	//		App->Custom_Button_Normal(item);
	//		return CDRF_DODEFAULT;
	//	}

		if (some_item->idFrom == IDC_BTLOOKAT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_INFODETAILS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}
		
	//	// ------------------------------------------ 
	/////	if (some_item->idFrom == IDC_OBJECT_SEL && some_item->code == NM_CUSTOMDRAW)
	//	{
	//		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
	//		App->Custom_Button_Toggle(item, App->Cl_Object_Props->Object_Selection);
	//		return CDRF_DODEFAULT;
	//	}

	/////	if (some_item->idFrom == IDC_PHYSICS_SEL && some_item->code == NM_CUSTOMDRAW)
	//	{
	//		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
	//		App->Custom_Button_Toggle(item, App->Cl_Object_Props->Physics_Selection);
	//		return CDRF_DODEFAULT;
	//	}

		if (some_item->idFrom == IDC_PHYSICSDEBUG && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_Object_Props->ToggleObjectDebug);
			return CDRF_DODEFAULT;
		}
		if (some_item->idFrom == IDC_BUTDIMENSIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_ImGui->Show_ImGui_Dimensions);
			return CDRF_DODEFAULT;
		}

		if (some_item->hwndFrom == App->Cl_Properties->Properties_hLV)
		{
			switch (some_item->code)
			{
			case NM_CLICK:
			{
				App->Cl_Properties->ListView_OnClickOptions(lParam);
			}
			}
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		
//	//	if (LOWORD(wParam) == IDC_BTHELP)
//		{
//			App->Cl_Utilities->OpenHTML("Help\\PropertiesPanel.html");
//			return 1;
//		}
//
//	//	if (LOWORD(wParam) == IDC_BTDELETE)
//		{ 
//			int Index = App->Cl_Properties->Current_Selected_Object;
//			bool Result = App->Cl_LookUps->Check_Usage(Index);
//
//			if (Result == 0)
//			{
//				App->Say("Used by another Entity");
//
//				App->Cl_Dialogs->YesNo("Permanently Delete", App->Cl_Scene_Data->Cl_Object[Index]->Name);
//
//				if (App->Cl_Dialogs->Canceled == 0)
//				{
//					App->Cl_Scene_Data->Cl_Object[Index]->Deleted = 1;
//					App->Cl_Scene_Data->Delete_Object(Index);
//					App->Cl_FileView->DeleteItem();
//				}
//			}
//			else
//			{
//				App->Cl_Dialogs->YesNo("Permanently Object", App->Cl_Scene_Data->Cl_Object[Index]->Name);
//
//				if (App->Cl_Dialogs->Canceled == 0)
//				{
//					App->Cl_Scene_Data->Cl_Object[Index]->Deleted = 1;
//					App->Cl_Scene_Data->Delete_Object(Index);
//					App->Cl_FileView->DeleteItem();
//				}
//			}
//			
//			return 1;
//		}
//
//	//	if (LOWORD(wParam) == IDC_BTTEST)
//		{
//			int Index = App->Cl_Properties->Current_Selected_Object;
//			App->Cl_Scene_Data->Reset_Triggers();
//			App->Cl_Collision->Move_Entity(Index);
//			return 1;
//		}
//
		if (LOWORD(wParam) == IDC_BTLOOKAT)
		{

			App->Cl_ToolBar->FreeCam_Active = 1;
			App->Cl_ToolBar->FirstPerson_Active = 0;
			App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;

			RedrawWindow(App->Cl_ToolBar->TB_1, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

			int Index = App->Cl_Properties->Current_Selected_Object;
			Ogre::Vector3 Centre = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->getAttachedObject(0)->getBoundingBox().getCenter();
			Ogre::Vector3 WS = App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->convertLocalToWorldPosition(Centre);
			App->Cl19_Ogre->mCamera->setPosition(WS);

			return 1;
		}

	
		if (LOWORD(wParam) == IDC_INFODETAILS)
		{

			if (App->Cl_ImGui->Show_Object_Data == 1)
			{
				App->Cl_ImGui->Show_Object_Data = 0;
			}
			else
			{
				App->Cl_ImGui->Update_StaticData();
				App->Cl_ImGui->Show_Object_Data = 1;
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_BUTDIMENSIONS)
		{

			if (App->Cl_ImGui->Show_ImGui_Dimensions == 1)
			{
				App->Cl_ImGui->Show_ImGui_Dimensions = 0;
			}
			else
			{
				App->Cl_ImGui->Show_ImGui_Dimensions = 1;
			}
			
			return 1;
		}

		
//
//	///	if (LOWORD(wParam) == IDC_BUTEDITPOS)
//		{
//			App->Cl_Dimensions->Start_Postion();
//			return 1;
//		}
//
//	///	if (LOWORD(wParam) == IDC_BUTEDITROT)
//		{
//			App->Cl_Dimensions->Start_Rotation_Dlg();
//			return 1;
//		}
//
//	///	if (LOWORD(wParam) == IDC_BUTEDITSCALE)
//		{
//			App->Cl_Dimensions->Start_Scale_Dlg();
//			return 1;
//		}
//
//	///	if (LOWORD(wParam) == IDC_BUTTRANSFORM)
//		{
//			// wheres the but
//			return 1;
//		}
//
/////		if (LOWORD(wParam) == IDC_OBJECT_SEL)
//		{
//			App->Cl_Object_Props->Object_Selection = 1;
//			App->Cl_Object_Props->Physics_Selection = 0;
//			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
//
//			App->Cl_Properties->Edit_Physics = 0;
//
//			if (App->Cl_Object_Props->Is_Player == 0)
//			{
//				// Sounds
//				if (App->Cl_Properties->Edit_Category == Enums::Edit_Sounds)
//				{
//					App->Cl_Properties->Update_ListView_Sounds();
//					return 1;
//				}
//				if (App->Cl_Properties->Edit_Category == Enums::Edit_Message)
//				{
//					App->Cl_Properties->Update_ListView_Messages();
//					return 1;
//				}
//				if (App->Cl_Properties->Edit_Category == Enums::Edit_Move_Entity)
//				{
//					App->Cl_Properties->Update_ListView_Move_Entities();
//					return 1;
//				}
//				if (App->Cl_Properties->Edit_Category == Enums::Edit_Collectable)
//				{
//					App->Cl_Properties->Update_ListView_Collectables();
//					return 1;
//				}
//
//				App->Cl_Properties->Update_ListView_Objects();
//			}
//			else
//			{
//				App->Cl_Properties->Update_ListView_Player();
//			}
//			return 1;
//		}
//
/////		if (LOWORD(wParam) == IDC_PHYSICS_SEL)
//		{
//			App->Cl_Object_Props->Object_Selection = 0;
//			App->Cl_Object_Props->Physics_Selection = 1;
//			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
//
//			App->Cl_Properties->Edit_Physics = 1;
//
//			if (App->Cl_Object_Props->Is_Player == 0)
//			{
//				App->Cl_Properties->Update_ListView_Physics();
//			}
//			else
//			{
//				App->Cl_Properties->Update_ListView_Player_Physics();
//			}
//
//			return 1;
//		}
//
		if (LOWORD(wParam) == IDC_PHYSICSDEBUG)
		{
			/*if (App->Cl19_Ogre->RenderListener->ShowDebug == 1)
			{
				App->Cl19_Ogre->RenderListener->ShowDebug = 0;
				App->Cl_Object_Props->ToggleObjectDebug = 0;
			}
			else
			{
				App->Cl19_Ogre->RenderListener->ShowDebug = 1;
				App->Cl_Object_Props->ToggleObjectDebug = 1;
			}*/

			if (App->Cl_Object_Props->Is_Player == 1)
			{
				int f = App->Cl_Player->mObject->getCollisionFlags();

				if (App->Cl_Player->ShowDebug == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowDebug = 0;
					App->Cl_Object_Props->ToggleObjectDebug = 0;
					App->Cl_Player->ShowDebug = 0;
					App->Cl_Player->mObject->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowDebug = 1;
					App->Cl_Object_Props->ToggleObjectDebug = 1;
					App->Cl_Player->ShowDebug = 1;
					App->Cl_Player->mObject->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
				}
				return 1;
			}
			else
			{
				int Index = App->Cl_Properties->Current_Selected_Object;

				if (App->Cl_Scene_Data->Cl_Object[Index]->Physics_Valid == 1)
				{
					int f = App->Cl_Scene_Data->Cl_Object[Index]->bt_body->getCollisionFlags();

					if (App->Cl_Scene_Data->Cl_Object[Index]->Show_Debug == 1)
					{
						App->Cl19_Ogre->RenderListener->ShowDebug = 0;
						App->Cl_Object_Props->ToggleObjectDebug = 0;
						App->Cl_Scene_Data->Cl_Object[Index]->Show_Debug = 0;
						App->Cl_Scene_Data->Cl_Object[Index]->bt_body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
					}
					else
					{
						App->Cl19_Ogre->RenderListener->ShowDebug = 1;
						App->Cl_Object_Props->ToggleObjectDebug = 1;
						App->Cl_Scene_Data->Cl_Object[Index]->Show_Debug = 1;
						App->Cl_Scene_Data->Cl_Object[Index]->bt_body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
					}
				}

				return 1;
			}

			return 1;
		}

		break;
	}
	}
	return FALSE;
}

// *************************************************************************
// *				Update_Transform_Dlg  Terry Bernie				   *
// *************************************************************************
bool GD19_Properties::Update_Transform_Dlg()
{
	int index = Current_Selected_Object;

	//if (index > 0)
	{
		char chr_PosX[100];
		char chr_PosY[100];
		char chr_PosZ[100];

		sprintf(chr_PosX, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos.x);
		sprintf(chr_PosY, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos.y);
		sprintf(chr_PosZ, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->Mesh_Pos.z);

		SetDlgItemText(Properties_Dlg_hWnd, IDC_STP1, chr_PosX);
		SetDlgItemText(Properties_Dlg_hWnd, IDC_STP2, chr_PosY);
		SetDlgItemText(Properties_Dlg_hWnd, IDC_STP3, chr_PosZ);


		char chr_RotX[100];
		char chr_RotY[100];
		char chr_RotZ[100];

		sprintf(chr_RotX, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->Mesh_Rot.x);
		sprintf(chr_RotY, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->Mesh_Rot.y);
		sprintf(chr_RotZ, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->Mesh_Rot.z);

		SetDlgItemText(Properties_Dlg_hWnd, IDC_STR1, chr_RotX);
		SetDlgItemText(Properties_Dlg_hWnd, IDC_STR2, chr_RotY);
		SetDlgItemText(Properties_Dlg_hWnd, IDC_STR3, chr_RotZ);

		char chr_ScaleX[100];
		char chr_ScaleY[100];
		char chr_ScaleZ[100];

		sprintf(chr_ScaleX, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale.x);
		sprintf(chr_ScaleY, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale.y);
		sprintf(chr_ScaleZ, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale.z);

		SetDlgItemText(Properties_Dlg_hWnd, IDC_STS1, chr_ScaleX);
		SetDlgItemText(Properties_Dlg_hWnd, IDC_STS2, chr_ScaleY);
		SetDlgItemText(Properties_Dlg_hWnd, IDC_STS3, chr_ScaleZ);
	}

	return 1;
}

// *************************************************************************
// *					Create_Properties_hLV Terry Bernie				   *
// *************************************************************************
void GD19_Properties::Create_Properties_hLV(void)
{
	int NUM_COLS = 2;
	Properties_hLV = CreateWindowEx(0, WC_LISTVIEW, "",
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_VSCROLL | LVS_REPORT | LVS_NOCOLUMNHEADER | LVS_SHOWSELALWAYS, 7, 50,
		230, 240, Properties_Dlg_hWnd, 0, App->hInst, NULL);

	DWORD exStyles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

	ListView_SetExtendedListViewStyleEx(Properties_hLV, exStyles, exStyles);

	ListView_SetBkColor(Properties_hLV, RGB(255, 255, 255));
	ListView_SetTextBkColor(Properties_hLV, RGB(255, 255, 255));

	LV_COLUMN lvC;
	memset(&lvC, 0, sizeof(LV_COLUMN));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	std::string headers[] =
	{
		"", ""
	};
	int headerSize[] =
	{
		100, 120
	};

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_InsertColumn(Properties_hLV, header, &lvC);
	}
	//HFONT Font;
	//Font = CreateFont(-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
	SendMessage(Properties_hLV, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

	//Update_ListView_Objects();
	return;
}

// *************************************************************************
// *			Update_ListView_Objects	Terry Bernie 				 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Objects()
{
	/*if (App->GDCL_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}*/

	int index = App->Cl_Properties->Current_Selected_Object;

	char chr_Scale[100];

	char chr_PosX[100];
	char chr_PosY[100];
	char chr_PosZ[100];

	char chr_RotX[100];
	char chr_RotY[100];
	char chr_RotZ[100];

	char chr_Total[100];

	char Num[255];
	_itoa(index, Num, 10);

	char buff[255];
	strcpy(buff, App->Cl_Scene_Data->Cl_Object[index]->Name);
	strcat(buff, "   (Object) ");
	strcat(buff,Num);
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	sprintf(chr_Scale, "%.3f", "2");//CL_Object[index]->MeshScale.x);

	sprintf(chr_PosX, "%.3f", "2");//CL_Object[index]->MeshPos.x);
	sprintf(chr_PosY, "%.3f", "2");//CL_Object[index]->MeshPos.y);
	sprintf(chr_PosZ, "%.3f", "2");//CL_Object[index]->MeshPos.z);

	sprintf(chr_RotX, "%.3f", "2");//CL_Object[index]->MeshRot.x);
	sprintf(chr_RotY, "%.3f", "2");// CL_Object[index]->MeshRot.y);
	sprintf(chr_RotZ, "%.3f", "2");//CL_Object[index]->MeshRot.z);

	sprintf(chr_Total, "%i", "2");//TotalCollectableCount);


	const int NUM_ITEMS = 3;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name", grid[1][0] = App->Cl_Scene_Data->Cl_Object[index]->Name;
	grid[0][1] = "Mesh File", grid[1][1] = App->Cl_Scene_Data->Cl_Object[index]->MeshName;


	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *			Update_ListView_Sounds()	Terry Bernie 			 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Sounds()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}

	if (App->Cl_Scene_Data->Cl_Object[Current_Selected_Object]->Show_Debug == 1)
	{
		ToggleObjectDebug = 1;
		App->RedrawWindow_Dlg(Properties_Dlg_hWnd);
	}
	else
	{
		ToggleObjectDebug = 0;
		App->RedrawWindow_Dlg(Properties_Dlg_hWnd);
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->Cl_Scene_Data->Cl_Object[index]->Name);
	strcat(buff, "   (Sound)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);


	// new sound
	char chr_Play[100];
	if (App->Cl_Scene_Data->Cl_Object[index]->Play_v2 == 1)
	{
		strcpy(chr_Play, "True");
	}
	else
	{
		strcpy(chr_Play, "False");
	}
	char chr_Stock_Sound[100];
	int sndIndex = App->Cl_Scene_Data->Cl_Object[index]->Sound_ID_v2;
	strcpy(chr_Stock_Sound, App->Cl_Scene_Data->St_Sounds[sndIndex]->Name);

	int StockIndex = App->Cl_Scene_Data->Cl_Object[index]->Entity[0].Stock_mIndex;

	const int NUM_ITEMS = 4;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->Cl_Scene_Data->Cl_Object[index]->Name;
	grid[0][1] = " ",			grid[1][1] = " ";
	grid[0][2] = "Stock_Snd",	grid[1][2] = chr_Stock_Sound;
	grid[0][3] = "Play",		grid[1][3] = chr_Play;

	


	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *			Update_ListView_Collectables()	Terry Bernie 		 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Collectables()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	
	char buff[255];
	strcpy(buff, App->Cl_Scene_Data->Cl_Object[index]->Name);
	strcat(buff, "   (Collectable)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	// new sound
	char chr_Play[100];
	if (App->Cl_Scene_Data->Cl_Object[index]->Play_v2 == 1)
	{
		strcpy(chr_Play, "True");
	}
	else
	{
		strcpy(chr_Play, "False");
	}
	char chr_Stock_Sound[100];
	int sndIndex = App->Cl_Scene_Data->Cl_Object[index]->Sound_ID_v2;
	strcpy(chr_Stock_Sound, App->Cl_Scene_Data->St_Sounds[sndIndex]->Name);

	const int NUM_ITEMS = 5;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->Cl_Scene_Data->Cl_Object[index]->Name;
	grid[0][1] = "Mesh File",	grid[1][1] = App->Cl_Scene_Data->Cl_Object[index]->MeshName;
	grid[0][2] = " ",			grid[1][2] = " ";
	grid[0][3] = "Stock_Snd",	grid[1][3] = chr_Stock_Sound;
	grid[0][4] = "Play",		grid[1][4] = chr_Play;



	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *			Update_ListView_Teleport()	Terry Bernie 		 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Teleport()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->Cl_Scene_Data->Cl_Object[index]->Name);
	strcat(buff, "   (Teleport)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	// new sound
	char chr_Play[100];
	if (App->Cl_Scene_Data->Cl_Object[index]->Play_v2 == 1)
	{
		strcpy(chr_Play, "True");
	}
	else
	{
		strcpy(chr_Play, "False");
	}
	char chr_Stock_Sound[100];
	int sndIndex = App->Cl_Scene_Data->Cl_Object[index]->Sound_ID_v2;
	strcpy(chr_Stock_Sound, App->Cl_Scene_Data->St_Sounds[sndIndex]->Name);

	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->Cl_Scene_Data->Cl_Object[index]->Name;
	grid[0][1] = "Mesh File",	grid[1][1] = App->Cl_Scene_Data->Cl_Object[index]->MeshName;
	grid[0][2] = " ",			grid[1][2] = " ";
	grid[0][3] = "Goto",		grid[1][3] = App->Cl_Scene_Data->Cl_Object[index]->S_Teleport[0]->Name;
	grid[0][4] = " ",			grid[1][4] = " ";
	grid[0][5] = "Stock_Snd",	grid[1][5] = chr_Stock_Sound;
	grid[0][6] = "Play",		grid[1][6] = chr_Play;


	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Update_ListView_Environment	Terry Bernie 		 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Environment()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->Cl_Scene_Data->Cl_Object[index]->Name);
	strcat(buff, "   (Environment)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_Fog[100];
	if (App->Cl_Scene_Data->Cl_Object[index]->S_Environment[0]->FogOn == 1)
	{
		strcpy(chr_Fog, "On");
	}
	else
	{
		strcpy(chr_Fog, "Off");
	}

	// new sound
	char chr_Play[100];
	if (App->Cl_Scene_Data->Cl_Object[index]->Play_v2 == 1)
	{
		strcpy(chr_Play, "True");
	}
	else
	{
		strcpy(chr_Play, "False");
	}
	char chr_Stock_Sound[100];
	int sndIndex = App->Cl_Scene_Data->Cl_Object[index]->Sound_ID_v2;
	strcpy(chr_Stock_Sound, App->Cl_Scene_Data->St_Sounds[sndIndex]->Name);


	const int NUM_ITEMS = 6;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		 grid[1][0] = App->Cl_Scene_Data->Cl_Object[index]->Name;
	grid[0][1] = " ",			 grid[1][1] = " ";
	grid[0][2] = "Fog",			 grid[1][2] = chr_Fog;
	grid[0][3] = " ",			 grid[1][3] = " ";
	grid[0][4] = "Stock_Snd",	 grid[1][4] = chr_Stock_Sound;
	grid[0][5] = "Play",		 grid[1][5] = chr_Play;

	
	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Update_ListView_Particles	Terry Bernie 		 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Particles()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	char chr_Speed[100];
	sprintf(chr_Speed, "%.3f", App->Cl_Scene_Data->Cl_Object[index]->Ogre_Particle->getSpeedFactor());

	char chr_Scale[100];
	sprintf(chr_Scale, "%.3f", App->Cl_Scene_Data->Cl_Object[index]->Mesh_Scale.x);

	const int NUM_ITEMS = 6;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->Cl_Scene_Data->Cl_Object[index]->Name;
	grid[0][1] = " ",			grid[1][1] = " ";
	grid[0][2] = "Particle",	grid[1][2] = App->Cl_Scene_Data->Cl_Object[index]->MeshName;
	grid[0][3] = " ",			grid[1][3] = " ";
	grid[0][4] = "Scale",		grid[1][4] = chr_Scale;
	grid[0][5] = "Speed",		grid[1][5] = chr_Speed;


	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}
	
	return 1;
}

// *************************************************************************
// *			Update_ListView_Mesages	Terry Bernie 				 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Messages()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}

	if (App->Cl_Scene_Data->Cl_Object[Current_Selected_Object]->Show_Debug == 1)
	{
		ToggleObjectDebug = 1;
		App->RedrawWindow_Dlg(Properties_Dlg_hWnd);
	}
	else
	{
		ToggleObjectDebug = 0;
		App->RedrawWindow_Dlg(Properties_Dlg_hWnd);
	}


	int index = App->Cl_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->Cl_Scene_Data->Cl_Object[index]->Name);
	strcat(buff, "   (Message)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_ReTrigger[100];

	int StockIndex = App->Cl_Scene_Data->Cl_Object[index]->Entity[0].Stock_mIndex;
	sprintf(chr_ReTrigger, "%i ", App->Cl_Scene_Data->Cl_Object[index]->Re_Trigger);

	char chr_FontSize[100];
	char chr_TextColour[100];
	char chr_PosVert[100];
	char chr_PosHoz[100];

	sprintf(chr_FontSize, "%i ", App->Cl_Scene_Data->S_Messages[StockIndex]->Font_Size);
	sprintf(chr_TextColour, "%.2f %.2f %.2f", App->Cl_Scene_Data->S_Messages[StockIndex]->Colour.x, App->Cl_Scene_Data->S_Messages[StockIndex]->Colour.y, App->Cl_Scene_Data->S_Messages[StockIndex]->Colour.z);
	sprintf(chr_PosVert, "%.2f ", App->Cl_Scene_Data->S_Messages[StockIndex]->Pos_Vert);
	sprintf(chr_PosHoz, "%.2f ", App->Cl_Scene_Data->S_Messages[StockIndex]->Pos_Hoz);

	// new sound
	char chr_Play[100];
	if (App->Cl_Scene_Data->Cl_Object[index]->Play_v2 == 1)
	{
		strcpy(chr_Play, "True");
	}
	else
	{
		strcpy(chr_Play, "False");
	}
	char chr_Stock_Sound[100];
	int sndIndex = App->Cl_Scene_Data->Cl_Object[index]->Sound_ID_v2;
	strcpy(chr_Stock_Sound, App->Cl_Scene_Data->St_Sounds[sndIndex]->Name);

	const int NUM_ITEMS = 14;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",			grid[1][0] = App->Cl_Scene_Data->Cl_Object[index]->Name;
	grid[0][1] = " ",				grid[1][1] = " ";
	grid[0][2] = "Message",			grid[1][2] = App->Cl_Scene_Data->Cl_Object[index]->Entity[0].mTextItem;
	grid[0][3] = "Message_Stock",	grid[1][3] = App->Cl_Panels_Com->Get_Panel_Name(StockIndex);//App->GDCL_Scene_Data->S_Messages[StockIndex]->Name;
	grid[0][4] = " ",				grid[1][4] = " "; 
	grid[0][5] = "Font Size",		grid[1][5] = chr_FontSize;
	grid[0][6] = "Text Colour",		grid[1][6] = chr_TextColour;
	grid[0][7] = "Pos Vertical",	grid[1][7] = chr_PosVert;
	grid[0][8] = "Pos Horizontal",	grid[1][8] = chr_PosHoz;
	grid[0][9] = " ",				grid[1][9] = " ";
	grid[0][10] = "Re-Trigger",		grid[1][10] = chr_ReTrigger;
	grid[0][11] = " ",				grid[1][11] = " ";
	grid[0][12] = "Stock_Snd",		grid[1][12] = chr_Stock_Sound;
	grid[0][13] = "Play",			grid[1][13] = chr_Play;


	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *			Update_ListView_Move_Entities	Terry Bernie 		 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Move_Entities()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}

	if (App->Cl_Scene_Data->Cl_Object[Current_Selected_Object]->Show_Debug == 1)
	{
		ToggleObjectDebug = 1;
		App->RedrawWindow_Dlg(Properties_Dlg_hWnd);
	}
	else
	{
		ToggleObjectDebug = 0;
		App->RedrawWindow_Dlg(Properties_Dlg_hWnd);
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->Cl_Scene_Data->Cl_Object[index]->Name);
	strcat(buff, "   (Mover)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_Distance[100];
	sprintf(chr_Distance, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->S_MoveType->Distance);

	char chr_Speed[100];
	sprintf(chr_Speed, "%.3f ", App->Cl_Scene_Data->Cl_Object[index]->S_MoveType->Speed);

	char chr_Axis[100];
	if (App->Cl_Scene_Data->Cl_Object[index]->S_MoveType->WhatDirection == Enums::Axis_x)
	{
		strcpy(chr_Axis, "X");
	}
	if (App->Cl_Scene_Data->Cl_Object[index]->S_MoveType->WhatDirection == Enums::Axis_y)
	{
		strcpy(chr_Axis, "Y");
	}
	if (App->Cl_Scene_Data->Cl_Object[index]->S_MoveType->WhatDirection == Enums::Axis_z)
	{
		strcpy(chr_Axis, "Z");
	}

	// new sound
	char chr_Play[100];
	if (App->Cl_Scene_Data->Cl_Object[index]->Play_v2 == 1)
	{
		strcpy(chr_Play, "True");
	}
	else
	{
		strcpy(chr_Play, "False");
	}
	char chr_Stock_Sound[100];
	int sndIndex = App->Cl_Scene_Data->Cl_Object[index]->Sound_ID_v2;
	strcpy(chr_Stock_Sound, App->Cl_Scene_Data->St_Sounds[sndIndex]->Name);

	const int NUM_ITEMS = 9;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->Cl_Scene_Data->Cl_Object[index]->Name;
	grid[0][1] = " ",			grid[1][1] = " ";
	grid[0][2] = "Object",		grid[1][2] = App->Cl_Scene_Data->Cl_Object[index]->S_MoveType->Object_Name;
	grid[0][3] = "Axis",		grid[1][3] = chr_Axis;
	grid[0][4] = "Distance",	grid[1][4] = chr_Distance;
	grid[0][5] = "Speed",		grid[1][5] = chr_Speed;
	grid[0][6] = " ",			grid[1][6] = " ";
	grid[0][7] = "Stock_Snd",	grid[1][7] = chr_Stock_Sound;
	grid[0][8] = "Play",		grid[1][8] = chr_Play;


	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *			Update_ListView_Physics	Terry Bernie 				 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Physics()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}

	int Index = Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->Cl_Scene_Data->Cl_Object[Current_Selected_Object]->Name);
	strcat(buff, "   (Physics)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_PhysicsType[100];
	char chr_PhysicsShape[100];

	switch (App->Cl_Scene_Data->Cl_Object[Index]->Type)
	{
	case 1: strcpy(chr_PhysicsType, "Dynamic");
		break;
	case 2: strcpy(chr_PhysicsType, "Static");;
		break;
	}

	switch (App->Cl_Scene_Data->Cl_Object[Index]->Shape)
	{
	case 0: strcpy(chr_PhysicsShape, "None");
		break;
	case 1: strcpy(chr_PhysicsShape, "Box");
		break;
	case 2: strcpy(chr_PhysicsShape, "Sphere");
		break;
	case 3: strcpy(chr_PhysicsShape, "Capsule");
		break;
	case 4: strcpy(chr_PhysicsShape, "Cylinder");
		break;
	case 5: strcpy(chr_PhysicsShape, "Cone");
		break;
	case 6: strcpy(chr_PhysicsShape, "Tri_Mesh");
		break;
	}


	const int NUM_ITEMS = 4;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name", grid[1][0] = App->Cl_Scene_Data->Cl_Object[Index]->Name;
	grid[0][1] = "Type", grid[1][1] = chr_PhysicsType;
	grid[0][2] = "Shape", grid[1][2] = chr_PhysicsShape;

	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Update_ListView_Player	Terry Bernie 			 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Player()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->Cl_Player->PlayerName);
	strcat(buff, "   (Player)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);


	char chr_Speed[100];
	char chr_Height[100];
	char chr_StartPosX[100];
	char chr_StartPosY[100];
	char chr_StartPosZ[100];

	sprintf(chr_Speed, "%.3f ", App->Cl_Player->Ground_speed);
	sprintf(chr_Height, "%.3f ", App->Cl_Player->PlayerHeight);

	sprintf(chr_StartPosX, "%.3f ", App->Cl_Player->StartPos.x);
	sprintf(chr_StartPosY, "%.3f ", App->Cl_Player->StartPos.y);
	sprintf(chr_StartPosZ, "%.3f ", App->Cl_Player->StartPos.z);

	const int NUM_ITEMS = 9;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",			grid[1][0] = App->Cl_Player->PlayerName;
	grid[0][1] = "Mode",			grid[1][1] = "1st_Person";
	grid[0][2] = " ",				grid[1][2] = " ";
	grid[0][3] = "Ground Speed",	grid[1][3] = chr_Speed;
	grid[0][4] = "Player Height",	grid[1][4] = chr_Height;
	grid[0][5] = " ",				grid[1][5] = " ";
	grid[0][6] = "Start Pos_X",		grid[1][6] = chr_StartPosX;
	grid[0][7] = "Start Pos_Y",		grid[1][7] = chr_StartPosY;
	grid[0][8] = "Start Pos_Z",		grid[1][8] = chr_StartPosZ;


	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Update_ListView_Player_Physics	Terry Berni		 	   *
// *************************************************************************
bool GD19_Properties::Update_ListView_Player_Physics()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		return 1;
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->Cl_Player->PlayerName);
	strcat(buff, "   (Physics)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_PhysicsType[100];
	strcpy(chr_PhysicsType, "Dynamic");

	char chr_PhysicsShape[100];
	strcpy(chr_PhysicsShape, "Capsule");

	char chr_Mass[100];
	char chr_Radius[100];
	char chr_Height[100];

	sprintf(chr_Mass, "%.3f ", App->Cl_Player->Capsule_Mass);
	//sprintf(chr_Mass,"%.3f ",App->GDCL_Player->mObject->getGravity().getY());
	sprintf(chr_Radius, "%.3f ", App->Cl_Player->Capsule_Radius);
	sprintf(chr_Height, "%.3f ", App->Cl_Player->Capsule_Height);


	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->Cl_Player->PlayerName;
	grid[0][1] = "Type",		grid[1][1] = chr_PhysicsType;
	grid[0][2] = "Shape ",		grid[1][2] = chr_PhysicsShape;
	grid[0][3] = " ",			grid[1][3] = " ";
	grid[0][4] = "Mass",		grid[1][4] = chr_Mass;
	grid[0][5] = "Radius",		grid[1][5] = chr_Radius;
	grid[0][6] = "Height",		grid[1][6] = chr_Height;

	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}
// *************************************************************************
// *			ListView_OnClickOptions  Terry Bernie			 		   *
// *************************************************************************
void GD19_Properties::ListView_OnClickOptions(LPARAM lParam)
{
	// Teleport
	if (App->Cl_Properties->Edit_Category == Enums::Edit_Teleport)
	{
		if (Edit_Physics == 0)
		{
			Edit_Teleport_OnClick(lParam);
		}
		else
		{
			Edit_Player_Physics_Onclick(lParam);
		}

		return;
	}

	// Player
	if (App->Cl_Properties->Edit_Category == Enums::Edit_Player)
	{
		if (Edit_Physics == 0)
		{
			Edit_Player_Onclick(lParam);
		}
		else
		{
			Edit_Player_Physics_Onclick(lParam);
		}

		return;
	}

	// Object
	if (App->Cl_Properties->Edit_Category == Enums::Edit_Mesh_Object)
	{
		if (Edit_Physics == 0)
		{
			Edit_Object_OnClick(lParam);
		}
		else
		{
			ListView_Object_Physics_OnClick(lParam);
		}

		return;
	}

	// Sounds
	if (App->Cl_Properties->Edit_Category == Enums::Edit_Sounds)
	{
		if (Edit_Physics == 0)
		{
			Edit_Sounds_OnClick(lParam);
		}
		else
		{
			ListView_Object_Physics_OnClick(lParam);
		}

		return;
	}

	// Messages
	if (App->Cl_Properties->Edit_Category == Enums::Edit_Message)
	{
		if (Edit_Physics == 0)
		{
			Edit_Messages_OnClick(lParam);
		}
		else
		{
			ListView_Object_Physics_OnClick(lParam);
		}

		return;
	}

	// Move Entities
	if (App->Cl_Properties->Edit_Category == Enums::Edit_Move_Entity)
	{
		if (Edit_Physics == 0)
		{
			Edit_Move_Entity_OnClick(lParam);
		}
		else
		{
			ListView_Object_Physics_OnClick(lParam);
		}

		return;
	}

	// Collectables
	if (App->Cl_Properties->Edit_Category == Enums::Edit_Collectable)
	{
		if (Edit_Physics == 0)
		{
			Edit_Collectables_OnClick(lParam);
		}
		else
		{
			ListView_Object_Physics_OnClick(lParam);
		}

		return;
	}

	// Collectables
	if (App->Cl_Properties->Edit_Category == Enums::Edit_Particles)
	{
		if (Edit_Physics == 0)
		{
			Edit_Particles_OnClick(lParam);
		}
		else
		{
			ListView_Object_Physics_OnClick(lParam);
		}

		return;
	}

	return;
}

// *************************************************************************
// *				Edit_Object_OnClick  Terry Bernie				   *
// *************************************************************************
bool GD19_Properties::Edit_Object_OnClick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->Cl_Object[Index]->Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Name, App->Cl_Dialogs->Chr_Text);

		App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Objects();
	}

	return 1;
}

// *************************************************************************
// *				Edit_Player_Onclick  Terry Bernie					   *
// *************************************************************************
bool GD19_Properties::Edit_Player_Onclick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);
	
	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Player->PlayerName);

		App->Cl_Dialogs->Dialog_Text(1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		// Needs Duplicate Name test 
		strcpy(App->Cl_Player->PlayerName, App->Cl_Dialogs->Chr_Text);

		App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Player();
	}

	result = strcmp(btext, "Ground Speed");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->Cl_Player->Ground_speed);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Ground Speed");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->Cl_Player->Ground_speed = App->Cl_Dialogs->mFloat;
		Update_ListView_Player();

		return 1;
	}

	result = strcmp(btext, "Player Height");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->Cl_Player->PlayerHeight);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Height");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->Cl_Player->PlayerHeight = App->Cl_Dialogs->mFloat;
		Update_ListView_Player();
		return 1;
	}

	result = strcmp(btext, "Start Pos_X");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->Cl_Player->StartPos.x);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos X");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->Cl_Player->StartPos.x = App->Cl_Dialogs->mFloat;
		App->Cl_Scene_Data->S_Player_Locations[0]->Current_Position.x = App->Cl_Dialogs->mFloat;
		App->Cl_Scene_Data->S_Player_Locations[0]->Physics_Position.setX(App->Cl_Dialogs->mFloat);
		Update_ListView_Player();

		App->Cl_Bullet->Reset_Physics();
		return 1;
	}

	result = strcmp(btext, "Start Pos_Y");
	if (result == 0)
	{
		
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->Cl_Player->StartPos.y);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos Y");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->Cl_Player->StartPos.y = App->Cl_Dialogs->mFloat;
		App->Cl_Scene_Data->S_Player_Locations[0]->Current_Position.y = App->Cl_Dialogs->mFloat;
		App->Cl_Scene_Data->S_Player_Locations[0]->Physics_Position.setY(App->Cl_Dialogs->mFloat);
		Update_ListView_Player();

		App->Cl_Bullet->Reset_Physics();
		return 1;
	}

	result = strcmp(btext, "Start Pos_Z");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->Cl_Player->StartPos.z);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos Z");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->Cl_Player->StartPos.z = App->Cl_Dialogs->mFloat;
		App->Cl_Scene_Data->S_Player_Locations[0]->Current_Position.z = App->Cl_Dialogs->mFloat;
		App->Cl_Scene_Data->S_Player_Locations[0]->Physics_Position.setZ(App->Cl_Dialogs->mFloat);
		Update_ListView_Player();

		App->Cl_Bullet->Reset_Physics();
		return 1;
	}

	return 1;
}

// *************************************************************************
// *				Edit_Player_Physics_Onclick  Terry Bernie					   *
// *************************************************************************
bool GD19_Properties::Edit_Player_Physics_Onclick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);
	
	result = strcmp(btext, "Mass");
	if (result == 0)
	{
		char chr_Radius[10];
		sprintf(chr_Radius, "%.3f ", App->Cl_Player->mObject->getInvMass());

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Radius);
		strcpy(App->Cl_Dialogs->btext, "Player Physics Mass");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }


		App->Cl_Player->mObject->setMassProps(App->Cl_Dialogs->mFloat, btVector3(0, 0, 0));

		Update_ListView_Player_Physics();

		return 1;
	}

	result = strcmp(btext, "Radius");
	if (result == 0)
	{
		char chr_Radius[10];
		sprintf(chr_Radius, "%.3f ", App->Cl_Player->Capsule_Radius);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Radius);
		strcpy(App->Cl_Dialogs->btext, "Player Physics Shape Radius");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) 
		{ 
			return TRUE; 
		}

		App->Cl_Player->Capsule_Radius = App->Cl_Dialogs->mFloat;

		Update_ListView_Player_Physics();

		App->Cl_Player->Adjust_Capsule();
		return 1;
	}

	result = strcmp(btext, "Height");
	if (result == 0)
	{
		char chr_Height[10];
		sprintf(chr_Height, "%.3f ", App->Cl_Player->Capsule_Height);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Height);
		strcpy(App->Cl_Dialogs->btext, "Player Physics Shape Height");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->Cl_Player->Capsule_Height = App->Cl_Dialogs->mFloat;

		App->Cl_Player->Adjust_Capsule();
		return 1;
	}
	return 1;
}

// *************************************************************************
// *				Edit_Sounds_OnClick  Terry Bernie					   *
// *************************************************************************
bool GD19_Properties::Edit_Sounds_OnClick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	// Name
	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->Cl_Object[Index]->Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Name, App->Cl_Dialogs->Chr_Text);

		App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);

		Update_ListView_Sounds();
	}

	// Stock Sound
	result = strcmp(btext, "Stock_Snd");
	if (result == 0)
	{

		//App->Cl_Stock->List_Stock_Dialog(Enums::ListBox_Stock_Sounds); // Needs Deleteing or somthing

		App->Cl_Stock->ItemToSelect = App->Cl_Scene_Data->Cl_Object[Index]->Sound_ID_v2;
		App->Cl_Stock->Start_Stock_Dialog();
		App->Cl_Scene_Data->Cl_Object[Index]->Sound_ID_v2 = App->Cl_Stock->ListIndex;
		
		Update_ListView_Sounds();
		return 1;
	}

	// Sound
	result = strcmp(btext, "Play");
	if (result == 0)
	{
		
		strcpy(App->Cl_Dialogs->btext, "Play Sound In The Game");

		App->Cl_Dialogs->TrueFlase = App->Cl_Scene_Data->Cl_Object[Index]->Play_v2;

		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if (App->Cl_Dialogs->TrueFlase == 1)
			{
				App->Cl_Scene_Data->Cl_Object[Index]->Play_v2 = 1;
			}
			else
			{
				App->Cl_Scene_Data->Cl_Object[Index]->Play_v2 = 0;
				
			}
		}

		Update_ListView_Sounds();
		return 1;
	}


	return 1;
}

// *************************************************************************
// *				Edit_Messages_OnClick  Terry Bernie					   *
// *************************************************************************
bool GD19_Properties::Edit_Messages_OnClick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	// Name
	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->Cl_Object[Index]->Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Name, App->Cl_Dialogs->Chr_Text);

		App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Messages();
	}

	// Message
	result = strcmp(btext, "Message");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Text");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem);

		App->Cl_Dialogs->Dialog_Text(0);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Entity[0].mTextItem, App->Cl_Dialogs->Chr_Text);
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Dialogs->Chr_Text);

		Update_ListView_Messages();
		return 1;
	}

	// Message stock
	result = strcmp(btext, "Message_Stock");
	if (result == 0)
	{
		App->Cl_Dialogs->Start_Gen_ListBox(Enums::ListBox_Stock_Messages);

		Update_ListView_Messages();
		return 1;
	}

	// Re Trigger
	result = strcmp(btext, "Re-Trigger");
	if (result == 0)
	{
		App->Say("Re-Trigger");
		//App->GDCL_Dialogs->Start_Postion();

		return 1;
	}

	return 1;
}

// *************************************************************************
// *				Edit_Move_Entity_OnClick  Terry Bernie					   *
// *************************************************************************
bool GD19_Properties::Edit_Move_Entity_OnClick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->Cl_Object[Index]->Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Name, App->Cl_Dialogs->Chr_Text);

		App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Move_Entities();
	}



	result = strcmp(btext, "Object");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Select Object to Move");

		App->Cl_Dialogs->DropList_Data = Enums::DropDialog_TrigMoveObject;
		App->Cl_Dialogs->Dialog_DropGen();

		if (App->Cl_Dialogs->Canceled == 0)
		{
			strcpy(App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Object_Name, App->Cl_Dialogs->Chr_DropText);

			int MoveObjectIndex = App->Cl_Scene_Data->GetJustIndex_ByName(App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Object_Name);
			App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Object_Index = MoveObjectIndex;
			App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Object_ID = App->Cl_Scene_Data->Cl_Object[MoveObjectIndex]->Object_ID;

			App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->MeshPos.x = App->Cl_Scene_Data->Cl_Object[MoveObjectIndex]->Mesh_Pos.x;
			App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->MeshPos.y = App->Cl_Scene_Data->Cl_Object[MoveObjectIndex]->Mesh_Pos.y;
			App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->MeshPos.z = App->Cl_Scene_Data->Cl_Object[MoveObjectIndex]->Mesh_Pos.z;

			App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->PhysicsPos.x = App->Cl_Scene_Data->Cl_Object[MoveObjectIndex]->Physics_Pos.x;
			App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->PhysicsPos.y = App->Cl_Scene_Data->Cl_Object[MoveObjectIndex]->Physics_Pos.y;
			App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->PhysicsPos.z = App->Cl_Scene_Data->Cl_Object[MoveObjectIndex]->Physics_Pos.z;

			Update_ListView_Move_Entities();

			App->Cl_Scene_Data->Reset_Triggers();

		}
		return 1;
	}

	result = strcmp(btext, "Axis");
	if (result == 0)
	{
		int TestChr = 1;
		strcpy(App->Cl_Dialogs->btext, "Select Axis ( World )");

		App->Cl_Dialogs->DropList_Data = Enums::DropDialog_TrigMoveAxis;
		App->Cl_Dialogs->Dialog_DropGen();

		if (App->Cl_Dialogs->Canceled == 0)
		{

			// X Axis
			TestChr = strcmp(App->Cl_Dialogs->Chr_DropText, "X");
			if (TestChr == 0)
			{
				App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->WhatDirection = Enums::Axis_x;

			}

			// y Axis
			TestChr = strcmp(App->Cl_Dialogs->Chr_DropText, "Y");
			if (TestChr == 0)
			{
				App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->WhatDirection = Enums::Axis_y;

			}

			// Z Axis
			TestChr = strcmp(App->Cl_Dialogs->Chr_DropText, "Z");
			if (TestChr == 0)
			{
				App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->WhatDirection = Enums::Axis_z;
			}

			Update_ListView_Move_Entities();
		}
		return 1;
	}


	result = strcmp(btext, "Distance");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set Offset Distance");

		char buff[256];

		sprintf(buff, "%f", App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Distance);
		strcpy(App->Cl_Dialogs->Chr_Float, buff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{

			if (App->Cl_Dialogs->mFloat < 0)
			{
				App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->IsNegative = true;
			}
			else
			{
				App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->IsNegative = false;
			}

			App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Distance = App->Cl_Dialogs->mFloat;

			Update_ListView_Move_Entities();
		}
		return 1;
	}

	result = strcmp(btext, "Speed");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set Movment Speed");

		char buff[256];
		sprintf(buff, "%f", App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Speed);
		strcpy(App->Cl_Dialogs->Chr_Float, buff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{

			App->Cl_Scene_Data->Cl_Object[Index]->S_MoveType->Speed = App->Cl_Dialogs->mFloat;

			Update_ListView_Move_Entities();
		}
		return 1;
	}

	// Stock Sound
	result = strcmp(btext, "Stock_Snd");
	if (result == 0)
	{

		App->Cl_Stock->List_Stock_Dialog(Enums::ListBox_Stock_Sounds);

		App->Cl_Scene_Data->Cl_Object[Index]->Sound_ID_v2 = App->Cl_Stock->ListIndex;
		Update_ListView_Move_Entities();
		return 1;
	}

	// Sound
	result = strcmp(btext, "Play");
	if (result == 0)
	{

		strcpy(App->Cl_Dialogs->btext, "Play Sound In The Game");

		App->Cl_Dialogs->TrueFlase = App->Cl_Scene_Data->Cl_Object[Index]->Play_v2;

		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if (App->Cl_Dialogs->TrueFlase == 1)
			{
				App->Cl_Scene_Data->Cl_Object[Index]->Play_v2 = 1;
			}
			else
			{
				App->Cl_Scene_Data->Cl_Object[Index]->Play_v2 = 0;

			}
		}

		Update_ListView_Move_Entities();
		return 1;
	}

	return 1;
}

// *************************************************************************
// *				Edit_Collectables_OnClick  Terry Bernie				   *
// *************************************************************************
bool GD19_Properties::Edit_Collectables_OnClick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;
	
	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->Cl_Object[Index]->Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Name, App->Cl_Dialogs->Chr_Text);
		

		App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Collectables();
	}

	return 1;
}

// *************************************************************************
// *				Edit_Particles_OnClick  Terry Bernie				   *
// *************************************************************************
bool GD19_Properties::Edit_Particles_OnClick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->Cl_Object[Index]->Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Name, App->Cl_Dialogs->Chr_Text);

		App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Collectables();
	}


	result = strcmp(btext, "Scale");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set Particle Scale");

		char buff[256];
		sprintf(buff, "%f", App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.x);
		strcpy(App->Cl_Dialogs->Chr_Float, buff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{
			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.x = App->Cl_Dialogs->mFloat;
			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.y = App->Cl_Dialogs->mFloat;
			App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale.z = App->Cl_Dialogs->mFloat;

			App->Cl_Scene_Data->Cl_Object[Index]->OgreNode->setScale(App->Cl_Scene_Data->Cl_Object[Index]->Mesh_Scale);

			Update_ListView_Particles();
		}
	}

	result = strcmp(btext, "Speed");
	if (result == 0)
	{
		
		strcpy(App->Cl_Dialogs->btext, "Set Particle Speed");

		char buff[256];
		sprintf(buff, "%f", App->Cl_Scene_Data->Cl_Object[Index]->Ogre_Particle->getSpeedFactor());
		strcpy(App->Cl_Dialogs->Chr_Float, buff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{
			App->Cl_Scene_Data->Cl_Object[Index]->Ogre_Particle->setSpeedFactor(App->Cl_Dialogs->mFloat);

			Update_ListView_Particles();
		}
	}



	return 1;
}

// *************************************************************************
// *				Edit_Teleport_OnClick  Terry Bernie					   *
// *************************************************************************
bool GD19_Properties::Edit_Teleport_OnClick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;
	
	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->Cl_Scene_Data->Cl_Object[Index]->Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->Cl_Scene_Data->Cl_Object[Index]->Name, App->Cl_Dialogs->Chr_Text);

		App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Teleport();
	}

	result = strcmp(btext, "Goto");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Select Object to Move");

		App->Cl_Dialogs->DropList_Data = Enums::DropDialog_Locations;
		App->Cl_Dialogs->Dialog_DropGen();


		if (App->Cl_Dialogs->Canceled == 0)
		{
			int LocationIndex = App->Cl_LookUps->Player_Location_GetIndex_ByName(App->Cl_Dialogs->Chr_DropText);


			strcpy(App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Name, App->Cl_Scene_Data->S_Player_Locations[LocationIndex]->Name);

			App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Player_Position = App->Cl_Scene_Data->S_Player_Locations[LocationIndex]->Current_Position;
			App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Physics_Position = App->Cl_Scene_Data->S_Player_Locations[LocationIndex]->Physics_Position;
			App->Cl_Scene_Data->Cl_Object[Index]->S_Teleport[0]->Physics_Rotation = App->Cl_Scene_Data->S_Player_Locations[LocationIndex]->Physics_Rotation;

			Update_ListView_Teleport();
		}
		
	}

	// Stock Sound
	result = strcmp(btext, "Stock_Snd");
	if (result == 0)
	{

		App->Cl_Stock->List_Stock_Dialog(Enums::ListBox_Stock_Sounds);

		App->Cl_Scene_Data->Cl_Object[Index]->Sound_ID_v2 = App->Cl_Stock->ListIndex;
		Update_ListView_Teleport();
		return 1;
	}

	// Sound
	result = strcmp(btext, "Play");
	if (result == 0)
	{

		strcpy(App->Cl_Dialogs->btext, "Play Sound In The Game");

		App->Cl_Dialogs->TrueFlase = App->Cl_Scene_Data->Cl_Object[Index]->Play_v2;

		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if (App->Cl_Dialogs->TrueFlase == 1)
			{
				App->Cl_Scene_Data->Cl_Object[Index]->Play_v2 = 1;
			}
			else
			{
				App->Cl_Scene_Data->Cl_Object[Index]->Play_v2 = 0;

			}
		}

		Update_ListView_Teleport();
		return 1;
	}

	return 1;
}

// *************************************************************************
// *				ListView_Object_OnClick  Terry Bernie				   *
// *************************************************************************
bool GD19_Properties::ListView_Object_Physics_OnClick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		
	}

	return 1;
}

// *************************************************************************
// *					Enable_Test_Button  Terry Bernie				   *
// *************************************************************************
void GD19_Properties::Enable_Test_Button(bool Enable)
{
///	EnableWindow(GetDlgItem(App->Cl_Properties->Properties_Dlg_hWnd, IDC_BTTEST), Enable);
}

// *************************************************************************
// *					Enable_Delete Button  Terry Bernie				   *
// *************************************************************************
void GD19_Properties::Enable_Delete_Button(bool Enable)
{
	///EnableWindow(GetDlgItem(App->Cl_Properties->Properties_Dlg_hWnd, IDC_BTDELETE), Enable);
}

