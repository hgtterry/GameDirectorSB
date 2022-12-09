/*
Copyright (c) 2021 EquitySB and EquityME -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_LookUps.h"

SB_LookUps::SB_LookUps(void)
{
	Chr_Type[0] = 0;
	Chr_Shape[0] = 0;
	Chr_Usage[0] = 0;
}

SB_LookUps::~SB_LookUps(void)
{
}

// *************************************************************************
// *			Update_Types:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_LookUps::Update_Types()
{
	int Index = App->SBC_Properties->Current_Selected_Object;

	Get_Type(Index);
	Get_Shape(Index);
	Get_Usage(Index);

	return 0;
}

// *************************************************************************
// *			 Get_Type:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
bool SB_LookUps::Get_Type(int Index)
{
	int Type = 0;

	if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
	{
		Type = App->SBC_Scene->B_Area[Index]->Type;
	}
	else
	{
		Type = App->SBC_Scene->B_Object[Index]->Type;
	}

	

	switch (Type)
	{

	case Enums::Bullet_Type_Dynamic:
	{
		strcpy(Chr_Type, "Dynamic");
		return 1;
	}
	case Enums::Bullet_Type_Static:
	{
		strcpy(Chr_Type, "Static");
		return 1;
	}

	break;

	}

	strcpy(Chr_Type, "None");
	return 0;
}

// *************************************************************************
// *				Get_Shape:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_LookUps::Get_Shape(int Index)
{
	int Shape = 0;

	if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
	{
		Shape = App->SBC_Scene->B_Area[Index]->Shape;
	}
	else
	{
		Shape = App->SBC_Scene->B_Object[Index]->Shape;
	}


	switch (Shape)
	{

	case Enums::Shape_Box:
	{
		strcpy(Chr_Shape, "Box");
		return 1;
	}
	case Enums::Sphere:
	{
		strcpy(Chr_Shape, "Sphere");
		return 1;
	}

	case Enums::Capsule:
	{
		strcpy(Chr_Shape, "Capsule");
		return 1;
	}

	case Enums::Shape_TriMesh:
	{
		strcpy(Chr_Shape, "Triangle Mesh");
		return 1;
	}

	break;

	}

	strcpy(Chr_Shape, "None");
	return 0;
}

// *************************************************************************
// *				Get_Usage:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_LookUps::Get_Usage(int Index)
{
	int Usage = 0;

	if (App->SBC_Properties->Edit_Category == Enums::Edit_Area)
	{
		Usage = App->SBC_Scene->B_Area[Index]->Usage;
	}
	else
	{
		Usage = App->SBC_Scene->B_Object[Index]->Usage;
	}

	switch (Usage)
	{

	case Enums::Usage_Room:
	{
		strcpy(Chr_Usage, "Usage_Room");
		return 1;
	}
	case Enums::Usage_Static:
	{
		strcpy(Chr_Usage, "Usage_Static");
		return 1;
	}

	case Enums::Usage_Dynamic:
	{
		strcpy(Chr_Usage, "Usage_Dynamic");
		return 1;
	}

	case Enums::Usage_Object:
	{
		strcpy(Chr_Usage, "Usage_Object");
		return 1;
	}

	case Enums::Usage_Teleport:
	{
		strcpy(Chr_Usage, "Usage_Teleport");
		return 1;
	}

	case Enums::Usage_Colectable:
	{
		strcpy(Chr_Usage, "Usage_Colectable");
		return 1;
	}

	case Enums::Usage_Message:
	{
		strcpy(Chr_Usage, "Usage_Message");
		return 1;
	}

	case Enums::Usage_Move:
	{
		strcpy(Chr_Usage, "Usage_Move");
		return 1;
	}

	case Enums::Usage_Sound:
	{
		strcpy(Chr_Usage, "Usage_Sound");
		return 1;
	}

	break;

	}

	strcpy(Chr_Usage, "None");
	return 0;
}

// *************************************************************************
// *			Show_Entities:- Terry and Hazel Flanigan 2022	 	 	   *
// *************************************************************************
bool SB_LookUps::Show_Entities(bool YesNo)
{
	/*int Count = 0;
	while (Count < ObjectCount)
	{
		if (Cl_Object[Count]->Deleted == 0)
		{
			if (Cl_Object[Count]->Usage == Enums::Usage_Sound)
			{
				Cl_Object[Count]->OgreNode->setVisible(YesNo);
			}
			if (Cl_Object[Count]->Usage == Enums::Usage_Message)
			{
				Cl_Object[Count]->OgreNode->setVisible(YesNo);
			}
			if (Cl_Object[Count]->Usage == Enums::Usage_Move)
			{
				Cl_Object[Count]->OgreNode->setVisible(YesNo);
			}
			if (Cl_Object[Count]->Usage == Enums::Usage_Teleport)
			{
				Cl_Object[Count]->OgreNode->setVisible(YesNo);
			}
			if (Cl_Object[Count]->Usage == Enums::Usage_Environment)
			{
				Cl_Object[Count]->OgreNode->setVisible(YesNo);
			}
		}
		Count++;
	}*/
	return 1;
}

// *************************************************************************
// *	  	Is_Meshes_Used:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
bool SB_LookUps::Is_Meshes_Used(char* Name)
{
	//int Count = 0;
	//int Total = ObjectCount;

	//if (strcmp(Name, "Sinbad.mesh") == 0) // Needs to be Actual Player Mesh
	//{
	//	return 1;
	//}

	//while (Count < Total)
	//{
	//	if (Cl_Object[Count]->Deleted == 0)
	//	{
	//		int Result = 1;
	//		Result = strcmp(Cl_Object[Count]->MeshName, Name);
	//		if (Result == 0)
	//		{
	//			return 1;
	//		}
	//	}

	//	Count++;
	//}

	return 0;
}

// *************************************************************************
// *		 CheckNames_Objects:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
int SB_LookUps::CheckNames_Objects(char* Name)
{
	int Count = 0;
	int Total = App->SBC_Scene->Object_Count;

	while (Count < Total)
	{
		if (App->SBC_Scene->B_Object[Count]->Deleted == 0)
		{
			int Result = 1;
			Result = strcmp(App->SBC_Scene->B_Object[Count]->Mesh_Name, Name);

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
// *	  Get_Adjusted_Object_Count:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
int SB_LookUps::Get_Adjusted_Object_Count(void)
{
	int New_Count = 0;
	int Count = 0;
	int Total = App->SBC_Scene->Object_Count;

	while (Count < Total)
	{
		if (App->SBC_Scene->B_Object[Count]->Deleted == 0)
		{
			New_Count++;
		}

		Count++;
	}

	return New_Count;
}

// *************************************************************************
// *	  Get_Adjusted_Counters_Count:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
int SB_LookUps::Get_Adjusted_Counters_Count(void)
{
	int New_Count = 0;
	int Count = 0;
	int Total = App->SBC_Scene->Counters_Count;

	while (Count < Total)
	{
		if (App->SBC_Scene->B_Counter[Count]->Deleted == 0)
		{
			New_Count++;
		}

		Count++;
	}

	return New_Count;
}

