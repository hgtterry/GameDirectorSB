/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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

#include "StdAfx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Environment.h"

#pragma warning( disable : 4800 )

GD19_Environment::GD19_Environment(void)
{

	BackDrop_hWnd = NULL;
	General_hLV = NULL;
	mPropsCon = NULL;
	Environment_hWnd = NULL;

	SelectedProperties = 0;
	Environment_Dlg_Active = 0;

	FileView_Folder[0] = 0;
	
	btext[0] = 0;
	
	mParent = NULL;
	mRoot1 = NULL;
}


GD19_Environment::~GD19_Environment(void)
{
}

// *************************************************************************
// *		Start_Environment:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void GD19_Environment::Start_Environment(char* Category)
{

	if(Environment_Dlg_Active == 1)
	{
		Select_Category(Category);
		return;
	}

	App->SBC_FileView->Show_FileView(false);

	Environment_Dlg_Active = 1;
	Environment_hWnd = CreateDialog(App->hInst,(LPCTSTR)IDD_ENVIRONMENT,App->Fdlg,(DLGPROC)Environment_Proc);
	Select_Category(Category);
}

// *************************************************************************
// *            Environment_Proc:- Terry and Hazel Flanigan 202			   *
// *************************************************************************
LRESULT CALLBACK GD19_Environment::Environment_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
				
	switch (message)
	{
	case WM_INITDIALOG:
		{	
			App->SetTitleBar(hDlg);

			SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
			SendDlgItemMessage(hDlg, IDC_STBANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
			
			App->Cl_Environment->Create_GeneralListBackDrop(hDlg);
			App->Cl_Environment->Create_GeneralList(hDlg);

			App->Cl_Environment->mPropsCon = App->Cl_Environment->General_hLV;

			int Index = App->SBC_Properties->Current_Selected_Object;
			App->SBC_Com_Environments->Set_Environment_By_Index(1,Index);

			SetDlgItemText(hDlg, IDC_STBANNER, App->SBC_Scene->B_Object[Index]->Mesh_Name);
			
			return TRUE;
		}
		case WM_CTLCOLORSTATIC:
		{
			if (GetDlgItem(hDlg, IDC_STBANNER) == (HWND)lParam)
			{
				SetBkColor((HDC)wParam, RGB(0, 255, 0));
				SetTextColor((HDC)wParam, RGB(0, 0,255));
				SetBkMode((HDC)wParam, TRANSPARENT);
				return (UINT)App->AppBackground;
			}

			return FALSE;
		}

		case WM_CTLCOLORDLG:
			{
				return (LONG)App->AppBackground;
			}
		case WM_NOTIFY:
			{
				LPNMHDR some_item = (LPNMHDR)lParam;

				if (some_item->idFrom == IDOK && some_item->code == NM_CUSTOMDRAW)
				{
					LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
					App->Custom_Button_Normal(item);
					return CDRF_DODEFAULT;
				}

				if (some_item->idFrom == IDCANCEL && some_item->code == NM_CUSTOMDRAW)
				{
					LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
					App->Custom_Button_Normal(item);
					return CDRF_DODEFAULT;
				}

			}break;

		case WM_COMMAND:
			if (LOWORD(wParam) == IDOK) 
			{
				int Index = App->SBC_Properties->Current_Selected_Object;
				App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);

				Index = App->SBC_Com_Environments->Get_First_Environ();
				App->SBC_Com_Environments->Set_Environment_By_Index(0,Index);

				App->Cl_Environment->Environment_Dlg_Active = 0;
				App->RedrawWindow_Dlg(App->SBC_Props_Dialog->Area_Props_HWND);

				App->SBC_FileView->Show_FileView(true);
				EndDialog(hDlg, LOWORD(wParam));
				App->Cl_Environment->Environment_hWnd = NULL;
				return TRUE;
			}

			if (LOWORD(wParam)== IDCANCEL) 
			{
				int Index = App->SBC_Properties->Current_Selected_Object;
				App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);

				Index = App->SBC_Com_Environments->Get_First_Environ();
				App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);

				App->Cl_Environment->Environment_Dlg_Active = 0;
				App->RedrawWindow_Dlg(App->SBC_Props_Dialog->Area_Props_HWND);

				App->SBC_FileView->Show_FileView(true);
				EndDialog(hDlg, LOWORD(wParam));
				App->Cl_Environment->Environment_hWnd = NULL;
				return TRUE;
			}

			break;
	}
    return FALSE;
}

