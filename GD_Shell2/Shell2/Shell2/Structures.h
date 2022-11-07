/*	
	Copyright (c) 2011 W.T.Flanigan And Bernard Parkin

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
typedef struct Char_type {char Name[256];}Char_type;
typedef struct Int_Type {int Array;}int_Type;

typedef struct Texture_type 
{
	bool Touched;
	int TextureCount;
	Char_type Texture[100];
	Int_Type TexureIndex[100];
}Texture_type;
//==================================== GDFloats Structure
typedef struct GDFloat_Type {
	float ObjectData;
}GDFloat_Type;
//==================================== GDInts Structure
typedef struct GDIntData_Type {
	int intData_1;
	int intData_2;
	int intData_3;
	int intData_4;
	int intData_5;
	int intData_6;
}GDIntData_Type;
//==================================== GDFloats Structure
typedef struct GDFloatData_Type {
	float FloatData_1;
	float FloatData_2;
	float FloatData_3;
	float FloatData_4;
	float FloatData_5;
	float FloatData_6;
}GDFloatData_Type;
//==================================== GDFloats Structure
typedef struct GDChrData_Type {
	char charData_1[255];
	char charData_2[255];
	char charData_3[255];
	char charData_4[255];
	char charData_5[255];
	char charData_6[255];
}GDChrData_Type;
//==================================== GDFloats Structure
typedef struct Colour_Type {
	float Red;
	float Green;
	float Blue;
}Colour_Type;
//==================================== Sound Structure
typedef struct Sound_Type {
	irrklang::ISound*	SndFile;
	char SoundFile[255];
	char SoundFileAndPath[255];
	float Volume;
	float Pan;
	float Data0;
	float Data1;
	bool Loop;
	bool Is3D;
}Sound_Type;
//==================================== Cam Structure
typedef struct Marker_Type { 
	char Name[256];
	float PosX;
	float PosY;
	float PosZ;
	float RotX;
	float RotY;
	float RotZ;
	float RotW;
	bool  Deleted;
}Marker_Type;

//==================================== Object Structure
typedef struct Object_Type { 
	char Name[256];
	char MeshName[256];
	char MeshName_FullPath[256];
	char ChangeLevel_Name[256];
	char TargetName_Name[256];
	char NXSFileName[256];
	int Type;
	int Shape;
	Ogre::Vector3 MeshScale;
	Ogre::Vector3 MeshPos;
	Ogre::Vector3 MeshCenter;
	Ogre::Vector4 MeshRot;
	Ogre::Quaternion MeshQuat;
	Ogre::Quaternion Ogre_GlobalRotationQuat;
	int Usage;
	int ObjectFolder;
	Ogre::SceneNode* OgreNode;
	Ogre::Entity*	OgreEntity;
	Ogre::ParticleSystem *Particle;
	Ogre::Light*	Light;
	HTREEITEM ListViewItem;
	bool  Deleted;
	//====================
	Ogre::Real Mesh_BB_Width;
	Ogre::Real Mesh_BB_Height;
	Ogre::Real Mesh_BB_Depth;
	Ogre::Quaternion Mesh_BB_Quat;
	Ogre::Vector3 Mesh_BB_Center;
	//====================
	/*Critter::KinematicBody*	Nx_Kinetic;
	Critter::Body*			Nx_Body;
	NxOgre::Volume*			Nx_volume;
	Ogre::Vector3			Nx_LocalSize;
	Ogre::Vector3			Nx_LocalPosition;
	Ogre::Vector3			Nx_LocalRotation;
	NxOgre::Quat			Nx_LocalRotaionQuat;
	NxOgre::SceneGeometry*	Nx_SceneGeo;
	NxOgre::Mesh*			Nx_Mesh;
	NxOgre::Mesh*			Nx_SavedMesh;*/
	int						Nx_ShapeID;
	bool					Collision;
	bool					UseTargetFlag;
	bool					IsInCollision;
	//----------------------------------------- Data Objects
	GDIntData_Type			IntsRow_1;
	GDIntData_Type			IntsRow_2;
	GDIntData_Type			IntsRow_3;
	GDIntData_Type			IntsRow_4;
	GDIntData_Type			IntsRow_5;
	GDFloatData_Type		Data_1;
	GDFloatData_Type		FloatsRow_1;
	GDFloatData_Type		FloatsRow_2;
	GDFloatData_Type		FloatsRow_3;
	GDFloatData_Type		FloatsRow_4;
	GDChrData_Type			ChrsRow_1;
	GDChrData_Type			ChrsRow_2;
	GDChrData_Type			ChrsRow_3;
	GDChrData_Type			ChrsRow_4;
	GDChrData_Type			ChrsRow_5;
	GDFloat_Type			Data[5];    /// NEED UPDATING TO PROPER DATA
	Sound_Type				Sound[1];
	// Animation
	Ogre::AnimationState *mAnimState;
	bool Animate;
	char AnimationName[255];
	float AnimationSpeed;
	Texture_type TextureData[1];

	// Move Entity Data
	int MoveEntityIndex;
	bool Triggered;								// Imternal
}Object_Type;

typedef struct ObjectMove_Type { 
	int Pitch;
	int Roll;
	int Yaw;
	int PosX;
	int PosY;
	int PosZ;	
	int Scale;
}ObjectMove_Type;

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
	Marker_Type Marker[20];
}Camera_Type;

