/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
#include "resource.h"
#include "GD19_App.h"
#include "GD19_Project.h"


GD19_Project::GD19_Project(void)
{

	StartFolder[0] = 0;
	ProjectFolder[0] = 0;
	Sub_ProjectFolder[0] = 0;

	SourceFile[0] = 0;
	DestinationFile[0] = 0;
	MediaFolder[0] = 0;

	LevelsFolder[0] = 0;
	ActorsFolder[0] = 0;
	MaterialsFolder[0] = 0;
	TexturesFolder[0] = 0;
	CoreDataFolder[0] = 0;
	ResourcePath[0] = 0;
	SoundFolder[0] = 0;

	
	// Config

	//App->Cl_Project->Read_From_Config();
	CF_Full_Screen = 1;
	strcpy(GameName, "YourGameName");
	StartFolder[0] = 0;

	Write_IniFile = NULL;

}
GD19_Project::~GD19_Project(void)
{
}

// *************************************************************************
// *	  				Start_Project_Build Terry Bernie				   *
// *************************************************************************
void GD19_Project::Start_Project_Build()
{
	App->Cl_Project->Read_From_Config();
	
	DialogBox(App->hInst, (LPCTSTR)IDD_BUILD_DIALOG, App->Fdlg, (DLGPROC)Project_Build_Proc);
}
// *************************************************************************
// *				Start_Geometry_Proc Terry Bernie		  			   *
// *************************************************************************
LRESULT CALLBACK GD19_Project::Project_Build_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_EDGAMENAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STGAMENAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPATH, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_EDGAMENAME, (LPCTSTR)App->Cl_Project->GameName);
		SetDlgItemText(hDlg, IDC_STLOCATION, (LPCTSTR)App->Cl_Project->StartFolder);
		
		

		if (App->Cl_Project->CF_Full_Screen == 1)
		{
			SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 1, 0);
		}
		else
		{
			SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 0, 0);
		}


		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_EDGAMENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		if (GetDlgItem(hDlg, IDC_STLOCATION) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}
		if (GetDlgItem(hDlg, IDC_CKFULLSCREEN) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		if (GetDlgItem(hDlg, IDC_STGAMENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STPATH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
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

		if (some_item->idFrom == IDC_BTBROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_CKFULLSCREEN)
		{
			
			if (App->Cl_Project->CF_Full_Screen == 1)
			{
				SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 0, 0);
				App->Cl_Project->CF_Full_Screen = 0;
			}
			else
			{
				SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 1, 0);
				App->Cl_Project->CF_Full_Screen = 1;
			}
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTBROWSE)
		{
			strcpy(App->Cl_File_IO->BrowserMessage, "Select a Folder for Game Files a Sub folder will be created");
			int Test = App->Cl_File_IO->StartBrowser(App->DeskTop_Folder);
			if (Test == 0) { return 1; }
			strcpy(App->Cl_Project->StartFolder, App->Cl_File_IO->szSelectedDir);
			SetDlgItemText(hDlg, IDC_STLOCATION, (LPCTSTR)App->Cl_Project->StartFolder);

			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			char GameName[255];
			char PathName[255];
			GetDlgItemText(hDlg, IDC_EDGAMENAME, (LPTSTR)GameName, 255);
			GetDlgItemText(hDlg, IDC_STLOCATION, (LPTSTR)PathName, 255);
			int result = 1;

			// Check Name Entered
			result = strcmp(GameName, "");
			if (result == 0)
			{
				App->Say("No Game Name Specified");
				return 1;
			}

			// Check Path Selected
			result = strcmp(PathName, "");
			if (result == 0)
			{
				App->Say("No Path Specified");
				return 1;
			}

			strcpy(App->Cl_File_IO->szSelectedDir, PathName);
			strcpy(App->Cl_Project->StartFolder, PathName);

			strcpy(App->Cl_Project->GameName, GameName);

			App->Cl_Project->Write_To_Config(); // Writre to Config File

			App->Cl_Project->Create_ProjectFolder();

			EndDialog(hDlg, LOWORD(wParam));
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
// *					Create_ProjectFolder Terry Berine				   *
// *************************************************************************
void GD19_Project::Create_ProjectFolder(void)
{


	//StartFolder[0] = 0;
	ProjectFolder[0] = 0;
	Sub_ProjectFolder[0] = 0;

	MediaFolder[0] = 0;

	ActorsFolder[0] = 0;
	MaterialsFolder[0] = 0;
	TexturesFolder[0] = 0;
	CoreDataFolder[0] = 0;
	SoundFolder[0] = 0;

	App->Cl_PB = new GD19_PB();
	App->Cl_PB->StartNewProgressBar();

	//App->CL_Dialogs->MessageLoad("Please Wait");

	strcpy(ProjectFolder, App->Cl_File_IO->szSelectedDir);
	strcat(ProjectFolder, "\\");
	strcat(ProjectFolder, GameName);
	strcat(ProjectFolder, "_Project");

	int test = CreateDirectory(ProjectFolder, NULL);
	/*if(test == 0)
	{
		App->Say("Failed");
	}
	else
	{*/
	strcpy(Sub_ProjectFolder, ProjectFolder);
	strcat(Sub_ProjectFolder, "\\");
	strcat(Sub_ProjectFolder, "GD_Project");
	CreateDirectory(Sub_ProjectFolder, NULL);

	strcpy(MediaFolder, ProjectFolder);
	strcat(MediaFolder, "\\");
	strcat(MediaFolder, "Media");
	CreateDirectory(MediaFolder, NULL);

	strcpy(LevelsFolder, MediaFolder);
	strcat(LevelsFolder, "\\");
	strcat(LevelsFolder, "Levels");
	CreateDirectory(LevelsFolder, NULL);

	strcpy(ActorsFolder, MediaFolder);
	strcat(ActorsFolder, "\\");
	strcat(ActorsFolder, "Actors");
	CreateDirectory(ActorsFolder, NULL);

	strcpy(MaterialsFolder, MediaFolder);
	strcat(MaterialsFolder, "\\");
	strcat(MaterialsFolder, "Materials");
	CreateDirectory(MaterialsFolder, NULL);

	strcpy(TexturesFolder, MediaFolder);
	strcat(TexturesFolder, "\\");
	strcat(TexturesFolder, "Textures");
	CreateDirectory(TexturesFolder, NULL);

	strcpy(CoreDataFolder, MediaFolder);
	strcat(CoreDataFolder, "\\");
	strcat(CoreDataFolder, "Core_Data");
	CreateDirectory(CoreDataFolder, NULL);

	strcpy(SoundFolder, MediaFolder);
	strcat(SoundFolder, "\\");
	strcat(SoundFolder, "Sounds");
	CreateDirectory(SoundFolder, NULL);

	int TCount = Get_Transfer_Count();
	
	App->Cl_PB->Set_Progress("Copy_SystemFiles", TCount+9);
	Copy_SystemFiles();
	

	App->Cl_PB->Set_Progress_Text("Copy_ZipFiles");
	Copy_ZipFiles();
	

	App->Cl_PB->Set_Progress_Text("Copy_Level_Files");
	Copy_Level_Files();
	

	App->Cl_PB->Set_Progress_Text("Transfer_UsedMaterials");
	Transfer_UsedMaterials();
	

	App->Cl_PB->Set_Progress_Text("Transfer_Meshes");
	Transfer_Meshes();
	

	App->Cl_PB->Set_Progress_Text("Transfer_Textures");
	Transfer_Textures();
	

	App->Cl_PB->Set_Progress_Text("Transfer_Environment_Sound");
	Transfer_Environment_Sound();
	

	App->Cl_PB->Set_Progress_Text("Transfer_Sounds");
	Transfer_Sounds();
	

	App->Cl_PB->Set_Progress_Text("Create_Game_IniFile");
	Create_Game_IniFile();
	

	App->Cl_PB->Set_Progress_Text("Create_Config_File");
	Create_Config_File();
	

	//App->CL_Dialogs->MessageLoad_Finish("Project Created");

	//App->Cl_PB->Close();
	delete App->Cl_PB;
	App->Cl_PB = nullptr;

	//}
}

// *************************************************************************
// *					Copy_SystemFiles Terry Berine					   *
// *************************************************************************
void GD19_Project::Copy_SystemFiles(void)
{
	
	//----------------------------- OgreMain.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\OgreMain.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\OgreMain.dll");

	CopyFile(SourceFile, DestinationFile, false);

	App->Cl_PB->Nudge();

	//----------------------------- RenderSystem_GL.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\RenderSystem_Direct3D9.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\RenderSystem_Direct3D9.dll");

	CopyFile(SourceFile, DestinationFile, false);

	App->Cl_PB->Nudge();
	//----------------------------- cg.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\cg.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\cg.dll");

	CopyFile(SourceFile, DestinationFile, false);

	App->Cl_PB->Nudge();
	//----------------------------- msvcp100.dll
	/*strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\msvcp100.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\msvcp100.dll");

	CopyFile(SourceFile, DestinationFile, false);*/

	App->Cl_PB->Nudge();
	//----------------------------- msvcr100.dll
	/*strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\msvcr100.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\msvcr100.dll");

	CopyFile(SourceFile, DestinationFile, false);*/
	App->Cl_PB->Nudge();

	//----------------------------- irrKlang.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\irrKlang.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\irrKlang.dll");

	CopyFile(SourceFile, DestinationFile, false);
	App->Cl_PB->Nudge();

	//----------------------------- Plugin_CgProgramManager.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Plugin_CgProgramManager.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\Plugin_CgProgramManager.dll");

	CopyFile(SourceFile, DestinationFile, false);
	App->Cl_PB->Nudge();

	//----------------------------- Plugin_ParticleFX.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Plugin_ParticleFX.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\Plugin_ParticleFX.dll");

	CopyFile(SourceFile, DestinationFile, false);
	App->Cl_PB->Nudge();

	//----------------------------- OgreOverlay.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\OgreOverlay.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\OgreOverlay.dll");

	CopyFile(SourceFile, DestinationFile, false);
	App->Cl_PB->Nudge();
	
	//----------------------------- Game FIle
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\GDShell.gex");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\");
	strcat(DestinationFile, GameName);
	strcat(DestinationFile, ".exe");

	CopyFile(SourceFile, DestinationFile, false);
	App->Cl_PB->Nudge();
	
	//----------------------------- Game FIle
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\plugins.cfg");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\plugins.cfg");

	CopyFile(SourceFile, DestinationFile, false);
	App->Cl_PB->Nudge();

}

// *************************************************************************
// *					Copy_ZipFiles Terry Berine					   *
// *************************************************************************
void GD19_Project::Copy_ZipFiles(void)
{
	//----------------------------- GDCore.zip
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Media\\Core_Data\\GDCore.zip");

	strcpy(DestinationFile, CoreDataFolder);
	strcat(DestinationFile, "\\GDCore.zip");

	CopyFile(SourceFile, DestinationFile, false);
	App->Cl_PB->Nudge();
	//----------------------------- Equity.zip
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Media\\Core_Data\\Equity.zip");

	strcpy(DestinationFile, CoreDataFolder);
	strcat(DestinationFile, "\\Equity.zip");

	CopyFile(SourceFile, DestinationFile, false);
	App->Cl_PB->Nudge();
	//----------------------------- OgreCore.zip
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Media\\Core_Data\\OgreCore.zip");

	strcpy(DestinationFile, CoreDataFolder);
	strcat(DestinationFile, "\\OgreCore.zip");

	CopyFile(SourceFile, DestinationFile, false);
	App->Cl_PB->Nudge();
	//----------------------------- skybox.zip
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Media\\Core_Data\\skybox.zip");

	strcpy(DestinationFile, CoreDataFolder);
	strcat(DestinationFile, "\\skybox.zip");

	CopyFile(SourceFile, DestinationFile, false);
	App->Cl_PB->Nudge();
}

// *************************************************************************
// *					Copy_Level_Files Terry Berine					   *
// *************************************************************************
void GD19_Project::Copy_Level_Files(void)
{
	//----------------------------- GDCore.zip
	strcpy(SourceFile, LevelsFolder);
	strcat(SourceFile, "\\");
	strcat(SourceFile, App->Cl_Scene_Data->S_Scene[0]->GDSceneName);

	strcpy(App->Cl_Save_Scene->mLevel_Directory, LevelsFolder);
	strcat(App->Cl_Save_Scene->mLevel_Directory, "\\");

	strcpy(App->Cl_File_IO->Full_Path_And_File, SourceFile);
	App->Cl_Save_Scene->SaveGDScene_40(0);
	App->Cl_PB->Nudge();
}

// *************************************************************************
// *					Create_Game_IniFile Terry Berine				   *
// *************************************************************************
void GD19_Project::Create_Game_IniFile(void)
{
	Write_IniFile = 0;

	char buff[2048];
	strcpy(buff, ProjectFolder);
	strcat(buff, "\\Load_Level.gds");

	Write_IniFile = fopen(buff, "wt");

	fprintf(Write_IniFile, "%s\n", "[Start_Level]");
	fprintf(Write_IniFile, "%s%s\n", "First_Level=", App->Cl_Scene_Data->S_Scene[0]->GDSceneName);

	fclose(Write_IniFile);
	App->Cl_PB->Nudge();
}

// *************************************************************************
// *					Create_Config_File Terry Berine					   *
// *************************************************************************
void GD19_Project::Create_Config_File(void)
{
	Write_IniFile = 0;

	char buff[2048];
	strcpy(buff, ProjectFolder);
	strcat(buff, "\\Config.cfg");

	Write_IniFile = fopen(buff, "wt");

	fprintf(Write_IniFile, "%s\n", "[Config]");
	fprintf(Write_IniFile, "%s%s\n", "Version=", "1.0");
	fprintf(Write_IniFile, "%s%i\n", "Full_Screen=", App->Cl_Project->CF_Full_Screen);

	fclose(Write_IniFile);
	App->Cl_PB->Nudge();
}

// *************************************************************************
// *					Transfer_UsedMaterials Terry Bernie	 		 	   *
// *************************************************************************
bool GD19_Project::Transfer_UsedMaterials()
{
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
				Start_List_Folders(NULL, pScriptFile, 0);

				SourceFile[0] = 0;
				strcpy(SourceFile, ResourcePath);
				strcat(SourceFile, pScriptFile);

				DestinationFile[0] = 0;
				strcpy(DestinationFile, MaterialsFolder);
				strcat(DestinationFile, "\\");
				strcat(DestinationFile, pScriptFile);

				CopyFile(SourceFile, DestinationFile, false);

			}
		}

		App->Cl_PB->Nudge();
		materialIterator.moveNext();
	}

	return 1;
}

