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

typedef struct Folder_Type
{
	char Folder_Path[1024];
	bool Selected;
}Folder_Type;

typedef struct Selection_type2
{
	char Name[255];
	char Type[255];
	char Shape[255];

}Selection_type2;

class SB_MeshViewer
{
public:
	SB_MeshViewer();
	~SB_MeshViewer();
	bool StartMeshViewer();

	char Chr_CurrentFolder[1024];
	char Selected_MeshFile[1024];
	char Object_Name[255];
	char Last_MeshFile[255];
	Ogre::SceneNode*		MvNode;

	Selection_type2*			S_Selection[1];

	HWND MainDlgHwnd;
	int Physics_Type;
	int Physics_Shape;

	bool ShowRooms;
	bool ShowBuildings;
	bool SelectDynamic;
	bool SelectStatic;
	bool SelectTriMesh;


	bool ShowMisc;
	int Mesh_Viewer_Mode;

	int Media_Folders_Count;
	std::vector<std::string> Media_Folders_Vec;

	char TempFolder[1024];


protected:

	static LRESULT CALLBACK MeshViewer_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ShapeDialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Folders_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	std::vector<Folder_Type> Folder_Vec;
	int FolderList_Count;

	bool Clear_ButFlags();
	bool Set_OgreWindow(void);
	void Close_OgreWindow(void);

	void ShowMesh(char* MeshFile, bool Update);

	void Start_ShapeDialog();
	void Reset_Shape_Flags();

	void Enable_ShapeButtons(bool state);
	void Enable_TypeButtons(bool state);

	bool Get_Files();

	//  Folders
	//----------------------------------
	bool Selected_Shape_Box;
	bool Selected_Shape_Sphere;
	bool Selected_Shape_Capsule;
	bool Selected_Shape_Cylinder;
	bool Selected_Shape_Cone;

	bool Start_Folders();
	void Create_Properties_hLV(void);
	bool Update_ListView();

	bool Create_Resources_Group();
	bool Add_Resources();
	bool Delete_Resources_Group();

	Ogre::String MV_Resource_Group;

	HWND Folders_MainWin_hWnd;
	HWND Properties_hLV;

	HWND MeshView_Hwnd;
	HWND ListHwnd;
	HWND CB_hWnd;

	Ogre::Entity*			MvEnt;

	Ogre::RenderWindow* MeshView_Window;
	Ogre::SceneManager* mSceneMgrMeshView;
	Ogre::Camera*		mCameraMeshView;
	Ogre::SceneNode*	CamNode;
};

