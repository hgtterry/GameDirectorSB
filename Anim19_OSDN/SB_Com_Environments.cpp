/*
Copyright (c) 2021 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Com_Environments.h"

SB_Com_Environments::SB_Com_Environments()
{
}

SB_Com_Environments::~SB_Com_Environments()
{
}

// *************************************************************************
// *			Add_New_Environment:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
void SB_Com_Environments::Add_New_Environment()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Environment_Count;

	App->SBC_Scene->B_Environment[Index] = new Base_Environment();
	App->SBC_Scene->B_Environment[Index]->Set_Environment_Defaults();

	strcpy_s(B_Name, "Environment_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Environment[Index]->Name, B_Name);

	App->SBC_Scene->B_Environment[Index]->This_Object_ID = App->SBC_Scene->UniqueID_Environment_Count;

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Environments_Folder, App->SBC_Scene->B_Environment[Index]->Name, Index, true);
	App->SBC_Scene->B_Environment[Index]->FileViewItem = Temp;

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Environments_Folder);

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Environment[Index]->FileViewItem);

	Mark_As_Altered(Index);

	App->SBC_Scene->UniqueID_Environment_Count++;
	App->SBC_Scene->Environment_Count++;
}

// *************************************************************************
// *			Mark_As_Altered:- Terry and Hazel Flanigan 2022		 	   *
// *************************************************************************
void SB_Com_Environments::Mark_As_Altered(int Index)
{
	App->SBC_Scene->B_Environment[Index]->Altered = 1;

	App->SBC_Scene->Scene_Modified = 1;

	App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Environment[Index]->FileViewItem);
}

// *************************************************************************
// *	Add_Environments_From_File:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Com_Environments::Add_Environments_From_File() // From File
{

	int Environments_Count = App->SBC_Scene->Environment_Count;
	int Count = 0;

	while (Count < Environments_Count)
	{

		HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Environments_Folder, App->SBC_Scene->B_Environment[Count]->Name, Count, false);
		App->SBC_Scene->B_Environment[Count]->FileViewItem = Temp;

		Count++;
	}

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Environments_Folder);

	return 1;
}