// *************************************************************************
// *			Select_Category:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void GD19_Environment::Select_Category(char* FileView_Folder)
{
	
	if (!strcmp(FileView_Folder, "Fog"))
	{
		SelectedProperties = 1; 
		SetDlgItemText(BackDrop_hWnd,IDC_ITEMHEADER,(LPCTSTR)"Fog options");
		Update_CreateFogListView();
		return;
	}

	if (!strcmp(FileView_Folder, "Main Light"))
	{
		SelectedProperties = 2; 
		SetDlgItemText(BackDrop_hWnd,IDC_ITEMHEADER,(LPCTSTR)"Main Light options");
		Update_CreateMainLightListView();
		return;
	}

	if (!strcmp(FileView_Folder, "Composite Map"))
	{
		SelectedProperties = 3; 
		SetDlgItemText(BackDrop_hWnd,IDC_ITEMHEADER,(LPCTSTR)"Composite Map options");
		//Update_CreateCompositeListView();
		return;
	}

	if (!strcmp(FileView_Folder, "Sound"))
	{
		SelectedProperties = 4; 
		SetDlgItemText(BackDrop_hWnd,IDC_ITEMHEADER,(LPCTSTR)"Sound options");
		Update_CreateSoundListView();
		return;
	}

	if (!strcmp(FileView_Folder, "Sky"))
	{
		SelectedProperties = 5; 
		SetDlgItemText(BackDrop_hWnd,IDC_ITEMHEADER,(LPCTSTR)"Sky options");
		Update_CreateSkyListView();
		return;
	}
}

