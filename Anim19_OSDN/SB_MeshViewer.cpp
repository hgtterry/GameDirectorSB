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
	Detail_List_hLV = nullptr;
	// Folders
	Folders_MainWin_hWnd = NULL;
	Properties_hLV = NULL;

	MvEnt = NULL;
	MvNode = NULL;

	MeshView_Window = NULL;
	mSceneMgrMeshView = NULL;
	mCameraMeshView = NULL;
	CamNode = NULL;

	ShowRooms = 1;
	ShowBuildings = 0;
	ShowMisc = 0;
	Mesh_Viewer_Mode = 0; // 0 = Defaulet Objects 1 = Collectables

	S_Selection[0] = new Selection_type2();

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

	strcpy(Chr_CurrentFolder, App->EquityDirecory_FullPath);
	strcat(Chr_CurrentFolder, "\\Media\\Actors\\Ammo\\*.mesh");
	Last_MeshFile[0] = 0;

	Media_Folders_Count = 0;

	Folder_Vec.resize(20);
	strcpy(Folder_Vec[0].Folder_Path, App->EquityDirecory_FullPath);
	strcat(Folder_Vec[0].Folder_Path, "\\Data\\Cube_Ogre\\");
	FolderList_Count = 1;

	strcpy(TempFolder, Folder_Vec[0].Folder_Path);
	
	MV_Resource_Group = "MV_Resource_Group";
}


SB_MeshViewer::~SB_MeshViewer()
{
}

