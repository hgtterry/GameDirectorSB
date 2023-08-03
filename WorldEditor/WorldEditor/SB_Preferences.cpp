/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
#include "AB_App.h"
#include "SB_Preferences.h"

SB_Preferences::SB_Preferences(void)
{
	WriteData = nullptr;
}

SB_Preferences::~SB_Preferences(void)
{
}

// *************************************************************************
// *						Read_Preferences Terry Flanigan 			   *
// *************************************************************************
bool SB_Preferences::Read_Preferences()
{
	char chr_Tag1[MAX_PATH];
	chr_Tag1[0] = 0;
	
	char Preferences_Path[MAX_PATH];

	strcpy(Preferences_Path, App->WorldEditor_Directory);
	//strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "PreferencesWE.ini");

	App->Just_Equity = App->CLSB_Ini->GetInt("Equity", "Just_Equity", 0, 10);
	App->New_Equity_Flag = App->CLSB_Ini->GetInt("Equity", "New_Equity", 0, 10);

	return 1;
}

// *************************************************************************
// *						Write_Preferences Terry Flanigan 			   *
// *************************************************************************
bool SB_Preferences::Write_Preferences()
{
	WriteData = nullptr;

	char Preferences_Path[MAX_PATH];

	strcpy(Preferences_Path, App->WorldEditor_Directory);
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "PreferencesWE.ini");

	WriteData = fopen(Preferences_Path, "wt");
	if (!WriteData)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	fprintf(WriteData, "%s\n", "[Equity]");
	fprintf(WriteData, "%s%i\n", "Just_Equity=", App->Just_Equity);
	fprintf(WriteData, "%s%i\n", "New_Equity=", App->New_Equity_Flag);

	fprintf(WriteData, "%s\n", " ");

	//fprintf(WriteData, "%s\n", "[Start_Up]");
	//fprintf(WriteData, "%s%i\n", "Start_FullScreen=", Prefs_FullScreen_Flag);

	fprintf(WriteData, "%s\n", " ");

	/*fprintf(WriteScene, "%s\n", "[WE_Fast_Load]");
	fprintf(WriteScene, "%s%s\n", "Pref_WE_JustFileName=", Pref_WE_JustFileName);
	fprintf(WriteScene, "%s%s\n", "Pref_WE_Path_FileName=", Pref_WE_Path_FileName);
	fprintf(WriteScene, "%s%s\n", "Pref_Txl_Path_FileName=", Pref_Txl_Path_FileName);
	fprintf(WriteScene, "%s%s\n", "Pref_Ogre_JustFileName=", Pref_Ogre_JustFileName);
	fprintf(WriteScene, "%s%s\n", "Pref_Ogre_Path_FileName=", Pref_Ogre_Path);*/

	fprintf(WriteData, "%s\n", " ");
	fclose(WriteData);

	//Read_Preferences();
	return 1;
}
