/*	
	Copyright (c) Equity10 2016 HGT Software W.T.Flanigan B.Parkin H.C.Flanigan

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
class GD19_ToolBar
{
public:
	GD19_ToolBar(void);
	~GD19_ToolBar(void);


	void Start_TB1(void);

	void Create_ToolBars(void); // To Be Deleted

	void Set_TexturesOn(bool State);
	void Set_JointsOn(bool State);
	void Set_LightsOn(bool State);
	void Set_FacesOn(bool State);
	void Set_PointsOn(bool State);
	void Set_NormalsOn(bool State);
	void Set_BoundingBoxOn(bool State);

	void Init_Bmps(void);
	
	void UnCheck_All_MouseOption(HWND hDlg);

	void Toggle_TB1(void);
	bool TB_1_Active;
	
	HWND TB1;
	HWND TB2;
	HWND TB3;

	HWND TB_1;
	HWND hTooltip_TB_1;

	HWND MouseOption_DlgHwnd;
	

	bool FreeCam_Active;
	bool FirstPerson_Active;
	bool ThirdPerson_Active;
	bool Selection_Active;

protected:

	static LRESULT CALLBACK TopOgre_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK TB1_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

};

