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
	void Object_Selection(void);
	void Fire_Target(void);

	void ImGui_Image(void);
	void ImGui_GroupList(void);
	void ImGui_MotionList(void);
	void ImGui_Texture_Data(void);

	void ImGui_Model_Data(void);
	void ImGui_App_Data(void);

	void ImGui_Editor_Loop(void);
	
	void ImGui_Collision_Debug(void);

	void Set_ProgressCount(float Count);
	bool Nudge();

	bool StartPos;

	bool StartPos_PB;

	bool Show_ImGui_Test;
	bool Show_FPS;

	bool Show_Progress_Bar;

	bool Show_Image;
	bool Show_Group_List;
	bool Show_Motion_List;
	bool Show_ImGui_TextureData;
	bool Show_Model_Data;
	bool Show_App_Data;
	bool Show_Object_Data;
	bool Show_Collision_Debug;
	bool Show_Object_Selection;
	bool Show_Fire_Target;

	ImFont* font0;
	ImFont* font1;
	ImFont* font2;
	ImFont* font3;
	ImFont* fontDroid;
	
	float Model_XTranslate;
	float Model_YTranslate;
	float Model_ZTranslate;

	float progress;
	float Progress_Count;
	float Progress_Delta;
	MSG msg;

	float Test;

	float PosX;
	float PosY;

	bool Block;
	bool Block_Motion;
	bool Reset_Groups;

	int Object_Index;
	
protected:

	void ImGui_Object_Data(void);
};

