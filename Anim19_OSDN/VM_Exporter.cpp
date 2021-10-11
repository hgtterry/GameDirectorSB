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

// *************************************************************************
// *					Ogre3D_Model Terry Bernie						   *
// *************************************************************************
void VM_Exporter::Ogre3D_Model(void)
{

	if (App->CL_Vm_Model->Model_Loaded == 0)
	{
		App->Say("No Model Loaded to Export");
		return;
	}

	if (App->CL_Vm_Model->Model_Type == LoadedFile_Actor)
	{
		App->Say("Not available for the Actor format just yet.");
		return;
	}

	strcpy(App->CL_Vm_FileIO->BrowserMessage, "Select Folder To Place Ogre Files a sub folder will be created");
	int Test = App->CL_Vm_FileIO->StartBrowser("");

	if (Test == 0) { return; }

	/*if (App->CL_Vm_Model->ItsAnOgreModel == 1)
	{
		App->Cl_Export_Ogre3D->Start_OgreExportOptions();
		if (App->Cl_Export_Ogre3D->ExportOptions_Cancled == 1) { return; }
	}


	if (App->CL_Vm_Model->ItsAnOgreModel == 1)
	{
		App->Cl_Export_Ogre3D->Export_OgreToOgre();
		App->CL_Dialogs->Message("Ogre3D Model Saved successfully");
		return;
	}*/
	//else
	//{
		App->Cl_Vm_Ogre3d->Export_AssimpToOgre();
		App->Say("Ogre3D Model Saved successfully");
	//}
}
