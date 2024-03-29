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

class A_CreateConeDialog
{
public:
	A_CreateConeDialog(void);
	~A_CreateConeDialog(void);

	void Start_CreateCone_Dlg();

	BrushTemplate_Cone *pConeTemplate;

	int		m_Style;
	float	m_Width;
	float	m_Height;
	int		m_VerticalStrips;
	float	m_Thickness;
	bool	m_TCut;

	bool	m_UseCamPos;

private:

	static LRESULT CALLBACK CreateCone_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Members();
	void Set_DLG_Members(HWND hDlg);
	void Get_DLG_Members(HWND hDlg);
	void Set_ConeTemplate();

	void Set_Defaults(HWND hDlg);

	void CreateCone();
	void CreateNewTemplateBrush(Brush *pBrush);

	CFusionDoc			*m_pDoc;

	char ConeName[MAX_PATH];
};
