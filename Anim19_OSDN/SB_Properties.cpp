/*
Copyright (c) 2021 EquitySB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

	Edit_Category = Enums::FV_Edit_Object;
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
	CheckMenuItem(mMenu, ID_WINDOWS_PROPERTIES, MF_BYCOMMAND | MF_CHECKED);

	Properties_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_GD_PROPERTIES, App->Fdlg, (DLGPROC)GD_Properties_Proc);
	ShowWindow(Properties_Dlg_hWnd, 1);

	Create_Properties_hLV();

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


		App->SBC_Properties->Edit_Category = Enums::FV_Edit_Object;

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
		
		HMENU mMenu = GetMenu(App->MainHwnd);
		CheckMenuItem(mMenu, ID_WINDOWS_PROPERTIES, MF_BYCOMMAND | MF_UNCHECKED);

		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 0);
		
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
		230, 280, Properties_Dlg_hWnd, 0, App->hInst, NULL);

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
	if (Edit_Category == Enums::FV_Edit_Object)
	{
		if (Edit_Physics == 0)
		{
			Edit_Object_Onclick(lParam);
		}
		return;
	}

	// Messages
	if (Edit_Category == Enums::Edit_Message)
	{
		if (Edit_Physics == 0)
		{
			Edit_Messages_OnClick(lParam);
		}
		return;
	}

	// Messages
	if (Edit_Category == Enums::Edit_Move_Entity)
	{
		if (Edit_Physics == 0)
		{
			Edit_Move_Entity_OnClick(lParam);
		}
		return;
	}

	// Sounds
	if (Edit_Category == Enums::Edit_Sounds)
	{
		if (Edit_Physics == 0)
		{
			Edit_Sounds_OnClick(lParam);
		}
		return;
	}

	// Teleports
	if (Edit_Category == Enums::Edit_Teleport)
	{
		if (Edit_Physics == 0)
		{
			Edit_Teleport_OnClick(lParam);
		}
		return;
	}

	// Collectables
	if (Edit_Category == Enums::Edit_Collectable)
	{
		if (Edit_Physics == 0)
		{
			Edit_Collectables_OnClick(lParam);
		}
		return;
	}

	// Counters
	if (Edit_Category == Enums::Edit_Counters)
	{
		if (Edit_Physics == 0)
		{
			Edit_Counters_OnClick(lParam);
		}
		return;
	}

	return;
}

// *************************************************************************
// *					Mark_As_Altered Terry Bernie				 	   *
// *************************************************************************
void SB_Properties::Mark_As_Altered(int Index)
{
	App->SBC_Scene->B_Object[Index]->Altered = 1;
	App->SBC_Scene->Scene_Modified = 1;
	App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Object[Index]->FileViewItem);
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


	const int NUM_ITEMS = 5;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = "Mesh File",	grid[1][1] = App->SBC_Scene->B_Object[index]->Mesh_FileName;
	grid[0][2] = "Material",	grid[1][2] = App->SBC_Scene->B_Object[index]->Material_File;
	grid[0][3] = " ",			grid[1][3] = " ";
	grid[0][4] = "Scale",		grid[1][4] = chr_Scale;



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
	if (App->SBC_Scene->Scene_Loaded == 0)
	{
		//	return 1;
	}

	int index = App->SBC_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Scene->B_Player[0]->Player_Name);
	strcat(buff, "   (Player)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_Speed[100];
	char chr_TurnRate[100];
	char chr_Height[100];
	char chr_StartPosX[100];
	char chr_StartPosY[100];
	char chr_StartPosZ[100];

	sprintf(chr_Speed, "%.3f ", App->SBC_Scene->B_Player[0]->Ground_speed);
	sprintf(chr_TurnRate, "%.6f ", App->SBC_Scene->B_Player[0]->TurnRate);

	sprintf(chr_Height, "%.3f ", App->SBC_Scene->B_Player[0]->PlayerHeight);

	sprintf(chr_StartPosX, "%.3f ", App->SBC_Scene->B_Player[0]->StartPos.x);
	sprintf(chr_StartPosY, "%.3f ", App->SBC_Scene->B_Player[0]->StartPos.y);
	sprintf(chr_StartPosZ, "%.3f ", App->SBC_Scene->B_Player[0]->StartPos.z);

	const int NUM_ITEMS = 10;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Player[0]->Player_Name;
	grid[0][1] = "Mode",		grid[1][1] = "1st_Person";
	grid[0][2] = " ",			grid[1][2] = " ";
	grid[0][3] = "Ground Speed", grid[1][3] = chr_Speed;
	grid[0][4] = "Turn Rate",	grid[1][4] = chr_TurnRate;
	grid[0][5] = "Player Height", grid[1][5] = chr_Height;
	grid[0][6] = " ",			grid[1][6] = " ";
	grid[0][7] = "Start Pos_X", grid[1][7] = chr_StartPosX;
	grid[0][8] = "Start Pos_Y", grid[1][8] = chr_StartPosY;
	grid[0][9] = "Start Pos_Z", grid[1][9] = chr_StartPosZ;


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
	if (App->SBC_Scene->Scene_Loaded == 0)
	{
		//return 1;
	}

	int index = App->SBC_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Scene->B_Player[0]->Player_Name);
	strcat(buff, "   (Physics)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_PhysicsType[100];
	strcpy(chr_PhysicsType, "Dynamic");

	char chr_PhysicsShape[100];
	strcpy(chr_PhysicsShape, "Capsule");

	char chr_Mass[100];
	char chr_Radius[100];
	char chr_Height[100];

	sprintf(chr_Mass, "%.3f ", App->SBC_Scene->B_Player[0]->Capsule_Mass);
	//sprintf(chr_Mass,"%.3f ",App->GDSBC_Player->mObject->getGravity().getY());
	sprintf(chr_Radius, "%.3f ", App->SBC_Scene->B_Player[0]->Capsule_Radius);
	sprintf(chr_Height, "%.3f ", App->SBC_Scene->B_Player[0]->Capsule_Height);


	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",   grid[1][0] = App->SBC_Scene->B_Player[0]->Player_Name;
	grid[0][1] = "Type",   grid[1][1] = chr_PhysicsType;
	grid[0][2] = "Shape ", grid[1][2] = chr_PhysicsShape;
	grid[0][3] = " ",      grid[1][3] = " ";
	grid[0][4] = "Mass",   grid[1][4] = chr_Mass;
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
// *			Update_ListView_Mesages	Terry Flanigan				 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Messages()
{
	if (App->SBC_Scene->Scene_Loaded == 0)
	{
		return 1;
	}

	int index = App->SBC_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Scene->B_Object[index]->Mesh_Name);
	strcat(buff, "   (Message)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_PosX[20];
	sprintf(chr_PosX, "%.3f ", App->SBC_Scene->B_Object[index]->Message_PosX);

	char chr_PosY[20];
	sprintf(chr_PosY, "%.3f ", App->SBC_Scene->B_Object[index]->Message_PosY);


	const int NUM_ITEMS = 5;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",            grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = " ",               grid[1][1] = " ";
	grid[0][2] = "Pos_X",           grid[1][2] = chr_PosX;
	grid[0][3] = "Pos_Y",           grid[1][3] = chr_PosY;
	grid[0][4] = "Text",            grid[1][4] = App->SBC_Scene->B_Object[index]->Message_Text;
	
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
// *			Update_ListView_Sounds:- Terry and Hazel Flanigan 2022     *
// *************************************************************************
bool SB_Properties::Update_ListView_Sounds()
{
	if (App->SBC_Scene->Scene_Loaded == 0)
	{
		return 1;
	}

	int index = Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Scene->B_Object[index]->Mesh_Name);
	strcat(buff, "   (Sound)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);


	char chr_Volume[100];
	float sum2 = App->SBC_Scene->B_Object[index]->SndVolume;
	int Percent = int(sum2 * 100);
	_itoa(Percent, chr_Volume, 10);

	const int NUM_ITEMS = 4;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",	grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = " ",		grid[1][1] = " ";
	grid[0][2] = "Sound",	grid[1][2] = App->SBC_Scene->B_Object[index]->Sound_File;
	grid[0][3] = "Volume",  grid[1][3] = chr_Volume;


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

// **************************************************************************
// *		Update_ListView_Teleport():- Terry and Hazel Flanigan 2022		*
// **************************************************************************
bool SB_Properties::Update_ListView_Teleport()
{
	int index = App->SBC_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Scene->B_Object[index]->Mesh_Name);
	strcat(buff, "   (Teleport)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	// new sound
	char chr_Play[100];
	if (App->SBC_Scene->B_Object[index]->S_Teleport[0]->Play == 1)
	{
		strcpy(chr_Play, "True");
	}
	else
	{
		strcpy(chr_Play, "False");
	}

	char chr_Volume[100];
	float sum2 = App->SBC_Scene->B_Object[index]->S_Teleport[0]->SndVolume;
	int Percent = int(sum2 * 100);
	_itoa(Percent, chr_Volume, 10);

	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = " ",			grid[1][1] = " ";
	grid[0][2] = "Goto",		grid[1][2] = App->SBC_Scene->B_Object[index]->S_Teleport[0]->Name;
	grid[0][3] = " ",			grid[1][3] = " ";
	grid[0][4] = "Sound",		grid[1][4] = App->SBC_Scene->B_Object[index]->S_Teleport[0]->Sound_File;
	grid[0][5] = "Volume",		grid[1][5] = chr_Volume;
	grid[0][6] = "Play",		grid[1][6] = chr_Play;


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
// *	Update_ListView_Collectables():- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Collectables()
{
	int index = App->SBC_Properties->Current_Selected_Object;


	char buff[255];
	strcpy(buff, App->SBC_Scene->B_Object[index]->Mesh_Name);
	strcat(buff, "   (Collectable)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);
	
	// new sound
	char chr_Play[100];
	if (App->SBC_Scene->B_Object[index]->S_Collectable[0]->Play == 1)
	{
		strcpy(chr_Play, "True");
	}
	else
	{
		strcpy(chr_Play, "False");
	}

	char chr_Volume[100];
	float sum2 = App->SBC_Scene->B_Object[index]->S_Collectable[0]->SndVolume;
	int Percent = int(sum2 * 100);
	_itoa(Percent, chr_Volume, 10);

	char chr_CounterID[100];
	_itoa(App->SBC_Scene->B_Object[index]->S_Collectable[0]->Counter_ID, chr_CounterID, 10);

	char chr_Value[100];
	_itoa(App->SBC_Scene->B_Object[index]->S_Collectable[0]->Value, chr_Value, 10);

	char chr_Maths[20];
	if (App->SBC_Scene->B_Object[index]->S_Collectable[0]->Maths == 1)
	{
		strcpy(chr_Maths, "Add");
	}
	else
	{
		strcpy(chr_Maths, "Subtract");
	}

	const int NUM_ITEMS = 11;
	const int NUM_COLS = 2;
	string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",			grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = "Mesh File",		grid[1][1] = App->SBC_Scene->B_Object[index]->Mesh_FileName;
	grid[0][2] = " ",				grid[1][2] = " ";
	grid[0][3] = "Sound",			grid[1][3] = App->SBC_Scene->B_Object[index]->S_Collectable[0]->Sound_File;
	grid[0][4] = "Volume",			grid[1][4] = chr_Volume;
	grid[0][5] = "Play",			grid[1][5] = chr_Play;
	grid[0][6] = " ",				grid[1][6] = " ";
	grid[0][7] = "Counter",			grid[1][7] = App->SBC_Scene->B_Object[index]->S_Collectable[0]->Counter_Name;
	grid[0][8] = "ID",				grid[1][8] = chr_CounterID;
	grid[0][9] = "Maths",			grid[1][9] = chr_Maths;
	grid[0][10] = "Value",			grid[1][10] = chr_Value;


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
// *		Update_ListView_Counters():- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Counters()
{
	int index = App->SBC_Properties->Current_Selected_Object;


	char buff[255];
	strcpy(buff, App->SBC_Scene->B_Counter[index]->Panel_Name);
	strcat(buff, "   (Counters)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_PosX[20];
	sprintf(chr_PosX, "%.3f ", App->SBC_Scene->B_Counter[index]->PosX);

	char chr_PosY[20];
	sprintf(chr_PosY, "%.3f ", App->SBC_Scene->B_Counter[index]->PosY);

	char chr_Counter[20];
	_itoa(App->SBC_Scene->B_Counter[index]->Counter, chr_Counter, 10);

	char chr_Display[20];
	if (App->SBC_Scene->B_Counter[index]->Show_Panel_Flag == 1)
	{
		strcpy(chr_Display, "Always");
	}
	else
	{
		strcpy(chr_Display, "Auto");
	}

	
	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Counter[index]->Panel_Name;
	grid[0][1] = " ",			grid[1][1] = " ";
	grid[0][2] = "Pos_X",		grid[1][2] = chr_PosX;
	grid[0][3] = "Pos_Y",		grid[1][3] = chr_PosY;
	grid[0][4] = "Text",		grid[1][4] = App->SBC_Scene->B_Counter[index]->Text;
	grid[0][5] = "Start_Value",	grid[1][5] = chr_Counter;
	grid[0][6] = "Display",		grid[1][6] = chr_Display;


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
// *	Update_ListView_Move_Entities:- Terry and Hazel Flanigan 2022 	    *
// *************************************************************************
bool SB_Properties::Update_ListView_Move_Entities()
{
	if (App->SBC_Scene->Scene_Loaded == 0)
	{
		return 1;
	}

	int index = App->SBC_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Scene->B_Object[index]->Mesh_Name);
	strcat(buff, "   (Mover)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_Distance[100];
	sprintf(chr_Distance, "%.3f ", App->SBC_Scene->B_Object[index]->S_MoveType[0]->Move_Distance);

	char chr_Speed[100];
	sprintf(chr_Speed, "%.3f ", App->SBC_Scene->B_Object[index]->S_MoveType[0]->Speed);

	char chr_Axis[100];
	if (App->SBC_Scene->B_Object[index]->S_MoveType[0]->WhatDirection == Enums::Axis_x)
	{
		strcpy(chr_Axis, "X");
	}
	if (App->SBC_Scene->B_Object[index]->S_MoveType[0]->WhatDirection == Enums::Axis_y)
	{
		strcpy(chr_Axis, "Y");
	}
	if (App->SBC_Scene->B_Object[index]->S_MoveType[0]->WhatDirection == Enums::Axis_z)
	{
		strcpy(chr_Axis, "Z");
	}

	// new sound
	char chr_Play[100];
	if (App->SBC_Scene->B_Object[index]->Play_Sound == 1)
	{
		strcpy(chr_Play, "True");
	}
	else
	{
		strcpy(chr_Play, "False");
	}

	char chr_Object_Name[100];
	strcpy(chr_Object_Name, App->SBC_Scene->B_Object[App->SBC_Scene->B_Object[index]->S_MoveType[0]->Object_To_Move_Index]->Mesh_Name);


	char chr_Selected_Object_Id[100];
	_itoa(App->SBC_Scene->B_Object[index]->S_MoveType[0]->Object_To_Move_Index, chr_Selected_Object_Id, 10);

	char chr_Trigger_Value[100];
	_itoa(App->SBC_Scene->B_Object[index]->S_MoveType[0]->Trigger_Value, chr_Trigger_Value, 10);

	char chr_Volume[100];
	float sum2 = App->SBC_Scene->B_Object[index]->SndVolume;
	int Percent = int(sum2 * 100);
	_itoa(Percent, chr_Volume, 10);


	char chr_Stock_Sound[100];
	int sndIndex = 0;// App->SBC_Scene->B_Object[index]->Sound_ID_v2;
	strcpy(chr_Stock_Sound, "poo");// App->Cl_Scene_Data->St_Sounds[sndIndex]->Name);

	const int NUM_ITEMS = 13;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = " ",			grid[1][1] = " ";
	grid[0][2] = "Move_Object",		grid[1][2] = chr_Object_Name;
	grid[0][3] = "ID_Num",		grid[1][3] = chr_Selected_Object_Id;
	grid[0][4] = "Axis",		grid[1][4] = chr_Axis;
	grid[0][5] = "Distance",	grid[1][5] = chr_Distance;
	grid[0][6] = "Speed",		grid[1][6] = chr_Speed;
	grid[0][7] = " ",			grid[1][7] = " ";
	grid[0][8] = "Sound",		grid[1][8] = App->SBC_Scene->B_Object[index]->Sound_File;
	grid[0][9] = "Volume",		grid[1][9] = chr_Volume;
	grid[0][10] = "Play",		grid[1][10] = chr_Play;
	grid[0][11] = " ",			grid[1][11] = " ";
	grid[0][12] = "Trigger_Val", grid[1][12] = chr_Trigger_Value;



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
// *			Update_ListView_Level:- Terry and Hazel Flanigan 2022     *
// *************************************************************************
bool SB_Properties::Update_ListView_Level()
{
	/*if (App->SBC_Scene->Scene_Loaded == 0)
	{
		return 1;
	}*/

	char buff[255];
	strcpy(buff, App->SBC_Project->m_Level_Name);
	strcat(buff, "   (Level)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char strCamCount[20];
	
	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",			grid[1][0] = App->SBC_Project->m_Level_Name;
	grid[0][1] = " ",				grid[1][1] = " ";
	grid[0][2] = "Cameras",			grid[1][2] = _itoa(App->SBC_Scene->Camera_Count, strCamCount, 10);
	grid[0][3] = "Players",			grid[1][3] = _itoa(App->SBC_Scene->Player_Count, strCamCount, 10);
	grid[0][4] = "Areas",			grid[1][4] = _itoa(App->SBC_Scene->Area_Count, strCamCount, 10);
	grid[0][5] = "Objects",			grid[1][5] = _itoa(App->SBC_LookUps->Get_Adjusted_Object_Count(), strCamCount, 10);
	grid[0][6] = "Counters",		grid[1][6] = _itoa(App->SBC_LookUps->Get_Adjusted_Counters_Count(), strCamCount, 10);
	//grid[0][7] = "Text Messages",   grid[1][7] = _itoa(App->SBC_Scene->TextMessage_Count, strCamCount, 10);


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

	Base_Area* Area = App->SBC_Scene->B_Area[Index];

	LPNMLISTVIEW List = (LPNMLISTVIEW)lParam;
	List_Index = List->iItem;
	ListView_GetItemText(Properties_hLV, List_Index, 0, btext, 20);

	result = strcmp(App->SBC_Properties->btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Area Name");
		strcpy(App->Cl_Dialogs->Chr_Text, Area->Area_Name);

		App->Cl_Dialogs->Dialog_Text(1, 1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		// Needs Duplicate Name test 
		strcpy(Area->Area_Name, App->Cl_Dialogs->Chr_Text);

		Area->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(Area->FileViewItem);

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
		strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Scene->B_Player[0]->Player_Name);

		App->Cl_Dialogs->Dialog_Text(1, 1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		// Needs Duplicate Name test 
		strcpy(App->SBC_Scene->B_Player[0]->Player_Name, App->Cl_Dialogs->Chr_Text);

		App->SBC_Scene->B_Player[0]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		App->SBC_FileView->Change_Item_Name(App->SBC_Scene->B_Player[0]->FileViewItem, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Player();
	}

	result = strcmp(App->SBC_Properties->btext, "Ground Speed");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->B_Player[0]->Ground_speed);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Ground Speed");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) 
		{ 
			return TRUE; 
		}

		App->SBC_Scene->B_Player[0]->Ground_speed = App->Cl_Dialogs->mFloat;

		App->SBC_Scene->B_Player[0]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		Update_ListView_Player();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Turn Rate");
	if (result == 0)
	{
		
		char chr_Value[10];
		sprintf(chr_Value, "%.6f ", App->SBC_Scene->B_Player[0]->TurnRate);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Ground Speed");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->SBC_Scene->B_Player[0]->TurnRate = App->Cl_Dialogs->mFloat;

		App->SBC_Scene->B_Player[0]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		Update_ListView_Player();

		return 1;
	}
	
	result = strcmp(App->SBC_Properties->btext, "Player Height");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->B_Player[0]->PlayerHeight);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Height");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->B_Player[0]->PlayerHeight = App->Cl_Dialogs->mFloat;

		App->SBC_Scene->B_Player[0]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		Update_ListView_Player();
		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Start Pos_X");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->B_Player[0]->StartPos.x);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos X");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->B_Player[0]->StartPos.x = App->Cl_Dialogs->mFloat;
		
		App->SBC_Physics->Reset_Physics();

		App->SBC_Scene->B_Player[0]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		Update_ListView_Player();
		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Start Pos_Y");
	if (result == 0)
	{

		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->B_Player[0]->StartPos.y);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos Y");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->B_Player[0]->StartPos.y = App->Cl_Dialogs->mFloat;
	
		App->SBC_Physics->Reset_Physics();

		App->SBC_Scene->B_Player[0]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		Update_ListView_Player();
		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Start Pos_Z");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->B_Player[0]->StartPos.z);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos Z");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->B_Player[0]->StartPos.z = App->Cl_Dialogs->mFloat;
		
		App->SBC_Physics->Reset_Physics();

		App->SBC_Scene->B_Player[0]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		Update_ListView_Player();

		return 1;
	}

	return 1;
}

