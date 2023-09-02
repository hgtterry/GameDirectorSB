#include "StdAfx.h"
#include "AB_App.h"
#include "resource.h"
#include "SB_Equity.h"

SB_Equity::SB_Equity(void)
{
	mAutoLoad = 0;
	EquitySB_Dialog_Created = 0;
	EquitySB_Dialog_Visible = 0;
	Equity_Start_Mode = 0;

	OgreView_3D_hWnd =		nullptr;
	Render_Buttons_hWnd =	nullptr;

	First_Run = 1;

	Close_Equity_Flag = 0;

	m_pDoc = nullptr;
}

SB_Equity::~SB_Equity(void)
{
}


// *************************************************************************
// *		Get_CurrentDocument:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Equity::Get_CurrentDocument()
{
	m_pDoc = NULL;
	m_pDoc = (CFusionDoc*)App->m_pMainFrame->GetCurrentDoc();
	if (m_pDoc == NULL)
	{
		App->Say("Cant Get Current Document");
	}
}

// *************************************************************************
// *			Auto_Load_File:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Equity::Auto_Load_File()
{
	if (mAutoLoad == 1)
	{
		char Path[MAX_PATH];
		strcpy(Path, App->WorldEditor_Directory);
		strcat(Path, "Data\\Temp.Wepf");

		strcpy(App->CLSB_Loader->Path_FileName, Path);
		strcpy(App->CLSB_Loader->FileName, "Temp.Wepf");

		bool test = App->CLSB_FileIO->Check_File_Exist(Path);
		if (test == 0)
		{
			App->Message_ToFile("Auto_Load_File No File");
		}
		else
		{
			App->Message_ToFile("Auto_Load_File File Ok");
		}

		App->CLSB_Loader->Read_Project_File(Path);

		test = App->CLSB_Loader->Load_File_Wepf();
		if (test == 0)
		{
			return 0;
		}

		return 1;
	}

	return 1;
}

// *************************************************************************
// *			Show_Equity_Dialog:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Equity::Show_Equity_Dialog(bool Show)
{
	
	if (App->Equity_Dlg_hWnd)
	{
		if (Show == 1)
		{
			EquitySB_Dialog_Visible = 1;
			ShowWindow(App->Equity_Dlg_hWnd, SW_SHOW);
		}
		else
		{
			if (Equity_Start_Mode == 2)
			{
				App->CLSB_Camera_EQ->Save_Camera_Pos();
			}
			
			EquitySB_Dialog_Visible = 0;
			ShowWindow(App->Equity_Dlg_hWnd, SW_HIDE);
		}
	}
	else
	{
		App->Say("Cant Start");
	}
}

// *************************************************************************
// *		Start_Equity_Dialog_New:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_Equity::Start_Equity_Dialog_New()
{
	if (EquitySB_Dialog_Created == 0)
	{
		App->Equity_Dlg_hWnd = nullptr;
		mAutoLoad = 0;

		App->Equity_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_EQUITYME, App->MainHwnd, (DLGPROC)Equity_Dialog_New_Proc);

		Start_Render_Buttons();
		App->CLSB_TopTabs_Equity->Start_Tabs();

		EquitySB_Dialog_Created = 1;

		App->CLSB_Ogre->RenderHwnd = App->ViewGLhWnd;

		Resize_3DView();

		Set_Mode_Equity();

	}
}

