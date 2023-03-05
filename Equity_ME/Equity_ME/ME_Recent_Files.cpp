/*
Copyright (c) 2022- 2023 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "resource.h"
#include "ME_App.h"
#include "ME_Recent_Files.h"

ME_Recent_Files::ME_Recent_Files()
{
	ReadRecentFiles = nullptr;
	WriteRecentFiles = nullptr;
}

ME_Recent_Files::~ME_Recent_Files()
{
}

// *************************************************************************
// *						Init_History() Terry Bernie					   *
// *************************************************************************
void ME_Recent_Files::Init_History()
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
		mPreviousFiles_Projects.resize(RECENT_FILES);

		CreateDirectory(DirCheck, NULL);
		ResentHistory_Models_Clear();	// Models
		ResentHistory_Projects_Clear();	// Projects

		Save_FileHistory_Models();
		Save_FileHistory_Projects();

		LoadHistory_Models();
		LoadHistory_Projects();
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
			mPreviousFiles_Projects.resize(RECENT_FILES);

			ResentHistory_Projects_Clear();
			Save_FileHistory_Projects();
			LoadHistory_Projects();
		}

		LoadHistory_Models();
		LoadHistory_Projects();
	}
}

// *************************************************************************
// *		ResentHistory_Models_Clear:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
void ME_Recent_Files::ResentHistory_Models_Clear()
{

	// Set all slots to <empty>
	for (unsigned int i = 0; i < RECENT_FILES; ++i)
	{
		mPreviousFiles_Models[i] = std::string("<empty>");
	}

	// Save Changes
	Save_FileHistory_Models();
}

// *************************************************************************
// *	ResentHistory_Projects_Clear:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
void ME_Recent_Files::ResentHistory_Projects_Clear()
{

	// Set all slots to <empty>
	for (unsigned int i = 0; i < RECENT_FILES; ++i)
	{
		mPreviousFiles_Projects[i] = std::string("<empty>");
	}


	// Save Changes
	Save_FileHistory_Projects();
}

// *************************************************************************
// *		Save_FileHistory_Models:- Terry and Hazel Flanigan 2023		   *
// *************************************************************************
void ME_Recent_Files::Save_FileHistory_Models()
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

	// Save out to Vima19.ini
	for (unsigned int i = 0; i < RECENT_FILES; ++i)
	{
		char szName[MAX_PATH];
		strcpy(szName, mPreviousFiles_Models[i].c_str());

		fprintf(WriteRecentFiles, "%s\n", szName);
	}
	fclose(WriteRecentFiles);

	return;
}

// *************************************************************************
// *		Save_FileHistory_Projects:- Terry and Hazel Flanigan 2023	   *
// *************************************************************************
void ME_Recent_Files::Save_FileHistory_Projects()
{

	WriteRecentFiles = nullptr;

	char buf[MAX_PATH];
	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Projects.ini");

	WriteRecentFiles = fopen(buf, "wt");

	if (!WriteRecentFiles)
	{
		App->Say("Why Cant Find Recent Files");
		return;
	}

	// Save out to Projects.ini
	for (unsigned int i = 0; i < RECENT_FILES; ++i)
	{
		char szName[MAX_PATH];
		strcpy(szName, mPreviousFiles_Projects[i].c_str());

		fprintf(WriteRecentFiles, "%s\n", szName);
	}
	fclose(WriteRecentFiles);

	return;
}

// *************************************************************************
// *					LoadHistory_Models Terry Bernie					   *
// *************************************************************************
void ME_Recent_Files::LoadHistory_Models()
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
// *				LoadHistory_Projects Terry Bernie					   *
// *************************************************************************
void ME_Recent_Files::LoadHistory_Projects()
{
	mPreviousFiles_Projects.resize(RECENT_FILES);

	char buffer[1024];
	char buf[1024];

	strcpy(buf, UserData_Folder);
	strcat(buf, "\\Vima19\\Projects.ini");


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

		mPreviousFiles_Projects[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	// Check for empty slots and gray out
	for (int i = RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[1024];
		strcpy(szText, mPreviousFiles_Projects[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);

	}

	return;
}

// *************************************************************************
// *			RecentFile_Models_History_Update Terry Bernie			   *
// *************************************************************************
void ME_Recent_Files::RecentFile_Models_History_Update()
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
	}

	// Save Changes
	Save_FileHistory_Models();

	return;
}

// *************************************************************************
// *			RecentFile_Project_History_Update Terry Bernie			   *
// *************************************************************************
void ME_Recent_Files::RecentFile_Projects_History_Update()
{

	std::string sz = std::string(App->CL_Model->Path_FileName);
	if (mPreviousFiles_Projects[RECENT_FILES - 1] == sz)return;

	// add the new file to the list of recent files
	for (unsigned int i = 0; i < RECENT_FILES - 1; ++i)
	{
		mPreviousFiles_Projects[i] = mPreviousFiles_Projects[i + 1];
	}

	mPreviousFiles_Projects[RECENT_FILES - 1] = sz;

	// Check for empty slots and gray out
	for (int i = RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[MAX_PATH];
		strcpy(szText, mPreviousFiles_Projects[i].c_str());

		UINT iFlags = 0;
		int Result = 0;
		Result = strcmp("<empty>", szText);
	}

	// Save Changes
	Save_FileHistory_Projects();

	return;
}

// *************************************************************************
// *					LoadHistory_Equity Terry Bernie					   *
// *************************************************************************
void ME_Recent_Files::LoadHistory_Equity()
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
// *	  				List_Recent_Files Terry Flanigan				   *
// *************************************************************************
void ME_Recent_Files::List_Recent_Files(HWND hDlg)
{
	char buf[MAX_PATH];
	char buffer[MAX_PATH];

	mPreviousFiles_Models.resize(RECENT_FILES);

	strcpy(buf, App->CL_Recent_Files->UserData_Folder);
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
void ME_Recent_Files::List_Recent_Projects(HWND hDlg)
{
	char buf[MAX_PATH];
	char buffer[MAX_PATH];

	mPreviousFiles_Projects.resize(RECENT_FILES);

	strcpy(buf, App->CL_Recent_Files->UserData_Folder);
	strcat(buf, "\\Vima19\\Projects.ini");

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

		mPreviousFiles_Projects[i] = std::string(Path);
	}

	fclose(ReadRecentFiles);

	// Check for empty slots and gray out
	for (int i = RECENT_FILES - 1; i >= 0; --i)
	{
		char szText[MAX_PATH];
		strcpy(szText, mPreviousFiles_Projects[i].c_str());

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
// *					Search_For_Folder Terry Bernie				 	   *
// *************************************************************************
bool ME_Recent_Files::Search_For_Folder(char* FolderPath)
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
