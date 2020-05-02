#include "stdafx.h"
#include "GD19_App.h"
#include "VM_Exporter.h"


VM_Exporter::VM_Exporter()
{
}


VM_Exporter::~VM_Exporter()
{
}

// *************************************************************************
// *					Actor_Model Terry Bernie						   *
// *************************************************************************
void VM_Exporter::Actor_Model(void)
{
	if (App->CL_Vm_Model->Model_Loaded == 0)
	{
		App->Say("No Model Loaded to Export");
		return;
	}

	strcpy(App->CL_Vm_FileIO->BrowserMessage, "Select Folder To Place Decompiled Files a sub folder will be created");
	int Test = App->CL_Vm_FileIO->StartBrowser("");

	if (Test == 0)
	{
		return;
	}



	App->CL_Vm_Genesis3D->Export_As_Actor();

	App->Say("RF Actor Saved successfully");
}
