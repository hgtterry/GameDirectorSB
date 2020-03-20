// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#if defined(_MSC_VER) && !defined(_CRT_SECURE_NO_WARNINGS)
#define _CRT_SECURE_NO_WARNINGS
#endif

#pragma warning( disable : 4251 4193 4275 4005)
#pragma warning( disable : 4996)
#pragma warning( disable : 4305)
#pragma warning( disable : 4316) // Heap Alication
#pragma warning( disable : 4477) // format string

#pragma comment(lib, "legacy_stdio_definitions.lib")

//typedef unsigned long  uint32;

#include "targetver.h"

#define NOMINMAX
#include <windows.h>
#include "btBulletDynamicsCommon.h"
// C RunTime Header Files
//#include <stdint.h>
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <direct.h>
#include <Commctrl.h>   // includes the Common control header

#include "Ogre.h"
#include "OgreConfigFile.h"
#include "OgreStringConverter.h"
#include "OgreException.h"
#include "OgreTerrain.h"
#include "OgreTerrainGroup.h"
#include "OgreTerrainMaterialGeneratorA.h"
#include "OgreTextAreaOverlayElement.h"
#include "OgreBillboardParticleRenderer.h"
#include "OgreStringConverter.h"
#include "OgreDefaultHardwareBufferManager.h"
#include "OgreHardwareVertexBuffer.h"
#include "OgreVertexIndexData.h"
#include "OgreResourceGroupManager.h"
#include "irrKlang.h"

namespace Enums
{
	enum Mesh_Viewer
	{
		Mesh_Viewer_None = -1,
		Mesh_Viewer_Objects = 0,
		Mesh_Viewer_Collectables = 1,
		Mesh_Viewer_Area = 2
	};

	enum Check_Names
	{
		Check_Names_None = 0,
		Check_Names_Locatoins = 1,
		Check_Names_Objects = 2
	};

	enum Edit_Mouse
	{
		Edit_Mouse_None = 0,
		Edit_Mouse_Active = 1
	};

	enum Edit_Dimensions
	{
		Edit_Dimensions_None = 0,

		Edit_Dimensions_PosX = 1,
		Edit_Dimensions_PosY = 2,
		Edit_Dimensions_PosZ = 3,

		Edit_Dimensions_ScaleAll = 4,
		Edit_Dimensions_ScaleX = 5,
		Edit_Dimensions_ScaleY = 6,
		Edit_Dimensions_ScaleZ = 7,

		Edit_Dimensions_RotateX = 8,
		Edit_Dimensions_RotateY = 9,
		Edit_Dimensions_RotateZ = 10
	};

	enum Edit_Type
	{
		Edit_None = 0,
		Edit_Mesh_Object = 1,
		Edit_Physics_Object = 2,
		Edit_Player = 3,
		Edit_Message = 4,
		Edit_Move_Entity = 5,
		Edit_Sounds = 6,
		Edit_Collectable = 7,
		Edit_Teleport = 8,
		Edit_Environment = 9,
		Edit_Area_Change = 10,
		Edit_Change_Level = 11,
		Edit_Particles = 12
	};

	enum Usage
	{
		Usage_None = -1,
		Usage_Room = 0,
		Usage_Static = 1,
		Usage_Dynamic = 2,
		Usage_Object = 3,
		Usage_Ammo = 4,
		Usage_Weapon = 5,
		Usage_Teleport = 6,
		Usage_ChangeLevel = 7,
		Usage_MediKit = 8,
		Usage_Recevier = 9,
		Usage_Particle = 10,
		Usage_Light = 11,
		Usage_Colectable = 12,
		Usage_Message = 13,
		Usage_Move = 14,
		Usage_Sound = 15,
		Usage_PlayerDeath = 16,
		Usage_Counter = 17,
		Usage_Player = 18,
		Usage_Environment = 19,
		Usage_RoomChange = 20,
	};
	enum Camera
	{
		CamNone = 0,
		CamFirst = 1,
		CamDetached = 2,
		CamThird = 3
	};
	enum SpaceBar
	{
		SB_SelectionNone = 0,
		SB_SelectionJump = 1,
		SB_SelectionObject = 2
	};
	enum Stock_Type
	{
		Stock_Type_None = 0,
		Stock_Type_Message = 1,
		Stock_Type_Sound = 2,
		Stock_Type_Panel = 3
	};

