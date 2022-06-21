#include "stdafx.h"
#include "ME_App.h"
#include "resource.h"
#include "ME_FileView.h"


ME_FileView::ME_FileView()
{
	Root =				nullptr;
	GD_ProjectFolder =	nullptr;
	GD_ModelFolder =	nullptr;;
	GD_GroupsFolder =	nullptr;;

	strcpy(FileView_Folder, "");
	strcpy(FileView_File, "");

	FileView_Active = 0;
}


ME_FileView::~ME_FileView()
{
}

// *************************************************************************
//							Start_FileView Terry Flanigan					*
// *************************************************************************
void ME_FileView::Start_FileView(void)
{
	App->ListPanel = CreateDialog(App->hInst, (LPCTSTR)IDD_LIST, App->MainHwnd, (DLGPROC)ListPanel_Proc);

	Init_FileView();
}

// *************************************************************************
// *					ListPanel_Proc_Proc Terry Flanigan				   *
// *************************************************************************
LRESULT CALLBACK ME_FileView::ListPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{

	case WM_INITDIALOG:
	{
		App->CL_FileView->FileView_Active = 1;
		ShowWindow(hDlg, 1);

		SendDlgItemMessage(hDlg, IDC_TREE1, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_CHECKED);
		return TRUE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_SIZE:
	{
		//App->Cl_Panels->Resize_FileView();
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
				App->CL_FileView->Get_Selection((LPNMHDR)lParam);
			}
			}
		}

		return 1;
	}
	case WM_COMMAND:
	{
	
		break;
	}

	case WM_CLOSE:
	{
		App->CL_FileView->FileView_Active = 0;
		ShowWindow(App->ListPanel, 0);

		CheckMenuItem(App->mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_UNCHECKED);

		break;
	}

	break;
	}
	return FALSE;
}

// *************************************************************************
// *						Init_FileView Terry Flanigan				   *
// *************************************************************************
void ME_FileView::Init_FileView(void)
{
	InitCommonControls();	    // make our tree control to work

								////====================================================//
	//hImageList = ImageList_Create(16, 16, FALSE, 6, 0); // Zero Index

	//													//--------- Grayed Folder Closed Open 0 1
	//hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_FILEINACTIVE));
	//ImageList_Add(hImageList, hBitMap, NULL);
	//DeleteObject(hBitMap);

	////--------- Green Folder Closed Open 2 3
	//hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_TREE));
	//ImageList_Add(hImageList, hBitMap, NULL);
	//DeleteObject(hBitMap);

	////--------- Uselected File Open 4
	//hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_FILE));
	//ImageList_Add(hImageList, hBitMap, (HBITMAP)NULL);
	//DeleteObject(hBitMap);

	////--------- Selected File Open 5
	//hBitMap = LoadBitmap(App->hInst, MAKEINTRESOURCE(IDB_FILESELECTED));
	//ImageList_Add(hImageList, hBitMap, (HBITMAP)NULL);
	//DeleteObject(hBitMap);

	//SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETIMAGELIST, 0, (LPARAM)hImageList);

	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	TreeView_DeleteAllItems(Temp);


	TreeView_SetBkColor(Temp, (COLORREF)RGB(255, 255, 255));

	AddRootFolder();
	MoreFoldersD(); //  Folders under root 
	ExpandRoot();
}

// *************************************************************************
// *					AddRootFolder Terry Flanigan				 	   *
// *************************************************************************
void ME_FileView::AddRootFolder(void)
{
	tvinsert.hParent = Root;			// top most level no need handle
	tvinsert.hInsertAfter = TVI_LAST; // work as root level
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "No Project";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	GD_ProjectFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}

// *************************************************************************
// *						MoreFoldersD Terry Flanigan 			 	   *
// *************************************************************************
void ME_FileView::MoreFoldersD(void) // last folder level
{
	//------------------------------------------------------- Level 
	tvinsert.hParent = GD_ProjectFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Test";// App->SBC_Project->Level_File_Name;
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_ModelFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	////------------------------------------------------------- Camera
	tvinsert.hParent = GD_ModelFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Groups";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	GD_GroupsFolder = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}

// *************************************************************************
// *					ExpandRoot Terry Flanigan						   *
// *************************************************************************
void ME_FileView::ExpandRoot(void)
{
	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	HTREEITEM i = TreeView_GetSelection(Temp);

	TreeView_Expand(Temp, GD_ProjectFolder, TVE_EXPAND);
	TreeView_Expand(Temp, GD_ModelFolder, TVE_EXPAND);
	TreeView_Expand(Temp, GD_GroupsFolder, TVE_EXPAND);
}

// *************************************************************************
// *						Add_Group Terry Flanigan				 	   *
// *************************************************************************
HTREEITEM ME_FileView::Add_Group(char *SFileName, int Index)
{
	tvinsert.hParent = GD_GroupsFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvinsert.item.pszText = SFileName;
	tvinsert.item.iImage = 4;
	tvinsert.item.iSelectedImage = 5;
	tvinsert.item.lParam = Index;
	HTREEITEM Temp = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	return Temp;
}

// *************************************************************************
// *					Get_Selection Terry Bernie					 	   *
// *************************************************************************
void ME_FileView::Get_Selection(LPNMHDR lParam)
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

	if (!strcmp(FileView_Folder, "Groups")) // Folder
	{

		return;
	}

	if (!strcmp(FileView_File, "Groups"))
	{
		App->Say_Win(App->CL_Model->Group[Index]->GroupName);

		/*HideRightPanes();
		ShowWindow(App->GD_Properties_Hwnd, 1);
		App->SBC_Aera->Hide_Area_Dlg(1);

		App->SBC_Properties->Edit_Category = Enums::Edit_Area;

		App->SBC_Properties->Update_ListView_Area();*/

		return;

	}

}
