/*
Copyright (c) 2021 Stage Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Project.h"


SB_Project::SB_Project()
{
	
	strcpy(m_Project_Sub_Folder, App->EquityDirecory_FullPath);
	strcat(m_Project_Sub_Folder, "\\");
	strcat(m_Project_Sub_Folder, "Projects");
	strcat(m_Project_Sub_Folder, "\\");
	strcat(m_Project_Sub_Folder, "No Project?");
	strcat(m_Project_Sub_Folder, "_Prj");

	strcpy(m_Project_Name, "Project_X");
	strcpy(m_Level_Name, "Level_X");

	m_Level_Folder_Path[0] = 0;
	m_Players_Folder_Path[0] = 0;

	m_Ini_Path_File_Name[0] = 0;
	
	m_Level_File_Name[0] = 0;

	WriteFile =			NULL;

	Project_Loaded = 0;

	test = "Char Test";

}


SB_Project::~SB_Project()
{
}

// *************************************************************************
// *	  			Start_Save_Project_Dialog Terry Flanigan			   *
// *************************************************************************
bool SB_Project::Start_Save_Project_Dialog()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_PROJECT, App->Fdlg, (DLGPROC)Save_Project_Dialog_Proc);
	return 1;
}

// *************************************************************************
// *				Save_Project_Dialog_Proc Terry Flanigan	  			   *
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

		SendDlgItemMessage(hDlg, IDC_BTPJBROWSE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTDESKTOP, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STBANNER, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SetDlgItemText(hDlg, IDC_STPROJECTNAME, (LPCTSTR)App->SBC_Project->m_Project_Name);
		SetDlgItemText(hDlg, IDC_STLEVELNAME, (LPCTSTR)App->SBC_Project->m_Level_Name);
		SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->m_Project_Sub_Folder);

		SetDlgItemText(hDlg, IDC_STBANNER, (LPCTSTR)"Save Project As");
		
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

		if (some_item->idFrom == IDC_BTDESKTOP && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}
	case WM_COMMAND:

		if (LOWORD(wParam) == IDC_BTPJBROWSE)
		{
			strcpy(App->Com_CDialogs->BrowserMessage, "Select Folder To Place New Project a sub folder will be created");
			int Test = App->Com_CDialogs->StartBrowser("", App->Fdlg);

			if (Test == 0){return true;}

			strcpy(App->SBC_Project->m_Project_Sub_Folder, App->Com_CDialogs->szSelectedDir);
			strcat(App->SBC_Project->m_Project_Sub_Folder, App->SBC_Project->m_Project_Name);
			strcat(App->SBC_Project->m_Project_Sub_Folder, "_Prj");

	
			SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->m_Project_Sub_Folder);

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

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTCHANGELEVEL)
		{
			strcpy(App->SBC_Dialogs->btext, "Change Level Name");
			strcpy(App->SBC_Dialogs->Chr_Text, App->SBC_Project->m_Level_Name);

			App->SBC_Dialogs->Dialog_Text();

			strcpy(App->SBC_Project->m_Level_Name, App->SBC_Dialogs->Chr_Text);


			SetDlgItemText(hDlg, IDC_STLEVELNAME, (LPCTSTR)App->SBC_Project->m_Level_Name);
			

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTDESKTOP)
		{
			
			strcpy(App->SBC_Project->m_Project_Sub_Folder, App->SBC_FileIO->DeskTop_Folder);
			strcat(App->SBC_Project->m_Project_Sub_Folder, "\\");
			strcat(App->SBC_Project->m_Project_Sub_Folder, App->SBC_Project->m_Project_Name);
			strcat(App->SBC_Project->m_Project_Sub_Folder, "_Prj");

			SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->m_Project_Sub_Folder);

			return TRUE;
		}
		
		
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			App->SBC_Project->Save_Project();
			
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;

	}
	return FALSE;
}

// *************************************************************************
// *	  				Save_Project Terry Flanigan						   *
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

	Save_Project_Ini();

	Save_Level_Folder();

	_chdir(m_Level_Folder_Path);

	if (App->SBC_Scene->Area_Added == 1)
	{
		Save_Aera_Folder();
	}

	if (App->SBC_Scene->Player_Added == 1)
	{
		Save_Players_Folder();

		App->SBC_Player->FileViewItem = App->SBC_FileView->Add_PlayerFile("Player_1", 0);
		App->SBC_FileView->Set_FolderActive(App->SBC_FileView->GD_Player);

	}

	App->SBC_FileView->Change_Level_Name();
	App->SBC_FileView->Change_Project_Name();

	App->Set_Main_TitleBar(App->SBC_FileIO->Project_Path_File_Name);

	App->Say("Scene Created");
	return 1;
}

// *************************************************************************
// *	  					Save_Project_Ini Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Save_Project_Ini()
{
	m_Ini_Path_File_Name[0] = 0;

	strcpy(m_Ini_Path_File_Name, m_Project_Sub_Folder);
	strcat(m_Ini_Path_File_Name, "\\");
	strcat(m_Ini_Path_File_Name, "Project.SBProj");

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
	fprintf(WriteFile, "%s%s\n", "Folder_Path=", App->SBC_Project->m_Project_Sub_Folder);

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", "[Options]");
	fprintf(WriteFile, "%s%i\n", "Aeras_Count=", App->SBC_Scene->Area_Count);
	fprintf(WriteFile, "%s%i\n", "Players_Count=", App->SBC_Scene->Player_Count);
	fprintf(WriteFile, "%s%i\n", "Cameras_Count=", App->SBC_Scene->Camera_Count);
	fprintf(WriteFile, "%s%i\n", "Objects_Count=", App->SBC_Scene->Object_Count);

	fclose(WriteFile);

	return 1;
}

// *************************************************************************
// *	  				Save_Level_Folder Terry Flanigan				   *
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
// *	  				Save_Aera_Folder Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Save_Aera_Folder()
{
	m_Aera_Folder_Path[0] = 0;

	strcpy(m_Aera_Folder_Path, m_Level_Folder_Path);
	strcat(m_Aera_Folder_Path, "\\");
	strcat(m_Aera_Folder_Path,"Aeras");

	
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
// *	  				Save_Aeras_Data Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Save_Aeras_Data()
{
	Ogre::Vector3 Pos;
	char File[1024];

	strcpy(File, m_Aera_Folder_Path);
	strcat(File, "\\");
	strcat(File, "Aeras.aer");

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
	fprintf(WriteFile, "%s%i\n", "Aeras_Count=", App->SBC_Scene->Area_Count);

	fprintf(WriteFile, "%s\n", " ");

	char Cbuff[255];
	char buff[255];

	float x = 0;
	float y = 0;
	float z = 0;

	int Count = 0;
	while (Count < App->SBC_Scene->Area_Count)
	{
		strcpy(buff, "[Aera_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);
		strcat(buff, "]");

		fprintf(WriteFile, "%s\n", buff); // Header also Player name until changed by user

		fprintf(WriteFile, "%s%s\n", "Aera_Name=", App->SBC_Scene->SBC_Base_Area[Count]->Area_Name); // Change

		fprintf(WriteFile, "%s%s\n", "Aera_File=", App->SBC_Scene->SBC_Base_Area[Count]->Area_FileName);
		fprintf(WriteFile, "%s%s\n", "Aera_Path_File=", App->SBC_Scene->SBC_Base_Area[Count]->Area_Path_And_FileName);
		fprintf(WriteFile, "%s%s\n", "Aera_Resource_Path=", App->SBC_Scene->SBC_Base_Area[Count]->Area_Resource_Path);

		fprintf(WriteFile, "%s\n", "[Position]");
		x = App->SBC_Scene->SBC_Base_Area[Count]->Area_Node->getPosition().x;
		y = App->SBC_Scene->SBC_Base_Area[Count]->Area_Node->getPosition().y;
		z = App->SBC_Scene->SBC_Base_Area[Count]->Area_Node->getPosition().z;

		fprintf(WriteFile, "%s%f,%f,%f\n", "Mesh_Pos=", x, y, z);

		Count++;
	}

	fclose(WriteFile);

	return 1;
}

// *************************************************************************
// *	  				Save_Players_Folder Terry Flanigan				   *
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
// *	  				Save_Player_Data Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Save_Player_Data()
{
	Ogre::Vector3 Pos;
	char File[1024];

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

		fprintf(WriteFile, "%s%s\n", "Player_Name=", App->SBC_Scene->SBC_Base_Player[Count]->Player_Name);

		Pos.x = App->SBC_Scene->SBC_Base_Player[Count]->StartPos.x;
		Pos.y = App->SBC_Scene->SBC_Base_Player[Count]->StartPos.y;
		Pos.z = App->SBC_Scene->SBC_Base_Player[Count]->StartPos.z;

		fprintf(WriteFile, "%s%f,%f,%f\n", "Start_Position=", Pos.x, Pos.y, Pos.z);
		fprintf(WriteFile, "%s%s\n", "Shape=", "Capsule");
		fprintf(WriteFile, "%s%f\n", "Mass=", App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Mass);
		fprintf(WriteFile, "%s%f\n", "Radius=", App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Radius);
		fprintf(WriteFile, "%s%f\n", "Height=", App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Height);
		fprintf(WriteFile, "%s%f\n", "Ground_Speed=", App->SBC_Scene->SBC_Base_Player[Count]->Ground_speed);
		fprintf(WriteFile, "%s%f\n", "Cam_Height=", App->SBC_Scene->SBC_Base_Player[Count]->PlayerHeight);

		Count++;
	}

	fclose(WriteFile);

	return 1;
}

// *************************************************************************
// *	  					Set_Paths Terry Flanigan					   *
// *************************************************************************
void SB_Project::Set_Paths()
{
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
// *	  					Load_Project Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Load_Project()
{
	m_Ini_Path_File_Name[0] = 0;

	App->SBC_Scene->Clear_Level();

	Set_Paths();
	
	// ------------------------------------------------------------------- 
	Load_Options* Options = new Load_Options;

	Options->Has_Aera = 0;
	Options->Has_Player = 0;
	Options->Has_Camera = 0;

	int Int1 = 0;
	char chr_Tag1[1024];
	char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	App->Cl_Ini->SetPathName(m_Ini_Path_File_Name);
	
	App->Cl_Ini->GetString("Version_Data", "Version", chr_Tag1, 1024);

	App->Cl_Ini->GetString("Files", "Level_Name", m_Level_Name, MAX_PATH);
	App->Cl_Ini->GetString("Files", "Project_Name", m_Project_Name, MAX_PATH);

	App->SBC_FileView->Change_Level_Name();
	App->SBC_FileView->Change_Project_Name();

	Options->Has_Aera = App->Cl_Ini->GetInt("Options", "Aeras_Count", 0,10);
	Options->Has_Player = App->Cl_Ini->GetInt("Options", "Players_Count", 0, 10);
	Options->Has_Camera = App->Cl_Ini->GetInt("Options", "Cameras_Count", 0, 10);
	Options->Has_Objects = App->Cl_Ini->GetInt("Options", "Objects_Count", 0, 10);

	// ------------------------------------- Aera
	if (Options->Has_Aera > 0)
	{
		Load_Project_Aera();
	}

	// ------------------------------------- Player
	if (Options->Has_Player > 0)
	{
		Load_Project_Player();
	}

	// ------------------------------------- Camera
	if (Options->Has_Camera > 0)
	{
		App->SBC_Scene->Camera_Added = 1;
	}

	// ------------------------------------- Objects
	if (Options->Has_Objects > 0)
	{

	}

	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;
	
	App->SBC_FileView->Redraw_FileView();

	App->SBC_Scene->Scene_Loaded = 1;

	App->SBC_Scene->Area_Added = 1;

	/*App->Cl_Ini->GetString("Levels", "Folder", chr_Tag1, 1024);
	strcpy(Scene_JustPath, Level_Folder_Path);
	strcat(Scene_JustPath, chr_Tag1);

	App->Cl_Ini->GetString("Levels", "File", chr_Tag2, 1024);

	strcpy(App->CL_Vm_Model->Model_FolderPath, Scene_JustPath);
	strcpy(App->CL_Vm_Model->FileName, chr_Tag2);*/

	//Read_Player();
	Load_Project_Camera();
	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->GD_CameraFolder);
	//App->SBC_Aera->Add_Area();

	////App->SBC_Player->Load_Player();

	//App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;


	////          File View Stuff
	//App->SBC_FileView->Change_Level_Name();

	//HTREEITEM Temp = App->SBC_FileView->Add_Area("Area_1", 0);
	//App->SBC_FileView->Redraw_FileView();

	////  Start Level
	//App->SBC_Physics->Enable_Physics(1);
	//App->SBC_Camera->Set_Camera();

	//App->SBC_Scene->Scene_Loaded = 1;

	delete Options;

	App->Set_Main_TitleBar(App->SBC_FileIO->Project_Path_File_Name);
	App->SBC_FileIO->RecentFileHistory_Update();
	return 1;
}