	enum Attribute
	{
		Attribute_NO_Weapon = 0,
		Attribute_Ammo = 1,
		Attribute_Weapon = 2,
		Attribute_Medikit = 3,
		Attribute_Collectable = 4
	};

	enum Shape
	{
		NoShape = 0,
		Shape_Box = 1,
		Sphere = 2,
		Capsule = 3,
		Cylinder = 4,
		Cone = 5,
		Shape_TriMesh = 6,
		VolumeBox = 7
	};
	enum Bullet_Type // Dont Forget GD19_LookUps::Get_Type_Category_String(void)
	{
		Bullet_Type_None = 0,
		Bullet_Type_Dynamic = 1, // Free Moving Physics
		Bullet_Type_Static = 2, // Fixed Non Moving Shape
		Bullet_Type_TriMesh = 3,
		Type_NXS_Convex = 4,
		Type_JustOgre = 5,
		Bullet_Type_Volume = 6
	};
	enum Light_Type
	{
		LightType_Point = 0,
		LightType_Spot = 1,
		LightType_Direction = 2
	};
	enum Vector_Type
	{
		NoVector = 0,
		Vector_X = 1,
		Vector_Y = 2,
		Vector_Z = 3
	};
	enum FreeSpeed_Type
	{
		Slow = 0,
		Mid = 1,
		Fast = 2
	};
	enum Debug_Type
	{
	Debug_Off = 0,
		Debug_On = 1,
	};
	enum ListBox_Type
	{
		ListBox_None = 0,
		ListBox_Stock_Sounds = 1,
		ListBox_Stock_Messages = 2,
		ListBox_Resource_Paths = 3,
		ListBox_Resource_MeshMaterials = 4
	};
	enum OptionsProperties_Type
	{
		Options_None = 0,
		Options_Speeds = 1,
		Options_Debug = 2
	};

	enum Folder_Type
	{
		Folder_None = 0,
		Folder_Objects = 1,
		Folder_Sound_Entity = 2,
		Folder_Message_Entity = 3,
		Folder_Move_Entity = 4,
		Folder_Collectables = 5,
		Folder_Teleports = 6,
		Folder_Environment = 7,
		Folder_RoomChange = 8,
		Folder_Change_Level = 9,
		Folder_Particle = 10
	};
	enum Selected_Type
	{
		Selected_None = 0,
		Selected_Objects = 1,
		Selected_Buildings = 2,
		Selected_Characters = 3,
		Selected_Vegitation = 4,
		Selected_Tools = 5,
		Selected_Micellaneous = 6,
		Selected_Player_Setup = 7,
		Selected_Player_Start = 8,
		Selected_Planes = 9,
		Selected_ChangeLevel = 10,
		Selected_TelePort = 11,
		Selected_TeleTarget = 12,
		Selected_Particles = 13,
		Selected_Lights = 14,
		Selected_Folder_Medikit = 15,
		Selected_Folder_Collectables = 16,
		Selected_Folder_Ammo = 17,
		Selected_Folder_Weapons = 18,
		Selected_Folder_Message = 19,
		Selected_Folder_Doors = 20,
		Selected_Folder_Sound = 21,
		Selected_Folder_Death_Trigger = 22,
		Selected_Folder_Counter = 23
	};
	enum Movement
	{
		Movement_None = 0,
		Movement_StaticObject = 1
	};

	enum MovementMode
	{
		Move_None = 0,
		Move_World = 1,
		Move_Object = 2
	};
	enum Axis
	{
		Axis_None = 0,
		Axis_x = 1,
		Axis_y = 2,
		Axis_z = 3
	};

	enum DropDialogItems
	{
		DropDialog_None = 0,
		DropDialog_TrigMoveObject = 1,
		DropDialog_TrigMoveAxis = 2,
		DropDialog_Counters = 3,
		DropDialog_Locations = 4
	};
}


#define debug2 App->Say("Debug")

#define Func_DLog(...) App->Cl_ImGui->ImGui_Test_Log(__VA_ARGS__)


#define  DLog(x) { if (App->FollowFunctions == 1) {App->Cl_ImGui->ImGui_Test_Log(x); }}

// TODO: reference additional headers your program requires here
