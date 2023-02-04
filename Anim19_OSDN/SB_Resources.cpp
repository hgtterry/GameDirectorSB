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
#include "SB_Resources.h"


SB_Resources::SB_Resources()
{
	FX_General_hLV = nullptr;
	Active_MeshMaterials = 0;
	Active_Textures = 1;

	Show_App_Res_Flag = 0;
	Show_MV_Res_Flag = 0;
	Show_Project_Res_Flag = 0;
}


SB_Resources::~SB_Resources()
{
}

// *************************************************************************
// *	  					Start_Resources Terry Bernie				   *
// *************************************************************************
void SB_Resources::Start_Resources(HWND hDlg)
{
	DialogBox(App->hInst, (LPCTSTR)IDD_RESOURCESMATERIAL,hDlg, (DLGPROC)Resources_Proc);
}
// *************************************************************************
// *							Materials_Proc	  						   *
// *************************************************************************
LRESULT CALLBACK SB_Resources::Resources_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		App->SetTitleBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_ST_BANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BT_SCENEMESH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STCOUNT, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTMATSF, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTMESHSF, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTTEXTSF, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		App->SBC_Resources->CreateListGeneral_FX(hDlg);

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_ST_BANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->DialogBackGround;
		}

		if (GetDlgItem(hDlg, IDC_STCOUNT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
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

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		if (some_item->idFrom == IDC_BT_APPRESOURCES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Resources->Show_App_Res_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_PRJRESOURCES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Resources->Show_Project_Res_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTMVRESOURCES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Toggle(item, App->SBC_Resources->Show_MV_Res_Flag);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BT_SCENEMESH && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTMATSF && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTMESHSF && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTTEXTSF && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}


	case WM_COMMAND:


		//if (LOWORD(wParam) == IDC_MESHMATERIALS)
		//{
		//	App->GDCL_Dialogs->Start_Gen_ListBox(Enums::ListBox_Resource_MeshMaterials);
		//	return TRUE;
		//}

		//if (LOWORD(wParam) == IDC_Paths)
		//{
		//	App->GDCL_Dialogs->Start_Gen_ListBox(Enums::ListBox_Resource_Paths);
		//	return TRUE;
		//}

		if (LOWORD(wParam) == IDC_MATERIALS)
		{
			App->SBC_Resources->ShowAllMaterials();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_TEXTURES)
		{
			App->SBC_Resources->ShowAllTextures();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_MESH)
		{
			App->SBC_Resources->ShowAllMeshes();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_USED)
		{
			App->SBC_Resources->ShowUsedMaterials();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_PRJRESOURCES)
		{
			SetDlgItemText(hDlg, IDC_ST_BANNER, (LPCTSTR)"Project Resources");

			App->SBC_Resources->Show_Project_Res();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_APPRESOURCES)
		{
			SetDlgItemText(hDlg, IDC_ST_BANNER, (LPCTSTR)"App Resources");

			App->SBC_Resources->Show_App_Res();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTMVRESOURCES)
		{
			SetDlgItemText(hDlg, IDC_ST_BANNER, (LPCTSTR)"Mesh Viewer Resources");

			App->SBC_Resources->Show_MV_Res();
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BT_SCENEMESH)
		{
			SetDlgItemText(hDlg, IDC_ST_BANNER, (LPCTSTR)"Scene Meshes");
			App->SBC_Resources->Show_Scene_Meshes(hDlg);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTMATSF)
		{
			char Message[MAX_PATH];
			strcpy(Message, "Scene Folder Materials - ");
			strcat(Message, App->SBC_Project->m_Main_Assets_Path);

			SetDlgItemText(hDlg, IDC_ST_BANNER, (LPCTSTR)Message);

			ListView_DeleteAllItems(App->SBC_Resources->FX_General_hLV);
			App->SBC_Resources->SearchFolders("*.material");
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTMESHSF)
		{
			char Message[MAX_PATH];
			strcpy(Message, "Scene Folder Mesh - ");
			strcat(Message, App->SBC_Project->m_Main_Assets_Path);

			SetDlgItemText(hDlg, IDC_ST_BANNER, (LPCTSTR)Message);

			ListView_DeleteAllItems(App->SBC_Resources->FX_General_hLV);
			App->SBC_Resources->SearchFolders("*.mesh");
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTTEXTSF)
		{
			char Message[MAX_PATH];
			strcpy(Message, "Scene Folder Textures - ");
			strcat(Message, App->SBC_Project->m_Main_Assets_Path);

			SetDlgItemText(hDlg, IDC_ST_BANNER, (LPCTSTR)Message);

			ListView_DeleteAllItems(App->SBC_Resources->FX_General_hLV);
			App->SBC_Resources->SearchFolders("*.bmp");
			App->SBC_Resources->SearchFolders("*.tga");
			App->SBC_Resources->SearchFolders("*.jpg");
			App->SBC_Resources->SearchFolders("*.png");
			App->SBC_Resources->SearchFolders("*.dds");

			return TRUE;
		}
	
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		break;

	}
	return FALSE;
}

