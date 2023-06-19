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

class A_TabsGroups_Dlg
{
public:
	A_TabsGroups_Dlg(void);
	~A_TabsGroups_Dlg(void);

	void Show_GroupsDialog(bool Show);
	void Start_GroupsDialog();
	void Start_Properties_Dlg();

	void Get_Index(const Brush *b);
	void Fill_ListBox();
	void Update_Dlg_SelectedBrushesCount();

	bool Groups_Dlg_Created;

	HWND GroupsDlg_Hwnd;

private:

	static LRESULT CALLBACK Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void List_Selection_Changed();
	void OnSelchangeBrushlist(int Index);

	void List_BrushData(HWND hDlg);

	bool Show_Brush_Info(const Brush *b, HWND hDlg);
	bool Show_Brush_ListInfo(BrushList *BList, HWND hDlg);
	bool Show_Brush_Faces_Info(const FaceList *pList, HWND hDlg);
	bool Show_Face_Data(const Face *f, HWND hDlg);

	void List_SelectedBrushes(HWND hDlg);

	int Selected_Index;
	Brush*	Selected_Brush;
	CFusionDoc			*m_pDoc;
};
