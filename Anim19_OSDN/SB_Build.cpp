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

	CoreDataFolder[0] = 0;
	SoundFolder[0] = 0;

	m_Build_Sub_Folder[0] = 0;

	//---------------------------------
	Sub_Build_Folder[0] = 0;
	m_Ini_Path_File_Name[0] = 0;
	m_Level_Folder_Path[0] = 0;
	m_Main_Assets_Path[0] = 0;
	m_Aera_Folder_Path[0] = 0;
	m_Players_Folder_Path[0] = 0;
	m_Cameras_Folder_Path[0] = 0;
	m_Objects_Folder_Path[0] = 0;
	m_Display_Folder_Path[0] = 0;

	WriteFile = nullptr;
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
		SendDlgItemMessage(hDlg, IDC_CK_BL_DESKTOP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

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

		if (GetDlgItem(hDlg, IDC_CK_BL_DESKTOP) == (HWND)lParam)
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

		
		if (LOWORD(wParam) == IDC_CK_BL_DESKTOP)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_BL_DESKTOP);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				char Desktop[MAX_PATH];
				strcpy(Desktop, App->SBC_FileIO->DeskTop_Folder);
				strcat(Desktop, "\\");

				strcpy(App->Com_CDialogs->szSelectedDir, Desktop);
				strcpy(App->SBC_Build->StartFolder, App->Com_CDialogs->szSelectedDir);
				SetDlgItemText(hDlg, IDC_STLOCATION, (LPCTSTR)App->SBC_Build->StartFolder);

				EnableWindow(GetDlgItem(hDlg, IDC_BTBROWSE), 0);
				return 1;
			}
			else
			{
				EnableWindow(GetDlgItem(hDlg, IDC_BTBROWSE), 1);
				return 1;
			}
			return TRUE;
		}

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

	CoreDataFolder[0] = 0;
	SoundFolder[0] = 0;


//	App->CL10_PB = new GD10_PB();
//	App->CL10_PB->StartNewProgressBar();

	//App->CL_Dialogs->MessageLoad("Please Wait");

	strcpy(ProjectFolder, App->Com_CDialogs->szSelectedDir);
	strcat(ProjectFolder, GameName);
	strcat(ProjectFolder, "_Project");

	int test = CreateDirectory(ProjectFolder, NULL);
	/*if(test == 0)
	{
		App->Say("Failed");
	}
	else
	{*/

	strcpy(MediaFolder, ProjectFolder);
	strcat(MediaFolder, "\\");
	strcat(MediaFolder, "Media");
	CreateDirectory(MediaFolder, NULL);

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

	strcpy(m_Build_Sub_Folder, ProjectFolder);
	strcat(m_Build_Sub_Folder, "\\");
	strcat(m_Build_Sub_Folder, "Game");
	Build_Project();

	//App->CL10_PB->Set_Progress_Text("Copy_ZipFiles");
	Copy_ZipFiles();
	Copy_Sound_Files();

	App->Say("Game Created");

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

	//----------------------------- Plugin_ParticleFX.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Plugin_ParticleFX.dll");
	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\Plugin_ParticleFX.dll");
	CopyFile(SourceFile, DestinationFile, false);
