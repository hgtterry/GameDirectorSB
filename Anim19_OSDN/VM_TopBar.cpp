#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "VM_TopBar.h"


VM_TopBar::VM_TopBar()
{
	TabsHwnd =	nullptr;
	
	Tabs_TB_hWnd = nullptr;

	Camera_TB_hWnd =		nullptr;
	Motions_TB_hWnd =		nullptr;
	Dimensions_TB_hWnd =	nullptr;
	Groups_TB_hWnd =		nullptr;
	Physics_TB_hWnd =		nullptr;

	MouseOption_DlgHwnd =	nullptr;

	// Main Controls
	Toggle_Faces_Flag = 0;
	Toggle_Textures_Flag = 0;
	Toggle_Points_Flag = 0;
	Toggle_Bones_Flag = 0;
	Toggle_Normals_Flag = 0;
	Toggle_BBox_Flag = 0;
	Toggle_Grid_Flag = 1;
	Toggle_Hair_Flag = 1;

	Toggle_Tabs_Old_Flag = 1;
	Toggle_Tabs_Motions_Flag = 0;
	Toggle_Tabs_Dimensions_Flag = 0;
	Toggle_Tabs_Groups_Flag = 0;
	Toggle_Tabs_Shapes_Flag = 0;


	Toggle_GroupsOnly_Flag = 0;

	// Motions
	Toggle_Play_Flag = 0;

	// Camera
	Toggle_Model_Flag = 1;
	Toggle_World_Flag = 0;

	// Dimensions - >ImGui Flags
	
}


VM_TopBar::~VM_TopBar()
{
}

// *************************************************************************
// *	  					Reset_Class  	Terry						   *
// *************************************************************************
void VM_TopBar::Reset_Class()
{
	Toggle_Faces_Flag = 0;
	Toggle_Textures_Flag = 0;
	Toggle_Points_Flag = 0;
	Toggle_Bones_Flag = 0;

	Toggle_Tabs_Old_Flag = 1;
	Toggle_Tabs_Motions_Flag = 0;
	Toggle_Tabs_Dimensions_Flag = 0;
	Toggle_Tabs_Groups_Flag = 0;
	Toggle_GroupsOnly_Flag = 0;

	// Motions
	Toggle_Play_Flag = 0;

	// Camera
	Toggle_Model_Flag = 1;
	Toggle_World_Flag = 0;

	Reset_Main_Controls();
	TogglePlayBmp();

	// Dimensions - >ImGui Flags
	
	//App->Cl19_Ogre->RenderListener->ShowOnlySubMesh = 0;

	App->CL_Vm_TopBar->Hide_Tabs();
	ShowWindow(App->CL_Vm_TopBar->Camera_TB_hWnd, SW_SHOW);
	App->CL_Vm_TopBar->Toggle_Tabs_Old_Flag = 1;

	RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	return;
}

// *************************************************************************
// *	  				Start_TopBar_Globals  	Terry					   *
// *************************************************************************
bool VM_TopBar::Start_TopBar_Globals()
{
	CreateDialog(App->hInst,(LPCTSTR)IDD_TOPBAR,App->Fdlg,(DLGPROC)TopBar_Globals_Proc);
	Init_Bmps_Globals();
	return 1;
}

