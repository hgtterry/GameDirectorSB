#pragma once


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


typedef struct Int_Type {int Array;}int_Type;


//--------------------------------------------------------
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
	bool Play;
}Sound_Type;

typedef struct Scene_Type { 	
	int PlaneCount;
	char TerrainFileName[255];
	char LevelName[255]; // Just Level Name no extension
	char SceneVersion[32];
	char GDSceneName[255];
	char Full_Path_AndFile[1024];
	char Level_Directory[1024]; // Level Directory Full Path

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


class GD19_Scene_Data
{
public:
	GD19_Scene_Data(void);
	~GD19_Scene_Data(void);

	bool Init_Scene(void);
	bool Init_Class(void);

	void SetScene_Defaults(void);
	void SetOptions_Defaults(void);
	void SetFlags_Defaults(void);

	void Set_Move_Defaults(int Index);

	bool Open_Project_Dlg(char* Extension, char* Title, char* StartDirectory);
	
	bool Show_Entities(bool YesNo);

	bool Is_Meshes_Used(char* Name);
	
	Flags_Type*				S_Flags[1];
	Scene_Type*				S_Scene[1];
	Load_Options_Type*		S_LoadOptions[1];
	Stock_Sound_type*		St_Sounds[200];

	int Player_Location_Count;
	int Stock_Messgae_Count;
	int Stock_Sound_Count;
	int NewObjectID;
	int CurrentCamMode;
	bool SceneLoaded;
	bool Scene_Has_Area;

	//---------------------Unique Counters
	int Locations_ID_Counter; //Unique Counter
	int StockSounds_ID_Counter;

	char mFilename[1024];
	char Path_mFilename[1024];

	char Data_mFilename[1024];
	char Data_Path_mFilename[1024];

	FILE* Write_OBJECTFILE;
	OPENFILENAME ofn;

protected:


};

