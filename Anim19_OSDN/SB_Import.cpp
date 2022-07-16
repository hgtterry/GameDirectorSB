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
#include "SB_Import.h"


SB_Import::SB_Import()
{
}


SB_Import::~SB_Import()
{
}

// *************************************************************************
// *						Assimp_Loader Terry Bernie					   *
// *************************************************************************
bool SB_Import::Assimp_Loader(char* Extension, char* Extension2)
{
	int Result = App->CL_Vm_FileIO->Vm_OpenFile(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	App->EBC_Model->Clear_ModelData();

	App->CL_Vm_Model->Set_Paths();


	App->Cl_Vm_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;

	bool Test = App->Cl_Vm_Assimp->LoadFile(App->CL_Vm_FileIO->Model_Path_FileName);
	if (Test == 0)
	{
		App->Say("Failed To Load");
		return 0;
	}

	App->CL_Vm_Model->Model_Type = LoadedFile_Assimp;

	//Set_Equity();
	App->SBC_Equity->Set_Equity();

	App->Say("Model Loaded");
	return 1;
}

// *************************************************************************
// *					WorldEditor_Loader Terry Terry Berine			   *
// *************************************************************************
bool SB_Import::WorldEditor_Loader(void)
{
	App->Cl_Vm_WorldEditor->Start_WE_import();
	return 1;
}

// *************************************************************************
// *						Genesis3D Terry Terry Berine				   *
// *************************************************************************
bool SB_Import::Genesis3D_Loader(void)
{

	int Result = App->CL_Vm_FileIO->Vm_OpenFile("RF Actor   *.act\0*.act\0", "RF Actor", NULL);
	if (Result == 0)
	{
		return 1;
	}

	App->EBC_Model->Clear_ModelData();

	App->CL_Vm_Model->Set_Paths();

	bool test = App->CL_Vm_Genesis3D->Import_LoadActor();
	if (test == 0)
	{
		return 0;
	}

	App->CL_Vm_Model->Model_Type = LoadedFile_Actor;

	App->SBC_Equity->Set_Equity();

	App->Say("Model Loaded");

	return 1;
}

// *************************************************************************
// *						Ogre_Loader Terry Bernie					   *
// *************************************************************************
bool SB_Import::Ogre_Loader(char* Extension, char* Extension2)
{

	int Result = App->CL_Vm_FileIO->Vm_OpenFile(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	App->EBC_Model->Clear_ModelData();

	App->CL_Vm_Model->Set_Paths();


	App->CL_Ogre_Import_E15->Load_OgreModel(); // Load Ogre Model

	App->CL_Vm_Model->Model_Type = LoadedFile_Assimp;

	App->SBC_Equity->Set_Equity();

	App->Say("Model Loaded");
	return 1;
}

// *************************************************************************
// *						Room_Loader Terry Bernie					   *
// *************************************************************************
bool SB_Import::Room_Loader(char* Extension, char* Extension2)
{
	int Result = App->CL_Vm_FileIO->Vm_OpenFile(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	//App->EBC_Model->Clear_ModelData();

	//App->CL_Vm_Model->Set_Paths();


	//App->CL_Ogre_Import_E15->Load_OgreModel(); // Load Ogre Model

	//App->CL_Vm_Model->Model_Type = LoadedFile_Assimp;

	//App->SBC_Equity->Set_Equity();

	//App->Say("Model Loaded");
	return 1;
}

// *************************************************************************
// *					Reload_FromResentFiles Terry Bernie				   *
// *************************************************************************
void SB_Import::Reload_FromResentFiles(char* ResentPathAndFile)
{

	// Check Recent File Exsists
	bool Result = App->CL_Vm_FileIO->Search_For_Folder(ResentPathAndFile);
	if (Result == 0)
	{
		App->Say(" Can Not Find File:- This may be due to it has been deleted or renamed");
		return;
	}

	App->EBC_Model->Clear_ModelData();

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

		App->SBC_Equity->Set_Equity();

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

	App->SBC_Equity->Set_Equity();

	App->Say("Model Loaded");

}



// *************************************************************************
// *						Load_Scene Terry Flanigan   				   *
// *************************************************************************
bool SB_Import::Load_Scene(char* Extension, char* Extension2)
{

	int Result = App->CL_Vm_FileIO->Vm_OpenFile(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	App->SBC_Project->Load_Scene();

	App->Say("Scene Loaded");
	return 1;
}
