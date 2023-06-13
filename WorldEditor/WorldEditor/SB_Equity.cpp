#include "StdAfx.h"
#include "AB_App.h"
#include "resource.h"
#include "SB_Equity.h"

SB_Equity::SB_Equity(void)
{
	mAutoLoad = 0;
	EquitySB_Dialog_Created = 0;
	OgreView_3D_hWnd =		nullptr;
	Equity_Main_hWnd =		nullptr;
	Render_Buttons_hWnd =	nullptr;
}

SB_Equity::~SB_Equity(void)
{
}

// *************************************************************************
// *			Switch_3D_Window:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Equity::Switch_3D_Window()
{
	//App->CL_Ogre->InitOgre();
	//Ogre::Root::getSingletonPtr()->renderOneFrame();

	App->CLSB_Ogre->mWindow->resize(500, 500);
	int test = SetWindowLong(App->CLSB_Ogre->Ogre_Window_hWnd, GWL_WNDPROC, (LONG)Ogre3D_Proc);

	SetWindowLongPtr(App->CLSB_Ogre->Ogre_Window_hWnd, GWL_STYLE, WS_BORDER);
	SetWindowPos(App->CLSB_Ogre->Ogre_Window_hWnd, 0, 0, 0, 0, 0, SWP_NOZORDER | SWP_NOMOVE | SWP_NOSIZE | SWP_NOACTIVATE | SWP_DRAWFRAME);
	ShowWindow(App->CLSB_Ogre->Ogre_Window_hWnd, SW_SHOW);

	SetWindowPos(App->CLSB_Ogre->Ogre_Window_hWnd, NULL, 4, 4, 820, 450, SWP_NOZORDER);
	
	HWND Check_hWnd = NULL;
	Check_hWnd = SetParent(App->CLSB_Ogre->Ogre_Window_hWnd, Equity_Main_hWnd);

	//if (!Check_hWnd)
	{
		//Debug
	}

	Resize_3DView();

	/*App->CLSB_Ogre->mWindow->resize(810, 400);
	App->CLSB_Ogre->mWindow->windowMovedOrResized();
	App->CLSB_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CLSB_Ogre->mWindow->getWidth() / (Ogre::Real)App->CLSB_Ogre->mWindow->getHeight());
	App->CLSB_Ogre->mCamera->yaw(Ogre::Radian(0));*/

	Auto_Load_File();

	App->CLSB_Ogre->OgreIsRunning = 1;
	App->CLSB_Ogre->Ogre_Render_Loop();
	
	if (App->CLSB_Ogre->OgreIsRunning == 1)
	{
		App->Say("xxx");
		delete App->CLSB_Ogre->mRoot;
		App->CLSB_Ogre->mRoot = NULL;
		App->CLSB_Ogre->OgreIsRunning = 0;
	}
}

// *************************************************************************
// *			Auto_Load_File:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Equity::Auto_Load_File()
{
	if (mAutoLoad == 1)
	{
		char Path[MAX_PATH];
		strcpy(Path, App->WorldEditor_Directory);
		strcat(Path, "Data\\Temp.Wepf");

		strcpy(App->CLSB_Loader->Path_FileName, Path);
		strcpy(App->CLSB_Loader->FileName, "Temp.Wepf");

		App->CLSB_Loader->Read_Project_File(Path);
		App->CLSB_Loader->Load_File_Wepf();

	}
}

// *************************************************************************
// *			Start_Equity_Dialog:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Equity::Start_Equity_Dialog(bool AutoLoad)
{
	mAutoLoad = AutoLoad;

	if (EquitySB_Dialog_Created == 0)
	{
		Equity_Main_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_OGREVIEWER, App->MainHwnd, (DLGPROC)Equity_Dialog_Proc);
		
		Start_Render_Buttons();
		
		EquitySB_Dialog_Created = 1;
		Switch_3D_Window();	
	}
	else
	{
		Auto_Load_File();
	}
}

