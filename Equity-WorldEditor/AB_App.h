// SB_App.h: interface for the SB_App class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_SB_APP_H__F1CE337E_1C46_4F80_9639_566F8F7DFBD6__INCLUDED_)
#define AFX_SB_APP_H__F1CE337E_1C46_4F80_9639_566F8F7DFBD6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000



#include "AB_Export_RFW.h"
#include "A_FileIO.h"
#include "A_Dialogs.h"
#include "A_Scene.h"

class A_App  
{
public:

	AB_Export_RFW*			ABC_Export_RFW;
	A_FileIO*				CL_FileIO;
	A_Dialogs*				CL_Dialogs;
	A_Scene*				CL_Scene;

	A_App();
	virtual ~A_App();

	bool InitApp(void);
	void SetBrushes_Fonts(void);

	void Say(const char* Message);

	HBRUSH AppBackground;	// Main App Background Colour [120122]
	HBRUSH BlackBrush;		// Black Brush Colour [120122]
	HBRUSH Brush_White;		// Black Brush Colour [120122]
	HBRUSH Brush_Green;		// Black Brush Colour [120122]

	HFONT Font_CB15;
	HFONT Font_CB18;
	HFONT Font_Arial20;

	HINSTANCE hInst;
	HWND MainHwnd;
};

extern A_App* App;

#endif // !defined(AFX_SB_APP_H__F1CE337E_1C46_4F80_9639_566F8F7DFBD6__INCLUDED_)