// *************************************************************************
// *				CreateListGeneral_FX Terry Bernie					   *
// *************************************************************************
bool SB_Resources::CreateListGeneral_FX(HWND hDlg)
{
	int NUM_COLS = 4;
	FX_General_hLV = CreateWindowEx(0, WC_LISTVIEW, "",
		WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT |  LVS_SHOWSELALWAYS, 2, 2,
		1280, 405, hDlg, 0, App->hInst, NULL);

	DWORD exStyles = LVS_EX_GRIDLINES;

	ListView_SetExtendedListViewStyleEx(FX_General_hLV, exStyles, exStyles);

	ListView_SetBkColor(FX_General_hLV, RGB(250, 250, 250));
	ListView_SetTextBkColor(FX_General_hLV, RGB(250, 250, 250));

	LV_COLUMN lvC;
	memset(&lvC, 0, sizeof(LV_COLUMN));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	std::string headers[] =
	{
		"Script", "Material File","Used","Path"
	};
	int headerSize[] =
	{
		165,380,70,250
	};

	//Groups

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_InsertColumn(FX_General_hLV, header, &lvC);
	}
	HFONT Font;
	Font = CreateFont(-12, 0, 0, 0, FW_NORMAL, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");
	SendMessage(FX_General_hLV, WM_SETFONT, (WPARAM)Font, MAKELPARAM(TRUE, 0));

	//ShowAllMaterials();
	ShowAllTextures();
	return 1;
}

// *************************************************************************
// *					Show_Scene_Meshes Terry Bernie	 			 	   *
// *************************************************************************
bool SB_Resources::Show_Scene_Meshes(HWND hDlg)
{
	Ogre::String st;
	int NUM_COLS = 4;

	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	ListView_DeleteAllItems(FX_General_hLV);

	LV_COLUMN lvC;
	memset(&lvC, 0, sizeof(LV_COLUMN));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	std::string headers[] =
	{
		"Mesh", "Material File","Usage","Path"
	};
	int headerSize[] =
	{
		165,180,170,250
	};

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_SetColumn(FX_General_hLV, header, &lvC);
	}

	int	 pRow = 0;
	char pMeshName[MAX_PATH];
	char pMaterialName[MAX_PATH];
	char pUsage[MAX_PATH];
	
	int Count = 0;
	while (Count < App->SBC_Scene->Object_Count)
	{
		strcpy(pMeshName, App->SBC_Scene->B_Object[Count]->Mesh_FileName);
		strcpy(pMaterialName, App->SBC_Scene->B_Object[Count]->Material_File);

		if (App->SBC_Scene->B_Object[Count]->UsageEX == 777)
		{
			strcpy(pUsage, "In Scene");
		}
		else
		{
			strcpy(pUsage, "Editor");
		}
		
		pitem.iItem = pRow;
		pitem.pszText = pMeshName;

		ListView_InsertItem(FX_General_hLV, &pitem);
		ListView_SetItemText(FX_General_hLV, pRow, 1, pMaterialName);
		ListView_SetItemText(FX_General_hLV, pRow, 2, pUsage);
		ListView_SetItemText(FX_General_hLV, pRow, 3, " ");

		pRow++;

		Count++;
	}

	char num[256];
	_itoa(Count, num, 10);
	SetDlgItemText(hDlg, IDC_STCOUNT, (LPCTSTR)num);
	
	return 1;
}

