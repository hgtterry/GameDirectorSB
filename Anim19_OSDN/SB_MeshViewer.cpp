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

:- Terry and Hazel Flanigan 2022

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
	Phys_Body = nullptr;

	MeshView_Window = NULL;
	mSceneMgrMeshView = NULL;
	mCameraMeshView = NULL;
	CamNode = NULL;

	Mesh_Viewer_Mode = 0; // 0 = Defaulet Objects 1 = Collectables

	// ------------------------------------------------ 
	Physics_Type = Enums::Bullet_Type_None;
	Physics_Shape = Enums::NoShape;

	SelectDynamic = 0;
	SelectStatic = 0;
	SelectTriMesh = 0;

	Selected_Shape_Box = 0;
	Selected_Shape_Sphere = 0;
	Selected_Shape_Capsule = 0;
	Selected_Shape_Cylinder = 0;
	Selected_Shape_Cone = 0;

	Placement_Camera = 1;

	// ------------------------------------------------ 

	Last_MeshFile[0] = 0;
	m_Material_File[0] = 0;

	strcpy(mResource_Folder, App->EquityDirecory_FullPath);
	strcat(mResource_Folder, "\\Media_New\\Walls\\");
	strcpy(Selected_MeshFile, "Wall_1.mesh");

	strcpy(m_Current_Folder, "Structure");

	MV_Resource_Group = "MV_Resource_Group";

	/*btDebug_Manual = mSceneMgrMeshView->createManualObject("MVManual");
	btDebug_Manual->setRenderQueueGroup(RENDER_QUEUE_MAX);

	btDebug_Manual->setDynamic(true);
	btDebug_Manual->estimateVertexCount(2000);

	btDebug_Manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1,1,1,1);
	btDebug_Manual->end();

	btDebug_Node = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
	btDebug_Node->attachObject(btDebug_Manual);*/
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

	//Set_Debug_Shapes();

	if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area)
	{
		strcpy(mResource_Folder, App->EquityDirecory_FullPath);
		strcat(mResource_Folder, "\\Media_New\\Areas\\");
		strcpy(Selected_MeshFile, "Test1.mesh");
	}
	else
	{
		strcpy(mResource_Folder, App->EquityDirecory_FullPath);
		strcat(mResource_Folder, "\\Media_New\\Walls\\");
		strcpy(Selected_MeshFile, "Wall_1.mesh");
	}


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

		SendDlgItemMessage(hDlg, IDC_STPLACEMENT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKPLACECAMERA, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CKPLACECENTER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_BT_PROPERTIES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CB_FOLDERS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ST_CURRENTFOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		
		SetDlgItemText(hDlg, IDC_ST_CURRENTFOLDER, App->SBC_MeshViewer->mResource_Folder);

		SetWindowText(hDlg, App->SBC_MeshViewer->mResource_Folder);

		HWND temp = GetDlgItem(hDlg, IDC_CKPLACECAMERA);
		SendMessage(temp, BM_SETCHECK, 1, 0);

		App->SBC_MeshViewer->ListHwnd = GetDlgItem(hDlg, IDC_LISTFILES);

		App->SBC_MeshViewer->MeshView_Hwnd = GetDlgItem(hDlg, IDC_OGREWIN);
		App->SBC_MeshViewer->Set_OgreWindow();

		HWND CB_hWnd = GetDlgItem(hDlg, IDC_CB_FOLDERS);

		App->SBC_MeshViewer->Get_Media_Folders_Actors(CB_hWnd); // Populate Combo

		App->SBC_MeshViewer->SelectStatic = 0;
		App->SBC_MeshViewer->SelectDynamic = 0;
		App->SBC_MeshViewer->SelectTriMesh = 0;


		if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area)
		{
			App->SBC_MeshViewer->SetUp_Area_Trimesh(hDlg);
		}


		if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Objects 
			|| App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Collectables)
		{
			App->SBC_MeshViewer->Set_ResourceMesh_File(hDlg);
			App->SBC_MeshViewer->Get_Files();

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

		if (GetDlgItem(hDlg, IDC_STPLACEMENT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_CKPLACECAMERA) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_CKPLACECENTER) == (HWND)lParam)
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


		if (LOWORD(wParam) == IDC_CKPLACECAMERA)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CKPLACECAMERA);
			SendMessage(temp, BM_SETCHECK, 1, 0);

			temp = GetDlgItem(hDlg, IDC_CKPLACECENTER);
			SendMessage(temp, BM_SETCHECK, 0, 0);

			App->SBC_MeshViewer->Placement_Camera = 1;
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKPLACECENTER)
		{

			HWND temp = GetDlgItem(hDlg, IDC_CKPLACECENTER);
			SendMessage(temp, BM_SETCHECK, 1, 0);

			temp = GetDlgItem(hDlg, IDC_CKPLACECAMERA);
			SendMessage(temp, BM_SETCHECK, 0, 0);

			App->SBC_MeshViewer->Placement_Camera = 0;
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_PROPERTIES)
		{

			App->SBC_MeshViewer->Show_Mesh_Properties();

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

			App->SBC_MeshViewer->Update_Mesh(App->SBC_MeshViewer->Selected_MeshFile);

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

			App->SBC_MeshViewer->Show_Physics_Trimesh();

			return 1;
		}

		if (LOWORD(wParam) == IDC_MVSTATIC)
		{
			App->SBC_MeshViewer->Physics_Type = Enums::Bullet_Type_Static;
			App->SBC_MeshViewer->Physics_Shape = Enums::NoShape;
			App->SBC_MeshViewer->SelectStatic = 1;
			App->SBC_MeshViewer->SelectDynamic = 0;
			App->SBC_MeshViewer->SelectTriMesh = 0;
			
			App->SBC_MeshViewer->Enable_ShapeButtons(true);

			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Show_Physics_None();

			return 1;
		}

		if (LOWORD(wParam) == IDC_DYNAMIC)
		{
			App->SBC_MeshViewer->Physics_Type = Enums::Bullet_Type_Dynamic;
			App->SBC_MeshViewer->Physics_Shape = Enums::NoShape;
			App->SBC_MeshViewer->SelectDynamic = 1;
			App->SBC_MeshViewer->SelectStatic = 0;
			App->SBC_MeshViewer->SelectTriMesh = 0;

			App->SBC_MeshViewer->Enable_ShapeButtons(true);

			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Show_Physics_None();

			return 1;
		}

		// --------------------------------------------------------------------- Shapes
		if (LOWORD(wParam) == IDC_BOX)
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Box = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Shape_Box;

			App->SBC_MeshViewer->Show_Physics_Box();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_SPHERE)
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Sphere = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Sphere;

			App->SBC_MeshViewer->Show_Physics_Sphere();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CAPSULE)
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Capsule = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Capsule;

			App->SBC_MeshViewer->Show_Physics_Capsule();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CYLINDER)
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Cylinder = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Cylinder;

			App->SBC_MeshViewer->Show_Physics_Cylinder();

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CONE)
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Cone = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Cone;

			App->SBC_MeshViewer->Show_Physics_Cone();
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{

			if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area || App->SBC_MeshViewer->Physics_Type == Enums::Bullet_Type_TriMesh)
			{
				
			}
			else if (App->SBC_MeshViewer->Physics_Type == Enums::Bullet_Type_None || App->SBC_MeshViewer->Physics_Shape == Enums::NoShape)
			{
				App->Say("No Type or Shape Selected");
				return TRUE;
			}


			char buff[255];
			GetDlgItemText(hDlg, IDC_OBJECTNAME, (LPTSTR)buff, 256);
			strcpy(App->SBC_MeshViewer->Object_Name, buff);

			App->Cl19_Ogre->OgreListener->MeshViewer_Running = 0;
			
			if (App->SBC_MeshViewer->Phys_Body)
			{
				App->Cl_Bullet->dynamicsWorld->removeCollisionObject(App->SBC_MeshViewer->Phys_Body);
				App->SBC_MeshViewer->Phys_Body = nullptr;
			}

			App->SBC_MeshViewer->Close_OgreWindow();
			App->SBC_MeshViewer->Delete_Resources_Group();

			if (App->SBC_MeshViewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area) // Area
			{
				App->SBC_MeshViewer->Copy_Assets();
				App->SBC_Objects_Create->Add_New_Area();
			}
			else // Normal Object
			{
				App->SBC_MeshViewer->Copy_Assets();
				App->SBC_Objects_Create->Add_Objects_From_MeshViewer();
			}

			App->SBC_MeshViewer->Set_Debug_Shapes();

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}


		if (LOWORD(wParam) == IDCANCEL)
		{

			App->Cl19_Ogre->OgreListener->MeshViewer_Running = 0;

			if (App->SBC_MeshViewer->MvEnt && App->SBC_MeshViewer->MvNode)
			{
				App->SBC_MeshViewer->MvNode->detachAllObjects();
				App->SBC_MeshViewer->mSceneMgrMeshView->destroySceneNode(App->SBC_MeshViewer->MvNode);
				App->SBC_MeshViewer->mSceneMgrMeshView->destroyEntity(App->SBC_MeshViewer->MvEnt);
				App->SBC_MeshViewer->MvEnt = NULL;
				App->SBC_MeshViewer->MvNode = NULL;
			}

			if (App->SBC_MeshViewer->Phys_Body)
			{
				App->Cl_Bullet->dynamicsWorld->removeCollisionObject(App->SBC_MeshViewer->Phys_Body);
				App->SBC_MeshViewer->Phys_Body = nullptr;
			}

			App->SBC_MeshViewer->Close_OgreWindow();

			App->SBC_MeshViewer->Delete_Resources_Group();

			App->SBC_MeshViewer->Set_Debug_Shapes();
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;
	}
	return FALSE;
}

