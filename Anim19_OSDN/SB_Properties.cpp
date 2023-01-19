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
	App->SBC_Com_Camera->Hide_Cam_Dlg(0);
	App->SBC_Player->Hide_Player_Dlg(0);
	App->SBC_Props_Dialog->Hide_Area_Dlg(0);
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

	Init_Bmps_Properties();

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
		SendDlgItemMessage(hDlg, IDC_STOBJECTNAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

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

		if (some_item->idFrom == IDC_BT_OBJECTHELP2 && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_BT_OBJECTHELP2)
		{
			if (App->SBC_Properties->Edit_Category == Enums::FV_Edit_Level)
			{
				App->Cl_Utilities->OpenHTML("Help\\LevelFolder.html");
				return 1;
			}

			return 1;

		}

		break;
	}
	}
	return FALSE;
}

// *************************************************************************
// *		Init_Bmps_Properties:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Properties::Init_Bmps_Properties()
{

	HWND Temp = GetDlgItem(Properties_Dlg_hWnd, IDC_BT_OBJECTHELP2);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_InfoSmall_Bmp);

	HWND hTooltip_TB_2 = CreateWindowEx(0, TOOLTIPS_CLASS, "", TTS_ALWAYSTIP | TTS_BALLOON, 0, 0, 0, 0, App->MainHwnd, 0, App->hInst, 0);

	Temp = GetDlgItem(Properties_Dlg_hWnd, IDC_BT_OBJECTHELP2);
	TOOLINFO ti1 = { 0 };
	ti1.cbSize = sizeof(ti1);
	ti1.uFlags = TTF_IDISHWND | TTF_SUBCLASS | TTF_CENTERTIP;
	ti1.uId = (UINT_PTR)Temp;
	ti1.lpszText = "Show Help File";
	ti1.hwnd = App->MainHwnd;
	SendMessage(hTooltip_TB_2, TTM_ADDTOOL, 0, (LPARAM)&ti1);
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

	// Move Entity
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

	// Environs
	if (Edit_Category == Enums::Edit_Environs)
	{
		if (Edit_Physics == 0)
		{
			Edit_Environs_OnClick(lParam);
		}
		return;
	}

	// Particles
	if (Edit_Category == Enums::Edit_Particles)
	{
		if (Edit_Physics == 0)
		{
			Edit_Particle_Onclick(lParam);
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

	char Num[10];
	char chr_ID[50];
	char IndexNum[10];
	_itoa(App->SBC_Scene->B_Object[index]->This_Object_UniqueID, Num, 10);
	_itoa(index, IndexNum, 10);
	strcpy(chr_ID, "Unique ID ");
	strcat(chr_ID, Num);
	strcat(chr_ID, "  Object Index ");
	strcat(chr_ID, IndexNum);


	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Object[index]->Mesh_Name);

	
	const int NUM_ITEMS = 4;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = "Mesh File",	grid[1][1] = App->SBC_Scene->B_Object[index]->Mesh_FileName;
	grid[0][2] = "Material",	grid[1][2] = App->SBC_Scene->B_Object[index]->Material_File;
	grid[0][3] = " ",			grid[1][3] = " ";
	
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
	int index = App->SBC_Properties->Current_Selected_Object;

//	char Num[10];
	char chr_ID[50];
	//_itoa(App->SBC_Scene->B_Object[index]->This_Object_ID, Num, 10);
	strcpy(chr_ID, "Properties ID=0");
	//strcat(chr_ID, Num);

	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Player[0]->Player_Name);

	char chr_Speed[100];
	char chr_TurnRate[100];
	char chr_Height[100];
	char chr_StartPosX[100];
	char chr_StartPosY[100];
	char chr_StartPosZ[100];

	char chr_LookUp_Limit[100];
	char chr_LookDown_Limit[100];

	sprintf(chr_Speed, "%.3f ", App->SBC_Scene->B_Player[0]->Ground_speed/100);

	sprintf(chr_TurnRate, "%.6f ", App->SBC_Scene->B_Player[0]->TurnRate);

	sprintf(chr_Height, "%.3f ", App->SBC_Scene->B_Player[0]->PlayerHeight);

	sprintf(chr_StartPosX, "%.3f ", App->SBC_Scene->B_Player[0]->StartPos.x);
	sprintf(chr_StartPosY, "%.3f ", App->SBC_Scene->B_Player[0]->StartPos.y);
	sprintf(chr_StartPosZ, "%.3f ", App->SBC_Scene->B_Player[0]->StartPos.z);

	sprintf(chr_LookUp_Limit, "%.3f ", App->SBC_Scene->B_Player[0]->Limit_Look_Up);
	sprintf(chr_LookDown_Limit, "%.3f ", App->SBC_Scene->B_Player[0]->Limit_Look_Down);


	const int NUM_ITEMS = 13;
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
	grid[0][10] = " ",			grid[1][10] = " ";
	grid[0][11] = "Look Up",	grid[1][11] = chr_LookUp_Limit;
	grid[0][12] = "Look Down",	grid[1][12] = chr_LookDown_Limit;


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
	//strcat(buff, "   (Physics)");
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


	const int NUM_ITEMS = 6;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",   grid[1][0] = App->SBC_Scene->B_Player[0]->Player_Name;
	grid[0][1] = "Type",   grid[1][1] = chr_PhysicsType;
	grid[0][2] = "Shape ", grid[1][2] = chr_PhysicsShape;
	grid[0][3] = " ",      grid[1][3] = " ";
	grid[0][4] = "Radius", grid[1][4] = chr_Radius;
	grid[0][5] = "Height", grid[1][5] = chr_Height;

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
	int index = App->SBC_Properties->Current_Selected_Object;

	char Num[10];
	char chr_ID[50];
	char IndexNum[10];
	_itoa(App->SBC_Scene->B_Object[index]->This_Object_UniqueID, Num, 10);
	_itoa(index, IndexNum, 10);
	strcpy(chr_ID, "Unique ID ");
	strcat(chr_ID, Num);
	strcat(chr_ID, "  Object Index ");
	strcat(chr_ID, IndexNum);

	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Object[index]->Mesh_Name);

	char chr_PosX[20];
	sprintf(chr_PosX, "%.3f ", App->SBC_Scene->B_Object[index]->S_Message[0]->Message_PosX);

	char chr_PosY[20];
	sprintf(chr_PosY, "%.3f ", App->SBC_Scene->B_Object[index]->S_Message[0]->Message_PosY);

	char chr_Counter_Disabled[20];
	if (App->SBC_Scene->B_Object[index]->S_Message[0]->Counter_Disabled == 1)
	{
		strcpy(chr_Counter_Disabled, "Disabled");
	}
	else
	{
		strcpy(chr_Counter_Disabled, "Enabled");
	}

	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",            grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = " ",               grid[1][1] = " ";
	grid[0][2] = "Pos_X",           grid[1][2] = chr_PosX;
	grid[0][3] = "Pos_Y",           grid[1][3] = chr_PosY;
	grid[0][4] = "Text",            grid[1][4] = App->SBC_Scene->B_Object[index]->S_Message[0]->Message_Text;
	grid[0][5] = " ",				grid[1][5] = " ";
	grid[0][6] = "Counter",			grid[1][6] = chr_Counter_Disabled;


	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

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
	int index = Current_Selected_Object;

	char Num[10];
	char chr_ID[50];
	char IndexNum[10];
	_itoa(App->SBC_Scene->B_Object[index]->This_Object_UniqueID, Num, 10);
	_itoa(index, IndexNum, 10);
	strcpy(chr_ID, "Unique ID ");
	strcat(chr_ID, Num);
	strcat(chr_ID, "  Object Index ");
	strcat(chr_ID, IndexNum);

	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Object[index]->Mesh_Name);


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

