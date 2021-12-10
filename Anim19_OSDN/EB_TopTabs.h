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
class EB_TopTabs
{
public:
	EB_TopTabs();
	~EB_TopTabs();

	void Start_Tabs(void);

	void Update_Textures_Combo(void);

	HWND TexturesCombo_Hwnd;

protected:

	static LRESULT CALLBACK Tabs_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Files_ETB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Camera_ETB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Textures_ETB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Start_Files_ETB(void);
	void Start_Camera_ETB(void);
	void Start_Textures_ETB(void);

	void Hide_Tabs(void);

	HWND Tabs_hWnd;
	HWND File_ETB_hWnd;
	HWND Camera_ETB_hWnd;
	HWND Textures_ETB_hWnd;

	bool Toggle_Tabs_File_Flag;
	bool Toggle_Tabs_Cam_Flag;
	bool Toggle_Tabs_Textures_Flag;
};

