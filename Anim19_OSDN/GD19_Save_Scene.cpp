#include "StdAfx.h"
#include "GD19_App.h"
#include "GD19_Save_Scene.h"


GD19_Save_Scene::GD19_Save_Scene(void)
{
	strcpy(SceneVersion,"3.0"); // Versioning
	WriteScene = NULL;

	strcpy(New_Scene_File, "");
	strcpy(New_Scene_Path_File, "");

	SubFolder[0] = 0;
	mLevel_Directory[0] = 0;
}


GD19_Save_Scene::~GD19_Save_Scene(void)
{
}

// *************************************************************************
// *						Create_NewScene Terry Bernie  				   *
// *************************************************************************
bool GD19_Save_Scene::Create_NewScene()
{
	int test = App->CL_Vm_FileIO->SaveFileCom("Scene Files   *.GDScene\0*.GDScene\0", "GDScene",NULL);
	if (test == 0) { return 1; }

	strcpy(New_Scene_File, App->CL_Vm_FileIO->mSaveFileCom);
	strcpy(New_Scene_Path_File, App->CL_Vm_FileIO->mSavePathFileCom);

	if (_stricmp(New_Scene_File + strlen(New_Scene_File) - 8, ".GDScene") != 0)
	{
		strcat(New_Scene_File, ".GDScene");
	}

	if (_stricmp(New_Scene_Path_File + strlen(New_Scene_Path_File) - 8, ".GDScene") != 0)
	{
		strcat(New_Scene_Path_File, ".GDScene");
	}

		Write_NewScene();

	return 1;
}

