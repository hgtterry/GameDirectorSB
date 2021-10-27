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

	Project_Ini_FilePath[0] = 0;
	Level_Folder_Path[0] = 0;
	Write_Ini = NULL;

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
			strcpy(App->CL_Vm_FileIO->BrowserMessage, "Select Folder To Place New Project a sub folder will be created");
			int Test = App->CL_Vm_FileIO->StartBrowser("");

			if (Test == 0){return true;}

			strcpy(App->SBC_Project->Project_FullPath, App->CL_Vm_FileIO->szSelectedDir);
			strcat(App->SBC_Project->Project_FullPath, App->SBC_Project->Project_Name);
			strcat(App->SBC_Project->Project_FullPath, "_Prj");

			strcpy(App->SBC_Project->Project_Path, App->CL_Vm_FileIO->szSelectedDir);

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
			App->SBC_Project->Create_Project();
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

	Add_World();

	strcpy(App->CL_Vm_Model->Model_FolderPath, Level_Folder_Path);
	strcpy(App->CL_Vm_Model->FileName, "World.mesh");

	App->CL_Bullet_AddRoom->AddToScene(1);

	App->Say("Created");
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

	fclose(Write_Ini);
	
	return 1;
}

// *************************************************************************
// *	  				Create_Level_Folder Terry Flanigan				   *
// *************************************************************************
bool SB_Project::Create_Level_Folder()
{

	if (_mkdir(Level_Folder_Path) == 0)
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
// *	  					Add_World Terry Flanigan					   *
// *************************************************************************
bool SB_Project::Add_World()
{
	char Source[1024];
	char Destination[1024];

	strcpy(Source, "C:\\Users\\Equity\\Desktop\\Equity15\\Bin\\Data\\World_Ogre\\World.mesh");

	strcpy(Destination, Level_Folder_Path);
	strcat(Destination, "\\");
	strcat(Destination, "World.mesh");

	CopyFile(Source, Destination, true);

	// --------------------------------------------------------------------
	strcpy(Source, "C:\\Users\\Equity\\Desktop\\Equity15\\Bin\\Data\\World_Ogre\\World.material");

	strcpy(Destination, Level_Folder_Path);
	strcat(Destination, "\\");
	strcat(Destination, "World.material");

	CopyFile(Source, Destination, true);

	// --------------------------------------------------------------------
	strcpy(Source, "C:\\Users\\Equity\\Desktop\\Equity15\\Bin\\Data\\World_Ogre\\Wall.bmp");

	strcpy(Destination, Level_Folder_Path);
	strcat(Destination, "\\");
	strcat(Destination, "Wall.bmp");

	CopyFile(Source, Destination, true);

	// --------------------------------------------------------------------
	strcpy(Source, "C:\\Users\\Equity\\Desktop\\Equity15\\Bin\\Data\\World_Ogre\\stfloor1.bmp");

	strcpy(Destination, Level_Folder_Path);
	strcat(Destination, "\\");
	strcat(Destination, "stfloor1.bmp");

	CopyFile(Source, Destination, true);

	// --------------------------------------------------------------------
	strcpy(Source, "C:\\Users\\Equity\\Desktop\\Equity15\\Bin\\Data\\World_Ogre\\concrete.bmp");

	strcpy(Destination, Level_Folder_Path);
	strcat(Destination, "\\");
	strcat(Destination, "concrete.bmp");

	CopyFile(Source, Destination, true);

	return 1;
}
