/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

#include "SB_Base_Group.h"

#pragma once
class SB_Model
{
public:
	SB_Model(void);
	~SB_Model(void);

	Base_Group* Group[5000];

	void Create_Mesh_Group(int Index);
	int Get_Groupt_Count();
	void Set_Groupt_Count(int Count);
	void Set_Texture_Count(int Count);
	void Set_Motion_Count(int Count);

	void SB_Model::Set_Paths(void);

	char FileName[MAX_PATH];
	char Path_FileName[MAX_PATH];
	char Model_FolderPath[MAX_PATH];
	char Texture_FolderPath[MAX_PATH];
	char JustName[MAX_PATH];

	int VerticeCount;
	int FaceCount;
	int GroupCount;
	int TextureCount;
	int MotionCount;
};

