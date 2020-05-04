#pragma once
class VM_TopBar
{
public:
	VM_TopBar();
	~VM_TopBar();

	bool Start_TopBar();
	void Reset_Class();

	void TogglePlayBmp(void);
	void UnCheck_All_MouseOption(HWND hDlg);

	HWND TabsHwnd;
	HWND Camera_TB_hWnd;
	HWND Tabs_TB_hWnd;

	HWND Motions_TB_hWnd;
	HWND Dimensions_TB_hWnd;
	HWND Groups_TB_hWnd;

	HWND MouseOption_DlgHwnd;

	// Motions
	bool Toggle_Play_Flag;

protected:

	static LRESULT CALLBACK TopMain_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK View_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Motions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Dimensions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Groups_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Tabs_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Start_View_TB(void);

	void Init_Bmps_TB1(void);
	void Init_Bmps_TB2(void);
	void Init_Bmps_Motions(void);

	void Start_Motions_TB(void);
	void Start_Dimensions_TB(void);
	void Start_Groups_TB(void);

	void Start_Tabs(void);

	void Hide_Tabs(void);

	bool Toggle_Faces_Flag;
	bool Toggle_Textures_Flag;
	bool Toggle_Points_Flag;
	bool Toggle_Bones_Flag;
	bool Toggle_Normals_Flag;
	bool Toggle_BBox_Flag;

	// Groups
	bool Toggle_Tabs_Old_Flag;
	bool Toggle_Tabs_Motions_Flag;
	bool Toggle_Tabs_Dimensions_Flag;
	bool Toggle_Tabs_Groups_Flag;

	// Camera
	bool Toggle_Model_Flag;
	bool Toggle_World_Flag;

	// Dimensions - >ImGui Flags
	


	bool Toggle_GroupsOnly_Flag;

};

