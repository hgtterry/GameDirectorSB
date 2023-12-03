#pragma once
class SB_ViewMgrDlg
{
public:
	SB_ViewMgrDlg(void);
	~SB_ViewMgrDlg(void);

	void Start_View_MgrDlg();
	void RestoreAllPanes();

	bool View_MgrDlg_Active;
	bool LinkViews_Flag;
	bool WorldView_Active_Flag;

	HWND MgrDlg_hWnd;

private:
	static LRESULT CALLBACK View_MgrDlg_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void MaximizeUpperLeftPane();
	void MaximizeUpperRightPane();
	void MaximizeLowerLeftPane();
	void MaximizeLowerRightPane();

	void Reset_Flags();

	bool TopLeft_Flag;
	bool TopRight_Flag;
	bool BottomLeft_Flag;
	bool BottomRight_Flag;
};