// *************************************************************************
// *	  					Load_Project_Aera Terry Flanigan			   *
// *************************************************************************
bool SB_Project::Load_Project_Aera()
{
	char Area_Ini_Path[MAX_PATH];
	char chr_Tag1[MAX_PATH];
	char Area_Name[1024];
	char Mesh_FileName[MAX_PATH];
	char Resource_Location[MAX_PATH];
	int Area_Count = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	strcpy(Area_Ini_Path, m_Project_Sub_Folder);
	strcat(Area_Ini_Path, "\\");

	strcat(Area_Ini_Path, m_Level_Name);
	strcat(Area_Ini_Path, "\\");

	strcat(Area_Ini_Path, "Aeras");
	strcat(Area_Ini_Path, "\\");

	strcat(Area_Ini_Path, "Aeras.aer");

	App->Cl_Ini->SetPathName(Area_Ini_Path);

	Area_Count = App->Cl_Ini->GetInt("Counters","Aeras_Count", 0);
	
	int Count = 0;

	while (Count < Area_Count)
	{

		App->Cl_Ini->GetString("Aera_0", "Aera_Name", Area_Name, MAX_PATH);
		App->Cl_Ini->GetString("Aera_0", "Aera_File", Mesh_FileName, MAX_PATH);
		App->Cl_Ini->GetString("Aera_0", "Aera_Resource_Path", Resource_Location, MAX_PATH);

		App->SBC_Aera->Add_Aera_To_Project(Count, Mesh_FileName, Resource_Location);

		App->Cl_Ini->GetString("Position", "Mesh_Pos", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);

		App->SBC_Scene->SBC_Base_Area[Count]->Area_Node->setPosition(x, y, z);
		App->SBC_Scene->SBC_Base_Area[Count]->Phys_Body->getWorldTransform().setOrigin(btVector3(x, y, z));
		App->SBC_Scene->SBC_Base_Area[Count]->Physics_Pos = Ogre::Vector3(x, y, z);

		strcpy(App->SBC_Scene->SBC_Base_Area[Count]->Area_Name, Area_Name);
		App->SBC_Scene->SBC_Base_Area[Count]->FileViewItem = App->SBC_FileView->Add_Area(Area_Name, Count);

		Count++;
	}

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->GD_Rooms);

	return 1;
}

