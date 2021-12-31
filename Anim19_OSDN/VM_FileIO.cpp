#include "stdafx.h"
#include "GD19_App.h"
#include "resource.h"
#include <tchar.h>
#include <shellapi.h>
#include "Shlobj.h"
#include "io.h"
#include "VM_FileIO.h"


VM_FileIO::VM_FileIO()
{

	Scene_FileName[0] = 0;
	Scene_Path_FileName[0] = 0;

	Model_FileName[0] = 0;
	Model_Path_FileName[0] = 0;
	JustFileName[0] = 0;

	Cannceled = 0;
}


VM_FileIO::~VM_FileIO()
{
}

// *************************************************************************
// *					Vm_OpenFile Terry Bernie						   *
// *************************************************************************
bool VM_FileIO::Vm_OpenFile(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Model_FileName, "");
	strcpy(Model_Path_FileName, "");

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
// *					OpenFile Terry Bernie							   *
// *************************************************************************
bool VM_FileIO::OpenFile(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Scene_FileName, "");
	strcpy(Scene_Path_FileName, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Scene_Path_FileName;						// full path and file name
	ofn.nMaxFile = sizeof(Scene_Path_FileName);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Scene_FileName;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Scene_FileName);;
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
bool VM_FileIO::OpenTextureFile(char* Title, char* StartDirectory, bool SaveLocation)
{
	strcpy(Texture_FileName, "");
	strcpy(Texture_Path_FileName, "");

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
		if (SaveLocation == 1)
		{
			//_getcwd(S_Folders[0]->TempLoadLocation,1024);
		}

		return 1;
	}

	return 0;
}

// ************************************************************************
// *						SaveFileCom Terry Bernie		 		 	   *
// *************************************************************************
bool VM_FileIO::SaveFileCom(char* Extension, char* Title, char* StartDirectory)
{
	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = mSavePathFileCom;
	ofn.nMaxFile = sizeof(mSavePathFileCom);
	ofn.lpstrFilter = Extension;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = mSaveFileCom;
	ofn.nMaxFileTitle = sizeof(mSaveFileCom);
	ofn.lpstrInitialDir = StartDirectory;
	ofn.lpstrTitle = Title;
	ofn.Flags = //OFN_PATHMUSTEXIST |
		OFN_NOCHANGEDIR |
		//OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn) == TRUE)
	{
		return 1;
	}

	return 0;
}

// *************************************************************************
// *							SaveFile		  			  		 	   *
// *************************************************************************
bool VM_FileIO::SaveFile(char* Extension, char* Title, char* FileName)
{

	Full_Path_And_File[0] = 0;
	Just_FileName[0] = 0;

	strcpy(Full_Path_And_File, FileName);
	strcpy(Just_FileName, FileName);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Full_Path_And_File; // Full Path
	ofn.nMaxFile = sizeof(Full_Path_And_File);
	ofn.lpstrFilter = Extension;
	;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Just_FileName;
	ofn.nMaxFileTitle = sizeof(Just_FileName); // Just File name
	ofn.lpstrInitialDir = "";
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT;

	if (GetSaveFileName(&ofn) == TRUE)
	{

		return 1;
	}

	return 0;
}

// *************************************************************************
// *					GetColor   Terry Bernie							   *
// *************************************************************************
bool VM_FileIO::GetColor()
{
	Cannceled = 0;
	COLORREF ccref[8];//custom colors
	COLORREF selcolor = 0x000000;//the default selected color

	memset(&color, 0, sizeof(color));
	color.lStructSize = sizeof(CHOOSECOLOR);
	color.hwndOwner = App->MainHwnd;
	color.lpCustColors = ccref;
	color.rgbResult = selcolor;
	color.Flags = CC_RGBINIT;

	if (ChooseColor(&color))
	{
		Cannceled = 0;
		selcolor = color.rgbResult;
		return 1;
	}

	Cannceled = 1;
	return 1;
}

// *************************************************************************
// *							Update_File_Info Terry		  	  	 	   *
// *************************************************************************
bool VM_FileIO::Update_File_Info(char* Full_Path, char* File_Name)
{
	strcpy(App->Cl_Scene_Data->S_Scene[0]->TerrainFileName, File_Name);
	strcpy(App->Cl_Scene_Data->S_Scene[0]->GDSceneName, File_Name);
	strcpy(App->Cl_Scene_Data->S_Scene[0]->Full_Path_AndFile, Full_Path);

	char mPath[256];
	strcpy(mPath, Full_Path);
	int FLen = strlen(File_Name);
	int PLen = strlen(Full_Path);
	mPath[PLen - FLen] = 0;
	strcpy(App->LevelDirectory, mPath);
	strcpy(App->Cl_Scene_Data->S_Scene[0]->Level_Directory, mPath);

	char Temp[256];
	strcpy(Temp, File_Name);
	int Len = strlen(Temp);
	Temp[Len - 8] = 0;
	strcpy(App->Cl_Scene_Data->S_Scene[0]->LevelName, Temp);

	return 0;
}

