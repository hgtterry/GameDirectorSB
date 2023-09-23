#pragma once
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

#include "Base_Player.h"
#include "Base_Object.h"

class SB_Scene
{
public:
	SB_Scene();
	~SB_Scene();

	bool Clear_Level();
	void Go_FullScreen_Mode(void);
	void Build_World(int ExpSelected);
	bool Level_Build_G3ds(Level3* pLevel, const char* Filename, BrushList* BList, int ExpSelected, geBoolean ExpLights, int GroupID);
	bool BrushList_Export(BrushList* BList, geBoolean SubBrush);
	bool Brush_Export(const Brush* b);
	bool FaceList_Export(const Brush* b, const FaceList* pList, int BrushCount, int SubBrushCount);
	int Get_Adjusted_Index(int RealIndex);
	bool AddTexture_GL(geVFile* BaseFile, const char* TextureName, int GroupIndex);
	void Update_Scene(void);
	bool Create_Resources_Group();
	bool Delete_Resources_Group();
	bool Add_Resource_Location_Project(char* Resource_Location);

	Brush* Selected_Brush;

	std::vector<Base_Player*> B_Player;
	std::vector<Base_Object*> V_Object;

	bool Scene_Loaded;
	bool Area_Added;
	bool Player_Added;
	int Player_Count;
	int Object_Count;

	int AdjusedIndex_Store[500];
	int AdjustedIndex_Count;

	bool Picking(void);

	bool FullScreenMode_Flag;
	bool SameBrush;

	bool Scene_Modified;
	bool Project_Resources_Created;

	int BrushChange;
	int SubBrushChange;

	Ogre::String Project_Resource_Group;
};

