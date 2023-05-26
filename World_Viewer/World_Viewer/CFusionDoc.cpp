#include "stdafx.h"
#include "WV_App.h"
#include "CFusionDoc.h"
#include "level.h"

CFusionDoc::CFusionDoc()
{
	pLevel = NULL;
}

CFusionDoc::~CFusionDoc()
{
}

// *************************************************************************
// *									Load 							   *
// *************************************************************************
bool CFusionDoc::Load(const char* FileName)
{

	Level* NewLevel = NULL;

	NewLevel = App->CL_CLevel->Level_CreateFromFile(FileName);// , & Errmsg, Prefs_GetHeadersList(pPrefs),

	if (NewLevel == NULL)
	{
		App->Say("Cant Create New Level");
		return 0;
	}



	pLevel = NewLevel;

	char buf[MAX_PATH];
	strcpy(buf, FileName);
	App->Say("Loaded", buf);

	return 1;
}