// *************************************************************************
// *					ShowAllMaterials Terry Bernie	 			 	   *
// *************************************************************************
bool SB_Resources::ShowAllMaterials()
{
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	ListView_DeleteAllItems(FX_General_hLV);

	int	 pRow = 0;
	char pScriptName[255];
	char pScriptFile[255];
	char pUsed[255];
	bool pIsLoaded = 0;
	Ogre::String st;
	Ogre::ResourcePtr pp;
	Ogre::ResourceManager::ResourceMapIterator materialIterator = Ogre::MaterialManager::getSingleton().getResourceIterator();

	while (materialIterator.hasMoreElements())
	{
		strcpy(pScriptName, materialIterator.peekNextValue()->getName().c_str());

		pp = Ogre::MaterialManager::getSingleton().getByName(pScriptName);
		st = pp->getOrigin();
		pIsLoaded = pp->isLoaded();

		if (pIsLoaded == 1)
		{
			strcpy(pUsed, "Yes");
		}
		else
		{
			strcpy(pUsed, "No");
		}

		//--------------------------------
		if (st == "")
		{
			strcpy(pScriptFile, "Internal");
			strcpy(ResourcePath, "Internal");

		}
		else if (st == "SdkTrays.material")
		{
			strcpy(pScriptFile, st.c_str());
			strcpy(ResourcePath, "packs\\SdkTrays.zip");
		}
		else if (st == "OgreCore.material")
		{
			strcpy(pScriptFile, st.c_str());
			strcpy(ResourcePath, "packs\\OgreCore.zip");
		}
		else if (st == "OgreProfiler.material")
		{
			strcpy(pScriptFile, st.c_str());
			strcpy(ResourcePath, "packs\\OgreCore.zip");
		}
		else if (st == "PhysCore.material")
		{
			strcpy(pScriptFile, st.c_str());
			strcpy(ResourcePath, "packs\\GDCore.zip");
		}
		else
		{
			strcpy(pScriptFile, st.c_str());
			//App->GDCL_Resources->SearchFolders(pScriptFile,"Media\\materials\\");
			Start_List_Folders(NULL, pScriptFile, 0);

		}

		pitem.iItem = pRow;
		pitem.pszText = pScriptName;

		ListView_InsertItem(FX_General_hLV, &pitem);
		ListView_SetItemText(FX_General_hLV, pRow, 1, pScriptFile);
		ListView_SetItemText(FX_General_hLV, pRow, 2, pUsed);
		ListView_SetItemText(FX_General_hLV, pRow, 3, ResourcePath);

		pRow++;

		materialIterator.moveNext();
	}

	return 1;
}

// *************************************************************************
// *					ShowUsedMaterials Terry Bernie	 			 	   *
// *************************************************************************
bool SB_Resources::ShowUsedMaterials()
{
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	ListView_DeleteAllItems(FX_General_hLV);

	int	 pRow = 0;
	char pScriptName[255];
	char pScriptFile[255];
	char pUsed[255];
	bool pIsLoaded = 0;
	Ogre::String st;
	Ogre::ResourcePtr pp;
	Ogre::ResourceManager::ResourceMapIterator materialIterator = Ogre::MaterialManager::getSingleton().getResourceIterator();

	while (materialIterator.hasMoreElements())
	{

		strcpy(pScriptName, materialIterator.peekNextValue()->getName().c_str());

		pp = Ogre::MaterialManager::getSingleton().getByName(pScriptName);
		st = pp->getOrigin();
		pIsLoaded = pp->isLoaded();

		if (pIsLoaded == 1)
		{
			strcpy(pUsed, "Yes");

			//--------------------------------
			if (st == "")
			{
				strcpy(pScriptFile, "Internal");
			}
			else if (st == "SdkTrays.material")
			{
				strcpy(pScriptFile, st.c_str());
				strcpy(ResourcePath, "packs\\SdkTrays.zip");
			}
			else if (st == "OgreCore.material")
			{
				strcpy(pScriptFile, st.c_str());
				strcpy(ResourcePath, "packs\\OgreCore.zip");
			}
			else if (st == "OgreProfiler.material")
			{
				strcpy(pScriptFile, st.c_str());
				strcpy(ResourcePath, "packs\\OgreCore.zip");
			}
			else if (st == "PhysCore.material")
			{
				strcpy(pScriptFile, st.c_str());
				strcpy(ResourcePath, "packs\\GDCore.zip");
			}
			else
			{
				strcpy(pScriptFile, st.c_str());
				//SearchFolders(pScriptFile,"Media\\materials\\");
				Start_List_Folders(NULL, pScriptFile, 0);
			}

			pitem.iItem = pRow;
			pitem.pszText = pScriptName;

			ListView_InsertItem(FX_General_hLV, &pitem);
			ListView_SetItemText(FX_General_hLV, pRow, 1, pScriptFile);
			ListView_SetItemText(FX_General_hLV, pRow, 2, pUsed);
			ListView_SetItemText(FX_General_hLV, pRow, 3, ResourcePath);

			pRow++;
		}

		materialIterator.moveNext();
	}

	return 1;
}

