#include "StdAfx.h"
#include "BT_App.h"
#include "GD_Scene_Data.h"


GD_Scene_Data::GD_Scene_Data(void)
{
	Project_Resource_Group = "Project_Resource_Group";
	Project_Resources_Created = 0;

	Object_Count = 0;

	Area_Added = 0;
	Area_Count = 0;

	Player_Added = 0;
	Player_Count = 0;

	Counters_Count = 0;
	//----------------------------------------------------------------------
	SceneLoaded = 0;
	S_Flags[0] = NULL;
	S_Scene[0] = NULL;
	S_Camera[0] = NULL;
	S_LoadOptions[0] = NULL;

	ObjectCount = 0;
	Stock_Messgae_Count = 0;
	Stock_Sound_Count = 0;

	NewObjectID = 0;
	CurrentCamMode = 0;

	Read_IniFile = NULL;

	Player_Location_Count = 0;

	First_SceneFile[0] = 0;
}


GD_Scene_Data::~GD_Scene_Data(void)
{
}

// *************************************************************************
// *					Create_Resources_Group	Terry Bernie 		 	   *
// *************************************************************************
bool GD_Scene_Data::Create_Resources_Group()
{
	if (Project_Resources_Created == 0)
	{
		Ogre::ResourceGroupManager::getSingleton().createResourceGroup(Project_Resource_Group);
		Project_Resources_Created = 1;
	}

	return 1;
}

// *************************************************************************
// *	Add_Resource_Location_Project:- Terry and Hazel Flanigan 2022	   *
// *************************************************************************
bool GD_Scene_Data::Add_Resource_Location_Project(char* Resource_Location)
{
	bool Test = Ogre::ResourceGroupManager::getSingleton().resourceLocationExists(Resource_Location, Project_Resource_Group);

	if (Test == 0)
	{
		Ogre::ResourceGroupManager::getSingleton().addResourceLocation(Resource_Location, "FileSystem", Project_Resource_Group);
		Ogre::ResourceGroupManager::getSingleton().clearResourceGroup(Project_Resource_Group);
		Ogre::ResourceGroupManager::getSingleton().initialiseResourceGroup(Project_Resource_Group);
	}

	return 1;
}

//---------------------------------------------------------------------------------------------------
// *************************************************************************
// *	  				Init_Scene Terry Bernie							   *
// *************************************************************************
bool GD_Scene_Data::Init_Scene(void)
{
	App->GDCL_Scene_Data->S_Scene[0] = new Scene_Type();
	App->GDCL_Scene_Data->SetScene_Defaults();

	App->GDCL_Scene_Data->S_Camera[0] = new Camera_Type();

	App->GDCL_Scene_Data->S_LoadOptions[0] = new Load_Options_Type();
	App->GDCL_Scene_Data->SetOptions_Defaults();

	App->GDCL_Scene_Data->S_Flags[0]  = new Flags_Type();
	SetFlags_Defaults();

	//------------------------ Default Message
	//App->GDCL_Add_NewObject->Add_Stock_Message();
	
	return 1;
}

// *************************************************************************
//					Set_Mesgaes_Defaults Terry Bernie			  		   *
// *************************************************************************
void GD_Scene_Data::Set_Mesgaes_Defaults(int Index)
{

	strcpy(App->GDCL_Scene_Data->S_Messages[Index]->Name,"None");
	strcpy(App->GDCL_Scene_Data->S_Messages[Index]->Default_Text,"Test Text");

	App->GDCL_Scene_Data->S_Messages[Index]->Font_Size = 48;

	App->GDCL_Scene_Data->S_Messages[Index]->Colour = Ogre::Vector3(1,1,1);
	App->GDCL_Scene_Data->S_Messages[Index]->overlay = NULL;
	App->GDCL_Scene_Data->S_Messages[Index]->panel = NULL;
	App->GDCL_Scene_Data->S_Messages[Index]->textArea1 = NULL;
	App->GDCL_Scene_Data->S_Messages[Index]->textArea2 = NULL;
	App->GDCL_Scene_Data->S_Messages[Index]->Pos_Vert = -20;
	App->GDCL_Scene_Data->S_Messages[Index]->Pos_Hoz =  -70;
}