//==================================== Scene Structure
typedef struct Plane_Type { 
	char Name[50];
	char Type[50];
	char MaterialScript[255];
	Ogre::Real Width;
	Ogre::Real Height;
	int Visible;
	int Normals;
	int CoordSets;
	int TileX;
	int TileY;
	Ogre::Real UTile;
	Ogre::Real VTile;
	Ogre::Real RotW;
	Ogre::Vector3 Scale;
	Ogre::Vector3 Pos;
	Ogre::Vector4 Rot;
	Ogre::Real Bow;
	bool IsBowed;
	bool Deleted;
	int NameIndex;
}Plane_Type;

typedef struct Fog_Type { 
	int FogOn;
	char FogOnText[20];
	char Mode[20];
	char Color[20];
	char Density[20];
	char Start[20];
	char End[20];
}Fog_Type;

typedef struct Scene_Type { 	
	int PlaneCount;
	char TerrainFileName[256];
	char LevelName[256];
	char GDSceneName[256];
	float CompositeMapDistance;
	Plane_Type Plane[20];
	Fog_Type Fog[1];
	int SceneType;	
	int LastSceneType;	
	Ogre::Vector3 AmbientColour;
	Ogre::Vector3 DiffuseColour;
	Ogre::Vector3 SpecularColour;
	int MoveWhat;
	Sound_Type				Sound[1];

}Scene_Type;

typedef struct Player_Type { 
	char Name[255];
	int PlayerMode;
	float MaxGroundSpeed;
	float mSlopeLimit;
	float StepOffset;
	float Sharpness;
	float JumpHeight;
	float TurnRate;
	float PlayerPoseY;

}Player_Type;

typedef struct MoveEntity_Type { 
	float MoveDistance;
	float Speed;
	int ObjectToUseIndex;
	char ObjectToUseName[255];
	Ogre::Vector3 StartPosition;
	bool IsMoving;
	float Xpos;
	float Ypos;
	float Zpos;
	int WhatDirection;
	bool IsNegative;
}MoveEntity_Type;

//==================================== Application Flags Structure	
typedef struct Flags_Type 
{ 
	bool RenderBackGround;
	bool SceneLoadedOnce;
	bool OgreIsRunning;
	bool FlyOn;
	bool GameSpeedOn;
	bool RenderNxOgre;
	bool Save;
	bool CamDetached;
	bool CamFirst;
	bool CamThird;
	bool CamLookAt;
	bool MovePalyer;
	bool MoveCamera;
	bool StartScreen;
	bool GameMode;
	bool PosEitorActive;
	bool SaveScene;
	bool ShowOgreDebug;
	bool ShowContactReport;
	bool PosEditorScale;
	bool StopKeys;
	bool StopCapture;
	bool FileView_SceneLoaded;
	bool Show_VRD_Editor;
	bool Show_VRD_Shape;
	bool VRD_HideMesh;
	bool SceneAltered;
	bool ShowMarker;

}Flags_Type;
//==================================== Terrain Structure	
typedef struct Layers_Type { 

	char Texture0[256];
	char Texture1[256];
	char LayerSize[256];
	
}Layers_Type;

typedef struct Terrain_Type { 

	char WorldSize[256];
	char WorldHeight[256];
	char MapSize[256];
	char MapDistance[256];
	char MinHeight[256];
	char MaxHeight[256];
	char LodLevel[256];
	char WorldTexture[256];	
	char BlendCount[256];

	Layers_Type Layers[10];

	char FullPath[256];
	
	char DetailTexture[256];
	char DetailTile[256];
	char Heightmap_image[256];
	char PageSize[256];
	char TileSize[256];
	char MaxPixelError[256];
	char PageWorldX[256];
	char PageWorldZ[256];
	
	char MaxMipMapLevel[256];
	char VertexProgramMorph[256];
	char LODMorphStart[256];
	int Manager16;
	int Manager17;
	int ManagerETM;
	char VertexMorph;
	int VertexMorphTog;

	Ogre::String blendImages[10];
}Terrain_Type;

//==================================== Load Options Structure
typedef struct Load_Options_Type { 
	bool Has_Planes;
	bool Has_Objects;
	bool Has_Particles;
	bool Has_Weapons;
	bool Has_CC;
	bool Has_Debug;
}Load_Options_Type;

typedef struct Message_Type { 
	Ogre::Overlay* overlay;
	Ogre::OverlayContainer* panel;
	Ogre::TextAreaOverlayElement* textArea1;
	Ogre::TextAreaOverlayElement* textArea2;
	Ogre::Real PosLeft;
	Ogre::Real PosTop;
	Colour_Type Colour;
	
}Message_Type;

extern Flags_Type*		Flags[1];
extern Scene_Type*		S_Scene[1];
extern Camera_Type*		S_Camera[5];
extern Terrain_Type*	S_Terrain[1];
extern Load_Options_Type* S_LoadOptions[1];
extern Player_Type*		S_Player[1];
extern Object_Type*		S_Object[300];
extern ObjectMove_Type* S_ObjectMove[1];
extern Message_Type*	S_Message[100];
extern MoveEntity_Type*	S_MoveEntity[30];
