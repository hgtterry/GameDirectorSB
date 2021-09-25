#include "stdafx.h"
#include "GD19_App.h"
#include "VM_File_Equity.h"


VM_File_Equity::VM_File_Equity()
{
}


VM_File_Equity::~VM_File_Equity()
{
}

// *************************************************************************
// *							SaveFile		  			  		 	   *
// *************************************************************************
bool VM_File_Equity::SaveFile(char* Extension, char* Title, char* FileName)
{

	mPath_FileName[0] = 0;
	mFileName[0] = 0;

	strcpy(mPath_FileName, FileName);
	strcpy(mFileName, FileName);

	ZeroMemory(&ofn, sizeof(ofn));
	ofn.lStructSize = sizeof(ofn);
	ofn.hwndOwner = App->MainHwnd;
	ofn.hInstance = App->hInst;
	ofn.lpstrFile = mPath_FileName; // Full Path
	ofn.nMaxFile = sizeof(mPath_FileName);
	ofn.lpstrFilter = Extension;
	;
	ofn.nFilterIndex = 1;
	ofn.lpstrFileTitle = mFileName;
	ofn.nMaxFileTitle = sizeof(mFileName); // Just File name
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
// *						WriteData_File Terry Bernie  				   *
// *************************************************************************
bool VM_File_Equity::WriteData_File()
{
	WriteScene = NULL;

	WriteScene = fopen(mPath_FileName, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	fprintf(WriteScene, "%s %s\n", "Equity Model Data File", App->CL_Vm_Model->FileName);
	fprintf(WriteScene, "%s\n", " ");

	fprintf(WriteScene, "%s%i\n", "Vertices = ", App->CL_Vm_Model->VerticeCount);
	fprintf(WriteScene, "%s%i\n", "Faces = ", App->CL_Vm_Model->FaceCount);

	fprintf(WriteScene, "%s\n", " ");

	fprintf(WriteScene, "%s%i\n", "Groups = ", App->CL_Vm_Model->GroupCount);
	
	fclose(WriteScene);
	return 1;
}