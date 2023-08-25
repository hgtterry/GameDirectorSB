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

#include "level.h"
#include "entity.h"
#include "brush.h"
#include "model.h"
#include "group.h"
#include "wadfile.h"
#include "compiler.h"
#include "EntView.h"
#include "BrushTemplate.h"
#include "EntityTable.h"
#include "basetype.h"
typedef struct tag_Level3 Level3;

class SB_Export_World
{
public:
	SB_Export_World(void);
	~SB_Export_World(void);

	void Export_World_GD3D(bool Silent);

	bool Level_Build_G3ds(Level3 *pLevel, const char *Filename, BrushList *BList,int ExpSelected, geBoolean ExpLights, int GroupID);
	void ExportTo_RFW(const char *FileName, int ExpSelected, geBoolean ExpLights, geBoolean ExpFiles);
	bool Write_Project_File(char* Path_And_File,const char* Filename);


	void Export_World_Text(int ExpSelected);
	bool Level_Build_Text_G3ds(Level3* pLevel, const char* Filename, BrushList* BList, int ExpSelected, geBoolean ExpLights, int GroupID);
	bool BrushList_ExportToText(BrushList* BList, geBoolean SubBrush);
	bool Brush_ExportToText(const Brush* b);
	bool FaceList_ExportToText(const Brush* b, const FaceList* pList, int BrushCount, int SubBrushCount);

private:

	FILE* WriteScene;
	FILE* WriteScene_TXT;
};
