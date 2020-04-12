/*
Copyright (c) Vima19 Inflanite Software W.T.Flanigan H.C.Flanigan

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
class VM_Groups
{
public:
	VM_Groups();
	~VM_Groups();

	bool Start_Groups();
	void Update_Groups_Dialog(int Index);

	bool ChangeTexture_ModelLocation(void);

	int SelectedGroup;

	HWND RightGroups_Hwnd;

	HBITMAP	Sel_BaseBitmap;

	long BasePicWidth;
	long BasePicHeight;

protected:

	static LRESULT CALLBACK Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static bool CALLBACK ViewerBasePic(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool RenderTexture_Blit(HDC hDC, HBITMAP Bmp, const RECT *SourceRect, const RECT *DestRect);
};

