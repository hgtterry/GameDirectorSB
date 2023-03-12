#pragma once

/*
Copyright (c) 2022- 2023 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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

class ME_Editor_Gui
{
public:
	ME_Editor_Gui();
	~ME_Editor_Gui();

	void ImGui_Editor_Loop(void);

	void Start_Model_Data(void);
	void Model_Data_GUI(void);
	void Close_Model_Data(void);

	void Start_Group_Data(void);
	void Group_Data_GUI(void);
	void Close_Group_Data(void);

	void Start_App_Data(void);
	void App_Data_GUI(void);
	void Close_App_Data(void);

	bool Show_Model_Data_F;
	bool Show_Group_Data_F;
	bool Show_App_Data_F;

	float Model_Data_PosX;
	float Model_Data_PosY;

	float Group_Data_PosX;
	float Group_Data_PosY;

	float App_Data_PosX;
	float App_Data_PosY;
};

