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

#include "StdAfx.h"
#include "AB_App.h"
#include "SB_Model.h"

SB_Model::SB_Model(void)
{
	VerticeCount = 0;
	FaceCount = 0;
	GroupCount = 0;
	TextureCount = 0;
	MotionCount = 0;
}

SB_Model::~SB_Model(void)
{
}

// *************************************************************************
// *		Create_Mesh_Group:- Terry and Hazel Flanigan 2023		  	   *
// *************************************************************************
void SB_Model::Create_Mesh_Group(int Index)
{
	if (Group[Index] != nullptr)
	{
		delete Group[Index];
		Group[Index] = nullptr;
	}

	Group[Index] = new Base_Group();

}

// *************************************************************************
// *		Get_Groupt_Count:- Terry and Hazel Flanigan 2023		   	   *
// *************************************************************************
int SB_Model::Get_Groupt_Count()
{
	return GroupCount;
}

// *************************************************************************
// *			Set_Groupt_Count:- Terry and Hazel Flanigan 2023	 	   *
// *************************************************************************
void SB_Model::Set_Groupt_Count(int Count)
{
	GroupCount = Count;
}

// *************************************************************************
// *		Set_Groupt_Count:- Terry and Hazel Flanigan 2023	  		   *
// *************************************************************************
void SB_Model::Set_Texture_Count(int Count)
{
	TextureCount = Count;
}

// *************************************************************************
// *			Set_Groupt_Count:- Terry and Hazel Flanigan 2023	   	   *
// *************************************************************************
void SB_Model::Set_Motion_Count(int Count)
{
	MotionCount = Count;
}
