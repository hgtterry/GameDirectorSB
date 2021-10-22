#include "StdAfx.h"
#include "resource.h"
#include "GD19_App.h"
#include "GD19_Load_Scene.h"

#pragma warning( disable : 4800)

GD19_Load_Scene::GD19_Load_Scene(void)
{
	LoadScene = NULL;
	LoadObjects = NULL;

	File_Is_Loading = 0;
}


GD19_Load_Scene::~GD19_Load_Scene(void)
{
}

// *************************************************************************
// *	  				OpenScene Terry Bernie							   *
// *************************************************************************
bool GD19_Load_Scene::OpenScene(bool AskForScene)
{
	if (AskForScene == 1)
	{
		int test = App->CL_Vm_FileIO->OpenFile("Scene Files   *.gdscene\0*.gdscene\0", "gdscene", "Media\\Levels");
		if (test == 0) { return 1; }
	}


	File_Is_Loading = 1; // Signal File is loading 

	App->CL_Vm_FileIO->Update_File_Info(App->CL_Vm_FileIO->Scene_Path_FileName, App->CL_Vm_FileIO->Scene_FileName);

	gdLoader_LoadGDScene_New(); // Load All of the Scene

	SetWindowText(App->MainHwnd, App->CL_Vm_FileIO->Scene_Path_FileName);

	File_Is_Loading = 0; // Signal File is Loaded 

	App->Cl_FileView->Redraw_FileView(); // Leave this call here for the Moment

	if (App->Cl_Scene_Data->ObjectCount > 1)
	{
		App->Cl_FileView->Select_Item(1);
	}
	
	return 1;
}

// *************************************************************************
// *				gdLoader_LoadGDScene_New   Terry Bernie  			   *
// *************************************************************************
bool GD19_Load_Scene::gdLoader_LoadGDScene_New()
{
	LoadScene = NULL;
	char Tag1[1024];
	int ObjectsCount = 0;
	int TagFloat = 0;
	int TagInt = 0;

	App->Cl_Ini->SetPathName(App->CL_Vm_FileIO->Scene_Path_FileName);

	////========== Version
	
	App->Cl_Ini->GetString("GDScene", "Version", Tag1, 1024);
	strcpy(App->Cl_Scene_Data->S_Scene[0]->SceneVersion, Tag1);	// Save for later

	int result = strcmp(Tag1, "4.0");
	if (result == 0)
	{
		TagInt = App->Cl_Ini->GetInt("GDScene", "Type", 0, 10);
		App->Cl_Scene_Data->S_Scene[0]->SceneType = TagInt;
		Load_Scene40();
	}

	// Erro Check;

	return 1;
}


// *************************************************************************
//						Load_Scene40 Terry Bernie						   *
// *************************************************************************
void GD19_Load_Scene::Load_Scene40()
{
	App->Cl_Scene_Data->ClearScene();
	
	Load_Player40();
	Load_Environment40();
	Load_Objects40();
	Populate_Level40();

	//// New Folder for Data
	SubFolder[0] = 0;
	strcpy(SubFolder, App->LevelDirectory);
	strcat(SubFolder, App->Cl_Scene_Data->S_Scene[0]->LevelName);
	strcat(SubFolder, "_Data");

	Load_Player_Locations40();
	Load_Stock_Sounds40();
}



