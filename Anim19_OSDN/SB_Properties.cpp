/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "resource.h"
#include "SB_Properties.h"


SB_Properties::SB_Properties()
{
}


SB_Properties::~SB_Properties()
{
}

// *************************************************************************
// *				Update_ListView_Player	Terry Bernie 			 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Player()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		//	return 1;
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Player->PlayerName);
	strcat(buff, "   (Player)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_Speed[100];
	char chr_Height[100];
	char chr_StartPosX[100];
	char chr_StartPosY[100];
	char chr_StartPosZ[100];

	sprintf(chr_Speed, "%.3f ", App->SBC_Player->Ground_speed);
	sprintf(chr_Height, "%.3f ", App->SBC_Player->PlayerHeight);

	sprintf(chr_StartPosX, "%.3f ", App->SBC_Player->StartPos.x);
	sprintf(chr_StartPosY, "%.3f ", App->SBC_Player->StartPos.y);
	sprintf(chr_StartPosZ, "%.3f ", App->SBC_Player->StartPos.z);

	const int NUM_ITEMS = 9;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name", grid[1][0] = App->SBC_Player->PlayerName;
	grid[0][1] = "Mode", grid[1][1] = "1st_Person";
	grid[0][2] = " ", grid[1][2] = " ";
	grid[0][3] = "Ground Speed", grid[1][3] = chr_Speed;
	grid[0][4] = "Player Height", grid[1][4] = chr_Height;
	grid[0][5] = " ", grid[1][5] = " ";
	grid[0][6] = "Start Pos_X", grid[1][6] = chr_StartPosX;
	grid[0][7] = "Start Pos_Y", grid[1][7] = chr_StartPosY;
	grid[0][8] = "Start Pos_Z", grid[1][8] = chr_StartPosZ;


	ListView_DeleteAllItems(App->Cl_Properties->Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(App->Cl_Properties->Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(App->Cl_Properties->Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Update_ListView_Player_Physics	Terry Berni		 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Player_Physics()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		//return 1;
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Player->PlayerName);
	strcat(buff, "   (Physics)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_PhysicsType[100];
	strcpy(chr_PhysicsType, "Dynamic");

	char chr_PhysicsShape[100];
	strcpy(chr_PhysicsShape, "Capsule");

	char chr_Mass[100];
	char chr_Radius[100];
	char chr_Height[100];

	sprintf(chr_Mass, "%.3f ", App->SBC_Player->Capsule_Mass);
	//sprintf(chr_Mass,"%.3f ",App->GDSBC_Player->mObject->getGravity().getY());
	sprintf(chr_Radius, "%.3f ", App->SBC_Player->Capsule_Radius);
	sprintf(chr_Height, "%.3f ", App->SBC_Player->Capsule_Height);


	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Name", grid[1][0] = App->SBC_Player->PlayerName;
	grid[0][1] = "Type", grid[1][1] = chr_PhysicsType;
	grid[0][2] = "Shape ", grid[1][2] = chr_PhysicsShape;
	grid[0][3] = " ", grid[1][3] = " ";
	grid[0][4] = "Mass", grid[1][4] = chr_Mass;
	grid[0][5] = "Radius", grid[1][5] = chr_Radius;
	grid[0][6] = "Height", grid[1][6] = chr_Height;

	ListView_DeleteAllItems(App->Cl_Properties->Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(App->Cl_Properties->Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(App->Cl_Properties->Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Edit_Player_Onclick  Terry Bernie					   *
// *************************************************************************
bool SB_Properties::Edit_Player_Onclick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(App->Cl_Properties->Properties_hLV, test, 0, App->Cl_Properties->btext, 20);

	result = strcmp(App->Cl_Properties->btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Player->PlayerName);

		App->Cl_Dialogs->Dialog_Text(1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		// Needs Duplicate Name test 
		strcpy(App->SBC_Player->PlayerName, App->Cl_Dialogs->Chr_Text);

		App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Player();
	}

	result = strcmp(App->Cl_Properties->btext, "Ground Speed");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Player->Ground_speed);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Ground Speed");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Player->Ground_speed = App->Cl_Dialogs->mFloat;
		Update_ListView_Player();

		return 1;
	}

	result = strcmp(App->Cl_Properties->btext, "Player Height");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Player->PlayerHeight);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Height");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Player->PlayerHeight = App->Cl_Dialogs->mFloat;
		Update_ListView_Player();
		return 1;
	}

	result = strcmp(App->Cl_Properties->btext, "Start Pos_X");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Player->StartPos.x);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos X");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Player->StartPos.x = App->Cl_Dialogs->mFloat;
		//App->Cl_Scene_Data->S_Player_Locations[0]->Current_Position.x = App->Cl_Dialogs->mFloat;
		//App->Cl_Scene_Data->S_Player_Locations[0]->Physics_Position.setX(App->Cl_Dialogs->mFloat);
		Update_ListView_Player();

		App->Cl_Bullet->Reset_Physics();
		return 1;
	}

	result = strcmp(App->Cl_Properties->btext, "Start Pos_Y");
	if (result == 0)
	{

		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Player->StartPos.y);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos Y");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Player->StartPos.y = App->Cl_Dialogs->mFloat;
		//App->Cl_Scene_Data->S_Player_Locations[0]->Current_Position.y = App->Cl_Dialogs->mFloat;
		//App->Cl_Scene_Data->S_Player_Locations[0]->Physics_Position.setY(App->Cl_Dialogs->mFloat);
		Update_ListView_Player();

		App->Cl_Bullet->Reset_Physics();
		return 1;
	}

	result = strcmp(App->Cl_Properties->btext, "Start Pos_Z");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Player->StartPos.z);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);

		strcpy(App->Cl_Dialogs->btext, "Player Start Pos Z");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Player->StartPos.z = App->Cl_Dialogs->mFloat;
		//App->Cl_Scene_Data->S_Player_Locations[0]->Current_Position.z = App->Cl_Dialogs->mFloat;
		//App->Cl_Scene_Data->S_Player_Locations[0]->Physics_Position.setZ(App->Cl_Dialogs->mFloat);
		Update_ListView_Player();

		App->Cl_Bullet->Reset_Physics();

		return 1;
	}

	return 1;
}

