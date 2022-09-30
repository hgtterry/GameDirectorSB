/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_MeshViewer.h"


SB_MeshViewer::SB_MeshViewer()
{
	MeshView_Hwnd = nullptr;
	ListHwnd = nullptr;
	CB_hWnd = nullptr;

	MvEnt = NULL;
	MvNode = NULL;

	MeshView_Window = NULL;
	mSceneMgrMeshView = NULL;
	mCameraMeshView = NULL;
	CamNode = NULL;

	Mesh_Viewer_Mode = 0; // 0 = Defaulet Objects 1 = Collectables

	// ------------------------------------------------ 
	Physics_Type = Enums::Bullet_Type_Dynamic;
	Physics_Shape = Enums::NoShape;

	SelectDynamic = 0;
	SelectStatic = 0;
	SelectTriMesh = 0;

	Selected_Shape_Box = 0;
	Selected_Shape_Sphere = 0;
	Selected_Shape_Capsule = 0;
	Selected_Shape_Cylinder = 0;
	Selected_Shape_Cone = 0;

	// ------------------------------------------------ 

	Last_MeshFile[0] = 0;
	m_Material_File[0] = 0;

	strcpy(mResource_Folder, App->EquityDirecory_FullPath);
	strcat(mResource_Folder, "\\Media_New\\Walls\\");
	strcpy(Selected_MeshFile, "Wall_1.mesh");

	strcpy(m_Current_Folder, "Structure");

	MV_Resource_Group = "MV_Resource_Group";
}


SB_MeshViewer::~SB_MeshViewer()
{
}

// *************************************************************************
// *		SetUp_Area_Trimesh:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_MeshViewer::SetUp_Area_Trimesh(HWND hDlg)
{
	EnableWindow(GetDlgItem(MainDlgHwnd, IDC_MVSTATIC),false);
	EnableWindow(GetDlgItem(MainDlgHwnd, IDC_DYNAMIC), false);
	EnableWindow(GetDlgItem(MainDlgHwnd, IDC_TRIMESH), true);
	EnableWindow(GetDlgItem(MainDlgHwnd, IDC_JUSTOGRE), false);
	EnableWindow(GetDlgItem(MainDlgHwnd, IDC_TEST), false);

	SelectTriMesh = 1;

	Enable_ShapeButtons(0);

	char ConNum[256];
	char ATest[256];

	strcpy_s(ATest, "Area_");
	_itoa(App->SBC_Scene->Object_Count, ConNum, 10);
	strcat(ATest, ConNum);

	SetDlgItemText(hDlg, IDC_OBJECTNAME, ATest);
	strcpy(App->SBC_MeshViewer->Object_Name, ATest);
	strcpy(App->SBC_MeshViewer->m_Current_Folder, "Areas");
	HWND temp = GetDlgItem(hDlg, IDC_CB_FOLDERS);
	SendMessage(temp, CB_SELECTSTRING, -1, LPARAM(App->SBC_MeshViewer->m_Current_Folder));

	SendMessage(App->SBC_MeshViewer->ListHwnd, LB_RESETCONTENT, 0, 0);

	strcpy(App->SBC_MeshViewer->mResource_Folder, App->EquityDirecory_FullPath);
	strcat(App->SBC_MeshViewer->mResource_Folder, "\\Media_New\\");
	strcat(App->SBC_MeshViewer->mResource_Folder, App->SBC_MeshViewer->m_Current_Folder);
	strcat(App->SBC_MeshViewer->mResource_Folder, "\\");

	SetDlgItemText(hDlg, IDC_ST_CURRENTFOLDER, App->SBC_MeshViewer->mResource_Folder);
	SetWindowText(hDlg, App->SBC_MeshViewer->mResource_Folder);

	App->SBC_MeshViewer->Add_Resources();
	App->SBC_MeshViewer->Get_Files();

}

