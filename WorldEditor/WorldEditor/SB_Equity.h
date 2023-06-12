#pragma once
class SB_Equity
{
public:
	SB_Equity(void);
	~SB_Equity(void);

	void Switch_3D_Window();
	void Start_Ogre_Dialog(bool AutoLoad);

	bool mAutoLoad;

	HWND OgreView_3D_hWnd;
	HWND TestHwnd;

	static LRESULT CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static LRESULT CALLBACK Ogre_Dialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	
	void Auto_Load_File();
	void Resize_3DView();

	bool EquitySB_Dialog_Created;
};

