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
#include "SB_FileView.h"

#define IDM_FILE_NEW 1
#define IDM_FILE_DELETE 2
#define IDM_FILE_RENAME 3
#define IDM_COPY 4
#define IDM_PASTE 5

SB_FileView::SB_FileView()
{
	Root = nullptr;
	GD_ProjectFolder = nullptr;
	FV_Objects_Folder = nullptr;
	FV_LevelFolder = nullptr;
	FV_Cameras_Folder = nullptr;
	GD_TriggerFolder = nullptr;
	GD_EntitiesFolder = nullptr;
	FV_Sounds_Folder = nullptr;
	FV_Messages_Folder = nullptr;
	FV_Move_Folder = nullptr;
	GD_Collectables_Folder = nullptr;
	FV_Teleporters_Folder = nullptr;
	GD_Environment_Folder = nullptr;
	GD_Area_Change_Folder = nullptr;
	GD_Level_Change_Folder = nullptr;
	GD_Particles_Folder = nullptr;

	FV_Players_Folder = nullptr;
	FV_Areas_Folder = nullptr;

	hImageList = nullptr;
	hBitMap = nullptr;

	Level_But_Active = 1;
	Stock_But_Active = 0;

	FileView_Pined = 0;

	Context_Selection = Enums::FileView_None;

	FileView_Active = 0;
}


SB_FileView::~SB_FileView()
{
}

// *************************************************************************
// *			Reset_Class:- Terry and Hazel Flanigan 2022			 	   *
// *************************************************************************
void SB_FileView::Reset_Class()
{
	TreeView_DeleteAllItems(GetDlgItem(App->ListPanel, IDC_TREE1));

	Root = nullptr;
	GD_ProjectFolder = nullptr;
	FV_Objects_Folder = nullptr;
	FV_LevelFolder = nullptr;
	FV_Cameras_Folder = nullptr;
	GD_TriggerFolder = nullptr;
	GD_EntitiesFolder = nullptr;
	FV_Sounds_Folder = nullptr;
	FV_Messages_Folder = nullptr;
	FV_Move_Folder = nullptr;
	GD_Collectables_Folder = nullptr;
	FV_Teleporters_Folder = nullptr;
	GD_Environment_Folder = nullptr;
	GD_Area_Change_Folder = nullptr;
	GD_Level_Change_Folder = nullptr;
	GD_Particles_Folder = nullptr;

	FV_Players_Folder = nullptr;
	FV_Areas_Folder = nullptr;

	strcpy(App->SBC_Project->m_Level_File_Name, "No Level");

	AddRootFolder();
	MoreFoldersD(); //  Folders under root 
	ExpandRoot();
}


// *************************************************************************
// *			Init_Bmps_FileView:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_FileView::Init_Bmps_FileView()
{

	HWND Temp = GetDlgItem(App->ListPanel, IDC_BT_INFO_FILEVIEW);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_InfoSmall_Bmp);

	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	Temp = GetDlgItem(App->ListPanel, IDC_BT_INFO_FILEVIEW);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Show Help File";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti1);
}

