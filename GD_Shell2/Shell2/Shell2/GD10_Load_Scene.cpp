#include "StdAfx.h"
#include "BT_App.h"
#include "GD10_Load_Scene.h"

#pragma warning( disable : 4800)

GD10_Load_Scene::GD10_Load_Scene()
{
	LoadScene = NULL;
	LoadObjects = NULL;

	Scene_FileName[0] = 0;
	Scene_Path_FileName[0] = 0;
	SubFolder[0] = 0;
}


GD10_Load_Scene::~GD10_Load_Scene()
{
}

// *************************************************************************
// *	  				OpenScene Terry Bernie							   *
// *************************************************************************
bool GD10_Load_Scene::OpenScene(bool AskForScene)
{
	strcpy(App->GDCL_Scene_Data->S_Scene[0]->TerrainFileName, Scene_FileName);
	strcpy(App->GDCL_Scene_Data->S_Scene[0]->GDSceneName, Scene_FileName);

	
	char mPath[256];
	strcpy(mPath, Scene_Path_FileName);
	int FLen = strlen(Scene_FileName);
	int PLen = strlen(Scene_Path_FileName);
	mPath[PLen - FLen] = 0;
	strcpy(App->LevelDirectory, mPath);

	char Temp[256];
	strcpy(Temp, Scene_FileName);
	int Len = strlen(Temp);
	Temp[Len - 8] = 0;
	strcpy(App->GDCL_Scene_Data->S_Scene[0]->LevelName, Temp);

	gdLoader_LoadGDScene_New();

	return 1;
}

// *************************************************************************
// *				gdLoader_LoadGDScene_New   Terry Bernie  			   *
// *************************************************************************
bool GD10_Load_Scene::gdLoader_LoadGDScene_New()
{
	LoadScene = NULL;
	char Tag1[1024];
	int ObjectsCount = 0;
	int TagFloat = 0;
	int TagInt = 0;

	App->CL10_Ini->SetPathName(Scene_Path_FileName);

	//========== Version

	App->CL10_Ini->GetString("GDScene", "Version", Tag1, 1024);
	strcpy(App->GDCL_Scene_Data->S_Scene[0]->SceneVersion, Tag1);	// Save for later

	int result = strcmp(Tag1, "4.0");
	if (result == 0)
	{
		TagInt = App->CL10_Ini->GetInt("GDScene", "Type", 0, 10);
		App->GDCL_Scene_Data->S_Scene[0]->SceneType = TagInt;
		Load_Scene40();
	}

	// Erro Check;

	return 1;
}


// *************************************************************************
//						Load_Scene40 Terry Bernie						   *
// *************************************************************************
void GD10_Load_Scene::Load_Scene40()
{
	App->GDCL_Scene_Data->ClearScene();
	Load_Player40();
	Load_Environment40();
	Load_Objects40();

	Populate_Level40();
	
	// New Folder for Data
	SubFolder[0] = 0;
	strcpy(SubFolder, App->LevelDirectory);
	strcat(SubFolder, App->GDCL_Scene_Data->S_Scene[0]->LevelName);
	strcat(SubFolder, "_Data");

	Load_Player_Locations40();
	Load_Stock_Sounds40();
}



