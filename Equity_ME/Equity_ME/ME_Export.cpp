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
