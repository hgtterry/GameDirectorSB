#pragma once
class SB_Equity
{
public:
	SB_Equity();
	~SB_Equity();

	bool StartMeshDesign();

	Ogre::SceneNode*		MvNode;

	ManualObject*		GridManual;
	SceneNode*			GridNode;

	ManualObject*		HairManual;
	SceneNode*			HairNode;

	Ogre::ManualObject *manObj;
	Ogre::SceneNode*	ModelNode;

	Ogre::SceneManager* mSceneMgrMeshView;

	VM_Render*		RenderListener;

protected:

	static LRESULT CALLBACK MeshDesign_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Init_Bmps_Globals(void);

	bool Set_OgreWindow(void);
	void Close_OgreWindow(void);

	void Grid_Update(bool Create);
	void Hair_Update(bool Create);

	void Update_Model(void);

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
	int HairExtend;

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
	Ogre::SceneNode*	CamNode;
};

