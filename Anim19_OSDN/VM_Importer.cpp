#include "stdafx.h"
#include "GD19_App.h"
#include "VM_Importer.h"


VM_Importer::VM_Importer()
{
}


VM_Importer::~VM_Importer()
{
}

// *************************************************************************
// *						Genesis3D Terry Terry Berine				   *
// *************************************************************************
bool VM_Importer::Genesis3D_Loader(void)
{

	int Result = App->CL_Vm_FileIO->Vm_OpenFile("RF Actor   *.act\0*.act\0", "RF Actor", NULL);
	if (Result == 0)
	{
		return 1;
	}

	App->CL_Vm_Model->Clear_ModelData();

	App->CL_Vm_Model->Set_Paths();

	App->CL_Vm_Genesis3D->Import_LoadActor();

	App->CL_Vm_Model->Model_Type = LoadedFile_Actor;

	App->CL_Vm_Model->Model_Loaded = 1;

	

	//App->Cl_Grid->Zoom();

	return 1;
}

// *************************************************************************
// *					Reload_FromResentFiles Terry Bernie				   *
// *************************************************************************
void VM_Importer::Reload_FromResentFiles(char* ResentPathAndFile)
{

	// Check Recent File Exsists
	bool Result = App->CL_Vm_FileIO->Search_For_Folder(ResentPathAndFile);
	if (Result == 0)
	{
		App->Say(" Can Not Find File:- This may be due to it has been deleted or renamed");
		return;
	}


	
	App->CL_Vm_Model->Clear_ModelData();

	strcpy(App->CL_Vm_FileIO->Model_Path_FileName, ResentPathAndFile);

	char mPathAndFile[1024];
	char mJustFileName[1024];

	strcpy(mPathAndFile, ResentPathAndFile); // Full Path and File

	App->CL_Vm_FileIO->CheckPath(mPathAndFile, mPathAndFile);
	strcpy(mJustFileName, App->CL_Vm_FileIO->JustFileName); // Just File Name

	strcpy(App->CL_Vm_FileIO->Model_FileName, mJustFileName);

	App->CL_Vm_Model->Set_Paths();

	//_chdir(App->CL_Model_Data->Model_FullPath);

	//--------------------------------------------------------------- Genesis Actor
	if (_stricmp(mJustFileName + strlen(mJustFileName) - 4, ".act") == 0)
	{
		App->CL_Vm_Genesis3D->Import_LoadActor();

		App->CL_Vm_Model->Model_Type = LoadedFile_Actor;

		App->CL_Vm_Model->Model_Loaded = 1;

		//App->Cl_Grid->Zoom();
		
		return;
	}

}