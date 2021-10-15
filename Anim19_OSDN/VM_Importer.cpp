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
// *						Assimp_Loader Terry Bernie					   *
// *************************************************************************
bool VM_Importer::Assimp_Loader(char* Extension, char* Extension2)
{
	int Result = App->CL_Vm_FileIO->Vm_OpenFile(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	App->CL_Vm_Model->Clear_ModelData();

	App->CL_Vm_Model->Set_Paths();


	App->Cl_Vm_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;

	bool Test = App->Cl_Vm_Assimp->LoadFile(App->CL_Vm_FileIO->Model_Path_FileName);
	if (Test == 0)
	{
		App->Say("Failed To Load");
		return 0;
	}

	App->CL_Vm_Model->Model_Type = LoadedFile_Assimp;
	
	Set_Equity();

	App->Say("Model Loaded");
	return 1;
}

// *************************************************************************
// *					WorldEditor_Loader Terry Terry Berine			   *
// *************************************************************************
bool VM_Importer::WorldEditor_Loader(void)
{
	App->Cl_Vm_WorldEditor->Start_WE_import();
	return 1;
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

	bool test = App->CL_Vm_Genesis3D->Import_LoadActor();
	if (test == 0)
	{
		return 0;
	}

	App->CL_Vm_Model->Model_Type = LoadedFile_Actor;

	Set_Equity();

	App->Say("Model Loaded");

	return 1;
}

// *************************************************************************
// *						Ogre_Loader Terry Bernie					   *
// *************************************************************************
bool VM_Importer::Ogre_Loader(char* Extension, char* Extension2)
{
	
	int Result = App->CL_Vm_FileIO->Vm_OpenFile(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	App->CL_Vm_Model->Clear_ModelData();

	App->CL_Vm_Model->Set_Paths();


	App->CL_Ogre_Import_E15->Load_OgreModel(); // Load Ogre Model

	App->CL_Vm_Model->Model_Type = LoadedFile_Assimp;

	App->CL_Vm_Model->Model_Loaded = 1;

	App->Cl_Grid->Zoom();
	//Set_Equity();
	
	App->Say("Model Loaded");
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
		//App->CL_Vm_Model->Clear_ModelData();

		bool test = App->CL_Vm_Genesis3D->Import_LoadActor();
		if (test == 0)
		{
			return;
		}

		App->CL_Vm_Model->Model_Type = LoadedFile_Actor;

		Set_Equity();

		App->Say("Model Loaded");
		
		return;
	}


	// Fall through fo assimp
	bool Test = App->Cl_Vm_Assimp->LoadFile(ResentPathAndFile);
	if (Test == 0)
	{
		App->Say("Can Not Load File");
		return;
	}
	
	App->CL_Vm_Model->Model_Type = LoadedFile_Assimp;
	
	Set_Equity();
	
	App->Say("Model Loaded");

}

// *************************************************************************
// *						Set_Equity Terry Bernie						   *
// *************************************************************************
void VM_Importer::Set_Equity(void)
{
	App->CL_Vm_Model->Model_Loaded = 1;

	App->Cl_Grid->Zoom();


	App->CL_Vm_Groups->Update_Groups_Dialog(0);

	App->CL_Vm_TopBar->ToggleTexturesBmp(1);
	App->Set_Main_TitleBar();

	App->Cl19_Ogre->RenderFrame();
}