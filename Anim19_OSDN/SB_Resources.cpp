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
}


SB_Resources::~SB_Resources()
{
}

// *************************************************************************
// *	  					Start_Resources Terry Bernie				   *
// *************************************************************************
void SB_Resources::Start_Resources(void)
{
	DialogBox(App->hInst, (LPCTSTR)IDD_RESOURCESMATERIAL, App->Fdlg, (DLGPROC)Resources_Proc);
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

		HFONT Font;
		Font = CreateFont(-15, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");


		////App->GDC_DlgResources->SelectedResource = 0;
		App->SBC_Resources->CreateListGeneral_FX(hDlg);

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		return FALSE;
	}

	case WM_CTLCOLORDLG:
	{
		return (LONG)App->DialogBackGround;
	}

	case WM_NOTIFY:
	{
		LPNMHDR some_item = (LPNMHDR)lParam;

		/*if (some_item->idFrom == IDC_MESHMATERIALS && some_item->code == NM_CUSTOMDRAW)
		{
		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		App->Custom_Button_Toggle(item,App->GDCL_Resources->Active_MeshMaterials);
		return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_TEXTURES && some_item->code == NM_CUSTOMDRAW)
		{
		LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
		App->Custom_Button_Toggle(item,App->GDCL_Resources->Active_Textures);
		return CDRF_DODEFAULT;
		}*/

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

		//if (LOWORD(wParam) == IDC_MATERIALS)
		//{
		//	App->GDCL_Resources->ShowAllMaterials();
		//	return TRUE;
		//}

		//if (LOWORD(wParam) == IDC_TEXTURES)
		//{
		//	App->GDCL_Resources->ShowAllTextures();
		//	return TRUE;
		//}

		if (LOWORD(wParam) == IDC_MESH)
		{
			App->SBC_Resources->ShowAllMeshes();
			return TRUE;
		}

		//if (LOWORD(wParam) == IDC_USED)
		//{
		//	App->GDCL_Resources->ShowUsedMaterials();
		//	return TRUE;
		//}

		////if (LOWORD(wParam) == IDC_NOTUSED)
		////{
		////	App->GDC_DlgResources->ShowNotUsedMaterials();
		////	return TRUE;
		////}

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
		WS_CHILD | WS_VISIBLE | WS_BORDER | LVS_REPORT | LVS_SHOWSELALWAYS, 2, 2,
		1280, 445, hDlg, 0, App->hInst, NULL);

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
		165,180,70,250
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

		Ogre::Entity *DummyEnt = App->Cl19_Ogre->mSceneMgr->createEntity("GDTemp1", pMeshName);
		pHasSkel = DummyEnt->hasSkeleton();
		App->Cl19_Ogre->mSceneMgr->destroyEntity(DummyEnt);

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
bool SB_Resources::SearchFolders(char* File, char* StartFolder)
{
	strcpy(ResourcePath, StartFolder);

	//	char Folder[255];
	char pSearchPath[1024];
	//	char pReturnPath[1024];
	//	char *pPartPath;

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(pSearchPath, App->EquityDirecory_FullPath);
	strcat(pSearchPath, "\\");
	strcat(pSearchPath, StartFolder);
	strcat(pSearchPath, "*.*");

	hFind = FindFirstFile(pSearchPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		//App->Say("Cant Find File");
		return FALSE;
	}

	do
	{
		if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
		{

			if (strcmp(FindFileData.cFileName, "."))
			{
				if (strcmp(FindFileData.cFileName, ".."))
				{
					//App->Say(FindFileData.cFileName);
					int Result = FindPath(FindFileData.cFileName, File, StartFolder);
					if (Result == 1)
					{
						strcat(ResourcePath, FindFileData.cFileName);
						//App->Say(ResourcePath);
						SearchFolders(File, ResourcePath); // Needs Checking
						return 1;
					}
				}
			}
		}
	}

	while (FindNextFile(hFind, &FindFileData));
	FindClose(hFind);

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
	while (Count < App->Cl_Scene_Data->ObjectCount) // Remove Ogre Objects
	{
		char MeshName[255];

		strcpy(MeshName, App->Cl_Scene_Data->Cl_Object[Count]->MeshName);
		SendMessage(List, LB_ADDSTRING, 0, (LPARAM)(LPCTSTR)MeshName);

		int SubMeshCount = App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity->getNumSubEntities();
		int Index = 0;
		while (Index < SubMeshCount)
		{
			char MaterialName[1024];
			Ogre::SubMesh const *subMesh = App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity->getSubEntity(Index)->getSubMesh();
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
	int Count = 0;
	while (Count < App->Cl_Scene_Data->ObjectCount) // Remove Objects Materials
	{
		char MeshName[255];

		strcpy(MeshName, App->Cl_Scene_Data->Cl_Object[Count]->MeshName);

		int SubMeshCount = App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity->getNumSubEntities();
		int Index = 0;
		while (Index < SubMeshCount)
		{
			char MaterialName[1024];
			Ogre::SubMesh const *subMesh = App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity->getSubEntity(Index)->getSubMesh();
			strcpy(MaterialName, subMesh->getMaterialName().c_str());
			Ogre::MaterialManager::getSingleton().unload(MaterialName);

			Index++;
		}

		Count++;
	}

	return;
}

// *************************************************************************
// *					Remove_OblectMesh Terry Bernie			 	 	   *
// *************************************************************************
void SB_Resources::Remove_OblectMesh(void)
{
	int Count = 0;
	while (Count < App->Cl_Scene_Data->ObjectCount) // Remove Ogre Objects
	{
		if (App->Cl_Scene_Data->Cl_Object[Count]->OgreNode && App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity)
		{
			App->Cl_Scene_Data->Cl_Object[Count]->OgreNode->detachAllObjects();

			App->Cl19_Ogre->mSceneMgr->destroySceneNode(App->Cl_Scene_Data->Cl_Object[Count]->OgreNode);

			App->Cl19_Ogre->mSceneMgr->destroyEntity(App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity);

			App->Cl_Scene_Data->Cl_Object[Count]->OgreNode = NULL;
			App->Cl_Scene_Data->Cl_Object[Count]->OgreEntity = NULL;
		}

		// --------------------------------------------------------------------- 
		bool Test = Ogre::MeshManager::getSingleton().getByName(App->Cl_Scene_Data->Cl_Object[Count]->MeshName).isNull();
		if (Test == 0) // is loaded
		{
			Ogre::ResourcePtr ptr = Ogre::MeshManager::getSingleton().getByName(App->Cl_Scene_Data->Cl_Object[Count]->MeshName);
			ptr->unload();
			Ogre::MeshManager::getSingleton().remove(App->Cl_Scene_Data->Cl_Object[Count]->MeshName);
		}

		Count++;
	}

	return;
}

// *************************************************************************
// *					Unload_Game_Resources Terry Bernie		 	 	   *
// *************************************************************************
void SB_Resources::Unload_Game_Resources(void)
{
	
	Ogre::ResourceGroupManager::getSingleton().destroyResourceGroup(App->Cl19_Ogre->Level_Resource_Group);
	Ogre::ResourceGroupManager::getSingleton().createResourceGroup(App->Cl19_Ogre->Level_Resource_Group);
	return;
}