// *************************************************************************
// *						TopBar_Globals_Proc Terry					   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::TopBar_Globals_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		App->CL_Vm_TopBar->TabsHwnd = hDlg;
	
		SendDlgItemMessage(hDlg, IDC_TBSHOWFACES, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBSHOWTEXTURE, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBPOINTS, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBSHOWBONES, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBNORMALS, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBBOUNDBOX, WM_SETFONT, (WPARAM)App->Font_CB15_Bold, MAKELPARAM(TRUE, 0));
		
		App->CL_Vm_TopBar->Start_Tabs_Headers();
		App->CL_Vm_TopBar->Start_Camera_TB();
		App->CL_Vm_TopBar->Start_Motions_TB();
		App->CL_Vm_TopBar->Start_Dimensions_TB();
		App->CL_Vm_TopBar->Start_Groups_TB();
		App->CL_Vm_TopBar->Start_Shapes_TB();
		
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
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_TBSHOWTEXTURE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Textures_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSHOWFACES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Faces_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBPOINTS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Points_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSHOWBONES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Bones_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBNORMALS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Normals_Flag);
			return CDRF_DODEFAULT;
		}
		
		if (some_item->idFrom == IDC_TBBOUNDBOX && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_BBox_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSHOWGRID && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Grid_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSHOWHAIR && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Hair_Flag);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
		
		// -----------------------------------------------------

		if (LOWORD(wParam) == IDC_TBSHOWGRID)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWGRID);

			if (App->Cl_Grid->ShowGridFlag == 1)
			{
				App->Cl_Grid->Grid_SetVisible(0);
				App->Cl_Grid->ShowGridFlag = 0;

				App->CL_Vm_TopBar->Toggle_Grid_Flag = 0;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOff_Bmp);
			}
			else
			{
				App->Cl_Grid->Grid_SetVisible(1);
				App->Cl_Grid->ShowGridFlag = 1;

				App->CL_Vm_TopBar->Toggle_Grid_Flag = 1;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSHOWHAIR)
		{
			HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWHAIR);

			if (App->Cl_Grid->ShowHair == 1)
			{
				App->Cl_Grid->ShowHair = 0;
				App->Cl_Grid->Hair_SetVisible(0);	

				App->CL_Vm_TopBar->Toggle_Hair_Flag = 0;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOff_Bmp);
			}
			else
			{
				App->Cl_Grid->ShowHair = 1;
				App->Cl_Grid->Hair_SetVisible(1);

				App->CL_Vm_TopBar->Toggle_Hair_Flag = 1;

				SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);
			}
			return TRUE;
		}


		if (LOWORD(wParam) == IDC_TBSHOWTEXTURE)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWTEXTURE);

				if (App->Cl19_Ogre->RenderListener->ShowTextured == 1)
				{
					//App->Cl19_Ogre->RenderListener->ShowTextured = 0;
					App->CL_Vm_TopBar->Toggle_Textures_Flag = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);
				}
				else
				{
					//App->Cl19_Ogre->RenderListener->ShowTextured = 1;
					App->CL_Vm_TopBar->Toggle_Textures_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOn_Bmp);
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSHOWFACES)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWFACES);

				if (App->Cl19_Ogre->RenderListener->ShowFaces == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowFaces = 0;
					App->CL_Vm_TopBar->Toggle_Faces_Flag = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowFaces = 1;
					App->CL_Vm_TopBar->Toggle_Faces_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOn_Bmp);
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBPOINTS)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBPOINTS);

				if (App->Cl19_Ogre->RenderListener->ShowPoints == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowPoints = 0;
					App->CL_Vm_TopBar->Toggle_Points_Flag = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowPoints = 1;
					App->CL_Vm_TopBar->Toggle_Points_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOn_Bmp);
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSHOWBONES)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				if (App->CL_Vm_Model->BoneCount == 0)
				{
					App->Say("Model has no Bone/Joint structure.");
					return FALSE;
				}

				HWND Temp = GetDlgItem(hDlg, IDC_TBSHOWBONES);

				if (App->Cl19_Ogre->RenderListener->ShowBones == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowBones = 0;
					App->CL_Vm_TopBar->Toggle_Bones_Flag = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOff_Bmp);
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowBones = 1;
					App->CL_Vm_TopBar->Toggle_Bones_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOn_Bmp);
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBNORMALS)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBNORMALS);

				if (App->Cl19_Ogre->RenderListener->ShowNormals == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowNormals = 0;
					App->CL_Vm_TopBar->Toggle_Normals_Flag = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowNormals = 1;
					App->CL_Vm_TopBar->Toggle_Normals_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOn_Bmp);
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBBOUNDBOX)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBBOUNDBOX);

				if (App->Cl19_Ogre->RenderListener->ShowBoundingBox == 1)
				{
					App->Cl19_Ogre->RenderListener->ShowBoundingBox = 0;
					App->CL_Vm_TopBar->Toggle_BBox_Flag = 0;

					
					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOff_Bmp);
				}
				else
				{
					App->Cl19_Ogre->RenderListener->ShowBoundingBox = 1;
					App->CL_Vm_TopBar->Toggle_BBox_Flag = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOn_Bmp);
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBLIGHT)
		{
			if (App->CL_Vm_Model->Model_Loaded == 1)
			{
				HWND Temp = GetDlgItem(hDlg, IDC_TBLIGHT);

				if (App->Cl19_Ogre->RenderListener->Light_Activated == 1)
				{
					App->Cl19_Ogre->RenderListener->Light_Activated = 0;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);
				}
				else
				{
					App->Cl19_Ogre->RenderListener->Light_Activated = 1;

					SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOn_Bmp);
				}
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBINFO)
		{
			if (App->CL_Vm_ImGui->Show_Model_Data == 1)
			{
				App->CL_Vm_ImGui->Show_Model_Data = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_Model_Data = 1;
			}
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
// *						Start_Tabs_Headers Terry					   *
// *************************************************************************
void VM_TopBar::Start_Tabs_Headers(void)
{
	Tabs_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_TAB, App->CL_Vm_TopBar->TabsHwnd, (DLGPROC)Tabs_Headers_Proc);
}

