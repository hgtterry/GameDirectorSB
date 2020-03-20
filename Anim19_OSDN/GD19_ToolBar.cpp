/*	
	Copyright (c) Equity10 2016 HGT Software W.T.Flanigan H.C.Flanigan B.Parkin

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
#include "resource.h"
#include "GD19_App.h"
#include "GD19_ToolBar.h"


GD19_ToolBar::GD19_ToolBar(void)
{
	TB1 = 0;
	TB2 = 0;
	TB3 = 0;

	TB_1 = NULL;
	hTooltip_TB_1 = NULL;

	TB_1_Active = 0;

	MouseOption_DlgHwnd = NULL;

	FreeCam_Active = 1;
	FirstPerson_Active = 0;
	ThirdPerson_Active = 0;
	Selection_Active = 0;
}


GD19_ToolBar::~GD19_ToolBar(void)
{
}


// *************************************************************************
// *						Toggle_TB1 Terry Berine						   *
// *************************************************************************
void GD19_ToolBar::Toggle_TB1(void)
{
	if (TB_1_Active == 1)
	{
		int Test = DestroyWindow(App->Cl_ToolBar->hTooltip_TB_1);
		if (Test == 0)
		{
			App->Say("Failed");
		}
		App->Cl_ToolBar->hTooltip_TB_1 = NULL;

		Test = DestroyWindow(App->Cl_ToolBar->TB_1);
		if (Test == 0)
		{
			App->Say("Failed");
		}
		App->Cl_ToolBar->TB_1 = NULL;
		TB_1_Active = 0;
	}
	else
	{
		Start_TB1();
	}
	
}

// *************************************************************************
// *						Start_TB1 Terry Berine						   *
// *************************************************************************
void GD19_ToolBar::Start_TB1(void)
{
	TB_1 = CreateDialog(App->hInst,(LPCTSTR) IDD_TB1,App->Fdlg,(DLGPROC)App->Cl_ToolBar->TB1_Proc);
	Init_Bmps();
	TB_1_Active = 1;
}

// *************************************************************************
// *								TB1_Proc							   *
// *************************************************************************
LRESULT CALLBACK GD19_ToolBar::TB1_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
				App->Custom_Button_Toggle(item,App->Cl_ToolBar->Selection_Active);
				return CDRF_DODEFAULT;
			}

			if (some_item->idFrom == IDC_SHOWMESHPOINTS && some_item->code == NM_CUSTOMDRAW)
			{
				LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_ToolBar->FreeCam_Active);
				return CDRF_DODEFAULT;
			}

			if (some_item->idFrom == IDC_SHOWTEXTURED && some_item->code == NM_CUSTOMDRAW)
			{
				LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_ToolBar->FirstPerson_Active);
				return CDRF_DODEFAULT;
			}

			if (some_item->idFrom == IDC_SHOWFACES && some_item->code == NM_CUSTOMDRAW)
			{
				LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_ToolBar->ThirdPerson_Active);
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

			App->Cl_Dialogs->Start_DataView();
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
// *					Create_ToolBars Terry Berine					   *
// *************************************************************************
void GD19_ToolBar::Create_ToolBars(void)
{
	//CreateDialog(App->hInst,(LPCTSTR) IDD_TOOLBAR,App->Fdlg,(DLGPROC)App->CL_ToolBar->TopOgre_Proc);

}

// *************************************************************************
// *							TopOgre_Proc  							   *
// *************************************************************************
LRESULT CALLBACK GD19_ToolBar::TopOgre_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		{	

			return TRUE;
		}

	case WM_CTLCOLORDLG:
		{
			return (LONG)App->AppBackground;
		}
	case WM_NOTIFY:
		{
			LPTOOLTIPTEXT lpToolTipText;
			lpToolTipText = (LPTOOLTIPTEXT) lParam;

			if (lpToolTipText->hdr.code == TTN_NEEDTEXT)
			{

			}
			break;
		}
	case WM_COMMAND:
		{
		}
	}
	return FALSE;
}

// *************************************************************************
// *						Set_TexturesOn Terry Bernie					   *
// *************************************************************************
void GD19_ToolBar::Set_TexturesOn(bool State)
{
	if (State == 1)
	{
		///App->Cl19_Ogre->RenderListener->ShowTextured = 1;
	//	HWND Temp = GetDlgItem(TB_1,IDC_SHOWTEXTURED);
	//	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_TexturesOn_Bmp);
	}
	else
	{
		///App->Cl19_Ogre->RenderListener->ShowTextured = 0;
		//HWND Temp = GetDlgItem(TB_1,IDC_SHOWTEXTURED);
		//SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_TexturesOff_Bmp);
	}
}

// *************************************************************************
// *						Set_LightsOn Terry Bernie					   *
// *************************************************************************
void GD19_ToolBar::Set_LightsOn(bool State)
{
	/*if (State == 1)
	{
		App->Cl_Ogre->RenderListener->Light_Activated = 1;
		HWND Temp = GetDlgItem(TB_1,IDC_LIGHTS);
		SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_LightsOn_Bmp);
	}
	else
	{
		App->Cl_Ogre->RenderListener->Light_Activated = 0;
		HWND Temp = GetDlgItem(TB_1,IDC_LIGHTS);
		SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_LightsOff_Bmp);
	}*/
}

