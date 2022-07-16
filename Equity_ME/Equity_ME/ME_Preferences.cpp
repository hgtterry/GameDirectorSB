#include "stdafx.h"
#include "resource.h"
#include "ME_App.h"
#include "ME_Preferences.h"


ME_Preferences::ME_Preferences()
{

	strcpy(Pref_Txl_Path_FileName, "Not_Set");

	strcpy(Pref_WE_JustFileName, "Not_Set");
	strcpy(Pref_WE_Path_FileName, "Not_Set");

	strcpy(Pref_Ogre_JustFileName, "Not_Set");
	strcpy(Pref_Ogre_Path, "Not_Set");

	WriteScene = nullptr;
}


ME_Preferences::~ME_Preferences()
{
}

// *************************************************************************
// *						Read_Preferences Terry Flanigan 			   *
// *************************************************************************
bool ME_Preferences::Read_Preferences()
{
	char chr_Tag1[1024];
	char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	char Preferences_Path[1024];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Preferences.ini");

	App->CL_Ini->SetPathName(Preferences_Path);

	App->CL_Ini->GetString("WE_Fast_Load", "Pref_WE_JustFileName", chr_Tag1, 1024);
	strcpy(Pref_WE_JustFileName, chr_Tag1);

	App->CL_Ini->GetString("WE_Fast_Load", "Pref_WE_Path_FileName", chr_Tag1, 1024);
	strcpy(Pref_WE_Path_FileName, chr_Tag1);

	App->CL_Ini->GetString("WE_Fast_Load", "Pref_Txl_Path_FileName", chr_Tag2, 1024);
	strcpy(Pref_Txl_Path_FileName, chr_Tag2);

	App->CL_Ini->GetString("WE_Fast_Load", "Pref_Ogre_JustFileName", chr_Tag2, 1024);
	strcpy(Pref_Ogre_JustFileName, chr_Tag2);

	App->CL_Ini->GetString("WE_Fast_Load", "Pref_Ogre_Path_FileName", chr_Tag2, 1024);
	strcpy(Pref_Ogre_Path, chr_Tag2);

	return 1;
}

// *************************************************************************
// *						Write_Preferences Terry Flanigan 			   *
// *************************************************************************
bool ME_Preferences::Write_Preferences()
{
	WriteScene = nullptr;

	char Preferences_Path[1024];

	strcpy(Preferences_Path, App->EquityDirecory_FullPath);;
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Data");
	strcat(Preferences_Path, "\\");
	strcat(Preferences_Path, "Preferences.ini");

	WriteScene = fopen(Preferences_Path, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	fprintf(WriteScene, "%s\n", "[WE_Fast_Load]");
	fprintf(WriteScene, "%s%s\n", "Pref_WE_JustFileName=", Pref_WE_JustFileName);
	fprintf(WriteScene, "%s%s\n", "Pref_WE_Path_FileName=", Pref_WE_Path_FileName);
	fprintf(WriteScene, "%s%s\n", "Pref_Txl_Path_FileName=", Pref_Txl_Path_FileName);

	fprintf(WriteScene, "%s%s\n", "Pref_Ogre_JustFileName=", Pref_Ogre_JustFileName);
	fprintf(WriteScene, "%s%s\n", "Pref_Ogre_Path_FileName=", Pref_Ogre_Path);

	fprintf(WriteScene, "%s\n", " ");
	fclose(WriteScene);

	Read_Preferences();
	return 1;
}
