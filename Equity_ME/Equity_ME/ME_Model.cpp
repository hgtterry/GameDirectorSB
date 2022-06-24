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

#include "stdafx.h"
#include "ME_App.h"
#include "ME_Model.h"


ME_Model::ME_Model()
{
	GroupCount = 0;
	TextureCount = 0;
	MotionCount = 0;

	FileName[0] = 0;
	Path_FileName[0] = 0;
	Model_FolderPath[0] = 0;
	Texture_FolderPath[0] = 0;
	JustName[0] = 0;
}


ME_Model::~ME_Model()
{
}

// *************************************************************************
// *						Set_Groupt_Count Terry Flanigan		  	 	   *
// *************************************************************************
void ME_Model::Set_Groupt_Count(int Count)
{
	GroupCount = Count;
}

// *************************************************************************
// *						Get_Groupt_Count Terry Flanigan		  	 	   *
// *************************************************************************
int ME_Model::Get_Groupt_Count()
{
	return GroupCount;
}

// *************************************************************************
// *						Set_Groupt_Count Terry Flanigan		  	 	   *
// *************************************************************************
void ME_Model::Set_Texture_Count(int Count)
{
	TextureCount = Count;
}

// *************************************************************************
// *						Set_Groupt_Count Terry Flanigan		  	 	   *
// *************************************************************************
void ME_Model::Set_Motion_Count(int Count)
{
	MotionCount = Count;
}

// *************************************************************************
// *						Set_Paths Terry Bernie						   *
// *************************************************************************
void ME_Model::Set_Paths(void)
{
	strcpy(FileName, App->CL_FileIO->Model_FileName);
	strcpy(Path_FileName, App->CL_FileIO->Model_Path_FileName);

	// Get Texture path assumed at this point to be where model is
	int len1 = strlen(FileName);
	int len2 = strlen(Path_FileName);
	strcpy(Model_FolderPath, Path_FileName);
	Model_FolderPath[len2 - len1] = 0;

	strcpy(Texture_FolderPath, Model_FolderPath); // Back Slash remains
	
	strcpy(JustName, FileName);
	int Len = strlen(JustName);
	JustName[Len - 4] = 0;

	//App->CL_Vm_FileIO->RecentFileHistory_Update();
}