// *************************************************************************
// *				Edit_Messages_OnClick  Terry Bernie					   *
// *************************************************************************
bool SB_Properties::Edit_Messages_OnClick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	// Name
	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Scene->B_Object[Index]->Mesh_Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects, 1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, App->Cl_Dialogs->Chr_Text);

		App->SBC_Properties->Mark_As_Altered(Index);

		App->SBC_FileView->Change_Item_Name(App->SBC_Scene->B_Object[Index]->FileViewItem, App->Cl_Dialogs->Chr_Text);

		Update_ListView_Messages();
	}

	result = strcmp(btext, "Text");
	if (result == 0)
	{
		strcpy(App->SBC_Dialogs->btext, "Change Text");
		strcpy(App->SBC_Dialogs->Chr_Text, App->SBC_Scene->B_Object[Index]->Message_Text);

		App->SBC_Dialogs->Dialog_Text();

		if (App->SBC_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->SBC_Scene->B_Object[Index]->Message_Text, App->SBC_Dialogs->Chr_Text);

		App->SBC_Properties->Mark_As_Altered(Index);

		Update_ListView_Messages();

		return 1;
	}

	result = strcmp(btext, "Pos_X");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set Position X");

		char buff[256];
		sprintf(buff, "%.3f", App->SBC_Scene->B_Object[Index]->Message_PosX);
		strcpy(App->Cl_Dialogs->Chr_Float, buff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{

			App->SBC_Scene->B_Object[Index]->Message_PosX = App->Cl_Dialogs->mFloat;

			App->SBC_Properties->Mark_As_Altered(Index);

			Update_ListView_Messages();

		}

		return 1;
	}

	result = strcmp(btext, "Pos_Y");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set Position Y");

		char buff[256];
		sprintf(buff, "%.3f", App->SBC_Scene->B_Object[Index]->Message_PosY);
		strcpy(App->Cl_Dialogs->Chr_Float, buff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{

			App->SBC_Scene->B_Object[Index]->Message_PosY = App->Cl_Dialogs->mFloat;

			App->SBC_Properties->Mark_As_Altered(Index);

			Update_ListView_Messages();

		}

	}

	return 1;
}

