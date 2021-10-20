#pragma once
class VM_Preferences
{
public:
	VM_Preferences();
	~VM_Preferences();

	bool Write_Preferences();
	bool Read_Preferences();

	bool Start_Preferences();

	char Pref_Txl_FileName[255];
	char Pref_Txl_Path_FileName[1024];

	char Pref_WE_JustFileName[255];			//World Editor/RFpro File 3ds
	char Pref_WE_Path_FileName[1024];		//World Editor/RFpro File 3ds

	char Pref_Ogre_JustFileName[255];		//Ogre File for Update
	char Pref_Ogre_Path[1024];		//Ogre File for Update Location

protected:

	static LRESULT CALLBACK Preferences_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	FILE *WriteScene;
};

