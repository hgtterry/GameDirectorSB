#pragma once


//==================================== Application Flags Structure	
typedef struct Flags_Type 
{ 
	bool GameMode;

}Flags_Type;

//==================================== Sound Structure

typedef struct Int_Type {int Array;}int_Type;


//--------------------------------------------------------

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
	int MoveWhat;

}Scene_Type;


class GD19_Scene_Data
{
public:
	GD19_Scene_Data(void);
	~GD19_Scene_Data(void);

	bool Init_Scene(void);
	bool Init_Class(void);

	void SetScene_Defaults(void);

	void SetFlags_Defaults(void);

	void Set_Move_Defaults(int Index);

	bool Open_Project_Dlg(char* Extension, char* Title, char* StartDirectory);
	
	bool Show_Entities(bool YesNo);

	bool Is_Meshes_Used(char* Name);
	
	Flags_Type*				S_Flags[1];
	Scene_Type*				S_Scene[1];

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

