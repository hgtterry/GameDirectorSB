/*
Copyright (c) 2021 EquitySB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

:- Terry and Hazel Flanigan 2022

*/

#include "stdafx.h"
#include "resource.h"
#include "GD19_App.h"
#include "SB_Preferences.h"

SB_Preferences::SB_Preferences()
{
	Main_Window_Hwnd = nullptr;
	FileView_Hwnd = nullptr;

	// -------------------------- Quick Load
	QL_Use_TestFile_Flag = 1;
	strcpy(QL_User_File,"Not_Set");

	Show_StartScreen = 1;
}

SB_Preferences::~SB_Preferences()
{
	
}

// *************************************************************************
// *			Set_Defaults:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Preferences::Set_Defaults()
{
	// -------------------------- Quick Load
	QL_Use_TestFile_Flag = 1;
	strcpy(QL_User_File, "Not_Set");

	Show_StartScreen = 1;

	Write_Preferences();
}

// *************************************************************************
// *			Write_Preferences:- Terry and Hazel Flanigan 2022 		   *
// *************************************************************************
bool SB_Preferences::Write_Preferences()
{
	
	WriteScene = NULL;

	char Preferences_Path[1024];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);;
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Preferences.ini");

	WriteScene = fopen(Preferences_Path, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	

	fprintf(WriteScene, "%s\n", "[Quick_Load]");
	fprintf(WriteScene, "%s%i\n", "QL_Use_TestFile=", QL_Use_TestFile_Flag);
	fprintf(WriteScene, "%s%s\n", "QL_User_File=", QL_User_File);

	fprintf(WriteScene, "%s\n", " ");

	fprintf(WriteScene, "%s\n", "[Start_Up]");
	fprintf(WriteScene, "%s%i\n", "Show_StartScreen=", Show_StartScreen);
	
	fclose(WriteScene);

	//Read_Preferences();
	return 1;
}

// *************************************************************************
// *			Read_Preferences:- Terry and Hazel Flanigan 2022 		   *
// *************************************************************************
bool SB_Preferences::Read_Preferences()
{
	char chr_Tag1[1024];
	char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	char Preferences_Path[1024];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Preferences.ini");

	App->Cl_Ini->SetPathName(Preferences_Path);

	QL_Use_TestFile_Flag = App->Cl_Ini->GetInt("Quick_Load", "QL_Use_TestFile", 10);

	App->Cl_Ini->GetString("Quick_Load", "QL_User_File", chr_Tag1, 1024);
	strcpy(QL_User_File, chr_Tag1);

	Show_StartScreen = App->Cl_Ini->GetInt("Start_Up", "Show_StartScreen", 10);

	return 1;
}

// *************************************************************************
// *	  	 Start_Preferences:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Preferences::Start_Preferences()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_PREFERENCES, App->Fdlg, (DLGPROC)Preferences_Proc);
	return 1;
}

// *************************************************************************
// *		  Preferences_Proc:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
LRESULT CALLBACK SB_Preferences::Preferences_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		App->SetTitleBar(hDlg);

		SendDlgItemMessage(hDlg, IDC_EDITTEXT, IDOK, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_EDITTEXT, IDCANCEL, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));


		/*SetDlgItemText(hDlg, IDC_TITLENAME, (LPCTSTR)App->Cl_Dialogs->btext);

		SetDlgItemText(hDlg, IDC_EDITTEXT, (LPCTSTR)App->Cl_Dialogs->Chr_Text);*/

		App->SBC_Prefs->Main_Window_Hwnd = hDlg;

		App->SBC_Prefs->FileView_Hwnd = GetDlgItem(hDlg, IDC_PREFTREE1);

		App->SBC_Prefs->AddRootFolder();

		//App->SBC_Prefs->Read_Preferences();

		App->SBC_Prefs->Start_QuickLoad_Dlg();

		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		/*if (GetDlgItem(hDlg, IDC_TITLENAME) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 255));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}*/
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

		if (some_item->idFrom == IDCANCEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDOK)
		{
			App->SBC_Prefs->Write_Preferences();

			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}

		if (LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return TRUE;
		}
	}

	break;

	}
	return FALSE;
}