// *************************************************************************
// *							Tabs_Headers_Proc_Proc					   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::Tabs_Headers_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_CBMOTIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_TBOLD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBMOTIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBDIMENSIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBGROUPS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBSHAPES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_TBOLD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_Vm_TopBar->Toggle_Tabs_Old_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBMOTIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_Vm_TopBar->Toggle_Tabs_Motions_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBDIMENSIONS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_Vm_TopBar->Toggle_Tabs_Dimensions_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBGROUPS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_Vm_TopBar->Toggle_Tabs_Groups_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSHAPES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle_Tabs(item, App->CL_Vm_TopBar->Toggle_Tabs_Shapes_Flag);
			return CDRF_DODEFAULT;
		}
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		if (LOWORD(wParam) == IDC_TBOLD)
		{
			App->CL_Vm_TopBar->Hide_Tabs();
			ShowWindow(App->CL_Vm_TopBar->Camera_TB_hWnd, SW_SHOW);
			App->CL_Vm_TopBar->Toggle_Tabs_Old_Flag = 1;

			App->Cl19_Ogre->OgreListener->ImGui_Render_Tab = Enums::ImGui_Camera;

			RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBMOTIONS)
		{
			App->CL_Vm_TopBar->Hide_Tabs();
			ShowWindow(App->CL_Vm_TopBar->Motions_TB_hWnd, SW_SHOW);
			App->CL_Vm_TopBar->Toggle_Tabs_Motions_Flag = 1;
			App->CL_Vm_ImGui->Show_Motion_List = 1;

			App->Cl19_Ogre->OgreListener->ImGui_Render_Tab = Enums::ImGui_Motions;
			
			RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}


		if (LOWORD(wParam) == IDC_TBDIMENSIONS)
		{
			App->CL_Vm_TopBar->Hide_Tabs();
			ShowWindow(App->CL_Vm_TopBar->Dimensions_TB_hWnd, SW_SHOW);
			App->CL_Vm_TopBar->Toggle_Tabs_Dimensions_Flag = 1;
			
			App->Cl19_Ogre->OgreListener->ImGui_Render_Tab = Enums::ImGui_Dimensions;

			RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBGROUPS)
		{
			App->CL_Vm_TopBar->Hide_Tabs();
			
			ShowWindow(App->CL_Vm_TopBar->Groups_TB_hWnd, SW_SHOW);
			ShowWindow(App->CL_Vm_Groups->RightGroups_Hwnd, SW_SHOW);
			App->CL_Vm_ImGui->Show_Group_List = 1;

			App->CL_Vm_TopBar->Toggle_Tabs_Groups_Flag = 1;

			App->Cl19_Ogre->OgreListener->ImGui_Render_Tab = Enums::ImGui_Groups;

			RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSHAPES)
		{
			App->CL_Vm_TopBar->Hide_Tabs();
			
			ShowWindow(App->CL_Vm_TopBar->Physics_TB_hWnd, SW_SHOW);
			ShowWindow(App->CL_Physics_E15->PhysicsPannel_Hwnd, SW_SHOW);

			App->CL_Vm_TopBar->Toggle_Tabs_Shapes_Flag = 1;

			App->Cl19_Ogre->OgreListener->ImGui_Render_Tab = Enums::ImGui_None;

			RedrawWindow(App->CL_Vm_TopBar->Tabs_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

	}
	}
	return FALSE;
}

