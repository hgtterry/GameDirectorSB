/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

#include "stdafx.h"
#include "SB_Base_Group.h"

Base_Group::Base_Group()
{
	GroupName[0] = 0;
	MaterialName[0] = 0;
	Text_FileName[0] = 0;

	Texture_FolderPath[0] = 0;
	Texture_PathFileName[0] = 0;

	Bitmap_Loaded = 0;

	GroupVertCount = 0;

	IndicesCount = 0; // Ogre
	BoneAssignMentCount = 0; // Ogre

	MaterialIndex = 0;
	Soil_TextureIndex = 0;

	Base_Bitmap = NULL;
	//RF_Bitmap = NULL;
	ListView_Item = NULL;

	// Bounding Box
	BB_Max.x = 0;
	BB_Max.y = 0;
	BB_Max.z = 0;

	BB_Min.x = 0;
	BB_Min.y = 0;
	BB_Min.z = 0;

	Size.x = 0;
	Size.y = 0;
	Size.z = 0;

	Centre.x = 0;
	Centre.y = 0;
	Centre.z = 0;

	radius = 0;;
}


Base_Group::~Base_Group()
{
}
