#pragma once
class VM_ImGui
{
public:
	VM_ImGui();
	~VM_ImGui();

	void Render_ImGui(void);
	void ImGui_FPS(void);
	void ImGui_Rotation(void);
	
	bool StartPos;

	bool Show_ImGui_Test;
	bool Show_FPS;

	bool Show_Rotation;

	float Test;
};

