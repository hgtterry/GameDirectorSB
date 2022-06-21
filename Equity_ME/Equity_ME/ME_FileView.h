#pragma once
class ME_FileView
{
public:
	ME_FileView();
	~ME_FileView();

	void Start_FileView(void);


protected:

	static LRESULT CALLBACK ListPanel_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
};



