#include "StdAfx.h"
#include "GD19_App.h"
#include "resource.h"
#include "GD19_Environment.h"

#pragma warning( disable : 4800 )

GD19_Environment::GD19_Environment(void)
{
	OptionsDlgHwnd = NULL;
	BackDrop_hWnd = NULL;
	General_hLV = NULL;
	mTreeCon = NULL;
	mPropsCon = NULL;
	Environment_hWnd = NULL;

	SelectedProperties = 0;
	Environment_Dlg_Active = 0;

	FileView_Folder[0] = 0;
	FileView_File[0] = 0;
	btext[0] = 0;
	TextInt[0] = 0;

	mParent = NULL;
	mRoot1 = NULL;

	mImageList = NULL;
	hBitMap = NULL;
}


GD19_Environment::~GD19_Environment(void)
{
}

// *************************************************************************
// *				Load_Environment  Terry Bernie						   *
// *************************************************************************
void GD19_Environment::Load_Environment(void)
{
	float x = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.x;
	float y = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.y;
	float z = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.z;

	App->Cl19_Ogre->mSceneMgr->setAmbientLight(ColourValue(x,y,z));

	if (App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn == 1)
	{
		EnableFog(true);
	}
	else
	{
		App->Cl19_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}
}

// *************************************************************************
// *				Start_Environment  Terry Bernie						   *
// *************************************************************************
void GD19_Environment::Start_Environment(void)
{

	if(Environment_Dlg_Active == 1){return;}

	Environment_Dlg_Active = 1;

	Environment_hWnd = CreateDialog(App->hInst,(LPCTSTR)IDD_ENVIRONMENT,App->Fdlg,(DLGPROC)Environment_Proc);
}
// *************************************************************************
// *        		Level_Front_Proc Terry Bernie						   *
// *************************************************************************
LRESULT CALLBACK GD19_Environment::Environment_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
				
	switch (message)
	{
	case WM_INITDIALOG:
		{	
			App->SetTitleBar(hDlg);

			HFONT Font;
			HFONT Font2;
			Font = CreateFont( -13,0,0,0,FW_BOLD,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Aerial Black");
			Font2 = CreateFont( -20,0,0,0,FW_BOLD,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Aerial Black");

			SendDlgItemMessage(hDlg,IDC_STINFO, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
			
			SendDlgItemMessage(hDlg,IDC_USAGEBANNER, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));
			
			SetDlgItemText(hDlg,IDC_USAGEBANNER,(LPCTSTR)"Game Environment Options");

			App->Cl_Environment->Init_FileView();

			App->Cl_Environment->OptionsDlgHwnd = hDlg;

			App->Cl_Environment->Create_GeneralListBackDrop(hDlg);
			App->Cl_Environment->Create_GeneralList(hDlg);

			App->Cl_Environment->GetListControls();

			SendDlgItemMessage(hDlg,IDC_OPTIOINSTREE,TVM_SETIMAGELIST,0,(LPARAM)App->Cl_Environment->mImageList); // put it onto the tree control
			HWND Temp=GetDlgItem(hDlg,IDC_OPTIOINSTREE);
			TreeView_DeleteAllItems(Temp);
			
			App->Cl_Environment->AddOptions();

			//Temp=GetDlgItem(hDlg,IDC_ENVHELP);
			//SendMessage(Temp,BM_SETIMAGE, (WPARAM) IMAGE_BITMAP,(LPARAM) (HANDLE)App->SetUp_C->BmpHelp);

			
			return TRUE;
		}
		case WM_CTLCOLORSTATIC:
		{
			if(GetDlgItem(hDlg,IDC_STINFO) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,0));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->Brush_White;
			}
			if(GetDlgItem(hDlg,IDC_USAGEBANNER) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}
			/*if(GetDlgItem(hDlg,IDC_STSCENETYPE) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}
			if(GetDlgItem(hDlg,IDC_STSCENENAME) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,255));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}
			if(GetDlgItem(hDlg,IDC_SCENESELECTION) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,0));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}
			if(GetDlgItem(hDlg,IDC_STTEST) == (HWND)lParam)
			{	
				SetBkColor((HDC) wParam, RGB(0, 255, 0));	
				SetTextColor((HDC) wParam, RGB(0,0,0));
				SetBkMode((HDC) wParam, TRANSPARENT);
				return (UINT) App->AppBackground;
			}*/

			return FALSE;
		}

		case WM_CTLCOLORDLG:
			{
				return (LONG)App->AppBackground;
			}
		case WM_NOTIFY:
			{
				LPNMHDR nmhdr = (LPNMHDR) lParam;

				// ListView
				if (nmhdr->hwndFrom == App->Cl_Environment->mTreeCon)
				{
					switch (nmhdr->code) 
					{

					case TVN_SELCHANGED:
						{
							App->Cl_Environment->ListView_Selection((LPNMHDR) lParam); 
						}	
					}
				}

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
				App->Cl_Environment->Environment_Dlg_Active = 0;
				App->RedrawWindow_Dlg(App->SBC_Aera->Area_Props_HWND);
				EndDialog(hDlg, LOWORD(wParam));
				App->Cl_Environment->Environment_hWnd = NULL;
				return TRUE;
			}

			if (LOWORD(wParam)== IDCANCEL) 
			{
				App->Cl_Environment->Environment_Dlg_Active = 0;
				App->RedrawWindow_Dlg(App->SBC_Aera->Area_Props_HWND);
				EndDialog(hDlg, LOWORD(wParam));
				App->Cl_Environment->Environment_hWnd = NULL;
				return TRUE;
			}

			break;
	}
    return FALSE;
}

