/*
Copyright (c) 2021 Equity Scene Builder and Equity Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

// :- Terry and Hazel Flanigan 2022

*/

#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include "SB_Project.h"


SB_Project::SB_Project()
{
	
	strcpy(m_Main_Assets_Path,"None");

	strcpy(m_Project_Sub_Folder, App->EquityDirecory_FullPath);
	strcat(m_Project_Sub_Folder, "\\");
	strcat(m_Project_Sub_Folder, "Projects");
	strcat(m_Project_Sub_Folder, "\\");
	strcat(m_Project_Sub_Folder, "First_Project");
	strcat(m_Project_Sub_Folder, "_Prj");

	strcpy(m_Project_Name, "First_Project");
	strcpy(m_Level_Name, "First_Level");

	m_Level_Folder_Path[0] = 0;
	m_Players_Folder_Path[0] = 0;
	m_Objects_Folder_Path[0] = 0;
	m_Cameras_Folder_Path[0] = 0;

	m_Ini_Path_File_Name[0] = 0;
	
	m_Level_File_Name[0] = 0;

	WriteFile =			NULL;

	Project_Loaded = 0;
	Directory_Changed_Flag = 0;
	Set_QuickLoad_Flag = 1;
}


SB_Project::~SB_Project()
{
}

// *************************************************************************
// *	  			Reset_Class:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Reset_Class()
{
	strcpy(m_Project_Name, "First_Project");
	strcpy(m_Level_Name, "First_Level");

	return 1;
}

// *************************************************************************
// *	  Start_Save_Project_Dialog:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Start_Save_Project_Dialog()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_PROJECT, App->Fdlg, (DLGPROC)Save_Project_Dialog_Proc);
	return 1;
}

// *************************************************************************
// *		Save_Project_Dialog_Proc:- Terry and Hazel Flanigan 2022  	   *
// *************************************************************************
LRESULT CALLBACK SB_Project::Save_Project_Dialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STPJFOLDERPATH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPROJECTNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STLEVELNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_STPATH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPN, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STLN, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		SendDlgItemMessage(hDlg, IDC_BTCHANGE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTCHANGELEVEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_CK_SP_DESKTOP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		
		
		SendDlgItemMessage(hDlg, IDC_BTPJBROWSE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STBANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_CKQUICKLOAD, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_STPROJECTNAME, (LPCTSTR)App->SBC_Project->m_Project_Name);
		SetDlgItemText(hDlg, IDC_STLEVELNAME, (LPCTSTR)App->SBC_Project->m_Level_Name);
		SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->m_Project_Sub_Folder);

		SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->m_Project_Sub_Folder);

		SetDlgItemText(hDlg, IDC_STBANNER, (LPCTSTR)"Save Project As");
		
		HWND temp = GetDlgItem(hDlg, IDC_CKQUICKLOAD);
		SendMessage(temp, BM_SETCHECK, 1, 0);

		return TRUE;
	}

	case WM_CTLCOLORSTATIC:
	{

		if (GetDlgItem(hDlg, IDC_STPJFOLDERPATH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STPROJECTNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STLEVELNAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_STPN) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STLN) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 255));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}
		
		if (GetDlgItem(hDlg, IDC_STPATH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STBANNER) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_CKQUICKLOAD) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_CK_SP_DESKTOP) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
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

		if (some_item->idFrom == IDC_BTCHANGE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTCHANGELEVEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}
		
		if (some_item->idFrom == IDC_BTPJBROWSE && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

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

		return CDRF_DODEFAULT;
	}
	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_CK_SP_DESKTOP)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_SP_DESKTOP);

			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				strcpy(App->SBC_Project->m_Project_Sub_Folder, App->SBC_FileIO->DeskTop_Folder);
				strcat(App->SBC_Project->m_Project_Sub_Folder, "\\");
				strcat(App->SBC_Project->m_Project_Sub_Folder, App->SBC_Project->m_Project_Name);
				strcat(App->SBC_Project->m_Project_Sub_Folder, "_Prj");

				SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->m_Project_Sub_Folder);

				App->SBC_Project->Directory_Changed_Flag = 1;

				EnableWindow(GetDlgItem(hDlg, IDC_BTPJBROWSE), 0);
				EnableWindow(GetDlgItem(hDlg, IDC_STPJFOLDERPATH), 0);

			}
			else
			{
				EnableWindow(GetDlgItem(hDlg, IDC_BTPJBROWSE), 1);
				EnableWindow(GetDlgItem(hDlg, IDC_STPJFOLDERPATH), 1);
			}

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDC_BTPJBROWSE)
		{
			strcpy(App->Com_CDialogs->BrowserMessage, "Select Folder To Place New Project a sub folder will be created");
			int Test = App->Com_CDialogs->StartBrowser("", App->Fdlg);

			if (Test == 0){return true;}

			strcpy(App->SBC_Project->m_Project_Sub_Folder, App->Com_CDialogs->szSelectedDir);
			strcat(App->SBC_Project->m_Project_Sub_Folder, App->SBC_Project->m_Project_Name);
			strcat(App->SBC_Project->m_Project_Sub_Folder, "_Prj");

			SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->m_Project_Sub_Folder);
			
			App->SBC_Project->Directory_Changed_Flag = 1;

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTCHANGE)
		{
			strcpy(App->SBC_Dialogs->btext, "Change Project Name");
			strcpy(App->SBC_Dialogs->Chr_Text, App->SBC_Project->m_Project_Name);

			App->SBC_Dialogs->Dialog_Text();

			if (App->SBC_Dialogs->Canceled == 1)
			{
				return TRUE;
			}
	
			int len1 = strlen(App->SBC_Project->m_Project_Sub_Folder);
			int len2 = strlen(App->SBC_Project->m_Project_Name);
			App->SBC_Project->m_Project_Sub_Folder[len1 - (len2+5)] = 0;

			
			strcpy(App->SBC_Project->m_Project_Name,App->SBC_Dialogs->Chr_Text);

			strcpy(App->SBC_Project->m_Project_Sub_Folder, App->SBC_Project->m_Project_Sub_Folder);
			strcat(App->SBC_Project->m_Project_Sub_Folder, "\\");
			strcat(App->SBC_Project->m_Project_Sub_Folder, App->SBC_Project->m_Project_Name);
			strcat(App->SBC_Project->m_Project_Sub_Folder, "_Prj");

			SetDlgItemText(hDlg, IDC_STPROJECTNAME, (LPCTSTR)App->SBC_Project->m_Project_Name);
			SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->m_Project_Sub_Folder);

			App->SBC_Project->Directory_Changed_Flag = 1;

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTCHANGELEVEL)
		{
			strcpy(App->SBC_Dialogs->btext, "Change Level Name");
			strcpy(App->SBC_Dialogs->Chr_Text, App->SBC_Project->m_Level_Name);

			App->SBC_Dialogs->Dialog_Text();
			if (App->SBC_Dialogs->Canceled == 1)
			{
				return TRUE;
			}

			strcpy(App->SBC_Project->m_Level_Name, App->SBC_Dialogs->Chr_Text);
			SetDlgItemText(hDlg, IDC_STLEVELNAME, (LPCTSTR)App->SBC_Project->m_Level_Name);
			
			App->SBC_Project->Directory_Changed_Flag = 1;

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_CKQUICKLOAD)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CKQUICKLOAD);

			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				App->SBC_Project->Set_QuickLoad_Flag = 1;
			}
			else
			{
				App->SBC_Project->Set_QuickLoad_Flag = 0;
			}

			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			App->SBC_Project->Directory_Changed_Flag = 0;

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{

			App->SBC_Project->Save_Project();
			App->SBC_Project->Project_Loaded = 1;

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;

	}
	return FALSE;
}