// *************************************************************************
// *					Enable_ShapeButtons Terry Bernie				   *
// *************************************************************************
void SB_MeshViewer::Enable_TypeButtons(bool state)
{
	ShowWindow(GetDlgItem(MainDlgHwnd, IDC_MVSTATIC), state);
	ShowWindow(GetDlgItem(MainDlgHwnd, IDC_DYNAMIC), state);
	ShowWindow(GetDlgItem(MainDlgHwnd, IDC_TRIMESH), state);
	ShowWindow(GetDlgItem(MainDlgHwnd, IDC_JUSTOGRE), state);
	ShowWindow(GetDlgItem(MainDlgHwnd, IDC_TEST), state);
}
// *************************************************************************
// *					Enable_ShapeButtons Terry Bernie				   *
// *************************************************************************
void SB_MeshViewer::Enable_ShapeButtons(bool state)
{
	EnableWindow(GetDlgItem(MainDlgHwnd, IDC_BOX), state);
	EnableWindow(GetDlgItem(MainDlgHwnd, IDC_SPHERE), state);
	EnableWindow(GetDlgItem(MainDlgHwnd, IDC_CAPSULE), state);
	EnableWindow(GetDlgItem(MainDlgHwnd, IDC_CYLINDER), state);
	EnableWindow(GetDlgItem(MainDlgHwnd, IDC_CONE), state);

	Selected_Shape_Box = 0;
	Selected_Shape_Sphere = 0;
	Selected_Shape_Capsule = 0;
	Selected_Shape_Cylinder = 0;
	Selected_Shape_Cone = 0;
}

// *************************************************************************
// *			StartMeshViewer:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_MeshViewer::StartMeshViewer()
{
	MvEnt = NULL;
	MvNode = NULL;
	Last_MeshFile[0] = 0;

	App->RenderBackGround = 1;

	strcpy(mResource_Folder, App->EquityDirecory_FullPath);
	strcat(mResource_Folder, "\\Media_New\\Walls\\");

	Create_Resources_Group();
	Add_Resources();
	
	
	DialogBox(App->hInst, (LPCTSTR)IDD_GD_MESHVIEWER, App->Fdlg, (DLGPROC)MeshViewer_Proc);

	App->Cl19_Ogre->OgreListener->MeshViewer_Running = 0;


	App->RenderBackGround = 0;
	return 1;
}

