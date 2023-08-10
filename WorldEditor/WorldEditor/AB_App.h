/*
Copyright (c) 2023 World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

#if !defined(AFX_SB_APP_H__F1CE337E_1C46_4F80_9639_566F8F7DFBD6__INCLUDED_)
#define AFX_SB_APP_H__F1CE337E_1C46_4F80_9639_566F8F7DFBD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "FUSIONDoc.h"
//#include "FUSIONView.h"

#include "AB_Export_RFW.h"
#include "A_FileIO.h"
#include "A_Dialogs.h"
#include "A_Scene.h"
#include "A_Render_App.h"
#include "A_TxlEditor.h"
#include "A_TextureDialog.h"
#include "A_FaceDialog.h"

#include "A_TabsControl.h"
#include "A_TabsGroups_Dlg.h"
#include "A_TabsTemplates_Dlg.h"

#include "A_CreateArchDialog.h"
#include "A_CreateBoxDialog.h"
#include "A_CreateConeDialog.h"
#include "A_CreateCylDialog.h"
#include "A_CreateSpheroidDialog.h"
#include "A_CreateStaircaseDialog.h"
#include "A_Camera.h"
#include "A_TopTabs.h"
#include "A_File.h"
#include "A_Brush.h"

#include "A_MainView.h"

#include "SB_Export_World.h"
#include "F_View.h"

// Scene Builder 
#include "SB_Ogre.h"
#include "SB_Grid.h"
#include "SB_Equity.h"
#include "SB_Keyboard.h"
#include "SB_Camera.h"
#include "SB_Assimp.h"
#include "SB_Model.h"
#include "SB_Loader.h"
#include "SB_Ini.h"
#include "SB_Export_Ogre3D.h"
#include "SB_Export_Object.h"
#include "SB_Exporter.h"
#include "SB_Textures.h"
#include "SB_Dialogs.h"
#include "SB_ImGui.h"
#include "SB_Genesis3D.h"
#include "SB_Brushes.h"
#include "SB_RecentFiles.h"
#include "SB_TopTabs_Equity.h"
#include "SB_Dimensions.h"
#include "SB_Preferences.h"
#include "SB_Doc.h"

#include "SB_Bullet.h"
#include "SB_Player.h"
//#include <stack>

class SB_App
{
public:

	SB_App();
	virtual ~SB_App();

	//std::stack::size();

	AB_Export_RFW*				ABC_Export_RFW;
	SB_FileIO*					CLSB_FileIO;
	A_Dialogs*					CL_Dialogs;
	A_World*					CL_World;
	A_Render_App*				CL_Render_App;
	A_TxlEditor*				CL_TxlEditor;
	A_TextureDialog*			CL_TextureDialog;
	A_FaceDialog*				CL_FaceDialog;
	A_TabsControl*				CL_TabsControl;
	A_TabsGroups_Dlg*			CL_TabsGroups_Dlg;
	A_TabsTemplates_Dlg*		CL_TabsTemplates_Dlg;

	A_CreateArchDialog*			CL_CreateArchDialog;
	A_CreateBoxDialog*			CL_CreateBoxDialog;
	A_CreateConeDialog*			CL_CreateConeDialog;
	A_CreateCylDialog*			CL_CreateCylDialog;
	A_CreateSpheroidDialog*		CL_CreateSpheroidDialog;
	A_CreateStaircaseDialog*	CL_CreateStaircaseDialog;
	SB_Camera_WE*				CLSB_Camera_WE;
	SB_TopTabs*					CLSB_TopTabs;
	SB_File_WE*					CLSB_File_WE;
	A_Brush*					CL_Brush;

	SB_Export_World*			CLSB_Export_World;

	A_MainView*					CL_Main_View;

	F_View*						CL_F_View;

	// Scene Builder 
	SB_Ogre*					CLSB_Ogre;
	SB_Grid*					CLSB_Grid;
	SB_Equity*					CLSB_Equity;
	SB_Keyboard*				CLSB_Keyboard;
	SB_Camera_EQ*				CLSB_Camera_EQ;
	SB_Assimp*					CLSB_Assimp;
	SB_Model*					CLSB_Model;
	SB_Loader*					CLSB_Loader;
	SB_Ini*						CLSB_Ini;
	SB_Export_Ogre3D*			CLSB_Export_Ogre3D;
	SB_Export_Object*			CLSB_Export_Object;
	SB_Exporter*				CLSB_Exporter;
	SB_Textures*				CLSB_Textures;
	SB_Dialogs*					CLSB_Dialogs;
	SB_ImGui*					CLSB_ImGui;
	SB_Genesis3D*				CLSB_Genesis3D;
	SB_Brushes*					CLSB_Brushes;
	SB_RecentFiles*				CLSB_RecentFiles;
	SB_TopTabs_Equity*			CLSB_TopTabs_Equity;
	SB_Dimensions*				CLSB_Dimensions;
	SB_Preferences*				CLSB_Preferences;
	SB_Doc*						CLSB_Doc;
	SB_Bullet*					CLSB_Bullet;
	SB_Player*					CLSB_Player;

	bool InitApp(void);
	void InitMFC(void);

	void SetBrushes_Fonts(void);
	void LoadProgramResource(void);

	void Say(const char* Message, char* Message2 = NULL);
	void Say_Int(int Value);
	void Say_Float(float Value);
	void Say_Vector3(Ogre::Vector3 Vector);
	void Message_ToFile(char* Message);
	void Error_ToFile(char* Message, char* Message2 = NULL);
	void Clear_ErrorLog();

	void Flash_Window();
	bool IsProcessRunning(char* executableName);
	uint64_t Get_Stack(void);

	bool Custom_Button_Greyed(LPNMCUSTOMDRAW item);
	bool Custom_Button_Normal(LPNMCUSTOMDRAW item);
	bool Custom_Button_Toggle(LPNMCUSTOMDRAW item, bool Toggle);
	bool Custom_Button_Toggle_Tabs(LPNMCUSTOMDRAW item, bool Toggle);

	bool Custom_Button_Normal_MFC(LPDRAWITEMSTRUCT lpDIS,HWND hDlg);
	bool Custom_Button_Toggle_MFC(LPDRAWITEMSTRUCT lpDIS,HWND hDlg, bool Toggle);
	bool Custom_Button_Toggle_Disable(LPDRAWITEMSTRUCT lpDIS,HWND hDlg, bool Toggle);

	void Debug_Set(void);
	void Debug_Close(void);
	void Debug_Message(char* Message, bool NewLine);
	void Debug_Int(int Value, bool NewLine);
	void Debug_Float(float Value, bool NewLine);
	void Wait_For_Key(int Delay);

	HBRUSH CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item);

	char WorldEditor_Directory[MAX_PATH];

	HBRUSH AppBackground;	
	HBRUSH BlackBrush;		
	HBRUSH Brush_White;		
	HBRUSH Brush_Green;		

	HBRUSH Brush_But_Pressed;
	HBRUSH Brush_But_Normal;
	HBRUSH Brush_But_Hover;
	HBRUSH Brush_Tabs_UnSelected;
	HBRUSH Brush_Tabs;

	HFONT Font_CB15;
	HFONT Font_CB18;
	HFONT Font_Arial20;
	HFONT Font_Banner;

	HANDLE Hnd_HollowBox_Bmp;
	HANDLE Hnd_SolidBox_Bmp;

	HANDLE Hnd_HollowSpheroid_Bmp;
	HANDLE Hnd_SolidSpheroid_Bmp;

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

	HANDLE Hnd_Arch_Icon;
	HANDLE Hnd_Cone_Icon;
	HANDLE Hnd_Cyl_Icon;
	HANDLE Hnd_Spheriod_Icon;
	HANDLE Hnd_Box_Icon;
	HANDLE Hnd_Stairs_Icon;

	bool Debug_App;
	bool Debug_File;
	bool Just_Equity;
	bool New_Equity_Flag;

	HCURSOR CUR;

	int CursorPosX;
	int CursorPosY;

	HINSTANCE hInst;
	HWND MainHwnd;
	HWND ViewGLhWnd;
	HMENU hMenu;

	//      MFC
	CMainFrame *m_pMainFrame;
	CFusionDoc *pCFusionDoc;

	FILE *Write_DebugFile;

	void Get_Current_Document();

	CFusionDoc* m_pDoc;
};

extern SB_App* App;

#endif // !defined(AFX_SB_APP_H__F1CE337E_1C46_4F80_9639_566F8F7DFBD6__INCLUDED_)
