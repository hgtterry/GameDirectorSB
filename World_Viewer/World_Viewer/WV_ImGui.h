#pragma once
class WV_ImGui
{
public:
	WV_ImGui();
	~WV_ImGui();

	void Load_Font(void);
	void ImGui_Set_Colours(void);

	void ImGui_Editor_Loop(void);

	void ImGui_FPS(void);

	void Start_Model_Data(void);
	void Model_Data_GUI(void);
	void Close_Model_Data(void);

	ImFont* font0;
	ImFont* font1;
	ImFont* font2;

	float PosX;
	float PosY;

	float Model_Data_PosX;
	float Model_Data_PosY;

	bool Show_Model_Data_F;
	bool Show_FPS_F;

	bool StartPos;
	
protected:

};

