#pragma once
class VM_TopBar
{
public:
	VM_TopBar();
	~VM_TopBar();

	bool Start_TopBar_Globals();
	void Reset_Class();

	void TogglePlayBmp(void);
	void ToggleTexturesBmp(bool Show);

	void UnCheck_All_MouseOption(HWND hDlg);

	HWND TabsHwnd;
	HWND Camera_TB_hWnd;
	HWND Tabs_TB_hWnd;

	HWND Motions_TB_hWnd;
	HWND Dimensions_TB_hWnd;
	HWND Groups_TB_hWnd;
	HWND Physics_TB_hWnd;
	HWND Editors_TB_hWnd;

	HWND MouseOption_DlgHwnd;

	// Motions
	bool Toggle_Play_Flag;

protected:

	static LRESULT CALLBACK TopBar_Globals_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Camera_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Motions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dimensions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Groups_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Shapes_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Editors_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Tabs_Headers_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Start_Camera_TB(void);

	void Init_Bmps_Camera(void);
	void Init_Bmps_Globals(void);
	void Init_Bmps_Motions(void);
	void Init_Bmps_Dimensions(void);
	void Init_Bmps_Groups(void);

	void Start_Motions_TB(void);
	void Start_Dimensions_TB(void);
	void Start_Groups_TB(void);
	void Start_Shapes_TB(void);
	void Start_Editors_TB(void);

	void Start_Tabs_Headers(void);

	void Hide_Tabs(void);

	void Reset_Main_Controls(void);

	// Main Controls
	bool Toggle_Faces_Flag;
	bool Toggle_Textures_Flag;
	bool Toggle_Points_Flag;
	bool Toggle_Bones_Flag;
	bool Toggle_Normals_Flag;
	bool Toggle_BBox_Flag;
	bool Toggle_Grid_Flag;
	bool Toggle_Hair_Flag;

	// Tabs
	bool Toggle_Tabs_Old_Flag;
	bool Toggle_Tabs_Motions_Flag;
	bool Toggle_Tabs_Dimensions_Flag;
	bool Toggle_Tabs_Groups_Flag;
	bool Toggle_Tabs_Shapes_Flag;
	bool Toggle_Tabs_Editors_Flag;

	// Camera
	bool Toggle_FirstCam_Flag;
	bool Toggle_FreeCam_Flag;

	// Dimensions - >ImGui Flags
	


	bool Toggle_GroupsOnly_Flag;

};

