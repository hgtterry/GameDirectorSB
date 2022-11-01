/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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

#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_LookUps.h"

#pragma warning( disable : 4172) // returning address of local variable or temporary: strcat2

GD19_LookUps::GD19_LookUps(void)
{
}

GD19_LookUps::~GD19_LookUps(void)
{
}

// *************************************************************************
// *	  			Check_Objects_CheckNames Terry Bernie				   *
// *************************************************************************
int GD19_LookUps::Check_Objects_CheckNames(char* Name)
{
	/*int Count = 0;
	int Total = App->Cl_Scene_Data->ObjectCount;
	while (Count < Total)
	{
		if (App->Cl_Scene_Data->Cl_Object[Count]->Deleted == 0)
		{
			int Result = 1;
			Result = strcmp(App->Cl_Scene_Data->Cl_Object[Count]->Name, Name);

			if (Result == 0)
			{
				return 1;
			}
		}
		Count++;
	}*/
	return 0;
}

// *************************************************************************
// *	  			Player_Location_CheckNames Terry Bernie				   *
// *************************************************************************
int GD19_LookUps::Player_Location_CheckNames(char* Name)
{
	int Count = 0;
	int Total = App->SBC_Scene->Player_Location_Count;
	while (Count < Total)
	{
		if (App->SBC_Scene->B_Locations[Count]->Deleted == 0)
		{
			int Result = 1;
			Result = strcmp(App->SBC_Scene->B_Locations[Count]->Name, Name);

			if (Result == 0)
			{
				return 1;
			}
		}
		Count++;
	}
	return 0;
}

// *************************************************************************
// *	  			Player_Location_GetIndex_ByName Terry Bernie		   *
// *************************************************************************
int GD19_LookUps::Player_Location_GetIndex_ByName(char* Name)
{
	int Count = 0;
	int Total = App->SBC_Scene->Player_Location_Count;
	while (Count < Total)
	{
		if (App->SBC_Scene->B_Locations[Count]->Deleted == 0)
		{
			int Result = 1;
			Result = strcmp(App->SBC_Scene->B_Locations[Count]->Name, Name);

			if (Result == 0)
			{
				return Count;
				break;
			}
		}
		Count++;
	}
	return -1;
}

// *************************************************************************
// *	  			Player_Location_GetCount Terry Bernie				   *
// *************************************************************************
int GD19_LookUps::Player_Location_GetCount(void)
{
	int RealCount = 0;
	int Count = 0;
	int Total = App->SBC_Scene->Player_Location_Count;

	while (Count < Total)
	{
		if (App->SBC_Scene->B_Locations[Count]->Deleted == 0)
		{
			RealCount++;
		}
		Count++;
	}
	return RealCount;
}

// *************************************************************************
// *	  			Stock_Sound_GetCount Terry Bernie					   *
// *************************************************************************
int GD19_LookUps::Stock_Sound_GetCount(void)
{
	int RealCount = 0;
	int Count = 0;
	int Total = 0;// App->Cl_Scene_Data->Stock_Sound_Count;

	while (Count < Total)
	{
		/*if (App->Cl_Scene_Data->St_Sounds[Count]->Deleted == 0)
		{
			RealCount++;
		}*/
		Count++;
	}
	return RealCount;
}

// *************************************************************************
// *	  					Check_Usage Terry							   *
// *************************************************************************
bool GD19_LookUps::Check_Usage(int Index)
{
	//char Selected_Object_Name[1024];

	//strcpy(Selected_Object_Name, App->Cl_Scene_Data->Cl_Object[Index]->Name);
	//bool Delete_It = 0;
	//
	//// check movers
	//int Count = 0;
	//while (Count < App->Cl_Scene_Data->ObjectCount)
	//{
	//	if (App->Cl_Scene_Data->Cl_Object[Count]->Deleted == 0)
	//	{
	//		if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Move)
	//		{
	//			char Mover_Name[1024];
	//			strcpy(Mover_Name, App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Object_Name);

	//			int Result = 1;
	//			Result = strcmp(Selected_Object_Name, Mover_Name);

	//			if (Result == 0)
	//			{
	//				Delete_It = 0;
	//				return 0;
	//			}
	//			else
	//			{
	//				Delete_It = 1;
	//			}

	//		}
	//	}

	//	Count++;
	//}
	
	return 1;
}

// *************************************************************************
// *	  					GetIndex_From_ID Terry						   *
// *************************************************************************
int GD19_LookUps::GetIndex_From_ID(int Object_ID)
{
	/*int Count = 0;
	while (Count < App->Cl_Scene_Data->ObjectCount)
	{
		if (App->Cl_Scene_Data->Cl_Object[Count]->Deleted == 0)
		{
			
			if (App->Cl_Scene_Data->Cl_Object[Count]->Object_ID == Object_ID)
			{
				
				return Count;
			}
		}

		Count++;
	}*/

	return -1;
}

// *************************************************************************
// *	  			Get_AdjustedCoun Terry Bernie						   *
// *************************************************************************
int GD19_LookUps::Get_AdjustedCount(void)
{
	int New_Count = 0;
	/*int Count = 0;
	int Total = App->Cl_Scene_Data->ObjectCount;
	while (Count < Total)
	{
		if (App->Cl_Scene_Data->Cl_Object[Count]->Deleted == 0)
		{
			New_Count++;
		}
		Count++;
	}*/
	return New_Count;
}