// *************************************************************************
// *				Update_ListView_Camera	Terry Bernie 			 	   *
// *************************************************************************
bool SB_Properties::Update_ListView_Camera()
{
	if (App->Cl_Scene_Data->SceneLoaded == 0)
	{
		//	return 1;
	}

	int index = App->Cl_Properties->Current_Selected_Object;

	char buff[255];
	strcpy(buff, App->SBC_Player->PlayerName);
	strcat(buff, "   (Camera)");
	SetDlgItemText(App->Cl_Properties->Properties_Dlg_hWnd, IDC_STOBJECTNAME, (LPCTSTR)buff);

	char chr_Pos_X[100];
	char chr_Pos_Y[100];
	char chr_Pos_Z[100];

	char chr_LookAT_X[100];
	char chr_LookAT_Y[100];
	char chr_LookAT_Z[100];
	
	sprintf(chr_Pos_X, "%.3f ", App->SBC_Camera->CamPos_X);
	sprintf(chr_Pos_Y, "%.3f ", App->SBC_Camera->CamPos_Y);
	sprintf(chr_Pos_Z, "%.3f ", App->SBC_Camera->CamPos_Z);

	sprintf(chr_LookAT_X, "%.3f ", App->SBC_Camera->LookAt_X);
	sprintf(chr_LookAT_Y, "%.3f ", App->SBC_Camera->LookAt_Y);
	sprintf(chr_LookAT_Z, "%.3f ", App->SBC_Camera->LookAt_Z);


	const int NUM_ITEMS = 7;
	const int NUM_COLS = 2;
	std::string grid[NUM_COLS][NUM_ITEMS]; // string table
	LV_ITEM pitem;
	memset(&pitem, 0, sizeof(LV_ITEM));
	pitem.mask = LVIF_TEXT;

	grid[0][0] = "Pos_X",		grid[1][0] = chr_Pos_X;
	grid[0][1] = "Pos_Y",		grid[1][1] = chr_Pos_Y;
	grid[0][2] = "Pos_Z",		grid[1][2] = chr_Pos_Z;
	grid[0][3] = " ",			grid[1][3] = " ";
	grid[0][4] = "LookAt_X",	grid[1][4] = chr_LookAT_X;
	grid[0][5] = "LookAt_Y",	grid[1][5] = chr_LookAT_Y;
	grid[0][6] = "LookAt_Z",	grid[1][6] = chr_LookAT_Z;
	

	ListView_DeleteAllItems(App->Cl_Properties->Properties_hLV);

	for (DWORD row = 0; row < NUM_ITEMS; row++)
	{
		pitem.iItem = row;
		pitem.pszText = const_cast<char*>(grid[0][row].c_str());
		ListView_InsertItem(App->Cl_Properties->Properties_hLV, &pitem);

		//ListView_SetItemText

		for (DWORD col = 1; col < NUM_COLS; col++)
		{
			ListView_SetItemText(App->Cl_Properties->Properties_hLV, row, col,
				const_cast<char*>(grid[col][row].c_str()));
		}
	}

	return 1;
}