// *************************************************************************
// *					ShowAllTextures Terry Bernie				 	   *
// *************************************************************************
bool SB_Resources::ShowAllTextures()
{
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	ListView_DeleteAllItems(FX_General_hLV);
	bool pIsLoaded = 0;
	int	 pRow = 0;
	//	char buff[255];
	char pUsed[255];
	char pScriptName[255];
	//	char pScriptFile[255];
	//	char chr_AsSkell[255];
	bool pHasSkel = 0;
	Ogre::String st;
	Ogre::ResourcePtr pp;

	Ogre::ResourceManager::ResourceMapIterator TextureIterator = Ogre::TextureManager::getSingleton().getResourceIterator();

	while (TextureIterator.hasMoreElements())
	{
		//strcpy(pScriptName,(static_cast<Ogre::MaterialPtr>(TextureIterator.peekNextValue()))->getName().c_str());

		strcpy(pScriptName, TextureIterator.peekNextValue()->getName().c_str());

		pp = Ogre::TextureManager::getSingleton().getByName(pScriptName);
		pIsLoaded = pp->isLoaded();

		if (pIsLoaded == 1)
		{
			strcpy(pUsed, "Yes");
		}
		else
		{
			strcpy(pUsed, "No");
		}

		char Filename[255];
		char ext[255];
		char JustFile[255];
		char SubFolder[255];
		_splitpath(pScriptName, NULL, SubFolder, Filename, ext);
		strcpy(JustFile, Filename);
		strcat(JustFile, ext);

		/*if(SubFolder[0] > 0)
		{
		App->Say(SubFolder);
		}*/

		Start_List_Folders(NULL, JustFile, 0);

		pitem.iItem = pRow;
		pitem.pszText = JustFile;

		ListView_InsertItem(FX_General_hLV, &pitem);
		ListView_SetItemText(FX_General_hLV, pRow, 1, ResourcePath);
		ListView_SetItemText(FX_General_hLV, pRow, 2, pUsed);

		pRow++;

		TextureIterator.moveNext();
	}

	return 1;
}

// **************************************************************************
// *			Show_App_Res Terry:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
bool SB_Resources::Show_App_Res()
{
	ListView_DeleteAllItems(FX_General_hLV);

	bool Test = Ogre::ResourceGroupManager::getSingleton().resourceGroupExists(App->SBC_Ogre->App_Resource_Group);

	if (Test == 1)
	{

		Ogre::String st;
		int NUM_COLS = 4;

		LV_ITEM pitem;
		memset(&pitem, 0, sizeof(LV_ITEM));
		pitem.mask = LVIF_TEXT;

		LV_COLUMN lvC;
		memset(&lvC, 0, sizeof(LV_COLUMN));
		lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvC.fmt = LVCFMT_LEFT;  // left-align the column
		std::string headers[] =
		{
			"Resource Group", "Path","Type"," "
		};
		int headerSize[] =
		{
			165,380,170,250
		};

		for (int header = 0; header < NUM_COLS; header++)
		{
			lvC.iSubItem = header;
			lvC.cx = headerSize[header]; // width of the column, in pixels
			lvC.pszText = const_cast<char*>(headers[header].c_str());
			ListView_SetColumn(FX_General_hLV, header, &lvC);
		}

		int	 pRow = 0;
		char pPath[MAX_PATH];
		char chr_Type[255];

		Ogre::ResourceGroupManager::LocationList resLocationsList = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(App->SBC_Ogre->App_Resource_Group);
		Ogre::ResourceGroupManager::LocationList::iterator it = resLocationsList.begin();
		Ogre::ResourceGroupManager::LocationList::iterator itEnd = resLocationsList.end();

		for (; it != itEnd; ++it)
		{
			pitem.iItem = pRow;
			pitem.pszText = "Project_Resource_Group";

			strcpy(pPath, (*it)->archive->getName().c_str());
			strcpy(chr_Type, (*it)->archive->getType().c_str());

			ListView_InsertItem(FX_General_hLV, &pitem);
			ListView_SetItemText(FX_General_hLV, pRow, 1, pPath);
			ListView_SetItemText(FX_General_hLV, pRow, 2, chr_Type);
			ListView_SetItemText(FX_General_hLV, pRow, 3, " ");
		}
	}
	else
	{
		App->Say("No Project Loaded");

		return 0;
	}

	return 1;
}

