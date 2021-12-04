/*
	Copyright (c) GD10 (GameDirector) 2019 Inflanite Software W.T.Flanigan H.C.Flanigan B.Parkin

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
class GD19_Properties
{
public:
	GD19_Properties(void);
	~GD19_Properties(void);

	void Start_GD_Properties(void);

	bool ListView_Object_Physics_OnClick(LPARAM lParam);

	int Current_Selected_Object;

	bool Edit_Physics;
	bool ToggleObjectDebug;
	bool Object_Selection;
	bool Physics_Selection;
	bool Is_Player;
	bool Properties_Dlg_Active;

	HWND Properties_hLV;
	HWND Properties_Dlg_hWnd;
	int Edit_Category;
	char btext[255];

protected:

	static LRESULT CALLBACK GD_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Create_Properties_hLV(void);

};

