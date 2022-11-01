#pragma once


typedef struct Int_Type {int Array;}int_Type;

class GD19_Scene_Data
{
public:
	GD19_Scene_Data(void);
	~GD19_Scene_Data(void);


	bool Init_Class(void);

	bool Open_Project_Dlg(char* Extension, char* Title, char* StartDirectory);
	
	bool Show_Entities(bool YesNo);

	bool Is_Meshes_Used(char* Name);
	
	int Player_Location_Count;
	int Stock_Messgae_Count;
	int Stock_Sound_Count;
	int NewObjectID;
	
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