// *************************************************************************
//						Load_Player40 Terry Bernie						   *
// *************************************************************************
bool GD10_Load_Scene::Load_Player40()
{
	char chr_Tag1[1024];
	float x = 0;
	float y = 0;
	float z = 0;

	// Name
	App->CL10_Ini->GetString("Player", "Name", chr_Tag1, 1024);
	strcpy(App->GDCL_Player->PlayerName, chr_Tag1);

	// Position
	App->CL10_Ini->GetString("Player", "Start_Position", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->GDCL_Player->StartPos.x = x;
	App->GDCL_Player->StartPos.y = y;
	App->GDCL_Player->StartPos.z = z;

	App->CL10_Ini->GetString("Player", "Shape", chr_Tag1, 1024); // Capsule

	x = App->CL10_Ini->Get_Float("Player", "Mass");
	y = App->CL10_Ini->Get_Float("Player", "Radius");
	z = App->CL10_Ini->Get_Float("Player", "Height");

	App->GDCL_Player->Capsule_Mass = x;
	App->GDCL_Player->Capsule_Radius = y;
	App->GDCL_Player->Capsule_Height = z;

	x = App->CL10_Ini->Get_Float("Player", "Ground_Speed");
	if (x == 0) { x = 2.220; }
	App->GDCL_Player->Ground_speed = x;

	x = App->CL10_Ini->Get_Float("Player", "Cam_Height");
	if (x == 0) { x = 6.00; }
	App->GDCL_Player->PlayerHeight = x;

	return 1;
}

// *************************************************************************
//						Load_Environment40 Terry Bernie					   *
// *************************************************************************
bool GD10_Load_Scene::Load_Environment40()
{
	char chr_Tag1[1024];
	int Int_Tag = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	// Visibility
	Int_Tag = App->CL10_Ini->GetInt("Environment", "Fog_Visible", 0, 10);
	App->GDCL_Scene_Data->S_Scene[0]->Fog[0].FogOn = Int_Tag;

	// Mode
	Int_Tag = App->CL10_Ini->GetInt("Environment", "Fog_Mode", 0, 10);
	App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Mode = Int_Tag;

	// Colour
	App->CL10_Ini->GetString("Environment", "Fog_Colour", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Colour.x = x;
	App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Colour.y = y;
	App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Colour.z = z;

	x = App->CL10_Ini->Get_Float("Environment", "Fog_Density");
	y = App->CL10_Ini->Get_Float("Environment", "Fog_Start");
	z = App->CL10_Ini->Get_Float("Environment", "Fog_End");

	App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Density = x;
	App->GDCL_Scene_Data->S_Scene[0]->Fog[0].Start = y;
	App->GDCL_Scene_Data->S_Scene[0]->Fog[0].End = z;

	// Light 
	App->CL10_Ini->GetString("Environment", "Light_Ambient", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->GDCL_Scene_Data->S_Scene[0]->AmbientColour.x = x;
	App->GDCL_Scene_Data->S_Scene[0]->AmbientColour.y = y;
	App->GDCL_Scene_Data->S_Scene[0]->AmbientColour.z = z;

	App->CL10_Ini->GetString("Environment", "Light_Diffuse", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->GDCL_Scene_Data->S_Scene[0]->DiffuseColour.x = x;
	App->GDCL_Scene_Data->S_Scene[0]->DiffuseColour.y = y;
	App->GDCL_Scene_Data->S_Scene[0]->DiffuseColour.z = z;

	App->CL10_Ini->GetString("Environment", "Light_Specular", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->GDCL_Scene_Data->S_Scene[0]->SpecularColour.x = x;
	App->GDCL_Scene_Data->S_Scene[0]->SpecularColour.y = y;
	App->GDCL_Scene_Data->S_Scene[0]->SpecularColour.z = z;

	App->CL10_Ini->GetString("Environment", "Light_Position", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->GDCL_Scene_Data->S_Scene[0]->Light_Position.x = x;
	App->GDCL_Scene_Data->S_Scene[0]->Light_Position.y = y;
	App->GDCL_Scene_Data->S_Scene[0]->Light_Position.z = z;

	// Sound 
	App->CL10_Ini->GetString("Environment", "Sound_Track", chr_Tag1, 1024);
	strcpy(App->GDCL_Scene_Data->S_Scene[0]->Sound[0].SoundFile, chr_Tag1);
	strcpy(App->GDCL_Scene_Data->S_Scene[0]->Sound[0].SoundFileAndPath, App->GDCL_SoundMgr->Default_Folder);
	strcat(App->GDCL_Scene_Data->S_Scene[0]->Sound[0].SoundFileAndPath, "\\Media\\Sounds\\");
	strcat(App->GDCL_Scene_Data->S_Scene[0]->Sound[0].SoundFileAndPath, chr_Tag1);
	//App->GDCL_SoundMgr->Remeber_SoundFile(chr_Tag1);

	x = App->CL10_Ini->Get_Float("Environment", "Sound_Volume");
	App->GDCL_Scene_Data->S_Scene[0]->Sound[0].Volume = x;

	Int_Tag = App->CL10_Ini->GetInt("Environment", "Sound_Play", 0, 10);
	App->GDCL_Scene_Data->S_Scene[0]->Sound[0].Play = Int_Tag;

	Int_Tag = App->CL10_Ini->GetInt("Environment", "Sound_Loop", 0, 10);
	App->GDCL_Scene_Data->S_Scene[0]->Sound[0].Loop = Int_Tag;

	// Sky
	Int_Tag = App->CL10_Ini->GetInt("Environment", "Sky_Enabled", 0, 10);
	App->GDCL_Scene_Data->S_Scene[0]->Sky[0].Enabled = Int_Tag;

	Int_Tag = App->CL10_Ini->GetInt("Environment", "Sky_Type", 0, 10);
	App->GDCL_Scene_Data->S_Scene[0]->Sky[0].type = Int_Tag;

	App->CL10_Ini->GetString("Environment", "Sky_Material", chr_Tag1, 1024);
	strcpy(App->GDCL_Scene_Data->S_Scene[0]->Sky[0].Material, chr_Tag1);

	x = App->CL10_Ini->Get_Float("Environment", "Sky_Distance");
	y = App->CL10_Ini->Get_Float("Environment", "Sky_Tiling");
	z = App->CL10_Ini->Get_Float("Environment", "Sky_Curvature");

	App->GDCL_Scene_Data->S_Scene[0]->Sky[0].Distance = x;
	App->GDCL_Scene_Data->S_Scene[0]->Sky[0].Tiling = y;
	App->GDCL_Scene_Data->S_Scene[0]->Sky[0].Curvature = z;
	return 1;
}

// *************************************************************************
//						Load_Objects40 Terry Bernie						   *
// *************************************************************************
bool GD10_Load_Scene::Load_Objects40()
{
	char chr_Tag1[1024];
	int Int_Tag = 0;
	bool bool_Tag = 0;
	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	Int_Tag = App->CL10_Ini->GetInt("Objects", "Objects_Count", 0, 10);

	int Object_Count = Int_Tag;
	int Count = 0;
	while (Count < Object_Count)
	{
		App->GDCL_Scene_Data->S_Object[Count] = new Object_Type;
		App->GDCL_Scene_Data->SetObjectDefaults(Count);

		char n_buff[255];
		char buff[255];
		strcpy(buff, "Object_");
		itoa(Count, n_buff, 10);
		strcat(buff, n_buff);

		Int_Tag = App->CL10_Ini->GetInt(buff, "Object_ID", 0, 10);
		//App->GDCL_Scene_Data->S_Object[Count]->Object_ID = Int_Tag;

		App->CL10_Ini->GetString(buff, "Object_Name", chr_Tag1, 1024);
		strcpy(App->GDCL_Scene_Data->S_Object[Count]->Name, chr_Tag1);

		App->CL10_Ini->GetString(buff, "Object_Mesh", chr_Tag1, 1024);
		strcpy(App->GDCL_Scene_Data->S_Object[Count]->MeshName, chr_Tag1);

		// Type
		Int_Tag = App->CL10_Ini->GetInt(buff, "Object_Type", 0, 10);
		App->GDCL_Scene_Data->S_Object[Count]->Type = Int_Tag;

		// Shape
		Int_Tag = App->CL10_Ini->GetInt(buff, "Object_Shape", 0, 10);
		App->GDCL_Scene_Data->S_Object[Count]->Shape = Int_Tag;

		// Usage
		Int_Tag = App->CL10_Ini->GetInt(buff, "Object_Usage", 0, 10);
		App->GDCL_Scene_Data->S_Object[Count]->Usage = Int_Tag;

		// Folder
		Int_Tag = App->CL10_Ini->GetInt(buff, "Object_Folder", 0, 10);
		App->GDCL_Scene_Data->S_Object[Count]->Folder = Int_Tag;

		// Mesh_Pos
		App->CL10_Ini->GetString(buff, "Object_Mesh_Pos", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Pos.x = x;
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Pos.y = y;
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Pos.z = z;

		// Mesh_Rot
		App->CL10_Ini->GetString(buff, "Object_Mesh_Rot", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Rot.x = x;
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Rot.y = y;
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Rot.z = z;

		// Mesh_Quat
		App->CL10_Ini->GetString(buff, "Object_Mesh_Quat", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Quat.w = w;
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Quat.x = x;
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Quat.y = y;
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Quat.z = z;

		// Mesh_Scale
		App->CL10_Ini->GetString(buff, "Object_Mesh_Scale", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Scale.x = x;
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Scale.y = y;
		App->GDCL_Scene_Data->S_Object[Count]->Mesh_Scale.z = z;

		////------------------------------------------------------------- Physics

		x = App->CL10_Ini->Get_Float(buff, "Physics_Mass");
		y = App->CL10_Ini->Get_Float(buff, "Physics_Restitution");
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Mass = x;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Restitution = y;

		// Physics_Pos
		App->CL10_Ini->GetString(buff, "Physics_Pos", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Pos.x = x;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Pos.y = y;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Pos.z = z;

		// Physics_Rot
		App->CL10_Ini->GetString(buff, "Physics_Rot", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Rot.x = x;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Rot.y = y;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Rot.z = z;

		// Physics_Quat
		App->CL10_Ini->GetString(buff, "Physics_Quat", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Quat.w = w;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Quat.x = x;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Quat.y = y;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Quat.z = z;

		// Physics_Scale
		App->CL10_Ini->GetString(buff, "Physics_Scale", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Scale.x = x;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Scale.y = y;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Scale.z = z;

		// Physics_Size
		App->CL10_Ini->GetString(buff, "Physics_Size", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Size.x = x;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Size.y = y;
		App->GDCL_Scene_Data->S_Object[Count]->Physics_Size.z = z;

		// Stock
		App->CL10_Ini->GetString(buff, "Stock_Text", chr_Tag1, 1024);
		strcpy(App->GDCL_Scene_Data->S_Object[Count]->Entity[0].mTextItem, chr_Tag1);


		//-------------------------- 
		if (App->GDCL_Scene_Data->S_Object[Count]->Usage == Enums::Usage_Sound)
		{
			char buff[1024];
			strcpy(buff, App->GDCL_SoundMgr->Default_Folder);
			strcat(buff, "\\Media\\Sounds\\");
			strcat(buff, chr_Tag1);

			strcpy(App->GDCL_Scene_Data->S_Object[Count]->Entity[0].mFileAndPath, buff);
		}
		////-------------------------- 

		// Stock Name
		App->CL10_Ini->GetString(buff, "Stock_Name", chr_Tag1, 1024);
		strcpy(App->GDCL_Scene_Data->S_Object[Count]->Entity[0].Stock_mName, chr_Tag1);

		Int_Tag = App->CL10_Ini->GetInt(buff, "Stock_Index", 0, 10);
		App->GDCL_Scene_Data->S_Object[Count]->Entity[0].Stock_mIndex = Int_Tag;

		// Has Sound
		bool_Tag = App->CL10_Ini->GetBool(buff, "Has_Sound", 0);
		App->GDCL_Scene_Data->S_Object[Count]->HasSound = bool_Tag;

		// new sound v2

		Int_Tag = App->CL10_Ini->GetInt(buff, "Sound_ID", 0, 10);
		App->GDCL_Scene_Data->S_Object[Count]->Sound_ID_v2 = Int_Tag;

		Int_Tag = App->CL10_Ini->GetInt(buff, "Play", 0, 10);
		App->GDCL_Scene_Data->S_Object[Count]->Play_v2 = Int_Tag;

		if (App->GDCL_Scene_Data->S_Object[Count]->Usage == Enums::Usage_Move)
		{
			Load_MoveEntity40(Count);
		}

		if (App->GDCL_Scene_Data->S_Object[Count]->Usage == Enums::Usage_Teleport)
		{
			// Create Teleport and use Player Start Position as Default
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0] = new Teleport_type;
			App->CL10_Ini->GetString(buff, "Goto", chr_Tag1, 1024);

			strcpy(App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Name, chr_Tag1);

			// Mesh_Pos
			App->CL10_Ini->GetString(buff, "Mesh_Position", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Player_Position.x = x;
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Player_Position.y = y;
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Player_Position.z = z;

			App->CL10_Ini->GetString(buff, "Physics_Position", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Physics_Position.setX(x);
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Physics_Position.setY(y);
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Physics_Position.setZ(z);

			App->CL10_Ini->GetString(buff, "Physics_Rotation", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Physics_Rotation.setW(w);
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Physics_Rotation.setX(x);
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Physics_Rotation.setY(y);
			App->GDCL_Scene_Data->S_Object[Count]->S_Teleport[0]->Physics_Rotation.setZ(z);
		}

		Count++;
	}

	// j
	Int_Tag = App->CL10_Ini->GetInt("Counters", "Object_ID_Counter", 0, 10);
	//App->GDCL_Scene_Data->Object_ID_Counter = Int_Tag;

	App->GDCL_Scene_Data->ObjectCount = Count;
	return 1;
}

// *************************************************************************
// *					Load_MoveEntity40 Terry Bernie  				   *
// *************************************************************************
void GD10_Load_Scene::Load_MoveEntity40(int Count)
{
	char chr_Tag1[1024];
	int Int_Tag = 0;

	float x = 0;
	float y = 0;

	char n_buff[255];
	char buff[255];
	strcpy(buff, "Object_");
	itoa(Count, n_buff, 10);
	strcat(buff, n_buff);

	int result = 0;

	App->GDCL_Scene_Data->S_Object[Count]->S_MoveType = new Move_Type;
	App->GDCL_Scene_Data->Set_Move_Defaults(Count);


	App->CL10_Ini->GetString(buff, "Object_To_Move", chr_Tag1, 1024);
	strcpy(App->GDCL_Scene_Data->S_Object[Count]->S_MoveType->Object_Name, chr_Tag1);

	Int_Tag = App->CL10_Ini->GetInt(buff, "Object_Index", 0, 10);
	App->GDCL_Scene_Data->S_Object[Count]->S_MoveType->Object_Index = Int_Tag;



	App->CL10_Ini->GetString(buff, "Data", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%i", &x, &y, &Int_Tag);
	App->GDCL_Scene_Data->S_Object[Count]->S_MoveType->Distance = x;
	App->GDCL_Scene_Data->S_Object[Count]->S_MoveType->Speed = y;
	App->GDCL_Scene_Data->S_Object[Count]->S_MoveType->IsNegative = Int_Tag;

	Int_Tag = App->CL10_Ini->GetInt(buff, "Axi", 0, 10);
	App->GDCL_Scene_Data->S_Object[Count]->S_MoveType->WhatDirection = Int_Tag;

}

// *************************************************************************
// *				LoadOptionsDetails40   Terry Bernie  				   *
// *************************************************************************
bool GD10_Load_Scene::LoadOptionsDetails40()
{
	int TagInt_1 = 0;
	int TagInt_2 = 0;
	int TagInt_3 = 0;
	int TagInt_4 = 0;
	int TagInt_5 = 0;
	int TagInt_6 = 0;

	TagInt_1 = App->CL10_Ini->GetInt("Options", "Has_Planes", 0, 10);
	TagInt_2 = App->CL10_Ini->GetInt("Options", "Has_Objects", 0, 10);
	TagInt_3 = App->CL10_Ini->GetInt("Options", "Has_Particles", 0, 10);
	TagInt_4 = App->CL10_Ini->GetInt("Options", "Has_Weapons", 0, 10);
	TagInt_5 = App->CL10_Ini->GetInt("Options", "Has_Player", 0, 10);
	TagInt_6 = App->CL10_Ini->GetInt("Options", "Has_Debug", 0, 10);

	App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Planes = (bool)TagInt_1;
	App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Objects = (bool)TagInt_2;
	App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Particles = (bool)TagInt_3;
	App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Weapons = (bool)TagInt_4;
	App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Player = (bool)TagInt_5;
	App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Debug = (bool)TagInt_6;

	return 1;
}

// *************************************************************************
//						LoadCameraDetails Terry Bernie					   *
// *************************************************************************
bool GD10_Load_Scene::LoadCameraDetails()
{

	return 1;
}

// *************************************************************************
//						Populate_Level30 Terry Bernie					   *
// *************************************************************************
bool GD10_Load_Scene::Populate_Level40()
{
	//strcpy(App->GDCL_FileView->LevelName, App->GDCL_Scene_Data->S_Scene[0]->LevelName);

	//App->GDCL_FileView->Delete_AllItems(); // Bit Bruttle

	App->GDCL_Environment->Load_Environment();

	if (App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Player == 1)
	{
		App->GDCL_Player->Load_Player();
	}

	if (App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Objects == 1)
	{
		App->GDCL_Add_Objects->Add_Object();
	}

	if (App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Player == 1)
	{
		App->GDCL_Player->PlayerAdded = 1;
	}

	App->GDCL_Scene_Data->SceneLoaded = 1;
	App->GDCL_Bullet->GD_Physics_On = 1;

	App->GDCL_Scene_Data->SceneLoaded = 1;
	App->GDCL_Bullet->GD_Physics_On = 1;
	App->Ogre17->PhysicsFrameListener->GD_Run_Physics = 1;
	return 1;
}

// *************************************************************************
// *				Load_Player_Locations40   Terry Bernie  			   *
// *************************************************************************
bool GD10_Load_Scene::Load_Player_Locations40()
{
	App->GDCL_Scene_Data->Player_Location_Count = 0;

	char PathTemp[1024];
	strcpy(PathTemp, SubFolder);
	strcat(PathTemp, "\\");
	strcat(PathTemp, App->GDCL_Scene_Data->S_Scene[0]->LevelName);
	strcat(PathTemp, ".gpl");

	bool test = App->GDCL_Utilities->Search_Folder_ForFile("", PathTemp);

	if (test == 0)
	{
		App->Say("No Position File Found");
		return 1;
	}
	else
	{
		char buff[1024];
		strcpy(buff, App->LevelDirectory);
		strcat(buff, App->GDCL_Scene_Data->S_Scene[0]->LevelName);
		strcat(buff, ".gpl");

		App->CL10_Ini->SetPathName(PathTemp);

		char chr_Tag1[1024];
		int Int_Tag = 0;
		int Int_Count = 0;
		float w = 0;
		float x = 0;
		float y = 0;
		float z = 0;

		Int_Count = App->CL10_Ini->GetInt("Locations", "Locations_Count", 0, 10);

		int Count = 0;
		while (Count < Int_Count)
		{
			if (App->GDCL_Scene_Data->S_Player_Locations[Count])
			{
				delete App->GDCL_Scene_Data->S_Player_Locations[Count];
				App->GDCL_Scene_Data->S_Player_Locations[Count] = NULL;
			}

			char n_buff[255];
			char buff[255];
			strcpy(buff, "Location_");
			itoa(Count, n_buff, 10);
			strcat(buff, n_buff);

			App->GDCL_Scene_Data->S_Player_Locations[Count] = new Player_Location_type();
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Deleted = 0;


			Int_Tag = App->CL10_Ini->GetInt(buff, "Locatoin_ID", 0, 10);
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Location_ID = Int_Tag;

			App->CL10_Ini->GetString(buff, "Name", chr_Tag1, 1024);


			strcpy(App->GDCL_Scene_Data->S_Player_Locations[Count]->Name, chr_Tag1);

			// Mesh_Pos
			App->CL10_Ini->GetString(buff, "Mesh_Position", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Current_Position.x = x;
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Current_Position.y = y;
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Current_Position.z = z;

			App->CL10_Ini->GetString(buff, "Physics_Position", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Physics_Position.setX(x);
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Physics_Position.setY(y);
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Physics_Position.setZ(z);

			App->CL10_Ini->GetString(buff, "Physics_Rotation", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.setW(w);
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.setX(x);
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.setY(y);
			App->GDCL_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.setZ(z);

			Count++;

		}

		App->GDCL_Scene_Data->Player_Location_Count = Count;

	}

	int Int_Tag = 0;
	Int_Tag = App->CL10_Ini->GetInt("Counters", "Location_ID_Counter", 0, 10);
	//App->GDCL_Scene_Data->Locations_ID_Counter = Int_Tag;

	return 1;
}

// *************************************************************************
// *					Load_Stock_Sound40   Terry Bernie  				   *
// *************************************************************************
bool GD10_Load_Scene::Load_Stock_Sounds40()
{
	App->GDCL_Scene_Data->Stock_Sound_Count = 0;

	char PathTemp[1024];
	strcpy(PathTemp, SubFolder);
	strcat(PathTemp, "\\");
	strcat(PathTemp, App->GDCL_Scene_Data->S_Scene[0]->LevelName);
	strcat(PathTemp, ".gss");

	bool test = App->GDCL_Utilities->Search_Folder_ForFile("", PathTemp);

	if (test == 0)
	{
		App->Say("No Position File Found");
		return 1;
	}
	else
	{
		App->CL10_Ini->SetPathName(PathTemp);

		char chr_Tag1[1024];
		int Int_Tag = 0;
		int Int_Count = 0;
		float x = 0;

		Int_Count = App->CL10_Ini->GetInt("Sounds", "Sounds_Count", 0, 10);

		int Count = 0;
		while (Count < Int_Count)
		{
			if (App->GDCL_Scene_Data->St_Sounds[Count])
			{
				delete App->GDCL_Scene_Data->St_Sounds[Count];
				App->GDCL_Scene_Data->St_Sounds[Count] = NULL;
			}

			char n_buff[255];
			char buff[255];
			strcpy(buff, "Sound_");
			itoa(Count, n_buff, 10);
			strcat(buff, n_buff);

			App->GDCL_Scene_Data->St_Sounds[Count] = new Stock_Sound_type();
			App->GDCL_Scene_Data->St_Sounds[Count]->Deleted = 0;


			Int_Tag = App->CL10_Ini->GetInt(buff, "Sound_ID", 0, 10);
			App->GDCL_Scene_Data->St_Sounds[Count]->Sound_ID = Int_Tag;

			App->CL10_Ini->GetString(buff, "Name", chr_Tag1, 1024);
			strcpy(App->GDCL_Scene_Data->St_Sounds[Count]->Name, chr_Tag1);

			App->CL10_Ini->GetString(buff, "SoundFile", chr_Tag1, 1024);
			strcpy(App->GDCL_Scene_Data->St_Sounds[Count]->SoundFile, chr_Tag1);

			App->CL10_Ini->GetString(buff, "Volume", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f", &x);
			App->GDCL_Scene_Data->St_Sounds[Count]->Volume = x;

			Count++;

		}

		App->GDCL_Scene_Data->Stock_Sound_Count = Count;

	}

	int Int_Tag = 0;
	Int_Tag = App->CL10_Ini->GetInt("Counters", "Sounds_ID_Counter", 0, 10);
	//App->GDCL_Scene_Data->StockSounds_ID_Counter = Int_Tag;

	return 1;
}

// *************************************************************************
// *					Load_Config_File   Terry Bernie  				   *
// *************************************************************************
bool GD10_Load_Scene::Load_Config_File()
{
	char Tag1[256];
	char ReadBuf[256];
	bool mBool = 0;
	char FileName[2048];
	strcpy(FileName, App->GameDirecory_FullPath);
	strcat(FileName, "\\Config.cfg");

	App->CL10_Ini->SetPathName(FileName);

	mBool = App->CL10_Ini->GetBool("Config", "Full_Screen", 1);
	App->Ogre17->Full_Screen = mBool;
	return 1;
}