// *************************************************************************
// *    	Update_CreateSkyListView:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
void GD19_Environment::Update_CreateSkyListView(void)
{
	char Chr_Enabled[10];
	char Chr_Curvature[10];
	char Chr_Tiling[10];
	char Chr_Distance[10];

	int Index = App->SBC_Properties->Current_Selected_Object;

	if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Enabled == 1)
	{
		strcpy(Chr_Enabled,"True");
	}
	else
	{
		strcpy(Chr_Enabled,"Flase");
	}

	sprintf(Chr_Curvature,"%.3f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Curvature);
	sprintf(Chr_Tiling,"%.3f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Tiling);
	sprintf(Chr_Distance,"%.3f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Distance);

	const int NUM_ITEMS = 1;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Enable",			grid[1][0] = Chr_Enabled;
	//grid[0][1] = "Type",			grid[1][1] = "SkyDome";
	//grid[0][2] = "Material",		grid[1][2] = "Examples/CloudySky";
	//grid[0][3] = "Curvature",		grid[1][3] = Chr_Curvature;
	//grid[0][4] = "Tiling",			grid[1][4] = Chr_Tiling;
	
	
	
	ListView_DeleteAllItems(General_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(General_hLV, &pitem);

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(General_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}
}
// *************************************************************************
// *	Update_CreateFogListView:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void GD19_Environment::Update_CreateFogListView(void)
{
	
	const int NUM_ITEMS = 6;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	char chr_FogOn[40];
	char chr_Colour[20];
	char chr_Start[20];
	char chr_End[20];
	char chr_Density[20];
	char chr_Mode[20];

	int Index = App->SBC_Properties->Current_Selected_Object;

	if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On == 1)
	{
		strcpy(chr_FogOn,"True");
	}
	else
	{
		strcpy(chr_FogOn,"Flase");
	}

	sprintf(chr_Density,"%f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Density);
	sprintf(chr_Start,"%.2f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start);
	sprintf(chr_End,"%.2f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End);
	sprintf(chr_Mode,"%i", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Mode);


	float mRed = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.x;
	float mGreen = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.y;
	float mBlue = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.z;
	
	sprintf(chr_Colour,"%.2f %.2f %.2f",mRed,mGreen,mBlue);
	
	grid[0][0] = "Visible",		grid[1][0] = chr_FogOn;
	grid[0][1] = "Mode",		grid[1][1] = chr_Mode;
	grid[0][2] = "Colour",		grid[1][2] = chr_Colour;
	grid[0][3] = "Density",		grid[1][3] = chr_Density;
	grid[0][4] = "Start",		grid[1][4] = chr_Start;
	grid[0][5] = "End",			grid[1][5] = chr_End;
	
	ListView_DeleteAllItems(General_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(General_hLV, &pitem);

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(General_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}
}
// *************************************************************************
// *	Update_CreateMainLightListView:- Terry and Hazel Flanigan 2022 	   *
// *************************************************************************
void GD19_Environment::Update_CreateMainLightListView(void)
{
	Ogre::Real mRed=0;
	Ogre::Real mGreen=0;
	Ogre::Real mBlue=0;

	int Index = App->SBC_Properties->Current_Selected_Object;

	mRed = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.x;
	mGreen = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.y;
	mBlue = App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour.z;
	
	char Chr_Ambient[100];
	sprintf(Chr_Ambient,"%.2f %.2f %.2f",mRed,mGreen,mBlue);

	const int NUM_ITEMS = 1;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Ambient",		grid[1][0] =Chr_Ambient;
	
	ListView_DeleteAllItems(General_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(General_hLV, &pitem);

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(General_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}
}

// *************************************************************************
// *	Update_CreateSoundListView:- Terry and Hazel Flanigan 2022	 	   *
// *************************************************************************
void GD19_Environment::Update_CreateSoundListView(void)
{
	char Chr_Volume[100];
	char Chr_Play[100];
	char Chr_Loop[100];

	int Index = App->SBC_Properties->Current_Selected_Object;

	sprintf(Chr_Volume,"%.1f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndVolume);

	// Play
	if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Play == 1)
	{
		strcpy(Chr_Play,"True");
	}
	else
	{
		strcpy(Chr_Play,"False");
	}

	// Loop
	if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Loop == 1)
	{
		strcpy(Chr_Loop,"True");
	}
	else
	{
		strcpy(Chr_Loop,"False");
	}

	const int NUM_ITEMS = 4;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Track",		grid[1][0] = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Sound_File;
	grid[0][1] = "Volume",		grid[1][1] = Chr_Volume;
	grid[0][2] = "Play",		grid[1][2] = Chr_Play;
	grid[0][3] = "Loop",		grid[1][3] = Chr_Loop;
	
	ListView_DeleteAllItems(General_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(General_hLV, &pitem);

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(General_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}
}

// *************************************************************************
// *	Create_GeneralListBackDrop:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void GD19_Environment::Create_GeneralListBackDrop(HWND hDlg)
{
	 BackDrop_hWnd = CreateDialog(App->hInst,(LPCTSTR)IDD_ENVIRONMENTBACKDROP,hDlg,(DLGPROC)BackDrop_Proc);
}

// *************************************************************************
// *			BackDrop_Proc:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
LRESULT CALLBACK GD19_Environment::BackDrop_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
		{
			HFONT Font;
			Font = CreateFont( -20,0,0,0,FW_BOLD,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Aerial Black");
			SendDlgItemMessage(hDlg,IDC_ITEMHEADER, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

			return 1;
		}
	case WM_CTLCOLORSTATIC:
		{
			if(GetDlgItem(hDlg,IDC_ITEMHEADER) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->Brush_White;
			}
		}
	case WM_CTLCOLORDLG:
		{
			return (LONG)App->Brush_White;
		}
		case WM_NOTIFY:
			{
				LPNMHDR nmhdr = (LPNMHDR) lParam;

				// Properties
				if (nmhdr->hwndFrom == App->Cl_Environment->mPropsCon)
				{
					switch (nmhdr->code)
					{
					case NM_CLICK:
						{
							App->Cl_Environment->On_Click_Props(lParam);
							break;
						}
					case NM_DBLCLK:
						{
							
							break;
						}
					}
				}
			}break;

		break;
	}
	return 0;
}

// *************************************************************************
// *		Create_GeneralList:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void GD19_Environment::Create_GeneralList(HWND hDlg)
{
	int NUM_COLS = 2;
	General_hLV = CreateWindowEx(0, WC_LISTVIEW, "",
					WS_CHILD | WS_VISIBLE|LVS_NOCOLUMNHEADER|LVS_REPORT|LVS_SHOWSELALWAYS,6,40,
					350,200,BackDrop_hWnd, 0,App->hInst, NULL);

	DWORD exStyles = LVS_EX_FULLROWSELECT;

	ListView_SetExtendedListViewStyleEx(General_hLV, exStyles, exStyles);

	ListView_SetBkColor(General_hLV,RGB(255,255,255));
	ListView_SetTextBkColor(General_hLV,RGB(255,255,255));
	
	LV_COLUMN lvC;
	memset(&lvC, 0, sizeof(LV_COLUMN));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	std::string headers[] =
	{
		"Setting", "Value"
	};
	int headerSize[] =
	{
		70,150
	};

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_InsertColumn(General_hLV, header, &lvC);
	}
	
	SendMessage(General_hLV,WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
}

// *************************************************************************
// *			On_Click_Props:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool GD19_Environment::On_Click_Props(LPARAM lParam)
{

	int result = 1;
	int SelectionIndex = 0;

	int Index = App->SBC_Properties->Current_Selected_Object;

	LPNMLISTVIEW Selection = (LPNMLISTVIEW) lParam;
	SelectionIndex = Selection->iItem;
	ListView_GetItemText(General_hLV,SelectionIndex, 0, btext, 255);

	// ----------------------------------------------------------- Fog
	result = strcmp(btext, "Visible");
	if (result == 0 && SelectedProperties == 1)
	{
		strcpy(App->Cl_Dialogs->btext,"Set Fog Visiblity");

		App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On;

		strcpy(App->Cl_Dialogs->btext, "Set Fog On/Off");
		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if(App->Cl_Dialogs->TrueFlase == 1)
			{
				App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On = 1;
				EnableFog(true);
			}
			else
			{
				App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On = 0;
				EnableFog(false);
			}

			Update_CreateFogListView();

			App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
		}
		return 1;
	}
	result = strcmp(btext, "Start");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Set Fog Start Distance");

		sprintf(App->Cl_Dialogs->Chr_Float,"%f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start);
		
		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start = App->Cl_Dialogs->mFloat;
			if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On == 1)
			{
				EnableFog(true);
			}
			Update_CreateFogListView();
			App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
		}
		return 1;
	}

	result = strcmp(btext, "End");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Set Fog End Distance");

		sprintf(App->Cl_Dialogs->Chr_Float,"%f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End);
		
		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End = App->Cl_Dialogs->mFloat;
			if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On == 1)
			{
				EnableFog(true);
			}
			Update_CreateFogListView();
			App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
		}
		return 1;
	}

	result = strcmp(btext, "Density");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Set Density Of Fog");

		sprintf(App->Cl_Dialogs->Chr_Float,"%f", App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Density);
		
		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Density = App->Cl_Dialogs->mFloat;

			if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On == 1)
			{
				EnableFog(true);
			}

			Update_CreateFogListView();
			App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
		}
		return 1;
	}

	result = strcmp(btext, "Colour");
	if (result == 0)
	{
		App->SBC_FileIO->GetColor();
		
		if (App->SBC_FileIO->Cannceled == 0)
		{
			int Red = GetRValue(App->SBC_FileIO->color.rgbResult);
			int Green = GetGValue(App->SBC_FileIO->color.rgbResult);
			int Blue = GetBValue(App->SBC_FileIO->color.rgbResult);

			App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.x = (float)Red / 256;
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.y = (float)Green / 256;;
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.z = (float)Blue / 256;;

			Update_CreateFogListView();

			if (App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_On == 1)
			{
				EnableFog(true);
			}

			Update_CreateFogListView();
			App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
		}
		return 1;
	}

	//result = strcmp(btext, "Mode");
	//if (result == 0)
	//{
	//	Dialog_Drop();
	//	Update_CreateFogListView();
	//	Flags[0]->RenderBackGround = 1;
	//	return 1;
	//}

	// ----------------------------------------------------------- Main Light
	result = strcmp(btext, "Ambient");
	if (result == 0)
	{
		Show_Environment_Dialog(0);

		App->SBC_Gui_Dialogs->Start_Colour_Picker(App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour);

		while (App->SBC_Gui_Dialogs->Show_ColourPicker == 1)
		{
			App->SBC_Gui_Dialogs->BackGround_Render_Loop();

			App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour = Ogre::Vector3(App->SBC_Gui_Dialogs->Float_Colour.x, App->SBC_Gui_Dialogs->Float_Colour.y, App->SBC_Gui_Dialogs->Float_Colour.z);
			App->SBC_Ogre->mSceneMgr->setAmbientLight(ColourValue(App->SBC_Gui_Dialogs->Float_Colour.x, App->SBC_Gui_Dialogs->Float_Colour.y, App->SBC_Gui_Dialogs->Float_Colour.z));
		}

		App->SBC_Gui_Dialogs->Show_ColourPicker = 0;

		App->Disable_Panels(false);
		App->Show_Panels(true);
		Show_Environment_Dialog(1);

		if (App->SBC_Gui_Dialogs->ColourPicker_Canceled == 0)
		{
			
		}
		else
		{
			float x = App->SBC_Gui_Dialogs->Float_Colour_Copy.x;
			float y = App->SBC_Gui_Dialogs->Float_Colour_Copy.y;
			float z = App->SBC_Gui_Dialogs->Float_Colour_Copy.z;

			App->SBC_Scene->B_Object[Index]->S_Environ[0]->AmbientColour = Ogre::Vector3(x, y, z);
			App->SBC_Ogre->mSceneMgr->setAmbientLight(ColourValue(x, y, z));

		}

		Update_CreateMainLightListView();
		App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
		
		return 1;
	}

	// ----------------------------------------------------------- Sound
	result = strcmp(btext, "Track");
	if (result == 0)
	{
		App->SBC_SoundMgr->Accessed = 1;
		strcpy(App->SBC_SoundMgr->Access_File, App->SBC_Scene->B_Object[Index]->S_Environ[0]->Sound_File);

		App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);
		App->SBC_SoundMgr->Dialog_SoundFile();

		if (App->SBC_SoundMgr->IsCancelled == 0)
		{
			
			strcpy(App->SBC_Scene->B_Object[Index]->S_Environ[0]->Sound_File, App->SBC_SoundMgr->Access_File);
			App->SBC_Scene->B_Object[Index]->S_Environ[0]->SndVolume = App->SBC_SoundMgr->SndVolume;

			App->SBC_Com_Environments->Set_Environment_By_Index(1, Index);

			App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);

			Update_CreateSoundListView();	
		}
		else
		{
			App->SBC_Com_Environments->Set_Environment_By_Index(1, Index);
		}

		return 1;
	}

	result = strcmp(btext, "Play");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Play Main BackGround Track");

		App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Play;

		strcpy(App->Cl_Dialogs->btext, "BackGround Music On/Off");
		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if(App->Cl_Dialogs->TrueFlase == 1)
			{
				App->SBC_Scene->B_Object[Index]->S_Environ[0]->Play = 1;

				App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);
				App->SBC_Com_Environments->Set_Environment_By_Index(1, Index);

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
			}
			else
			{
				App->SBC_Scene->B_Object[Index]->S_Environ[0]->Play = 0;

				App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);
				App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
			}

			Update_CreateSoundListView();
			
		}
		return 1;
	}
	result = strcmp(btext, "Loop");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Loop BackGround Track");

		App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Loop;

		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if(App->Cl_Dialogs->TrueFlase == 1)
			{
				App->SBC_Scene->B_Object[Index]->S_Environ[0]->Loop = 1;

				App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);
				App->SBC_Com_Environments->Set_Environment_By_Index(1, Index);

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
			}
			else
			{
				App->SBC_Scene->B_Object[Index]->S_Environ[0]->Loop = 0;

				App->SBC_Com_Environments->Set_Environment_By_Index(0, Index);
				App->SBC_Com_Environments->Set_Environment_By_Index(1, Index);

				App->SBC_Com_Environments->Mark_As_Altered_Environ(Index);
			}

			Update_CreateSoundListView();
			
		}
		return 1;
	}

	//// Composite
	//result = strcmp(btext, "Distance");
	//if (result == 0)
	//{
	//	/*strcpy(App->Class_Dlg_Com->btext,"Set Composite Map Distance");

	//	char Chr_MFScale[100];
	//	sprintf(Chr_MFScale,"%.0f",S_Scene[0]->CompositeMapDistance);

	//	strcpy (App->Class_Dlg_Com->Chr_Float,Chr_MFScale);
	//	
	//	App->Class_Dlg_Com->Dialog_Float();

	//	if (App->Class_Dlg_Com->Canceled == 0)
	//	{
	//		S_Scene[0]->CompositeMapDistance=App->Class_Dlg_Com->mFloat;	
	//		Update_Composite();

	//		App->Ogre17->mTerrainGlobals->setCompositeMapDistance(App->Class_Dlg_Com->mFloat);

	//		strcpy(App->FileName,S_Scene[0]->TerrainFileName);

	//		char Temp[256];
	//		strcpy(Temp,App->FileName);
	//		int Len=strlen(Temp);
	//		Temp[Len-8]=0;
	//		strcpy(S_Scene[0]->LevelName,Temp);

	//		App->Terrain_C->ReloadTerrain(0);
	//	}*/
	//	//return 1;
	//}

	//// Sky
	result = strcmp(btext, "Enable");
	if (result == 0 && SelectedProperties == 5)
	{
		SetSky(1);

		strcpy(App->Cl_Dialogs->btext,"Set Sky Visiblity");

		App->Cl_Dialogs->TrueFlase = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Enabled;
		
		strcpy(App->Cl_Dialogs->btext, "Set Fog On/Off");
		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if(App->Cl_Dialogs->TrueFlase == 1)
			{
				App->SBC_Scene->B_Object[Index]->S_Environ[0]->Enabled = 1;
				SetSky(1);
			}
			else
			{
				App->SBC_Scene->B_Object[Index]->S_Environ[0]->Enabled = 0;
				SetSky(0);
			}

			Update_CreateSkyListView();
		//	Flags[0]->RenderBackGround = 1;
		}
		return 1;
	}
	//result = strcmp(btext, "Curvature");
	//if (result == 0 && SelectedProperties == 5)
	//{
	//	strcpy(App->Class_Dlg_Com->btext,"Set Sky Cervature");

	//	char buff[256];
	//	sprintf(buff,"%f",S_Scene[0]->Sky[0].Curvature);
	//	strcpy (App->Class_Dlg_Com->Chr_Float,buff);

	//	App->Class_Dlg_Com->Dialog_Float();

	//	if (App->Class_Dlg_Com->Canceled == 0)
	//	{
	//		S_Scene[0]->Sky[0].Curvature = App->Class_Dlg_Com->mFloat;
	//		
	//		SetSky(1);
	//		
	//		Update_CreateSkyListView();
	//		Flags[0]->RenderBackGround = 1;
	//	}
	//	return 1;
	//}
	//result = strcmp(btext, "Tiling");
	//if (result == 0 && SelectedProperties == 5)
	//{
	//	strcpy(App->Class_Dlg_Com->btext,"Set Texture Tiling");

	//	char buff[256];
	//	sprintf(buff,"%f",S_Scene[0]->Sky[0].Tiling);
	//	strcpy (App->Class_Dlg_Com->Chr_Float,buff);

	//	App->Class_Dlg_Com->Dialog_Float();

	//	if (App->Class_Dlg_Com->Canceled == 0)
	//	{
	//		S_Scene[0]->Sky[0].Tiling = App->Class_Dlg_Com->mFloat;
	//		
	//		SetSky(1);
	//		
	//		Update_CreateSkyListView();
	//		Flags[0]->RenderBackGround = 1;
	//	}
	//	return 1;
	//}
	/*result = strcmp(btext, "Distance");
	if (result == 0 && SelectedProperties == 5)
	{
		strcpy(App->Class_Dlg_Com->btext,"Set Sky Distance");

		char buff[256];
		sprintf(buff,"%f",S_Scene[0]->Sky[0].Distance);
		strcpy (App->Class_Dlg_Com->Chr_Float,buff);

		App->Class_Dlg_Com->Dialog_Float();

		if (App->Class_Dlg_Com->Canceled == 0)
		{
			S_Scene[0]->Sky[0].Distance = App->Class_Dlg_Com->mFloat;
			
			SetSky(1);
			
			Update_CreateSkyListView();
			Flags[0]->RenderBackGround = 1;
		}
		return 1;
	}*/

	App->Say("Not Available Yet");
	return 1;
}