// *************************************************************************
// *				Edit_Player_Physics_Onclick  Terry Bernie			   *
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
		sprintf(chr_Radius, "%.3f ", App->SBC_Scene->B_Player[0]->Phys_Body->getInvMass());

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Radius);
		strcpy(App->Cl_Dialogs->btext, "Player Physics Mass");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }


		App->SBC_Scene->B_Player[0]->Phys_Body->setMassProps(App->Cl_Dialogs->mFloat, btVector3(0, 0, 0));

		App->SBC_Scene->B_Player[0]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		App->SBC_Properties->Update_ListView_Player_Physics();

		return 1;
	}

	result = strcmp(btext, "Radius");
	if (result == 0)
	{
		char chr_Radius[10];
		sprintf(chr_Radius, "%.3f ", App->SBC_Scene->B_Player[0]->Capsule_Radius);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Radius);
		strcpy(App->Cl_Dialogs->btext, "Player Physics Shape Radius");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->SBC_Scene->B_Player[0]->Capsule_Radius = App->Cl_Dialogs->mFloat;

		App->SBC_Player->Adjust_Capsule();

		App->SBC_Scene->B_Player[0]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		App->SBC_Properties->Update_ListView_Player_Physics();
		return 1;
	}

	result = strcmp(btext, "Height");
	if (result == 0)
	{
		char chr_Height[10];
		sprintf(chr_Height, "%.3f ", App->SBC_Scene->B_Player[0]->Capsule_Height);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Height);
		strcpy(App->Cl_Dialogs->btext, "Player Physics Shape Height");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->B_Player[0]->Capsule_Height = App->Cl_Dialogs->mFloat;

		App->SBC_Player->Adjust_Capsule();

		App->SBC_Scene->B_Player[0]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		App->SBC_Properties->Update_ListView_Player_Physics();

		return 1;
	}
	return 1;
}