// *************************************************************************
// *				  	ListView_Selection Terry Bernie				  	   *
// *************************************************************************
void GD19_Environment::ListView_Selection(LPNMHDR lParam)
{
	
	HWND Temp=GetDlgItem(OptionsDlgHwnd,IDC_OPTIOINSTREE);
	
	HTREEITEM i=TreeView_GetSelection(Temp);
	
	TVITEM item;
	item.hItem = i;
	item.pszText = FileView_Folder;
	item.cchTextMax = sizeof(FileView_Folder);
	item.mask = TVIF_TEXT;
	TreeView_GetItem(((LPNMHDR) lParam)->hwndFrom, &item);
	
	HTREEITEM p=TreeView_GetParent(Temp,i);
	
	TVITEM item1;
	item1.hItem = p;
	item1.pszText = FileView_File;
	item1.cchTextMax = sizeof(FileView_File);
	item1.mask = TVIF_TEXT;
	TreeView_GetItem(((LPNMHDR) lParam)->hwndFrom, &item1);

	if (!strcmp(FileView_Folder, "Fog"))
	{
		SelectedProperties = 1; 
		SetDlgItemText(BackDrop_hWnd,IDC_ITEMHEADER,(LPCTSTR)"Fog options");
		Update_CreateFogListView();
		SetDlgItemText(OptionsDlgHwnd,IDC_STINFO,(LPCSTR)" Settings for scene Fog");
		return;
	}
	if (!strcmp(FileView_Folder, "Main Light"))
	{
		SelectedProperties = 2; 
		SetDlgItemText(BackDrop_hWnd,IDC_ITEMHEADER,(LPCTSTR)"Main Light options");
		Update_CreateMainLightListView();
		SetDlgItemText(OptionsDlgHwnd,IDC_STINFO,(LPCSTR)" Option for the main light in the scene");
		return;
	}
	if (!strcmp(FileView_Folder, "Composite Map"))
	{
		SelectedProperties = 3; 
		SetDlgItemText(BackDrop_hWnd,IDC_ITEMHEADER,(LPCTSTR)"Composite Map options");
		//Update_CreateCompositeListView();
		SetDlgItemText(OptionsDlgHwnd,IDC_STINFO,(LPCSTR)" Options for Composite Map");
		return;
	}
	if (!strcmp(FileView_Folder, "Sound"))
	{
		SelectedProperties = 4; 
		SetDlgItemText(BackDrop_hWnd,IDC_ITEMHEADER,(LPCTSTR)"Sound options");
		Update_CreateSoundListView();
		SetDlgItemText(OptionsDlgHwnd,IDC_STINFO,(LPCSTR)" Main background Sound options");
		return;
	}
	if (!strcmp(FileView_Folder, "Sky"))
	{
		SelectedProperties = 5; 
		SetDlgItemText(BackDrop_hWnd,IDC_ITEMHEADER,(LPCTSTR)"Sky options");
		Update_CreateSkyListView();
		SetDlgItemText(OptionsDlgHwnd,IDC_STINFO,(LPCSTR)" Various options for the main Sky");
		return;
	}
}

