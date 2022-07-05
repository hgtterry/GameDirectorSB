/*
Copyright (c) 2022 Equity_ME Model Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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
class ME_Groups
{
public:
	ME_Groups();
	~ME_Groups();

	void Reset_Class(void);

	bool Start_Groups();
	bool Update_Groups();

	int Selected_Group;

	bool RightGroups_Visable;

	HWND RightGroups_Hwnd;

	HBITMAP	Sel_BaseBitmap;
	long BasePicWidth;
	long BasePicHeight;

protected:

	static LRESULT CALLBACK Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static bool CALLBACK ViewerBasePic(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool RenderTexture_Blit(HDC hDC, HBITMAP Bmp, const RECT *SourceRect, const RECT *DestRect);
};