// *************************************************************************
// *					SearchFolders Terry Bernie			 		 	   *
// *************************************************************************
bool VM_FileIO::SearchFolders(char* Path, char* File)
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
// *							StartBrowser   							   *
// *************************************************************************
bool VM_FileIO::StartBrowser(char* szInitDir,HWND hDlg)
{
	TCHAR dname[MAX_PATH * 2];
	IMalloc *imalloc; SHGetMalloc(&imalloc);
	BROWSEINFO bi; ZeroMemory(&bi, sizeof(bi));
	bi.hwndOwner = hDlg;
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
int __stdcall VM_FileIO::BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData)
{
	//Initialization callback message
	if (uMsg == BFFM_INITIALIZED)
	{
		//SendMessage(hWnd, BFFM_SETSELECTION, 1, (LPARAM) szInitialPathName); 
		SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);

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
			strcpy(App->CL_Vm_FileIO->szSelectedDir, "");
		}
		else
			strcpy(App->CL_Vm_FileIO->szSelectedDir, szDir);
			strcat(App->CL_Vm_FileIO->szSelectedDir,"\\");
	}

	return 0;
}

// *************************************************************************
// *					Create_OutPut_Folder Terry Bernie			 	   *
// *************************************************************************
bool VM_FileIO::Create_Output_Folder(char* Extension)
{
	strcpy(OutputFolder, "");

	strcpy(OutputFolder, App->CL_Vm_FileIO->szSelectedDir);
	strcat(OutputFolder, App->CL_Vm_Model->JustName);
	strcat(OutputFolder, Extension);
	strcat(OutputFolder, "\\");

	CreateDirectory(OutputFolder, NULL);
	return 0;
}