// **************************************************************************
// *			Start_FileView:- Terry and Hazel Flanigan 2022				*
// **************************************************************************
void SB_FileView::Start_FileView(void)
{
	App->ListPanel = CreateDialog(App->hInst, (LPCTSTR)IDD_LIST, App->MainHwnd, (DLGPROC)ListPanel_Proc);
	Init_Bmps_FileView();
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
		App->SBC_FileView->FileView_Active = 1;
		ShowWindow(hDlg, 1);

		SendDlgItemMessage(hDlg, IDC_TREE1, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_ENVIONMENT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
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

	case WM_CONTEXTMENU:
	{
		App->SBC_FileView->Context_Menu(hDlg);

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
		}
		
		return 1;
	}
	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDM_COPY)
		{
			App->SBC_Object->Copy_Object(App->SBC_Properties->Current_Selected_Object);

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

			App->SBC_Object->Rename_Object(App->SBC_Properties->Current_Selected_Object);
			App->SBC_Properties->Update_ListView_Objects();

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDC_LEVELS)
		{
			//App->SBC_FileView->Level_But_Active = 1;
			//App->SBC_FileView->Stock_But_Active = 0;
			//App->RedrawWindow_Dlg(hDlg);

			//ShowWindow(GetDlgItem(App->ListPanel, IDC_TREE1), 1);

			//App->GDCL_FileView->HideRightPanes();
			//ShowWindow(App->GD_Properties_Hwnd, 1);*/

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_STOCK)
		{
			if (App->SBC_Scene->Scene_Loaded == 1)
			{
				/*App->Cl_FileView->HideRightPanes();
				ShowWindow(App->GD_Stock_Hwnd, 1);*/
				//App->Cl_Stock->Start_Stock_Dialog();
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_ENVIONMENT)
		{
			App->Cl_Environment->Start_Environment();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_INFO_FILEVIEW)
		{
			App->Cl_Utilities->OpenHTML("Help\\Templete.html");
			return TRUE;
		}
		break;
	}

	case WM_CLOSE:
	{
		App->SBC_FileView->FileView_Active = 0;
		ShowWindow(App->ListPanel, 0);

		CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_UNCHECKED);

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
// *			AddRootFolder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_FileView::AddRootFolder(void)
{
	tvinsert.hParent = Root;			// top most level no need handle
	tvinsert.hInsertAfter = TVI_LAST; // work as root level
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = App->SBC_Project->m_Project_Name;
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
	tvinsert.item.pszText = App->SBC_Project->m_Level_Name;
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
	FV_Areas_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

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
	GD_EntitiesFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = GD_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Sounds";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_Sounds_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = GD_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Messages";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_Messages_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = GD_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Move_Entities";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_Move_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	//tvinsert.hParent = GD_EntitiesFolder;
	//tvinsert.hInsertAfter = TVI_LAST;
	//tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	//tvinsert.item.pszText = "Collectables";
	//tvinsert.item.iImage = 0;
	//tvinsert.item.iSelectedImage = 1;
	//GD_Collectables_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	//----------------------------------------------------
	tvinsert.hParent = GD_EntitiesFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Teleporters";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_Teleporters_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	////----------------------------------------------------
	//tvinsert.hParent = GD_EntitiesFolder;
	//tvinsert.hInsertAfter = TVI_LAST;
	//tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	//tvinsert.item.pszText = "Particles";
	//tvinsert.item.iImage = 0;
	//tvinsert.item.iSelectedImage = 1;
	//GD_Particles_Folder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

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
	TreeView_Expand(Temp, GD_EntitiesFolder, TVE_EXPAND);
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

	

	//App->SBC_Properties->Enable_Test_Button(0);
	//App->SBC_Properties->Enable_Delete_Button(0);

	//--------------------------------------------------------------------------

	if (!strcmp(FileView_Folder, App->SBC_Project->m_Level_Name)) // Level Folder
	{
		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

		App->SBC_Properties->Edit_Category = Enums::FV_Edit_Level;
		App->SBC_Properties->Update_ListView_Level();
	}

	// ------------------------------------------------------------ Areas
	if (!strcmp(FileView_Folder, "Area")) // Folder
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Areas_Folder;

		return;
	}

	if (!strcmp(FileView_File, "Area"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Areas_File;

		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);
		App->SBC_Aera->Hide_Area_Dlg(1);

		App->SBC_Properties->Edit_Category = Enums::Edit_Area;

		App->SBC_Properties->Update_ListView_Area();

		return;

	}

	// ------------------------------------------------------------ Objects
	if (!strcmp(FileView_Folder, "Objects")) // Folder
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Objects_Folder;
		return;
	}
	if (!strcmp(FileView_File, "Objects"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Objects_File;

		HideRightPanes();
		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 1);
		App->SBC_Object->Hide_Object_Dlg(1);
		App->SBC_Props_Dialog->Hide_Dimensions_Dlg(1);
		App->SBC_Props_Dialog->Hide_Debug_Dlg(1);

		App->SBC_Properties->Edit_Category = Enums::FV_Edit_Object;
		App->SBC_Properties->Current_Selected_Object = Index;

		App->SBC_Object->Update_Types();

		if (App->SBC_Properties->Edit_Physics == 0)
		{
			App->Cl_Visuals->MarkerBB_Addjust(Index);
			App->SBC_Properties->Update_ListView_Objects();
		}
		else
		{
			//App->SBC_Properties->Update_ListView_Physics();
		}

		return;
	}

	// ------------------------------------------------------------ Players
	if (!strcmp(FileView_Folder, "Player")) // Folder
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Player_Folder;
		return;
	}
	if (!strcmp(FileView_File, "Player"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Player_File;

		HideRightPanes();
		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 1);
		App->SBC_Player->Hide_Player_Dlg(1);

		App->SBC_Properties->Edit_Category = Enums::Edit_Player;
		App->SBC_Properties->Current_Selected_Object = Index;
		
		if (App->SBC_Properties->Edit_Physics == 0)
		{
			App->SBC_Properties->Update_ListView_Player();
		}
		else
		{
			App->SBC_Properties->Update_ListView_Player_Physics();
		}
		return;
	}

	// ------------------------------------------------------------ Cameras
	if (!strcmp(FileView_Folder, "Camera"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Cameras_Folder;

		return;
	}

	if (!strcmp(FileView_File, "Camera"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Cameras_File;

		HideRightPanes();
		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 1);
		App->SBC_Camera->Hide_Cam_Dlg(1);
		
		App->SBC_Properties->Edit_Category = Enums::Edit_Camera;

		App->SBC_Properties->Current_Selected_Object = Index;

		App->SBC_Properties->Update_ListView_Camera();
		
		return;
	}

	// ------------------------------------------------------------ Sounds
	if (!strcmp(FileView_Folder, "Sounds")) // Folder
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Sounds_Folder;
		return;
	}
	if (!strcmp(FileView_File, "Sounds"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Sounds_File;

		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);
		App->SBC_Object->Hide_Object_Dlg(1);
		App->SBC_Props_Dialog->Hide_Dimensions_Dlg(1);
		App->SBC_Props_Dialog->Hide_Debug_Dlg(1);

		App->SBC_Properties->Is_Player = 0;
		App->SBC_Properties->Edit_Category = Enums::Edit_Sounds;
		App->SBC_Properties->Current_Selected_Object = Index;

		if (App->SBC_Properties->Edit_Physics == 0)
		{
			App->SBC_Properties->Update_ListView_Sounds();
		}
		else
		{
			//App->SBC_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(Index);

		return;
	}

	// ------------------------------------------------------------ Messages
	if (!strcmp(FileView_Folder, "Messages")) // Folder
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Messages_Folder;
		return;
	}

	if (!strcmp(FileView_File, "Messages"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Messages_File;

		HideRightPanes();
		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 1);
		App->SBC_Object->Hide_Object_Dlg(1);
		App->SBC_Props_Dialog->Hide_Dimensions_Dlg(1);
		App->SBC_Props_Dialog->Hide_Debug_Dlg(1);

		App->SBC_Properties->Is_Player = 0; // Mark as Object selected
		App->SBC_Properties->Edit_Category = Enums::Edit_Message;
		App->SBC_Properties->Current_Selected_Object = Index;


		if (App->SBC_Properties->Edit_Physics == 0)
		{
			App->SBC_Properties->Update_ListView_Messages();
		}
		else
		{
			//App->SBC_Properties->Update_ListView_Physics();
		}

		App->Cl_Visuals->MarkerBB_Addjust(Index);

		return;
	}

	// ------------------------------------------------------------ Move Entity
	if (!strcmp(FileView_Folder, "Move_Entities")) // Folder
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Move_Folder;

		return;
	}
	if (!strcmp(FileView_File, "Move_Entities"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Move_File;

		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);
		App->SBC_Object->Hide_Object_Dlg(1);
		App->SBC_Props_Dialog->Hide_Dimensions_Dlg(1);
		App->SBC_Props_Dialog->Hide_Physics_Reset_Dlg(1);
		App->SBC_Props_Dialog->Hide_Debug_Dlg(1);

		App->SBC_Properties->Is_Player = 0; // Mark as Object selected

		App->SBC_Properties->Edit_Category = Enums::Edit_Move_Entity;
		App->SBC_Properties->Current_Selected_Object = Index;

		App->SBC_Properties->Update_ListView_Move_Entities();

		return;
	}

	// ------------------------------------------------------------ Teleporter Entity
	if (!strcmp(FileView_Folder, "Teleporters")) // Folder
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Teleports_Folder;

		return;
	}
	if (!strcmp(FileView_File, "Teleporters"))
	{
		App->SBC_FileView->Context_Selection = Enums::FileView_Teleports_File;

		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);
		App->SBC_Object->Hide_Object_Dlg(1);
		App->SBC_Props_Dialog->Hide_Dimensions_Dlg(1);
		App->SBC_Props_Dialog->Hide_Debug_Dlg(1);

		App->SBC_Properties->Is_Player = 0; // Mark as Object selected

		App->Cl_Visuals->MarkerBB_Addjust(Index);

		App->SBC_Properties->Edit_Category = Enums::Edit_Teleport;
		App->SBC_Properties->Current_Selected_Object = Index;
		

		App->SBC_Properties->Update_ListView_Teleport();
		
		return;
	}

	// Collectables
	if (!strcmp(FileView_Folder, "Collectables")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");

			return;
		}

		App->SBC_Dialogs->YesNo("Add Entity", "Do you want to add a new Collectable Entity now", 1);
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_MeshViewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Collectables;; // Collectables
			App->SBC_MeshViewer->StartMeshViewer();
			
			//App->Cl__Add_NewObject->Add_Collectable_Entity();
		}

		return;
	}
	if (!strcmp(FileView_File, "Collectables"))
	{
		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

//		App->SBC_Properties->Enable_Delete_Button(1);

		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->SBC_Properties->Edit_Category = Enums::Edit_Collectable;
		App->SBC_Properties->Current_Selected_Object = Index;
//		App->SBC_Properties->Update_Transform_Dlg();


		if (App->SBC_Properties->Edit_Physics == 0)
		{
			//App->SBC_Properties->Update_ListView_Collectables();
		}
		else
		{
			//App->SBC_Properties->Update_ListView_Physics();
		}

		/*if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Player)
		{
			App->Cl_Object_Props->Edit_Type = Enums::FV_Edit_Object;
			App->Cl_Object_Props->Update_Properties_Mesh();
			return;
		}

		if (App->Cl_Object_Props->Edit_Type == Enums::FV_Edit_Object)
		{
			App->Cl_Object_Props->Update_Properties_Mesh();
			return;
		}

		if (App->Cl_Object_Props->Edit_Type == Enums::Edit_Physics_Object)
		{
			App->Cl_Object_Props->Update_Properties_Physics();
			return;
		}*/
		return;
	}

	// Particles
	if (!strcmp(FileView_Folder, "Particles")) // Folder
	{
		if (App->Cl_Scene_Data->Scene_Has_Area == 0)
		{
			App->Say("An Area or Building must be Added Firest");
			return;
		}


		App->SBC_Dialogs->YesNo("Add Entity", "Do you want to add a new Particle Entity now", 1);
		bool Doit = App->Cl_Dialogs->Canceled;
		if (Doit == 0)
		{
			//App->SBC_Objects_New->Add_New_Particle();
		}

		return;
	}
	if (!strcmp(FileView_File, "Particles"))
	{

		HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);