// *************************************************************************
// *						Hide_Tabs Terry Berine						   *
// *************************************************************************
void VM_TopBar::Hide_Tabs(void)
{
	ShowWindow(App->CL_Vm_TopBar->Camera_TB_hWnd, SW_HIDE);
	ShowWindow(App->CL_Vm_TopBar->Motions_TB_hWnd, SW_HIDE);
	ShowWindow(App->CL_Vm_TopBar->Dimensions_TB_hWnd, SW_HIDE);
	ShowWindow(App->CL_Vm_TopBar->Groups_TB_hWnd, SW_HIDE);
	ShowWindow(App->CL_Vm_TopBar->Physics_TB_hWnd, SW_HIDE);
	
	ShowWindow(App->CL_Vm_Groups->RightGroups_Hwnd, 0);
	ShowWindow(App->CL_Physics_E15->PhysicsPannel_Hwnd,0);

	Toggle_Tabs_Old_Flag = 0;
	Toggle_Tabs_Motions_Flag = 0;
	Toggle_Tabs_Dimensions_Flag = 0;
	Toggle_Tabs_Groups_Flag = 0;
	Toggle_Tabs_Shapes_Flag = 0;
}

// *************************************************************************
// *						Reset_Main Controlls Terry Berine			   *
// *************************************************************************
void VM_TopBar::Reset_Main_Controls(void)
{
	HWND Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWFACES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBPOINTS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBBOUNDBOX);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWBONES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWGRID);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWHAIR);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBINFO);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBNORMALS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWTEXTURE);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBLIGHT);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);

	// Main Controls
	
	Toggle_Textures_Flag = 0;
	//App->Cl19_Ogre->RenderListener->ShowTextured = 0;

	Toggle_Faces_Flag = 0;
	//App->Cl19_Ogre->RenderListener->ShowFaces = 0;

	Toggle_Points_Flag = 0;
	//App->Cl19_Ogre->RenderListener->ShowPoints = 0;

	Toggle_Bones_Flag = 0;
	//App->Cl19_Ogre->RenderListener->ShowBones = 0;

	Toggle_Normals_Flag = 0;
	//App->Cl19_Ogre->RenderListener->ShowNormals = 0;

	Toggle_BBox_Flag = 0;
	//App->Cl19_Ogre->RenderListener->ShowBoundingBox = 0;

	Toggle_Hair_Flag = 1;
	App->Cl_Grid->ShowHair = 1;
	App->Cl_Grid->Hair_SetVisible(1);

	Toggle_Grid_Flag = 1;
	App->Cl_Grid->Grid_SetVisible(1);
	App->Cl_Grid->ShowGridFlag = 1;
}

// *************************************************************************
// *						Start_Camera_TB Terry Berine				   *
// *************************************************************************
void VM_TopBar::Start_Camera_TB(void)
{
	Camera_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB1, Tabs_TB_hWnd, (DLGPROC)Camera_TB_Proc);
	Init_Bmps_Camera();
}

// *************************************************************************
// *								View_TB_Proc						   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::Camera_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_TBRESETVIEW, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBZOOM, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBMODEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBWORLD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTMOUSESPEED, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_FULLSCREEN, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_SELECTION && some_item->code == NM_CUSTOMDRAW)
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
		}*/

		if (some_item->idFrom == IDC_TBMODEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Model_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBWORLD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_World_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBZOOM && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBRESETVIEW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTMOUSESPEED && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_FULLSCREEN && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_TBRESETVIEW)
		{
			App->Cl_Grid->Reset_View();
			return 1;
		}

		if (LOWORD(wParam) == IDC_TBZOOM)
		{
			App->Cl_Grid->Zoom();
			return 1;
		}

		if (LOWORD(wParam) == IDC_BTMOUSESPEED)
		{
			App->Cl_Dialogs->Start_Mouse_Sensitivity();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_FULLSCREEN)
		{
			App->Cl19_Ogre->Go_FullScreen_Mode();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBMODEL)
		{
			App->Cl19_Ogre->OgreListener->CameraMode = 1;
			App->CL_Vm_TopBar->Toggle_Model_Flag = 1;
			App->CL_Vm_TopBar->Toggle_World_Flag = 0;
			RedrawWindow(App->CL_Vm_TopBar->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBWORLD)
		{
			App->Cl19_Ogre->OgreListener->CameraMode = 0;
			App->CL_Vm_TopBar->Toggle_World_Flag = 1;
			App->CL_Vm_TopBar->Toggle_Model_Flag = 0;
			RedrawWindow(App->CL_Vm_TopBar->Camera_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		return FALSE;
	}

	}
	return FALSE;
}