// *************************************************************************
// *						MeshViewer_Proc Terry Bernie				   *
// *************************************************************************
LRESULT CALLBACK SB_MeshViewer::MeshViewer_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		App->SBC_MeshViewer->MainDlgHwnd = hDlg;

		
		SendDlgItemMessage(hDlg, IDC_BT_FOLDERBROWSE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BOX, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_SELECTEDNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_MVSTATIC, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_DYNAMIC, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_TRIMESH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_SPHERE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CAPSULE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CYLINDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CONE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_LISTFILES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_OBJECTNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STSHAPE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTYPE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STFOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		
		SendDlgItemMessage(hDlg, IDC_BT_PROPERTIES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CB_FOLDERS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_CURRENTFOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		
		SetDlgItemText(hDlg, IDC_ST_CURRENTFOLDER, App->SBC_MeshViewer->mResource_Folder);

		SetWindowText(hDlg, App->SBC_MeshViewer->mResource_Folder);

		App->SBC_MeshViewer->ListHwnd = GetDlgItem(hDlg, IDC_LISTFILES);

		App->SBC_MeshViewer->MeshView_Hwnd = GetDlgItem(hDlg, IDC_OGREWIN);
		App->SBC_MeshViewer->Set_OgreWindow();

		HWND CB_hWnd = GetDlgItem(hDlg, IDC_CB_FOLDERS);

		App->SBC_MeshViewer->Get_Media_Folders_Actors(CB_hWnd); // Populate Combo

		App->SBC_MeshViewer->Set_ResourceMesh_File(hDlg);

		App->SBC_MeshViewer->SelectStatic = 0;
		App->SBC_MeshViewer->SelectDynamic = 0;
		App->SBC_MeshViewer->SelectTriMesh = 0;


		if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area)
		{
			App->SBC_MeshViewer->SetUp_Area_Trimesh(hDlg);
		}

		App->SBC_MeshViewer->Get_Files();

		if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Objects)
		{
			App->SBC_MeshViewer->Enable_ShapeButtons(1);
			App->SBC_MeshViewer->Enable_TypeButtons(1);

			char ATest[256];
			char ConNum[256];

			strcpy_s(ATest, "Object_");
			_itoa(App->SBC_Scene->Object_Count, ConNum, 10);
			strcat(ATest, ConNum);

			SetDlgItemText(hDlg, IDC_OBJECTNAME, ATest);
			strcpy(App->SBC_MeshViewer->Object_Name, ATest);

			App->SBC_MeshViewer->Enable_TypeButtons(1);
		}

		App->Cl19_Ogre->OgreListener->MeshViewer_Running = 1;


		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STSHAPE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STTYPE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STFOLDER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_ST_CURRENTFOLDER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_SELECTEDNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
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

		if (some_item->idFrom == IDC_BT_FOLDERBROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_MVSTATIC && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->SelectStatic);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_DYNAMIC && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->SelectDynamic);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TRIMESH && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->SelectTriMesh);
			return CDRF_DODEFAULT;
		}

		//// ---------------------------------------------------------------------
		if (some_item->idFrom == IDC_BOX && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->Selected_Shape_Box);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_SPHERE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->Selected_Shape_Sphere);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CAPSULE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->Selected_Shape_Capsule);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CYLINDER && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->Selected_Shape_Cylinder);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_CONE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->Selected_Shape_Cone);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_PROPERTIES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
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

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BT_PROPERTIES)
		{

			App->SBC_MeshViewer->Start_Properties_ListBox();

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CB_FOLDERS)
		{
			switch (HIWORD(wParam)) // Find out what message it was
			{
			case CBN_DROPDOWN:
				break;
			case CBN_CLOSEUP:
			{

				HWND temp = GetDlgItem(hDlg, IDC_CB_FOLDERS);
				int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
				SendMessage(temp, CB_GETLBTEXT, Index, (LPARAM)App->SBC_MeshViewer->m_Current_Folder);

				SendMessage(App->SBC_MeshViewer->ListHwnd, LB_RESETCONTENT, 0, 0);

				strcpy(App->SBC_MeshViewer->mResource_Folder, App->EquityDirecory_FullPath);
				strcat(App->SBC_MeshViewer->mResource_Folder, "\\Media_New\\");
				strcat(App->SBC_MeshViewer->mResource_Folder, App->SBC_MeshViewer->m_Current_Folder);
				strcat(App->SBC_MeshViewer->mResource_Folder, "\\");

				SetDlgItemText(hDlg, IDC_ST_CURRENTFOLDER, App->SBC_MeshViewer->mResource_Folder);
				SetWindowText(hDlg, App->SBC_MeshViewer->mResource_Folder);

				App->SBC_MeshViewer->Add_Resources();
				App->SBC_MeshViewer->Get_Files();

			}
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_LISTFILES)
		{
			char buff[256];
			int Index = 0;
			Index = SendDlgItemMessage(hDlg, IDC_LISTFILES, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

			if (Index == -1)
			{
				return 1;
			}

			SendDlgItemMessage(hDlg, IDC_LISTFILES, LB_GETTEXT, (WPARAM)Index, (LPARAM)buff);
			SetDlgItemText(hDlg, IDC_SELECTEDNAME, buff);

			strcpy(App->SBC_MeshViewer->Selected_MeshFile, buff);

			App->SBC_MeshViewer->Add_Resources();

			App->SBC_MeshViewer->ShowMesh(App->SBC_MeshViewer->Selected_MeshFile);

			return TRUE;

		}

		// ---------------------------------------------------------------------
		if (LOWORD(wParam) == IDC_BT_FOLDERBROWSE)
		{
			strcpy(App->Com_CDialogs->BrowserMessage, "Select Folder");
			int Test = App->Com_CDialogs->StartBrowser(App->SBC_MeshViewer->mResource_Folder, App->Fdlg);

			if (Test == 0) { return true; }


			SetDlgItemText(hDlg, IDC_ST_CURRENTFOLDER, App->Com_CDialogs->szSelectedDir);
			SetWindowText(hDlg, App->Com_CDialogs->szSelectedDir);

			strcpy(App->SBC_MeshViewer->mResource_Folder, App->Com_CDialogs->szSelectedDir);

			App->SBC_MeshViewer->Add_Resources();
			App->SBC_MeshViewer->Get_Files();
			return TRUE;
		}
		if (LOWORD(wParam) == ID_TOOLS_MVRESOURCEVIEWER)
		{
			App->SBC_Resources->Start_Resources(App->SBC_MeshViewer->MainDlgHwnd);
			return TRUE;
		}

		if (LOWORD(wParam) == ID_FOLDERS_POO)
		{

			//App->SBC_MeshViewer->Start_Folders();

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TRIMESH)
		{
			App->SBC_MeshViewer->Physics_Type = Enums::Bullet_Type_TriMesh;
			App->SBC_MeshViewer->SelectStatic = 0;
			App->SBC_MeshViewer->SelectDynamic = 0;
			App->SBC_MeshViewer->SelectTriMesh = 1;

			App->SBC_MeshViewer->Enable_ShapeButtons(false);
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::NoShape;

			return 1;
		}

		if (LOWORD(wParam) == IDC_MVSTATIC)
		{
			App->SBC_MeshViewer->Physics_Type = Enums::Bullet_Type_Static;
			App->SBC_MeshViewer->SelectStatic = 1;
			App->SBC_MeshViewer->SelectDynamic = 0;
			App->SBC_MeshViewer->SelectTriMesh = 0;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Enable_ShapeButtons(true);

			return 1;
		}

		if (LOWORD(wParam) == IDC_DYNAMIC)
		{
			App->SBC_MeshViewer->Physics_Type = Enums::Bullet_Type_Dynamic;
			App->SBC_MeshViewer->SelectDynamic = 1;
			App->SBC_MeshViewer->SelectStatic = 0;
			App->SBC_MeshViewer->SelectTriMesh = 0;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Enable_ShapeButtons(true);
			return 1;
		}

		// --------------------------------------------------------------------- Shape
		if (LOWORD(wParam) == IDC_BOX)
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Box = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Shape_Box;
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_SPHERE)
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Sphere = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Sphere;
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CAPSULE)
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Capsule = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Capsule;
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CYLINDER)
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Cylinder = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Cylinder;
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CONE)
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Cone = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Cone;
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{

			if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area)
			{
				
			}
			else if (App->SBC_MeshViewer->Physics_Type == Enums::Bullet_Type_None || App->SBC_MeshViewer->Physics_Shape == Enums::NoShape)
			{
				if (App->SBC_MeshViewer->Physics_Type == Enums::Bullet_Type_TriMesh)
				{
					break;
				}

				App->Say("No Type or Shape Selected");
				return TRUE;
			}


			char buff[255];
			GetDlgItemText(hDlg, IDC_OBJECTNAME, (LPTSTR)buff, 256);
			strcpy(App->SBC_MeshViewer->Object_Name, buff);

			App->Cl19_Ogre->OgreListener->MeshViewer_Running = 0;


			App->SBC_MeshViewer->Close_OgreWindow();
			App->SBC_MeshViewer->Delete_Resources_Group();

			if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area) // Area
			{
				App->SBC_Objects_Create->Add_New_Area();
			}
			else
			{
				App->SBC_Objects_Create->Update_MV_Details();
			}

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}


		if (LOWORD(wParam) == IDCANCEL)
		{

			App->Cl19_Ogre->OgreListener->MeshViewer_Running = 0;

			/*if (App->SBC_MeshViewer->MvEnt && App->SBC_MeshViewer->MvNode)
			{
				App->SBC_MeshViewer->MvNode->detachAllObjects();
				App->SBC_MeshViewer->mSceneMgrMeshView->destroySceneNode(App->SBC_MeshViewer->MvNode);
				App->SBC_MeshViewer->mSceneMgrMeshView->destroyEntity(App->SBC_MeshViewer->MvEnt);
				App->SBC_MeshViewer->MvEnt = NULL;
				App->SBC_MeshViewer->MvNode = NULL;
			}*/

			//Debug
			App->SBC_MeshViewer->Close_OgreWindow();

			App->SBC_MeshViewer->Delete_Resources_Group();

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *					Set_ResourceMesh_File  Terry Flanigan			   *
// *************************************************************************
void SB_MeshViewer::Set_ResourceMesh_File(HWND hDlg)
{
	char buff[MAX_PATH];

	strcpy(App->SBC_MeshViewer->mResource_Folder, App->EquityDirecory_FullPath);
	strcat(App->SBC_MeshViewer->mResource_Folder, "\\Media_New\\");
	strcat(App->SBC_MeshViewer->mResource_Folder, App->SBC_MeshViewer->m_Current_Folder);
	strcat(App->SBC_MeshViewer->mResource_Folder, "\\");

	SetDlgItemText(hDlg, IDC_ST_CURRENTFOLDER, App->SBC_MeshViewer->mResource_Folder);
	SetWindowText(hDlg, App->SBC_MeshViewer->mResource_Folder);

	App->SBC_MeshViewer->Add_Resources();
	App->SBC_MeshViewer->Get_Files();

	HWND temp = GetDlgItem(hDlg, IDC_CB_FOLDERS);
	SendMessage(temp, CB_SELECTSTRING, -1, LPARAM(App->SBC_MeshViewer->m_Current_Folder));
	

	SendDlgItemMessage(hDlg, IDC_LISTFILES, LB_GETTEXT, (WPARAM)0, (LPARAM)buff);
	SetDlgItemText(hDlg, IDC_SELECTEDNAME, buff);

	strcpy(App->SBC_MeshViewer->Selected_MeshFile, buff);
}

// *************************************************************************
// *					ShowMesh Terry Bernie							   *
// *************************************************************************
void SB_MeshViewer::ShowMesh(char* MeshFile)
{
	if (MvEnt && MvNode)
	{
		MvNode->detachAllObjects();
		mSceneMgrMeshView->destroySceneNode(MvNode);
		mSceneMgrMeshView->destroyEntity(MvEnt);
		MvEnt = NULL;
		MvNode = NULL;
	}

	MvEnt = mSceneMgrMeshView->createEntity(MeshFile);
	MvNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
	MvNode->attachObject(MvEnt);
	MvNode->setPosition(0, 0, 0);

	Ogre::Vector3 Centre = MvEnt->getBoundingBox().getCenter();

	Ogre::Real Radius = MvEnt->getBoundingRadius();

	mCameraMeshView->setPosition(0, Centre.y, -Radius*2.5);
	mCameraMeshView->lookAt(0, Centre.y, 0);

	//	Check_HasAnimations();
}

// *************************************************************************
// *				Set_OgreWindow Terry Bernie						   *
// *************************************************************************
bool SB_MeshViewer::Set_OgreWindow(void)
{

	Ogre::NameValuePairList options;

	options["externalWindowHandle"] =
		Ogre::StringConverter::toString((size_t)MeshView_Hwnd);

	MeshView_Window = App->Cl19_Ogre->mRoot->createRenderWindow("MeshViewWin", 1024, 768, false, &options);

	mSceneMgrMeshView = App->Cl19_Ogre->mRoot->createSceneManager("DefaultSceneManager", "MeshViewGD");

	mCameraMeshView = mSceneMgrMeshView->createCamera("CameraMV");
	mCameraMeshView->setPosition(Ogre::Vector3(0, 0, 0));
	mCameraMeshView->setNearClipDistance(0.1);
	mCameraMeshView->setFarClipDistance(1000);

	Ogre::Viewport* vp = MeshView_Window->addViewport(mCameraMeshView);
	mCameraMeshView->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));

	vp->setBackgroundColour(ColourValue(0.5, 0.5, 0.5));

	CamNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode("Camera_Node");
	CamNode->attachObject(mCameraMeshView);

	////-------------------------------------------- 
	
	MvEnt = mSceneMgrMeshView->createEntity("MVTest2", Selected_MeshFile, MV_Resource_Group);
	MvNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
	MvNode->attachObject(MvEnt);
	MvNode->setVisible(true);

	mSceneMgrMeshView->setAmbientLight(ColourValue(0.7, 0.7, 0.7));

	// add a bright light above the scene
	Light* light = mSceneMgrMeshView->createLight();
	light->setType(Light::LT_POINT);
	light->setPosition(-10, 40, 20);
	light->setSpecularColour(ColourValue::White);

	Ogre::Vector3 Centre = MvEnt->getBoundingBox().getCenter();
	Ogre::Real Radius = MvEnt->getBoundingRadius();

	mCameraMeshView->setPosition(0, Centre.y, -Radius*(Real(2.5)));
	mCameraMeshView->lookAt(0, Centre.y, 0);

	return 1;
}

