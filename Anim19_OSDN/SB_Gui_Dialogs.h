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
class SB_Gui_Dialogs
{
public:
	SB_Gui_Dialogs(void);
	~SB_Gui_Dialogs(void);

	void Close_All_Dialogs(void);
	void BackGround_Render_Loop(void);

	void Start_Dialog_Float(float Step, float StartValue, char* Banner);

	void Start_Dialog_MessageEditor(int Index);

	void Start_Colour_Picker(Ogre::Vector3 Colour);

	void Dialog_Colour_Picker(void);

	void ImGui_ProgressBar2(void);
	void Start_ProgressBar(void);
	void Stop_ProgressBar(void);
	void Set_ProgressCount(float Count);
	bool SB_Gui_Dialogs::Nudge();

	float progress;
	float Progress_Count;
	float Progress_Delta;
	bool StartPos_PB;

	bool Show_Progress_Bar2;
	// -------------- General
	ImVec4 Float_Colour;

	// -------------- Float Dialog
	bool Show_Dialog_Float;
	float Float_Step;
	bool Float_Canceld;
	bool Float_StartPos;
	float Float_PosX;
	float Float_PosY;
	float m_Dialog_Float;
	float m_Dialog_Float_Copy;
	char Float_Banner[MAX_PATH];
	bool Float_Exit;

	// -------------- Message Editor Dialog
	bool Centre_X_Selected;
	bool Centre_Y_Selected;
	bool Show_Dialog_MessageEditor;
	bool MessageEditor_Canceld;
	float Message_Editor_PosX;
	float Message_Editor_PosY;
	bool Message_Editor_StartPos;
	int Message_Index;
	ImVec4 BackGround_color;

	// -------------- Dialog Colour Picker
	bool Show_ColourPicker;
	int Colour_Int_Red;
	int Colour_Int_Green;
	int Colour_Int_Blue;
	ImVec4 Float_Colour_Copy;
	bool ColourPicker_Canceled;

	MSG msg;

	void Dialog_Float(void);
	void Dialog_MessageEditor(void);
};