// **************************************************************************
// *				Equity_Dialog_Proc:- Terry and Hazel Flanigan 2022		*
// **************************************************************************
LRESULT CALLBACK SB_Equity::Equity_Dialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_UPDATE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_TITLENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}*/
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_DRAWITEM:
	{

		LPDRAWITEMSTRUCT lpDIS = (LPDRAWITEMSTRUCT)lParam;

		if (lpDIS->CtlID == IDC_UPDATE)
		{
			App->Custom_Button_Normal_MFC(lpDIS, hDlg);
			return TRUE;
		}

		return TRUE;
	}

	case WM_SIZE:
	{
		App->CLSB_Equity->Resize_3DView();
		Ogre::Root::getSingletonPtr()->renderOneFrame();
	}break;

	case WM_COMMAND:
	{
		// File Import
		if (LOWORD(wParam) == ID_IMPORT_WORLDEDITORPROJECT)
		{
			int Result = App->CLSB_Loader->Open_File_Model("GDSB File   *.Wepf\0*.Wepf\0", "GDSB File", NULL);
			if (Result == 0)
			{
				return 1;
			}

			App->CLSB_Loader->Read_Project_File(App->CLSB_Loader->Path_FileName);
			App->CLSB_Loader->Load_File_Wepf();

			return TRUE;
		}

		// File Export
		if (LOWORD(wParam) == ID_OGRE3D_MESH)
		{
			App->CLSB_Exporter->Ogre3D_Model();
			return TRUE;
		}

		// File Clear Model
		if (LOWORD(wParam) == ID_FILE_CLEARMODEL)
		{
			App->CLSB_Model->Clear_Model_And_Reset();
			return TRUE;
		}

		
		
		// Camera
		if (LOWORD(wParam) == ID_CAMERAMODE_FREE)
		{
			App->CLSB_Camera->Set_Camera_Mode(Enums::CamDetached);
			return TRUE;
		}

		if (LOWORD(wParam) == ID_CAMERAMODE_MODEL)
		{
			App->CLSB_Camera->Set_Camera_Mode(Enums::CamModel);
			return TRUE;
		}
		
		if (LOWORD(wParam) == ID_CAMERA_RESETVIEW)
		{
			App->CLSB_Camera->Reset_View();
			return TRUE;
		}

		if (LOWORD(wParam) == ID_CAMERA_ZEROVIEW)
		{
			App->CLSB_Camera->Zero_View();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TEST)
		{
			App->CLSB_Ogre->OgreListener->StopOgre = 1;
			App->CLSB_Ogre->OgreIsRunning = 0;
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_UPDATE)
		{
			CFusionDoc* pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();

			pDoc->SelectAll();
			pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);

			App->CL_Export_World->Export_World_GD3D(1);

			pDoc->ResetAllSelections();
			pDoc->UpdateAllViews(UAV_ALL3DVIEWS, NULL);

			App->CLSB_Equity->mAutoLoad = 1;
			App->CLSB_Equity->Auto_Load_File();

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDOK)
		{
			App->CLSB_Equity->EquitySB_Dialog_Created = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->CLSB_Equity->EquitySB_Dialog_Created = 0;
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	break;

	}
	return FALSE;
}

// *************************************************************************
// *	  				Start_Render_Buttons		  	Terry			   *
// *************************************************************************
bool SB_Equity::Start_Render_Buttons()
{
	Render_Buttons_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TB_BUTTONS, Equity_Main_hWnd, (DLGPROC)Render_Buttons_Proc);
	Init_Bmps_Globals();
	return 1;
}

