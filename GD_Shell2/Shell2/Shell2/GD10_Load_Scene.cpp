#include "StdAfx.h"
#include "BT_App.h"
#include "GD10_Load_Scene.h"

#pragma warning( disable : 4800)

GD10_Load_Scene::GD10_Load_Scene()
{
	m_Ini_Path_File_Name[0] = 0;

	Scene_FileName[0] = 0;
	Scene_Path_FileName[0] = 0;
	m_Game_Name[0] = 0;
}


GD10_Load_Scene::~GD10_Load_Scene()
{
}

// *************************************************************************
// *	  				OpenScene Terry Bernie							   *
// *************************************************************************
bool GD10_Load_Scene::OpenScene(bool AskForScene)
{
	Load_Project();
	return 1;
}

// *************************************************************************
// *	  		Load_Project:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool GD10_Load_Scene::Load_Project()
{

	m_Ini_Path_File_Name[0] = 0;

	//App->SBC_Scene->Clear_Level();
	App->GDCL_Scene_Data->Create_Resources_Group();

	Set_Paths();

	//// ------------------------------------------------------------------- 
	Load_Options* Options = new Load_Options;

	Options->Has_Aera = 0;
	Options->Has_Player = 0;
	Options->Has_Camera = 0;
	Options->Has_Objects = 0;
	Options->Has_Counters = 0;

	int Int1 = 0;
	char chr_Tag1[1024];
	char chr_Tag2[1024];

	chr_Tag1[0] = 0;
	chr_Tag2[0] = 0;

	App->CL10_Ini->SetPathName(m_Ini_Path_File_Name);

	App->CL10_Ini->GetString("Version_Data", "Version", chr_Tag1, 1024);

	App->CL10_Ini->GetString("Files", "Level_Name", m_Level_Name, MAX_PATH);
	App->CL10_Ini->GetString("Files", "Project_Name", m_Project_Name, MAX_PATH);
	
	Options->Has_Aera = App->CL10_Ini->GetInt("Options", "Aeras_Count", 0, 10);
	Options->Has_Player = App->CL10_Ini->GetInt("Options", "Players_Count", 0, 10);
	Options->Has_Camera = App->CL10_Ini->GetInt("Options", "Cameras_Count", 0, 10);
	Options->Has_Objects = App->CL10_Ini->GetInt("Options", "Objects_Count", 0, 10);
	Options->Has_Counters = App->CL10_Ini->GetInt("Options", "Counters_Count", 0, 10);


	//App->SBC_Scene->UniqueID_Object_Counter = App->Cl_Ini->GetInt("Options", "Objects_ID_Count", 0, 10);
	//App->SBC_Scene->UniqueID_Counters_Count = App->Cl_Ini->GetInt("Options", "Counters_ID_Count", 0, 10);

	////-------------------------------------- Set Resource Path

	Load_Get_Resource_Path();

	//// ------------------------------------- Aera
	if (Options->Has_Aera > 0)
	{
		bool test = Load_Project_Aera();
		App->GDCL_Scene_Data->Area_Added = 1;
		App->GDCL_Environment->Load_Environment();
	}

	// ------------------------------------- Player
	if (Options->Has_Player > 0)
	{
		bool test = Load_Project_Player();
	}

	//// ------------------------------------- Camera
	//if (Options->Has_Camera > 0)
	//{
	//	Load_Project_Camera();
	//	App->SBC_Scene->Camera_Added = 1;
	//	App->SBC_Camera->Set_Camera(0);
	//	App->SBC_FileView->Set_FolderActive(App->SBC_FileView->FV_Cameras_Folder);
	//}

	// ------------------------------------- Objects
	if (Options->Has_Objects > 0)
	{
		Load_Project_Objects();
		App->SBC_Objects_Create->Add_Objects_From_File();
	}

	//// ------------------------------------- Counters
	//if (Options->Has_Counters > 0)
	//{
	//	Load_Project_Counters();
	//	App->SBC_Display->Add_Counters_From_File();

	//}

	//App->Cl19_Ogre->OgreListener->GD_CameraMode = Enums::CamDetached;

	//App->SBC_FileView->Change_Level_Name();
	//App->SBC_FileView->Change_Project_Name();
	//App->SBC_FileView->Redraw_FileView();


	//App->SBC_Scene->Scene_Loaded = 1;
	//App->SBC_Project->Project_Loaded = 1;

	//delete Options;

	//App->Set_Main_TitleBar(App->SBC_FileIO->Project_Path_File_Name);
	//App->SBC_FileIO->RecentFileHistory_Update();

	//App->SBC_FileView->SelectItem(App->SBC_FileView->FV_LevelFolder);

	//App->SBC_Scene->Scene_Modified = 0;
	return 1;
}

