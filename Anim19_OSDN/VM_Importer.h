#pragma once
class VM_Importer
{
public:
	VM_Importer();
	~VM_Importer();

	bool Assimp_Loader(char* Extension, char* Extension2);
	bool Genesis3D_Loader(void);
	void Reload_FromResentFiles(char* ResentPathAndFile);

	void Set_Hazel19(void);
};