// *************************************************************************
// *					Clear_ButFlags Terry Bernie						   *
// *************************************************************************
bool SB_MeshViewer::Clear_ButFlags()
{
	ShowRooms = 0;
	ShowBuildings = 0;
	ShowMisc = 0;
	return 1;
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
// *				StartMeshViewer  Terry	Bernie						   *
// *************************************************************************
bool SB_MeshViewer::StartMeshViewer()
{
	MvEnt = NULL;
	MvNode = NULL;
	Last_MeshFile[0] = 0;

	App->RenderBackGround = 1;

	Create_Resources_Group();
	Add_Resources();
	
	DialogBox(App->hInst, (LPCTSTR)IDD_GD_MESHVIEWER, App->Fdlg, (DLGPROC)MeshViewer_Proc);

	App->Cl19_Ogre->OgreListener->MeshViewer_Running = 0;

	//Close_OgreWindow();

	//App->Cl19_Ogre->OgreListener->showDebugOverlay(true);
	//App->Cl19_Ogre->textArea->show();

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

		SendDlgItemMessage(hDlg, IDC_LISTFILES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_LISTDETAIL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_OBJECTNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STSHAPE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTYPE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STFOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_SELECTEDNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_MVBTADDFOLDERS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		App->SBC_MeshViewer->ListHwnd = GetDlgItem(hDlg, IDC_LISTFILES);
		
		App->SBC_MeshViewer->MeshView_Hwnd = GetDlgItem(hDlg, IDC_OGREWIN);
		App->SBC_MeshViewer->Set_OgreWindow();

		//App->Cl19_Ogre->textArea->hide();

		//Ogre::Root::getSingletonPtr()->renderOneFrame();
		//Ogre::Root::getSingletonPtr()->renderOneFrame();

		//App->Cl_Mesh_Viewer->Get_Media_Folders_Actors(CB_hWnd); // Populate Combo


		App->SBC_MeshViewer->SelectStatic = 0;
		App->SBC_MeshViewer->SelectDynamic = 0;
		App->SBC_MeshViewer->SelectTriMesh = 0;

		App->SBC_MeshViewer->Enable_ShapeButtons(0);
		App->SBC_MeshViewer->Enable_TypeButtons(0);

		//	App->SBC_MeshViewer->Physics_Type = Enums::Bullet_Type_None;

		char ConNum[256];
		char ATest[256];

		App->SBC_MeshViewer->Get_Files();
		App->SBC_MeshViewer->Create_Detail_List();

		/*if (App->Cl_Mesh_Viewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Collectables)
		{
		strcpy_s(ATest, "Collectable_");
		_itoa(App->Cl_Scene_Data->ObjectCount, ConNum, 10);
		strcat(ATest, ConNum);
		SetDlgItemText(hDlg, IDC_OBJECTNAME, ATest);
		strcpy(App->Cl_Mesh_Viewer->Object_Name, ATest);

		ShowWindow(GetDlgItem(hDlg, IDC_MVSTATIC),1);
		App->Cl_Mesh_Viewer->SelectStatic = 1;
		App->Cl_Mesh_Viewer->Enable_ShapeButtons(1);
		App->Cl_Mesh_Viewer->Physics_Type = Enums::Bullet_Type_Static;

		}*/

		/*if (App->Cl_Mesh_Viewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area)
		{
		SendMessage(GetDlgItem(hDlg, IDC_CB_FOLDERS), CB_SELECTSTRING, -1, (LPARAM)"Areas_Levels");
		strcpy(App->Cl_Mesh_Viewer->Chr_CurrentFolder, App->EquityDirecory_FullPath);
		strcat(App->Cl_Mesh_Viewer->Chr_CurrentFolder, "\\Media\\Actors\\Areas_Levels\\*.mesh");
		App->Cl_Mesh_Viewer->SelectStartFolder();

		strcpy_s(ATest, "Area_");
		_itoa(App->Cl_Scene_Data->ObjectCount, ConNum, 10);
		strcat(ATest, ConNum);
		SetDlgItemText(hDlg, IDC_OBJECTNAME, ATest);
		strcpy(App->Cl_Mesh_Viewer->Object_Name, ATest);

		App->Cl_Mesh_Viewer->SelectTriMesh = 1;
		App->Cl_Mesh_Viewer->Physics_Type = Enums::Bullet_Type_TriMesh;
		ShowWindow(GetDlgItem(hDlg, IDC_TRIMESH), 1);

		}*/

		/*if (App->Cl_Mesh_Viewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Objects)
		{
		strcpy_s(ATest, "Object_");
		_itoa(App->Cl_Scene_Data->ObjectCount, ConNum, 10);
		strcat(ATest, ConNum);
		SetDlgItemText(hDlg, IDC_OBJECTNAME, ATest);
		strcpy(App->Cl_Mesh_Viewer->Object_Name, ATest);

		App->Cl_Mesh_Viewer->Enable_TypeButtons(1);
		}*/

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

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_MVBTADDFOLDERS && some_item->code == NM_CUSTOMDRAW)
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

		if (LOWORD(wParam) == ID_TOOLS_MVRESOURCEVIEWER)
		{
			App->SBC_Resources->Start_Resources(App->SBC_MeshViewer->MainDlgHwnd);
			return TRUE;
		}

		if (LOWORD(wParam) == ID_FOLDERS_POO)
		{

			App->SBC_MeshViewer->Start_Folders();

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_MVBTADDFOLDERS)
		{
			App->SBC_MeshViewer->Start_Folders();

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

			//App->GDCL_Mesh_Viewer->Start_ShapeDialog();
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
			//App->GDSBC_MeshViewer->Start_ShapeDialog();
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

		// ---------------------------------------------------------------------
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
			App->SBC_MeshViewer->ShowMesh(App->SBC_MeshViewer->Selected_MeshFile, 1);
			App->SBC_MeshViewer->Get_Details_hLV();
			return TRUE;

		}

		if (LOWORD(wParam) == IDOK)
		{

			/*if (App->Cl_Mesh_Viewer->Physics_Type == Enums::Bullet_Type_TriMesh)
			{

			}
			else if(App->Cl_Mesh_Viewer->Physics_Type == Enums::Bullet_Type_None || App->Cl_Mesh_Viewer->Physics_Shape == Enums::NoShape)
			{
			if (App->Cl_Mesh_Viewer->Physics_Type == Enums::Bullet_Type_TriMesh)
			{
			break;
			}

			App->Say("No Type or Shape Selected");
			return TRUE;
			}

			char buff[255];
			GetDlgItemText(hDlg,IDC_OBJECTNAME,(LPTSTR)buff,256);
			strcpy(App->Cl_Mesh_Viewer->Object_Name,buff);

			App->Cl_Objects_New->Dispatcher_New_Object();

			App->Cl19_Ogre->OgreListener->Equity_Running = 0;*/

			App->SBC_MeshViewer->Close_OgreWindow();
			App->SBC_MeshViewer->Delete_Resources_Group();
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			Debug1
			/*bool Test = App->Cl_Scene_Data->Is_Meshes_Used(App->Cl_Mesh_Viewer->Last_MeshFile);
			if (Test == 0)
			{
			Ogre::ResourcePtr ptr = Ogre::MeshManager::getSingleton().getByName(App->Cl_Mesh_Viewer->Last_MeshFile);
			ptr->unload();
			Ogre::MeshManager::getSingleton().remove(App->Cl_Mesh_Viewer->Last_MeshFile);
			App->Cl_Mesh_Viewer->Last_MeshFile[0] = 0;
			}

			App->Cl19_Ogre->OgreListener->Equity_Running = 0;*/
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
// *					ShowMesh Terry Bernie							   *
// *************************************************************************
void SB_MeshViewer::ShowMesh(char* MeshFile, bool Update)
{
	bool DeleteAll = 0;

	bool Test = App->Cl_Scene_Data->Is_Meshes_Used(Last_MeshFile);
	if (Test == 0)
	{
		DeleteAll = 1;
	}

	if (MvEnt && MvNode)
	{
		MvNode->detachAllObjects();
		mSceneMgrMeshView->destroySceneNode(MvNode);
		mSceneMgrMeshView->destroyEntity(MvEnt);
		MvEnt = NULL;
		MvNode = NULL;

		//if (DeleteAll == 1)
		//{
		//	Ogre::ResourcePtr pp = Ogre::MeshManager::getSingleton().getByName(Last_MeshFile);

		//	if (pp.isNull()) // is loaded
		//	{

		//	}
		//	else
		//	{
		//		Ogre::ResourcePtr ptr = Ogre::MeshManager::getSingleton().getByName(Last_MeshFile);
		//		ptr->unload();
		//		Ogre::MeshManager::getSingleton().remove(Last_MeshFile);
		//	}
		//}
	}

	strcpy(Last_MeshFile, MeshFile);

	MvEnt = mSceneMgrMeshView->createEntity(MeshFile);
	MvNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
	MvNode->attachObject(MvEnt);
	MvNode->setPosition(0, 0, 0);

	Ogre::Vector3 Centre = MvEnt->getBoundingBox().getCenter();

	Ogre::Real Radius = MvEnt->getBoundingRadius();

	mCameraMeshView->setPosition(0, Centre.y, -Radius*2.5);
	mCameraMeshView->lookAt(0, Centre.y, 0);

	//Flags[0]->MeshViewer_SpinObject = 1; // NEED TO CHECK FOR VALID OBJECT

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
	
	MvEnt = mSceneMgrMeshView->createEntity("MVTest2", "Cube.mesh", App->SBC_MeshViewer->MV_Resource_Group);
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
// *	  					Start_ShapeDialog Terry Bernie				   *
// *************************************************************************
void SB_MeshViewer::Start_ShapeDialog()
{
	///	DialogBox(App->hInst,(LPCTSTR)IDD_PHYSICSSHAPE,MainDlgHwnd,(DLGPROC)ShapeDialog_Proc);
}

// *************************************************************************
// *					ShapeDialog_Proc Terry Bernie 					   *
// *************************************************************************
LRESULT CALLBACK SB_MeshViewer::ShapeDialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG: // Bernie as the dialog is created
	{
		/*HFONT Font;
		Font = CreateFont( -15,0,0,0,FW_BOLD,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Aerial Black");
		SendDlgItemMessage(hDlg,IDC_STWAIT, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

		App->PLeaseWaitMessage_Hwnd = GetDlgItem(hDlg,IDC_STPROGRESS);*/

		//App->Cl_Grid->StartThread();
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		///      if (some_item->idFrom == IDC_BOX && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->Selected_Shape_Box);
			return CDRF_DODEFAULT;
		}

		///	if (some_item->idFrom == IDC_SPHERE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->Selected_Shape_Sphere);
			return CDRF_DODEFAULT;
		}

		///		if (some_item->idFrom == IDC_CAPSULE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->Selected_Shape_Capsule);
			return CDRF_DODEFAULT;
		}

		///		if (some_item->idFrom == IDC_CYLINDER && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->Selected_Shape_Cylinder);
			return CDRF_DODEFAULT;
		}

		///		if (some_item->idFrom == IDC_CONE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_MeshViewer->Selected_Shape_Cone);
			return CDRF_DODEFAULT;
		}

		// ---------------------------------------------------------------------
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
	case WM_CTLCOLORSTATIC:
	{
		/*if(GetDlgItem(hDlg,IDC_STWAIT) == (HWND)lParam)
		{
		SetBkColor((HDC) wParam, RGB(0, 255, 0));
		SetTextColor((HDC) wParam, RGB(0,255,0));
		SetBkMode((HDC) wParam, TRANSPARENT);
		return (UINT) App->BlackBrush;
		}

		if(GetDlgItem(hDlg,IDC_STPROGRESS) == (HWND)lParam)
		{
		SetBkColor((HDC) wParam, RGB(0, 255, 0));
		SetTextColor((HDC) wParam, RGB(0,255,0));
		SetBkMode((HDC) wParam, TRANSPARENT);
		return (UINT) App->BlackBrush;
		}*/
		return FALSE;
	}

	case WM_COMMAND:
	{
		///		if (LOWORD(wParam) == IDC_BOX) 
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Box = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Shape_Box;
			return TRUE;
		}

		///		if (LOWORD(wParam) == IDC_SPHERE) 
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Sphere = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Sphere;
			return TRUE;
		}

		///		if (LOWORD(wParam) == IDC_CAPSULE) 
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Capsule = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Capsule;
			return TRUE;
		}

		///		if (LOWORD(wParam) == IDC_CYLINDER) 
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Cylinder = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Cylinder;
			return TRUE;
		}

		///		if (LOWORD(wParam) == IDC_CONE) 
		{
			App->SBC_MeshViewer->Reset_Shape_Flags();
			App->SBC_MeshViewer->Selected_Shape_Cone = 1;
			App->RedrawWindow_Dlg(hDlg);

			App->SBC_MeshViewer->Physics_Shape = Enums::Cone;
			return TRUE;
		}

		//--------------------------------------

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
	}

	break;
	}

	return FALSE;
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
	char Path[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(Path, TempFolder);
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

	return 0;
}


