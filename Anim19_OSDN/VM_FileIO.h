#pragma once
class VM_FileIO
{
public:
	VM_FileIO();
	~VM_FileIO();

	bool Vm_OpenFile(char* Extension, char* Title, char* StartDirectory);

	bool OpenFile(char* Extension, char* Title, char* StartDirectory);
	bool SaveFileCom(char* Extension, char* Title, char* StartDirectory);
	bool SaveFile(char* Extension, char* Title, char* FileName); // ?

	bool GetColor();

	bool Update_File_Info(char* Full_Path, char* File_Name);

	bool SearchFolders(char* Path, char* File);
	bool StartBrowser(char* szInitDir);;

	bool Cannceled;

	char Scene_FileName[255];
	char Scene_Path_FileName[1024];

	char Model_FileName[255];
	char Model_Path_FileName[1024];

	char mSaveFileCom[255];
	char mSavePathFileCom[255];

	char Full_Path_And_File[1024];
	char Just_FileName[1024];

	char BrowserMessage[250];
	TCHAR szSelectedDir[500];

	CHOOSECOLOR color;
	OPENFILENAME ofn;

protected:
	static int __stdcall BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData);
};

