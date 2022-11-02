/*
Copyright (c) 2021 EquitySB and EquityME -- HGTO Software W.T.Flanigan H.C.Flanigan

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

:- Terry and Hazel Flanigan 2022

*/

#pragma once
class Base_Panel
{
public:

	Base_Panel();
	~Base_Panel();

	void Set_ImGui_Panel_Name(void);

	void Render_ImGui_Panel(void);

	bool Show_Panel_Flag;
	bool Deleted;
	bool Altered;

	int Unique_ID;

	char Panel_Name[MAX_PATH];
	char Text[MAX_PATH];

	char ImGui_Panel_Name[MAX_PATH];

	int Counter;

	float PosX;
	float PosY;
	//------------------------------ ListView

	HTREEITEM FileViewItem;
};

