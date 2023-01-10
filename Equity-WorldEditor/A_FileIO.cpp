// A_FileIO.cpp: implementation of the A_FileIO class.
//
//////////////////////////////////////////////////////////////////////

#include "stdafx.h"
#include "AB_App.h"
#include "A_FileIO.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

A_FileIO::A_FileIO()
{
	FileName[0] = 0;
	PathFileName[0] = 0;
}

A_FileIO::~A_FileIO()
{

}

// *************************************************************************
// *				SaveSelectedFile  09/04/04   						   *
// *************************************************************************
bool A_FileIO::SaveSelectedFile(char* Extension,char* File)
{
	OPENFILENAME ofn;

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = PathFileName;
	ofn.nMaxFile = sizeof(PathFileName);
	ofn.lpstrFilter =Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = FileName;
	ofn.nMaxFileTitle = sizeof(FileName);
	ofn.lpstrInitialDir = File;
	ofn.lpstrTitle = "Save File";

	ofn.Flags = 
		OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |	
		OFN_HIDEREADONLY |
		OFN_OVERWRITEPROMPT ;
	if (GetSaveFileName(&ofn) == TRUE)
	{
		return 1;
	}

	return 0;

}

// *************************************************************************
// *					CheckExtention  09/04/04   					 	   *
// *************************************************************************
bool A_FileIO::CheckExtention(char *FileName)
{
	int ch='.';
	char *IsIt;	
	IsIt=strchr(FileName,ch);	

	if (IsIt==NULL) // if no extension . extension return 0
	{
		return 0;
	}	

	return 1; // file name has an extension return 1;
}
