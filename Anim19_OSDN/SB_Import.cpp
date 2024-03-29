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
	Quick_Load_Flag = 0;
}


SB_Import::~SB_Import()
{
}

// *************************************************************************
// *						Load_Project Terry Flanigan   				   *
// *************************************************************************
bool SB_Import::Load_Project(char* Extension, char* Extension2)
{

	int Result = App->SBC_FileIO->Open_Project_File(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	bool test = App->SBC_Project->Load_Project();

	App->SBC_TopTabs->Project_Loaded_Reset();
	App->CL_Ogre->RenderFrame();
	
	if (test == 1)
	{
		App->Say("Project Loaded");
	}
	else
	{
		App->Say("Project Failed to Load");
	}
	
	return 1;
}

// *************************************************************************
// *						Room_Loader Terry Bernie					   *
// *************************************************************************
bool SB_Import::Room_Loader(char* Extension, char* Extension2)
{
	int Result = App->SBC_FileIO->Open_Project_File(Extension, Extension2, NULL);
	if (Result == 0)
	{
		return 1;
	}

	return 1;
}

// *************************************************************************
// *					Reload_FromResentFiles Terry Bernie				   *
// *************************************************************************
void SB_Import::Reload_FromResentFiles(char* ResentPathAndFile)
{

	// Check Recent File Exsists
	bool Result = App->SBC_FileIO->Check_File_Exist(ResentPathAndFile);
	if (Result == 0)
	{
		App->Say(" Can Not Find File:- This may be due to it has been deleted or renamed");
		return;
	}

	strcpy(App->SBC_FileIO->Project_Path_File_Name, ResentPathAndFile);

	std::string mJustFileName = App->Cl_Utilities->Get_FileName_From_Path(ResentPathAndFile);

	strcpy(App->SBC_FileIO->Project_File_Name, mJustFileName.c_str());

	bool test = App->SBC_Project->Load_Project();

	App->CL_Prefs->Update_User_File(ResentPathAndFile);

	App->SBC_TopTabs->Project_Loaded_Reset();
	App->CL_Ogre->RenderFrame();
	
	if (Quick_Load_Flag == 0)
	{
		if (test == 1)
		{
			App->Say("Project Loaded");
		}
		else
		{
			App->Say("Project Failed to Load");
		}
	}

}

