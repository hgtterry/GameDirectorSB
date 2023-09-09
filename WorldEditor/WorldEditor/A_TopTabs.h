#pragma once

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

//#include "FUSIONView.h"
//#include "FUSIONDoc.h"


class SB_TopTabs
{

public:
	SB_TopTabs(void);
	~SB_TopTabs(void);

	bool Start_Headers_Tabs();
	void Reset_Tabs_Buttons();
	void Reset_Render_Buttons();
	void Reset_Brush_Buttons();
	void Select_Mode();

	void Update_Dlg_Controls();

	void Show_BrushPanel();

	bool Header_BrushModify_Flag;
	bool Textured_Flag;
	bool Brush_Select_Flag;
	bool OgreRunning_Flag;

	HWND Top_Tabs_Hwnd;
	HWND Brush_Modify_Panel_Hwnd;
	HWND File_Panel_Hwnd;
	HWND Test_Panel_Hwnd;
	HWND Equity_Panel_Hwnd;
	HWND Faces_Panel_Hwnd;
	HWND Camera_Panel_Hwnd;

private:
	static LRESULT CALLBACK TB_Headers_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK BrushModify_Panel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Top_File_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Top_Test_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Top_Faces_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Top_Camera_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Top_Equity_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	bool Start_File_Tab();
	bool Start_Test_Tab();
	bool Start_Equity_Tab();
	bool Start_Faces_Tab();
	bool Start_Camera_Tab();

	bool Start_BrushModify_Panel();
	
	void Select_MoveRotate();
	void Select_Scale();
	void Select_Shear();

	bool Wired_Flag;

	bool Quick_Command_Started;

	bool Header_File_Flag;
	bool Header_Test_Flag;
	bool Header_Equity_Flag;
	bool Header_Faces_Flag;
	bool Header_Camera_Flag;
	
	bool Brush_MoveRotate_Flag;
	bool Brush_Scale_Flag;
	bool Brush_Shear_Flag;

	CFusionDoc			*m_pDoc;

};
