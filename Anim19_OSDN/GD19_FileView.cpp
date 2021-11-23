/*
Copyright (c) GameDirector 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
#include "GD19_FileView.h"


GD19_FileView::GD19_FileView()
{
	FileView_Active = 0;

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

	Level_But_Active = 1;
	Stock_But_Active = 0;
}


GD19_FileView::~GD19_FileView()
{
}

// *************************************************************************
// *					Add_PlayeFile Terry Bernie					 	   *
// *************************************************************************
HTREEITEM GD19_FileView::Add_PlayerFile(char *SFileName, int Index)
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

// *************************************************************************
// *						ChangeItem_Name_Stock Terry Bernie		 	   *
// *************************************************************************
void GD19_FileView::ChangeItem_Name_Stock(HTREEITEM Folder, char* FolderName)
{
	///HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE2);
	///HTREEITEM i = TreeView_GetSelection(Temp);

	TVITEM Sitem;
	Sitem.mask = TVIF_TEXT;
	//Sitem.hItem = i;
	Sitem.pszText = FolderName;
	///SendDlgItemMessage(App->ListPanel, IDC_TREE2, TVM_SETITEM, 0, (LPARAM)(const LPTVITEM)& Sitem);
}

// *************************************************************************
// *						ChangeItem_Name Terry Bernie			 	   *
// *************************************************************************
void GD19_FileView::ChangeItem_Name(HTREEITEM Folder, char* New_Name)
{
	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	//HTREEITEM i = TreeView_GetSelection(Temp);

	TVITEM Sitem;
	Sitem.mask = TVIF_TEXT;
	Sitem.hItem = Folder;
	Sitem.pszText = New_Name;
	SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_SETITEM, 0, (LPARAM)(const LPTVITEM)& Sitem);
}

// *************************************************************************
// *						DeleteItem  Terry Bernie 					   *
// *************************************************************************
void GD19_FileView::DeleteItem()
{
	HWND Temp = GetDlgItem(App->ListPanel, IDC_TREE1);
	HTREEITEM i = TreeView_GetSelection(Temp);
	TreeView_DeleteItem(Temp, i);
}

// *************************************************************************
// *						Select_Item Terry Bernie				 	   *
// *************************************************************************
void GD19_FileView::Select_Item(int Index)
{
	HideRightPanes();
	ShowWindow(App->GD_Properties_Hwnd, 1);

	App->Cl_Properties->Is_Player = 0; // Mark as Object selected

	App->Cl_Properties->Current_Selected_Object = Index;

	// Sounds
	if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Sound)
	{
		//App->Cl_FileView_V2->Select_ObjectFV(Index);

		App->Cl_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
		App->Cl_Properties->Edit_Category = Enums::Edit_Sounds;
		App->Cl_Properties->Update_ListView_Sounds();
		return;
	}

	// Messages
	if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Message)
	{
		App->Cl_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
		App->Cl_Properties->Edit_Category = Enums::Edit_Message;
		App->Cl_Properties->Update_ListView_Messages();
		return;
	}

	// Move Entity
	if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Move)
	{
		App->Cl_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
		App->Cl_Properties->Edit_Category = Enums::Edit_Move_Entity;
		App->Cl_Properties->Update_ListView_Move_Entities();
		return;
	}

	// Collectables
	if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Colectable)
	{
		App->Cl_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
		App->Cl_Properties->Edit_Category = Enums::Edit_Collectable;
		App->Cl_Properties->Update_ListView_Collectables();
		return;
	}

	// Teleports
	if (App->Cl_Scene_Data->Cl_Object[Index]->Usage == Enums::Usage_Teleport)
	{
		App->Cl_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
		App->Cl_Properties->Edit_Category = Enums::Edit_Teleport;
		App->Cl_Properties->Update_ListView_Teleport();
		return;
	}

	// Fall Through
	//if (App->Cl_Scene_Data->CL_Object[Index]->Usage == Enums::Usage_Object)
	{
		//App->Cl_FileView_V2->Select_ObjectFV(Index);

		App->Cl_FileView->SelectItem(App->Cl_Scene_Data->Cl_Object[Index]->ListViewItem);
		App->Cl_Properties->Edit_Category = Enums::Edit_Mesh_Object;
		App->Cl_Properties->Update_Transform_Dlg();

		if (App->Cl_Properties->Edit_Physics == 0)
		{
			App->Cl_Properties->Update_ListView_Objects();
		}
		else
		{
			App->Cl_Properties->Update_ListView_Physics();
		}

		return;
	}
}

// *************************************************************************
// *				SelectItem	Terry Bernie							   *
// *************************************************************************
bool GD19_FileView::SelectItem(HTREEITEM TreeItem)
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
// *					HideRightPanes Terry Bernie 					   *
// *************************************************************************
void GD19_FileView::HideRightPanes(void)
{
	if (App->Cl_Scene_Data->SceneLoaded == 1)
	{
		ShowWindow(App->GD_Properties_Hwnd, 0);
	///	ShowWindow(App->GD_Stock_Hwnd, 0);
	}
}

// *************************************************************************
// *					Add_Room_Object Terry Bernie				 	   *
// *************************************************************************
HTREEITEM GD19_FileView::Add_Room_Object(char* SFileName, int Index)
{
	HWND Temp2 = GetDlgItem(App->ListPanel, IDC_TREE1);

	tvinsert.hParent = GD_Rooms;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvinsert.item.pszText = SFileName;
	tvinsert.item.iImage = 4;
	tvinsert.item.iSelectedImage = 5;
	tvinsert.item.lParam = Index;
	HTREEITEM Temp = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	if (App->Cl_Load_Scene->File_Is_Loading == 0)
	{
		TreeView_Select(Temp2, Temp, TVGN_CARET);
	}

	return Temp;
}

// *************************************************************************
// *					Add_MiscFile Terry Bernie					 	   *
// *************************************************************************
HTREEITEM GD19_FileView::Add_MiscFile(char *SFileName, int Index)
{
	HWND Temp2 = GetDlgItem(App->ListPanel, IDC_TREE1);

	tvinsert.hParent = GD_ObjectsFolder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvinsert.item.pszText = SFileName;
	tvinsert.item.iImage = 4;
	tvinsert.item.iSelectedImage = 5;
	tvinsert.item.lParam = Index;
	HTREEITEM Temp = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	if (App->Cl_Load_Scene->File_Is_Loading == 0)
	{
		TreeView_Select(Temp2, Temp, TVGN_CARET);
	}

	return Temp;
}

// *************************************************************************
// *					Add_Sound_Entity Terry Bernie				 	   *
// *************************************************************************
HTREEITEM GD19_FileView::Add_Sound_Entity(char *SFileName, int Index)
{
	HWND Temp2 = GetDlgItem(App->ListPanel, IDC_TREE1);

	tvinsert.hParent = GD_Entities_Sound_Folder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvinsert.item.pszText = SFileName;
	tvinsert.item.iImage = 4;
	tvinsert.item.iSelectedImage = 5;
	tvinsert.item.lParam = Index;
	HTREEITEM Temp = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	if (App->Cl_Load_Scene->File_Is_Loading == 0)
	{
		TreeView_Select(Temp2, Temp, TVGN_CARET);
	}

	return Temp;
}

// *************************************************************************
// *					Add_Message_Entity Terry Bernie				 	   *
// *************************************************************************
HTREEITEM GD19_FileView::Add_Message_Entity(char *SFileName, int Index)
{
	HWND Temp2 = GetDlgItem(App->ListPanel, IDC_TREE1);

	tvinsert.hParent = GD_Entities_Message_Folder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvinsert.item.pszText = SFileName;
	tvinsert.item.iImage = 4;
	tvinsert.item.iSelectedImage = 5;
	tvinsert.item.lParam = Index;
	HTREEITEM Temp = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	if (App->Cl_Load_Scene->File_Is_Loading == 0)
	{
		TreeView_Select(Temp2, Temp, TVGN_CARET);
	}

	return Temp;
}

// *************************************************************************
// *					Add_Move_Entity Terry Bernie				 	   *
// *************************************************************************
HTREEITEM GD19_FileView::Add_Move_Entity(char *SFileName, int Index)
{
	HWND Temp2 = GetDlgItem(App->ListPanel, IDC_TREE1);

	tvinsert.hParent = GD_Entities_Move_Folder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvinsert.item.pszText = SFileName;
	tvinsert.item.iImage = 4;
	tvinsert.item.iSelectedImage = 5;
	tvinsert.item.lParam = Index;
	HTREEITEM Temp = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	if (App->Cl_Load_Scene->File_Is_Loading == 0)
	{
		TreeView_Select(Temp2, Temp, TVGN_CARET);
	}

	return Temp;
}

// *************************************************************************
// *					Add_Collectable Terry Bernie				 	   *
// *************************************************************************
HTREEITEM  GD19_FileView::Add_Collectable(char* SFileName, int Index)
{
	HWND Temp2 = GetDlgItem(App->ListPanel, IDC_TREE1);

	tvinsert.hParent = GD_Collectables_Folder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvinsert.item.pszText = SFileName;
	tvinsert.item.iImage = 4;
	tvinsert.item.iSelectedImage = 5;
	tvinsert.item.lParam = Index;
	HTREEITEM Temp = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	if (App->Cl_Load_Scene->File_Is_Loading == 0)
	{
		TreeView_Select(Temp2, Temp, TVGN_CARET);
	}

	return Temp;
}

// *************************************************************************
// *					Add_Teleport Terry Bernie				 	   *
// *************************************************************************
HTREEITEM GD19_FileView::Add_Teleport(char* SFileName, int Index)
{
	HWND Temp2 = GetDlgItem(App->ListPanel, IDC_TREE1);

	tvinsert.hParent = GD_Teleporters_Folder;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE | TVIF_PARAM;
	tvinsert.item.pszText = SFileName;
	tvinsert.item.iImage = 4;
	tvinsert.item.iSelectedImage = 5;
	tvinsert.item.lParam = Index;
	HTREEITEM Temp = (HTREEITEM)SendDlgItemMessage(App->ListPanel, IDC_TREE1, TVM_INSERTITEM, 0, (LPARAM)& tvinsert);

	if (App->Cl_Load_Scene->File_Is_Loading == 0)
	{
		TreeView_Select(Temp2, Temp, TVGN_CARET);
	}

	return Temp;
}
