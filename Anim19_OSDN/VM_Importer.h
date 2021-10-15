#pragma once
class VM_Importer
{
public:
	VM_Importer();
	~VM_Importer();

	bool Assimp_Loader(char* Extension, char* Extension2);
	bool Genesis3D_Loader(void);
	bool WorldEditor_Loader(void);
	bool Ogre_Loader(char* Extension, char* Extension2);

	void Reload_FromResentFiles(char* ResentPathAndFile);

	void Set_Equity(void);
};

