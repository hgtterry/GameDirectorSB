/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "AB_App.h"
#include "SB_RecentFiles.h"

SB_RecentFiles::SB_RecentFiles(void)
{
	UserData_Folder[0] = 0;

	WriteRecentFiles = nullptr;
	ReadRecentFiles = nullptr;
}

SB_RecentFiles::~SB_RecentFiles(void)
{
}

// *************************************************************************
// *			  Start_RecentFiles:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_RecentFiles::Start_RecentFiles_Dlg()
{
	DialogBox(App->hInst, (LPCTSTR)IDD_SB_RECENTPRJ, App->MainHwnd, (DLGPROC)RecentFiles_Proc);
}

// *************************************************************************
// *			RecentFiles_Proc:- Terry and Hazel Flanigan 2022 		   *
// *************************************************************************
LRESULT CALLBACK SB_RecentFiles::RecentFiles_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_RECENTPRJLIST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		//SendDlgItemMessage(hDlg, IDC_BTCLEARFILES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));

	
		SendDlgItemMessage(hDlg, IDC_RECENTPRJLIST, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		App->CLSB_RecentFiles->List_Recent_Files(hDlg);

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

		/*if (some_item->idFrom == IDCANCEL && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		if (some_item->idFrom == IDC_BTCLEARFILES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}*/

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		/*if (LOWORD(wParam) == IDC_RECENTPRJLIST)
		{
			App->CL_FileIO->RecentFile[0] = 0;
			int Index = 0;

			Index = SendDlgItemMessage(hDlg, IDC_RECENTPRJLIST, LB_GETCURSEL, (WPARAM)0, (LPARAM)0);
			if (Index == -1)
			{
				return 1;
			}
			else
			{
				SendDlgItemMessage(hDlg, IDC_RECENTPRJLIST, LB_GETTEXT, (WPARAM)Index, (LPARAM)App->CL_FileIO->RecentFile);

			}

			return TRUE;
		}*/

		/*if (LOWORD(wParam) == IDC_BTCLEARFILES)
		{
			if (App->CL_FileIO->mSelected_Recent == 0)
			{
				App->CL_Dialogs->YesNo("Delete file history.", "Are you sure all Models history will be Deleted Procede.");
				if (App->CL_Dialogs->Canceled == 1)
				{
					return 1;
				}
				App->CL_Recent_Files->ResentHistory_Models_Clear();
			}

			if (App->CL_FileIO->mSelected_Recent == 1)
			{
				App->CL_Dialogs->YesNo("Delete file history.", "Are you sure all Projects history will be Deleted Procede.");
				if (App->CL_Dialogs->Canceled == 1)
				{
					return 1;
				}
				App->CL_Recent_Files->ResentHistory_Projects_Clear();
			}


			SendDlgItemMessage(hDlg, IDC_RECENTPRJLIST, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

			return TRUE;
		}*/

		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			//App->CL_Import->Reload_FromResentFiles(App->CL_FileIO->RecentFile);
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
// *	  				List_Recent_Files Terry Flanigan				   *
// *************************************************************************
void SB_RecentFiles::List_Recent_Files(HWND hDlg)
{
	char buf[MAX_PATH];
	char buffer[MAX_PATH];

	mPreviousFiles_Files.resize(RECENT_FILES);

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\WorldEditorSB.ini");

	ReadRecentFiles = fopen(buf, "rt");

	if (!ReadRecentFiles)
	{
		App->Say("Cant Find Recent Files");
		return;
	}

	// Read in File Names from RecentFiles.ini
	for (unsigned int i = 0; i < RECENT_FILES; ++i)
	{
		memset(buffer, 0, MAX_PATH);
		fgets(buffer, MAX_PATH, ReadRecentFiles);

		char Path[MAX_PATH];
		strcpy(Path, buffer);
		int Len = strlen(Path);
		Path[Len - 1] = 0;

		mPreviousFiles_Files[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	// Check for empty slots and gray out
	for (int i = RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[MAX_PATH];
		strcpy(szText, mPreviousFiles_Files[i].c_str());

		int Result = 0;
		Result = strcmp("<empty>", szText);
		if (Result == 0)
		{

		}
		else
		{
			sprintf(buf, "%s", szText);
			SendDlgItemMessage(hDlg, IDC_RECENTPRJLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);
		}
	}
}

// *************************************************************************
// *			Init_History:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_RecentFiles::Init_History()
{

	char DirCheck[MAX_PATH];
	strcpy(DirCheck, UserData_Folder);
	strcat(DirCheck, "\\");
	strcat(DirCheck, "Vima19");


	bool check = 0;
	check = Search_For_Folder(DirCheck);
	if (check == 0)
	{
		mPreviousFiles_Files.resize(RECENT_FILES);
	
		CreateDirectory(DirCheck, NULL);
		ResentHistory_Files_Clear();	// Models
	
		Save_FileHistory_Files();

		LoadHistory_Files();
	}
	else
	{
		char mCheckFile[MAX_PATH];
		strcpy(mCheckFile, DirCheck);
		strcat(mCheckFile, "\\WorldEditorSB.ini");


		bool checkfile = Check_File_Exist(mCheckFile);

		if (checkfile == 1)
		{

		}
		else
		{
			mPreviousFiles_Files.resize(RECENT_FILES);

			ResentHistory_Files_Clear();
			Save_FileHistory_Files();
			LoadHistory_Files();
		}

		LoadHistory_Files();
	}
}

// *************************************************************************
// *		ResentHistory_Files_Clear:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
void SB_RecentFiles::ResentHistory_Files_Clear()
{

	// Set all slots to <empty>
	for (unsigned int i = 0; i < RECENT_FILES; ++i)
	{
		mPreviousFiles_Files[i] = std::string("<empty>");
	}

	// Save Changes
	Save_FileHistory_Files();
}

// *************************************************************************
// *		Save_FileHistory_Files:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void SB_RecentFiles::Save_FileHistory_Files()
{

	WriteRecentFiles = nullptr;

	char buf[MAX_PATH];
	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\WorldEditorSB.ini");

	WriteRecentFiles = std::fopen(buf, "wt");

	if (!WriteRecentFiles)
	{
		App->Say("Why Cant Find Recent Files");
		return;
	}

	// Save out to Vima19.ini
	for (unsigned int i = 0; i < RECENT_FILES; ++i)
	{
		char szName[MAX_PATH];
		strcpy(szName, mPreviousFiles_Files[i].c_str());

		fprintf(WriteRecentFiles, "%s\n", szName);
	}

	std::fclose(WriteRecentFiles);

	return;
}

// *************************************************************************
// *		LoadHistory_Files:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_RecentFiles::LoadHistory_Files()
{
	mPreviousFiles_Files.resize(RECENT_FILES);

	char buffer[1024];
	char buf[1024];

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\WorldEditorSB.ini");


	ReadRecentFiles = nullptr;

	ReadRecentFiles = std::fopen(buf, "rt");

	if (!ReadRecentFiles)
	{
		App->Say("Cant Find Recent Files");
		return;
	}

	// Read in File Names from RecentFiles.ini
	for (unsigned int i = 0; i < RECENT_FILES; ++i)
	{
		memset(buffer, 0, 1024);
		fgets(buffer, 1024, ReadRecentFiles);

		char Path[1024];
		strcpy(Path, buffer);
		int Len = strlen(Path);
		Path[Len - 1] = 0;

		mPreviousFiles_Files[i] = std::string(Path);
	}

	std::fclose(ReadRecentFiles);

	// Check for empty slots and gray out
	for (int i = RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles_Files[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);

	}

	return;
}

// *************************************************************************
// *		Search_For_Folder:- Terry and Hazel Flanigan 2023		 	   *
// *************************************************************************
bool SB_RecentFiles::Search_For_Folder(char* FolderPath)
{
	char pSearchPath[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(pSearchPath, FolderPath);

	hFind = FindFirstFile(pSearchPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	else
	{
		FindClose(hFind);
		return 1;
	}

	return 0;
}

// *************************************************************************
// *		Check_File_Exist:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
bool SB_RecentFiles::Check_File_Exist(char* Full_Path)
{
	char pSearchPath[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(pSearchPath, Full_Path);

	hFind = FindFirstFile(pSearchPath, &FindFileData);
	if (hFind == INVALID_HANDLE_VALUE)
	{
		return 0;
	}
	else
	{
		FindClose(hFind);
		return 1;
	}

	return 0;
}