// *************************************************************************
// *				CloseMeshView (Terry Bernie)						   *
// *************************************************************************
void SB_MeshViewer::Close_OgreWindow(void)
{
	App->Cl19_Ogre->mRoot->detachRenderTarget("MeshViewWin");
	MeshView_Window->destroy();
	App->Cl19_Ogre->mRoot->destroySceneManager(mSceneMgrMeshView);
}

// *************************************************************************
// *	  					Reset_Shape_Flags Terry Bernie				   *
// *************************************************************************
void SB_MeshViewer::Reset_Shape_Flags()
{
	Selected_Shape_Box = 0;
	Selected_Shape_Sphere = 0;
	Selected_Shape_Capsule = 0;
	Selected_Shape_Cylinder = 0;
	Selected_Shape_Cone = 0;
}

// *************************************************************************
// *							Get_Files( Terry Bernie				 	   *
// *************************************************************************
bool SB_MeshViewer::Get_Files()
{
	SendMessage(ListHwnd, LB_RESETCONTENT, 0, 0);

	char Path[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(Path, mResource_Folder);
	strcat(Path, "*.*");
	
	hFind = FindFirstFile(Path, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (FindFileData.dwFileAttributes)
			{
				if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0)
				{

				}
				else
				{
					if (_stricmp(FindFileData.cFileName + strlen(FindFileData.cFileName) - 5, ".mesh") == 0)
					{
						SendMessage(ListHwnd, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)FindFileData.cFileName);
					}
				}

			}
		} while (FindNextFile(hFind, &FindFileData));

		FindClose(hFind);
	}

	char buff[256];
	SendDlgItemMessage(MainDlgHwnd, IDC_LISTFILES, LB_GETTEXT, (WPARAM)0, (LPARAM)buff);
	SetDlgItemText(MainDlgHwnd, IDC_SELECTEDNAME, buff);

	strcpy(App->SBC_MeshViewer->Selected_MeshFile, buff);
	App->SBC_MeshViewer->ShowMesh(App->SBC_MeshViewer->Selected_MeshFile);
	//App->SBC_MeshViewer->Get_Details_hLV();
	return 0;
}

