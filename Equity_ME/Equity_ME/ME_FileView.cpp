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

		HMENU mMenu = GetMenu(App->MainHwnd);
		CheckMenuItem(mMenu, ID_WINDOWS_FILEVIEW, MF_BYCOMMAND | MF_CHECKED);
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
				//App->SBC_FileView->Get_Selection((LPNMHDR)lParam);
			}
			}
		}

		return 1;
	}
	case WM_COMMAND:
	{
		//if (LOWORD(wParam) == IDC_LEVELS)
		//{
		//	App->SBC_FileView->Level_But_Active = 1;
		//	App->SBC_FileView->Stock_But_Active = 0;
		//	App->RedrawWindow_Dlg(hDlg);

		//	ShowWindow(GetDlgItem(App->ListPanel, IDC_TREE1), 1);

		//	//App->GDCL_FileView->HideRightPanes();
		//	//ShowWindow(App->GD_Properties_Hwnd, 1);*/

		//	return TRUE;
		//}

		break;
	}

	case WM_CLOSE:
	{
		App->CL_FileView->FileView_Active = 0;
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
// *			AddRootFolder Terry Bernie			 				 	   *
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
// *						MoreFoldersD Terry Bernie 				 	   *
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
// *					ExpandRoot Terry Bernie							   *
// *************************************************************************
void ME_FileView::ExpandRoot(void)
{
	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	HTREEITEM i = TreeView_GetSelection(Temp);

	TreeView_Expand(Temp, GD_ProjectFolder, TVE_EXPAND);
	TreeView_Expand(Temp, GD_ModelFolder, TVE_EXPAND);
	TreeView_Expand(Temp, GD_GroupsFolder, TVE_EXPAND);
}
