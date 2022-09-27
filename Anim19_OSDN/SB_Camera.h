/*
Copyright (c) 2021 Scene Builder and Equity -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Camera
{
public:
	SB_Camera();
	~SB_Camera();

	void Add_New_Camera(void);
	bool Start_Camera_PropsPanel();
	void Hide_Cam_Dlg(bool Show);

	void Reset_View(void);
	void Zoom(void);

	void Set_Camera(int Index);
	void Update_Camera(int Index);

	float CamPos_X;
	float CamPos_Y;
	float CamPos_Z;

	float LookAt_X;
	float LookAt_Y;
	float LookAt_Z;

	char Camera_Name[255];	// Camera Name [211121]

	HWND Cam_Props_HWND;

	HTREEITEM FileViewItem; // Holder for Camera File view item [211121]

protected:

	static LRESULT CALLBACK Camera_PropsPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Update_Camera_StartUp(void);
};

