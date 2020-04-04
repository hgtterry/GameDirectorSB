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
	bool StartBrowser(char* szInitDir);
	bool Create_Output_Folder(char* Extension);

	void Init_History();
	void LoadHistory();
	void Save_FileHistory();
	void RecentFileHistory_Update();
	void ResentHistory_Clear();

	bool Search_For_Folder(char* FolderPath);

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
	char OutputFolder[1024];

	char UserData_Folder[1024];

	std::vector<std::string> mPreviousFiles;

	CHOOSECOLOR color;
	OPENFILENAME ofn;

protected:
	static int __stdcall BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData);

	FILE *WriteRecentFiles;
	FILE *ReadRecentFiles;

	HMENU mHistoryMenu;

#define EQUITY_NUM_RECENT_FILES 0x8
#define EQUITY_RECENT_FILE_ID(_n_) (5000 + _n_)
};

