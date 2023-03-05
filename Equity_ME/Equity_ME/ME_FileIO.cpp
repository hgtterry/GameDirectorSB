/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "resource.h"
#include "ME_FileIO.h"
#include <shellapi.h>
#include "Shlobj.h"
#include "io.h"
#include <string>
#include "shobjidl_core.h"

ME_FileIO::ME_FileIO()
{
	Model_FileName[0] = 0;
	Model_Path_FileName[0] = 0;
	RecentFile[0] = 0;
	Texture_FileName[0] = 0;
	Texture_Path_FileName[0] = 0;
	JustFileName[0] = 0;
	mSelected_Recent = 0;
	BrowserMessage[0] = 0;
	szSelectedDir[0] = 0;

	ReadRecentFiles = nullptr;
}


ME_FileIO::~ME_FileIO()
{
}

// *************************************************************************
// *						Folder_Browser Terry Bernie					   *
// *************************************************************************
bool ME_FileIO::Folder_Browser()
{
	IFileDialog* pfd;
	if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd))))
	{
		DWORD dwOptions;
		if (SUCCEEDED(pfd->GetOptions(&dwOptions)))
		{
			pfd->SetOptions(dwOptions | FOS_PICKFOLDERS);
		}
		if (SUCCEEDED(pfd->Show(App->MainHwnd)))
		{
			IShellItem* psi;
			if (SUCCEEDED(pfd->GetResult(&psi)))
			{
				if (!SUCCEEDED(psi->GetDisplayName(SIGDN_DESKTOPABSOLUTEPARSING, (LPWSTR*)"poo")))
				{
					//MessageBox(NULL, "GetIDListName() failed", NULL, NULL);
					App->Say("Failed");
				}
				psi->Release();
			}
		}
		pfd->Release();
	}

	return 1;
}

// *************************************************************************
// *						OpenFile Terry Bernie						   *
// *************************************************************************
bool ME_FileIO::Open_File_Model(char* Extension, char* Title, char* StartDirectory)
{
	
	Model_FileName[0] = 0;
	Model_Path_FileName[0] = 0;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Model_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Model_Path_FileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Model_FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Model_FileName);;
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		return 1;
	}

	return 0;
}

// *************************************************************************
// *					OpenTextureFile Terry Bernie			  	 	   *
// *************************************************************************
bool ME_FileIO::OpenTextureFile(char* Title, char* StartDirectory, bool SaveLocation)
{
	Texture_FileName[0] = 0;
	Texture_Path_FileName[0] = 0;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->Fdlg;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Texture_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Texture_Path_FileName);
	ofn.lpstrFilter = "Available Formats\0*.bmp;*.tga;*.jpg;*.png;*.dds;*.pcx;*.tif;*.tiff;\0Windows Bitmap  (*.bmp)\0*.bmp\0Truevision Targa  (*.tga) \0*.tga\0JPEG  (*.jpg) \0*.jpg\0Portable Network Graphics (*.png) \0*.png\0Direct Draw  (*.dds) \0*.dds\0ZSoft PCX  (*.pcx) \0*.pcx\0Tagged Image File Format  (*.tif) \0*.tif\0Tagged Image File Format  (*.tiff) \0*.tiff\0";

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Texture_FileName;				// Just File Name
	ofn.nMaxFileTitle = sizeof(Texture_FileName);
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;
	if (GetOpenFileName(&ofn) == TRUE)
	{
		return 1;
	}

	return 0;
}

// *************************************************************************
// *					Get_Model_File_Name Terry Flanigan				   *
// *************************************************************************
std::string ME_FileIO::Get_Model_File_Name()
{
	return Model_FileName;
}

// *************************************************************************
// *				Get_Model_Path_File_Name Terry Flanigan				   *
// *************************************************************************
std::string ME_FileIO::Get_Model_Path_File_Name()
{
	return Model_Path_FileName;
}