// *************************************************************************
//					SetFlags_Defaults Terry Bernie				  		   *
// *************************************************************************
void GD_Scene_Data::SetFlags_Defaults(void)
{
	App->GDCL_Scene_Data->S_Flags[0]->GameMode = 0;
}
// *************************************************************************
//					SetObjectDefaults Terry Bernie				  		   *
// *************************************************************************
void GD_Scene_Data::SetObjectDefaults(int Index)
{

	strcpy(App->GDCL_Scene_Data->S_Object[Index]->Name,"None");
	strcpy(App->GDCL_Scene_Data->S_Object[Index]->MeshName,"None");
	strcpy(App->GDCL_Scene_Data->S_Object[Index]->MeshName_FullPath,"None");
	strcpy(App->GDCL_Scene_Data->S_Object[Index]->ChangeLevel_Name,"None");
	strcpy(App->GDCL_Scene_Data->S_Object[Index]->TargetName_Name,"None");

	// Actor Scale ------------------------------------------------------
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Scale.x = 1;
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Scale.y = 1;
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Scale.z = 1;

	// Actor Pos
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Pos.x = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Pos.y = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Pos.z = 0;

	// Actor Rotation
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Rot.x = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Rot.y = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Rot.z = 0;

	// Actor Quat
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Quat.w = 1;
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Quat.x = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Quat.y = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Mesh_Quat.z = 0;

	// Physics Scale ------------------------------------------------------
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Scale.x = 1;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Scale.y = 1;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Scale.z = 1;

	// Physics Pos
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Pos.x = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Pos.y = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Pos.z = 0;

	// Physics Rotation
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Rot.x = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Rot.y = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Rot.z = 0;

	// Physics Size
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Size.x = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Size.y = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Size.z = 0;

	// Physics Quat
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.w = 1;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.x = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.y = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Quat.z = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Physics_Valid = 0;

	
	App->GDCL_Scene_Data->S_Object[Index]->Usage = Enums::Usage_None;

	// Object Folder
	App->GDCL_Scene_Data->S_Object[Index]->Folder = Enums::Folder_None;

	// Object Shape
	App->GDCL_Scene_Data->S_Object[Index]->Shape = -1;

	// Flag it is valid
	App->GDCL_Scene_Data->S_Object[Index]->Deleted = 0;

	App->GDCL_Scene_Data->S_Object[Index]->Show_Debug = 0;
	App->GDCL_Scene_Data->S_Object[Index]->bt_body = NULL;
	App->GDCL_Scene_Data->S_Object[Index]->IsInCollision = 0;

	App->GDCL_Scene_Data->S_Object[Index]->Triggered = 0;

	/*strcpy(App->GDCL_Scene_Data->S_Object[Index]->Sound[0].SoundFile,"None");
	strcpy(App->GDCL_Scene_Data->S_Object[Index]->Sound[0].SoundFileAndPath,"None");
	App->GDCL_Scene_Data->S_Object[Index]->Sound[0].Volume = 1.0;
	App->GDCL_Scene_Data->S_Object[Index]->Sound[0].Play = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Sound[0].Loop = 0;*/

	strcpy(App->GDCL_Scene_Data->S_Object[Index]->Entity[0].mTextItem,"Welcome");
	strcpy(App->GDCL_Scene_Data->S_Object[Index]->Entity[0].Stock_mName,"None");
	App->GDCL_Scene_Data->S_Object[Index]->Entity[0].Stock_mIndex = 0;

	App->GDCL_Scene_Data->S_Object[Index]->Re_Trigger = 1;

	App->GDCL_Scene_Data->S_Object[Index]->HasSound = 0;

	App->GDCL_Scene_Data->S_Object[Index]->Sound_ID_v2 = 0;
	App->GDCL_Scene_Data->S_Object[Index]->Play_v2 = 1;
	
	return;
}

// *************************************************************************
//						Set_Move_Defaults Terry Bernie				  	   *
// *************************************************************************
void GD_Scene_Data::Set_Move_Defaults(int Index)
{
	/*S_Object[Index]->S_MoveType->IsNegative = 1;
	S_Object[Index]->S_MoveType->Distance = -50;
	S_Object[Index]->S_MoveType->Newpos = 0;
	S_Object[Index]->S_MoveType->Speed = 10.0;
	S_Object[Index]->S_MoveType->WhatDirection = Enums::Axis_x;
	S_Object[Index]->S_MoveType->Object_Index = 0;
	S_Object[Index]->S_MoveType->Triggered = 0;
	S_Object[Index]->S_MoveType->Re_Trigger = 0;
	strcpy(S_Object[Index]->S_MoveType->Object_Name,"None");*/
	return;
}


