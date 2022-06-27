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