// *************************************************************************
// *						Render_Buttons_Proc Terry					   *
// *************************************************************************
LRESULT CALLBACK SB_Equity::Render_Buttons_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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

	case WM_COMMAND:

		//-------------------------------------------------------- Show Grid
		if (LOWORD(wParam) == IDC_TBSHOWGRID)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWGRID);

			if (App->CLSB_Grid->ShowGridFlag == 1)
			{
				App->CLSB_Grid->Grid_SetVisible(0);
				App->CLSB_Grid->ShowGridFlag = 0;

				//App->CLSB_TopBar->Toggle_Grid_Flag = 0;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOff_Bmp);
			}
			else
			{
				App->CLSB_Grid->Grid_SetVisible(1);
				App->CLSB_Grid->ShowGridFlag = 1;

				//App->CLSB_TopBar->Toggle_Grid_Flag = 1;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

			}

			return TRUE;
		}

		//-------------------------------------------------------- Show Hair
		if (LOWORD(wParam) == IDC_TBSHOWHAIR)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWHAIR);

			if (App->CLSB_Grid->ShowHair == 1)
			{
				App->CLSB_Grid->ShowHair = 0;
				App->CLSB_Grid->Hair_SetVisible(0);

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOff_Bmp);
			}
			else
			{
				App->CLSB_Grid->ShowHair = 1;
				App->CLSB_Grid->Hair_SetVisible(1);

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);
			}

			return TRUE;
		}

		//-------------------------------------------------------- Show Info
		if (LOWORD(wParam) == IDC_TBINFO2)
		{
			/*if (App->CL_Editor_Gui->Show_Model_Data_F == 1)
			{
				App->CL_Editor_Gui->Close_Model_Data();
			}
			else
			{
				App->CL_Editor_Gui->Start_Model_Data();
			}*/


			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSHOWFACES)
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWFACES);

				if (App->CLSB_Ogre->RenderListener->ShowFaces == 1)
				{
					if (App->CLSB_Ogre->RenderListener->ShowFaces == 1)
						App->CLSB_Ogre->RenderListener->ShowFaces = 0;

					//App->CLSB_TopBar->Toggle_Faces_Flag = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);
				}
				else
				{
					App->CLSB_Ogre->RenderListener->ShowFaces = 1;
					//App->CLSB_TopBar->Toggle_Faces_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOn_Bmp);
				}
			}

			return TRUE;
		}

		//-------------------------------------------------------- Show Textures
		if (LOWORD(wParam) == IDC_BTSHOWTEXTURES)
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_BTSHOWTEXTURES);

				if (App->CLSB_Ogre->RenderListener->ShowTextured == 1)
				{
					App->CLSB_Ogre->RenderListener->ShowTextured = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);
				}
				else
				{
					App->CLSB_Ogre->RenderListener->ShowTextured = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOn_Bmp);
				}
			}

			return TRUE;
		}

		//-------------------------------------------------------- Show Normals
		if (LOWORD(wParam) == IDC_BTSHOWNORMALS)
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_BTSHOWNORMALS);

				if (App->CLSB_Ogre->RenderListener->ShowNormals == 1)
				{
					App->CLSB_Ogre->RenderListener->ShowNormals = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);
				}
				else
				{
					App->CLSB_Ogre->RenderListener->ShowNormals = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOn_Bmp);
				}
			}

			return TRUE;
		}

		//-------------------------------------------------------- Show Light
		if (LOWORD(wParam) == IDC_BTSHOWLIGHT2)
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_BTSHOWLIGHT2);

				if (App->CLSB_Ogre->RenderListener->Light_Activated == 1)
				{
					App->CLSB_Ogre->RenderListener->Light_Activated = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);
				}
				else
				{
					App->CLSB_Ogre->RenderListener->Light_Activated = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOn_Bmp);
				}
			}

			return TRUE;
		}

		//-------------------------------------------------------- Show Points
		if (LOWORD(wParam) == IDC_BTSHOWPOINTS)
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_BTSHOWPOINTS);

				if (App->CLSB_Ogre->RenderListener->ShowPoints == 1)
				{
					App->CLSB_Ogre->RenderListener->ShowPoints = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);
				}
				else
				{
					App->CLSB_Ogre->RenderListener->ShowPoints = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOn_Bmp);
				}
			} 
			return TRUE;
		}

		//-------------------------------------------------------- Show Bones
		if (LOWORD(wParam) == IDC_BTSHOWBONES)
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_BTSHOWBONES);

				if (App->CLSB_Ogre->RenderListener->ShowBones == 1)
				{
					App->CLSB_Ogre->RenderListener->ShowBones = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOff_Bmp);
				}
				else
				{
					App->CLSB_Ogre->RenderListener->ShowBones = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOn_Bmp);
				}
			}

			return TRUE;
		}

		//-------------------------------------------------------- Show Bound Box
		if (LOWORD(wParam) == IDC_TBBOUNDBOX)
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBBOUNDBOX);

				if (App->CLSB_Ogre->RenderListener->ShowBoundingBox == 1)
				{
					App->CLSB_Ogre->RenderListener->ShowBoundingBox = 0;
					//App->CLSB_TopBar->Toggle_BBox_Flag = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOff_Bmp);
				}
				else
				{
					App->CLSB_Ogre->RenderListener->ShowBoundingBox = 1;
					//App->CLSB_TopBar->Toggle_BBox_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOn_Bmp);
				}
			}

			return TRUE;
		}
		break;
	}
	return FALSE;
}

