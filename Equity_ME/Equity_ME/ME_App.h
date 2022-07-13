/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

#include "ME_Ogre.h"
#include "ME_Utilities.h"
#include "ME_Grid.h"
#include "ME_ImGui.h"
#include "ME_Assimp.h"
#include "ME_Import.h"
#include "ME_FileIO.h"
#include "ME_Model.h"
#include "ME_TopBar.h"
#include "ME_FileView.h"
#include "ME_Groups.h"
#include "ME_Panels.h"
#include "ME_Textures.h"
#include "ME_Dialogs.h"
#include "ME_Dimensions.h"

#include "ME_Export.h"
#include "ME_Export_Object.h"
#include "ME_Export_Milkshape.h"

#include "ME_Genesis3D.h"
#include "ME_Ogre3D.h"
#include "ME_Motions.h"

class ME_App
{
public:
	ME_App();
	~ME_App();

	ME_Ogre*			CL_Ogre;			// Ogre Main Class [120122]
	ME_Utilities*		CL_Utilities;		// Maths String Routines [130122]
	ME_Grid*			CL_Grid;			// Main Grid Routines [150122]
	ME_ImGui*			CL_ImGui;
	ME_Assimp*			CL_Assimp;			// Assimp Model Importer[220222]
	ME_Import*			CL_Import;			// Importer Class [050322]
	ME_FileIO*			CL_FileIO;			// Windows Open/Save Routines [050322]
	ME_Model*			CL_Model;			// Main Model Class [050322]
	ME_TopBar*			CL_TopBar;			// Top Bar and Tabs [130322]
	ME_FileView*		CL_FileView;		// FileView [210622]
	ME_Groups*			CL_Groups;			// Groups  [220622]
	ME_Panels*			CL_Panels;			// Panels  [220623]
	ME_Textures*		CL_Textures;		// Textures [220623]
	ME_Dialogs*			CL_Dialogs;			// Common Dialogs [220626]
	ME_Dimensions*		CL_Dimensions;		// Scale Position Rotation [220627]

	ME_Export*			CL_Export;			// Exporters [220630]
	ME_Export_Object*	CL_Export_Object;
	ME_Export_Milkshape* CL_Export_Milk;	// Milkshape Exporter [070722]

	ME_Genesis3D*		CL_Genesis3D;		// All Things Genesis/RF [080722]
	ME_Ogre3D*			CL_Ogre3D;
	ME_Motions*			CL_Motions;			// Motions [100722]

	bool InitApp(void);
	bool SetMainWin_Centre(void);

	void LoadProgramResource(void);
	void SetBrushes_Fonts(void);
	bool ResizeOgre_Window(void);

	bool Custom_Button_Toggle(LPNMCUSTOMDRAW item, bool Toggle);
	bool Custom_Button_Toggle_Tabs(LPNMCUSTOMDRAW item, bool Toggle);
	bool Custom_Button_Normal(LPNMCUSTOMDRAW item);

	HBRUSH CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item);

	void Say(const char* Message);
	void Say_Win(const char* Message);
	void Say_Int(int Value);
	void Say_Float(float Value);

	HINSTANCE hInst;	// Store instance handle in our global variable [120122]

	HWND MainHwnd;		// Main Window hWnd [120122]
	HWND Fdlg;			// Main Window BackGround [120122]
	HWND ViewGLhWnd;	// Ogre Render Window [120122]
	HWND ListPanel;		
	
	HBRUSH AppBackground;	// Main App Background Colour [120122]
	HBRUSH BlackBrush;		// Black Brush Colour [120122]
	HBRUSH Brush_White;		// Black Brush Colour [120122]
	HBRUSH Brush_Green;		// Black Brush Colour [120122]

	HBRUSH Brush_But_Pressed;
	HBRUSH Brush_But_Normal;
	HBRUSH Brush_But_Hover;

	HBRUSH Brush_Tabs;
	HBRUSH Brush_Tabs_UnSelected;

	HFONT Font_CB15;
	HFONT Font_CB18;
	HFONT Font_Arial20;

	HANDLE Hnd_GridOn_Bmp;
	HANDLE Hnd_GridOff_Bmp;
	HANDLE Hnd_ModelInfo_Bmp;		// Bitmap for button Model Info Screen
	HANDLE Hnd_ModelInfoOn_Bmp;
	HANDLE Hnd_BBOn_Bmp;
	HANDLE Hnd_BBOff_Bmp;
	HANDLE Hnd_MeshOn_Bmp;
	HANDLE Hnd_MeshOff_Bmp;
	HANDLE Hnd_HairOn_Bmp;
	HANDLE Hnd_HairOff_Bmp;
	HANDLE Hnd_TexturesOn_Bmp;
	HANDLE Hnd_TexturesOff_Bmp;
	HANDLE Hnd_MeshPointsOn_Bmp;
	HANDLE Hnd_MeshPointsOff_Bmp;
	HANDLE Hnd_BonesOn_Bmp;
	HANDLE Hnd_BonesOff_Bmp;
	HANDLE Hnd_NormalsOn_Bmp;
	HANDLE Hnd_NormalsOff_Bmp;
	HANDLE Hnd_LightsOn_Bmp;
	HANDLE Hnd_LightsOff_Bmp;
	HANDLE Hnd_PlayOff_Bmp;
	HANDLE Hnd_PlayOn_Bmp;
	HANDLE Hnd_PlayStop_Bmp;


	HMENU mMenu;
	HCURSOR CUR;

	char EquityDirecory_FullPath[MAX_PATH];
	char Version[255];
};

extern ME_App* App;

