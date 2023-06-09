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

class A_CreateBoxDialog
{
public:
	A_CreateBoxDialog(void);
	~A_CreateBoxDialog(void);

	void A_CreateBoxDialog::Start_CreateBox_Dlg();

	BrushTemplate_Box *pBoxTemplate;

	float	m_YSize;
	int		m_Solid;
	float	m_XSizeBot;
	float	m_XSizeTop;
	float	m_ZSizeBot;
	float	m_ZSizeTop;
	bool	m_TCut;
	float	m_Thickness;
	bool	m_TSheet;

	bool	m_UseCamPos;

	CFusionDoc			*m_pDoc;

private:

	static LRESULT CALLBACK CreateBox_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Members();
	void Get_DLG_Members(HWND hDlg);
	void Set_DLG_Members(HWND hDlg);
	void Set_BoxTemplate();

	void Set_Defaults(HWND hDlg);

	void CreateCube();
	void CreateNewTemplateBrush(Brush *pBrush);

	char BoxName[MAX_PATH];
};
