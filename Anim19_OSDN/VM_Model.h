#pragma once
class VM_Model
{
public:
	VM_Model();
	~VM_Model();

	void Set_Paths(void);

	char FileName[255];				// Just the File name of the model NO Path includes the extension
	char Path_FileName[1024];		// Full Path to Model including file name and extension
	char JustName[255];				// Model name No Path No Extension
	char Texture_FolderPath[1024];	// Just the Path of the model Textures location includes "\" at the end
	char Texture_FullPath[1024];
	char Model_FullPath[1024];
};

