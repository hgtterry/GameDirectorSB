/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "AB_App.h"
#include "SB_FileView.h"

SB_FileView::SB_FileView(void)
{
	hImageList = nullptr;
	hBitMap = nullptr;

	Root = nullptr;
	GD_ProjectFolder =	nullptr;
	FV_Players_Folder = nullptr;	// Players Folder FileFView
	FV_Areas_Folder =	nullptr;	// Areas/Rooms Folder FileFView
	FV_LevelFolder =	nullptr;
	FV_Cameras_Folder = nullptr;
	FV_Objects_Folder = nullptr;
	FV_EntitiesFolder = nullptr;
	FV_Evirons_Folder = nullptr;

	FileView_Folder[0] = 0;
	FileView_File[0] = 0;
}

SB_FileView::~SB_FileView(void)
{
}

// **************************************************************************
// *			Start_FileView:- Terry and Hazel Flanigan 2022				*
// **************************************************************************
void SB_FileView::Start_FileView(void)
{
	App->ListPanel = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_LIST, App->Equity_Dlg_hWnd, (DLGPROC)ListPanel_Proc);
	//Init_Bmps_FileView();
	Init_FileView();
}

// *************************************************************************
// *		ListPanel_Proc_Proc:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
LRESULT CALLBACK SB_FileView::ListPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
	{
		//App->SBC_FileView->FileView_Active = 1;
		SendDlgItemMessage(hDlg, IDC_TREE1, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		//CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_CHECKED);
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_SIZE:
	{
		//App->SBC_Panels->Resize_FileView();
	}break;

	case WM_CONTEXTMENU:
	{
		//App->SBC_FileView->Context_Menu(hDlg);

		break;
	}

	case WM_NOTIFY:
	{
		LPNMHDR nmhdr = (LPNMHDR)lParam;
		if (nmhdr->idFrom == IDC_TREE1)
		{
			switch (nmhdr->code)
			{

			case TVN_SELCHANGED:
			{
				App->CLSB_FileView->Get_Selection((LPNMHDR)lParam);
			}

			}
		}

		/*LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_LEVELS && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_FileView->Level_But_Active);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_STOCK && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_FileView->Stock_But_Active);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_INFO_FILEVIEW && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return 1;
	}
	case WM_COMMAND:
	{
		/*if (LOWORD(wParam) == IDM_GOTO)
		{
			App->SBC_FileView->Context_Goto(hDlg);
			return TRUE;
		}

		if (LOWORD(wParam) == IDM_COPY)
		{
			App->SBC_FileView->Context_Copy(hDlg);
			return TRUE;
		}

		if (LOWORD(wParam) == IDM_FILE_DELETE)
		{
			App->SBC_FileView->Context_Delete(hDlg);

			return TRUE;
		}

		if (LOWORD(wParam) == IDM_FILE_NEW)
		{
			App->SBC_FileView->Context_New(hDlg);
			return TRUE;
		}

		if (LOWORD(wParam) == IDM_FILE_RENAME)
		{
			App->SBC_FileView->Context_Rename(hDlg);
			return TRUE;
		}*/

		//if (LOWORD(wParam) == IDC_LEVELS)
		//{
		//	//App->SBC_FileView->Level_But_Active = 1;
		//	//App->SBC_FileView->Stock_But_Active = 0;
		//	//App->RedrawWindow_Dlg(hDlg);

		//	//ShowWindow(GetDlgItem(App->ListPanel, IDC_TREE1), 1);

		//	//App->GDCL_FileView->HideRightPanes();
		//	//ShowWindow(App->GD_Properties_Hwnd, 1);*/

		//	return TRUE;
		//}

		//if (LOWORD(wParam) == IDC_STOCK)
		//{
		//	if (App->SBC_Scene->Scene_Loaded == 1)
		//	{
		//		/*App->Cl_FileView->HideRightPanes();
		//		ShowWindow(App->GD_Stock_Hwnd, 1);*/
		//		//App->Cl_Stock->Start_Stock_Dialog();
		//	}
		//	return TRUE;
		//}

		//if (LOWORD(wParam) == IDC_BT_INFO_FILEVIEW)
		//{
		//	App->Cl_Utilities->OpenHTML("Help\\FileView.html");
		//	return TRUE;
		//}

		if (LOWORD(wParam) == IDC_BT_ENVIRONMENT)
		{
			Debug
			return TRUE;
		}

		
		break;
	}

	case WM_CLOSE:
	{
		/*App->SBC_FileView->FileView_Active = 0;
		ShowWindow(App->ListPanel, 0);

		CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_UNCHECKED);*/

		return TRUE;
	}

	break;
	}
	return FALSE;
}