// *************************************************************************
// *		Show_Project_Res:- Terry and Hazel Flanigan 2022 		 	   *
// *************************************************************************
bool SB_Resources::Show_Project_Res()
{
	ListView_DeleteAllItems(FX_General_hLV);

	bool Test = Ogre::ResourceGroupManager::getSingleton().resourceGroupExists(App->SBC_Scene->Project_Resource_Group);

	if (Test == 1)
	{

		Ogre::String st;
		int NUM_COLS = 4;

		LV_ITEM pitem;
		memset(&pitem, 0, sizeof(LV_ITEM));
		pitem.mask = LVIF_TEXT;

		LV_COLUMN lvC;
		memset(&lvC, 0, sizeof(LV_COLUMN));
		lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvC.fmt = LVCFMT_LEFT;  // left-align the column
		std::string headers[] =
		{
			"Resource Group", "Path","Type"," "
		};
		int headerSize[] =
		{
			165,380,170,250
		};

		for (int header = 0; header < NUM_COLS; header++)
		{
			lvC.iSubItem = header;
			lvC.cx = headerSize[header]; // width of the column, in pixels
			lvC.pszText = const_cast<char*>(headers[header].c_str());
			ListView_SetColumn(FX_General_hLV, header, &lvC);
		}

		int	 pRow = 0;
		char pPath[MAX_PATH];
		char chr_Type[255];

		Ogre::ResourceGroupManager::LocationList resLocationsList = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(App->SBC_Scene->Project_Resource_Group);
		Ogre::ResourceGroupManager::LocationList::iterator it = resLocationsList.begin();
		Ogre::ResourceGroupManager::LocationList::iterator itEnd = resLocationsList.end();

		for (; it != itEnd; ++it)
		{
			pitem.iItem = pRow;
			pitem.pszText = "Project_Resource_Group";

			strcpy(pPath, (*it)->archive->getName().c_str());
			strcpy(chr_Type, (*it)->archive->getType().c_str());

			ListView_InsertItem(FX_General_hLV, &pitem);
			ListView_SetItemText(FX_General_hLV, pRow, 1, pPath);
			ListView_SetItemText(FX_General_hLV, pRow, 2, chr_Type);
			ListView_SetItemText(FX_General_hLV, pRow, 3, " ");
		}
	}
	else
	{
		App->Say("No Project Loaded");

		return 0;
	}

	return 1;
}

