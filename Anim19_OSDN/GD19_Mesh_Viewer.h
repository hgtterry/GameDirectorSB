#pragma once

typedef struct Selection_type 
{
	char Name[255];
	char Type[255];
	char Shape[255];

}Selection_type;

class GD19_Mesh_Viewer
{
public:
	GD19_Mesh_Viewer(void);
	~GD19_Mesh_Viewer(void);

	bool StartMeshViewer();

	char Chr_CurrentFolder[1024];
	char Selected_MeshFile[1024];
	char Object_Name[255];
	char Last_MeshFile[255];
	Ogre::SceneNode*		MvNode;

	Selection_type*			S_Selection[1];

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


protected:

	static LRESULT CALLBACK MeshViewer_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK ShapeDialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool Clear_ButFlags();
	bool Set_OgreWindow(void);
	void Close_OgreWindow(void);
	void SelectStartFolder(void);

	bool GetMeshFiles(char* Location,bool ResetList);
	bool Get_Sub_Folders(char* Folder, HWND DropHwnd);
	void ShowMesh(char* MeshFile,bool Update);

	void Start_ShapeDialog();
	void Reset_Shape_Flags();

	void Enable_ShapeButtons(bool state);
	void Enable_TypeButtons(bool state);

	bool Get_Media_Folders_Actors(HWND DropHwnd);

	bool Selected_Shape_Box;
	bool Selected_Shape_Sphere;
	bool Selected_Shape_Capsule;
	bool Selected_Shape_Cylinder;
	bool Selected_Shape_Cone;

	HWND MeshView_Hwnd;
	HWND ListHwnd;
	
	Ogre::Entity*			MvEnt; 

	Ogre::RenderWindow* MeshView_Window;
	Ogre::SceneManager* mSceneMgrMeshView;
	Ogre::Camera*		mCameraMeshView;
	Ogre::SceneNode*	CamNode;

};

