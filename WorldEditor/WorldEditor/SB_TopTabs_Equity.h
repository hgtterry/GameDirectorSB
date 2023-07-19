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

class SB_TopTabs_Equity
{
public:
	SB_TopTabs_Equity(void);
	~SB_TopTabs_Equity(void);

	void Start_Tabs(void);
	void Start_Tabs_Headers(void);

	HWND Tabs_TB_hWnd_Eq;
private:

	static LRESULT CALLBACK Tabs_Headers_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Files_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Start_Files_TB(void);

	HWND Test_TB_hWnd;

	bool Toggle_Tabs_Test_Flag;
	bool Toggle_Dimensions_Flag;
};


