#pragma once

typedef struct Environment_type
{
	//--------------- Sound
	irrklang::ISound* SndFile;
	Ogre::Real SndVolume;
	char Sound_File[MAX_PATH];
	bool Play;
	bool Loop;

	//--------------- Light
	Ogre::Vector3 AmbientColour;
	Ogre::Vector3 DiffuseColour;
	Ogre::Vector3 SpecularColour;
	Ogre::Vector3 Light_Position;

	//--------------- Sky
	bool Enabled;
	int type;
	char Material[255];
	float Curvature;
	float Tiling;
	float Distance;

	//--------------- Fog
	int Fog_On;
	int Fog_Mode;
	Ogre::Vector3 Fog_Colour;
	float Fog_Start;
	float Fog_End;
	float Fog_Density;

}Environment_type;

class Base_Area
{
public:
	Base_Area();
	~Base_Area();

	Ogre::Entity*		Area_Ent;
	Ogre::SceneNode*	Area_Node;

	btRigidBody *Phys_Body;
	btCollisionShape *Phys_Shape;

	void Collect_Object_Data(void);

	Ogre::Vector3			Physics_Pos;
	Ogre::Vector3			Physics_Rot;
	Ogre::Vector3			Physics_Scale;

	Ogre::Quaternion		Physics_Quat;

	int Type;
	int Shape;
	int Usage;
	int Folder;
	int This_Object_ID;  // Unique Number

	char Area_Name[100];

	char Area_FileName[MAX_PATH];
	char Area_Path_And_FileName[MAX_PATH];
	char Area_Resource_Path[MAX_PATH];
	char Material_File[MAX_PATH];

	//------------------------------ Mesh
	Ogre::Vector3			Mesh_Scale;
	Ogre::Vector3			Mesh_Pos;
	Ogre::Vector3			Mesh_Center;
	Ogre::Vector3			Mesh_Rot;
	Ogre::Quaternion		Mesh_Quat;

	HTREEITEM FileViewItem;			// Holder for Area File view item [211121]

	bool Physics_Valid;
	bool Altered;

	bool Physics_Debug_On;

	//------------------------------ Environment
	
	Environment_type* S_Environment[1];
};

