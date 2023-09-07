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
#include "SB_Properties.h"

SB_Properties::SB_Properties()
{
	Properties_Dlg_hWnd = nullptr;
	Properties_hLV = nullptr;

	Edit_Category = 3; // Player Enums::FV_Edit_Object;
}

SB_Properties::~SB_Properties()
{
}

// *************************************************************************
// *		Start_GD_Properties:- Terry and Hazel Flanigan 2023   	 	   *
// *************************************************************************
void SB_Properties::Start_GD_Properties(void)
{
	/*if (Properties_Dlg_Active == 1)
	{
		return;
	}*/

	//Properties_Dlg_Active = 1;
	//HMENU mMenu = GetMenu(App->MainHwnd);
	//CheckMenuItem(mMenu, ID_WINDOWS_PROPERTIES, MF_BYCOMMAND | MF_CHECKED);

	Properties_Dlg_hWnd = CreateDialog(App->hInst, (LPCTSTR)IDD_SB_PROPERTIES, App->Equity_Dlg_hWnd, (DLGPROC)GD_Properties_Proc);
	//ShowWindow(Properties_Dlg_hWnd, 1);

	//Init_Bmps_Properties();

	Create_Properties_hLV();

}

// *************************************************************************
// *		GD_Properties_Proc:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
LRESULT CALLBACK SB_Properties::GD_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		//SendDlgItemMessage(hDlg, IDC_STOBJECTNAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		App->CLSB_Properties->Edit_Category = 3; // Enums::FV_Edit_Object;

		return 1;
	}

	case WM_CTLCOLORSTATIC:
	{

		/*if (GetDlgItem(hDlg, IDC_STOBJECTNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->DialogBackGround;
		}*/

		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->AppBackground;
	}

	case WM_CLOSE:
	{
		/*App->SBC_Properties->Properties_Dlg_Active = 0;

		HMENU mMenu = GetMenu(App->MainHwnd);
		CheckMenuItem(mMenu, ID_WINDOWS_PROPERTIES, MF_BYCOMMAND | MF_UNCHECKED);

		ShowWindow(App->SBC_Properties->Properties_Dlg_hWnd, 0);*/

		break;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->hwndFrom == App->CLSB_Properties->Properties_hLV)
		{
			switch (some_item->code)
			{
			case NM_CLICK:
			{
				App->CLSB_Properties->ListView_OnClickOptions(lParam);
			}
			}
		}

		/*if (some_item->idFrom == IDC_BT_OBJECTHELP2 && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		/*if (LOWORD(wParam) == IDC_BT_OBJECTHELP2)
		{
			if (App->SBC_Properties->Edit_Category == Enums::FV_Edit_Level)
			{
				App->Cl_Utilities->OpenHTML("Help\\LevelFolder.html");
				return 1;
			}

			return 1;

		}*/

		break;
	}
	}
	return FALSE;
}

// *************************************************************************
// *		Create_Properties_hLV:- Terry and Hazel Flanigan 2023		   *
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
// *	  ListView_OnClickOptions:- Terry and Hazel Flanigan 2023	 	   *
// *************************************************************************
void SB_Properties::ListView_OnClickOptions(LPARAM lParam)
{
	//// Area
	//if (Edit_Category == Enums::Edit_Area)
	//{
	//	App->SBC_Properties->Edit_Area_Onclick(lParam);

	//	return;
	//}

	//// Camera
	//if (Edit_Category == Enums::Edit_Camera)
	//{
	//	App->SBC_Properties->Edit_Camera_Onclick(lParam);

	//	return;
	//}

	// Player
	if (Edit_Category == 3) //Enums::Edit_Player)
	{
		//if (Edit_Physics == 0)
		{
			Edit_Player_Onclick(lParam);
		}
		//else
		//{
		//	//Edit_Player_Physics_Onclick(lParam);
		//}

		return;
	}

	//// Objects
	//if (Edit_Category == Enums::FV_Edit_Object)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_Object_Onclick(lParam);
	//	}
	//	return;
	//}

	//// Messages
	//if (Edit_Category == Enums::Edit_Message)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_Messages_OnClick(lParam);
	//	}
	//	return;
	//}

	//// Move Entity
	//if (Edit_Category == Enums::Edit_Move_Entity)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_Move_Entity_OnClick(lParam);
	//	}
	//	return;
	//}

	//// Sounds
	//if (Edit_Category == Enums::Edit_Sounds)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_Sounds_OnClick(lParam);
	//	}
	//	return;
	//}

	//// Teleports
	//if (Edit_Category == Enums::Edit_Teleport)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_Teleport_OnClick(lParam);
	//	}
	//	return;
	//}

	//// Collectables
	//if (Edit_Category == Enums::Edit_Collectable)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_Collectables_OnClick(lParam);
	//	}
	//	return;
	//}

	//// Counters
	//if (Edit_Category == Enums::Edit_Counters)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_Counters_OnClick(lParam);
	//	}
	//	return;
	//}

	//// Environs
	//if (Edit_Category == Enums::Edit_Environs)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_Environs_OnClick(lParam);
	//	}
	//	return;
	//}

	//// Particles
	//if (Edit_Category == Enums::Edit_Particles)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_Particle_Onclick(lParam);
	//	}
	//	return;
	//}

	//// Lights
	//if (Edit_Category == Enums::Edit_Lights)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_Light_Onclick(lParam);
	//	}
	//	return;
	//}

	//// UserObjects
	//if (Edit_Category == Enums::Edit_UserObjects)
	//{
	//	if (Edit_Physics == 0)
	//	{
	//		Edit_UserObjects_Onclick(lParam);
	//	}
	//	return;
	//}

	return;
}