// *************************************************************************
// *	  		Save_Project:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Save_All()
{
	Save_Project();
	return 1;
}

// *************************************************************************
// *	  		Save_Project:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Save_Project()
{

	if (_mkdir(m_Project_Sub_Folder) == 0)
	{
		_chdir(m_Project_Sub_Folder);
	}
	else
	{
		_chdir(m_Project_Sub_Folder);
	}

	bool test = Save_Project_Ini();
	if (test == 0)
	{
		return 0;
	}

	Save_Level_Folder();
	Save_Main_Asset_Folder();

	_chdir(m_Level_Folder_Path);

	if (App->SBC_Scene->Area_Added == 1)
	{
		Save_Aera_Folder();
	}

	if (App->SBC_Scene->Player_Added == 1)
	{
		Save_Players_Folder();

		//App->SBC_Scene->B_Player[0]->FileViewItem = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Players_Folder,"Player_1", 0, false);
		//App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Players_Folder);

	}

	Save_Cameras_Folder();
	Save_Objects_Folder();
	Save_Display_Folder();

	App->SBC_FileView->Change_Level_Name();
	App->SBC_FileView->Change_Project_Name();

	App->Set_Main_TitleBar(App->SBC_FileIO->Project_Path_File_Name);

	App->SBC_Object->Clear_Modified_Objects(); // Clear Altered FileView Items

	App->SBC_Project->Directory_Changed_Flag = 0;

	strcpy(App->SBC_FileIO->Project_Path_File_Name, m_Ini_Path_File_Name);
	App->Set_Main_TitleBar(App->SBC_FileIO->Project_Path_File_Name);
	App->SBC_FileIO->RecentFileHistory_Update();


	if (Set_QuickLoad_Flag == 1)
	{
		strcpy(App->SBC_Prefs->QL_User_File, App->SBC_FileIO->Project_Path_File_Name);
		App->SBC_Prefs->QL_Use_TestFile_Flag = 0;
		App->SBC_Prefs->Write_Preferences();
	}


	App->Say("Scene Saved");

	return 1;
}

