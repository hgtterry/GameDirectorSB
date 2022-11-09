#pragma once
class VM_ImGui
{
public:
	VM_ImGui();
	~VM_ImGui();

	void Load_Font(void);
	void ImGui_Set_Colours(void);

	void ImGui_FPS(void);

	void ImGui_Render_Loop(void);
	
	bool StartPos;
	bool Show_FPS;

	ImFont* font0;
	ImFont* font1;
	ImFont* font2;
	ImFont* fontDroid;
	
	MSG msg;

protected:

	
};

