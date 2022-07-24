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
	strcpy(Project_Name,"Project1");
	strcpy(Project_Path,App->EquityDirecory_FullPath);
	strcat(Project_Path, "\\");
	strcat(Project_Path, "Projects\\");

	strcpy(Project_FullPath, App->EquityDirecory_FullPath);
	strcat(Project_FullPath, "\\");
	strcat(Project_FullPath, "Projects");
	strcat(Project_FullPath, "\\");
	strcat(Project_FullPath, Project_Name);
	strcat(Project_FullPath, "_Prj");

	strcpy(m_Level_Name,"Level_1");
	m_Level_Folder_Path[0] = 0;
	m_Players_Folder_Path[0] = 0;

	Project_Ini_FilePath[0] = 0;
	Level_Folder_Path[0] = 0;
	Level_Folder_Path_World[0] = 0;

	strcpy(Level_File_Name, "No Level");

	Scene_Path_FileName[0] = 0;
	Scene_JustPath[0] = 0;

	Write_Ini =			NULL;
	Write_Player_Ini =	NULL;
	WriteFile =			NULL;
	Write_Object_Ini =	NULL;

	Project_Loaded = 0;

}


SB_Project::~SB_Project()
{
}

// *************************************************************************
// *	  				Start_Create_Project Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Start_Create_Project()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_PROJECT, App->Fdlg, (DLGPROC)Create_Project_Proc);
	return 1;
}

// *************************************************************************
// *				Create_Project_Proc Terry Flanigan	  				   *
// *************************************************************************
LRESULT CALLBACK SB_Project::Create_Project_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{
		SendDlgItemMessage(hDlg, IDC_STPJFOLDERPATH, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPROJECTNAME, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_STPATH, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STPN, WM_SETFONT, (WPARAM)App->Font_Arial20, MAKELPARAM(TRUE, 0));

		SendDlgItemMessage(hDlg, IDC_BTCHANGE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTPJBROWSE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		

		SetDlgItemText(hDlg, IDC_STPROJECTNAME, (LPCTSTR)App->SBC_Project->Project_Name);
		SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->Project_FullPath);

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

		if (GetDlgItem(hDlg, IDC_STPN) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STPATH) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 0, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
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
		
		if (some_item->idFrom == IDC_BTPJBROWSE && some_item->code == NM_CUSTOMDRAW)
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

			strcpy(App->SBC_Project->Project_FullPath, App->Com_CDialogs->szSelectedDir);
			strcat(App->SBC_Project->Project_FullPath, App->SBC_Project->Project_Name);
			strcat(App->SBC_Project->Project_FullPath, "_Prj");

			strcpy(App->SBC_Project->Project_Path, App->Com_CDialogs->szSelectedDir);

			SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->Project_FullPath);

			return TRUE;
		}

		if (LOWORD(wParam) == IDC_BTCHANGE)
		{
			strcpy(App->SBC_Dialogs->btext, "Change Project Name");
			strcpy(App->SBC_Dialogs->Chr_Text, App->SBC_Project->Project_Name);

			App->SBC_Dialogs->Dialog_Text();

			strcpy(App->SBC_Project->Project_Name,App->SBC_Dialogs->Chr_Text);

			strcpy(App->SBC_Project->Project_FullPath, App->SBC_Project->Project_Path);
			strcat(App->SBC_Project->Project_FullPath, App->SBC_Project->Project_Name);
			strcat(App->SBC_Project->Project_FullPath, "_Prj");

			SetDlgItemText(hDlg, IDC_STPROJECTNAME, (LPCTSTR)App->SBC_Project->Project_Name);
			SetDlgItemText(hDlg, IDC_STPJFOLDERPATH, (LPCTSTR)App->SBC_Project->Project_FullPath);

			return TRUE;
		}
		
		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			//App->SBC_Project->Create_Project();

			App->SBC_Project->Save_Project();

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
		break;

	}
	return FALSE;
}

