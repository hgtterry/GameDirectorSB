#pragma once
class VM_TopBar
{
public:
	VM_TopBar();
	~VM_TopBar();

	bool Start_TopBar();

	HWND TabsHwnd;
	HWND TB_1;
	HWND Motions_TB_hWnd;
	HWND Tabs_TB_hWnd;

protected:

	static LRESULT CALLBACK TopBar_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK TB1_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Motions_TB_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Tabs_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Start_TB1(void);
	void Init_Bmps_TB1(void);

	void Start_Motions_TB(void);

	void Start_Tabs(void);
};

