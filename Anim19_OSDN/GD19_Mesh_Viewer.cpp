#include "StdAfx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Mesh_Viewer.h"

#pragma warning( disable : 4244)

GD19_Mesh_Viewer::GD19_Mesh_Viewer(void)
{
	MeshView_Hwnd = NULL;
	ListHwnd = NULL;

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

	S_Selection[0] = new Selection_type();

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

	strcpy(Chr_CurrentFolder,App->EquityDirecory_FullPath);
	strcat(Chr_CurrentFolder,"\\Media\\Actors\\Ammo\\*.mesh");
	Last_MeshFile[0] = 0 ;

	Media_Folders_Count = 0;
}	



GD19_Mesh_Viewer::~GD19_Mesh_Viewer(void)
{
}

// *************************************************************************
// *					Clear_ButFlags Terry Bernie						   *
// *************************************************************************
bool GD19_Mesh_Viewer::Clear_ButFlags()
{
	ShowRooms = 0;
	ShowBuildings = 0;
	ShowMisc = 0;
	return 1;
}

// *************************************************************************
// *					Enable_ShapeButtons Terry Bernie				   *
// *************************************************************************
void GD19_Mesh_Viewer::Enable_TypeButtons(bool state)
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
void GD19_Mesh_Viewer::Enable_ShapeButtons(bool state)
{
	EnableWindow(GetDlgItem(MainDlgHwnd,IDC_BOX),state);
	EnableWindow(GetDlgItem(MainDlgHwnd,IDC_SPHERE),state);
	EnableWindow(GetDlgItem(MainDlgHwnd,IDC_CAPSULE),state);
	EnableWindow(GetDlgItem(MainDlgHwnd,IDC_CYLINDER),state);
	EnableWindow(GetDlgItem(MainDlgHwnd,IDC_CONE),state);

	Selected_Shape_Box = 0;
	Selected_Shape_Sphere = 0;
	Selected_Shape_Capsule = 0;
	Selected_Shape_Cylinder = 0;
	Selected_Shape_Cone = 0;
}

// *************************************************************************
// *				StartMeshViewer  Terry	Bernie						   *
// *************************************************************************
bool GD19_Mesh_Viewer::StartMeshViewer()
{
	MvEnt = NULL; 
	MvNode = NULL;
	Last_MeshFile[0] = 0;

	App->RenderBackGround = 1;
	
	DialogBox(App->hInst,(LPCTSTR)IDD_GD_MESHVIEWER,App->Fdlg,(DLGPROC)MeshViewer_Proc);

	App->Cl19_Ogre->OgreListener->GD_MeshViewer_Running = 0;
	Close_OgreWindow();

	//App->Cl19_Ogre->OgreListener->showDebugOverlay(true);
	//App->Cl19_Ogre->textArea->show();

	App->RenderBackGround = 0;
	return 1;
}

