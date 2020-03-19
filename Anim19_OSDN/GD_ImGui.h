#pragma once

class GD_ImGui
{
public:
	GD_ImGui();
	~GD_ImGui();

	void ImGui_Selection_Dlg(void);
	void Load_Font(void);

	void Render_Main_Panels(void);
	void Render_Panels(void);

	void ImGui_FPS(void);
	void ImGui_Preferences(void);

	void ImGui_PhysicsConsole(void);

	void ShowExampleAppLog(void);

	void ImGui_Test_Log(char* Message);

	void Object_Properties(void);
	void ImGui_Properties(void);

	void ImGui_Scene_Data(void);
	void ImGui_Dimensions(void);
	void Debug_Player(bool* p_open);

	void Camera_Object(void);

	void ShowExampleAppPropertyEditor(bool* p_open);

	void ImGui_FileView(void);
	
	void ImGui_Set_Colours(void);
	void Update_StaticData(void);

	void Toggle_X(bool x, bool y, bool z);

	bool StartPos;
	bool Show_OgreData;
	bool Show_ImGui_Test;
	bool Show_Object_Data;
	bool Show_PhysicsConsole;
	bool Show_ImGui_Counters;
	bool Show_ImGui_Dimensions;
	bool Show_ImGui_Properties_Editor;
	bool Show_ImGui_Debug_Player;
	bool Show_ImGui_FileView;
	bool Show_ImGui_Preferences;
	bool Show_ImGui_Log;
	bool Show_Propertities;
	bool Show_Camera_Object;

	char Edit_Category_Str[255];
	char Edit_Type_Str[255];
	char Edit_Usage_Str[255];

	char Log_Message[255];

	ImFont* font0;
	ImFont* font1;
	ImFont* font2;
	ImFont* fontDroid;

	int Block;

	bool BlockX;
	bool BlockY;
	bool BlockZ;
	bool Lock_X;
	bool Lock_Y;
	bool Lock_Z;

	bool Add_Log;

	btVector3 SetAxis;

protected:

	static LRESULT CALLBACK ImGui_Selection_Dlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