// *************************************************************************
// *				Edit_Move_Entity_OnClick  Terry Bernie					   *
// *************************************************************************
bool SB_Properties::Edit_Move_Entity_OnClick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Scene->B_Object[Index]->Mesh_Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects, 1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, App->Cl_Dialogs->Chr_Text);

		Mark_As_Altered(Index);
		
		App->SBC_FileView->Change_Item_Name(App->SBC_Scene->B_Object[Index]->FileViewItem, App->Cl_Dialogs->Chr_Text);

		Update_ListView_Move_Entities();

		App->SBC_Physics->Reset_Triggers();
	} 



	result = strcmp(btext, "Move_Object");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Select Object to Move");
		strcpy(App->SBC_Dialogs->Chr_DropText, App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Object_Name);

		App->SBC_Dialogs->DropList_Data = Enums::DropDialog_TrigMoveObject;
		App->SBC_Dialogs->Dialog_DropGen();


		if (App->SBC_Dialogs->Canceled == 0)
		{
			strcpy(App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Object_Name, App->SBC_Dialogs->Chr_DropText);

			int MoveObjectIndex = App->SBC_Object->GetIndex_By_Name(App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Object_Name);

			App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Object_To_Move_Index = MoveObjectIndex;

			App->SBC_Scene->B_Object[Index]->S_MoveType[0]->MeshPos.x = App->SBC_Scene->B_Object[MoveObjectIndex]->Mesh_Pos.x;
			App->SBC_Scene->B_Object[Index]->S_MoveType[0]->MeshPos.y = App->SBC_Scene->B_Object[MoveObjectIndex]->Mesh_Pos.y;
			App->SBC_Scene->B_Object[Index]->S_MoveType[0]->MeshPos.z = App->SBC_Scene->B_Object[MoveObjectIndex]->Mesh_Pos.z;

			App->SBC_Scene->B_Object[Index]->S_MoveType[0]->PhysicsPos.x = App->SBC_Scene->B_Object[MoveObjectIndex]->Physics_Pos.x;
			App->SBC_Scene->B_Object[Index]->S_MoveType[0]->PhysicsPos.y = App->SBC_Scene->B_Object[MoveObjectIndex]->Physics_Pos.y;
			App->SBC_Scene->B_Object[Index]->S_MoveType[0]->PhysicsPos.z = App->SBC_Scene->B_Object[MoveObjectIndex]->Physics_Pos.z;

			Mark_As_Altered(Index);

			Update_ListView_Move_Entities();

			App->SBC_Physics->Reset_Triggers();

		}
		return 1;
	}

	result = strcmp(btext, "Axis");
	if (result == 0)
	{
		int TestChr = 1;
		strcpy(App->Cl_Dialogs->btext, "Select Axis ( World )");

		if (App->SBC_Scene->B_Object[Index]->S_MoveType[0]->WhatDirection == Enums::Axis_x)
		{
			strcpy(App->SBC_Dialogs->Chr_DropText,"X");
		}

		if (App->SBC_Scene->B_Object[Index]->S_MoveType[0]->WhatDirection == Enums::Axis_y)
		{
			strcpy(App->SBC_Dialogs->Chr_DropText, "Y");
		}

		if (App->SBC_Scene->B_Object[Index]->S_MoveType[0]->WhatDirection == Enums::Axis_z)
		{
			strcpy(App->SBC_Dialogs->Chr_DropText, "Z");
		}

		App->SBC_Dialogs->DropList_Data = Enums::DropDialog_TrigMoveAxis;
		App->SBC_Dialogs->Dialog_DropGen();

		if (App->SBC_Dialogs->Canceled == 0)
		{

			// X Axis
			TestChr = strcmp(App->SBC_Dialogs->Chr_DropText, "X");
			if (TestChr == 0)
			{
				App->SBC_Scene->B_Object[Index]->S_MoveType[0]->WhatDirection = Enums::Axis_x;

			}

			// y Axis
			TestChr = strcmp(App->SBC_Dialogs->Chr_DropText, "Y");
			if (TestChr == 0)
			{
				App->SBC_Scene->B_Object[Index]->S_MoveType[0]->WhatDirection = Enums::Axis_y;

			}

			// Z Axis
			TestChr = strcmp(App->SBC_Dialogs->Chr_DropText, "Z");
			if (TestChr == 0)
			{
				App->SBC_Scene->B_Object[Index]->S_MoveType[0]->WhatDirection = Enums::Axis_z;
			}

			Mark_As_Altered(Index);

			Update_ListView_Move_Entities();

			App->SBC_Physics->Reset_Triggers();
		}
		return 1;
	}


	result = strcmp(btext, "Distance");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set Offset Distance");

		char buff[256];

		sprintf(buff, "%f", App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Move_Distance);
		strcpy(App->Cl_Dialogs->Chr_Float, buff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{

			if (App->Cl_Dialogs->mFloat < 0)
			{
				App->SBC_Scene->B_Object[Index]->S_MoveType[0]->IsNegative = true;
			}
			else
			{
				App->SBC_Scene->B_Object[Index]->S_MoveType[0]->IsNegative = false;
			}

			App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Move_Distance = App->Cl_Dialogs->mFloat;

			Mark_As_Altered(Index);

			Update_ListView_Move_Entities();

			App->SBC_Physics->Reset_Triggers();
		}

		return 1;
	}

	result = strcmp(btext, "Speed");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set Movment Speed");

		char buff[256];
		sprintf(buff, "%f", App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Speed);
		strcpy(App->Cl_Dialogs->Chr_Float, buff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{

			App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Speed = App->Cl_Dialogs->mFloat;

			Mark_As_Altered(Index);

			Update_ListView_Move_Entities();
			App->SBC_Physics->Reset_Triggers();
		}

		return 1;
	}

	result = strcmp(btext, "Volume");
	if (result == 0)
	{

		App->SBC_SoundMgr->Dialog_SoundFile();

		strcpy(App->SBC_Scene->B_Object[Index]->Sound_File, App->SBC_SoundMgr->m_Current_Sound_file);

		App->SBC_Scene->B_Object[Index]->SndVolume = App->SBC_SoundMgr->SndVolume;

		Mark_As_Altered(Index);

		Update_ListView_Move_Entities();

		App->SBC_Physics->Reset_Triggers();

		return 1;
	}


	//Sound
	result = strcmp(btext, "Sound");
	if (result == 0)
	{
		App->SBC_SoundMgr->Accessed = 1;
		strcpy(App->SBC_SoundMgr->Access_File, App->SBC_Scene->B_Object[Index]->Sound_File);

		App->SBC_SoundMgr->Dialog_SoundFile();

		strcpy(App->SBC_Scene->B_Object[Index]->Sound_File, App->SBC_SoundMgr->Access_File);

		App->SBC_Scene->B_Object[Index]->SndVolume = App->SBC_SoundMgr->SndVolume;

		Mark_As_Altered(Index);

		Update_ListView_Move_Entities();

		App->SBC_Physics->Reset_Triggers();

		return 1;
	}

	// Play
	result = strcmp(btext, "Play");
	if (result == 0)
	{

		strcpy(App->Cl_Dialogs->btext, "Play Sound In The Game");

		App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Index]->Play_Sound;

		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if (App->Cl_Dialogs->TrueFlase == 1)
			{
				App->SBC_Scene->B_Object[Index]->Play_Sound = 1;
			}
			else
			{
				App->SBC_Scene->B_Object[Index]->Play_Sound = 0;

			}
		}

		Mark_As_Altered(Index);

		Update_ListView_Move_Entities();

		App->SBC_Physics->Reset_Triggers();
		return 1;
	}

	// Trigger_Val
	result = strcmp(btext, "Trigger_Val");
	if (result == 0)
	{
		App->SBC_Dialogs->Dialog_Counter();


		/*strcpy(App->Cl_Dialogs->btext, "Trigger Value");

		char buff[256];
		sprintf(buff, "%i", App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Trigger_Value);
		strcpy(App->Cl_Dialogs->Chr_Int, buff);

		App->Cl_Dialogs->Dialog_Int();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->SBC_Scene->B_Object[Index]->S_MoveType[0]->Trigger_Value = App->Cl_Dialogs->mInt;*/

		Mark_As_Altered(Index);

		Update_ListView_Move_Entities();

		App->SBC_Physics->Reset_Triggers();
		return 1;
	}

	return 1;
}