// *************************************************************************
// *	  		SetSky:- Terry and Hazel Flanigan 2022					   *
// *************************************************************************
void GD19_Environment::SetSky(bool Enable)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	App->SBC_Ogre->mSceneMgr->setSkyDome(Enable,
		App->SBC_Scene->B_Object[Index]->S_Environ[0]->Material,
		App->SBC_Scene->B_Object[Index]->S_Environ[0]->Curvature,
		App->SBC_Scene->B_Object[Index]->S_Environ[0]->Tiling,
		App->SBC_Scene->B_Object[Index]->S_Environ[0]->Distance);
}

// *************************************************************************
// *	  		EnableFog:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
bool GD19_Environment::EnableFog(bool SetFog)
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	if (SetFog == true)
	{
		float Start = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Start;
		float End = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_End;
		float Density = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Density;

		float x = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.x;
		float y = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.y;
		float z = App->SBC_Scene->B_Object[Index]->S_Environ[0]->Fog_Colour.z;

		App->SBC_Ogre->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x, y, z), Density, (Ogre::Real)Start, (Ogre::Real)End);
	}
	else
	{
		App->SBC_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}
	
	return 1;
}

// *************************************************************************
// *		Show_Environment_Dialog:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void GD19_Environment::Show_Environment_Dialog(bool show)
{
	if (show == 1)
	{
		ShowWindow(Environment_hWnd, SW_SHOW);	
	}
	else
	{
		ShowWindow(Environment_hWnd, SW_HIDE);
	}
}