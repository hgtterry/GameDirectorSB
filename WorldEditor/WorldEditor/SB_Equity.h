#pragma once
class SB_Equity
{
public:
	SB_Equity(void);
	~SB_Equity(void);

	void Switch_3D_Window();

	void Start_Equity_Dialog();
	void Start_Equity_Dialog_New();

	void Auto_Load_File();
	void Show_Equity_Dialog(bool Show);

	void Preview_Selected();
	void Preview_All();

	bool mAutoLoad;

	bool EquitySB_Dialog_Created;

	HWND OgreView_3D_hWnd;
	HWND Equity_Main_hWnd;
	HWND Render_Buttons_hWnd;

	bool Close_Equity_Flag;

	Ogre::Vector3 Position_Offsets;

	static LRESULT CALLBACK Ogre3D_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

private:
	static LRESULT CALLBACK Equity_Dialog_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);
	static LRESULT CALLBACK Equity_Dialog_New_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);

	static LRESULT CALLBACK Render_Buttons_Proc(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam);


	bool Start_Render_Buttons();
	void Init_Bmps_Globals(void);

	void Resize_3DView();

	void Get_CurrentDocument();

	CFusionDoc* m_pDoc;
};