// *************************************************************************
// *						Set_FacesOn Terry Bernie					   *
// *************************************************************************
void GD19_ToolBar::Set_FacesOn(bool State)
{
	if (State == 1)
	{
		///App->Cl19_Ogre->RenderListener->ShowMesh = 1;
		///HWND Temp = GetDlgItem(TB_1,IDC_SHOWFACES);
		///SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_MeshOn_Bmp);
	}
	else
	{
		///App->Cl19_Ogre->RenderListener->ShowMesh = 0;
		///HWND Temp = GetDlgItem(TB_1,IDC_SHOWFACES);
		///SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_MeshOff_Bmp);
	}
}

// *************************************************************************
// *						Set_PointsOn Terry Bernie					   *
// *************************************************************************
void GD19_ToolBar::Set_PointsOn(bool State)
{
	if (State == 1)
	{
		///App->Cl19_Ogre->RenderListener->ShowPoints = 1;
		///HWND Temp = GetDlgItem(TB_1,IDC_SHOWMESHPOINTS);
		///SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_MeshPointsOn_Bmp);
	}
	else
	{
		///App->Cl19_Ogre->RenderListener->ShowPoints = 0;
		///HWND Temp = GetDlgItem(TB_1,IDC_SHOWMESHPOINTS);
		///SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_MeshPointsOff_Bmp);
	}
}

// *************************************************************************
// *						Set_NormalsOn Terry Bernie					   *
// *************************************************************************
void GD19_ToolBar::Set_NormalsOn(bool State)
{
	/*if (State == 1)
	{
		App->Cl_Ogre->RenderListener->ShowNormals = 1;
		HWND Temp = GetDlgItem(TB_1,IDC_SHOWNORMALS);
		SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_NormalsOn_Bmp);
	}
	else
	{
		App->Cl_Ogre->RenderListener->ShowNormals = 0;
		HWND Temp = GetDlgItem(TB_1,IDC_SHOWNORMALS);
		SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_NormalsOff_Bmp);
	}*/
}

// *************************************************************************
// *					Set_BoundingBoxOn Terry Bernie					   *
// *************************************************************************
void GD19_ToolBar::Set_BoundingBoxOn(bool State)
{
	/*if (State == 1)
	{
		App->Cl_Ogre->RenderListener->ShowBoundingBox = 1;
		HWND Temp = GetDlgItem(TB_1,IDC_BOUNDINGBOX);
		SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_BBOn_Bmp);
	}
	else
	{
		App->Cl_Ogre->RenderListener->ShowBoundingBox = 0;
		HWND Temp = GetDlgItem(TB_1,IDC_BOUNDINGBOX);
		SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_BBOff_Bmp);
	}*/
}

// *************************************************************************
// *						Set_JointsOn Terry Bernie					   *
// *************************************************************************
void GD19_ToolBar::Set_JointsOn(bool State)
{
	
}