// **************************************************************************
// *			Show_MV_Res Terry:- Terry and Hazel Flanigan 2022			*
// **************************************************************************
bool SB_Resources::Show_MV_Res()
{
	ListView_DeleteAllItems(FX_General_hLV);

	bool Test = Ogre::ResourceGroupManager::getSingleton().resourceGroupExists(App->SBC_MeshViewer->MV_Resource_Group);

	if (Test == 1)
	{

		Ogre::String st;
		int NUM_COLS = 4;

		LV_ITEM pitem;
		memset(&pitem, 0, sizeof(LV_ITEM));
		pitem.mask = LVIF_TEXT;

		LV_COLUMN lvC;
		memset(&lvC, 0, sizeof(LV_COLUMN));
		lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
		lvC.fmt = LVCFMT_LEFT;  // left-align the column
		std::string headers[] =
		{
			"Resource Group", "Path","Type"," "
		};
		int headerSize[] =
		{
			165,380,170,250
		};

		for (int header = 0; header < NUM_COLS; header++)
		{
			lvC.iSubItem = header;
			lvC.cx = headerSize[header]; // width of the column, in pixels
			lvC.pszText = const_cast<char*>(headers[header].c_str());
			ListView_SetColumn(FX_General_hLV, header, &lvC);
		}

		int	 pRow = 0;
		char pPath[MAX_PATH];
		char chr_Type[255];

		Ogre::ResourceGroupManager::LocationList resLocationsList = Ogre::ResourceGroupManager::getSingleton().getResourceLocationList(App->SBC_MeshViewer->MV_Resource_Group);
		Ogre::ResourceGroupManager::LocationList::iterator it = resLocationsList.begin();
		Ogre::ResourceGroupManager::LocationList::iterator itEnd = resLocationsList.end();

		for (; it != itEnd; ++it)
		{
			pitem.iItem = pRow;
			pitem.pszText = "Project_Resource_Group";

			strcpy(pPath, (*it)->archive->getName().c_str());
			strcpy(chr_Type, (*it)->archive->getType().c_str());

			ListView_InsertItem(FX_General_hLV, &pitem);
			ListView_SetItemText(FX_General_hLV, pRow, 1, pPath);
			ListView_SetItemText(FX_General_hLV, pRow, 2, chr_Type);
			ListView_SetItemText(FX_General_hLV, pRow, 3, " ");
		}
	}
	else
	{
		App->Say("No Project Loaded");

		return 0;
	}

	return 1;
}

// *************************************************************************
// *					ShowAllMeshes Terry Bernie	 				 	   *
// *************************************************************************
bool SB_Resources::ShowAllMeshes()
{
	Ogre::String st;
	int NUM_COLS = 4;

	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	ListView_DeleteAllItems(FX_General_hLV);

	LV_COLUMN lvC;
	memset(&lvC, 0, sizeof(LV_COLUMN));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	std::string headers[] =
	{
		"Mesh", "Has Skeleton","Material File","Path"
	};
	int headerSize[] =
	{
		165,180,170,250
	};

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_SetColumn(FX_General_hLV, header, &lvC);
	}

	int	 pRow = 0;
	char pMeshName[255];
	char chr_AsSkell[255];
	char buff[255];
	char Origin[255];
	bool pHasSkel = 0;
	Ogre::ResourcePtr pp;

	Ogre::ResourceManager::ResourceMapIterator MeshIterator = Ogre::MeshManager::getSingleton().getResourceIterator();

	while (MeshIterator.hasMoreElements())
	{
		//strcpy(pMeshName,(static_cast<Ogre::MeshPtr>(MeshIterator.peekNextValue()))->getName().c_str());

		strcpy(pMeshName, MeshIterator.peekNextValue()->getName().c_str());

		pp = Ogre::MeshManager::getSingleton().getByName(pMeshName);
		st = pp->getGroup();
		strcpy(Origin, st.c_str());
		//App->Say(st.c_str());

		Ogre::Entity *DummyEnt = App->SBC_Ogre->mSceneMgr->createEntity("GDTemp1", pMeshName);
		pHasSkel = DummyEnt->hasSkeleton();
		App->SBC_Ogre->mSceneMgr->destroyEntity(DummyEnt);

		if (pHasSkel == 1)
		{
			strcpy(chr_AsSkell, "Yes");
		}
		else
		{
			strcpy(chr_AsSkell, "No");
		}

		strcpy(buff, pMeshName);
		if (_stricmp(buff + strlen(buff) - 5, ".mesh") != 0)
		{
			strcpy(ResourcePath, "Internal");
		}
		else
		{
			Start_List_Folders(NULL, pMeshName, 0);
		}

		pitem.iItem = pRow;
		pitem.pszText = pMeshName;

		ListView_InsertItem(FX_General_hLV, &pitem);
		ListView_SetItemText(FX_General_hLV, pRow, 1, chr_AsSkell);
		ListView_SetItemText(FX_General_hLV, pRow, 2, ResourcePath);
		ListView_SetItemText(FX_General_hLV, pRow, 3, Origin);

		pRow++;

		MeshIterator.moveNext();
	}

	return 1;
}

