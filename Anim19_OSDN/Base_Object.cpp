/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "GD19_App.h"
#include "Base_Object.h"

Base_Object::Base_Object()
{
	Init_Object();
}

Base_Object::~Base_Object()
{
}

// *************************************************************************
// *	  					Init_Object Terry Flanigan					   *
// *************************************************************************
bool Base_Object::Init_Object(void)
{
	Object_Ent = nullptr;
	Object_Node = nullptr;

	Phys_Body = nullptr;
	Phys_Shape = nullptr;

	strcpy(Mesh_Name, "None");
	strcpy(Mesh_FileName, "None");
	Mesh_Resource_Path[0] = 0;
	strcpy(Material_File, "Not Found");

	// Actor Scale ------------------------------------------------------
	Mesh_Scale.x = 1;
	Mesh_Scale.y = 1;
	Mesh_Scale.z = 1;

	// Actor Pos
	Mesh_Pos.x = 0;
	Mesh_Pos.y = 0;
	Mesh_Pos.z = 0;

	// Mesh Rotation
	Mesh_Rot.x = 0;
	Mesh_Rot.y = 0;
	Mesh_Rot.z = 0;

	// Mesh Quat
	Mesh_Quat.w = 1;
	Mesh_Quat.x = 0;
	Mesh_Quat.y = 0;
	Mesh_Quat.z = 0;

	// Physics Scale ------------------------------------------------------
	Physics_Scale.x = 1;
	Physics_Scale.y = 1;
	Physics_Scale.z = 1;

	// Physics Pos
	Physics_Pos.x = 0;
	Physics_Pos.y = 0;
	Physics_Pos.z = 0;

	// Physics Rotation
	Physics_Rot.x = 0;
	Physics_Rot.y = 0;
	Physics_Rot.z = 0;

	// Physics Size
	Physics_Size.x = 0;
	Physics_Size.y = 0;
	Physics_Size.z = 0;

	// Physics Quat
	Physics_Quat.w = 1;
	Physics_Quat.x = 0;
	Physics_Quat.y = 0;
	Physics_Quat.z = 0;
	Physics_Valid = 0;

	Usage = Enums::Usage_None;

	Folder = Enums::Folder_None;

	Shape = -1;

	FileViewItem = nullptr;

	This_Object_ID = 0; // This Needs Checking
	Deleted = 0;
	Altered = 0;

	Collision = 0;
	Triggered = 0;
	Physics_Debug_On = 0;

	//------------------------------ Message Entity
	strcpy(Message_Text, "This is in the Object");

	//------------------------------ Sound Entity
	HasSound = 0;
	strcpy(Sound_File, "Door_Open.wav");
	Sound_Path[0] = 0;
	Play_Sound = 1;
	SndVolume = 0.5; // Default Half Volume

	strcpy(TextMessage_Name, "Not_Set");
	TextMessage_ID = 0;
	return 1;
}
