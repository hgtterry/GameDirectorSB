#pragma once
class SB_ViewMgrDlg
{
public:
	SB_ViewMgrDlg(void);
	~SB_ViewMgrDlg(void);

	void Start_View_MgrDlg();

	void MaximizeUpperLeftPane();

private:
	static LRESULT CALLBACK View_MgrDlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