// *************************************************************************
// *							StartBrowser   							   *
// *************************************************************************
bool ME_FileIO::StartBrowser(char* szInitDir)
{
	TCHAR dname[MAX_PATH * 2];
	IMalloc *imalloc; SHGetMalloc(&imalloc);
	BROWSEINFO bi; ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = App->Fdlg;
	bi.pszDisplayName = dname;
	bi.lpszTitle = BrowserMessage;
	bi.lParam = (LPARAM)szInitDir;
	bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_USENEWUI;
	bi.lpfn = BrowseCallbackProc;

	CoInitialize(NULL);
	ITEMIDLIST *pidl = SHBrowseForFolder(&bi);

	if (pidl)
	{
		imalloc->Free(pidl);
		imalloc->Release();
		return 1;
	}

	imalloc->Free(pidl);
	imalloc->Release();

	return 0;
}

// *************************************************************************
// *						BrowseCallbackProc   						   *
// *************************************************************************
int __stdcall ME_FileIO::BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData)
{
	//Initialization callback message
	if (uMsg == BFFM_INITIALIZED)
	{
		//SendMessage(hWnd, BFFM_SETSELECTION, 1, (LPARAM) szInitialPathName); 

		LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);

		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, (LPARAM)path);

	}

	//Selection change message - store the selected directory
	if (uMsg == BFFM_SELCHANGED)
	{
		TCHAR szDir[MAX_PATH * 2] = { 0 };

		// fail if non-filesystem
		BOOL bRet = SHGetPathFromIDList((LPITEMIDLIST)lParam, szDir);
		if (bRet)
		{
			//If the folder cannot be "read" then fail
			if (_taccess(szDir, 00) != 0)
			{
				bRet = FALSE;
			}
			else
			{
				SHFILEINFO sfi;
				::SHGetFileInfo((LPCTSTR)lParam, 0, &sfi, sizeof(sfi),
					SHGFI_PIDL | SHGFI_ATTRIBUTES);

				// fail if pidl is a link
				if (sfi.dwAttributes & SFGAO_LINK)
					bRet = FALSE;
			}
		}

		// if invalid selection, disable the OK button
		if (!bRet)
		{
			::EnableWindow(GetDlgItem(hwnd, IDOK), FALSE);
			strcpy(App->CL_FileIO->szSelectedDir, "");
		}
		else
			strcpy(App->CL_FileIO->szSelectedDir, szDir);
	}

	return 0;
}