// *************************************************************************
// *		Update_ListView_Environs:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Environs()
{
	int index = Current_Selected_Object;

	char Num[10];
	char IndexNum[10];
	char chr_ID[50];
	_itoa(App->SBC_Scene->B_Object[index]->This_Object_UniqueID, Num, 10);
	_itoa(index, IndexNum, 10);
	strcpy(chr_ID, "Unique ID ");
	strcat(chr_ID, Num);
	strcat(chr_ID, "  Object Index ");
	strcat(chr_ID, IndexNum);

	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Object[index]->Mesh_Name);

	const int NUM_ITEMS = 8;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS];
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = " ",			grid[1][1] = " ";
	grid[0][2] = "Main Light",	grid[1][2] = "Options";
	grid[0][3] = "Sound",		grid[1][3] = "Options";
	grid[0][4] = "Fog",			grid[1][4] = "Options";
	grid[0][5] = "Sky",			grid[1][5] = "Options";
	grid[0][6] = " ",			grid[1][6] = " ";
	grid[0][7] = "Evironment",	grid[1][7] = "Settings";

	ListView_DeleteAllItems(Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(Properties_hLV, &pitem);

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

	char Num[10];
	char chr_ID[50];
	_itoa(App->SBC_Scene->B_Object[index]->This_Object_UniqueID, Num, 10);
	strcpy(chr_ID, "Properties ID=");
	strcat(chr_ID, Num);

	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Object[index]->Mesh_Name);

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

	char chr_Goto_Location[100];
	int Goto_ID = App->SBC_Scene->B_Object[index]->S_Teleport[0]->Location_ID;
	strcpy(chr_Goto_Location, App->SBC_Scene->B_Locations[Goto_ID]->Name);

	char chr_Volume[100];
	float sum2 = App->SBC_Scene->B_Object[index]->S_Teleport[0]->SndVolume;
	int Percent = int(sum2 * 100);
	_itoa(Percent, chr_Volume, 10);

	char chr_Counter_Disabled[20];
	if (App->SBC_Scene->B_Object[index]->S_Teleport[0]->Counter_Disabled == 1)
	{
		strcpy(chr_Counter_Disabled, "Disabled");
	}
	else
	{
		strcpy(chr_Counter_Disabled, "Enabled");
	}

	// Environ
	char chr_Environ_Disabled[100];
	if (App->SBC_Scene->B_Object[index]->S_Environ[0]->Enabled == 1)
	{
		strcpy(chr_Environ_Disabled, "Enabled");
	}
	else
	{
		strcpy(chr_Environ_Disabled, "Disabled");
	}


	if (App->SBC_Scene->B_Object[index]->S_Environ[0]->Enabled == 1)
	{
		const int NUM_ITEMS = 13;
		const int NUM_COLS = 2;
		string grid[NUM_COLS][NUM_ITEMS]; // string table

		LV_ITEM pitem;
		memset(&pitem, 0, sizeof(LV_ITEM));
		pitem.mask = LVIF_TEXT;

		grid[0][0] = "Name",	grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
		grid[0][1] = " ",		grid[1][1] = " ";
		grid[0][2] = "Goto",	grid[1][2] = chr_Goto_Location;
		grid[0][3] = "Sound",	grid[1][3] = App->SBC_Scene->B_Object[index]->S_Teleport[0]->Sound_File;
		grid[0][4] = "Volume",	grid[1][4] = chr_Volume;
		grid[0][5] = "Play",	grid[1][5] = chr_Play;
		grid[0][6] = " ",		grid[1][6] = " ";
		grid[0][7] = "Counter", grid[1][7] = chr_Counter_Disabled;
		grid[0][8] = "Environment", grid[1][8] = chr_Environ_Disabled;

		grid[0][9] = "Main Light",		grid[1][9] = "Options";
		grid[0][10] = "Sound_Env",		grid[1][10] = "Options";
		grid[0][11] = "Fog",			grid[1][11] = "Options";
		grid[0][12] = "Sky",			grid[1][12] = "Options";

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
	}
	else
	{
		const int NUM_ITEMS = 9;
		const int NUM_COLS = 2;
		string grid[NUM_COLS][NUM_ITEMS]; // string table

		LV_ITEM pitem;
		memset(&pitem, 0, sizeof(LV_ITEM));
		pitem.mask = LVIF_TEXT;

		grid[0][0] = "Name",	grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
		grid[0][1] = " ",		grid[1][1] = " ";
		grid[0][2] = "Goto",	grid[1][2] = chr_Goto_Location;
		grid[0][3] = "Sound",	grid[1][3] = App->SBC_Scene->B_Object[index]->S_Teleport[0]->Sound_File;
		grid[0][4] = "Volume", grid[1][4] = chr_Volume;
		grid[0][5] = "Play",	grid[1][5] = chr_Play;
		grid[0][6] = " ",		grid[1][6] = " ";
		grid[0][7] = "Counter", grid[1][7] = chr_Counter_Disabled;
		grid[0][8] = "Environment", grid[1][8] = chr_Environ_Disabled;

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
	}


	return 1;
}