// *************************************************************************
// *	  			Copy_Assets:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_MeshViewer::Copy_Assets()
{
	
	App->SBC_Scene->Add_Resource_Location_Project(App->SBC_MeshViewer->mResource_Folder);

	
	//Get_Mesh_Assets();

	// ------------------ Copy Mesh
	strcpy(SourceFile, App->SBC_MeshViewer->mResource_Folder);
	strcat(SourceFile, App->SBC_MeshViewer->Selected_MeshFile);

	strcpy(DestinationFile, App->SBC_Project->m_Main_Assets_Path);
	strcat(DestinationFile, App->SBC_MeshViewer->Selected_MeshFile);

	CopyFile(SourceFile, DestinationFile, false);

	// ------------------ Copy Material File
	strcpy(SourceFile, App->SBC_MeshViewer->mResource_Folder);
	strcat(SourceFile, App->SBC_MeshViewer->m_Material_File);

	strcpy(DestinationFile, App->SBC_Project->m_Main_Assets_Path);
	strcat(DestinationFile, App->SBC_MeshViewer->m_Material_File);

	CopyFile(SourceFile, DestinationFile, false);

	// ------------------ Copy Textures
	int Count = 0;
	while (Count < Texure_Count)
	{
		strcpy(SourceFile, App->SBC_MeshViewer->mResource_Folder);
		strcat(SourceFile, v_Texture_Names[Count].c_str());

		strcpy(DestinationFile, App->SBC_Project->m_Main_Assets_Path);
		strcat(DestinationFile, v_Texture_Names[Count].c_str());

		CopyFile(SourceFile, DestinationFile, false);

		Count++;
	}
	
}

