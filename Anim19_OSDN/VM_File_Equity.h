#pragma once
class VM_File_Equity
{
public:
	VM_File_Equity();
	~VM_File_Equity();

	bool SaveFile(char* Extension, char* Title, char* FileName);
	bool WriteData_File();
	bool Write_All(int Count);

	char mFileName[255];
	char mPath_FileName[1024];

	FILE *WriteScene;

	OPENFILENAME ofn;
};

