/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "SB_Collision.h"

SB_Collision::SB_Collision()
{
}

SB_Collision::~SB_Collision()
{
}

// *************************************************************************
// *			Message_Entity:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool SB_Collision::Message_Entity(int Index)
{
	if (App->SBC_Scene->B_Object[Index]->Triggered == 1) // Retrigger Yes No
	{
		return 1;
	}

	if (App->SBC_Scene->B_Object[Index]->Triggered == 1) // Retrigger Yes No
	{
		return 1;
	}

	//-----------------  Do Action
	App->CL_Vm_ImGui->Object_Index = Index;
	App->CL_Vm_ImGui->Show_Test_Text = 1;
	App->SBC_Scene->B_Object[Index]->Triggered = 1;

	return 1;
}

// **************************************************************************
// *				Play_Sound:- Terry and Hazel Flanigan 2022				*
// **************************************************************************
bool SB_Collision::Play_Sound(int Index)
{

	//if (App->Cl_Scene_Data->Cl_Object[Index]->HasSound == 1 && App->Cl_Scene_Data->Cl_Object[Index]->Play_v2 == 1)
	{
		char buff[1024];
		strcpy(buff, App->SBC_SoundMgr->Default_Folder);
		strcat(buff, "\\Media\\Sounds\\");

		strcat(buff, App->SBC_Scene->B_Object[Index]->Sound_File);

		App->SBC_SoundMgr->SndFile = App->SBC_SoundMgr->SoundEngine->play2D(buff, false, true, true);
		App->SBC_SoundMgr->SndFile->setVolume(App->SBC_Scene->B_Object[Index]->SndVolume);
		App->SBC_SoundMgr->SndFile->setIsPaused(false);

		App->SBC_Scene->B_Object[Index]->Triggered = 1;
	}

	return 1;
}