//		App->SBC_Properties->Enable_Delete_Button(1);

		//App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		//App->Cl_Object_Props->Selected_Object_Index = Index;
		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->SBC_Properties->Edit_Category = Enums::Edit_Particles;
		App->SBC_Properties->Current_Selected_Object = Index;

//		App->SBC_Properties->Update_Transform_Dlg();



		if (App->SBC_Properties->Edit_Physics == 0)
		{
			//App->SBC_Properties->Update_ListView_Particles();
		}
		else
		{
			//App->SBC_Properties->Update_ListView_Physics();
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
		App->SBC_Dialogs->YesNo("Add Entity", "Not Available Yet Next Release", 1);
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

//		App->SBC_Properties->Enable_Delete_Button(1);

		//App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		//App->Cl_Object_Props->Selected_Object_Index = Index;
		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->SBC_Properties->Edit_Category = Enums::Edit_Environment;
		App->SBC_Properties->Current_Selected_Object = Index;

//		App->SBC_Properties->Update_Transform_Dlg();


		if (App->SBC_Properties->Edit_Physics == 0)
		{
			//App->SBC_Properties->Update_ListView_Environment();
		}
		else
		{
			//App->SBC_Properties->Update_ListView_Physics();
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
		App->SBC_Dialogs->YesNo("Add Entity", "Not Available Yet Next Release", 1);
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
		App->SBC_Aera->Hide_Area_Dlg(1);

//		App->SBC_Properties->Enable_Delete_Button(1);

		//App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		//App->Cl_Object_Props->Selected_Object_Index = Index;
		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->SBC_Properties->Edit_Category = Enums::Edit_Area_Change;
		App->SBC_Properties->Current_Selected_Object = Index;

//		App->SBC_Properties->Update_Transform_Dlg();


		if (App->SBC_Properties->Edit_Physics == 0)
		{
			//App->SBC_Properties->Update_ListView_Environment();
		}
		else
		{
			//App->SBC_Properties->Update_ListView_Physics();
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
		App->SBC_Dialogs->YesNo("Add Entity", "Not Available Yet Next Release", 1);
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

//		App->SBC_Properties->Enable_Delete_Button(1);

		//App->Cl_Object_Props->Is_Player = 0; // Mark as Object selected

		//App->Cl_Object_Props->Selected_Object_Index = Index;
		App->Cl_Visuals->MarkerBB_Addjust(Index);


		App->SBC_Properties->Edit_Category = Enums::Edit_Change_Level;
		App->SBC_Properties->Current_Selected_Object = Index;

//		App->SBC_Properties->Update_Transform_Dlg();


		if (App->SBC_Properties->Edit_Physics == 0)
		{
			//App->SBC_Properties->Update_ListView_Environment();
		}
		else
		{
			//App->SBC_Properties->Update_ListView_Physics();
		}

		return;
	}

}

// *************************************************************************
// *					HideRightPanes Terry Bernie 					   *
// *************************************************************************
void SB_FileView::HideRightPanes(void)
{
	if (App->SBC_Scene->Scene_Loaded == 1)
	{
		//ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 0);	
	}

	App->SBC_Camera->Hide_Cam_Dlg(0);
	App->SBC_Player->Hide_Player_Dlg(0);
	App->SBC_Aera->Hide_Area_Dlg(0);
	App->SBC_Object->Hide_Object_Dlg(0);

	App->SBC_Props_Dialog->Hide_Dimensions_Dlg(0);
	App->SBC_Props_Dialog->Hide_Physics_Reset_Dlg(0);
	App->SBC_Props_Dialog->Hide_Debug_Dlg(0);
}


// *************************************************************************
// *				Add_Item:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
HTREEITEM SB_FileView::Add_Item(HTREEITEM Folder,char *SFileName, int Index,bool NewItem)
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
// *						Redraw_FileView Terry Bernie			 	   *
// *************************************************************************
void SB_FileView::Redraw_FileView()
{
	App->RedrawWindow_Dlg(GetDlgItem(App->ListPanel, IDC_TREE1));
}

// *************************************************************************
// *					Change_Level_Name Terry Flanigan 				   *
// *************************************************************************
void SB_FileView::Change_Level_Name(void)
{
	TVITEM Sitem;
	Sitem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	Sitem.hItem = FV_LevelFolder;
	Sitem.pszText = App->SBC_Project->m_Level_Name;
	Sitem.iImage = 3;
	Sitem.iSelectedImage = 3;
	SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETITEM, 0, (LPARAM)(const LPTVITEM)&Sitem);
}