// *************************************************************************
// *			Init_FileView:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_FileView::Init_FileView(void)
{
	InitCommonControls();	    // make our tree control to work

	////====================================================//
	hImageList = ImageList_Create(16, 16, FALSE, 8, 0); // Zero Index

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
	ImageList_Add(hImageList, hBitMap, (HBITMAP)NULL);
	DeleteObject(hBitMap);

	//--------- File changed Open 6
	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_FILECHANGED));
	ImageList_Add(hImageList, hBitMap, (HBITMAP)NULL);
	DeleteObject(hBitMap);

	//--------- File changed Selected Open 7
	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_FILECHANGEDSELECTED));
	ImageList_Add(hImageList, hBitMap, (HBITMAP)NULL);
	DeleteObject(hBitMap);

	//--------- File changed Selected Open 8 and 9
	hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_FVFOLDERRED));
	ImageList_Add(hImageList, hBitMap, (HBITMAP)NULL);
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
// *			ExpandRoot:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_FileView::ExpandRoot(void)
{
	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	HTREEITEM i = TreeView_GetSelection(Temp);

	TreeView_Expand(Temp, GD_ProjectFolder, TVE_EXPAND);
	TreeView_Expand(Temp, FV_LevelFolder, TVE_EXPAND);
	TreeView_Expand(Temp, FV_Players_Folder, TVE_EXPAND);
}

// *************************************************************************
// *			AddRootFolder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_FileView::AddRootFolder(void)
{
	tvinsert.hParent = Root;			// top most level no need handle
	tvinsert.hInsertAfter = TVI_LAST; // work as root level
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Project";// App->SBC_Project->m_Project_Name;
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	GD_ProjectFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}

// *************************************************************************
// *			MoreFoldersD:- Terry and Hazel Flanigan 2022 		 	   *
// *************************************************************************
void SB_FileView::MoreFoldersD(void) // last folder level
{
	//------------------------------------------------------- Level 
	tvinsert.hParent = GD_ProjectFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Level"; // App->SBC_Project->m_Level_Name;
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_LevelFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	////------------------------------------------------------- Camera
	tvinsert.hParent = FV_LevelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Camera";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_Cameras_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = FV_LevelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Player";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_Players_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = FV_LevelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Area";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_Areas_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = FV_LevelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Objects";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_Objects_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = FV_LevelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Entities";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_EntitiesFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	//--------------------------------------- Evironments Eviron_Entity
	tvinsert.hParent = FV_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Evironments";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_Evirons_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}

// *************************************************************************
// *		Get_Selection Terry:- Terry and Hazel Flanigan 2022		 	   *
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


	//--------------------------------------------------------------------------

	//if (!strcmp(FileView_Folder, App->SBC_Project->m_Level_Name)) // Level Folder
	//{
	//	HideRightPanes();
	//	ShowWindow(App->GD_Properties_Hwnd, 1);

	//	App->SBC_Properties->Edit_Category = Enums::FV_Edit_Level;
	//	App->SBC_Properties->Update_ListView_Level();
	//}

	// ------------------------------------------------------------ Areas
	if (!strcmp(FileView_Folder, "Area")) // Folder
	{
		//App->SBC_FileView->Context_Selection = Enums::FileView_Areas_Folder;

		return;
	}

	if (!strcmp(FileView_File, "Area"))
	{
		//App->SBC_FileView->Context_Selection = Enums::FileView_Areas_File;
		//App->SBC_Properties->Edit_Category = Enums::Edit_Area;
		//App->SBC_Properties->Current_Selected_Object = Index;

		//HideRightPanes();
		//ShowWindow(App->GD_Properties_Hwnd, 1);

		//App->SBC_Props_Dialog->Hide_Area_Dlg(1);
		//App->SBC_Props_Dialog->Hide_Debug_Dlg(1);
		//App->SBC_Props_Dialog->Hide_Dimensions_Dlg(1, 1);
		//App->SBC_Props_Dialog->Hide_Details_Goto_Dlg(1);
		//App->SBC_Props_Dialog->Hide_Material_Dlg(1);

		////----------------------------------------------------------------------------
		////App->SBC_Properties->Current_Selected_Object = Index;
		////App->SBC_Properties->Reset_Last_Selected_Object(App->SBC_Properties->Last_Selected_Object);
		////App->SBC_Properties->Last_Selected_Object = Index;
		////----------------------------------------------------------------------------

		//App->SBC_Properties->Update_ListView_Area();


		//if (App->SBC_Dimensions->Show_Dimensions == 1)
		//{
		//	App->SBC_Dimensions->Prepare_Dimensions();
		//}

		return;

	}

	// ------------------------------------------------------------ Objects
	if (!strcmp(FileView_Folder, "Objects")) // Folder
	{
		//App->SBC_FileView->Context_Selection = Enums::FileView_Objects_Folder;
		return;
	}
	if (!strcmp(FileView_File, "Objects"))
	{
		//App->SBC_FileView->Context_Selection = Enums::FileView_Objects_File;

		/*HideRightPanes();
		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 1);

		App->SBC_Props_Dialog->Hide_Details_Goto_Dlg(1);
		App->SBC_Props_Dialog->Hide_Dimensions_Dlg(1, App->SBC_Scene->V_Object[Index]->Dimensions_Locked);
		App->SBC_Props_Dialog->Hide_Debug_Dlg(1);
		App->SBC_Props_Dialog->Hide_Material_Dlg(1);*/


		App->CLSB_Properties->Edit_Category = Enums::FV_Edit_Object;

		//----------------------------------------------------------------------------
		App->CLSB_Properties->Current_Selected_Object = Index;
		//App->SBC_Properties->Reset_Last_Selected_Object(App->SBC_Properties->Last_Selected_Object);
		//App->SBC_Properties->Last_Selected_Object = Index;
		//----------------------------------------------------------------------------

		//App->SBC_LookUps->Update_Types();

		//App->SBC_Markers->MarkerBB_Addjust(Index);

		App->CLSB_Properties->Update_ListView_Objects();


		/*if (App->SBC_Dimensions->Show_Dimensions == 1)
		{
			App->SBC_Dimensions->Prepare_Dimensions();
		}*/

		return;
	}

	// ------------------------------------------------------------ Players
	if (!strcmp(FileView_Folder, "Player")) // Folder
	{
	//	App->SBC_FileView->Context_Selection = Enums::FileView_Player_Folder;
	//	return;
	}
	if (!strcmp(FileView_File, "Player"))
	{
	//	App->SBC_FileView->Context_Selection = Enums::FileView_Player_File;

	//	HideRightPanes();
		ShowWindow(App->CLSB_Properties->Properties_Dlg_hWnd, 1);
	//	App->SBC_Player->Hide_Player_Dlg(1);

		App->CLSB_Properties->Edit_Category = Enums::Edit_Player;

	//	//----------------------------------------------------------------------------
		App->CLSB_Properties->Current_Selected_Object = Index;
	//	App->SBC_Properties->Reset_Last_Selected_Object(App->SBC_Properties->Last_Selected_Object);
	//	App->SBC_Properties->Last_Selected_Object = Index;
	//	//----------------------------------------------------------------------------

	//	if (App->SBC_Properties->Edit_Physics == 0)
	//	{
			App->CLSB_Properties->Update_ListView_Player();
	//	}
	//	else
	//	{
	//		App->SBC_Properties->Update_ListView_Player_Physics();
	//	}
		return;
	}

	// ------------------------------------------------------------ Cameras
	/*if (!strcmp(FileView_Folder, "Camera"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Cameras_Folder;

		return;
	}

	if (!strcmp(FileView_File, "Camera"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Cameras_File;

		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 0);
		App->SBC_Com_Camera->Hide_Cam_Dlg(1);

		App->SBC_Properties->Edit_Category = Enums::Edit_Camera;

		App->SBC_Properties->Current_Selected_Object = Index;

		App->SBC_Properties->Update_ListView_Camera();

		return;
	}*/

}

