#pragma once
class Base_Entity
{

public:

	Base_Entity();
	~Base_Entity();

	bool Init_Object(void);

	Ogre::SceneNode		*Object_Node;
	Ogre::Entity		*Object_Ent;
	btRigidBody			*Phys_Body;
	btCollisionShape	*Phys_Shape;

	char Mesh_Name[MAX_PATH];				// Mesh Name Mesh.mesh
	char Mesh_FileName[MAX_PATH];
	char Mesh_Resource_Path[MAX_PATH];

	//------------------------------ Description
	int Type;
	int Shape;
	int Usage;
	int Folder;
	int Object_ID;  // Unique Number

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
	HTREEITEM ListViewItem;
	//------------------------------ Bounding Box
	Ogre::Real Mesh_BB_Width;
	Ogre::Real Mesh_BB_Height;
	Ogre::Real Mesh_BB_Depth;
	Ogre::Quaternion Mesh_BB_Quat;
	Ogre::Vector3 Mesh_BB_Center;

	bool  Deleted;
};

