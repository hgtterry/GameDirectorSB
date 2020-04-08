#pragma once
class VM_ImGui
{
public:
	VM_ImGui();
	~VM_ImGui();

	void Reset_Class(void);
	void Render_ImGui(void);
	void ImGui_FPS(void);

	void ImGui_Rotation(void);
	void ImGui_Position(void);
	void ImGui_Scale(void);
	void ImGui_Image(void);
	
	bool StartPos;

	bool Show_ImGui_Test;
	bool Show_FPS;

	bool Show_Rotation;
	bool Show_Position;
	bool Show_Scale;
	bool Show_Image;
	
	float Model_XTranslate;
	float Model_YTranslate;
	float Model_ZTranslate;

	float Test;
};

