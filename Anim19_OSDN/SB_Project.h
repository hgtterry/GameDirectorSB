/*
Copyright (c) 2021 Stage Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Project
{
public:
	SB_Project();
	~SB_Project();

	bool Start_Create_Project();

	char Project_Name[255];
	char Project_Path[1024];
	char Project_FullPath[1024];

	char Project_Ini_FilePath[1024];

	char Level_Folder_Path[1024];

	char Level_Folder_Path_World[1024];

protected:

	static LRESULT CALLBACK Create_Project_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool Create_Project();

	bool Set_Paths();
	bool Write_Project_Ini();
	bool Create_Level_Folder();
	bool Add_World();
	bool Write_Player();


	FILE *Write_Ini;
	FILE *Write_Player_Ini;
	FILE *WriteFile;
};
