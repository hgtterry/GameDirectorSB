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

#pragma once
class SB_Brushes
{
public:
	SB_Brushes(void);
	~SB_Brushes(void);

	void Start_Dimensions_Dlg();
	void Update_Pos_Dlg(HWND hDlg);
	void Centre_CentreBrush();

	bool Dimensions_Dlg_Running;

	HWND Dimensions_Dlg_hWnd;

private:
	static LRESULT CALLBACK Dimensions_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Fill_ComboBox_PosDelta(HWND hDlg);

	void Move_Brush();
	void Rotate_Brush(float SX, float SY, float SZ);
	void Scale_Brush(float SX, float SY, float SZ);
	void Scale_Brush_Lock(bool increase);

	void Lock_Textures(bool flag);

	void EnableScaleControls_Dlg(HWND hDlg, bool Enable);

	void Get_Brush();

	float PosX_Delta;
	float PosY_Delta;
	float PosZ_Delta;

	float ScaleX_Delta;
	float ScaleY_Delta;
	float ScaleZ_Delta;

	bool ScaleLock_Flag;

	vertex_type Size;
	vertex_type Scale;

	geVec3d CenterOfSelection;
	geVec3d FinalScale;

	CFusionDoc* m_pDoc;
};