// *************************************************************************
// *				Add_Item:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
HTREEITEM SB_FileView::Add_Item(HTREEITEM Folder, char* SFileName, int Index, bool NewItem)
{
	HWND Temp2 = GetDlgItem(App->ListPanel, IDC_TREE1);

	tvinsert.hParent = Folder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvinsert.item.pszText = SFileName;

	if (NewItem == 1)
	{
		tvinsert.item.iImage = 6;
		tvinsert.item.iSelectedImage = 7;
		tvinsert.item.lParam = Index;
	}
	else
	{
		tvinsert.item.iImage = 4;
		tvinsert.item.iSelectedImage = 5;
		tvinsert.item.lParam = Index;
	}

	HTREEITEM Temp = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	return Temp;
}

// *************************************************************************
// *			Set_FolderActive:- Terry and Hazel Flanigan 2022	 	   *
// *************************************************************************
void SB_FileView::Set_FolderActive(HTREEITEM Folder)
{
	TVITEM Sitem;

	Sitem.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	Sitem.hItem = Folder;
	Sitem.iImage = 3;
	Sitem.iSelectedImage = 3;

	SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETITEM, 0, (LPARAM)(const LPTVITEM)&Sitem);
}

// *************************************************************************
// *				SelectItem:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_FileView::SelectItem(HTREEITEM TreeItem)
{

	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);

	//if (Flags[0]->FileView_SceneLoaded == 1)
	{
		//TreeView_Select(Temp, NULL, TVGN_CARET);
		TreeView_Select(Temp, TreeItem, TVGN_CARET);
	}
}

// *************************************************************************
// *			Mark_Altered:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_FileView::Mark_Altered(HTREEITEM Item)
{
	TVITEM Sitem;
	Sitem.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	Sitem.hItem = Item;
	Sitem.iImage = 6;
	Sitem.iSelectedImage = 7;
	SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETITEM, 0, (LPARAM)(const LPTVITEM)&Sitem);

	//EnableMenuItem(App->mMenu, ID_FILE_SAVEPROJECTALL, MF_ENABLED);
}
