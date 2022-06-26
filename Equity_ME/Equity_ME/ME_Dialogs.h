#pragma once
class ME_Dialogs
{
public:
	ME_Dialogs();
	~ME_Dialogs();

	bool Show_GroupData();

protected:

	static LRESULT CALLBACK GroupData_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

};