//	App->CL10_PB->Nudge();

	//----------------------------- Plugin_ParticleFX.dll
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Roboto-Medium.ttf");
	strcpy(DestinationFile, ProjectFolder);
	strcat(DestinationFile, "\\Roboto-Medium.ttf");
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
	////App->CL10_PB->Nudge();
	////----------------------------- Equity.zip
	//strcpy(SourceFile, App->EquityDirecory_FullPath);
	//strcat(SourceFile, "\\Media\\Core_Data\\Equity.zip");

	//strcpy(DestinationFile, CoreDataFolder);
	//strcat(DestinationFile, "\\Equity.zip");

	//CopyFile(SourceFile, DestinationFile, false);
	////App->CL10_PB->Nudge();
	//----------------------------- OgreCore.zip
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Media\\Core_Data\\OgreCore.zip");
	strcpy(DestinationFile, CoreDataFolder);
	strcat(DestinationFile, "\\OgreCore.zip");
	CopyFile(SourceFile, DestinationFile, false);
	//App->CL10_PB->Nudge();

	//----------------------------- skybox.zip
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Media\\Core_Data\\skybox.zip");
	strcpy(DestinationFile, CoreDataFolder);
	strcat(DestinationFile, "\\skybox.zip");
	CopyFile(SourceFile, DestinationFile, false);
	//App->CL10_PB->Nudge();

	//----------------------------- skybox.zip
	strcpy(SourceFile, App->EquityDirecory_FullPath);
	strcat(SourceFile, "\\Media\\App_Resources\\App_Resources.zip");
	strcpy(DestinationFile, CoreDataFolder);
	strcat(DestinationFile, "\\App_Resources.zip");
	CopyFile(SourceFile, DestinationFile, false);
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
// *					Copy_Sound_Files Terry Berine					   *
// *************************************************************************
void SB_Build::Copy_Sound_Files(void)
{
	char StartFolder[MAX_PATH];
	strcpy(StartFolder, App->EquityDirecory_FullPath);
	strcat(StartFolder, "\\");
	strcat(StartFolder, "Media\\Sounds\\");

	char Destination[MAX_PATH];
	strcpy(Destination, SoundFolder);
	strcat(Destination, "\\");

	Copy_Assets(StartFolder, Destination);
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
	//char chr_Tag1[1024];
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

// *************************************************************************
// *	  		Build_Project:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Build::Build_Project()
{

	if (_mkdir(m_Build_Sub_Folder) == 0)
	{
		_chdir(m_Build_Sub_Folder);
	}
	else
	{
		_chdir(m_Build_Sub_Folder);
	}

	bool test = Build_Project_Ini();
	if (test == 0)
	{
		return 0;
	}

	Build_Level_Folder();
	Build_Main_Asset_Folder();

	_chdir(m_Level_Folder_Path);

	if (App->SBC_Scene->Area_Added == 1)
	{
		Build_Area_Folder();
	}

	if (App->SBC_Scene->Player_Added == 1)
	{
		Build_Players_Folder();
	}

	Build_Cameras_Folder();
	Build_Objects_Folder();
	Build_Display_Folder();

	return 1;
}

// *************************************************************************
// *	  		Build_Project_Ini:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Build::Build_Project_Ini()
{
	m_Ini_Path_File_Name[0] = 0;

	strcpy(m_Ini_Path_File_Name, m_Build_Sub_Folder);
	strcat(m_Ini_Path_File_Name, "\\");
	strcat(m_Ini_Path_File_Name, "Game.gdat");

	int test = App->SBC_FileIO->SearchFolders(m_Build_Sub_Folder, "\\Game.gdat");
	if (test == 1)
	{
		App->SBC_Dialogs->YesNo("File Exsits", "Do you want to update File", 1);

		bool Doit = App->SBC_Dialogs->Canceled;
		if (Doit == 1)
		{
			return 0;
		}
	}

	WriteFile = nullptr;

	WriteFile = fopen(m_Ini_Path_File_Name, "wt");

	if (!WriteFile)
	{
		App->Say("Cant Create File");
		return 0;
	}

	fprintf(WriteFile, "%s\n", "[Version_Data]");
	fprintf(WriteFile, "%s%s\n", "Version=", "V1.2");

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", "[Files]");
	fprintf(WriteFile, "%s%s\n", "Project_Name=", GameName);
	fprintf(WriteFile, "%s%s\n", "Level_Name=", GameName);
	
	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", "[Options]");
	fprintf(WriteFile, "%s%i\n", "Aeras_Count=", App->SBC_Scene->Area_Count);
	fprintf(WriteFile, "%s%i\n", "Players_Count=", App->SBC_Scene->Player_Count);
	fprintf(WriteFile, "%s%i\n", "Cameras_Count=", App->SBC_Scene->Camera_Count);
	fprintf(WriteFile, "%s%i\n", "Objects_Count=", App->SBC_Scene->Object_Count);
	fprintf(WriteFile, "%s%i\n", "Objects_ID_Count=", App->SBC_Scene->UniqueID_Object_Counter);

	int Adjusted = App->SBC_LookUps->Get_Adjusted_Counters_Count();
	fprintf(WriteFile, "%s%i\n", "Counters_Count=", Adjusted);
	fprintf(WriteFile, "%s%i\n", "Counters_ID_Count=", App->SBC_Scene->UniqueID_Counters_Count);

	fclose(WriteFile);

	return 1;
}

// *************************************************************************
// *	  	Build_Level_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Build::Build_Level_Folder()
{
	strcpy(m_Level_Folder_Path, m_Build_Sub_Folder);
	strcat(m_Level_Folder_Path, "\\");
	strcat(m_Level_Folder_Path, GameName);

	// First Level Folder
	if (_mkdir(m_Level_Folder_Path) == 0)
	{
		_chdir(m_Level_Folder_Path);
	}
	else
	{
		_chdir(m_Level_Folder_Path);
	}

	return 1;
}

// *************************************************************************
// *	  	Build_Main_Asset_Folder:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Build::Build_Main_Asset_Folder()
{
	char LastFolder[MAX_PATH];

//	if (Directory_Changed_Flag == 1)
	{
		strcpy(LastFolder, App->SBC_Project->m_Main_Assets_Path);
	}

	m_Main_Assets_Path[0] = 0;

	strcpy(m_Main_Assets_Path, m_Level_Folder_Path);
	strcat(m_Main_Assets_Path, "\\");
	strcat(m_Main_Assets_Path, "Assets");
	strcat(m_Main_Assets_Path, "\\");

	if (_mkdir(m_Main_Assets_Path) == 0)
	{
		_chdir(m_Main_Assets_Path);
	}
	else
	{
		_chdir(m_Main_Assets_Path);
	}

	//if (Directory_Changed_Flag == 1)
	{
		Copy_Assets(LastFolder, m_Main_Assets_Path);
	}

	//Directory_Changed_Flag = 0;

	_chdir(m_Level_Folder_Path); // Return to Level Folder
	return 1;
}

// *************************************************************************
// *	  	Save_Area_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Build::Build_Area_Folder()
{
	m_Aera_Folder_Path[0] = 0;

	strcpy(m_Aera_Folder_Path, m_Level_Folder_Path);
	strcat(m_Aera_Folder_Path, "\\");
	strcat(m_Aera_Folder_Path, "Areas");


	if (_mkdir(m_Aera_Folder_Path) == 0)
	{
		_chdir(m_Aera_Folder_Path);
	}
	else
	{
		_chdir(m_Aera_Folder_Path);
	}

	Build_Areas_Data();

	_chdir(m_Level_Folder_Path); // Return to Level Folder
	return 1;
}

// *************************************************************************
// *	  		Save_Areas_Data:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Build::Build_Areas_Data()
{
	Ogre::Vector3 Pos;
	char File[1024];

	strcpy(File, m_Aera_Folder_Path);
	strcat(File, "\\");
	strcat(File, "Areas.aer");

	WriteFile = nullptr;

	WriteFile = fopen(File, "wt");

	if (!WriteFile)
	{
		App->Say("Cant Create File");
		App->Say_Win(File);
		return 0;
	}

	fprintf(WriteFile, "%s\n", "[Version_Data]");
	fprintf(WriteFile, "%s%s\n", "Version=", "V1.2");

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", "[Counters]");
	fprintf(WriteFile, "%s%i\n", "Areas_Count=", App->SBC_Scene->Area_Count);

	fprintf(WriteFile, "%s\n", " ");

	char Cbuff[255];
	char buff[255];

	float x = 0;
	float y = 0;
	float z = 0;

	int Count = 0;
	while (Count < App->SBC_Scene->Area_Count)
	{
		strcpy(buff, "[Area_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);
		strcat(buff, "]");

		fprintf(WriteFile, "%s\n", buff); // Header also Player name until changed by user

		fprintf(WriteFile, "%s%s\n", "Area_Name=", App->SBC_Scene->B_Area[Count]->Area_Name); // Change

		fprintf(WriteFile, "%s%s\n", "Area_File=", App->SBC_Scene->B_Area[Count]->Area_FileName);
		fprintf(WriteFile, "%s%s\n", "Area_Path_File=", App->SBC_Scene->B_Area[Count]->Area_Path_And_FileName);
		fprintf(WriteFile, "%s%s\n", "Area_Resource_Path=", App->SBC_Scene->B_Area[Count]->Area_Resource_Path);
		fprintf(WriteFile, "%s%s\n", "Material_File=", App->SBC_Scene->B_Area[Count]->Material_File);

		fprintf(WriteFile, "%s\n", "[Position]");
		x = App->SBC_Scene->B_Area[Count]->Area_Node->getPosition().x;
		y = App->SBC_Scene->B_Area[Count]->Area_Node->getPosition().y;
		z = App->SBC_Scene->B_Area[Count]->Area_Node->getPosition().z;

		fprintf(WriteFile, "%s%f,%f,%f\n", "Mesh_Pos=", x, y, z);


		// ------------------------------------ Environment

		fprintf(WriteFile, "%s\n", "[Environment]");

		//--------------- Sound
		fprintf(WriteFile, "%s%s\n", "Sound_File=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Sound_File);
		fprintf(WriteFile, "%s%f\n", "Snd_Volume=", App->SBC_Scene->B_Area[0]->S_Environment[0]->SndVolume);

		fprintf(WriteFile, "%s%i\n", "Sound_Play=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Play);
		fprintf(WriteFile, "%s%i\n", "Sound_Loop=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Loop);

		//--------------- Light

		x = App->SBC_Scene->B_Area[0]->S_Environment[0]->AmbientColour.x;
		y = App->SBC_Scene->B_Area[0]->S_Environment[0]->AmbientColour.y;
		z = App->SBC_Scene->B_Area[0]->S_Environment[0]->AmbientColour.z;
		fprintf(WriteFile, "%s%f,%f,%f\n", "Ambient_Colour=", x, y, z);

		x = App->SBC_Scene->B_Area[0]->S_Environment[0]->DiffuseColour.x;
		y = App->SBC_Scene->B_Area[0]->S_Environment[0]->DiffuseColour.y;
		z = App->SBC_Scene->B_Area[0]->S_Environment[0]->DiffuseColour.z;
		fprintf(WriteFile, "%s%f,%f,%f\n", "Diffuse_Colour=", x, y, z);

		x = App->SBC_Scene->B_Area[0]->S_Environment[0]->SpecularColour.x;
		y = App->SBC_Scene->B_Area[0]->S_Environment[0]->SpecularColour.y;
		z = App->SBC_Scene->B_Area[0]->S_Environment[0]->SpecularColour.z;
		fprintf(WriteFile, "%s%f,%f,%f\n", "Specular_Colour=", x, y, z);

		x = App->SBC_Scene->B_Area[0]->S_Environment[0]->Light_Position.x;
		y = App->SBC_Scene->B_Area[0]->S_Environment[0]->Light_Position.y;
		z = App->SBC_Scene->B_Area[0]->S_Environment[0]->Light_Position.z;
		fprintf(WriteFile, "%s%f,%f,%f\n", "Light_Position=", x, y, z);

		//--------------- Sky
		fprintf(WriteFile, "%s%i\n", "Sky_Enable=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Enabled);
		fprintf(WriteFile, "%s%i\n", "Sky_Type=", App->SBC_Scene->B_Area[0]->S_Environment[0]->type);
		fprintf(WriteFile, "%s%s\n", "Sky_Material=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Material);
		fprintf(WriteFile, "%s%f\n", "Sky_Curvature=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Curvature);
		fprintf(WriteFile, "%s%f\n", "Sky_Tiling=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Tiling);
		fprintf(WriteFile, "%s%f\n", "Sky_Distance=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Distance);

		//--------------- Fog
		fprintf(WriteFile, "%s%i\n", "Fog_On=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_On);
		fprintf(WriteFile, "%s%i\n", "Fog_Mode=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_Mode);

		x = App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_Colour.x;
		y = App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_Colour.y;
		z = App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_Colour.z;
		fprintf(WriteFile, "%s%f,%f,%f\n", "Fog_Colour=", x, y, z);

		fprintf(WriteFile, "%s%f\n", "Fog_Start=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_Start);
		fprintf(WriteFile, "%s%f\n", "Fog_End=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_End);
		fprintf(WriteFile, "%s%f\n", "Fog_Density=", App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_Density);

		Count++;
	}

	fclose(WriteFile);

	return 1;
}

// *************************************************************************
// *	  	Build_Players_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Build::Build_Players_Folder()
{
	m_Players_Folder_Path[0] = 0;

	strcpy(m_Players_Folder_Path, m_Level_Folder_Path);
	strcat(m_Players_Folder_Path, "\\");
	strcat(m_Players_Folder_Path, "Players");


	_mkdir(m_Players_Folder_Path);

	_chdir(m_Players_Folder_Path);

	Build_Player_Data();

	_chdir(m_Level_Folder_Path); // Return to Level Folder
	return 1;
}

// *************************************************************************
// *	  	Build_Player_Data:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Build::Build_Player_Data()
{
	Ogre::Vector3 Pos;
	char File[1024];

	float W = 0;
	float X = 0;
	float Y = 0;
	float Z = 0;

	strcpy(File, m_Players_Folder_Path);
	strcat(File, "\\");
	strcat(File, "Players.ply");

	WriteFile = nullptr;

	WriteFile = fopen(File, "wt");

	if (!WriteFile)
	{
		App->Say("Cant Create File");
		App->Say_Win(File);
		return 0;
	}

	fprintf(WriteFile, "%s\n", "[Version_Data]");
	fprintf(WriteFile, "%s%s\n", "Version=", "V1.2");

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", "[Counters]");
	fprintf(WriteFile, "%s%i\n", "Player_Count=", App->SBC_Scene->Player_Count);

	fprintf(WriteFile, "%s\n", " ");

	char Cbuff[255];
	char buff[255];
	int Count = 0;
	while (Count < App->SBC_Scene->Player_Count)
	{
		strcpy(buff, "[Player_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);
		strcat(buff, "]");

		fprintf(WriteFile, "%s\n", buff); // Header also Player name until changed by user

		fprintf(WriteFile, "%s%s\n", "Player_Name=", App->SBC_Scene->B_Player[Count]->Player_Name);

		Pos.x = App->SBC_Scene->B_Player[Count]->StartPos.x;
		Pos.y = App->SBC_Scene->B_Player[Count]->StartPos.y;
		Pos.z = App->SBC_Scene->B_Player[Count]->StartPos.z;
		fprintf(WriteFile, "%s%f,%f,%f\n", "Start_Position=", Pos.x, Pos.y, Pos.z);

		W = App->SBC_Scene->B_Player[Count]->Physics_Rotation.getW();
		X = App->SBC_Scene->B_Player[Count]->Physics_Rotation.getX();
		Y = App->SBC_Scene->B_Player[Count]->Physics_Rotation.getY();
		Z = App->SBC_Scene->B_Player[Count]->Physics_Rotation.getZ();

		fprintf(WriteFile, "%s%f,%f,%f,%f\n", "Start_Rotation=", W, X, Y, Z);

		fprintf(WriteFile, "%s%s\n", "Shape=", "Capsule");
		fprintf(WriteFile, "%s%f\n", "Mass=", App->SBC_Scene->B_Player[Count]->Capsule_Mass);
		fprintf(WriteFile, "%s%f\n", "Radius=", App->SBC_Scene->B_Player[Count]->Capsule_Radius);
		fprintf(WriteFile, "%s%f\n", "Height=", App->SBC_Scene->B_Player[Count]->Capsule_Height);
		fprintf(WriteFile, "%s%f\n", "Ground_Speed=", App->SBC_Scene->B_Player[Count]->Ground_speed);
		fprintf(WriteFile, "%s%f\n", "Cam_Height=", App->SBC_Scene->B_Player[Count]->PlayerHeight);
		fprintf(WriteFile, "%s%f\n", "Turn_Rate=", App->SBC_Scene->B_Player[Count]->TurnRate);

		Count++;
	}

	// ---------------------------------------- Player Locations

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	fprintf(WriteFile, "%s\n", " ");
	fprintf(WriteFile, "%s\n", "[Locations]");

	int RealCount = App->Cl_LookUps->Player_Location_GetCount(); // Get The real Count Minus Deleted Files

	fprintf(WriteFile, "%s%i\n", "Locations_Count=", RealCount);

	int Location = 0; // Correct for Deleted Files

	Count = 0;
	while (Count < App->SBC_Scene->Player_Location_Count)
	{
		if (App->SBC_Scene->B_Locations[Count]->Deleted == 0)
		{
			fprintf(WriteFile, "%s\n", " ");

			char Cbuff[255];
			char buff[255];
			strcpy(buff, "[Location_");
			_itoa(Location, Cbuff, 10);
			strcat(buff, Cbuff);
			strcat(buff, "]");
			fprintf(WriteFile, "%s\n", buff);

			fprintf(WriteFile, "%s%i\n", "Locatoin_ID=", App->SBC_Scene->B_Locations[Count]->Location_ID);
			fprintf(WriteFile, "%s%s\n", "Name=", App->SBC_Scene->B_Locations[Count]->Name);

			x = App->SBC_Scene->B_Locations[Count]->Current_Position.x;
			y = App->SBC_Scene->B_Locations[Count]->Current_Position.y;
			z = App->SBC_Scene->B_Locations[Count]->Current_Position.z;
			fprintf(WriteFile, "%s%f,%f,%f\n", "Mesh_Position=", x, y, z);

			x = App->SBC_Scene->B_Locations[Count]->Physics_Position.getX();
			y = App->SBC_Scene->B_Locations[Count]->Physics_Position.getY();
			z = App->SBC_Scene->B_Locations[Count]->Physics_Position.getZ();
			fprintf(WriteFile, "%s%f,%f,%f\n", "Physics_Position=", x, y, z);

			w = App->SBC_Scene->B_Locations[Count]->Physics_Rotation.getW();
			x = App->SBC_Scene->B_Locations[Count]->Physics_Rotation.getX();
			y = App->SBC_Scene->B_Locations[Count]->Physics_Rotation.getY();
			z = App->SBC_Scene->B_Locations[Count]->Physics_Rotation.getZ();
			fprintf(WriteFile, "%s%f,%f,%f,%f\n", "Physics_Rotation=", w, x, y, z);
			Location++;
		}

		Count++;
	}

	fclose(WriteFile);

	return 1;
}

// *************************************************************************
// *	  	Build_Cameras_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Build::Build_Cameras_Folder()
{
	m_Cameras_Folder_Path[0] = 0;

	strcpy(m_Cameras_Folder_Path, m_Level_Folder_Path);
	strcat(m_Cameras_Folder_Path, "\\");
	strcat(m_Cameras_Folder_Path, "Cameras");

	if (_mkdir(m_Cameras_Folder_Path) == 0)
	{
		_chdir(m_Cameras_Folder_Path);
	}
	else
	{
		_chdir(m_Cameras_Folder_Path);
	}

	Build_Cameras_Data();

	_chdir(m_Level_Folder_Path); // Return to Level Folder

	return 1;
}

// *************************************************************************
// *	  		Build_Cameras_Data:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Build::Build_Cameras_Data()
{
	Ogre::Vector3 Pos;
	char File[1024];

	strcpy(File, m_Cameras_Folder_Path);
	strcat(File, "\\");
	strcat(File, "Cameras.epf");

	WriteFile = nullptr;

	WriteFile = fopen(File, "wt");

	if (!WriteFile)
	{
		App->Say("Cant Create File");
		App->Say_Win(File);
		return 0;
	}

	fprintf(WriteFile, "%s\n", "[Version_Data]");
	fprintf(WriteFile, "%s%s\n", "Version=", "V1.2");

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", "[Counters]");
	fprintf(WriteFile, "%s%i\n", "Cameras_Count=", App->SBC_Scene->Camera_Count);

	fprintf(WriteFile, "%s\n", " ");

	char Cbuff[255];
	char buff[255];

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	int Count = 0;
	while (Count < App->SBC_Scene->Camera_Count)
	{
		strcpy(buff, "[Camera_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);
		strcat(buff, "]");

		fprintf(WriteFile, "%s\n", buff); // Header also Player name until changed by user

		fprintf(WriteFile, "%s%s\n", "Camera_Name=", App->SBC_Scene->B_Camera[Count]->Camera_Name); // Change

		//---------------------------------- Camera Pos
		x = App->SBC_Scene->B_Camera[Count]->CamPos.x;
		y = App->SBC_Scene->B_Camera[Count]->CamPos.y;
		z = App->SBC_Scene->B_Camera[Count]->CamPos.z;

		fprintf(WriteFile, "%s%f,%f,%f\n", "Camera_Pos=", x, y, z);

		//---------------------------------- Camera Look At
		x = App->SBC_Scene->B_Camera[Count]->LookAt.x;
		y = App->SBC_Scene->B_Camera[Count]->LookAt.y;
		z = App->SBC_Scene->B_Camera[Count]->LookAt.z;

		fprintf(WriteFile, "%s%f,%f,%f\n", "LookAt=", x, y, z);

		//---------------------------------- Camera Quaternion
		w = App->SBC_Scene->B_Camera[Count]->Cam_Quat.w;
		x = App->SBC_Scene->B_Camera[Count]->Cam_Quat.x;
		y = App->SBC_Scene->B_Camera[Count]->Cam_Quat.y;
		z = App->SBC_Scene->B_Camera[Count]->Cam_Quat.z;

		fprintf(WriteFile, "%s%f,%f,%f,%f\n", "Camera_Quat=", w, x, y, z);

		Count++;
	}

	fclose(WriteFile);

	return 1;
}

// *************************************************************************
// *	  	Build_Objects_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Build::Build_Objects_Folder()
{
	m_Objects_Folder_Path[0] = 0;

	strcpy(m_Objects_Folder_Path, m_Level_Folder_Path);
	strcat(m_Objects_Folder_Path, "\\");
	strcat(m_Objects_Folder_Path, "Objects");

	_mkdir(m_Objects_Folder_Path);
	_chdir(m_Objects_Folder_Path);

	Build_Objects_Data();

	_chdir(m_Level_Folder_Path); // Return to Level Folder
	return 1;
}

// *************************************************************************
// *	  		Build_Objects_Data:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Build::Build_Objects_Data()
{
	Ogre::Vector3 Pos;
	char File[1024];

	strcpy(File, m_Objects_Folder_Path);
	strcat(File, "\\");
	strcat(File, "Objects.efd");

	WriteFile = nullptr;

	WriteFile = fopen(File, "wt");

	if (!WriteFile)
	{
		App->Say("Cant Create File");
		App->Say_Win(File);
		return 0;
	}

	fprintf(WriteFile, "%s\n", "[Version_Data]");
	fprintf(WriteFile, "%s%s\n", "Version=", "V1.2");

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", " ");

	char Cbuff[255];
	char buff[255];

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	int new_Count = 0;

	int Count = 0;
	while (Count < App->SBC_Scene->Object_Count)
	{
		if (App->SBC_Scene->B_Object[Count]->Deleted == 0)
		{
			strcpy(buff, "[Object_");
			_itoa(new_Count, Cbuff, 10);
			strcat(buff, Cbuff);
			strcat(buff, "]");

			fprintf(WriteFile, "%s\n", buff); // Header also Player name until changed by user

			fprintf(WriteFile, "%s%s\n", "Mesh_Name=", App->SBC_Scene->B_Object[Count]->Mesh_Name); // Change

			fprintf(WriteFile, "%s%s\n", "Mesh_File=", App->SBC_Scene->B_Object[Count]->Mesh_FileName);
			fprintf(WriteFile, "%s%s\n", "Mesh_Resource_Path=", App->SBC_Scene->B_Object[Count]->Mesh_Resource_Path);
			fprintf(WriteFile, "%s%s\n", "Material_File=", App->SBC_Scene->B_Object[Count]->Material_File);
			fprintf(WriteFile, "%s%i\n", "Object_ID=", App->SBC_Scene->B_Object[Count]->This_Object_ID);
			fprintf(WriteFile, "%s%i\n", "Object_Type=", App->SBC_Scene->B_Object[Count]->Type);
			fprintf(WriteFile, "%s%i\n", "Object_Shape=", App->SBC_Scene->B_Object[Count]->Shape);
			fprintf(WriteFile, "%s%i\n", "Object_Usage=", App->SBC_Scene->B_Object[Count]->Usage);

			// Position
			x = App->SBC_Scene->B_Object[Count]->Mesh_Pos.x;
			y = App->SBC_Scene->B_Object[Count]->Mesh_Pos.y;
			z = App->SBC_Scene->B_Object[Count]->Mesh_Pos.z;
			fprintf(WriteFile, "%s%f,%f,%f\n", "Mesh_Pos=", x, y, z);

			// Mesh_Scale
			x = App->SBC_Scene->B_Object[Count]->Mesh_Scale.x;
			y = App->SBC_Scene->B_Object[Count]->Mesh_Scale.y;
			z = App->SBC_Scene->B_Object[Count]->Mesh_Scale.z;
			fprintf(WriteFile, "%s%f,%f,%f\n", "Mesh_Scale=", x, y, z);

			// Mesh_Rot
			x = App->SBC_Scene->B_Object[Count]->Mesh_Rot.x;
			y = App->SBC_Scene->B_Object[Count]->Mesh_Rot.y;
			z = App->SBC_Scene->B_Object[Count]->Mesh_Rot.z;
			fprintf(WriteFile, "%s%f,%f,%f\n", "Mesh_Rot=", x, y, z);

			// Mesh_Quat
			w = App->SBC_Scene->B_Object[Count]->Mesh_Quat.w;
			x = App->SBC_Scene->B_Object[Count]->Mesh_Quat.x;
			y = App->SBC_Scene->B_Object[Count]->Mesh_Quat.y;
			z = App->SBC_Scene->B_Object[Count]->Mesh_Quat.z;
			fprintf(WriteFile, "%s%f,%f,%f,%f\n", "Mesh_Quat=", w, x, y, z);

			// Physics_Quat
			w = App->SBC_Scene->B_Object[Count]->Physics_Quat.w;
			x = App->SBC_Scene->B_Object[Count]->Physics_Quat.x;
			y = App->SBC_Scene->B_Object[Count]->Physics_Quat.y;
			z = App->SBC_Scene->B_Object[Count]->Physics_Quat.z;
			fprintf(WriteFile, "%s%f,%f,%f,%f\n", "Physics_Quat=", w, x, y, z);
			//---------------------------------------------------------------------------------- Message Entity
			if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Message)
			{
				fprintf(WriteFile, "%s\n", "------------------- Message");
				fprintf(WriteFile, "%s%s\n", "Message_Text=", App->SBC_Scene->B_Object[Count]->Message_Text);

				x = App->SBC_Scene->B_Object[Count]->Message_PosX;
				y = App->SBC_Scene->B_Object[Count]->Message_PosY;
				fprintf(WriteFile, "%s%f,%f\n", "Message_Pos=", x, y);

				// Message Counter
				fprintf(WriteFile, "%s%i\n", "Message_Counter_ID=", App->SBC_Scene->B_Object[Count]->S_Message[0]->Counter_ID);
				fprintf(WriteFile, "%s%i\n", "Message_Trigger_Value=", App->SBC_Scene->B_Object[Count]->S_Message[0]->Trigger_Value);
				fprintf(WriteFile, "%s%i\n", "Message_Counter_Disabled=", App->SBC_Scene->B_Object[Count]->S_Message[0]->Counter_Disabled);
			}

			//---------------------------------------------------------------------------------- Sound Entity
			if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Sound)
			{
				fprintf(WriteFile, "%s%s\n", "Sound_File=", App->SBC_Scene->B_Object[Count]->Sound_File);
				fprintf(WriteFile, "%s%f\n", "Sound_Volume=", App->SBC_Scene->B_Object[Count]->SndVolume);
			}

			//---------------------------------------------------------------------------------- Colectable Entity
			if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Colectable)
			{
				fprintf(WriteFile, "%s%s\n", "Col_Sound_File=", App->SBC_Scene->B_Object[Count]->S_Collectable[0]->Sound_File);
				fprintf(WriteFile, "%s%f\n", "Col_Sound_Volume=", App->SBC_Scene->B_Object[Count]->S_Collectable[0]->SndVolume);
				fprintf(WriteFile, "%s%i\n", "Col_Play=", App->SBC_Scene->B_Object[Count]->S_Collectable[0]->Play);
				fprintf(WriteFile, "%s%s\n", "Col_Counter_Name=", App->SBC_Scene->B_Object[Count]->S_Collectable[0]->Counter_Name);
				fprintf(WriteFile, "%s%i\n", "Col_Counter_ID=", App->SBC_Scene->B_Object[Count]->S_Collectable[0]->Counter_ID);
				fprintf(WriteFile, "%s%i\n", "Col_Maths=", App->SBC_Scene->B_Object[Count]->S_Collectable[0]->Maths);
				fprintf(WriteFile, "%s%i\n", "Col_Value=", App->SBC_Scene->B_Object[Count]->S_Collectable[0]->Value);
			}

			//---------------------------------------------------------------------------------- Move Entity
			if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Move)
			{
				fprintf(WriteFile, "%s%f\n", "Move_Distance=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Move_Distance);
				fprintf(WriteFile, "%s%i\n", "Move_IsNegative=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->IsNegative);
				//	fprintf(WriteFile, "%s%s\n", "Move_MeshPos=", App->SBC_Scene->B_Object[Count]->S_MoveType->MeshPos);
				fprintf(WriteFile, "%s%f\n", "Move_NewPos=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Newpos);
				fprintf(WriteFile, "%s%i\n", "Move_ObjectID=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Object_To_Move_Index);
				fprintf(WriteFile, "%s%s\n", "Move_ObjectName=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Object_Name);
				//	fprintf(WriteFile, "%s%s\n", "Move_PhysicsPos=", App->SBC_Scene->B_Object[Count]->S_MoveType->PhysicsPos);
				fprintf(WriteFile, "%s%i\n", "Move_Re_Trigger=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Re_Trigger);
				fprintf(WriteFile, "%s%f\n", "Move_Speed=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Speed);
				fprintf(WriteFile, "%s%i\n", "Move_Triggered=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Triggered);
				fprintf(WriteFile, "%s%i\n", "Move_WhatDirection=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->WhatDirection);

				// Move Sound
				fprintf(WriteFile, "%s%s\n", "Move_Sound=", App->SBC_Scene->B_Object[Count]->Sound_File);
				fprintf(WriteFile, "%s%i\n", "Move_Play_Sound=", App->SBC_Scene->B_Object[Count]->Play_Sound);
				fprintf(WriteFile, "%s%f\n", "Move_Volume=", App->SBC_Scene->B_Object[Count]->SndVolume);

				// Move Counter
				fprintf(WriteFile, "%s%i\n", "Move_Counter_ID=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Counter_ID);
				fprintf(WriteFile, "%s%i\n", "Move_Trigger_Value=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Trigger_Value);
				fprintf(WriteFile, "%s%i\n", "Move_Counter_Disabled=", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Counter_Disabled);
	
			}

			//---------------------------------------------------------------------------------- Teleport Entity
			if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Teleport)
			{
				fprintf(WriteFile, "%s%s\n", "Tele_Goto=", App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Name);

				fprintf(WriteFile, "%s%i\n", "Tele_ID=", App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Location_ID);

				fprintf(WriteFile, "%s%s\n", "Tele_Sound=", App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Sound_File);
				fprintf(WriteFile, "%s%f\n", "Tele_Volume=", App->SBC_Scene->B_Object[Count]->S_Teleport[0]->SndVolume);
				fprintf(WriteFile, "%s%i\n", "Tele_Play=", App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Play);

				x = App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Player_Position.x;
				y = App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Player_Position.y;
				z = App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Player_Position.z;
				fprintf(WriteFile, "%s%f,%f,%f\n", "Tele_Mesh_Position=", x, y, z);

				x = App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Position.getX();
				y = App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Position.getY();
				z = App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Position.getZ();
				fprintf(WriteFile, "%s%f,%f,%f\n", "Tele_Physics_Position=", x, y, z);

				w = App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Rotation.getW();
				x = App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Rotation.getX();
				y = App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Rotation.getY();
				z = App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Rotation.getZ();
				fprintf(WriteFile, "%s%f,%f,%f,%f\n", "Tele_Physics_Rotation=", w, x, y, z);
			}


			fprintf(WriteFile, "%s\n", " ");
			new_Count++;
		}

		Count++;
	}

	fprintf(WriteFile, "%s\n", "[Counters]");
	fprintf(WriteFile, "%s%i\n", "Objects_Count=", new_Count);

	fclose(WriteFile);

	return 1;
}

// *************************************************************************
// *	  	Build_Display_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Build::Build_Display_Folder()
{
	m_Display_Folder_Path[0] = 0;

	strcpy(m_Display_Folder_Path, m_Level_Folder_Path);
	strcat(m_Display_Folder_Path, "\\");
	strcat(m_Display_Folder_Path, "Display");

	_mkdir(m_Display_Folder_Path);
	_chdir(m_Display_Folder_Path);

	Build_Display_Data();

	_chdir(m_Level_Folder_Path); // Return to Level Folder
	return 1;
}

// *************************************************************************
// *	  		Build_Display_Data:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Build::Build_Display_Data()
{
	Ogre::Vector3 Pos;
	char File[1024];

	strcpy(File, m_Display_Folder_Path);
	strcat(File, "\\");
	strcat(File, "Counters.edf");

	WriteFile = nullptr;

	WriteFile = fopen(File, "wt");

	if (!WriteFile)
	{
		App->Say("Cant Create File");
		App->Say_Win(File);
		return 0;
	}

	fprintf(WriteFile, "%s\n", "[Version_Data]");
	fprintf(WriteFile, "%s%s\n", "Version=", "V1.2");

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", " ");

	char Cbuff[255];
	char buff[255];

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	int new_Count = 0;

	int Count = 0;
	while (Count < App->SBC_Scene->Counters_Count)
	{
		if (App->SBC_Scene->B_Counter[Count]->Deleted == 0)
		{
			strcpy(buff, "[Counter_");
			_itoa(new_Count, Cbuff, 10);
			strcat(buff, Cbuff);
			strcat(buff, "]");

			fprintf(WriteFile, "%s\n", buff); // Header also Player name until changed by user

			fprintf(WriteFile, "%s%s\n", "Counter_Name=", App->SBC_Scene->B_Counter[Count]->Panel_Name); // Change
			fprintf(WriteFile, "%s%i\n", "Counter_ID=", App->SBC_Scene->B_Counter[Count]->Unique_ID);

			x = App->SBC_Scene->B_Counter[Count]->PosX;
			y = App->SBC_Scene->B_Counter[Count]->PosY;
			fprintf(WriteFile, "%s%f,%f\n", "Counter_Pos=", x, y);

			fprintf(WriteFile, "%s%s\n", "Counter_Text=", App->SBC_Scene->B_Counter[Count]->Text);
			fprintf(WriteFile, "%s%i\n", "Counter_Display=", App->SBC_Scene->B_Counter[Count]->Show_Panel_Flag);
			fprintf(WriteFile, "%s%i\n", "Counter_Start=", App->SBC_Scene->B_Counter[Count]->Start_Value);

			fprintf(WriteFile, "%s\n", " ");
			new_Count++;
		}

		Count++;
	}

	fprintf(WriteFile, "%s\n", "[Counters]");
	fprintf(WriteFile, "%s%i\n", "Counters_Count=", new_Count);

	fclose(WriteFile);

	return 1;
}

// *************************************************************************
// *	  		Copy_Assets:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
bool SB_Build::Copy_Assets(char* SourceFolder, char* DestinationFolder)
{
	char SourceFile[MAX_PATH];
	char DestinationFile[MAX_PATH];

	char Path[MAX_PATH];
	strcpy(Path, SourceFolder);
	strcat(Path, "*.*");

	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(Path, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {

			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY))
			{

				strcpy(SourceFile, SourceFolder);
				strcat(SourceFile, fd.cFileName);

				strcpy(DestinationFile, DestinationFolder);
				strcat(DestinationFile, fd.cFileName);

				CopyFile(SourceFile, DestinationFile, false);
			}

		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	return 1;
}