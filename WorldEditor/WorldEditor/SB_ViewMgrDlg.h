#pragma once
class SB_ViewMgrDlg
{
public:
	SB_ViewMgrDlg(void);
	~SB_ViewMgrDlg(void);

	void Start_View_MgrDlg();

	void RestoreAllPanes();

private:
	static LRESULT CALLBACK View_MgrDlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void MaximizeUpperLeftPane();
	void MaximizeUpperRightPane();
	void MaximizeLowerLeftPane();
	void MaximizeLowerRightPane();
};