// *************************************************************************
// *	  		Get_Mesh_Assets:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_MeshViewer::Get_Mesh_Assets()
{
	App->SBC_MeshViewer->m_Material_File[0] = 0;
	v_Texture_Names.resize(0);
	Texure_Count = 0;

	int SubMeshCount = App->SBC_MeshViewer->MvEnt->getNumSubEntities();
	char pScriptName[255];
	char pMaterialFile[255];
	Ogre::String st;
	Ogre::MaterialPtr MP;

	MP.setNull();
	bool loaded = 0;
	
	// ---------------------------------------------------------- Material File
	Ogre::SubMesh const *subMesh = App->SBC_MeshViewer->MvEnt->getSubEntity(0)->getSubMesh();
	Ogre::String MatName = subMesh->getMaterialName();
	strcpy(pScriptName, MatName.c_str());

	loaded = Ogre::MaterialManager::getSingleton().resourceExists(MatName);

	if (loaded == 1)
	{
		MP = Ogre::MaterialManager::getSingleton().getByName(MatName, App->SBC_MeshViewer->MV_Resource_Group);
		st = MP->getOrigin();
		strcpy(pMaterialFile, st.c_str());

		strcpy(App->SBC_MeshViewer->m_Material_File, pMaterialFile);
	}
	else
	{
		//strcpy(test, "Not Loaded:- ");
	}

	// ---------------------------------------------------------- Textures
	Ogre::ResourcePtr TP;
	Ogre::ResourceManager::ResourceMapIterator TextureIterator = Ogre::TextureManager::getSingleton().getResourceIterator();

	while (TextureIterator.hasMoreElements())
	{
		//strcpy(pScriptName,(static_cast<Ogre::MaterialPtr>(TextureIterator.peekNextValue()))->getName().c_str());

		if (TextureIterator.peekNextValue()->getGroup() == App->SBC_MeshViewer->MV_Resource_Group)
		{

			strcpy(pScriptName, TextureIterator.peekNextValue()->getName().c_str());
			TP = Ogre::TextureManager::getSingleton().getByName(pScriptName);

			if (TP->isLoaded() == 1)
			{
				v_Texture_Names.push_back(pScriptName);
				Texure_Count = v_Texture_Names.size();
			}
			else
			{
				v_Texture_Names.push_back(pScriptName);
				Texure_Count = v_Texture_Names.size();
				//App->Say(pScriptName);
				//strcpy(test, "Not Loaded:- ");	
			}

		}

		TextureIterator.moveNext();
	}
	
	//Ogre::Pass *myMatPass = Ogre::MaterialManager::getSingletonPtr()->getByName("material bkt_ball")->getTechnique(0)->getPass(0);
	//Ogre::String test = myMatPass->getTextureUnitState(0)->getName();
	//App->Say(test.c_str());

	//or: myMatPass->getTextureUnitState(0)->setTextureName( "myTexture" );

	/*Ogre::ResourcePtr kres_it = MaterialManager::getSingleton().getResourceByName(pMaterialFile);
	
	ResourceManager::ResourceMapIterator res_it = MaterialManager::getSingleton().getResourceIterator();*/

	//while (res_it.hasMoreElements())
	//{

	//	ResourcePtr resource = res_it.getNext();
	//	MaterialPtr material = resource.staticCast<Material>();
	//	Material::TechniqueIterator tech_it = material->getTechniqueIterator();

	//	Ogre::String test= material->getName();
	//	//App->Say(test.c_str());

	//	while (tech_it.hasMoreElements())
	//	{
	//		Technique* technique = tech_it.getNext();
	//		Technique::PassIterator pass_it = technique->getPassIterator();
	//		while (pass_it.hasMoreElements())
	//		{
	//			Pass* pass = pass_it.getNext();

	//			int Passnum = technique->getNumPasses();

	//			int poop = technique->getPass(0)->getNumTextureUnitStates();
	//			//App->Say_Int(poop);

	//			if (poop > 0)
	//			{
	//				Ogre::String test = technique->getPass(0)->getTextureUnitState(0)->getTextureName();
	//				//App->Say(test.c_str()); Works
	//			}

	//			//Ogre::String test = pass->getTextureUnitState(1)->getTextureName();
	//			//App->Say(test.c_str());

	//			//TextureUnitState* tus = pass->getTextureUnitState(0);
	//			//if (tus != 0)
	//			//{
	//				//tus->setTexture(m_cubemap_filter->getTexture());
	//			//}
	//		}
	//	}
	//}
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
// *			Update_Mesh:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_MeshViewer::Update_Mesh(char* MeshFile)
{
	if (MvEnt && MvNode)
	{
		MvNode->detachAllObjects();
		mSceneMgrMeshView->destroySceneNode(MvNode);
		mSceneMgrMeshView->destroyEntity(MvEnt);
		MvEnt = NULL;
		MvNode = NULL;
	}

	MvEnt = mSceneMgrMeshView->createEntity("MV",MeshFile, App->SBC_MeshViewer->MV_Resource_Group);
	MvNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
	MvNode->attachObject(MvEnt);
	MvNode->setPosition(0, 0, 0);

	Ogre::Vector3 Centre = MvEnt->getBoundingBox().getCenter();

	Ogre::Real Radius = MvEnt->getBoundingRadius();

	mCameraMeshView->setPosition(0, Centre.y, -Radius*2.5);
	mCameraMeshView->lookAt(0, Centre.y, 0);

	Get_Mesh_Assets();

	if (Physics_Shape == Enums::Shape_Box)
	{
		Show_Physics_Box();
	}

	if (Physics_Shape == Enums::Sphere)
	{
		Show_Physics_Sphere();
	}

	if (Physics_Shape == Enums::Capsule)
	{
		Show_Physics_Capsule();
	}

	if (Physics_Shape == Enums::Cylinder)
	{
		Show_Physics_Cylinder();
	}

	if (App->SBC_MeshViewer->Physics_Shape == Enums::Cone)
	{
		Show_Physics_Cone();
	}

	if (App->SBC_MeshViewer->Physics_Type == Enums::Bullet_Type_TriMesh)
	{
		Show_Physics_Trimesh();
	}

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
	mCameraMeshView->setFarClipDistance(8000);

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


	// Debug Physics Shape
	btDebug_Manual = mSceneMgrMeshView->createManualObject("MVManual");
	btDebug_Manual->setRenderQueueGroup(RENDER_QUEUE_MAX);

	btDebug_Manual->setDynamic(true);
	btDebug_Manual->estimateVertexCount(2000);

	btDebug_Manual->begin("BaseWhiteNoLighting", Ogre::RenderOperation::OT_LINE_LIST);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1,1,1,1);
	btDebug_Manual->end();

	btDebug_Node = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
	btDebug_Node->attachObject(btDebug_Manual);

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
	App->SBC_MeshViewer->Update_Mesh(App->SBC_MeshViewer->Selected_MeshFile);

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
	bool Test = Ogre::ResourceGroupManager::getSingleton().resourceLocationExists(mResource_Folder, MV_Resource_Group);

	if (Test == 0)
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(mResource_Folder, "FileSystem", MV_Resource_Group);
		Ogre::ResourceGroupManager::getSingleton().clearResourceGroup(MV_Resource_Group);
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(MV_Resource_Group);

	}
	
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
	Update_Mesh(Selected_MeshFile);

	return 1;
}

