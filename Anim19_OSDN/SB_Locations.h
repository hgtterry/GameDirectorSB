/*
Copyright (c) 2022 GameDirectorSB and EquityME -- HGTInflanite Software W.T.Flanigan H.C.Flanigan

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
class SB_Locations
{
public:

	SB_Locations(void);
	~SB_Locations(void);

	void Start_Locations_Dlg();
	void Create_Location_Entity(char* name);
	void Goto_Location(int Index);
	void Set_To_PlayerView();

protected:

	static LRESULT CALLBACK Locations_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Set_To_FreeCam();
	void Delete_Location();
	void Save_Location();
	void Move_Player_To_Camera();

	void Init_Bmps_PlayerLocations();

	HWND Locations_Dlg_hWnd;

	bool Toggle_Player_Flag;
	bool Toggle_FreeCam_Flag;
};

