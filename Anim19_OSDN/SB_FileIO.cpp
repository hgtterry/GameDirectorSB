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
#include "SB_FileIO.h"


SB_FileIO::SB_FileIO()
{
	Project_File_Name[0] = 0;
	Project_Path_File_Name[0] = 0;
}


SB_FileIO::~SB_FileIO()
{
}

// *************************************************************************
// *					Open_Project_File Terry Flanigan				   *
// *************************************************************************
bool SB_FileIO::Open_Project_File(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(Project_File_Name, "");
	strcpy(Project_Path_File_Name, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Project_Path_File_Name;						// full path and file name
	ofn.nMaxFile = sizeof(Project_Path_File_Name);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = Project_File_Name;						// Just File Name
	ofn.nMaxFileTitle = sizeof(Project_File_Name);
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