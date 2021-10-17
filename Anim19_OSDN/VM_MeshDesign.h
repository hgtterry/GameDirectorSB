#pragma once
class VM_MeshDesign
{
public:
	VM_MeshDesign();
	~VM_MeshDesign();

	bool StartMeshDesign();

	Ogre::SceneNode*		MvNode;
	ManualObject*		GridManual;
	SceneNode*			GridNode;

protected:

	static LRESULT CALLBACK MeshDesign_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool Set_OgreWindow(void);
	void Close_OgreWindow(void);

	void Grid_Update(bool Create);

	HWND MeshView_Hwnd;
	HWND MeshViewDialog_Hwnd;

	bool ShowGridFlag;
	bool ShowDivisions;
	bool ShowHair;

	int XAxis_min;
	int	XAxis_max;
	int YAxis_min;
	int	YAxis_max;
	int ZAxis_min;
	int	ZAxis_max;

	int Scale_X;
	int Scale_Y;
	int Scale_Z;

	int Division_X;
	int Division_Y;
	int Division_Z;


	Ogre::ColourValue ColourMain;
	Ogre::ColourValue ColourHairZ;
	Ogre::ColourValue ColourHairX;
	Ogre::ColourValue ColourHairY;
	Ogre::ColourValue ColourDivision;

	Ogre::Entity*			MvEnt;

	Ogre::RenderWindow* MeshView_Window;
	Ogre::SceneManager* mSceneMgrMeshView;
	Ogre::SceneNode*	CamNode;
};

