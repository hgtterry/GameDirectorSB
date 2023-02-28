#pragma once
class ME_Preferences
{
public:
	ME_Preferences();
	~ME_Preferences();

	void Start_Preferences_GUI();
	void Preferences_GUI();
	void Close_Preferences_GUI();

	bool Read_Preferences();
	bool Write_Preferences();

	bool Show_Preferences_GUI;
	int Preferences_Page;

	bool Prefs_TestFile_Flag;
	bool Prefs_StartScreen_Flag;
	bool Prefs_FullScreen_Flag;
	bool Prefs_Load_LastScene_Flag;

	char Pref_Txl_FileName[MAX_PATH];
	char Pref_Txl_Path_FileName[MAX_PATH];

	char Pref_WE_JustFileName[MAX_PATH];			//World Editor/RFpro File 3ds
	char Pref_WE_Path_FileName[MAX_PATH];		//World Editor/RFpro File 3ds

	char Pref_Ogre_JustFileName[MAX_PATH];		//Ogre File for Update
	char Pref_Ogre_Path[MAX_PATH];				//Ogre File for Update Location


protected:

	FILE *WriteScene;

	float PosX;
	float PosY;
};

