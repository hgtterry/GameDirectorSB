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

typedef struct Move_Type {
	char Object_Name[MAX_PATH];	// Name of Object to Move
	float Newpos;
	float Speed;			// 
	int WhatDirection;		//
	int Object_To_Move_Index;		// Can Change
	bool IsNegative = 0;	// Positive or Negative distance to move
	bool Triggered;			// Entity 
	bool Re_Trigger;
	float Move_Distance;	// Distance to Move negative or positive
	Ogre::Vector3 MeshPos;
	Ogre::Vector3 PhysicsPos;
	int Trigger_Value;
	int Counter_ID;
	char Counter_Name[MAX_PATH];
	bool Counter_Disabled;

}Move_Type;

typedef struct Teleport_type
{
	char Name[MAX_PATH];
	Ogre::Vector3 Player_Position;
	btVector3 Physics_Position;
	btQuaternion Physics_Rotation;
	int Location_ID;
	irrklang::ISound* SndFile;
	Ogre::Real SndVolume;
	char Sound_File[MAX_PATH];
	bool Play;

}Teleport_type;

typedef struct Message_type
{
	int Trigger_Value;
	int Counter_ID;
	char Counter_Name[MAX_PATH];
	bool Counter_Disabled;

}Message_type;

typedef struct Collectable_type
{
	int Counter_ID;
	irrklang::ISound* SndFile;
	Ogre::Real SndVolume;
	char Sound_File[MAX_PATH];
	char Counter_Name[MAX_PATH];
	bool Counter_Disabled;
	bool Play;
	int Maths; // [ 0 = None ]  [ 1 = Add ]  [ 2 = Subtract ]
	int Value; 

}Collectable_type;

#pragma once
class Base_Object
{
public:

	Base_Object();
	~Base_Object();

	bool Init_Object(void);
	void Set_ImGui_Panel_Name(void);
	void Render_ImGui_Panel(void);

	Ogre::SceneNode		*Object_Node;
	Ogre::Entity		*Object_Ent;
	btRigidBody			*Phys_Body;
	btCollisionShape	*Phys_Shape;

	char Mesh_Name[MAX_PATH];				// Mesh Name Mesh.mesh
	char Mesh_FileName[MAX_PATH];
	char Mesh_Resource_Path[MAX_PATH];
	char Material_File[MAX_PATH];

	//------------------------------ Description
	int Type;
	int Shape;
	int Usage;
	int Folder;
	int This_Object_ID;  // Unique Number

	//------------------------------ Mesh
	Ogre::Vector3			Mesh_Scale;
	Ogre::Vector3			Mesh_Pos;
	Ogre::Vector3			Mesh_Center;
	Ogre::Vector3			Mesh_Rot;
	Ogre::Quaternion		Mesh_Quat;

	//------------------------------ Physics
	Ogre::Vector3			Physics_Pos;
	Ogre::Vector3			Physics_Rot;
	Ogre::Vector3			Physics_Scale;
	Ogre::Vector3			Physics_Size; // Box x y z ;- x = Radius y = Height
	Ogre::Quaternion		Physics_Quat;
	float					Physics_Mass;
	float					Physics_Restitution;
	bool					Physics_Valid;

	//------------------------------ ListView

	HTREEITEM FileViewItem;

	//------------------------------ Bounding Box
	Ogre::Real Mesh_BB_Width;
	Ogre::Real Mesh_BB_Height;
	Ogre::Real Mesh_BB_Depth;
	Ogre::Quaternion Mesh_BB_Quat;
	Ogre::Vector3 Mesh_BB_Center;

	bool Deleted;
	bool Altered;
	bool Physics_Debug_On;
	//------------------------------ Entity
	bool					Collision;
	bool					Triggered;

	//-----Sound Entity
	bool HasSound;
	bool Play_Sound;
	char Sound_File[MAX_PATH];
	char Sound_Path[MAX_PATH];
	irrklang::ISound* SndFile;
	Ogre::Real SndVolume;

	//-----Move Entity
	Move_Type* S_MoveType[1];

	//-----Teleport Entity
	Teleport_type* S_Teleport[1];

	//-----Collectable
	Collectable_type* S_Collectable[1];

	//-----Message Entity

	Message_type*	S_Message[1];

	bool Show_Message_Flag;
	char ImGui_Panel_Name[MAX_PATH];
	char Message_Text[MAX_PATH];
	float Message_PosX;
	float Message_PosY;

};

