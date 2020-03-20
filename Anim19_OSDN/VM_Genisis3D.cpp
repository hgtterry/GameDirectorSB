/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "VM_Genisis3D.h"
#include "stdio.h"
#include "stdarg.h"


VM_Genisis3D::VM_Genisis3D()
{
	ActorDef_Memory =	nullptr;
	ActorBody_Memory =	nullptr;
	TestActor =			nullptr;
}


VM_Genisis3D::~VM_Genisis3D()
{
}

// *************************************************************************
// *						LoadActor Terry Bernie					 	   *
// *************************************************************************
void VM_Genisis3D::LoadActor(void)
{

	AddActor(App->CL_Vm_Model->Path_FileName);

	//SetCounters();

	////	ListMotions();

	//GetDefaultBones();

	//LoadActorTextures();

	//GetBoundingBoxModel_Create();

	//FileView_AddMotions();

	//App->CL_Model_Data->HasMesh = 1;

}

// *************************************************************************
// *						AddActor Terry Bernie	  			  	 	   *
// *************************************************************************
bool VM_Genisis3D::AddActor(char* FileName)
{
	if (TestActor)
	{
		TestActor = nullptr;
	}

	geVFile* HFile;

	HFile = geVFile_OpenNewSystem(NULL, GE_VFILE_TYPE_DOS,
		FileName, NULL, GE_VFILE_OPEN_READONLY);

	if (HFile)
	{
		ActorDef_Memory = geActor_DefCreateFromFile(HFile);

		if (ActorDef_Memory)
		{
			TestActor = geActor_Create(ActorDef_Memory);

			geActor_SetScale(TestActor, 1, 1, 1);

			//BuildActor(TestActor);
			App->Say("Loaded");
		}
		else
		{
			App->Say("Cant Create HFile");
			return 0;
		}
	}

	geVFile_Close(HFile);

	//RenderActor(TestActor->Puppet, TestActor->Pose);

	//Animate(0);

	//GetUVs();

	//Set_Scene();

	return 1;
}