// *************************************************************************
// *					Create_Resources_Group	Terry Bernie 		 	   *
// *************************************************************************
bool SB_MeshViewer::Create_Resources_Group()
{

	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(MV_Resource_Group);

	return 1;
}

// *************************************************************************
// *						Add_Resources	Terry Bernie 			 	   *
// *************************************************************************
bool SB_MeshViewer::Add_Resources()
{
	Ogre::ResourceGroupManager::getSingleton().clearResourceGroup(MV_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mResource_Folder,"FileSystem", MV_Resource_Group);

	Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(MV_Resource_Group);
	
	return 1;
}

// *************************************************************************
// *					Delete_Resources_Group	Terry Bernie 		 	   *
// *************************************************************************
bool SB_MeshViewer::Delete_Resources_Group()
{

	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(MV_Resource_Group);

	return 1;
}

// *************************************************************************
// *					Get_Media_FoldersActors Terry Berni			 	   *
// *************************************************************************
bool SB_MeshViewer::Get_Media_Folders_Actors(HWND DropHwnd)
{
	char Path[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(Path, App->EquityDirecory_FullPath);
	strcat(Path, "\\Media_New\\*.*");

	hFind = FindFirstFile(Path, &FindFileData);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0)
				{

				}
				else
				{
					SendMessage(DropHwnd, CB_ADDSTRING, 0, (LPARAM)(LPCTSTR)FindFileData.cFileName);
				}

			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}

	SendMessage(DropHwnd, CB_SETCURSEL, 0, 0);
	return 0;
}