// *************************************************************************
// *				Edit_Collectables_OnClick  Terry Bernie				   *
// *************************************************************************
bool SB_Properties::Edit_Collectables_OnClick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->SBC_Dialogs->btext, "Change Object Name");
		strcpy(App->SBC_Dialogs->Chr_Text, App->SBC_Scene->B_Object[Index]->Mesh_Name);

		App->SBC_Dialogs->Dialog_Text();

		if (App->SBC_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, App->SBC_Dialogs->Chr_Text);


		Mark_As_Altered(Index);
		App->SBC_FileView->Change_Item_Name(App->SBC_Scene->B_Object[Index]->FileViewItem, App->SBC_Dialogs->Chr_Text);

		Update_ListView_Collectables();

		App->SBC_Physics->Reset_Triggers();
	}

	result = strcmp(btext, "Volume");
	if (result == 0)
	{

		App->SBC_SoundMgr->Accessed = 1;
		strcpy(App->SBC_SoundMgr->Access_File, App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Sound_File);

		App->SBC_SoundMgr->Dialog_SoundFile();

		strcpy(App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Sound_File, App->SBC_SoundMgr->Access_File);

		App->SBC_Scene->B_Object[Index]->S_Collectable[0]->SndVolume = App->SBC_SoundMgr->SndVolume;

		Mark_As_Altered(Index);

		Update_ListView_Collectables();

		App->SBC_Physics->Reset_Triggers();

		return 1;
	}


	//Sound
	result = strcmp(btext, "Sound");
	if (result == 0)
	{
		App->SBC_SoundMgr->Accessed = 1;
		strcpy(App->SBC_SoundMgr->Access_File, App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Sound_File);

		App->SBC_SoundMgr->Dialog_SoundFile();

		strcpy(App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Sound_File, App->SBC_SoundMgr->Access_File);

		App->SBC_Scene->B_Object[Index]->S_Collectable[0]->SndVolume = App->SBC_SoundMgr->SndVolume;

		Mark_As_Altered(Index);

		Update_ListView_Collectables();

		App->SBC_Physics->Reset_Triggers();

		return 1;
	}

	// Play
	result = strcmp(btext, "Play");
	if (result == 0)
	{

		strcpy(App->Cl_Dialogs->btext, "Play Sound In The Game");

		App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Play;

		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if (App->Cl_Dialogs->TrueFlase == 1)
			{
				App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Play = 1;
			}
			else
			{
				App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Play = 0;

			}
		}

		Mark_As_Altered(Index);

		Update_ListView_Collectables();

		App->SBC_Physics->Reset_Triggers();
		return 1;
	}

	result = strcmp(btext, "Counter");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Select Counter");

		strcpy(App->SBC_Dialogs->Chr_DropText, App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Name);

		App->SBC_Dialogs->DropList_Data = Enums::DropDialog_Counters;
		App->SBC_Dialogs->Dialog_DropGen();


		if (App->SBC_Dialogs->Canceled == 0)
		{
			strcpy(App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_Name, App->SBC_Dialogs->Chr_DropText);

			int CounterIndex = App->SBC_Display->GetIndex_By_Name(App->SBC_Dialogs->Chr_DropText);

			App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Counter_ID = CounterIndex;

			Mark_As_Altered(Index);
			Update_ListView_Collectables();
			App->SBC_Physics->Reset_Triggers();

		}
		return 1;
	}

	result = strcmp(btext, "Maths");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set Maths Option");

		if (App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths == 1)
		{
			strcpy(App->SBC_Dialogs->Chr_DropText, "Add");
		}

		if (App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths == 2)
		{
			strcpy(App->SBC_Dialogs->Chr_DropText, "Subtract");
		}

		App->SBC_Dialogs->DropList_Data = Enums::DropDialog_Maths;
		App->SBC_Dialogs->Dialog_DropGen();

		if (App->SBC_Dialogs->Canceled == 0)
		{
			int TestChr;

			// Add
			TestChr = strcmp(App->SBC_Dialogs->Chr_DropText, "Add");
			if (TestChr == 0)
			{
				App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths = 1;

			}

			// Subtract
			TestChr = strcmp(App->SBC_Dialogs->Chr_DropText, "Subtract");
			if (TestChr == 0)
			{
				App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Maths = 2;

			}

			Mark_As_Altered(Index);
			Update_ListView_Collectables();
			App->SBC_Physics->Reset_Triggers();
		}

		return 1;
	}

	result = strcmp(btext, "Value");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Collectable Value");
		char buff[256];
		sprintf(buff, "%i", App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Value);
		strcpy(App->Cl_Dialogs->Chr_Int, buff);

		App->Cl_Dialogs->Dialog_Int();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->SBC_Scene->B_Object[Index]->S_Collectable[0]->Value = App->Cl_Dialogs->mInt;

		Mark_As_Altered(Index);
		Update_ListView_Collectables();
		App->SBC_Physics->Reset_Triggers();

		return 1;
	}

	return 1;
}

