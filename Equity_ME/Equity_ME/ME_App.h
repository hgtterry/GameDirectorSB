/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

class ME_App
{
public:
	ME_App();
	~ME_App();

	ME_Ogre*			CL_Ogre;		// Ogre Main Class [120122]
	ME_Utilities*		CL_Utilities;	// Maths String Routines [130122]

	bool InitApp(void);
	bool SetMainWin_Centre(void);

	void SetBrushes_Fonts(void);
	bool ResizeOgre_Window(void);

	HINSTANCE hInst;	// Store instance handle in our global variable [120122]

	HWND MainHwnd;		// Main Window hWnd [120122]
	HWND Fdlg;			// Main Window BackGround [120122]
	HWND ViewGLhWnd;	// Ogre Render Window [120122]
	
	HBRUSH AppBackground;	// Main App Background Colour [120122]
	HBRUSH BlackBrush;		// Black Brush Colour [120122]

	char EquityDirecory_FullPath[MAX_PATH];
};

extern ME_App* App;