// *************************************************************************
// *					Transfer_Meshes Terry Bernie	 			 	   *
// *************************************************************************
bool GD19_Project::Transfer_Meshes()
{
	Ogre::String st;

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
		strcpy(pMeshName, MeshIterator.peekNextValue()->getName().c_str());

		pp = Ogre::MeshManager::getSingleton().getByName(pMeshName);
		st = pp->getOrigin();
		strcpy(Origin, st.c_str());


		Ogre::Entity* DummyEnt = App->Cl19_Ogre->mSceneMgr->createEntity("GDTemp1", pMeshName);
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
			ResourcePath[0] = 0;
			Start_List_Folders(NULL, pMeshName, 0);

			SourceFile[0] = 0;
			strcpy(SourceFile, ResourcePath);
			strcat(SourceFile, pMeshName);

			DestinationFile[0] = 0;
			strcpy(DestinationFile, ActorsFolder);
			strcat(DestinationFile, "\\");
			strcat(DestinationFile, pMeshName);

			CopyFile(SourceFile, DestinationFile, false);

			if (pHasSkel == 1)
			{
				pMeshName[strlen(pMeshName) - 5] = 0;
				strcat(pMeshName, ".skeleton");

				SourceFile[0] = 0;
				strcpy(SourceFile, ResourcePath);
				strcat(SourceFile, pMeshName);

				DestinationFile[0] = 0;
				strcpy(DestinationFile, ActorsFolder);
				strcat(DestinationFile, "\\");
				strcat(DestinationFile, pMeshName);
				CopyFile(SourceFile, DestinationFile, false);
			}

		}

		App->Cl_PB->Nudge();
		MeshIterator.moveNext();
	}

	return 1;
}

