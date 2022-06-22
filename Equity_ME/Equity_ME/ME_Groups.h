#pragma once
class ME_Groups
{
public:
	ME_Groups();
	~ME_Groups();

	bool Start_Groups();

	HWND RightGroups_Hwnd;

protected:

	static LRESULT CALLBACK Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