// *************************************************************************
// *						MeshViewer_Proc Terry Bernie				   *
// *************************************************************************
LRESULT CALLBACK GD19_Mesh_Viewer::MeshViewer_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
		{	
		
			App->Cl_Mesh_Viewer->MainDlgHwnd = hDlg;

			SendDlgItemMessage(hDlg,IDC_LISTFILES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_OBJECTNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_STNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_STSHAPE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg,IDC_STTYPE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDC_CB_FOLDERS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDC_STFOLDER, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDC_SELECTEDNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));


			App->Cl_Mesh_Viewer->ListHwnd = GetDlgItem(hDlg,IDC_LISTFILES);

			HWND Ogre_Hwnd = GetDlgItem(hDlg,IDC_OGREWIN); 
			App->Cl_Mesh_Viewer->MeshView_Hwnd = GetDlgItem(hDlg,IDC_OGREWIN);
			App->Cl_Mesh_Viewer->Set_OgreWindow();

			//App->Cl19_Ogre->textArea->hide();

			Ogre::Root::getSingletonPtr()->renderOneFrame();
			Ogre::Root::getSingletonPtr()->renderOneFrame();

			HWND CB_hWnd = GetDlgItem(hDlg, IDC_CB_FOLDERS);
			App->Cl_Mesh_Viewer->Get_Media_Folders_Actors(CB_hWnd); // Populate Combo

			
			App->Cl_Mesh_Viewer->SelectStartFolder();

				App->Cl_Mesh_Viewer->SelectStatic = 0;
				App->Cl_Mesh_Viewer->SelectDynamic = 0;
				App->Cl_Mesh_Viewer->SelectTriMesh = 0;
			
				App->Cl_Mesh_Viewer->Enable_ShapeButtons(0);
				App->Cl_Mesh_Viewer->Enable_TypeButtons(0);

				App->Cl_Mesh_Viewer->Physics_Type = Enums::Bullet_Type_None;

			char ConNum[256];
			char ATest[256];

			if (App->Cl_Mesh_Viewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Collectables)
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

			}

			if (App->Cl_Mesh_Viewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Area) 
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

			}

			if (App->Cl_Mesh_Viewer->Mesh_Viewer_Mode == Enums::Mesh_Viewer_Objects)
			{
				strcpy_s(ATest, "Object_");
				_itoa(App->Cl_Scene_Data->ObjectCount, ConNum, 10);
				strcat(ATest, ConNum);
				SetDlgItemText(hDlg, IDC_OBJECTNAME, ATest);
				strcpy(App->Cl_Mesh_Viewer->Object_Name, ATest);

				App->Cl_Mesh_Viewer->Enable_TypeButtons(1);
			}

			App->Cl19_Ogre->OgreListener->GD_MeshViewer_Running = 1;

			
			return TRUE;
		}
		case WM_CTLCOLORSTATIC:
		{
			if(GetDlgItem(hDlg,IDC_STNAME) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}

			if(GetDlgItem(hDlg,IDC_STSHAPE) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}

			if(GetDlgItem(hDlg,IDC_STTYPE) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
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
		case WM_HSCROLL:
		{
			/*HWND Slider =GetDlgItem(hDlg,IDC_SLIDERSPINRATE);
			int pos=0;
			pos=SendMessage(Slider, TBM_GETPOS, (WPARAM) 0,(LPARAM)0); 
			
			if (pos == 0){App->Ogre17->PhysicsFrameListener->SpinRate = 0;}
			if (pos == 1){App->Ogre17->PhysicsFrameListener->SpinRate = 0.5;}
			if (pos == 2){App->Ogre17->PhysicsFrameListener->SpinRate = 1;}
			if (pos == 3){App->Ogre17->PhysicsFrameListener->SpinRate = 1.5;}
			if (pos == 4){App->Ogre17->PhysicsFrameListener->SpinRate = 2;}
			if (pos == 5){App->Ogre17->PhysicsFrameListener->SpinRate = 4;}*/

			return 1;
		}

		case WM_NOTIFY:
		{
			LPNMHDR some_item = (LPNMHDR)lParam;
			
            /*if (some_item->idFrom == IDC_MVMISC && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->ShowMisc);
                return CDRF_DODEFAULT;
            }

			if (some_item->idFrom == IDC_MVBUILDINGS && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->ShowBuildings);
                return CDRF_DODEFAULT;
            }

			if (some_item->idFrom == IDC_MVROOMS && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->ShowRooms);
                return CDRF_DODEFAULT;
            }*/

			//// ---------------------------------------------------------------------

			if (some_item->idFrom == IDC_MVSTATIC && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->SelectStatic);
                return CDRF_DODEFAULT;
            }

			if (some_item->idFrom == IDC_DYNAMIC && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->SelectDynamic);
                return CDRF_DODEFAULT;
            }

			if (some_item->idFrom == IDC_TRIMESH && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->SelectTriMesh);
                return CDRF_DODEFAULT;
            }

			//// ---------------------------------------------------------------------
			if (some_item->idFrom == IDC_BOX && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->Selected_Shape_Box);
                return CDRF_DODEFAULT;
            }

			if (some_item->idFrom == IDC_SPHERE && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->Selected_Shape_Sphere);
                return CDRF_DODEFAULT;
            }

			if (some_item->idFrom == IDC_CAPSULE && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->Selected_Shape_Capsule);
                return CDRF_DODEFAULT;
            }

			if (some_item->idFrom == IDC_CYLINDER && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->Selected_Shape_Cylinder);
                return CDRF_DODEFAULT;
            }

			if (some_item->idFrom == IDC_CONE && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->Selected_Shape_Cone);
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

			if (LOWORD(wParam) == IDC_CB_FOLDERS)
			{
				switch (HIWORD(wParam)) // Find out what message it was
				{
				case CBN_DROPDOWN:
					break;
				case CBN_CLOSEUP:
				{
					char Get_Folder[1024];
					HWND temp = GetDlgItem(hDlg, IDC_CB_FOLDERS);
					int Index = SendMessage(temp, CB_GETCURSEL, 0, 0);
					SendMessage(temp, CB_GETLBTEXT, Index, (LPARAM)Get_Folder);

					SendMessage(App->Cl_Mesh_Viewer->ListHwnd, LB_RESETCONTENT, 0, 0);

					strcpy(App->Cl_Mesh_Viewer->Chr_CurrentFolder, App->EquityDirecory_FullPath);
					strcat(App->Cl_Mesh_Viewer->Chr_CurrentFolder, "\\Media\\Actors\\");
					strcat(App->Cl_Mesh_Viewer->Chr_CurrentFolder, Get_Folder);

					// Get Meshes in Sub Folders of Folder
					App->Cl_Mesh_Viewer->Get_Sub_Folders(Get_Folder, App->Cl_Mesh_Viewer->ListHwnd);

					// Get Meshes in the Folder
					strcat(App->Cl_Mesh_Viewer->Chr_CurrentFolder, "\\*.mesh");

					App->Cl_Mesh_Viewer->GetMeshFiles(App->Cl_Mesh_Viewer->Chr_CurrentFolder, false);

				}
				}

				return TRUE;
			}

	//		if (LOWORD(wParam) == IDC_BTUSER)
	//		{
	//			/*char Resource_Folder[1024];
	//			App->Cl_Mesh_Viewer->Clear_ButFlags();
	//			App->Cl_Mesh_Viewer->ShowMisc = 1;
	//			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	//			App->Cl_Mesh_Viewer->Clear_ButFlags();
	//			App->Cl_Mesh_Viewer->ShowMisc = 1;
	//			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	//			SendMessage(App->Cl_Mesh_Viewer->ListHwnd, LB_RESETCONTENT, 0, 0);*/
	//		
	//		//	int Count = 0;
	//	/*		while (Count < App->Cl19_Ogre->UserFile_Count)
	//			{
	//				strcpy(Resource_Folder, App->Cl19_Ogre->User_File[Count].c_str());

	//				strcpy(App->Cl_Mesh_Viewer->Chr_CurrentFolder, App->EquityDirecory_FullPath);
	//				strcat(App->Cl_Mesh_Viewer->Chr_CurrentFolder, "\\Media\\Actors\\User\\");
	//				strcat(App->Cl_Mesh_Viewer->Chr_CurrentFolder, Resource_Folder);
	//				strcat(App->Cl_Mesh_Viewer->Chr_CurrentFolder,"\\*.mesh");

	//				App->Cl_Mesh_Viewer->GetMeshFiles(App->Cl_Mesh_Viewer->Chr_CurrentFolder, false);

	//				Count++;
	//			}*/

	//			return 1;
	//		}

	//		if (LOWORD(wParam) == IDC_MVMISC) 
	//		{
	//			App->Cl_Mesh_Viewer->Clear_ButFlags();
	//			App->Cl_Mesh_Viewer->ShowMisc = 1;
	//			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	//			strcpy(App->Cl_Mesh_Viewer->Chr_CurrentFolder,App->EquityDirecory_FullPath);
	//			strcat(App->Cl_Mesh_Viewer->Chr_CurrentFolder,"\\Media\\Actors\\Misc\\*.mesh");
	//			App->Cl_Mesh_Viewer->GetMeshFiles(App->Cl_Mesh_Viewer->Chr_CurrentFolder,true);
	//			return 1;
	//		}

	//		if (LOWORD(wParam) == IDC_MVBUILDINGS) 
	//		{
	//			App->Cl_Mesh_Viewer->Clear_ButFlags();
	//			App->Cl_Mesh_Viewer->ShowBuildings = 1;
	//			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	//			strcpy(App->Cl_Mesh_Viewer->Chr_CurrentFolder,App->EquityDirecory_FullPath);
	//			strcat(App->Cl_Mesh_Viewer->Chr_CurrentFolder,"\\Media\\Actors\\Buildings\\*.mesh");
	//			App->Cl_Mesh_Viewer->GetMeshFiles(App->Cl_Mesh_Viewer->Chr_CurrentFolder,true);
	//			return 1;
	//		}

	//		if (LOWORD(wParam) == IDC_MVROOMS) 
	//		{
	//			App->Cl_Mesh_Viewer->Clear_ButFlags();
	//			App->Cl_Mesh_Viewer->ShowRooms = 1;
	//			RedrawWindow(hDlg, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);

	//			strcpy(App->Cl_Mesh_Viewer->Chr_CurrentFolder,App->EquityDirecory_FullPath);
	//			strcat(App->Cl_Mesh_Viewer->Chr_CurrentFolder,"\\Media\\Actors\\Rooms\\*.mesh");
	//			App->Cl_Mesh_Viewer->GetMeshFiles(App->Cl_Mesh_Viewer->Chr_CurrentFolder,true);
	//			return 1;
	//		}
	////		// ---------------------------------------------------------------------
			if (LOWORD(wParam) == IDC_TRIMESH) 
			{
				App->Cl_Mesh_Viewer->Physics_Type = Enums::Bullet_Type_TriMesh;
				App->Cl_Mesh_Viewer->SelectStatic = 0;
				App->Cl_Mesh_Viewer->SelectDynamic = 0;
				App->Cl_Mesh_Viewer->SelectTriMesh = 1;

				App->Cl_Mesh_Viewer->Enable_ShapeButtons(false);
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::NoShape;

				return 1;
			}

	//		if (LOWORD(wParam) == IDC_TEST)
	//		{
	//			
	//			App->Cl_Mesh_Viewer->Physics_Type = Enums::Bullet_Type_Volume;
	//			return 1;
	//		}

			if (LOWORD(wParam) == IDC_MVSTATIC) 
			{
				App->Cl_Mesh_Viewer->Physics_Type = Enums::Bullet_Type_Static;
				App->Cl_Mesh_Viewer->SelectStatic = 1;
				App->Cl_Mesh_Viewer->SelectDynamic = 0;
				App->Cl_Mesh_Viewer->SelectTriMesh = 0;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Enable_ShapeButtons(true);

				//App->GDCL_Mesh_Viewer->Start_ShapeDialog();
				return 1;
			}

			if (LOWORD(wParam) == IDC_DYNAMIC)
			{
				App->Cl_Mesh_Viewer->Physics_Type = Enums::Bullet_Type_Dynamic;
				App->Cl_Mesh_Viewer->SelectDynamic = 1;
				App->Cl_Mesh_Viewer->SelectStatic = 0;
				App->Cl_Mesh_Viewer->SelectTriMesh = 0;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Enable_ShapeButtons(true);
				//App->GDCL_Mesh_Viewer->Start_ShapeDialog();
				return 1;
			}

			// --------------------------------------------------------------------- Shape
			if (LOWORD(wParam) == IDC_BOX) 
			{
				App->Cl_Mesh_Viewer->Reset_Shape_Flags();
				App->Cl_Mesh_Viewer->Selected_Shape_Box = 1;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::Shape_Box;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_SPHERE) 
			{
				App->Cl_Mesh_Viewer->Reset_Shape_Flags();
				App->Cl_Mesh_Viewer->Selected_Shape_Sphere = 1;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::Sphere;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_CAPSULE) 
			{
				App->Cl_Mesh_Viewer->Reset_Shape_Flags();
				App->Cl_Mesh_Viewer->Selected_Shape_Capsule = 1;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::Capsule;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_CYLINDER) 
			{
				App->Cl_Mesh_Viewer->Reset_Shape_Flags();
				App->Cl_Mesh_Viewer->Selected_Shape_Cylinder = 1;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::Cylinder;
				return TRUE;
			}

			if (LOWORD(wParam) == IDC_CONE) 
			{
				App->Cl_Mesh_Viewer->Reset_Shape_Flags();
				App->Cl_Mesh_Viewer->Selected_Shape_Cone = 1;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::Cone;
				return TRUE;
			}

			// ---------------------------------------------------------------------
			if (LOWORD(wParam) == IDC_LISTFILES) 
			{
				char buff[256];
				int Index=0;
				Index = SendDlgItemMessage(hDlg,IDC_LISTFILES,LB_GETCURSEL, (WPARAM)0, (LPARAM)0);

				if (Index==-1)
				{
					return 1;
				}

				SendDlgItemMessage(hDlg,IDC_LISTFILES,LB_GETTEXT, (WPARAM)Index, (LPARAM)buff);
				SetDlgItemText(hDlg, IDC_SELECTEDNAME, buff);
				
				strcpy(App->Cl_Mesh_Viewer->Selected_MeshFile,buff);
				App->Cl_Mesh_Viewer->ShowMesh(App->Cl_Mesh_Viewer->Selected_MeshFile,1);

				/*HWND temp = GetDlgItem(hDlg,IDC_CHECKSPIN);
				SendMessage(temp,BM_SETCHECK,1,0);*/

				return TRUE;

			}

			if (LOWORD(wParam) == IDOK) 
			{
				
				if (App->Cl_Mesh_Viewer->Physics_Type == Enums::Bullet_Type_TriMesh)
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
				
				App->Cl19_Ogre->OgreListener->GD_MeshViewer_Running = 0;

				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if (LOWORD(wParam)== IDCANCEL) 
			{
				bool Test = App->Cl_Scene_Data->Is_Meshes_Used(App->Cl_Mesh_Viewer->Last_MeshFile);
				if (Test == 0)
				{
					Ogre::ResourcePtr ptr = Ogre::MeshManager::getSingleton().getByName(App->Cl_Mesh_Viewer->Last_MeshFile);
					ptr->unload();
					Ogre::MeshManager::getSingleton().remove(App->Cl_Mesh_Viewer->Last_MeshFile);	
					App->Cl_Mesh_Viewer->Last_MeshFile[0] = 0;
				}

				App->Cl19_Ogre->OgreListener->GD_MeshViewer_Running = 0;
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			break;
	}
    return FALSE;
}