// **************************************************************************
// *			Equity_Dialog_New_Proc:- Terry and Hazel Flanigan 2022		*
// **************************************************************************
LRESULT CALLBACK SB_Equity::Equity_Dialog_New_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->ViewGLhWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_VIEWER3D, hDlg, NULL);// (DLGPROC)Ogre3D_Proc);
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

	case WM_SIZE:
	{
		App->CLSB_Equity->Resize_3DView();
		Ogre::Root::getSingletonPtr()->renderOneFrame();
	}break;

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == ID_RENDER_BRUSEHS)
		{
			if (App->CLSB_Ogre->RenderListener->ShowBrushes == 1)
			{
				App->CLSB_Ogre->RenderListener->ShowBrushes = 0;
			}
			else
			{
				App->CLSB_Ogre->RenderListener->ShowBrushes = 1;
			}

			return TRUE;
		}
		
		if (LOWORD(wParam) == ID_DEBUG_PREFERENCESWE)
		{
			App->CLSB_Preferences->Start_Preferences_Dlg();
			return TRUE;
		}

		if (LOWORD(wParam) == ID_DEBUG_GENERAL)
		{
			if (App->CLSB_Ogre->RenderListener->ShowBoundingGroup == 1)
			{
				App->CLSB_Ogre->RenderListener->ShowBoundingGroup = 0;
			}
			else
			{
				App->CLSB_Ogre->RenderListener->ShowBoundingGroup = 1;
			}

			return TRUE;
		}

		if (LOWORD(wParam) == ID_DEBUG_ACTORTOWORLD)
		{
			App->CLSB_Loader->Load_ActorWorld();
			return TRUE;
		}

		if (LOWORD(wParam) == ID_DEBUG_SHOWCAMERAPOSITIONS)
		{
			if (App->CLSB_ImGui->Show_Camera_Pos_F == 1)
			{
				App->CLSB_ImGui->Close_Camera_Pos();
			}
			else
			{
				App->CLSB_ImGui->Start_Camera_Pos();
			}
			return TRUE;
		}

		if (LOWORD(wParam) == ID_DEBUG_BOUNDINGBOX)
		{
			if (App->CLSB_Model->Model_Loaded == 1)
			{
				if (App->CLSB_ImGui->Show_BB_Data_F == 1)
				{
					App->CLSB_ImGui->Close_BB_Data();
				}
				else
				{
					App->CLSB_ImGui->Start_BB_Data();
				}
			}
			return TRUE;
		}

		// Physics
		if (LOWORD(wParam) == ID_PHYSICS_PHYSICS)
		{
			if (App->CLSB_Ogre->OgreListener->GD_Run_Physics == 1)
			{
				App->CLSB_Ogre->OgreListener->GD_Run_Physics = 0;
			}
			else
			{
				App->CLSB_Ogre->OgreListener->GD_Run_Physics = 1;
			}
			return TRUE;
		}

		if (LOWORD(wParam) == ID_PHYSICS_DEBUGDRAW)
		{
			int f = App->CLSB_Bullet->Phys_Body->getCollisionFlags();
			
			if (App->CLSB_Ogre->OgreListener->Dubug_Physics_DrawAll == 1)
			{
				App->CLSB_Ogre->OgreListener->Dubug_Physics_DrawAll = 0;
				App->CLSB_Bullet->Phys_Body->setCollisionFlags(f | (1 << 5));
			}
			else
			{
				App->CLSB_Ogre->OgreListener->Dubug_Physics_DrawAll = 1;
				App->CLSB_Bullet->Phys_Body->setCollisionFlags(f& (~(1 << 5)));
			}
			
			return TRUE;
		}

		// File Import
		if (LOWORD(wParam) == ID_IMPORT_GENESIS3DACT)
		{
			App->CLSB_Loader->RFActor_Loader();
			return TRUE;
		}

		if (LOWORD(wParam) == ID_IMPORT_WAVEFRONTOBJ)
		{
			App->Clear_ErrorLog();
			App->CLSB_Loader->LoadError = 0;

			App->CLSB_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;
			App->CLSB_Loader->Assimp_Loader(App->Equity_Dlg_hWnd,"Wavefront OBJ   *.obj\0*.obj\0", "Wavefront OBJ");

			if (App->CLSB_Loader->LoadError == 1)
			{
				App->Say("Loaded With Errors");
				App->CLSB_Dialogs->Start_ListData(1);
			}

			return TRUE;
		}

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

		if (LOWORD(wParam) == ID_EXPORT_WAVEFRONTOBJ)
		{
			App->CLSB_Exporter->Object_Model();
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
			App->CLSB_Camera_EQ->Set_Camera_Mode(Enums::CamDetached);
			return TRUE;
		}

		if (LOWORD(wParam) == ID_CAMERAMODE_MODEL)
		{
			App->CLSB_Camera_EQ->Set_Camera_Mode(Enums::CamModel);
			return TRUE;
		}

		if (LOWORD(wParam) == ID_CAMERA_RESETVIEW)
		{
			App->CLSB_Camera_EQ->Reset_View();
			return TRUE;
		}

		if (LOWORD(wParam) == ID_CAMERA_ZEROVIEW)
		{
			App->CLSB_Camera_EQ->Zero_View();
			return TRUE;
		}

		/*if (LOWORD(wParam) == IDC_TEST)
		{
			App->CLSB_Ogre->OgreListener->StopOgre = 1;
			App->CLSB_Ogre->OgreIsRunning = 0;
			return TRUE;
		}*/

		if (LOWORD(wParam) == IDOK)
		{

			/*App->CLSB_Equity->EquitySB_Dialog_Created = 0;
			EndDialog(hDlg, LOWORD(wParam));*/
			App->CLSB_Equity->Show_Equity_Dialog(false);
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{

			if (App->CLSB_Equity->Close_Equity_Flag == 1)
			{
				EndDialog(hDlg, LOWORD(wParam));
				App->Get_Current_Document();
				App->m_pDoc->OnCloseDocument();
			}

			App->CLSB_Equity->Show_Equity_Dialog(false);
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
	Render_Buttons_hWnd = nullptr;

	Render_Buttons_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_TB_BUTTONS, App->Equity_Dlg_hWnd, (DLGPROC)Render_Buttons_Proc);
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

		//-------------------------------------------------------- Full Screen
		if (LOWORD(wParam) == IDC_BTTB_FULLSCREEN)
		{
			App->CLSB_Scene->Go_FullScreen_Mode();

			return TRUE;
		}
		//-------------------------------------------------------- Show Info
		if (LOWORD(wParam) == IDC_TBINFO2)
		{
			if (App->CLSB_ImGui->Show_Model_Data_F == 1)
			{
				App->CLSB_ImGui->Close_Model_Data();
			}
			else
			{
				App->CLSB_ImGui->Start_Model_Data();
			}

			return TRUE;
		}

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
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOn_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWPOINTS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWBONES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOff_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWNORMALS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTSHOWLIGHT2);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTTB_FULLSCREEN);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_FullScreen_Bmp);

	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);
	SendMessage(hTooltip_TB_2, TTM_SETMAXTIPWIDTH, 0, 150);

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

	Temp = GetDlgItem(Render_Buttons_hWnd, IDC_BTTB_FULLSCREEN);
	TOOLINFO ti18 = { 0 };
	ti18.cbSize = sizeof(ti11);
	ti18.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti18.uId = (UINT_PTR)Temp;
	ti18.lpszText = "Full Screen Mode\r\nPress Esc to Exit";
	ti18.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti18);

}