// *************************************************************************
// *						Init_Bmps_Camera Terry Bernie				   *
// *************************************************************************
void VM_TopBar::Init_Bmps_Camera(void)
{
	HWND hTooltip_TB_1 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	// --------------------------------------------------- 
	HWND Temp = GetDlgItem(Camera_TB_hWnd, IDC_TBRESETVIEW);
	
	TOOLINFO ti = { 0 };
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti.uId = (UINT_PTR)Temp;
	ti.lpszText = "Reset to Default View";
	ti.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Camera_TB_hWnd, IDC_TBZOOM);
	
	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Reset and Zoom to fit Model In Window";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Camera_TB_hWnd, IDC_BTMOUSESPEED);
	
	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti3);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Adujust Mouse and Keys Speed";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti3);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Camera_TB_hWnd, IDC_FULLSCREEN);
	
	TOOLINFO ti4 = { 0 };
	ti4.cbSize = sizeof(ti4);
	ti4.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti4.uId = (UINT_PTR)Temp;
	ti4.lpszText = "Go Fullscreen Press esc to return";
	ti4.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti4);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Camera_TB_hWnd, IDC_TBMODEL);
	
	TOOLINFO ti5 = { 0 };
	ti5.cbSize = sizeof(ti5);
	ti5.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti5.uId = (UINT_PTR)Temp;
	ti5.lpszText = "Camera Mode Rotate Model";
	ti5.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti5);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Camera_TB_hWnd, IDC_TBWORLD);

	TOOLINFO ti6 = { 0 };
	ti6.cbSize = sizeof(ti6);
	ti6.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti6.uId = (UINT_PTR)Temp;
	ti6.lpszText = "Camera Mode You Move Around Model";
	ti6.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_1, TTM_ADDTOOL, 0, (LPARAM)&ti6);

	// --------------------------------------------------- 

}

// *************************************************************************
// *						Init_Bmps_Dimensions Terry Bernie			   *
// *************************************************************************
void VM_TopBar::Init_Bmps_Dimensions(void)
{
	HWND hTooltip_TB_Dim = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	// --------------------------------------------------- 
	HWND Temp = GetDlgItem(Dimensions_TB_hWnd, IDC_TBROTATION);

	TOOLINFO ti = { 0 };
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti.uId = (UINT_PTR)Temp;
	ti.lpszText = "Rotate Model";
	ti.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Dim, TTM_ADDTOOL, 0, (LPARAM)&ti);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Dimensions_TB_hWnd, IDC_TBSCALE);

	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Scale Model";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Dim, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Dimensions_TB_hWnd, IDC_TBPOSITION);

	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti3);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Position Model";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Dim, TTM_ADDTOOL, 0, (LPARAM)&ti3);

}

// *************************************************************************
// *						Init_Bmps_Groups Terry Bernie				   *
// *************************************************************************
void VM_TopBar::Init_Bmps_Groups(void)
{
	HWND hTooltip_TB_Gro = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	// --------------------------------------------------- 
	HWND Temp = GetDlgItem(Groups_TB_hWnd, IDC_GRCHANGETEXTURE);

	TOOLINFO ti = { 0 };
	ti.cbSize = sizeof(ti);
	ti.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti.uId = (UINT_PTR)Temp;
	ti.lpszText = "Change Texture for Selected Group";
	ti.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Gro, TTM_ADDTOOL, 0, (LPARAM)&ti);

	// --------------------------------------------------- 

	Temp = GetDlgItem(Groups_TB_hWnd, IDC_ONLYGROUP);

	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Show Only Seleceted Group";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Gro, TTM_ADDTOOL, 0, (LPARAM)&ti2);
}