// *************************************************************************
// *						Init_Bmps_Globals Terry Bernie				   *
// *************************************************************************
void SB_Equity::Init_Bmps_Globals(void)
{

	HWND Temp = GetDlgItem(Render_Buttons_hWnd, IDC_TBSHOWGRID);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_TBSHOWHAIR);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_TBINFO2);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_TBBOUNDBOX);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOff_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_TBSHOWFACES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWTEXTURES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWPOINTS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWBONES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOff_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWNORMALS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWLIGHT2);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);


	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_TBINFO2);
	TOOLINFO ti8 = { 0 };
	ti8.cbSize = sizeof(ti8);
	ti8.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti8.uId = (UINT_PTR)Temp;
	ti8.lpszText = "Show Model Information";
	ti8.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti8);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_TBSHOWHAIR);
	TOOLINFO ti9 = { 0 };
	ti9.cbSize = sizeof(ti9);
	ti9.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti9.uId = (UINT_PTR)Temp;
	ti9.lpszText = "Toggle Main Cross Hair";
	ti9.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti9);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_TBSHOWGRID);
	TOOLINFO ti10 = { 0 };
	ti10.cbSize = sizeof(ti10);
	ti10.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti10.uId = (UINT_PTR)Temp;
	ti10.lpszText = "Toggle Main Grid";
	ti10.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti10);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_TBBOUNDBOX);
	TOOLINFO ti11 = { 0 };
	ti11.cbSize = sizeof(ti11);
	ti11.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti11.uId = (UINT_PTR)Temp;
	ti11.lpszText = "Toggle Bounding Box";
	ti11.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti11);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_TBSHOWFACES);
	TOOLINFO ti12 = { 0 };
	ti12.cbSize = sizeof(ti12);
	ti12.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti12.uId = (UINT_PTR)Temp;
	ti12.lpszText = "Toggle Show Faces";
	ti12.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti12);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWTEXTURES);
	TOOLINFO ti13 = { 0 };
	ti13.cbSize = sizeof(ti13);
	ti13.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti13.uId = (UINT_PTR)Temp;
	ti13.lpszText = "Toggle Show Textures";
	ti13.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti13);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWPOINTS);
	TOOLINFO ti14 = { 0 };
	ti14.cbSize = sizeof(ti14);
	ti14.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti14.uId = (UINT_PTR)Temp;
	ti14.lpszText = "Toggle Show Mesh Points";
	ti14.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti14);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWBONES);
	TOOLINFO ti15 = { 0 };
	ti15.cbSize = sizeof(ti15);
	ti15.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti15.uId = (UINT_PTR)Temp;
	ti15.lpszText = "Toggle Show Bones";
	ti15.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti15);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWNORMALS);
	TOOLINFO ti16 = { 0 };
	ti16.cbSize = sizeof(ti16);
	ti16.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti16.uId = (UINT_PTR)Temp;
	ti16.lpszText = "Toggle Show Normals";
	ti16.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti16);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWLIGHT2);
	TOOLINFO ti17 = { 0 };
	ti17.cbSize = sizeof(ti17);
	ti17.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti17.uId = (UINT_PTR)Temp;
	ti17.lpszText = "Toggle Show Light";
	ti17.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti17);

}