// *************************************************************************
// *				Edit_Camera_Onclick  Terry Bernie					   *
// *************************************************************************
bool SB_Properties::Edit_Camera_Onclick(LPARAM lParam)
{
	int Index = App->Cl_Properties->Current_Selected_Object; // Get Selected Object Index 
	int result = 1;
	int test;

	LPNMLISTVIEW poo = (LPNMLISTVIEW)lParam;
	test = poo->iItem;
	ListView_GetItemText(App->Cl_Properties->Properties_hLV, test, 0, App->Cl_Properties->btext, 20);

	result = strcmp(App->Cl_Properties->btext, "Name");
	if (result == 0)
	{
		strcpy(App->Cl_Dialogs->btext, "Change Object Name");
		strcpy(App->Cl_Dialogs->Chr_Text, App->SBC_Player->PlayerName);

		App->Cl_Dialogs->Dialog_Text(1);

		if (App->Cl_Dialogs->Canceled == 1)
		{
			return TRUE;
		}

		// Needs Duplicate Name test 
		strcpy(App->SBC_Player->PlayerName, App->Cl_Dialogs->Chr_Text);

		App->Cl_FileView->ChangeItem_Name(NULL, App->Cl_Dialogs->Chr_Text);
		Update_ListView_Player();
	}

	result = strcmp(App->Cl_Properties->btext, "Pos_X");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->CamPos_X);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Position X");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->CamPos_X = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}

	result = strcmp(App->Cl_Properties->btext, "Pos_Y");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->CamPos_Y);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Position Y");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->CamPos_Y = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}

	result = strcmp(App->Cl_Properties->btext, "Pos_Z");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->CamPos_Z);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Position Z");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->CamPos_Z = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}

	result = strcmp(App->Cl_Properties->btext, "LookAt_X");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->LookAt_X);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Look At X");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->LookAt_X = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}

	result = strcmp(App->Cl_Properties->btext, "LookAt_Y");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->LookAt_Y);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Look At Y");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->LookAt_Y = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}
	
	result = strcmp(App->Cl_Properties->btext, "LookAt_Z");
	if (result == 0)
	{
		char chr_Value[10];
		sprintf(chr_Value, "%.3f ", App->SBC_Camera->LookAt_Z);

		strcpy(App->Cl_Dialogs->Chr_Float, chr_Value);
		strcpy(App->Cl_Dialogs->btext, "Look At Z");

		App->Cl_Dialogs->Dialog_Float();
		if (App->Cl_Dialogs->Canceled == 1) { return TRUE; }

		App->SBC_Camera->LookAt_Z = App->Cl_Dialogs->mFloat;
		Update_ListView_Camera();

		return 1;
	}

	return 1;
}
