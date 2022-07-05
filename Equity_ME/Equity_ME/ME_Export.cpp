/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "ME_App.h"
#include "ME_Export.h"


ME_Export::ME_Export()
{
}


ME_Export::~ME_Export()
{
}

// *************************************************************************
// *					Object_Model Terry Bernie						   *
// *************************************************************************
void ME_Export::Object_Model(void)
{
	if (App->CL_Model->Model_Loaded == 0)
	{
		//App->CL_Dialogs->Message("No Model Loaded to Export");
		App->Say_Win("No Model Loaded to Export");
		return;
	}

	bool test = App->CL_Export_Object->Create_ObjectFile();

	if (test == 1)
	{
		//App->CL_Dialogs->Message("Wavefront Object file Created successfully");
		App->Say_Win("Wavefront Object file Created successfully");
	}
}
