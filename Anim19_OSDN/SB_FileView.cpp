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
#include "SB_FileView.h"


SB_FileView::SB_FileView()
{
	Root = nullptr;
	GD_ProjectFolder = nullptr;
	GD_ObjectsFolder = nullptr;
	GD_LevelFolder = nullptr;
	GD_CameraFolder = nullptr;
	GD_TriggerFolder = nullptr;
	GD_EntitiesFolder = nullptr;
	GD_Entities_Sound_Folder = nullptr;
	GD_Entities_Message_Folder = nullptr;
	GD_Entities_Move_Folder = nullptr;
	GD_Collectables_Folder = nullptr;
	GD_Teleporters_Folder = nullptr;
	GD_Environment_Folder = nullptr;
	GD_Area_Change_Folder = nullptr;
	GD_Level_Change_Folder = nullptr;
	GD_Particles_Folder = nullptr;

	GD_Player = nullptr;
	GD_Rooms = nullptr;

	hImageList = nullptr;
	hBitMap = nullptr;
}


SB_FileView::~SB_FileView()
{
}

// *************************************************************************
//							Start_FileView Terry Flanigan					*
// *************************************************************************
void SB_FileView::Start_FileView(void)
{
	App->ListPanel = CreateDialog(App->hInst, (LPCTSTR)IDD_LIST, App->MainHwnd, (DLGPROC)ListPanel_Proc);
}

// *************************************************************************
// *					ListPanel_Proc_Proc Terry Flanigan				   *
// *************************************************************************
LRESULT CALLBACK SB_FileView::ListPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
	{
		App->Cl_FileView->FileView_Active = 1;
		ShowWindow(hDlg, 1);

		SendDlgItemMessage(hDlg, IDC_TREE1, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_CHECKED);
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->DialogBackGround;
	}

	case WM_SIZE:
	{
		App->Cl_Panels->Resize_FileView();
	}break;

	case WM_NOTIFY:
	{
		LPNMHDR nmhdr = (LPNMHDR)lParam;
		if (nmhdr->idFrom == IDC_TREE1)
		{
			switch (nmhdr->code)
			{

			case TVN_SELCHANGED:
			{
				App->SBC_FileView->Get_Selection((LPNMHDR)lParam);
			}
			}
		}

		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_ENVIONMENT && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_LEVELS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_FileView->Level_But_Active);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_STOCK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->Cl_FileView->Stock_But_Active);
			return CDRF_DODEFAULT;
		}

		return 1;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_LEVELS)
		{
			App->Cl_FileView->Level_But_Active = 1;
			App->Cl_FileView->Stock_But_Active = 0;
			App->RedrawWindow_Dlg(hDlg);

			ShowWindow(GetDlgItem(App->ListPanel, IDC_TREE1), 1);

			//App->GDCL_FileView->HideRightPanes();
			//ShowWindow(App->GD_Properties_Hwnd, 1);*/

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_STOCK)
		{
			/*App->Cl_FileView->HideRightPanes();
			ShowWindow(App->GD_Stock_Hwnd, 1);*/
			App->Cl_Stock->Start_Stock_Dialog();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ENVIONMENT)
		{
			App->Cl_Environment->Start_Environment();
			return TRUE;
		}
		break;
	}

	case WM_CLOSE:
	{
		App->Cl_FileView->FileView_Active = 0;
		ShowWindow(App->ListPanel, 0);

		HMENU mMenu = GetMenu(App->MainHwnd);
		CheckMenuItem(mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_UNCHECKED);

		break;
	}

	break;
	}
	return FALSE;
}

// *************************************************************************
// *						Init_FileView Terry Flanigan				   *
// *************************************************************************
void SB_FileView::Init_FileView(void)
{
	InitCommonControls();	    // make our tree control to work

								////====================================================//
	hImageList = ImageList_Create(16, 16, FALSE, 6, 0); // Zero Index

														//--------- Grayed Folder Closed Open 0 1
	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_FILEINACTIVE));
	ImageList_Add(hImageList, hBitMap, NULL);
	DeleteObject(hBitMap);

	//--------- Green Folder Closed Open 2 3
	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_TREE));
	ImageList_Add(hImageList, hBitMap, NULL);
	DeleteObject(hBitMap);

	//--------- Uselected File Open 4
	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_FILE));
	ImageList_Add(hImageList, hBitMap, (HBITMAP)NULL);
	DeleteObject(hBitMap);

	//--------- Selected File Open 5
	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_FILESELECTED));
	ImageList_Add(hImageList, App->Cl_FileView->hBitMap, (HBITMAP)NULL);
	DeleteObject(hBitMap);

	SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETIMAGELIST, 0, (LPARAM)hImageList);

	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	TreeView_DeleteAllItems(Temp);


	TreeView_SetBkColor(Temp, (COLORREF)RGB(255, 255, 255));

	AddRootFolder();
	MoreFoldersD(); //  Folders under root 
	ExpandRoot();
}