// *************************************************************************
// *		OgreView_3D_New_Proc:- Terry and Hazel Flanigan 2023 		   *
// *************************************************************************
LRESULT CALLBACK SB_Equity::Ogre3D_New_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
	{
		return TRUE;
	}

	case WM_MOUSEWHEEL:
	{
		if (App->CLSB_Ogre->OgreListener->Pl_LeftMouseDown == 0)
		{
			{
		
				int zDelta = (short)HIWORD(wParam);    // wheel rotation

				if (zDelta > 0)
				{
					App->CLSB_Ogre->OgreListener->Wheel = -1;
				}
				else if (zDelta < 0)
				{
					App->CLSB_Ogre->OgreListener->Wheel = 1;
				}
				return 1;
			}
		}
	}

	case WM_MOUSEMOVE: // ok up and running and we have a loop for mouse
	{
		App->CLSB_Ogre->m_imgui.mouseMoved();

		SetFocus(App->ViewGLhWnd);
		break;
	}

	// Right Mouse Button
	case WM_RBUTTONDOWN: // BERNIE_HEAR_FIRE 
	{
		App->CLSB_Ogre->m_imgui.mousePressed();

		if (!ImGui::GetIO().WantCaptureMouse)
		{
			if (App->CLSB_Ogre->OgreIsRunning == 1)
			{
				POINT p;
				GetCursorPos(&p);
				ScreenToClient(App->MainHwnd, &p);
				App->CursorPosX = p.x;
				App->CursorPosY = p.y;
				App->CLSB_Ogre->OgreListener->Pl_Cent500X = p.x;
				App->CLSB_Ogre->OgreListener->Pl_Cent500Y = p.y;

				SetCapture(App->ViewGLhWnd);
				SetCursorPos(App->CursorPosX, App->CursorPosY);
				App->CLSB_Ogre->OgreListener->Pl_RightMouseDown = 1;
				App->CUR = SetCursor(NULL);
				return 1;
			}
			else
			{
				App->CLSB_Ogre->OgreListener->Pl_LeftMouseDown = 1;
			}

		}

		return 1;
	}
	case WM_RBUTTONUP:
	{
		App->CLSB_Ogre->m_imgui.mousePressed();

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
		App->CLSB_Ogre->m_imgui.mousePressed();

		if (!ImGui::GetIO().WantCaptureMouse)
		{
			if (App->CLSB_Ogre->OgreIsRunning == 1)
			{

				POINT p;
				GetCursorPos(&p);
				ScreenToClient(App->MainHwnd, &p);
				App->CursorPosX = p.x;
				App->CursorPosY = p.y;
				App->CLSB_Ogre->OgreListener->Pl_Cent500X = p.x;
				App->CLSB_Ogre->OgreListener->Pl_Cent500Y = p.y;

				SetCapture(App->ViewGLhWnd);// Bernie
				SetCursorPos(App->CursorPosX, App->CursorPosY);

				App->CLSB_Ogre->OgreListener->Pl_LeftMouseDown = 1;

				App->CUR = SetCursor(NULL);

				return 1;
			}
			else
			{
				App->CLSB_Ogre->OgreListener->Pl_LeftMouseDown = 1;
			}
		}


		return 1;
	}

	case WM_LBUTTONUP:
	{
		App->CLSB_Ogre->m_imgui.mouseReleased();

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
	GetClientRect(App->Equity_Dlg_hWnd, &rcl);

	int X = rcl.right-10;
	int Y = rcl.bottom - 90;

	SetWindowPos(App->ViewGLhWnd, NULL, 4, 80, X, Y, SWP_NOZORDER);
	
	
	if (App->CLSB_Ogre->OgreIsRunning == 1)
	{
		App->CLSB_Ogre->mWindow->windowMovedOrResized();
		App->CLSB_Ogre->mCamera->setAspectRatio((Ogre::Real)App->CLSB_Ogre->mWindow->getWidth() / (Ogre::Real)App->CLSB_Ogre->mWindow->getHeight());
		App->CLSB_Ogre->mCamera->yaw(Ogre::Radian(0));

		Root::getSingletonPtr()->renderOneFrame();
	}
}