// *************************************************************************
// *	  		Save_Project_Ini:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Save_Project_Ini()
{
	m_Ini_Path_File_Name[0] = 0;

	strcpy(m_Ini_Path_File_Name, m_Project_Sub_Folder);
	strcat(m_Ini_Path_File_Name, "\\");
	strcat(m_Ini_Path_File_Name, "Project.SBProj");

	int test = App->SBC_FileIO->SearchFolders(m_Project_Sub_Folder, "\\Project.SBProj");
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
	fprintf(WriteFile, "%s%s\n", "Project_Name=", App->SBC_Project->m_Project_Name);
	fprintf(WriteFile, "%s%s\n", "Level_Name=", App->SBC_Project->m_Level_Name);
	

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
// *	  	Save_Level_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Save_Level_Folder()
{
	strcpy(m_Level_Folder_Path, m_Project_Sub_Folder);
	strcat(m_Level_Folder_Path, "\\");
	strcat(m_Level_Folder_Path, m_Level_Name);

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
// *	  	Save_Cameras_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Save_Cameras_Folder()
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

	Save_Cameras_Data();

	_chdir(m_Level_Folder_Path); // Return to Level Folder

	return 1;
}

// *************************************************************************
// *	  		Save_Cameras_Data:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Save_Cameras_Data()
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
// *	  	Save_Objects_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Save_Objects_Folder()
{
	m_Objects_Folder_Path[0] = 0;

	strcpy(m_Objects_Folder_Path, m_Level_Folder_Path);
	strcat(m_Objects_Folder_Path, "\\");
	strcat(m_Objects_Folder_Path, "Objects");

	_mkdir(m_Objects_Folder_Path);
	_chdir(m_Objects_Folder_Path);

	Save_Objects_Data();

	_chdir(m_Level_Folder_Path); // Return to Level Folder
	return 1;
}

// *************************************************************************
// *	  		Save_Objects_Data:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Save_Objects_Data()
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
				fprintf(WriteFile, "%s%s\n", "Message_Text=", App->SBC_Scene->B_Object[Count]->Message_Text);

				x = App->SBC_Scene->B_Object[Count]->Message_PosX;
				y = App->SBC_Scene->B_Object[Count]->Message_PosY;
				fprintf(WriteFile, "%s%f,%f\n", "Message_Pos=",x,y);
				
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

				fprintf(WriteFile, "%s%s\n", "Move_Sound=", App->SBC_Scene->B_Object[Count]->Sound_File);
				fprintf(WriteFile, "%s%i\n", "Move_Play_Sound=", App->SBC_Scene->B_Object[Count]->Play_Sound);
				fprintf(WriteFile, "%s%f\n", "Move_Volume=", App->SBC_Scene->B_Object[Count]->SndVolume);
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
// *	  	Save_Display_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Save_Display_Folder()
{
	m_Display_Folder_Path[0] = 0;

	strcpy(m_Display_Folder_Path, m_Level_Folder_Path);
	strcat(m_Display_Folder_Path, "\\");
	strcat(m_Display_Folder_Path, "Display");

	_mkdir(m_Display_Folder_Path);
	_chdir(m_Display_Folder_Path);

	Save_Display_Data();

	_chdir(m_Level_Folder_Path); // Return to Level Folder
	return 1;
}

// *************************************************************************
// *	  		Save_Display_Data:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Save_Display_Data()
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
// *	  	Save_Main_Asset_Folder:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Save_Main_Asset_Folder()
{
	char LastFolder[MAX_PATH];

	if (Directory_Changed_Flag == 1)
	{
		strcpy(LastFolder, m_Main_Assets_Path);
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

	if (Directory_Changed_Flag == 1)
	{
		Copy_Assets(LastFolder, m_Main_Assets_Path);
	}

	Directory_Changed_Flag = 0;

	_chdir(m_Level_Folder_Path); // Return to Level Folder
	return 1;
}

// *************************************************************************
// *	  	Save_Aera_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Save_Aera_Folder()
{
	m_Aera_Folder_Path[0] = 0;

	strcpy(m_Aera_Folder_Path, m_Level_Folder_Path);
	strcat(m_Aera_Folder_Path, "\\");
	strcat(m_Aera_Folder_Path,"Areas");

	
	if (_mkdir(m_Aera_Folder_Path) == 0)
	{
		_chdir(m_Aera_Folder_Path);
	}
	else
	{
		_chdir(m_Aera_Folder_Path);
	}

	Save_Aeras_Data();

	_chdir(m_Level_Folder_Path); // Return to Level Folder
	return 1;
}

// *************************************************************************
// *	  		Save_Aeras_Data:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Save_Aeras_Data()
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
// *	  	Save_Players_Folder:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Save_Players_Folder()
{
	m_Players_Folder_Path[0] = 0;

	strcpy(m_Players_Folder_Path, m_Level_Folder_Path);
	strcat(m_Players_Folder_Path, "\\");
	strcat(m_Players_Folder_Path, "Players");


	_mkdir(m_Players_Folder_Path);
	
	_chdir(m_Players_Folder_Path);

	Save_Player_Data();

	_chdir(m_Level_Folder_Path); // Return to Level Folder
	return 1;
}

// *************************************************************************
// *	  	Save_Player_Data:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Save_Player_Data()
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
// *	  		Set_Paths:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void SB_Project::Set_Paths()
{
	App->Log_Messageg("void SB_Project::Set_Paths()");

	strcpy(m_Level_File_Name, App->SBC_FileIO->Project_File_Name);
	strcpy(m_Project_Sub_Folder, App->SBC_FileIO->Project_Path_File_Name);
	strcpy(m_Ini_Path_File_Name, App->SBC_FileIO->Project_Path_File_Name);

	strcpy(m_Level_Folder_Path, App->SBC_FileIO->Project_Path_File_Name);

	// Get path no file 
	int len1 = strlen(m_Level_File_Name);
	int len2 = strlen(m_Project_Sub_Folder);
	strcpy(m_Project_Sub_Folder, m_Project_Sub_Folder);
	m_Project_Sub_Folder[len2 - (len1+1)] = 0;

}

// *************************************************************************
// *	  		Load_Project:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Load_Project()
{
	App->Log_Messageg("bool SB_Project::Load_Project()");

	m_Ini_Path_File_Name[0] = 0;

	App->SBC_Scene->Clear_Level();
	App->SBC_Scene->Create_Resources_Group();

	Set_Paths();
	
	// ------------------------------------------------------------------- 
	Load_Options* Options = new Load_Options;

	Options->Has_Aera = 0;
	Options->Has_Player = 0;
	Options->Has_Camera = 0;
	Options->Has_Objects = 0;
	Options->Has_Counters = 0;

	int Int1 = 0;
	char chr_Tag1[1024];
	char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	App->Cl_Ini->SetPathName(m_Ini_Path_File_Name);
	
	App->Cl_Ini->GetString("Version_Data", "Version", chr_Tag1, 1024);

	App->Cl_Ini->GetString("Files", "Level_Name", m_Level_Name, MAX_PATH);
	App->Cl_Ini->GetString("Files", "Project_Name", m_Project_Name, MAX_PATH);

	Options->Has_Aera = App->Cl_Ini->GetInt("Options", "Aeras_Count", 0,10);
	Options->Has_Player = App->Cl_Ini->GetInt("Options", "Players_Count", 0, 10);
	Options->Has_Camera = App->Cl_Ini->GetInt("Options", "Cameras_Count", 0, 10);
	Options->Has_Objects = App->Cl_Ini->GetInt("Options", "Objects_Count", 0, 10);
	Options->Has_Counters = App->Cl_Ini->GetInt("Options", "Counters_Count", 0, 10);
	

	App->SBC_Scene->UniqueID_Object_Counter = App->Cl_Ini->GetInt("Options", "Objects_ID_Count", 0, 10);
	App->SBC_Scene->UniqueID_Counters_Count = App->Cl_Ini->GetInt("Options", "Counters_ID_Count", 0, 10);

	//-------------------------------------- Set Resource Path

		Load_Get_Resource_Path();

	// ------------------------------------- Aera
	if (Options->Has_Aera > 0)
	{
		bool test = Load_Project_Aera();
		App->SBC_Scene->Area_Added = 1;
		App->Cl_Environment->Load_Environment();
	}

	// ------------------------------------- Player
	if (Options->Has_Player > 0)
	{
		bool test = Load_Project_Player();
	}

	// ------------------------------------- Camera
	if (Options->Has_Camera > 0)
	{
		Load_Project_Camera();
		App->SBC_Scene->Camera_Added = 1;
		App->SBC_Camera->Set_Camera(0);
		App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Cameras_Folder);
	}

	// ------------------------------------- Objects
	if (Options->Has_Objects > 0)
	{
		Load_Project_Objects();
		App->SBC_Objects_Create->Add_Objects_From_File();

	}

	// ------------------------------------- Counters
	if (Options->Has_Counters > 0)
	{
		Load_Project_Counters();
		App->SBC_Display->Add_Counters_From_File();

	}

	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;
	
	App->SBC_FileView->Change_Level_Name();
	App->SBC_FileView->Change_Project_Name();
	App->SBC_FileView->Redraw_FileView();

	
	App->SBC_Scene->Scene_Loaded = 1;
	App->SBC_Project->Project_Loaded = 1;

	delete Options;

	App->Set_Main_TitleBar(App->SBC_FileIO->Project_Path_File_Name);
	App->SBC_FileIO->RecentFileHistory_Update();

	App->SBC_FileView->SelectItem(App->SBC_FileView->FV_LevelFolder);

	App->SBC_Scene->Scene_Modified = 0;
	return 1;
}

// *************************************************************************
// *	  	Load_Get_Resource_Path:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Load_Get_Resource_Path()
{
	App->Log_Messageg("bool SB_Project::Load_Get_Resource_Path()");

	m_Main_Assets_Path[0] = 0;

	strcpy(m_Main_Assets_Path, m_Project_Sub_Folder);
	strcat(m_Main_Assets_Path, "\\");

	strcat(m_Main_Assets_Path, m_Level_Name);
	strcat(m_Main_Assets_Path, "\\");

	strcat(m_Main_Assets_Path, "Assets");
	strcat(m_Main_Assets_Path, "\\");

	App->SBC_Scene->Add_Resource_Location_Project(m_Main_Assets_Path);

	return 1;
}

// *************************************************************************
// *	  	Load_Project_Objects:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Load_Project_Objects()
{
	char Object_Ini_Path[MAX_PATH];
	char chr_Tag1[MAX_PATH];
	int Object_Count = 0;

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	strcpy(Object_Ini_Path, m_Project_Sub_Folder);
	strcat(Object_Ini_Path, "\\");

	strcat(Object_Ini_Path, m_Level_Name);
	strcat(Object_Ini_Path, "\\");

	strcat(Object_Ini_Path, "Objects");
	strcat(Object_Ini_Path, "\\");

	//---------------------------------------------------

	strcat(Object_Ini_Path, "Objects.efd");

	App->Cl_Ini->SetPathName(Object_Ini_Path);

	Object_Count = App->Cl_Ini->GetInt("Counters", "Objects_Count", 0);

	int Count = 0;

	while (Count < Object_Count)
	{
		char n_buff[255];
		char buff[255];
		strcpy(buff, "Object_");
		_itoa(Count, n_buff, 10);
		strcat(buff, n_buff);

		App->SBC_Scene->B_Object[Count] = new Base_Object();
		Base_Object* Object = App->SBC_Scene->B_Object[Count];

		App->Cl_Ini->GetString(buff, "Mesh_Name", Object->Mesh_Name, MAX_PATH);
		App->Cl_Ini->GetString(buff, "Mesh_File", Object->Mesh_FileName, MAX_PATH);
		App->Cl_Ini->GetString(buff, "Mesh_Resource_Path", Object->Mesh_Resource_Path, MAX_PATH);
		App->Cl_Ini->GetString(buff, "Material_File", Object->Material_File, MAX_PATH);

		// Types
		Object->This_Object_ID = App->Cl_Ini->GetInt(buff, "Object_ID", 0);
		Object->Type = App->Cl_Ini->GetInt(buff, "Object_Type", 0);
		Object->Shape = App->Cl_Ini->GetInt(buff, "Object_Shape", 0);
		Object->Usage = App->Cl_Ini->GetInt(buff, "Object_Usage", 0);

		// Pos
		App->Cl_Ini->GetString(buff, "Mesh_Pos", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Object[Count]->Mesh_Pos = Ogre::Vector3(x, y, z);

		// Scale
		App->Cl_Ini->GetString(buff, "Mesh_Scale", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Object[Count]->Mesh_Scale = Ogre::Vector3(x, y, z);

		// Rotation
		App->Cl_Ini->GetString(buff, "Mesh_Rot", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Object[Count]->Mesh_Rot = Ogre::Vector3(x, y, z);

		// Mesh_Quat
		App->Cl_Ini->GetString(buff, "Mesh_Quat", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);

		App->SBC_Scene->B_Object[Count]->Mesh_Quat.w = w;
		App->SBC_Scene->B_Object[Count]->Mesh_Quat.x = x;
		App->SBC_Scene->B_Object[Count]->Mesh_Quat.y = y;
		App->SBC_Scene->B_Object[Count]->Mesh_Quat.z = z;

		// Physics_Quat
		App->Cl_Ini->GetString(buff, "Physics_Quat", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);

		App->SBC_Scene->B_Object[Count]->Physics_Quat.w = w;
		App->SBC_Scene->B_Object[Count]->Physics_Quat.x = x;
		App->SBC_Scene->B_Object[Count]->Physics_Quat.y = y;
		App->SBC_Scene->B_Object[Count]->Physics_Quat.z = z;

		//---------------------------------------------------------------------------------- Message Entity
		if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Message)
		{
			App->Cl_Ini->GetString(buff, "Message_Text", Object->Message_Text, MAX_PATH);

			App->Cl_Ini->GetString(buff, "Message_Pos", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f,%f", &x, &y);

			App->SBC_Scene->B_Object[Count]->Message_PosX = x;
			App->SBC_Scene->B_Object[Count]->Message_PosY = y;
			
		}

		//---------------------------------------------------------------------------------- Sound Entity
		if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Sound)
		{
			App->Cl_Ini->GetString(buff, "Sound_File", Object->Sound_File, MAX_PATH);
			
			App->Cl_Ini->GetString(buff, "Sound_Volume", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->SBC_Scene->B_Object[Count]->SndVolume = x;
		}

		//---------------------------------------------------------------------------------- Colectable Entity
		if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Colectable)
		{
			App->SBC_Scene->B_Object[Count]->S_Collectable[0] = new Collectable_type;
			App->SBC_Object->Set_Collectables_Sound_Defaults(Count);

			App->Cl_Ini->GetString(buff, "Col_Sound_File", chr_Tag1, MAX_PATH);
			strcpy(Object->S_Collectable[0]->Sound_File, chr_Tag1);
			
			App->Cl_Ini->GetString(buff, "Col_Sound_Volume", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->SBC_Scene->B_Object[Count]->S_Collectable[0]->SndVolume = x;

			App->SBC_Scene->B_Object[Count]->S_Collectable[0]->Play = App->Cl_Ini->GetInt(buff, "Col_Play", 0);

			App->Cl_Ini->GetString(buff, "Col_Counter_Name", chr_Tag1, MAX_PATH);
			strcpy(Object->S_Collectable[0]->Counter_Name, chr_Tag1);

			App->SBC_Scene->B_Object[Count]->S_Collectable[0]->Counter_ID = App->Cl_Ini->GetInt(buff, "Col_Counter_ID", 0);

		}

		//---------------------------------------------------------------------------------- Usage_Move
		if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Move)
		{

			App->SBC_Scene->B_Object[Count]->S_MoveType[0] = new Move_Type;
			App->SBC_Object->Set_Move_Defaults(Count); // Check

			// --------------------------- Distance
			App->Cl_Ini->GetString(buff, "Move_Distance", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f",&x);
			App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Move_Distance = x;

			App->SBC_Scene->B_Object[Count]->S_MoveType[0]->IsNegative = App->Cl_Ini->GetInt(buff, "Move_IsNegative", 0);

			// --------------------------- Speed
			App->Cl_Ini->GetString(buff, "Move_Speed", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Speed = x;

			// --------------------------- Name
			App->Cl_Ini->GetString(buff, "Move_ObjectName", App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Object_Name, MAX_PATH);

			App->SBC_Scene->B_Object[Count]->S_MoveType[0]->Object_To_Move_Index = App->Cl_Ini->GetInt(buff, "Move_ObjectID", 0);
			App->SBC_Scene->B_Object[Count]->S_MoveType[0]->WhatDirection = App->Cl_Ini->GetInt(buff, "Move_WhatDirection", 0);
		
			App->Cl_Ini->GetString(buff, "Move_Sound", App->SBC_Scene->B_Object[Count]->Sound_File, MAX_PATH);
			App->SBC_Scene->B_Object[Count]->Play_Sound = App->Cl_Ini->GetInt(buff, "Move_Play_Sound", 0);


			// --------------------------- Move_Volume
			App->Cl_Ini->GetString(buff, "Move_Volume", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->SBC_Scene->B_Object[Count]->SndVolume = x;

		}

		if (App->SBC_Scene->B_Object[Count]->Usage == Enums::Usage_Teleport)
		{
			
			App->SBC_Scene->B_Object[Count]->S_Teleport[0] = new Teleport_type;
			App->Cl_Ini->GetString(buff, "Tele_Goto", chr_Tag1, MAX_PATH);
			strcpy(App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Name, chr_Tag1);

			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Location_ID = App->Cl_Ini->GetInt(buff, "Tele_ID", 0);

			// Sound
			App->Cl_Ini->GetString(buff, "Tele_Sound", App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Sound_File, MAX_PATH);

			App->Cl_Ini->GetString(buff, "Tele_Volume", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->SndVolume = x;

			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Play = App->Cl_Ini->GetInt(buff, "Tele_Play", 0);

			// Mesh_Pos
			App->Cl_Ini->GetString(buff, "Tele_Mesh_Position", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);

			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Player_Position.x = x;
			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Player_Position.y = y;
			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Player_Position.z = z;

			//Player_Pos
			App->Cl_Ini->GetString(buff, "Tele_Physics_Position", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);

			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Position.setX(x);
			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Position.setY(y);
			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Position.setZ(z);

			//Player_Rotation
			App->Cl_Ini->GetString(buff, "Tele_Physics_Rotation", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);

			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Rotation.setW(w);
			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Rotation.setX(x);
			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Rotation.setY(y);
			App->SBC_Scene->B_Object[Count]->S_Teleport[0]->Physics_Rotation.setZ(z);
		}

		Count++;
	}

	App->SBC_Scene->Object_Count = Count;

	return 1;
}

// *************************************************************************
// *	  	Load_Project_Counters:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Load_Project_Counters()
{

	char Object_Ini_Path[MAX_PATH];
	char chr_Tag1[MAX_PATH];
	int Counters_Count = 0;

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	strcpy(Object_Ini_Path, m_Project_Sub_Folder);
	strcat(Object_Ini_Path, "\\");

	strcat(Object_Ini_Path, m_Level_Name);
	strcat(Object_Ini_Path, "\\");

	strcat(Object_Ini_Path, "Display");
	strcat(Object_Ini_Path, "\\");

	//---------------------------------------------------

	strcat(Object_Ini_Path, "Counters.edf");

	App->Cl_Ini->SetPathName(Object_Ini_Path);

	Counters_Count = App->Cl_Ini->GetInt("Counters", "Counters_Count", 0);

	int Count = 0;

	while (Count < Counters_Count)
	{
		App->SBC_Scene->B_Counter[Count] = new Base_Counter();
		App->SBC_Display->Set_Counter_Defaults(Count);


		char n_buff[255];
		char buff[255];
		strcpy(buff, "Counter_");
		_itoa(Count, n_buff, 10);
		strcat(buff, n_buff);

		App->Cl_Ini->GetString(buff, "Counter_Name", chr_Tag1, MAX_PATH);
		strcpy(App->SBC_Scene->B_Counter[Count]->Panel_Name, chr_Tag1);


		App->SBC_Scene->B_Counter[Count]->Unique_ID = App->Cl_Ini->GetInt(buff, "Counter_ID", 0);

		App->Cl_Ini->GetString(buff, "Counter_Pos", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f", &x, &y);
		App->SBC_Scene->B_Counter[Count]->PosX = x;
		App->SBC_Scene->B_Counter[Count]->PosY = y;
		
		App->Cl_Ini->GetString(buff, "Counter_Text", chr_Tag1, MAX_PATH);
		strcpy(App->SBC_Scene->B_Counter[Count]->Text, chr_Tag1);


		App->SBC_Scene->B_Counter[Count]->Set_ImGui_Panel_Name();

		Count++;
	}

	App->SBC_Scene->Counters_Count = Count;

	return 1;
}


// *************************************************************************
// *	  		Load_Project_Aera:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Load_Project_Aera()
{
	App->Log_Messageg("bool SB_Project::Load_Project_Aera()");

	char Area_Ini_Path[MAX_PATH];
	char chr_Tag1[MAX_PATH];
	char Area_Name[1024];
	char Mesh_FileName[MAX_PATH];
	char Resource_Location[MAX_PATH];
	int Area_Count = 0;
	int Int_Tag = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	strcpy(Area_Ini_Path, m_Project_Sub_Folder);
	strcat(Area_Ini_Path, "\\");

	strcat(Area_Ini_Path, m_Level_Name);
	strcat(Area_Ini_Path, "\\");

	strcat(Area_Ini_Path, "Areas");
	strcat(Area_Ini_Path, "\\");

	strcat(Area_Ini_Path, "Areas.aer");

	App->Cl_Ini->SetPathName(Area_Ini_Path);

	Area_Count = App->Cl_Ini->GetInt("Counters","Areas_Count", 0);
	
	int Count = 0;

	while (Count < Area_Count)
	{

		App->Cl_Ini->GetString("Area_0", "Area_Name", Area_Name, MAX_PATH);
		App->Cl_Ini->GetString("Area_0", "Area_File", Mesh_FileName, MAX_PATH);
		App->Cl_Ini->GetString("Area_0", "Area_Resource_Path", Resource_Location, MAX_PATH);

		App->SBC_Aera->Add_Aera_To_Project(Count, Mesh_FileName, m_Main_Assets_Path);
		App->SBC_Scene->B_Area[0]->S_Environment[0] = new Environment_type;
		App->SBC_Aera->Set_Environment_Defaults(Count);

		App->Cl_Ini->GetString("Area_0", "Material_File", App->SBC_Scene->B_Area[Count]->Material_File, MAX_PATH);

		App->Cl_Ini->GetString("Position", "Mesh_Pos", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);

		App->SBC_Scene->B_Area[Count]->Area_Node->setPosition(x, y, z);
		App->SBC_Scene->B_Area[Count]->Phys_Body->getWorldTransform().setOrigin(btVector3(x, y, z));
		App->SBC_Scene->B_Area[Count]->Physics_Pos = Ogre::Vector3(x, y, z);

		strcpy(App->SBC_Scene->B_Area[Count]->Area_Name, Area_Name);
		App->SBC_Scene->B_Area[Count]->FileViewItem = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Areas_Folder, Area_Name, Count, false);

		// ------------------------------------ Environment

		//--------------- Sound
		App->Cl_Ini->GetString("Environment", "Sound_File", chr_Tag1, MAX_PATH);
		strcpy(App->SBC_Scene->B_Area[0]->S_Environment[0]->Sound_File, chr_Tag1);

		App->Cl_Ini->GetString("Environment", "Snd_Volume", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->SndVolume = x;

		Int_Tag = App->Cl_Ini->GetInt("Environment", "Sound_Play", 0, 10);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Play = Int_Tag;

		Int_Tag = App->Cl_Ini->GetInt("Environment", "Sound_Loop", 0, 10);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Loop = Int_Tag;

		//--------------- Light
		App->Cl_Ini->GetString("Environment", "Ambient_Colour", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->AmbientColour = Ogre::Vector3(x, y, z);

		App->Cl_Ini->GetString("Environment", "Diffuse_Colour", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->DiffuseColour = Ogre::Vector3(x, y, z);

		App->Cl_Ini->GetString("Environment", "Specular_Colour", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->SpecularColour = Ogre::Vector3(x, y, z);

		App->Cl_Ini->GetString("Environment", "Light_Position", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Light_Position = Ogre::Vector3(x, y, z);

		//--------------- Sky
		Int_Tag = App->Cl_Ini->GetInt("Environment", "Sky_Enable", 0, 10);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Enabled = Int_Tag;

		Int_Tag = App->Cl_Ini->GetInt("Environment", "Sky_Type", 0, 10);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->type = Int_Tag;

		App->Cl_Ini->GetString("Environment", "Sky_Material", chr_Tag1, MAX_PATH);
		strcpy(App->SBC_Scene->B_Area[0]->S_Environment[0]->Material, chr_Tag1);

		App->Cl_Ini->GetString("Environment", "Sky_Curvature", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Curvature = x;
	
		App->Cl_Ini->GetString("Environment", "Sky_Tiling", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Tiling = x;
		
		App->Cl_Ini->GetString("Environment", "Sky_Distance", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Distance = x;
		
		//--------------- Fog
		Int_Tag = App->Cl_Ini->GetInt("Environment", "Fog_On", 0, 10);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_On = Int_Tag;

		Int_Tag = App->Cl_Ini->GetInt("Environment", "Fog_Mode", 0, 10);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_Mode = Int_Tag;
		
		App->Cl_Ini->GetString("Environment", "Fog_Colour", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_Colour = Ogre::Vector3(x, y, z);

		App->Cl_Ini->GetString("Environment", "Fog_Start", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_Start = x;

		App->Cl_Ini->GetString("Environment", "Fog_End", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_End = x;

		App->Cl_Ini->GetString("Environment", "Fog_Density", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->SBC_Scene->B_Area[0]->S_Environment[0]->Fog_Density = x;


		Count++;
		App->SBC_Scene->Area_Count++;
	}

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Areas_Folder);

	return 1;
}

// *************************************************************************
// *	  	Load_Project_Player:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Project::Load_Project_Player()
{
	int Players_Count = 0;
	int Locations_Count = 0;
	char Player_Name[MAX_PATH];
	char Player_Ini_Path[MAX_PATH];
	char chr_Tag1[MAX_PATH];

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	strcpy(Player_Ini_Path, m_Project_Sub_Folder);
	strcat(Player_Ini_Path, "\\");

	strcat(Player_Ini_Path, m_Level_Name);
	strcat(Player_Ini_Path, "\\");

	strcat(Player_Ini_Path, "Players");
	strcat(Player_Ini_Path, "\\");

	strcat(Player_Ini_Path, "Players.ply");

	App->Cl_Ini->SetPathName(Player_Ini_Path);

	Players_Count = App->Cl_Ini->GetInt("Counters", "Player_Count", 0);

	int Count = 0;
	char Cbuff[255];
	char buff[255];

	while (Count < Players_Count)
	{
		strcpy(buff, "Player_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);
	
		App->SBC_Player->Create_Player_Object();

		App->Cl_Ini->GetString(buff, "Player_Name", Player_Name, MAX_PATH);
		strcpy(App->SBC_Scene->B_Player[Count]->Player_Name, Player_Name);


		App->Cl_Ini->GetString(buff, "Start_Position", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Player[Count]->StartPos = Ogre::Vector3(x, y, z);

		App->Cl_Ini->GetString(buff, "Start_Rotation", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);

		App->SBC_Scene->B_Player[Count]->Physics_Rotation.setW(w);
		App->SBC_Scene->B_Player[Count]->Physics_Rotation.setX(x);
		App->SBC_Scene->B_Player[Count]->Physics_Rotation.setY(y);
		App->SBC_Scene->B_Player[Count]->Physics_Rotation.setZ(z);

		App->Cl_Ini->GetString(buff, "Turn_Rate", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f",&x);
		App->SBC_Scene->B_Player[Count]->TurnRate = x;

		App->SBC_Scene->B_Player[Count]->FileViewItem = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Players_Folder, Player_Name, Count, false);
	
		Count++;

	}

	// ------------------------------------------ Locations
	int Int_Tag = 0;
	Locations_Count = App->Cl_Ini->GetInt("Locations", "Locations_Count", 0);

	Count = 0;
	while (Count < Locations_Count)
	{
		if (App->SBC_Scene->B_Locations[Count])
		{
			delete App->SBC_Scene->B_Locations[Count];
			App->SBC_Scene->B_Locations[Count] = NULL;
		}

		char n_buff[255];
		char buff[255];
		strcpy(buff, "Location_");
		_itoa(Count, n_buff, 10);
		strcat(buff, n_buff);

		App->SBC_Scene->B_Locations[Count] = new Base_Locations();
		App->SBC_Scene->B_Locations[Count]->Deleted = 0;


		Int_Tag = App->Cl_Ini->GetInt(buff, "Locatoin_ID", 0, 10);
		App->SBC_Scene->B_Locations[Count]->Location_ID = Int_Tag;

		App->Cl_Ini->GetString(buff, "Name", chr_Tag1, MAX_PATH);


		strcpy(App->SBC_Scene->B_Locations[Count]->Name, chr_Tag1);

		// Mesh_Pos
		App->Cl_Ini->GetString(buff, "Mesh_Position", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Locations[Count]->Current_Position.x = x;
		App->SBC_Scene->B_Locations[Count]->Current_Position.y = y;
		App->SBC_Scene->B_Locations[Count]->Current_Position.z = z;

		App->Cl_Ini->GetString(buff, "Physics_Position", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->B_Locations[Count]->Physics_Position.setX(x);
		App->SBC_Scene->B_Locations[Count]->Physics_Position.setY(y);
		App->SBC_Scene->B_Locations[Count]->Physics_Position.setZ(z);

		App->Cl_Ini->GetString(buff, "Physics_Rotation", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);
		App->SBC_Scene->B_Locations[Count]->Physics_Rotation.setW(w);
		App->SBC_Scene->B_Locations[Count]->Physics_Rotation.setX(x);
		App->SBC_Scene->B_Locations[Count]->Physics_Rotation.setY(y);
		App->SBC_Scene->B_Locations[Count]->Physics_Rotation.setZ(z);

		Count++;

	}

	App->SBC_Scene->Player_Location_Count = Count;

	App->SBC_Physics->Reset_Physics();
	App->SBC_Physics->Enable_Physics(1);

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Players_Folder);
	return 1;
}

// *************************************************************************
// *	  		Load_Project_Camera:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Project::Load_Project_Camera()
{
	char Cameras_Ini_Path[MAX_PATH];
	char chr_Tag1[MAX_PATH];
	char Camera_Name[MAX_PATH];
	int Camera_Count = 0;

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	strcpy(Cameras_Ini_Path, m_Project_Sub_Folder);
	strcat(Cameras_Ini_Path, "\\");

	strcat(Cameras_Ini_Path, m_Level_Name);
	strcat(Cameras_Ini_Path, "\\");

	strcat(Cameras_Ini_Path, "Cameras");
	strcat(Cameras_Ini_Path, "\\");

	strcat(Cameras_Ini_Path, "Cameras.epf");

	App->Cl_Ini->SetPathName(Cameras_Ini_Path);

	Camera_Count = App->Cl_Ini->GetInt("Counters", "Cameras_Count", 0);

	int Count = 0;

	while (Count < Camera_Count)
	{
		char n_buff[255];
		char buff[255];
		strcpy(buff, "Camera_");
		_itoa(Count, n_buff, 10);
		strcat(buff, n_buff);

		App->SBC_Scene->B_Camera[Count] = new Base_Camera();

		App->Cl_Ini->GetString(buff, "Camera_Name", Camera_Name, MAX_PATH);
		strcpy(App->SBC_Scene->B_Camera[Count]->Camera_Name, Camera_Name);

		//---------------------------------- Camera Pos
		App->Cl_Ini->GetString(buff, "Camera_Pos", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);

		App->SBC_Scene->B_Camera[Count]->CamPos.x = x;
		App->SBC_Scene->B_Camera[Count]->CamPos.y = y;
		App->SBC_Scene->B_Camera[Count]->CamPos.z = z;

		//---------------------------------- Camera Look At
		App->Cl_Ini->GetString(buff, "LookAt", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);

		App->SBC_Scene->B_Camera[Count]->LookAt.x = x;
		App->SBC_Scene->B_Camera[Count]->LookAt.y = y;
		App->SBC_Scene->B_Camera[Count]->LookAt.z = z;

		//---------------------------------- Camera Quaternion
		App->Cl_Ini->GetString(buff, "Camera_Quat", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);

		App->SBC_Scene->B_Camera[Count]->Cam_Quat.w = w;
		App->SBC_Scene->B_Camera[Count]->Cam_Quat.x = x;
		App->SBC_Scene->B_Camera[Count]->Cam_Quat.y = y;
		App->SBC_Scene->B_Camera[Count]->Cam_Quat.z = z;


		App->SBC_Scene->B_Camera[Count]->FileViewItem = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Cameras_Folder,
			App->SBC_Scene->B_Camera[Count]->Camera_Name, Count , false);

		App->SBC_Scene->Camera_Count++;

		Count++;
	}

//	App->SBC_FileView->Redraw_FileView();

	return 1;
}

// *************************************************************************
// *	  		Copy_Assets:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
bool SB_Project::Copy_Assets(char* SourceFolder, char* DestinationFolder)
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

