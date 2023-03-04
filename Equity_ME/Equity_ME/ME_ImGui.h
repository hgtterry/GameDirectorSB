/*
Copyright (c) 2022 Equity_ME Model Editor -- Inflanite Software W.T.Flanigan H.C.Flanigan

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
class ME_ImGui
{
public:
	ME_ImGui();
	~ME_ImGui();

	void Start_Model_Data(void);
	void Close_Model_Data(void);

	void Start_Group_Data(void);
	void Close_Group_Data(void);

	void Start_App_Data(void);
	void Close_App_Data(void);

	void ImGui_Editor_Loop(void);

	void Render_FPS(void);
	void ImGui_Render_Model(void);

	void ImGui_FPS(void);

	bool Show_FPS;  // Show Frames Per Second [150122]
	bool StartPos;  // Position FPS Frame Flag [150122]

	void ImGui_Dimensions(void);

	bool Show_Dimensions;
	bool Show_ImGui_Test;

	bool Show_Model_Data_Flag;
	bool Show_Group_Data_Flag;
	bool Show_App_Data_Flag;

	float App_Data_PosX;
	float App_Data_PosY;

	float Model_Data_PosX;
	float Model_Data_PosY;

	float Group_Data_PosX;
	float Group_Data_PosY;

	float PosX;
	float PosY;

protected:

	void Model_Data_GUI(void);
	void Group_Data_GUI(void);
	void App_Data_GUI(void);

	void Load_Font(void);
	void ImGui_Set_Colours(void);

	void ImGui_Rotation(void);
	void ImGui_Position(void);

	ImFont* font0;
	ImFont* font1;
	ImFont* font2;
	ImFont* fontDroid;

	bool PosX_Selected;
	bool PosY_Selected;
	bool PosZ_Selected;
};

