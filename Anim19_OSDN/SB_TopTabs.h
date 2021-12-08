/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_TopTabs
{
public:
	SB_TopTabs();
	~SB_TopTabs();

	bool Start_TopBar_Globals();
	void Reset_Class();

	void TogglePlayBmp(void);

	void UnCheck_All_MouseOption(HWND hDlg);

	HWND TabsHwnd;
	HWND Camera_TB_hWnd;
	HWND Tabs_TB_hWnd;

	HWND Motions_TB_hWnd;
	HWND Dimensions_TB_hWnd;
	HWND Groups_TB_hWnd;
	HWND Physics_TB_hWnd;
	HWND Editors_TB_hWnd;
	HWND File_TB_hWnd;

	HWND MouseOption_DlgHwnd;

	// Motions
	bool Toggle_Play_Flag;

protected:

	static LRESULT CALLBACK TopBar_Globals_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Camera_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Motions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dimensions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Groups_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Shapes_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Editors_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Files_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Tabs_Headers_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Start_Camera_TB(void);

	void Init_Bmps_Camera(void);
	void Init_Bmps_Globals(void);
	void Init_Bmps_Motions(void);
	void Init_Bmps_Dimensions(void);
	void Init_Bmps_Groups(void);

	void Start_Motions_TB(void);
	void Start_Dimensions_TB(void);
	void Start_Groups_TB(void);
	void Start_Shapes_TB(void);
	void Start_Editors_TB(void);
	void Start_Files_TB(void);

	void Start_Tabs_Headers(void);

	void Hide_Tabs(void);

	void Reset_Main_Controls(void);

	// Main Controls

	bool Toggle_Grid_Flag;
	bool Toggle_Hair_Flag;

	// Tabs
	bool Toggle_Tabs_Old_Flag;
	bool Toggle_Tabs_Motions_Flag;
	bool Toggle_Tabs_Dimensions_Flag;
	bool Toggle_Tabs_Groups_Flag;
	bool Toggle_Tabs_Shapes_Flag;
	bool Toggle_Tabs_Editors_Flag;
	bool Toggle_Tabs_File_Flag;

	// Camera
	bool Toggle_FirstCam_Flag;
	bool Toggle_FreeCam_Flag;

	// Dimensions - >ImGui Flags



	bool Toggle_GroupsOnly_Flag;
};