// *************************************************************************
// *					Change_Project_Name Terry Flanigan 				   *
// *************************************************************************
void SB_FileView::Change_Project_Name(void)
{
	TVITEM Sitem;
	Sitem.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	Sitem.hItem = GD_ProjectFolder;
	Sitem.pszText = App->SBC_Project->m_Project_Name;
	Sitem.iImage = 3;
	Sitem.iSelectedImage = 3;
	SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETITEM, 0, (LPARAM)(const LPTVITEM)&Sitem);
}

// *************************************************************************
// *		Change_Item_Name:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_FileView::Change_Item_Name(HTREEITEM Folder, char *FolderName)
{
	TVITEM Sitem;
	Sitem.mask = TVIF_TEXT;
	Sitem.hItem = Folder;
	Sitem.pszText = FolderName;
	SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETITEM, 0, (LPARAM)(const LPTVITEM)&Sitem);
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
}

// *************************************************************************
// *		Mark_Altered_Folder:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_FileView::Mark_Altered_Folder(HTREEITEM Item)
{
	TVITEM Sitem;
	Sitem.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	Sitem.hItem = Item;
	Sitem.iImage = 8;
	Sitem.iSelectedImage = 9;
	SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETITEM, 0, (LPARAM)(const LPTVITEM)&Sitem);
}

