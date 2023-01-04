/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Com_Teleports.h"

SB_Com_Teleports::SB_Com_Teleports()
{
}

SB_Com_Teleports::~SB_Com_Teleports()
{
}

// *************************************************************************
// *	  Set_Teleports_Defaults:- Terry and Hazel Flanigan 2022	 	   *
// *************************************************************************
void SB_Com_Teleports::Set_Teleports_Defaults(int Index)
{
	float x = 0;
	float y = 0;
	float z = 0;

	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Location_ID = 0;

	strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Name, "Start_Location");

	strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Sound_File, "magicspell.ogg");
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->SndVolume = 0.5;
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Play = 1;

	x = App->SBC_Scene->B_Player[0]->StartPos.x;
	y = App->SBC_Scene->B_Player[0]->StartPos.y;
	z = App->SBC_Scene->B_Player[0]->StartPos.z;

	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Physics_Position = btVector3(x, y, z);
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Physics_Rotation = App->SBC_Scene->B_Player[0]->Physics_Rotation;

	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Trigger_Value = 0;
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Counter_ID = 0;
	strcpy(App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Counter_Name, "None");
	App->SBC_Scene->B_Object[Index]->S_Teleport[0]->Counter_Disabled = 1;
}
