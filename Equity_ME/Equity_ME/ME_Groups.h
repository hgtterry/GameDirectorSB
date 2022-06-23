#pragma once
class ME_Groups
{
public:
	ME_Groups();
	~ME_Groups();

	bool Start_Groups();
	bool Update_Groups();

	int Selected_Group;

	HWND RightGroups_Hwnd;

protected:

	static LRESULT CALLBACK Groups_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

