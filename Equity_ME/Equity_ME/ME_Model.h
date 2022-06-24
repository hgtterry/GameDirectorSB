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

class ME_Model
{
public:
	ME_Model();
	~ME_Model();

	Base_Group*			Group[100];

	void Set_Groupt_Count(int Count);
	int Get_Groupt_Count();
	void Set_Texture_Count(int Count);
	void Set_Motion_Count(int Count);

	char FileName[MAX_PATH];
	char Path_FileName[MAX_PATH];
	char Model_FolderPath[MAX_PATH];
	char Texture_FolderPath[MAX_PATH];
	char JustName[MAX_PATH];

	void Set_Paths(void);

protected:

	int GroupCount;
	int TextureCount;
	int MotionCount;
};

