#pragma once

#include "Base_Area.h"
#include "Base_Player.h"

//==================================== Application Flags Structure	
typedef struct Flags_Type 
{ 
	bool GameMode;
}Flags_Type;

//==================================== Load Options Structure
typedef struct Load_Options_Type { 
	bool Has_Planes;
	bool Has_Objects;
	bool Has_Particles;
	bool Has_Weapons;
	bool Has_Player;
	bool Has_Debug;
	bool Has_Messages;
}Load_Options_Type;
//==================================== Sound Structure

typedef struct Sky_Type {
	bool Enabled;
	int type;
	char Material[255];
	float Curvature;
	float Tiling;
	float Distance;
}Sky_Type;

typedef struct Fog_Type { 
	int FogOn;
	int Mode;
	Ogre::Vector3 Colour;
	float Start;
	float End;
	float Density;
}Fog_Type;


typedef struct Camera_Type { 
	// == Pos
	float PosX;
	float PosY;
	float PosZ;
	// == Rotation
	float RotW;
	float RotX;
	float RotY;
	float RotZ;
	// == Height
	float CameraHeight;
	// == Speeds
	float WalkSpeed;
	float RunSpeed;

	int MakerCount;				// Maker Count Total;
	int Adjusted_MakerCount;	// Maker Count Adjusted for saving Total;
//	Marker_Type Marker[20];
}Camera_Type;

typedef struct Int_Type {int Array;}int_Type;

//--------------------------------------------------------
typedef struct Move_Type {
	char Object_Name[255];	// Name of Object to Move
	float Distance;			// Distance to Move negative or positive
	float Newpos;
	float Speed;			// 
	int WhatDirection;		//
	int Object_Index;
	bool IsNegative;		//
	bool Triggered;		
	bool Re_Trigger;	
	Ogre::Vector3 MeshPos;
	Ogre::Vector3 PhysicsPos;
}Move_Type;
//--------------------------------------------------------
typedef struct Sound_Type {

	irrklang::ISound* SndFile;
	char SoundFile[255];
	char SoundFileAndPath[255];
	float Volume;
	float Pan;
	float Data0;
	float Data1;
	bool Loop;
	bool Is3D;
	bool Play;
}Sound_Type;

//--------------------------------------------------------
typedef struct Entity_Type 
{
	char mFileAndPath[1024];
	char mTextItem[255];
	char Stock_mName[255];
	int Stock_mIndex;
}Entity_Type;

typedef struct Teleport_type
{
	char Name[255];
	Ogre::Vector3 Player_Position;
	btVector3 Physics_Position;
	btQuaternion Physics_Rotation;

}Teleport_type;

//==================================== Object Structure
typedef struct Object_Type { 
	char Name[255];
	char MeshName[255];				// Mesh Name Mesh.mesh
	char MeshName_FullPath[255];
	char ChangeLevel_Name[255];
	char TargetName_Name[255];

	//------------------------------ Description
	int Type;
	int Shape;
	int Usage;
	int Folder;

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
	Ogre::Entity*	OgreEntity;
	btRigidBody		*bt_body;

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
	bool					Show_Debug;
	bool					Collision;
	bool					UseTargetFlag;
	bool					IsInCollision;
	bool					HasSound;

	//------------------------------
	Entity_Type				Entity[1];
	Move_Type*				S_MoveType;
	Sound_Type*				S_Sounds[1]; // Heap
	Teleport_type*			S_Teleport[1];
	//------------------------------ Move Entity Data
	int MoveEntityIndex;						// Imternal
	bool Triggered;								// Imternal
	bool Re_Trigger;		

	// New Sound
	int Sound_ID_v2;
	bool Play_v2;

}Object_Type;

typedef struct Scene_Type { 	
	int PlaneCount;
	char TerrainFileName[255];
	char LevelName[255];
	char SceneVersion[32];
	char GDSceneName[255];
	float CompositeMapDistance;
	//Plane_Type Plane[20];
	Fog_Type Fog[1];
	
	int SceneType; //0 = Terrian 1 = Indoor
	int LastSceneType;	
	Ogre::Vector3 AmbientColour;
	Ogre::Vector3 DiffuseColour;
	Ogre::Vector3 SpecularColour;
	Ogre::Vector3 Light_Position;
	int MoveWhat;
	Sound_Type				Sound[1];
	Sky_Type				Sky[1];

}Scene_Type;

// ------------------------ Stock Message
typedef struct Stock_Messages_type 
{
	int Type;
	char Name[255];
	char Default_Text[255];
	int Font_Size;
	Ogre::Overlay* overlay;
	Ogre::OverlayContainer* panel;
	Ogre::TextAreaOverlayElement* textArea1;
	Ogre::TextAreaOverlayElement* textArea2;
	Ogre::Real Pos_Vert;
	Ogre::Real Pos_Hoz;
	Ogre::Vector3 Colour;

}Stock_Messages_type;

// ------------------------ Stock Sound
typedef struct Stock_Sound_type 
{
	bool Deleted; // Internal
	int Sound_ID;  // Unique Number
	char Name[255];
	char SoundFile[255];
	char SoundFileAndPath[255];
	float Volume;
	float Pan;
	bool Loop;
	bool Is3D;
	bool Play;
	irrklang::ISound* SndFile;

}Stock_Sound_type;

// ------------------------ Player_Location_type
typedef struct Player_Location_type
{
	bool Deleted; // Internal
	int Location_ID;  // Unique Number
	char Name[255];
	Ogre::Vector3 Current_Position;
	btVector3 Physics_Position;
	btQuaternion Physics_Rotation;

}Player_Location_type;

class GD_Scene_Data
{
public:
	GD_Scene_Data(void);
	~GD_Scene_Data(void);

	bool Create_Resources_Group();
	bool Add_Resource_Location_Project(char* Resource_Location);


	bool Project_Resources_Created;

	bool Area_Added;
	int Area_Count;

	bool Player_Added;
	int Player_Count;

	Ogre::String Project_Resource_Group;

	Base_Player*			B_Player[5];
	Base_Area*				B_Area[100];

	//-----------------------------------------------------------------
	bool Start_Scene();

	bool Init_Scene(void);
	void SetObjectDefaults(int Index);
	void SetDataBlocks(int Index);
	void SetScene_Defaults(void);
	void SetOptions_Defaults(void);
	void SetFlags_Defaults(void);

	void Set_Mesgaes_Defaults(int Index);
	
	void Set_Move_Defaults(int Index);

	void ClearScene(void);

	bool GameMode(void);
	bool Show_Entities(bool YesNo);

	bool Read_LoadLevel(void);

	Flags_Type*				S_Flags[1];
	Scene_Type*				S_Scene[1];
	Camera_Type*			S_Camera[5];
	Load_Options_Type*		S_LoadOptions[1];
	Object_Type*			S_Object[300];
	Stock_Messages_type*	S_Messages[20];
	Stock_Sound_type*		St_Sounds[20];
	Player_Location_type*	S_Player_Locations[20];

	int ObjectCount;
	int Stock_Messgae_Count;
	int Stock_Sound_Count;
	int NewObjectID;
	int CurrentCamMode;
	bool SceneLoaded;

	int Player_Location_Count;

	char First_SceneFile[255];

	FILE *Read_IniFile;
};