// *************************************************************************
// *	  				Start_Folders  	Terry	Bernie					   *
// *************************************************************************
bool SB_MeshViewer::Start_Folders()
{

	DialogBox(App->hInst,(LPCTSTR)IDD_RESOURCEFOLDERS, MainDlgHwnd,(DLGPROC)Folders_Proc);
	return 1;
}
// *************************************************************************
// *        		Folders_Proc  Terry	Bernie							   *
// *************************************************************************
LRESULT CALLBACK SB_MeshViewer::Folders_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
	
		SendDlgItemMessage(hDlg, IDC_BTFOLDERADD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		App->SBC_MeshViewer->Folders_MainWin_hWnd = hDlg;

		App->SBC_MeshViewer->Create_Properties_hLV();

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

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

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
		
		if (some_item->idFrom == IDC_BTFOLDERADD && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}
	
		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BTFOLDERADD)
		{
			
			strcpy(App->CL_Vm_FileIO->BrowserMessage, "Select Folder to Scan");
			int Test = App->CL_Vm_FileIO->StartBrowser("");

			strcpy(App->SBC_MeshViewer->TempFolder, App->CL_Vm_FileIO->szSelectedDir);

			strcpy(App->SBC_MeshViewer->Folder_Vec[App->SBC_MeshViewer->FolderList_Count].Folder_Path, App->CL_Vm_FileIO->szSelectedDir);

			App->SBC_MeshViewer->FolderList_Count++;

			App->SBC_MeshViewer->Update_ListView();
			//App->SBC_MeshViewer->Get_Files();
			//App->SBC_MeshViewer->Add_Resources();

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDOK)
		{
			
			//App->SBC_MeshViewer->Update_ListView();
			App->SBC_MeshViewer->Get_Files();
			App->SBC_MeshViewer->Add_Resources();

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
// *					Create_Properties_hLV Terry Bernie				   *
// *************************************************************************
void SB_MeshViewer::Create_Properties_hLV(void)
{
	int NUM_COLS = 1;
	Properties_hLV = CreateWindowEx(0, WC_LISTVIEW, "",
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_VSCROLL | LVS_REPORT | LVS_NOCOLUMNHEADER | LVS_SHOWSELALWAYS, 2, 2,
		820, 300, Folders_MainWin_hWnd, 0, App->hInst, NULL);

	DWORD exStyles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES;

	ListView_SetExtendedListViewStyleEx(Properties_hLV, exStyles, exStyles);

	ListView_SetBkColor(Properties_hLV, RGB(255, 255, 255));
	ListView_SetTextBkColor(Properties_hLV, RGB(255, 255, 255));
	//listView.CheckBoxes

	LV_COLUMN lvC;
	memset(&lvC, 0, sizeof(LV_COLUMN));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	std::string headers[] =
	{
		""
	};
	int headerSize[] =
	{
		820
	};

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_InsertColumn(Properties_hLV, header, &lvC);
	}

	SendMessage(Properties_hLV, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

	Update_ListView();

	return;
}

// *************************************************************************
// *					Update_ListView	Terry Bernie 				 	   *
// *************************************************************************
bool SB_MeshViewer::Update_ListView()
{

	ListView_DeleteAllItems(Properties_hLV);

	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));

	int Count = 0;
	while (Count < FolderList_Count)
	{
		pitem.mask = LVIF_TEXT;
		pitem.iItem = Count;
		pitem.pszText = Folder_Vec[Count].Folder_Path;
		ListView_InsertItem(Properties_hLV, &pitem);
		//ListView_SetItemText(Properties_hLV, 0, 0, "Test");

		Count++;
	}

	
	return 1;
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

	int Count = 0;
	while (Count < FolderList_Count)
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Folder_Vec[Count].Folder_Path,
			"FileSystem", MV_Resource_Group);

		Count++;
	}

	try
	{
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(MV_Resource_Group);
	}
	catch (...)
	{

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
// *					Create_Detail_List Terry Bernie					   *
// *************************************************************************
bool SB_MeshViewer::Create_Detail_List()
{
	int NUM_COLS = 4;
	Detail_List_hLV = CreateWindowEx(0, WC_LISTVIEW, "",
		WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 11, 490,
		1120, 230, MainDlgHwnd, 0, App->hInst, NULL);

	DWORD exStyles = LVS_EX_GRIDLINES;

	ListView_SetExtendedListViewStyleEx(Detail_List_hLV, exStyles, exStyles);

	ListView_SetBkColor(Detail_List_hLV, RGB(250, 250, 250));
	ListView_SetTextBkColor(Detail_List_hLV, RGB(250, 250, 250));

	LV_COLUMN lvC;
	memset(&lvC, 0, sizeof(LV_COLUMN));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	std::string headers[] =
	{
		"Script", "Material File","Used","Path"
	};
	int headerSize[] =
	{
		165,180,70,250
	};

	//Groups

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_InsertColumn(Detail_List_hLV, header, &lvC);
	}
	SendMessage(Detail_List_hLV, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
	
	//ShowAllTextures();
	return 1;
}

// *************************************************************************
// *					Get_Details_hLV Terry Bernie	 			 	   *
// *************************************************************************
bool SB_MeshViewer::Get_Details_hLV()
{
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	int	 pRow = 0;
	char pScriptName[255];
	char pMaterialFile[255];
	char pUsed[255];
	bool pIsLoaded = 0;

	int SubMeshCount = MvEnt->getNumSubEntities();
	int Count = 0;

	Ogre::String st;
	Ogre::MaterialPtr pp;

	pp.setNull();
	bool loaded = 0;

	ListView_DeleteAllItems(Detail_List_hLV);

	while (Count < SubMeshCount)
	{
		Ogre::SubMesh const *subMesh = MvEnt->getSubEntity(Count)->getSubMesh();
		Ogre::String MatName = subMesh->getMaterialName();
		strcpy(pScriptName, MatName.c_str());

		loaded = Ogre::MaterialManager::getSingleton().resourceExists(MatName);

		if (loaded == 1)
		{
			pp = Ogre::MaterialManager::getSingleton().getByName(MatName, MV_Resource_Group);
			st = pp->getOrigin();
			strcpy(pMaterialFile, st.c_str());
		}
		else
		{
			strcpy(pMaterialFile," Not Loaded");
		}


		pitem.iItem = pRow;
		pitem.pszText = pScriptName;

		ListView_InsertItem(Detail_List_hLV, &pitem);
		ListView_SetItemText(Detail_List_hLV, pRow, 1, pMaterialFile);
		ListView_SetItemText(Detail_List_hLV, pRow, 2, "----");
		ListView_SetItemText(Detail_List_hLV, pRow, 3, "----");

		pRow++;
		Count++;
	}

	return 1;
}

