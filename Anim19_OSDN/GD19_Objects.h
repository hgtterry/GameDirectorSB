#pragma once

typedef struct Int_Type2 { int Array; }int_Type2;

//--------------------------------------------------------
typedef struct Environment2 {
	bool FogOn;
}Environment2;


class GD19_Objects
{
public:

	GD19_Objects(void);
	virtual ~GD19_Objects(void);

	bool Init_Object(void);
	

	btBvhTriangleMeshShape* createTrimesh(Ogre::Entity* ent, int Object_Index);
	

	btTransform Set_Physics_PosRot(void);
	void Set_Physics_Scale(void);
	Ogre::Vector3 GetPlacement(void);
	void Collect_Object_Data(void);
	Ogre::Vector3 Get_BoundingBox_World_Centre(void);

	// ---------------------------------------------------------------------

	char Name[255];
	char MeshName[255];				// Mesh Name Mesh.mesh
	char MeshName_FullPath[255];

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

	//------------------------------ Ogre Scene Entity/Node
	Ogre::SceneNode* OgreNode;
	Ogre::Entity* OgreEntity;
	btRigidBody* bt_body;
	Ogre::ParticleSystem* Ogre_Particle;
	//------------------------------ ListView
	HTREEITEM ListViewItem;
	bool  Deleted;

	//------------------------------ Bounding Box
	Ogre::Real Mesh_BB_Width;
	Ogre::Real Mesh_BB_Height;
	Ogre::Real Mesh_BB_Depth;
	Ogre::Quaternion Mesh_BB_Quat;
	Ogre::Vector3 Mesh_BB_Center;

	//------------------------------
	/*bool					Show_Debug;
	bool					Collision;
	bool					UseTargetFlag;
	bool					IsInCollision;
	bool					HasSound;*/

	//------------------------------
	
	Environment2* S_Environment[1];
	//------------------------------ Move Entity Data
	
	// New Sound
	int Sound_ID_v2;
	bool Play_v2;
};

 