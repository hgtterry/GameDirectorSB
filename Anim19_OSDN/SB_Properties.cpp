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
#include "SB_Properties.h"


SB_Properties::SB_Properties()
{
	Properties_Dlg_hWnd =	nullptr;
	Properties_hLV =		nullptr;

	Properties_Dlg_Active = 0;
	Current_Selected_Object = 0;

	btext[0] = 0;

	Edit_Category = Enums::Edit_Mesh_Object;
	Edit_Physics = 0;

	Is_Player = 0;
}


SB_Properties::~SB_Properties()
{
}

// *************************************************************************
// *						Reset_Class Terry Bernie				 	   *
// *************************************************************************
void SB_Properties::Reset_Class()
{
	App->SBC_Camera->Hide_Cam_Dlg(0);
	App->SBC_Player->Hide_Player_Dlg(0);
	App->SBC_Aera->Hide_Area_Dlg(0);
	Clear_Listview();
}

// *************************************************************************
// *					Start_GD_Properties Terry Bernie   		 	 	   *
// *************************************************************************
void SB_Properties::Start_GD_Properties(void)
{
	if (Properties_Dlg_Active == 1)
	{
		return;
	}

	Properties_Dlg_Active = 1;
	HMENU mMenu = GetMenu(App->MainHwnd);
	///	CheckMenuItem(mMenu, ID_WINDOW_SHOWMODELGLBAL, MF_BYCOMMAND | MF_CHECKED);

	Properties_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_GD_PROPERTIES, App->Fdlg, (DLGPROC)GD_Properties_Proc);
	ShowWindow(Properties_Dlg_hWnd, 1);

	Create_Properties_hLV();
	//Set_DataView();

}
// *************************************************************************
// *					GD_Properties_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK SB_Properties::GD_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STOBJECTNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BTOBJECT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTPHYSICS, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));


		App->Cl_Object_Props->Edit_Type = Enums::Edit_Mesh_Object;

		return 1;
	}

	case WM_CTLCOLORSTATIC:
	{

		if (GetDlgItem(hDlg, IDC_STOBJECTNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->DialogBackGround;
		}
		//--------------------------------------------
		if (GetDlgItem(hDlg, IDC_STP1) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STP2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STP3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		//--------------------------------------------
		if (GetDlgItem(hDlg, IDC_STR1) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STR2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STR3) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		//--------------------------------------------
		if (GetDlgItem(hDlg, IDC_STS1) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STS2) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STS3) == (HWND)lParam)
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
		return (LONG)App->DialogBackGround;
	}

	case WM_CLOSE:
	{
		App->SBC_Properties->Properties_Dlg_Active = 0;
		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 0);

		HMENU mMenu = GetMenu(App->MainHwnd);
		///CheckMenuItem(mMenu, ID_WINDOW_SHOWMODELGLBAL, MF_BYCOMMAND | MF_UNCHECKED);

		break;
	}
	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->hwndFrom == App->SBC_Properties->Properties_hLV)
		{
			switch (some_item->code)
			{
			case NM_CLICK:
			{
				App->SBC_Properties->ListView_OnClickOptions(lParam);
			}
			}
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{

		break;
	}
	}
	return FALSE;
}


// *************************************************************************
// *					Create_Properties_hLV Terry Bernie				   *
// *************************************************************************
void SB_Properties::Create_Properties_hLV(void)
{
	int NUM_COLS = 2;
	Properties_hLV = CreateWindowEx(0, WC_LISTVIEW, "",
		WS_CHILD | WS_VISIBLE | WS_BORDER | WS_VSCROLL | WS_VSCROLL | LVS_REPORT | LVS_NOCOLUMNHEADER | LVS_SHOWSELALWAYS, 7, 50,
		230, 240, Properties_Dlg_hWnd, 0, App->hInst, NULL);

	DWORD exStyles = LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES;

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
		"", ""
	};
	int headerSize[] =
	{
		100, 120
	};

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_InsertColumn(Properties_hLV, header, &lvC);
	}
	
	SendMessage(Properties_hLV, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

	return;
}