// *************************************************************************
// *	  		Set_Mode_Equity:- Terry and Hazel Flanigan 2023				*
// *************************************************************************
void SB_Equity::Set_Mode_Equity()
{
	Equity_Start_Mode = 1;

	App->CLSB_TopTabs_Equity->Hide_Tabs();
	ShowWindow(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, SW_SHOW);
	App->CLSB_TopTabs_Equity->Toggle_Tabs_Camera_Flag = 1;

	App->CLSB_ImGui->Show_Physics_Console = 0;

	App->CLSB_TopTabs_Equity->Toggle_Camera_Model_Flag = 1;

	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_BT_TT_MODEL), 1);
	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_FIRST_MODEX), 0);
	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_BT_TT_FREE), 0);
	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, IDC_UPDATE2), 0);

	if (App->CLSB_Ogre->OgreIsRunning == 1)
	{
		App->CLSB_Ogre->BulletListener->Render_Debug_Flag = 0;
	}

	RedrawWindow(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
}

// *************************************************************************
// *				Do_Equity:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
void SB_Equity::Do_Equity()
{
	App->CLSB_Model->Clear_Model_And_Reset();

	App->CLSB_Grid->Reset_View();

	App->CLSB_TopTabs_Equity->Camera_Set_Model();

	Equity_Start_Mode = 1;

	App->CLSB_TopTabs_Equity->Hide_Tabs();
	ShowWindow(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, SW_SHOW);
	App->CLSB_TopTabs_Equity->Toggle_Tabs_Camera_Flag = 1;

	App->CLSB_ImGui->Show_Physics_Console = 0;

	App->CLSB_TopTabs_Equity->Toggle_Camera_Model_Flag = 1;

	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_BT_TT_MODEL), 1);
	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_FIRST_MODEX), 0);
	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_BT_TT_FREE), 0);
	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, IDC_UPDATE2), 0);

	if (App->CLSB_Ogre->OgreIsRunning == 1)
	{
		App->CLSB_Ogre->BulletListener->Render_Debug_Flag = 0;
	}

	RedrawWindow(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	App->CLSB_Model->Model_Type = Enums::LoadedFile_Assimp;
	App->CLSB_Ogre->RenderListener->ShowTextured = 1;
	App->CLSB_Model->Model_Loaded = 1;
	App->CLSB_Equity->Show_Equity_Dialog(true);
}

