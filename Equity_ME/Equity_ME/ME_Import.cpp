/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "ME_Import.h"


ME_Import::ME_Import()
{
}


ME_Import::~ME_Import()
{
}

// *************************************************************************
// *						Assimp_Loader Terry Bernie					   *
// *************************************************************************
bool ME_Import::Assimp_Loader(char* Extension, char* Extension2)
{
	int Result = App->CL_FileIO->Open_File_Model(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	//App->EBC_Model->Clear_ModelData();

	//App->CL_Vm_Model->Set_Paths();


	//App->Cl_Vm_Assimp->SelectedPreset = 8 + 8388608 + 64 + aiProcess_PreTransformVertices;

	//bool Test = App->Cl_Vm_Assimp->LoadFile(App->CL_Vm_FileIO->Model_Path_FileName);
	//if (Test == 0)
	//{
	//	App->Say("Failed To Load");
	//	return 0;
	//}

	//App->CL_Vm_Model->Model_Type = LoadedFile_Assimp;

	////Set_Equity();
	//App->SBC_Equity->Set_Equity();

	//App->Say("Model Loaded");
	return 1;
}
