#pragma once
class ME_Dialogs
{
public:
	ME_Dialogs();
	~ME_Dialogs();

	bool Show_ListData();
	void Start_Speed_Camera();

	int What_List;

protected:

	static LRESULT CALLBACK GroupData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Speed_Camera_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void List_GroupData(HWND hDlg);
	void List_ModelData(HWND hDlg);

	void UnCheck_All_SpeedMouseOption();

	bool Mouse_Normal;
	bool Mouse_Slow;
	bool Mouse_VerySlow;
	bool Mouse_Fast;
};

