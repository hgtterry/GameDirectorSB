#pragma once

#include "Model_Data.h"

class VM_Model
{
public:
	VM_Model();
	~VM_Model();

	void Set_Paths(void);
	void Create_S_MeshGroup(int Index);
	void Clear_ModelData(void);
	void Reset_Counters(void);

	char FileName[255];				// Just the File name of the model NO Path includes the extension
	char Path_FileName[1024];		// Full Path to Model including file name and extension
	char JustName[255];				// Model name No Path No Extension
	char Model_FolderPath[1024];	// Just the Path of the model Textures location includes "\" at the end
	char Texture_FolderPath[1024];
	
	int VerticeCount;
	int NormalsCount;
	int FaceCount;

	int GroupCount;

	int TextureCount;
	int MotionCount;
	int BoneCount;

	int Model_Type;
	int Model_Loaded;

	Texture_Type*			S_Texture[1];
	GLTextureInfo_Type *	S_TextureInfo[30];
	Bone_Type*				S_Bones[200];
	MeshGroup_Type*			S_MeshGroup[500];
	AABB_Type*				S_BoundingBox[1];
	//AllTextureInfo_Type *	S_AllTexturesInfo[40];

	std::vector<vertex_type> vertex_Data;
	std::vector<normal_type> Normal_Data;
	std::vector<polygon_type> Face_Data;
	std::vector<int> MatIndex_Data;
	std::vector<mapcoord_type> MapCord_Data;
	std::vector<Char_type> MotionNames_Data;
	std::vector<Char_type> TextureNames_Data;

};