// *************************************************************************
// *		Edit_Counters_OnClick:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Properties::Edit_Counters_OnClick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		App->SBC_Display->Rename_Counter(Index);
		Update_ListView_Counters();
	}

	result = strcmp(btext, "Pos_X");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set Position X");

		char buff[256];
		sprintf(buff, "%.3f", App->SBC_Scene->B_Counter[Index]->PosX);
		strcpy(App->Cl_Dialogs->Chr_Float, buff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{

			App->SBC_Scene->B_Counter[Index]->PosX = App->Cl_Dialogs->mFloat;

			App->SBC_Display->Mark_As_Altered_Counter(Index);

			Update_ListView_Counters();
	
		}

		return 1;
	}

	result = strcmp(btext, "Pos_Y");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Set Position Y");

		char buff[256];
		sprintf(buff, "%.3f", App->SBC_Scene->B_Counter[Index]->PosY);
		strcpy(App->Cl_Dialogs->Chr_Float, buff);

		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{

			App->SBC_Scene->B_Counter[Index]->PosY = App->Cl_Dialogs->mFloat;

			App->SBC_Display->Mark_As_Altered_Counter(Index);

			Update_ListView_Counters();

		}

		return 1;
	}

	result = strcmp(btext, "Text");
	if (result == 0)
	{
		strcpy(App->SBC_Dialogs->btext, "Change Text");
		strcpy(App->SBC_Dialogs->Chr_Text, App->SBC_Scene->B_Counter[Index]->Text);

		App->SBC_Dialogs->Dialog_Text();

		if (App->SBC_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->SBC_Scene->B_Counter[Index]->Text, App->SBC_Dialogs->Chr_Text);


		App->SBC_Display->Mark_As_Altered_Counter(Index);
		
		Update_ListView_Counters();

		return 1;
	}

	result = strcmp(btext, "Start_Value");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Start Value");
		char buff[256];
		sprintf(buff, "%i", App->SBC_Scene->B_Counter[Index]->Start_Value);
		strcpy(App->Cl_Dialogs->Chr_Int, buff);

		App->Cl_Dialogs->Dialog_Int();

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		App->SBC_Scene->B_Counter[Index]->Start_Value = App->Cl_Dialogs->mInt;
		App->SBC_Scene->B_Counter[Index]->Counter = App->Cl_Dialogs->mInt;

		App->SBC_Display->Mark_As_Altered_Counter(Index);

		Update_ListView_Counters();

		return 1;
	}

	result = strcmp(btext, "Display");
	if (result == 0)
	{
		
		strcpy(App->Cl_Dialogs->btext, "Select Display Option");

		if (App->SBC_Scene->B_Counter[Index]->Show_Panel_Flag == 0)
		{
			strcpy(App->SBC_Dialogs->Chr_DropText, "Auto");
		}

		if (App->SBC_Scene->B_Counter[Index]->Show_Panel_Flag == 1)
		{
			strcpy(App->SBC_Dialogs->Chr_DropText, "Always");
		}

		App->SBC_Dialogs->DropList_Data = Enums::DropDialog_Display;
		App->SBC_Dialogs->Dialog_DropGen();


		if (App->SBC_Dialogs->Canceled == 0)
		{
			int TestChr = 0;

			// Auto
			TestChr = strcmp(App->SBC_Dialogs->Chr_DropText, "Auto");
			if (TestChr == 0)
			{
				App->SBC_Scene->B_Counter[Index]->Show_Panel_Flag = 0;
			}

			// Always
			TestChr = strcmp(App->SBC_Dialogs->Chr_DropText, "Always");
			if (TestChr == 0)
			{
				App->SBC_Scene->B_Counter[Index]->Show_Panel_Flag = 1;
			}

			App->SBC_Display->Mark_As_Altered_Counter(Index);
			Update_ListView_Counters();

		}

		return 1;
	}

	return 1;
}


