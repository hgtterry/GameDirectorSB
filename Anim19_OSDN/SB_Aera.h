/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

#include "Base_Area.h"

class SB_Aera
{
public:
	SB_Aera();
	~SB_Aera();

	void Reset_Class(void);

	bool Start_Area_PropsPanel();
	void Hide_Area_Dlg(bool Show);

	bool Show_Physics_Debug; // Show Physics Debug For Area [021221]

	void Add_Aera_To_Project(int Index, char* FileName, char* Resource_Location);

	void Set_Environment_Defaults(int Index);

	HWND Area_Props_HWND;

protected:

	static LRESULT CALLBACK Area_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	//btBvhTriangleMeshShape* create_Area_Trimesh(Base_Area* Object);
	btBvhTriangleMeshShape* create_Area_Trimesh_New(int Index,Base_Area* Object);
};

