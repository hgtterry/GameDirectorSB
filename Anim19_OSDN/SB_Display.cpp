/*
Copyright (c) 2021 EquitySB and EquityME -- HGTO Software W.T.Flanigan H.C.Flanigan

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

:- Terry and Hazel Flanigan 2022

*/

#include "stdafx.h"
#include "GD19_App.h"
#include "SB_Display.h"

SB_Display::SB_Display()
{
}

SB_Display::~SB_Display()
{
}

// *************************************************************************
//			Set_Counter_Defaults:- Terry and Hazel Flanigan 2022	  	   *
// *************************************************************************
void SB_Display::Set_Counter_Defaults(int Index)
{
	strcpy(App->SBC_Scene->B_Panel[Index]->Panel_Name, "Not_Set");
	App->SBC_Scene->B_Panel[Index]->PosX = 250;
	App->SBC_Scene->B_Panel[Index]->PosY = 10;

	App->SBC_Scene->B_Panel[Index]->Deleted = 0;
	App->SBC_Scene->B_Panel[Index]->Show_Panel_Flag = 0;
	App->SBC_Scene->B_Panel[Index]->Unique_ID = 0;

	strcpy(App->SBC_Scene->B_Panel[Index]->Text, "Score:= ");

	return;
}

// *************************************************************************
// *			Add_New_Counter:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Display::Add_New_Counter()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Counters_Count;

	App->SBC_Scene->B_Panel[Index] = new Base_Panel();
	App->SBC_Display->Set_Counter_Defaults(Index);

	strcpy_s(B_Name, "Counter_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Panel[Index]->Panel_Name, B_Name);

	App->SBC_Scene->B_Panel[Index]->Unique_ID = App->SBC_Scene->UniqueID_Counters_Count;

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Counters_Folder, App->SBC_Scene->B_Panel[Index]->Panel_Name, Index, true);
	App->SBC_Scene->B_Panel[Index]->FileViewItem = Temp;

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Display_Folder);
	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Counters_Folder);

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Panel[Index]->FileViewItem);
	
	App->SBC_Scene->B_Panel[Index]->Set_ImGui_Panel_Name();

	App->SBC_Scene->UniqueID_Counters_Count++;
	App->SBC_Scene->Counters_Count++;
	
}

// *************************************************************************
//			Add_Counters_From_File:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool SB_Display::Add_Counters_From_File() // From File
{

	int Counters_Count = App->SBC_Scene->Counters_Count;
	int Count = 0;

	while (Count < Counters_Count)
	{
		
		HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Counters_Folder, App->SBC_Scene->B_Panel[Count]->Panel_Name, Count, false);
		App->SBC_Scene->B_Panel[Count]->FileViewItem = Temp;

		Count++;
	}

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Display_Folder);
	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Counters_Folder);

	return 1;
}

// **************************************************************************
// *	  		Delete_Counter:- Terry and Hazel Flanigan 2022				*
// **************************************************************************
void SB_Display::Delete_Counter()
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	App->SBC_Scene->B_Panel[Index]->Deleted = 1;
	
	App->SBC_FileView->DeleteItem();

	App->SBC_Scene->Scene_Modified = 1;
}

// *************************************************************************
// *					Mark_As_Altered Terry Bernie				 	   *
// *************************************************************************
void SB_Display::Mark_As_Altered(int Index)
{
	App->SBC_Scene->B_Panel[Index]->Altered = 1;

	App->SBC_Scene->Scene_Modified = 1;

	App->SBC_FileView->Mark_Altered(App->SBC_Scene->B_Panel[Index]->FileViewItem);
}