// *************************************************************************
// *	  				Load_Project_Player Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Load_Project_Player()
{
	int Players_Count = 0;
	char Player_Name[MAX_PATH];
	char Player_Ini_Path[MAX_PATH];

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

	while (Count < Players_Count)
	{

		App->Cl_Ini->GetString("Player_0", "Player_Name", Player_Name, MAX_PATH);


		App->SBC_Player->Create_Player_Object();
		strcpy(App->SBC_Scene->SBC_Base_Player[Count]->Player_Name, Player_Name);

		App->SBC_Player->FileViewItem = App->SBC_FileView->Add_PlayerFile(Player_Name, Count);

		Count++;

	}

	App->Cl_Bullet->Reset_Physics();
	App->SBC_Physics->Enable_Physics(1);

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->GD_Player);
	return 1;
}

// *************************************************************************
// *	  			N_Load_Project_Camera Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Load_Project_Camera()
{
	char chr_Tag1[1024];
	char chr_Tag2[1024];

	float x = 0;
	float y = 0;
	float z = 0;

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	// ------------------------------------------------------------------- 
	char Path[1024];
	strcpy(Path, m_Project_Sub_Folder);
	strcat(Path, "Camera1.cam");

	// ------------------------------------------------------------------- 

	//App->Cl_Ini->SetPathName(Path);

	//App->Cl_Ini->GetString("Version_Data", "Version", chr_Tag1, 1024);

	//App->Cl_Ini->GetString("Camera", "Camera_Name", chr_Tag1, 1024);
	//strcpy(App->SBC_Camera->Camera_Name, chr_Tag1);

	//// Position
	//App->Cl_Ini->GetString("Camera", "Start_Position", chr_Tag1, 1024);
	//sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	//App->SBC_Camera->CamPos_X = x;
	//App->SBC_Camera->CamPos_Y = y;
	//App->SBC_Camera->CamPos_Z = z;

	//// Position
	//App->Cl_Ini->GetString("Camera", "Look_At", chr_Tag1, 1024);
	//sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	//App->SBC_Camera->LookAt_X = x;
	//App->SBC_Camera->LookAt_Y = y;
	//App->SBC_Camera->LookAt_Z = z;

	App->SBC_Camera->FileViewItem = App->SBC_FileView->Add_Camera(App->SBC_Camera->Camera_Name, 0);
	App->SBC_FileView->Redraw_FileView();
	return 1;
}

