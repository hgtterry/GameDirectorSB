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

	bool Update_Transform_Dlg();

	bool Update_ListView_Objects();
	bool Update_ListView_Messages();
	bool Update_ListView_Move_Entities();
	bool Update_ListView_Sounds();
	bool Update_ListView_Collectables();
	bool Update_ListView_Physics();
	bool Update_ListView_Player_Physics();
	bool Update_ListView_Player();
	bool Update_ListView_Teleport();
	bool Update_ListView_Environment();
	bool Update_ListView_Particles();

	bool Edit_Player_Onclick(LPARAM lParam);
	bool Edit_Player_Physics_Onclick(LPARAM lParam);

	bool Edit_Object_OnClick(LPARAM lParam);
	bool Edit_Sounds_OnClick(LPARAM lParam);
	bool Edit_Messages_OnClick(LPARAM lParam);
	bool Edit_Move_Entity_OnClick(LPARAM lParam);
	bool Edit_Collectables_OnClick(LPARAM lParam);
	bool Edit_Teleport_OnClick(LPARAM lParam);
	bool Edit_Particles_OnClick(LPARAM lParam);
	

	void ListView_OnClickOptions(LPARAM lParam);

	
	bool ListView_Object_Physics_OnClick(LPARAM lParam);

	void Enable_Test_Button(bool Enable);
	void Enable_Delete_Button(bool Enable);

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

protected:

	static LRESULT CALLBACK GD_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Create_Properties_hLV(void);

	char btext[255];

	
};

