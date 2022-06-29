#pragma once
class ME_Dialogs
{
public:
	ME_Dialogs();
	~ME_Dialogs();

	bool Show_ListData();

	int What_List;

protected:

	static LRESULT CALLBACK GroupData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	void List_GroupData(HWND hDlg);
	void List_ModelData(HWND hDlg);
};

