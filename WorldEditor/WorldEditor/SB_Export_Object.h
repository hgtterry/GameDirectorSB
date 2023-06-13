#pragma once
class SB_Export_Object
{
public:
	SB_Export_Object();
	~SB_Export_Object();

	bool Create_ObjectFile(void);

protected:

	void Write_ObjectFile(void);
	void Write_ObjectFile_Commit(void);
	bool WriteMTLFile(void);
	
	char OutputFolder[1024];

	char Object_FileName[255];
	char mtl_FileName[255];
	char Just_mtl_FileName[255];

	FILE *Write_OBJECTFILE;
	FILE *Write_MTLFile;
};