// *************************************************************************
// *						Init_Bmps_Globals Terry Bernie				   *
// *************************************************************************
void VM_TopBar::Init_Bmps_Globals(void)
{
	HWND Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWFACES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBPOINTS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_MeshPointsOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBBOUNDBOX);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BBOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWBONES);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_BonesOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWGRID);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_GridOn_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWHAIR);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_HairOn_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBINFO);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_ModelInfo_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBNORMALS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_NormalsOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWTEXTURE);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);

	Temp = GetDlgItem(TabsHwnd, IDC_TBLIGHT);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_LightsOff_Bmp);


	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWTEXTURE);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Toggle Textures";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti1);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWFACES);
	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Toggle Faces";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	Temp = GetDlgItem(TabsHwnd, IDC_TBPOINTS);
	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti3);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Toggle Points";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti3);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWBONES);
	TOOLINFO ti4 = { 0 };
	ti4.cbSize = sizeof(ti4);
	ti4.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti4.uId = (UINT_PTR)Temp;
	ti4.lpszText = "Toggle Bones";
	ti4.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti4);

	Temp = GetDlgItem(TabsHwnd, IDC_TBNORMALS);
	TOOLINFO ti5 = { 0 };
	ti5.cbSize = sizeof(ti5);
	ti5.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti5.uId = (UINT_PTR)Temp;
	ti5.lpszText = "Toggle Normals";
	ti5.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti5);

	Temp = GetDlgItem(TabsHwnd, IDC_TBBOUNDBOX);
	TOOLINFO ti6 = { 0 };
	ti6.cbSize = sizeof(ti6);
	ti6.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti6.uId = (UINT_PTR)Temp;
	ti6.lpszText = "Toggle Bounding Box";
	ti6.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti6);

	Temp = GetDlgItem(TabsHwnd, IDC_TBLIGHT);
	TOOLINFO ti7 = { 0 };
	ti7.cbSize = sizeof(ti7);
	ti7.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti7.uId = (UINT_PTR)Temp;
	ti7.lpszText = "Toggle Lights";
	ti7.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti7);

	Temp = GetDlgItem(TabsHwnd, IDC_TBINFO);
	TOOLINFO ti8 = { 0 };
	ti8.cbSize = sizeof(ti8);
	ti8.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti8.uId = (UINT_PTR)Temp;
	ti8.lpszText = "Show Model Information";
	ti8.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti8);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWHAIR);
	TOOLINFO ti9 = { 0 };
	ti9.cbSize = sizeof(ti9);
	ti9.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti9.uId = (UINT_PTR)Temp;
	ti9.lpszText = "Toggle Main Cross Hair";
	ti9.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti9);

	Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWGRID);
	TOOLINFO ti10 = { 0 };
	ti10.cbSize = sizeof(ti10);
	ti10.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti10.uId = (UINT_PTR)Temp;
	ti10.lpszText = "Toggle Main Grid";
	ti10.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti10);

}

// *************************************************************************
// *						Init_Bmps_Motions Terry Bernie				   *
// *************************************************************************
void VM_TopBar::Init_Bmps_Motions(void)
{
	HWND hTooltip_TB_Motions = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	// --------------------------------------------------- 
	HWND Temp = GetDlgItem(Motions_TB_hWnd, IDC_TBPLAY);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_Playoff);

	Temp = GetDlgItem(Motions_TB_hWnd, IDC_TBSTOP);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_PlayStop);

	Temp = GetDlgItem(Motions_TB_hWnd, IDC_STEPTIMEBACK);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_StepBack);

	Temp = GetDlgItem(Motions_TB_hWnd, IDC_STEPTIMEPLUS);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_StepForward);

	Temp = GetDlgItem(Motions_TB_hWnd, IDC_TBPLAY);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Play Selected Motion";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Motions, TTM_ADDTOOL, 0, (LPARAM)&ti1);

	Temp = GetDlgItem(Motions_TB_hWnd, IDC_TBSTOP);
	TOOLINFO ti2 = { 0 };
	ti2.cbSize = sizeof(ti2);
	ti2.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti2.uId = (UINT_PTR)Temp;
	ti2.lpszText = "Stop Selected Motion";
	ti2.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Motions, TTM_ADDTOOL, 0, (LPARAM)&ti2);

	Temp = GetDlgItem(Motions_TB_hWnd, IDC_STEPTIMEBACK);
	TOOLINFO ti3 = { 0 };
	ti3.cbSize = sizeof(ti3);
	ti3.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti3.uId = (UINT_PTR)Temp;
	ti3.lpszText = "Step Motion Back";
	ti3.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Motions, TTM_ADDTOOL, 0, (LPARAM)&ti3);

	Temp = GetDlgItem(Motions_TB_hWnd, IDC_STEPTIMEPLUS);
	TOOLINFO ti4 = { 0 };
	ti4.cbSize = sizeof(ti4);
	ti4.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti4.uId = (UINT_PTR)Temp;
	ti4.lpszText = "Step Motion Forward";
	ti4.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Motions, TTM_ADDTOOL, 0, (LPARAM)&ti4);

	Temp = GetDlgItem(Motions_TB_hWnd, IDC_TBPOSE);
	TOOLINFO ti5 = { 0 };
	ti5.cbSize = sizeof(ti5);
	ti5.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti5.uId = (UINT_PTR)Temp;
	ti5.lpszText = "Reset to default Pose";
	ti5.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_Motions, TTM_ADDTOOL, 0, (LPARAM)&ti5);

	// --------------------------------------------------- 
}

