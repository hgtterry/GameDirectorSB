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

	char Pref_WE_FileName[255];			//World Editor/RFpro File 3ds
	char Pref_WE_Path_FileName[1024];	//World Editor/RFpro File 3ds

protected:

	static LRESULT CALLBACK Preferences_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	FILE *WriteScene;
};