// *************************************************************************
// *				Mark_Clear:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_FileView::Mark_Clear(HTREEITEM Item)
{
	TVITEM Sitem;
	Sitem.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	Sitem.hItem = Item;
	Sitem.iImage = 4;
	Sitem.iSelectedImage = 5;
	SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETITEM, 0, (LPARAM)(const LPTVITEM)&Sitem);
}

// *************************************************************************
// *				Mark_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_FileView::Mark_Clear_Folder(HTREEITEM Item)
{
	TVITEM Sitem;
	Sitem.mask = TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	Sitem.hItem = Item;
	Sitem.iImage = 2;
	Sitem.iSelectedImage = 3;
	SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETITEM, 0, (LPARAM)(const LPTVITEM)&Sitem);
}

// *************************************************************************
// *						Delete_AllItems Terry Bernie			 	   *
// *************************************************************************
void SB_FileView::Delete_AllItems()
{
	TreeView_DeleteAllItems(GetDlgItem(App->ListPanel, IDC_TREE1));

	Root = 0;
	GD_ProjectFolder = NULL;
	FV_Objects_Folder = NULL;
	FV_LevelFolder = NULL;
	FV_Cameras_Folder = NULL;
	GD_TriggerFolder = NULL;
	GD_EntitiesFolder = NULL;
	FV_Sounds_Folder = NULL;
	FV_Messages_Folder = NULL;

	strcpy(App->SBC_Project->m_Level_File_Name, "No Level");

	AddRootFolder();
	MoreFoldersD(); //  Folders under root 
	ExpandRoot();
}