// *************************************************************************
// *		  AddRootFolder:- Terry and Hazel Flanigan 2022		 	 	   *
// *************************************************************************
void SB_Preferences::AddRootFolder(void)
{
	tvinsert.hParent = Root;			// top most level no need handle
	tvinsert.hInsertAfter = TVI_LAST; // work as root level
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "File";
	tvinsert.item.iImage = 0;
	tvinsert.item.iSelectedImage = 1;
	FV_File = (HTREEITEM)SendDlgItemMessage(Main_Window_Hwnd, IDC_PREFTREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);

	tvinsert.hParent = FV_File;
	tvinsert.hInsertAfter = TVI_LAST;
	tvinsert.item.mask = TVIF_TEXT | TVIF_IMAGE | TVIF_SELECTEDIMAGE;
	tvinsert.item.pszText = "Quick Load";
	tvinsert.item.iImage = 2;
	tvinsert.item.iSelectedImage = 3;
	SendDlgItemMessage(Main_Window_Hwnd, IDC_PREFTREE1, TVM_INSERTITEM, 0, (LPARAM)&tvinsert);
}

// *************************************************************************
// *	  	Start_QuickLoad_Dlg:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Preferences::Start_QuickLoad_Dlg()
{
	CreateDialog(App->hInst, (LPCTSTR)IDD_STARTUP, Main_Window_Hwnd, (DLGPROC)QuickLoad_Proc);
	return 1;
}
// *************************************************************************
// *		QuickLoad_Proc:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
LRESULT CALLBACK SB_Preferences::QuickLoad_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{


		HFONT Font2;
		Font2 = CreateFont(-20, 0, 0, 0, FW_BOLD, 0, 0, 0, 0, OUT_TT_ONLY_PRECIS, 0, 0, 0, "Aerial Black");

		SendDlgItemMessage(hDlg, IDC_CKDEFAULT, WM_SETFONT, (WPARAM)Font2, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_STTAGFILE, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_CK_SHOWSTARTUPSCREEN, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));


		char StartFile[1024];
		strcpy(StartFile, App->EquityDirecory_FullPath);
		strcat(StartFile, "\\");
		strcat(StartFile, "Data\\Preferences.ini");

		App->Cl_Ini->SetPathName(StartFile);

		bool Default = App->Cl_Ini->GetBool("Quick_Load", "QL_Use_TestFile", 1);
		if (Default == 1)
		{
			App->SBC_Prefs->QL_Use_TestFile_Flag = 1;
			HWND temp = GetDlgItem(hDlg, IDC_CKDEFAULT);
			SendMessage(temp, BM_SETCHECK, 1, 0);
			EnableWindow(GetDlgItem(hDlg, IDC_STUSERFILE), 0);
			EnableWindow(GetDlgItem(hDlg, IDC_BTBROWSE), 0);
		}
		else
		{
			App->SBC_Prefs->QL_Use_TestFile_Flag = 0;
			HWND temp = GetDlgItem(hDlg, IDC_CKDEFAULT);
			SendMessage(temp, BM_SETCHECK, 0, 0);
			EnableWindow(GetDlgItem(hDlg, IDC_STUSERFILE), 1);
			EnableWindow(GetDlgItem(hDlg, IDC_BTBROWSE), 1);
		}

		if (App->SBC_Prefs->Show_StartScreen == 1)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_SHOWSTARTUPSCREEN);
			SendMessage(temp, BM_SETCHECK, 1, 0);
		}

		char buff[1024];
		App->Cl_Ini->GetString("Startup", "Scene_Path_FileName", buff, 1024);
		SetDlgItemText(hDlg, IDC_STUSERFILE, (LPTSTR)buff);
		strcpy(App->SBC_FileIO->Data_Path_mFilename, buff);

		App->Cl_Ini->GetString("Startup", "Scene_FileName", buff, 1024);
		strcpy(App->SBC_FileIO->Data_mFilename, buff);


		return TRUE;
	}
	case WM_CTLCOLORSTATIC:
	{
		if (GetDlgItem(hDlg, IDC_STUSERFILE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->Brush_White;
		}

		if (GetDlgItem(hDlg, IDC_CKDEFAULT) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_STTAGFILE) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
			SetTextColor((HDC)wParam, RGB(0, 0, 0));
			SetBkMode((HDC)wParam, TRANSPARENT);
			return (UINT)App->AppBackground;
		}

		if (GetDlgItem(hDlg, IDC_CK_SHOWSTARTUPSCREEN) == (HWND)lParam)
		{
			SetBkColor((HDC)wParam, RGB(0, 255, 0));
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


	case WM_COMMAND:
		if (LOWORD(wParam) == IDC_BTBROWSE)
		{

			bool test = App->SBC_FileIO->Open_Project_File("Project   *.SBProj\0*.SBProj\0", "Project File", NULL);
			if (test == 0)
			{
				return 0;
			}

			SetDlgItemText(hDlg, IDC_STUSERFILE, (LPTSTR)App->SBC_FileIO->Data_mFilename);
			return 1;

		}
		if (LOWORD(wParam) == IDC_CKDEFAULT)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CKDEFAULT);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				App->SBC_Prefs->QL_Use_TestFile_Flag = 1;
				SetDlgItemText(hDlg, IDC_STUSERFILE, (LPTSTR)App->Default_Project);
				EnableWindow(GetDlgItem(hDlg, IDC_STUSERFILE), 0);
				EnableWindow(GetDlgItem(hDlg, IDC_BTBROWSE), 0);
				return 1;
			}
			else
			{
				App->SBC_Prefs->QL_Use_TestFile_Flag = 0;
				EnableWindow(GetDlgItem(hDlg, IDC_STUSERFILE), 1);
				EnableWindow(GetDlgItem(hDlg, IDC_BTBROWSE), 1);
				return 1;
			}

			return 1;
		}

		if (LOWORD(wParam) == IDC_CK_SHOWSTARTUPSCREEN)
		{
			HWND temp = GetDlgItem(hDlg, IDC_CK_SHOWSTARTUPSCREEN);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				App->SBC_Prefs->Show_StartScreen = 1;
				return 1;
			}
			else
			{
				App->SBC_Prefs->Show_StartScreen = 0;
				return 1;
			}

			return 1;
		}

		if (LOWORD(wParam) == IDOK)
		{
			bool test2 = 0;
			HWND temp = GetDlgItem(hDlg, IDC_CKDEFAULT);
			int test = SendMessage(temp, BM_GETCHECK, 0, 0);
			if (test == BST_CHECKED)
			{
				test2 = App->Cl_Ini->WriteBool("Startup", "Default", 1);
				if (test2 == 0)
				{
					App->Say("Error Writing 1");
				}

				test2 = App->Cl_Ini->WriteString("Startup", "Scene_Path_FileName", App->Default_Project);
				SetDlgItemText(hDlg, IDC_STUSERFILE, (LPTSTR)App->Default_Project);
				if (test2 == 0)
				{
					App->Say("Error Writing 1");
				}

			}
			else
			{
				test2 = App->Cl_Ini->WriteBool("Startup", "Default", 0);
				if (test2 == 0)
				{
					App->Say("Error Writing 2");
				}

				test2 = App->Cl_Ini->WriteString("Startup", "Scene_FileName", App->SBC_FileIO->Data_mFilename);
				if (test2 == 0)
				{
					App->Say("Error Writing 3");
				}

				test2 = App->Cl_Ini->WriteString("Startup", "Scene_Path_FileName", App->SBC_FileIO->Data_Path_mFilename);
				if (test2 == 0)
				{
					App->Say("Error Writing 4");
				}
			}

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
