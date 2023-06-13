#pragma once
class SB_Equity
{
public:
	SB_Equity(void);
	~SB_Equity(void);

	void Switch_3D_Window();
	void Start_Equity_Dialog(bool AutoLoad);

	bool mAutoLoad;

	bool EquitySB_Dialog_Created;

	HWND OgreView_3D_hWnd;
	HWND Equity_Main_hWnd;
	HWND Render_Buttons_hWnd;

	static LRESULT CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static LRESULT CALLBACK Equity_Dialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Render_Buttons_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


	bool Start_Render_Buttons();
	void Init_Bmps_Globals(void);

	void Auto_Load_File();
	void Resize_3DView();

};