// *************************************************************************
// *						DeleteItem  Terry Bernie 					   *
// *************************************************************************
void SB_FileView::DeleteItem()
{
	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	HTREEITEM i = TreeView_GetSelection(Temp);
	TreeView_DeleteItem(Temp, i);
}

// *************************************************************************
// *						Select_Item Terry Bernie				 	   *
// *************************************************************************
void SB_FileView::Select_Item(int Index)
{
	HideRightPanes();
	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->SBC_Properties->Is_Player = 0; // Mark as Object selected

	App->SBC_Properties->Current_Selected_Object = Index;

	// Sounds
	//if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Sound)
	//{
	//	//App->Cl_FileView_V2->Select_ObjectFV(Index);

	//	App->SBC_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
	//	App->SBC_Properties->Edit_Category = Enums::Edit_Sounds;
	//	//App->Cl_Properties->Update_ListView_Sounds();
	//	return;
	//}

	//// Messages
	//if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Message)
	//{
	//	App->SBC_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
	//	App->SBC_Properties->Edit_Category = Enums::Edit_Message;
	//	//App->Cl_Properties->Update_ListView_Messages();
	//	return;
	//}

	//// Move Entity
	//if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Move)
	//{
	//	App->SBC_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
	//	App->SBC_Properties->Edit_Category = Enums::Edit_Move_Entity;
	//	//App->Cl_Properties->Update_ListView_Move_Entities();
	//	return;
	//}

	//// Collectables
	//if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Colectable)
	//{
	//	App->SBC_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
	//	App->SBC_Properties->Edit_Category = Enums::Edit_Collectable;
	//	//App->Cl_Properties->Update_ListView_Collectables();
	//	return;
	//}

	//// Teleports
	//if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Teleport)
	//{
	//	App->SBC_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
	//	App->SBC_Properties->Edit_Category = Enums::Edit_Teleport;
	//	//App->Cl_Properties->Update_ListView_Teleport();
	//	return;
	//}

	// Fall Through
	//if (App->Cl_Scene_Data->CL_Object[Index]->Usage == Enums::Usage_Object)
	{
		//App->Cl_FileView_V2->Select_ObjectFV(Index);

		App->SBC_FileView->SelectItem(App->SBC_Scene->B_Object[Index]->FileViewItem);
		App->SBC_Properties->Edit_Category = Enums::FV_Edit_Object;
		
		if (App->SBC_Properties->Edit_Physics == 0)
		{
			App->SBC_Properties->Update_ListView_Objects();
		}
		else
		{
			//App->Cl_Properties->Update_ListView_Physics();
		}

		return;
	}
}

