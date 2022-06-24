#include "stdafx.h"
#include "Base_Group.h"


Base_Group::Base_Group()
{
	GroupName[0] = 0;
	MaterialName[0] = 0;
	Text_FileName[0] = 0;

	Texture_FolderPath[0] = 0;
	Texture_PathFileName[0] = 0;

	Bitmap_Loaded = 0;

	GroupVertCount = 0;
	MaterialIndex = 0;

	Base_Bitmap = NULL;

	ListView_Item = NULL;
}


Base_Group::~Base_Group()
{
}
