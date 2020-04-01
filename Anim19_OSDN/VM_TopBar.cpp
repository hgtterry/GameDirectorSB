#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "VM_TopBar.h"


VM_TopBar::VM_TopBar()
{
	TabsHwnd =	nullptr;
	TB_1 =		nullptr;
}


VM_TopBar::~VM_TopBar()
{
}

// *************************************************************************
// *	  					Start_TopBar  	Terry						   *
// *************************************************************************
bool VM_TopBar::Start_TopBar()
{
	CreateDialog(App->hInst,(LPCTSTR)IDD_TOPBAR,App->Fdlg,(DLGPROC)TopBar_Proc);
	return 1;
}
// *************************************************************************
// *						TopBar_Proc Terry							   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::TopBar_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->CL_Vm_TopBar->TabsHwnd = CreateWindow(WC_TABCONTROL, "",
			WS_CHILD |
			WS_VISIBLE |
			ES_LEFT |
			TCS_MULTILINE |
			TCS_RAGGEDRIGHT,

			4, 4, 1500, 80, hDlg, NULL, App->hInst, NULL);

		TabCtrl_SetItemSize(App->CL_Vm_TopBar->TabsHwnd, 54, 24);

		TC_ITEM item;
		ZeroMemory(&item, sizeof(item));
		item.mask = TCIF_TEXT;
		item.pszText = "Old";
		TabCtrl_InsertItem(App->CL_Vm_TopBar->TabsHwnd, 0, &item);
		item.pszText = "Folders";
		TabCtrl_InsertItem(App->CL_Vm_TopBar->TabsHwnd, 1, &item);
		item.pszText = "Texture Files";
		TabCtrl_InsertItem(App->CL_Vm_TopBar->TabsHwnd, 2, &item);

		TabCtrl_SetCurFocus(App->CL_Vm_TopBar->TabsHwnd, 0);

		App->CL_Vm_TopBar->Start_TB1();
		

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{

		/*if(GetDlgItem(hDlg,IDC_BANNER) == (HWND)lParam)
		{
		SetBkColor((HDC) wParam, RGB(0, 255, 0));
		SetTextColor((HDC) wParam, RGB(0,0,255));
		SetBkMode((HDC) wParam, TRANSPARENT);
		return (UINT) App->AppBackground;
		}*/
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{

		LPNMHDR nmhdr = (LPNMHDR)lParam;
		switch (nmhdr->code)
		{
		case TCN_SELCHANGE:
		{
			int num = TabCtrl_GetCurSel(nmhdr->hwndFrom);
			switch (num)
			{
				//--------------------------------- Textures
			case 0:

				ShowWindow(App->CL_Vm_TopBar->TB_1, SW_SHOW);

				break;
				//--------------------------------- Bones
			case 1:

				
				ShowWindow(App->CL_Vm_TopBar->TB_1, SW_HIDE);
				

				break;
				//--------------------------------- Mesh
			case 2:

				
				ShowWindow(App->CL_Vm_TopBar->TB_1, SW_HIDE);
				
				break;


			}
		}

		}
		return 0;
	}

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK)
		{
			
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}


// *************************************************************************
// *						Start_TB1 Terry Berine						   *
// *************************************************************************
void VM_TopBar::Start_TB1(void)
{
	TB_1 = CreateDialog(App->hInst, (LPCTSTR)IDD_TB1, App->CL_Vm_TopBar->TabsHwnd, (DLGPROC)TB1_Proc);
	Init_Bmps_TB1();
}

