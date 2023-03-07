/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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

#include "GD19_Ogre.h"
#include "GD19_Utilities.h"
#include "GD19_Grid.h"
#include "GD19_Panels.h"
#include "GD19_Bullet.h"
#include "GD19_Ini.h"
#include "GD19_DIALOGS.h"
#include "GD19_Objects_Com.h"
#include "GD19_LookUps.h"
#include "GD19_PB.h"


// Vima19 19/03/20
#include "VM_ImGui.h"

// ---------------------------------------------------- 07/12/21
#include "EB_Options.h"

// ---------------------------------------------------- 18/10/21
#include "SB_Keyboard.h"
#include "SB_Player.h"
#include "SB_Import.h"
#include "SB_Project.h"
#include "SB_Dialogs.h"
#include "SB_Physics.h"
#include "SB_FileView.h"
#include "SB_Properties.h"
#include "SB_Camera.h"
#include "SB_3DT.h"
#include "SB_Resources.h"
#include "SB_Scene.h"
#include "SB_TopTabs.h"
#include "SB_MeshViewer.h"
#include "SB_Debug.h"
#include "SB_FileIO.h"
#include "SB_Object.h"
#include "SB_Objects_Create.h"
#include "SB_Dimensions.h"
#include "SB_Collision.h"
#include "SB_SoundMgr.h"
#include "SB_Markers.h"
#include "SB_Props_Dialogs.h"

#include "Com_Diaolgs.h"
#include "SB_Import_Room.h"
#include "SB_LookUps.h"
#include "SB_Preferences.h"
#include "SB_Display.h"
#include "SB_Build.h"

#include "SB_Com_Entity.h"
#include "SB_Com_MoveEntity.h"
#include "SB_Com_Area.h"
#include "SB_Com_Environments.h"
#include "SB_Com_Lights.h"

#include "SB_Project_Create.h"
#include "SB_Locations.h"
#include "SB_Gui_Dialogs.h"
#include "SB_Gui_Environment.h"
#include "SB_Materials.h"
#include "Bass_Front_Dialog.h"
#include "SB_Gui_Properties.h"
#include "SB_Editor_Gui.h"

#include "DynamicCharacterController.h"

// :- Terry and Hazel Flanigan 2022

class GD19_App
{

public:

	SB_Ogre*			SBC_Ogre;
	GD19_Utilities*		Cl_Utilities;
	SB_Grid*			SBC_Grid;
	SB_Bullet*			SBC_Bullet;
	T_Ini*				Cl_Ini;
	GD19_Dialogs*		Cl_Dialogs;
	GD19_Objects_Com*	Cl_Objects_Com;
	GD19_LookUps*		Cl_LookUps;
	GD19_PB*			Cl_PB;
	
	// Vima19 19/03/20
	VM_ImGui*			CL_Vm_ImGui;

	// ---------------------------------------------------- 07/12/21
	EB_Options*				EBC_Options;		// Dialogs for Equity [151221]

	// ---------------------------------------------------- 18/10/21

	SB_Keyboard*			SBC_Keyboard;
	SB_Player*				SBC_Player;
	SB_Import*				SBC_Import;
	SB_Project*				SBC_Project;
	SB_Dialogs*				SBC_Dialogs;
	SB_Physics*				SBC_Physics;
	SB_FileView*			SBC_FileView;
	SB_Properties*			SBC_Properties;
	SB_Com_Camera*			SBC_Com_Camera;
	SB_3DT*					SBC_3DT;
	SB_Resources*			SBC_Resources;		// Resources Class Used by the Level [081221]
	SB_Scene*				SBC_Scene;			// Collection Class For Level [081221]
	SB_TopTabs*				SBC_TopTabs;		// Top Bar Tabs Class Level Editor [081221]
	SB_MeshViewer*			SBC_MeshViewer;
	SB_Debug*				SBC_Debug;
	SB_FileIO*				SBC_FileIO;
	SB_Import_Room*			SBC_Import_Room;
	SB_Object*				SBC_Object;
	SB_Objects_Create*		SBC_Objects_Create;
	SB_Dimensions*			SBC_Dimensions;
	SB_Collision*			SBC_Collision;
	SB_SoundMgr*			SBC_SoundMgr;
	SB_Markers*				SBC_Markers;
	SB_Props_Dialogs*		SBC_Props_Dialog;
	SB_LookUps*				SBC_LookUps;
	SB_Preferences*			CL_Prefs;
	SB_Display*				SBC_Display;
	SB_Build*				SBC_Build;
	SB_Panels*				SBC_Panels;


	SB_Com_Entity*			SBC_Com_Entity;
	SB_Com_MoveEntity*		SBC_Com_MoveEntity;
	SB_Com_Area*			SBC_Com_Area;
	SB_Com_Environments*	SBC_Com_Environments;
	SB_Com_Lights*			SBC_Com_Lights;
	
	SB_Project_Create*		SBC_Project_Create;
	SB_Locations*			SBC_Locations;
	SB_Gui_Dialogs*			SBC_Gui_Dialogs;
	SB_Gui_Environment*		SBC_Gui_Environ;
	SB_Materials*			SBC_Materials;

	Bass_Front_Dialog*		SBC_Front_Dlg;
	SB_Gui_Properties*		SBC_Gui_Propreties;
	SB_Editor_Gui*			CL_Editor_Gui;

	DynamicCharacterController*		SBC_DCC;


	Com_Diaolgs*			Com_CDialogs;		// Common Dialogs for App [291221]
	// ----------------------------------- 
	GD19_App(void);
	~GD19_App(void);

	bool InitApp(void);
	bool SetMainWinCentre(void);
	bool Resize_OgreWin(void);
	void SetBrushes_Fonts(void);
	void RedrawWindow_Dlg(HWND hDlg);

	void SetTitleBar(HWND hDlg);
	void Set_Main_TitleBar(char * PathFile);

	void GetPriority_Class();

	bool Custom_Button_Normal(LPNMCUSTOMDRAW item);
	bool Custom_Button_Toggle(LPNMCUSTOMDRAW item, bool Toggle);
	bool Custom_Button_Green(LPNMCUSTOMDRAW item);
	bool Custom_Button_Blue(LPNMCUSTOMDRAW item);
	bool Custom_Button_Red(LPNMCUSTOMDRAW item);

	bool Custom_Button_Toggle_Tabs(LPNMCUSTOMDRAW item, bool Toggle);

	void LoadProgramResource(void);

	void Debug_Text();
	void Say(const char* Message);
	void Say_Int(int Value);
	void Say_Win(const char* Message);
	void Log_Messageg(char* Message);

	void Flash_Window();

	void Disable_Panels(bool Disable);
	void Show_Panels(bool show);

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
	HFONT Font_Arial20;
	HFONT Font_CB15_Bold;
	HFONT Font_Banner;

	HMENU mMenu;
	HCURSOR CUR;

	int CursorPosX;
	int CursorPosY;

	bool OgreStarted;
	bool Debug_App;

	char EquityDirecory_FullPath[MAX_PATH];
	char Version[100];
	char LevelDirectory[MAX_PATH];
	char DeskTop_Folder[MAX_PATH];
	char ETemp_Folder[MAX_PATH];
	char Default_Project[MAX_PATH];

};

extern GD19_App* App;

