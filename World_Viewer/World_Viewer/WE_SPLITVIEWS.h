#pragma once

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
*/ // :- Terry and Hazel Flanigan 2023

class WE_SpliterViews
{
public:
	WE_SpliterViews();
	~WE_SpliterViews();

	static LRESULT CALLBACK ViewerMain_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Create_Left_Window();
	void Create_Right_Window();
	void Create_Bottom_Left_Window();

	bool Init_Views();
	bool Resize_Windows(HWND hDlg, int NewWidth, int NewDepth);

	bool Resize_Fldg(void);

	void Update_Views();

	void MoveCamera(HWND hwnd);

	HWND Left_Window_Hwnd;
	HWND Right_Window_Hwnd;

	HWND Bottom_Left_Hwnd;
	HWND Bottom_Right_Hwnd;

	int nleftWnd_width;
	int nleftWnd_Depth;



private:

	static LRESULT CALLBACK Left_Window_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Right_Window_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Bottom_Left_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	
	bool Draw_Grid(HDC hDC, int Interval, RECT Rect);

	int LEFT_WINDOW_WIDTH;

	int LEFT_WINDOW_DEPTH;
	int TOP_POS_BOTLEFT;

	int RIGHT_MINIMUM_SPACE;
	int LEFT_MINIMUM_SPACE;

	bool Do_Width;
	bool Do_Depth;
	bool Do_All;

	HBRUSH BackGround_Brush;
};