// *************************************************************************
// *	  	Show_Mesh_Properties:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_MeshViewer::Show_Mesh_Properties()
{
	DialogBox(App->hInst,(LPCTSTR)IDD_LISTDATA, MainDlgHwnd,(DLGPROC)Mesh_Properties_Proc);
}

// *************************************************************************
// *		Properties_ListBox_Proc:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
LRESULT CALLBACK SB_MeshViewer::Mesh_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_LISTGROUP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		HWND List = GetDlgItem(hDlg, IDC_LISTGROUP);
		ListView_DeleteAllItems(List);

		SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_MeshViewer->mResource_Folder);
		SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"");
		SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_MeshViewer->Selected_MeshFile);
		SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_MeshViewer->m_Material_File);
		SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)"");

		int Count = 0;
		while (Count < App->SBC_MeshViewer->Texure_Count)
		{
			SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)App->SBC_MeshViewer->v_Texture_Names[Count].c_str());
			
			Count++;
		}

		return TRUE;
	}

	

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
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

// *************************************************************************
// *	  	Set_Debug_Shapes:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_MeshViewer::Set_Debug_Shapes()
{
	int Count = 0;

	while (Count < App->SBC_Scene->Player_Count)
	{
		if (App->SBC_Scene->B_Player[Count]->Physics_Debug_On == 1)
		{
			int f = App->SBC_Scene->B_Player[Count]->Phys_Body->getCollisionFlags();
			App->SBC_Scene->B_Player[Count]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
		}

		Count++;
	}

	Count = 0;
	while (Count < App->SBC_Scene->Object_Count)
	{
		if (App->SBC_Scene->B_Object[Count]->Physics_Debug_On == 1)
		{
			int f = App->SBC_Scene->B_Object[Count]->Phys_Body->getCollisionFlags();
			App->SBC_Scene->B_Object[Count]->Phys_Body->setCollisionFlags(f ^ btCollisionObject::CF_DISABLE_VISUALIZE_OBJECT);
		}

		Count++;
	}

	App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 0;
	App->Cl19_Ogre->RenderFrame();
	App->Cl19_Ogre->BulletListener->Render_Debug_Flag = 1;
}

