#pragma once
class SB_Import_Room
{
public:
	SB_Import_Room();
	~SB_Import_Room();

	void SB_Import_Room::AddToScene(void);

	Ogre::Entity*		OgreModel_Ent;

protected:

	bool Open_Room_File(char* Extension, char* Title, char* StartDirectory);

	Ogre::SceneNode* OgreModel_Node;

	Ogre::String TempResourceGroup;   // Tempory Reosource Group

	char Room_FileName[MAX_PATH];
	char Room_Path_FileName[MAX_PATH];
	char Texture_FolderPath[MAX_PATH];
	char FileName[MAX_PATH];

	OPENFILENAME ofn;
};