// *************************************************************************
// *								TB1_Proc							   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::TB1_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		///	HWND Temp = GetDlgItem(hDlg, IDC_BTTBHELP);
		///	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_InfoSmall_Bmp);
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_SELECTION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_ToolBar->Selection_Active);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_SHOWMESHPOINTS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_ToolBar->FreeCam_Active);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_SHOWTEXTURED && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_ToolBar->FirstPerson_Active);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_SHOWFACES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_ToolBar->ThirdPerson_Active);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_IMGUIDEBUG && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_GAMEMODE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BUILDGAME && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTPROJECTION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		//if (LOWORD(wParam) == IDC_BTTBHELP)
		/*{
		App->Cl_Utilities->OpenHTML("Help\\TopPanel.html");
		return 1;
		}*/

		if (LOWORD(wParam) == IDC_IMGUIDEBUG)// ImGui Debug Stuff
		{
			App->Cl_ImGui->ImGui_Selection_Dlg();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BUILDGAME)
		{
			App->Cl_Project->Start_Project_Build();
			return 1;
		}

		if (LOWORD(wParam) == IDC_SELECTION)
		{
			if (App->Cl_ToolBar->Selection_Active == 1)
			{
				App->Cl_ToolBar->Selection_Active = 0;
				App->Cl_Visuals->mPickSight->hide();
				App->Cl19_Ogre->OgreListener->GD_Selection_Mode = 0;
				///App->Cl19_Ogre->OgreListener->mNameOverlay->hide();
			}
			else
			{
				App->Cl_ToolBar->Selection_Active = 1;
				App->Cl_Visuals->mPickSight->show();
				App->Cl19_Ogre->OgreListener->GD_Selection_Mode = 1;
				///App->Cl19_Ogre->OgreListener->mNameOverlay->hide();
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_GAMEMODE)
		{
			App->Cl_Dialogs->GameMode_StartPosition_Dlg();
			if (App->Cl_Dialogs->Canceled == 1)
			{
				return 1;
			}
			App->Cl_Scene_Data->GameMode();

			return 1;
		}


		if (LOWORD(wParam) == IDC_FULLSCREEN)
		{
			App->Cl19_Ogre->Go_FullScreen_Mode();
			return TRUE;
		}
		if (LOWORD(wParam) == IDC_BTMODELINFO)
		{
			if (App->Cl_ImGui->Show_ImGui_Counters == 1)
			{
				App->Cl_ImGui->Show_ImGui_Counters = 0;
			}
			else
			{
				App->Cl_ImGui->Show_ImGui_Counters = 1;
			}
			//App->Cl_Dialogs->Start_DataView();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTMOUSESPEED)
		{
			App->Cl_Dialogs->Start_Mouse_Sensitivity();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTPROJECTION)
		{
			App->Cl_Dialogs->Start_Projection();
			return TRUE;
		}

		/*if (LOWORD(wParam) == IDC_LIGHTS)
		{
		if (App->CL_Model_Data->Model_Loaded == 1 && App->CL_Model_Data->HasMesh == 1)
		{
		if (App->Cl_Ogre->RenderListener->Light_Activated == 1)
		{
		App->CL_ToolBar->Set_LightsOn(false);
		}
		else
		{
		App->CL_ToolBar->Set_LightsOn(true);
		}
		}
		return TRUE;
		}*/

		/*if (LOWORD(wParam) == IDC_BOUNDINGBOX)
		{
		if (App->CL_Model_Data->Model_Loaded == 1)
		{
		if (App->Cl_Ogre->RenderListener->ShowBoundingBox == 1)
		{
		App->CL_ToolBar->Set_BoundingBoxOn(false);
		}
		else
		{
		App->CL_ToolBar->Set_BoundingBoxOn(true);
		}
		}

		return TRUE;
		}*/

		/*if (LOWORD(wParam) == IDC_SHOWNORMALS)
		{
		if (App->CL_Model_Data->Model_Loaded == 1 && App->CL_Model_Data->HasMesh == 1)
		{
		if (App->Cl_Ogre->RenderListener->ShowNormals == 1)
		{
		App->CL_ToolBar->Set_NormalsOn(false);
		}
		else
		{
		App->CL_ToolBar->Set_NormalsOn(true);
		}
		}

		return TRUE;
		}*/

		if (LOWORD(wParam) == IDC_SHOWMESHPOINTS)  // Free Camera
		{
			//if (App->CL_Model_Data->Model_Loaded == 1 && App->CL_Model_Data->HasMesh == 1)
			{
				App->Cl_ToolBar->FreeCam_Active = 1;
				App->Cl_ToolBar->FirstPerson_Active = 0;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_SHOWFACES)// 3rd Person
		{
			//if (App->CL_Model_Data->Model_Loaded == 1 && App->CL_Model_Data->HasMesh == 1)
			{
				///if (App->Cl19_Ogre->RenderListener->ShowMesh == 1)
				{
					//App->CL_ToolBar->Set_FacesOn(false);
				}
				///else
				{
					//App->CL_ToolBar->Set_FacesOn(true);
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_SHOWTEXTURED) // 1st Person
		{
			if (App->Cl_Player->PlayerAdded == 1)
			{
				App->Cl_ToolBar->FreeCam_Active = 0;
				App->Cl_ToolBar->FirstPerson_Active = 1;
				RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

				App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamFirst;

			}
			else
			{
				App->Say("No Player in Scene");
			}
			return TRUE;
		}

		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *						Init_Bmps_TB1 Terry Bernie					   *
// *************************************************************************
void VM_TopBar::Init_Bmps_TB1(void)
{
	HWND hTooltip_TB_1 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	// --------------------------------------------------- 
	HWND Temp = GetDlgItem(TB_1, IDC_FULLSCREEN);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_FullScreen_Bmp);

	TOOLINFO ti = { 0 };
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti.uId = (UINT_PTR)Temp;
	ti.lpszText = "Full Screen View";
	ti.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_BTMODELINFO);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);

	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Model Information";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_BTMOUSESPEED);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MouseSensitivity_Bmp);

	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Set Mouse Sensitivity";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti3);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_BTLOCATIONS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_Projection_Bmp);

	TOOLINFO ti4 = { 0 };
	ti4.cbSize = sizeof(ti);
	ti4.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti4.uId = (UINT_PTR)Temp;
	ti4.lpszText = "Location:- Save and Move to Locations within the Scene";
	ti4.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti4);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_SELECTION);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);

	TOOLINFO ti5 = { 0 };
	ti5.cbSize = sizeof(ti);
	ti5.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti5.uId = (UINT_PTR)Temp;
	ti5.lpszText = "Selection Mode Press Space bar to Select";
	ti5.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti5);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_BUILDGAME);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOff_Bmp);

	TOOLINFO ti6 = { 0 };
	ti6.cbSize = sizeof(ti);
	ti6.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti6.uId = (UINT_PTR)Temp;
	ti6.lpszText = "Build Stand Alone GAme";
	ti6.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti6);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_GAMEMODE);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);

	TOOLINFO ti7 = { 0 };
	ti7.cbSize = sizeof(ti);
	ti7.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti7.uId = (UINT_PTR)Temp;
	ti7.lpszText = "Game Mode Preview";
	ti7.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti7);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_IMGUIDEBUG);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOff_Bmp);

	TOOLINFO ti8 = { 0 };
	ti8.cbSize = sizeof(ti);
	ti8.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti8.uId = (UINT_PTR)Temp;
	ti8.lpszText = "Debug Game/App";
	ti8.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti8);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_FREECAM);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);

	TOOLINFO ti9 = { 0 };
	ti9.cbSize = sizeof(ti);
	ti9.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti9.uId = (UINT_PTR)Temp;
	ti9.lpszText = "Free Camera No Collision";
	ti9.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti9);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_THIRDPERSON);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);

	TOOLINFO ti10 = { 0 };
	ti10.cbSize = sizeof(ti);
	ti10.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti10.uId = (UINT_PTR)Temp;
	ti10.lpszText = "3rd Person View Not available yet";
	ti10.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti10);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_FIRSTPERSON);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);

	TOOLINFO ti11 = { 0 };
	ti11.cbSize = sizeof(ti);
	ti11.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti11.uId = (UINT_PTR)Temp;
	ti11.lpszText = "1st Person View with Physics";
	ti11.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti11);

}