// *************************************************************************
// *			ListView_OnClickOptions  Terry Bernie			 		   *
// *************************************************************************
void SB_Properties::ListView_OnClickOptions(LPARAM lParam)
{
	// Area
	if (Edit_Category == Enums::Edit_Area)
	{
		App->SBC_Properties->Edit_Area_Onclick(lParam);

		return;
	}

	// Camera
	if (Edit_Category == Enums::Edit_Camera)
	{
		App->SBC_Properties->Edit_Camera_Onclick(lParam);

		return;
	}

	// Player
	if (Edit_Category == Enums::Edit_Player)
	{
		if (Edit_Physics == 0)
		{
			Edit_Player_Onclick(lParam);
		}
		else
		{
			Edit_Player_Physics_Onclick(lParam);
		}

		return;
	}

	// Objects
	if (Edit_Category == Enums::Edit_Mesh_Object)
	{
		if (Edit_Physics == 0)
		{
			Edit_Object_Onclick(lParam);
		}
		return;
	}

	return;
}

// *************************************************************************
// *					Clear_Listview Terry Bernie					 	   *
// *************************************************************************
void SB_Properties::Clear_Listview()
{
	ListView_DeleteAllItems(App->SBC_Properties->Properties_hLV);
}

// *************************************************************************
// *			Update_ListView_Objects	Terry Bernie 				 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Objects()
{
	int index = App->SBC_Properties->Current_Selected_Object;

	char chr_Scale[100];

	char chr_PosX[100];
	char chr_PosY[100];
	char chr_PosZ[100];

	char chr_RotX[100];
	char chr_RotY[100];
	char chr_RotZ[100];

	char chr_Total[100];

	char Num[255];
	_itoa(index, Num, 10);

	char buff[255];
	strcpy(buff, App->SBC_Scene->B_Object[index]->Mesh_Name);
	strcat(buff, "   (Object-");
	strcat(buff, Num);
	strcat(buff, ")");


	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	sprintf(chr_Scale, "%.3f", App->SBC_Scene->B_Object[index]->Mesh_Scale.x);

	sprintf(chr_PosX, "%.3f", "2");//CL_Object[index]->MeshPos.x);
	sprintf(chr_PosY, "%.3f", "2");//CL_Object[index]->MeshPos.y);
	sprintf(chr_PosZ, "%.3f", "2");//CL_Object[index]->MeshPos.z);

	sprintf(chr_RotX, "%.3f", "2");//CL_Object[index]->MeshRot.x);
	sprintf(chr_RotY, "%.3f", "2");// CL_Object[index]->MeshRot.y);
	sprintf(chr_RotZ, "%.3f", "2");//CL_Object[index]->MeshRot.z);

	sprintf(chr_Total, "%i", "2");//TotalCollectableCount);


	const int NUM_ITEMS = 4;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = "Mesh File",	grid[1][1] = App->SBC_Scene->B_Object[index]->Mesh_FileName;
	grid[0][2] = " ",			grid[1][2] = " ";
	grid[0][3] = "Scale",		grid[1][3] = chr_Scale;



	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Update_ListView_Player	Terry Bernie 			 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Player()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		//	return 1;
	}

	int index = App->SBC_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Scene->SBC_Base_Player[0]->Player_Name);
	strcat(buff, "   (Player)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_Speed[100];
	char chr_Height[100];
	char chr_StartPosX[100];
	char chr_StartPosY[100];
	char chr_StartPosZ[100];

	sprintf(chr_Speed, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->Ground_speed);
	sprintf(chr_Height, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->PlayerHeight);

	sprintf(chr_StartPosX, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->StartPos.x);
	sprintf(chr_StartPosY, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->StartPos.y);
	sprintf(chr_StartPosZ, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->StartPos.z);

	const int NUM_ITEMS = 9;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name", grid[1][0] = App->SBC_Scene->SBC_Base_Player[0]->Player_Name;
	grid[0][1] = "Mode", grid[1][1] = "1st_Person";
	grid[0][2] = " ", grid[1][2] = " ";
	grid[0][3] = "Ground Speed", grid[1][3] = chr_Speed;
	grid[0][4] = "Player Height", grid[1][4] = chr_Height;
	grid[0][5] = " ", grid[1][5] = " ";
	grid[0][6] = "Start Pos_X", grid[1][6] = chr_StartPosX;
	grid[0][7] = "Start Pos_Y", grid[1][7] = chr_StartPosY;
	grid[0][8] = "Start Pos_Z", grid[1][8] = chr_StartPosZ;


	ListView_DeleteAllItems(App->SBC_Properties->Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(App->SBC_Properties->Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(App->SBC_Properties->Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Update_ListView_Player_Physics	Terry Berni		 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Player_Physics()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		//return 1;
	}

	int index = App->SBC_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Scene->SBC_Base_Player[0]->Player_Name);
	strcat(buff, "   (Physics)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_PhysicsType[100];
	strcpy(chr_PhysicsType, "Dynamic");

	char chr_PhysicsShape[100];
	strcpy(chr_PhysicsShape, "Capsule");

	char chr_Mass[100];
	char chr_Radius[100];
	char chr_Height[100];

	sprintf(chr_Mass, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->Capsule_Mass);
	//sprintf(chr_Mass,"%.3f ",App->GDSBC_Player->mObject->getGravity().getY());
	sprintf(chr_Radius, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->Capsule_Radius);
	sprintf(chr_Height, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->Capsule_Height);


	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name", grid[1][0] = App->SBC_Scene->SBC_Base_Player[0]->Player_Name;
	grid[0][1] = "Type", grid[1][1] = chr_PhysicsType;
	grid[0][2] = "Shape ", grid[1][2] = chr_PhysicsShape;
	grid[0][3] = " ", grid[1][3] = " ";
	grid[0][4] = "Mass", grid[1][4] = chr_Mass;
	grid[0][5] = "Radius", grid[1][5] = chr_Radius;
	grid[0][6] = "Height", grid[1][6] = chr_Height;

	ListView_DeleteAllItems(App->SBC_Properties->Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(App->SBC_Properties->Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(App->SBC_Properties->Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *					Edit_Object_Onclick  Terry Flanigan				   *
// *************************************************************************
bool SB_Properties::Edit_Object_Onclick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object;
	int result = 1;
	int List_Index;

	Base_Object* Object = App->SBC_Scene->B_Object[Index];

	LPNMLISTVIEW List = (LPNMLISTVIEW)lParam;
	List_Index = List->iItem;
	ListView_GetItemText(Properties_hLV, List_Index, 0, btext, 20);

	result = strcmp(App->SBC_Properties->btext, "Name");
	if (result == 0)
	{
		App->SBC_Object->Rename_Object(Index);
		Update_ListView_Objects();
	}

	return 1;
}

// *************************************************************************
// *					Edit_Area_Onclick  Terry Flanigan				   *
// *************************************************************************
bool SB_Properties::Edit_Area_Onclick(LPARAM lParam)
{
	int Index = 0;// App->SBC_Properties->Current_Selected_Object;
	int result = 1;
	int List_Index;

	Base_Area* Area = App->SBC_Scene->SBC_Base_Area[Index];

	LPNMLISTVIEW List = (LPNMLISTVIEW)lParam;
	List_Index = List->iItem;
	ListView_GetItemText(Properties_hLV, List_Index, 0, btext, 20);

	result = strcmp(App->SBC_Properties->btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Area Name");
		strcpy(App->Cl_Dialogs->Chr_Text, Area->Area_Name);

		App->Cl_Dialogs->Dialog_Text(1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		// Needs Duplicate Name test 
		strcpy(Area->Area_Name, App->Cl_Dialogs->Chr_Text);

		App->SBC_FileView->Change_Item_Name(Area->FileViewItem, Area->Area_Name);
		Update_ListView_Area();
	}

	return 1;
}

// *************************************************************************
// *				Edit_Player_Onclick  Terry Bernie					   *
// *************************************************************************
bool SB_Properties::Edit_Player_Onclick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object;
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(App->SBC_Properties->Properties_hLV, test, 0, App->SBC_Properties->btext, 20);

	result = strcmp(App->SBC_Properties->btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Player Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Scene->SBC_Base_Player[0]->Player_Name);

		App->Cl_Dialogs->Dialog_Text(1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		// Needs Duplicate Name test 
		strcpy(App->SBC_Scene->SBC_Base_Player[0]->Player_Name, App->Cl_Dialogs->Chr_Text);

		App->SBC_FileView->Change_Item_Name(App->SBC_Player->FileViewItem, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Player();
	}

	result = strcmp(App->SBC_Properties->btext, "Ground Speed");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->Ground_speed);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Ground Speed");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->SBC_Base_Player[0]->Ground_speed = App->Cl_Dialogs->mFloat;
		Update_ListView_Player();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Player Height");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->PlayerHeight);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Height");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->SBC_Base_Player[0]->PlayerHeight = App->Cl_Dialogs->mFloat;
		Update_ListView_Player();
		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Start Pos_X");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->StartPos.x);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos X");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->SBC_Base_Player[0]->StartPos.x = App->Cl_Dialogs->mFloat;
		Update_ListView_Player();

		App->Cl_Bullet->Reset_Physics();
		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Start Pos_Y");
	if (result == 0)
	{

		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->StartPos.y);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos Y");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->SBC_Base_Player[0]->StartPos.y = App->Cl_Dialogs->mFloat;
	
		App->Cl_Bullet->Reset_Physics();
		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Start Pos_Z");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->StartPos.z);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos Z");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->SBC_Base_Player[0]->StartPos.z = App->Cl_Dialogs->mFloat;
		
		Update_ListView_Player();

		App->Cl_Bullet->Reset_Physics();

		return 1;
	}

	return 1;
}

// *************************************************************************
// *				Edit_Player_Physics_Onclick  Terry Bernie					   *
// *************************************************************************
bool SB_Properties::Edit_Player_Physics_Onclick(LPARAM lParam)
{
	int Index = Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Mass");
	if (result == 0)
	{
		char chr_Radius[10];
		sprintf(chr_Radius, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->Phys_Body->getInvMass());

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Radius);
		strcpy(App->Cl_Dialogs->btext, "Player Physics Mass");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }


		App->SBC_Scene->SBC_Base_Player[0]->Phys_Body->setMassProps(App->Cl_Dialogs->mFloat, btVector3(0, 0, 0));

		App->SBC_Properties->Update_ListView_Player_Physics();

		return 1;
	}

	result = strcmp(btext, "Radius");
	if (result == 0)
	{
		char chr_Radius[10];
		sprintf(chr_Radius, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->Capsule_Radius);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Radius);
		strcpy(App->Cl_Dialogs->btext, "Player Physics Shape Radius");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->SBC_Scene->SBC_Base_Player[0]->Capsule_Radius = App->Cl_Dialogs->mFloat;

		App->SBC_Properties->Update_ListView_Player_Physics();

		App->SBC_Player->Adjust_Capsule();
		return 1;
	}

	result = strcmp(btext, "Height");
	if (result == 0)
	{
		char chr_Height[10];
		sprintf(chr_Height, "%.3f ", App->SBC_Scene->SBC_Base_Player[0]->Capsule_Height);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Height);
		strcpy(App->Cl_Dialogs->btext, "Player Physics Shape Height");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->SBC_Base_Player[0]->Capsule_Height = App->Cl_Dialogs->mFloat;

		App->SBC_Properties->Update_ListView_Player_Physics();

		App->SBC_Player->Adjust_Capsule();
		return 1;
	}
	return 1;
}