// *************************************************************************
// *				SelectItem:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_FileView::SelectItem(HTREEITEM TreeItem)
{

	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);

	//if (Flags[0]->FileView_SceneLoaded == 1)
	{
		TreeView_Select(Temp, NULL, TVGN_CARET);
		TreeView_Select(Temp, TreeItem, TVGN_CARET);
	}
	return 1;
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
// *			Context_Menu:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_FileView::Context_Menu(HWND hDlg)
{
	RECT rcTree;
	HWND hwndTV;
	HTREEITEM htvItem;
	TVHITTESTINFO htInfo = { 0 };
	POINT pt;
	GetCursorPos(&pt);

	long xPos = pt.x;   // x position from message, in screen coordinates
	long yPos = pt.y;   // y position from message, in screen coordinates 

	hwndTV = GetDlgItem(hDlg, IDC_TREE1);         // get the tree view 
	GetWindowRect(hwndTV, &rcTree);              // get its window coordinates
	htInfo.pt.x = xPos - rcTree.left;              // convert to client coordinates
	htInfo.pt.y = yPos - rcTree.top;

	if (htvItem = TreeView_HitTest(hwndTV, &htInfo)) {    // hit test
		TreeView_SelectItem(hwndTV, htvItem);           // success; select the item

		//------------------------------------- Camera
		if (!strcmp(App->SBC_FileView->FileView_Folder, "Camera")) // Folder
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Cameras_Folder;
		}

		if (!strcmp(App->SBC_FileView->FileView_File, "Camera"))
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();

			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_RENAME, L"&Rename");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_COPY, L"&Copy");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING | MF_GRAYED, IDM_PASTE, L"&Paste");
			AppendMenuW(App->SBC_FileView->hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_DELETE, L"&Delete");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Cameras_File;
		}

		//------------------------------------- Objects
		if (!strcmp(App->SBC_FileView->FileView_Folder, "Objects")) // Folder
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Objects_Folder;
		}

		if (!strcmp(App->SBC_FileView->FileView_File, "Objects"))
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();

			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_RENAME, L"&Rename");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_COPY, L"&Copy");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING | MF_GRAYED, IDM_PASTE, L"&Paste");
			AppendMenuW(App->SBC_FileView->hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_DELETE, L"&Delete");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Objects_File;
		}

		//------------------------------------- Messages
		if (!strcmp(App->SBC_FileView->FileView_Folder, "Messages")) // Folder
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Messages_Folder;
		}

		if (!strcmp(App->SBC_FileView->FileView_File, "Messages"))
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();

			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_RENAME, L"&Rename");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_COPY, L"&Copy");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING | MF_GRAYED, IDM_PASTE, L"&Paste");
			AppendMenuW(App->SBC_FileView->hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_DELETE, L"&Delete");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Messages_File;
		}

		//------------------------------------- Sounds
		if (!strcmp(App->SBC_FileView->FileView_Folder, "Sounds")) // Folder
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Sounds_Folder;
		}

		if (!strcmp(App->SBC_FileView->FileView_File, "Sounds"))
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();

			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_RENAME, L"&Rename");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_COPY, L"&Copy");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING | MF_GRAYED, IDM_PASTE, L"&Paste");
			AppendMenuW(App->SBC_FileView->hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_DELETE, L"&Delete");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Sounds_File;
		}

		//------------------------------------- Areas
		if (!strcmp(App->SBC_FileView->FileView_Folder, "Area")) // Folder
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Areas_Folder;
		}

		if (!strcmp(App->SBC_FileView->FileView_File, "Area"))
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();

			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_RENAME, L"&Rename");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_COPY, L"&Copy");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING | MF_GRAYED, IDM_PASTE, L"&Paste");
			AppendMenuW(App->SBC_FileView->hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_DELETE, L"&Delete");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Areas_File;
		}

		//------------------------------------- Move_Entities
		if (!strcmp(App->SBC_FileView->FileView_Folder, "Move_Entities")) // Folder
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Move_Folder;
		}

		if (!strcmp(App->SBC_FileView->FileView_File, "Move_Entities"))
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();

			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_RENAME, L"&Rename");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_COPY, L"&Copy");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING | MF_GRAYED, IDM_PASTE, L"&Paste");
			AppendMenuW(App->SBC_FileView->hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_DELETE, L"&Delete");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Move_File;
		}

		//------------------------------------- Teleport_Entities
		if (!strcmp(App->SBC_FileView->FileView_Folder, "Teleporters")) // Folder
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_NEW, L"&New");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Teleports_Folder;
		}

		if (!strcmp(App->SBC_FileView->FileView_File, "Teleporters"))
		{
			App->SBC_FileView->hMenu = CreatePopupMenu();

			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_RENAME, L"&Rename");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_COPY, L"&Copy");
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING | MF_GRAYED, IDM_PASTE, L"&Paste");
			AppendMenuW(App->SBC_FileView->hMenu, MF_SEPARATOR, 0, NULL);
			AppendMenuW(App->SBC_FileView->hMenu, MF_STRING, IDM_FILE_DELETE, L"&Delete");
			TrackPopupMenu(App->SBC_FileView->hMenu, TPM_RIGHTBUTTON, pt.x, pt.y, 0, App->ListPanel, NULL);
			DestroyMenu(App->SBC_FileView->hMenu);
			Context_Selection = Enums::FileView_Teleports_File;
		}
	}
}

