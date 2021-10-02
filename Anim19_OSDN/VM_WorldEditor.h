#pragma once
class VM_WorldEditor
{
public:
	VM_WorldEditor();
	~VM_WorldEditor();

	void Adjust();;
	void Change_Textures();

	bool Txt_OpenFile(char* Extension, char* Title, char* StartDirectory);

	char Txt_FileName[255];
	char Txt_Path_FileName[1024];

protected:

	bool LoadFile();

	OPENFILENAME ofn;
};