// *************************************************************************
// *					SelectStartFolder Terry Bernie					   *
// *************************************************************************
void GD19_Mesh_Viewer::SelectStartFolder(void)
{
	GetMeshFiles(Chr_CurrentFolder,true);
}



// *************************************************************************
// *					ShowMesh Terry Bernie							   *
// *************************************************************************
void GD19_Mesh_Viewer::ShowMesh(char* MeshFile,bool Update)
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
		MvEnt=NULL;
		MvNode=NULL;

		if(DeleteAll == 1)
		{
			Ogre::ResourcePtr pp = Ogre::MeshManager::getSingleton().getByName(Last_MeshFile);
			
			if(pp.isNull()) // is loaded
			{
				
			}
			else
			{
				Ogre::ResourcePtr ptr = Ogre::MeshManager::getSingleton().getByName(Last_MeshFile);
				ptr->unload();
				Ogre::MeshManager::getSingleton().remove(Last_MeshFile);
			}
		}
	}

	strcpy(Last_MeshFile,MeshFile);

	MvEnt = mSceneMgrMeshView->createEntity(MeshFile);
	MvNode  = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
	MvNode->attachObject(MvEnt);
	MvNode->setPosition(0,0,0);

	Ogre::Vector3 Centre = MvEnt->getBoundingBox().getCenter();
	
	Ogre::Real Radius = MvEnt->getBoundingRadius();
	
	mCameraMeshView->setPosition(0,Centre.y,-Radius*2.5);
	mCameraMeshView->lookAt(0,Centre.y,0);

	//Flags[0]->MeshViewer_SpinObject = 1; // NEED TO CHECK FOR VALID OBJECT

