#pragma once
class VM_TopBar
{
public:
	VM_TopBar();
	~VM_TopBar();

	bool Start_TopBar();

	HWND TabsHwnd;
	HWND TB_1;

protected:

	static LRESULT CALLBACK TopBar_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK TB1_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void Start_TB1(void);
};

