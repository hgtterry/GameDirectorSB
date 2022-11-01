#include "StdAfx.h"
#include "resource.h"
#include "GD19_App.h"
#include "GD19_Scene_Data.h"


GD19_Scene_Data::GD19_Scene_Data(void)
{
	strcpy(Data_mFilename, "No Set");
	strcpy(Data_Path_mFilename, "No Set");
} 


GD19_Scene_Data::~GD19_Scene_Data(void)
{
}

// *************************************************************************
// *					Open_Project_Dlg Terry Bernie					   *
// *************************************************************************
bool GD19_Scene_Data::Open_Project_Dlg(char* Extension, char* Title, char* StartDirectory)
{
	strcpy(mFilename, "");
	strcpy(Path_mFilename, "");

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = Path_mFilename;						// full path and file name
	ofn.nMaxFile = sizeof(Path_mFilename);
	ofn.lpstrFilter = Extension;

	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = mFilename;						// Just File Name
	ofn.nMaxFileTitle = sizeof(mFilename);
	ofn.lpstrInitialDir = "";
	ofn.lpstrTitle = Title;
	ofn.Flags = OFN_PATHMUSTEXIST |
		OFN_FILEMUSTEXIST |
		OFN_EXPLORER |
		OFN_HIDEREADONLY |
		OFN_FILEMUSTEXIST;

	if (GetOpenFileName(&ofn) == TRUE)
	{
		strcpy(Data_mFilename, mFilename);
		strcpy(Data_Path_mFilename, Path_mFilename);
		return 1;
	}
	return 0;
}




