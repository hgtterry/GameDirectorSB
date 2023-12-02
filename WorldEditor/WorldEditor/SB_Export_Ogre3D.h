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

#pragma once

using namespace std;
using namespace Ogre;

class SB_Export_Ogre3D
{
public:
	SB_Export_Ogre3D(void);
	~SB_Export_Ogre3D(void);

	void Export_To_Ogre3D(bool Create);
	void Convert_ToOgre3D(bool Create);

	Ogre::SceneNode* World_Node;

private:

	void Set_World_Paths(void);
	void Set_Export_Paths(void);
	void Get_Data(int Index, int FaceIndex);
	bool DecompileTextures_TXL(char* PathAndFile);
	void CreateMaterialFile(char* MatFileName);

	char mDirectory_Name[MAX_PATH];
	char mSelected_Directory[MAX_PATH];

	char mWorld_File_Path[MAX_PATH];
	char mWorld_File_PathAndFile[MAX_PATH];

	char mExport_Just_Name[MAX_PATH];

	char mExport_Path[MAX_PATH];
	char mExport_PathAndFile_Material[MAX_PATH];
	char mExport_PathAndFile_Mesh[MAX_PATH];

	float nx;
	float ny;
	float nz;

	float u;
	float v;

	float x;
	float y;
	float z;

	Ogre::ManualObject* Export_Manual;
	Ogre::ManualObject* World_Manual;

	Ogre::Entity* World_Ent;
};