// *************************************************************************
// *				GetMeshFiles   Terry Bernie							   *
// *************************************************************************
bool SB_MeshViewer::GetMeshFiles(char* Location, bool ResetList)
{
	if (ResetList == true)
	{
		SendMessage(ListHwnd, LB_RESETCONTENT, 0, 0);
	}

	WIN32_FIND_DATA ffd;
	HANDLE hFind = INVALID_HANDLE_VALUE;

	char SearchName[255];
	strcpy(SearchName, Location);

	hFind = FindFirstFile(SearchName, &ffd);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return 0;
	}

	SendMessage(ListHwnd, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)ffd.cFileName);

	while (FindNextFile(hFind, &ffd) != 0)
	{
		SendMessage(ListHwnd, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)ffd.cFileName);
	}

	SendMessage(ListHwnd, LB_SETCURSEL, 0, 0);

	char buff[256];
	int Index = 0;
	Index = SendMessage(ListHwnd, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

	if (Index == -1)
	{
		return 0;
	}

	SendMessage(ListHwnd, LB_GETTEXT, (WPARAM)0, (LPARAM)buff);

	strcpy(Selected_MeshFile, buff);
	ShowMesh(Selected_MeshFile);

	return 1;
}

// *************************************************************************
// *	  				Start_Gen_ListBox TerryFlanigan					   *
// *************************************************************************
void SB_MeshViewer::Start_Properties_ListBox()
{
	DialogBox(App->hInst,(LPCTSTR)IDD_LISTDATA, MainDlgHwnd,(DLGPROC)Properties_ListBox_Proc);
}