// *************************************************************************
// *		Update_ListView_Area:- Terry and Hazel Flanigan 2022	 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Area()
{
	int Index = 0;// Current_Selected_Object; // Get Selected Object Index 

	char buff[255];
	strcpy(buff,"Area ");
	strcat(buff, App->SBC_Scene->B_Area[Index]->Area_Name);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	const int NUM_ITEMS = 3;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Area[Index]->Area_Name;
	grid[0][1] = "Mesh File",	grid[1][1] = App->SBC_Scene->B_Area[Index]->Area_FileName;
	grid[0][2] = "Material",	grid[1][2] = App->SBC_Scene->B_Area[Index]->Material_File;

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
	if (App->SBC_Scene->Scene_Loaded == 0)
	{
		//	return 1;
	}

	int Index = App->SBC_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Scene->B_Camera[Index]->Camera_Name);
	strcat(buff, "   (Camera)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_Pos_X[100];
	char chr_Pos_Y[100];
	char chr_Pos_Z[100];

	char chr_LookAT_X[100];
	char chr_LookAT_Y[100];
	char chr_LookAT_Z[100];
	
	sprintf(chr_Pos_X, "%.3f ", App->SBC_Scene->B_Camera[Index]->CamPos.x);
	sprintf(chr_Pos_Y, "%.3f ", App->SBC_Scene->B_Camera[Index]->CamPos.y);
	sprintf(chr_Pos_Z, "%.3f ", App->SBC_Scene->B_Camera[Index]->CamPos.z);

	sprintf(chr_LookAT_X, "%.3f ", App->SBC_Scene->B_Camera[Index]->LookAt.x);
	sprintf(chr_LookAT_Y, "%.3f ", App->SBC_Scene->B_Camera[Index]->LookAt.y);
	sprintf(chr_LookAT_Z, "%.3f ", App->SBC_Scene->B_Camera[Index]->LookAt.z);


	const int NUM_ITEMS = 9;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Camera[Index]->Camera_Name;
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
		strcpy(App->Cl_Dialogs->btext, "Change Camera Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Scene->B_Camera[Index]->Camera_Name);

		App->Cl_Dialogs->Dialog_Text(1, 1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		// Needs Duplicate Name test 
		strcpy(App->SBC_Scene->B_Camera[Index]->Camera_Name, App->Cl_Dialogs->Chr_Text);

		App->SBC_Scene->B_Camera[Index]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Camera[Index]->FileViewItem);

		App->SBC_FileView->Change_Item_Name(App->SBC_Scene->B_Camera[Index]->FileViewItem, App->Cl_Dialogs->Chr_Text);

		Update_ListView_Camera();
	}

	result = strcmp(App->SBC_Properties->btext, "Pos_X");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->B_Camera[Index]->CamPos.x);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Position X");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->B_Camera[Index]->CamPos.x = App->Cl_Dialogs->mFloat;

		App->SBC_Scene->B_Camera[Index]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Camera[Index]->FileViewItem);

		Update_ListView_Camera();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Pos_Y");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->B_Camera[Index]->CamPos.y);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Position Y");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->B_Camera[Index]->CamPos.y = App->Cl_Dialogs->mFloat;

		App->SBC_Scene->B_Camera[Index]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Camera[Index]->FileViewItem);

		Update_ListView_Camera();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Pos_Z");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Scene->B_Camera[Index]->CamPos.z);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Position Z");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Scene->B_Camera[Index]->CamPos.z = App->Cl_Dialogs->mFloat;

		App->SBC_Scene->B_Camera[Index]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Camera[Index]->FileViewItem);

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

		App->SBC_Scene->B_Camera[Index]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Camera[Index]->FileViewItem);

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

		App->SBC_Scene->B_Camera[Index]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Camera[Index]->FileViewItem);

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

		App->SBC_Scene->B_Camera[Index]->Altered = 1;
		App->SBC_Scene->Scene_Modified = 1;
		App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Camera[Index]->FileViewItem);

		Update_ListView_Camera();

		return 1;
	}

	return 1;
}