// *************************************************************************
// *	Update_ListView_Collectables():- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Collectables()
{
	int index = App->SBC_Properties->Current_Selected_Object;

	char Num[10];
	char chr_ID[50];
	char IndexNum[10];
	_itoa(App->SBC_Scene->B_Object[index]->This_Object_UniqueID, Num, 10);
	_itoa(index, IndexNum, 10);
	strcpy(chr_ID, "Unique ID ");
	strcat(chr_ID, Num);
	strcat(chr_ID, "  Object Index ");
	strcat(chr_ID, IndexNum);

	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Object[index]->Mesh_Name);
	
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

	char chr_Counter_Disabled[20];
	if (App->SBC_Scene->B_Object[index]->S_Collectable[0]->Counter_Disabled == 1)
	{
		strcpy(chr_Counter_Disabled, "Disabled");
	}
	else
	{
		strcpy(chr_Counter_Disabled, "Enabled");
	}

	const int NUM_ITEMS = 8;
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
	grid[0][7] = "Counter",			grid[1][7] = chr_Counter_Disabled;
	


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

	char Num[10];
	char chr_ID[50];
	_itoa(App->SBC_Scene->B_Counter[index]->Unique_ID, Num, 10);
	strcpy(chr_ID, "Properties ID=");
	strcat(chr_ID, Num);

	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Counter[index]->Panel_Name);

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

	int index = App->SBC_Properties->Current_Selected_Object;

	char Num[10];
	char chr_ID[50];
	char IndexNum[10];
	_itoa(App->SBC_Scene->B_Object[index]->This_Object_UniqueID, Num, 10);
	_itoa(index, IndexNum, 10);
	strcpy(chr_ID, "Unique ID ");
	strcat(chr_ID, Num);
	strcat(chr_ID, "  Object Index ");
	strcat(chr_ID, IndexNum);

	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Object[index]->Mesh_Name);

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

	char chr_Trigger_Value[100];
	_itoa(App->SBC_Scene->B_Object[index]->S_MoveType[0]->Trigger_Value, chr_Trigger_Value, 10);

	char chr_Volume[100];
	float sum2 = App->SBC_Scene->B_Object[index]->SndVolume;
	int Percent = int(sum2 * 100);
	_itoa(Percent, chr_Volume, 10);

	char chr_Counter_Disabled[20];
	if (App->SBC_Scene->B_Object[index]->S_MoveType[0]->Counter_Disabled == 1)
	{
		strcpy(chr_Counter_Disabled, "Disabled");
	}
	else
	{
		strcpy(chr_Counter_Disabled, "Enabled");
	}

	const int NUM_ITEMS = 12;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = " ",			grid[1][1] = " ";
	grid[0][2] = "Move_Object",	grid[1][2] = chr_Object_Name;
	grid[0][3] = "Axis",		grid[1][3] = chr_Axis;
	grid[0][4] = "Distance",	grid[1][4] = chr_Distance;
	grid[0][5] = "Speed",		grid[1][5] = chr_Speed;
	grid[0][6] = " ",			grid[1][6] = " ";
	grid[0][7] = "Sound",		grid[1][7] = App->SBC_Scene->B_Object[index]->Sound_File;
	grid[0][8] = "Volume",		grid[1][8] = chr_Volume;
	grid[0][9] = "Play",		grid[1][9] = chr_Play;
	grid[0][10] = " ",			grid[1][10] = " ";
	grid[0][11] = "Counter",	grid[1][11] = chr_Counter_Disabled;



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
	
	char buff[255];
	strcpy(buff, App->SBC_Project->m_Level_Name);
	//strcat(buff, "   (Level)");
	SetDlgItemText(App->SBC_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char strCamCount[20];
	
	const int NUM_ITEMS = 8;
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
// *		Update_ListView_Particles:- Terry and Hazel Flanigan 2022 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Particles()
{
	
	int index = App->SBC_Properties->Current_Selected_Object;

	char Num[10];
	char chr_ID[50];
	char IndexNum[10];
	_itoa(App->SBC_Scene->B_Object[index]->This_Object_UniqueID, Num, 10);
	_itoa(index, IndexNum, 10);
	strcpy(chr_ID, "Unique ID ");
	strcat(chr_ID, Num);
	strcat(chr_ID, "  Object Index ");
	strcat(chr_ID, IndexNum);
	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Object[index]->Mesh_Name);

	char chr_Speed[100];

	sprintf(chr_Speed, "%.3f", App->SBC_Scene->B_Object[index]->S_Particle[0]->Particle->getSpeedFactor());

	const int NUM_ITEMS = 4;
	const int NUM_COLS = 2;
	string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name",		grid[1][0] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][1] = "Particle",	grid[1][1] = App->SBC_Scene->B_Object[index]->Mesh_Name;
	grid[0][2] = " ",			grid[1][2] = " ";
	grid[0][3] = "Speed",		grid[1][3] = chr_Speed;
	
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
// *		Edit_Object_Onclick:- Terry and Hazel Flanigan 2022			   *
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
// *		Edit_Particle_Onclick:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Properties::Edit_Particle_Onclick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object;
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		App->SBC_Object->Rename_Object(Index);
		Update_ListView_Particles();
	}

	result = strcmp(btext, "Speed");
	if (result == 0)
	{

		App->SBC_Gui_Dialogs->Start_Dialog_Float(0.01, App->SBC_Scene->B_Object[Index]->S_Particle[0]->SpeedFactor, "Particle Speed");

		while (App->SBC_Gui_Dialogs->Show_Dialog_Float == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();

			App->SBC_Scene->B_Object[Index]->S_Particle[0]->SpeedFactor = App->SBC_Gui_Dialogs->m_Dialog_Float;
			App->SBC_Scene->B_Object[Index]->S_Particle[0]->Particle->setSpeedFactor(App->SBC_Gui_Dialogs->m_Dialog_Float);

		}

		App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

		if (App->SBC_Gui_Dialogs->Float_Canceld == 0)
		{
			App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

			App->SBC_Scene->B_Object[Index]->S_Particle[0]->SpeedFactor = App->SBC_Gui_Dialogs->m_Dialog_Float;

			App->SBC_Scene->Scene_Modified = 1;
			
			App->SBC_Scene->B_Object[Index]->Altered = 1;
			App->SBC_Scene->Scene_Modified = 1;
			App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Object[Index]->FileViewItem);
		}
		else
		{
			App->SBC_Gui_Dialogs->m_Dialog_Float = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
			App->SBC_Scene->B_Object[Index]->S_Particle[0]->SpeedFactor = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
			App->SBC_Scene->B_Object[Index]->S_Particle[0]->Particle->setSpeedFactor(App->SBC_Gui_Dialogs->m_Dialog_Float);
		}

		App->Disable_Panels(false);

		Update_ListView_Particles();
	}

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

		App->SBC_Gui_Dialogs->Start_Dialog_Float(1.0, App->SBC_Scene->B_Player[0]->Ground_speed / 100, "Ground Speed");

		while (App->SBC_Gui_Dialogs->Show_Dialog_Float == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();
		}

		if (App->SBC_Gui_Dialogs->Float_Canceld == 0)
		{
			App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;
			App->SBC_Scene->B_Player[0]->Ground_speed = App->SBC_Gui_Dialogs->m_Dialog_Float * 100;

			App->SBC_Scene->B_Player[0]->Altered = 1;
			App->SBC_Scene->Scene_Modified = 1;
			App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);
		}
		else
		{
			App->SBC_Gui_Dialogs->m_Dialog_Float = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
		}

		App->Disable_Panels(false);
		Update_ListView_Player();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Turn Rate");
	if (result == 0)
	{
		
		char chr_Value[10];
		sprintf(chr_Value, "%.6f ", App->SBC_Scene->B_Player[0]->TurnRate);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Turn Rate");

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
		App->SBC_Gui_Dialogs->Start_Dialog_Float(0.10, App->SBC_Scene->B_Player[0]->PlayerHeight, "Player Height");

		while (App->SBC_Gui_Dialogs->Show_Dialog_Float == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();

			App->SBC_Scene->B_Player[0]->PlayerHeight = App->SBC_Gui_Dialogs->m_Dialog_Float;
		}

		App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

		if (App->SBC_Gui_Dialogs->Float_Canceld == 0)
		{
			App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

			App->SBC_Scene->B_Player[0]->PlayerHeight = App->SBC_Gui_Dialogs->m_Dialog_Float;

			App->SBC_Scene->Scene_Modified = 1;

			App->SBC_Scene->B_Player[0]->Altered = 1;
			App->SBC_Scene->Scene_Modified = 1;
			App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);
		}
		else
		{
			App->SBC_Gui_Dialogs->m_Dialog_Float = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
			App->SBC_Scene->B_Player[0]->PlayerHeight = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
		}

		App->Disable_Panels(false);

		Update_ListView_Player();
		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Start Pos_X");
	if (result == 0)
	{
		App->SBC_Gui_Dialogs->Start_Dialog_Float(0.10, App->SBC_Scene->B_Player[0]->StartPos.x, "Start Pos_X");

		while (App->SBC_Gui_Dialogs->Show_Dialog_Float == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();

			App->SBC_Scene->B_Player[0]->StartPos.x = App->SBC_Gui_Dialogs->m_Dialog_Float;
			App->SBC_Physics->Reset_Physics();
		}

		App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

		if (App->SBC_Gui_Dialogs->Float_Canceld == 0)
		{
			App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

			App->SBC_Scene->B_Player[0]->StartPos.x = App->SBC_Gui_Dialogs->m_Dialog_Float;

			App->SBC_Scene->Scene_Modified = 1;

			App->SBC_Scene->B_Player[0]->Altered = 1;
			App->SBC_Scene->Scene_Modified = 1;
			App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);
		}
		else
		{
			App->SBC_Gui_Dialogs->m_Dialog_Float = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
			App->SBC_Scene->B_Player[0]->StartPos.x = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
			App->SBC_Physics->Reset_Physics();
		}

		App->Disable_Panels(false);

		Update_ListView_Player();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Start Pos_Y");
	if (result == 0)
	{
		App->SBC_Gui_Dialogs->Start_Dialog_Float(0.10, App->SBC_Scene->B_Player[0]->StartPos.y, "Start Pos_Y");

		while (App->SBC_Gui_Dialogs->Show_Dialog_Float == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();

			App->SBC_Scene->B_Player[0]->StartPos.y = App->SBC_Gui_Dialogs->m_Dialog_Float;
			App->SBC_Physics->Reset_Physics();
		}

		App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

		if (App->SBC_Gui_Dialogs->Float_Canceld == 0)
		{
			App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

			App->SBC_Scene->B_Player[0]->StartPos.y = App->SBC_Gui_Dialogs->m_Dialog_Float;

			App->SBC_Scene->Scene_Modified = 1;

			App->SBC_Scene->B_Player[0]->Altered = 1;
			App->SBC_Scene->Scene_Modified = 1;
			App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);
		}
		else
		{
			App->SBC_Gui_Dialogs->m_Dialog_Float = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
			App->SBC_Scene->B_Player[0]->StartPos.y = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
			App->SBC_Physics->Reset_Physics();
		}

		App->Disable_Panels(false);

		Update_ListView_Player();
		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Start Pos_Z");
	if (result == 0)
	{
		App->SBC_Gui_Dialogs->Start_Dialog_Float(0.10, App->SBC_Scene->B_Player[0]->StartPos.z, "Start Pos_Z");

		while (App->SBC_Gui_Dialogs->Show_Dialog_Float == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();

			App->SBC_Scene->B_Player[0]->StartPos.z = App->SBC_Gui_Dialogs->m_Dialog_Float;
			App->SBC_Physics->Reset_Physics();
		}

		App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

		if (App->SBC_Gui_Dialogs->Float_Canceld == 0)
		{
			App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

			App->SBC_Scene->B_Player[0]->StartPos.z = App->SBC_Gui_Dialogs->m_Dialog_Float;

			App->SBC_Scene->Scene_Modified = 1;

			App->SBC_Scene->B_Player[0]->Altered = 1;
			App->SBC_Scene->Scene_Modified = 1;
			App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);
		}
		else
		{
			App->SBC_Gui_Dialogs->m_Dialog_Float = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
			App->SBC_Scene->B_Player[0]->StartPos.z = App->SBC_Gui_Dialogs->m_Dialog_Float_Copy;
			App->SBC_Physics->Reset_Physics();
		}

		App->Disable_Panels(false);

		Update_ListView_Player();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Look Up");
	if (result == 0)
	{
		App->SBC_Gui_Dialogs->Start_Dialog_Float(0.5, App->SBC_Scene->B_Player[0]->Limit_Look_Up, "Player Look Up Limit");

		while (App->SBC_Gui_Dialogs->Show_Dialog_Float == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();
		}

		App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

		if (App->SBC_Gui_Dialogs->Float_Canceld == 0)
		{
			App->SBC_Scene->B_Player[0]->Limit_Look_Up = App->SBC_Gui_Dialogs->m_Dialog_Float;

			App->SBC_Scene->B_Player[0]->Altered = 1;
			App->SBC_Scene->Scene_Modified = 1;
			App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);
		}
		
		App->Disable_Panels(false);

		Update_ListView_Player();

		return 1;
	}

	result = strcmp(App->SBC_Properties->btext, "Look Down");
	if (result == 0)
	{
		
		App->SBC_Gui_Dialogs->Start_Dialog_Float(0.5, App->SBC_Scene->B_Player[0]->Limit_Look_Down, "Player Look Down Limit");

		while (App->SBC_Gui_Dialogs->Show_Dialog_Float == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();
		}

		App->SBC_Gui_Dialogs->Show_Dialog_Float = 0;

		if (App->SBC_Gui_Dialogs->Float_Canceld == 0)
		{
			App->SBC_Scene->B_Player[0]->Limit_Look_Down = App->SBC_Gui_Dialogs->m_Dialog_Float;

			App->SBC_Scene->B_Player[0]->Altered = 1;
			App->SBC_Scene->Scene_Modified = 1;
			App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);
		}

		App->Disable_Panels(false);

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
		strcpy(App->SBC_Dialogs->Chr_Text, App->SBC_Scene->B_Object[Index]->S_Message[0]->Message_Text);

		App->SBC_Dialogs->Dialog_Text();

		if (App->SBC_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		strcpy(App->SBC_Scene->B_Object[Index]->S_Message[0]->Message_Text, App->SBC_Dialogs->Chr_Text);

		App->SBC_Properties->Mark_As_Altered(Index);

		Update_ListView_Messages();

		return 1;
	}

	result = strcmp(btext, "Pos_X");
	if (result == 0)
	{
		App->SBC_Gui_Dialogs->Start_Dialog_MessageEditor(Index);

		while (App->SBC_Gui_Dialogs->Show_Dialog_MessageEditor == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();
		}

		App->SBC_Gui_Dialogs->Show_Dialog_MessageEditor = 0;

		App->SBC_Scene->B_Object[Index]->Show_Message_Flag = 0;

		App->SBC_Properties->Mark_As_Altered(Index);

		App->Show_Panels(true);
		App->Disable_Panels(false);

		Update_ListView_Messages();
		
		return 1;
	}

	result = strcmp(btext, "Pos_Y");
	if (result == 0)
	{
		App->SBC_Gui_Dialogs->Start_Dialog_MessageEditor(Index);

		while (App->SBC_Gui_Dialogs->Show_Dialog_MessageEditor == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();
		}

		App->SBC_Gui_Dialogs->Show_Dialog_MessageEditor = 0;

		App->SBC_Scene->B_Object[Index]->Show_Message_Flag = 0;

		App->SBC_Properties->Mark_As_Altered(Index);

		App->Show_Panels(true);
		App->Disable_Panels(false);

		Update_ListView_Messages();

		return 1;
	}

	// Counter
	result = strcmp(btext, "Counter");
	if (result == 0)
	{
		App->SBC_Dialogs->Dialog_Counter();

		if (App->SBC_Dialogs->Canceled == 1)
		{
			return 1;
		}

		App->SBC_Properties->Mark_As_Altered(Index);
		Update_ListView_Messages();

		return 1;
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

	/*result = strcmp(btext, "Mass");
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
	}*/

	result = strcmp(btext, "Radius");
	if (result == 0)
	{
		/*char chr_Radius[10];
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

		App->SBC_Properties->Update_ListView_Player_Physics();*/
		return 1;
	}

	result = strcmp(btext, "Height");
	if (result == 0)
	{
		/*char chr_Height[10];
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

		App->SBC_Properties->Update_ListView_Player_Physics();*/

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

	// Counter
	result = strcmp(btext, "Counter");
	if (result == 0)
	{
		App->SBC_Dialogs->Dialog_Counter();
		if (App->SBC_Dialogs->Canceled == 1)
		{
			return 1;
		}

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
		App->SBC_Dialogs->Dialog_Counter();

		if (App->SBC_Dialogs->Canceled == 1)
		{
			return 1;
		}

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
// *		Edit_Environs_OnClick:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Properties::Edit_Environs_OnClick(LPARAM lParam)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	/*result = strcmp(btext, "Name");
	if (result == 0)
	{
		App->SBC_Com_Environments->Rename_Environ(Index);
		Update_ListView_Environs();
		return 1;
	}

	result = strcmp(btext, "Main Light");
	if (result == 0)
	{
		App->Cl_Environment->Start_Environment("Main Light");
		Update_ListView_Environs();

		return 1;
	}

	result = strcmp(btext, "Sound");
	if (result == 0)
	{
		App->Cl_Environment->Start_Environment("Sound");
		Update_ListView_Environs();
		return 1;
	}

	result = strcmp(btext, "Fog");
	if (result == 0)
	{
		App->Cl_Environment->Start_Environment("Fog");
		Update_ListView_Environs();
		return 1;
	}

	result = strcmp(btext, "Sky");
	if (result == 0)
	{
		App->Cl_Environment->Start_Environment("Sky");
		Update_ListView_Environs();
		return 1;
	}*/

	result = strcmp(btext, "Evironment");
	if (result == 0)
	{
		App->SBC_Gui_Environ->Start_Environment_Editor(Index);
		return 1;
	}

	return 1;
}


// *************************************************************************
// *		Update_ListView_Area:- Terry and Hazel Flanigan 2022	 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Area()
{
	int Index = Current_Selected_Object;

	char Num[10];
	char chr_ID[50];
	_itoa(App->SBC_Scene->B_Area[Index]->This_Object_UniqueID, Num, 10);
	strcpy(chr_ID, "Properties ID=");
	strcat(chr_ID, Num);

	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Area[Index]->Area_Name);

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
	int Index = App->SBC_Properties->Current_Selected_Object;

//	char Num[10];
	char chr_ID[50];
	//_itoa(App->SBC_Scene->B_Camera[Index]->, Num, 10);
	strcpy(chr_ID, "Properties ID=0");
	//strcat(chr_ID, Num);
	
	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	SetDlgItemText(Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->SBC_Scene->B_Camera[Index]->Camera_Name);

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
		App->SBC_Com_Camera->Rename_Camera(Index);
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
		sprintf(chr_Value, "%.3f ", App->SBC_Com_Camera->LookAt_X);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Look At X");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Com_Camera->LookAt_X = App->Cl_Dialogs->mFloat;

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
		sprintf(chr_Value, "%.3f ", App->SBC_Com_Camera->LookAt_Y);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Look At Y");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Com_Camera->LookAt_Y = App->Cl_Dialogs->mFloat;

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
		sprintf(chr_Value, "%.3f ", App->SBC_Com_Camera->LookAt_Z);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Look At Z");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Com_Camera->LookAt_Z = App->Cl_Dialogs->mFloat;

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
		strcpy(App->Cl_Dialogs->btext, "Select Location");

		App->SBC_Dialogs->DropList_Data = Enums::DropDialog_Locations;
		App->SBC_Dialogs->Dialog_DropGen();


		if (App->SBC_Dialogs->Canceled == 0)
		{
			int LocationIndex = App->Cl_LookUps->Player_Location_GetIndex_ByName(App->SBC_Dialogs->Chr_DropText);
			App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Location_ID = LocationIndex;

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

	// Counter
	result = strcmp(btext, "Counter");
	if (result == 0)
	{
		App->SBC_Dialogs->Dialog_Counter();
		if (App->SBC_Dialogs->Canceled == 1)
		{
			return 1;
		}

		Mark_As_Altered(Index);
		Update_ListView_Teleport();

		//App->SBC_Physics->Reset_Triggers();
		return 1;
	}

	// Environment
	result = strcmp(btext, "Environment");
	if (result == 0)
	{
		App->SBC_Dialogs->YesNo("Enable Environment","Enable Teleport Environment", true);

		if (App->SBC_Dialogs->Canceled == 0)
		{
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->Enabled = 1;
		}
		else
		{
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->Enabled = 0;
		}

		Update_ListView_Teleport();

		return 1;
	}
	
	result = strcmp(btext, "Main Light");
	if (result == 0)
	{
		//App->Cl_Environment->Start_Environment("Main Light");
		Update_ListView_Teleport();

		return 1;
	}

	result = strcmp(btext, "Sound_Env");
	if (result == 0)
	{
		//App->Cl_Environment->Start_Environment("Sound");
		Update_ListView_Teleport();
		return 1;
	}

	result = strcmp(btext, "Fog");
	if (result == 0)
	{
		//App->Cl_Environment->Start_Environment("Fog");
		Update_ListView_Teleport();
		return 1;
	}

	result = strcmp(btext, "Sky");
	if (result == 0)
	{
		//App->Cl_Environment->Start_Environment("Sky");
		Update_ListView_Teleport();
		return 1;
	}
	return 1;
}

// *************************************************************************
// *				Reset_Last_Selected_Object Terry Bernie			 	   *
// *************************************************************************
void SB_Properties::Reset_Last_Selected_Object(int Index)
{
	App->SBC_Object->Show_Physics_Debug = 0;

	int f = App->SBC_Scene->B_Object[Index]->Phys_Body->getCollisionFlags();
	App->SBC_Scene->B_Object[Index]->Phys_Body->setCollisionFlags(f | (1 << 5)); // Off
	App->SBC_Scene->B_Object[Index]->Physics_Debug_On = 0;

	App->SBC_Ogre->BulletListener->Render_Debug_Flag = 0;
	App->SBC_Ogre->BulletListener->Clear_Debug_Render();
	App->SBC_Ogre->BulletListener->Render_Debug_Flag = 1;

	HWND Temp = GetDlgItem(App->SBC_Props_Dialog->Debug_Dlg_hWnd, IDC_BT_PHYSDEBUG);
	SendMessage(Temp, BM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)(HANDLE)App->Hnd_PhysicsOff_Bmp);

	App->SBC_Scene->B_Object[Index]->Object_Node->setVisible(true);
	App->SBC_Object->Show_Mesh_Debug = 1;

	App->SBC_Visuals->BoxNode->setVisible(false);
	App->SBC_Grid->Arrow_Node->setVisible(false);

	if (App->SBC_Scene->B_Object[Index]->Deleted == 0)
	{
		App->SBC_Object->Hide_AllObjects_Except(Index, true);
	}

	App->SBC_Object->Hide_All_Except_Flag = 0;
}