// *************************************************************************
// *					Transfer_Textures Terry Bernie				 	   *
// *************************************************************************
bool GD19_Project::Transfer_Textures()
{
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
		strcpy(pScriptName,TextureIterator.peekNextValue()->getName().c_str());

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

		ResourcePath[0] = 0;

		char Filename[255];
		char ext[255];
		char JustFile[255];
		char SubFolder[255];

		_splitpath(pScriptName, NULL, SubFolder, Filename, ext);
		strcpy(JustFile, Filename);
		strcat(JustFile, ext);

		Start_List_Folders(NULL, JustFile, 0);



		SourceFile[0] = 0;
		strcpy(SourceFile, ResourcePath);
		strcat(SourceFile, JustFile);

		if (SubFolder[0] > 0)
		{
			DestinationFile[0] = 0;
			strcpy(DestinationFile, TexturesFolder);
			strcat(DestinationFile, "\\");
			strcat(DestinationFile, SubFolder);

			CreateDirectory(DestinationFile, NULL);

			strcat(DestinationFile, JustFile);

			CopyFile(SourceFile, DestinationFile, false);
		}
		else
		{
			DestinationFile[0] = 0;
			strcpy(DestinationFile, TexturesFolder);
			strcat(DestinationFile, "\\");
			strcat(DestinationFile, JustFile);

			CopyFile(SourceFile, DestinationFile, false);
		}

		App->Cl_PB->Nudge();
		TextureIterator.moveNext();
	}

	return 1;
}

