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

:- Terry and Hazel Flanigan 2022

*/

#pragma once
class SB_Resources
{
public:
	SB_Resources();
	~SB_Resources();

	void Start_Resources(HWND hDlg);

	void Start_List_Folders(HWND List, char *FileName, bool ListDlg);
	void List_Folders(HWND List, char *StartFolder, char *FileName, bool ListDlg);

	void List_MeshMaterials(HWND List);

	void Unload_Materials(void);
	void Remove_OblectMesh(void);
	
	bool Show_Project_Res();
	bool Show_App_Res();
	bool Show_MV_Res();

protected:
	static LRESULT CALLBACK Resources_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool CreateListGeneral_FX(HWND hDlg);
	bool ShowAllMaterials();
	bool SearchFolders();
	bool FindPath(char* SubFolder, char* File, char* StartFolder);
	bool FindPath_New(char* File, char* Folder);

	bool ShowUsedMaterials();

	bool ShowAllTextures();
	bool ShowAllMeshes();

	bool Show_Scene_Meshes(HWND hDlg);

	char ResourcePath[2048];

	bool Active_MeshMaterials;
	bool Active_Textures;

	bool Show_App_Res_Flag;
	bool Show_MV_Res_Flag;
	bool Show_Project_Res_Flag;

	HWND FX_General_hLV;
};

