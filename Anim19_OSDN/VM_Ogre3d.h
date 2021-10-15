#pragma once
class VM_Ogre3d
{
public:
	VM_Ogre3d();
	~VM_Ogre3d();

	bool Export_AssimpToOgre(void);
	bool Load_OgreModel(void);

protected:

	bool CreateDirectoryMesh(void);
	bool DecompileTextures(void);
	bool CreateMeshFile(char* MatFileName);
	void CreateMaterialFile(char* MatFileName);

	void AddToScene(void);

	char mDecompileFolder[1024];
	char mOgreMeshFileName[255];
	char mOgreScriptFileName[255];
	char mOgreSkellFileName[255];
	char mOgreSkellTagName[255];
};

