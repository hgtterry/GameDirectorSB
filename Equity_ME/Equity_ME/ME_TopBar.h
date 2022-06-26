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
class ME_TopBar
{
public:
	ME_TopBar();
	~ME_TopBar();

	bool Start_TopBar();

protected:

	static LRESULT CALLBACK TopBar_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Tabs_Headers_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Group_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Init_Bmps_Globals(void);

	void Start_Tabs_Headers(void);
	void Start_Group_TB(void);
	void Init_Bmps_Group(void);

	bool Show_Model_Data;
	bool Toggle_Grid_Flag;
	bool Toggle_BBox_Flag;

	bool Toggle_Tabs_Group_Flag;

	bool Toggle_GroupInfo_Flag;

	HWND TabsHwnd;
	HWND Tabs_TB_hWnd;
	HWND Group_TB_hWnd;
};

