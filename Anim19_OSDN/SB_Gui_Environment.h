/*
Copyright (c) 2022 - 2023 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Gui_Environment
{
public:
	SB_Gui_Environment(void);
	~SB_Gui_Environment(void);

	void Environ_PropertyEditor();
	void Dialog_Colour_Picker(void);
	void Start_Colour_Picker(Ogre::Vector3 Colour);
	void Do_Colour_Picker();

	bool Show_PropertyEditor;
	int PropertyEditor_Page;

	bool Show_ColourPicker;
	int Colour_Int_Red;
	int Colour_Int_Green;
	int Colour_Int_Blue;
	ImVec4 Float_Colour_Copy;
	bool ColourPicker_Canceled;
	ImVec4 Float_Colour;
	bool Float_Exit;

	float Float_PosX;
	float Float_PosY;
	bool Float_StartPos;
};

