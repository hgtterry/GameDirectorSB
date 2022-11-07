/*	
	Copyright (c) 2009 - 2013 W.T.Flanigan Bernard Parkin and H.C.Flanigan

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

#pragma once

#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")

#pragma warning( disable : 4251 4193 4275 4005)
#pragma warning( disable : 4996)
#pragma warning( disable : 4305)

#include "targetver.h"

#include <windows.h>
#include "btBulletDynamicsCommon.h"
// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>
#include <stdio.h>
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

#include <gl/gl.h>
#include <gl/glu.h>


namespace Enums
{
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
		Edit_Player = 3
	};

	enum Usage
	{
		Usage_None = 0,
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
		Usage_Player = 18
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
		Stock_Type_Sound = 2
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
	enum Bullet_Type
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
		Debug_On= 1,
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
		Folder_Message_Entity = 3
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
		Selected_Player_Start =8,
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
		DropDialog_Counters = 3
	};
}