//	Check_HasAnimations();
}

// *************************************************************************
// *				Set_OgreWindow Terry Bernie						   *
// *************************************************************************
bool GD19_Mesh_Viewer::Set_OgreWindow(void)
{		

	Ogre::NameValuePairList options;		

	options["externalWindowHandle"] = 
		Ogre::StringConverter::toString((size_t)MeshView_Hwnd); 

	MeshView_Window = App->Cl19_Ogre->mRoot->createRenderWindow("MeshViewWin",1024,768,false, &options);

	mSceneMgrMeshView = App->Cl19_Ogre->mRoot->createSceneManager("DefaultSceneManager","MeshViewGD");

	mCameraMeshView = mSceneMgrMeshView->createCamera("CameraMV");
	mCameraMeshView->setPosition(Ogre::Vector3(0,0,0));
	mCameraMeshView->setNearClipDistance(0.1);
	mCameraMeshView->setFarClipDistance(1000);

	Ogre::Viewport* vp = MeshView_Window->addViewport(mCameraMeshView);
	mCameraMeshView->setAspectRatio(Ogre::Real(vp->getActualWidth()) / Ogre::Real(vp->getActualHeight()));
	
	vp->setBackgroundColour(ColourValue(0.5, 0.5, 0.5));

	CamNode = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode( "Camera_Node" );
	CamNode->attachObject( mCameraMeshView );

	////-------------------------------------------- 
	MvEnt = mSceneMgrMeshView->createEntity("MVTest","well.mesh");
	MvNode  = mSceneMgrMeshView->getRootSceneNode()->createChildSceneNode();
	MvNode->attachObject(MvEnt);

	mSceneMgrMeshView->setAmbientLight(ColourValue(0.7, 0.7, 0.7));

	// add a bright light above the scene
	Light* light = mSceneMgrMeshView->createLight();
	light->setType(Light::LT_POINT);
	light->setPosition(-10, 40, 20);
	light->setSpecularColour(ColourValue::White);

	Ogre::Vector3 Centre = MvEnt->getBoundingBox().getCenter();
	Ogre::Real Radius = MvEnt->getBoundingRadius();
	
	mCameraMeshView->setPosition(0,Centre.y,-Radius*(Real(2.5)));
	mCameraMeshView->lookAt(0,Centre.y,0);

	return 1;
}