// *************************************************************************
// *						Init_Bmps Terry Bernie						   *
// *************************************************************************
void GD19_ToolBar::Init_Bmps(void)
{
	hTooltip_TB_1 = CreateWindowEx(0, TOOLTIPS_CLASS,"", TTS_ALWAYSTIP | TTS_BALLOON,0, 0, 0, 0, App->MainHwnd, 0,App->hInst, 0);

	// --------------------------------------------------- 
	HWND Temp = GetDlgItem(TB_1,IDC_FULLSCREEN);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_FullScreen_Bmp);

	TOOLINFO ti = {0};
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti.uId = (UINT_PTR)Temp;
	ti.lpszText = "Full Screen View";
	ti.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1,IDC_BTMODELINFO);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_ModelInfo_Bmp);

	TOOLINFO ti2 = {0};
	ti2.cbSize = sizeof(ti);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS| TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Model Information";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1,IDC_BTMOUSESPEED);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_MouseSensitivity_Bmp);

	TOOLINFO ti3 = {0};
	ti3.cbSize = sizeof(ti);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS| TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Set Mouse Sensitivity";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti3);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1,IDC_BTLOCATIONS);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_Projection_Bmp);

	TOOLINFO ti4 = {0};
	ti4.cbSize = sizeof(ti);
	ti4.uFlags = TTF_IDISHWND | TTF_SUBCLASS| TTF_CENTERTIP;
	ti4.uId = (UINT_PTR)Temp;
	ti4.lpszText = "Location:- Save and Move to Locations within the Scene";
	ti4.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti4);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1, IDC_SELECTION);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_LightsOff_Bmp);

	TOOLINFO ti5 = {0};
	ti5.cbSize = sizeof(ti);
	ti5.uFlags = TTF_IDISHWND | TTF_SUBCLASS| TTF_CENTERTIP;
	ti5.uId = (UINT_PTR)Temp;
	ti5.lpszText = "Selection Mode Press Space bar to Select";
	ti5.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti5);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1,IDC_BUILDGAME);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_BBOff_Bmp);

	TOOLINFO ti6 = {0};
	ti6.cbSize = sizeof(ti);
	ti6.uFlags = TTF_IDISHWND | TTF_SUBCLASS| TTF_CENTERTIP;
	ti6.uId = (UINT_PTR)Temp;
	ti6.lpszText = "Build Stand Alone GAme";
	ti6.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti6);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1,IDC_GAMEMODE);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_NormalsOff_Bmp);

	TOOLINFO ti7 = {0};
	ti7.cbSize = sizeof(ti);
	ti7.uFlags = TTF_IDISHWND | TTF_SUBCLASS| TTF_CENTERTIP;
	ti7.uId = (UINT_PTR)Temp;
	ti7.lpszText = "Game Mode Preview";
	ti7.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti7);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1,IDC_IMGUIDEBUG);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_BonesOff_Bmp);

	TOOLINFO ti8 = {0};
	ti8.cbSize = sizeof(ti);
	ti8.uFlags = TTF_IDISHWND | TTF_SUBCLASS| TTF_CENTERTIP;
	ti8.uId = (UINT_PTR)Temp;
	ti8.lpszText = "Debug Game/App";
	ti8.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti8);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1,IDC_FREECAM);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_MeshPointsOff_Bmp);

	TOOLINFO ti9 = {0};
	ti9.cbSize = sizeof(ti);
	ti9.uFlags = TTF_IDISHWND | TTF_SUBCLASS| TTF_CENTERTIP;
	ti9.uId = (UINT_PTR)Temp;
	ti9.lpszText = "Free Camera No Collision";
	ti9.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti9);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1,IDC_THIRDPERSON);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_MeshOff_Bmp);

	TOOLINFO ti10 = {0};
	ti10.cbSize = sizeof(ti);
	ti10.uFlags = TTF_IDISHWND | TTF_SUBCLASS| TTF_CENTERTIP;
	ti10.uId = (UINT_PTR)Temp;
	ti10.lpszText = "3rd Person View Not available yet";
	ti10.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti10);

	// --------------------------------------------------- 

	Temp = GetDlgItem(TB_1,IDC_FIRSTPERSON);
	SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->Hnd_TexturesOff_Bmp);

	TOOLINFO ti11 = {0};
	ti11.cbSize = sizeof(ti);
	ti11.uFlags = TTF_IDISHWND | TTF_SUBCLASS| TTF_CENTERTIP;
	ti11.uId = (UINT_PTR)Temp;
	ti11.lpszText = "1st Person View with Physics";
	ti11.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti11);

}

// *************************************************************************
// *					Check_Current_Option Terry Bernie				   *
// *************************************************************************
void GD19_ToolBar::UnCheck_All_MouseOption(HWND hDlg)
{
	App->Cl_Dialogs->Mouse_Normal2 = 0;
	App->Cl_Dialogs->Mouse_Slow2 = 0;
	App->Cl_Dialogs->Mouse_VerySlow2 = 0;
	App->Cl_Dialogs->Mouse_Fast2 = 0;
}