// *************************************************************************
// *					SearchFolders Terry Bernie			 		 	   *
// *************************************************************************
bool SB_Resources::SearchFolders(char* Extension)
{

	int NUM_COLS = 4;

	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	//ListView_DeleteAllItems(FX_General_hLV);

	LV_COLUMN lvC;
	memset(&lvC, 0, sizeof(LV_COLUMN));
	lvC.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvC.fmt = LVCFMT_LEFT;  // left-align the column
	std::string headers[] =
	{
		"Mesh", "Has Skeleton","Material File","Path"
	};
	int headerSize[] =
	{
		165,180,170,250
	};

	for (int header = 0; header < NUM_COLS; header++)
	{
		lvC.iSubItem = header;
		lvC.cx = headerSize[header]; // width of the column, in pixels
		lvC.pszText = const_cast<char*>(headers[header].c_str());
		ListView_SetColumn(FX_General_hLV, header, &lvC);
	}

	int	 pRow = 0;

	char pSearchPath[1024];
	strcpy(pSearchPath, App->SBC_Project->m_Main_Assets_Path);
	strcat(pSearchPath, Extension); // "*.material");
	
	WIN32_FIND_DATA FindFileData;
	HANDLE hFind = ::FindFirstFile(pSearchPath, &FindFileData);

//	return 1;

	if (hFind != INVALID_HANDLE_VALUE) 
	{
		do {
			
			if (!(FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				
				pitem.iItem = pRow;
				pitem.pszText = FindFileData.cFileName;

				ListView_InsertItem(FX_General_hLV, &pitem);
				ListView_SetItemText(FX_General_hLV, pRow, 1, "");
				ListView_SetItemText(FX_General_hLV, pRow, 2, "");
				ListView_SetItemText(FX_General_hLV, pRow, 3, "");

				pRow++;
			}
		} while (::FindNextFile(hFind, &FindFileData));
		::FindClose(hFind);
	}

	return 1;
}

// *************************************************************************
// *					FindPath Terry Bernie				 		 	   *
// *************************************************************************
bool SB_Resources::FindPath(char* SubFolder, char* File, char* StartFolder)
{
	char pSearchPath[1024];
	char pReturnPath[1024];
	char *pPartPath;

	strcpy(pSearchPath, App->EquityDirecory_FullPath);
	strcat(pSearchPath, "\\");
	strcat(pSearchPath, StartFolder);
	strcat(pSearchPath, SubFolder);

	int result = SearchPath((LPCTSTR)pSearchPath, (LPCTSTR)File, NULL, 1024, pReturnPath, &pPartPath);
	if (result == 0)
	{
		return 0;
	}

	return 1;
}

// *************************************************************************
// *					Start_List_Folders Terry Bernie			 	 	   *
// *************************************************************************
void SB_Resources::Start_List_Folders(HWND List, char *FileName, bool ListDlg)
{
	char StartFolder[2048];

	if (ListDlg == 1)
	{
		SendMessage(List, LB_RESETCONTENT, 0, 0);
	}

	strcpy(StartFolder, App->EquityDirecory_FullPath);
	strcat(StartFolder, "\\");
	strcat(StartFolder, "Media\\");

	List_Folders(List, StartFolder, FileName, ListDlg);
	return;
}

// *************************************************************************
// *					List_Folders Terry Bernie			 		 	   *
// *************************************************************************
void SB_Resources::List_Folders(HWND List, char *StartFolder, char *FileName, bool ListDlg)
{

	char SearchPath[2048];

	if (ListDlg == 1)
	{
		SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)StartFolder);
	}

	int Result = FindPath_New(FileName, StartFolder);
	if (Result == 1)
	{
		ResourcePath[0] = 0;
		strcat(ResourcePath, StartFolder);

		if (ListDlg == 1)
		{
			SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)StartFolder);
		}

		return;
	}


	strcpy(SearchPath, StartFolder);
	strcat(SearchPath, "*.*");

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	hFind = FindFirstFile(SearchPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		//App->Say("Cant Find File");
		return;
	}

	do
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

			if (strcmp(FindFileData.cFileName, "."))
			{
				if (strcmp(FindFileData.cFileName, ".."))
				{
					char NewPath[2048];
					strcpy(NewPath, StartFolder);
					strcat(NewPath, FindFileData.cFileName);
					strcat(NewPath, "\\");

					List_Folders(List, NewPath, FileName, ListDlg);

				}
			}
		}
	}

	while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);

	return;
}

