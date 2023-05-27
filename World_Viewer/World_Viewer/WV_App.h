/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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
*/ // :- Terry and Hazel Flanigan 2023

#pragma once

#include "WV_Ogre.h"
#include "WV_Grid.h"
#include "WV_ImGui.h"
#include "WV_Loader.h"
#include "WV_Ini.h"
#include "WV_Assimp.h"
#include "WV_World.h"
#include "WV_Export_Ogre3D.h"
#include "WV_PB.h"
#include "WV_Load_Ogre.h"
#include "WV_Keyboard.h"
#include "WV_Dialogs.h"
#include "WV_Bullet.h"
#include "WV_TopTabs.h"
#include "WV_Player.h"
#include "WV_Properties.h"
#include "WV_Physics.h"
#include "WV_Import_3DT.h"


#include "WV_Faces.h"

#include "WV_BrushTabs_Dlg.h"

#include "A_Export_World.h"

#include "DynamicCharacterController.h"

#include "WE_SPLITVIEWS.h"

// Fusion
#include "CLevel.h"
#include "CFaceList.h"
#include "CBox3d.h"
#include "CFaces.h"
#include "CRender.h"
#include "CBrush.h"
#include "CBrushTemplate.h"
#include "CUtil.h"
#include "CList.h"
#include "CGroup.h"
#include "CModel.h"
#include "CFusionDoc.h"





class WV_App
{

public:

	WV_Ogre*		CL_Ogre;
	WV_Grid*		CL_Grid;
	WV_ImGui*		CL_ImGui;
	WV_Loader*		CL_Loader;
	WV_Ini*			CL_Ini;
	WV_Assimp*		CL_Assimp;
	WV_World*		CL_Scene;
	WV_Export_Ogre*	CL_Export_Ogre;
	WV_PB*			CL_PB;
	WV_Load_Ogre*	CL_Load_Ogre;
	WV_Keyboard*	CL_Keyboard;
	WV_Dialogs*		CL_Dialogs;
	WV_Bullet*		CL_Bullet;
	WV_TopTabs*		CL_TopTabs;
	WV_Player*		CL_Player;
	WV_Properties*	CL_Properties;
	WV_Physics*		CL_Physics;
	WV_Import_3DT*	CL_Import_3DT;

	WV_Faces*		CL_Faces;

	WV_BrushTabs_Dlg* CL_BrushTabs_Dlg;

	A_Export_World* CL_Export_World;

	DynamicCharacterController* CL_DCC;

	WE_SpliterViews*	CL_SplitterViews;

	// Fusion
	CFusionDoc*			CL_CFusionDoc;
	CLevel*				CL_CLevel;
	CGroup*				CL_CGroup;
	CUtil*				CL_CUtil;
	CModel*				CL_CModel;
	CList*				CL_CList;
	CBrushTemplate*		CL_CBrushTemplate;
	CRender*			CL_CRender;
	CFaces*				CL_CFaces;
	CBox3d*				CL_CBox3d;
	CBrush*				CL_CBrush;
	CFaceList*			CL_CFaceList;
	// ----------------------------------- 
	WV_App(void);
	~WV_App(void);

	bool InitApp(void);
	bool SetMainWinCentre(void);
	bool Resize_OgreWin(void);
	void SetBrushes_Fonts(void);
	void RedrawWindow_Dlg(HWND hDlg);

	void SetTitleBar(HWND hDlg);
	void Set_Main_TitleBar(char * PathFile);

	bool Custom_Button_Normal(LPNMCUSTOMDRAW item);
	bool Custom_Button_Toggle(LPNMCUSTOMDRAW item, bool Toggle);
	bool Custom_Button_Green(LPNMCUSTOMDRAW item);
	bool Custom_Button_Blue(LPNMCUSTOMDRAW item);
	bool Custom_Button_Red(LPNMCUSTOMDRAW item);

	bool Custom_Button_Toggle_Tabs(LPNMCUSTOMDRAW item, bool Toggle);

	void LoadProgramResource(void);

	void Debug_Text();

	HWND cmdHandle = NULL;

	bool IsProcessRunning(char* executableName);

