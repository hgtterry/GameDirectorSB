#pragma once


typedef struct Int_Type {int Array;}int_Type;

class GD19_Scene_Data
{
public:
	GD19_Scene_Data(void);
	~GD19_Scene_Data(void);

	bool Open_Project_Dlg(char* Extension, char* Title, char* StartDirectory);
	
	char mFilename[1024];
	char Path_mFilename[1024];

	char Data_mFilename[1024];
	char Data_Path_mFilename[1024];

	FILE* Write_OBJECTFILE;
	OPENFILENAME ofn;

protected:


};