// *************************************************************************
// *					SearchFolders Terry Bernie			 		 	   *
// *************************************************************************
bool ME_FileIO::SearchFolders(char* Path, char* File)
{
	char pSearchPath[1024];

	WIN32_FIND_DATA FindFileData;
	HANDLE hFind;

	strcpy(pSearchPath, Path);
	strcat(pSearchPath, File);

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
// *					Search_For_Folder Terry Bernie				 	   *
// *************************************************************************
bool ME_FileIO::Search_For_Folder(char* FolderPath)
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
// *						CheckPath Terry Bernie	   					   *
// *************************************************************************
void ME_FileIO::CheckPath(char *pString, char *FileName,char* mJustFileName)
{
	JustFileName[0] = 0;

	int Count = 0;
	int Mark = 0;
	bool Test = 0;

	while (*pString != 0)
	{
		if (*pString == '\\' || *pString == '/')
		{
			Test = 1;
			Mark = Count;
		}

		Count++;
		pString++;
	}

	if (Mark == 0 && Test == 0)
	{
		strcpy(mJustFileName, FileName);
	}
	else
	{
		if (Mark == 0 && Test == 1)
		{
			Mark = 1;
			strcpy(mJustFileName, (FileName + Mark));
		}
		else
		{
			strcpy(mJustFileName, (FileName + Mark) + 1);
		}
	}

}

// *************************************************************************
// *						Init_History() Terry Bernie					   *
// *************************************************************************
void ME_FileIO::Init_History()
{

	char DirCheck[MAX_PATH];
	strcpy(DirCheck, UserData_Folder);
	strcat(DirCheck, "\\");
	strcat(DirCheck, "Vima19");


	bool check = 0;
	check = Search_For_Folder(DirCheck);
	if (check == 0)
	{
		mPreviousFiles_Models.resize(RECENT_FILES);

		CreateDirectory(DirCheck, NULL);
		ResentHistory_Clear(); // Set all slots to Empty
		Save_FileHistory();
		LoadHistory();
	}
	else
	{
		char mCheckFile[MAX_PATH];

		strcpy(mCheckFile, DirCheck);
		strcat(mCheckFile, "\\Projects.ini");

		bool checkfile = App->CL_Utilities->Check_File_Exist(mCheckFile);

		if (checkfile == 1)
		{

		}
		else
		{
			ReadRecentFiles = nullptr;
			ReadRecentFiles = fopen(mCheckFile, "wt");
			fclose(ReadRecentFiles);
		}

		LoadHistory();
	}
}

// *************************************************************************
// *						LoadHistory() Terry Bernie					   *
// *************************************************************************
void ME_FileIO::LoadHistory()
{
	mPreviousFiles_Models.resize(RECENT_FILES);

	char buffer[1024];
	char buf[1024];

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Vima19.ini");

	
	ReadRecentFiles = nullptr;

	ReadRecentFiles = fopen(buf, "rt");

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

		mPreviousFiles_Models[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	// Check for empty slots and gray out
	for (int i = RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles_Models[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);

	}

	return;
}

// *************************************************************************
// *					Save_FileHistory Terry Bernie					   *
// *************************************************************************
void ME_FileIO::Save_FileHistory()
{

	WriteRecentFiles = nullptr;

	char buf[MAX_PATH];
	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Vima19.ini");

	WriteRecentFiles = fopen(buf, "wt");

	if (!WriteRecentFiles)
	{
		App->Say("Why Cant Find Recent Files");
		return;
	}

	// Save out to RecentFile.ini
	for (unsigned int i = 0; i < RECENT_FILES; ++i)
	{
		char szName[MAX_PATH];
		strcpy(szName, mPreviousFiles_Models[i].c_str());

		fprintf(WriteRecentFiles, "%s\n", szName);
	}
	fclose(WriteRecentFiles);



	WriteRecentFiles = nullptr;

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Projects.ini");

	WriteRecentFiles = fopen(buf, "wt");

	if (!WriteRecentFiles)
	{
		App->Say("Why Cant Find Recent Files");
		return;
	}

	fclose(WriteRecentFiles);
	return;
}

// *************************************************************************
// *					RecentFileHistory_Update Terry Bernie			   *
// *************************************************************************
void ME_FileIO::RecentFileHistory_Update()
{
	
	std::string sz = std::string(App->CL_Model->Path_FileName);
	if (mPreviousFiles_Models[RECENT_FILES - 1] == sz)return;

	// add the new file to the list of recent files
	for (unsigned int i = 0; i < RECENT_FILES - 1; ++i)
	{
		mPreviousFiles_Models[i] = mPreviousFiles_Models[i + 1];
	}

	mPreviousFiles_Models[RECENT_FILES - 1] = sz;

	// Check for empty slots and gray out
	for (int i = RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles_Models[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);
		/*if (Result == 0)
		{
			iFlags = MF_GRAYED | MF_DISABLED;
		}*/
	}

	// Save Changes
	Save_FileHistory();

	return;
}

// *************************************************************************
// *			ResentHistory_Clear Terry Bernie Hazel Nathan			   *
// *************************************************************************
void ME_FileIO::ResentHistory_Clear()
{
	App->CL_Dialogs->YesNo("Delete file history.", "Are you sure all File history will be Deleted Procede.");
	if (App->CL_Dialogs->Canceled == 1)
	{
		return;
	}

	// Set all slots to <empty>
	for (unsigned int i = 0; i < RECENT_FILES; ++i)
	{
		mPreviousFiles_Models[i] = std::string("<empty>");
	}

	// Save Changes
	Save_FileHistory();
}

// *************************************************************************
// *					LoadHistory_Equity Terry Bernie					   *
// *************************************************************************
void ME_FileIO::LoadHistory_Equity()
{
	mPreviousFiles_Models.resize(RECENT_FILES);

	char buffer[1024];
	char buf[1024];

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Vima19.ini");

	ReadRecentFiles = fopen(buf, "rt");

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

		mPreviousFiles_Models[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	
	// Check for empty slots and gray out
	for (int i = RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles_Models[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);
		if (Result == 0)
		{
			iFlags = MF_GRAYED | MF_DISABLED;
		}

		
	}

	return;
}

// *************************************************************************
// *	  Start_RecentProjects_Dlg:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void ME_FileIO::Start_RecentProjects_Dlg(int Selected_Recent)
{
	mSelected_Recent = Selected_Recent;

	DialogBox(App->hInst, (LPCTSTR)IDD_RECENTPRJ, App->Fdlg, (DLGPROC)RecentProjects_Proc);
}

// *************************************************************************
// *			RecentProjects_Proc:- Terry and Hazel Flanigan 2022 	   *
// *************************************************************************
LRESULT CALLBACK ME_FileIO::RecentProjects_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_INITDIALOG:
	{

		SendDlgItemMessage(hDlg, IDC_RECENTPRJLIST, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDOK, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDCANCEL, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		SendDlgItemMessage(hDlg, IDC_BTCLEARFILES, WM_SETFONT, (WPARAM)App->Font_CB15, MAKELPARAM(TRUE, 0));
		

		SendDlgItemMessage(hDlg, IDC_RECENTPRJLIST, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);

		if (App->CL_FileIO->mSelected_Recent == 0)
		{
			App->CL_FileIO->List_Recent_Files(hDlg);

			return TRUE;
		}

		if (App->CL_FileIO->mSelected_Recent == 1)
		{
			App->CL_FileIO->List_Recent_Files(hDlg);

			return TRUE;
		}

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

		if (some_item->idFrom == IDC_BTCLEARFILES && some_item->code == NM_CUSTOMDRAW)
		{
			LPNMCUSTOMDRAW item = (LPNMCUSTOMDRAW)some_item;
			App->Custom_Button_Normal(item);
			return CDRF_DODEFAULT;
		}

		return CDRF_DODEFAULT;
	}

	case WM_COMMAND:
	{
		if (LOWORD(wParam) == IDC_RECENTPRJLIST)
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
		}

		if (LOWORD(wParam) == IDC_BTCLEARFILES)
		{
			App->CL_FileIO->ResentHistory_Clear();
			SendDlgItemMessage(hDlg, IDC_RECENTPRJLIST, LB_RESETCONTENT, (WPARAM)0, (LPARAM)0);
			return TRUE;
		}

		if (LOWORD(wParam) == IDOK)
		{
			EndDialog(hDlg, LOWORD(wParam));
			App->CL_Import->Reload_FromResentFiles(App->CL_FileIO->RecentFile);
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
void ME_FileIO::List_Recent_Files(HWND hDlg)
{
	char buf[MAX_PATH];
	char buffer[MAX_PATH];

	mPreviousFiles_Models.resize(RECENT_FILES);

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Vima19.ini");

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

		mPreviousFiles_Models[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	// Check for empty slots and gray out
	for (int i = RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[MAX_PATH];
		strcpy(szText, mPreviousFiles_Models[i].c_str());

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
// *	  				List_Recent_Projects Terry Flanigan				   *
// *************************************************************************
void ME_FileIO::List_Recent_Projects(HWND hDlg)
{
	char buf[MAX_PATH];
	char buffer[MAX_PATH];

	sprintf(buf, "%s", "Model Info");
	SendDlgItemMessage(hDlg, IDC_RECENTPRJLIST, LB_ADDSTRING, (WPARAM)0, (LPARAM)buf);

	mPreviousFiles_Models.resize(RECENT_FILES);

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Vima19.ini");

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

		mPreviousFiles_Models[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	// Check for empty slots and gray out
	for (int i = RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[MAX_PATH];
		strcpy(szText, mPreviousFiles_Models[i].c_str());

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