// *************************************************************************
// *			Show_Physics_None:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_MeshViewer::Show_Physics_None()
{
	btDebug_Manual->beginUpdate(0);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->end();

	if (Phys_Body)
	{
		App->Cl_Bullet->dynamicsWorld->removeCollisionObject(Phys_Body);
		Phys_Body = nullptr;
	}
}
// *************************************************************************
// *			Show_Physics_Box:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_MeshViewer::Show_Physics_Box()
{
	btDebug_Manual->beginUpdate(0);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1,1,1);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1,1,1);
	btDebug_Manual->end();

	if (Phys_Body)
	{
		App->Cl_Bullet->dynamicsWorld->removeCollisionObject(Phys_Body);
		Phys_Body = nullptr;
	}

	AxisAlignedBox worldAAB = MvEnt->getBoundingBox();
	worldAAB.transformAffine(MvNode->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0, 0, 0, 1));

	btScalar mass;
	mass = 1.0f;
	
	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);
	startTransform.setOrigin(initialPosition);

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(MvNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	btCollisionShape* newRigidShape = new btBoxShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Phys_Body = new btRigidBody(rbInfo);
	Phys_Body->setRestitution(1.0);
	Phys_Body->setFriction(1.5);
	Phys_Body->setUserPointer(MvNode);
	Phys_Body->setWorldTransform(startTransform);

	Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Phys_Body);

	//Set_Physics(Index);
}

