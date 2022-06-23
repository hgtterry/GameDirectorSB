#include "stdafx.h"
#include "Base_Group.h"


Base_Group::Base_Group()
{
	GroupName[0] = 0;
	MaterialName[0] = 0;
	Text_FileName[0] = 0;

	Bitmap_Loaded = 0;

	Base_Bitmap = NULL;
}


Base_Group::~Base_Group()
{
}
