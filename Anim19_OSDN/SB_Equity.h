#pragma once
class SB_Equity
{
public:
	SB_Equity();
	~SB_Equity();

	bool Start_Equity();
	void Set_Equity(void);;

	void Reset_View(void);
	void Zoom(void);

	void Update_Model(void);
	void Convert_Model(void);

	bool Get_View_Height_Width(void);

	bool Model_Loaded;

	Ogre::SceneNode*		MvNode;

	ManualObject*		GridManual;
	SceneNode*			GridNode;

	ManualObject*		HairManual;
	SceneNode*			HairNode;

	Ogre::ManualObject *manObj;
	Ogre::SceneNode*	ModelNode;

	Ogre::SceneManager* mSceneMgrMeshView;

	VM_Render*		RenderListener;

	HWND MainWindow_Hwnd; // Main Equity Editor Window Handel (HWND) [121221]

	OgreImGui  EB_imgui;

	bool Use_Imgui;
	bool Show_Gui_Debug;

protected:

	static LRESULT CALLBACK Equity_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Init_Bmps_Globals(void);

	bool Set_OgreWindow(void);
	void Close_OgreWindow(void);

	void Grid_Update(bool Create);
	void Hair_Update(bool Create);

	HWND RenderWindow_Hwnd; // Equity Render Window Handel for Ogre (HWND) [121221]
	
	bool ShowGridFlag;
	bool ShowDivisions;
	bool ShowHair;

	bool Toggle_Faces_Flag;
	bool Toggle_Textures_Flag;
	bool Toggle_Points_Flag;
	bool Toggle_Bones_Flag;
	bool Toggle_Normals_Flag;
	bool Toggle_BBox_Flag;
	bool Toggle_Grid_Flag;
	bool Toggle_Hair_Flag;
	bool Toggle_Light_Flag;

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

#define EQUITY_NUM_RECENT_FILES2 0x8
#define EQUITY_RECENT_FILE_ID2(_n_) (6000 + _n_)
};

