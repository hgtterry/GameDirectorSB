/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

This software is provided 'as-is', without any express or implied
warranty. In no event will the authors be held liable for any damages
arising from the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it
freely, subject to the following restrictions:

1. The origin of this software must not be misrepresented; you must not
claim that you wrote the original software. If you use this software
in a product, an acknowledgment in the product documentation would be
appreciated but is not required.

2. Altered source versions must be plainly marked as such, and must not be
misrepresented as being the original software.

3. This notice may not be removed or altered from any source
distribution.
*/

#pragma once

#include "Base_Group.h"

typedef struct AABB_Type {
	vertex_type BB_Max[1];
	vertex_type BB_Min[1];
	vertex_type Size[1];
	vertex_type Centre[1];
	float radius;
} AABB_Type;


class ME_Model
{
public:
	ME_Model();
	~ME_Model();

	Base_Group*			Group[100];

	void Reset_Class(void);

	void Convert_To_GlobalMesh(void);
	void Set_Groupt_Count(int Count);
	int Get_Groupt_Count();
	void Set_Texture_Count(int Count);
	void Set_Motion_Count(int Count);
	void Create_Mesh_Group(int Index);
	void Create_BondingBox_Model(void);
	bool GetBoundingBoxModel_Update(void);

	void Clear_Model_And_Reset(void);

	char FileName[MAX_PATH];
	char Path_FileName[MAX_PATH];
	char Model_FolderPath[MAX_PATH];
	char Texture_FolderPath[MAX_PATH];
	char JustName[MAX_PATH];

	AABB_Type*				S_BoundingBox[1];

	void Set_Paths(void);

	int VerticeCount;			// Group Vertice Count 
	int FaceCount;				// Group Face Count 

	int Model_Type;

	bool Model_Loaded;

	std::vector<vertex_type> vertex_Data;
	std::vector<polygon_type> Face_Data;
	std::vector<normal_type> Normal_Data;
	std::vector<mapcoord_type> MapCord_Data;
	std::vector<int> MatIndex_Data;

protected:

	int GroupCount;
	int TextureCount;
	int MotionCount;
};

