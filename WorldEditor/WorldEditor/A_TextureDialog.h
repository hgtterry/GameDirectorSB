#pragma once

/*
Copyright (c) 2023 Equity_ME World Editor -- HGT Software W.T.Flanigan H.C.Flanigan

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

class A_TextureDialog
{
public:
	A_TextureDialog(void);
	~A_TextureDialog(void);

	void Start_TextureDialog();

	void Set_Txl_FileName();
	void Fill_ListBox();
	void Get_BitMap();
	HBITMAP CreateHBitmapFromgeBitmap (geBitmap *Bitmap, HDC hdc);

	void Apply_Texture();
	void List_Selection_Changed();
	void Select_Texture(int SelNum);
	void Show_Dialog(bool Show);
	int Get_Index_FromName(char* TextureName);

	HBITMAP	Sel_BaseBitmap;
	long BasePicWidth;
	long BasePicHeight;

	char m_CurrentTexture[MAX_PATH];

	bool f_TextureDlg_Active;
	HWND TextureDlg_Hwnd;

protected:

	static LRESULT CALLBACK TextureDialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static bool CALLBACK ViewerBasePic(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam);

	bool RenderTexture_Blit(HDC hDC, HBITMAP Bmp, const RECT *SourceRect, const RECT *DestRect);

};
