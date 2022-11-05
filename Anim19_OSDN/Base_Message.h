/*
Copyright (c) 2021 EquitySB and EquityME -- HGTO Software W.T.Flanigan H.C.Flanigan

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

:- Terry and Hazel Flanigan 2022

*/

#pragma once
class Base_Message
{
public:

	Base_Message();
	~Base_Message();

	bool Init_Object(void);

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

	void Set_ImGui_Panel_Name(void);

	void Render_ImGui_Panel(void);

	bool Show_Panel_Flag;
	bool Deleted;
	bool Altered;

	int Unique_ID;

	char TextMessage_Name[MAX_PATH];
	char Text[MAX_PATH];

	char ImGui_Panel_Name[MAX_PATH];

	float PosX;
	float PosY;
	//------------------------------ ListView

	HTREEITEM FileViewItem;
};

