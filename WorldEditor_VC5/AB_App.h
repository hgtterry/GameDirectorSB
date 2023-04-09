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

#include "A_Export_World.h"

class A_App  
{
public:

	A_App();
	virtual ~A_App();

	AB_Export_RFW*				ABC_Export_RFW;
	A_FileIO*					CL_FileIO;
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
	A_Camera*					CL_Camera;
	A_TopTabs*					CL_TopTabs;
	A_File*						CL_File;

	A_Export_World*				CL_Export_World;

	bool InitApp(void);
	void InitMFC(void);

	void SetBrushes_Fonts(void);
	void LoadProgramResource(void);

	void Say(const char* Message, char* Message2 = NULL);
	void Say_Int(int Value);
	void Say_Float(float Value);
	bool IsProcessRunning(char* executableName);

	bool Custom_Button_Normal(LPNMCUSTOMDRAW item);
	bool Custom_Button_Normal_MFC(LPDRAWITEMSTRUCT lpDIS,HWND hDlg);

	bool Custom_Button_Toggle(LPNMCUSTOMDRAW item, bool Toggle);
	bool Custom_Button_Toggle_MFC(LPDRAWITEMSTRUCT lpDIS,HWND hDlg, bool Toggle);

	HBRUSH CreateGradientBrush(COLORREF top, COLORREF bottom, LPNMCUSTOMDRAW item);

	char WorldEditor_Directory[MAX_PATH];

	HBRUSH AppBackground;	
	HBRUSH BlackBrush;		
	HBRUSH Brush_White;		
	HBRUSH Brush_Green;		

	HBRUSH Brush_But_Pressed;
	HBRUSH Brush_But_Normal;
	HBRUSH Brush_But_Hover;

	HFONT Font_CB15;
	HFONT Font_CB18;
	HFONT Font_Arial20;
	HFONT Font_Banner;

	HANDLE Hnd_HollowBox_Bmp;
	HANDLE Hnd_SolidBox_Bmp;

	HANDLE Hnd_HollowSpheroid_Bmp;
	HANDLE Hnd_SolidSpheroid_Bmp;

	HANDLE Hnd_Arch_Icon;
	HANDLE Hnd_Cone_Icon;
	HANDLE Hnd_Cyl_Icon;
	HANDLE Hnd_Spheriod_Icon;
	HANDLE Hnd_Box_Icon;
	HANDLE Hnd_Stairs_Icon;

	bool Debug_App;

	HINSTANCE hInst;
	HWND MainHwnd;

	HMENU hMenu;

	//      MFC
	CMainFrame *m_pMainFrame;
	CFusionDoc *pCFusionDoc;

	//m_pMainFrame		=(CMainFrame *)AfxGetMainWnd();
};

extern A_App* App;

#endif // !defined(AFX_SB_APP_H__F1CE337E_1C46_4F80_9639_566F8F7DFBD6__INCLUDED_)
