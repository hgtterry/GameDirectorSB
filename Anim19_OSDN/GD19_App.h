/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
#include "GD19_FileView.h"
#include "GD19_Panels.h"
#include "GD19_Load_Scene.h"
#include "GD19_Save_Scene.h"
#include "GD19_File_IO.h"
#include "GD19_Scene_Data.h"
#include "GD19_Bullet.h"
#include "GD19_Player.h"
#include "GD19_Collision.h"
#include "GD19_Ini.h"
#include "GD19_SoundMgr.h"
#include "GD19_Panel_Com.h"
#include "GD19_Resources.h"
#include "GD19_Visuals.h"
#include "GD19_Objects_New.h"
#include "GD19_Environment.h"
#include "GD19_DIALOGS.h"
#include "GD19_Mesh_Viewer.h"
#include "GD19_Objects_Com.h"
#include "GD19_Dimensions.h"
#include "GD19_Properties.h"
#include "GD19_Object_Properties.h"
#include "GD19_Stock.h"
#include "GD19_LookUps.h"
#include "GD19_ToolBar.h"
#include "GD19_Objects_FFile.h"
#include "GD_spdlog.h"
#include "GD19_PB.h"
#include "GD_Keyboard.h"

#include "GD19_FileView_V2.h" // Test


// Vima19 19/03/20

#include "VM_Importer.h"
#include "VM_Genisis3D.h"
#include "VM_Model.h"
#include "VM_Textures.h"
#include "VM_TopBar.h"
#include "VM_Motions.h"
#include "VM_Exporter.h"
#include "VM_FileIO.h"
#include "VM_ImGui.h"
#include "VM_TextLib.h"
#include "VM_Groups.h"


class GD19_App
{

public:

	GD19_Ogre*			Cl19_Ogre;
	GD19_Utilities*		Cl_Utilities;
	GD19_Grid*			Cl_Grid;
	GD19_FileView*		Cl_FileView;
	GD19_FileView_V2*	Cl_FileView_V2;
	GD19_Panels*		Cl_Panels;
	GD19_Load_Scene*	Cl_Load_Scene;
	GD19_Save_Scene*	Cl_Save_Scene;
	
	GD19_Scene_Data*	Cl_Scene_Data;
	GD19_Bullet*		Cl_Bullet;
	GD19_Player*		Cl_Player;
	GD19_Collision*		Cl_Collision;
	T_Ini*				Cl_Ini;
	GD19_SoundMgr*		Cl_SoundMgr;
	GD19_Panel_Com*		Cl_Panels_Com;
	GD19_Resources*		Cl_Resources;
	GD19_Visuals*		Cl_Visuals;
	GD19_Objects_New*	Cl_Objects_New;
	GD19_Environment*	Cl_Environment;
	GD19_Dialogs*		Cl_Dialogs;
	GD19_Mesh_Viewer*	Cl_Mesh_Viewer;
	GD19_Objects_Com*	Cl_Objects_Com;
	GD19_Dimensions*	Cl_Dimensions;
	GD19_Properties*	Cl_Properties;
	GD19_Object_Properties* Cl_Object_Props;
	GD19_Stock*			Cl_Stock;
	GD19_LookUps*		Cl_LookUps;
	GD19_ToolBar*		Cl_ToolBar;
	GD19_Objects_FFile*	Cl_Objects_FFile;
	GD_spdlog*			Cl_spdlog;
	GD19_PB*			Cl_PB;
	GD_Keyboard*		Cl_Keyboard;

	// Vima19 19/03/20
	VM_Importer*		CL_Importer;
	VM_Genisis3D*		CL_Vm_Genesis3D;
	VM_Model*			CL_Vm_Model;
	VM_Textures*		CL_Vm_Textures;
	VM_TopBar*			CL_Vm_TopBar;
	VM_Motions*			CL_Vm_Motions;
	VM_Exporter*		CL_Vm_Exporter;
	VM_FileIO*			CL_Vm_FileIO;
	VM_ImGui*			CL_Vm_ImGui;
	VM_TextLib*			CL_Vm_TextLib;
	VM_Groups*			CL_Vm_Groups;


	GD19_App(void);
	~GD19_App(void);

	bool InitApp(void);
	bool SetMainWinCentre(void);
	bool Resize_OgreWin(void);
	void SetBrushes_Fonts(void);
	void RedrawWindow_Dlg(HWND hDlg);
	void SetTitleBar(HWND hDlg);

	void GetPriority_Class();

	bool Custom_Button_Normal(LPNMCUSTOMDRAW item);
	bool Custom_Button_Toggle(LPNMCUSTOMDRAW item, bool Toggle);
	bool Custom_Button_Green(LPNMCUSTOMDRAW item);
	bool Custom_Button_Blue(LPNMCUSTOMDRAW item);
	bool Custom_Button_Red(LPNMCUSTOMDRAW item);

	bool Custom_Button_Toggle_Tabs(LPNMCUSTOMDRAW item, bool Toggle);

	HBRUSH CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item);

	void LoadProgramResource(void);

	void Say(const char* Message);
	void Say_Int(int Value);

	bool Start_Scene_Loaded;
	bool FullScreen;
	bool FullScreen_App;
	bool RenderBackGround;

	bool FollowFunctions;

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

	HANDLE Hnd_TexturesOn_Bmp;
	HANDLE Hnd_TexturesOff_Bmp;
	HANDLE Hnd_Info_Bmp;
	HANDLE Hnd_InfoSmall_Bmp;

	HFONT Font_CB12;
	HFONT Font_CB15;
	HFONT Font_Arial20;
	HFONT Font_CB15_Bold;

	HMENU mMenu;
	HCURSOR CUR;

	bool OgreStarted;
	
	char EquityDirecory_FullPath[1024];
	char Version[100];
	char LevelDirectory[1024];
	char DeskTop_Folder[1024];

};

extern GD19_App* App;