// *************************************************************************
//						Load_Player40 Terry Bernie						   *
// *************************************************************************
bool GD19_Load_Scene::Load_Player40()
{
	//char chr_Tag1[1024];
	//float x = 0;
	//float y = 0;
	//float z = 0;

	//// Name
	//App->Cl_Ini->GetString("Player", "Name", chr_Tag1, 1024);
	//strcpy(App->SBC_Player->PlayerName, chr_Tag1);
	//
	//// Position
	//App->Cl_Ini->GetString("Player", "Start_Position", chr_Tag1, 1024);
	//sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	//App->Cl_Player->StartPos.x = x;
	//App->Cl_Player->StartPos.y = y;
	//App->Cl_Player->StartPos.z = z;

	//App->Cl_Ini->GetString("Player", "Shape", chr_Tag1, 1024); // Capsule

	//x = App->Cl_Ini->Get_Float("Player", "Mass");
	//y = App->Cl_Ini->Get_Float("Player", "Radius");
	//z = App->Cl_Ini->Get_Float("Player", "Height");

	//App->Cl_Player->Capsule_Mass = x;
	//App->Cl_Player->Capsule_Radius = y;
	//App->Cl_Player->Capsule_Height = z;

	//x = App->Cl_Ini->Get_Float("Player", "Ground_Speed");
	//if (x == 0) { x = 2.220; }
	//App->Cl_Player->Ground_speed = x;

	//x = App->Cl_Ini->Get_Float("Player", "Cam_Height");
	//if (x == 0) { x = 6.00; }
	//App->Cl_Player->PlayerHeight = x;

	return 1;
}