// *************************************************************************
// *						Start_Motions_TB Terry						   *
// *************************************************************************
void VM_TopBar::Start_Motions_TB(void)
{
	Motions_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_MOTIONS, Tabs_TB_hWnd, (DLGPROC)Motions_TB_Proc);
	Init_Bmps_Motions();
}

// *************************************************************************
// *								Motions_TB_Proc						   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::Motions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_CBMOTIONS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBPOSE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_TBPLAY && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_Play_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSTOP && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, 0);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_STEPTIMEBACK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, 0);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_STEPTIMEPLUS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, 0);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBPOSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_TBPLAY) // Play Motion
		{
			App->CL_Vm_Motions->Play_SelectedMotion();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSTOP) // Stop Motion
		{
			App->CL_Vm_Motions->Stop_SelectedMotion();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBPOSE) // Stop Motion
		{
			App->CL_Vm_Motions->Set_Pose();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_STEPTIMEBACK)
		{
			if (App->CL_Vm_Model->MotionCount == 0) { return 1; }

			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->GetBoneMoveMent();
				App->CL_Vm_Genesis3D->Animate(3);

			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_STEPTIMEPLUS)
		{

			if (App->CL_Vm_Model->MotionCount == 0) { return 1; }

			if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
			{
				App->CL_Vm_Genesis3D->GetBoneMoveMent();
				App->CL_Vm_Genesis3D->Animate(2);

			}
			return TRUE;
		}

		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *						Start_Dimensions_TB Terry					   *
// *************************************************************************
void VM_TopBar::Start_Dimensions_TB(void)
{
	Dimensions_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_DIMENSIONS, Tabs_TB_hWnd, (DLGPROC)Dimensions_TB_Proc);
	Init_Bmps_Dimensions();
}

