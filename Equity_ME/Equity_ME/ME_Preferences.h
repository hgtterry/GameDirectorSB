#pragma once
class ME_Preferences
{
public:
	ME_Preferences();
	~ME_Preferences();

	bool Read_Preferences();
	bool Write_Preferences();

	char Pref_Txl_FileName[MAX_PATH];
	char Pref_Txl_Path_FileName[MAX_PATH];

	char Pref_WE_JustFileName[MAX_PATH];			//World Editor/RFpro File 3ds
	char Pref_WE_Path_FileName[MAX_PATH];		//World Editor/RFpro File 3ds

	char Pref_Ogre_JustFileName[MAX_PATH];		//Ogre File for Update
	char Pref_Ogre_Path[MAX_PATH];				//Ogre File for Update Location

protected:

	FILE *WriteScene;
};