// *************************************************************************
// *					Transfer_Environment_Sound Terry Bernie			   *
// *************************************************************************
void GD19_Project::Transfer_Environment_Sound(void)
{
	int result = 1;
	result = strcmp(App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFile, "None");
	if (result == 1) // Could be Unsafe 
	{

		SourceFile[0] = 0;

		strcpy(SourceFile, App->Cl_SoundMgr->Default_Folder);
		strcat(SourceFile, "\\Media\\Sounds\\");
		strcat(SourceFile, App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFile);

		DestinationFile[0] = 0;
		strcpy(DestinationFile, SoundFolder);
		strcat(DestinationFile, "\\");
		strcat(DestinationFile, App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFile);
		CopyFile(SourceFile, DestinationFile, false);
		App->Cl_PB->Nudge();
	}
	return;
}

// *************************************************************************
// *					Transfer_Sounds Terry Bernie					   *
// *************************************************************************
void GD19_Project::Transfer_Sounds(void)
{
	// Defaults
	SourceFile[0] = 0;
	strcpy(SourceFile, App->Cl_SoundMgr->Default_Folder); // Root
	strcat(SourceFile, "\\Media\\Sounds\\"); // GD Sound Folder
	strcat(SourceFile, "footstep.ogg");

	DestinationFile[0] = 0;
	strcpy(DestinationFile, SoundFolder);
	strcat(DestinationFile, "\\");
	strcat(DestinationFile, "footstep.ogg");

	CopyFile(SourceFile, DestinationFile, false);

	// Enviroment
	SourceFile[0] = 0;
	strcpy(SourceFile, App->Cl_SoundMgr->Default_Folder); // Root
	strcat(SourceFile, "\\Media\\Sounds\\"); // GD Sound Folder
	strcat(SourceFile, App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFile);

	DestinationFile[0] = 0;
	strcpy(DestinationFile, SoundFolder);
	strcat(DestinationFile, "\\");
	strcat(DestinationFile, App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFile);

	CopyFile(SourceFile, DestinationFile, false);

	// Objects
	int Index = 0;
	while (Index < App->Cl_Scene_Data->Stock_Sound_Count)
	{
			SourceFile[0] = 0;
			strcpy(SourceFile, App->Cl_SoundMgr->Default_Folder); // Root
			strcat(SourceFile, "\\Media\\Sounds\\"); // GD Sound Folder
			strcat(SourceFile, App->Cl_Scene_Data->St_Sounds[Index]->SoundFile);

			DestinationFile[0] = 0;
			strcpy(DestinationFile, SoundFolder);
			strcat(DestinationFile, "\\");
			strcat(DestinationFile, App->Cl_Scene_Data->St_Sounds[Index]->SoundFile);

			CopyFile(SourceFile, DestinationFile, false);
		
		App->Cl_PB->Nudge();
		Index++;
	}

	return;
}

