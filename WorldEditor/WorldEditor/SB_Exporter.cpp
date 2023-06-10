/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "AB_App.h"
#include "SB_Exporter.h"

SB_Exporter::SB_Exporter(void)
{
}

SB_Exporter::~SB_Exporter(void)
{
}

// *************************************************************************
// *			Ogre3D_Model:- Terry and Hazel Flanigan 2023			   *
// *************************************************************************
void SB_Exporter::Ogre3D_Model(void)
{
	if (App->CLSB_Model->Model_Loaded == 0)
	{
		App->Say("No Model Loaded to Export");
		return;
	}

	if (App->CLSB_Model->Model_Type == Enums::LoadedFile_Actor)
	{
		App->Say("Not available for the Actor format just yet.");
		return;
	}

	//App->CL_Export_Ogre3D->Export_AssimpToOgre();
}
