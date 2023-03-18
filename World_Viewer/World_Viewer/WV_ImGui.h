#pragma once
class VM_ImGui
{
public:
	VM_ImGui();
	~VM_ImGui();

	void Load_Font(void);
	void ImGui_Set_Colours(void);

	ImFont* font0;
	ImFont* font1;
	ImFont* font2;
	
protected:

};

