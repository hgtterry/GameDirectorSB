#pragma once
class SB_Import_Room
{
public:
	SB_Import_Room();
	~SB_Import_Room();

	bool Room_Loader(char* Extension, char* Extension2);

	Ogre::String TempResourceGroup;   // Tempory Reosource Group

protected:

	void AddToScene(void);
	bool Open_Room_File(char* Extension, char* Title, char* StartDirectory);
	void Set_Paths(void);
	
	char Room_FileName[MAX_PATH];
	char Room_Path_FileName[MAX_PATH];
	char Texture_FolderPath[MAX_PATH];
	char FileName[MAX_PATH];

	OPENFILENAME ofn;
};