// *************************************************************************
// *				Update_CreateSkyListView Terry Bernie			 	   *
// *************************************************************************
void GD19_Environment::Update_CreateSkyListView(void)
{
	char Chr_Enabled[10];
	char Chr_Curvature[10];
	char Chr_Tiling[10];
	char Chr_Distance[10];

	if (App->Cl_Scene_Data->S_Scene[0]->Sky[0].Enabled == 1)
	{
		strcpy(Chr_Enabled,"True");
	}
	else
	{
		strcpy(Chr_Enabled,"Flase");
	}

	sprintf(Chr_Curvature,"%.3f",App->Cl_Scene_Data->S_Scene[0]->Sky[0].Curvature);
	sprintf(Chr_Tiling,"%.3f",App->Cl_Scene_Data->S_Scene[0]->Sky[0].Tiling);
	sprintf(Chr_Distance,"%.3f",App->Cl_Scene_Data->S_Scene[0]->Sky[0].Distance);

	const int NUM_ITEMS = 5;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Enable",			grid[1][0] = Chr_Enabled;
	grid[0][1] = "Type",			grid[1][1] = "SkyDome";
	grid[0][2] = "Material",		grid[1][2] = "Examples/CloudySky";
	grid[0][3] = "Curvature",		grid[1][3] = Chr_Curvature;
	grid[0][4] = "Tiling",			grid[1][4] = Chr_Tiling;
	
	
	
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
// *				Update_CreateFogListView Terry Bernie			 	   *
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


	if (App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn == 1)
	{
		strcpy(chr_FogOn,"True");
	}
	else
	{
		strcpy(chr_FogOn,"Flase");
	}

	sprintf(chr_Density,"%f",App->Cl_Scene_Data->S_Scene[0]->Fog[0].Density);
	sprintf(chr_Start,"%.2f",App->Cl_Scene_Data->S_Scene[0]->Fog[0].Start);
	sprintf(chr_End,"%.2f",App->Cl_Scene_Data->S_Scene[0]->Fog[0].End);

	sprintf(chr_Mode,"%i",App->Cl_Scene_Data->S_Scene[0]->Fog[0].Mode);


	float mRed = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.x;
	float mGreen = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.y;
	float mBlue = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.z;
	
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
// *			Update_CreateMainLightListView Terry Bernie 		 	   *
// *************************************************************************
void GD19_Environment::Update_CreateMainLightListView(void)
{
	Ogre::Real mRed=0;
	Ogre::Real mGreen=0;
	Ogre::Real mBlue=0;

	mRed = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.x;
	mGreen = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.y;
	mBlue = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.z;
	
	char Chr_Ambient[100];
	sprintf(Chr_Ambient,"%.2f %.2f %.2f",mRed,mGreen,mBlue);

	mRed = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.x;
	mGreen = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.y;
	mBlue = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.z;
	
	char Chr_Diffuse[100];
	sprintf(Chr_Diffuse,"%.2f %.2f %.2f",mRed,mGreen,mBlue);

	mRed = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.x;
	mGreen = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.y;
	mBlue = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.z;
	
	char Chr_Specular[100];
	sprintf(Chr_Specular,"%.2f %.2f %.2f",mRed,mGreen,mBlue);

	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Ambient",		grid[1][0] =Chr_Ambient;
	grid[0][1] = "Diffuse",		grid[1][1] =Chr_Diffuse;
	grid[0][2] = "Specular",	grid[1][2] =Chr_Specular;
	grid[0][3] = " ",			grid[1][3] = " ";
	grid[0][4] = "PosX",		grid[1][4] = " ";
	grid[0][5] = "PosY",		grid[1][5] = " ";
	grid[0][6] = "Posz",		grid[1][6] = " ";
	
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
// *				Update_CreateSoundListView Terry Bernie			 	   *
// *************************************************************************
void GD19_Environment::Update_CreateSoundListView(void)
{
	char Chr_Volume[100];
	char Chr_Play[100];
	char Chr_Loop[100];
	sprintf(Chr_Volume,"%.1f", App->SBC_Scene->B_Area[0]->S_Environment[0]->SndVolume);

	// Play
	if (App->SBC_Scene->B_Area[0]->S_Environment[0]->Play == 1)
	{
		strcpy(Chr_Play,"True");
	}
	else
	{
		strcpy(Chr_Play,"False");
	}

	//// Loop
	//if (App->Cl_Scene_Data->S_Scene[0]->Sound[0].Loop == 1)
	//{
	//	strcpy(Chr_Loop,"True");
	//}
	//else
	//{
	//	strcpy(Chr_Loop,"False");
	//}

	const int NUM_ITEMS = 4;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Track",		grid[1][0] = App->SBC_Scene->B_Area[0]->S_Environment[0]->Sound_File;
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
// *				Create_GeneralListBackDrop Terry Bernie				   *
// *************************************************************************
void GD19_Environment::Create_GeneralListBackDrop(HWND hDlg)
{
	 BackDrop_hWnd = CreateDialog(App->hInst,(LPCTSTR)IDD_ENVIRONMENTBACKDROP,hDlg,(DLGPROC)BackDrop_Proc);
}
// *************************************************************************
// *						BackDrop_Proc  (Terry Bernie)				   *
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
							App->Cl_Environment->Props_OnClick(lParam);
							break;
						}
					case NM_DBLCLK:
						{
							//App->Class_Dlg_Options->PropsDBLCLK_OnClick(lParam);
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
// *					Create_GeneralList Terry Bernie					   *
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
	HFONT Font;
	Font = CreateFont( -15,0,0,0,FW_NORMAL,0,0,0,0,OUT_TT_ONLY_PRECIS ,0,0,0, "Aerial Black");
	SendMessage(General_hLV,WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));
}

// *************************************************************************
// *	  				GetListControls Terry Bernie					   *
// *************************************************************************
void GD19_Environment::GetListControls(void)
{
	mTreeCon = GetDlgItem(OptionsDlgHwnd,IDC_OPTIOINSTREE);
	mPropsCon = General_hLV;
}
// *************************************************************************
// *					Init_FileView Terry Bernie	                   	   *
// *************************************************************************
void GD19_Environment::Init_FileView(void)
{
	mImageList=ImageList_Create(32,32, ILC_COLOR24,2,0);
	//hBitMap=LoadBitmap(App->hInst,MAKEINTRESOURCE(IDB_SELECTON));
	//ImageList_Add(mImageList,hBitMap,NULL);
	//DeleteObject(hBitMap);
	//
	//// Speeds
	//hBitMap=LoadBitmap(App->hInst,MAKEINTRESOURCE(IDB_SPEEDOFF));
	//ImageList_Add(mImageList,hBitMap,NULL);
	//DeleteObject(hBitMap);
	//			 
	//hBitMap=LoadBitmap(App->hInst,MAKEINTRESOURCE(IDB_SPEEDON));
	//ImageList_Add(mImageList,hBitMap,NULL);
	//DeleteObject(hBitMap);

	//// Debug
	//hBitMap=LoadBitmap(App->hInst,MAKEINTRESOURCE(IDB_DEBUGOFF));
	//ImageList_Add(mImageList,hBitMap,NULL);
	//DeleteObject(hBitMap);
	//			 
	//hBitMap=LoadBitmap(App->hInst,MAKEINTRESOURCE(IDB_DEBUGON));
	//ImageList_Add(mImageList,hBitMap,NULL);
	//DeleteObject(hBitMap);

	//// Keys
	//hBitMap=LoadBitmap(App->hInst,MAKEINTRESOURCE(IDB_KEYBOARDOFF));
	//ImageList_Add(mImageList,hBitMap,NULL);
	//DeleteObject(hBitMap);
	//			 
	//hBitMap=LoadBitmap(App->hInst,MAKEINTRESOURCE(IDB_KEYBOARDON));
	//ImageList_Add(mImageList,hBitMap,NULL);
	//DeleteObject(hBitMap);

	// StartUp
	hBitMap=LoadBitmap(App->hInst,MAKEINTRESOURCE(IDB_STARTUPOFF));
	ImageList_Add(mImageList,hBitMap,NULL);
	DeleteObject(hBitMap);
				 
	hBitMap=LoadBitmap(App->hInst,MAKEINTRESOURCE(IDB_STARTUPON));
	ImageList_Add(mImageList,hBitMap,NULL);
	DeleteObject(hBitMap);
}

// *************************************************************************
// *						AddOptions Terry Bernie					 	   *
// *************************************************************************
void GD19_Environment::AddOptions(void)
{
	tvinsert.hParent = mRoot1;		// top most level no need handle
	tvinsert.hInsertAfter=TVI_LAST; // work as root level
	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText="Main Light";
	tvinsert.item.iImage= 0 ;
	tvinsert.item.iSelectedImage = 1;
	mParent=(HTREEITEM)SendDlgItemMessage(OptionsDlgHwnd,IDC_OPTIOINSTREE,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

	tvinsert.hParent = mRoot1;		// top most level no need handle
	tvinsert.hInsertAfter=TVI_LAST; // work as root level
	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText="Sound";
	tvinsert.item.iImage= 0 ;
	tvinsert.item.iSelectedImage = 1;
	mParent=(HTREEITEM)SendDlgItemMessage(OptionsDlgHwnd,IDC_OPTIOINSTREE,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

	//tvinsert.hParent = mRoot1;		// top most level no need handle
	//tvinsert.hInsertAfter=TVI_LAST; // work as root level
	//tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	//tvinsert.item.pszText="Composite Map";
	//tvinsert.item.iImage= 0 ;
	//tvinsert.item.iSelectedImage = 1;
	//mParent=(HTREEITEM)SendDlgItemMessage(OptionsDlgHwnd,IDC_OPTIOINSTREE,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

	tvinsert.hParent = mRoot1;		// top most level no need handle
	tvinsert.hInsertAfter=TVI_LAST; // work as root level
	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText="Fog";
	tvinsert.item.iImage= 0 ;
	tvinsert.item.iSelectedImage = 1;
	mParent=(HTREEITEM)SendDlgItemMessage(OptionsDlgHwnd,IDC_OPTIOINSTREE,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

	tvinsert.hParent = mRoot1;		// top most level no need handle
	tvinsert.hInsertAfter=TVI_LAST; // work as root level
	tvinsert.item.mask=TVIF_TEXT|TVIF_IMAGE|TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText="Sky";
	tvinsert.item.iImage= 0;
	tvinsert.item.iSelectedImage = 1;
	mParent=(HTREEITEM)SendDlgItemMessage(OptionsDlgHwnd,IDC_OPTIOINSTREE,TVM_INSERTITEM,0,(LPARAM)&tvinsert);

	HWND TTemp=GetDlgItem(OptionsDlgHwnd,IDC_OPTIOINSTREE);

	HTREEITEM root=TreeView_GetRoot(TTemp);		

	TreeView_SelectItem(TTemp,root);
}

// *************************************************************************
// *						Props_OnClick Terry Bernie			 		   *
// *************************************************************************
bool GD19_Environment::Props_OnClick(LPARAM lParam)
{
	int result = 1;
	int SelectionIndex = 0;

	LPNMLISTVIEW Selection = (LPNMLISTVIEW) lParam;
	SelectionIndex = Selection->iItem;
	ListView_GetItemText(General_hLV,SelectionIndex, 0, btext, 255);

	// Fog
	result = strcmp(btext, "Visible");
	if (result == 0 && SelectedProperties == 1)
	{
		strcpy(App->Cl_Dialogs->btext,"Set Fog Visiblity");

		App->Cl_Dialogs->TrueFlase = App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn;

		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if(App->Cl_Dialogs->TrueFlase == 1)
			{
				App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn = 1;
				EnableFog(true);
			}
			else
			{
				App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn = 0;
				EnableFog(false);
			}

			Update_CreateFogListView();
		}
		return 1;
	}
	result = strcmp(btext, "Start");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Set Fog Start Distance");

		sprintf(App->Cl_Dialogs->Chr_Float,"%f",App->Cl_Scene_Data->S_Scene[0]->Fog[0].Start);
		
		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{
			App->Cl_Scene_Data->S_Scene[0]->Fog[0].Start = App->Cl_Dialogs->mFloat;
			if (App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn == 1)
			{
				EnableFog(true);
			}
			Update_CreateFogListView();
		//	Flags[0]->RenderBackGround = 1;
		}
		return 1;
	}

	result = strcmp(btext, "End");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Set Fog End Distance");

		sprintf(App->Cl_Dialogs->Chr_Float,"%f",App->Cl_Scene_Data->S_Scene[0]->Fog[0].End);
		
		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{
			App->Cl_Scene_Data->S_Scene[0]->Fog[0].End = App->Cl_Dialogs->mFloat;
			if (App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn==1)
			{
				EnableFog(true);
			}
			Update_CreateFogListView();
		//	Flags[0]->RenderBackGround = 1;
		}
		return 1;
	}

	result = strcmp(btext, "Density");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Set Density Of Fog");

		sprintf(App->Cl_Dialogs->Chr_Float,"%f",App->Cl_Scene_Data->S_Scene[0]->Fog[0].Density);
		
		App->Cl_Dialogs->Dialog_Float();

		if (App->Cl_Dialogs->Canceled == 0)
		{
			App->Cl_Scene_Data->S_Scene[0]->Fog[0].Density = App->Cl_Dialogs->mFloat;
			if (App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn==1)
			{
				EnableFog(true);
			}
			Update_CreateFogListView();
		//	Flags[0]->RenderBackGround = 1;
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

			App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.x = (float)Red / 256;
			App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.y = (float)Green / 256;;
			App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.z = (float)Blue / 256;;

			Update_CreateFogListView();

			if (App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn == 1)
			{
				EnableFog(true);
			}

			Update_CreateFogListView();
			//Flags[0]->RenderBackGround = 1;
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

	// Main Light
	result = strcmp(btext, "Ambient");
	if (result == 0)
	{

		//strcpy_s(TextInt,App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Mode);
		App->SBC_FileIO->GetColor();

		if (App->SBC_FileIO->Cannceled == 0)
		{
			int Red = GetRValue(App->SBC_FileIO->color.rgbResult);
			int Green = GetGValue(App->SBC_FileIO->color.rgbResult);
			int Blue = GetBValue(App->SBC_FileIO->color.rgbResult);

			App->Cl_Scene_Data->S_Scene[0]->AmbientColour = Ogre::Vector3((float)Red/256,(float)Green/256,(float)Blue/256);

			Update_CreateMainLightListView();

			App->Cl19_Ogre->mSceneMgr->setAmbientLight(ColourValue((float)Red/256,(float)Green/256,(float)Blue/256));

		}
		return 1;
	}

	result = strcmp(btext, "Diffuse");
	if (result == 0)
	{

	//	strcpy_s(TextInt,App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Mode);
		App->SBC_FileIO->GetColor();

		if (App->SBC_FileIO->Cannceled==0)
		{
			int Red=GetRValue(App->SBC_FileIO->color.rgbResult);
			int Green=GetGValue(App->SBC_FileIO->color.rgbResult);
			int Blue=GetBValue(App->SBC_FileIO->color.rgbResult);

			App->Cl_Scene_Data->S_Scene[0]->DiffuseColour = Ogre::Vector3((float)Red/256,(float)Green/256,(float)Blue/256);

			Update_CreateMainLightListView();

			//App->Cl_Ogre->mSceneMgr->setDiffuseColour(ColourValue(rRed,rGreen,rBlue));

		}
       return 1;
	}

	result = strcmp(btext, "Specular");
	if (result == 0)
	{

	//	strcpy_s(TextInt,App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Mode);
		App->SBC_FileIO->GetColor();

		if (App->SBC_FileIO->Cannceled==0)
		{
			int Red=GetRValue(App->SBC_FileIO->color.rgbResult);
			int Green=GetGValue(App->SBC_FileIO->color.rgbResult);
			int Blue=GetBValue(App->SBC_FileIO->color.rgbResult);

			App->Cl_Scene_Data->S_Scene[0]->SpecularColour = Ogre::Vector3((float)Red/256,(float)Green/256,(float)Blue/256);

			Update_CreateMainLightListView();

			//App->Cl_Ogre->l->setSpecularColour(ColourValue(rRed,rGreen,rBlue));

		}
      return 1;
	}

	// Sound
	result = strcmp(btext, "Track");
	if (result == 0)
	{
		strcpy(App->SBC_SoundMgr->mSoundFile,App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFile);
		App->SBC_SoundMgr->SndVolume = App->Cl_Scene_Data->S_Scene[0]->Sound[0].Volume;
		App->SBC_SoundMgr->Dialog_SoundFile();

		//if (App->Class_Dlg_Com->Canceled == 0)
		{
			
			strcpy(App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFile,App->SBC_SoundMgr->mSoundFile);

			strcpy(App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFileAndPath,App->SBC_SoundMgr->Default_Folder);
			strcat(App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFileAndPath,"\\Media\\Sounds\\");
			strcat(App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFileAndPath,App->SBC_SoundMgr->mSoundFile);
			App->Cl_Scene_Data->S_Scene[0]->Sound[0].Volume = App->SBC_SoundMgr->SndVolume;

			App->Cl_Scene_Data->S_Scene[0]->Sound[0].Play = 1;

			Update_CreateSoundListView();
			
		}
		return 1;
	}

	result = strcmp(btext, "Play");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Play Main BackGround Track");

		App->Cl_Dialogs->TrueFlase = App->Cl_Scene_Data->S_Scene[0]->Sound[0].Play;

		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if(App->Cl_Dialogs->TrueFlase == 1)
			{
				App->Cl_Scene_Data->S_Scene[0]->Sound[0].Play = 1;
			}
			else
			{
				App->Cl_Scene_Data->S_Scene[0]->Sound[0].Play = 0;
			}

			Update_CreateSoundListView();
			
		}
		return 1;
	}
	result = strcmp(btext, "Loop");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext,"Loop BackGround Track");

		App->Cl_Dialogs->TrueFlase = App->Cl_Scene_Data->S_Scene[0]->Sound[0].Loop;

		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if(App->Cl_Dialogs->TrueFlase == 1)
			{
				App->Cl_Scene_Data->S_Scene[0]->Sound[0].Loop = 1;
			}
			else
			{
				App->Cl_Scene_Data->S_Scene[0]->Sound[0].Loop = 0;
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

		App->Cl_Dialogs->TrueFlase = App->Cl_Scene_Data->S_Scene[0]->Sky[0].Enabled;
		
		App->Cl_Dialogs->Dialog_TrueFlase(App->MainHwnd);

		if (App->Cl_Dialogs->Canceled == 0)
		{
			if(App->Cl_Dialogs->TrueFlase == 1)
			{
				App->Cl_Scene_Data->S_Scene[0]->Sky[0].Enabled = 1;
				SetSky(1);
			}
			else
			{
				App->Cl_Scene_Data->S_Scene[0]->Sky[0].Enabled = 0;
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
// *	  					SetSky Terry Bernie							   *
// *************************************************************************
void GD19_Environment::SetSky(bool Enable)
{
	App->Cl19_Ogre->mSceneMgr->setSkyDome(Enable,
	App->Cl_Scene_Data->S_Scene[0]->Sky[0].Material,
	App->Cl_Scene_Data->S_Scene[0]->Sky[0].Curvature,
	App->Cl_Scene_Data->S_Scene[0]->Sky[0].Tiling,
	App->Cl_Scene_Data->S_Scene[0]->Sky[0].Distance);
}

// *************************************************************************
// *	  				  EnableFog	Terry Bernie						   *
// *************************************************************************
bool GD19_Environment::EnableFog(bool SetFog)
{
	if (SetFog == true)
	{
		float Start = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Start;
		float End = App->Cl_Scene_Data->S_Scene[0]->Fog[0].End;
		float Density = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Density;

		float x = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.x;
		float y = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.y;
		float z = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.z;

		App->Cl19_Ogre->mSceneMgr->setFog(FOG_LINEAR, ColourValue(x, y, z), Density, (Ogre::Real)Start, (Ogre::Real)End);
	}
	else
	{
		App->Cl19_Ogre->mSceneMgr->setFog(FOG_NONE, ColourValue(0.7, 0.7, 0.8), 0, 100, 1000);
	}
	

	
	return 1;
}