// *************************************************************************
// *						Write_NewScene Terry Bernie  				   *
// *************************************************************************
bool GD19_Save_Scene::Write_NewScene()
{
	WriteScene = NULL;

	WriteScene = fopen(New_Scene_Path_File, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	fprintf(WriteScene, "%s\n", "[GDScene]");
	fprintf(WriteScene, "%s%s\n", "Version=","4.0");
	fprintf(WriteScene, "%s%s\n", "Type=", "Standard");

	// Player
	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Player]");
	fprintf(WriteScene, "%s%s\n", "Name=", App->SBC_Player->Player_Name);
	fprintf(WriteScene, "%s%f,%f,%f\n", "Start_Position=", App->SBC_Player->StartPos.x, App->SBC_Player->StartPos.y, App->SBC_Player->StartPos.z);

	fprintf(WriteScene, "%s%s\n", "Shape=", "Capsule");
	fprintf(WriteScene, "%s%f\n", "Mass=", App->SBC_Player->Capsule_Mass);
	fprintf(WriteScene, "%s%f\n", "Radius=", App->SBC_Player->Capsule_Radius);
	fprintf(WriteScene, "%s%f\n", "Height=", App->SBC_Player->Capsule_Height);


	// Environment
	float x = 0;
	float y = 0;
	float z = 0;

	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Environment]");
	
	// Fog
	fprintf(WriteScene, "%s %i\n", "Fog_Visible=", App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn);
	fprintf(WriteScene, "%s %i\n", "Fog_Mode=", App->Cl_Scene_Data->S_Scene[0]->Fog[0].Mode);

	x = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.x;
	y = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.y;
	z = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.z;

	fprintf(WriteScene, "%s%f,%f,%f\n", "Fog_Colour=", x, y, z);
	fprintf(WriteScene, "%s%f\n", "Fog_Density=", App->Cl_Scene_Data->S_Scene[0]->Fog[0].Density);
	fprintf(WriteScene, "%s%f\n", "Fog_Start=", App->Cl_Scene_Data->S_Scene[0]->Fog[0].Start);
	fprintf(WriteScene, "%s%f\n", "Fog_End=", App->Cl_Scene_Data->S_Scene[0]->Fog[0].End);
	//--------------------------------------------------------
	
	// Light
	x = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.x;
	y = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.y;
	z = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.z;
	fprintf(WriteScene, "%s%f,%f,%f\n", "Light_Ambient=", x, y, z);

	x = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.x;
	y = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.y;
	z = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.z;
	fprintf(WriteScene, "%s%f,%f,%f\n", "Light_Diffuse=", x, y, z);

	x = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.x;
	y = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.y;
	z = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.z;
	fprintf(WriteScene, "%s%f,%f,%f\n", "Light_Specular=", x, y, z);

	x = 0;//App->Cl_Scene_Data->S_Scene[0]->SpecularColour.x;
	y = 0;//App->Cl_Scene_Data->S_Scene[0]->SpecularColour.y;
	z = 0;//App->Cl_Scene_Data->S_Scene[0]->SpecularColour.z;
	fprintf(WriteScene, "%s%f,%f,%f\n", "Light_Position=", x, y, z);
	//--------------------------------------------------------
		// Sound
	fprintf(WriteScene, "%s%s\n", "Sound_Track=", App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFile);
	fprintf(WriteScene, "%s%f\n", "Sound_Volume=", App->Cl_Scene_Data->S_Scene[0]->Sound[0].Volume);
	fprintf(WriteScene, "%s%i\n", "Sound_Play=", App->Cl_Scene_Data->S_Scene[0]->Sound[0].Play);
	fprintf(WriteScene, "%s%i\n", "Sound_Loop=", App->Cl_Scene_Data->S_Scene[0]->Sound[0].Loop);
	//--------------------------------------------------------
	fprintf(WriteScene, "%s%i\n", "Sky_Enabled=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].Enabled);
	fprintf(WriteScene, "%s%i\n", "Sky_Type=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].type);
	fprintf(WriteScene, "%s%s\n", "Sky_Material=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].Material);
	fprintf(WriteScene, "%s%f\n", "Sky_Distance=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].Distance);
	fprintf(WriteScene, "%s%f\n", "Sky_Tiling=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].Tiling);
	fprintf(WriteScene, "%s%f\n", "Sky_Curvature=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].Curvature);

	// Objects
	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Objects]");
	fprintf(WriteScene, "%s%i\n", "Objects_Count=",App->Cl_Scene_Data->ObjectCount);


	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Options]");

	fprintf(WriteScene, "%s%i\n", "Options_Has_Planes=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Planes);
	fprintf(WriteScene, "%s%i\n", "Options_Has_Objects=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Objects);
	fprintf(WriteScene, "%s%i\n", "Options_Has_Particles=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Particles);
	fprintf(WriteScene, "%s%i\n", "Options_Has_Weapons=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Weapons);
	fprintf(WriteScene, "%s%i\n", "Options_Has_Player=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Player);
	fprintf(WriteScene, "%s%i\n", "Options_Has_Debug=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Debug);


	// stock
	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Stock_Message]");
	fprintf(WriteScene, "%s%s\n", "Stock_Message_Count=","0");

	// Sounds
	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Stock_Sound]");
	fprintf(WriteScene, "%s%s\n", "Stock_Sounds_Count=", "0");
	

	fclose(WriteScene);
	return 1;
}

// *************************************************************************
// *					SaveGDScene_40   Terry Bernie  					   *
// *************************************************************************
bool GD19_Save_Scene::SaveGDScene_40(bool AskForFile)
{

	WriteScene = NULL;

	if (AskForFile == 1)
	{
		int test = App->CL_Vm_FileIO->SaveFile("Scene Files   *.GDScene\0*.GDScene\0", "GDScene", App->Cl_Scene_Data->S_Scene[0]->GDSceneName);
		if (test == 0) { return 1; }

		if (_stricmp(App->CL_Vm_FileIO->Full_Path_And_File + strlen(App->CL_Vm_FileIO->Full_Path_And_File) - 8, ".GDScene") != 0)
		{
			strcat(App->CL_Vm_FileIO->Full_Path_And_File, ".GDScene");
		}

		if (_stricmp(App->CL_Vm_FileIO->Just_FileName + strlen(App->CL_Vm_FileIO->Just_FileName) - 8, ".GDScene") != 0)
		{
			strcat(App->CL_Vm_FileIO->Just_FileName, ".GDScene");
		}

		App->CL_Vm_FileIO->Update_File_Info(App->CL_Vm_FileIO->Full_Path_And_File, App->CL_Vm_FileIO->Just_FileName);

		mLevel_Directory[0] = 0;

		strcpy(mLevel_Directory, App->LevelDirectory);
	//	DLog(App->LevelDirectory);

	//	DLog(App->Cl_Scene_Data->S_Scene[0]->LevelName);
	}

//	DLog(App->CL_Vm_FileIO->Full_Path_And_File);
	

	WriteScene = fopen(App->CL_Vm_FileIO->Full_Path_And_File, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Level Files");
		return 0;
	}

	fprintf(WriteScene, "%s\n", "[GDScene]");
	fprintf(WriteScene, "%s%s\n", "Version=", "4.0");
	fprintf(WriteScene, "%s%i\n", "Type=", App->Cl_Scene_Data->S_Scene[0]->SceneType);

	WritePlayerSetup_New();
	WriteEnvironment_New();
	WriteObjects_New();
	WriteOptions_New();
	//WriteStock_New();
	fclose(WriteScene);

	// New Folder for Data
	SubFolder[0] = 0;
	strcpy(SubFolder, mLevel_Directory);
	strcat(SubFolder, App->Cl_Scene_Data->S_Scene[0]->LevelName);
	strcat(SubFolder,"_Data");
	int test = CreateDirectory(SubFolder, NULL);
	// ------------------------------------------------------------------

	Write_Player_Locations_New();
	Write_Stock_Sounds_New();

	SetWindowText(App->MainHwnd, App->CL_Vm_FileIO->Full_Path_And_File);

//	strcpy(App->Cl_FileView->LevelName, App->Cl_Scene_Data->S_Scene[0]->LevelName);
//	App->Cl_FileView->ChangeItem_Name(App->Cl_FileView->GD_LevelFolder, App->Cl_Scene_Data->S_Scene[0]->LevelName);

	if (AskForFile == 1)
	{
		//App->Cl_Dialogs->Message("Saved");
	//	DLog("Saved");
	}
	else
	{
		//App->Say("Saved");
	}
	return 1;
}

// *************************************************************************
// *					WritePlayerSetup  Terry Bernie  				   *
// *************************************************************************
bool GD19_Save_Scene::WritePlayerSetup_New()
{
	// Player
	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Player]");
	fprintf(WriteScene, "%s%s\n", "Name=", App->SBC_Player->Player_Name);
	fprintf(WriteScene, "%s%f,%f,%f\n", "Start_Position=", App->SBC_Player->StartPos.x, App->SBC_Player->StartPos.y, App->SBC_Player->StartPos.z);

	fprintf(WriteScene, "%s%s\n", "Shape=", "Capsule");
	fprintf(WriteScene, "%s%f\n", "Mass=", App->SBC_Player->Capsule_Mass);
	fprintf(WriteScene, "%s%f\n", "Radius=", App->SBC_Player->Capsule_Radius);
	fprintf(WriteScene, "%s%f\n", "Height=", App->SBC_Player->Capsule_Height);
	fprintf(WriteScene, "%s%f\n", "Ground_Speed=", App->SBC_Player->Ground_speed);
	fprintf(WriteScene, "%s%f\n", "Cam_Height=", App->SBC_Player->PlayerHeight);

	return 1;
}

// *************************************************************************
// *					WriteEnvironment  Terry Bernie  				   *
// *************************************************************************
bool GD19_Save_Scene::WriteEnvironment_New()
{
	// Environment
	float x = 0;
	float y = 0;
	float z = 0;

	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Environment]");

	// Fog
	fprintf(WriteScene, "%s %i\n", "Fog_Visible=", App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn);
	fprintf(WriteScene, "%s %i\n", "Fog_Mode=", App->Cl_Scene_Data->S_Scene[0]->Fog[0].Mode);

	x = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.x;
	y = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.y;
	z = App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.z;

	fprintf(WriteScene, "%s%f,%f,%f\n", "Fog_Colour=", x, y, z);
	fprintf(WriteScene, "%s%f\n", "Fog_Density=", App->Cl_Scene_Data->S_Scene[0]->Fog[0].Density);
	fprintf(WriteScene, "%s%f\n", "Fog_Start=", App->Cl_Scene_Data->S_Scene[0]->Fog[0].Start);
	fprintf(WriteScene, "%s%f\n", "Fog_End=", App->Cl_Scene_Data->S_Scene[0]->Fog[0].End);
	//--------------------------------------------------------

	// Light
	x = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.x;
	y = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.y;
	z = App->Cl_Scene_Data->S_Scene[0]->AmbientColour.z;
	fprintf(WriteScene, "%s%f,%f,%f\n", "Light_Ambient=", x, y, z);

	x = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.x;
	y = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.y;
	z = App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.z;
	fprintf(WriteScene, "%s%f,%f,%f\n", "Light_Diffuse=", x, y, z);

	x = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.x;
	y = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.y;
	z = App->Cl_Scene_Data->S_Scene[0]->SpecularColour.z;
	fprintf(WriteScene, "%s%f,%f,%f\n", "Light_Specular=", x, y, z);

	x = 0;//App->Cl_Scene_Data->S_Scene[0]->SpecularColour.x;
	y = 0;//App->Cl_Scene_Data->S_Scene[0]->SpecularColour.y;
	z = 0;//App->Cl_Scene_Data->S_Scene[0]->SpecularColour.z;
	fprintf(WriteScene, "%s%f,%f,%f\n", "Light_Position=", x, y, z);
	//--------------------------------------------------------
		// Sound
	fprintf(WriteScene, "%s%s\n", "Sound_Track=", App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFile);
	fprintf(WriteScene, "%s%f\n", "Sound_Volume=", App->Cl_Scene_Data->S_Scene[0]->Sound[0].Volume);
	fprintf(WriteScene, "%s%i\n", "Sound_Play=", App->Cl_Scene_Data->S_Scene[0]->Sound[0].Play);
	fprintf(WriteScene, "%s%i\n", "Sound_Loop=", App->Cl_Scene_Data->S_Scene[0]->Sound[0].Loop);
	//--------------------------------------------------------
	fprintf(WriteScene, "%s%i\n", "Sky_Enabled=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].Enabled);
	fprintf(WriteScene, "%s%i\n", "Sky_Type=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].type);
	fprintf(WriteScene, "%s%s\n", "Sky_Material=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].Material);
	fprintf(WriteScene, "%s%f\n", "Sky_Distance=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].Distance);
	fprintf(WriteScene, "%s%f\n", "Sky_Tiling=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].Tiling);
	fprintf(WriteScene, "%s%f\n", "Sky_Curvature=", App->Cl_Scene_Data->S_Scene[0]->Sky[0].Curvature);
	return 1;
}

// *************************************************************************
// *					WriteObjects  Terry Bernie						   *
// *************************************************************************
bool GD19_Save_Scene::WriteObjects_New()
{
	int Real_Count = App->Cl_LookUps->Get_AdjustedCount();

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	// Objects
	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Objects]");
	fprintf(WriteScene, "%s%i\n", "Objects_Count=", Real_Count);// App->Cl_Scene_Data->ObjectCount);

	int new_Count = 0;
	int Count = 0;
	while (Count < App->Cl_Scene_Data->ObjectCount)
	{
		if (App->Cl_Scene_Data->Cl_Object[Count]->Deleted == 1)
		{
			//App->Say(App->Cl_Scene_Data->CL_Object[Count]->Name);
		}

		if (App->Cl_Scene_Data->Cl_Object[Count]->Deleted == 0)
		{
			char Cbuff[255];
			char buff[255];
			strcpy(buff, "[Object_");
			//itoa(Count, Cbuff, 10);
			_itoa(new_Count, Cbuff, 10);
			strcat(buff, Cbuff);
			strcat(buff, "]");

			fprintf(WriteScene, "%s\n", buff);
			fprintf(WriteScene, "%s%i\n", "Object_ID=", App->Cl_Scene_Data->Cl_Object[Count]->Object_ID);
			fprintf(WriteScene, "%s%s\n", "Object_Name=", App->Cl_Scene_Data->Cl_Object[Count]->Name);
			fprintf(WriteScene, "%s%s\n", "Object_Mesh=", App->Cl_Scene_Data->Cl_Object[Count]->MeshName);
			fprintf(WriteScene, "%s%i\n", "Object_Type=", App->Cl_Scene_Data->Cl_Object[Count]->Type);
			fprintf(WriteScene, "%s%i\n", "Object_Shape=", App->Cl_Scene_Data->Cl_Object[Count]->Shape);
			fprintf(WriteScene, "%s%i\n", "Object_Usage=", App->Cl_Scene_Data->Cl_Object[Count]->Usage);
			fprintf(WriteScene, "%s%i\n", "Object_Folder=", App->Cl_Scene_Data->Cl_Object[Count]->Folder);

			x = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Pos.x;
			y = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Pos.y;
			z = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Pos.z;
			fprintf(WriteScene, "%s%f,%f,%f\n", "Object_Mesh_Pos=", x, y, z);

			x = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Rot.x;
			y = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Rot.y;
			z = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Rot.z;
			fprintf(WriteScene, "%s%f,%f,%f\n", "Object_Mesh_Rot=", x, y, z);

			w = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Quat.w;
			x = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Quat.x;
			y = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Quat.y;
			z = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Quat.z;
			fprintf(WriteScene, "%s%f,%f,%f,%f\n", "Object_Mesh_Quat=", w, x, y, z);

			x = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Scale.x;
			y = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Scale.y;
			z = App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Scale.z;
			fprintf(WriteScene, "%s%f,%f,%f\n", "Object_Mesh_Scale=", x, y, z);

			//----------------- Physics
			fprintf(WriteScene, "%s%f\n", "Physics_Mass=", App->Cl_Scene_Data->Cl_Object[Count]->bt_body->getInvMass());
			fprintf(WriteScene, "%s%f\n", "Physics_Restitution=", App->Cl_Scene_Data->Cl_Object[Count]->bt_body->getRestitution());

			x = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Pos.x;
			y = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Pos.y;
			z = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Pos.z;
			fprintf(WriteScene, "%s%f,%f,%f\n", "Physics_Pos=", x, y, z);

			x = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Rot.x;
			y = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Rot.y;
			z = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Rot.z;
			fprintf(WriteScene, "%s%f,%f,%f\n", "Physics_Rot=", x, y, z);

			w = App->Cl_Scene_Data->Cl_Object[Count]->bt_body->getWorldTransform().getRotation().getW();
			x = App->Cl_Scene_Data->Cl_Object[Count]->bt_body->getWorldTransform().getRotation().getX();
			y = App->Cl_Scene_Data->Cl_Object[Count]->bt_body->getWorldTransform().getRotation().getY();;
			z = App->Cl_Scene_Data->Cl_Object[Count]->bt_body->getWorldTransform().getRotation().getZ();;
			fprintf(WriteScene, "%s%f,%f,%f,%f\n", "Physics_Quat=", w, x, y, z);

			x = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Scale.x;
			y = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Scale.y;
			z = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Scale.z;
			fprintf(WriteScene, "%s%f,%f,%f\n", "Physics_Scale=", x, y, z);

			x = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Size.x;
			y = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Size.y;
			z = App->Cl_Scene_Data->Cl_Object[Count]->Physics_Size.z;
			fprintf(WriteScene, "%s%f,%f,%f\n", "Physics_Size=", x, y, z);

			fprintf(WriteScene, "%s%s\n", "Stock_Text=", App->Cl_Scene_Data->Cl_Object[Count]->Entity[0].mTextItem);
			fprintf(WriteScene, "%s%s\n", "Stock_Name=", App->Cl_Scene_Data->Cl_Object[Count]->Entity[0].Stock_mName);
			fprintf(WriteScene, "%s%i\n", "Stock_Index=", App->Cl_Scene_Data->Cl_Object[Count]->Entity[0].Stock_mIndex);
			//fprintf(WriteScene,"%s %s\n","FileAndPath",App->Cl_Scene_Data->CL_Object[Count]->Entity[0].mFileAndPath);

			// Sound Settings
			if (App->Cl_Scene_Data->Cl_Object[Count]->HasSound == 1)
			{
				fprintf(WriteScene, "%s%i\n", "Has_Sound=", 1);
			}
			else
			{
				fprintf(WriteScene, "%s%i\n", "Has_Sound=", 0);// App->Cl_Scene_Data->CL_Object[Count]->Entity[0].Stock_mIndex);
			}

			// new sound v2
			fprintf(WriteScene, "%s%i\n", "Sound_ID=",App->Cl_Scene_Data->Cl_Object[Count]->Sound_ID_v2);
			fprintf(WriteScene, "%s%i\n", "Play=", App->Cl_Scene_Data->Cl_Object[Count]->Play_v2);

			if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Move)
			{
				fprintf(WriteScene, "%s%s\n", "Object_To_Move=", App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Object_Name);
				fprintf(WriteScene, "%s%i\n", "Object_Index=", App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Object_Index);
				fprintf(WriteScene, "%s%i\n", "Move_Object_ID=", App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Object_ID);
				fprintf(WriteScene, "%s%f,%f,%i\n", "Data=", App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Distance, App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Speed, App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->IsNegative);
				fprintf(WriteScene, "%s%i\n", "Axi=", App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->WhatDirection);
			}

			// Teleport
			if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Teleport)
			{
				fprintf(WriteScene, "%s%s\n", "Goto=", App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Name);

				x = App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Player_Position.x;
				y = App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Player_Position.y;
				z = App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Player_Position.z;
				fprintf(WriteScene, "%s%f,%f,%f\n", "Mesh_Position=", x, y, z);

				x = App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Position.getX();
				y = App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Position.getY();
				z = App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Position.getZ();
				fprintf(WriteScene, "%s%f,%f,%f\n", "Physics_Position=", x, y, z);

				w = App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Rotation.getW();
				x = App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Rotation.getX();
				y = App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Rotation.getY();
				z = App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Rotation.getZ();
				fprintf(WriteScene, "%s%f,%f,%f,%f\n", "Physics_Rotation=", w, x, y, z);

			}

			fprintf(WriteScene, "%s\n", "#-------------------------------------------------------------");

			new_Count++;
		}

		Count++;
	}

	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Counters]");
	fprintf(WriteScene, "%s%i\n", "Object_ID_Counter=", App->Cl_Scene_Data->Object_ID_Counter);

	return 1;
}

// *************************************************************************
// *					WriteStock  Terry Bernie						   *
// *************************************************************************
bool GD19_Save_Scene::WriteStock_New()
{
	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	// Messages
	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Stock_Message]");
	fprintf(WriteScene, "%s%i\n", "Stock_Message_Count=", App->Cl_Scene_Data->Stock_Messgae_Count);

	int Count = 0;
	while (Count < App->Cl_Scene_Data->Stock_Messgae_Count)
	{
		char Cbuff[255];
		char buff[255];
		strcpy(buff, "[Stock_Message_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);
		strcat(buff, "]");

		fprintf(WriteScene, "%s\n", buff);
		fprintf(WriteScene, "%s%s\n", "Name=", App->Cl_Scene_Data->S_Messages[Count]->Name);
		fprintf(WriteScene, "%s%s\n", "Default_Text=", App->Cl_Scene_Data->S_Messages[Count]->Default_Text);
		fprintf(WriteScene, "%s%i\n", "Font_Size=", App->Cl_Scene_Data->S_Messages[Count]->Font_Size);

		x = App->Cl_Scene_Data->S_Messages[Count]->Colour.x;
		y = App->Cl_Scene_Data->S_Messages[Count]->Colour.y;
		z = App->Cl_Scene_Data->S_Messages[Count]->Colour.z;
		fprintf(WriteScene, "%s%f,%f,%f\n", "Colour=", x, y, z);

		x = App->Cl_Scene_Data->S_Messages[Count]->Pos_Hoz;
		y = App->Cl_Scene_Data->S_Messages[Count]->Pos_Vert;
		fprintf(WriteScene, "%s%f,%f\n", "Position=", x, y);

		fprintf(WriteScene, "%s\n", "-------------------------------------------------------------");
		Count++;
	}

	// Sounds
	fprintf(WriteScene, "%s\n", "[Stock_Sound]");
	fprintf(WriteScene, "%s%i\n", "Stock_Sound_Count=", App->Cl_Scene_Data->Stock_Messgae_Count);

	Count = 0;
	while (Count < App->Cl_Scene_Data->Stock_Sound_Count)
	{
		char Cbuff[255];
		char buff[255];
		strcpy(buff, "[Stock_Sound_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);
		strcat(buff, "]");

		fprintf(WriteScene, "%s\n", buff);
		fprintf(WriteScene, "%s%s\n", "Name=", App->Cl_Scene_Data->St_Sounds[Count]->Name);
		fprintf(WriteScene, "%s%s\n", "SoundFile=", App->Cl_Scene_Data->St_Sounds[Count]->SoundFile);
		fprintf(WriteScene, "%s%s\n", "FileAndPath=", App->Cl_Scene_Data->St_Sounds[Count]->SoundFileAndPath);
		fprintf(WriteScene, "%s%f\n", "Volume=", App->Cl_Scene_Data->St_Sounds[Count]->Volume);
		fprintf(WriteScene, "%s%i\n", "Play=", App->Cl_Scene_Data->St_Sounds[Count]->Play);
		fprintf(WriteScene, "%s%i\n", "Loop=", App->Cl_Scene_Data->St_Sounds[Count]->Loop);
		fprintf(WriteScene, "%s\n", "-------------------------------------------------------------");
		Count++;
	}

	return 1;
}

// *************************************************************************
// *						Options Terry Bernie  						   *
// *************************************************************************
bool GD19_Save_Scene::WriteOptions_New()
{
	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Options]");

	fprintf(WriteScene, "%s%i\n", "Has_Planes=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Planes);
	fprintf(WriteScene, "%s%i\n", "Has_Objects=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Objects);
	fprintf(WriteScene, "%s%i\n", "Has_Particles=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Particles);
	fprintf(WriteScene, "%s%i\n", "Has_Weapons=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Weapons);
	fprintf(WriteScene, "%s%i\n", "Has_Player=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Player);
	fprintf(WriteScene, "%s%i\n", "Has_Debug=", App->Cl_Scene_Data->S_LoadOptions[0]->Has_Debug);
	return 1;
}

// *************************************************************************
// *						Write_Player_Locations_New 					   *
// *************************************************************************
bool GD19_Save_Scene::Write_Player_Locations_New()
{
	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	WriteScene = NULL;

	char PathTemp[1024];
	strcpy(PathTemp, SubFolder);
	strcat(PathTemp, "\\");
	strcat(PathTemp,App->Cl_Scene_Data->S_Scene[0]->LevelName);
	strcat(PathTemp, ".gpl");

	WriteScene = fopen(PathTemp, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	fprintf(WriteScene, "%s\n", "[GDScene]");
	fprintf(WriteScene, "%s%s\n", "Version=", "4.0");

	// Player
	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Locations]");

	int RealCount = App->Cl_LookUps->Player_Location_GetCount(); // Get The real Count Minus Deleted Files

	fprintf(WriteScene, "%s%i\n", "Locations_Count=", RealCount);

	int Location = 0; // Correct for Deleted Files
	int Count = 0;
	while (Count < App->Cl_Scene_Data->Player_Location_Count)
	{
		if (App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted == 0)
		{
			fprintf(WriteScene, "%s\n", " ");

			char Cbuff[255];
			char buff[255];
			strcpy(buff, "[Location_");
			_itoa(Location, Cbuff, 10);
			strcat(buff, Cbuff);
			strcat(buff, "]");
			fprintf(WriteScene, "%s\n", buff);

			fprintf(WriteScene, "%s%i\n", "Locatoin_ID=", App->Cl_Scene_Data->S_Player_Locations[Count]->Location_ID);
			fprintf(WriteScene, "%s%s\n", "Name=", App->Cl_Scene_Data->S_Player_Locations[Count]->Name);

			x = App->Cl_Scene_Data->S_Player_Locations[Count]->Current_Position.x;
			y = App->Cl_Scene_Data->S_Player_Locations[Count]->Current_Position.y;
			z = App->Cl_Scene_Data->S_Player_Locations[Count]->Current_Position.z;
			fprintf(WriteScene, "%s%f,%f,%f\n", "Mesh_Position=", x, y, z);

			x = App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Position.getX();
			y = App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Position.getY();
			z = App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Position.getZ();
			fprintf(WriteScene, "%s%f,%f,%f\n", "Physics_Position=", x, y, z);

			w = App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.getW();
			x = App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.getX();
			y = App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.getY();
			z = App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.getZ();
			fprintf(WriteScene, "%s%f,%f,%f,%f\n", "Physics_Rotation=", w, x, y, z);
			Location++;
		}

		Count++;
	}


	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Counters]");
	fprintf(WriteScene, "%s%i\n", "Location_ID_Counter=", App->Cl_Scene_Data->Locations_ID_Counter);

	fclose(WriteScene);
	return 1;
}

// *************************************************************************
// *						Write_Stock_Sounds_New	 					   *
// *************************************************************************
bool GD19_Save_Scene::Write_Stock_Sounds_New()
{
	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	WriteScene = NULL;

	char PathTemp[1024];
	strcpy(PathTemp, SubFolder);
	strcat(PathTemp, "\\");
	strcat(PathTemp, App->Cl_Scene_Data->S_Scene[0]->LevelName);
	strcat(PathTemp, ".gss");

	//----------------------------------

	WriteScene = fopen(PathTemp, "wt");
	if (!WriteScene)
	{
		App->Say("Cant Create Save File");
		return 0;
	}

	fprintf(WriteScene, "%s\n", "[GDScene]");
	fprintf(WriteScene, "%s%s\n", "Version=", "4.0");

	// Player
	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Sounds]");

	int RealCount = App->Cl_LookUps->Stock_Sound_GetCount(); // Get The real Count Minus Deleted Files

	fprintf(WriteScene, "%s%i\n", "Sounds_Count=", RealCount);

	int Location = 0; // Correct for Deleted Files
	int Count = 0;
	while (Count < App->Cl_Scene_Data->Stock_Sound_Count)
	{
		if (App->Cl_Scene_Data->St_Sounds[Count]->Deleted == 0)
		{
			fprintf(WriteScene, "%s\n", " ");

			char Cbuff[255];
			char buff[255];
			strcpy(buff, "[Sound_");
			_itoa(Location, Cbuff, 10);
			strcat(buff, Cbuff);
			strcat(buff, "]");
			fprintf(WriteScene, "%s\n", buff);

			fprintf(WriteScene, "%s%i\n", "Sound_ID=", App->Cl_Scene_Data->St_Sounds[Count]->Sound_ID);
			fprintf(WriteScene, "%s%s\n", "Name=", App->Cl_Scene_Data->St_Sounds[Count]->Name);

			fprintf(WriteScene, "%s%s\n", "SoundFile=", App->Cl_Scene_Data->St_Sounds[Count]->SoundFile);
			fprintf(WriteScene, "%s%f\n", "Volume=", App->Cl_Scene_Data->St_Sounds[Count]->Volume);

			Location++;
		}

		Count++;
	}


	fprintf(WriteScene, "%s\n", " ");
	fprintf(WriteScene, "%s\n", "[Counters]");
	fprintf(WriteScene, "%s%i\n", "Sounds_ID_Counter=", App->Cl_Scene_Data->StockSounds_ID_Counter);

	fclose(WriteScene);
	return 1;
}