	void Say(const char* Message, char* Message2 = NULL);
	void Say_Int(int Value);
	void Say_Win(const char* Message);
	
	void Flash_Window();

	bool Start_Scene_Loaded;
	bool FullScreen;
	bool FullScreen_App;
	bool RenderBackGround;

	bool Panels_Disabled_Flag;
	bool Panels_Hidden_Flag;

	bool FollowFunctions;

	bool Block_Mouse_Buttons;

	HWND Fdlg;
	HINSTANCE hInst;
	HWND MainHwnd;
	HWND ListPanel;

	HWND ViewGLhWnd;
	
	HWND ViewPLeaseWait;
	HWND Physics_Console_Hwnd;

	HWND GD_Properties_Hwnd;

	HBRUSH AppBackground;
	HBRUSH DialogBackGround;
	HBRUSH AppTest;
	HBRUSH Brush_Panel;
	HBRUSH BlackBrush;
	HBRUSH Brush_White;
	HBRUSH Brush_Red;
	HBRUSH Brush_Blue;
	HBRUSH Brush_Green;
	HBRUSH Brush_But_Pressed;
	HBRUSH Brush_But_Normal;
	HBRUSH Brush_But_Hover;
	HBRUSH Brush_Tabs;
	HBRUSH Brush_Tabs_UnSelected;

	HBRUSH Brush_Button;
	HBRUSH Brush_Button_Hover;

	HANDLE Hnd_PinOff;
	HANDLE Hnd_PinOn;
	HANDLE Hnd_FlipWindingOrder; // 
	HANDLE Hnd_FullScreen_Bmp;		// Bitmap for button Full Screen
	HANDLE Hnd_ModelInfo_Bmp;		// Bitmap for button Model Info Screen
	HANDLE Hnd_MouseSensitivity_Bmp;// Bitmap for button MouseSensitivity Screen
	HANDLE Hnd_Projection_Bmp;

	HANDLE Hnd_LightsOn_Bmp;
	HANDLE Hnd_LightsOff_Bmp;

	HANDLE Hnd_BBOn_Bmp;
	HANDLE Hnd_BBOff_Bmp;

	HANDLE Hnd_NormalsOn_Bmp;
	HANDLE Hnd_NormalsOff_Bmp;

	HANDLE Hnd_BonesOn_Bmp;
	HANDLE Hnd_BonesOff_Bmp;

	HANDLE Hnd_MeshPointsOn_Bmp;
	HANDLE Hnd_MeshPointsOff_Bmp;

	HANDLE Hnd_MeshOn_Bmp;
	HANDLE Hnd_MeshOff_Bmp;

	HANDLE Hnd_GridOn_Bmp;
	HANDLE Hnd_GridOff_Bmp;

	HANDLE Hnd_HairOn_Bmp;
	HANDLE Hnd_HairOff_Bmp;

	HANDLE Hnd_TexturesOn_Bmp;
	HANDLE Hnd_TexturesOff_Bmp;
	HANDLE Hnd_Info_Bmp;
	HANDLE Hnd_InfoSmall_Bmp;

	HANDLE Hnd_PhysicsOff_Bmp;
	HANDLE Hnd_PhysicsOn_Bmp;

	HANDLE Hnd_Playoff;
	HANDLE Hnd_PlayOn;
	HANDLE Hnd_PlayStop;
	HANDLE Hnd_StepBack;
	HANDLE Hnd_StepForward;

	HANDLE Hnd_InfoBig_Bmp;

	HFONT Font_CB12;
	HFONT Font_CB15;
	HFONT Font_CB18;
	HFONT Font_Arial20;
	HFONT Font_CB15_Bold;
	HFONT Font_Banner;

	HMENU mMenu;
	HCURSOR CUR;

	int CursorPosX;
	int CursorPosY;

	bool OgreStarted;
	bool Debug_App;
	bool V_New_Objects;
	bool Is_WorldEditor;

	char EquityDirecory_FullPath[MAX_PATH];
	char Version[100];
	char LevelDirectory[MAX_PATH];
	char DeskTop_Folder[MAX_PATH];
	char ETemp_Folder[MAX_PATH];
	char Default_Project[MAX_PATH];

};

extern WV_App* App;