// *************************************************************************
// *		Update_ListView_Player:- Terry and Hazel Flanigan 2023 	 	   *
// *************************************************************************
void SB_Properties::Update_ListView_Player()
{
	//int index = App->CLSB_Properties->Current_Selected_Object;

	//	char Num[10];
	char chr_ID[50];
	//_itoa(App->SBC_Scene->V_Object[index]->This_Object_ID, Num, 10);
	strcpy(chr_ID, "Properties ID=0");
	//strcat(chr_ID, Num);

	SetWindowText(Properties_Dlg_hWnd, chr_ID);
	//SetDlgItemText(App->CLSB_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)App->CLSB_Scene->B_Player[0]->Player_Name);

	char chr_Speed[100];
	char chr_TurnRate[100];
	char chr_Height[100];
	char chr_StartPosX[100];
	char chr_StartPosY[100];
	char chr_StartPosZ[100];

	char chr_LookUp_Limit[100];
	char chr_LookDown_Limit[100];

	sprintf(chr_Speed, "%.3f ", App->CLSB_Scene->B_Player[0]->Ground_speed / 100);

	sprintf(chr_TurnRate, "%.6f ", App->CLSB_Scene->B_Player[0]->TurnRate);

	sprintf(chr_Height, "%.3f ", App->CLSB_Scene->B_Player[0]->PlayerHeight);

	sprintf(chr_StartPosX, "%.3f ", App->CLSB_Scene->B_Player[0]->StartPos.x);
	sprintf(chr_StartPosY, "%.3f ", App->CLSB_Scene->B_Player[0]->StartPos.y);
	sprintf(chr_StartPosZ, "%.3f ", App->CLSB_Scene->B_Player[0]->StartPos.z);

	sprintf(chr_LookUp_Limit, "%.3f ", App->CLSB_Scene->B_Player[0]->Limit_Look_Up);
	sprintf(chr_LookDown_Limit, "%.3f ", App->CLSB_Scene->B_Player[0]->Limit_Look_Down);


	const int NUM_ITEMS = 13;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name", grid[1][0] = App->CLSB_Scene->B_Player[0]->Player_Name;
	grid[0][1] = "Mode", grid[1][1] = "1st_Person";
	grid[0][2] = " ", grid[1][2] = " ";
	grid[0][3] = "Ground Speed", grid[1][3] = chr_Speed;
	grid[0][4] = "Turn Rate", grid[1][4] = chr_TurnRate;
	grid[0][5] = "Player Height", grid[1][5] = chr_Height;
	grid[0][6] = " ", grid[1][6] = " ";
	grid[0][7] = "Start Pos_X", grid[1][7] = chr_StartPosX;
	grid[0][8] = "Start Pos_Y", grid[1][8] = chr_StartPosY;
	grid[0][9] = "Start Pos_Z", grid[1][9] = chr_StartPosZ;
	grid[0][10] = " ", grid[1][10] = " ";
	grid[0][11] = "Look Up", grid[1][11] = chr_LookUp_Limit;
	grid[0][12] = "Look Down", grid[1][12] = chr_LookDown_Limit;


	ListView_DeleteAllItems(App->CLSB_Properties->Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(App->CLSB_Properties->Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(App->CLSB_Properties->Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

}

// *************************************************************************
// *		Edit_Player_Onclick:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
bool SB_Properties::Edit_Player_Onclick(LPARAM lParam)
{
	//int Index = App->SBC_Properties->Current_Selected_Object;
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(Properties_hLV, test, 0, btext, 20);

	result = strcmp(btext, "Name");
	if (result == 0)
	{
		//strcpy(App->Cl_Dialogs->btext, "Change Player Name");
		//strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Scene->B_Player[0]->Player_Name);

		//App->Cl_Dialogs->Dialog_Text(1, 1);

		//if (App->Cl_Dialogs->Canceled == 1)
		//{
		//	return TRUE;
		//}

		//// Needs Duplicate Name test 
		//strcpy(App->SBC_Scene->B_Player[0]->Player_Name, App->Cl_Dialogs->Chr_Text);

		//App->SBC_Scene->B_Player[0]->Altered = 1;
		//App->SBC_Scene->Scene_Modified = 1;
		//App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);

		//App->SBC_FileView->Change_Item_Name(App->SBC_Scene->B_Player[0]->FileViewItem, App->Cl_Dialogs->Chr_Text);
		//Update_ListView_Player();
	}

	result = strcmp(btext, "Ground Speed");
	if (result == 0)
	{

		App->CLSB_ImGui->Start_Dialog_Float(1.0, App->CLSB_Scene->B_Player[0]->Ground_speed / 100, "Ground Speed");

		while (App->CLSB_ImGui->Show_Dialog_Float == 1)
		{
			App->CLSB_ImGui->BackGround_Render_Loop();
			App->CLSB_Scene->B_Player[0]->Ground_speed = App->CLSB_ImGui->m_Dialog_Float * 100;
		}

		if (App->CLSB_ImGui->Float_Canceld == 0)
		{
			App->CLSB_ImGui->Show_Dialog_Float = 0;
			App->CLSB_Scene->B_Player[0]->Ground_speed = App->CLSB_ImGui->m_Dialog_Float * 100;

			App->CLSB_Scene->B_Player[0]->Altered = 1;
			//App->CLSB_Model->Scene_Modified = 1;
			//App->SBC_FileView->Mark_Altered(App->CLSB_Model->B_Player[0]->FileViewItem);
		}
		else
		{
			App->CLSB_ImGui->m_Dialog_Float = App->CLSB_ImGui->m_Dialog_Float_Copy * 100;
			App->CLSB_Scene->B_Player[0]->Ground_speed = App->CLSB_ImGui->m_Dialog_Float_Copy * 100;
		}

		//App->Disable_Panels(false);
		Update_ListView_Player();

		return 1;
	}

	result = strcmp(btext, "Turn Rate");
	if (result == 0)
	{

		/*char chr_Value[10];
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

		Update_ListView_Player();*/

		return 1;
	}

	result = strcmp(btext, "Player Height");
	if (result == 0)
	{
		App->CLSB_ImGui->Start_Dialog_Float(0.10, App->CLSB_Scene->B_Player[0]->PlayerHeight, "Player Height");

		while (App->CLSB_ImGui->Show_Dialog_Float == 1)
		{
			App->CLSB_ImGui->BackGround_Render_Loop();

			App->CLSB_Scene->B_Player[0]->PlayerHeight = App->CLSB_ImGui->m_Dialog_Float;
		}

		App->CLSB_ImGui->Show_Dialog_Float = 0;

		if (App->CLSB_ImGui->Float_Canceld == 0)
		{
			App->CLSB_ImGui->Show_Dialog_Float = 0;

			App->CLSB_Scene->B_Player[0]->PlayerHeight = App->CLSB_ImGui->m_Dialog_Float;

			//App->SBC_Scene->Scene_Modified = 1;

			//App->SBC_Scene->B_Player[0]->Altered = 1;
			//App->SBC_Scene->Scene_Modified = 1;
			//App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Player[0]->FileViewItem);
		}
		else
		{
			App->CLSB_ImGui->m_Dialog_Float = App->CLSB_ImGui->m_Dialog_Float_Copy;
			App->CLSB_Scene->B_Player[0]->PlayerHeight = App->CLSB_ImGui->m_Dialog_Float_Copy;
		}

		//App->Disable_Panels(false);

		Update_ListView_Player();
		return 1;
	}

	result = strcmp(btext, "Start Pos_X");
	if (result == 0)
	{
		/*App->SBC_Gui_Dialogs->Start_Dialog_Float(0.10, App->SBC_Scene->B_Player[0]->StartPos.x, "Start Pos_X");

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

		Update_ListView_Player();*/

		return 1;
	}

	result = strcmp(btext, "Start Pos_Y");
	if (result == 0)
	{
		/*App->SBC_Gui_Dialogs->Start_Dialog_Float(0.10, App->SBC_Scene->B_Player[0]->StartPos.y, "Start Pos_Y");

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

		Update_ListView_Player();*/
		return 1;
	}

	result = strcmp(btext, "Start Pos_Z");
	if (result == 0)
	{
		/*App->SBC_Gui_Dialogs->Start_Dialog_Float(0.10, App->SBC_Scene->B_Player[0]->StartPos.z, "Start Pos_Z");

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

		Update_ListView_Player();*/

		return 1;
	}

	result = strcmp(btext, "Look Up");
	if (result == 0)
	{
		/*App->SBC_Gui_Dialogs->Start_Dialog_Float(0.5, App->SBC_Scene->B_Player[0]->Limit_Look_Up, "Player Look Up Limit");

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

		Update_ListView_Player();*/

		return 1;
	}

	result = strcmp(btext, "Look Down");
	if (result == 0)
	{

		/*App->SBC_Gui_Dialogs->Start_Dialog_Float(0.5, App->SBC_Scene->B_Player[0]->Limit_Look_Down, "Player Look Down Limit");

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

		Update_ListView_Player();*/

		return 1;
	}


	return 1;
}