// *************************************************************************
// *			Do_Preview_Selected:- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
void SB_Equity::Do_Preview_Selected()
{
	bool AllGood = 0;

	Equity_Start_Mode = 3;

	Get_CurrentDocument();

	int NumSelBrushes = SelBrushList_GetSize(m_pDoc->pSelBrushes);

	if (NumSelBrushes == 0)
	{
		App->Say("No Brushes Selected");
		return;
	}

	
	for (int i = 0; i < NumSelBrushes; ++i)
	{
		Brush* pBrush = SelBrushList_GetBrush(App->m_pDoc->pSelBrushes, i);
		if (pBrush->Flags & 1 || pBrush->Flags & 1024)
		{
			AllGood = 1;
		}
	}

	if (AllGood == 1)
	{
		App->CLSB_Model->Set_Equity();
		App->CLSB_Camera_EQ->Reset_Orientation();

		App->CLSB_Camera_EQ->Set_Camera_Mode(Enums::CamModel);

		App->CLSB_TopTabs_Equity->Hide_Tabs();
		ShowWindow(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, SW_SHOW);
		App->CLSB_TopTabs_Equity->Toggle_Tabs_Camera_Flag = 1;

		App->CLSB_TopTabs_Equity->Camera_Set_Model();

		EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_BT_TT_FREE), 0);
		EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_BT_TT_MODEL), 1);
		EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_FIRST_MODEX), 0);
		EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, IDC_UPDATE2), 0);

		App->CLSB_ImGui->Show_Physics_Console = 0;
		App->CLSB_Ogre->BulletListener->Render_Debug_Flag = 0;

		App->CLSB_Camera_EQ->Reset_View();

		if (App->CLSB_Ogre->OgreIsRunning == 1)
		{
			App->CLSB_Ogre->OgreListener->GD_Run_Physics = 0;
		}

		RedrawWindow(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

		App->CLSB_Scene->Build_World(1);
		App->CLSB_Bullet->Create_Brush_Trimesh(0);
		App->CLSB_Model->Set_BondingBox_Brushes();
		App->CLSB_Dimensions->Centre_Model_Mid_Brushes();

		App->CLSB_Model->Model_Loaded = 1;
		App->CLSB_Ogre->RenderListener->ShowBrushes = 1;
		App->CLSB_Ogre->RenderListener->ShowTextured = 1;
		App->CLSB_Model->Model_Type = Enums::LoadedFile_Brushes;
		App->CLSB_Equity->Show_Equity_Dialog(true);
	}
	else
	{
		App->Say("Only Cut Brush Selected","Cant not build Geometry from only Cut Brushes");

	}

}

// *************************************************************************
// *			Do_Preview_All():- Terry and Hazel Flanigan 2023	  	   *
// *************************************************************************
void SB_Equity::Do_Preview_All()
{
	Get_CurrentDocument();

	Equity_Start_Mode = 2;

	App->CLSB_ImGui->Show_Physics_Console = 1;

	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_BT_TT_MODEL), 0);
	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_FIRST_MODEX), 1);
	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Camera_TB_hWnd, IDC_BT_TT_FREE), 1);
	EnableWindow(GetDlgItem(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, IDC_UPDATE2), 1);

	App->CLSB_Ogre->BulletListener->Render_Debug_Flag = 1;

	RedrawWindow(App->CLSB_TopTabs_Equity->Tabs_TB_hWnd_Eq, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	Ogre::Vector3 OldCamPos = App->CLSB_Camera_EQ->Saved_Pos;
	App->CLSB_Ogre->mCamera->setPosition(Ogre::Vector3(OldCamPos.x, OldCamPos.y, OldCamPos.z));


	//------------------------------------------------------
	int BCount = App->CL_World->Get_Brush_Count();
	if (BCount == 0)
	{
		App->Say("No Scene to Preview");
		return;
	}

	App->CLSB_TopTabs->Update_Dlg_Controls();

	OldCamPos = App->CLSB_Camera_EQ->Saved_Pos;
	Ogre::Quaternion OldCamRot = App->CLSB_Camera_EQ->Saved_Rotation;
	App->CLSB_Ogre->mCamera->setPosition(Ogre::Vector3(OldCamPos.x, OldCamPos.y, OldCamPos.z));
	App->CLSB_Ogre->mCamera->setOrientation(OldCamRot);

	App->CLSB_Scene->Build_World(0);
	
	App->CLSB_Bullet->Create_Brush_Trimesh(0);
	App->CLSB_Model->Set_BondingBox_Brushes();


	App->CLSB_Model->Set_Equity();
	App->CLSB_Camera_EQ->Reset_Orientation();
	App->CLSB_Camera_EQ->Set_Camera_Mode(Enums::CamDetached);
	App->CLSB_TopTabs_Equity->Camera_Set_Free();

	App->CLSB_Model->Model_Loaded = 1;
	App->CLSB_Ogre->RenderListener->ShowBrushes = 1;
	App->CLSB_Ogre->RenderListener->ShowTextured = 1;
	App->CLSB_Model->Model_Type = Enums::LoadedFile_Brushes;
	App->CLSB_Equity->Show_Equity_Dialog(true);

	//-----------------------------------------------------
	if (App->CLSB_Model->Player_Count == 0)
	{
		App->CLSB_Player->Create_Player_Object();
	}

	if (App->CLSB_Equity->First_Run == 1)
	{
		App->CLSB_Camera_EQ->Zero_View();
		App->CLSB_Equity->First_Run = 0;
	}

}