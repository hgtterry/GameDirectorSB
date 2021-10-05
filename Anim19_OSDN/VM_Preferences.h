#pragma once
class VM_Preferences
{
public:
	VM_Preferences();
	~VM_Preferences();

	bool Start_Preferences();

protected:

	static LRESULT CALLBACK Preferences_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};