// *************************************************************************
// *				CloseMeshView (Terry Bernie)						   *
// *************************************************************************
void GD19_Mesh_Viewer::Close_OgreWindow(void)
{		
	App->Cl19_Ogre->mRoot->detachRenderTarget("MeshViewWin");
	MeshView_Window->destroy();
	App->Cl19_Ogre->mRoot->destroySceneManager(mSceneMgrMeshView);
}

// *************************************************************************
// *	  					Start_ShapeDialog Terry Bernie				   *
// *************************************************************************
void GD19_Mesh_Viewer::Start_ShapeDialog()
{
///	DialogBox(App->hInst,(LPCTSTR)IDD_PHYSICSSHAPE,MainDlgHwnd,(DLGPROC)ShapeDialog_Proc);
}

// *************************************************************************
// *					ShapeDialog_Proc Terry Bernie 					   *
// *************************************************************************
LRESULT CALLBACK GD19_Mesh_Viewer::ShapeDialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
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
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->Selected_Shape_Box);
                return CDRF_DODEFAULT;
            }

		///	if (some_item->idFrom == IDC_SPHERE && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->Selected_Shape_Sphere);
                return CDRF_DODEFAULT;
            }

	///		if (some_item->idFrom == IDC_CAPSULE && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->Selected_Shape_Capsule);
                return CDRF_DODEFAULT;
            }

	///		if (some_item->idFrom == IDC_CYLINDER && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->Selected_Shape_Cylinder);
                return CDRF_DODEFAULT;
            }

	///		if (some_item->idFrom == IDC_CONE && some_item->code == NM_CUSTOMDRAW)
            {
                LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
				App->Custom_Button_Toggle(item,App->Cl_Mesh_Viewer->Selected_Shape_Cone);
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
				App->Cl_Mesh_Viewer->Reset_Shape_Flags();
				App->Cl_Mesh_Viewer->Selected_Shape_Box = 1;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::Shape_Box;
				return TRUE;
			}

	///		if (LOWORD(wParam) == IDC_SPHERE) 
			{
				App->Cl_Mesh_Viewer->Reset_Shape_Flags();
				App->Cl_Mesh_Viewer->Selected_Shape_Sphere = 1;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::Sphere;
				return TRUE;
			}

	///		if (LOWORD(wParam) == IDC_CAPSULE) 
			{
				App->Cl_Mesh_Viewer->Reset_Shape_Flags();
				App->Cl_Mesh_Viewer->Selected_Shape_Capsule = 1;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::Capsule;
				return TRUE;
			}

	///		if (LOWORD(wParam) == IDC_CYLINDER) 
			{
				App->Cl_Mesh_Viewer->Reset_Shape_Flags();
				App->Cl_Mesh_Viewer->Selected_Shape_Cylinder = 1;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::Cylinder;
				return TRUE;
			}

	///		if (LOWORD(wParam) == IDC_CONE) 
			{
				App->Cl_Mesh_Viewer->Reset_Shape_Flags();
				App->Cl_Mesh_Viewer->Selected_Shape_Cone = 1;
				App->RedrawWindow_Dlg(hDlg);

				App->Cl_Mesh_Viewer->Physics_Shape = Enums::Cone;
				return TRUE;
			}

			//--------------------------------------

			if (LOWORD(wParam) == IDOK) 
			{
				EndDialog(hDlg, LOWORD(wParam));
				return TRUE;
			}

			if (LOWORD(wParam)== IDCANCEL) 
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
void GD19_Mesh_Viewer::Reset_Shape_Flags()
{
	Selected_Shape_Box = 0;
	Selected_Shape_Sphere = 0;
	Selected_Shape_Capsule = 0;
	Selected_Shape_Cylinder = 0;
	Selected_Shape_Cone = 0;	
}

