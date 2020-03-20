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

	int Result = App->Cl_File_IO->Vm_OpenFile("RF Actor   *.act\0*.act\0", "RF Actor", NULL);
	if (Result == 0)
	{
		return 1;
	}

	App->Say("Genesis");

	/*App->Cl_Ogre->Loading_Text("Loading Data", 1);

	Clear_Model();

	App->CL_Model_Data->Set_Paths();

	App->CL_Genesis_Import->LoadActor();

	App->CL_Model_Data->Model_Type = LoadedFile_Actor;

	Set_Equity();

	App->CL_Model_Data->Model_Loaded = 1;

	App->Cl_Grid->Zoom();

	App->Cl_Ogre->Loading_Text("Loading Finished", 0);*/

	return 1;
}