// *************************************************************************
// *					FindPath_New Terry Bernie					 	   *
// *************************************************************************
bool SB_Resources::FindPath_New(char* File, char* Folder)
{
	char pSearchPath[1024];
	char pReturnPath[1024];
	char *pPartPath;

	strcpy(pSearchPath, Folder);

	int result = SearchPath((LPCTSTR)pSearchPath, (LPCTSTR)File, NULL, 1024, pReturnPath, &pPartPath);
	if (result == 0)
	{
		return 0;
	}

	return 1;
}

// *************************************************************************
// *					List_MeshMaterials Terry Bernie			 	 	   *
// *************************************************************************
void SB_Resources::List_MeshMaterials(HWND List)
{
	SendMessage(List, LB_RESETCONTENT, 0, 0);

	int Count = 0;
	while (Count < App->SBC_Scene->Object_Count) // Remove Ogre Objects
	{
		char MeshName[255];

		strcpy(MeshName, App->SBC_Scene->B_Object[Count]->Mesh_Name);
		SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MeshName);

		int SubMeshCount = App->SBC_Scene->B_Object[Count]->Object_Ent->getNumSubEntities();
		int Index = 0;
		while (Index < SubMeshCount)
		{
			char MaterialName[1024];
			Ogre::SubMesh const *subMesh = App->SBC_Scene->B_Object[Count]->Object_Ent->getSubEntity(Index)->getSubMesh();
			strcpy(MaterialName, subMesh->getMaterialName().c_str());
			SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MaterialName);
			Index++;
		}


		Count++;

		SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)" --------------------------------- ");
	}

	return;
}

// *************************************************************************
// *					Unload_Materials Terry Bernie			 	 	   *
// *************************************************************************
void SB_Resources::Unload_Materials(void)
{
	//int Count = 0;
	//while (Count < App->Cl_Scene_Data->ObjectCount) // Remove Objects Materials
	//{
	//	char MeshName[255];

	//	strcpy(MeshName, App->Cl_Scene_Data->Cl_Object[Count]->MeshName);

	//	int SubMeshCount = App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity->getNumSubEntities();
	//	int Index = 0;
	//	while (Index < SubMeshCount)
	//	{
	//		char MaterialName[1024];
	//		Ogre::SubMesh const *subMesh = App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity->getSubEntity(Index)->getSubMesh();
	//		strcpy(MaterialName, subMesh->getMaterialName().c_str());
	//		Ogre::MaterialManager::getSingleton().unload(MaterialName);

	//		Index++;
	//	}

	//	Count++;
	//}

	return;
}

// *************************************************************************
// *					Remove_OblectMesh Terry Bernie			 	 	   *
// *************************************************************************
void SB_Resources::Remove_OblectMesh(void)
{
	//int Count = 0;
	//while (Count < App->Cl_Scene_Data->ObjectCount) // Remove Ogre Objects
	//{
	//	if (App->Cl_Scene_Data->Cl_Object[Count]->OgreNode && App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity)
	//	{
	//		App->Cl_Scene_Data->Cl_Object[Count]->OgreNode->detachAllObjects();

	//		App->SBC_Ogre->mSceneMgr->destroySceneNode(App->Cl_Scene_Data->Cl_Object[Count]->OgreNode);

	//		App->SBC_Ogre->mSceneMgr->destroyEntity(App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity);

	//		App->Cl_Scene_Data->Cl_Object[Count]->OgreNode = NULL;
	//		App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity = NULL;
	//	}

	//	// --------------------------------------------------------------------- 
	//	bool Test = Ogre::MeshManager::getSingleton().getByName(App->Cl_Scene_Data->Cl_Object[Count]->MeshName).isNull();
	//	if (Test == 0) // is loaded
	//	{
	//		Ogre::ResourcePtr ptr = Ogre::MeshManager::getSingleton().getByName(App->Cl_Scene_Data->Cl_Object[Count]->MeshName);
	//		ptr->unload();
	//		Ogre::MeshManager::getSingleton().remove(App->Cl_Scene_Data->Cl_Object[Count]->MeshName);
	//	}

	//	Count++;
	//}

	return;
}