// *************************************************************************
//						Load_Environment40 Terry Bernie					   *
// *************************************************************************
bool GD19_Load_Scene::Load_Environment40()
{
	char chr_Tag1[1024];
	int Int_Tag = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	// Visibility
	Int_Tag = App->Cl_Ini->GetInt("Environment", "Fog_Visible", 0, 10);
	App->Cl_Scene_Data->S_Scene[0]->Fog[0].FogOn = Int_Tag;

	// Mode
	Int_Tag = App->Cl_Ini->GetInt("Environment", "Fog_Mode", 0, 10);
	App->Cl_Scene_Data->S_Scene[0]->Fog[0].Mode = Int_Tag;

	// Colour
	App->Cl_Ini->GetString("Environment", "Fog_Colour", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.x = x;
	App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.y = y;
	App->Cl_Scene_Data->S_Scene[0]->Fog[0].Colour.z = z;

	x = App->Cl_Ini->Get_Float("Environment", "Fog_Density");
	y = App->Cl_Ini->Get_Float("Environment", "Fog_Start");
	z = App->Cl_Ini->Get_Float("Environment", "Fog_End");

	App->Cl_Scene_Data->S_Scene[0]->Fog[0].Density = x;
	App->Cl_Scene_Data->S_Scene[0]->Fog[0].Start = y;
	App->Cl_Scene_Data->S_Scene[0]->Fog[0].End = z;

	// Light 
	App->Cl_Ini->GetString("Environment", "Light_Ambient", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->Cl_Scene_Data->S_Scene[0]->AmbientColour.x = x;
	App->Cl_Scene_Data->S_Scene[0]->AmbientColour.y = y;
	App->Cl_Scene_Data->S_Scene[0]->AmbientColour.z = z;

	App->Cl_Ini->GetString("Environment", "Light_Diffuse", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.x = x;
	App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.y = y;
	App->Cl_Scene_Data->S_Scene[0]->DiffuseColour.z = z;

	App->Cl_Ini->GetString("Environment", "Light_Specular", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->Cl_Scene_Data->S_Scene[0]->SpecularColour.x = x;
	App->Cl_Scene_Data->S_Scene[0]->SpecularColour.y = y;
	App->Cl_Scene_Data->S_Scene[0]->SpecularColour.z = z;

	App->Cl_Ini->GetString("Environment", "Light_Position", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
	App->Cl_Scene_Data->S_Scene[0]->Light_Position.x = x;
	App->Cl_Scene_Data->S_Scene[0]->Light_Position.y = y;
	App->Cl_Scene_Data->S_Scene[0]->Light_Position.z = z;

	// Sound 
	App->Cl_Ini->GetString("Environment", "Sound_Track", chr_Tag1, 1024);
	strcpy(App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFile, chr_Tag1);
	strcpy(App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFileAndPath, App->Cl_SoundMgr->Default_Folder);
	strcat(App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFileAndPath, "\\Media\\Sounds\\");
	strcat(App->Cl_Scene_Data->S_Scene[0]->Sound[0].SoundFileAndPath, chr_Tag1);
	App->Cl_SoundMgr->Remeber_SoundFile(chr_Tag1);

	x = App->Cl_Ini->Get_Float("Environment", "Sound_Volume");
	App->Cl_Scene_Data->S_Scene[0]->Sound[0].Volume = x;

	Int_Tag = App->Cl_Ini->GetInt("Environment", "Sound_Play", 0, 10);
	App->Cl_Scene_Data->S_Scene[0]->Sound[0].Play = Int_Tag;

	Int_Tag = App->Cl_Ini->GetInt("Environment", "Sound_Loop", 0, 10);
	App->Cl_Scene_Data->S_Scene[0]->Sound[0].Loop = Int_Tag;

	// Sky
	Int_Tag = App->Cl_Ini->GetInt("Environment", "Sky_Enabled", 0, 10);
	App->Cl_Scene_Data->S_Scene[0]->Sky[0].Enabled = Int_Tag;

	Int_Tag = App->Cl_Ini->GetInt("Environment", "Sky_Type", 0, 10);
	App->Cl_Scene_Data->S_Scene[0]->Sky[0].type = Int_Tag;

	App->Cl_Ini->GetString("Environment", "Sky_Material", chr_Tag1, 1024);
	strcpy(App->Cl_Scene_Data->S_Scene[0]->Sky[0].Material, chr_Tag1);

	x = App->Cl_Ini->Get_Float("Environment", "Sky_Distance");
	y = App->Cl_Ini->Get_Float("Environment", "Sky_Tiling");
	z = App->Cl_Ini->Get_Float("Environment", "Sky_Curvature");

	App->Cl_Scene_Data->S_Scene[0]->Sky[0].Distance = x;
	App->Cl_Scene_Data->S_Scene[0]->Sky[0].Tiling = y;
	App->Cl_Scene_Data->S_Scene[0]->Sky[0].Curvature = z;

	
	return 1;
}

// *************************************************************************
//						Load_Objects40 Terry Bernie						   *
// *************************************************************************
bool GD19_Load_Scene::Load_Objects40()
{
	char chr_Tag1[1024];
	int Int_Tag = 0;
	bool bool_Tag = 0;
	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	Int_Tag = App->Cl_Ini->GetInt("Objects", "Objects_Count", 0, 10);

	int Object_Count = Int_Tag;
	int Count = 0;
	while (Count < Object_Count)
	{
		
		App->Cl_Scene_Data->Cl_Object[Count] = new GD19_Objects();

		char n_buff[255];
		char buff[255];
		strcpy(buff, "Object_");
		_itoa(Count, n_buff, 10);
		strcat(buff, n_buff);

		Int_Tag = App->Cl_Ini->GetInt(buff, "Object_ID", 0, 10);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Object_ID = Int_Tag;

		App->Cl_Ini->GetString(buff, "Object_Name", chr_Tag1, 1024);
		
		strcpy(App->Cl_Scene_Data->Cl_Object[Count]->Name, chr_Tag1);

		App->Cl_Ini->GetString(buff, "Object_Mesh", chr_Tag1, 1024);
		
		strcpy(App->Cl_Scene_Data->Cl_Object[Count]->MeshName, chr_Tag1);

		// Type
		Int_Tag = App->Cl_Ini->GetInt(buff, "Object_Type", 0, 10);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Type = Int_Tag;

		// Shape
		Int_Tag = App->Cl_Ini->GetInt(buff, "Object_Shape", 0, 10);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Shape = Int_Tag;

		// Usage
		Int_Tag = App->Cl_Ini->GetInt(buff, "Object_Usage", 0, 10);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Usage = Int_Tag;

		// Folder
		Int_Tag = App->Cl_Ini->GetInt(buff, "Object_Folder", 0, 10);
	
		App->Cl_Scene_Data->Cl_Object[Count]->Folder = Int_Tag;

		// Mesh_Pos
		App->Cl_Ini->GetString(buff, "Object_Mesh_Pos", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Pos.x = x;
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Pos.y = y;
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Pos.z = z;

		// Mesh_Rot
		App->Cl_Ini->GetString(buff, "Object_Mesh_Rot", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Rot.x = x;
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Rot.y = y;
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Rot.z = z;

		// Mesh_Quat
		App->Cl_Ini->GetString(buff, "Object_Mesh_Quat", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Quat.w = w;
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Quat.x = x;
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Quat.y = y;
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Quat.z = z;

		// Mesh_Scale
		App->Cl_Ini->GetString(buff, "Object_Mesh_Scale", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Scale.x = x;
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Scale.y = y;
		App->Cl_Scene_Data->Cl_Object[Count]->Mesh_Scale.z = z;

		////------------------------------------------------------------- Physics

		x = App->Cl_Ini->Get_Float(buff, "Physics_Mass");
		y = App->Cl_Ini->Get_Float(buff, "Physics_Restitution");
		
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Mass = x;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Restitution = y;

		// Physics_Pos
		App->Cl_Ini->GetString(buff, "Physics_Pos", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Pos.x = x;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Pos.y = y;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Pos.z = z;

		// Physics_Rot
		App->Cl_Ini->GetString(buff, "Physics_Rot", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Rot.x = x;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Rot.y = y;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Rot.z = z;

		// Physics_Quat
		App->Cl_Ini->GetString(buff, "Physics_Quat", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Quat.w = w;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Quat.x = x;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Quat.y = y;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Quat.z = z;
		
		// Physics_Scale
		App->Cl_Ini->GetString(buff, "Physics_Scale", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Scale.x = x;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Scale.y = y;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Scale.z = z;

		// Physics_Size
		App->Cl_Ini->GetString(buff, "Physics_Size", chr_Tag1, 1024);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Size.x = x;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Size.y = y;
		App->Cl_Scene_Data->Cl_Object[Count]->Physics_Size.z = z;
	
		// Stock
		App->Cl_Ini->GetString(buff, "Stock_Text", chr_Tag1, 1024);
		
		strcpy(App->Cl_Scene_Data->Cl_Object[Count]->Entity[0].mTextItem, chr_Tag1);

	
		//-------------------------- 
		if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Sound)
		{
			char buff[1024];
			strcpy(buff, App->Cl_SoundMgr->Default_Folder);
			strcat(buff, "\\Media\\Sounds\\");
			strcat(buff, chr_Tag1);

			strcpy(App->Cl_Scene_Data->Cl_Object[Count]->Entity[0].mFileAndPath, buff);
		}
		////-------------------------- 

		// Stock Name
		App->Cl_Ini->GetString(buff, "Stock_Name", chr_Tag1, 1024);
		
		strcpy(App->Cl_Scene_Data->Cl_Object[Count]->Entity[0].Stock_mName, chr_Tag1);

		Int_Tag = App->Cl_Ini->GetInt(buff, "Stock_Index", 0, 10);
		
		App->Cl_Scene_Data->Cl_Object[Count]->Entity[0].Stock_mIndex = Int_Tag;

		// Has Sound
		bool_Tag = App->Cl_Ini->GetBool(buff, "Has_Sound", 0);
		
		App->Cl_Scene_Data->Cl_Object[Count]->HasSound = bool_Tag;

		// new sound v2
		
		Int_Tag = App->Cl_Ini->GetInt(buff, "Sound_ID", 0, 10);
		App->Cl_Scene_Data->Cl_Object[Count]->Sound_ID_v2 = Int_Tag;

		Int_Tag = App->Cl_Ini->GetInt(buff, "Play", 0, 10);
		App->Cl_Scene_Data->Cl_Object[Count]->Play_v2 = Int_Tag;



		if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Move)
		{
			Load_MoveEntity40(Count);
		}

		if (App->Cl_Scene_Data->Cl_Object[Count]->Usage == Enums::Usage_Teleport)
		{
			// Create Teleport and use Player Start Position as Default
		
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0] = new Teleport_type2;
			App->Cl_Ini->GetString(buff, "Goto", chr_Tag1, 1024);

			
			strcpy(App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Name, chr_Tag1);

			// Mesh_Pos
			App->Cl_Ini->GetString(buff, "Mesh_Position", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
			
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Player_Position.x = x;
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Player_Position.y = y;
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Player_Position.z = z;

			App->Cl_Ini->GetString(buff, "Physics_Position", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
			
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Position.setX(x);
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Position.setY(y);
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Position.setZ(z);

			App->Cl_Ini->GetString(buff, "Physics_Rotation", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);
			
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Rotation.setW(w);
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Rotation.setX(x);
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Rotation.setY(y);
			App->Cl_Scene_Data->Cl_Object[Count]->S_Teleport[0]->Physics_Rotation.setZ(z);
		}

		Count++;
	}

	// j
	Int_Tag = App->Cl_Ini->GetInt("Counters", "Object_ID_Counter", 0, 10);
	App->Cl_Scene_Data->Object_ID_Counter = Int_Tag;

	App->Cl_Scene_Data->ObjectCount = Count;

	return 1;
}

// *************************************************************************
// *					Load_MoveEntity40 Terry Bernie  				   *
// *************************************************************************
void GD19_Load_Scene::Load_MoveEntity40(int Count)
{
	char chr_Tag1[1024];
	int Int_Tag = 0;

	float x = 0;
	float y = 0;

	char n_buff[255];
	char buff[255];
	strcpy(buff, "Object_");
	_itoa(Count, n_buff, 10);
	strcat(buff, n_buff);

	int result = 0;

	
	App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType = new Move_Type2;
	App->Cl_Scene_Data->Set_Move_Defaults(Count); // ?

	App->Cl_Ini->GetString(buff, "Object_To_Move", chr_Tag1, 1024);
	
	strcpy(App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Object_Name, chr_Tag1);

	Int_Tag = App->Cl_Ini->GetInt(buff, "Object_Index", 0, 10);
	
	App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Object_Index = Int_Tag;

	Int_Tag = App->Cl_Ini->GetInt(buff, "Move_Object_ID", 0, 10);
	
	App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Object_ID = Int_Tag;

	App->Cl_Ini->GetString(buff, "Data", chr_Tag1, 1024);
	sscanf(chr_Tag1, "%f,%f,%i", &x, &y, &Int_Tag);
	
	App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Distance = x;
	App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->Speed = y;
	App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->IsNegative = Int_Tag;

	Int_Tag = App->Cl_Ini->GetInt(buff, "Axi", 0, 10);

	App->Cl_Scene_Data->Cl_Object[Count]->S_MoveType->WhatDirection = Int_Tag;

}

// *************************************************************************
// *				LoadOptionsDetails40   Terry Bernie  				   *
// *************************************************************************
bool GD19_Load_Scene::LoadOptionsDetails40()
{
	int TagInt_1 = 0;
	int TagInt_2 = 0;
	int TagInt_3 = 0;
	int TagInt_4 = 0;
	int TagInt_5 = 0;
	int TagInt_6 = 0;

	TagInt_1 = App->Cl_Ini->GetInt("Options", "Has_Planes", 0, 10);
	TagInt_2 = App->Cl_Ini->GetInt("Options", "Has_Objects", 0, 10);
	TagInt_3 = App->Cl_Ini->GetInt("Options", "Has_Particles", 0, 10);
	TagInt_4 = App->Cl_Ini->GetInt("Options", "Has_Weapons", 0, 10);
	TagInt_5 = App->Cl_Ini->GetInt("Options", "Has_Player", 0, 10);
	TagInt_6 = App->Cl_Ini->GetInt("Options", "Has_Debug", 0, 10);

	App->Cl_Scene_Data->S_LoadOptions[0]->Has_Planes = (bool)TagInt_1;
	App->Cl_Scene_Data->S_LoadOptions[0]->Has_Objects = (bool)TagInt_2;
	App->Cl_Scene_Data->S_LoadOptions[0]->Has_Particles = (bool)TagInt_3;
	App->Cl_Scene_Data->S_LoadOptions[0]->Has_Weapons = (bool)TagInt_4;
	App->Cl_Scene_Data->S_LoadOptions[0]->Has_Player = (bool)TagInt_5;
	App->Cl_Scene_Data->S_LoadOptions[0]->Has_Debug = (bool)TagInt_6;

	return 1;
}

// *************************************************************************
//						LoadCameraDetails Terry Bernie					   *
// *************************************************************************
bool GD19_Load_Scene::LoadCameraDetails()
{
	
	return 1;
}

// *************************************************************************
//						Populate_Level30 Terry Bernie					   *
// *************************************************************************
bool GD19_Load_Scene::Populate_Level40()
{
	strcpy(App->Cl_FileView->LevelName, App->Cl_Scene_Data->S_Scene[0]->LevelName);

	App->Cl_FileView->Delete_AllItems(); // Bit Bruttle

	App->Cl_Environment->Load_Environment();

	if(App->Cl_Scene_Data->S_LoadOptions[0]->Has_Player == 1)
	{
		App->SBC_Player->Load_Player();
	}

	if(App->Cl_Scene_Data->S_LoadOptions[0]->Has_Objects == 1)
	{
		App->Cl_Objects_FFile->Add_Objects_FromFile();
	}

	if(App->Cl_Scene_Data->S_LoadOptions[0]->Has_Player == 1)
	{
		App->SBC_Player->PlayerAdded = 1;
	}

	App->Cl_Scene_Data->SceneLoaded = 1;
	App->Cl_Bullet->GD_Physics_On = 1;
	App->Cl19_Ogre->OgreListener->GD_Run_Physics = 1;
	//App->RedrawWindow_Dlg(App->Physics_Console_Hwnd);

	return 1;
}

// *************************************************************************
// *				Load_Player_Locations40   Terry Bernie  			   *
// *************************************************************************
bool GD19_Load_Scene::Load_Player_Locations40()
{
	App->Cl_Scene_Data->Player_Location_Count = 0;

	char PathTemp[1024];
	strcpy(PathTemp, SubFolder);
	strcat(PathTemp, "\\");
	strcat(PathTemp, App->Cl_Scene_Data->S_Scene[0]->LevelName);
	strcat(PathTemp, ".gpl");

	bool test = App->CL_Vm_FileIO->SearchFolders("", PathTemp);

	if (test == 0)
	{
		App->Say("No Position File Found");
		return 1;
	}
	else
	{
		char buff[1024];
		strcpy(buff, App->LevelDirectory);
		strcat(buff, App->Cl_Scene_Data->S_Scene[0]->LevelName);
		strcat(buff, ".gpl");

		App->Cl_Ini->SetPathName(PathTemp);

		char chr_Tag1[1024];
		int Int_Tag = 0;
		int Int_Count = 0;
		float w = 0;
		float x = 0;
		float y = 0;
		float z = 0;

		Int_Count = App->Cl_Ini->GetInt("Locations", "Locations_Count", 0, 10);

		int Count = 0;
		while (Count < Int_Count)
		{
			if (App->Cl_Scene_Data->S_Player_Locations[Count])
			{
				delete App->Cl_Scene_Data->S_Player_Locations[Count];
				App->Cl_Scene_Data->S_Player_Locations[Count] = NULL;
			}

			char n_buff[255];
			char buff[255];
			strcpy(buff, "Location_");
			_itoa(Count, n_buff, 10);
			strcat(buff, n_buff);

			App->Cl_Scene_Data->S_Player_Locations[Count] = new Player_Location_type();
			App->Cl_Scene_Data->S_Player_Locations[Count]->Deleted = 0;


			Int_Tag = App->Cl_Ini->GetInt(buff, "Locatoin_ID", 0, 10);
			App->Cl_Scene_Data->S_Player_Locations[Count]->Location_ID = Int_Tag;

			App->Cl_Ini->GetString(buff, "Name", chr_Tag1, 1024);


			strcpy(App->Cl_Scene_Data->S_Player_Locations[Count]->Name, chr_Tag1);

			// Mesh_Pos
			App->Cl_Ini->GetString(buff, "Mesh_Position", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
			App->Cl_Scene_Data->S_Player_Locations[Count]->Current_Position.x = x;
			App->Cl_Scene_Data->S_Player_Locations[Count]->Current_Position.y = y;
			App->Cl_Scene_Data->S_Player_Locations[Count]->Current_Position.z = z;

			App->Cl_Ini->GetString(buff, "Physics_Position", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
			App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Position.setX(x);
			App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Position.setY(y);
			App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Position.setZ(z);

			App->Cl_Ini->GetString(buff, "Physics_Rotation", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);
			App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.setW(w);
			App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.setX(x);
			App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.setY(y);
			App->Cl_Scene_Data->S_Player_Locations[Count]->Physics_Rotation.setZ(z);

			Count++;

		}

		App->Cl_Scene_Data->Player_Location_Count = Count;

	}

	int Int_Tag = 0;
	Int_Tag = App->Cl_Ini->GetInt("Counters", "Location_ID_Counter", 0, 10);
	App->Cl_Scene_Data->Locations_ID_Counter = Int_Tag;

	return 1;
}

// *************************************************************************
// *					Load_Stock_Sound40   Terry Bernie  				   *
// *************************************************************************
bool GD19_Load_Scene::Load_Stock_Sounds40()
{
	App->Cl_Scene_Data->Stock_Sound_Count = 0;

	char PathTemp[1024];
	strcpy(PathTemp, SubFolder);
	strcat(PathTemp, "\\");
	strcat(PathTemp, App->Cl_Scene_Data->S_Scene[0]->LevelName);
	strcat(PathTemp, ".gss");

	bool test = App->CL_Vm_FileIO->SearchFolders("", PathTemp);

	if (test == 0)
	{
		App->Say("No Position File Found");
		return 1;
	}
	else
	{
		App->Cl_Ini->SetPathName(PathTemp);

		char chr_Tag1[1024];
		int Int_Tag = 0;
		int Int_Count = 0;
		float x = 0;
		
		Int_Count = App->Cl_Ini->GetInt("Sounds", "Sounds_Count", 0, 10);

		int Count = 0;
		while (Count < Int_Count)
		{
			if (App->Cl_Scene_Data->St_Sounds[Count])
			{
				delete App->Cl_Scene_Data->St_Sounds[Count];
				App->Cl_Scene_Data->St_Sounds[Count] = NULL;
			}

			char n_buff[255];
			char buff[255];
			strcpy(buff, "Sound_");
			_itoa(Count, n_buff, 10);
			strcat(buff, n_buff);

			App->Cl_Scene_Data->St_Sounds[Count] = new Stock_Sound_type();
			App->Cl_Scene_Data->St_Sounds[Count]->Deleted = 0;


			Int_Tag = App->Cl_Ini->GetInt(buff, "Sound_ID", 0, 10);
			App->Cl_Scene_Data->St_Sounds[Count]->Sound_ID = Int_Tag;

			App->Cl_Ini->GetString(buff, "Name", chr_Tag1, 1024);
			strcpy(App->Cl_Scene_Data->St_Sounds[Count]->Name, chr_Tag1);

			App->Cl_Ini->GetString(buff, "SoundFile", chr_Tag1, 1024);
			strcpy(App->Cl_Scene_Data->St_Sounds[Count]->SoundFile, chr_Tag1);

			App->Cl_Ini->GetString(buff, "Volume", chr_Tag1, 1024);
			sscanf(chr_Tag1, "%f", &x);
			App->Cl_Scene_Data->St_Sounds[Count]->Volume = x;

			Count++;

		}

		App->Cl_Scene_Data->Stock_Sound_Count = Count;

	}

	int Int_Tag = 0;
	Int_Tag = App->Cl_Ini->GetInt("Counters", "Sounds_ID_Counter", 0, 10);
	App->Cl_Scene_Data->StockSounds_ID_Counter = Int_Tag;

	return 1;
}