// *************************************************************************
// *				Edit_Sounds_OnClick  Terry Bernie					   *
// *************************************************************************
bool SB_Properties::Edit_Sounds_OnClick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	// Name
	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Scene->B_Object[Index]->Mesh_Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects, 1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, App->Cl_Dialogs->Chr_Text);

		App->SBC_Properties->Mark_As_Altered(Index);

		App->SBC_FileView->Change_Item_Name(App->SBC_Scene->B_Object[Index]->FileViewItem, App->Cl_Dialogs->Chr_Text);

		Update_ListView_Sounds();
	}


	// Sound
	result = strcmp(btext, "Sound");
	if (result == 0)
	{
		App->SBC_SoundMgr->Accessed = 1;
		strcpy(App->SBC_SoundMgr->Access_File, App->SBC_Scene->B_Object[Index]->Sound_File);

		App->SBC_SoundMgr->Dialog_SoundFile();

		strcpy(App->SBC_Scene->B_Object[Index]->Sound_File, App->SBC_SoundMgr->Access_File);

		App->SBC_Scene->B_Object[Index]->SndVolume = App->SBC_SoundMgr->SndVolume;

		Mark_As_Altered(Index);

		Update_ListView_Sounds();

		return 1;
	}

	// Sound
	result = strcmp(btext, "Volume");
	if (result == 0)
	{
		App->SBC_SoundMgr->Accessed = 1;
		strcpy(App->SBC_SoundMgr->Access_File, App->SBC_Scene->B_Object[Index]->Sound_File);

		App->SBC_SoundMgr->Dialog_SoundFile();

		strcpy(App->SBC_Scene->B_Object[Index]->Sound_File, App->SBC_SoundMgr->Access_File);

		App->SBC_Scene->B_Object[Index]->SndVolume = App->SBC_SoundMgr->SndVolume;

		Mark_As_Altered(Index);

		Update_ListView_Sounds();

		return 1;
	}

	// Sound
	/*result = strcmp(btext, "Play");
	if (result == 0)
	{

		App->SBC_Dialogs->YesNo("Play Sound",App->SBC_Scene->B_Object[Index]->Sound_File,true);

		if (App->SBC_Dialogs->Canceled == 0)
		{
			App->SBC_Scene->B_Object[Index]->
		}

		Update_ListView_Teleport();

		return 1;
	}*/

	return 1;
}

// *************************************************************************
// *				Edit_Teleport_OnClick  Terry Bernie					   *
// *************************************************************************
bool SB_Properties::Edit_Teleport_OnClick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Scene->B_Object[Index]->Mesh_Name);

		App->Cl_Dialogs->Dialog_Text(Enums::Check_Names_Objects, 1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->SBC_Scene->B_Object[Index]->Mesh_Name, App->Cl_Dialogs->Chr_Text);

		App->SBC_Properties->Mark_As_Altered(Index);

		App->SBC_FileView->Change_Item_Name(App->SBC_Scene->B_Object[Index]->FileViewItem, App->Cl_Dialogs->Chr_Text);

		Update_ListView_Teleport();
	}

	result = strcmp(btext, "Goto");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Select Object to Move");

		App->SBC_Dialogs->DropList_Data = Enums::DropDialog_Locations;
		App->SBC_Dialogs->Dialog_DropGen();


		if (App->SBC_Dialogs->Canceled == 0)
		{
			int LocationIndex = App->Cl_LookUps->Player_Location_GetIndex_ByName(App->SBC_Dialogs->Chr_DropText);


			strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Name, App->SBC_Scene->B_Locations[LocationIndex]->Name);

			App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Player_Position = App->SBC_Scene->B_Locations[LocationIndex]->Current_Position;
			App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Physics_Position = App->SBC_Scene->B_Locations[LocationIndex]->Physics_Position;
			App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Physics_Rotation = App->SBC_Scene->B_Locations[LocationIndex]->Physics_Rotation;

			Update_ListView_Teleport();
		}

	}

	// Sound
	result = strcmp(btext, "Sound");
	if (result == 0)
	{

		App->SBC_SoundMgr->Accessed = 1; // For Sound Manager Dlg
		strcpy(App->SBC_SoundMgr->Access_File, App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Sound_File);

		App->SBC_SoundMgr->Dialog_SoundFile();

		strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Sound_File, App->SBC_SoundMgr->Access_File);

		App->SBC_Scene->B_Object[Index]->S_Teleport[0]->SndVolume = App->SBC_SoundMgr->SndVolume;

		Mark_As_Altered(Index);

		Update_ListView_Teleport();
		return 1;
	}

	// Volume
	result = strcmp(btext, "Volume");
	if (result == 0)
	{

		App->SBC_SoundMgr->Accessed = 1; // For Sound Manager Dlg
		strcpy(App->SBC_SoundMgr->Access_File, App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Sound_File);

		App->SBC_SoundMgr->Dialog_SoundFile();

		strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Sound_File, App->SBC_SoundMgr->Access_File);

		App->SBC_Scene->B_Object[Index]->S_Teleport[0]->SndVolume = App->SBC_SoundMgr->SndVolume;

		Mark_As_Altered(Index);

		Update_ListView_Teleport();
		return 1;
	}

	result = strcmp(btext, "Play");
	if (result == 0)
	{

		App->SBC_Dialogs->YesNo("Play Sound", App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Sound_File, true);

		if (App->SBC_Dialogs->Canceled == 0)
		{
			App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Play = 1;
		}
		else
		{
			App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Play = 0;
		}

		Update_ListView_Teleport();

		return 1;
	}

	return 1;
}