// *************************************************************************
// *	  				Create_Project Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Create_Project()
{


	if (_mkdir(App->SBC_Project->Project_FullPath) == 0)
	{
		_chdir(App->SBC_Project->Project_FullPath);
	}
	else
	{
		
	}

	Set_Paths();

	Write_Project_Ini();

	Create_Level_Folder();

	Write_Level_File();

	// Player
	App->SBC_Player->Create_Player_Object();
	strcpy(App->SBC_Scene->SBC_Base_Player[0]->Player_Name,"Player_1");
	Write_Player();

	// Camera
	Write_Camera();

	// Objects
	Write_Objects();

	Add_World(); // Create First room Not Loaded

	strcpy(App->CL_Vm_Model->Model_FolderPath, Level_Folder_Path_World);
	strcpy(App->CL_Vm_Model->FileName, "World.mesh");

	App->SBC_Aera->Add_Area();

	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;


	//          File View Stuff
	App->SBC_FileView->Change_Level_Name();

	App->SBC_Camera->FileViewItem = App->SBC_FileView->Add_Camera(App->SBC_Camera->Camera_Name, 0);
	App->SBC_Player->FileViewItem = App->SBC_FileView->Add_PlayerFile(App->SBC_Scene->SBC_Base_Player[0]->Player_Name, 0);
	HTREEITEM Temp = App->SBC_FileView->Add_Area("Area_1", 0);
	App->SBC_FileView->Redraw_FileView();

	//  Start Level
	App->SBC_Physics->Enable_Physics(1);
	App->SBC_Camera->Set_Camera();

	App->SBC_Scene->Scene_Loaded = 1;

	App->Say("Scene Created");
	return 1;
}

// *************************************************************************
// *	  					Set_Paths Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Set_Paths()
{
	Project_Ini_FilePath[0] = 0;

	strcpy(Project_Ini_FilePath, App->SBC_Project->Project_FullPath);
	strcat(Project_Ini_FilePath, "\\");
	strcat(Project_Ini_FilePath, "Project.eif");

	strcpy(Level_Folder_Path, App->SBC_Project->Project_FullPath);
	strcat(Level_Folder_Path, "\\");
	strcat(Level_Folder_Path, "Level_1");
	return 1;
}

// *************************************************************************
// *	  				Write_Project_Ini Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Write_Project_Ini()
{
	
	Write_Ini = NULL;

	Write_Ini = fopen(Project_Ini_FilePath, "wt");

	if (!Write_Ini)
	{
		App->Say("Cant Create File");
		return 0;
	}

	fprintf(Write_Ini, "%s\n", "[Files]");
	fprintf(Write_Ini, "%s%s\n", "Project_Name=", App->SBC_Project->Project_Name);
	fprintf(Write_Ini, "%s%s\n", "Folder_Path=", App->SBC_Project->Project_FullPath);

	fprintf(Write_Ini, "%s\n", "[Player]");
	fprintf(Write_Ini, "%s%s\n", "Player_File=","Player1.ply");
	
	fprintf(Write_Ini, "%s\n", "[Camera]");
	fprintf(Write_Ini, "%s%s\n", "Camera_File=", "Cam1.cam");

	fprintf(Write_Ini, "%s\n", "[Objects]");
	fprintf(Write_Ini, "%s%s\n", "Camera_File=", "Objects.obf");

	fclose(Write_Ini);
	
	return 1;
}

// *************************************************************************
// *	  				Create_Level_Folder Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Create_Level_Folder()
{
	Level_Folder_Path_World[0] = 0;

	strcpy(Level_Folder_Path_World, Level_Folder_Path);
	strcat(Level_Folder_Path_World, "\\");
	strcat(Level_Folder_Path_World, "World1");

	// First Level Folder
	if (_mkdir(Level_Folder_Path) == 0)
	{
		_chdir(Level_Folder_Path);

	}
	else
	{
		//App->Say("Directory already exsits");
		
	}

	// First world Folder
	if (_mkdir(Level_Folder_Path_World) == 0)
	{
		_chdir(Level_Folder_Path);

	}
	else
	{
		//App->Say("Directory already exsits");

	}

	return 1;
}

