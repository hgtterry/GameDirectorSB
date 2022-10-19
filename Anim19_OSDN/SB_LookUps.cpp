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
	int Type = App->SBC_Scene->B_Object[Index]->Type;

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
	int Shape = App->SBC_Scene->B_Object[Index]->Shape;

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
	int Usage = App->SBC_Scene->B_Object[Index]->Usage;

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