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

class SB_MeshViewer
{
public:
	SB_MeshViewer();
	~SB_MeshViewer();

	bool StartMeshViewer();

	char mResource_Folder[MAX_PATH];
	char Selected_MeshFile[MAX_PATH];
	char Object_Name[MAX_PATH];
	char Last_MeshFile[MAX_PATH];
	char m_Material_File[MAX_PATH];
	char m_Current_Folder[MAX_PATH];

	Ogre::SceneNode*		MvNode;
	HWND MainDlgHwnd;

	int Physics_Type;
	int Physics_Shape;

	bool SelectDynamic;
	bool SelectStatic;
	bool SelectTriMesh;

	int Mesh_Viewer_Mode;
	
protected:

	static LRESULT CALLBACK MeshViewer_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Properties_ListBox_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void SetUp_Area_Trimesh(HWND hDlg);

	void Set_ResourceMesh_File(HWND hDlg);

	bool Set_OgreWindow(void);
	void Close_OgreWindow(void);

	void ShowMesh(char* MeshFile);

	void Reset_Shape_Flags();

	void Enable_ShapeButtons(bool state);
	void Enable_TypeButtons(bool state);

	bool Get_Files();

	void Start_Properties_ListBox();
	//  Folders
	//----------------------------------
	bool Selected_Shape_Box;
	bool Selected_Shape_Sphere;
	bool Selected_Shape_Capsule;
	bool Selected_Shape_Cylinder;
	bool Selected_Shape_Cone;

	bool Create_Resources_Group();
	bool Add_Resources();
	bool Delete_Resources_Group();

	bool Get_Media_Folders_Actors(HWND DropHwnd);
	bool GetMeshFiles(char* Location, bool ResetList);

	Ogre::String MV_Resource_Group;

	HWND MeshView_Hwnd;
	HWND ListHwnd;
	
	HWND CB_hWnd;

	Ogre::Entity*		MvEnt;

	Ogre::RenderWindow* MeshView_Window;
	Ogre::SceneManager* mSceneMgrMeshView;
	Ogre::Camera*		mCameraMeshView;
	Ogre::SceneNode*	CamNode;
};

