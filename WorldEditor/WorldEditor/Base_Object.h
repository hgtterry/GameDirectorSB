#pragma once

/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

class Base_Object
{
public:
	Base_Object(void);
	~Base_Object(void);

	void Init_Object(void);

	Ogre::SceneNode* Object_Node;
	Ogre::Entity* Object_Ent;
	btRigidBody* Phys_Body;
	btCollisionShape* Phys_Shape;

	char Mesh_Name[MAX_PATH];				// Mesh Name Mesh.mesh
	char Mesh_FileName[MAX_PATH];
	char Mesh_Resource_Path[MAX_PATH];
	char Material_File[MAX_PATH];

	//------------------------------ Description
	int Type;
	int Shape;
	int Usage;
	int UsageEX;
	int Folder;
	int This_Object_UniqueID;  // Unique Number

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
	bool Dimensions_Locked;

	//------------------------------ Entity
	bool					Collision;
	bool					Triggered;

	//-----Sound Entity
	bool HasSound;
	bool Play_Sound;
	char Sound_File[MAX_PATH];
	char Sound_Path[MAX_PATH];


	/*irrklang::ISound* SndFile;
	Ogre::Real SndVolume;

	Move_Type* S_MoveType[1];
	Teleport_type* S_Teleport[1];
	Collectable_type* S_Collectable[1];
	Message_type* S_Message[1];
	Environ_type* S_Environ[1];
	Particle_type* S_Particle[1];
	Light_type* S_Light[1];*/

	bool Show_Message_Flag;
	char ImGui_Panel_Name[MAX_PATH];

	
};