// *************************************************************************
// *		Show_Physics_Capsule:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_MeshViewer::Show_Physics_Capsule()
{
	btDebug_Manual->beginUpdate(0);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->end();

	if (Phys_Body)
	{
		App->Cl_Bullet->dynamicsWorld->removeCollisionObject(Phys_Body);
		Phys_Body = nullptr;
	}

	AxisAlignedBox worldAAB = MvEnt->getBoundingBox();
	worldAAB.transformAffine(MvNode->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	//Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btScalar mass;
	mass = 0.0f;
	
	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

	startTransform.setOrigin(initialPosition);

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(MvNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(MvNode);
	
	btCollisionShape* newRigidShape = new btCapsuleShape(Radius, sy);
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Phys_Body = new btRigidBody(rbInfo);
	Phys_Body->setRestitution(1.0);
	Phys_Body->setFriction(1.5);
	Phys_Body->setUserPointer(MvNode);
	Phys_Body->setWorldTransform(startTransform);

	Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Phys_Body);

	//Set_Physics(Index);
}

// *************************************************************************
// *		Show_Physics_Cone:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_MeshViewer::Show_Physics_Cone()
{
	btDebug_Manual->beginUpdate(0);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->end();

	if (Phys_Body)
	{
		App->Cl_Bullet->dynamicsWorld->removeCollisionObject(Phys_Body);
		Phys_Body = nullptr;
	}

	AxisAlignedBox worldAAB = MvEnt->getBoundingBox();
	worldAAB.transformAffine(MvNode->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btScalar mass;
	mass = 0.0f;
	
	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

	startTransform.setOrigin(initialPosition);

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(MvNode);
	float sx = Size.x / 2;
	float sy = Size.y;// / 2;
	float sz = Size.z / 2;

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(MvNode);
	
	btCollisionShape* newRigidShape = new btConeShape(Radius, sy);
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Phys_Body = new btRigidBody(rbInfo);
	Phys_Body->setRestitution(1.0);
	Phys_Body->setFriction(1.5);
	Phys_Body->setUserPointer(MvNode);
	Phys_Body->setWorldTransform(startTransform);

	Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Phys_Body);

	//Set_Physics(Index);
}

// *************************************************************************
// *		Show_Physics_Sphere:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_MeshViewer::Show_Physics_Sphere()
{
	btDebug_Manual->beginUpdate(0);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->end();

	if (Phys_Body)
	{
		App->Cl_Bullet->dynamicsWorld->removeCollisionObject(Phys_Body);
		Phys_Body = nullptr;
	}

	AxisAlignedBox worldAAB = MvEnt->getBoundingBox();
	worldAAB.transformAffine(MvNode->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btScalar mass;
	mass = 0.0f;
	

	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

	startTransform.setOrigin(initialPosition);

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(MvNode);
	
	btCollisionShape* newRigidShape = new btSphereShape(Radius);
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Phys_Body = new btRigidBody(rbInfo);
	Phys_Body->setRestitution(1.0);
	Phys_Body->setFriction(1.5);
	Phys_Body->setUserPointer(MvNode);
	Phys_Body->setWorldTransform(startTransform);

	Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Phys_Body);

	//Set_Physics(Index);
}

// *************************************************************************
// *		Show_Physics_Cylinder:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_MeshViewer::Show_Physics_Cylinder()
{
	btDebug_Manual->beginUpdate(0);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->end();

	if (Phys_Body)
	{
		App->Cl_Bullet->dynamicsWorld->removeCollisionObject(Phys_Body);
		Phys_Body = nullptr;
	}

	AxisAlignedBox worldAAB = MvEnt->getBoundingBox();
	worldAAB.transformAffine(MvNode->_getFullTransform());
	Ogre::Vector3 Centre = worldAAB.getCenter();
	//Ogre::Vector3 Centre = Object->Get_BoundingBox_World_Centre();

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));

	btScalar mass;
	mass = 0.0f;
	

	btVector3 localInertia(0, 0, 0);
	btVector3 initialPosition(Centre.x, Centre.y, Centre.z);

	startTransform.setOrigin(initialPosition);

	Ogre::Vector3 Size = App->Cl_Objects_Com->GetMesh_BB_Size(MvNode);
	float sx = Size.x / 2;
	float sy = Size.y / 2;
	float sz = Size.z / 2;

	float Radius = App->Cl_Objects_Com->GetMesh_BB_Radius(MvNode);
	
	btCollisionShape* newRigidShape = new btCylinderShape(btVector3(sx, sy, sz));
	newRigidShape->calculateLocalInertia(mass, localInertia);

	App->Cl_Bullet->collisionShapes.push_back(newRigidShape);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);

	btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, newRigidShape, localInertia);

	Phys_Body = new btRigidBody(rbInfo);
	Phys_Body->setRestitution(1.0);
	Phys_Body->setFriction(1.5);
	Phys_Body->setUserPointer(MvNode);
	Phys_Body->setWorldTransform(startTransform);

	Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Phys_Body);

	//Set_Physics(Index);
}