// *************************************************************************
// *				GetMeshFiles   Terry Bernie							   *
// *************************************************************************
bool GD19_Mesh_Viewer::GetMeshFiles(char* Location, bool ResetList)
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
	ShowMesh(Selected_MeshFile, 1);

	return 1;
}

// *************************************************************************
// *					Get_Media_FoldersActors Terry Berni			 	   *
// *************************************************************************
bool GD19_Mesh_Viewer::Get_Media_Folders_Actors(HWND DropHwnd)
{
	char Path[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(Path, App->EquityDirecory_FullPath);
	strcat(Path, "\\Media\\Actors\\*.*");

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
// *						Get_Sub_Folders Terry Berni				 	   *
// *************************************************************************
bool GD19_Mesh_Viewer::Get_Sub_Folders(char* Folder,HWND DropHwnd)
{
	char Path[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(Path, App->EquityDirecory_FullPath);
	strcat(Path, "\\Media\\Actors\\");
	strcat(Path, Folder);
	strcat(Path, "\\*.*");

	char Mesh_Path[1024];
	strcpy(Mesh_Path, App->EquityDirecory_FullPath);
	strcat(Mesh_Path, "\\Media\\Actors\\");
	strcat(Mesh_Path, Folder);
	strcat(Mesh_Path,"\\");

	hFind = FindFirstFile(Path, &FindFileData);

	//SendMessage(ListHwnd, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)FindFileData.cFileName);

	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
			{
				if (strcmp(FindFileData.cFileName, ".") == 0 || strcmp(FindFileData.cFileName, "..") == 0)
				{

				}
				else
				{
					char New_Path[1024];
					strcpy(New_Path, Mesh_Path);
					strcat(New_Path, FindFileData.cFileName);
					strcat(New_Path, "\\*.mesh");

					App->Cl_Mesh_Viewer->GetMeshFiles(New_Path, false);
					
				}

			}
		} while (FindNextFile(hFind, &FindFileData));
		FindClose(hFind);
	}

	return 0;
}