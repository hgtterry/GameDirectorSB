/*
Copyright (c) 2022 EquitySB Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Props_Dialogs
{
public:
	SB_Props_Dialogs();
	~SB_Props_Dialogs();

	bool Start_Props_Dialogs();

	void Start_Area_PropsPanel();
	void Hide_Dimensions_Dlg(bool Show, bool Lock_Dimensions);
	void Hide_Physics_Reset_Dlg(bool Show);
	void Hide_Debug_Dlg(bool Show);
	void Hide_Panel_Test_Dlg(bool Show);
	void Hide_Area_Dlg(bool Show);
	void Hide_Details_Goto_Dlg(bool Show);
	void Hide_Material_Dlg(bool Show);

	bool Start_Dialog_Dimensions();
	bool Start_Dialog_PhysicsReset();
	bool Start_Dialog_Debug();
	bool Start_Panels_Test_Dlg();
	void Start_Details_Goto_Dlg(void);
	void Start_Materials_PropsPanel();

	void Init_Bmps_Debug();
	void Init_Bmps_Dimensions();
	void Init_Bmps_DetailsGo();
	void Init_Bmps_PhysicsReset();

	//void Set_Debug_Buttons();

	bool Show_Area_Physics_Debug;

	HWND Dimensions_Dlg_hWnd;
	HWND PhysicsReset_Dlg_hWnd;
	HWND Panel_Test_Dlg_hWnd;
	HWND Debug_Dlg_hWnd;
	HWND Area_Props_HWND;
	HWND Details_Goto_Hwnd;
	HWND Material_Props_Hwnd;

protected:
	static LRESULT CALLBACK Dialog_Dimensions_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dialog_PhysicsReset_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dialog_Debug_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Panels_Test_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Area_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Details_Goto_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Materials_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