// *************************************************************************
// *	  	Load_Project_Objects:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool GD10_Load_Scene::Load_Project_Objects()
{
	char Object_Ini_Path[MAX_PATH];
	char chr_Tag1[MAX_PATH];
	int Object_Count = 0;

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	strcpy(Object_Ini_Path, m_Project_Sub_Folder);
	strcat(Object_Ini_Path, "\\");

	strcat(Object_Ini_Path, m_Level_Name);
	strcat(Object_Ini_Path, "\\");

	strcat(Object_Ini_Path, "Objects");
	strcat(Object_Ini_Path, "\\");

	//---------------------------------------------------

	strcat(Object_Ini_Path, "Objects.efd");

	App->CL10_Ini->SetPathName(Object_Ini_Path);

	Object_Count = App->CL10_Ini->GetInt("Counters", "Objects_Count", 0);

	int Count = 0;

	while (Count < Object_Count)
	{
		char n_buff[255];
		char buff[255];
		strcpy(buff, "Object_");
		_itoa(Count, n_buff, 10);
		strcat(buff, n_buff);

		App->GDCL_Scene_Data->B_Object[Count] = new Base_Object();
		Base_Object* Object = App->GDCL_Scene_Data->B_Object[Count];

		App->CL10_Ini->GetString(buff, "Mesh_Name", Object->Mesh_Name, MAX_PATH);
		App->CL10_Ini->GetString(buff, "Mesh_File", Object->Mesh_FileName, MAX_PATH);
		App->CL10_Ini->GetString(buff, "Mesh_Resource_Path", Object->Mesh_Resource_Path, MAX_PATH);
		App->CL10_Ini->GetString(buff, "Material_File", Object->Material_File, MAX_PATH);

		// Types
		Object->This_Object_ID = App->CL10_Ini->GetInt(buff, "Object_ID", 0);
		Object->Type = App->CL10_Ini->GetInt(buff, "Object_Type", 0);
		Object->Shape = App->CL10_Ini->GetInt(buff, "Object_Shape", 0);
		Object->Usage = App->CL10_Ini->GetInt(buff, "Object_Usage", 0);

		// Pos
		App->CL10_Ini->GetString(buff, "Mesh_Pos", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Object[Count]->Mesh_Pos = Ogre::Vector3(x, y, z);

		// Scale
		App->CL10_Ini->GetString(buff, "Mesh_Scale", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Object[Count]->Mesh_Scale = Ogre::Vector3(x, y, z);

		// Rotation
		App->CL10_Ini->GetString(buff, "Mesh_Rot", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Object[Count]->Mesh_Rot = Ogre::Vector3(x, y, z);

		// Mesh_Quat
		App->CL10_Ini->GetString(buff, "Mesh_Quat", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);

		App->GDCL_Scene_Data->B_Object[Count]->Mesh_Quat.w = w;
		App->GDCL_Scene_Data->B_Object[Count]->Mesh_Quat.x = x;
		App->GDCL_Scene_Data->B_Object[Count]->Mesh_Quat.y = y;
		App->GDCL_Scene_Data->B_Object[Count]->Mesh_Quat.z = z;

		// Physics_Quat
		App->CL10_Ini->GetString(buff, "Physics_Quat", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);

		App->GDCL_Scene_Data->B_Object[Count]->Physics_Quat.w = w;
		App->GDCL_Scene_Data->B_Object[Count]->Physics_Quat.x = x;
		App->GDCL_Scene_Data->B_Object[Count]->Physics_Quat.y = y;
		App->GDCL_Scene_Data->B_Object[Count]->Physics_Quat.z = z;

		//---------------------------------------------------------------------------------- Message Entity
		if (App->GDCL_Scene_Data->B_Object[Count]->Usage == Enums::Usage_Message)
		{
			App->CL10_Ini->GetString(buff, "Message_Text", Object->Message_Text, MAX_PATH);

			App->CL10_Ini->GetString(buff, "Message_Pos", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f,%f", &x, &y);

			App->GDCL_Scene_Data->B_Object[Count]->Message_PosX = x;
			App->GDCL_Scene_Data->B_Object[Count]->Message_PosY = y;

		}

		//---------------------------------------------------------------------------------- Sound Entity
		if (App->GDCL_Scene_Data->B_Object[Count]->Usage == Enums::Usage_Sound)
		{
			App->CL10_Ini->GetString(buff, "Sound_File", Object->Sound_File, MAX_PATH);

			App->CL10_Ini->GetString(buff, "Sound_Volume", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->GDCL_Scene_Data->B_Object[Count]->SndVolume = x;
		}

		//---------------------------------------------------------------------------------- Colectable Entity
		if (App->GDCL_Scene_Data->B_Object[Count]->Usage == Enums::Usage_Colectable)
		{
			App->GDCL_Scene_Data->B_Object[Count]->S_Collectable[0] = new Collectable_type;
			App->SBC_Object->Set_Collectables_Sound_Defaults(Count);

			App->CL10_Ini->GetString(buff, "Col_Sound_File", chr_Tag1, MAX_PATH);
			strcpy(Object->S_Collectable[0]->Sound_File, chr_Tag1);

			App->CL10_Ini->GetString(buff, "Col_Sound_Volume", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->GDCL_Scene_Data->B_Object[Count]->S_Collectable[0]->SndVolume = x;

			App->GDCL_Scene_Data->B_Object[Count]->S_Collectable[0]->Play = App->CL10_Ini->GetInt(buff, "Col_Play", 0);

			App->CL10_Ini->GetString(buff, "Col_Counter_Name", chr_Tag1, MAX_PATH);
			strcpy(Object->S_Collectable[0]->Counter_Name, chr_Tag1);

			App->GDCL_Scene_Data->B_Object[Count]->S_Collectable[0]->Counter_ID = App->CL10_Ini->GetInt(buff, "Col_Counter_ID", 0);

		}

		//---------------------------------------------------------------------------------- Usage_Move
		if (App->GDCL_Scene_Data->B_Object[Count]->Usage == Enums::Usage_Move)
		{

			App->GDCL_Scene_Data->B_Object[Count]->S_MoveType[0] = new Move_Type;
			App->SBC_Object->Set_Move_Defaults(Count); // Check

			// --------------------------- Distance
			App->CL10_Ini->GetString(buff, "Move_Distance", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->GDCL_Scene_Data->B_Object[Count]->S_MoveType[0]->Move_Distance = x;

			App->GDCL_Scene_Data->B_Object[Count]->S_MoveType[0]->IsNegative = App->CL10_Ini->GetInt(buff, "Move_IsNegative", 0);

			// --------------------------- Speed
			App->CL10_Ini->GetString(buff, "Move_Speed", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->GDCL_Scene_Data->B_Object[Count]->S_MoveType[0]->Speed = x;

			// --------------------------- Name
			App->CL10_Ini->GetString(buff, "Move_ObjectName", App->GDCL_Scene_Data->B_Object[Count]->S_MoveType[0]->Object_Name, MAX_PATH);

			App->GDCL_Scene_Data->B_Object[Count]->S_MoveType[0]->Object_To_Move_Index = App->CL10_Ini->GetInt(buff, "Move_ObjectID", 0);
			App->GDCL_Scene_Data->B_Object[Count]->S_MoveType[0]->WhatDirection = App->CL10_Ini->GetInt(buff, "Move_WhatDirection", 0);

			App->CL10_Ini->GetString(buff, "Move_Sound", App->GDCL_Scene_Data->B_Object[Count]->Sound_File, MAX_PATH);
			App->GDCL_Scene_Data->B_Object[Count]->Play_Sound = App->CL10_Ini->GetInt(buff, "Move_Play_Sound", 0);


			// --------------------------- Move_Volume
			App->CL10_Ini->GetString(buff, "Move_Volume", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->GDCL_Scene_Data->B_Object[Count]->SndVolume = x;

		}

		if (App->GDCL_Scene_Data->B_Object[Count]->Usage == Enums::Usage_Teleport)
		{

			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0] = new Teleport_type;
			App->CL10_Ini->GetString(buff, "Tele_Goto", chr_Tag1, MAX_PATH);
			strcpy(App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Name, chr_Tag1);

			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Location_ID = App->CL10_Ini->GetInt(buff, "Tele_ID", 0);

			// Sound
			App->CL10_Ini->GetString(buff, "Tele_Sound", App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Sound_File, MAX_PATH);

			App->CL10_Ini->GetString(buff, "Tele_Volume", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f", &x);
			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->SndVolume = x;

			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Play = App->CL10_Ini->GetInt(buff, "Tele_Play", 0);

			// Mesh_Pos
			App->CL10_Ini->GetString(buff, "Tele_Mesh_Position", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);

			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Player_Position.x = x;
			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Player_Position.y = y;
			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Player_Position.z = z;

			//Player_Pos
			App->CL10_Ini->GetString(buff, "Tele_Physics_Position", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);

			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Physics_Position.setX(x);
			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Physics_Position.setY(y);
			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Physics_Position.setZ(z);

			//Player_Rotation
			App->CL10_Ini->GetString(buff, "Tele_Physics_Rotation", chr_Tag1, MAX_PATH);
			sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);

			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Physics_Rotation.setW(w);
			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Physics_Rotation.setX(x);
			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Physics_Rotation.setY(y);
			App->GDCL_Scene_Data->B_Object[Count]->S_Teleport[0]->Physics_Rotation.setZ(z);
		}

		Count++;
	}

	App->GDCL_Scene_Data->Object_Count = Count;

	return 1;
}

// *************************************************************************
// *	  	Load_Project_Player:- Terry and Hazel Flanigan 2022			   *
// *************************************************************************
bool GD10_Load_Scene::Load_Project_Player()
{
	int Players_Count = 0;
	int Locations_Count = 0;
	char Player_Name[MAX_PATH];
	char Player_Ini_Path[MAX_PATH];
	char chr_Tag1[MAX_PATH];

	float w = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	strcpy(Player_Ini_Path, m_Project_Sub_Folder);
	strcat(Player_Ini_Path, "\\");

	strcat(Player_Ini_Path, m_Level_Name);
	strcat(Player_Ini_Path, "\\");

	strcat(Player_Ini_Path, "Players");
	strcat(Player_Ini_Path, "\\");

	strcat(Player_Ini_Path, "Players.ply");

	App->CL10_Ini->SetPathName(Player_Ini_Path);

	Players_Count = App->CL10_Ini->GetInt("Counters", "Player_Count", 0);

	int Count = 0;
	char Cbuff[255];
	char buff[255];

	while (Count < Players_Count)
	{
		
		strcpy(buff, "Player_");
		_itoa(Count, Cbuff, 10);
		strcat(buff, Cbuff);

		App->SBC_Player->Create_Player_Object();

		App->CL10_Ini->GetString(buff, "Player_Name", Player_Name, MAX_PATH);
		strcpy(App->GDCL_Scene_Data->B_Player[Count]->Player_Name, Player_Name);

		//App->Say(App->GDCL_Scene_Data->B_Player[Count]->Player_Name);

		App->CL10_Ini->GetString(buff, "Start_Position", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Player[Count]->StartPos = Ogre::Vector3(x, y, z);

		App->CL10_Ini->GetString(buff, "Start_Rotation", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);

		App->GDCL_Scene_Data->B_Player[Count]->Physics_Rotation.setW(w);
		App->GDCL_Scene_Data->B_Player[Count]->Physics_Rotation.setX(x);
		App->GDCL_Scene_Data->B_Player[Count]->Physics_Rotation.setY(y);
		App->GDCL_Scene_Data->B_Player[Count]->Physics_Rotation.setZ(z);

		App->CL10_Ini->GetString(buff, "Turn_Rate", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->GDCL_Scene_Data->B_Player[Count]->TurnRate = x;

		Count++;
	}

	// ------------------------------------------ Locations
	int Int_Tag = 0;
	Locations_Count = App->CL10_Ini->GetInt("Locations", "Locations_Count", 0);

	Count = 0;
	while (Count < Locations_Count)
	{
		if (App->GDCL_Scene_Data->B_Locations[Count])
		{
			delete App->GDCL_Scene_Data->B_Locations[Count];
			App->GDCL_Scene_Data->B_Locations[Count] = NULL;
		}

		char n_buff[255];
		char buff[255];
		strcpy(buff, "Location_");
		_itoa(Count, n_buff, 10);
		strcat(buff, n_buff);

		App->GDCL_Scene_Data->B_Locations[Count] = new Base_Locations();
		App->GDCL_Scene_Data->B_Locations[Count]->Deleted = 0;


		Int_Tag = App->CL10_Ini->GetInt(buff, "Locatoin_ID", 0, 10);
		App->GDCL_Scene_Data->B_Locations[Count]->Location_ID = Int_Tag;

		App->CL10_Ini->GetString(buff, "Name", chr_Tag1, MAX_PATH);


		strcpy(App->GDCL_Scene_Data->B_Locations[Count]->Name, chr_Tag1);

		// Mesh_Pos
		App->CL10_Ini->GetString(buff, "Mesh_Position", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Locations[Count]->Current_Position.x = x;
		App->GDCL_Scene_Data->B_Locations[Count]->Current_Position.y = y;
		App->GDCL_Scene_Data->B_Locations[Count]->Current_Position.z = z;

		App->CL10_Ini->GetString(buff, "Physics_Position", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Locations[Count]->Physics_Position.setX(x);
		App->GDCL_Scene_Data->B_Locations[Count]->Physics_Position.setY(y);
		App->GDCL_Scene_Data->B_Locations[Count]->Physics_Position.setZ(z);

		App->CL10_Ini->GetString(buff, "Physics_Rotation", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f,%f", &w, &x, &y, &z);
		App->GDCL_Scene_Data->B_Locations[Count]->Physics_Rotation.setW(w);
		App->GDCL_Scene_Data->B_Locations[Count]->Physics_Rotation.setX(x);
		App->GDCL_Scene_Data->B_Locations[Count]->Physics_Rotation.setY(y);
		App->GDCL_Scene_Data->B_Locations[Count]->Physics_Rotation.setZ(z);

		Count++;

	}

	App->GDCL_Scene_Data->Player_Location_Count = Count;

	App->SBC_Physics->Reset_Physics();
	App->SBC_Physics->Enable_Physics(1);

	return 1;
}

// *************************************************************************
// *	  		Load_Project_Aera:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool GD10_Load_Scene::Load_Project_Aera()
{
	//App->Log_Messageg("bool SB_Project::Load_Project_Aera()");

	char Area_Ini_Path[MAX_PATH];
	char chr_Tag1[MAX_PATH];
	char Area_Name[1024];
	char Mesh_FileName[MAX_PATH];
	char Resource_Location[MAX_PATH];
	int Area_Count = 0;
	int Int_Tag = 0;
	float x = 0;
	float y = 0;
	float z = 0;

	strcpy(Area_Ini_Path, m_Project_Sub_Folder);
	strcat(Area_Ini_Path, "\\");

	strcat(Area_Ini_Path, m_Level_Name);
	strcat(Area_Ini_Path, "\\");

	strcat(Area_Ini_Path, "Areas");
	strcat(Area_Ini_Path, "\\");

	strcat(Area_Ini_Path, "Areas.aer");

	App->CL10_Ini->SetPathName(Area_Ini_Path);

	Area_Count = App->CL10_Ini->GetInt("Counters", "Areas_Count", 0);

	int Count = 0;

	while (Count < Area_Count)
	{

		App->CL10_Ini->GetString("Area_0", "Area_Name", Area_Name, MAX_PATH);
		App->CL10_Ini->GetString("Area_0", "Area_File", Mesh_FileName, MAX_PATH);
		App->CL10_Ini->GetString("Area_0", "Area_Resource_Path", Resource_Location, MAX_PATH);

		App->SBC_Aera->Add_Aera_To_Project(Count, Mesh_FileName, m_Main_Assets_Path);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0] = new Environment_type;
		App->SBC_Aera->Set_Environment_Defaults(Count);

		App->CL10_Ini->GetString("Area_0", "Material_File", App->GDCL_Scene_Data->B_Area[Count]->Material_File, MAX_PATH);

		App->CL10_Ini->GetString("Position", "Mesh_Pos", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);

		App->GDCL_Scene_Data->B_Area[Count]->Area_Node->setPosition(x, y, z);
		App->GDCL_Scene_Data->B_Area[Count]->Phys_Body->getWorldTransform().setOrigin(btVector3(x, y, z));
		App->GDCL_Scene_Data->B_Area[Count]->Physics_Pos = Ogre::Vector3(x, y, z);

		strcpy(App->GDCL_Scene_Data->B_Area[Count]->Area_Name, Area_Name);
		
		// ------------------------------------ Environment

		//--------------- Sound
		App->CL10_Ini->GetString("Environment", "Sound_File", chr_Tag1, MAX_PATH);
		strcpy(App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Sound_File, chr_Tag1);

		App->CL10_Ini->GetString("Environment", "Snd_Volume", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->SndVolume = x;

		Int_Tag = App->CL10_Ini->GetInt("Environment", "Sound_Play", 0, 10);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Play = Int_Tag;

		Int_Tag = App->CL10_Ini->GetInt("Environment", "Sound_Loop", 0, 10);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Loop = Int_Tag;

		//--------------- Light
		App->CL10_Ini->GetString("Environment", "Ambient_Colour", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->AmbientColour = Ogre::Vector3(x, y, z);

		App->CL10_Ini->GetString("Environment", "Diffuse_Colour", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->DiffuseColour = Ogre::Vector3(x, y, z);

		App->CL10_Ini->GetString("Environment", "Specular_Colour", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->SpecularColour = Ogre::Vector3(x, y, z);

		App->CL10_Ini->GetString("Environment", "Light_Position", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Light_Position = Ogre::Vector3(x, y, z);

		//--------------- Sky
		Int_Tag = App->CL10_Ini->GetInt("Environment", "Sky_Enable", 0, 10);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Enabled = Int_Tag;

		Int_Tag = App->CL10_Ini->GetInt("Environment", "Sky_Type", 0, 10);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->type = Int_Tag;

		App->CL10_Ini->GetString("Environment", "Sky_Material", chr_Tag1, MAX_PATH);
		strcpy(App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Material, chr_Tag1);

		App->CL10_Ini->GetString("Environment", "Sky_Curvature", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Curvature = x;

		App->CL10_Ini->GetString("Environment", "Sky_Tiling", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Tiling = x;

		App->CL10_Ini->GetString("Environment", "Sky_Distance", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Distance = x;

		//--------------- Fog
		Int_Tag = App->CL10_Ini->GetInt("Environment", "Fog_On", 0, 10);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_On = Int_Tag;

		Int_Tag = App->CL10_Ini->GetInt("Environment", "Fog_Mode", 0, 10);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Mode = Int_Tag;

		App->CL10_Ini->GetString("Environment", "Fog_Colour", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f,%f,%f", &x, &y, &z);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Colour = Ogre::Vector3(x, y, z);

		App->CL10_Ini->GetString("Environment", "Fog_Start", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Start = x;

		App->CL10_Ini->GetString("Environment", "Fog_End", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_End = x;

		App->CL10_Ini->GetString("Environment", "Fog_Density", chr_Tag1, MAX_PATH);
		sscanf(chr_Tag1, "%f", &x);
		App->GDCL_Scene_Data->B_Area[0]->S_Environment[0]->Fog_Density = x;

		Count++;
		App->GDCL_Scene_Data->Area_Count++;
	}

	return 1;
}

// *************************************************************************
// *	  	Load_Get_Resource_Path:- Terry and Hazel Flanigan 2022		   *
// *************************************************************************
bool GD10_Load_Scene::Load_Get_Resource_Path()
{
	//App->Log_Messageg("bool SB_Project::Load_Get_Resource_Path()");

	m_Main_Assets_Path[0] = 0;

	strcpy(m_Main_Assets_Path, m_Project_Sub_Folder);
	strcat(m_Main_Assets_Path, "\\");

	strcat(m_Main_Assets_Path, m_Level_Name);
	strcat(m_Main_Assets_Path, "\\");

	strcat(m_Main_Assets_Path, "Assets");
	strcat(m_Main_Assets_Path, "\\");

	App->GDCL_Scene_Data->Add_Resource_Location_Project(m_Main_Assets_Path);

	return 1;
}

// *************************************************************************
// *	  		Set_Paths:- Terry and Hazel Flanigan 2022				   *
// *************************************************************************
void GD10_Load_Scene::Set_Paths()
{
	//App->Log_Messageg("void SB_Project::Set_Paths()");

	char Project_File_Name[MAX_PATH];
	char Project_Path_File_Name[MAX_PATH];

	strcpy(Project_Path_File_Name, App->GameDirecory_FullPath);
	strcat(Project_Path_File_Name, "\\Game\\Game.gdat");

	strcpy(Project_File_Name, "Game.gdat");


	strcpy(m_Level_File_Name, Project_File_Name);
	strcpy(m_Project_Sub_Folder, Project_Path_File_Name);
	strcpy(m_Ini_Path_File_Name, Project_Path_File_Name);

	strcpy(m_Level_Folder_Path, Project_Path_File_Name);

	// Get path no file 
	int len1 = strlen(m_Level_File_Name);
	int len2 = strlen(m_Project_Sub_Folder);
	strcpy(m_Project_Sub_Folder, m_Project_Sub_Folder);
	m_Project_Sub_Folder[len2 - (len1 + 1)] = 0;

}

// *************************************************************************
// *					Load_Config_File   Terry Bernie  				   *
// *************************************************************************
bool GD10_Load_Scene::Load_Config_File()
{
	//char Tag1[256];
	//char ReadBuf[256];
	bool mBool = 0;
	char FileName[2048];
	strcpy(FileName, App->GameDirecory_FullPath);
	strcat(FileName, "\\Config.cfg");

	App->CL10_Ini->SetPathName(FileName);

	mBool = App->CL10_Ini->GetBool("Config", "Full_Screen", 1);
	App->Ogre17->Full_Screen = mBool;
	return 1;
}
