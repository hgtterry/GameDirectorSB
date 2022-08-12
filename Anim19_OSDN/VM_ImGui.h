#pragma once
class VM_ImGui
{
public:
	VM_ImGui();
	~VM_ImGui();

	void Reset_Class(void);

	void Load_Font(void);
	void ImGui_Set_Colours(void);

	void ImGui_FPS(void);

	void ImGui_Rotation2(void);
	void ImGui_Position(void);
	void ImGui_Scale(void);

	void ImGui_Image(void);
	void ImGui_GroupList(void);
	void ImGui_MotionList(void);
	void ImGui_Texture_Data(void);
	void ImGui_Model_Data(void);

	void Tabs_Render_Camera(void);
	void Tabs_Render_Motions(void);
	void Tabs_Render_Dimensions(void);
	void Tabs_Render_Groups(void);

	void ImGui_ProgressBar(void);
	void Start_ProgressBar(void);
	void Stop_ProgressBar(void);
	void Set_ProgressCount(float Count);
	bool Nudge();
	
	bool StartPos;

	bool StartPos_PB;

	bool Show_ImGui_Test;
	bool Show_FPS;

	bool Show_Progress_Bar;


	bool Show_Rotation;
	bool Show_Position;
	bool Show_Scale;
	bool Show_Image;
	bool Show_Group_List;
	bool Show_Motion_List;
	bool Show_ImGui_TextureData;
	bool Show_Model_Data;

	ImFont* font0;
	ImFont* font1;
	ImFont* font2;
	ImFont* fontDroid;
	
	float Model_XTranslate;
	float Model_YTranslate;
	float Model_ZTranslate;

	float progress;
	float Progress_Count;
	float Progress_Delta;
	MSG msg;

	float Test;

	bool Block;
	bool Block_Motion;
	bool Reset_Groups;

	char test[250];
	char* poo();
};

