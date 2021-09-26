#pragma once
class VM_File_Equity
{
public:
	VM_File_Equity();
	~VM_File_Equity();

	bool SaveFile(char* Extension, char* Title, char* FileName);
	bool WriteData_File();
	bool Write_Vertices(int Count);
	bool Write_Face_Indices(int Count);
	void Convert_To_GlobalMesh(void);

	bool Write_Global_Vertices();

	char mFileName[255];
	char mPath_FileName[1024];

	FILE *WriteScene;

	OPENFILENAME ofn;
};