// *************************************************************************
// *				Update_ListView_Area	Terry Bernie 			 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Area()
{
	int Index = 0;// Current_Selected_Object; // Get Selected Object Index 

	char buff[255];
	strcpy(buff,"Area ");
	strcat(buff, App->SBC_Scene->SBC_Base_Area[Index]->Area_Name);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	const int NUM_ITEMS = 3;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name", grid[1][0] = App->SBC_Scene->SBC_Base_Area[Index]->Area_Name;
	grid[0][1] = "Mesh File", grid[1][1] = App->SBC_Scene->SBC_Base_Area[Index]->Area_FileName;

	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Update_ListView_Camera	Terry Bernie 			 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Camera()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		//	return 1;
	}

	int index = App->SBC_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Camera->Camera_Name);
	strcat(buff, "   (Camera)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_Pos_X[100];
	char chr_Pos_Y[100];
	char chr_Pos_Z[100];

	char chr_LookAT_X[100];
	char chr_LookAT_Y[100];
	char chr_LookAT_Z[100];
	
	sprintf(chr_Pos_X, "%.3f ", App->SBC_Camera->CamPos_X);
	sprintf(chr_Pos_Y, "%.3f ", App->SBC_Camera->CamPos_Y);
	sprintf(chr_Pos_Z, "%.3f ", App->SBC_Camera->CamPos_Z);

	sprintf(chr_LookAT_X, "%.3f ", App->SBC_Camera->LookAt_X);
	sprintf(chr_LookAT_Y, "%.3f ", App->SBC_Camera->LookAt_Y);
	sprintf(chr_LookAT_Z, "%.3f ", App->SBC_Camera->LookAt_Z);


	const int NUM_ITEMS = 9;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Camera->Camera_Name;
	grid[0][1] = " ",			grid[1][1] = " ";
	grid[0][2] = "Pos_X",		grid[1][2] = chr_Pos_X;
	grid[0][3] = "Pos_Y",		grid[1][3] = chr_Pos_Y;
	grid[0][4] = "Pos_Z",		grid[1][4] = chr_Pos_Z;
	grid[0][5] = " ",			grid[1][5] = " ";
	grid[0][6] = "LookAt_X",	grid[1][6] = chr_LookAT_X;
	grid[0][7] = "LookAt_Y",	grid[1][7] = chr_LookAT_Y;
	grid[0][8] = "LookAt_Z",	grid[1][8] = chr_LookAT_Z;
	

	ListView_DeleteAllItems(App->SBC_Properties->Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(App->SBC_Properties->Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(App->SBC_Properties->Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Edit_Camera_Onclick  Terry Bernie					   *
// *************************************************************************
bool SB_Properties::Edit_Camera_Onclick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(App->SBC_Properties->Properties_hLV, test, 0, App->SBC_Properties->btext, 20);

	result = strcmp(App->SBC_Properties->btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Camera->Camera_Name);

		App->Cl_Dialogs->Dialog_Text(1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		// Needs Duplicate Name test 
		strcpy(App->SBC_Camera->Camera_Name, App->Cl_Dialogs->Chr_Text);

		App->SBC_FileView->Change_Item_Name(App->SBC_Camera->FileViewItem, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Camera();
	}

	result = strcmp(App->SBC_Properties->btext, "Pos_X");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->CamPos_X);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Position X");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->CamPos_X = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Pos_Y");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->CamPos_Y);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Position Y");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->CamPos_Y = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Pos_Z");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->CamPos_Z);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Position Z");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->CamPos_Z = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "LookAt_X");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->LookAt_X);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Look At X");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->LookAt_X = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "LookAt_Y");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->LookAt_Y);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Look At Y");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->LookAt_Y = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}
	
	result = strcmp(App->SBC_Properties->btext, "LookAt_Z");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->LookAt_Z);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Look At Z");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->LookAt_Z = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}

	return 1;
}
