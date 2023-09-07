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
class SB_ImGui
{
public:
	SB_ImGui();
	~SB_ImGui();

	void ImGui_Editor_Loop(void);

	void Render_FPS(void);
	void ImGui_FPS(void);

	void Start_Model_Data(void);
	void Model_Data_GUI(void);
	void Close_Model_Data(void);

	void Start_Camera_Pos(void);
	void Camera_Pos_GUI(void);
	void Close_Camera_Pos(void);

	void Start_BB_Data(void);
	void Model_BB_GUI(void);
	void Close_BB_Data(void);

	void Physics_Console_Gui(void);

	void Start_Dialog_Float(float Step, float StartValue, char* Banner);
	void BackGround_Render_Loop(void);

	bool Show_FPS;  // Show Frames Per Second [150122]
	bool StartPos;  // Position FPS Frame Flag [150122]

	bool Show_Model_Data_F;
	bool Show_Camera_Pos_F;
	bool Show_BB_Data_F;

	float PosX;
	float PosY;

	float Model_Data_PosX;
	float Model_Data_PosY;

	// -------------- Physics Console
	bool Disable_Physics_Console;
	bool Show_Physics_Console;
	float Physics_PosX;
	float Physics_PosY;
	bool Physics_Console_StartPos;

	// -------------- Float Dialog
	bool Show_Dialog_Float;
	float Float_Step;
	bool Float_Canceld;
	bool Float_StartPos;
	float Float_PosX;
	float Float_PosY;
	float m_Dialog_Float;
	float m_Dialog_Float_Copy;
	char Float_Banner[MAX_PATH];
	bool Float_Exit;

protected:

	void Load_Font(void);
	void ImGui_Set_Colours(void);

	void Dialog_Float(void);

	ImFont* font0;
	ImFont* font1;
	ImFont* font2;
	ImFont* fontDroid;

	CFusionDoc* m_pDoc;
	CEntity* pCameraEntity;

	bool PosX_Selected;
	bool PosY_Selected;
	bool PosZ_Selected;
};

