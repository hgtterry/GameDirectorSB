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

class A_TabsTemplates_Dlg
{
public:
	A_TabsTemplates_Dlg(void);
	~A_TabsTemplates_Dlg(void);

	void Show_TemplatesDialog(bool Show);
	void Start_TemplatesDialog();

	void CreateNewTemplateBrush(Brush *pBrush);
	void Enable_Insert_Button(bool Enable);

	HWND TemplatesDlg_Hwnd;

private:

	static LRESULT CALLBACK Templates_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Icons();

	bool Insert_Enabled_Flag;

};
