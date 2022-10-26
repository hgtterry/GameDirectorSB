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
// *			Add_New_Counter:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
void SB_Display::Add_New_Counter()
{
	char B_Name[MAX_PATH];
	char ConNum[MAX_PATH];

	int Index = App->SBC_Scene->Counters_Count;

	App->SBC_Scene->B_Panel[Index] = new Base_Panel();

	strcpy_s(B_Name, "Counter_");
	_itoa(Index, ConNum, 10);
	strcat(B_Name, ConNum);
	strcpy(App->SBC_Scene->B_Panel[Index]->Panel_Name, B_Name);

	App->SBC_Scene->B_Panel[Index]->Unique_ID = App->SBC_Scene->Counters_ID_Count;

	HTREEITEM Temp = App->SBC_FileView->Add_Item(App->SBC_FileView->FV_Counters_Folder, App->SBC_Scene->B_Panel[Index]->Panel_Name, Index, true);
	App->SBC_Scene->B_Panel[Index]->FileViewItem = Temp;

	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Display_Folder);
	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Counters_Folder);

	App->SBC_FileView->SelectItem(App->SBC_Scene->B_Panel[Index]->FileViewItem);
	
	App->SBC_Scene->Counters_Count++;
	App->SBC_Scene->Counters_ID_Count++;
}