// *************************************************************************
// *					Start_List_Folders Terry Bernie			 	 	   *
// *************************************************************************
void GD19_Project::Start_List_Folders(HWND List, char* FileName, bool ListDlg)
{
	char StartFolder[2048];

	strcpy(StartFolder, App->EquityDirecory_FullPath);
	strcat(StartFolder, "\\");
	strcat(StartFolder, "Media\\");

	List_Folders(List, StartFolder, FileName, ListDlg);
	return;
}

// *************************************************************************
// *					List_Folders Terry Bernie			 		 	   *
// *************************************************************************
void GD19_Project::List_Folders(HWND List, char* StartFolder, char* FileName, bool ListDlg)
{

	char SearchPath[2048];

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
		App->Say("Cant Find File");
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
bool GD19_Project::FindPath_New(char* File, char* Folder)
{
	char pSearchPath[1024];
	char pReturnPath[1024];
	char* pPartPath;

	strcpy(pSearchPath, Folder);

	int result = SearchPath((LPCTSTR)pSearchPath, (LPCTSTR)File, NULL, 1024, pReturnPath, &pPartPath);
	if (result == 0)
	{
		return 0;
	}

	return 1;
}

// *************************************************************************
// *					Write_To_Config Terry Berine					   *
// *************************************************************************
void GD19_Project::Write_To_Config(void)
{
	char StartFile[1024];
	strcpy(StartFile, App->EquityDirecory_FullPath);
	strcat(StartFile, "\\");
	strcat(StartFile, "Data\\StartUp.gcf");

	App->Cl_Ini->SetPathName(StartFile);

	bool test2;
	test2 = App->Cl_Ini->WriteBool("Config", "Full_Screen", CF_Full_Screen);
	if (test2 == 0)
	{
		App->Say("Error Writing 2");
	}

	test2 = App->Cl_Ini->WriteString("Config", "Project_Path", StartFolder);
	if (test2 == 0)
	{
		App->Say("Error Writing 3");
	}

	test2 = App->Cl_Ini->WriteString("Config", "Game_Name", GameName);
	if (test2 == 0)
	{
		App->Say("Error Writing 4");
	}
	
}

// *************************************************************************
// *					Read_From_Config Terry Berine					   *
// *************************************************************************
void GD19_Project::Read_From_Config(void)
{
	char chr_Tag1[1024];
	char StartFile[1024];
	strcpy(StartFile, App->EquityDirecory_FullPath);
	strcat(StartFile, "\\");
	strcat(StartFile, "Data\\StartUp.gcf");

	App->Cl_Ini->SetPathName(StartFile);

	CF_Full_Screen = App->Cl_Ini->GetBool("Config", "Full_Screen", 1);

	App->Cl_Ini->GetString("Config", "Project_Path", chr_Tag1, 1024);
	strcpy(App->Cl_Project->StartFolder,chr_Tag1);

	App->Cl_Ini->GetString("Config", "Game_Name", chr_Tag1, 1024);
	strcpy(App->Cl_Project->GameName, chr_Tag1);

}

// *************************************************************************
// *					Get_Transfer_Count Terry Berine					   *
// *************************************************************************
int GD19_Project::Get_Transfer_Count(void)
{
	int Tcount = 9;

	Tcount = Tcount + 4; // Zip Files
	Tcount = Tcount + 1; // Level File

	Ogre::ResourceManager::ResourceMapIterator materialIterator = Ogre::MaterialManager::getSingleton().getResourceIterator();

	while (materialIterator.hasMoreElements())
	{
		Tcount++;
		materialIterator.moveNext();
	}

	Ogre::ResourceManager::ResourceMapIterator MeshIterator = Ogre::MeshManager::getSingleton().getResourceIterator();

	while (MeshIterator.hasMoreElements())
	{
		Tcount++;
		MeshIterator.moveNext();
	}

	Ogre::ResourceManager::ResourceMapIterator TextureIterator = Ogre::TextureManager::getSingleton().getResourceIterator();

	while (TextureIterator.hasMoreElements())
	{
		Tcount++;
		TextureIterator.moveNext();
	}

	Tcount++; // Enviroment Sound

	int Index = 0;
	while (Index < App->Cl_Scene_Data->Stock_Sound_Count)
	{
		Tcount++;
		Index++;
	}


	Tcount = Tcount + 2; // Ini File Config File


	return Tcount;
}