// *************************************************************************
// *						SetOptions_Defaults Terry Bernie			   *
// *************************************************************************
void GD_Scene_Data::SetOptions_Defaults(void)
{
	S_LoadOptions[0]->Has_Player = 0;
	S_LoadOptions[0]->Has_Debug = 0;
	S_LoadOptions[0]->Has_Messages = 0;
	S_LoadOptions[0]->Has_Objects = 0;
	S_LoadOptions[0]->Has_Particles = 0;
	S_LoadOptions[0]->Has_Planes = 0;
	S_LoadOptions[0]->Has_Weapons = 0;
	
}
// *************************************************************************
// *						SetScene_Defaults Terry Bernie				   *
// *************************************************************************
void GD_Scene_Data::SetScene_Defaults(void)
{
	S_Scene[0]->SceneType = 0;
	S_Scene[0]->LastSceneType = 0;
	S_Scene[0]->CompositeMapDistance=8000;
	S_Scene[0]->PlaneCount=0;

	S_Scene[0]->Fog[0].FogOn = 0;
	S_Scene[0]->Fog[0].Mode = FOG_LINEAR;
	S_Scene[0]->Fog[0].Density = 0.001000;
	S_Scene[0]->Fog[0].Start = 50;
	S_Scene[0]->Fog[0].End = 300;
	S_Scene[0]->Fog[0].Colour = Ogre::Vector3(1,1,1);

	S_Scene[0]->AmbientColour.x = 1;
	S_Scene[0]->AmbientColour.y = 1;
	S_Scene[0]->AmbientColour.z = 1;

	S_Scene[0]->DiffuseColour.x = 0;
	S_Scene[0]->DiffuseColour.y = 0;
	S_Scene[0]->DiffuseColour.z = 0;

	S_Scene[0]->SpecularColour.x = 0;
	S_Scene[0]->SpecularColour.y = 0;
	S_Scene[0]->SpecularColour.z = 0;

	// Sound
	strcpy(S_Scene[0]->Sound[0].SoundFileAndPath,App->GDCL_SoundMgr->Default_Folder);
	strcat(S_Scene[0]->Sound[0].SoundFileAndPath,"\\Media\\Sounds\\");
	strcat(S_Scene[0]->Sound[0].SoundFileAndPath,"The_Sun.ogg");
	strcpy(S_Scene[0]->Sound[0].SoundFile,"The_Sun.ogg");

	S_Scene[0]->Sound[0].Volume = 1;
	S_Scene[0]->Sound[0].Loop = 0;
	S_Scene[0]->Sound[0].Is3D = 0;
	S_Scene[0]->Sound[0].Play = 1;
	S_Scene[0]->Sound[0].Pan = 0;
	S_Scene[0]->Sound[0].Data0 = 0;
	S_Scene[0]->Sound[0].Data1 = 0;
	S_Scene[0]->Sound[0].SndFile = NULL;

	// Sky
	S_Scene[0]->Sky[0].Curvature = 15;
	S_Scene[0]->Sky[0].Distance = 4000;
	S_Scene[0]->Sky[0].Enabled = 0;
	strcpy(S_Scene[0]->Sky[0].Material,"Examples/CloudySky");
	S_Scene[0]->Sky[0].Tiling = 15;
	S_Scene[0]->Sky[0].type = 1;
}

// *************************************************************************
//						ClearScene Terry Bernie					  		   *
// *************************************************************************
void GD_Scene_Data::ClearScene(void)
{
	
	App->GDCL_Bullet->GD_Physics_On = 0;
	App->Ogre17->PhysicsFrameListener->GD_Run_Physics = 0;

	App->Ogre17->PhysicsFrameListener->GD_Dubug_Physics = 0;

	
	if (App->Ogre17->mSceneMgr!=NULL) 
	{
		App->Ogre17->PhysicsFrameListener->Animate_Ogre = 0;

		

		//App->GDCL_Resources->Unload_Materials();
		//App->GDCL_Resources->Remove_OblectMesh();

	}

	 //remove the rigidbodies from the dynamics world and delete them
    int i;
    for (i = App->GDCL_Bullet->dynamicsWorld->getNumCollisionObjects()-1; i>=0 ;i--)
    {
            btCollisionObject* obj = App->GDCL_Bullet->dynamicsWorld->getCollisionObjectArray()[i];
            App->GDCL_Bullet->dynamicsWorld->removeCollisionObject( obj );
            delete obj;
    }


	int Count = 0;
	while (Count < ObjectCount) // Remove Ogre Objects
	{
		if(App->GDCL_Scene_Data->S_Object[Count])
		{
			delete App->GDCL_Scene_Data->S_Object[Count];
			App->GDCL_Scene_Data->S_Object[Count] = NULL;
		}

		Count++;
	}

	ObjectCount = 0;
	SceneLoaded = 0;

}

