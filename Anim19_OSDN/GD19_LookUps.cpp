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
	int Total = App->Cl_Scene_Data->Player_Location_Count;
	while (Count < Total)
	{
		if (App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted == 0)
		{
			int Result = 1;
			Result = strcmp(App->Cl_Scene_Data->S_Player_Locations[Count]->Name, Name);

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
	int Total = App->Cl_Scene_Data->Player_Location_Count;
	while (Count < Total)
	{
		if (App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted == 0)
		{
			int Result = 1;
			Result = strcmp(App->Cl_Scene_Data->S_Player_Locations[Count]->Name, Name);

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
	int Total = App->Cl_Scene_Data->Player_Location_Count;

	while (Count < Total)
	{
		if (App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted == 0)
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
	int Total = App->Cl_Scene_Data->Stock_Sound_Count;

	while (Count < Total)
	{
		if (App->Cl_Scene_Data->St_Sounds[Count]->Deleted == 0)
		{
			RealCount++;
		}
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

// *************************************************************************
// *	  			Get_Edit_Category_String Terry Bernie				   *
// *************************************************************************
char* GD19_LookUps::Get_Edit_Category_String(void)
{
	char strcat2[255];
	strcpy(strcat2, "Undifined");

	
		if (App->SBC_Properties->Edit_Category == Enums::Edit_None)
		{
			strcpy(strcat2, "Edit_None");
			return strcat2;
		}
		if (App->SBC_Properties->Edit_Category == Enums::FV_Edit_Object)
		{
			strcpy(strcat2, "Edit_Mesh_Object");
			return strcat2;
		}
		if (App->SBC_Properties->Edit_Category == Enums::Edit_Physics_Object)
		{
			strcpy(strcat2, "Edit_Physics_Object");
			return strcat2;
		}
		if (App->SBC_Properties->Edit_Category == Enums::Edit_Player)
		{
			strcpy(strcat2, "Edit_Player");
			return strcat2;
		}
		if (App->SBC_Properties->Edit_Category == Enums::Edit_Message)
		{
			strcpy(strcat2, "Edit_Message");
			return strcat2;
		}
		if (App->SBC_Properties->Edit_Category == Enums::Edit_Move_Entity)
		{
			strcpy(strcat2, "Edit_Move_Entity");
			return strcat2;
		}

		if (App->SBC_Properties->Edit_Category == Enums::Edit_Sounds)
		{
			strcpy(strcat2, "Edit_Sounds");
			return strcat2;
		}

		if (App->SBC_Properties->Edit_Category == Enums::Edit_Collectable)
		{
			strcpy(strcat2, "Edit_Collectable");
			return strcat2;
		}

		if (App->SBC_Properties->Edit_Category == Enums::Edit_Teleport)
		{
			strcpy(strcat2, "Edit_Teleport");
			return strcat2;
		}

		if (App->SBC_Properties->Edit_Category == Enums::Edit_Environment)
		{
			strcpy(strcat2, "Edit_Environment");
			return strcat2;
		}

		if (App->SBC_Properties->Edit_Category == Enums::Edit_Area_Change)
		{
			strcpy(strcat2, "Edit_Area_Change");
			return strcat2;
		}

		if (App->SBC_Properties->Edit_Category == Enums::Edit_Change_Level)
		{
			strcpy(strcat2, "Edit_Change_Level");
			return strcat2;
		}

		if (App->SBC_Properties->Edit_Category == Enums::Edit_Particles)
		{
			strcpy(strcat2, "Edit_Particles");
			return strcat2;
		}
	
	return strcat2;
}

// *************************************************************************
// *	  			Get_Type_String Terry Bernie						   *
// *************************************************************************
char* GD19_LookUps::Get_Type_Category_String(void)
{
	char strcat2[255];
	/*strcpy(strcat2, "Undifined");

	int index = App->SBC_Properties->Current_Selected_Object;

	if (App->Cl_Scene_Data->Cl_Object[index]->Type == Enums::Bullet_Type_None)
	{
		strcpy(strcat2, "Bullet_Type_None");
		return strcat2;
	}
	if (App->Cl_Scene_Data->Cl_Object[index]->Type == Enums::Bullet_Type_Dynamic)
	{
		strcpy(strcat2, "Bullet_Type_Dynamic");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Type == Enums::Bullet_Type_Static)
	{
		strcpy(strcat2, "Bullet_Type_Static");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Type == Enums::Bullet_Type_TriMesh)
	{
		strcpy(strcat2, "Bullet_Type_TriMesh)");
		return strcat2;
	}
	if (App->Cl_Scene_Data->Cl_Object[index]->Type == Enums::Type_NXS_Convex)
	{
		strcpy(strcat2, "Type_NXS_Convex");
		return strcat2;
	}
	if (App->Cl_Scene_Data->Cl_Object[index]->Type == Enums::Type_JustOgre)
	{
		strcpy(strcat2, "Type_JustOgre");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Type == Enums::Bullet_Type_Volume)
	{
		strcpy(strcat2, "Bullet_Type_Volume");
		return strcat2;
	}*/

	return strcat2;
}

// *************************************************************************
// *	  			Get_Usage_String Terry Bernie						   *
// *************************************************************************
char* GD19_LookUps::Get_Usage_Category_String(void)
{
	char strcat2[255];
	/*strcpy(strcat2, "Undifined");

	int index = App->SBC_Properties->Current_Selected_Object;

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_None)
	{
		strcpy(strcat2, "Usage_None");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Room)
	{
		strcpy(strcat2, "Usage_Room");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Static)
	{
		strcpy(strcat2, "Usage_Static");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Dynamic)
	{
		strcpy(strcat2, "Usage_Dynamic");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Object)
	{
		strcpy(strcat2, "Usage_Object");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Ammo)
	{
		strcpy(strcat2, "Usage_Ammo");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Weapon)
	{
		strcpy(strcat2, "Usage_Weapon");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Teleport)
	{
		strcpy(strcat2, "Usage_Teleport");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_ChangeLevel)
	{
		strcpy(strcat2, "Usage_ChangeLevel");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_MediKit)
	{
		strcpy(strcat2, "Usage_MediKit");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Recevier)
	{
		strcpy(strcat2, "Usage_Recevier");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Particle)
	{
		strcpy(strcat2, "Usage_Particle");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Light)
	{
		strcpy(strcat2, "Usage_Light");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Colectable)
	{
		strcpy(strcat2, "Usage_Colectable");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Message)
	{
		strcpy(strcat2, "Usage_Message");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Move)
	{
		strcpy(strcat2, "Usage_Move");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Sound)
	{
		strcpy(strcat2, "Usage_Sound");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_PlayerDeath)
	{
		strcpy(strcat2, "Usage_PlayerDeath");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Counter)
	{
		strcpy(strcat2, "Usage_Counter");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Player)
	{
		strcpy(strcat2, "Usage_Player");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_Environment)
	{
		strcpy(strcat2, "Usage_Environment");
		return strcat2;
	}

	if (App->Cl_Scene_Data->Cl_Object[index]->Usage == Enums::Usage_RoomChange)
	{
		strcpy(strcat2, "Usage_RoomChange");
		return strcat2;
	}*/

	return strcat2;
}

