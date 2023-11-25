/*
Copyright (c) World_Viewer 2023 Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Exporter
{
public:
	SB_Exporter(void);
	~SB_Exporter(void);

	void Ogre3D_Model(void);
	void Object_Model(void);
	void Autodesk_Model(void);
	void Milkshape_Model(void);

	void Start_Export_Dlg();

	bool Is_Canceled;
	bool Export_Selected;

	char mJustName[MAX_PATH];
	char mDirectory_Name[MAX_PATH];
	char mFolder_Path[MAX_PATH];

	HWND Export_Dlg_Hwnd;

private:

	static LRESULT CALLBACK Export_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_Dialog_Data(HWND m_hDlg);

	void Set_Dialog_Data_FromIndex(HWND m_hDlg);

	void List_File_Formats(HWND m_hDlg);
	
	int Selected_Index;

};