// *************************************************************************
// *		    	GameMode:- Terry and Hazel Flanigan 202	 		 	   *
// *************************************************************************
bool GD_Scene_Data::GameMode(void)
{
	
	if (B_Area[0]->S_Environment[0]->Play == 1)
	{
		int result = 1;
		result = strcmp(B_Area[0]->S_Environment[0]->Sound_File, "None");
		if (result == 1) // Could be Unsafe 
		{
			char buff[1024];
			strcpy(buff, App->GDCL_SoundMgr->Default_Folder);
			strcat(buff, "\\Media\\Sounds\\");

			strcat(buff, B_Area[0]->S_Environment[0]->Sound_File);

			B_Area[0]->S_Environment[0]->SndFile = App->GDCL_SoundMgr->SoundEngine->play2D(buff, B_Area[0]->S_Environment[0]->Loop, true, true);

			B_Area[0]->S_Environment[0]->SndFile->setVolume(B_Area[0]->S_Environment[0]->SndVolume);
			B_Area[0]->S_Environment[0]->SndFile->setIsPaused(false);
		}
	}


	CurrentCamMode = App->Ogre17->PhysicsFrameListener->GD_CameraMode;
	App->Ogre17->PhysicsFrameListener->GD_CameraMode = Enums::CamFirst;
	
	App->SBC_Physics->Enable_Physics(1); 
	App->Ogre17->PhysicsFrameListener->GD_Dubug_Physics = 0;

	//Show_Entities(false);

	SetCursorPos(500,500);
	S_Flags[0]->GameMode = 1;

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	HWND WinHwnd = GetForegroundWindow();
	SetCapture(WinHwnd);
	App->CUR = SetCursor(NULL);

	App->Ogre17->PhysicsFrameListener->Pl_LeftMouseDown = 1;
	
	return 1;
}

// *************************************************************************
// *		Show_Entities:- Terry and Hazel Flanigan 2022			  	   *
// *************************************************************************
bool GD_Scene_Data::Show_Entities(bool YesNo)
{
	int Count = 0;
	while (Count < ObjectCount)
	{
		if (S_Object[Count]->Usage == Enums::Usage_Sound)
		{
			S_Object[Count]->OgreNode->setVisible(YesNo);
		}
		if (S_Object[Count]->Usage == Enums::Usage_Message)
		{
			S_Object[Count]->OgreNode->setVisible(YesNo);
		}
		if (S_Object[Count]->Usage == Enums::Usage_Move)
		{
			S_Object[Count]->OgreNode->setVisible(YesNo);
		}
		if (S_Object[Count]->Usage == Enums::Usage_Teleport)
		{
			S_Object[Count]->OgreNode->setVisible(YesNo);
		}
		Count++;
	}
	return 1;
}

// *************************************************************************
//						Start_Scene Terry Bernie						   *
// *************************************************************************
bool GD_Scene_Data::Start_Scene()
{
	//int Index = App->GDCL_Scene_Data->ObjectCount;

	//App->GDCL_Player->SetUp();

	App->Ogre17->PhysicsFrameListener->GD_Run_Physics = 0; // ComeBack

	App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Objects = 1;
	App->GDCL_Scene_Data->S_LoadOptions[0]->Has_Player = 1;

	App->GDCL_Scene_Data->SceneLoaded = 1;

	Read_LoadLevel(); // Get Scene File Name From External File
	
	//char FileName[255];
	//char ParhFile[255];
	//strcpy(FileName,First_SceneFile);
	//
	//strcpy(ParhFile,App->GameDirecory_FullPath);
	//strcat(ParhFile,"\\");
	//strcat(ParhFile,"Media\\Levels\\");
	//strcat(ParhFile,First_SceneFile); // Create Relative File from EXE

	//strcpy(App->CL10_Load_Scene->Scene_FileName, FileName);
	//strcpy(App->CL10_Load_Scene->Scene_Path_FileName, ParhFile);
	
	App->CL10_Load_Scene->OpenScene(0);

	return 1;
}

// *************************************************************************
// *					 Read_LoadLevel(Terry Bernie)			 	 	   *
// *************************************************************************
bool GD_Scene_Data::Read_LoadLevel(void)
{
	First_SceneFile[0] = 0;

	char Tag1[MAX_PATH];
	
	/*char FileName[2048];
	strcpy(FileName,App->GameDirecory_FullPath);
	strcat(FileName,"\\Load_Level.gds");

	App->CL10_Ini->SetPathName(FileName);

	App->CL10_Ini->GetString("Start_Level", "First_Level", Tag1, 1024);

	strcpy(First_SceneFile,Tag1);*/

	// Temp 
	strcpy(Tag1,App->GameDirecory_FullPath);
	strcat(Tag1,"\\Game\\Game.gdat");
	strcpy(First_SceneFile, Tag1);

	return 1;
}