// *************************************************************************
// *		OgreView_3D_Proc:- Terry and Hazel Flanigan 2023 			   *
// *************************************************************************
LRESULT CALLBACK SB_Equity::Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	/*case WM_ACTIVATE:
	{
	
		Beep(400, 50);
		break;
	}*/

	case WM_MOUSEWHEEL:
	{
		if (App->CLSB_Ogre->OgreListener->Pl_LeftMouseDown == 0)
		{
			{
				int zDelta = (short)HIWORD(wParam);    // wheel rotation

				if (zDelta > 0)
				{
					//App->CLSB_Ogre->OgreListener->Wheel_Move = -1;
				}
				else if (zDelta < 0)
				{
					//App->CLSB_Ogre->OgreListener->Wheel_Move = 1;
				}
				return 1;
			}
		}
	}

	case WM_MOUSEMOVE: // ok up and running and we have a loop for mouse
	{
		//App->Flash_Window();
		//SetFocus(App->CLSB_Ogre->Ogre_Window_hWnd);
		break;
	}

	// Right Mouse Button
	case WM_RBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		
		if (App->CLSB_Ogre->OgreIsRunning == 1)
		{
			SetCapture(App->CLSB_Ogre->Ogre_Window_hWnd);// Bernie
			SetCursorPos(App->CursorPosX, App->CursorPosY);
			App->CLSB_Ogre->OgreListener->Pl_RightMouseDown = 1;
			App->CUR = SetCursor(NULL);
			return 1;
		}

		return 1;
	}
	case WM_RBUTTONUP:
	{
		if (App->CLSB_Ogre->OgreIsRunning == 1)
		{
			ReleaseCapture();
			App->CLSB_Ogre->OgreListener->Pl_RightMouseDown = 0;
			SetCursor(App->CUR);
			return 1;
		}

		return 1;
	}

	// Left Mouse Button
	case WM_LBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		if (App->CLSB_Ogre->OgreIsRunning == 1)
		{
			SetCapture(App->CLSB_Ogre->Ogre_Window_hWnd);// Bernie
			SetCursorPos(App->CursorPosX, App->CursorPosY);

			App->CLSB_Ogre->OgreListener->Pl_LeftMouseDown = 1;

			App->CUR = SetCursor(NULL);

			return 1;
		}

		return 1;
	}

	case WM_LBUTTONUP:
	{

		if (App->CLSB_Ogre->OgreIsRunning == 1)
		{
			ReleaseCapture();
			App->CLSB_Ogre->OgreListener->Pl_LeftMouseDown = 0;
			SetCursor(App->CUR);
			return 1;
		}

		return 1;
	}
	//case WM_KEYDOWN:
	//	switch (wParam)
	//	{
	//	case 'C':
	//		if (GetAsyncKeyState(VK_CONTROL))
	//		{
	//			//		//		App->CL10_Objects_Com->Copy_Object();
	//			//		//		return 1;
	//		}
	//	case 'V':
	//		if (GetAsyncKeyState(VK_CONTROL))
	//		{
	//			//		//		App->CL10_Objects_Com->Paste_Object();
	//			//		//		return 1;
	//		}
	//		//	return 1;
	//		//	//	// more keys here
	//	}break;
	}

	return DefWindowProc(hDlg, message, wParam, lParam);
}

// *************************************************************************
// *			Resize_3DView:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Equity::Resize_3DView()
{
	RECT rcl;
	GetClientRect(Equity_Main_hWnd, &rcl);

	int X = rcl.right-10;
	int Y = rcl.bottom - 90;

	SetWindowPos(App->CLSB_Ogre->Ogre_Window_hWnd, NULL, 4, 80, X, Y, SWP_NOZORDER);

	App->CLSB_Ogre->mWindow->windowMovedOrResized();
	App->CLSB_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CLSB_Ogre->mWindow->getWidth() / (Ogre::Real)App->CLSB_Ogre->mWindow->getHeight());
	App->CLSB_Ogre->mCamera->yaw(Ogre::Radian(0));

	Root::getSingletonPtr()->renderOneFrame();
}