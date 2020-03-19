/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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

#include <OgreBorderPanelOverlayElement.h>
#include <OgreFontManager.h>

class GD19_Panel
{
public:
	GD19_Panel(char* PanelName,char* OverlayName, char* TextAreaName);
	~GD19_Panel(void);

	bool CreateTextOverlay(char* PanelName, char* OverlayName, char* TextAreaName);

	char mOverlayName[256];
	char mTextAreaName[256];
	char mPanel_Name[256];

	char mText[256];
	char mFont_Name[256];

	int Font_Size;

	float Red;
	float Green;
	float Blue;

	float mText_Pos_X;
	float mText_Pos_Y;

	float mPanel_Pos_X;
	float mPanel_Pos_Y;

	float mPanel_Width;
	float mPanel_Height;


	BorderPanelOverlayElement* panel;
	TextAreaOverlayElement* textArea;
	TextAreaOverlayElement* LoadingText;
	Overlay* overlay;

};

