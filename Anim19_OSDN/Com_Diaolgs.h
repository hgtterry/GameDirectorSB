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
class Com_Diaolgs
{
public:
	Com_Diaolgs();
	~Com_Diaolgs();

	void Start_Mouse_Sensitivity(HWND hDlg);
	bool StartBrowser(char* szInitDir, HWND hDlg);

	char BrowserMessage[MAX_PATH];
	TCHAR szSelectedDir[MAX_PATH];

protected:

	static LRESULT CALLBACK Mouse_Sensitivity_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static int __stdcall BrowseCallbackProc(HWND  hwnd, UINT  uMsg, LPARAM  lParam, LPARAM  lpData);
};