// *************************************************************************
// *								Dimensions_TB_Proc					   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::Dimensions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_TBROTATION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBPOSITION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TBSCALE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_TBROTATION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_ImGui->Show_Rotation);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBPOSITION && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_ImGui->Show_Position);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TBSCALE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_ImGui->Show_Scale);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_TBROTATION) // Rotation
		{
			
			if (App->CL_Vm_ImGui->Show_Rotation == 1)
			{
				App->CL_Vm_ImGui->Show_Rotation = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_Rotation = 1;
			}

			RedrawWindow(App->CL_Vm_TopBar->Dimensions_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBPOSITION) // Position
		{
			
			if (App->CL_Vm_ImGui->Show_Position == 1)
			{
				App->CL_Vm_ImGui->Show_Position = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_Position = 1;
			}

			RedrawWindow(App->CL_Vm_TopBar->Dimensions_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TBSCALE) // Scale
		{
			
			if (App->CL_Vm_ImGui->Show_Scale == 1)
			{
				App->CL_Vm_ImGui->Show_Scale = 0;
			}
			else
			{
				App->CL_Vm_ImGui->Show_Scale = 1;
			}

			RedrawWindow(App->CL_Vm_TopBar->Dimensions_TB_hWnd, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
			return TRUE;
		}
		
		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *						Start_Groups_TB Terry					   *
// *************************************************************************
void VM_TopBar::Start_Groups_TB(void)
{
	Groups_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_GROUPS, Tabs_TB_hWnd, (DLGPROC)Groups_TB_Proc);
	Init_Bmps_Groups();
}

// *************************************************************************
// *						Start_Shapes_TB Terry						   *
// *************************************************************************
void VM_TopBar::Start_Shapes_TB(void)
{
	Physics_TB_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_TB_PHYSICS, Tabs_TB_hWnd, (DLGPROC)Shapes_TB_Proc);
	//Init_Bmps_Groups();
}

// *************************************************************************
// *								Shapes_TB_Proc					   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::Shapes_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		/*SendDlgItemMessage(hDlg, IDC_GRCHANGETEXTURE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ONLYGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));*/
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{

		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_ONLYGROUP && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_GroupsOnly_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_GRCHANGETEXTURE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		/*if (LOWORD(wParam) == IDC_GRCHANGETEXTURE)
		{
			App->CL_Vm_Groups->ChangeTexture_ModelLocation();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ONLYGROUP)
		{
			if (App->Cl19_Ogre->RenderListener->ShowOnlySubMesh == 1)
			{
				App->Cl19_Ogre->RenderListener->ShowOnlySubMesh = 0;
				App->CL_Vm_TopBar->Toggle_GroupsOnly_Flag = 0;
			}
			else
			{
				App->Cl19_Ogre->RenderListener->ShowOnlySubMesh = 1;
				App->CL_Vm_TopBar->Toggle_GroupsOnly_Flag = 1;
			}

			return TRUE;
		}*/

		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *								Dimensions_TB_Proc					   *
// *************************************************************************
LRESULT CALLBACK VM_TopBar::Groups_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_GRCHANGETEXTURE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ONLYGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->Brush_Tabs;
	}

	case WM_NOTIFY:
	{

		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_ONLYGROUP && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->CL_Vm_TopBar->Toggle_GroupsOnly_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_GRCHANGETEXTURE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_GRCHANGETEXTURE) 
		{
			App->CL_Vm_Groups->ChangeTexture_ModelLocation();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ONLYGROUP) 
		{
			/*if (App->Cl19_Ogre->RenderListener->ShowOnlySubMesh == 1)
			{
				App->Cl19_Ogre->RenderListener->ShowOnlySubMesh = 0;
				App->CL_Vm_TopBar->Toggle_GroupsOnly_Flag = 0;
			}
			else
			{
				App->Cl19_Ogre->RenderListener->ShowOnlySubMesh = 1;
				App->CL_Vm_TopBar->Toggle_GroupsOnly_Flag = 1;
			}*/

			return TRUE;
		}

		//if (LOWORD(wParam) == IDC_TBSCALE) // Scale
		//{
		//	if (App->CL_Vm_ImGui->Show_Scale == 1)
		//	{
		//		App->CL_Vm_ImGui->Show_Scale = 0;
		//	}
		//	else
		//	{
		//		App->CL_Vm_ImGui->Show_Scale = 1;
		//	}
		//	return TRUE;
		//}

		return FALSE;
	}
	}
	return FALSE;
}

// *************************************************************************
// *					TogglePlayBmp Inflanite						       *
// *************************************************************************
void VM_TopBar::TogglePlayBmp(void)
{
	HWND Temp = GetDlgItem(Motions_TB_hWnd, IDC_TBPLAY);

	if (Toggle_Play_Flag == 1)
	{
		SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_PlayOn);
	}
	else
	{
		SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_Playoff);
	}
}

// *************************************************************************
// *					ToggleTexturesBmp Inflanite					       *
// *************************************************************************
void VM_TopBar::ToggleTexturesBmp(bool Show)
{
	HWND Temp = GetDlgItem(TabsHwnd, IDC_TBSHOWTEXTURE);

	if (Show == 1)
	{
		//App->Cl19_Ogre->RenderListener->ShowTextured = 1;
		App->CL_Vm_TopBar->Toggle_Textures_Flag = 1;

		SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOn_Bmp);
	}
	else
	{
		//App->Cl19_Ogre->RenderListener->ShowTextured = 0;
		App->CL_Vm_TopBar->Toggle_Textures_Flag = 0;

		SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_TexturesOff_Bmp);
	}

}

// *************************************************************************
// *					Check_Current_Option Terry Bernie				   *
// *************************************************************************
void VM_TopBar::UnCheck_All_MouseOption(HWND hDlg)
{
	App->Cl_Dialogs->Mouse_Normal2 = 0;
	App->Cl_Dialogs->Mouse_Slow2 = 0;
	App->Cl_Dialogs->Mouse_VerySlow2 = 0;
	App->Cl_Dialogs->Mouse_Fast2 = 0;
}