// *************************************************************************
// *						Init_History() Terry Bernie					   *
// *************************************************************************
void VM_FileIO::Init_History()
{
	char DirCheck[1024];
	strcpy(DirCheck, UserData_Folder);
	strcat(DirCheck, "\\");
	strcat(DirCheck, "Vima19");

	bool check = 0;
	check = Search_For_Folder(DirCheck);
	if (check == 0)
	{
		mPreviousFiles.resize(EQUITY_NUM_RECENT_FILES);

		CreateDirectory(DirCheck, NULL);
		ResentHistory_Clear(); // Set all slots to Empty
		Save_FileHistory();
		LoadHistory();
	}
	else
	{
		LoadHistory();
	}
}
// *************************************************************************
// *						LoadHistory() Terry Bernie					   *
// *************************************************************************
void VM_FileIO::LoadHistory()
{
	mPreviousFiles.resize(EQUITY_NUM_RECENT_FILES);

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
	for (unsigned int i = 0; i < EQUITY_NUM_RECENT_FILES; ++i)
	{
		memset(buffer, 0, 1024);
		fgets(buffer, 1024, ReadRecentFiles);

		char Path[1024];
		strcpy(Path, buffer);
		int Len = strlen(Path);
		Path[Len - 1] = 0;

		mPreviousFiles[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	mHistoryMenu = CreateMenu();

	// Check for empty slots and gray out
	for (int i = EQUITY_NUM_RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);
		if (Result == 0)
		{
			iFlags = MF_GRAYED | MF_DISABLED;
		}

		AppendMenu(mHistoryMenu, MF_STRING | iFlags, EQUITY_RECENT_FILE_ID(i), szText);
	}

	ModifyMenu(GetMenu(App->MainHwnd), ID_FILE_RECENTFILES, MF_BYCOMMAND | MF_POPUP,
		(UINT_PTR)mHistoryMenu, "Recent files");
	return;
}

// *************************************************************************
// *					Save_FileHistory Terry Bernie					   *
// *************************************************************************
void VM_FileIO::Save_FileHistory()
{

	//	WriteRecentFiles = 0;

	char buf[1024];
	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Vima19.ini");


	WriteRecentFiles = fopen(buf, "wt");

	if (!WriteRecentFiles)
	{
		App->Say("Why Cant Find Recent Files");
		return;
	}

	// Save out to RecentFile.ini
	for (unsigned int i = 0; i < EQUITY_NUM_RECENT_FILES; ++i)
	{
		char szName[1024];
		strcpy(szName, mPreviousFiles[i].c_str());

		fprintf(WriteRecentFiles, "%s\n", szName);
	}

	fclose(WriteRecentFiles);
	return;
}
// *************************************************************************
// *					RecentFileHistory_Update Terry Bernie			   *
// *************************************************************************
void VM_FileIO::RecentFileHistory_Update()
{
	if (!mHistoryMenu)return;

	std::string sz = std::string(App->CL_Vm_Model->Path_FileName);
	if (mPreviousFiles[EQUITY_NUM_RECENT_FILES - 1] == sz)return;

	// add the new file to the list of recent files
	for (unsigned int i = 0; i < EQUITY_NUM_RECENT_FILES - 1; ++i)
	{
		mPreviousFiles[i] = mPreviousFiles[i + 1];
	}

	mPreviousFiles[EQUITY_NUM_RECENT_FILES - 1] = sz;

	// Check for empty slots and gray out
	for (int i = EQUITY_NUM_RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);
		if (Result == 0)
		{
			iFlags = MF_GRAYED | MF_DISABLED;
		}

		ModifyMenu(mHistoryMenu, EQUITY_RECENT_FILE_ID(i),
			MF_STRING | MF_BYCOMMAND | iFlags, EQUITY_RECENT_FILE_ID(i), szText);
	}

	// Save Changes
	Save_FileHistory();

	return;
}
// *************************************************************************
// *			ResentHistory_Clear Terry Bernie Hazel Nathan			   *
// *************************************************************************
void VM_FileIO::ResentHistory_Clear()
{
	App->Cl_Dialogs->YesNo("Delete file history.", "Are you sure all File history will be Deleted Procede.");
	if (App->Cl_Dialogs->Canceled == 1)
	{
		return;
	}

	// Set all slots to <empty>
	for (unsigned int i = 0; i < EQUITY_NUM_RECENT_FILES; ++i)
	{
		mPreviousFiles[i] = std::string("<empty>");
	}

	// Repopulate Menu system
	for (int i = EQUITY_NUM_RECENT_FILES - 1; i >= 0; --i)
	{
		ModifyMenu(mHistoryMenu, EQUITY_RECENT_FILE_ID(i),
			MF_STRING | MF_BYCOMMAND | MF_GRAYED | MF_DISABLED, EQUITY_RECENT_FILE_ID(i), "<empty>");
	}

	// Save Changes
	Save_FileHistory();
}

// *************************************************************************
// *					LoadHistory_Equity Terry Bernie					   *
// *************************************************************************
void VM_FileIO::LoadHistory_Equity()
{
	mPreviousFiles.resize(EQUITY_NUM_RECENT_FILES);

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
	for (unsigned int i = 0; i < EQUITY_NUM_RECENT_FILES; ++i)
	{
		memset(buffer, 0, 1024);
		fgets(buffer, 1024, ReadRecentFiles);

		char Path[1024];
		strcpy(Path, buffer);
		int Len = strlen(Path);
		Path[Len - 1] = 0;

		mPreviousFiles[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	mHistoryMenu = CreateMenu();

	// Check for empty slots and gray out
	for (int i = EQUITY_NUM_RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);
		if (Result == 0)
		{
			iFlags = MF_GRAYED | MF_DISABLED;
		}

		AppendMenu(mHistoryMenu, MF_STRING | iFlags, EQUITY_RECENT_FILE_ID(i), szText);
	}

	ModifyMenu(GetMenu(App->SBC_Equity->MainWindow_Hwnd), ID_FILE_RECENTFILESEQ, MF_BYCOMMAND | MF_POPUP,
		(UINT_PTR)mHistoryMenu, "Recent files");
	return;
}

// *************************************************************************
// *					Search_For_Folder Terry Bernie				 	   *
// *************************************************************************
bool VM_FileIO::Search_For_Folder(char* FolderPath)
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
void VM_FileIO::CheckPath(char *pString, char *FileName)
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
		strcpy(JustFileName, FileName);
	}
	else
	{
		if (Mark == 0 && Test == 1)
		{
			Mark = 1;
			strcpy(JustFileName, (FileName + Mark));
		}
		else
		{
			strcpy(JustFileName, (FileName + Mark) + 1);
		}
	}
}