// *************************************************************************
// *			AddRootFolder Terry Bernie			 				 	   *
// *************************************************************************
void SB_FileView::AddRootFolder(void)
{
	tvinsert.hParent = Root;			// top most level no need handle
	tvinsert.hInsertAfter = TVI_LAST; // work as root level
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Test Project rr";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	GD_ProjectFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}

// *************************************************************************
// *						MoreFoldersD Terry Bernie 				 	   *
// *************************************************************************
void SB_FileView::MoreFoldersD(void) // last folder level
{
	//------------------------------------------------------- Mesh
	tvinsert.hParent = GD_ProjectFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "LevelName";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_LevelFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	////------------------------------------------------------- Camera
	tvinsert.hParent = GD_LevelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Camera";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_CameraFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = GD_LevelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Player";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_Player = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = GD_LevelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Area";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_Rooms = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	tvinsert.hParent = GD_LevelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Objects";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_ObjectsFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = GD_LevelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Entities";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_EntitiesFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = GD_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Sounds";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_Entities_Sound_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = GD_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Messages";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_Entities_Message_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = GD_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Move_Entities";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_Entities_Move_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = GD_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Collectables";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_Collectables_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	//----------------------------------------------------
	tvinsert.hParent = GD_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Teleporters";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_Teleporters_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	//----------------------------------------------------
	tvinsert.hParent = GD_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Particles";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_Particles_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

}

// *************************************************************************
// *					ExpandRoot Terry Bernie							   *
// *************************************************************************
void SB_FileView::ExpandRoot(void)
{
	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	HTREEITEM i = TreeView_GetSelection(Temp);

	TreeView_Expand(Temp, GD_ProjectFolder, TVE_EXPAND);
	TreeView_Expand(Temp, GD_LevelFolder, TVE_EXPAND);
	TreeView_Expand(Temp, GD_EntitiesFolder, TVE_EXPAND);
}

// *************************************************************************
// *					Get_Selection Terry Bernie					 	   *
// *************************************************************************
void SB_FileView::Get_Selection(LPNMHDR lParam)
{

	strcpy(FileView_Folder, "");
	strcpy(FileView_File, "");

	int Index = 0;
	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	HTREEITEM i = TreeView_GetSelection(Temp);

	TVITEM item;
	item.hItem = i;
	item.pszText = FileView_Folder;
	item.cchTextMax = sizeof(FileView_Folder);
	item.mask = TVIF_TEXT | TVIF_PARAM;
	TreeView_GetItem(((LPNMHDR)lParam)->hwndFrom, &item);
	Index = item.lParam;

	HTREEITEM p = TreeView_GetParent(Temp, i);

	TVITEM item1;
	item1.hItem = p;
	item1.pszText = FileView_File;
	item1.cchTextMax = sizeof(FileView_File);
	item1.mask = TVIF_TEXT;
	TreeView_GetItem(((LPNMHDR)lParam)->hwndFrom, &item1);

	///App->Cl_Properties->Enable_Test_Button(0);
	///App->Cl_Properties->Enable_Delete_Button(0);

	//--------------------------------------------------------------------------

	if (!strcmp(FileView_Folder, "Area")) // Folder
	{

		App->Cl_Dialogs->YesNo("Add Object", "Do you want to add a new Area/Building now");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->Cl_Mesh_Viewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Area; // 0; // Objects
			App->Cl_Mesh_Viewer->StartMeshViewer();
			App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected
		}
		else
		{

		}

		return;
	}

	if (!strcmp(FileView_File, "Area"))
	{
		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;

		App->Cl_Properties->Edit_Category = Enums::Edit_Mesh_Object;
		App->Cl_Properties->Current_Selected_Object = Index;
		App->Cl_Properties->Update_Transform_Dlg();

		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Objects();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(Index);

		return;

	}

	if (!strcmp(FileView_Folder, "Objects")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");

			return;
		}

		App->Cl_Dialogs->YesNo("Add Object", "Do you want to add a new Object now");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->Cl_Mesh_Viewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Objects; // 0; // Objects; // Objects
			App->Cl_Mesh_Viewer->StartMeshViewer();
			App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected
		}

		return;
	}
	if (!strcmp(FileView_File, "Objects"))
	{
		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);
		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;

		App->Cl_Properties->Edit_Category = Enums::Edit_Mesh_Object;
		App->Cl_Properties->Current_Selected_Object = Index;
		App->Cl_Properties->Update_Transform_Dlg();


		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Objects();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(Index);

		return;
	}

	if (!strcmp(FileView_File, "Player"))
	{
		App->Cl_Object_Props->Is_Player = 1; // Mark as Player selected

		App->Cl_Properties->Enable_Delete_Button(0);

		App->Cl_Properties->Edit_Category = Enums::Edit_Player;
		App->Cl_Properties->Current_Selected_Object = Index;
		//App->CL10_Properties->Update_Transform_Dlg();

		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->SBC_Properties->Update_ListView_Player();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Player_Physics();
		}
		return;
	}


	if (!strcmp(FileView_Folder, "Sounds")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");

			return;
		}

		App->Cl_Dialogs->YesNo("Add Entity", "Do you want to add a new Sound Entity now");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->Cl_Objects_New->Add_New_SoundEntity();
		}

		return;
	}
	if (!strcmp(FileView_File, "Sounds"))
	{
		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Properties->Is_Player = 0;
		App->Cl_Properties->Edit_Category = Enums::Edit_Sounds;
		App->Cl_Properties->Current_Selected_Object = Index;
		App->Cl_Properties->Update_Transform_Dlg();


		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Sounds();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(Index);

		return;
	}

	// Messages
	if (!strcmp(FileView_Folder, "Messages")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");

			return;
		}

		App->Cl_Dialogs->YesNo("Add Entity", "Do you want to add a new Message Entity now");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->Cl_Objects_New->Add_New_MessageEntity();
		}

		return;
	}

	if (!strcmp(FileView_File, "Messages"))
	{
		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Edit_Type = Enums::Edit_Message;

		App->Cl_Properties->Is_Player = 0; // Mark as Object selected
		App->Cl_Properties->Edit_Category = Enums::Edit_Message;
		App->Cl_Properties->Current_Selected_Object = Index;
		App->Cl_Properties->Update_Transform_Dlg();



		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Messages();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(Index);

		return;
	}

	// Move Entities
	if (!strcmp(FileView_Folder, "Move_Entities")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added First");

			return;
		}

		App->Cl_Dialogs->YesNo("Add Entity", "Do you want to add a new Move Entity now");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->Cl_Objects_New->Add_New_MoveEntity();
		}

		return;
	}
	if (!strcmp(FileView_File, "Move_Entities"))
	{
		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Edit_Type = Enums::Edit_Move_Entity;
		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Properties->Enable_Test_Button(1);
		App->Cl_Properties->Is_Player = 0; // Mark as Object selected

		App->Cl_Properties->Edit_Category = Enums::Edit_Move_Entity;
		App->Cl_Properties->Current_Selected_Object = Index;
		App->Cl_Properties->Update_Transform_Dlg();


		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Move_Entities();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(Index);

		return;
	}

	// *************************************************************************
	// *				Collectables	Terry Bernie 					 	   *
	// *************************************************************************
	if (!strcmp(FileView_Folder, "Collectables")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");

			return;
		}

		App->Cl_Dialogs->YesNo("Add Entity", "Do you want to add a new Collectable Entity now");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->Cl_Mesh_Viewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Collectables;; // Collectables
			App->Cl_Mesh_Viewer->StartMeshViewer();
			App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected
												 //App->Cl__Add_NewObject->Add_Collectable_Entity();
		}

		return;
	}
	if (!strcmp(FileView_File, "Collectables"))
	{
		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Selected_Object_Index = Index;
		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->Cl_Properties->Edit_Category = Enums::Edit_Collectable;
		App->Cl_Properties->Current_Selected_Object = Index;
		App->Cl_Properties->Update_Transform_Dlg();


		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Collectables();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Player)
		{
			App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;
			App->Cl_Object_Props->Update_Properties_Mesh();
			return;
		}

		if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Mesh_Object)
		{
			App->Cl_Object_Props->Update_Properties_Mesh();
			return;
		}

		if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Physics_Object)
		{
			App->Cl_Object_Props->Update_Properties_Physics();
			return;
		}
		return;
	}

	// *************************************************************************
	// *				"Teleporters	Terry Bernie 					 	   *
	// *************************************************************************
	if (!strcmp(FileView_Folder, "Teleporters")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");

			return;
		}

		App->Cl_Dialogs->YesNo("Add Entity", "Do you want to add a new Telport Entity now");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->Cl_Objects_New->Add_New_TeleportEntity();
		}

		return;
	}
	if (!strcmp(FileView_File, "Teleporters"))
	{
		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Selected_Object_Index = Index;
		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->Cl_Properties->Edit_Category = Enums::Edit_Teleport;
		App->Cl_Properties->Current_Selected_Object = Index;
		App->Cl_Properties->Update_Transform_Dlg();


		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Teleport();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Player)
		{
			App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;
			App->Cl_Object_Props->Update_Properties_Mesh();
			return;
		}

		if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Mesh_Object)
		{
			App->Cl_Object_Props->Update_Properties_Mesh();
			return;
		}

		if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Physics_Object)
		{
			App->Cl_Object_Props->Update_Properties_Physics();
			return;
		}
		return;
	}


	// *************************************************************************
	// *					Particles	Terry Bernie 					 	   *
	// *************************************************************************
	if (!strcmp(FileView_Folder, "Particles")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");
			return;
		}


		App->Cl_Dialogs->YesNo("Add Entity", "Do you want to add a new Particle Entity now");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->Cl_Objects_New->Add_New_Particle();
		}

		return;
	}
	if (!strcmp(FileView_File, "Particles"))
	{

		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Selected_Object_Index = Index;
		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->Cl_Properties->Edit_Category = Enums::Edit_Particles;
		App->Cl_Properties->Current_Selected_Object = Index;

		App->Cl_Properties->Update_Transform_Dlg();



		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Particles();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		return;
	}
	// *************************************************************************
	// *				"Environment	Terry Bernie 					 	   *
	// *************************************************************************
	if (!strcmp(FileView_Folder, "Environment")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");
			return;
		}


		//App->CL_Dialogs->YesNo("Add Entity", "Do you want to add a new Environment Entity now");
		App->Cl_Dialogs->YesNo("Add Entity", "Not Available Yet Next Release");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			//App->CL10_Objects_New->Add_New_EnvironmentEntity();
		}

		return;
	}
	if (!strcmp(FileView_File, "Environment"))
	{

		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Selected_Object_Index = Index;
		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->Cl_Properties->Edit_Category = Enums::Edit_Environment;
		App->Cl_Properties->Current_Selected_Object = Index;

		App->Cl_Properties->Update_Transform_Dlg();


		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Environment();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		return;
	}

	// *************************************************************************
	// *				Area_Change Terry Bernie 						 	   *
	// *************************************************************************
	if (!strcmp(FileView_Folder, "Area_Change")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");
			return;
		}

		//App->CL_Dialogs->YesNo("Add Entity", "Do you want to add a new Area Change Entity now");
		App->Cl_Dialogs->YesNo("Add Entity", "Not Available Yet Next Release");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			//App->CL10_Objects_New->Add_New_Area_Change();
		}

		return;
	}
	if (!strcmp(FileView_File, "Area_Change"))
	{

		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Selected_Object_Index = Index;
		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->Cl_Properties->Edit_Category = Enums::Edit_Area_Change;
		App->Cl_Properties->Current_Selected_Object = Index;

		App->Cl_Properties->Update_Transform_Dlg();


		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Environment();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		return;
	}


	// *************************************************************************
	// *				Change_Level Terry Bernie 						 	   *
	// *************************************************************************
	if (!strcmp(FileView_Folder, "Change_Level")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");
			return;
		}


		//App->CL_Dialogs->YesNo("Add Entity", "Do you want to add a new Change Level Entity now");
		App->Cl_Dialogs->YesNo("Add Entity", "Not Available Yet Next Release");
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			//App->CL10_Objects_New->Add_New_Change_Level();
		}

		return;
	}
	if (!strcmp(FileView_File, "Change_Level"))
	{

		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->Cl_Properties->Enable_Delete_Button(1);

		App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		App->Cl_Object_Props->Selected_Object_Index = Index;
		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->Cl_Properties->Edit_Category = Enums::Edit_Change_Level;
		App->Cl_Properties->Current_Selected_Object = Index;

		App->Cl_Properties->Update_Transform_Dlg();


		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Environment();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		return;
	}

}

// *************************************************************************
// *					HideRightPanes Terry Bernie 					   *
// *************************************************************************
void SB_FileView::HideRightPanes(void)
{
	if (App->Cl_Scene_Data->SceneLoaded == 1)
	{
		ShowWindow(App->GD_Properties_Hwnd, 0);
		///	ShowWindow(App->GD_Stock_Hwnd, 0);
	}
}

// *************************************************************************
// *					Add_PlayeFile Terry Bernie					 	   *
// *************************************************************************
HTREEITEM SB_FileView::Add_PlayerFile(char *SFileName, int Index)
{
	HWND Temp2 = GetDlgItem(App->ListPanel, IDC_TREE1);

	tvinsert.hParent = GD_Player;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvinsert.item.pszText = SFileName;
	tvinsert.item.iImage = 4;
	tvinsert.item.iSelectedImage = 5;
	tvinsert.item.lParam = Index;
	HTREEITEM Temp = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	//TreeView_Select(Temp2,Temp,TVGN_CARET);

	return Temp;
}