// *************************************************************************
// *	  					Write_Objects Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Write_Objects()
{
	char File[1024];

	strcpy(File, Level_Folder_Path);
	strcat(File, "\\");
	strcat(File, "Objects.obf");

	Write_Object_Ini = NULL;

	Write_Object_Ini = fopen(File, "wt");

	if (!Write_Object_Ini)
	{
		App->Say("Cant Create File");
		App->Say(File);
		return 0;
	}

	fprintf(Write_Object_Ini, "%s\n", "[Version_Data]");
	fprintf(Write_Object_Ini, "%s%s\n", "Version=", "V1.2");

	fprintf(Write_Object_Ini, "%s\n", " ");

	fprintf(Write_Object_Ini, "%s\n", "[Objects]");
	fprintf(Write_Object_Ini, "%s%i\n", "Objects_Count=", App->SBC_Scene->Object_Count);



	fclose(Write_Object_Ini);

	return 1;
}

// *************************************************************************
// *	  					Write_Player Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Write_Player()
{
	Ogre::Vector3 Pos;
	char File[1024];

	strcpy(File, Level_Folder_Path);
	strcat(File, "\\");
	strcat(File, "Player1.ply");

	Write_Player_Ini = NULL;

	Write_Player_Ini = fopen(File, "wt");

	if (!Write_Player_Ini)
	{
		App->Say("Cant Create File");
		App->Say(File);
		return 0;
	}

	fprintf(Write_Player_Ini, "%s\n", "[Version_Data]");
	fprintf(Write_Player_Ini, "%s%s\n", "Version=", "V1.2");

	fprintf(Write_Player_Ini, "%s\n", " ");

	fprintf(Write_Player_Ini, "%s\n", "[Counters]");
	fprintf(Write_Player_Ini, "%s%i\n", "Player_Count=",App->SBC_Scene->Player_Count);

	fprintf(Write_Player_Ini, "%s\n", " ");

	char Cbuff[255];
	char buff[255];
	int Count = 0;
	while (Count < App->SBC_Scene->Player_Count)
	{
		strcpy(buff, "[Player_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);
		strcat(buff, "]");

		fprintf(Write_Player_Ini, "%s\n", buff); // Header also Player name until changed by user

		fprintf(Write_Player_Ini, "%s%s\n", "Player_Name=", App->SBC_Scene->SBC_Base_Player[Count]->Player_Name);

		Pos.x = App->SBC_Scene->SBC_Base_Player[Count]->StartPos.x;
		Pos.y = App->SBC_Scene->SBC_Base_Player[Count]->StartPos.y;
		Pos.z = App->SBC_Scene->SBC_Base_Player[Count]->StartPos.z;

		fprintf(Write_Player_Ini, "%s%f,%f,%f\n", "Start_Position=", Pos.x, Pos.y, Pos.z);
		fprintf(Write_Player_Ini, "%s%s\n", "Shape=", "Capsule");
		fprintf(Write_Player_Ini, "%s%f\n", "Mass=", App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Mass);
		fprintf(Write_Player_Ini, "%s%f\n", "Radius=", App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Radius);
		fprintf(Write_Player_Ini, "%s%f\n", "Height=", App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Height);
		fprintf(Write_Player_Ini, "%s%f\n", "Ground_Speed=", App->SBC_Scene->SBC_Base_Player[Count]->Ground_speed);
		fprintf(Write_Player_Ini, "%s%f\n", "Cam_Height=", App->SBC_Scene->SBC_Base_Player[Count]->PlayerHeight);

		Count++;
	}
	
	fclose(Write_Player_Ini);

	return 1;
}

// *************************************************************************
// *	  					Write_Camera Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Write_Camera()
{
	char File[1024];

	strcpy(File, Level_Folder_Path);
	strcat(File, "\\");
	strcat(File, "Camera1.cam");

	WriteFile = NULL;

	WriteFile = fopen(File, "wt");

	if (!WriteFile)
	{
		App->Say("Cant Create File");
		App->Say(File);
		return 0;
	}

	fprintf(WriteFile, "%s\n", "[Version_Data]");
	fprintf(WriteFile, "%s%s\n", "Version=", "V1.2");

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", "[Camera]");
	fprintf(WriteFile, "%s%s\n", "Camera_Name=", App->SBC_Camera->Camera_Name);

	fprintf(WriteFile, "%s%f,%f,%f\n", "Start_Position=", App->SBC_Camera->CamPos_X, App->SBC_Camera->CamPos_Y, App->SBC_Camera->CamPos_Z);
	fprintf(WriteFile, "%s%f,%f,%f\n", "Look_At=", App->SBC_Camera->LookAt_X, App->SBC_Camera->LookAt_Y, App->SBC_Camera->LookAt_Z);

	

	fclose(WriteFile);

	return 1;
}
// *************************************************************************
// *	  				Write_Level_File Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Write_Level_File()
{
	char File[1024];
	File[0] = 0;

	WriteFile = NULL;

	strcpy(File, Level_Folder_Path);
	strcat(File, "\\");
	strcat(File, "Level.SBLevel");


	WriteFile = fopen(File, "wt");

	if (!WriteFile)
	{
		App->Say("Cant Create File");
		return 0;
	}

	fprintf(WriteFile, "%s\n", "[Version_Data]");
	fprintf(WriteFile, "%s%s\n", "Version=", "V1.2");

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", "[Levels]");
	fprintf(WriteFile, "%s%s\n", "Folder=", "World1");
	fprintf(WriteFile, "%s%s\n", "File=", "World.mesh");

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", "[Player]");
	fprintf(WriteFile, "%s%s\n", "Player_File=", "Player1.ply");

	fprintf(WriteFile, "%s\n", " ");

	fprintf(WriteFile, "%s\n", "[Camere]");
	fprintf(WriteFile, "%s%s\n", "Camera_File=", "Cam1.cam");

	fclose(WriteFile);
	return 1;
}

// *************************************************************************
// *	  					Add_World Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Add_World()
{
	char Source[1024];
	char Destination[1024];

	strcpy(Source, App->EquityDirecory_FullPath);
	strcat(Source, "\\Data\\World_Ogre\\World.mesh");

	strcpy(Destination, Level_Folder_Path_World);
	strcat(Destination, "\\");
	strcat(Destination, "World.mesh");

	CopyFile(Source, Destination, true);

	// --------------------------------------------------------------------
	strcpy(Source, App->EquityDirecory_FullPath);
	strcat(Source, "\\Data\\World_Ogre\\World.material");

	strcpy(Destination, Level_Folder_Path_World);
	strcat(Destination, "\\");
	strcat(Destination, "World.material");

	CopyFile(Source, Destination, true);

	// --------------------------------------------------------------------
	strcpy(Source, App->EquityDirecory_FullPath);
	strcat(Source, "\\Data\\World_Ogre\\Wall.bmp");

	strcpy(Destination, Level_Folder_Path_World);
	strcat(Destination, "\\");
	strcat(Destination, "Wall.bmp");

	CopyFile(Source, Destination, true);

	// --------------------------------------------------------------------
	strcpy(Source, App->EquityDirecory_FullPath);
	strcat(Source, "\\Data\\World_Ogre\\stfloor1.bmp");

	strcpy(Destination, Level_Folder_Path_World);
	strcat(Destination, "\\");
	strcat(Destination, "stfloor1.bmp");

	CopyFile(Source, Destination, true);

	// --------------------------------------------------------------------
	strcpy(Source, App->EquityDirecory_FullPath);
	strcat(Source, "\\Data\\World_Ogre\\concrete.bmp");

	strcpy(Destination, Level_Folder_Path_World);
	strcat(Destination, "\\");
	strcat(Destination, "concrete.bmp");

	CopyFile(Source, Destination, true);

	return 1;
}

// *************************************************************************
// *					Load_Scene_Auto   Terry Bernie  				   *
// *************************************************************************
bool SB_Project::Load_Scene_Auto()
{
	int ObjectsCount = 0;
	int TagFloat = 0;
	int TagInt = 0;

	char StartFile[1024];
	strcpy(StartFile, App->EquityDirecory_FullPath);
	strcat(StartFile, "\\");
	strcat(StartFile, "Data\\StartUp.gcf");

	App->Cl_Ini->SetPathName(StartFile);

	App->Cl_Ini->GetString("Startup", "Scene_FileName", App->CL_Vm_FileIO->Model_FileName, 1024);
	App->Cl_Ini->GetString("Startup", "Scene_Path_FileName", App->CL_Vm_FileIO->Model_Path_FileName,1024);

	Load_Scene();

	return 1;
}

// *************************************************************************
// *	  					Load_Scene Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Load_Scene()
{
	Debug1
		return 1;

	App->SBC_Scene->Clear_Level();

	strcpy(Level_File_Name, App->CL_Vm_FileIO->Model_FileName);
	strcpy(Level_Path_File_Name, App->CL_Vm_FileIO->Model_Path_FileName);

	// Get path no file 
	int len1 = strlen(Level_File_Name);
	int len2 = strlen(Level_Path_File_Name);
	strcpy(Level_Folder_Path, Level_Path_File_Name);
	Level_Folder_Path[len2 - len1] = 0;

	// ------------------------------------------------------------------- 

	char chr_Tag1[1024];
	char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	App->Cl_Ini->SetPathName(Level_Path_File_Name);

	App->Cl_Ini->GetString("Version_Data", "Version", chr_Tag1, 1024);
	

	App->Cl_Ini->GetString("Levels", "Folder", chr_Tag1, 1024);
	strcpy(Scene_JustPath, Level_Folder_Path);
	strcat(Scene_JustPath, chr_Tag1);

	App->Cl_Ini->GetString("Levels", "File", chr_Tag2, 1024);

	strcpy(App->CL_Vm_Model->Model_FolderPath, Scene_JustPath);
	strcpy(App->CL_Vm_Model->FileName, chr_Tag2);

	Read_Player();
	Read_Camera();

	App->SBC_Aera->Add_Area();

	//App->SBC_Player->Load_Player();

	App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;


	//          File View Stuff
	App->SBC_FileView->Change_Level_Name();

	HTREEITEM Temp = App->SBC_FileView->Add_Area("Area_1", 0);
	App->SBC_FileView->Redraw_FileView();

	//  Start Level
	App->SBC_Physics->Enable_Physics(1);
	App->SBC_Camera->Set_Camera();

	App->SBC_Scene->Scene_Loaded = 1;

	App->Set_Main_TitleBar(App->CL_Vm_FileIO->Model_Path_FileName);

	return 1;
}

// *************************************************************************
// *	  				Read_Player Terry Flanigan						   *
// *************************************************************************
bool SB_Project::Read_Player()
{
	char chr_Tag1[1024];
	char chr_Tag2[1024];

	int Int_Tag = 0;

	float x = 0;
	float y = 0;
	float z = 0;

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	// ------------------------------------------------------------------- 
	char Path[1024];
	strcpy(Path, Level_Folder_Path);
	strcat(Path, "Player1.ply");

	// ------------------------------------------------------------------- 

	App->Cl_Ini->SetPathName(Path);

	App->Cl_Ini->GetString("Version_Data", "Version", chr_Tag1, 1024);
	
	Int_Tag = App->Cl_Ini->GetInt("Counters", "Player_Count", 0, 10);

	char Cbuff[255];
	char buff[255];
	int Count = 0;

	while (Count < Int_Tag)
	{
		App->SBC_Player->Create_Player_Object(); // Increments Player Counter 

		strcpy(buff, "Player_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);

		App->Cl_Ini->GetString(buff, "Player_Name", chr_Tag1, 1024);

		strcpy(App->SBC_Scene->SBC_Base_Player[Count]->Player_Name, chr_Tag1);

		//// Position
		App->Cl_Ini->GetString(buff, "Start_Position", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->SBC_Scene->SBC_Base_Player[Count]->StartPos.x = x;
		App->SBC_Scene->SBC_Base_Player[Count]->StartPos.y = y;
		App->SBC_Scene->SBC_Base_Player[Count]->StartPos.z = z;


		App->Cl_Ini->GetString(buff, "Shape", chr_Tag1, 1024); // Capsule

		x = App->Cl_Ini->Get_Float(buff, "Mass");
		y = App->Cl_Ini->Get_Float(buff, "Radius");
		z = App->Cl_Ini->Get_Float(buff, "Height");

		App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Mass = x;
		App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Radius = y;
		App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Height = z;

		x = App->Cl_Ini->Get_Float(buff, "Ground_Speed");
		App->SBC_Scene->SBC_Base_Player[Count]->Ground_speed = x;

		x = App->Cl_Ini->Get_Float(buff, "Cam_Height");
		App->SBC_Scene->SBC_Base_Player[Count]->PlayerHeight = x;

		App->SBC_Player->FileViewItem = App->SBC_FileView->Add_PlayerFile(App->SBC_Scene->SBC_Base_Player[Count]->Player_Name, Count);

		Count++;

	}

	App->SBC_FileView->Redraw_FileView();

	App->Cl_Bullet->Reset_Physics();
	return 1;
}

// *************************************************************************
// *	  				Read_Camera Terry Flanigan						   *
// *************************************************************************
bool SB_Project::Read_Camera()
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
	strcpy(Path, Level_Folder_Path);
	strcat(Path, "Camera1.cam");

	// ------------------------------------------------------------------- 

	App->Cl_Ini->SetPathName(Path);

	App->Cl_Ini->GetString("Version_Data", "Version", chr_Tag1, 1024);

	App->Cl_Ini->GetString("Camera", "Camera_Name", chr_Tag1, 1024);
	strcpy(App->SBC_Camera->Camera_Name, chr_Tag1);

	// Position
	App->Cl_Ini->GetString("Camera", "Start_Position", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->SBC_Camera->CamPos_X = x;
	App->SBC_Camera->CamPos_Y = y;
	App->SBC_Camera->CamPos_Z = z;

	// Position
	App->Cl_Ini->GetString("Camera", "Look_At", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->SBC_Camera->LookAt_X = x;
	App->SBC_Camera->LookAt_Y = y;
	App->SBC_Camera->LookAt_Z = z;

	App->SBC_Camera->FileViewItem = App->SBC_FileView->Add_Camera(App->SBC_Camera->Camera_Name, 0);
	App->SBC_FileView->Redraw_FileView();
	return 1;
}

// *************************************************************************
// *	  				Save_Project Terry Flanigan						   *
// *************************************************************************
bool SB_Project::Save_Project()
{


	if (_mkdir(App->SBC_Project->Project_FullPath) == 0)
	{
		_chdir(App->SBC_Project->Project_FullPath);
	}
	else
	{
		_chdir(App->SBC_Project->Project_FullPath);
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
	}


	//Write_Level_File();

	//// Player
	//App->SBC_Player->Create_Player_Object();
	//strcpy(App->SBC_Scene->SBC_Base_Player[0]->Player_Name, "Player_1");
	//Write_Player();

	//// Camera
	//Write_Camera();

	//// Objects
	//Write_Objects();

	//Add_World(); // Create First room Not Loaded

	//strcpy(App->CL_Vm_Model->Model_FolderPath, Level_Folder_Path_World);
	//strcpy(App->CL_Vm_Model->FileName, "World.mesh");

	//App->SBC_Aera->Add_Area();

	//App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;


	////          File View Stuff
	//App->SBC_FileView->Change_Level_Name();

	//App->SBC_Camera->FileViewItem = App->SBC_FileView->Add_Camera(App->SBC_Camera->Camera_Name, 0);
	//App->SBC_Player->FileViewItem = App->SBC_FileView->Add_PlayerFile(App->SBC_Scene->SBC_Base_Player[0]->Player_Name, 0);
	//HTREEITEM Temp = App->SBC_FileView->Add_Area("Area_1", 0);
	//App->SBC_FileView->Redraw_FileView();

	////  Start Level
	//App->SBC_Physics->Enable_Physics(1);
	//App->SBC_Camera->Set_Camera();

	//App->SBC_Scene->Scene_Loaded = 1;

	App->Say("Scene Created");
	return 1;
}

//------------------------------------------------------------------------------------------ NEW 24/07/22
// *************************************************************************
// *	  					Save_Project_Ini Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Save_Project_Ini()
{
	Project_Ini_FilePath[0] = 0;

	strcpy(Project_Ini_FilePath, App->SBC_Project->Project_FullPath);
	strcat(Project_Ini_FilePath, "\\");
	strcat(Project_Ini_FilePath, "Project.SBProj");

	Write_Ini = nullptr;

	Write_Ini = fopen(Project_Ini_FilePath, "wt");

	if (!Write_Ini)
	{
		App->Say("Cant Create File");
		return 0;
	}

	fprintf(Write_Ini, "%s\n", "[Version_Data]");
	fprintf(Write_Ini, "%s%s\n", "Version=", "V1.2");

	fprintf(Write_Ini, "%s\n", " ");

	fprintf(Write_Ini, "%s\n", "[Files]");
	fprintf(Write_Ini, "%s%s\n", "Project_Name=", App->SBC_Project->Project_Name);
	fprintf(Write_Ini, "%s%s\n", "Folder_Path=", App->SBC_Project->Project_FullPath);

	fprintf(Write_Ini, "%s\n", "[Players]");
	fprintf(Write_Ini, "%s%i\n", "Players_Count=", App->SBC_Scene->Player_Count);
	fprintf(Write_Ini, "%s%s\n", "Player_File=", "Player1.ply");

	fprintf(Write_Ini, "%s\n", "[Aeras]");
	fprintf(Write_Ini, "%s%i\n", "Aeras_Count=", App->SBC_Scene->Area_Count);
	fprintf(Write_Ini, "%s%s\n", "Aeras_File=", "Aeras.aer");

	fprintf(Write_Ini, "%s\n", "[Camera]");
	fprintf(Write_Ini, "%s%s\n", "Camera_File=", "Cam1.cam");

	fprintf(Write_Ini, "%s\n", "[Objects]");
	fprintf(Write_Ini, "%s%i\n", "Objects_Count=", App->SBC_Scene->Object_Count);
	fprintf(Write_Ini, "%s%s\n", "Objects_File=", "Objects.obf");

	fclose(Write_Ini);

	return 1;
}

// *************************************************************************
// *	  				Save_Level_Folder Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Save_Level_Folder()
{
	strcpy(m_Level_Folder_Path, App->SBC_Project->Project_FullPath);
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

	Write_Player_Ini = nullptr;

	Write_Player_Ini = fopen(File, "wt");

	if (!Write_Player_Ini)
	{
		App->Say("Cant Create File");
		App->Say(File);
		return 0;
	}

	fprintf(Write_Player_Ini, "%s\n", "[Version_Data]");
	fprintf(Write_Player_Ini, "%s%s\n", "Version=", "V1.2");

	fprintf(Write_Player_Ini, "%s\n", " ");

	fprintf(Write_Player_Ini, "%s\n", "[Counters]");
	fprintf(Write_Player_Ini, "%s%i\n", "Aeras_Count=", App->SBC_Scene->Area_Count);

	fprintf(Write_Player_Ini, "%s\n", " ");

	char Cbuff[255];
	char buff[255];
	int Count = 0;
	while (Count < App->SBC_Scene->Area_Count)
	{
		strcpy(buff, "[Aera_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);
		strcat(buff, "]");

		fprintf(Write_Player_Ini, "%s\n", buff); // Header also Player name until changed by user

		fprintf(Write_Player_Ini, "%s%s\n", "Aera_Name=", App->SBC_Scene->SBC_Base_Area[Count]->Area_FileName); // Change

		fprintf(Write_Player_Ini, "%s%s\n", "Aera_File=", App->SBC_Scene->SBC_Base_Area[Count]->Area_FileName);
		fprintf(Write_Player_Ini, "%s%s\n", "Aera_Path_File=", App->SBC_Scene->SBC_Base_Area[Count]->Area_Path_And_FileName);
		fprintf(Write_Player_Ini, "%s%s\n", "Aera_Resource_Path=", App->SBC_Scene->SBC_Base_Area[Count]->Area_Resource_Path);

		Count++;
	}

	fclose(Write_Player_Ini);

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

	Write_Player_Ini = nullptr;

	Write_Player_Ini = fopen(File, "wt");

	if (!Write_Player_Ini)
	{
		App->Say("Cant Create File");
		App->Say(File);
		return 0;
	}

	fprintf(Write_Player_Ini, "%s\n", "[Version_Data]");
	fprintf(Write_Player_Ini, "%s%s\n", "Version=", "V1.2");

	fprintf(Write_Player_Ini, "%s\n", " ");

	fprintf(Write_Player_Ini, "%s\n", "[Counters]");
	fprintf(Write_Player_Ini, "%s%i\n", "Player_Count=", App->SBC_Scene->Player_Count);

	fprintf(Write_Player_Ini, "%s\n", " ");

	char Cbuff[255];
	char buff[255];
	int Count = 0;
	while (Count < App->SBC_Scene->Player_Count)
	{
		strcpy(buff, "[Player_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);
		strcat(buff, "]");

		fprintf(Write_Player_Ini, "%s\n", buff); // Header also Player name until changed by user

		fprintf(Write_Player_Ini, "%s%s\n", "Player_Name=", App->SBC_Scene->SBC_Base_Player[Count]->Player_Name);

		Pos.x = App->SBC_Scene->SBC_Base_Player[Count]->StartPos.x;
		Pos.y = App->SBC_Scene->SBC_Base_Player[Count]->StartPos.y;
		Pos.z = App->SBC_Scene->SBC_Base_Player[Count]->StartPos.z;

		fprintf(Write_Player_Ini, "%s%f,%f,%f\n", "Start_Position=", Pos.x, Pos.y, Pos.z);
		fprintf(Write_Player_Ini, "%s%s\n", "Shape=", "Capsule");
		fprintf(Write_Player_Ini, "%s%f\n", "Mass=", App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Mass);
		fprintf(Write_Player_Ini, "%s%f\n", "Radius=", App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Radius);
		fprintf(Write_Player_Ini, "%s%f\n", "Height=", App->SBC_Scene->SBC_Base_Player[Count]->Capsule_Height);
		fprintf(Write_Player_Ini, "%s%f\n", "Ground_Speed=", App->SBC_Scene->SBC_Base_Player[Count]->Ground_speed);
		fprintf(Write_Player_Ini, "%s%f\n", "Cam_Height=", App->SBC_Scene->SBC_Base_Player[Count]->PlayerHeight);

		Count++;
	}

	fclose(Write_Player_Ini);

	return 1;
}

// *************************************************************************
// *	  					Load_Project Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Load_Project()
{
	m_Ini_Path_File_Name[0] = 0;

	App->SBC_Scene->Clear_Level();

	strcpy(Level_File_Name, App->CL_Vm_FileIO->Model_FileName);
	strcpy(Level_Path_File_Name, App->CL_Vm_FileIO->Model_Path_FileName);
	strcpy(m_Ini_Path_File_Name, App->CL_Vm_FileIO->Model_Path_FileName);

	// Get path no file 
	int len1 = strlen(Level_File_Name);
	int len2 = strlen(Level_Path_File_Name);
	strcpy(Level_Folder_Path, Level_Path_File_Name);
	Level_Folder_Path[len2 - len1] = 0;

	// ------------------------------------------------------------------- 

	int Int1 = 0;
	char chr_Tag1[1024];
	char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	App->Cl_Ini->SetPathName(m_Ini_Path_File_Name);
	
	App->Cl_Ini->GetString("Version_Data", "Version", chr_Tag1, 1024);

	Int1 = App->Cl_Ini->GetInt("Aeras", "Aeras_Count", 0,10);
	
	if (Int1 == 1)
	{
		Load_Project_Aera();
	}

	/*App->Cl_Ini->GetString("Levels", "Folder", chr_Tag1, 1024);
	strcpy(Scene_JustPath, Level_Folder_Path);
	strcat(Scene_JustPath, chr_Tag1);

	App->Cl_Ini->GetString("Levels", "File", chr_Tag2, 1024);

	strcpy(App->CL_Vm_Model->Model_FolderPath, Scene_JustPath);
	strcpy(App->CL_Vm_Model->FileName, chr_Tag2);*/

	//Read_Player();
	//Read_Camera();

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

	App->Set_Main_TitleBar(App->CL_Vm_FileIO->Model_Path_FileName);

	return 1;
}

// *************************************************************************
// *	  					Load_Project_Aera Terry Flanigan			   *
// *************************************************************************
bool SB_Project::Load_Project_Aera()
{
	

	App->Say(Level_Folder_Path);
	return 1;
}
