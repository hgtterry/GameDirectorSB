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
class SB_Properties
{
public:
	SB_Properties();
	~SB_Properties();

	void Reset_Class();

	void Start_GD_Properties(void);

	void Clear_Listview(); 
	void Mark_As_Altered(int Index);

	bool Update_ListView_Player();
	bool Update_ListView_Player_Physics();
	bool Update_ListView_Camera();
	bool Update_ListView_Area();
	bool Update_ListView_Objects();
	bool Update_ListView_Messages();
	bool Update_ListView_Sounds();
	bool Update_ListView_Level();
	bool Update_ListView_Move_Entities();
	bool Update_ListView_Teleport();
	bool Update_ListView_Collectables();
	bool Update_ListView_Counters();
	
	bool Properties_Dlg_Active;

	int Current_Selected_Object; // Object Index of Currently Selected Object [041221]

	int Edit_Category; // Category of Currently Selected Object [041221]

	bool Is_Player;

	bool Edit_Physics; // Flag for Edit Physics or Object [041221]

	HWND Properties_Dlg_hWnd;
	HWND Properties_hLV;

protected:

	static LRESULT CALLBACK GD_Properties_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Create_Properties_hLV(void);

	void ListView_OnClickOptions(LPARAM lParam);

	bool Edit_Area_Onclick(LPARAM lParam);
	bool Edit_Player_Onclick(LPARAM lParam);
	bool Edit_Player_Physics_Onclick(LPARAM lParam);
	bool Edit_Object_Onclick(LPARAM lParam);
	bool Edit_Messages_OnClick(LPARAM lParam);
	bool Edit_Camera_Onclick(LPARAM lParam);
	bool Edit_Move_Entity_OnClick(LPARAM lParam);
	bool Edit_Sounds_OnClick(LPARAM lParam);
	bool Edit_Teleport_OnClick(LPARAM lParam);
	bool Edit_Collectables_OnClick(LPARAM lParam);
	bool Edit_Counters_OnClick(LPARAM lParam);
	
	char btext[20]; // ListView_GetItemText Text Holder for Compare [041221]
	
};