// *************************************************************************
// *		Show_Physics_Trimesh:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_MeshViewer::Show_Physics_Trimesh()
{
	btDebug_Manual->beginUpdate(0);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->position(0, 0, 0);
	btDebug_Manual->colour(1, 1, 1);
	btDebug_Manual->end();

	if (Phys_Body)
	{
		App->Cl_Bullet->dynamicsWorld->removeCollisionObject(Phys_Body);
		Phys_Body = nullptr;
	}

	// Get the mesh from the entity
	Ogre::MeshPtr myMesh = MvEnt->getMesh();
	Ogre::Mesh::SubMeshIterator SubMeshIter = myMesh->getSubMeshIterator();

	// Create the triangle mesh
	btTriangleMesh* triMesh = NULL;
	btVector3 vert0, vert1, vert2;
	int i = 0;

	while (SubMeshIter.hasMoreElements())
	{
		i = 0;
		Ogre::SubMesh* subMesh = SubMeshIter.getNext();
		Ogre::IndexData* indexData = subMesh->indexData;
		Ogre::VertexData* vertexData = subMesh->vertexData;

		// -------------------------------------------------------
		// Get the position element
		const Ogre::VertexElement* posElem = vertexData->vertexDeclaration->findElementBySemantic(Ogre::VES_POSITION);
		// Get a pointer to the vertex buffer
		Ogre::HardwareVertexBufferSharedPtr vBuffer = vertexData->vertexBufferBinding->getBuffer(posElem->getSource());
		// Get a pointer to the index buffer
		Ogre::HardwareIndexBufferSharedPtr iBuffer = indexData->indexBuffer;

		// -------------------------------------------------------
		// The vertices and indices used to create the triangle mesh
		std::vector<Ogre::Vector3> vertices;
		vertices.reserve(vertexData->vertexCount);
		std::vector<unsigned long> indices;
		indices.reserve(indexData->indexCount);

		// -------------------------------------------------------
		// Lock the Vertex Buffer (READ ONLY)
		unsigned char* vertex = static_cast<unsigned char*> (vBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		float* pReal = NULL;

		for (size_t j = 0; j < vertexData->vertexCount; ++j, vertex += vBuffer->getVertexSize()) {
			posElem->baseVertexPointerToElement(vertex, &pReal);
			Ogre::Vector3 pt(pReal[0], pReal[1], pReal[2]);

			vertices.push_back(pt);
		}
		vBuffer->unlock();
		// -------------------------------------------------------
		bool use32bitindexes = (iBuffer->getType() == Ogre::HardwareIndexBuffer::IT_32BIT);

		// -------------------------------------------------------
		// Lock the Index Buffer (READ ONLY)
		unsigned long* pLong = static_cast<unsigned long*> (iBuffer->lock(Ogre::HardwareBuffer::HBL_READ_ONLY));
		unsigned short* pShort = reinterpret_cast<unsigned short*> (pLong);

		if (use32bitindexes) {
			for (size_t k = 0; k < indexData->indexCount; ++k) {
				//
				indices.push_back(pLong[k]);
			}
		}
		else {
			for (size_t k = 0; k < indexData->indexCount; ++k) {
				//
				indices.push_back(static_cast<unsigned long> (pShort[k]));
			}
		}
		iBuffer->unlock();

		// -------------------------------------------------------
		// We now have vertices and indices ready to go
		// ----

		if (triMesh == nullptr)
		{
			triMesh = new btTriangleMesh(use32bitindexes);
		}

		for (size_t y = 0; y < indexData->indexCount / 3; y++) {
			// Set each vertex
			vert0.setValue(vertices[indices[i]].x, vertices[indices[i]].y, vertices[indices[i]].z);
			vert1.setValue(vertices[indices[i + 1]].x, vertices[indices[i + 1]].y, vertices[indices[i + 1]].z);
			vert2.setValue(vertices[indices[i + 2]].x, vertices[indices[i + 2]].y, vertices[indices[i + 2]].z);

			// Add the triangle into the triangle mesh
			triMesh->addTriangle(vert0, vert1, vert2);

			// Increase index count
			i += 3;
		}

		//App->Say("here");
	}

	const bool useQuantizedAABB = true;
	btBvhTriangleMeshShape* mShape = new btBvhTriangleMeshShape(triMesh, false, true);
	//mShape->buildOptimizedBvh();

	float x = MvNode->getPosition().x;
	float y = MvNode->getPosition().y;
	float z = MvNode->getPosition().z;

	btVector3 inertia(0, 0, 0);
	mShape->calculateLocalInertia(0.0, inertia);

	btTransform startTransform;
	startTransform.setIdentity();
	startTransform.setRotation(btQuaternion(0.0f, 0.0f, 0.0f, 1));
	btVector3 initialPosition(x, y, z);
	startTransform.setOrigin(initialPosition);

	btDefaultMotionState* myMotionState = new btDefaultMotionState(startTransform);


	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI
	(
		0,  // mass
		myMotionState,// initial position
		mShape,      // collision shape of body
		inertia   // local inertia
	);

	Phys_Body = new btRigidBody(rigidBodyCI);
	Phys_Body->clearForces();
	Phys_Body->setLinearVelocity(btVector3(0, 0, 0));
	Phys_Body->setAngularVelocity(btVector3(0, 0, 0));
	Phys_Body->setWorldTransform(startTransform);

	Phys_Body->setCustomDebugColor(btVector3(0, 1, 1));

	App->Cl_Bullet->dynamicsWorld->addRigidBody(Phys_Body);

}

