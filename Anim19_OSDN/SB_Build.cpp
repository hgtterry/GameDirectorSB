/*
Copyright (c) 2022 GameDirectorSB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Build.h"

SB_Build::SB_Build()
{
	strcpy(GameName, "YourGameName");
	StartFolder[0] = 0;

	ProjectFolder[0] = 0;
	Sub_ProjectFolder[0] = 0;

	MediaFolder[0] = 0;

	ActorsFolder[0] = 0;
	MaterialsFolder[0] = 0;
	TexturesFolder[0] = 0;
	CoreDataFolder[0] = 0;
	SoundFolder[0] = 0;

}

SB_Build::~SB_Build()
{
}

// *************************************************************************
// *	  	Start_Project_Build:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Build::Start_Project_Build()
{
	//App->CL10_Project->Read_From_Config();

	DialogBox(App->hInst, (LPCTSTR)IDD_BUILD_DIALOG, App->Fdlg, (DLGPROC)Project_Build_Proc);
}

// *************************************************************************
// *		Project_Build_Proc:- Terry and Hazel Flanigan 2022	  		   *
// *************************************************************************
LRESULT CALLBACK SB_Build::Project_Build_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{

	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_EDGAMENAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STGAMENAME, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPATH, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STLOCATION, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTBROWSE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SetDlgItemText(hDlg, IDC_EDGAMENAME, (LPCTSTR)App->SBC_Build->GameName);
		SetDlgItemText(hDlg, IDC_STLOCATION, (LPCTSTR)App->SBC_Build->StartFolder);



		/*if (App->CL10_Project->CF_Full_Screen == 1)
		{
			SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 1, 0);
		}
		else
		{
			SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 0, 0);
		}*/


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

			/*if (App->CL10_Project->CF_Full_Screen == 1)
			{
				SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 0, 0);
				App->CL10_Project->CF_Full_Screen = 0;
			}
			else
			{
				SendMessage(GetDlgItem(hDlg, IDC_CKFULLSCREEN), BM_SETCHECK, 1, 0);
				App->CL10_Project->CF_Full_Screen = 1;
			}*/
			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTBROWSE)
		{
			strcpy(App->Com_CDialogs->BrowserMessage, "Select a Folder for Game Files a Sub folder will be created");
			int Test = App->Com_CDialogs->StartBrowser(App->SBC_MeshViewer->mResource_Folder, App->Fdlg);
			if (Test == 0) { return true; }

			strcpy(App->SBC_Build->StartFolder, App->Com_CDialogs->szSelectedDir);

			SetDlgItemText(hDlg, IDC_STLOCATION, (LPCTSTR)App->SBC_Build->StartFolder);

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

			strcpy(App->Com_CDialogs->szSelectedDir, PathName);
			strcpy(App->SBC_Build->StartFolder, PathName);

			strcpy(App->SBC_Build->GameName, GameName);

			//App->CL10_Project->Write_To_Config(); // Writre to Config File

			App->SBC_Build->Create_ProjectFolder();

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
// *		Create_ProjectFolder:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Build::Create_ProjectFolder(void)
{

	ProjectFolder[0] = 0;
	Sub_ProjectFolder[0] = 0;

	MediaFolder[0] = 0;

	ActorsFolder[0] = 0;
	MaterialsFolder[0] = 0;
	TexturesFolder[0] = 0;
	CoreDataFolder[0] = 0;
	SoundFolder[0] = 0;


//	App->CL10_PB = new GD10_PB();
//	App->CL10_PB->StartNewProgressBar();

	//App->CL_Dialogs->MessageLoad("Please Wait");

	strcpy(ProjectFolder, App->Com_CDialogs->szSelectedDir);
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

//	int TCount = Get_Transfer_Count();

//	App->CL10_PB->Set_Progress("Copy_SystemFiles", TCount + 9);
	Copy_SystemFiles();


	/*App->CL10_PB->Set_Progress_Text("Copy_ZipFiles");
	Copy_ZipFiles();


	App->CL10_PB->Set_Progress_Text("Copy_Level_Files");
	Copy_Level_Files();


	App->CL10_PB->Set_Progress_Text("Transfer_UsedMaterials");
	Transfer_UsedMaterials();


	App->CL10_PB->Set_Progress_Text("Transfer_Meshes");
	Transfer_Meshes();


	App->CL10_PB->Set_Progress_Text("Transfer_Textures");
	Transfer_Textures();


	App->CL10_PB->Set_Progress_Text("Transfer_Environment_Sound");
	Transfer_Environment_Sound();


	App->CL10_PB->Set_Progress_Text("Transfer_Sounds");
	Transfer_Sounds();


	App->CL10_PB->Set_Progress_Text("Create_Game_IniFile");
	Create_Game_IniFile();


	App->CL10_PB->Set_Progress_Text("Create_Config_File");
	Create_Config_File();*/


	//App->CL_Dialogs->MessageLoad_Finish("Project Created");

	//App->CL10_PB->Close();
	//delete App->CL10_PB;
	//App->CL10_PB = nullptr;

	//}
}

// *************************************************************************
// *		Copy_SystemFiles:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Build::Copy_SystemFiles(void)
{

	//----------------------------- OgreMain.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\OgreMain.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\OgreMain.dll");

	CopyFile(SourceFile, DestinationFile, false);

//	App->CL10_PB->Nudge();

	//----------------------------- RenderSystem_GL.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\RenderSystem_GL.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\RenderSystem_GL.dll");

	CopyFile(SourceFile, DestinationFile, false);

//	App->CL10_PB->Nudge();
	//----------------------------- cg.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\cg.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\cg.dll");

	CopyFile(SourceFile, DestinationFile, false);

	//----------------------------- OgreOverlay.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\OgreOverlay.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\OgreOverlay.dll");

	CopyFile(SourceFile, DestinationFile, false);
	
//	App->CL10_PB->Nudge();
	//----------------------------- msvcp140.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\msvcp140.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\msvcp140.dll");

	CopyFile(SourceFile, DestinationFile, false);

//	App->CL10_PB->Nudge();
	//----------------------------- vcruntime140.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\vcruntime140.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\vcruntime140.dll");

	CopyFile(SourceFile, DestinationFile, false);
//	App->CL10_PB->Nudge();

	//----------------------------- irrKlang.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\irrKlang.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\irrKlang.dll");

	CopyFile(SourceFile, DestinationFile, false);
//	App->CL10_PB->Nudge();

	//----------------------------- Plugin_CgProgramManager.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Plugin_CgProgramManager.dll");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\Plugin_CgProgramManager.dll");

	CopyFile(SourceFile, DestinationFile, false);
//	App->CL10_PB->Nudge();

	//----------------------------- Game FIle
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\GDShell.gex");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\");
	strcat(DestinationFile, GameName);
	strcat(DestinationFile, ".exe");

	CopyFile(SourceFile, DestinationFile, false);
//	App->CL10_PB->Nudge();

	//----------------------------- Game FIle
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\plugins.cfg");

	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\plugins.cfg");

	CopyFile(SourceFile, DestinationFile, false);
//	App->CL10_PB->Nudge();

}

// *************************************************************************
// *					Copy_ZipFiles Terry Berine					   *
// *************************************************************************
void SB_Build::Copy_ZipFiles(void)
{
	////----------------------------- GDCore.zip
	//strcpy(SourceFile, App->EquityDirecory_FullPath);
	//strcat(SourceFile, "\\Media\\Core_Data\\GDCore.zip");

	//strcpy(DestinationFile, CoreDataFolder);
	//strcat(DestinationFile, "\\GDCore.zip");

	//CopyFile(SourceFile, DestinationFile, false);
	//App->CL10_PB->Nudge();
	////----------------------------- Equity.zip
	//strcpy(SourceFile, App->EquityDirecory_FullPath);
	//strcat(SourceFile, "\\Media\\Core_Data\\Equity.zip");

	//strcpy(DestinationFile, CoreDataFolder);
	//strcat(DestinationFile, "\\Equity.zip");

	//CopyFile(SourceFile, DestinationFile, false);
	//App->CL10_PB->Nudge();
	////----------------------------- OgreCore.zip
	//strcpy(SourceFile, App->EquityDirecory_FullPath);
	//strcat(SourceFile, "\\Media\\Core_Data\\OgreCore.zip");

	//strcpy(DestinationFile, CoreDataFolder);
	//strcat(DestinationFile, "\\OgreCore.zip");

	//CopyFile(SourceFile, DestinationFile, false);
	//App->CL10_PB->Nudge();
	////----------------------------- skybox.zip
	//strcpy(SourceFile, App->EquityDirecory_FullPath);
	//strcat(SourceFile, "\\Media\\Core_Data\\skybox.zip");

	//strcpy(DestinationFile, CoreDataFolder);
	//strcat(DestinationFile, "\\skybox.zip");

	//CopyFile(SourceFile, DestinationFile, false);
	//App->CL10_PB->Nudge();
}

// *************************************************************************
// *					Copy_Level_Files Terry Berine					   *
// *************************************************************************
void SB_Build::Copy_Level_Files(void)
{
	/*----------------------------- GDCore.zip
	strcpy(SourceFile, LevelsFolder);
	strcat(SourceFile, "\\");
	strcat(SourceFile, App->GDCL_Scene_Data->S_Scene[0]->GDSceneName);

	strcpy(App->GDCL_Save_Scene->mLevel_Directory, LevelsFolder);
	strcat(App->GDCL_Save_Scene->mLevel_Directory, "\\");

	strcpy(App->CL10_File->Full_Path_And_File, SourceFile);
	App->GDCL_Save_Scene->SaveGDScene_40(0);
	App->CL10_PB->Nudge();*/
}

// *************************************************************************
// *					Create_Game_IniFile Terry Berine				   *
// *************************************************************************
void SB_Build::Create_Game_IniFile(void)
{
	/*Write_IniFile = 0;

	char buff[2048];
	strcpy(buff, ProjectFolder);
	strcat(buff, "\\Load_Level.gds");

	Write_IniFile = fopen(buff, "wt");

	fprintf(Write_IniFile, "%s\n", "[Start_Level]");
	fprintf(Write_IniFile, "%s%s\n", "First_Level=", App->GDCL_Scene_Data->S_Scene[0]->GDSceneName);

	fclose(Write_IniFile);
	App->CL10_PB->Nudge();*/
}

// *************************************************************************
// *					Create_Config_File Terry Berine					   *
// *************************************************************************
void SB_Build::Create_Config_File(void)
{
	/*Write_IniFile = 0;

	char buff[2048];
	strcpy(buff, ProjectFolder);
	strcat(buff, "\\Config.cfg");

	Write_IniFile = fopen(buff, "wt");

	fprintf(Write_IniFile, "%s\n", "[Config]");
	fprintf(Write_IniFile, "%s%s\n", "Version=", "1.0");
	fprintf(Write_IniFile, "%s%i\n", "Full_Screen=", App->CL10_Project->CF_Full_Screen);

	fclose(Write_IniFile);
	App->CL10_PB->Nudge();*/
}

// *************************************************************************
// *					Read_From_Config Terry Berine					   *
// *************************************************************************
void SB_Build::Read_From_Config(void)
{
	char chr_Tag1[1024];
	char StartFile[1024];
	strcpy(StartFile, App->EquityDirecory_FullPath);
	strcat(StartFile, "\\");
	strcat(StartFile, "Data\\StartUp.gcf");

	/*App->CL_Ini->SetPathName(StartFile);

	CF_Full_Screen = App->CL_Ini->GetBool("Config", "Full_Screen", 1);

	App->CL_Ini->GetString("Config", "Project_Path", chr_Tag1, 1024);
	strcpy(App->CL10_Project->StartFolder, chr_Tag1);

	App->CL_Ini->GetString("Config", "Game_Name", chr_Tag1, 1024);
	strcpy(App->CL10_Project->GameName, chr_Tag1);*/

}