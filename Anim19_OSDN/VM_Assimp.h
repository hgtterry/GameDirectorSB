

#include "cimport.h"
//#include "Importer.hpp"
//#include "Exporter.hpp"
#include "PostProcess.h"
#include "Scene.h"
#include "DefaultLogger.hpp"
#include "LogStream.hpp"
#include "matrix4x4.h"

#pragma once
class VM_Assimp
{
public:
	VM_Assimp();
	~VM_Assimp();

	bool LoadFile(const char* pFile);

	long int SelectedPreset;

	int mTotalVertices;

protected:

	void logInfo(std::string logString);
	void logDebug(const char* logString);

	void GetBasicInfo(const aiScene* pScene);
	void Create_MeshGroups(const aiScene* pScene);
	void Get_Group_VertCount(const aiScene* pScene);
	void StoreMeshData(const aiScene* pScene);
};