// *************************************************************************
// *				Properties_ListBox_Proc Terry Flanigan				   *
// *************************************************************************
LRESULT CALLBACK SB_MeshViewer::Properties_ListBox_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		HWND List = GetDlgItem(hDlg, IDC_LISTGROUP);
		ListView_DeleteAllItems(List);

		App->SBC_MeshViewer->m_Material_File[0] = 0;

		int SubMeshCount = App->SBC_MeshViewer->MvEnt->getNumSubEntities();
		char test[255];
		char pScriptName[255];
		char pMaterialFile[255];
		Ogre::String st;
		Ogre::MaterialPtr pp;

		pp.setNull();
		bool loaded = 0;
		//SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_MeshViewer->MvEnt->getSubEntity(0)->getMaterialName().c_str());

		Ogre::SubMesh const *subMesh = App->SBC_MeshViewer->MvEnt->getSubEntity(0)->getSubMesh();
		Ogre::String MatName = subMesh->getMaterialName();
		strcpy(pScriptName, MatName.c_str());

		loaded = Ogre::MaterialManager::getSingleton().resourceExists(MatName);

		if (loaded == 1)
		{
			pp = Ogre::MaterialManager::getSingleton().getByName(MatName, App->SBC_MeshViewer->MV_Resource_Group);
			st = pp->getOrigin();
			strcpy(pMaterialFile, st.c_str());

			strcpy(test, "Loaded:- ");
			strcat(test, pMaterialFile);
			SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)test);

			strcpy(App->SBC_MeshViewer->m_Material_File, pMaterialFile);

		}
		else
		{
			strcpy(test, "Not Loaded:- ");
			strcat(test, pMaterialFile);
			SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)test);
		}

		
		Ogre::ResourcePtr ppp;
		Ogre::ResourceManager::ResourceMapIterator TextureIterator = Ogre::TextureManager::getSingleton().getResourceIterator();

		while (TextureIterator.hasMoreElements())
		{
			//strcpy(pScriptName,(static_cast<Ogre::MaterialPtr>(TextureIterator.peekNextValue()))->getName().c_str());

			if (TextureIterator.peekNextValue()->getGroup() == App->SBC_MeshViewer->MV_Resource_Group)
			{
				
				strcpy(pScriptName, TextureIterator.peekNextValue()->getName().c_str());
				ppp = Ogre::TextureManager::getSingleton().getByName(pScriptName);

				if (ppp->isLoaded() == 1)
				{
					
					strcpy(test, "Loaded:- ");
					strcat(test, pScriptName);
					SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)test);
				}
				else
				{
					strcpy(test, "Not Loaded:- ");
					strcat(test, pScriptName);
					SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)test);
				}

			}

			TextureIterator.moveNext();
		}

		return TRUE;
	}

	

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	break;
	case WM_CTLCOLORSTATIC:
	{

		return FALSE;
	}

	case WM_COMMAND:
	{
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
	}
	return FALSE;
}