// *************************************************************************
// *				Context_New:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_FileView::Context_New(HWND hDlg)
{
	if (App->SBC_Project->Project_Loaded == 0)
	{
		App->Say("A Project must be created First");

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Areas_Folder)
	{
		App->SBC_Dialogs->YesNo("Add Area", "Do you want to add a new Area", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_MeshViewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Area;
			App->SBC_MeshViewer->StartMeshViewer();
		}

		return;
	}

	if (App->SBC_Scene->Area_Added == 0)
	{
		App->Say("An Area must be Added Firest before adding items");

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Cameras_Folder)
	{
		App->SBC_Dialogs->YesNo("Add Object", "Do you want to add a new Camera", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_Camera->Add_New_Camera();
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Objects_Folder)
	{
		App->SBC_Dialogs->YesNo("Add Object", "Do you want to add a new Object Entity", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_MeshViewer->Mesh_Viewer_Mode = Enums::Mesh_Viewer_Objects;
			App->SBC_MeshViewer->StartMeshViewer();
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Messages_Folder)
	{
		App->SBC_Dialogs->YesNo("Add Message", "Do you want to add a new Message Entity", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_Objects_Create->Add_New_Message();
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Sounds_Folder)
	{
		App->SBC_Dialogs->YesNo("Add Message", "Do you want to add a new Sound Entity", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_Objects_Create->Add_New_Sound();
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Move_Folder)
	{
		App->SBC_Dialogs->YesNo("Add Message", "Do you want to add a new Move Entity", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_Objects_Create->Add_New_Move_Entity();
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Teleports_Folder)
	{
		App->SBC_Dialogs->YesNo("Add Message", "Do you want to add a new Teleport Entity", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_Objects_Create->Add_New_Teleporter();
		}

		return;
	}

	return;
}

// *************************************************************************
// *			Context_Delete:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_FileView::Context_Delete(HWND hDlg)
{

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Areas_File)
	{
		if (App->SBC_Scene->Area_Count == 1)
		{
			App->Say("Can not delete there must be at least one Area");
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Cameras_File)
	{
		if (App->SBC_Scene->Camera_Count == 1)
		{
			App->Say("Can not delete there must be at least one Camera");
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Player_File)
	{
		if (App->SBC_Scene->Player_Count == 1)
		{
			App->Say("Can not delete there must be at least one Player");
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Objects_File)
	{
		App->SBC_Dialogs->YesNo("Remove Object","Are you sure", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_Object->Delete_Object();
			App->SBC_FileView->Mark_Altered_Folder(FV_Objects_Folder);
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Messages_File)
	{
		App->SBC_Dialogs->YesNo("Remove Message", "Are you sure", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_Object->Delete_Object();
			App->SBC_FileView->Mark_Altered_Folder(FV_Messages_Folder);
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Sounds_File)
	{
		App->SBC_Dialogs->YesNo("Remove Sound", "Are you sure", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_Object->Delete_Object();
			App->SBC_FileView->Mark_Altered_Folder(FV_Sounds_Folder);
		}

		return;
	}

	if (App->SBC_FileView->Context_Selection == Enums::FileView_Move_File)
	{
		App->SBC_Dialogs->YesNo("Remove Move Entity", "Are you sure", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 0)
		{
			App->SBC_Object->Delete_Object();
			App->SBC_FileView->Mark_Altered_Folder(FV_Move_Folder);
		}

		return;
	}

	return;
}


